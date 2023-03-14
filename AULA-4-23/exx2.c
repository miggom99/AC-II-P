#include <detpic32.h>



int main(){
    
    TRISE = TRISE & 0x0087; // 1000 0111
    LATE = LATE & 0xFF87; //boa prática inicializar o porto
    int counter = 0;
    while(1){
        
        LATE = (LATE & 0xFF87) | (counter << 3); // O counter tem de ser feito
        //de forma atómica, de forma a que seja tudo atualizado como sempre
        
        resetCoreTimer();
        while(readCoreTimer() < 5000000);

        counter++;

        if (counter >9){
            counter = 0;
        }

    }
}
