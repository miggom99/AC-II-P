#include <detpic32.h>

int main(void) {

    //config T3

    T3CONbits.TCKPS = 2; // 1:4 prescaler (i.e Fout_presc = 5 MHz)
    PR3 = 49999; // Fout = 20MHz / (4 * (x + 1)) = 100 Hz
    // x = 49999
    TMR3 = 0; // Reset timer T2 count register
    T3CONbits.TON = 1; // Enable timer T1 (must be the last command of the
    // timer configuration sequence)


    //config duty cycle OC1

    OC1CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL =1;// Use timer T3 as the time base for PWM generation
    OC1RS = 12500; // OC1RS = ((PR3 +1)*duty-cycle)/100
    // = ((49999 +1) *  25) /100 = 12500
    OC1CONbits.ON = 1; // Enable OC1 module 




    while(1);
    return 0;
}
