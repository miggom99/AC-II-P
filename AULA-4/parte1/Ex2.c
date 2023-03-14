#include <detpic32.h>

void delay(unsigned int ms);

int main(void)
{
	TRISE = 0xFFF0; // TRISE0, TRISE1, TRISE2, TRISE3 = 0 (SAIDAS)
	int count = 0;  // contador para ser incrementado no ciclo

	while(1)
	{
		delay(4);	//freq 4Hz
		LATE = (LATE & 0xFFF0) | count;
		count++;
		if(count > 15){
			count = 0;
		}
	}
	return 0;
} 
 
void delay(unsigned int ms)
{
	resetCoreTimer();
	while(readCoreTimer() < ms * 1000000);
} 
