#include<iom128v.h>
#include<macros.h>


unsigned char i=0;//Digital tube position selection
unsigned int ad_data1=0;
unsigned int adc=0;

//I/O口初始化
void por_init(void)
{
   PORTF = 0XFF;//
   DDRF = 0XFE;//1111 1110 AD采集口 ADC 设置为输入
   
}


//CPU总体初始化
void init_devices(void)
{
   por_init();//Initialize the I/O ports
   SEI();//Enable Global Interrupt 
}

unsigned int ad_cat(void)//电压采集函数
{
     unsigned int ad1,ad2;
	 ADCSRA=0x00;//先关闭ADC功能
     ADMUX=0x40;//AVCC,connect internal reference source,align right
     ACSR = 0x80;//Analog comparator is cut off
     ADCSRA|=BIT(ADEN);//Enable ADC           
     ADCSRA|=BIT(ADSC);//ADC begin to turn           
     while(!(ADCSRA&(1<<ADIF)));//Judgement for ADIF=1
     ADCSRA&=~BIT(ADIF);//Clear interrupt flag
     ad1 = (unsigned int)ADCL;
     ad2 = (unsigned int)ADCH;
     ad2 = (ad2<<8)+ad1;//move the high bits to the left
     return ad2;
}
 
 
//主函数
void main(void)
{
   init_devices();
   
   while(1)
   {
    ad_data1=ad_cat();
    adc=(unsigned int)(ad_data1*2.44);
	
	if((adc>0)&&(adc<=357))
	PORTF=0xFD;
	else if((adc>357)&&(adc<=714))
	PORTF=0xFB;
	else if((adc>714)&&(adc<=1071))
	PORTF=0xF7;
    else if((adc>1071)&&(adc<=1428))
	PORTF=0xEF;
	else if((adc>1428)&&(adc<=1785))
	PORTF=0xDF;
	else if((adc>1785)&&(adc<=2142))
	PORTF=0xBF;
	else 
	PORTF=0x7F;
   }
}