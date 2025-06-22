#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "vulkan_test.h"

#define PROGRAM_NAME "test_vulkan"

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
    const char *shader_path = ".";
    int         point_count = 500*1024;
    int         log_level = 0;
    int         test_level = 1;
    char        msg[256*1024];

    if (show_usage(argc, argv)) {

        std::cout << "USAGE: " << PROGRAM_NAME
                  << " [shader_path: "    << shader_path << "]"
                  << " [point_count: "    << point_count << "]"
                  << " [log_level=0-3: "  << log_level   << "]"
                  << " [test_level=0-2: " << test_level  << "]"
                  << std::endl;

        return EXIT_SUCCESS;
    }

    if (argc > 1) {
        shader_path = argv[1];
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

    point_count = std::max(point_count, 1);
    log_level   = std::max(log_level,   0);
    test_level  = std::max(test_level,  0);

    vulkan_test_params(shader_path, point_count, log_level, test_level, msg, sizeof(msg));

    std::cout << msg << std::endl;

    vulkan_msm_time msm_time;

    const int error = vulkan_measure_msm_time(shader_path, VULKAN_TEST_CURVE_G1, point_count,
                                        &msm_time, msg, sizeof(msg));

    if (error == VULKAN_TEST_RESULT_OK) {
        std::cout << "MSM measurement results" << std::endl;
        std::cout << "GPU time: " << msm_time.gpu << " ms" << std::endl;
        std::cout << "CPU time: " << msm_time.cpu << " ms" << std::endl;

    } else {
        std::cout << "Error: " << msg << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
