#include "lcd_1602.h"

//us延时函数
void delay_us(uint n)   //8*0.125=1us
{
    int i,j;
	for(j=0;j<8;j++)
	{
	  for (i=0;i<n;i++) 
	  NOP();
	}  
}

//ms延时函数
void delay_ms(uint i)
{
    while(i--)
    {                          
	    uint j;                
        for(j=1;j<=1332;j++)   
			   ;               
    } 
}
//控制LCD写时序
void LCD_en_write(void)        //EN端产生一个高电平脉冲，控制LCD写时序
  {
    E_ON;//EN_SET;
    delay_us(3);
    E_OFF;//EN_CLR;
	delay_us(3);
  }
//写指令函数
void Write_Instruction(uchar command)
{
  RS_OFF;//RS_CLR;
  RW_OFF;//RW_CLR;
  E_ON;//EN_SET;
  PORTC=command;
  LCD_en_write();//写入指令数据
}

//写数据函数
void Write_Data(uchar Wdata)
{
  RS_ON;//RS_SET;
  RW_OFF;//RW_CLR;
  E_ON;//EN_SET;
  PORTC=Wdata;
  LCD_en_write();//写入数据
} 
//清屏函数
void LCD_clear(void)
{
  Write_Instruction(0x01);
  delay_ms(2);
}

//字符显示初始地址设置
void LCD_SET_XY(uchar X,uchar Y)
{
    uchar address;
    if(Y==0)
       address=0x80+X;//Y=0,表示在第一行显示，地址基数为0x80
    else 
       address=0xc0+X;//Y非0时，表时在第二行显示，地址基数为0XC0
    Write_Instruction(address);//写指令，设置显示初始地址
}

//在第X行Y列开始显示，指针*S所指向的字符串
void LCD_write_str(uchar X,uchar Y,uchar *s)
{
  LCD_SET_XY(X,Y);//设置初始字符显示地址
  while(*s)//逐次写入显示字符，直到最后一个字符"/0"
  {
    Write_Data(*s);//写入当前字符并显示
	s++;//地址指针加1，指向下一个待写字符
  }
}

//在第X行Y列开始显示Wdata所对应的单个字符
void LCD_write_char(uchar X,uchar Y,uchar Wdata)
{
  LCD_SET_XY(X,Y);//写地址
  Write_Data(Wdata);//写入当前字符并显示
}
//显示屏初始化函数
void LCD_init(void) 
{
	DDRC = 0xFF;						    //I/O口方向设置
	DDRA|=(1<<PA6)|(1<<PA7);
	DDRG|=(1<<PG2);
	delay_ms(15);                           //上电延时一段时间，使供电稳定
	Write_Instruction(0x38);				//8bit interface,2line,5*7dots
	delay_ms(5);
	Write_Instruction(0x38);	
	delay_ms(5);
	Write_Instruction(0x38);	
	
	Write_Instruction(0x08);	//关显示，不显光标，光标不闪烁
	Write_Instruction(0x01);	//清屏
	delay_ms(5);
	
	Write_Instruction(0x04);	//写一字符，整屏显示不移动
	//Write_Instruction(0x05);	//写一字符，整屏右移
	//Write_Instruction(0x06);	//写一字符，整屏显示不移动
	//Write_Instruction(0x07);	//写一字符，整屏左移
	delay_ms(5);
	
	//Write_Instruction(0x0B);	//关闭显示（不显示字符，只有背光亮）
	Write_Instruction(0x0C);	//开显示，光标、闪烁都关闭
	//Write_Instruction(0x0D);	//开显示，不显示光标，但光标闪烁
	//Write_Instruction(0x0E);	//开显示，显示光标，但光标不闪烁
	//Write_Instruction(0x0F);	//开显示，光标、闪烁均显示
}





