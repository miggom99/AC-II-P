#include <detpic32.h>

int main(void)
{
	LATD = ( LATD & 0xFF9F) | 0x0020;
    	LATB = LATB & 0x80FF;
	
	TRISB = (TRISB & 0x80FF);
    	TRISD = (TRISD & 0xFF9F);

	while(1)
	{
		char c = getChar();
		switch(c){
		case 'a':
		case 'A':
			LATB = 0x0100;
			break;

		case 'b': 
		case 'B':
			LATB = 0x0200; //b -> RB9
                	break;
                
            	case 'c':
            	case 'C':
            		LATB = 0x0400; //c -> RB10
                	break;
                
            	case 'd': 
            	case 'D':
            		LATB = 0x0800; //d -> RB11
                	break;
                
            	case 'e':
            	case 'E': 
            		LATB = 0x1000; //e -> RB12
                	break;
                
            	case 'f': 
            	case 'F':
            		LATB = 0x2000;//f -> RB13
                	break;
                
            	case 'g': 
            	case 'G':
            		LATB = 0x4000;//g -> RB14
                	break;
                	
                default:
                	break;
		}
	}
	return 0;
} 
 

