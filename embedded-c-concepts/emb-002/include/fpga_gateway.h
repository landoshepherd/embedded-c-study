#ifndef FPGA_GATEWAY_H
#define FPGA_GATEWAY_H

#include <stdint.h>
#include <stdbool.h>

// The state of the FPGA as a system
typedef enum{
	FPGA_STATE_IDLE = 0,
	FPGA_STATE_INITIALIZING,
	FPGA_STATE_RUNNING,
	FPGA_STATE_ERROR
}FpgaState_t;

// Status of an FPGA function invocation
typedef enum{
	FPGA_STATUS_OK = 0,
	FPGA_STATUS_ERROR,
	FPGA_STATUS_NULL_POINTER,
	FPGA_STATUS_INVALID_GATEWAY
}FpgaStatus_t;

// Structure ordering to minimize padding
typedef struct{
	uint32_t 		base_address;			// 4 bytes
	uint32_t 		error_count;			// 4 bytes
	uint32_t 		watchdog_count;		// 4 bytes
	FpgaState_t state;						// 4 byte
	bool 				initialized;			// 1 byte
}FpgaGateway_t;

/**
 * @brief Initializes the FPGA gateway.
 * 
 * Sets the gateway structure to its initial state, assigns the base address,
 * and marks it as initialized.
 * 
 * @param fpga_gateway Pointer to the FPGA gateway structure.
 * @param base_address The base memory address for the FPGA gateway.
 * @return FpgaStatus_t FPGA_STATUS_OK on success, or FPGA_STATUS_NULL_POINTER if the gateway pointer is NULL.
 */
FpgaStatus_t fpga_gateway_init(FpgaGateway_t* fpga_gateway, uint32_t base_address);

/**
 * @brief Deinitializes the FPGA gateway.
 * 
 * Resets the gateway structure fields to their default uninitialized values.
 * 
 * @param fpga_gateway Pointer to the FPGA gateway structure.
 * @return FpgaStatus_t FPGA_STATUS_OK on success, or FPGA_STATUS_INVALID_GATEWAY if the gateway is invalid.
 */
FpgaStatus_t fpga_gateway_deinit(FpgaGateway_t* fpga_gateway);

/**
 * @brief Resets the FPGA gateway.
 * 
 * @param fpga_gateway Pointer to the FPGA gateway structure.
 * @return FpgaStatus_t FPGA_STATUS_OK on success, or FPGA_STATUS_INVALID_GATEWAY if the gateway is invalid.
 */
FpgaStatus_t fpga_gateway_reset(FpgaGateway_t* fpga_gateway);

/**
 * @brief Checks if the FPGA gateway is ready and running.
 * 
 * @param fpga_gateway Pointer to the FPGA gateway structure.
 * @param[out] ready Pointer to a boolean that will be set to true if the gateway 
 *                   is valid, initialized, and in the RUNNING state; false otherwise.
 * @return FpgaStatus_t FPGA_STATUS_OK on success, FPGA_STATUS_INVALID_GATEWAY if the gateway is invalid, or FPGA_STATUS_NULL_POINTER if the ready pointer is NULL.
 */
FpgaStatus_t fpga_gateway_is_ready(const FpgaGateway_t* fpga_gateway, bool* ready);

/**
 * @brief Retrieves the current error count of the FPGA gateway.
 * 
 * @param fpga_gateway Pointer to the FPGA gateway structure.
 * @param[out] count Pointer to a uint32_t where the error count will be stored.
 * @return FpgaStatus_t FPGA_STATUS_OK on success, FPGA_STATUS_INVALID_GATEWAY if the gateway is invalid, or FPGA_STATUS_NULL_POINTER if the count pointer is NULL.
 */
FpgaStatus_t fpga_gateway_get_error_count(const FpgaGateway_t* fpga_gateway, uint32_t* count);


#endif //FPGA_GATEWAY_H