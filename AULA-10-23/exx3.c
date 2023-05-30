#include <detpic32.h>
#include <stdbool.h>


void configureUART2(int bps, bool parity, int dataBits, int nstopBits);
void putstr(char *str);
void putc(char byte);

int main(void){
    configureUART2(115200, false, 8, 1);

    while(1){
        putstr("String de teste\n");
        resetCoreTimer();
        while(readCoreTimer() < 20000000);
    }

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

 void putstr(char *str)
 {
    int i= 0;
 // use putc() function to send each charater ('\0' should not be sent)
    while(str[i] != '\0'){
        putc(str[i++]);
    }
    
 } 

void putc(char byte)
 {
    // wait 
    while (U2STAbits.UTXBF == 1);
    // Copy "byte" to the U2TXREG register
    U2TXREG = byte;
 } 

