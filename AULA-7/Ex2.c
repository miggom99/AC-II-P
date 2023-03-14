#include <detpic32.h>

void delay(int);
void send2displays(unsigned char);
unsigned char toBcd(unsigned char);

volatile unsigned char voltage = 0;

// Interrupt Handler
void _int_(27) isr_adc(void){ // Replace VECTOR by the A/D vector number - see "PIC32 family data sheet" (pages 74-76)
	int i;
	int *p = (int *)(&ADC1BUF0);
	int media = 0;
	
	for(i = 0; i <8; i++){
		media += (p[i*4]*33+511)/1023;
	}
	
	media = media/8;
	voltage = toBcd(media);
	IFS1bits.AD1IF = 0;                    // Reset AD1IF flag
}


int main(void)
 {
 	unsigned int cnt = 0; 
 	TRISB = (TRISB & 0x80FF) | 0xF;     // sets RB8-RB14 as output and RB0-RB as input
    	TRISD = TRISD & 0xFF9F;             // sets RD5-RD8 as output
    	LATD = (LATD & 0xFF9F) | 0x40;      // sets RD6 and RD5 to 0 then sets RD6 to 1
 	 // Configure all (digital I/O, analog input, A/D module)
 	 TRISBbits.TRISB4 = 1; // RBx digital output disconnected
	 AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
	 AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
	 // mode an internal counter ends sampling and
	 // starts conversion
	 AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
	 // interrupt is generated. At the same time,
	 // hardware clears the ASAM bit
	 AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
	 AD1CON2bits.SMPI = 8-1; // Interrupt is generated after XX samples
	 // (replace XX by the desired number of
	 // consecutive samples)
	 AD1CHSbits.CH0SA = 4; // replace x by the desired input
	 // analog channel (0 to 15)
	 AD1CON1bits.ON = 1; // Enable A/D converter
	 // This must the last command of the A/D
	 // configuration sequence 
 	
 	
 	// Configure interrupt system
 	IPC6bits.AD1IP = 2; // configure priority of A/D interrupts
 	IFS1bits.AD1IF = 0; // clear A/D interrupt flag
 	IEC1bits.AD1IE = 1; // enable A/D interrupts 
 	EnableInterrupts(); // Global Interrupt Enable
 	
 	
 	while(1){ // all activity is done by the ISR
 		if(cnt%20 == 0){ //5 per sec	
 			AD1CON1bits.ASAM = 1;
 		}
 		send2displays(voltage);
 		cnt++; 
 		delay(100);		
 	}
 	return 0;
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

void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000000 / ms);
}

unsigned char toBcd(unsigned char value)
 {
	return ((value / 10) << 4) + (value % 10);
 } 
