#include <iom128v.h>
#include <macros.h>
#include "lcd_1602.c"

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

unsigned int tune[]={0,M1,M2,M3,M4,M5,M6,M7,H1};
unsigned int star[]= {
H1,8, H1,8, H5,8, H5,8, H6,8, H6,8, H5,16, 
H4,8, H4,8, H3,8, H3,8, H2,8, H2,8, H1,16, 
H5,8, H5,8, H4,8, H4,8, H3,8, H3,8, H2,16, 
H5,8, H5,8, H4,8, H4,8, H3,8, H3,8, H2,16,
H1,8, H1,8, H5,8, H5,8, H6,8, H6,8, H5,16, 
H4,8, H4,8, H3,8, H3,8, H2,8, H2,8, H1,16,
0xFF
};

unsigned char state=1;

void init_port(void){
	DDRF=0xFF;
	PORTF=0xFF;
	DDRE=0X0F;
	PORTE=0XF0;
}

void init_timer1(void){
  TIMSK=0x00;//disable timer1 
  TCCR1A|=(0<<WGM11)|(0<<WGM10); 
  TCCR1B|=(1<<WGM12);//CTC
  TCCR1A|=(0<<COM1A1)|(0<<COM1A0);//OC1A NORMAL MODE OUTPUT
  TCCR1B|=(0<<CS12)|(1<<CS11)|(0<<CS10);//8prescale
}

void init_int(void){
	EICRB=0x80;//risng edge of INT7 
	EIMSK=0x80;//enable INT7
	asm("sei"); //enable global
}

//to get key value from keybord
unsigned char key_scan(void){
	unsigned char X,Y,key,key_value=0;
	DDRE=0X0F;
	PORTE=0XF0;
	if(PINE!=0XF0){
		delay_ms(10);
		if(PINE!=0XF0){
			X=PINE|0X0F;
			DDRE=0X70;
			PORTE=0X8F; 
			if(PINE!=0X8F){
				delay_ms(10);
				if(PINE!=0X8F){
					Y=PINE|0XF0;
					key=X&Y; 
					switch ( key ) {
						case 0xbe: key_value=1; break;
						case 0xde: key_value=2; break;
						case 0xee: key_value=3; break;
						case 0xbd: key_value=4; break;
						case 0xdd: key_value=5; break;
						case 0xed: key_value=6; break;
						case 0xbb: key_value=7; break;
						case 0xdb: key_value=8; break;
						default:key_value=0; break;
					}
				}
			}
		}
	}
	return key_value;
}

void music(unsigned int *song){
	while(*song!=0XFF){
	delay_ms(5);
	OCR1A=(unsigned int)(500000/(*song)-1);
	//OCR1=8M/(8*2*f)-1
	TIMSK=0x10;//enable timer1 compture interrupt
  	song++;//get time
  	delay_ms(52*(*song));
  	song++;//get another tune
    TIMSK=0x00;//disable timer1
	if (state==1)break;//change state 
	if (key_scan()==1){//key 1 to pause
    	LCD_write_str(11,0,"STOP");
		while(!(key_scan()==2));
		//key 2 to play		
		}
	LCD_write_str(11,0,"PLAY");//play
	}
	delay_ms(1000);
}

void beat(unsigned int a){
	OCR1A=(unsigned int)(500000/a-1);//OCR1=8M/(8*2*f)-1
	TIMSK=0x10;//enable timer1 compture interrupt
  	delay_ms(400);
    TIMSK=0x00;//disable timer1 
}

#pragma interrupt_handler timer1:iv_TIM1_COMPC
void timer1(void){
	PORTF^=BIT(7);
	//inversing PF7 to make sound
}

#pragma interrupt_handler int7:9
void int7(void){
	if(state==1){
        state=2;
	    LCD_clear();
		LCD_write_str(0,0,"MODE:Music");
		LCD_write_str(0,1,"S1:Change mode");
	}
	else if(state==2){
	 	state=1;
		LCD_clear();
		LCD_write_str(0,0,"MODE:E-organs");
		LCD_write_str(0,1,"S1:Change mode");	
	}
}

void main(void){
	init_port();
	init_timer1();
	init_int();
	LCD_init();//initalize device
    LCD_clear();
	LCD_write_str(1,0,"MODE: E-organs");
	LCD_write_str(0,1,"S1:Change mode");		
	while(1){
	    if(state==1)//Play a single tone
		    if(key_scan()) beat(tune[key_scan()]);
	    else if(state==2) music(star);
	    //play music
	}
}
