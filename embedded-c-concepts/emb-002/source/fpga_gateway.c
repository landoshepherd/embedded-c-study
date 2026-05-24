#include "fpga_gateway.h"
#include <stddef.h>

static const uint32_t DEFAULT_ADDRESS = 0x00000000u;

static bool is_valid_gateway(const FpgaGateway_t* fpga_gateway){
	return (fpga_gateway != NULL && fpga_gateway->initialized);
}

FpgaStatus_t fpga_gateway_init(FpgaGateway_t* fpga_gateway, uint32_t base_address){
	if(fpga_gateway == NULL){
		return FPGA_STATUS_NULL_POINTER;
	}
	fpga_gateway->initialized = true;
	fpga_gateway->error_count = 0u;
	fpga_gateway->state = FPGA_STATE_INITIALIZING;
	fpga_gateway->base_address = base_address;
	fpga_gateway->watchdog_count = 0u;
	return FPGA_STATUS_OK;
}

FpgaStatus_t fpga_gateway_deinit(FpgaGateway_t* fpga_gateway){
	if(!is_valid_gateway(fpga_gateway)){
		return FPGA_STATUS_INVALID_GATEWAY;
	}
	fpga_gateway->initialized = false;
	fpga_gateway->error_count = 0u;
	fpga_gateway->state = FPGA_STATE_IDLE;
	fpga_gateway->base_address = DEFAULT_ADDRESS;
	fpga_gateway->watchdog_count = 0u;
	return FPGA_STATUS_OK;
}

FpgaStatus_t fpga_gateway_reset(FpgaGateway_t* fpga_gateway){
	if(!is_valid_gateway(fpga_gateway)){
		return FPGA_STATUS_INVALID_GATEWAY;
	}

	fpga_gateway->error_count = 0u;
	fpga_gateway->watchdog_count = 0u;
	fpga_gateway->state = FPGA_STATE_INITIALIZING;

	return FPGA_STATUS_OK;
}

FpgaStatus_t fpga_gateway_is_ready(const FpgaGateway_t* fpga_gateway, bool* ready){
	if(ready == NULL){
		return FPGA_STATUS_NULL_POINTER;
	}
	
	if(!is_valid_gateway(fpga_gateway)){
		return FPGA_STATUS_INVALID_GATEWAY;
	}

	*ready = (fpga_gateway->state == FPGA_STATE_RUNNING);
	return FPGA_STATUS_OK;
}

FpgaStatus_t fpga_gateway_get_error_count(const FpgaGateway_t* fpga_gateway, uint32_t* count){
	if(count == NULL){
		return FPGA_STATUS_NULL_POINTER;
	}
	
	if(!is_valid_gateway(fpga_gateway)){
		return FPGA_STATUS_INVALID_GATEWAY;
	}

	*count = fpga_gateway->error_count;
	return FPGA_STATUS_OK;
}