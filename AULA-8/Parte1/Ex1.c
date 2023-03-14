#include <detpic32.h>

int main(void){
	// Configure Timer T3 (2 Hz with interrupts disabled)
	// 20000000÷(65536×2) = 153 para saber a min escala
	T2CONbits.TCKPS = 7; // 1:256 prescaler (i.e. fout_presc = 625 KHz)
	// Para saber que valor introduzir em PR2 
	//1º temos de dividir o clck pela escala anterior
	//20 MHz / 256 = 78125
	//2º dividir o valor obtido anteriormente pelo valor que pretendemos na saida do clk
	//78125/2= 39062,5 -> este é o PR3
 	PR3 = 39062; // Fout = 20MHz / (256 * (39062 + 1)) = 2 Hz
 	TMR3 = 0; // Reset timer T3 count register
 	T3CONbits.TON = 1; // Enable timer T3 (must be the last command of the
 	// timer configuration sequence)
 	
 	IFS0bits.T3IF = 0;      // Reset timer T3 interrupt flag, should be set 		before enabling interrupts
    	IPC3bits.T3IP = 2;      // Interrupt priority 2
    	IEC0bits.T3IE = 1;      // Enable timer T3 interrupts
 	
 	while(1){
 		// Wait until T3IF = 1
		while (IFS0bits.T3IF != 1);
		// Reset T3IF
		IFS0bits.T3IF = 0;
		putChar('.');
	}
 	
}
