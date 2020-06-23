#include "lcd_1602.h"

//us��ʱ����
void delay_us(uint n)   //8*0.125=1us
{
    int i,j;
	for(j=0;j<8;j++)
	{
	  for (i=0;i<n;i++) 
	  NOP();
	}  
}

//ms��ʱ����
void delay_ms(uint i)
{
    while(i--)
    {                          
	    uint j;                
        for(j=1;j<=1332;j++)   
			   ;               
    } 
}
//����LCDдʱ��
void LCD_en_write(void)        //EN�˲���һ���ߵ�ƽ���壬����LCDдʱ��
  {
    E_ON;//EN_SET;
    delay_us(3);
    E_OFF;//EN_CLR;
	delay_us(3);
  }
//дָ���
void Write_Instruction(uchar command)
{
  RS_OFF;//RS_CLR;
  RW_OFF;//RW_CLR;
  E_ON;//EN_SET;
  PORTC=command;
  LCD_en_write();//д��ָ������
}

//д���ݺ���
void Write_Data(uchar Wdata)
{
  RS_ON;//RS_SET;
  RW_OFF;//RW_CLR;
  E_ON;//EN_SET;
  PORTC=Wdata;
  LCD_en_write();//д������
} 
//��������
void LCD_clear(void)
{
  Write_Instruction(0x01);
  delay_ms(2);
}

//�ַ���ʾ��ʼ��ַ����
void LCD_SET_XY(uchar X,uchar Y)
{
    uchar address;
    if(Y==0)
       address=0x80+X;//Y=0,��ʾ�ڵ�һ����ʾ����ַ����Ϊ0x80
    else 
       address=0xc0+X;//Y��0ʱ����ʱ�ڵڶ�����ʾ����ַ����Ϊ0XC0
    Write_Instruction(address);//дָ�������ʾ��ʼ��ַ
}

//�ڵ�X��Y�п�ʼ��ʾ��ָ��*S��ָ����ַ���
void LCD_write_str(uchar X,uchar Y,uchar *s)
{
  LCD_SET_XY(X,Y);//���ó�ʼ�ַ���ʾ��ַ
  while(*s)//���д����ʾ�ַ���ֱ�����һ���ַ�"/0"
  {
    Write_Data(*s);//д�뵱ǰ�ַ�����ʾ
	s++;//��ַָ���1��ָ����һ����д�ַ�
  }
}

//�ڵ�X��Y�п�ʼ��ʾWdata����Ӧ�ĵ����ַ�
void LCD_write_char(uchar X,uchar Y,uchar Wdata)
{
  LCD_SET_XY(X,Y);//д��ַ
  Write_Data(Wdata);//д�뵱ǰ�ַ�����ʾ
}
//��ʾ����ʼ������
void LCD_init(void) 
{
	DDRC = 0xFF;						    //I/O�ڷ�������
	DDRA|=(1<<PA6)|(1<<PA7);
	DDRG|=(1<<PG2);
	delay_ms(15);                           //�ϵ���ʱһ��ʱ�䣬ʹ�����ȶ�
	Write_Instruction(0x38);				//8bit interface,2line,5*7dots
	delay_ms(5);
	Write_Instruction(0x38);	
	delay_ms(5);
	Write_Instruction(0x38);	
	
	Write_Instruction(0x08);	//����ʾ�����Թ�꣬��겻��˸
	Write_Instruction(0x01);	//����
	delay_ms(5);
	
	Write_Instruction(0x04);	//дһ�ַ���������ʾ���ƶ�
	//Write_Instruction(0x05);	//дһ�ַ�����������
	//Write_Instruction(0x06);	//дһ�ַ���������ʾ���ƶ�
	//Write_Instruction(0x07);	//дһ�ַ�����������
	delay_ms(5);
	
	//Write_Instruction(0x0B);	//�ر���ʾ������ʾ�ַ���ֻ�б�������
	Write_Instruction(0x0C);	//����ʾ����ꡢ��˸���ر�
	//Write_Instruction(0x0D);	//����ʾ������ʾ��꣬�������˸
	//Write_Instruction(0x0E);	//����ʾ����ʾ��꣬����겻��˸
	//Write_Instruction(0x0F);	//����ʾ����ꡢ��˸����ʾ
}





