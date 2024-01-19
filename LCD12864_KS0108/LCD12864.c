#include "LCD12864.h"
bit LCD_RE = 0;
MY_GBKFONT * gbkpointer;
MY_ASCIIFont * asciipointer;


void Delay_us(uchar us)		//@11.0592MHz,以1us作为单位
{
    _nop_();
    while(us--)
    {
        _nop_();
    }
}
void Delay_ms(uchar ms)		//@11.0592MHz,以1ms作为单位
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

void LCD12864_COMMAND(uchar cmd)
{
    while(Check_Ready());
    LCD_EN=0;
    LCD_RS=0;
    LCD_RW=0;
    _nop_();//Address set-up time
    LCD_EN=1;//latch address 
    _nop_();//enable high width 
    BUS=cmd;
    _nop_();//Data set-up time
    LCD_EN=0;//latch data
	//		BUS = 0; 当enable下降沿到来时，数据已经被所存住，所以这个时候改变也不会影响
    Delay_us(50);//instruction implement time
}

void Write_Data(uchar dat)
{
    while(Check_Ready());
    LCD_EN=0;
    LCD_RS=1;
    LCD_RW=0;
    _nop_();//Address set-up time
    LCD_EN=1;//latch address 
    _nop_();//enable high width 
    BUS=dat;
    _nop_();//Data set-up time
    LCD_EN=0;//latch data
	//		BUS = 0; 当enable下降沿到来时，数据已经被所存住，所以这个时候改变也不会影响
    Delay_us(50);//instruction implement time
}

uchar Read_Data()
{
    uchar data_result;
    while(Check_Ready());
    LCD_EN=0;
	LCD_RS=0;
	LCD_RW=1;
    _nop_();//Addres set up time and enable hold time 
    LCD_EN=1;//latch address
	BUS=0xff;
	_nop_();//
	LCD_EN=1;
	_nop_();//Data delay time
	data_result = BUS;
	LCD_EN=0;//latch data
    Delay_us(50);
    return data_result;
}

uchar Read_Status()
{
	uchar BF_AD_result;//读指令不需要checkbusy
    LCD_EN=0;
	LCD_RS=0;
	LCD_RW=1;
    _nop_();//Addres set up time and enable hold time 
    LCD_EN=1;//latch address
	BUS=0xff;
	_nop_();//
	LCD_EN=1;
	_nop_();//Data delay time
	BF_AD_result = BUS;
	LCD_EN=0;//latch data
    Delay_us(10);
	return BF_AD_result;
}

bit Check_Ready()
{
    bit result;
    result = (bit)(Read_Status()&0x90);
    return result;//BF=1orReady=1,the next instruction will not be accepted.
}


void Display_Control(bit entire_display)
{
    uchar cmd =0x3E;
    if(entire_display)cmd+=1;
    LCD12864_COMMAND(cmd);
    Delay_us(50);
}

void Set_Vertical_Address(uchar address)
{
    if(address<0x40)
    {
        address = address|0x40;
    }
    else address = 0x40;
    LCD12864_COMMAND(address);
}
void Set_Horizontal_Address(uchar address)
{
    if(address<0x08)
    {
        address = address|0xB8;
    }
    else address = 0xB8;
    LCD12864_COMMAND(address);
}

void Set_Start_Line(uchar address)
{
    if(address<0x40)
    {
        address = address|0xC0;
    }
    else address = 0xC0;
    LCD12864_COMMAND(address);
}

void LCD12864_init()
{
    Delay_ms(30);
	LCD_CS2=0;
	LCD_CS1=1;
    while(Check_Ready());
    Display_Control(1);
    Set_Start_Line(0);
}

void LCD12864_Set_Display_location(uchar x,uchar y)
{

    if(x<64&&y<8)//显示在左边屏幕
    {
        LCD_CS2=0;
        LCD_CS1=1;
        Set_Vertical_Address(x);
        Set_Horizontal_Address(y);
    }
    else if(x>=64&&x<128&&y<8)
    {
        LCD_CS2=1;
        LCD_CS1=0;
        Set_Vertical_Address(x-64);
        Set_Horizontal_Address(y);
    }
    else
    {
        LCD_CS2=0;
        LCD_CS1=1;
        Set_Vertical_Address(0);
        Set_Horizontal_Address(0);
    }

}

void LCD12864_Show_chinese(const MY_GBKFONT * ptr,const char * indexptr,uchar x, uchar y)
{
    uchar i,j;
    LCD12864_Set_Display_location(x,y);
    for(i=0;i<GBK_size;i++)
    {
        if(strncmp(&((ptr+i)->Index),indexptr,sizeof(format))==0)
        {
            for(j=0;j<16;j++)
            Write_Data((ptr+i)->Msk[j]);
            LCD12864_Set_Display_location(x,y+1);
            for(;j<32;j++)
            Write_Data((ptr+i)->Msk[j]);
            break;
        }
    }
    LCD12864_Set_Display_location(x+16,y);
}

void LCD12864_Showchar(const MY_ASCIIFont * ptr,uchar index,uchar x, uchar y)
{
    uchar i,j;
    LCD12864_Set_Display_location(x,y);
    for(i=0;i<ASCII_size;i++)
    {
        if((ptr+i)->Index==index)
        {
            for(j=0;j<8;j++)
            Write_Data((ptr+i)->Msk[j]);
            LCD12864_Set_Display_location(x,y+1);
            for(;j<16;j++)
            Write_Data((ptr+i)->Msk[j]);
            break;
        }
    }
	LCD12864_Set_Display_location(x+8,y);
}

void LCD12864_Shownum(uint num,char x,char y)
{
    uchar i;
    uint w;
    uchar flag=0;
    LCD12864_Set_Display_location(x,y);
    for(w=10000;w>=1;w/=10)
    {
        i = num/w;
        num = num%w;
        if (i) flag+=1;
        if (flag) 
        {
            LCD12864_Showchar(ASCIITABLE,i+0x30,x+8*(flag-1),y);
        }
    }
}

void LCD12864_ShowString(uchar * string,uchar x,uchar y)
{
    uchar i=0;
    LCD12864_Set_Display_location(x,y);
    while(*(string+i)!='\0')
    {
        LCD12864_Showchar(ASCIITABLE,*(i+string),x+8*i,y);
        i++;
    }
}

void LCD12864_Show_chinese_String(const format* string,uchar x,uchar y)
{
    uchar i=0;
    LCD12864_Set_Display_location(x,y);
    while(strncmp((char * )(string+i),"\0",3)!=0)
    {
        LCD12864_Show_chinese(GBKTABLE,(char *)(i+string),x+16*i,y);
        i++;
    }
}