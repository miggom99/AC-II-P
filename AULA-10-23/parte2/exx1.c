#include <detpic32.h>
#include <stdbool.h>


void configureUART1(int bps, bool parity, int dataBits, int nstopBits);
//char getc(void);
void putc(char byte);

int main(void){
    configureUART1(115200, false, 8, 1);

    while(1){
        putc(0x5A);
    }

    return 0;

}

void configureUART1(int bps, bool parity, int dataBits, int nstopBits){
    // Configure UART1:
    // 115200 bps, sem paridade, 8 data bits, 
    // 1 stop bit (consulte os registos UxMODE e UxSTA no manual da UART). 
    int nPDSEL;
    int nStop;
    int nU1brg;
    // 1 - Configure BaudRate Generator

    U1MODEbits.BRGH = 0; // Divisão do relogio por 16

    // ((20M +8*115200) / (16 * 115200)) -1 = 10.35
    nU1brg = ((20000000 + (8*bps)) / (16 * 115200)) -1;
    U1BRG = nU1brg;

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
    U1MODEbits.PDSEL = nPDSEL;

    if(nstopBits == 1){
        nStop = 0;
    }else{
        nStop = 1;
    }

    U1MODEbits.STSEL = nStop;
    
    // 3 – Enable the trasmitter and receiver modules (see register U2STA)
    U1STAbits.URXEN = 1;
    U1STAbits.UTXEN = 1;
    
    // 4 – Enable UART1 (see register U2MODE)
    U1MODEbits.ON = 1;
}

//  char getc(void)
//  {
//     // Wait while URXDA == 0
//     while(U1STAbits.URXDA == 0);
//     // Return U1RXREG
//     return U1RXREG;
//  } 

void putc(char byte)
 {
    // wait 
    while (U1STAbits.UTXBF == 1);
    // Copy "byte" to the U1TXREG register
    U1TXREG = byte;
 } 