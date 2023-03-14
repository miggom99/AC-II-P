#include <detpic32.h>

int main(void){

    static const int disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x73, 0x39, 0x5C, 0x79, 0x71 };
    TRISB = (TRISB & 0x80FF)| 0x000F;
    TRISD = TRISD & 0xFF9F; // 1111 1111 1001 1111

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    unsigned int read;
    unsigned int pos;

    while(1){
        pos = PORTB & 0x000F;
        read = disp7Scodes[pos] <<8;

        LATB = (LATB & 0x80FF) | read;

    }

}
