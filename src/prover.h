#ifndef PROVER_HPP
#define PROVER_HPP

#ifdef __cplusplus
extern "C" {
#endif

//Error codes returned by the functions.
#define PROVER_OK                     0x0
#define PROVER_ERROR                  0x1
#define PROVER_ERROR_SHORT_BUFFER     0x2
#define PROVER_INVALID_WITNESS_LENGTH 0x3

/**
 * Calculates buffer size to output public signals as json string
 * @returns PROVER_OK in case of success, and the size of public buffer is written to public_size
 */
int
groth16_public_size_for_zkey_buf(
    const void          *zkey_buffer,
    unsigned long long   zkey_size,
    unsigned long long  *public_size,
    char                *error_msg,
    unsigned long long   error_msg_maxsize);

/**
 * groth16_public_size_for_zkey_file calculates minimum buffer size for
 * JSON-formatted public signals. The calculated buffer size is written
 * to the public_size variable.
 *
 * @return error code:
 *        PROVER_OK (0) - in case of success
 *        PROVER_ERROR - in case of an error, error_msg contains the error message
 */
int
groth16_public_size_for_zkey_file(
    const char          *zkey_fname,
    unsigned long long  *public_size,
    char                *error_msg,
    unsigned long long   error_msg_maxsize);

/**
 * Returns buffer size to output proof as json string
 */
void
groth16_proof_size(
    unsigned long long *proof_size);

/**
 * Initializes 'prover_object' with a pointer to a new prover object.
 * @return error code:
 *         PROVER_OK - in case of success
 *         PPOVER_ERROR - in case of an error
 */
int
groth16_prover_create(
    void                **prover_object,
    const void          *zkey_buffer,
    unsigned long long   zkey_size,
    char                *error_msg,
    unsigned long long   error_msg_maxsize);

/**
 * Initializes 'prover_object' with a pointer to a new prover object.
 * @return error code:
 *         PROVER_OK - in case of success
 *         PPOVER_ERROR - in case of an error
 */
int
groth16_prover_create_zkey_file(
    void                **prover_object,
    const char          *zkey_file_path,
    char                *error_msg,
    unsigned long long   error_msg_maxsize);

/**
 * Proves 'wtns_buffer' and saves results to 'proof_buffer' and 'public_buffer'.
 * @return error code:
 *         PROVER_OK - in case of success
 *         PPOVER_ERROR - in case of an error
 *         PROVER_ERROR_SHORT_BUFFER - in case of a short buffer error, also updates proof_size and public_size with actual proof and public sizes
 */
int
groth16_prover_prove(
    void                *prover_object,
    const void          *wtns_buffer,
    unsigned long long   wtns_size,
    char                *proof_buffer,
    unsigned long long  *proof_size,
    char                *public_buffer,
    unsigned long long  *public_size,
    char                *error_msg,
    unsigned long long   error_msg_maxsize);

/**
 * Destroys 'prover_object'.
 */
void
groth16_prover_destroy(void *prover_object);

/**
 * groth16_prover
 * @return error code:
 *         PROVER_OK - in case of success
 *         PPOVER_ERROR - in case of an error
 *         PROVER_ERROR_SHORT_BUFFER - in case of a short buffer error, also updates proof_size and public_size with actual proof and public sizes
 */
int
groth16_prover(
    const void          *zkey_buffer,
    unsigned long long   zkey_size,
    const void          *wtns_buffer,
    unsigned long long   wtns_size,
    char                *proof_buffer,
    unsigned long long  *proof_size,
    char                *public_buffer,
    unsigned long long  *public_size,
    char                *error_msg,
    unsigned long long   error_msg_maxsize);

/**
 * groth16_prover_zkey_file
 * @return error code:
 *         PROVER_OK - in case of success
 *         PPOVER_ERROR - in case of an error
 *         PROVER_ERROR_SHORT_BUFFER - in case of a short buffer error, also updates proof_size and public_size with actual proof and public sizes
 */
int
groth16_prover_zkey_file(
    const char          *zkey_file_path,
    const void          *wtns_buffer,
    unsigned long long   wtns_size,
    char                *proof_buffer,
    unsigned long long  *proof_size,
    char                *public_buffer,
    unsigned long long  *public_size,
    char                *error_msg,
    unsigned long long   error_msg_maxsize);

#ifdef __cplusplus
}
#endif


#endif // PROVER_HPP
