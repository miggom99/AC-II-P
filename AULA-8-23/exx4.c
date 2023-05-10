#include<detpic32.h>

int main(void){

    // Config T3

    T3CONbits.TCKPS = 6; // 1:64 prescaler (i.e. fout_presc = 312500 Hz)
    PR3 = 12499; // 312500 hz / ((x + 1)) = 25HZ || x = 12499 
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

    //Config T1

    T1CONbits.TCKPS = 3; // 1:256 prescaler (i.e. fout_presc = 78125 Hz)
    PR1 = 15624; // 78125 hz / ((x + 1)) = 5HZ || x =  15624
    TMR1 = 0;

    T1CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)

    IPC1bits.T1IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1; // Enable timer T1 interrupts
    IFS0bits.T1IF = 0; // Reset timer T1 interrupt flag 


    EnableInterrupts();
    while(1);
    return 0;

}

void _int_(12) isr_T3(void) {
    
    putChar('3');
    
    IFS0bits.T3IF = 0; // Reset timer T3 interrupt flag
}



void _int_(4) isr_T1(void) {
    
    putChar('1');
    
    IFS0bits.T1IF = 0; // Reset timer T3 interrupt flag
}
