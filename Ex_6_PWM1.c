#include <iom128v.h>
#include <macros.h>
void init_port(void)
{
  PORTB=0x00; 
  DDRB=0xFF;
}
void init_timer1(void){
  TCCR1A=0XFD;//set on compare match clear on bottom
  TCCR1B|=(1<<WGM12);//8-bit fast PWM
  TCCR1B|=(0<<CS12)|(1<<CS11)|(0<<CS10);//8prescale
  OCR1C=64;//75% 256-256*75%
  OCR1B=128;//50% 256-256*50%
  OCR1A=192;//25% 256-256*25%
}

void main(void){
	init_port();
	init_timer1();
	while(1);
} 
