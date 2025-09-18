# Buddy Memory Allocator - Bitmap Visualization

This document illustrates how the buddy memory allocator manages memory blocks using bitmaps. We'll walk through a 16-byte heap example with `MAX_ORDER = 4`.

## Memory Block Sizes

| Order | Block Size | Number of Blocks |
|-------|------------|------------------|
|   0   |     1 B    |        16        |
|   1   |     2 B    |        8         |
|   2   |     4 B    |        4         |
|   3   |     8 B    |        2         |
|   4   |    16 B    |        1         |

## Initial State (All Memory Free)

```
Order 0: 0000000000000000  # 16 x 1B blocks
Order 1: 00000000          # 8 x 2B blocks
Order 2: 0000              # 4 x 4B blocks
Order 3: 00                # 2 x 8B blocks
Order 4: 0                 # 1 x 16B block
```

## Step 1 — Allocate 4B (Order 2 Block 0)

Allocate a 4B block by marking the first order 2 block as used.

```
Order 2: 1000  # Block 0 allocated
```

## Step 2 — Allocate 2B (Split Order 2 Block 1)

1. No free 2B blocks available
2. Split order 2 block 1 into two order 1 blocks
3. Allocate order 1 block 2

```
Order 1: 00100000  # Block 2 allocated
Order 2: 1000      # Block 1 is split (not allocated)
```

## Step 3 — Free 2B (Order 1 Block 2)

1. Free order 1 block 2
2. Its buddy (block 3) is free → merge into order 2 block 1
3. Order 2 block 1's buddy is allocated, so merging stops

```
Order 1: 00000000  # Both 2B blocks free
Order 2: 1000      # Block 1 is now free and mergeable
```

## Step 4 — Free 4B (Order 2 Block 0)

1. Free order 2 block 0
2. Its buddy (block 1) is free → merge into order 3 block 0
3. Order 3 block 0's buddy is free → merge into order 4 block 0

```
Order 2: 0000  # All 4B blocks free
Order 3: 00    # All 8B blocks free
Order 4: 0     # 16B block free
```

## ✅ Key Takeaways

1. **Splitting**:
   - When allocating, split larger blocks only as needed
   - Parent blocks are marked as split, not allocated

2. **Merging**:
   - Triggered on free operations
   - Check if buddy is free → merge → recurse upward
   - Continue until buddy is allocated or max order reached

3. **Bitmap Semantics**:
   - 0: Block is completely free at this order
   - 1: Block is either allocated or split (not available at this order)
   - The allocator must track whether a block is split or allocated separately

## 🖼️ Memory Layout Evolution

```
Initial: [................]  (16B free)
Step 1:  [AAAA][............]  (4B allocated, 12B free)
Step 2:  [AAAA][BB][..][........]  (split 4B → alloc 2B, 2B free, 8B free)
Step 3:  [AAAA][....][........]  (free BB → merged with buddy → 4B free)
Step 4:  [................]  (free AAAA → merged with adjacent 4B → 8B → merged with other 8B → 16B free)
```

Where:
- `A` = first 4B allocated
- `B` = 2B allocated from split
- `.` = free memory
