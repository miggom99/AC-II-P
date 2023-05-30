#include <stdbool.h>
#include <detpic32.h>

typedef struct
 {
    char mem[100]; // Storage area
    int nchar; // Number of characters to be transmitted
    int posrd; // Position of the next character to be transmitted
 } t_buf; 

volatile t_buf txbuf;


void _int_(32) isr_uart2(void)
{
    if (IFS1bits.U2TXIF)
    {
        if (txbuf.nchar > 0)
        { 
            // At least one character to be transmitted
            // U2TXREG = ... // Read 1 character from the buffer and
            U2TXREG = txbuf.mem[txbuf.posrd++];
            // Update buffer "posrd" and "nchar" variables
            txbuf.nchar--;
        }
        else
        {
            // Disable UART2 Tx interrupts
            IEC1bits.U2TXIE = 0;
        }
        // Clear UART2 Tx interrupt flag
        IFS1bits.U2TXIF= 0;
    }
}

void putstrInt(char *s);
void configureUART2(int bps, bool parity, int dataBits, int nstopBits);
int main(void)
{
    // Configure UART2: 115200, N, 8, 1
    configureUART2(115200, false, 8, 1);
    // Configure UART2 interrupts, with RX and TX interrupts DISABLED
    //  disable U2RXIE, disable U2TXIE (register IEC1)
    IEC1bits.U2RXIE = 0;
    IEC1bits.U2TXIE = 0;
    //  set UART2 priority level (register IPC8)
    IPC8bits.U2IP = 2;
    //  define TX interrupt mode (UTXISEL bits)
    U2STAbits.UTXISEL = 0;
    // Enable global Interrupts
    EnableInterrupts();
    // Initialize buffer variable "nchar" with 0
    txbuf.nchar = 0;
    while (1)
    {
        putstrInt("Test string which can be as long as you like, up to a maximum of 100 characters\n");
    }
    return 0;
}


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

void configureUART2(int bps, bool parity, int dataBits, int nstopBits){
    // Configure UART2:
    // 115200 bps, sem paridade, 8 data bits, 
    // 1 stop bit (consulte os registos UxMODE e UxSTA no manual da UART). 
    int nPDSEL;
    int nStop;
    int nU2brg;
    // 1 - Configure BaudRate Generator

    U2MODEbits.BRGH = 0; // Divisão do relogio por 16

    // ((20M +8*115200) / (16 * 115200)) -1 = 10.35
    nU2brg = ((20000000 + (8*bps)) / (16 * 115200)) -1;
    U2BRG = nU2brg;

    // 2 – Configure number of data bits, parity and number of stop bits
    // (see U2MODE register)
    if (dataBits == 8){
        
        if(parity){
            nPDSEL = 2;
        
        }else{
            nPDSEL = 0;
        }

    }else{
        
        nPDSEL = 3;

    }
    U2MODEbits.PDSEL = nPDSEL;

    if(nstopBits == 1){
        nStop = 0;
    }else{
        nStop = 1;
    }

    U2MODEbits.STSEL = nStop;
    
    // 3 – Enable the trasmitter and receiver modules (see register U2STA)
    U2STAbits.URXEN = 1;
    U2STAbits.UTXEN = 1;
    
    // 4 – Enable UART2 (see register U2MODE)
    U2MODEbits.ON = 1;
}
