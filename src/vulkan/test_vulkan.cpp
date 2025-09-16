#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "vulkan_test.h"

#define PROGRAM_NAME "test_vulkan"

int test(
    const char   *shader_path,
    const char   *test_type,
    unsigned int  point_count,
    unsigned int  log_level,
    unsigned int  test_level,
    char         *msg,
    long          msg_max_size)
{
    int error = vulkan_test_params(shader_path, test_type, point_count, log_level, test_level, msg, msg_max_size);

    if (error == VULKAN_TEST_RESULT_OK) {
        std::cout << msg << std::endl;

    } else {
        std::cout << "Error: " << msg << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

std::string curve_name(int curve_id)
{
    switch (curve_id) {
    case VULKAN_TEST_CURVE_G1:
        return "G1";
    case VULKAN_TEST_CURVE_G2:
        return "G2";
    default:
        break;
    }

    return "";
}

int measure_time(
    int           curve_id,
    const char   *shader_path,
    unsigned int  point_count,
    char         *msg,
    long          msg_max_size)
{
    std::string name = curve_name(curve_id);
    vulkan_msm_time msm_time;

    int error = vulkan_measure_msm_time(shader_path, curve_id, point_count,
                                        &msm_time, msg, msg_max_size);

    if (error == VULKAN_TEST_RESULT_OK) {
        std::cout << "MSM measurement results for " << name << std::endl;
        std::cout << "GPU compile time: " << msm_time.compile << " ms" << std::endl;
        std::cout << "GPU time: "         << msm_time.gpu << " ms" << std::endl;
        std::cout << "CPU time: "         << msm_time.cpu << " ms" << std::endl;

    } else {
        std::cout << "Error on MSM " << name << " time measurement: " << msg << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int measure_time(
    const char   *shader_dir,
    unsigned int  point_count,
    char         *msg,
    long          msg_max_size)
{
    const std::string shaderPathG1 = std::string(shader_dir) + "/msm_g1";
    const std::string shaderPathG2 = std::string(shader_dir) + "/msm_g2";

    int error = measure_time(VULKAN_TEST_CURVE_G1, shaderPathG1.c_str(),
                             point_count, msg, msg_max_size);

    if (error != EXIT_SUCCESS) {
        return error;
    }

    error = measure_time(VULKAN_TEST_CURVE_G2, shaderPathG2.c_str(),
                         point_count, msg, msg_max_size);

    return error;
}

bool show_usage(int argc, char **argv)
{
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-h") {
            return true;
        }
    }

    return false;
}

int main(int argc, char **argv)
{
    const char *shader_dir = ".";
    int         point_count = 500*1024;
    int         log_level = 0;
    int         test_level = 1;
    const char *test_type = "msm_g1";
    char        msg[256*1024];

    if (show_usage(argc, argv)) {

        std::cout << "USAGE: " << PROGRAM_NAME
                  << " [shader_dir: "     << shader_dir  << "]"
                  << " [point_count: "    << point_count << "]"
                  << " [log_level=0-3: "  << log_level   << "]"
                  << " [test_level=0-2: " << test_level  << "]"
                  << " [test_type=measure|msm_mock|msm_g1|msm_g2|curve_mock|curve_g1|curve_g2: " << test_type << "]"
                  << std::endl;

        return EXIT_SUCCESS;
    }

    if (argc > 1) {
        shader_dir = argv[1];
    }

    if (argc > 2) {
        point_count = std::atoi(argv[2]);
    }

    if (argc > 3) {
        log_level = std::atoi(argv[3]);
    }

    if (argc > 4) {
        test_level = std::atoi(argv[4]);
    }

    if (argc > 5) {
        test_type = argv[5];
    }

    point_count = std::max(point_count, 1);
    log_level   = std::max(log_level,   0);
    test_level  = std::max(test_level,  0);

    if (std::string(test_type) == "measure") {
        return measure_time(shader_dir, point_count, msg, sizeof(msg));

    } else {
        return test(shader_dir, test_type, point_count, log_level, test_level, msg, sizeof(msg));
    }

    return EXIT_SUCCESS;
}
