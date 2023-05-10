#include<detpic32.h>


void config();
unsigned char toBcd(unsigned char value);
void send2displays(unsigned int value);

volatile int V = 0;

int main(void) {

    config();
    IFS0bits.T3IF = 0; // Reset timer T3 interrupt flag 
    IFS0bits.T1IF = 0; // Reset timer T3 interrupt flag 
    IFS1bits.AD1IF= 0;// Reset AD1IF
    EnableInterrupts();
    while(1);
    return 0;


}

void config() {

    //config T1

    T1CONbits.TCKPS = 2; // 1:64 prescaler (i.e Fout_presc = 312.5 KHz)
    PR1 = 62499; // Fout = 20MHz / (64 * (x + 1)) = 5 Hz
    // x = 62499
    TMR1 = 0; // Reset timer T2 count register
    T1CONbits.TON = 1; // Enable timer T1 (must be the last command of the
    // timer configuration sequence)

    IPC1bits.T1IP = 3; // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1; // Enable timer T1 interrupts


    //config T3

    T3CONbits.TCKPS = 2; // 1:4 prescaler (i.e Fout_presc = 5 MHz)
    PR3 = 49999; // Fout = 20MHz / (4 * (x + 1)) = 100 Hz
    // x = 49999
    TMR3 = 0; // Reset timer T2 count register
    T3CONbits.TON = 1; // Enable timer T1 (must be the last command of the
    // timer configuration sequence)

    IPC3bits.T3IP = 3; // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1; // Enable timer T3 interrupts
    IFS0bits.T3IF = 0; // Reset timer T3 interrupt flag 


    // Configure all (digital I/O, analog input, A/D module)
    TRISBbits.TRISB4 = 1; // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 8-1; // Interrupt is generated after XX samples
    // (replace XX by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
    // This must the last command of the A/D
    // configuration sequence 

    //config Adc interrupt

    IPC6bits.AD1IP = 2; // configure priority of A/D interrupts
    IFS1bits.AD1IF = 0; // clear A/D interrupt flag 
    IEC1bits.AD1IE = 1; // enable A/D interrupts 

    //config A/D
    LATB = LATB & 0x80FE;
    LATE = LATE & 0xFF00;
    LATD = LATD & 0xFF9F;

    TRISB = (TRISB & 0x80FF) | 0x0001;
    TRISE = TRISE & 0xFF00;
    TRISD = TRISD & 0xFF9F;



}


unsigned char toBcd(unsigned char value)
 {
    return ((value / 10) << 4) + (value % 10);
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

void _int_(12) isr_T3(void) {

    send2displays(toBcd(V));
    IFS0bits.T3IF = 0; // Reset timer T3 interrupt flag
}

void _int_(4) isr_T1(void) {

    putChar('.');
    AD1CON1bits.ASAM = 1; // Start A/D conversion
    IFS0bits.T1IF = 0; // Reset timer T1 interrupt flag
}

void _int_(27) isr_adc(void) // Replace VECTOR by the A/D vector
 // number - see "PIC32 family data
 // sheet" (pages 74-76)
{
 // Read conversion result (ADC1BUF0) and print it


    int media = 0;
    int i= 0;


    int *p = (int *)(&ADC1BUF0);
    // Convert analog input (4 samples)
    // Read samples and calculate the average
    // Calculate voltage amplitude
    media = 0;
    for(i = 0; i < 8; i++ ) {
        media += p[i*4];
    }
    media = media/4;
    V=(media*33+511)/1023;

    IFS1bits.AD1IF= 0;// Reset AD1IF
} 

