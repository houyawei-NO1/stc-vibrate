#include   "gpio_interrupt.h"

/*************	功能说明	**************
//	GPIO_INT_Config(GPIO_P0, INT_FALL, Pin0 | Pin1 | Pin2 | Pin3);	
//	GPIO_INT_Config(GPIO_P2, INT_FALL, Pin4 | Pin5 | Pin6 | Pin7);
	//普通IO中断配置函数, 中断模式(只取其一): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. 分别是 上升沿 下降沿 低电平  高电平 中断.
请先别修改程序, 直接下载"Objects"里的"interrupt.hex"测试, 主频选择11.0592MHZ. 测试正常后再修改移植.
由于使用的中断号超过了31，所以KEIL C251编译器要拓展Keil的C代码中断号, 运行一下"拓展Keil的C代码中断号.exe"即可。

P0~P7所有IO中断测试程序.
P0.0~P0.7中断对应取反P1.0~P1.7输出指示。
P1.0~P1.7中断对应取反P0.0~P0.7输出指示。
P2.0~P2.7中断对应取反P4.0~P4.7输出指示。
P3.0~P3.7中断对应取反P4.0~P4.7输出指示。
P4.0~P4.7中断对应取反P2.0~P2.7输出指示。
P5.0~P5.7中断对应取反P4.0~P4.7输出指示。
P6.0~P6.7中断对应取反P7.0~P7.7输出指示。
P7.0~P7.7中断对应取反P6.0~P6.7输出指示。

由于IO有限, 本例子只设置了P0.0~P0.7和P2.0~P2.7的中断, 中断函数分别取反P1.0~P1.7和P4.0~P4.7来指示进入中断.
用户可以根据例子随意设置自己需要的IO中断.
主函数取反P3.3输出一个方波信号, 方便用户测试.

******************************************/

/*************	本地常量声明	**************/


/*************	本地变量声明	**************/


/*************	本地函数声明	**************/




/*************  外部函数和变量声明 *****************/
//GPIO_INT_Config(GPIO_P0, INT_FALL, Pin0 | Pin1 | Pin2 | Pin3);	//普通IO中断配置函数, 中断模式(只取其一): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. 分别是 上升沿 下降沿 低电平  高电平 中断.
//	GPIO_INT_Config(GPIO_P0, INT_RISE, Pin4 | Pin5 | Pin6 | Pin7);	//普通IO中断配置函数, 中断模式(只取其一): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. 分别是 上升沿 下降沿 低电平  高电平 中断.
////	GPIO_INT_Config(GPIO_P1, INT_FALL, PinAll);		//普通IO中断配置函数, 中断模式(只取其一): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. 分别是 上升沿 下降沿 低电平  高电平 中断.
//	GPIO_INT_Config(GPIO_P2, INT_FALL, PinAll);		//普通IO中断配置函数, 中断模式(只取其一): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. 分别是 上升沿 下降沿 低电平  高电平 中断.
////	GPIO_INT_Config(GPIO_P3, INT_FALL, PinAll);		//普通IO中断配置函数, 中断模式(只取其一): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. 分别是 上升沿 下降沿 低电平  高电平 中断.
////	GPIO_INT_Config(GPIO_P4, INT_FALL, PinAll);		//普通IO中断配置函数, 中断模式(只取其一): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. 分别是 上升沿 下降沿 低电平  高电平 中断.
////	GPIO_INT_Config(GPIO_P5, INT_FALL, PinAll);		//普通IO中断配置函数, 中断模式(只取其一): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. 分别是 上升沿 下降沿 低电平  高电平 中断.
////	GPIO_INT_Config(GPIO_P6, INT_FALL, PinAll);		//普通IO中断配置函数, 中断模式(只取其一): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. 分别是 上升沿 下降沿 低电平  高电平 中断.
////	GPIO_INT_Config(GPIO_P7, INT_FALL, PinAll);		//普通IO中断配置函数, 中断模式(只取其一): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. 分别是 上升沿 下降沿 低电平  高电平 中断.


//========================================================================
// 函数: void	GPIO_INT_Config(u8 gpio, u8 pin, u8 mode)
// 描述: IO中断初始化函数.
// 参数: gpio: 要初始化的IO组, 参数取值(只取其一): GPIO_P0, GPIO_P1, GPIO_P2, GPIO_P3, GPIO_P4, GPIO_P5, GPIO_P6, GPIO_P7, GPIO_P8, GPIO_P9.
//       mode: 中断模式,       参数取值(只取其一): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. 分别是 上升沿 下降沿 低电平  高电平 中断.
//       pin:  要初始化的引脚, 参数取值(多个值时用或操作): Pin0, Pin1, Pin2, Pin3, Pin4, Pin5, Pin6, Pin7. PinAll.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-5-20
// 备注:
//========================================================================
void	GPIO_INT_Config(u8 gpio, u8 mode, u8 pin)
{
	u8	volatile far *pt;
	u8	j;

	if(gpio > GPIO_P7)	return;	//IO口错误
	if(mode >= 4)		return;	//模式错误
	P_SW2 |= 0x80;			//访问XFR

	pt  = (unsigned char volatile far *)(0x7efd10 + gpio);	//PxINTF端口中断标志寄存器
	*pt = *pt & ~pin;	//清除中断标志

	pt  = (unsigned char volatile far *)(0x7efd30 + gpio);	//PxIM1端口中断模式配置寄存器1
	if(mode & 0x02)	j = 0xff & pin;	//设置模式
	else			j = 0;
	*pt = (*pt & ~pin) | j;

	pt  = (unsigned char volatile far *)(0x7efd20 + gpio);	//PxIM0端口中断模式配置寄存器0
	if(mode & 0x01)	j = 0xff & pin;
	else			j = 0;
	*pt = (*pt & ~pin) | j;

	pt  = (unsigned char volatile far *)(0x7efd00 + gpio);	//PxINTE端口中断使能寄存器
	*pt |= pin;				//允许IO中断
}



//========================================================================
// 函数: void	P0INT_ISR(void) interrupt 37
// 描述: P0(P0.0~P0.7)中断处理函数.
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-5-20
// 备注:
//========================================================================
void	P0INT_ISR(void) interrupt 37	//P0.0~P0.7 IO中断处理代码
{
	u8	i;
	i = P0INTF;		//读取中断标志
	P0INTF &= ~i;	//清除中断标志

	if((i & INTF_0) != 0)	//P0.0中断
	{
//		printf("中断P00:%hd\r\n",P00);
		six_f=1;
		
	}
	if((i & INTF_1) != 0)	//P0.1中断
	{
//		printf("中断P01:%hd\r\n",P01);
		three_f = 1;
	}
	if((i & INTF_2) != 0)	//P0.2中断
	{
//		printf("中断P02:%hd\r\n",P02);
		high_f = 1;
		
	}
	if((i & INTF_3) != 0)	//P0.3中断
	{
//		printf("中断P03:%hd\r\n",P03);
		low_f  =1;
		
	}
	if((i & INTF_4) != 0)	//P0.4中断
	{
		
	}
	if((i & INTF_5) != 0)	//P0.5中断
	{
		
	}
	if((i & INTF_6) != 0)	//P0.6中断
	{
		
	}
	if((i & INTF_7) != 0)	//P0.7中断
	{
		
	}
	
	
	EA = 0;
	delay_ms(20);
	EA = 1;
}

//========================================================================
// 函数: void	P1INT_ISR(void) interrupt 38
// 描述: P1(P1.0~P1.7)中断处理函数.
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-5-20
// 备注:
//========================================================================
void	P1INT_ISR(void) interrupt 38		//P1.0~P1.7 IO中断处理代码
{
	u8	i;
	i = P1INTF;		//读取中断标志
	P1INTF &= ~i;	//清除中断标志

	if((i & INTF_0) != 0)	//P1.0中断
	{
		P00 = ~P00;			//取反P0.0指示
	}
	if((i & INTF_1) != 0)	//P1.1中断
	{
		P01 = ~P01;			//取反P0.1指示
	}
	if((i & INTF_2) != 0)	//P1.2中断
	{
		P02 = ~P02;			//取反P0.2指示
	}
	if((i & INTF_3) != 0)	//P1.3中断
	{
		P03 = ~P03;			//取反P0.3指示
	}
	if((i & INTF_4) != 0)	//P1.4中断
	{
		P04 = ~P04;			//取反P0.4指示
	}
	if((i & INTF_5) != 0)	//P1.5中断
	{
		P05 = ~P05;			//取反P0.5指示
	}
	if((i & INTF_6) != 0)	//P1.6中断
	{
		P06 = ~P06;			//取反P0.6指示
	}
	if((i & INTF_7) != 0)	//P1.7中断
	{
		P07 = ~P07;			//取反P0.7指示
	}
}

//========================================================================
// 函数: void	P2INT_ISR(void) interrupt 39
// 描述: P2(P2.0~P2.7)中断处理函数.
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-5-20
// 备注:
//========================================================================
void	P2INT_ISR(void) interrupt 39		//P2.0~P2.7 IO中断处理代码
{
	u8	i;
	i = P2INTF;		//读取中断标志
	P2INTF &= ~i;	//清除中断标志

	if((i & INTF_0) != 0)	//P2.0中断
	{
		
	}
	if((i & INTF_1) != 0)	//P2.1中断
	{
		
	}
	if((i & INTF_2) != 0)	//P2.2中断
	{
		
	}
	if((i & INTF_3) != 0)	//P2.3中断
	{
		
	}
	if((i & INTF_4) != 0)	//P2.4中断
	{
//		printf("中断P24:%hd\r\n",P24);
		four_f =1;
	}
	if((i & INTF_5) != 0)	//P2.5中断
	{
//		printf("中断P25:%hd\r\n",P25);
		one_f = 1;
	}
	if((i & INTF_6) != 0)	//P2.6中断
	{
//		printf("中断P26:%hd\r\n",P26);
		five_f = 1;
	}
	if((i & INTF_7) != 0)	//P2.7中断
	{
//		printf("中断P27:%hd\r\n",P27);
		two_f = 1;
	}
	
	EA = 0;
	delay_ms(20);
	EA = 1;
}

//========================================================================
// 函数: void	P3INT_ISR(void) interrupt 40
// 描述: P3(P3.0~P3.7)中断处理函数.
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-5-20
// 备注:
//========================================================================
void	P3INT_ISR(void) interrupt 40		//P3.0~P3.7 IO中断处理代码
{
	u8	i;
	i = P3INTF;		//读取中断标志
	P3INTF &= ~i;	//清除中断标志

	if((i & INTF_0) != 0)	//P3.0中断
	{
		P40 = ~P40;			//取反P4.0指示
	}
	if((i & INTF_1) != 0)	//P3.1中断
	{
		P41 = ~P41;			//取反P4.1指示
	}
	if((i & INTF_2) != 0)	//P3.2中断
	{
		P42 = ~P42;			//取反P4.2指示
	}
	if((i & INTF_3) != 0)	//P3.3中断
	{
		P43 = ~P43;			//取反P4.3指示
	}
	if((i & INTF_4) != 0)	//P3.4中断
	{
		P44 = ~P44;			//取反P4.4指示
	}
	if((i & INTF_5) != 0)	//P3.5中断
	{
		P45 = ~P45;			//取反P4.5指示
	}
	if((i & INTF_6) != 0)	//P3.6中断
	{
		P46 = ~P46;			//取反P4.6指示
	}
	if((i & INTF_7) != 0)	//P3.7中断
	{
		P47 = ~P47;			//取反P4.7指示
	}
}

//========================================================================
// 函数: void	P4INT_ISR(void) interrupt 41
// 描述: P4(P4.0~P4.7)中断处理函数.
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-5-20
// 备注:
//========================================================================
void	P4INT_ISR(void) interrupt 41		//P4.0~P4.7 IO中断处理代码
{
	u8	i;
	i = P4INTF;		//读取中断标志
	P4INTF &= ~i;	//清除中断标志

	if((i & INTF_0) != 0)	//P4.0中断
	{
		P20 = ~P20;			//取反P2.0指示
	}
	if((i & INTF_1) != 0)	//P4.1中断
	{
		P21 = ~P21;			//取反P2.1指示
	}
	if((i & INTF_2) != 0)	//P4.2中断
	{
		P22 = ~P22;			//取反P2.2指示
	}
	if((i & INTF_3) != 0)	//P4.3中断
	{
		P23 = ~P23;			//取反P2.3指示
	}
	if((i & INTF_4) != 0)	//P4.4中断
	{
		P24 = ~P24;			//取反P2.4指示
	}
	if((i & INTF_5) != 0)	//P4.5中断
	{
		P25 = ~P25;			//取反P2.5指示
	}
	if((i & INTF_6) != 0)	//P4.6中断
	{
		P26 = ~P26;			//取反P2.6指示
	}
	if((i & INTF_7) != 0)	//P4.7中断
	{
		P27 = ~P27;			//取反P2.7指示
	}
}

//========================================================================
// 函数: void	P5INT_ISR(void) interrupt 42
// 描述: P5(P5.0~P5.4)中断处理函数.
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-5-20
// 备注:
//========================================================================
void	P5INT_ISR(void) interrupt 42		//P5.0~P5.4 IO中断处理代码
{
	u8	i;
	i = P5INTF;		//读取中断标志
	P5INTF &= ~i;	//清除中断标志

	if((i & INTF_0) != 0)	//P5.0中断
	{
		P40 = ~P40;			//取反P4.0指示
	}
	if((i & INTF_1) != 0)	//P5.1中断
	{
		P41 = ~P41;			//取反P4.1指示
	}
	if((i & INTF_2) != 0)	//P5.2中断
	{
		P42 = ~P42;			//取反P4.2指示
	}
	if((i & INTF_3) != 0)	//P5.3中断
	{
		P43 = ~P43;			//取反P4.3指示
	}
	if((i & INTF_4) != 0)	//P5.4中断
	{
		P44 = ~P44;			//取反P4.4指示
	}
	if((i & INTF_5) != 0)	//P5.5中断
	{
		P45 = ~P45;			//取反P4.5指示
	}
}

//========================================================================
// 函数: void	P6INT_ISR(void) interrupt 43
// 描述: P6(P6.0~P6.7)中断处理函数.
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-5-20
// 备注:
//========================================================================
void	P6INT_ISR(void) interrupt 43		//P6.0~P6.7 IO中断处理代码
{
	u8	i;
	i = P6INTF;		//读取中断标志
	P6INTF &= ~i;	//清除中断标志

	if((i & INTF_0) != 0)	//P6.0中断
	{
		P70 = ~P70;			//取反P7.0指示
	}
	if((i & INTF_1) != 0)	//P6.1中断
	{
		P71 = ~P71;			//取反P7.1指示
	}
	if((i & INTF_2) != 0)	//P6.2中断
	{
		P72 = ~P72;			//取反P7.2指示
	}
	if((i & INTF_3) != 0)	//P6.3中断
	{
		P73 = ~P73;			//取反P7.3指示
	}
	if((i & INTF_4) != 0)	//P6.4中断
	{
		P74 = ~P74;			//取反P7.4指示
	}
	if((i & INTF_5) != 0)	//P6.5中断
	{
		P75 = ~P75;			//取反P7.5指示
	}
	if((i & INTF_6) != 0)	//P6.6中断
	{
		P76 = ~P76;			//取反P7.6指示
	}
	if((i & INTF_7) != 0)	//P6.7中断
	{
		P77 = ~P77;			//取反P7.7指示
	}
}

//========================================================================
// 函数: void	P7INT_ISR(void) interrupt 44
// 描述: P0(P7.0~P7.7)中断处理函数.
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2020-5-20
// 备注:
//========================================================================
void	P7INT_ISR(void) interrupt 44		//P7.0~P7.7 IO中断处理代码
{
	u8	i;
	i = P7INTF;		//读取中断标志
	P7INTF &= ~i;	//清除中断标志

	if((i & INTF_0) != 0)	//P7.0中断
	{
		P60 = ~P60;			//取反P6.0指示
	}
	if((i & INTF_1) != 0)	//P7.1中断
	{
		P61 = ~P61;			//取反P6.1指示
	}
	if((i & INTF_2) != 0)	//P7.2中断
	{
		P62 = ~P62;			//取反P6.2指示
	}
	if((i & INTF_3) != 0)	//P7.3中断
	{
		P63 = ~P63;			//取反P6.3指示
	}
	if((i & INTF_4) != 0)	//P7.4中断
	{
		P64 = ~P64;			//取反P6.4指示
	}
	if((i & INTF_5) != 0)	//P7.5中断
	{
		P65 = ~P65;			//取反P6.5指示
	}
	if((i & INTF_6) != 0)	//P7.6中断
	{
		P66 = ~P66;			//取反P6.6指示
	}
	if((i & INTF_7) != 0)	//P7.7中断
	{
		P67 = ~P67;			//取反P6.7指示
	}
}

