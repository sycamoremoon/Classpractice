#ifndef __LCD12864_H__
#define __LCD12864_H__
#include <REGX51.H>
#include <INTRINS.H>
#include "font.h"
#include <string.h>
#define BUS P0  //定义数据口
extern bit LCD_RE;
extern MY_GBKFONT* gbkpointer;
extern MY_ASCIIFont* asciipointer;
typedef struct Format
{
    uchar format[3];  
}format;
sbit LCD_RST=P2^0;//定义控制引脚
sbit LCD_EN=P2^2;
sbit LCD_RW=P2^3;
sbit LCD_RS=P2^4; 
sbit LCD_CS1= P2^5;//控制右边屏幕的显示
sbit LCD_CS2= P2^6;//控制左边屏幕的显示


void Delay_us(uchar us);
void Delay_ms(uchar ms);
//basic instruction
void LCD12864_COMMAND(uchar cmd);
void Display_Control(bit entire_display);
void Set_Vertical_Address(uchar address);//选择显示在第几列范围0~63
void Set_Start_Line(uchar address);
void Set_Horizontal_Address(uchar address);//选择显示在第几行范围0~7
uchar Read_Status();
bit Check_Ready();
uchar Read_Data();
void Write_Data(uchar mdata);


//assemble function
void LCD12864_init();
void LCD12864_Set_Display_location(uchar x,uchar y);
void LCD12864_Show_chinese(const MY_GBKFONT * ptr,const char * indexptr,uchar x, uchar y);
void LCD12864_Showchar(const MY_ASCIIFont * ptr,uchar index,uchar x, uchar y);
void LCD12864_Shownum(uint num,uchar x,uchar y);
void LCD12864_ShowString(uchar * string,uchar x,uchar y);
void LCD12864_Show_chinese_String(const format*string,uchar x,uchar y);

#endif