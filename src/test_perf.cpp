#include <iostream>
#include <cstdlib>
#include <string>
#include "gpu_test.h"

int main(int argc, char **argv)
{
    const char *shader_path = "shader.spv";
    int         point_count = 500*1024;
    int         iter_count = 160;
    int         log_level = 0;
    int         test_level = 1;
    char        msg[256*1024];

    if (argc > 1) {
        if (std::string(argv[1]) == "-h") {

            std::cout << "USAGE: test_perf [shader_path] [point_path] [iter_path] [log_level=0-3] [test_level=0-2]" << std::endl;
            return EXIT_SUCCESS;
        }

        shader_path = argv[1];
    }

    if (argc > 2) {
        point_count = std::atoi(argv[2]);
    }

    if (argc > 3) {
        iter_count = std::atoi(argv[3]);
    }

    if (argc > 4) {
        log_level = std::atoi(argv[4]);
    }

    if (argc > 5) {
        test_level = std::atoi(argv[5]);
    }

    if (point_count <= 0) {
        point_count = 1;
    }

    if (iter_count <= 0) {
        iter_count = 1;
    }

    if (log_level < 0) {
        log_level = 0;
    }

    if (test_level < 0) {
        test_level = 0;
    }

    gpu_test_params(shader_path, point_count, iter_count, log_level, test_level, msg, sizeof(msg));

    std::cout << msg << std::endl;

    return EXIT_SUCCESS;
}
