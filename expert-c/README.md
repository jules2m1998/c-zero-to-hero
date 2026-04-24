# Expert C Programming — Peter van der Linden

Deep C concepts: declarations, arrays vs pointers, linker, memory layout.

## Progress

| Chapter | Topic | Status |
|---------|-------|--------|
| 1 | Language hazards and pitfalls | DONE |
| 3 | Unscrambling declarations (right-left rule) | DONE |
| 4 | Arrays vs pointers | DONE |
| 5 | Linker and symbols | DONE |
| 6-7 | Memory segments (text, data, BSS, heap, stack) | DONE |

## Key concepts covered

- Operator precedence traps (`&` vs `==`)
- Undefined behavior (unsequenced modifications, `sizeof`)
- `char *` vs `char []` — read-only vs stack copy
- Right-left rule for parsing complex declarations
- `extern` type mismatch — arrays vs pointers across files
- ODR — One Definition Rule
- `static` — file-local symbols
- Memory segments: text, data, BSS, heap, stack
- Demand paging, BSS optimization
- Function pointer dispatch tables

## Project — cdecl

A C declaration explainer implementing the right-left rule.

```
$ echo "int (*(*x[3])(void))[5]" | ./cdecl
x is array 3 of pointer to function (void) returning pointer to array 5 of int
```
