#include "sensor.h"

#include <stddef.h>
#include <stdint.h>

uint8_t checksum(SensorData_t* sensor) {
  if (sensor == NULL) {
    return CHECKSUM_FAILURE;
  }

  uint8_t ret = 0;

  ret ^= (uint8_t)(sensor->timestamp >> 0);
  ret ^= (uint8_t)(sensor->timestamp >> 8);
  ret ^= (uint8_t)(sensor->timestamp >> 16);
  ret ^= (uint8_t)(sensor->timestamp >> 24);
  ret ^= sensor->sensor_id;

  for (uint8_t i = 0; i < SENSOR_DATA_SIZE; i++) {
    ret ^= sensor->data[i];
  }

  return ret;
}

bool verify_checksum(SensorData_t* sensor) {
  if (sensor == NULL) {
    return false;
  }

  // Calculate the checksum again and compare it to checksum
  // that is stored in the sensor.
  return checksum(sensor) == sensor->checksum;
}
