#include <detpic32.h>

typedef struct
 {
 	char mem[100]; // Storage area
 	int nchar; // Number of characters to be transmitted
 	int posrd; // Position of the next character to be transmitted
 } t_buf; 
 
 volatile t_buf txbuf;
 
 void putstrInt(char *s)
 {
 	while(txbuf.nchar > 0); // Wait while the buffer is not empty
 	// Copy all characters of the string "s" to the buffer
 	while(*s != '\0') {
 		txbif.mem[nchar] = *s;
 		nchar++;
 	}
 	// Initialize "posrd" variable with 0
 	txbuf.posrd=0;
 	// Enable UART2 Tx interrupts
 	IEC1bits.U2TXIE = 1;
 } 
 
 void _int_(VECTOR_UART2) isr_uart2(void)
 {
 	if (IFS1bits.U2RXIF == 1)
 	{
 		if(txbuf.nchar > 0) { // At least one character to be transmitted
 		 	U2TXREG = txbuf.mem[txbuf.posrd] // Read 1 character from 
 			//the buffer and send it
 			txbuf.posrd++;
 			// Update buffer "posrd" and "nchar" variables
	 	} else {
		 	U2STAbits.URXISEL = 0;
		 	// Disable UART2 Tx interrupts
	 	}
		 // Clear UART2 Tx interrupt flag
		 IFS1bits.U2RXIF = 0;
 	}
 } 
