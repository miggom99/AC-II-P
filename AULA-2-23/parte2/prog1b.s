.data
# Mapa de registos
# $s0 - cnt1
# $s1 - cnt5
# $s2 - cnt10
.equ PRINT_INT,6
.equ PUT_CHAR,3
.equ READ_CORE_TIMER,11
.equ RESET_CORE_TIMER,12

.text
.globl main

main:   
        addiu $sp,$sp,-16
        sw $s0,0($sp)
        sw $s1,4($sp)
        sw $s2,8($sp)
        sw $ra,12($sp)

        li $s0,0
        li $s1,0
        li $s2,0
while:
        li $a0,100
        jal delay
        li $a1,0x0005000A
        move $a0,$s2
        li $v0,PRINT_INT
        syscall

        li $a0,' '
        li $v0,PUT_CHAR
        syscall

        move $a0,$s1
        li $v0,PRINT_INT
        syscall

        li $a0,' '
        li $v0,PUT_CHAR
        syscall

        move $a0,$s0
        li $v0,PRINT_INT
        syscall

        li $a0,' '
        li $v0,PUT_CHAR
        syscall

        addiu $s2,$s2,1

        li $t1,2
        rem $t0,$s2,$t1
        bne $t0,0,if2
        addiu $s1,$s1,1

if2:    li $t1,10
        rem $t0,$s2,$t1
        bne $t0,0,while
        addiu $s0,$s0,1
        move $a0,$s0
        li $a1,0x0005000A
        li $v0,PRINT_INT
        syscall


        j while

        lw $s0,0($sp)
        lw $s1,4($sp)
        lw $s2,8($sp)
        lw $ra,12($sp)
        addiu $sp,$sp,16
        li $v0,0
        jr $ra

delay:  li $v0,RESET_CORE_TIMER
        syscall

whiledelay:
        li $t0,2000
        move $t1,$a0
        mul $t0,$t0,$t1
        li $v0,READ_CORE_TIMER
        syscall
        bge $v0,$t0,enddelay
        j whiledelay

enddelay:
        li $v0,0
        jr $ra
