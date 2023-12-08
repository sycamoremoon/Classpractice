#ifndef __LCD1602_H__
#define __LCD1602_H__

#include <REGX51.H>
#include <INTRINS.H>
#define BUS P2  //定义数据地址接口
 sbit LCD_RS=P1^7; //定义控制引脚
 sbit LCD_RW=P1^6;
 sbit LCD_EN=P1^5;

enum Character
{
    Addition,
    Subtraction,
    Multiplication,
    Division,
    Dot,
		EQUAL,
    NULLOPERTATOR
};

typedef enum Character character;

//basic function
void Delay_us(uchar us);
void Delay1ms(uchar ms);
void LCD1602_COMMAND(uchar cmd);
void Clear_Display();
void Return_Home();
void Entry_mode_set(bit dir,bit shift);
void Display_Control(bit entire_display,bit cursor,bit blinking);
void Shift_Control(bit choose_dispaly,bit shift_left);
void Function_set(bit dataLength,bit display_lines,bit char_size);
void Set_CGRAM_Address(uchar address);
void Set_DDRAM_Address(uchar address);
uchar Read_Busyflag_and_AD();
bit Check_Busy();
//To write or read into CG or DDRAM is determined by the previous specification of the CGRAM or DDRAM
//address setting.
uchar Read_Data();
void Write_Data(uchar mdata);

//assemble function
void LCD1602_init();
void LCD1602_Set_Display_location(uchar x,uchar y);
void LCD1602_Showchar(uchar character,char x,char y);
void LCD1602_Shownum(uint num,char x,char y);
void LCD1602_ShowSymbol(character symbol,char x,char y);
void LCD1602_ShowString(uchar * string,char x,char y);

#endif