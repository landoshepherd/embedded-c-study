#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stdbool.h>
#include <stdint.h>

#define POOL_BLOCK_SIZE (32U)  // 32 bytes
#define POOL_BLOCK_COUNT (8U)  // 8 blocks

typedef enum {
  STATUS_OK = 0,
  STATUS_NULL_POINTER,
  STATUS_INVALID_ADDRESS,
  STATUS_POOL_FULL,
  STATUS_POOL_EMPTY
} Status_t;

typedef struct {
  uint8_t pool[POOL_BLOCK_COUNT][POOL_BLOCK_SIZE];
  bool block_used[POOL_BLOCK_COUNT];
  uint8_t num_used;
} MemoryPool_t;

/**
 * @brief Initializes a memory pool structure.
 *
 * This function prepares a MemoryPool_t instance for use. It zeroes out the
 * entire data pool, marks all blocks as unused, and resets the usage counter.
 * After calling this function, the pool is in a clean, ready-to-use state.
 *
 * @param mem_pool A pointer to the MemoryPool_t structure to be initialized.
 *                 The memory for this structure must be allocated by the
 * caller.
 * @return Status_t Returns STATUS_OK on successful initialization, or
 *                  STATUS_NULL_POINTER if the provided mem_pool pointer is
 * NULL.
 */
Status_t pool_init(MemoryPool_t* mem_pool);

/**
 * @brief Allocates a single block of memory from the pool.
 *
 * This function searches for the first available memory block in the pool.
 * If a free block is found, it is marked as used, the pool's usage counter
 * is incremented, and a void pointer to the start of that block is returned.
 * The caller is responsible for casting this pointer to the desired type.
 *
 * @param mem_pool A pointer to the MemoryPool_t structure from which to
 * allocate.
 *
 * @return void* A pointer to the allocated memory block if successful.
 *               Returns NULL if the mem_pool pointer is NULL or if the pool
 *               is full and no blocks are available for allocation.
 */
void* pool_alloc(MemoryPool_t* mem_pool);

/**
 * @brief Frees a memory block, returning it to the pool.
 *
 * This function takes a pointer to a previously allocated memory block and
 * returns it to the pool for future use. It finds the corresponding block
 * within the pool by comparing addresses, marks it as unused, and decrements
 * the pool's usage counter.
 *
 * @param mem_pool A pointer to the MemoryPool_t structure.
 * @param mem_address A pointer to the memory block to be freed. This should be
 *                    an address previously returned by pool_alloc.
 * @return Status_t Returns STATUS_OK on success, STATUS_NULL_POINTER if
 *                  mem_pool is NULL, or STATUS_INVALID_ADDRESS if the
 *                  mem_address is not a valid block from this pool.
 */
Status_t pool_free(MemoryPool_t* mem_pool, void* mem_address);

/**
 * @brief Prints the current status of the memory pool to stdout.
 *
 * This utility function displays the number of memory blocks currently in use
 * and the number of blocks that are free and available for allocation.
 *
 * @param mem_pool A pointer to the MemoryPool_t structure whose status is to be
 *                 printed.
 * @return Status_t Returns STATUS_OK on success, or STATUS_NULL_POINTER if the
 *                  provided mem_pool pointer is NULL.
 */
Status_t pool_status(MemoryPool_t* mem_pool);

#endif  // MEMORY_POOL_H