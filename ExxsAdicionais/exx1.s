
    .equ SFR_BASE_HI, 0xBF88
    .equ TRISE, 0x6100 #saida
    .equ TRISB, 0x6040 #entrada
    .equ PORTB, 0x6050
    .equ LATE, 0x6120
.data
.text
.globl main

main:   lui $t0, SFR_BASE_HI
        lw $t1, TRISE($t0)
        andi $t1,$t1, 0xFFF0
        sw $t1, TRISE($t0)

        lw $t1, TRISB($t0)
        ori $t1,$t1, 0x000F 
        sw $t1, TRISB($t0)

loop:  
        lw $t1, PORTB($t0)
        andi $t1,$t1, 0x000F
        move $a0,$t1
        li $a1,16
        li $v0,6
        syscall
        
        lw $t2, LATE($t0)
        andi $t2,$t2, 0xFFF0
        or $t2,$t2,$t1
        sw $t2, LATE($t0)
        
        j loop

        jr $ra




