#include <detpic32.h>

int main(void){
	
	// Configure UART2:
 	// 1 - Configure BaudRate Generator 
	U2MODE.BRGH = 0
	U2BRG = 10	//UxBRG = (20M / (16 * 115200)) – 1 
	
	//Configurar tipo de paridade e de stop bits
	U2MODE.PDSEL = 2;
	U2MODE.STSEL = 0;
	
	// 3 – Enable the trasmitter and receiver modules (see register U2STA)
 	
 	U2STAbits.UTXEN = 1; // 1 = UARTx transmitter is enabled.
 	U2STAbits.URXEN = 1; // 1 = UARTx receiver is enabled
 	
 	// 4 – Enable UART2 (see register U2MODE)
 	
 	U2MODEbits.ON = 1; // UART2 Enable bit
 	
 	// config RD11 as output 
 	TRISbits.TRISD11 = 0;
 	LATbits.LATD11 = 0; //reset RD11
 	
 	while(1){
 		while(U2STAbits.TRMT == 0);
 		LATbits.LATD11 = 1;
 		puts("12345");
 		LATbits.LATD11 = 0; //reset RD11
 	}
	return 0;
}
