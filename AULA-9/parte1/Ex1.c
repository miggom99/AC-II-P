#include <detpic32.h>

void confT();
void delay(unsigned int ms);
void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);

volatile int voltage = 0; // Global variable 

int main(void){
	 
    	confT();
    	EnableInterrupts();
    	while(1);
    	return 0;

}

void confT(){

	TRISBbits.TRISB4 = 1; // RBx digital output disconnected
	AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
	AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
	// mode an internal counter ends sampling and
	// starts conversion
	AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
	// interrupt is generated. At the same time,
	// hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = 4-1; // Interrupt is generated after XX samples
	// (replace XX by the desired number of
	// consecutive samples)
	AD1CHSbits.CH0SA = 4; // replace x by the desired input
	// analog channel (0 to 15)
	AD1CON1bits.ON = 1; // Enable A/D converter
	// This must the last command of the A/D
	// configuration sequence 
	 
	//reset
	 
	TRISB = (TRISB & 0x80FF);	// Defenir [RB8 - RB14] como saidas
    	TRISD = (TRISD & 0xFF9F);		// RD5 E RD6 como saídas
    	
    	LATB = (LATB & 0x80FF);
    	LATD = (LATD & 0xFF9F);	
	
	// Configure Timer T1 (5 Hz with interrupts disabled)
	// 20000000÷(65536×5) = 61 para saber a min escala
	T1CONbits.TCKPS = 6; // 1:64 prescaler (i.e. fout_presc = 625 KHz)
	
	// Configure Timer T3 (100 Hz with interrupts disabled)
	// 20000000÷(65536×100) = 3 para saber a min escala
	T3CONbits.TCKPS = 2; // 1:4 prescaler (i.e. fout_presc = 625 KHz)
	
	
	
	// Para saber que valor introduzir em PR2 
	//1º temos de dividir o clck pela escala anterior
	//20 MHz / 64 = 312500
	//2º dividir o valor obtido anteriormente pelo valor que pretendemos na saida do clk
	//312500/5= 62500 -> este é o PR3
 	PR1 = 62499; // Fout = 20MHz / (256 * (39062 + 1)) = 2 Hz
 	
 	// Para saber que valor introduzir em PR2 
	//1º temos de dividir o clck pela escala anterior
	//20 MHz / 4 = 5000000
	//2º dividir o valor obtido anteriormente pelo valor que pretendemos na saida do clk
	//5000000/100= 50000 -> este é o PR3
 	PR3 = 49999; // Fout = 20MHz / (256 * (39062 + 1)) = 25 Hz
 	
 	TMR1 = 0; // Reset timer T3 count register
 	T1CONbits.TON = 1; // Enable timer T3 (must be the last command of the
 	// timer configuration sequence)
 	
 	TMR3 = 0; // Reset timer T3 count register
 	T3CONbits.TON = 1; // Enable timer T3 (must be the last command of the
 	// timer configuration sequence)
 	
 	 	
    	IPC6bits.AD1IP = 3;     // configure priority of A/D interrupts
    	IEC1bits.AD1IE = 1;     // Enable A/D interrupts
    	IFS1bits.AD1IF = 0;     // Reset timer AD interrupt flag 
    	
    	IFS0bits.T1IF = 0;      // Reset timer T1 interrupt flag, should be set 		before enabling interrupts
    	IPC1bits.T1IP = 1;      // Interrupt priority 1
    	IEC0bits.T1IE = 1;      // Enable timer T1 interrupts
    	
    	IFS0bits.T3IF = 0;      // Reset timer T3 interrupt flag, should be set 		before enabling interrupts
    	IPC3bits.T3IP = 2;      // Interrupt priority 2
    	IEC0bits.T3IE = 1;      // Enable timer T3 interrupts

}

void _int_(4) isr_T1(void)
 {
 	AD1CON1bits.ASAM = 1;	// Start A/D conversion
 	IFS1bits.AD1IF = 0;
 } 

void _int_(12) isr_T3(void){ 
	
	send2displays(toBcd(voltage));
	IFS0bits.T3IF = 0;            // Reset AD1IF fl
}

void _int_(19) isr_adc(void)
 {
 	int i = 0;
 	int *p = (int *)(&ADC1BUF0);
 	
 	double media = 0;
 	for( i = 0; i < 4; i++ ) {
 		media += (double)p[i*4];
 	}
 	media = media/4;
 	voltage = (media * 33 +511) / 1023;
 	IFS1bits.AD1IF = 0;
 	IFS1bits.AD1IF = 0; // Reset AD1IF flag
 } 

void send2displays(unsigned char value){

	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; 	// Array com os códigos para o display de 7 segmentos
	static char displayFlag = 0;
	
	LATD = ( LATD & 0xFF9F) | 0x0040;	//Selecionar o display mais
						//significativo
	LATB = LATB & 0x80FF;			// Máscara para os portos de
    						//saida[RB8 - RB14]
    	unsigned char dl = value & 0x0F;	//colocar a 0 os 4 bits + sgntvs.
    	unsigned char dh = value >> 4;		// shiftR para mover os bits mais
						// significativos para os bits -
						// significativos de forma a ficar
						// ideal para comparar c o array
	if(displayFlag==0){
		LATB = display7Scodes[dh] << 8;	//Imprimir
	}else{
		LATD = ( LATD & 0xFF9F) | 0x0020;	//Selecionar o display menos
							//significativo
		LATB = LATB & 0x80FF;			// Máscara para os portos de
    							//saida[RB8 - RB14]
    	
    		LATB = display7Scodes[dl] << 8;	//Imprimir
	}
    	displayFlag = !displayFlag;					
	
	
}

void delay(unsigned int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}

unsigned char toBcd(unsigned char value)
 {
	return ((value / 10) << 4) + (value % 10);
 } 
