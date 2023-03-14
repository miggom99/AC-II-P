    .equ BASE, 0xBF88
    .equ TRISD, 0x60C0
    .equ PORTD, 0x60D0
    .equ TRISE, 0x6100
    .equ LATE, 0x6120
    
    .data
    .text
    .globl main

main:   lui $t0,BASE
        lw $t1, TRISD($t0)
        ori $t1,$t1,0x0100
        sw $t1,TRISD($t0)

        lw $t1,TRISE($t0)
        andi $t1,$t1, 0xFFFE
        sw $t1,TRISE($t0)

loop:
        lw $t1, PORTD($t0)
        andi $t1,$t1, 0x0100

        lw $t2,LATE($t0)
        andi $t2,$t2, 0xFFFE
        srl $t1,$t1,8 	#0000 0001 0000 0000 -> 0000 0000 0000 0001
	xori $t2,$t1,1	#RE0 = RD8
        sw $t2,LATE($t0)

        j loop 
        jr $ra
