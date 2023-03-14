.data
# Mapa de registos:
# 1000 = 10^3($t0) - k
# $t1 - ms

.equ READ_CORE_TIMER,11
.equ RESET_CORE_TIMER,12

.text
.globl main

main:
delay:  li $v0,RESET_CORE_TIMER
        syscall

whiledelay:
        li $t0,1000
        li $t1,4294967
        mul $t0,$t0,$t1
        li $v0,READ_CORE_TIMER
        syscall
        bge $v0,$t0,enddelay
        j whiledelay

enddelay:
        li $v0,0
        jr $ra


    