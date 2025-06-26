#ifndef _IO_KBC_
#define _IO_KBC_

#include "../../utils/result.h"
#include "i8042.h"
#include "lcom/lcf.h"
#include "stdbool.h"
#include "stdint.h"

typedef uint8_t KBCStatus;
typedef uint8_t KBCOutput;

/** @brief Checks if the given KBC status indicates a parity error.
 *  @param status The status byte read from the KBC.
 *  @return true if a parity error occurred; false otherwise.
 */
static inline bool KBC_parity_error(KBCStatus status) { return status & KBC_STATUS_PARITY_BIT; }

/** @brief Checks if the given KBC status indicates a timeout error.
 *  @param status The status byte read from the KBC.
 *  @return true if a timeout error occurred; false otherwise.
 */
static inline bool KBC_timeout_error(KBCStatus status) { return status & KBC_STATUS_TIMEOUT_BIT; }

/** @brief Checks if any communication error (parity or timeout) occurred.
 *  @param status The status byte read from the KBC.
 *  @return true if an error occurred; false otherwise.
 */
static inline bool KBC_error(KBCStatus status) { return KBC_parity_error(status) || KBC_timeout_error(status); }

/** @brief Tests whether the KBC input buffer is full.
 *  @param status The status byte read from the KBC.
 *  @return true if input buffer is full; false otherwise.
 */
static inline bool KBC_input_buffer_full(KBCStatus status) { return status & KBC_STATUS_IBF_BIT; }

/** @brief Tests whether the KBC output buffer is full.
 *  @param status The status byte read from the KBC.
 *  @return true if output buffer is full; false otherwise.
 */
static inline bool KBC_output_buffer_full(KBCStatus status) { return status & KBC_STATUS_OBF_BIT; }

/**
 * @brief Reads the status register of the Keyboard Controller (KBC).
 * @param status Pointer to a KBCStatus variable where the value will be stored.
 * @return RES_OK on success, or an error code on failure.
 */
Result KBC_read_status(KBCStatus *status);

/**
 * @brief Reads one byte from the KBC output buffer if available.
 * @param output Pointer to a KBCOutput variable where the byte will be stored.
 * @return RES_OK on success, RES_NOT_READY if buffer empty, or an error code on failure.
 */
Result KBC_read_output(KBCOutput *output);

#endif // _IO_KBC_
