#include <detpic32.h>
#include <stdbool.h>

void configureUART2(int bps, bool parity, int dataBits, int nstopBits);
void putc(char byte);

int main(void){
    configureUART2(115200, false, 8, 1);
    // Configure UART2 interrupts, with RX interrupts enabled
    // and TX interrupts disabled:
    // enable U2RXIE, disable U2TXIE (register IEC1)    
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    
    
    // set UART2 priority level (register IPC8)
    IPC8bits.U2IP = 2;
    // clear Interrupt Flag bit U2RXIF (register IFS1)
    IFS1bits.U2RXIF = 0;
    // define RX interrupt mode (URXISEL bits)

    U2STAbits.URXISEL = 0;
    // Enable global Interrupts

    EnableInterrupts();

    while(1);
    return 0; 
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

void _int_(32) isr_uart2(void)
 {
    if (IFS1bits.U2RXIF)
    {
        // Read character from FIFO (U2RXREG)
        char c = U2RXREG;
        // Send the character using putc()
        putc(c);
        // Clear UART2 Rx interrupt flag
        IFS1bits.U2RXIF = 0;
    }
 }

 void putc(char byte)
 {
    // wait 
    while (U2STAbits.UTXBF == 1);
    // Copy "byte" to the U2TXREG register
    U2TXREG = byte;
 } 

