cmake_minimum_required(VERSION 3.24)

project(rapidsnark LANGUAGES CXX C ASM)

set(USE_ASM    ON  CACHE BOOL "Use asm implementation for Fr and Fq")
set(USE_OPENMP ON  CACHE BOOL "Use OpenMP")
set(USE_VULKAN OFF CACHE BOOL "Use Vulkan accelaration")
set(USE_LOGGER OFF CACHE BOOL "Use logger")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/platform.cmake)

message("USE_ASM=" ${USE_ASM})
message("USE_OPENMP=" ${USE_OPENMP})
message("USE_VULKAN=" ${USE_VULKAN})
message("USE_LOGGER=" ${USE_LOGGER})
message("BITS_PER_CHUNK=" ${BITS_PER_CHUNK})
message("CMAKE_CROSSCOMPILING=" ${CMAKE_CROSSCOMPILING})

message("GMP_PREFIX=" ${GMP_PREFIX})
message("GMP_INCLUDE_DIR=" ${GMP_INCLUDE_DIR})
message("GMP_LIB_DIR=" ${GMP_LIB_DIR})

if (NOT EXISTS ${GMP_INCLUDE_FILE_FULLPATH})
    message("WARNING: ${GMP_INCLUDE_FILE_FULLPATH} is not found and so system ${GMP_INCLUDE_FILE} is used.")
endif()

if (NOT EXISTS ${GMP_LIB_FILE_FULLPATH})
    message("WARNING: ${GMP_LIB_FILE_FULLPATH} is not found and so system ${GMP_LIB_FILE} is used.")
    set(GMP_LIB gmp)
endif()


include_directories(BEFORE ${GMP_INCLUDE_DIR})

add_subdirectory(src)


install(TARGETS prover verifier rapidsnark rapidsnarkStatic rapidsnarkStaticFrFq test_prover fr fq)

install(FILES "${GMP_LIB_DIR}/${GMP_LIB_FILE}"
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES src/prover.h src/verifier.h
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

if(Vulkan_FOUND)
    install(TARGETS test_vulkan vulkan_test)

    install(FILES src/vulkan/vulkan_test.h
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/vulkan)

    set(SHADER_BIN_DIR ${CMAKE_BINARY_DIR}/src/vulkan/shaders)
    set(SHADER_SRC_DIR ${CMAKE_SOURCE_DIR}/src/vulkan/shaders)

    function(install_shader dir filename)
        cmake_path(GET filename STEM name)

        install(FILES ${SHADER_BIN_DIR}/${dir}/${name}.spv
                      ${SHADER_SRC_DIR}/${dir}/${name}.glsl
                DESTINATION ${CMAKE_INSTALL_PREFIX}/shaders/${dir})
    endfunction()

    function(install_shader_set dir)

        file(GLOB shaderList LIST_DIRECTORIES FALSE
             RELATIVE ${SHADER_SRC_DIR}/${dir}
             ${SHADER_SRC_DIR}/${dir}/*.glsl)

        foreach(filename IN LISTS shaderList)
            install_shader("${dir}" "${filename}")
        endforeach()
    endfunction()

    install_shader_set(curve_mock)
    install_shader_set(curve_g1)
    install_shader_set(msm_mock)
    install_shader_set(msm_g1)
    install_shader_set(msm_g2)
endif()

enable_testing()
