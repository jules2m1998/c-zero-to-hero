.data
i: .word 5
c: .byte 'A'
x: .byte 'B'





.text
.align 2
.globl main

main:
    la  t0, i           # t0 point to i
    lw  t1, 0(t0)       # t1 implements i
    lb  t2, 4(t0)       # t2 implements c

    addi t1, t1, 1      # i++;
    addi t2, t2, 32     # c += 32;

    sw  t1, 0(t0)       # Update i
    sb  t2, 4(t0)       # Update c
    addi a0, t2, 0      # retun c
    ret

