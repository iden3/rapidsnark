#include <iostream>
#include <cstdlib>
#include <string>
#include "gpu_test.h"

int main(int argc, char **argv)
{
    const char *shader_path = "shader.spv";
    int         point_count = 500*1024;
    int         iter_count = 160;
    char        msg[256*1024];

    if (argc > 1) {
        if (std::string(argv[1]) == "-h") {

            std::cout << "USAGE: test_perf [shader_path] [point_path]  [iter_path]" << std::endl;
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

    if (point_count <= 0) {
        point_count = 1;
    }

    if (iter_count <= 0) {
        iter_count = 1;
    }

    std::cout << "Input arguments: " << std::endl;
    std::cout << "shader path: " << shader_path << std::endl;
    std::cout << "iter count: "  << iter_count  << std::endl;
    std::cout << "point count: " << point_count << std::endl;

    gpu_test_params(shader_path, point_count, iter_count, msg, sizeof(msg));

    std::cout << msg << std::endl;

    return EXIT_SUCCESS;
}
