.data
count:  .word   0
str:    .string "RISC-V is the bomb!!!"

.text
.align 2
.globl main

main:
    la  t0, count
    lw  t1, 0(t0)
    la  t2, str

while:
    lb  t3, 0(t2)
    beqz t3, finish
    addi t1, t1, 1
    addi t2, t2, 1
    j while

finish:
    sw  t1, 0(t0)
    mv  a0, t1
    ret
