    .equ BASE, 0xBF88
    .equ TRISE, 0x6100
    .equ LATE, 0x6120
    .equ READ_CORE_TIMER,11
    .equ RESET_CORE_TIMER,12
    .equ PRINT_INT10,7
    
    .data
    .text
    .globl main

main:   addiu $sp,$sp,-20
        sw $s0,0($sp)
        sw $s1,4($sp)
        sw $s2,8($sp)
        sw $s3,12($sp)
        sw $ra,16($sp)

        li $s2,0 # counter = 0

        lui $s0,BASE 
        lw $s1,TRISE($s0)
        andi $s1,$s1,0xFFE1  #1110 0001
        sw $s1,TRISE($s0)

loop:   bgt $s2,15,reset

        move $a0,$s2
        li $v0,PRINT_INT10
        syscall

        lw $s1, LATE($s0)
        andi $s1,$s1, 0xFFE1

        sll $s3,$s2,1 # shift left para ficar no registo do led
        addu $s1,$s1,$s3
        sw $s1, LATE($s0)

        addiu $s2,$s2,1

        li $a0,10000
        jal delay

        j loop

reset:  li $s2,0 # counter = 0
        j loop

        
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


