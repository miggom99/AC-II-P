.data 
str0:	.asciiz "\nIntroduza um inteiro (sinal e módulo): "
str1:	.asciiz "\nValor em base 10 (signed): "
str2:	.asciiz "\nValor em base 2: "
str3:	.asciiz "\nValor em base 16: "
str4:	.asciiz "\nValor em base 10 (unsigned): "
str5:	.asciiz "\nValor em base 10 (unsigned), formatado: "
.text
.globl main

# $t0 - value
main:	beq $t0,1,end
	la $a0,str0
	li $v0,8
	syscall
	
	li $v0,5
	syscall
	
	move $t0,$v0
	la $a0,str1
	li $v0,8
	syscall
	
	move $a0,$t0
	li $v0,7
	syscall
	
	la $a0,str2
	li $v0,8
	syscall
	
	move $a0,$t0
	li $a1,2
	li $v0,6
	syscall
	

	la $a0,str3
	li $v0,8
	syscall
	
	move $a0,$t0
	li $a1,16
	li $v0,6
	syscall
	
	la $a0,str4
	li $v0,8
	syscall
	
	move $a0,$t0
	li $a1,10
	li $v0,6
	syscall
	
	la $a0,str5
	li $v0,8
	syscall
	
	move $a0,$t0
	li $a1,0x00040002
	li $v0,6
	syscall
	
	j main

end: jr $ra