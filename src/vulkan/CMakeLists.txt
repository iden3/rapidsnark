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

if(Vulkan_FOUND)
    add_library(vulkan_test SHARED
        vulkan_test.cpp
        vulkan_manager.cpp
        vulkan_pipeline.cpp
        vulkan_buffer.cpp
        ../../depends/ffiasm/c/misc.cpp
        ../../depends/ffiasm/c/naf.cpp
        )

    target_link_libraries(vulkan_test Vulkan::Vulkan)

    if(NOT TARGET_PLATFORM MATCHES "android")
        target_link_libraries(vulkan_test pthread)
    endif()

    add_executable(test_vulkan test_vulkan.cpp)
    target_link_libraries(test_vulkan vulkan_test)

    set(SHADER_SRC_DIR ${CMAKE_SOURCE_DIR}/src/vulkan/shaders)

    macro(build_shader dir name)
        add_custom_command(OUTPUT shaders/${dir}/${name}.spv
            COMMAND mkdir -p shaders/${dir}
            COMMAND ${Vulkan_GLSLC_EXECUTABLE} -fshader-stage=comp ${SHADER_SRC_DIR}/${dir}/${name}.glsl
                                                                          -o shaders/${dir}/${name}.spv
            MAIN_DEPENDENCY ${SHADER_SRC_DIR}/${dir}/${name}.glsl
            )
    endmacro()

    build_shader(msm    stage0)
    build_shader(msm    stage1)
    build_shader(msm_g1 stage0)
    build_shader(msm_g1 stage1)
    build_shader(msm_g2 stage0)
    build_shader(msm_g2 stage1)

    add_custom_target(shaders_msm    DEPENDS shaders/msm/stage0.spv    shaders/msm/stage1.spv)
    add_custom_target(shaders_msm_g1 DEPENDS shaders/msm_g1/stage0.spv shaders/msm_g1/stage1.spv)
    add_custom_target(shaders_msm_g2 DEPENDS shaders/msm_g2/stage0.spv shaders/msm_g2/stage1.spv)

    add_dependencies(test_vulkan shaders_msm shaders_msm_g1 shaders_msm_g2)

endif()
