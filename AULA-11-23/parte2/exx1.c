
typedef struct
 {
    char mem[100]; // Storage area
    int nchar; // Number of characters to be transmitted
    int posrd; // Position of the next character to be transmitted
 } t_buf; 

volatile t_buf txbuf;
void putstrInt(char *s)
{
    while (txbuf.nchar > 0); 
    // Wait while the buffer is not empty
    // Copy all characters of the string "s" to the buffer
    int i = 0;
    while (*s != '\0')
    {
        txbuf.mem[i++] = *s++;
 	}

    txbuf.nchar = i;
 	// Initialize "posrd" variable with 0
 	txbuf.posrd=0;
 	// Enable UART2 Tx interrupts
 	IEC1bits.U2TXIE = 1;
}