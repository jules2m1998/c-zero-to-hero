.data
i: .word 5
c: .byte 'A'
x: .byte 'B'

.text
.align 2
.globl main

main:
    la   t0, i
    lw   t1, 0(t0)     # t1 = i = 5
    lb   t2, 4(t0)     # t2 = c = 'A' = 0x41

    addi t1, t1, 1     # i++ → 6
    addi t2, t2, 32    # c += 32 → 'a' = 0x61

    # sw et sb commentes — pk ne permet pas ecrire en .data
    # sw   t1, 0(t0)
    # sb   t2, 4(t0)

    # retourne t2 (0x61 = 97) pour verifier
    mv   a0, t2
    ret
