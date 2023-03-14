#include <detpic32.h>



int main(){
    
    TRISB = TRISB & 0x80FF; // 1000 0000 1111 1111
    TRISD = TRISD & 0xFF9F; // 1001 1111
    LATD = (LATD & 0xFF9F) | 0x0040; //boa prática inicializar o porto 0100
    LATB = LATB & 0x80FF;
    char c;
    while(1){
        c = getChar();
        switch (c)
        {
        case 'a':
            LATB = (LATB & 0x80FF) | 0x0100;
            break;
        case 'b':
            LATB = (LATB & 0x80FF) | 0x0200;
            break;
        case 'c':
            LATB = (LATB & 0x80FF) | 0x0400;
            break;
        case 'd':
            LATB = (LATB & 0x80FF) | 0x0800;
            break;

        case 'e':
            LATB = (LATB & 0x80FF) | 0x1000;
            break;

        case 'f':
            LATB = (LATB & 0x80FF) | 0x2000;
            break;

        case 'g':
            LATB = (LATB & 0x80FF) | 0x4000;
            break;
        
        default:
            LATB = (LATB & 0x80FF) | 0x7F00;
            break;
        }
        

    }
}
