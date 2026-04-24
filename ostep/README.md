# OSTEP — Operating Systems: Three Easy Pieces

OS internals: virtualization, concurrency, persistence.
Goal: prerequisites for RISC-V Fundamentals (LFD210).

## Progress

| Part | Topic | Status |
|------|-------|--------|
| I — Virtualization (processes) | fork/exec/wait, scheduler, PCB, context switch | IN PROGRESS |
| I — Virtualization (memory) | virtual memory, paging, MMU, TLB, demand paging | IN PROGRESS |
| II — Concurrency | threads, race conditions, mutex, deadlock | IN PROGRESS |
| III — Persistence | filesystems, journaling | TODO |

## Key concepts covered

- Time sharing — preemptive scheduler via timer interrupt
- PCB — Process Control Block (pid, state, registers, memory maps, open files)
- Process states: running, ready, blocked
- `fork()` / `exec()` / `waitpid()` — Unix process model
- Copy-on-Write — lazy memory duplication after fork
- Virtual memory — every process has its own address space
- Page table — virtual → physical address translation via MMU
- Demand paging — pages loaded on page fault, not upfront
- Overcommitment and OOM Killer
- `mmap` vs `sbrk` for memory allocation
- Threads — shared heap, separate stacks
- Race conditions — non-atomic `counter++`
- Mutex — mutual exclusion for critical sections
- Cache coherence — cache line bouncing between cores

## Project

Mini-shell — `fork`, `exec`, `wait`, pipes, redirection.
