#include <detpic32.h>

void send2displays(unsigned int value);
int main(void){
    LATB = LATB & 0x80FF;
    LATD = LATD & 0xFF9F;

    TRISD = TRISD & 0xFF9F;
    TRISB = TRISB & 0x80FF;
    int counter = 0;

    while(1){
        int i = 0;

        do{
            send2displays(counter);
            resetCoreTimer();
            while(readCoreTimer()<200000 ); //valor do exx6

        }while(++i < 20);// valor do exx6

        counter++;
    }

    return 0;

}

void send2displays(unsigned int value){
    static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x73, 0x39, 0x5C, 0x79, 0x71 };
    static char displayFlag = 0; //flag
    
    int lh = disp7Scodes[value  >> 4] << 8;
    int ll = disp7Scodes[value & 0x0F] << 8;

    if(displayFlag == 0){

        LATDbits.LATD6 = 0; // Select low display
        LATDbits.LATD5 = 1;

        LATB = (LATB & 0x80FF) | ll;
    }else{

        LATDbits.LATD6 = 1; // Select hih display
        LATDbits.LATD5 = 0;

        LATB = (LATB & 0x80FF) | lh;
    }

    displayFlag = !displayFlag;

}
