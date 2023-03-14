int main(void)
 {
 	// Configure UART2: 115200, N, 8, 1
 	//1- Config gerador de braudate e taca de transmissão
 	U2BRG = 21;	//(20M / (8 * 115200)) -1) = 21
 	U2MODEbits.BRGH = 1; 
 	
 	//2- Configurar paridade e stopbits
 	U2MODEbits.PDSEL = 0;
 	U2MODEbits.STSEL = 1;
 	
 	//3 - Ativar 
 	U2STAbits.UTXEN = 1;
 	U2STAbits.URXEN = 1;
 	
 	//4- ATIVAR UART
 	U2MODEbits.ON = 1; // UART2 Enable bit
 	
 	
 	// Configure UART2 interrupts, with RX interrupts enabled
 	// and TX interrupts disabled:
 		// enable U2RXIE, disable U2TXIE (register IEC1)
 		IEC1bits.U2RXIE = 1;
 		IEC1bits.U2TXIE = 1;
 		// set UART2 priority level (register IPC8)
 		IPC8bits.U2IP = 1;
 		// clear Interrupt Flag bit U2RXIF (register IFS1)
 		IFS1bits.U2RXIF = 0;
 		// define RX interrupt mode (URXISEL bits)
 		U2STAbits.URXISEL=0;
 	// Enable global Interrupts
 	EnableInterrupts();

 	while(1);
 	return 0;
 } 
