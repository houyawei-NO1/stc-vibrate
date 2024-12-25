/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#ifndef		__CONFIG_H
#define		__CONFIG_H

/*********************************************************/

//#define MAIN_Fosc		22118400L	//定义主时钟
#define MAIN_Fosc		12000000L	//定义主时钟
//#define MAIN_Fosc		11059200L	//定义主时钟
//#define MAIN_Fosc		 5529600L	//定义主时钟
//#define MAIN_Fosc		24000000L	//定义主时钟


/*********************************************************/

#include "type_def.h"
#include "stc32g.h"
#include <stdlib.h>
#include <stdio.h>

//extern bit one_f,two_f,three_f,four_f,five_f,six_f,low_f,high_f;
extern void	PWM_config(u16 Fre);

sbit one_f=P2^5;
sbit two_f=P2^7;
sbit three_f=P0^1;
sbit four_f=P2^4;
sbit five_f=P2^6;
sbit six_f=P0^0;
sbit low_f=P0^3;
sbit high_f=P0^2;

sbit one_key=P3^6;
sbit two_key=P3^5;
sbit three_key=P3^4;
sbit four_key=P3^3;
sbit mode_key=P3^2;

#endif
