#include <iostream>
#include <stdexcept>

#include "fileloader.hpp"
#include "verifier.h"

int main(int argc, char **argv)
{
    if (argc != 4) {
        std::cerr << "Invalid number of parameters:\n";
        std::cerr << "Usage: verifier <verification_key.json> <inputs.json> <proof.json>\n";
        return EXIT_FAILURE;
    }

    try {
        const std::string keyFilename    = argv[1];
        const std::string inputsFilename = argv[2];
        const std::string proofFilename  = argv[3];

        BinFileUtils::FileLoader proof(proofFilename);
        BinFileUtils::FileLoader inputs(inputsFilename);
        BinFileUtils::FileLoader key(keyFilename);

        char errorMessage[256];

        const int error = groth16_verify(proof.dataAsString().c_str(),
                                         inputs.dataAsString().c_str(),
                                         key.dataAsString().c_str(),
                                         errorMessage, sizeof(errorMessage));

        if (error == VERIFIER_VALID_PROOF) {

            std::cerr << "Result: Valid proof" << std::endl;
            return EXIT_SUCCESS;

        } else if (error == VERIFIER_INVALID_PROOF) {

            std::cerr << "Result: Invalid proof" << std::endl;
            return EXIT_FAILURE;

        } else {
            std::cerr << "Error: " << errorMessage << '\n';
            return EXIT_FAILURE;
        }

    } catch (std::exception* e) {
        std::cerr << "Error: " << e->what() << std::endl;
        return EXIT_FAILURE;

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_FAILURE;
}
