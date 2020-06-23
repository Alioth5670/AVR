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
unsigned char disp[4];
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
	DDRF  = 0XFC; 
	PORTF = 0XFC;
	DDRD  = 0XFF;
	PORTD = 0XFF;
	PORTG = 0x1B;
	DDRG  = 0x1B;
}

unsigned int Read_ADC(/*unsigned char channel*/){
	unsigned int rhigh,rlow,result;
	ADMUX=0x00;
	ADCSRA|=0XC3;          //使能ADC          //启动转换
	while(!(ADCSRA&(BIT(ADIF))));
	ADCSRA&=~BIT(ADIF);
	
	rlow =(unsigned int)ADCL;
	rhigh=(unsigned int)ADCH;
	result =(rhigh<<8)+rlow;
	return result;

}


void display(void){
	if(voltage<417) {PORTF&=~BIT(2);delay_us(500);PORTF = 0XFC;}
	else if(voltage<834){PORTF&=~BIT(3);delay_us(500);PORTF = 0XFC;}
	else if(voltage<1251){PORTF&=~BIT(4);delay_us(500);PORTF = 0XFC;}
	else if(voltage<1668){PORTF&=~BIT(5);delay_us(500);PORTF = 0XFC;}
	else if(voltage<2085){PORTF&=~BIT(6);delay_us(500);PORTF = 0XFC;}
	else if(voltage<2501){PORTF&=~BIT(7);delay_us(500);PORTF = 0XFC;}
	
	
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
	voltage=(unsigned int)(Read_ADC(0x00)*2.44);
	display(); 
	//PORTF=0x00;
		
	}
	
	
}
