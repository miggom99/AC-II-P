#include <detpic32.h>

//volatile int var =0;
int main(void){

    T3CONbits.TCKPS = 7; // 1:256 prescaler (i.e. fout_presc = 78125 Hz)
    PR3 = 39062; // 78125 hz / ((x + 1)) = 1HZ || x = 78124 
    // O valor de x não é possivel porque o PR tem 16 bits ou seja o valor
    // máximo é de 2^16 - 1 = 65535
    // Ou seja vamos utilizar o valor do exx anterior que era 2 hz
    // e chmar a system call a cada duas interrupts
    TMR3 = 0; // Clear timer T2 count register
    T3CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)

    IPC3bits.T3IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1; // Enable timer T3 interrupts
    IFS0bits.T3IF = 0; // Reset timer T3 interrupt flag 

    EnableInterrupts();
    while(1);
    return 0;


}

void _int_(12) isr_T3(void) {
    static int var = 0;
    var++;
    if(var >= 2) {
        var =0;
        putChar('.');
    }
    
    IFS0bits.T3IF = 0; // Reset timer T3 interrupt flag
}
