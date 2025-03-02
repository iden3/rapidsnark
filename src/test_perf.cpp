#include <iostream>
#include "gpu_test.h"

int main(int argc, char **argv)
{
    const char *shader_path = "shader.spv";
    char msg[256*1024];

    if (argc > 1) {
        shader_path = argv[1];
    }

    gpu_test(shader_path, msg, sizeof(msg));

    std::cout << msg << std::endl;

    return EXIT_SUCCESS;
}
