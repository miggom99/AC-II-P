#include<detpic32.h>

void delay(int s);

int main(void)
 {
 	TRISE = TRISE & 0xFFFE; //1110
 	TRISD = TRISD & 0x0100; //0001 0000 0000
 	LATE = (LATE & 0xFFFE);        //reset
 	PORTD = (PORTD & 0x0100);

 	
 	AD1CON1bits.ASAM = 1; // Start conversion
 	while(1){
 		LATE = (LATE & 0xFFFE);
	 	while(((PORTD & 0x0100) == 0x0100)); // Wait while conversion not done 
	 	LATE = (LATE & 0xFFFE) | 0x0001;
	 	delay(3);
	 }
 	
 	return 0;
 } 
 
 void delay(int s){
 	resetCoreTimer();
 	while(readCoreTimer() < 20000000*s);
 }
