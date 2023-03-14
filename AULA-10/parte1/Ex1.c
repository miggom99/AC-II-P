#include <detpic32.h>

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

}
