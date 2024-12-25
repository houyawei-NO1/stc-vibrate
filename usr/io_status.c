#include "io_status.h"

void	read_iostatus(void)
{
	//data1= 0x00000000;//p3-p0
	//data2= 0x00000000;//p7-p4
	if(P00==1) data1 |=0x00000001;  else data1 &=0xFFFFFFFE;//P0
	if(P01==1) data1 |=0x00000002;  else data1 &=0xFFFFFFFD;
	if(P02==1) data1 |=0x00000004;  else data1 &=0xFFFFFFFB;
	if(P03==1) data1 |=0x00000008;  else data1 &=0xFFFFFFF7;
	if(P04==1) data1 |=0x00000010;  else data1 &=0xFFFFFFEF;
	if(P05==1) data1 |=0x00000020;  else data1 &=0xFFFFFFDF;
	if(P06==1) data1 |=0x00000040;  else data1 &=0xFFFFFFBF;
	if(P07==1) data1 |=0x00000080;  else data1 &=0xFFFFFF7F;
	
	if(P10==1) data1 |=0x00000100;  else data1 &=0xFFFFFEFF;//P1
	if(P11==1) data1 |=0x00000200;  else data1 &=0xFFFFFDFF;
	if(P12==1) data1 |=0x00000400;  else data1 &=0xFFFFFBFF;
	if(P13==1) data1 |=0x00000800;  else data1 &=0xFFFFF7FF;
	if(P14==1) data1 |=0x00001000;  else data1 &=0xFFFFEFFF;
	if(P15==1) data1 |=0x00002000;  else data1 &=0xFFFFDFFF;
	if(P16==1) data1 |=0x00004000;  else data1 &=0xFFFFBFFF;
	if(P17==1) data1 |=0x00008000;  else data1 &=0xFFFF7FFF;
	
	if(P20==1) data1 |=0x00010000;  else data1 &=0xFFFEFFFF;//P2
	if(P21==1) data1 |=0x00020000;  else data1 &=0xFFFDFFFF;
	if(P22==1) data1 |=0x00040000;  else data1 &=0xFFFBFFFF;
	if(P23==1) data1 |=0x00080000;  else data1 &=0xFFF7FFFF;
	if(P24==1) data1 |=0x00100000;  else data1 &=0xFFEFFFFF;
	if(P25==1) data1 |=0x00200000;  else data1 &=0xFFDFFFFF;
	if(P26==1) data1 |=0x00400000;  else data1 &=0xFFBFFFFF;
	if(P27==1) data1 |=0x00800000;  else data1 &=0xFF7FFFFF;
	
	if(P30==1) data1 |=0x01000000;  else data1 &=0xFEFFFFFF;//P3
	if(P31==1) data1 |=0x02000000;  else data1 &=0xFDFFFFFF;
	if(P32==1) data1 |=0x04000000;  else data1 &=0xFBFFFFFF;
	if(P33==1) data1 |=0x08000000;  else data1 &=0xF7FFFFFF;
	if(P34==1) data1 |=0x10000000;  else data1 &=0xEFFFFFFF;
	if(P35==1) data1 |=0x20000000;  else data1 &=0xDFFFFFFF;
	if(P36==1) data1 |=0x40000000;  else data1 &=0xBFFFFFFF;
	if(P37==1) data1 |=0x80000000;  else data1 &=0x7FFFFFFF;
	
	//data2
	if(P40==1) data2 |=0x00000001;  else data2 &=0xFFFFFFFE;//P4
	if(P41==1) data2 |=0x00000002;  else data2 &=0xFFFFFFFD;
	if(P42==1) data2 |=0x00000004;  else data2 &=0xFFFFFFFB;
	if(P43==1) data2 |=0x00000008;  else data2 &=0xFFFFFFF7;
	if(P44==1) data2 |=0x00000010;  else data2 &=0xFFFFFFEF;
	if(P45==1) data2 |=0x00000020;  else data2 &=0xFFFFFFDF;
	if(P46==1) data2 |=0x00000040;  else data2 &=0xFFFFFFBF;
	if(P47==1) data2 |=0x00000080;  else data2 &=0xFFFFFF7F;
	
	if(P50==1) data2 |=0x00000100;  else data2 &=0xFFFFFEFF;//P5
	if(P51==1) data2 |=0x00000200;  else data2 &=0xFFFFFDFF;
	if(P52==1) data2 |=0x00000400;  else data2 &=0xFFFFFBFF;
	if(P53==1) data2 |=0x00000800;  else data2 &=0xFFFFF7FF;
	if(P54==1) data2 |=0x00001000;  else data2 &=0xFFFFEFFF;
	if(P55==1) data2 |=0x00002000;  else data2 &=0xFFFFDFFF;
	if(P56==1) data2 |=0x00004000;  else data2 &=0xFFFFBFFF;
	if(P57==1) data2 |=0x00008000;  else data2 &=0xFFFF7FFF;
	
	if(P60==1) data2 |=0x00010000;  else data2 &=0xFFFEFFFF;//P6
	if(P61==1) data2 |=0x00020000;  else data2 &=0xFFFDFFFF;
	if(P62==1) data2 |=0x00040000;  else data2 &=0xFFFBFFFF;
	if(P63==1) data2 |=0x00080000;  else data2 &=0xFFF7FFFF;
	if(P64==1) data2 |=0x00100000;  else data2 &=0xFFEFFFFF;
	if(P65==1) data2 |=0x00200000;  else data2 &=0xFFDFFFFF;
	if(P66==1) data2 |=0x00400000;  else data2 &=0xFFBFFFFF;
	if(P67==1) data2 |=0x00800000;  else data2 &=0xFF7FFFFF;
	
	if(P70==1) data2 |=0x01000000;  else data2 &=0xFEFFFFFF;//P7
	if(P71==1) data2 |=0x02000000;  else data2 &=0xFDFFFFFF;
	if(P72==1) data2 |=0x04000000;  else data2 &=0xFBFFFFFF;
	if(P73==1) data2 |=0x08000000;  else data2 &=0xF7FFFFFF;
	if(P74==1) data2 |=0x10000000;  else data2 &=0xEFFFFFFF;
	if(P75==1) data2 |=0x20000000;  else data2 &=0xDFFFFFFF;
	if(P76==1) data2 |=0x40000000;  else data2 &=0xBFFFFFFF;
	if(P77==1) data2 |=0x80000000;  else data2 &=0x7FFFFFFF;

}