#include <detpic32.h>

unsigned char toBcd(unsigned char value);
void send2displays(unsigned int value);
void delay(unsigned int ns);

int main(void)
 {
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
    AD1CON2bits.SMPI = 4-1; // Interrupt is generated after XX samples
    // (replace XX by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
    // This must the last command of the A/D
    // configuration sequence 

    //config A/D
    LATB = LATB & 0x80FE;
    LATE = LATE & 0xFF00;
    LATD = LATD & 0xFF9F;

    TRISB = (TRISB & 0x80FF) | 0x0001;
    TRISE = TRISE & 0xFF00;
    TRISD = TRISD & 0xFF9F;
    
    int media = 0,V= 0;
    int i = 0;
    

    while(1)
    {   
        if(i == 0) // 0, 200ms, 400ms, 600ms, ...
        {   
            AD1CON1bits.ASAM = 1; // tem de ficar dentro do ciclo porque é metido a 0 por default

            while( IFS1bits.AD1IF == 0 ) ;// Wait while conversion not done

            int *p = (int *)(&ADC1BUF0);
            // Convert analog input (4 samples)
            // Read samples and calculate the average
            // Calculate voltage amplitude
            media = 0;
            for(i = 0; i < 16; i++ ) {
                media += p[i*4];
            }
            media = media/4;
            V=(media*33+511)/1023;
            IFS1bits.AD1IF= 0;// Reset AD1IF
        }
    // Convert voltage amplitude to decimal and
    // Send voltage value to displays
    send2displays(toBcd(V));
    // Wait 10 ms (using the core timer)
    delay(200000);
    i = (i + 1) % 20;
    }
    return 0;
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

void delay(unsigned int ns){
    
    resetCoreTimer();
    while(readCoreTimer() < ns ); 

}
