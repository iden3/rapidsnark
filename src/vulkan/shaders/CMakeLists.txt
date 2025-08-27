set(SHADER_SRC_DIR ${CMAKE_SOURCE_DIR}/src/vulkan/shaders)

set(cmd_glc ${Vulkan_GLSLC_EXECUTABLE})
set(cmd_glv ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE})

set(cmd_glc_preproc ${cmd_glc} -E -std=460         -I${SHADER_SRC_DIR})
set(cmd_glc_build   ${cmd_glc} -fshader-stage=comp -I${SHADER_SRC_DIR})
set(cmd_glv_build   ${cmd_glv} -V -S comp          -I${SHADER_SRC_DIR})

set(cmd_shader_preproc ${cmd_glc_preproc})
set(cmd_shader_build   ${cmd_glc_build})

set(opt_glc "-O")
set(opt_glv "-gVS")
set(opt_comp ${opt_glc})

function(preproc_shader dir name)
    set(in_file  ${SHADER_SRC_DIR}/${dir}/${name}.glsl)
    set(out_file ${dir}/${name}.glsl)

    add_custom_command(OUTPUT ${out_file}
        COMMAND mkdir -p ${dir}
        COMMAND ${cmd_shader_preproc} ${in_file} -o ${out_file}
        MAIN_DEPENDENCY ${in_file}
        )
endfunction()

function(build_shader dir filename opts)
    cmake_path(GET filename STEM name)

    set(in_file  ${SHADER_SRC_DIR}/${dir}/${name}.glsl)
    set(out_file ${dir}/${name}.spv)

    add_custom_command(OUTPUT ${out_file}
        COMMAND mkdir -p ${dir}
        COMMAND ${cmd_shader_build} ${opts} ${in_file} -o ${out_file}
        MAIN_DEPENDENCY ${in_file}
        )
endfunction()

function(build_shader_set dir opts)

    file(GLOB shaderList LIST_DIRECTORIES FALSE
        RELATIVE ${SHADER_SRC_DIR}/${dir}
        ${dir}/*.glsl)

    foreach(filename IN LISTS shaderList)
        build_shader("${dir}" "${filename}" "${opts}")
    endforeach()
endfunction()

preproc_shader(math fq "")
preproc_shader(math g1 "")

build_shader_set(curve_mock ${opt_comp})
build_shader_set(curve_g1   ${opt_comp})
build_shader_set(msm_mock   ${opt_comp})
build_shader_set(msm_g1     ${opt_comp})
build_shader_set(msm_g2     "")

add_custom_target(math DEPENDS
    math/fq.glsl
    math/g1.glsl
    )

add_custom_target(curve_mock DEPENDS
    curve_mock/stage0.spv
    )

add_custom_target(curve_g1 DEPENDS
    curve_g1/stage0.spv
    )

add_custom_target(msm_mock DEPENDS
    msm_mock/stage0.spv
    msm_mock/stage1.spv
    msm_mock/stage2.spv
    msm_mock/stage3.spv
    msm_mock/stage4.spv
    )

add_custom_target(msm_g1 DEPENDS
    msm_g1/stage0.spv
    msm_g1/stage1.spv
    msm_g1/stage2.spv
    msm_g1/stage3.spv
    msm_g1/stage4.spv
    )

add_custom_target(msm_g2 DEPENDS
    msm_g2/stage0.spv
    msm_g2/stage1.spv
    )

add_dependencies(test_vulkan
    math
    curve_mock
    curve_g1
    msm_mock
    msm_g1
    msm_g2
    )
