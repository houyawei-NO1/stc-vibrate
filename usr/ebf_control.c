#include "ebf_control.h"


u16 code Sound_Fre[4][7]=          //…˘“Ùø‚
{                           
        45627        ,40677        ,36253        ,34285        ,30534        ,27210        ,24242,//µÕ“Ù
        22900        ,20408        ,18181        ,17167        ,15286        ,13620        ,12133,//÷–“Ù
        11450        ,10204        ,9022         ,8583         ,7648         ,6814         ,6069,//∏ﬂ“Ù
        5730         ,5106         ,4548         ,4293         ,3825         ,3408         ,3036,//≥¨∏ﬂ“Ù
} ;        

void	controlbeep(void)
{

	if( (low_f==0) && (high_f==1) && (six_f==0) && (five_f==0) && (four_f==0) && (three_f==0) && (two_f==0) && (one_f==0)) //diyin sol
		{
		PWM_config(Sound_Fre[0][4]);
		printf("diyin sol\r\n");
		}
	if( (low_f==0) && (high_f==1) && (six_f==0) && (five_f==0) && (four_f==0) && (three_f==0) && (two_f==0) && (one_f==1)) //diyin la
		{
		PWM_config(Sound_Fre[0][5]);
		printf("diyin 2\r\n");
		}
	if( (low_f==0) && (high_f==1) && (six_f==0) && (five_f==0) && (four_f==0) && (three_f==0) && (two_f==1) && (one_f==1)) //diyin si
		{
		PWM_config(Sound_Fre[0][6]);
		printf("diyin 3\r\n");
		}
	
	if( (low_f==1) && (high_f==1) && (six_f==0) && (five_f==0) && (four_f==0) && (three_f==1) && (two_f==1) && (one_f==1)) //zhongyin do
		{
		PWM_config(Sound_Fre[1][0]);
		printf("yin 1\r\n");
		}
	if( (low_f==1) && (high_f==1) && (six_f==0) && (five_f==0) && (four_f==1) && (three_f==1) && (two_f==1) && (one_f==1)) //zhongyin re
		{
		PWM_config(Sound_Fre[1][1]);
		printf("yin 2\r\n");
		}
	if( (low_f==1) && (high_f==1) && (six_f==0) && (five_f==1) && (four_f==1) && (three_f==1) && (two_f==1) && (one_f==1)) //zhongyin mi
		{
		PWM_config(Sound_Fre[1][2]);  
		printf("yin 3\r\n");
		}
	if( (low_f==1) && (high_f==1) && (six_f==1) && (five_f==0) && (four_f==0) && (three_f==1) && (two_f==1) && (one_f==1))//zhongyin fa
		{
		PWM_config(Sound_Fre[1][3]);  
		printf("yin 4\r\n");
		}
	if( (low_f==1) && (high_f==1) && (six_f==0) && (five_f==0) && (four_f==0) && (three_f==0) && (two_f==0) && (one_f==0)) //zhongyin sol
		{
		PWM_config(Sound_Fre[1][4]);
		printf("yin 5\r\n");
		}
	if( (low_f==1) && (high_f==1) && (six_f==0) && (five_f==0) && (four_f==0) && (three_f==0) && (two_f==0) && (one_f==1))//zhongyin la
		{
		PWM_config(Sound_Fre[1][5]);
		printf("yin 6\r\n");
		}
	if( (low_f==1) && (high_f==1) && (six_f==0) && (five_f==0) && (four_f==0) && (three_f==0) && (two_f==1) && (one_f==1)) //zhongyin si
		{
		PWM_config(Sound_Fre[1][6]);
		printf("yin 7\r\n");
		}
	
	if( (low_f==1) && (high_f==0) && (six_f==0) && (five_f==0) && (four_f==0) && (three_f==1) && (two_f==1) && (one_f==1)) //gaoyiin do
		{
		PWM_config(Sound_Fre[2][0]);
		printf("gaoyin 1\r\n");
		}
	if( (low_f==1) && (high_f==0) && (six_f==0) && (five_f==0) && (four_f==1) && (three_f==1) && (two_f==1) && (one_f==1)) //gaoyiin re
		{
		PWM_config(Sound_Fre[2][1]);
		printf("gaoyin 2\r\n");
		}
	if( (low_f==1) && (high_f==0) && (six_f==0) && (five_f==1) && (four_f==1) && (three_f==1) && (two_f==1) && (one_f==1)) //gaoyiin mi
		{
		PWM_config(Sound_Fre[2][2]);  
		printf("gaoyin 3\r\n");
		}
	if( (low_f==1) && (high_f==0) && (six_f==1) && (five_f==0) && (four_f==0) && (three_f==0) && (two_f==0) && (one_f==1))//gaoyiin fa
		{
		PWM_config(Sound_Fre[2][3]);  
		printf("gaoyin 4\r\n");
		}
	if( (low_f==1) && (high_f==0) && (six_f==1) && (five_f==0) && (four_f==0) && (three_f==0) && (two_f==0) && (one_f==0)) //gaoyiin sol
		{
		PWM_config(Sound_Fre[2][4]);
		printf("gaoyin 5\r\n");
		}
	if( (low_f==1) && (high_f==0) && (six_f==0) && (five_f==0) && (four_f==1) && (three_f==0) && (two_f==0) && (one_f==1)) //gaoyiin la
		{
		PWM_config(Sound_Fre[2][5]);
		printf("gaoyin 6\r\n");
		}
	if( (low_f==1) && (high_f==0) && (six_f==0) && (five_f==1) && (four_f==0) && (three_f==0) && (two_f==1) && (one_f==0)) //gaoyiin si
		{
		PWM_config(Sound_Fre[2][6]);
		printf("gaoyin 7\r\n");
		}
		
	if( (low_f==1) && (high_f==1) && (six_f==1) && (five_f==1) && (four_f==1) && (three_f==1) && (two_f==1) && (one_f==1)) //zhongyin re
		{
		PWM_config(0);
		printf("turn off\r\n");
		}
//		printf("low_f:%hd\r\n",low_f);
//		printf("high_f:%hd\r\n",high_f);
//		printf("six_f:%hd\r\n",six_f);
//		printf("five_f:%hd\r\n",five_f);
//		printf("four_f:%hd\r\n",four_f);
//		printf("three_f:%hd\r\n",three_f);
//		printf("two_f:%hd\r\n",two_f);
//		printf("one_f:%hd\r\n",one_f);
		
}