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


unsigned int star[]= {
H1,8, H1,8, H5,8, H5,8, H6,8, H6,8, H5,16, 
H4,8, H4,8, H3,8, H3,8, H2,8, H2,8, H1,16, 
H5,8, H5,8, H4,8, H4,8, H3,8, H3,8, H2,16, 
H5,8, H5,8, H4,8, H4,8, H3,8, H3,8, H2,16,
H1,8, H1,8, H5,8, H5,8, H6,8, H6,8, H5,16, 
H4,8, H4,8, H3,8, H3,8, H2,8, H2,8, H1,16,
0xFF
};

// to get 1 us delay
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
}

void init_port(void){
	DDRE=0xFF;
	PORTE=0XFF;
}

void music(unsigned int *song){
	while(*song!=0XFF){
	delay_ms(10);
	OCR1A=(unsigned int)(500000/(*song)-1);//OCR1=8M/(8*2*f)-1
	TIMSK=0x10;//enable timer1 compture interrupt
  	song++;//get time
  	delay_ms(62*(*song));
  	song++;//get another tune
    TIMSK=0x00;//disable timer1 
	}
	delay_ms(1000);
}

void timer1(void){
	PORTE^=BIT(0);
}

void main(void){
	init_port();
	init_timer1();
	SEI();//enable global interrupt
	while(1){
		music(star);
	}
}
