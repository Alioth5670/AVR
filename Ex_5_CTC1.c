#include <iom128v.h>
#include <macros.h>

unsigned char a=0;

void init_timer1(void){
  TCCR1A|=(0<<WGM11)|(0<<WGM10); 
  TCCR1B|=(1<<WGM12);//CTC
  TCCR1A|=(0<<COM1A1)|(0<<COM1A0);//OC1A normal output 
  TCCR1B|=(0<<CS12)|(1<<CS11)|(0<<CS10);//8prescale 1US
  OCR1A=9999;//10ms
  TIMSK=0x10;//TIM1_COMPC enable
}

void init_port(void){
	DDRF=0XFF;//port F as output
	PORTF=0X00;// low level
}

#pragma interrupt_handler timer1:iv_TIM1_COMPC
void timer1(void){//ISR
	a++;
	if(a==100){//1s
		a=0;
		PORTF=~PORTF;//invert PORTF
	}
}

void main(void){
	init_port();
	init_timer1();
	SEI();// enable global interrupt
	while(1){
		;
	}
}
