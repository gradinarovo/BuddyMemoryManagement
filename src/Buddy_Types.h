/**
 * @file Buddy_Types.h
 * @brief Type definitions for the Buddy Memory Allocator
 * 
 * This file contains the data structures used by the buddy memory allocator.
 * The buddy system maintains bitmaps to track free and used blocks at each order.
 */

#ifndef BUDDY_TYPES_H
#define BUDDY_TYPES_H

#include "Std_Types.h"
#include "Buddy_Cfg.h"

/**
 * @brief Structure representing the buddy memory allocator
 * 
 * The buddy system divides memory into blocks that are powers of two in size.
 * Each 'order' represents a specific block size (2^order bytes).
 * 
 * Example with 16-byte heap (MAX_ORDER=4):
 * 
 * Order  Block Size  Blocks  Bitmap (1 bit per block)
 * -----  ----------  ------  ------------------------
 *   0        1B       16     0bxxxxxxxx xxxxxxxx     (16 bits)
 *   1        2B        8     0bxxxxxsxxx              (8 bits)
 *   2        4B        4     0bxxxx                  (4 bits)
 *   3        8B        2     0bxx                    (2 bits)
 *   4       16B        1     0bx                     (1 bit)
 * 
 * Bit values: 0 = free, 1 = used
 * 
 * When allocating a block, we find the smallest block that can satisfy the request
 * and mark it as used in the bitmap. When freeing, we mark it as free and check
 * if its buddy is also free to potentially merge them.
 */
typedef struct {
    /** 
     * @brief Pointer to the start of the heap memory region
     * 
     * This is the base address of the memory pool that the buddy system manages.
     * The memory should be aligned to the maximum block size for optimal performance.
     */
    uint8* heap_start;
    
    /** 
     * @brief Total size of the heap in bytes
     * 
     * Must be a power of 2 for the buddy system to work correctly.
     * The actual usable size might be slightly less due to alignment and metadata.
     */
    uint32 heap_size;
    
    /** 
     * @brief Maximum order supported by this allocator
     * 
     * Calculated as log2(heap_size). Determines the number of different block sizes.
     * For example, with heap_size=1024, max_order would be 10 (2^10 = 1024).
     */
    uint32 max_order;
    
    /** 
     * @brief Size of each order's bitmap in 32-bit words
     * 
     * Since we use uint32 for bitmaps, this stores how many 32-bit words
     * are needed to represent all blocks at each order.
     */
    uint32 bitmap_size;
    
    /** 
     * @brief Array of bitmaps, one for each order
     * 
     * The array has (MAX_ORDER + 1) elements because order ranges from 0 to MAX_ORDER.
     * Each element is a pointer to a bitmap for that order.
     * 
     * Example for 16-byte heap (MAX_ORDER=4):
     * - bitmaps[0]: bitmap for 1-byte blocks (16 bits)
     * - bitmaps[1]: bitmap for 2-byte blocks (8 bits)
     * - bitmaps[2]: bitmap for 4-byte blocks (4 bits)
     * - bitmaps[3]: bitmap for 8-byte blocks (2 bits)
     * - bitmaps[4]: bitmap for 16-byte blocks (1 bit)
     */
    uint32* bitmaps[MAX_ORDER + 1];
} TBuddy_system;

#endif /* BUDDY_TYPES_H */