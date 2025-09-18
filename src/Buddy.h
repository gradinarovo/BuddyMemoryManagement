/**
 * @file Buddy.h
 * @brief Public interface for the Buddy Memory Allocator
 * 
 * This file provides the public API for the buddy memory allocation system.
 * The buddy allocator is designed for efficient memory management with minimal
 * fragmentation by maintaining blocks in power-of-two sizes.
 */

#ifndef BUDDY_H
#define BUDDY_H

#include "Buddy_Types.h"

/**
 * @brief Initialize the buddy memory allocator
 * 
 * @param buddy Pointer to the buddy system structure to initialize
 * @param heap_start Pointer to the start of the memory region to manage
 * @param heap_size Total size of the memory region in bytes (must be power of 2)
 * 
 * @note The provided memory region must be aligned to its size for optimal performance.
 *       The actual usable memory will be slightly less than heap_size due to metadata.
 */
void Buddy_Init(TBuddy_system* buddy, uint8* heap_start, uint32 heap_size);

/**
 * @brief Allocate a block of memory
 * 
 * @param buddy Pointer to the initialized buddy system
 * @param size Number of bytes to allocate
 * @return uint8* Pointer to the allocated memory, or NULL if allocation fails
 * 
 * @note The actual allocated block size will be the smallest power of two that is
 *       greater than or equal to the requested size and at least MIN_BLOCK_SIZE.
 */
uint8* Buddy_Alloc(TBuddy_system* buddy, uint32 size);

/**
 * @brief Free a previously allocated block of memory
 * 
 * @param buddy Pointer to the buddy system
 * @param ptr Pointer to the memory block to free
 * 
 * @note If ptr is NULL, the function returns immediately without taking any action.
 *       The pointer must have been previously returned by Buddy_Alloc() and not
 *       freed already.
 */
void Buddy_Free(TBuddy_system* buddy, uint8* ptr);

#endif /* BUDDY_H */
