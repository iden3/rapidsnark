#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "prover.h"
#include "fileloader.hpp"
#include "logging.hpp"

#ifdef USE_VULKAN
#include "vulkan/vulkan_test.h"
#endif

bool HasVulkan()
{
#ifdef USE_VULKAN
    return true;
#else
    return false;
#endif
}

struct ProverArgs
{
    void showUsage()
    {
        std::cerr << "Usage: prover <circuit.zkey> <witness.wtns> <proof.json> <public.json>";

        if (HasLogging()) {
            std::cerr << " [log_level=0-4: 0]";
        }

        if (HasVulkan()) {
            std::cerr << " [shader_dir] [debug_gpu_time_factor]";
        }

        std::cerr << std::endl;

        if (HasLogging()) {
            std::cerr << std::endl;
            std::cerr << "  log_level = 0 : disabled" << std::endl;
            std::cerr << "  log_level = 1 : to file" << std::endl;
            std::cerr << "  log_level = 2 : to file and log debug messages" << std::endl;
            std::cerr << "  log_level = 3 : to console" << std::endl;
            std::cerr << "  log_level = 4 : to console and log debug messages" << std::endl;
        }

        if (HasVulkan()) {
            std::cerr << std::endl;
            std::cerr << "  debug_gpu_time_factor = [0.001 - 1000]" << std::endl;
        }

        std::cerr << std::endl;
    }

    bool parse(int argc, char **argv)
    {
        const int argcMin = 5;
        int argcMax = argcMin;

        if (HasLogging()) {
            argcMax += 1;
        }

        if (HasVulkan()) {
            argcMax += 2;
        }

        if (argc < argcMin || argc > argcMax) {
            std::cerr << "Invalid number of parameters" << std::endl;
            showUsage();
            return false;
        }

        filenameZkey   = argv[1];
        filenameWtns   = argv[2];
        filenameProof  = argv[3];
        filenamePublic = argv[4];

        int argIndexVulkan = argcMin;

        if (HasLogging()) {
            if (argc > 5) {
                logLevel = std::atoi(argv[5]);
            }

            argIndexVulkan += 1;
        }

        if (HasVulkan()) {
            if (argc > argIndexVulkan) {
                shaderDir = argv[argIndexVulkan];

                shaderDirMsmG1 = getShaderPath(shaderDir, "msm_g1");
                shaderDirMsmG2 = getShaderPath(shaderDir, "msm_g2");
            }

            if (argc > argIndexVulkan+1) {
                gpuTimeFactor = argv[argIndexVulkan+1];
            }
        }

        return true;
    }

    std::string getShaderPath(const std::string &shaderDir, const std::string &shaderSubdir)
    {
        std::string shaderPath;

        if (!shaderDir.empty()) {
            shaderPath = shaderDir + "/";
        }

        return shaderPath + shaderSubdir;
    }

    std::string filenameZkey;
    std::string filenameWtns;
    std::string filenameProof;
    std::string filenamePublic;
    int         logLevel = 0;
    std::string shaderDir;
    std::string gpuTimeFactor;

    std::string shaderDirMsmG1;
    std::string shaderDirMsmG2;
    prover_params params = {};
};

#ifdef USE_VULKAN

bool getGpuTimeFactor(const std::string &str, double &factor)
{
    if (str.empty()) {
        return false;
    }

    try {
        const double value = std::stof(str);

        if (value < 0.001 || value > 1000) {
            LOG_TRACE("GPU time factor must be in range [0.001, 1000]");
            return false;
        }

        factor = value;

    } catch(...) {
        return false;
    }

    return true;
}

bool measureMsmTime(ProverArgs &args)
{
    vulkan_msm_time  timeMsmG1;
    vulkan_msm_time  timeMsmG2;
    unsigned int     pointCount = 16000;
    char             errorMsg[1024];
    prover_params   &params = args.params;

    LOG_TRACE("shader_dir_msm_g1: " + args.shaderDirMsmG1);
    LOG_TRACE("shader_dir_msm_g2: " + args.shaderDirMsmG2);

    params.shader_dir_msm_g1 = args.shaderDirMsmG1.c_str();
    params.shader_dir_msm_g2 = args.shaderDirMsmG2.c_str();

    int error = vulkan_measure_msm_time(
        params.shader_dir_msm_g1,
        VULKAN_TEST_CURVE_G1,
        pointCount,
        &timeMsmG1,
        errorMsg, sizeof(errorMsg));


    if (error != VULKAN_TEST_RESULT_OK) {
        std::cerr << "Error on MSM G1 time measurement: " << errorMsg << std::endl;

        return false;
    }

    error = vulkan_measure_msm_time(
        params.shader_dir_msm_g2,
        VULKAN_TEST_CURVE_G2,
        pointCount,
        &timeMsmG2,
        errorMsg, sizeof(errorMsg));


    if (error != VULKAN_TEST_RESULT_OK) {
        std::cerr << "Error on MSM G2 time measurement: " << errorMsg << std::endl;

        return false;
    }

    params.time_msm_cpu_g1 = timeMsmG1.cpu;
    params.time_msm_gpu_g1 = timeMsmG1.gpu;
    params.time_msm_cpu_g2 = timeMsmG2.cpu;
    params.time_msm_gpu_g2 = timeMsmG2.gpu;

    LOG_TRACE("time_msm_cpu_g1: " + std::to_string(params.time_msm_cpu_g1) + " ms");
    LOG_TRACE("time_msm_gpu_g1: " + std::to_string(params.time_msm_gpu_g1) + " ms");
    LOG_TRACE("time_msm_cpu_g2: " + std::to_string(params.time_msm_cpu_g2) + " ms");
    LOG_TRACE("time_msm_gpu_g2: " + std::to_string(params.time_msm_gpu_g2) + " ms");

    LOG_TRACE("time_msm_compile_gpu_g1: " + std::to_string(timeMsmG1.compile) + " ms");
    LOG_TRACE("time_msm_compile_gpu_g2: " + std::to_string(timeMsmG2.compile) + " ms");

    double factor;

    if (getGpuTimeFactor(args.gpuTimeFactor, factor)) {

        params.time_msm_gpu_g1 = timeMsmG1.cpu * factor;

        LOG_TRACE("time_factor_gpu_g1: " + std::to_string(factor));
        LOG_TRACE("effective_time_msm_gpu_g1: " + std::to_string(params.time_msm_gpu_g1) + " ms");
    }

    return true;
}
#endif // USE_VULKAN

bool initProverParams(ProverArgs &args)
{
#ifdef USE_VULKAN
    if (args.shaderDir.empty()) {
        return true;
    }

    return measureMsmTime(args);
#else

    return true;
#endif
}

void makeProof(ProverArgs &args)
{
    BinFileUtils::FileLoader zkeyFile(args.filenameZkey);
    BinFileUtils::FileLoader wtnsFile(args.filenameWtns);
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
               &args.params,
               errorMsg,
               sizeof(errorMsg));

    if (error != PROVER_OK) {
        throw std::runtime_error(errorMsg);
    }

    std::ofstream proofFile(args.filenameProof);
    proofFile.write(proofBuffer.data(), proofSize);

    std::ofstream publicFile(args.filenamePublic);
    publicFile.write(publicBuffer.data(), publicSize);
}

int main(int argc, char **argv)
{
    ProverArgs args;

    if (!args.parse(argc, argv)) {
        return EXIT_FAILURE;
    }

    InitLogging(args.logLevel);

    if (!initProverParams(args)) {
        return EXIT_FAILURE;
    }

    try {
        makeProof(args);

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;

    }

    exit(EXIT_SUCCESS);
}
