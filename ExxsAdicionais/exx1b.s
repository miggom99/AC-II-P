
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

        andi $t2,$t1,0x0001
        sll $t3,$t2,3

        andi $t2,$t1,0x0002
        sll $t3,$t2,1

        andi $t2,$t1,0x0004
        srl $t3,$t2,1

        andi $t2,$t1,0x0008
        srl $t3,$t2,3

        


        
        lw $t2, LATE($t0)
        andi $t2,$t2, 0xFFFE
        
        or $t2,$t2,$t3
        sw $t2, LATE($t0)
        
        j loop

        jr $ra
