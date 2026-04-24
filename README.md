# C — Zero to Hero

Systems programming journey from managed ecosystems to bare metal C.
Strict Socratic mentorship, chapter by chapter, code at every concept.

## Roadmap

| Phase | Resource | Project | Status |
|-------|----------|---------|--------|
| 1 | K&R — The C Programming Language | malloc_lab | DONE |
| 2 | cserve — Async HTTP server | cserve | DONE |
| 3 | Expert C Programming (van der Linden) | cdecl | DONE |
| 4 | OSTEP — Operating Systems: Three Easy Pieces | mini-shell | IN PROGRESS |
| 5 | RISC-V Fundamentals (LFD210) | — | TODO |

## Structure

```
c-zero-to-hero/
├── krc/          # K&R exercises, ch01–ch08
├── mallolab/     # Custom malloc — implicit free list + boundary tags
├── cserver/      # Async HTTP server — kqueue, static file serving
├── expert-c/     # Expert C exercises + cdecl project
│   └── cdecl/    # C declaration explainer (right-left rule parser)
└── ostep/        # OS internals — processes, memory, concurrency
```

## Goals

- Intimate mastery of manual memory management
- Understanding of OS internals (scheduler, virtual memory, concurrency)
- Systems programming foundation for embedded/RISC-V work
