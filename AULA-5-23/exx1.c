#include <detpic32.h>



int main(void){
    
}


void send2displays(unsigned char value){
    static const int disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x73, 0x39, 0x5C, 0x79, 0x71 };
    LATDbits.LATD6 = 1; // Select hih display
    LATDbits.LATD5 = 0;

    LATB = (LATB & 0x80FF) | value  >> 4;

    LATDbits.LATD6 = 1; // Select low display
    LATDbits.LATD5 = 0;

    LATB = (LATB & 0x80FF) | (value & 0x0F);

}