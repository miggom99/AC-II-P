#include<detpic32.h>

void confT();

int main(void)
 {
 	TRISE = TRISE & 0xFFFE; //1110
 	TRISD = TRISD | 0x0100; //0001 0000 0000
 	confT();
	INTCONbits.INT1EP = 0;
 	
 	EnableInterrupts();
 	while(1);
 	return 0; 
 	
 } 

void _int_(8) isr_T2(void){ 
	
	LATE = (LATE & 0xFFFE) | 0x0001;
	static int count = 0;
	count++;
	if((count % 6) == 0){
		IEC0bits.T2IE = 0;      // Desable timer T2 interrupts
		LATE = (LATE & 0xFFFE);
	}
	IFS0bits.T2IF = 0;
}
//LATE = (LATE & 0xFFFE) | 0x0001;

void _int_ (7) isr_INT1 (void){
    IPC2bits.T2IP = 1;      // Interrupt priority 1
    IEC0bits.T2IE = 1;      // Enable timer T2 interrupts
    IFS0bits.T2IF = 0;      // Reset timer T2 interrupt flag
    

    //waits for another push on int1
    IFS0bits.INT1IF = 0;
}


 
 void confT(){
 	// Configure Timer T1 (2 Hz with interrupts disabled)
	// 20000000÷(65536×2) = 153 para saber a min escala
	T2CONbits.TCKPS = 7; // 1:256 prescaler (i.e. fout_presc = 625 KHz)
	
	// Para saber que valor introduzir em PR2 
	//1º temos de dividir o clck pela escala anterior
	//20 MHz / 256 = 78125
	//2º dividir o valor obtido anteriormente pelo valor que pretendemos na saida do clk
	//78125/2= 39062 -> este é o PR3
 	PR2 = 39062; // Fout = 20MHz / (256 * (39062 + 1)) = 2 Hz

 	
 	TMR2 = 0; // Reset timer T3 count register
 	T2CONbits.TON = 1; // Enable timer T3 (must be the last command of the
 	// timer configuration sequence)
 	
 	IPC1bits.INT1IP = 2;      // Interrupt priority INT1
    	IEC0bits.INT1IE = 1;      // Enable timer INT1 interrupts
    	IFS0bits.INT1IF = 0;      // Reset timer INT1 interrupt flag
 	

 	

    	
 }
