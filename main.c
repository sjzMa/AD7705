#include <STC15F2K60S2.h>
#include <stdio.h>
#include <intrins.h>
#include "AD7705.h"

void Delay20ms();

int main(void)
{
	unsigned int V1, V2;
	///
	SCON  = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L   = 0xE0;		//�趨��ʱ��ֵ
	T2H   = 0xFE;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
	///
	AD7705_Init();
	
	while(1)
	{
		V1 = AD7705_DATA(0);
		V2 = AD7705_DATA(1);
		TI = 1;
		printf("%d,%d\n", V1, V2);
		TI = 0;
		Delay20ms();
	}
	
}




void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 216;
	k = 35;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
