#include <detpic32.h>

void putc(char byte);
void delay(unsigned int ns);
void putstr(char *str);

int main(void){

	// Configure UART2:
 	// 1 - Configure BaudRate Generator
 	U2MODEbits.BRGH = 0; 	//  fator de divisão é 16
 	U2BRG =10;		// UxBRG = (fPBCLK / (16 * baudrate)) – 1 
 				// UxBRG = (20M / (16 * 115200)) - 1 = 10
	
	// 2 – Configure number of data bits, parity and number of stop bits
 	// (see U2MODE register) 
 	
 	U2MODEbits.PDSEL = 0; 	// 8-bit data, no parity
 	U2MODEbits.STSEL = 0;	// 0 = 1 Stop bit
 	
 	// 3 – Enable the trasmitter and receiver modules (see register U2STA)
 	
 	U2STAbits.UTXEN = 1; // 1 = UARTx transmitter is enabled.
 	U2STAbits.URXEN = 1; // 1 = UARTx receiver is enabled
 	
 	// 4 – Enable UART2 (see register U2MODE)
 	
 	U2MODEbits.ON = 1; // UART2 Enable bit 
 	
 	while(1)
 	{
 		putstr("String de teste\n");
 		// wait 1 s
 		delay(1000);
 	}
 	return 0; 

}

void putstr(char *str)
 {
 	while(*str != '\0'){
 		putc(*str);
 		str++;
 	}
 	
 } 
 
 void putc(char byte)
 {
 	// wait while UART2 UTXBF == 1
 	while (U2STAbits.UTXBF == 1);
 	// Copy "byte" to the U2TXREG register
 	U2TXREG = byte;
 } 
 
 void delay(unsigned int ns){
 	resetCoreTimer();
 	while(readCoreTimer() < 20000*ns);
 }
