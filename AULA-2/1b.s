	.equ READ_CORE_TIMER,11
 	.equ RESET_CORE_TIMER,12
 	.equ PUT_CHAR,3
 	.equ PRINT_INT,6
 	.data
 	.text
 	.globl main

#$t0 - counter
#$t1 - 1 do while para ficar sempre true
main: 	li $t0,0
	li $t1,0

#$t2 - readCoreTimer()
while: 	beq $t1,1,end
 	li $v0,RESET_CORE_TIMER #
 	syscall #
 	li $v0,READ_CORE_TIMER
 	syscall
 	move $t2,$v0
 	bge $t2,200000,while
 	addiu $t0,$t0,1
 	move $a0,$t0
 	li $a1,0x0004000A
 	li $v0,PRINT_INT
 	syscall
 	li $a0,'\r'
 	li $v0,PUT_CHAR
 	syscall
 	j while	
 	
end: 	li $v0,0
	jr $ra