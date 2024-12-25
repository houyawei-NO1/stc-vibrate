#include	"\..\library\config.h"
#include	"\..\library\STC32G_GPIO.h"
#include	"\..\library\STC32G_Delay.h"
#include	"\..\library\STC32G_UART.h"
//#include	"\..\library\STC32G_ADC.h"
#include	"\..\library\STC32G_PWM.h"
#include	"\..\library\STC32G_NVIC.h"//�ж�
#include	"\..\library\STC32G_Switch.h"//���ܽ��л�
//#include   "gpio_interrupt.h"
//#include   "ebf_control.h"
#include    "ntc_sampling.h"
#include    "io_status.h"


//����ʱ, ѡ��ʱ�� 12MHz (�����������ļ�"config.h"���޸�).

/*************	���س�������	**************/




/*************	���ر�������	**************/

PWMx_Duty PWMA_Duty;
bit PWM1_Flag;
float set_wendu;
float ntc_wendu;
u8 switch_data;
u32 data1;//p3-p0
u32 data2;//p7-p4
/*************	���غ�������	**************/
void	PWM_config(u16 Fre);
void	UART_config(void);
void    GPIO_config(void);
void	controlbeep(void);
float    NTC_ADC_convert(u8 chn);
void 	temp_control_switch(void);
/*************  �ⲿ�����ͱ������� *****************/



//========================================================================
// ����: main
// ����: �û�Ӧ�ó���.
// ����: None.
// ����: None.
// �汾: V1.0, 2020-09-23
//========================================================================
void main(void)
{
//	u8	i;
//	u16	j;
	

	WTST = 0;		//���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
	EAXSFR();		//��չSFR(XFR)����ʹ�� 
	CKCON = 0;      //��߷���XRAM�ٶ�

	GPIO_config();
	UART_config();
	ADC_config();
	EA = 1;

	set_wendu=0.0;
	switch_data=0;
	data1 = 0x00000000;
	data2 = 0x00000000;
	printf("�����϶���������53���񶯲���\r\n");	//UART����һ���ַ���
	
	while(1)
	{
		delay_ms(500);
		
		read_iostatus();
		printf("%lx;%lx\r\n",data1,data2);	
//		printf("P40:%lx  \r\n",P40);	
		//temp_control_switch();
	}
}



//	P1_MODE_IN_HIZ(GPIO_Pin_5);		//P1.5����Ϊ��������
//P1_MODE_IN_HIZ(GPIO_Pin_All);		//P1.0~P1.7 ����Ϊ��������
//	P0_MODE_IN_HIZ(GPIO_Pin_LOW | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);	//P0.0~P0.6 ����Ϊ��������
//	P1_MODE_IN_HIZ(GPIO_Pin_All);		//P1.0~P1.7 ����Ϊ��������
//	P3_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);	//P3.0,P3.1 ����Ϊ׼˫���
//������PWM���ܺ�������Զ�����Ϊ׼˫���ģʽ��

/******************* IO���ú��� *******************/
void	GPIO_config(void)
{
//	P1_MODE_IN_HIZ(GPIO_Pin_5);		//P1.5����Ϊ��������  adc 
//	P1_MODE_OUT_PP(GPIO_Pin_4);		//P1.4 ����Ϊ���� �̵���
//	P3_MODE_IO_PU(GPIO_Pin_All);			//P3.x����Ϊ׼˫���  ���뿪��
//	P14=0;
	P0_MODE_IO_PU(GPIO_Pin_All);
	P1_MODE_IO_PU(GPIO_Pin_All);
	P2_MODE_IO_PU(GPIO_Pin_All);
	P2_MODE_IO_PU(GPIO_Pin_All);
	P3_MODE_IO_PU(GPIO_Pin_All);
	P4_MODE_IO_PU(GPIO_Pin_All);
	P5_MODE_IO_PU(GPIO_Pin_All);
	P6_MODE_IO_PU(GPIO_Pin_All);
	P7_MODE_IO_PU(GPIO_Pin_All);
}

/***************  ���ڳ�ʼ������ *****************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer1,BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������ UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}

/***************  PWM��ʼ������ *****************/
void	PWM_config(u16 Fre)
{
	PWMx_InitDefine		PWMx_InitStructure;
	
	PWMx_InitStructure.PWM_Period   = Fre;							//����ʱ��,   0~65535
	PWMA_Duty.PWM1_Duty = PWMx_InitStructure.PWM_Period / 2;

	PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty    = PWMA_Duty.PWM1_Duty;	//PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect   = ENO1P;
	PWM_Configuration(PWM1, &PWMx_InitStructure);				//��ʼ��PWM1

	PWMx_InitStructure.PWM_DeadTime = 0;								//��������������, 0~255
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//�����ʹ��, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;				//ʹ�ܼ�����, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);				//��ʼ��PWMͨ�üĴ���,  PWMA,PWMB
	
	
	PWM1_USE_P10P11();

	NVIC_PWM_Init(PWMA,DISABLE,Priority_0);

}

void 	temp_control_switch()
{
		ntc_wendu = NTC_ADC_convert(5);		//���͹̶�ͨ��ADֵ
		printf("NTC�����¶�Ϊ%f ��C\r\n",ntc_wendu);
		if(ntc_wendu<-70.0) 
		{
			printf("û��ntc�����״̬���رռ̵���\r\n");
			P14=0;
			return;
		}
//		printf("one_key:%hd\r\n",one_key);
//		printf("two_key:%hd\r\n",two_key);
//		printf("three_key:%hd\r\n",three_key);
//		printf("four_key:%hd\r\n",four_key);
//		printf("mode_key:%hd\r\n",mode_key);
//		P14 = ~P14;
//		P14=0;
//		printf("P14:%hd\r\n",P14);
//	if(mode_key==0) switch_data |= 0x10;
//		else switch_data &= 0x0F;
	if(one_key==0) switch_data |= 0x8;
		else switch_data &= 0x7;
	if(two_key==0) switch_data |= 0x4;
		else switch_data &= 0xB;
	if(three_key==0) switch_data |= 0x2;
		else switch_data &= 0xD;
	if(four_key==0) switch_data |= 0x1;
		else switch_data &= 0xE;
	printf("switch_data:%x\r\n",switch_data);
	
	if(switch_data ==0x0 ) set_wendu=-15.0;//1
	else if(switch_data ==0x1 ) set_wendu=-10.0;//2
	else if(switch_data ==0x2 ) set_wendu=-5.0;//3
	else if(switch_data ==0x3 ) set_wendu=0.0;//4
	else if(switch_data ==0x4 ) set_wendu=5.0;//5
	else if(switch_data ==0x5 ) set_wendu=10.0;//6
	else if(switch_data ==0x6 ) set_wendu=15.0;//7
	else if(switch_data ==0x7 ) set_wendu=20.0;//8
	else if(switch_data ==0x8 ) set_wendu=25.0;//9
	else if(switch_data ==0x9 ) set_wendu=30.0;//10
	else if(switch_data ==0xa ) set_wendu=35.0;//11
	else if(switch_data ==0xb ) set_wendu=40.0;//12
	else if(switch_data ==0xc ) set_wendu=45.0;//13
	else if(switch_data ==0xd ) set_wendu=50.0;//14
	else if(switch_data ==0xe ) set_wendu=60.0;//15
	else if(switch_data ==0xf ) set_wendu=70.0;//16
	printf("�趨�¶�Ϊ%f ��C\r\n",set_wendu);
	
	if(mode_key==0)//�������Ǽ���ģʽ
	{
		printf("����ģʽ\r\n");
		if(ntc_wendu<set_wendu) P14=1;
		else P14=0;
	}
	else if(mode_key==1)//�������ǽ���ģʽ
	{
		printf("����ģʽ\r\n");
		if(ntc_wendu>set_wendu) P14=1;
		else P14=0;
	}
}

