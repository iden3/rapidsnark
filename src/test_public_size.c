/**
 * Test functions groth16_public_size_for_zkey_file and
 * groth16_public_size_for_zkey_buf.
 *
 * Run it as
 * ./test_public_size <zkey_file> <expected_pub_size>
 * it will calculate the required public signals buffer size from the zkey file
 * and compare it with the expected one. Return 0 if success.
 * Return 1 if failure. Also prints the time taken by each function.
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <unistd.h>
#include <time.h>
#include "prover.h"

int
test_groth16_public_size(const char *zkey_fname, size_t *public_size) {
    int ret_val = 0;
    const int error_sz = 256;
    char error_msg[error_sz];

    int fd = open(zkey_fname, O_RDONLY);
    if (fd == -1) {
        printf("Error: %s\n", "open");
        ret_val = 1;
        goto cleanup;
    }

    struct stat sb = {0};
    if (fstat(fd, &sb) == -1) {
        printf("Error: %s\n", "fstat");
        ret_val = 1;
        goto cleanup;
    }

    void *buf = malloc(sb.st_size);
    if (buf == NULL) {
        printf("Error: %s\n", "malloc");
        ret_val = 1;
        goto cleanup;
    }

    ssize_t bytes_read = read(fd, buf, sb.st_size);
    if (bytes_read != sb.st_size) {
        printf("Error: %s\n", "read");
        ret_val = 1;
        goto cleanup;
    }

    int ok = groth16_public_size_for_zkey_buf(buf, sb.st_size, public_size, error_msg, error_sz);
    if (ok == 0) {
        printf("Public size: %lu\n", *public_size);
    } else {
        printf("Error: %s\n", error_msg);
        ret_val = 1;
        goto cleanup;
    }

cleanup:

    if (fd != -1)
        if (close(fd) == -1)
            printf("Error: %s\n", "close");

    return ret_val;
}

int
test_groth16_public_size_for_zkey_file(const char *zkey_fname,
                                       size_t *public_size) {
    const int err_ln = 256;
    char error_msg[err_ln];
    int ret = groth16_public_size_for_zkey_file(zkey_fname, public_size, error_msg, err_ln);

    if (ret == 0) {
        printf("Public size: %lu\n", *public_size);
    } else {
        printf("Error: %s\n", error_msg);
    }
    return ret;
}

int
main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <zkey_file> <expected_pub_size>\n", argv[0]);
        return 1;
    }

    long want_pub_size = 0;
    want_pub_size = strtol(argv[2], NULL, 10);

    int ret_val = 0;
    clock_t start = clock();

    size_t public_size = 0;

    int test_groth16_public_size_ok =
            test_groth16_public_size(argv[1], &public_size);
    if (test_groth16_public_size_ok) {
        printf("test_groth16_public_size failed\n");
        ret_val = 1;
    } else {
        clock_t end = clock();
        printf("test_groth16_public_size succeeded in %f seconds\n",
               (double)(end - start) / CLOCKS_PER_SEC);
    }

    if (public_size != want_pub_size) {
        printf("test_groth16_public_size expected public signals buf size: %ld\n",
               want_pub_size);
        printf("test_groth16_public_size actual public signals buf size: %lu\n",
               public_size);
        ret_val = 1;
    }

    public_size = 0;
    start = clock();
    int test_groth16_public_size_for_zkey_file_ok =
            test_groth16_public_size_for_zkey_file(argv[1], &public_size);
    if (test_groth16_public_size_for_zkey_file_ok) {
        printf("test_groth16_public_size_for_zkey_file failed\n");
        ret_val = 1;
    } else {
        clock_t end = clock();
        printf("test_groth16_public_size_for_zkey_file succeeded in %f seconds\n",
               (double)(end - start) / CLOCKS_PER_SEC);
    }

    if (public_size != want_pub_size) {
        printf("test_groth16_public_size_for_zkey_file expected public signals buf size: %ld\n",
               want_pub_size);
        printf("test_groth16_public_size_for_zkey_file actual public signals buf size: %lu\n",
               public_size);
        ret_val = 1;
    }

    return ret_val;
}

