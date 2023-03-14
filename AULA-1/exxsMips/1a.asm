.data 
.text
.globl main

# $t0 = c
main:	li $t0,0
	
do:	li $v0,12
	syscall
	move $t0,$v0
	move $a0,$t0
	li $v0,11
	syscall

while:	beq $t0,'\n',enddo
	j do

enddo:	li $v0,0
	jr $ra
	
	
	
