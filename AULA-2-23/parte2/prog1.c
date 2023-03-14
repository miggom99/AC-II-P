#include <detpic32.h>

void delay(unsigned int ms)
{
    
    resetCoreTimer();
    while(readCoreTimer() < ms * 20000);

}

int main(){

    int cnt1,cnt5,cnt10;
    cnt1 = cnt5 = cnt10 = 0;
    while(1){
        delay(100); // 10 hz
        printInt(cnt10++, 10 | 5  << 16);


        if (cnt10 % 2 == 0){
            cnt5++;
        }
        if (cnt10 % 10 == 0){
            cnt1++;
        }

        printInt(cnt5, 10 | 6  << 16);
        putChar(' ');

        printInt(cnt1, 10 | 7  << 16);
        putChar(' ');
    }
    return 0;
}
