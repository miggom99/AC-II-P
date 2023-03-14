#include <detpic32.h>

void delay(unsigned int ms);
void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);
int main(void){
	
	//reset
    	LATB = (LATB & 0x80FF);
    	LATD = (LATD & 0xFF9F);
    	LATE = LATE & 0XFF00;
	
	TRISB = (TRISB & 0x80FF);		// Defenir [RB8 - RB14] como saidas
    	TRISD = (TRISD & 0xFF9F);		// RD5 E RD6 como saídas
    	TRISE = (TRISE & 0XFF00);		// porto E saida
    	
    	static int counter = 0;
    	int i;
    	while(1){
    		i = 0;
    		do{
	    		send2displays(toBcd(counter));
	    		LATE = LATE & 0XFF00 | toBcd(counter);
	    		delay(20); //50hz
    		}while(++i < 10); 
    		counter = (counter +1) & 0x00FF;
    		if (counter >= 60){
    			counter = 0;
    		}
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

void delay(unsigned int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}

unsigned char toBcd(unsigned char value)
 {
	return ((value / 10) << 4) + (value % 10);
 } 
