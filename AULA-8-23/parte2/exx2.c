#include<detpic32.h>

void _int_(8) isr_T2(void){ 

    LATEbits.LATE0 = 1;
    static int count = 0;
    count++;
    if(count >= 6){
        IEC0bits.T2IE = 0;  
        LATEbits.LATE0 = 0;
    }

    IFS0bits.T2IF = 0; // Reset timer T3 interrupt flag 
}

void _int_(7) isr_INT1(void){
    IPC2bits.T2IP = 2; // Interrupt priority (must be in range [1..6])
    IFS0bits.T2IF = 0; // Reset timer T3 interrupt flag
    IEC0bits.T2IE = 1; // Enable timer T3 interrupts

    IFS0bits.INT1IF = 0;

}


int main(void){

    // Config T3

    T2CONbits.TCKPS = 7; // 1:256 prescaler (i.e. fout_presc = 78125 Hz)
    PR2 = 39062; // 78125 Hz / ((x + 1)) = 1HZ || x = 78124 
    // O valor de x não é possivel porque o PR tem 16 bits ou seja o valor
    // máximo é de 2^16 - 1 = 65535
    // Ou seja vamos utilizar o valor do exx anterior que era 2 hz
    // e chmar a system call a cada duas interrupts
    TMR2 = 0; // Clear timer T2 count register

    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)


    // Config INT1

    IPC1bits.INT1IP = 2;
    IEC0bits.INT1IE = 1; // 
    IFS0bits.INT1IF = 0; // 
    INTCONbits.INT1EP = 0; //

    // Config 

    PORTDbits.RD8 = 0;
    LATEbits.LATE0 = 0;

    TRISDbits.TRISD8 = 1;
    TRISEbits.TRISE0 = 0;


    EnableInterrupts();
    while(1);
    return 0;

}



