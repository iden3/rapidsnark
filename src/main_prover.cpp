#include <iostream>
#include <fstream>
#include <gmp.h>
#include <memory>
#include <stdexcept>
#include <nlohmann/json.hpp>

#include <alt_bn128.hpp>
#include "binfile_utils.hpp"
#include "zkey_utils.hpp"
#include "wtns_utils.hpp"
#include "groth16.hpp"

#include "fileloader.hpp"
#include "prover.h"

using json = nlohmann::json;

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

const size_t BufferSize = 32768;

int main(int argc, char **argv)
{
    if (argc != 5) {
        std::cerr << "Invalid number of parameters:\n";
        std::cerr << "Usage: prover <circuit.zkey> <witness.wtns> <proof.json> <public.json>\n";
        return EXIT_FAILURE;
    }

    mpz_t altBbn128r;

    mpz_init(altBbn128r);
    mpz_set_str(altBbn128r, "21888242871839275222246405745257275088548364400416034343698204186575808495617", 10);

    try {
        std::string zkeyFilename = argv[1];
        std::string wtnsFilename = argv[2];
        std::string proofFilename = argv[3];
        std::string publicFilename = argv[4];

        const char* zkeyFilenameC = zkeyFilename.c_str();

        BinFileUtils::FileLoader wtnsFileLoader(wtnsFilename);

        char proofBuffer[BufferSize];
        char publicBuffer[BufferSize];

        size_t proofSize  = sizeof(proofBuffer);
        size_t publicSize = sizeof(publicBuffer);
        char errorMessage[256];
        int error = 0;

        error = groth16_prover_zkey_file(zkeyFilenameC,
                               wtnsFileLoader.dataBuffer(), wtnsFileLoader.dataSize(),
                               proofBuffer,  &proofSize,
                               publicBuffer, &publicSize,
                               errorMessage, sizeof(errorMessage));

        if (error == PROVER_ERROR_SHORT_BUFFER) {
            std::cerr << "Error: Short buffer for proof or public" << '\n';
            return EXIT_FAILURE;
        } else if (error) {
            std::cerr << errorMessage << '\n';
            return EXIT_FAILURE;
        }

        std::ofstream proofFile;
        proofFile.open (proofFilename);
        proofFile << proofBuffer;
        proofFile.close();

        std::ofstream publicFile;
        publicFile.open (publicFilename);
        publicFile << publicBuffer;
        publicFile.close();

    } catch (std::exception* e) {
        mpz_clear(altBbn128r);
        std::cerr << e->what() << '\n';
        return EXIT_FAILURE;
    } catch (std::exception& e) {
        mpz_clear(altBbn128r);
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    mpz_clear(altBbn128r);
    exit(EXIT_SUCCESS);
}
