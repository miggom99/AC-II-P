.data

# Mapa de registos:
# c = $t0

.text
.globl main

main:   
do:     li $v0,1        #inkey != do putchar pq não espera que o utilizador 
                        #prima uma teclapara devolver um valor, devolve logo 
                        # 0x00
        syscall
        move $t0,$v0

if:     beq $t0,0,else
        move $a0,$t0
        li $v0,3
        syscall

else:   li $a0,'.'
        li $v0,3
        syscall

while:  bne $t0,'\n',do
        li $v0,0
        jr $ra