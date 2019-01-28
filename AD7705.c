#include <STC15F2K60S2.h>
#include <intrins.h>
#include "AD7705.h"

sbit SCLK = P1^1;
sbit DIN  = P1^2;
sbit DOUT = P1^3;
sbit DRDY = P1^4;
sbit CS   = P1^5;
sbit RST  = P1^6;

sbit LED  = P1^0;

void AD7705_Write(unsigned char _data)
{
	unsigned char i;
	
	CS = 0;
	SCLK = 1;
	for(i = 0; i < 8; i++)
	{
		SCLK = 0;
		_nop_();
		if(_data & 0x80)
		{
			DIN = 1; 
		}			
        else
		{
			DIN = 0;
		}
		_nop_();
		SCLK = 1;
		_data <<= 1;
	}
	
	SCLK = 1;
	DIN  = 1;
	CS   = 1;
}

unsigned char AD7705_Read()
{
	unsigned char i, ret = 0x0;
	
	CS   = 0;
	SCLK = 1;
	for(i = 0; i < 8; i++)
	{
		SCLK = 0;
		_nop_();
		ret = (ret << 1) | DOUT;
		_nop_();
		SCLK = 1;
		_nop_();
	}
	SCLK = 1;
	CS   = 1;
	return ret;	
}


void AD7705_Init(void)
{
	unsigned char i;
	
	P1M0 = 0X00;
	P1M1 = 0X00;
	
	LED = 1;
	
	RST  = 1;
	CS   = 0;
	SCLK = 1;
	DIN  = 1;
	DOUT = 1;
	DRDY = 1;
	
	for(i = 0; i < 40; i++)
	{
		SCLK = 0;
		_nop_();
		SCLK = 1;
		_nop_();
	}
	_nop_();
	_nop_();	

	AD7705_Write(REG_CLOCK | WRITE_FLAG | ENABLE | CH_0);
	AD7705_Write(CLK_4_9152M | FS_60HZ );
	AD7705_Write(REG_SETTING | WRITE_FLAG | ENABLE | CH_0);
	AD7705_Write(ZERO_CALIBRATE | GAIN_1 | SINGAL_POLAR | OPEN_BUFFER | FSYNC);	
	
	
	AD7705_Write(REG_CLOCK | WRITE_FLAG | ENABLE | CH_1);
	AD7705_Write(CLK_4_9152M | FS_60HZ );
	AD7705_Write(REG_SETTING | WRITE_FLAG | ENABLE | CH_1);
	AD7705_Write(ZERO_CALIBRATE | GAIN_1 | SINGAL_POLAR | OPEN_BUFFER | FSYNC);
			
    CS = 1; 
	
	while(DRDY);
	LED = 0;
}

unsigned int AD7705_DATA(unsigned char channel)
{
	unsigned int ret = 0;
	unsigned char Low8Bit, High8Bit = 0;
	unsigned short channel_flag ;
	switch(channel)
	{
		case 0:
			channel_flag = CH_0;
			break;
		case 1:
			channel_flag = CH_1;
			break;
		default:
			break;
	}

	ret = 0;
	
	while(DRDY);
	AD7705_Write(REG_DATA | READ_FLAG | ENABLE | channel_flag);
	High8Bit = AD7705_Read();
	Low8Bit = AD7705_Read();
		
	while(DRDY);
	AD7705_Write(REG_DATA | READ_FLAG | ENABLE | channel_flag);
	High8Bit = AD7705_Read();
	Low8Bit = AD7705_Read();
	
	ret = (High8Bit << 8) | Low8Bit;

	return ret;
}

