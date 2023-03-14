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
	andi 	$t1,$t1,0xFFFE 	#RE0 = out	#Modify
	sw 	$t1,TRISE($s0)		#Write
	
while:		
	lw 	$t1,LATE($s0)
	andi 	$t1,$t1,0xFFFE	#cleaning output before placing input (RE0)
	or 	$t1,$t1,$s1	#RE0 = v
	sw 	$t1,LATE($s0)	#write
	
	jal delay
	
	xori $s1,$s1,1
	
	j while
	
	lw	$ra,0($sp)
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
	blt $v0,10000000,whiledelay
	
end:	jr $ra
