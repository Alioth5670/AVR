#include<iom128v.h>
#include<macros.h> 

#pragma interrupt_handler int4:iv_INT4
#pragma interrupt_handler int5:iv_INT5
#pragma interrupt_handler int6:iv_INT6
#pragma interrupt_handler int7:iv_INT7

void init_int(void){
	asm("cli");
	EICRB=0x1B;//7 low level 6 any logical change 
			   //5 falling eage 4rising eage
	EIMSK=0xF0;//enable INT4~7
	asm("sei");//enable global
}

void init_port(void){
	DDRF =0xFF;//led
	PORTF=0xFF;//pull-up
	DDRE =0x01;//key
	PORTE|=0xFE;//low level output and pull-up input
}
//Tlights the LED lamp 0.5s
void int4(void){
	PORTF=0x00;
	delay_ms(500);
	PORTF=0xFF; 
}

void int5(void){
	PORTF=0x00;
	delay_ms(500);
	PORTF=0xFF; 
}

void int6(void){
	PORTF=0x00;
	delay_ms(500);
	PORTF=0xFF; 
}

void int7(void){
	PORTF=0x00;
	delay_ms(500);
	PORTF=0xFF; 
}

void main(void){
	init_port();
	init_int();
	while(1){;}
}
