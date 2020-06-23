#include <iom128v.h>
#include <macros.h>

#define L1 262
#define L2 294
#define L3 330
#define L4 349
#define L5 392
#define L6 440
#define L7 494
#define M1 523
#define M2 587
#define M3 659
#define M4 698
#define M5 784
#define M6 880
#define M7 988
#define H1 1047
#define H2 1175
#define H3 1319
#define H4 1397
#define H5 1568
#define H6 1760
#define H7 1967

#pragma interrupt_handler timer1:iv_TIM1_COMPC

unsigned char i=0;
unsigned int a=0;
unsigned int star[]= {
H1,2, H1,2, H5,2, H5,2, H6,2, H6,2, H5,1, 
H4,2, H4,2, H3,2, H3,2, H2,2, H2,2, H1,1, 
H5,2, H5,2, H4,2, H4,2, H3,2, H3,2, H2,1, 
H5,2, H5,2, H4,2, H4,2, H3,2, H3,2, H2,1,
H1,2, H1,2, H5,2, H5,2, H6,2, H6,2, H5,1, 
H4,2, H4,2, H3,2, H3,2, H2,2, H2,2, H1,1
};


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

void init_timer1(void){
  TCCR1A|=(0<<WGM11)|(0<<WGM10); 
  TCCR1B|=(1<<WGM12);//CTC
  TCCR1A|=(0<<COM1A1)|(0<<COM1A0);//OC1A NORMAL MODE OUTPUT
  TCCR1B|=(0<<CS12)|(1<<CS11)|(0<<CS10);//8prescale
  OCR1A=(unsigned int)(500000/star[0]-1);//OCR1=8M/(8*2*f)-1
  TIMSK=0x10;//enable timer1 compture interrupt
}

void init_port(void){
	DDRE|=BIT(0);
	PORTE=0XFF;
}



void timer1(void){
	a++;
	if(a%2)PORTE&=~BIT(0);
	else PORTE|=BIT(0);
	if(a==(unsigned int)(2*star[i]/star[i+1])){
		a=0;
		i+=2;
		OCR1A=(unsigned int)(500000/star[i]-1);
		delay_ms(10);
		if(i==84){i=0;delay_ms(1000);}
	}
}

void main(void){
	init_port();
	init_timer1();
	SEI();
	while(1){
		;
	}
}
