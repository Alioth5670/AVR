#include<iom128v.h>
#include<macros.h> 

#pragma interrupt_handler int4:iv_INT4
#pragma interrupt_handler int5:iv_INT5
#pragma interrupt_handler int6:iv_INT6
#pragma interrupt_handler int7:iv_INT7

unsigned char tab[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,0x80, 0x90};

void init_int(void){
	asm("cli");
	EICRB=0x1B;//7 low level 6 any logical change 
				//5falling eage 4rising eage
	EIMSK=0xF0;//enable INT4~7
	asm("sei"); //enable global
}

void init_port(void){
	DDRF =0xFF;//led
	PORTF=0xFF;//pull-up
	DDRE =0x01;//key
	PORTE|=0xFE;//low level output and pull-up input
	DDRD  = 0XFF;//Digital tube
	PORTD = 0XFF;//pull-up
	PORTG = 0x10;
	DDRG  = 0x10;//Digital tube number selection
}
//The digital tube displays the switch number and lights the LED lamp
void int4(void){
	PORTD = tab[4];
	PORTF=0x00;
	delay_ms(500);
	PORTF=0xFF; 
	PORTD = 0XFF;
}

void int5(void){
	PORTD = tab[5];
	PORTF=0x00;
	delay_ms(500);
	PORTF=0xFF; 
	PORTD = 0XFF;
}

void int6(void){
	
	PORTD = tab[6];
	PORTF=0x00;
	delay_ms(500);
	PORTF=0xFF; 
	PORTD = 0XFF;
}

void int7(void){
	
	PORTD = tab[7];
	PORTF=0x00;
	delay_ms(500);
	PORTF=0xFF; 
	PORTD = 0XFF;
}

void main(void){
	init_port();
	init_int();
	while(1){;}
}
