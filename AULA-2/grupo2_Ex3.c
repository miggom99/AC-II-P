#include <stdio.h>

int main()
{
    int cnt1 = 0, cnt5 = 0, cnt10 = 0, k = 1;
    char letra = 'N';
    resetCoreTimer(); 
    while(1){
    	letra = putChar();
    	if(letra == 'A'){
    		k = 2;
    	}else{
    		k = 1;
    	}while(readCoreTimer() < 1000000 * k){
        	printInt(cnt1++, 10 | 4 << 16);
        	putChar('\r');
        }while(readCoreTimer() < 5000000 * k){
        	printInt(cnt5++, 10 | 4 << 16);
        	putChar('\r');
        }while(readCoreTomer() < 10000000 * k){
        	printInt(cnt10++, 10 | 4 << 16);
        	putChar('\r');
        }
    }
    return 0;
}
