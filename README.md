# Buddy Memory Management Algorithm

## Overview
The Buddy Memory Management Algorithm is an efficient memory allocation technique that divides memory into partitions to satisfy allocation requests. It uses a "divide and combine" strategy where memory blocks are split into smaller "buddies" during allocation and merged back when freed, minimizing fragmentation while maintaining fast allocation/deallocation times.

## How It Works

### Key Concepts
- **Blocks**: Memory is divided into blocks of sizes that are powers of two (e.g., 64KB, 128KB).
- **Buddy**: Each block has a "buddy" – an adjacent block of the same size. When two buddies are free, they merge into a larger block.
- **Free Lists**: The algorithm maintains multiple linked lists (free lists), one for each block size (e.g., 2⁰, 2¹, ..., 2ᵏ).

### Steps

#### Initialization:
- Memory starts as a single large block of size 2ᴺ.
- Free lists are initialized, with the largest block (2ᴺ) added to the free list for that size.

#### Allocation:
- For a request of size S, find the smallest block size 2ᴷ such that 2ᴷ ≥ S.
- If a free block of size 2ᴷ exists, allocate it.
- If not, split a larger free block (recursively) into two halves (buddies). One buddy is used for allocation, and the other is added to the free list for its size.

#### Deallocation:
- When a block is freed, check if its buddy is also free.
- If yes, merge the two buddies into a larger block and repeat the process recursively.
- If not, add the freed block to the appropriate free list.

## Detailed Example: 1MB Memory Block

Let's walk through a complete example with a 1MB (1024KB) memory segment. We'll track each allocation and deallocation step by step.

### Memory Block Sizes
In our example, we'll work with these block sizes (all in KB):
- 1024 (1MB)
- 512
- 256
- 128
- 64
- 32
- 16
- 8
- 4
- 2
- 1

### Initial State
```
Memory: [1024KB (free)]
Free Lists:
- 1024KB: [1024KB]
- All other sizes: []
```

### Step 1: Request 100KB Allocation
**Request**: Allocate 100KB
**Action**: 
1. Find the smallest block ≥100KB → 128KB
2. No 128KB block available, so we need to split larger blocks
3. Split 1024KB → 512KB + 512KB
4. Still no 128KB, so split one 512KB → 256KB + 256KB
5. Still no 128KB, so split one 256KB → 128KB + 128KB
6. Now we have a 128KB block to allocate

**Memory Layout**:
```
1024KB
├── 512KB (free)
└── 512KB
    ├── 256KB (free)
    └── 256KB
        ├── 128KB (allocated for 100KB request)
        └── 128KB (free)
```

**Free Lists**:
- 128KB: [128KB]
- 256KB: [256KB]
- 512KB: [512KB]
- 1024KB: []

### Step 2: Request 240KB Allocation
**Request**: Allocate 240KB
**Action**:
1. Find smallest block ≥240KB → 256KB
2. We have a free 256KB block
3. Allocate the 256KB block (wastes 16KB as internal fragmentation)

**Memory Layout**:
```
1024KB
├── 512KB (free)
└── 512KB
    ├── 256KB (allocated for 240KB request)
    └── 256KB
        ├── 128KB (allocated for 100KB request)
        └── 128KB (free)
```

**Free Lists**:
- 128KB: [128KB]
- 256KB: []
- 512KB: [512KB]
- 1024KB: []

### Step 3: Free the 100KB Allocation (128KB Block)
**Action**:
1. Free the 128KB block
2. Check its buddy: other 128KB is free
3. Merge into 256KB block
4. Check new 256KB block's buddy: it's allocated, so stop merging

**Memory Layout**:
```
1024KB
├── 512KB (free)
└── 512KB
    ├── 256KB (allocated for 240KB request)
    └── 256KB (free, from merged 128KB buddies)
```

**Free Lists**:
- 128KB: []
- 256KB: [256KB]  (from merged 128KB buddies)
- 512KB: [512KB]
- 1024KB: []

### Step 4: Free the 240KB Allocation (256KB Block)
**Action**:
1. Free the 256KB block
2. Check its buddy: other 256KB is free
3. Merge into 512KB block
4. Check new 512KB block's buddy: other 512KB is free
5. Merge into 1024KB block

**Final Memory Layout**:
```
1024KB (completely free)
```

**Free Lists**:
- 1024KB: [1024KB]
- All other sizes: []

### Key Observations:
1. **Splitting**: When we can't find a block of the right size, we keep splitting larger blocks in half until we get the right size.
2. **Merging**: When freeing memory, we check if the buddy block is also free. If yes, we merge them back together.
3. **Internal Fragmentation**: We sometimes waste space because we can only allocate in power-of-two sizes (e.g., allocating 256KB for a 240KB request).
4. **External Fragmentation**: The buddy system minimizes external fragmentation by always merging adjacent free blocks.
5. **Performance**: All operations (allocate, free) are O(log N) time complexity where N is the total memory size.

### Visualizing the Process
```
Initial: [1024]  (All memory free)

After 100KB alloc:
[512] [512]  (Split 1024)
[512] [256] [256]  (Split second 512)
[512] [256] [128] [128]  (Split second 256)
Allocate one 128KB block

After 240KB alloc:
[512] [256] [128] [128]  (Allocate 256KB block for 240KB request)

After freeing 100KB (128KB block):
[512] [256] [256]  (Merge two 128KB blocks)

After freeing 240KB (256KB block):
[1024]  (Merge all the way back)
```

## Advantages
- **Reduces External Fragmentation**: Merging buddies ensures larger contiguous blocks are available.
- **Fast Allocation/Deallocation**: Operations are O(log N) due to hierarchical splitting/merging.
- **Simple Coalescing**: Merging is straightforward by checking the buddy.

## Disadvantages
- **Internal Fragmentation**: Up to 50% waste if the requested size is just over a power of two.
- **Fixed Block Sizes**: Limited to power-of-two sizes, which may not fit all requests optimally.

## Implementation
Typically implemented using:
- A free list for each block size (e.g., array of linked lists).
- A binary tree to track split/merge operations.
- Bitmaps or flags to mark allocated blocks and buddies.

## References
- Knuth, D. E. (1997). *The Art of Computer Programming, Volume 1*. Addison-Wesley.
- Wilson, P. R., Johnstone, M. S., Neely, M., & Boles, D. (1995). *Dynamic Storage Allocation: A Survey and Critical Review.*