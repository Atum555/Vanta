#ifndef _T_RESULT_
#define _T_RESULT_

/**
 * @file result.h
 * @brief Defines the Result enum and helper macros for error handling.
 */

/**
 * @enum Result
 * @brief Status codes indicating success or specific error conditions.
 */
typedef enum {
    RES_OK = 0,           // Success, no error

    RES_ERROR,            // General error, no specific message

    RES_IO_ERROR,         // Input/output operation failed
    RES_INVALID_ARGUMENT, // Invalid argument passed to function
    RES_NULL_POINTER,     // Null pointer passed to function
    RES_LCOM_ERROR,       // LCOM library internal error
    RES_KERNEL_ERROR,     // Kernel internal error
    RES_NOT_READY,        // The result is not ready / cannot be read yet
    RES_TIMEOUT,          // The operation asked timed out
} Result;

/**
 * @brief Test whether a Result value indicates success.
 * @param result The Result code to test.
 * @return Non-zero (true) if result == RES_OK, zero otherwise.
 */
#define IS_OK(result) ((result) == RES_OK)

/**
 * @brief Test whether a Result value indicates any error.
 * @param result The Result code to test.
 * @return Non-zero (true) if result != RES_OK, zero otherwise.
 */
#define IS_ERROR(result) ((result) != RES_OK)

/**
 * @brief Return immediately if a Result indicates an error.
 * @param result The Result code to check and potentially return.
 */
#define RETURN_IF_ERROR(result)                          \
    do {                                                 \
        Result _temp_result = (result);                  \
        if (_temp_result != RES_OK) return _temp_result; \
    } while (0)

#endif // _T_RESULT_
