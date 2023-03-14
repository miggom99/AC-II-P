	.data
	.equ SFR_BASE_HIGH,0xBF88
	.equ TRISE,0x6100
	.equ PORTE,0x6110
	.equ LATE,0x6120
	.equ TRISD,0x60C0
	.equ PORTD,0x60D0
	.equ LATD,0x60E0
	.text
	.globl main
main:

	lui 	$t0,SFR_BASE_HIGH
	lw 	$t1,TRISE($t0)		#Read
	andi 	$t1,$t1,0xFFFE 	#RE0 = out	#Modify
	sw 	$t1,TRISE($t0)		#Write

	lw 	$t1,TRISD($t0)		#Read
	ori 	$t1,$t1,0x0100		#Modify	#RD8 = in	
	sw 	$t1,TRISD($t0)		#Write

loop:
	lw 	$t1,PORTD($t0)
	andi 	$t2,$t1,0x0100	#Read only RD8

	lw 	$t1,LATE($t0)
	andi 	$t1,$t1,0xFFFE	#cleaning output before placing input
	srl 	$t2,$t2,8 	#0000 0001 0000 0000 -> 0000 0000 0000 0001
	xori	$t1,$t2,1	#RE0 = RD8
	sw 	$t1,LATE($t0)	#write

	j loop
	jr $ra
		
