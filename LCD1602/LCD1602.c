#include "LCD1602.h"
void Delay_us(uchar us)		//@11.0592MHz,以1us作为单位
{
    _nop_();
    while(us--)
    {
        _nop_();
    }
}
void Delay1ms(uchar ms)		//@11.0592MHz,以1ms作为单位
{
	unsigned char i, j;
    while(ms--)
    {
        _nop_();
        i = 2;
        j = 199;
        do
        {
            while (--j);
        } while (--i);        
    }

}
void LCD1602_COMMAND(uchar cmd)
{
    while(Check_Busy());
    LCD_RS=0;
    LCD_RW=0;
    _nop_();//Address set-up time
    LCD_EN=1;
    _nop_();
		BUS=cmd;
		_nop_();//Data set-up time
    LCD_EN=0;
	//		BUS = 0; 当enable下降沿到来时，数据已经被所存住，所以这个时候改变也不会影响
		Delay_us(50);//instruction implement time
}

void Write_Data(uchar dat)
{
    while(Check_Busy());
    LCD_RS=1;
    LCD_RW=0;
    _nop_();//Address set-up time
    LCD_EN=1;
    _nop_();
		BUS=dat;
		_nop_();//Data set-up time
    LCD_EN=0;
		Delay_us(50);//Data and address hold time
}

uchar Read_Data()
{
    uchar data_result;
		while(Check_Busy());
    LCD_RS=1;
    LCD_RW=1;
		BUS=0xff;		//读取数据之前要先置一
    _nop_();//Address set-up time
    LCD_EN=1;
    _nop_();//Data delay time，
    data_result = BUS;
    LCD_EN=0;
    return data_result;
}

uchar Read_Busyflag_and_AD()
{
	uchar BF_AD_result;//读指令不需要checkbusy
	LCD_RS=0;
	LCD_RW=1;
	BUS=0xff;
	_nop_();//Address set-up time
	LCD_EN=1;
	_nop_();//Data delay time
	BF_AD_result = BUS;
	LCD_EN=0;
	return BF_AD_result;
}

bit Check_Busy()
{
    bit result;
    result = (bit)(Read_Busyflag_and_AD()&0x80);
    return result;//BF=1,the next instruction will not be accepted.
}

void Clear_Display()
{
    LCD1602_COMMAND(0x01);
    Delay1ms(2);
}

void Return_Home()
{
    LCD1602_COMMAND(0x02);
    Delay1ms(2);
}

void Entry_mode_set(bit dir,bit shift)
{
    uchar cmd =0x04;
    if(dir)cmd+=2;
    if(shift)cmd+=1;
    LCD1602_COMMAND(cmd);
    Delay_us(50);
}

void Display_Control(bit entire_display,bit cursor,bit blinking)
{
    uchar cmd =0x08;
    if(entire_display)cmd+=4;
    if(cursor)cmd+=2;
    if(blinking)cmd+=1;
    LCD1602_COMMAND(cmd);
    Delay_us(50);
}

void Shift_Control(bit choose_dispaly,bit shift_left)
{
    uchar cmd = 0x10;
    if(choose_dispaly)cmd+=8;
    if(shift_left)cmd+=4;
    LCD1602_COMMAND(cmd);
    Delay_us(50);
}
void Function_set(bit dataLength,bit display_lines,bit char_size)
{
    uchar cmd = 0x20;
    if(dataLength)cmd+=16;
    if(display_lines)cmd+=8;
    if(char_size)cmd+=4;
    LCD1602_COMMAND(cmd);

}
void Set_CGRAM_Address(uchar address)
{
    if(address<0x40)
    {
        address = address|0x40;
    }
    else address = 0x40;
    LCD1602_COMMAND(address);
}
void Set_DDRAM_Address(uchar address)
{
    if(address<0x80)
    {
        address = address|0x80;
    }
    else address = 0x80;
    LCD1602_COMMAND(address);
}

void LCD1602_init()
{
    Delay1ms(47);
    Function_set(1,1,0);
    Display_Control(1,1,1);
		Entry_mode_set(1,0);
		Clear_Display();
		Delay1ms(1);
}

void LCD1602_Set_Display_location(uchar x,uchar y)
{
    uchar DD_address;
    if(x<40&&y<2)
    {
        DD_address=x+0x40*(y);
        Set_DDRAM_Address(DD_address);
    }
    else Set_DDRAM_Address(0x00);
}
void LCD1602_Showchar(uchar character,char x,char y)
{
    if(x!=-1&&y!=-1)
        LCD1602_Set_Display_location(x,y);
    Write_Data(character);
}
void LCD1602_Shownum(uint num,char x,char y)
{
    uchar i;
    uint w;
    bit flag=0;
    if(x!=-1&&y!=-1)
        LCD1602_Set_Display_location(x,y);
    for(w=10000;w>=1;w/=10)
    {
        i = num/w;
        num = num%w;
        if (i) flag=1;
        if (flag) Write_Data(i+0x30);
    }
}
void LCD1602_ShowSymbol(character symbol,char x,char y)
{
    if(x!=-1&&y!=-1)
        LCD1602_Set_Display_location(x,y);
    switch (symbol)
    {
        case Addition:
        Write_Data(0x2B);
        break;
        case Subtraction:
        Write_Data(0x2D);
        break;
        case Multiplication:
        Write_Data(0x2A);
        break;
        case Division:
        Write_Data(0x2F);
        break;
				case EQUAL:
				Write_Data(0x3D);
				break;
        case Dot:
        Write_Data(0x2E);
        Write_Data(0x2E);
        Write_Data(0x2E);
        break;
        default:
            break;
    }
}
void LCD1602_ShowString(uchar * string,char x,char y)
{
    uchar i=0;
    if(x!=-1&&y!=-1)
        LCD1602_Set_Display_location(x,y);
    while(*(string+i)!='\0')
    {
        Write_Data(*(string+i));
        i++;
    }
}