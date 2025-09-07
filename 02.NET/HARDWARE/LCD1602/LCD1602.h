#ifndef __LCD1602A__H
#define __LCD1602A__H

#include "stm32f10x_it.h"  
#include "delay.h"
/***************************�����Լ���Ӳ���������޸�*****************************/
#define LCD_RS_Set()    GPIO_SetBits( GPIOB, GPIO_Pin_12 )//1602������/ָ��ѡ�������
#define LCD_RS_Clr()    GPIO_ResetBits( GPIOB, GPIO_Pin_12 )

#define LCD_RW_Set()    GPIO_SetBits( GPIOB, GPIO_Pin_13 )//1602�Ķ�д������
#define LCD_RW_Clr()    GPIO_ResetBits( GPIOB, GPIO_Pin_13 )

#define LCD_EN_Set()    GPIO_SetBits( GPIOB, GPIO_Pin_14 )//1602��ʹ�ܿ�����
#define LCD_EN_Clr()    GPIO_ResetBits( GPIOB, GPIO_Pin_14 )
 
// #define DATAOUT( x ) GPIO_Write( GPIOA, x ) //1602��8�����ݿ�����
 
void WriteData(u8 data);
void LCD1602_GPIO(void);
void LCD1602_Wait_Ready(void);
void LCD1602_Write_Cmd(u8 cmd);
void LCD1602_Write_Dat(u8 dat);
void LCD1602_ClearScreen(void);
void LCD1602_Set_Cursor(u8 x, u8 y);
void LCD1602_Show_Str(u8 x, u8 y, u8 *str);
void LCD1602_Init(void);

#endif
