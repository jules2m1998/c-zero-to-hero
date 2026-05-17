# call_asm.s
.section .text
.globl main

main:
    addi sp, sp, -32
    # callee saves ra, s1
    sd  ra, 24(sp)
    sd  s1, 16(sp)
    addi    s1, x0, 8
    addi    t1, x0, 4
    addi    a0, x0, 2

    # call function
    # save t1 (caller)
    sd  t1, 8(sp)
    # argument s0
    call    function_c
    # restaure t1
    ld  t1, 8(sp)
    add a0, a0, t1
    add a0, a0, s1
    ld  s1, 16(sp)
    ld  ra, 24(sp)
    addi    sp, sp, 32
    ret
