#include <string>
#include <stdexcept>
#include <alt_bn128.hpp>
#include <nlohmann/json.hpp>

#include "verifier.h"
#include "groth16.hpp"

using json = nlohmann::json;

static Groth16::Proof<AltBn128::Engine>
parse_proof(const char *proof_str)
{
    Groth16::Proof<AltBn128::Engine> proof(AltBn128::Engine::engine);

    try {
        json proof_json = json::parse(proof_str);

        std::string protocol = proof_json["protocol"].template get<std::string>();

        if (protocol != "groth16") {
            throw std::invalid_argument("invalid proof data");
        }

        proof.fromJson(proof_json);

    } catch(...) {
        throw std::invalid_argument("invalid proof data") ;
    }

    return proof;
}

static std::vector<AltBn128::FrElement>
parse_inputs(const char *inputs_str)
{
    std::vector<AltBn128::FrElement> inputs;

    try {
        json inputs_json = json::parse(inputs_str);

        auto inputs_str_vec = inputs_json.template get<std::vector<std::string>>();

        if (inputs_str_vec.empty()) {
            throw std::invalid_argument("invalid inputs data");
        }

        inputs.reserve(inputs_str_vec.size());

        for (const auto& elem: inputs_str_vec) {
            AltBn128::FrElement aux;

            AltBn128::Fr.fromString(aux, elem);
            inputs.push_back(aux);
        }

    } catch(...) {
        throw std::invalid_argument("invalid inputs data") ;
    }

    return inputs;
}

static Groth16::VerificationKey<AltBn128::Engine>
parse_key(const char *key_str)
{
    Groth16::VerificationKey<AltBn128::Engine> key(AltBn128::Engine::engine);

    try {
        json key_json = json::parse(key_str);

        auto protocol = key_json["protocol"].template get<std::string>();
        auto curve    = key_json["curve"].template get<std::string>();
        auto nPublic  = key_json["nPublic"].template get<int64_t>();

        if (protocol != "groth16" || curve != "bn128") {
            throw std::invalid_argument("invalid verification key data");
        }

        key.fromJson(key_json);

        if (key.IC.empty()) {
            throw std::invalid_argument("invalid verification key data");
        }

    } catch(...) {
        throw std::invalid_argument("invalid verification key data");
    }

    return key;
}

int
groth16_verify(const char    *proof,
               const char    *inputs,
               const char    *verification_key,
               char          *error_msg,
               unsigned long  error_msg_maxsize)
{
    try {

        auto proof_value = parse_proof(proof);
        auto inputs_value = parse_inputs(inputs);
        auto key_value = parse_key(verification_key);

        Groth16::Verifier<AltBn128::Engine> verifier;

        bool valid = verifier.verify(proof_value, inputs_value, key_value);

        return valid ? VERIFIER_VALID_PROOF : VERIFIER_INVALID_PROOF;

    } catch (std::exception& e) {

        if (error_msg) {
            strncpy(error_msg, e.what(), error_msg_maxsize);
        }
        return VERIFIER_ERROR;

    } catch (std::exception *e) {

        if (error_msg) {
            strncpy(error_msg, e->what(), error_msg_maxsize);
        }
        delete e;
        return VERIFIER_ERROR;

    } catch (...) {
        if (error_msg) {
            strncpy(error_msg, "unknown error", error_msg_maxsize);
        }
        return VERIFIER_ERROR;
    }

    return VERIFIER_INVALID_PROOF;
}
