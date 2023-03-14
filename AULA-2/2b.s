	.data
	.equ READ_CORE_TIMER,11
 	.equ RESET_CORE_TIMER,12
	.text
	.globl main
	
# $t0 - readCoreTimer()
# $t1 - K
# $t2 - ms

main: 	li $v0,RESET_CORE_TIMER
	syscall
	li $v0,READ_CORE_TIMER	
	syscall
	move $t0,$v0
	li $t1,20000000
	li $t2,1
	mul $t3,$t1,$t2
	bge $t0,$t3,end
	j main
	
end:	jr $ra
	