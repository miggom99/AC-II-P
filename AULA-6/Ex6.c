#include <detpic32.h>

void delay(unsigned int ms);
void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);
int main(void){
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
    	LATB = (LATB & 0x80FF);
    	LATD = (LATD & 0xFF9F);
	 
	TRISB = (TRISB & 0x80FF) | 0xF;	// Defenir [RB8 - RB14] como saidas
    	TRISD = (TRISD & 0xFF9F);		// RD5 E RD6 como saídas
    	
    	int i = 0;
    	char v = 0;
	 
	 while(1){
	 	if(i==0){
		 	double media = 0;
		 	AD1CON1bits.ASAM = 1;
		 	while( IFS1bits.AD1IF == 0);
		 	int *p = (int *)(&ADC1BUF0);
		 	for( i = 0; i < 4; i++ ) {
		 		media += (double)p[i*4];
		 	}
		 	media = media/4;
		 	v = (media * 33 +511) / 1023;
		 	IFS1bits.AD1IF = 0;
		 }
		 send2displays(toBcd(v));
		 delay(10); //100hz
		 i = (i + 1) % 20; 
	 }
	 
	 return 0;




}


void send2displays(unsigned char value){
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x73, 0x39, 0x5C, 0x79, 0x71 }; 	// Array com os códigos para o display de 7 segmentos
	
}

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
