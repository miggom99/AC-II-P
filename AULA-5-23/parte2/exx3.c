#include <detpic32.h>

unsigned char toBcd(unsigned char value);
void send2displays(unsigned int value);

int main(void){
    LATB = LATB & 0x80FE;
    LATE = LATE & 0xFF00;
    LATD = LATD & 0xFF9F;

    TRISB = (TRISB & 0x80FF) | 0x0001;
    TRISE = TRISE & 0xFF00;
    TRISD = TRISD & 0xFF9F;


    int counter = 0;
    int update_count = 0;

    while(1){
        int i = 0;

        if (PORTBbits.RB0 == 1){
            update_count = 20;
        }else{
            update_count = 50;
        }

        do{
            send2displays(toBcd(counter));
            resetCoreTimer();
            while(readCoreTimer()<200000 ); 

        }while(++i < update_count);
        LATE = (LATE & 0xFF00) | toBcd(counter);
        
        if (PORTBbits.RB0 == 1){
            counter++;
        }else{
            counter--;
        }
        
        if (counter >= 60){
            counter = 0;
        }else if( counter < 0){
            counter = 60;
        }
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
