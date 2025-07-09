#ifndef VULKAN_TEST_H
#define VULKAN_TEST_H


#ifdef __cplusplus
extern "C" {
#endif

#define VULKAN_TEST_RESULT_OK                  0
#define VULKAN_TEST_RESULT_INVALID_PATH        1
#define VULKAN_TEST_RESULT_INVALID_SHADER      2
#define VULKAN_TEST_RESULT_INVALID_CURVE_ID    3
#define VULKAN_TEST_RESULT_TOO_BIG_POINT_COUNT 4
#define VULKAN_TEST_RESULT_TIMEOUT             5
#define VULKAN_TEST_RESULT_COMP_NOT_EQUAL      6
#define VULKAN_TEST_RESULT_OTHER_ERROR         7

/**
 * 'shader_path' should point to the directory with
 *  MSM shaders for G1 curve.
 *
 * log_level is in range [0 - 3].
 * The higher log_level the more logging is provided.
 *
 * test_level is in range [0 - 2]:
    0 - test GPU
    1 - test GPU + ParallelCPU
    2 - test GPU + ParallelCPU + SingleCPU
 */
int vulkan_test_params(
    const char   *shader_path,
    unsigned int  point_count,
    unsigned int  log_level,
    unsigned int  test_level,
    char         *msg,
    long          msg_max_size);

/**
 * The default log_level is 0.
 * The default test_level is 1.
 */
int vulkan_test(
    const char *shader_path,
    char       *msg,
    long        msg_max_size);


#define VULKAN_TEST_CURVE_G1 1
#define VULKAN_TEST_CURVE_G2 2

struct vulkan_msm_time {
    unsigned long long gpu;
    unsigned long long cpu;
};

/**
 * Computes MSM on GPU and CPU for the number of points from 'point_count' on 'curve'.
 * Puts the time spent in milliseconds to 'msm_result'.
 *
 * 'curve' should be one of VULKAN_TEST_CURVE_* IDs.
 *
 * 'shader_path' must point to the directory with a set of shader used for computation.
 * The set of shaders consists of 'stage0.spv' and 'stage1.spv'.
 *
 * If 'error_msg' is not NULL it keeps an error message in case of error.
 *
 * @return error code:
 * VULKAN_TEST_RESULT_OK                  - 'msm_time' keeps MSM times measured on GPU and CPU.
 * VULKAN_TEST_RESULT_INVALID_PATH        - 'shader_path' doesn't point to a correct set of shaders.
 * VULKAN_TEST_RESULT_INVALID_SHADER      - the set contains an invalid shader.
   VULKAN_TEST_RESULT_INVALID_CURVE_ID    - 'curve_id' contains an unrecognized curve ID.
 * VULKAN_TEST_RESULT_TOO_BIG_POINT_COUNT - 'point_count' is greater than a reasonable number of points.
 * VULKAN_TEST_RESULT_TIMEOUT             - the MSM computation took too long time and was interrupted.
 * VULKAN_TEST_RESULT_COMP_NOT_EQUAL      - computation results of GPU and CPU are different.
 * VULKAN_TEST_RESULT_OTHER_ERROR         - some error occured. Its description is in 'error_msg'.
 */
int vulkan_measure_msm_time(
    const char             *shader_path,
    int                     curve_id,
    unsigned int            point_count,
    struct vulkan_msm_time *msm_time,
    char                   *error_msg,
    unsigned long long      error_msg_maxsize);

#ifdef __cplusplus
}
#endif

#endif // VULKAN_TEST_H
