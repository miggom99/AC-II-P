.data 
.text
.globl main

# $t0 = c
main:	li $t0,0
	
do:	li $v0,1
	move $a0,$v0
	syscall
	li $v0,1
	syscall
	move $t0,$v0

if:	beq $t0,0,else
	move $a0,$t0
	li $v0,3
	syscall
	j while

else:	li $a0,'.'
	li $v0,3
	syscall
	
while:	beq $t0,'\n',enddo
	j do

enddo:	li $v0,0
	jr $ra
	