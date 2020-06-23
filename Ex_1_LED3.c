#include <iom128v.h>
#define LED PORTB

unsigned char i = 0;

//to get 1 us delay in 8MHz crystal 
void delay_us(unsigned int microsecond){      
    do{ 
        microsecond--; 
	}while (microsecond>1); 
}

// to get 1 ms delay
void delay_ms(unsigned int millisecond){       
    while (millisecond--){
        delay_us(999);
	}  
}

void port_init(void){
	DDRB=0xff; //Set  as output
	PORTB = 0xFF;
}

void main(void){
    port_init();
	delay_ms(100);
    while(1){
    	for(i=0;i<3;i++){
			LED=0xf0;
			delay_ms(500);
			LED=0xff;
			delay_ms(500);    		
		}//D0~D3 flash 3 times 
		for(i=0;i<3;i++){
			LED=0x0f;
			delay_ms(500);
			LED=0xff;
			delay_ms(500);    		
		}//D4~D7 flash 3 times 
    	for(i=0;i<3;i++){
			LED=0x3c;
			delay_ms(500);
			LED=0xff;
			delay_ms(500);    		
		}//D2~D5 flash 3 times 
	}	
}
