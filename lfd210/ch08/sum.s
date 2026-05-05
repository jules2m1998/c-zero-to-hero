.data
arr: .word 5, 8, 2, 2, 1
sum: .word

.text
.align 2
.globl main

main:
    la  t0, arr     # t0 points to arr

    addi t1, t0, 0  # t1 will traverse the array
    addi t2, x0, 5  # t2 implements i
    addi t3, x0, 0  # t3 implements sum

for:
    beqz t2, finish # contion to stop
    lw  t4, 0(t1)    # t4 is arr[i]
    add t3, t3, t4   # sum += arr[i]
    addi t1, t1, 4   # Next element of arr
    addi t2, t2, -1  # Decrement the counter (instead of i++)
    j for

finish:
    sw  t3, 20(t0)   # Update sum
    mv  a0, t3
    ret
