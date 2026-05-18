#include "memory_pool.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

Status_t pool_init(MemoryPool_t* mem_pool) {
  if (mem_pool == NULL) {
    return STATUS_NULL_POINTER;
  }

  // A single memset is more efficient and robust. It zeroes the data pool,
  // sets block_used to false (0), and num_used to 0.
  memset(mem_pool, 0, sizeof(MemoryPool_t));

  return STATUS_OK;
}

void* pool_alloc(MemoryPool_t* mem_pool) {
  if (mem_pool == NULL) {
    return NULL;
  }

  // Check if memory is available
  if (mem_pool->num_used < POOL_BLOCK_COUNT) {
    // Find available block of memory
    for (uint8_t i = 0; i < POOL_BLOCK_COUNT; i++) {
      if (!mem_pool->block_used[i]) {
        mem_pool->block_used[i] = true;
        mem_pool->num_used++;
        return mem_pool->pool[i];
      }
    }
  }

  // Return NULL if the pool is full, consistent with the function's return
  // type.
  return NULL;
}

Status_t pool_free(MemoryPool_t* mem_pool, void* mem_address) {
  if (mem_pool == NULL && mem_address == NULL) {
    return STATUS_NULL_POINTER;
  }

  // The sensor id and the memory pool block used should not
  // be associated. The sensor id could be anything while
  // the blocked_used is simply one of the memory blocks
  // the pool is maintaining. Therefore, we need to compare the
  // address of the SensorData_t to the address of the actual
  // memory block being used in order to determine the block index.
  for (uint8_t i = 0; i < POOL_BLOCK_COUNT; i++) {
    if (mem_pool->pool[i] == mem_address) {
      mem_pool->block_used[i] = false;
      mem_pool->num_used--;
      return STATUS_OK;
    }
  }
  return STATUS_INVALID_ADDRESS;
}

Status_t pool_status(MemoryPool_t* mem_pool) {
  if (mem_pool == NULL) {
    return STATUS_NULL_POINTER;
  }

  // Print number of blocks in use
  uint8_t blocksUsed = mem_pool->num_used;
  printf("Blocks in use: %" PRIu8 "\n", blocksUsed);

  // Print number of blocks free
  uint8_t blocksFree = POOL_BLOCK_COUNT - blocksUsed;
  printf("Blocks free: %" PRIu8 "\n", blocksFree);

  return STATUS_OK;
}
