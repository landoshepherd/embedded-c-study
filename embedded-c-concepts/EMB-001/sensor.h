#ifndef SENSOR_H
#define SENSOR_H

#include <stdbool.h>
#include <stdint.h>

// Sensor data size
#define SENSOR_DATA_SIZE (24U)  // 24 bytes

// Sensor error codes
#define CHECKSUM_FAILURE (42U)

typedef struct {
  uint32_t timestamp;              // Byte: 4
  uint8_t sensor_id;               // Byte: 1
  uint8_t data[SENSOR_DATA_SIZE];  // Variable Size: 1 byte; 24 bytes
  uint8_t checksum;                // Byte: 1
} SensorData_t;

/**
 * @brief Calculates a simple 8-bit XOR checksum over the sensor data packet.
 *
 * This function computes a checksum for the fields within the SensorData_t
 * struct that precede the checksum member itself (timestamp, sensor_id, and
 * data). This allows for verification of the data's integrity.
 *
 * @param sensor A pointer to the SensorData_t struct to be checksummed.
 * @return uint8_t The calculated 8-bit checksum. If the sensor pointer is
 *                 NULL, it returns CHECKSUM_FAILURE.
 */
uint8_t checksum(SensorData_t* sensor);

/**
 * @brief Verifies the integrity of a sensor data packet by checking its
 * checksum.
 *
 * This function recalculates the checksum of the provided sensor data packet
 * and compares it against the `checksum` value stored within the packet.
 *
 * @param sensor A pointer to the SensorData_t struct to be verified.
 * @return bool Returns `true` if the stored checksum matches the calculated
 *              checksum (and the pointer is not NULL), `false` otherwise.
 */
bool verify_checksum(SensorData_t* sensor);

#endif  // SENSOR_H