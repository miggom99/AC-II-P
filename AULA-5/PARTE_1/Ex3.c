#include <detpic32.h>

void send2displays(unsigned char value);
int main(void){
	
	//reset
    	LATB = (LATB & 0x80FF);
    	LATD = (LATD & 0xFF9F);
	
	TRISB = (TRISB & 0x80FF);		// Defenir [RB8 - RB14] como saidas
    	TRISD = (TRISD & 0xFF9F);		// RD5 E RD6 como saídas
    	
    	while(1){
    		send2displays(0x75);
    	}

}

void send2displays(unsigned char value){

	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x73, 0x39, 0x5C, 0x79, 0x71 }; 	// Array com os códigos para o display de 7 segmentos
	static char displayFlag = 0;
	
	LATD = ( LATD & 0xFF9F) | 0x0040;	//Selecionar o display mais
						//significativo
	LATB = LATB & 0x80FF;			// Máscara para os portos de
    						//saida[RB8 - RB14]
    	unsigned char dl = value & 0x0F;	//colocar a 0 os 4 bits + sgntvs.
    	unsigned char dh = value >> 4;		// shiftR para mover os bits mais
						// significativos para os bits menos
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
