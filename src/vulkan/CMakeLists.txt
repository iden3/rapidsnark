link_libraries(${GMP_LIB})

add_compile_definitions(${GMP_DEFINIONS})

if(USE_ASM)
    if(ARCH MATCHES "arm64")
            add_compile_definitions(USE_ASM ARCH_ARM64)
    elseif(ARCH MATCHES "x86_64")
            add_compile_definitions(USE_ASM ARCH_X86_64)
    endif()
endif()

if(DEFINED BITS_PER_CHUNK)
    add_definitions(-DMSM_BITS_PER_CHUNK=${BITS_PER_CHUNK})
endif()

link_libraries(fr)
link_libraries(fq)

if(OpenMP_CXX_FOUND)
    add_compile_definitions(USE_OPENMP)

    add_compile_options(${OpenMP_CXX_FLAGS})
endif()

include_directories(
    ../../build
    ../../depends/ffiasm/c
    )

add_library(vulkan_test SHARED
    vulkan_test.cpp
    vulkan_manager.cpp
    vulkan_pipeline.cpp
    vulkan_buffer.cpp
    ../../depends/ffiasm/c/misc.cpp
    ../../depends/ffiasm/c/naf.cpp
    ../../depends/ffiasm/c/splitparstr.cpp
    ../../depends/ffiasm/c/alt_bn128.cpp
    )

target_link_libraries(vulkan_test Vulkan::Vulkan)

if(NOT TARGET_PLATFORM MATCHES "android")
    target_link_libraries(vulkan_test pthread)
endif()

add_executable(test_vulkan test_vulkan.cpp)
target_link_libraries(test_vulkan vulkan_test)


if(OpenMP_CXX_FOUND)
    target_link_libraries(test_vulkan OpenMP::OpenMP_CXX)
endif()


add_subdirectory(shaders)
