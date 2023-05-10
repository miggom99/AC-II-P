#include <detpic32.h>


void delay(unsigned int time);
int main(void){

    PORTDbits.RD8 = 0;
    LATEbits.LATE0 = 0;

    TRISDbits.TRISD8 = 1;
    TRISEbits.TRISE0 = 0;

    while(1){

        if (!PORTDbits.RD8){
            LATEbits.LATE0 = 1;
            delay(60000000);
        }

        LATEbits.LATE0 = 0;
    }

    return 0;

}

void delay(unsigned int time){
    resetCoreTimer();
    while(readCoreTimer() < time);
}
