#ifndef GPU_TEST_H
#define GPU_TEST_H


#ifdef __cplusplus
extern "C" {
#endif

/**
 * log_level is in range [0 - 3].
 * The higher log_level the more logging is provided.
 *
 * test_level is in range [0 - 2]:
    0 - test GPU
    1 - test GPU + ParallelCPU
    2 - test GPU + ParallelCPU + SingleCPU
 */
void gpu_test_params(
    const char*   shader_path,
    unsigned int  point_count,
    unsigned int  iter_count,
    unsigned int  log_level,
    unsigned int  test_level,
    char*         msg,
    long          msg_max_size);

/**
 * The default log_level is 0.
 * The default test_level is 1.
 */
void gpu_test(
    const char* shader_path,
    char*       msg,
    long        msg_max_size);

#ifdef __cplusplus
}
#endif



#endif // GPU_TEST_H
