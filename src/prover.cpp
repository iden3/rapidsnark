#include <gmp.h>
#include <string>
#include <cstring>
#include <cstdarg>
#include <stdexcept>
#include <alt_bn128.hpp>
#include <nlohmann/json.hpp>
#include "prover.h"
#include "groth16.hpp"
#include "zkey_utils.hpp"
#include "wtns_utils.hpp"
#include "binfile_utils.hpp"
#include "fileloader.hpp"

using json = nlohmann::json;


class InvalidWitnessLengthException : public std::invalid_argument
{
public:
    explicit InvalidWitnessLengthException(const std::string &msg)
        : std::invalid_argument(msg) {}
};

static void
CopyError(
    char                 *error_msg,
    size_t                error_msg_maxsize,
    const std::exception &e)
{
    if (!error_msg || error_msg_maxsize == 0) return;
    std::snprintf(error_msg, error_msg_maxsize, "%s", e.what());
}

static void
CopyErrorFmt(
    char               *error_msg,
    unsigned long long  error_msg_maxsize,
    const char         *format,
    ...) __attribute__((format(printf, 3, 4)));

static void
CopyErrorFmt(
    char               *error_msg,
    unsigned long long  error_msg_maxsize,
    const char         *format,
    ...)
{
    if (!error_msg || error_msg_maxsize == 0) return;

    va_list args;
    va_start(args, format);
    std::vsnprintf(error_msg, error_msg_maxsize, format, args);
    va_end(args);
}

static unsigned long long
ProofBufferMinSize()
{
    return 810;
}

static unsigned long long
PublicBufferMinSize(unsigned long long count)
{
    return count * 82 + 4;
}

static bool
PrimeIsValid(mpz_srcptr prime)
{
    mpz_t altBbn128r;

    mpz_init(altBbn128r);
    mpz_set_str(altBbn128r, "21888242871839275222246405745257275088548364400416034343698204186575808495617", 10);

    const bool is_valid = (mpz_cmp(prime, altBbn128r) == 0);

    mpz_clear(altBbn128r);

    return is_valid;
}

static std::string
BuildPublicString(AltBn128::FrElement *wtnsData, uint32_t nPublic)
{
    json jsonPublic;
    AltBn128::FrElement aux;
    for (u_int32_t i=1; i<= nPublic; i++) {
        AltBn128::Fr.toMontgomery(aux, wtnsData[i]);
        jsonPublic.push_back(AltBn128::Fr.toString(aux));
    }

    return jsonPublic.dump();
}

class Groth16Prover
{
    BinFileUtils::BinFile zkey;
    std::unique_ptr<ZKeyUtils::Header> zkeyHeader;
    std::unique_ptr<Groth16::Prover<AltBn128::Engine>> prover;

public:
    Groth16Prover(const void         *zkey_buffer,
                  unsigned long long  zkey_size)

        : zkey(zkey_buffer, zkey_size, "zkey", 1),
          zkeyHeader(ZKeyUtils::loadHeader(&zkey))
    {
        if (!PrimeIsValid(zkeyHeader->rPrime)) {
            throw std::invalid_argument("zkey curve not supported");
        }

        prover = Groth16::makeProver<AltBn128::Engine>(
            zkeyHeader->nVars,
            zkeyHeader->nPublic,
            zkeyHeader->domainSize,
            zkeyHeader->nCoefs,
            zkeyHeader->vk_alpha1,
            zkeyHeader->vk_beta1,
            zkeyHeader->vk_beta2,
            zkeyHeader->vk_delta1,
            zkeyHeader->vk_delta2,
            zkey.getSectionData(4),    // Coefs
            zkey.getSectionData(5),    // pointsA
            zkey.getSectionData(6),    // pointsB1
            zkey.getSectionData(7),    // pointsB2
            zkey.getSectionData(8),    // pointsC
            zkey.getSectionData(9)     // pointsH1
        );
    }

    void prove(const void         *wtns_buffer,
               unsigned long long  wtns_size,
               std::string        &stringProof,
               std::string        &stringPublic)
    {
        BinFileUtils::BinFile wtns(wtns_buffer, wtns_size, "wtns", 2);
        auto wtnsHeader = WtnsUtils::loadHeader(&wtns);

        if (zkeyHeader->nVars != wtnsHeader->nVars) {
            throw InvalidWitnessLengthException("Invalid witness length. Circuit: "
                                        + std::to_string(zkeyHeader->nVars)
                                        + ", witness: "
                                        + std::to_string(wtnsHeader->nVars));
        }

        if (!PrimeIsValid(wtnsHeader->prime)) {
            throw std::invalid_argument("different wtns curve");
        }

        AltBn128::FrElement *wtnsData = (AltBn128::FrElement *)wtns.getSectionData(2);

        auto proof = prover->prove(wtnsData);

        stringProof = proof->toJson().dump();
        stringPublic = BuildPublicString(wtnsData, zkeyHeader->nPublic);
    }
};

int
groth16_public_size_for_zkey_buf(
    const void          *zkey_buffer,
    unsigned long long   zkey_size,
    unsigned long long  *public_size,
    char                *error_msg,
    unsigned long long   error_msg_maxsize)
{
    try {
        BinFileUtils::BinFile zkey(zkey_buffer, zkey_size, "zkey", 1);
        auto zkeyHeader = ZKeyUtils::loadHeader(&zkey);

        *public_size = PublicBufferMinSize(zkeyHeader->nPublic);

    } catch (std::exception& e) {
        CopyError(error_msg, error_msg_maxsize, e);
        return PROVER_ERROR;

    } catch (...) {
        CopyErrorFmt(error_msg, error_msg_maxsize, "unknown error");
        return PROVER_ERROR;
    }

    return PROVER_OK;
}

int
groth16_public_size_for_zkey_file(
    const char          *zkey_fname,
    unsigned long long  *public_size,
    char                *error_msg,
    unsigned long long   error_msg_maxsize)
{
    try {
        auto zkey = BinFileUtils::openExisting(zkey_fname, "zkey", 1);
        auto zkeyHeader = ZKeyUtils::loadHeader(zkey.get());

        *public_size = PublicBufferMinSize(zkeyHeader->nPublic);

    } catch (std::exception& e) {
        CopyError(error_msg, error_msg_maxsize, e);
        return PROVER_ERROR;

    } catch (...) {
        CopyErrorFmt(error_msg, error_msg_maxsize, "unknown error");
        return PROVER_ERROR;
    }

    return PROVER_OK;
}

void
groth16_proof_size(
    unsigned long long *proof_size)
{
    *proof_size = ProofBufferMinSize();
}

int
groth16_prover_create(
    void                **prover_object,
    const void          *zkey_buffer,
    unsigned long long   zkey_size,
    char                *error_msg,
    unsigned long long   error_msg_maxsize)
{
    try {
        if (prover_object == NULL) {
            throw std::invalid_argument("Null prover object");
        }

        if (zkey_buffer == NULL) {
            throw std::invalid_argument("Null zkey buffer");
        }

        Groth16Prover *prover = new Groth16Prover(zkey_buffer, zkey_size);

        *prover_object = prover;

    } catch (std::exception& e) {
        CopyError(error_msg, error_msg_maxsize, e);
        return PROVER_ERROR;

    } catch (std::exception *e) {
        CopyError(error_msg, error_msg_maxsize, *e);
        delete e;
        return PROVER_ERROR;

    } catch (...) {
        CopyErrorFmt(error_msg, error_msg_maxsize, "unknown error");
        return PROVER_ERROR;
    }

    return PROVER_OK;
}

int
groth16_prover_create_zkey_file(
    void                **prover_object,
    const char          *zkey_file_path,
    char                *error_msg,
    unsigned long long   error_msg_maxsize)
{
    BinFileUtils::FileLoader fileLoader;

    try {
        fileLoader.load(zkey_file_path);

    } catch (std::exception& e) {
        CopyError(error_msg, error_msg_maxsize, e);
        return PROVER_ERROR;
    }

    return groth16_prover_create(
                prover_object,
                fileLoader.dataBuffer(),
                fileLoader.dataSize(),
                error_msg,
                error_msg_maxsize);
}

int
groth16_prover_prove(
    void                *prover_object,
    const void          *wtns_buffer,
    unsigned long long   wtns_size,
    char                *proof_buffer,
    unsigned long long  *proof_size,
    char                *public_buffer,
    unsigned long long  *public_size,
    char                *error_msg,
    unsigned long long   error_msg_maxsize)
{
    if (!prover_object) {
        CopyErrorFmt(error_msg, error_msg_maxsize, "Null prover object");
        return PROVER_ERROR;
    }

    if (!wtns_buffer) {
        CopyErrorFmt(error_msg, error_msg_maxsize, "Null witness buffer");
        return PROVER_ERROR;
    }

    if (!proof_buffer) {
        CopyErrorFmt(error_msg, error_msg_maxsize, "Null proof buffer");
        return PROVER_ERROR;
    }

    if (!proof_size) {
        CopyErrorFmt(error_msg, error_msg_maxsize, "Null proof size");
        return PROVER_ERROR;
    }

    if (!public_buffer) {
        CopyErrorFmt(error_msg, error_msg_maxsize, "Null public buffer");
        return PROVER_ERROR;
    }

    if (!public_size) {
        CopyErrorFmt(error_msg, error_msg_maxsize, "Null public size");
        return PROVER_ERROR;
    }

    auto prover = static_cast<Groth16Prover*>(prover_object);

    std::string stringProof;
    std::string stringPublic;

    try {
        prover->prove(wtns_buffer, wtns_size, stringProof, stringPublic);

    } catch(InvalidWitnessLengthException& e) {
        CopyError(error_msg, error_msg_maxsize, e);
        return PROVER_INVALID_WITNESS_LENGTH;

    } catch (std::exception& e) {
        CopyError(error_msg, error_msg_maxsize, e);
        return PROVER_ERROR;

    } catch (std::exception *e) {
        CopyError(error_msg, error_msg_maxsize, *e);
        delete e;
        return PROVER_ERROR;

    } catch (...) {
        CopyErrorFmt(error_msg, error_msg_maxsize, "unknown error");
        return PROVER_ERROR;
    }

    // Check for overflow before adding 1 for null terminator
    if (stringProof.length() >= ULLONG_MAX || stringPublic.length() >= ULLONG_MAX) {
        CopyErrorFmt(error_msg, error_msg_maxsize, "Proof or public data too large");
        return PROVER_ERROR;
    }

    unsigned long long requiredProofSize = stringProof.length() + 1;
    unsigned long long requiredPublicSize = stringPublic.length() + 1;

    if (*proof_size < requiredProofSize || *public_size < requiredPublicSize) {
        unsigned long long origProofSize = *proof_size;
        unsigned long long origPublicSize = *public_size;
        *proof_size = requiredProofSize;
        *public_size = requiredPublicSize;

        CopyErrorFmt(error_msg, error_msg_maxsize,
            "Buffer insufficient for generated proof. Required - proof: %llu (provided: %llu), public: %llu (provided: %llu)",
            requiredProofSize, origProofSize, requiredPublicSize, origPublicSize);
        return PROVER_ERROR_SHORT_BUFFER;
    }

    std::memcpy(proof_buffer, stringProof.c_str(), stringProof.length());
    proof_buffer[stringProof.length()] = '\0';
    *proof_size = stringProof.length();

    std::memcpy(public_buffer, stringPublic.c_str(), stringPublic.length());
    public_buffer[stringPublic.length()] = '\0';
    *public_size = stringPublic.length();

    return PROVER_OK;
}

void
groth16_prover_destroy(void *prover_object)
{
    if (prover_object != NULL) {
        Groth16Prover *prover = static_cast<Groth16Prover*>(prover_object);

        delete prover;
    }
}

int
groth16_prover(
    const void          *zkey_buffer,
    unsigned long long   zkey_size,
    const void          *wtns_buffer,
    unsigned long long   wtns_size,
    char                *proof_buffer,
    unsigned long long  *proof_size,
    char                *public_buffer,
    unsigned long long  *public_size,
    char                *error_msg,
    unsigned long long   error_msg_maxsize)
{
    void *prover = NULL;

    int error = groth16_prover_create(
                    &prover,
                    zkey_buffer,
                    zkey_size,
                    error_msg,
                    error_msg_maxsize);

    if (error != PROVER_OK) {
        return error;
    }

    error = groth16_prover_prove(
                    prover,
                    wtns_buffer,
                    wtns_size,
                    proof_buffer,
                    proof_size,
                    public_buffer,
                    public_size,
                    error_msg,
                    error_msg_maxsize);

    groth16_prover_destroy(prover);

    return error;
}

int
groth16_prover_zkey_file(
    const char          *zkey_file_path,
    const void          *wtns_buffer,
    unsigned long long   wtns_size,
    char                *proof_buffer,
    unsigned long long  *proof_size,
    char                *public_buffer,
    unsigned long long  *public_size,
    char                *error_msg,
    unsigned long long   error_msg_maxsize)
{
    BinFileUtils::FileLoader fileLoader;

    try {
        fileLoader.load(zkey_file_path);

    } catch (std::exception& e) {
        CopyError(error_msg, error_msg_maxsize, e);
        return PROVER_ERROR;
    }

    return groth16_prover(
            fileLoader.dataBuffer(),
            fileLoader.dataSize(),
            wtns_buffer,
            wtns_size,
            proof_buffer,
            proof_size,
            public_buffer,
            public_size,
            error_msg,
            error_msg_maxsize);
}
