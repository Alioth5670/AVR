#include<iom128v.h>
#include<macros.h>

#define SEG1_ON   PORTG |= BIT(4);
#define SEG1_OFF  PORTG &= ~BIT(4); 

#define SEG2_ON   PORTG |= BIT(3);
#define SEG2_OFF  PORTG &= ~BIT(3);
 
#define SEG3_ON   PORTG |= BIT(1); 
#define SEG3_OFF  PORTG &= ~BIT(1);

#define SEG4_ON   PORTG |= BIT(0); 
#define SEG4_OFF  PORTG &= ~BIT(0);

unsigned char tab[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,0x80, 0x90};
unsigned char key_value=0;
unsigned int voltage;

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

void init_port(void){
	DDRF  = 0X00; 
	PORTF = 0X00;
	DDRD  = 0XFF;
	PORTD = 0XFF;
	PORTG = 0x1B;
	DDRG  = 0x1B;
	DDRE  = 0x01;
	PORTE = 0xc0;
}

void key(void){
	if(PINE!=0xC0){
		if (PINE==0X80)	key_value = 1;
		else if (PINE==0X40)  key_value = 0;	
	}
}

unsigned int Read_ADC(unsigned char channel){
	unsigned int rhigh,rlow,result;
	ADMUX=channel;
	ADCSRA|=0XC3;//Enable ADC, start conversion,8-prescale  
	while(!(ADCSRA&(BIT(ADIF))));//Wait for the conversion to complete
	ADCSRA&=~(BIT(ADIF)|BIT(ADEN));//cleat ADEN and ADIF
	
	rlow =(unsigned int)ADCL;//read low resistor
	rhigh=(unsigned int)ADCH;//read low resistor
	result =(rhigh<<8)+rlow;//get final result
	return result;
}

//Dynamic digital tube display
void display(void){
	PORTD=tab[voltage/1000];
	SEG4_ON;
	delay_us(500);
	SEG4_OFF;
	
	PORTD=tab[(voltage%1000)/100];
	SEG3_ON;
	delay_us(500);
	SEG3_OFF;
	
	PORTD=tab[(voltage%100)/10];
	SEG2_ON;
	delay_us(500);
	SEG2_OFF;
	
	PORTD=tab[(voltage%10)];
	SEG1_ON;
	delay_us(500); 			
	SEG1_OFF;		 
}

void main(void){
	init_port();
	while(1){	
	key();
	switch(key_value){
		case 0:voltage=(unsigned int)(Read_ADC(0x00)*2.44);break;
		case 1:voltage=(unsigned int)(Read_ADC(0x01)*2.44);break;
		default:break;
	}
	display(); 	
	}
}
