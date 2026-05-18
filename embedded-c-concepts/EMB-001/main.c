#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "memory_pool.h"
#include "sensor.h"

_Static_assert(POOL_BLOCK_SIZE >= sizeof(SensorData_t),
               "Pool block size too small");

int main(void) {
  // Declare and initialize memory pool
  MemoryPool_t mem_pool;

  // Initialize the pool
  if (pool_init(&mem_pool) == STATUS_OK) {
    printf("Memory pool initialized\n");
  } else {
    printf("Memory pool initialization failed. ABORT.\n");
    return 1;
  }

  // Allocate buffers for 3 sensors
  SensorData_t* tempSensor = NULL;
  tempSensor = pool_alloc(&mem_pool);
  if (tempSensor != NULL) {
    printf("Temp Sensor Address: %p\n", tempSensor);
    tempSensor->sensor_id = 1;
    tempSensor->timestamp = 10;
    int16_t data = 2550;
    memcpy(tempSensor->data, &data, sizeof(int16_t));
  } else {
    printf("Memory full. Temperature Sensor failed to allocate.\n");
  }

  SensorData_t* humiditySensor = NULL;
  humiditySensor = pool_alloc(&mem_pool);
  if (humiditySensor != NULL) {
    printf("Humidity Sensor Address: %p\n", humiditySensor);
    humiditySensor->sensor_id = 2;
    humiditySensor->timestamp = 20;
    uint16_t data = 6025;
    memcpy(humiditySensor->data, &data, sizeof(uint16_t));
  } else {
    printf("Memory full. Humidity Sensor failed to allocate.\n");
  }

  SensorData_t* pressureSensor = NULL;
  pressureSensor = pool_alloc(&mem_pool);
  if (pressureSensor != NULL) {
    printf("Pressure Sensor Address: %p\n", pressureSensor);
    pressureSensor->sensor_id = 3;
    pressureSensor->timestamp = 30;
    uint32_t data = 101325;
    memcpy(pressureSensor->data, &data, sizeof(uint32_t));
  } else {
    printf("Memory full. Pressure Sensor failed to allocate.\n");
  }

  // Calculate checksum
  if (tempSensor != NULL) {
    tempSensor->checksum = checksum(tempSensor);
    if (verify_checksum(tempSensor)) {
      printf("Temp sensor data integrity: OK\n");
    } else {
      printf("Temp sensor data integrity: FAILED\n");
    }
  }

  if (humiditySensor != NULL) {
    humiditySensor->checksum = checksum(humiditySensor);
    if (verify_checksum(humiditySensor)) {
      printf("Humidity sensor data integrity: OK\n");
    } else {
      printf("Humidity sensor data integrity: FAILED\n");
    }
  }

  if (pressureSensor != NULL) {
    pressureSensor->checksum = checksum(pressureSensor);
    if (verify_checksum(pressureSensor)) {
      printf("Pressure sensor data integrity: OK\n");
    } else {
      printf("Pressure sensor data integrity: FAILED\n");
    }
  }

  // Print pool status
  if (pool_status(&mem_pool) != STATUS_OK) {
    printf("Memory pool status failed. ABORT.\n");
    return 1;
  }

  // Free humidity sensor
  if (pool_free(&mem_pool, humiditySensor) != STATUS_OK) {
    printf("Memory pool free failed. ABORT.\n");
    return 1;
  }

  humiditySensor = NULL;

  // Print status
  if (pool_status(&mem_pool) != STATUS_OK) {
    printf("Memory pool status failed. ABORT.\n");
    return 1;
  }

  // Try to allocate 7 more sensors
  for (uint8_t i = 0; i < 7; i++) {
    SensorData_t* sensor = NULL;
    sensor = pool_alloc(&mem_pool);
    if (sensor != NULL) {
      printf("Sensor_%d Address: %p\n", i, sensor);
    } else {
      printf("Memory full. Failed to allocate memory for Sensor_%d\n", i);
    }
  }

  // Print pool status
  if (pool_status(&mem_pool) != STATUS_OK) {
    printf("Memory pool status failed. ABORT.\n");
    return 1;
  }

  return 0;
}