#include    "ntc_sampling.h"

#ifdef BUBBLE_SORT  //ʹ��ð������ȥ�����ֵ�����ֵ�����м�ƽ��ֵ
u16 ADC_Buffer[16];
#endif

/******************* AD���ú��� *******************/
void	ADC_config(void)
{
	ADC_InitTypeDef		ADC_InitStructure;		//�ṹ����
	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
	ADC_InitStructure.ADC_CsHold    = 1;		//ADC ͨ��ѡ�񱣳�ʱ����� 0,1(Ĭ��),2,3
	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X16T;		//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//��ʼ��
	ADC_PowerControl(ENABLE);						//ADC��Դ����, ENABLE��DISABLE
	NVIC_ADC_Init(DISABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

/***********************************
��ѯ��ʽ��һ��ADC, chnΪͨ����, chn=0~7��ӦP1.0~P1.7, chn=8~14��ӦP0.0~P0.6, chn=15��ӦBandGap��ѹ.
***********************************/
float NTC_ADC_convert(u8 chn)
{
	u16	j;
	u8	k;		//ƽ��ֵ�˲�ʱʹ��
    float vADC;

	Get_ADCResult(chn);		//����i=0~15,��ѯ��ʽ��һ��ADC, �л�ͨ�����һ��ת���������. ����������ݵĲд��ѹӰ��.
	Get_ADCResult(chn);    //����i=0~15,��ѯ��ʽ��һ��ADC, �л�ͨ����ڶ���ת���������. ����������ݵĲд��ѹӰ��.

#ifdef BUBBLE_SORT  //ʹ��ð������ȥ�����ֵ�����ֵ�����м�ƽ��ֵ

	for(k=0; k<16; k++)	ADC_Buffer[k] = Get_ADCResult(chn);
	BubbleSort(ADC_Buffer,16);  //ð������
	for(k=4, j=0; k<12; k++) j += ADC_Buffer[k];  //ȡ�м�8������
	j >>= 3;		// ����3λ(��8)����ƽ��

#else   //�����ۼӣ���ƽ��ֵ������Ҫ�Ļ��ɽ� SUM_LENGTH ����ֵ��Ϊ 1 ��

	for(k=0, j=0; k<SUM_LENGTH; k++)	j += Get_ADCResult(chn);	// �����ۼӺ� ����0~15,��ѯ��ʽ��һ��ADC, ����ֵ���ǽ��
	j = j / SUM_LENGTH;		// ��ƽ��

#endif
    
    printf("12bit: ADC%02d=%04u  ",chn,j);  //���ADCֵ
    
    vADC = ((float)j * 5.0 / 4096);  //����NTC��ѹ, Vref=5.0V
//    printf("��ѹ:%fV  ",vADC);
    
    vADC = CalculationTemperature(j); //�����¶�ֵ
//    printf("T=%f ��C\r\n",vADC);
	return vADC;

    //����������
//	for(k=0, j=0; k<16; k++)	j += Get_ADCResult(chn);	// �����ۼӺ� ����0~15,��ѯ��ʽ��һ��ADC, ����ֵ���ǽ��
//	vADC = j / 4;		// 12λADC������16����ֵ�ۼӺ����4�������Ϊ14λ������ADC��ֵ
//    printf("14bit: ADC=%f  ",vADC);
//    vADC = (vADC * 5.0 / 16384);  //����NTC��ѹ, Vref=2.5V
//    printf("P13=%fV  ",vADC);
	
}


/******************** �����¶� *********************/

#define     Vref     5.0
float CalculationTemperature(u16 adc)
{
    float Temperature=0.0;
    float R2=0.0;
    float R1=10000.0;
    float T2=298.15;//273.15+25;
    float B=3950.0;//3435.0-��3950
    float K=273.15;
    float R2V=0.0;

    R2V=(adc*(Vref/4096));    //12λADC
    R2=(R2V*R1)/(Vref-R2V);
	printf("Rntc=%f ��\r\n",R2);
    Temperature=1.0/(1.0/T2+log(R2/R1)/B)-K+0.5;

    return Temperature;
}


#ifdef BUBBLE_SORT  //ʹ��ð������
//========================================================================
// ����: void DataSwap(u16* data1, u16* data2)
// ����: ���ݽ���������
// ����: data1,data2 Ҫ����������.
// ����: none.
// �汾: VER1.0
// ����: 2021-9-27
// ��ע: 
//========================================================================
void DataSwap(u16* data1, u16* data2)
{
	u16 temp;
	temp = *data1;
	*data1 = *data2;
	*data2 = temp;
}

//========================================================================
// ����: void BubbleSort(u16* pDataArry, u8 DataNum)
// ����: ð����������
// ����: pDataArry��Ҫ��������飬DataNum��Ҫ��������ݸ���.
// ����: none.
// �汾: VER1.0
// ����: 2021-9-27
// ��ע: 
//========================================================================
void BubbleSort(u16* pDataArry, u8 DataNum)
{
	bit flag;
	u8 i,j;
	for(i=0;i<DataNum-1;i++)
	{
		flag = 0;
		for(j=0;j<DataNum-i-1;j++)
		{
			if(pDataArry[j] > pDataArry[j+1])
			{
				flag = 1;
				DataSwap(&pDataArry[j], &pDataArry[j+1]);
			}
		}
		if(!flag)  //��һ�ֱȽ��в��������ݽ��������˳�����
		{
			break;
		}
	}
}
#endif