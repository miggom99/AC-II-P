#include <detpic32.h>

void delay(unsigned int ms);

 int main(void)
 {
 	LATCbits.LATC14 = 0;    // The initial value should be set
                            	// before configuring the port as output
    	TRISCbits.TRISC14 = 0;  // RC14 configured as output
	while(1)
	{
		delay(10);	//freq 10Hz
		LATCbits.LATC14 = !LATCbits.LATC14;	
	}
 	return 0;
 } 
 
void delay(unsigned int ms)
{
	resetCoreTimer();
	while(readCoreTimer() < ms * 1000000);
} 
