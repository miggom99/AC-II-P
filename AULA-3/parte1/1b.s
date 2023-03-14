	.data
	.equ SFR_BASE_HIGH,0xBF88
	.equ TRISE,0x6100
	.equ PORTE,0x6110
	.equ LATE,0x6120
	.equ TRISB,0x6040
	.equ PORTB,0x6050
	.equ LATB,0x6060
	.text
	.globl main
main:

	lui 	$t0,SFR_BASE_HIGH
	lw 	$t1,TRISE($t0)		#Read
	andi 	$t1,$t1,0xFFFE 	#RE0 = out	#Modify
	sw 	$t1,TRISE($t0)		#Write

	lw 	$t1,TRISB($t0)		#Read
	andi 	$t1,$t1,0xFFFE		#Modify
	ori 	$t1,$t1,0x0001 	#RB0 = in	
	sw 	$t1,TRISB($t0)		#Write

loop:
	lw 	$t1,PORTB($t0)
	andi 	$t2,$t1,0x0001	#Read only RB0

	lw 	$t1,LATE($t0)
	andi 	$t1,$t1,0xFFFE	#cleaning output before placing input
	xori 	$t1,$t2,1	#RE0 = RB0\
	sw 	$t1,LATE($t0)	#write

	j loop
	jr $ra
			
