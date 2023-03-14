	.data
	.equ SFR_BASE_HIGH,0xBF88
	.equ READ_CORE_TIMER,11
 	.equ RESET_CORE_TIMER,12
	.equ TRISE,0x6100
	.equ PORTE,0x6110
	.equ LATE,0x6120
	.equ TRISB,0x6040
	.equ PORTB,0x6050
	.equ LATB,0x6060
	
	.equ TRISD,0x60C0
	.equ PORTD,0x60D0
	.equ LATD,0x60E0
	
	.text
	.globl main
	
#$s1 = v
main:	addiu	$sp,$sp,-16
	sw	$ra,0($sp)
	sw	$s0,4($sp)
	sw	$s1,8($sp)

	li $s1,0
	
	lui 	$s0,SFR_BASE_HIGH
	lw 	$t1,TRISE($s0)		#Read
	andi 	$t1,$t1,0xFFFE 	#RE0 = out	#Modify
	sw 	$t1,TRISE($s0)		#Write

	lw 	$t1,TRISB($s0)		#Read
	ori 	$t1,$t1,0x0001 	#RB0 = in	
	sw 	$t1,TRISB($s0)		#Write
	
	lw 	$t1,TRISE($s0)		#Read
	andi 	$t1,$t1,0xFFFD 	#RE1 = out	#Modify
	sw 	$t1,TRISE($s0)		#Write

	lw 	$t1,TRISB($s0)		#Read
	ori 	$t1,$t1,0x0002 	#RB1 = in	
	sw 	$t1,TRISB($s0)		#Write
	
	lw 	$t1,TRISE($s0)		#Read
	andi 	$t1,$t1,0xFFFB 	#RE2 = out	#Modify
	sw 	$t1,TRISE($s0)		#Write

	lw 	$t1,TRISB($s0)		#Read
	ori 	$t1,$t1,0x0004 	#RB2 = in	
	sw 	$t1,TRISB($s0)		#Write
	
	lw 	$t1,TRISE($s0)		#Read
	andi 	$t1,$t1,0xFFF7 	#RE3 = out	#Modify
	sw 	$t1,TRISE($s0)		#Write

	lw 	$t1,TRISB($s0)		#Read
	ori 	$t1,$t1,0x0008 	#RB3 = in	
	sw 	$t1,TRISB($s0)		#Write


	
while:	bgt	$s1,15,endw
	lw 	$t1,PORTB($s0)
	andi 	$t2,$t1,0x0001	#Read only RB0

	lw 	$t1,LATE($s0)
	andi 	$t1,$t1,0xFFFE	#cleaning output before placing input (RE0)
	andi	$t3,$s1,0x0001	# $s1 na posição 0
	or	$t1,$t1,$t3	#RE0 = $s1 na posição 0
	sw 	$t1,LATE($s0)	#write
	
	lw 	$t1,PORTB($s0)
	andi 	$t2,$t1,0x0002	#Read only RB1

	lw 	$t1,LATE($s0)
	andi 	$t1,$t1,0xFFFD	#cleaning output before placing input (RE1)
	andi	$t3,$s1,0x0002	# $s1 na posição 2
	or 	$t1,$t1,$t3	#RE0 = $s1 na posição 2
	sw 	$t1,LATE($s0)	#write
	
	lw 	$t1,PORTB($s0)
	andi 	$t2,$t1,0x0004	#Read only RB2

	lw 	$t1,LATE($s0)
	andi 	$t1,$t1,0xFFFB	#cleaning output before placing input (RE2)
	andi	$t3,$s1,0x0004	# $s1 na posição 3
	or 	$t1,$t1,$t3	#RE0 = $s1 na posição 3
	sw 	$t1,LATE($s0)	#write
	
	lw 	$t1,PORTB($s0)
	andi 	$t2,$t1,0x0008	#Read only RB3

	lw 	$t1,LATE($s0)
	andi 	$t1,$t1,0xFFF7	#cleaning output before placing input (RE3)
	andi	$t3,$s1,0x0008	# $s1 na posição 3
	or 	$t1,$t1,$t3	#RE0 = $s1 na posição 3
	sw 	$t1,LATE($s0)	#write

	
	jal delay
	
	addiu $s1,$s1,1
	
	j while
	
endw:	lw	$ra,0($sp)
	lw	$s0,4($sp)
	lw	$s1,8($sp)
	addiu	$sp,$sp,16
	jr $ra
	
	
	
delay:	


 	li $v0,RESET_CORE_TIMER
	syscall
whiledelay:	
	li $v0,READ_CORE_TIMER	
	syscall
	blt $v0,1000000,whiledelay
		
	jr $ra
	
