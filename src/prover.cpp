#include <gmp.h>
#include <memory>
#include <string>
#include <cstring>
#include <stdexcept>
#include <alt_bn128.hpp>
#include <nlohmann/json.hpp>

#include "prover.h"
#include "zkey_utils.hpp"
#include "wtns_utils.hpp"
#include "groth16.hpp"
#include "binfile_utils.hpp"

using json = nlohmann::json;


int
groth16_prover(const void *zkey_buffer,   unsigned long zkey_size,
               const void *wtns_buffer,   unsigned long wtns_size,
               char       *proof_buffer,  unsigned long proof_size,
               char       *public_buffer, unsigned long public_size,
               char       *error_msg,     unsigned long error_msg_maxsize)
{
    mpz_t altBbn128r;

    mpz_init(altBbn128r);
    mpz_set_str(altBbn128r, "21888242871839275222246405745257275088548364400416034343698204186575808495617", 10);

    try {
        BinFileUtils::BinFile zkey(zkey_buffer, zkey_size, "zkey", 1);

        auto zkeyHeader = ZKeyUtils::loadHeader(&zkey);

        std::string proofStr;
        if (mpz_cmp(zkeyHeader->rPrime, altBbn128r) != 0) {
            throw std::invalid_argument( "zkey curve not supported" );
        }

        BinFileUtils::BinFile wtns(wtns_buffer, wtns_size, "wtns", 2);
        auto wtnsHeader = WtnsUtils::loadHeader(&wtns);

        if (mpz_cmp(wtnsHeader->prime, altBbn128r) != 0) {
            throw std::invalid_argument( "different wtns curve" );
        }

        auto prover = Groth16::makeProver<AltBn128::Engine>(
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
        AltBn128::FrElement *wtnsData = (AltBn128::FrElement *)wtns.getSectionData(2);
        auto proof = prover->prove(wtnsData);

        std::string stringProof = proof->toJson().dump();

        std::strncpy(proof_buffer, stringProof.data(), proof_size);

        json jsonPublic;
        AltBn128::FrElement aux;
        for (u_int32_t i=1; i<=zkeyHeader->nPublic; i++) {
            AltBn128::Fr.toMontgomery(aux, wtnsData[i]);
            jsonPublic.push_back(AltBn128::Fr.toString(aux));
        }

        std::string stringPublic = jsonPublic.dump();

        std::strncpy(public_buffer, stringPublic.data(), public_size);

    } catch (std::exception& e) {
        mpz_clear(altBbn128r);

        if (error_msg) {
            strncpy(error_msg, e.what(), error_msg_maxsize);
        }
        return PPROVER_ERROR;
    }

    mpz_clear(altBbn128r);

    return PRPOVER_OK;
}
