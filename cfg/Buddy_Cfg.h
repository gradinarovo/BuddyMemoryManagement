/**
 * @file Buddy_Cfg.h
 * @brief Configuration parameters for the Buddy Memory Allocator
 * 
 * This file contains compile-time configuration parameters for the buddy memory
 * allocation system. Modify these values according to your system's requirements.
 */

#ifndef BUDDY_CFG_H
#define BUDDY_CFG_H

/**
 * @def MAX_ORDER
 * @brief Maximum number of block orders (0 to MAX_ORDER-1)
 * 
 * This defines the maximum block size as 2^(MAX_ORDER-1) bytes.
 * For example, with MAX_ORDER = 10, the system will support blocks
 * from 2^0 (1 byte) up to 2^9 (512 bytes).
 */
#define MAX_ORDER       10u

/**
 * @def MIN_BLOCK_SIZE
 * @brief Minimum block size in bytes (must be a power of 2)
 * 
 * This is the smallest block size that can be allocated in bytes.
 * Must be a power of 2 and at least 1.
 */
#define MIN_BLOCK_SIZE  8u

#endif /* BUDDY_CFG_H */