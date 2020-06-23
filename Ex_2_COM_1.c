#include<iom128v.h>
#include <macros.h>

#define fosc 8000000
#define baud 9600

unsigned char tab[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,0x80, 0x90};
unsigned char i,data;

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

void init_usart(void){
	UCSR0A = 0x02;//double speed
	UCSR0B = 0x00;
	UCSR0C = 0x86;//asynchronous, no parity, 1 stop bit,8 data bits
	UBRR0L = (fosc/(8*baud)-1)%256;//Baud Rate initialization
	UBRR0H = (fosc/(8*baud)-1)/256;
	UCSR0B = 0x18;//enable receive and trasmitter
}

void send(unsigned char a){
	UDR0 = a;//load data to UDR for transmission
	while(!(UCSR0A&BIT(UDRE0)));//wait for UDRE flag
}

void init_port(void){
	DDRD  = 0XFF;
	PORTD = 0XFF;
	PORTG = 0x1B;
	DDRG  = 0x1B;
}

unsigned char receive(void){
	while(!(UCSR0A&BIT(RXC0)));//wait for RXC flag
	return UDR0;//retrieve data from UDR and return
}

void main(void){
	init_port();  
	init_usart();
	while(1){
		for(i=0;i<10;i++){
			send(i);
			data=receive();
			PORTD=tab[data];
			delay_ms(1000);
		}
	}
}
