    .equ BASE, 0xBF88
    .equ TRISB, 0x6040
    .equ PORTB, 0x6050
    .equ TRISE, 0x6100
    .equ LATE, 0x6120
    .equ READ_CORE_TIMER,11
    .equ RESET_CORE_TIMER,12
    
    .data
    .text
    .globl main

main:   lui $t0,BASE
        lw $t1, TRISB($t0)
        ori $t1,$t1,0x0001
        sw $t1,TRISB($t0)

        lw $t1,TRISE($t0)
        andi $t1,$t1, 0xFFFE
        sw $t1,TRISE($t0)

loop:
        lw $t1, PORTB($t0)
        andi $t1,$t1, 0x0001
        xori $t1,$t1, 0x0001

        lw $t2,LATE($t0)
        andi $t2,$t2, 0xFFFE
        or $t2,$t2,$t1
        sw $t2,LATE($t0)

        j loop 
        jr $ra
