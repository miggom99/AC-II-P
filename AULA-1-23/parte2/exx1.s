.data
.text
.globl main

# Mapa de registos:
# c = $t0
main:   
do:     li $v0,2
        syscall
        move $t0,$v0
        
        move $a0,$t0
        li $v0,3
        syscall

while:  bne $t0,'\n',do
        li $v0,0
        jr $ra
        