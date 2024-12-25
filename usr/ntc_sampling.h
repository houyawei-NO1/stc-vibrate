#ifndef	__NTC_SAMPLING_H
#define	__NTC_SAMPLING_H

#include	"\..\library\STC32G_ADC.h"
#include	"\..\library\STC32G_NVIC.h"//�ж�
#include 	<math.h>

#define SUM_LENGTH	16	/* ƽ��ֵ�������� ���ֵ16������Ҫ�Ļ��ɽ�����ֵ��Ϊ 1 ��*/

#define BUBBLE_SORT     //����ʹ��ð������ȥ�����ֵ�����ֵ�����м�ƽ��ֵ������Ҫ�Ļ����δ��У�



void  	ADC_config(void);
extern float    NTC_ADC_convert(u8 chn);	//chn=0~7��ӦP1.0~P1.7, chn=8~14��ӦP0.0~P0.6, chn=15��ӦBandGap��ѹ
void 	BubbleSort(u16* pDataArry, u8 DataNum);
float 	CalculationTemperature(u16 adc);
void 	DataSwap(u16* data1, u16* data2);
void 	BubbleSort(u16* pDataArry, u8 DataNum);

#endif