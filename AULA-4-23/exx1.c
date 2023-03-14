#include <detpic32.h>



int main(){
    
    TRISC = TRISC & 0xBFFF
    LATCbits.LATE14 = 0; //boa prática inicializar o porto
    while(1){

        resetCoreTimer();
        while(readCoreTimer() < 10000000);
        LATCbits.LATC14 = !LATCbits.LATC14;
        // aleternativa LATC = LATC ^ 0x4000 

    }
}