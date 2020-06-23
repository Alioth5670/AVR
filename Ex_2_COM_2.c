#include<iom128v.h>
#include <macros.h>
# define fosc 8000000
#define baud 9600

unsigned char rdata;

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
	UCSR0B = 0x18;//enable receive and trasmitter
	UCSR0C = 0x86;//asynchronous, no parity, 1 stop bit,8 data bits
	UBRR0L = (fosc/(8*baud)-1)%256;//Baud Rate initialization
	UBRR0H = (fosc/(8*baud)-1)/256;
}

void send(unsigned char a){
	UDR0 = a;//load data to UDR for transmission
	while(!(UCSR0A&BIT(UDRE0)));//wait for UDRE flag
}


unsigned char receive(void){
	while(!(UCSR0A&BIT(RXC0)));//wait for RXC flag
	return UDR0;//retrieve data from UDR and return
}

void main (void){
	init_usart(); 
	while(1){
		rdata=receive();
		send(rdata);  	
	}		
}
