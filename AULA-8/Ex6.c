#include<detpic32.h>

void confT();

// Interrupt Handler

void _int_(12) isr_T3(void){ 
	
	LATE = LATE ^ 0x0008;
	IFS0bits.T3IF = 0;            // Reset AD1IF fl
}

void _int_(4) isr_T1(void){ 

 	LATE = LATE ^ 0x0002;
	IFS0bits.T1IF = 0;            // Reset AD1IF flag	
}



int main(void)
 {
 	confT();
 	TRISE = TRISE & 0xFFF5; //0101
 	LATE = (LATE & 0xFFF5) | 0x000A;        //reset
 	
 	EnableInterrupts();
 	while(1);
 	return 0;
 } 
 
 void confT(){
 
 	// Configure Timer T1 (5 Hz with interrupts disabled)
	// 20000000÷(65536×5) = 61 para saber a min escala
	T1CONbits.TCKPS = 6; // 1:64 prescaler (i.e. fout_presc = 625 KHz)
	
	// 20000000÷(65536×25) = 12 para saber a min escala
	T3CONbits.TCKPS = 4; // 1:16 prescaler (i.e. fout_presc = 625 KHz)
	
	
	
	// Para saber que valor introduzir em PR2 
	//1º temos de dividir o clck pela escala anterior
	//20 MHz / 64 = 312500
	//2º dividir o valor obtido anteriormente pelo valor que pretendemos na saida do clk
	//312500/5= 62500 -> este é o PR3
 	PR1 = 62500; // Fout = 20MHz / (256 * (39062 + 1)) = 2 Hz
 	
 	// Para saber que valor introduzir em PR2 
	//1º temos de dividir o clck pela escala anterior
	//20 MHz / 16 = 1250000
	//2º dividir o valor obtido anteriormente pelo valor que pretendemos na saida do clk
	//1250000/25= 50000 -> este é o PR3
 	PR3 = 50000; // Fout = 20MHz / (256 * (39062 + 1)) = 25 Hz
 	
 	TMR1 = 0; // Reset timer T3 count register
 	T1CONbits.TON = 1; // Enable timer T3 (must be the last command of the
 	// timer configuration sequence)
 	
 	TMR3 = 0; // Reset timer T3 count register
 	T3CONbits.TON = 1; // Enable timer T3 (must be the last command of the
 	// timer configuration sequence)
 	
 	 	
    	
    	IFS0bits.T1IF = 0;      // Reset timer T1 interrupt flag, should be set 		before enabling interrupts
    	IPC1bits.T1IP = 1;      // Interrupt priority 2
    	IEC0bits.T1IE = 1;      // Enable timer T1 interrupts
    	
    	IFS0bits.T3IF = 0;      // Reset timer T3 interrupt flag, should be set 		before enabling interrupts
    	IPC3bits.T3IP = 1;      // Interrupt priority 2
    	IEC0bits.T3IE = 1;      // Enable timer T3 interrupts
 }
