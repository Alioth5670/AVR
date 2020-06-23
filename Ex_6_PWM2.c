#include <iom128v.h>
#include <macros.h>

unsigned char i=0;

//to get 1us delay
void delay_us(unsigned int microsecond){      
    do{ 
        microsecond--; 
	}         
    while (microsecond>1); 
}

//to get 1ms delay 
void delay_ms(unsigned int millisecond){      
    while (millisecond--){
        delay_us(999);
	}  
}

void init_port(void){
  PORTB=0x00;
  DDRB=0xFF;//PB as output
}

void init_timer1(void){
    TCCR1A=0XFD;// set on compare match clear on bottom
    TCCR1B|=(1<<WGM12);//8-bie fast pwm
    TCCR1B|=(0<<CS12)|(1<<CS11)|(0<<CS10);//8 prescale
    OCR1A=i;
    OCR1B=i+80;
    OCR1C=i+160;
}

void main(void){
    init_port();
	init_timer1();
	while(1){
		delay_ms(100);
		i++; 
		OCR1A=i;
  		OCR1B=i+80;
 		OCR1C=i+160;
	}
} 

