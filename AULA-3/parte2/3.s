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
	lw 	$t1,TRISE($s0)
	andi 	$t1,$t1,0xFFF0	#modify //RE[3..0]=out
	sw 	$t1,TRISE($s0)
	
	lw 	$t1,TRISB($s0)	#read	
	ori 	$t1,$t1,0x0008	#modify //RB3=in
	sw 	$t1,TRISB($s0)	#write
	
	
while:	lw 	$t1,PORTB($s0)
	andi 	$t1,$t1,0x0008	#Read only RB3
if:	bne	$t1,0,else

	lw 	$t1,LATE($s0)
	andi 	$t1,$t1,0xFFF0	#clean LATE[3..0]
	or 	$t1,$t1,$s1	#LATE = LATE + CNT
	sw 	$t1,LATE($s0)	#write
	addiu 	$s1,$s1,-1
	j else
	
else:	bne	$t1,0x0008,endif

	lw 	$t1,LATE($s0)
	andi 	$t1,$t1,0xFFF0	#clean LATE[3..0]
	or 	$t1,$t1,$s1	#LATE = LATE + CNT
	sw 	$t1,LATE($s0)	#write
	addiu 	$s1,$s1,1
	j endif

endif:	jal delay
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
	blt $v0,2000000,whiledelay
		
	jr $ra
