#include <detpic32.h>

void delay(unsigned int ms);
int main(void)
{
	LATD = ( LATD & 0xFF9F) | 0x0020;	//Selecionar o display menos
						//significativo
    	LATB = LATB & 0x80FF;			// Máscara para os portos de
    						//saida[RB8 - RB14]
	
	TRISB = (TRISB & 0x80FF);		// Defenir [RB8 - RB14] como saidas
    	TRISD = (TRISD & 0xFF9F);		// RD5 E RD6 como saídas

	while(1){
		int segment = 1;
		int i;
		for (i = 0; i<7; i++){
			LATB = segment << 8;	
			delay(10);
			segment = segment << 1;
		}
		
		LATD = (LATD ^ 0x0060);
	}
	return 0;
}
	
void delay(unsigned int ms)
{
	resetCoreTimer();
	while(readCoreTimer() < ms * 1000000);
} 
