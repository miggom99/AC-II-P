.data
# Mapa de registos
# $s0 - cnt1
# $s1 - cnt5
# $s2 - cnt10
# $s3 - valf1 to x2
# $s4 - valf5 to x2
# $s5 - valf10 to x2
.equ PRINT_INT,6
.equ PUT_CHAR,3
.equ READ_CORE_TIMER,11
.equ RESET_CORE_TIMER,12
.equ IN_KEY,1

.text
.globl main

main:   
        addiu $sp,$sp,-20
        sw $s0,0($sp)
        sw $s1,4($sp)
        sw $s2,8($sp)
        sw $s3,12($sp)
        sw $ra,16($sp)

        li $s0,0
        li $s1,0
        li $s2,0
        li $s3,100
while:

        move $a0,$s3
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


        li $a0,'\n'
        li $v0,PUT_CHAR
        syscall

ifputS: li $v0,IN_KEY
        syscall
        bne $v0,'S',if2x

whileput:     
        li $v0,IN_KEY
        syscall
        beq $v0,'R',if2x
        j whileput


if2x:   li $v0,IN_KEY
        syscall
        bne $v0,'A',endif2x
        div $s3,$s3,2

endif2x:
        addiu $s2,$s2,1

if:     rem $t0,$s2,2
        bne $t0,0,if2
        addiu $s1,$s1,1

if2:    li $t1,10
        rem $t0,$s2,10
        bne $t0,0,while
        addiu $s0,$s0,1


        j while

        lw $s0,0($sp)
        lw $s1,4($sp)
        lw $s2,8($sp)
        lw $s3,12($sp)
        lw $ra,16($sp)
        addiu $sp,$sp,20
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
