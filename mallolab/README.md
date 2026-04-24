# malloc_lab — Custom Memory Allocator

Implementation of `malloc`, `free`, `realloc`, and `calloc` from scratch.

## Architecture

Implicit free list with boundary tags (header + footer per block).

```
[ header | payload | footer ] [ header | payload | footer ] ...
```

- Header/footer encode size + allocated bit in a single `unsigned int`
- Bit 0 = allocated (1) or free (0)
- Remaining bits = block size (multiple of 8)

## Phases

### Phase 1 — Implicit free list
- `mem_init`: initialize heap via `sbrk`
- `mem_malloc`: first-fit search + block splitting
- `mem_free`: forward coalescence

### Phase 2 — Boundary tags
- Header + footer per block for O(1) bidirectional coalescence
- `get_prev`: reads footer at `header - 1` to find previous block
- `get_next`: advances by `header_size + block_size + footer_size`
- Bidirectional coalescence in `mem_free`

## Files

| File | Description |
|------|-------------|
| `allocator.c` | Core allocator logic |
| `allocator.h` | Public API |
| `block.c` | Block encoding/decoding |
| `block.h` | Block interface |
