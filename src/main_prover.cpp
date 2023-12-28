#include <iostream>
#include <fstream>
#include <stdexcept>

#include "fileloader.hpp"
#include "prover.h"

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)


const size_t BufferSize = 4194304;


int main(int argc, char **argv)
{
    if (argc != 5) {
        std::cerr << "Invalid number of parameters:\n";
        std::cerr << "Usage: prover <circuit.zkey> <witness.wtns> <proof.json> <public.json>\n";
        return EXIT_FAILURE;
    }

    try {
        std::string zkeyFilename = argv[1];
        std::string wtnsFilename = argv[2];
        std::string proofFilename = argv[3];
        std::string publicFilename = argv[4];

        char proofBuffer[910];
        char publicBuffer[BufferSize];
        size_t proofSize  = sizeof(proofBuffer);
        size_t publicSize = sizeof(publicBuffer);
        char errorMessage[256];
        int error = 0;

        BinFileUtils::FileLoader zkeyFileLoader(zkeyFilename);
        BinFileUtils::FileLoader wtnsFileLoader(wtnsFilename);

        error = groth16_prover(zkeyFileLoader.dataBuffer(), zkeyFileLoader.dataSize(),
                               wtnsFileLoader.dataBuffer(), wtnsFileLoader.dataSize(),
                               proofBuffer,  &proofSize,
                               publicBuffer, &publicSize,
                               errorMessage, sizeof(errorMessage));

        if (error == PPROVER_ERROR_SHORT_BUFFER) {

            std::cerr << "Error: Short buffer for proof or public" << '\n';
            return EXIT_FAILURE;
        }

        else if (error) {
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
        std::cerr << e->what() << '\n';
        return EXIT_FAILURE;

    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    exit(EXIT_SUCCESS);
}
