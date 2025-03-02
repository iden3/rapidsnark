#ifndef GPU_TEST_H
#define GPU_TEST_H


#ifdef __cplusplus
extern "C" {
#endif


void gpu_test(
    const char *shader_path,
    char       *msg,
    long        msg_max_size);

#ifdef __cplusplus
}
#endif



#endif // GPU_TEST_H
