#include <detpic32.h>

void confT();
int main(void){

	EnableInterrupts();

    	while (1);

    	return 0;
}

void _int_(12) isr_T3(void){
    IFS0bits.T3IF = 0;
}

void confT(){

	//Configure T3

	// Configure Timer T3 (100 Hz with interrupts disabled)
	// 20000000÷(65536×100) = 3 para saber a min escala
	T3CONbits.TCKPS = 2; // 1:4 prescaler (i.e. fout_presc = 625 KHz)
	
	
 	
 	// Para saber que valor introduzir em PR3 
	//1º temos de dividir o clck pela escala anterior
	//20 MHz / 4 = 5000000
	//2º dividir o valor obtido anteriormente pelo valor que pretendemos na saida do clk
	//5000000/100= 50000 -> este é o PR3
 	PR3 = 49999; // Fout = 20MHz / (256 * (39062 + 1)) = 25 Hz
 	
 	
 	TMR3 = 0; // Reset timer T3 count register
 	T3CONbits.TON = 1; // Enable timer T3 (must be the last command of the
 	// timer configuration sequence)
 	

    	IFS0bits.T3IF = 0;      // Reset timer T3 interrupt flag, should be set 		before enabling interrupts
    	IPC3bits.T3IP = 2;      // Interrupt priority 2
    	IEC0bits.T3IE = 1;      // Enable timer T3 interrupts
    	
    	//Configure duty-cicle
    	// OC1RS = ((PR3 +1) * 25)/100
    	
    	OC1CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
 	OC1CONbits.OCTSEL =0;// Use timer T2 as the time base for PWM generation
 	OC1RS = 12500; 		// Ton constant
 	OC1CONbits.ON = 1; // Enable OC1 module
    	
}


