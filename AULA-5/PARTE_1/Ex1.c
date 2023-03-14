void send2displays(unsigned char value){

	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x73, 0x39, 0x5C, 0x79, 0x71 }; 	// Array com os códigos para o display de 7 segmentos 
	
	LATD = ( LATD & 0xFF9F) | 0x0040;	//Selecionar o display mais
						//significativo
	LATB = LATB & 0x80FF;			// Máscara para os portos de
    						//saida[RB8 - RB14]
    						
	unsigned char dh = value >> 4;		// shiftR para mover os bits mais
						// significativos para os bits menos
						// significativos de forma a ficar
						// ideal para comparar c o array
	
	LATB = display7Scodes[dh] << 8;	//Imprimir
	
	
	LATD = ( LATD & 0xFF9F) | 0x0020;	//Selecionar o display menos
						//significativo
	LATB = LATB & 0x80FF;			// Máscara para os portos de
    						//saida[RB8 - RB14]
    						
    	unsigned char dl = value & 0x0F;	//colocar a 0 os 1ºs 4 bits.
    	LATB = display7Scodes[dl] << 8;	//Imprimir
    	
}
