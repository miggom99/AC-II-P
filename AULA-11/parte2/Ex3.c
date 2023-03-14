#include <detpic32.h>

void putstrInt(char *s);

typedef struct
 {
 	char mem[100]; // Storage area
 	int nchar; // Number of characters to be transmitted
 	int posrd; // Position of the next character to be transmitted
 } t_buf; 
 
 volatile t_buf txbuf;
 
void putstrInt(char *s){
    while(txbuf.nchar>0);
    while(*s!='\0'){
        txbuf.mem[txbuf.nchar] = *s;
        txbuf.nchar++;
        s++;
    }
    txbuf.posrd=0;
    IEC1bits.U2TXIE = 1;
}

void _int_(32) isr_uart2(void){
    if(IFS1bits.U2TXIF==1){
        if(txbuf.nchar>0){
            U2TXREG = txbuf.mem[txbuf.posrd];
            txbuf.posrd++;
            txbuf.nchar--;   
        } else{
            IEC1bits.U2TXIE = 0;
        }
        IFS1bits.U2TXIF=0;
    }
}
 
 int main(void){
 
 	// Configure UART2: 115200, N, 8, 1
 	//1- Configure uxbrg and U2BRG
 	U2BRG = 10;
 	U2MODEbits.BRGH = 0;
 	
 	//2-Configurar paridade e numero de stop bits
 	U2MODEbits.PDSEL = 0;
 	U2MODEbits.STSEL= 0;
 	
 	//3- ligar os modulos de transmissão e receção
 	U2STAbits.UTXEN = 1;
 	U2STAbits.URXEN = 1;
 	
 	//4- Ativar on
 	U2MODEbits.ON = 1;
 	
 	
 	// set UART2 priority level (register IPC8) 
 	IPC8bits.U2IP = 2;
 	// Configure UART2 interrupts, with RX and TX interrupts DISABLED 
 	IFS1bits.U2RXIF = 0; //reset RX interrupt flag
    	IFS1bits.U2TXIF = 0; //reset TX interrupt flag
    	IEC1bits.U2RXIE = 0; //disable interrupts for RX
    	IEC1bits.U2TXIE = 0; //disable interrupts for TX
 	// define TX interrupt mode (UTXISEL bits) 
 	U2STAbits.UTXISEL= 0;
 	
 	EnableInterrupts();
 	txbuf.nchar = 0;
 	while(1){
 		putstrInt("Test String \n"); 
 	}
 	
 	
 	return 0;
 	
 
 }
