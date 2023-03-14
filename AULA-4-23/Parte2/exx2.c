#include <detpic32.h>



int main(){
    
    unsigned int segment;
    int i;
    TRISB = TRISB & 0x80FF; // 1000 0000 1111 1111
    TRISD = TRISD & 0xFF9F; // 1001 1111
    LATD = (LATD & 0xFF9F) | 0x0020; //boa prática inicializar o porto 0010 0000
    LATB = LATB & 0x80FF;
    while(1){
       
       segment = 1;
       segment = segment <<8;


       for (i = 0; i < 7; i++)
       {
            LATB = (LATB & 0x80FF) | segment;
            resetCoreTimer();
            while (readCoreTimer() < 10000000);

            segment = segment << 1;
       }
       
        

    }
}
