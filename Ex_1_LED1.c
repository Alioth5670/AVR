#include <iom128v.h>
#define LED PORTB

unsigned char i = 0;
unsigned char tab[16] = {0XFE,0XFC,0XF8,0XF0,0XE0,0XC0,0X80,0X00,0X01,0X03,0X07,0X0F,0X1F,0X3F,0X7F,0XFF};
//Turn on 8 LEDs in turn and the last one in tab[] is close all LEDs
 
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
	DDRB=0xff; //Set B port as output with pull-up
	PORTB = 0xFF;
	DDRE = 0x00; //Set E port as input with pull-up
	PORTE = 0xFF;
}

void main(void){
    port_init();
	delay_ms(100);
    while(1){
		for(i = 0;i < 16;i ++){
		    LED = tab[i];
			delay_ms(1000);
		}	
    }
}

