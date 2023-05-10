#include <detpic32.h>

int main(void){

    T3CONbits.TCKPS = 7; // 1:256 prescaler (i.e. fout_presc = 78125 Hz)
    PR3 = 39062; // 78125 hz / ((x + 1)) = 2HZ || x = 39062
    TMR3 = 0; // Clear timer T2 count register
    T3CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)


    while(1){
        // Wait for timer T3 interrupt
        while(IFS0bits.T3IF == 0);
        IFS0bits.T3IF = 0; // Reset timer T3 interrupt flag

        putChar('.');
    }


}
