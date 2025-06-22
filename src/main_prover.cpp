#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "prover.h"
#include "fileloader.hpp"

#ifdef USE_VULKAN
#include "vulkan/vulkan_test.h"

bool measureMsmTime(const char *shaderDir, prover_params &params)
{
    vulkan_msm_time msmTime;
    int             curveId = VULKAN_TEST_CURVE_G1;
    unsigned int    pointCount = 1000;
    char            errorMsg[1024];

    int error = vulkan_measure_msm_time(
        shaderDir,
        curveId,
        pointCount,
        &msmTime,
        errorMsg, sizeof(errorMsg));


    if (error != VULKAN_TEST_RESULT_OK) {
        std::cerr << "Error: " << errorMsg << std::endl;

        return false;
    }

    params.shader_dir = shaderDir;
    params.cpu_msm_time = msmTime.cpu;
    params.gpu_msm_time = msmTime.gpu;

    return true;
}
#endif

bool calcProverParams(int argc, char **argv, prover_params &params)
{
    if (argc < 6) {
        return true;
    }

    const char *shaderDir = argv[5];

#ifdef USE_VULKAN
    return measureMsmTime(shaderDir, params);
#endif

    return true;
}

int main(int argc, char **argv)
{
    if (argc != 5 && argc != 6) {
        std::cerr << "Invalid number of parameters" << std::endl;
        std::cerr << "Usage: prover <circuit.zkey> <witness.wtns> <proof.json> <public.json> [shader_dir]" << std::endl;
        return EXIT_FAILURE;
    }

    prover_params params = {};

    if (!calcProverParams(argc, argv, params)) {
        return EXIT_FAILURE;
    }

    try {
        const std::string zkeyFilename = argv[1];
        const std::string wtnsFilename = argv[2];
        const std::string proofFilename = argv[3];
        const std::string publicFilename = argv[4];

        BinFileUtils::FileLoader zkeyFile(zkeyFilename);
        BinFileUtils::FileLoader wtnsFile(wtnsFilename);
        std::vector<char>        publicBuffer;
        std::vector<char>        proofBuffer;
        unsigned long long       publicSize = 0;
        unsigned long long       proofSize = 0;
        char                     errorMsg[1024];

        int error = groth16_public_size_for_zkey_buf(
                     zkeyFile.dataBuffer(),
                     zkeyFile.dataSize(),
                     &publicSize,
                     errorMsg,
                     sizeof(errorMsg));

        if (error != PROVER_OK) {
            throw std::runtime_error(errorMsg);
        }

        groth16_proof_size(&proofSize);

        publicBuffer.resize(publicSize);
        proofBuffer.resize(proofSize);

        error = groth16_prover(
                   zkeyFile.dataBuffer(),
                   zkeyFile.dataSize(),
                   wtnsFile.dataBuffer(),
                   wtnsFile.dataSize(),
                   proofBuffer.data(),
                   &proofSize,
                   publicBuffer.data(),
                   &publicSize,
                   &params,
                   errorMsg,
                   sizeof(errorMsg));

        if (error != PROVER_OK) {
            throw std::runtime_error(errorMsg);
        }

        std::ofstream proofFile(proofFilename);
        proofFile.write(proofBuffer.data(), proofSize);

        std::ofstream publicFile(publicFilename);
        publicFile.write(publicBuffer.data(), publicSize);

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;

    }

    exit(EXIT_SUCCESS);
}
