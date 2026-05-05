.data
a: .word 3
b: .word 4
c: .word 0

.text
.align 2
.globl main

main:
    la   t0, a
    lw   t1, 0(t0)
    lw   t2, 4(t0)
    add  t3, t1, t2
    # sw t3, 8(t0)   # store desactive — pk ne permet pas ecrire en .data
    mv   a0, t3
    ret
