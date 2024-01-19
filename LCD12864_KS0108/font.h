#ifndef __FONT_H__
#define __FONT_H__

#include <REGX51.H>
typedef struct FNT_GBK16                 // 汉字字模数据结构
{
    signed char Index[4];               // 汉字内码索引，由于UTF-8编码一个汉字要3个字节，所以索引长度为4，最后放\0
    char Msk[32];                       // 点阵码数据
}MY_GBKFONT;
typedef struct FNT_ASCII                 // ASCII字模数据结构
{
    char Index;                         // 汉字内码索引,编码一个ascii只需要一个字节
		char Msk[16];                          // 点阵码数据
}MY_ASCIIFont;

extern MY_GBKFONT code GBKTABLE[];
extern MY_ASCIIFont code ASCIITABLE[];
extern uint GBK_size;
extern uint ASCII_size;
#endif