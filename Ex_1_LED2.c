#include <iom128v.h>
#define LED PORTB

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
	DDRE = 0x00; //Set E port as input with pull-up
	PORTE = 0xFF;
}

void main(void){
    port_init();
	delay_ms(100);
    while(1)
    {

	if(PINE!=0XFF){
		delay_ms(100);
		if(PINE!=0XFF){
			LED=PINE;
			delay_ms(1000);
			LED=0xff;
			}
		}
	}	
}
