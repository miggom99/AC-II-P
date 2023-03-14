#include <detpic32.h>

int main(void)
{
	int display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x73, 0x39, 0x5C, 0x79, 0x71 }; 	// Array com os códigos para o display de 7 segmentos 
	 
	LATD = ( LATD & 0xFF9F) | 0x0020;	//Selecionar o display menos
						//significativo
    	LATB = LATB & 0x80FF;			// Máscara para os portos de
    						//saida[RB8 - RB14]
	
	TRISB = (TRISB & 0x80FF) | 0x000F;		// Defenir [RB8 - RB14] como saidas e [RB0 - RB3] como entradas
    	TRISD = (TRISD & 0xFF9F);		// RD5 E RD6 como saídas

	while(1){
		int n = (PORTB & 0x000F);
		LATB = display7Scodes[n] << 8;	
	}
	return 0;
}
	
