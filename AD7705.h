#ifndef __AD7705_H
#define __AD7705_H


//COMMON Regsiter
#define REG_SETTING          0x10 // _ 0 0 1 _ _ _ _
#define REG_CLOCK            0x20 // _ 0 1 0 _ _ _ _
#define REG_DATA             0x30 // _ 0 1 1 _ _ _ _
//RW_FLAG
#define READ_FLAG            0x08 // _ _ _ _ 1 _ _ _
#define WRITE_FLAG           0x00 // _ _ _ _ 0 _ _ _
//ENABLE
#define ENABLE               0x00 // _ _ _ _ _ 0 _ _
#define DISENABLE            0x04 // _ _ _ _ _ 1 _ _
//Channel Regsiter
#define CH_0                 0x00 // _ _ _ _ _ _ 0 0
#define CH_1                 0x01 // _ _ _ _ _ _ 0 1

//Clock Regsiter
//Note : CANNOT MIX
///-----------Type 1--------------
#define CLK_4_9152M          0x0C // _ _ _ _ 1 1 _ _
#define CLK_2_4576M          0x04 // _ _ _ _ 0 1 _ _
#define FS_50HZ              0x00 // _ _ _ _ _ _ 0 0
#define FS_60HZ              0x01 // _ _ _ _ _ _ 0 1
#define FS_250HZ             0x02 // _ _ _ _ _ _ 1 0
#define FS_500HZ             0x03 // _ _ _ _ _ _ 1 1
///-----------Type 2--------------
#define CLK_2_0000M          0x08 // _ _ _ _ 1 0 _ _ 
#define CLK_1_0000M          0x00 // _ _ _ _ 0 0 _ _
#define FS_20HZ              0x00 // _ _ _ _ _ _ 0 0
#define FS_25HZ              0x01 // _ _ _ _ _ _ 0 1
#define FS_100HZ             0x02 // _ _ _ _ _ _ 1 0
#define FS_200HZ             0x03 // _ _ _ _ _ _ 1 1

//SETTING Regsiter
#define NO_CALIBRATE         0x00 // 0 0 _ _ _ _ _ _
#define SELF_CALIBRATE       0x40 // 0 1 _ _ _ _ _ _
#define ZERO_CALIBRATE       0x80 // 1 0 _ _ _ _ _ _
#define FULL_CALIBRATE       0xC0 // 1 1 _ _ _ _ _ _

#define GAIN_1               0x00 // _ _ 0 0 0 _ _ _
#define GAIN_2               0x08 // _ _ 0 0 1 _ _ _
#define GAIN_4               0x10 // _ _ 0 1 0 _ _ _
#define GAIN_8               0x18 // _ _ 0 1 1 _ _ _
#define GAIN_16              0x20 // _ _ 1 0 0 _ _ _
#define GAIN_32              0x28 // _ _ 1 0 1 _ _ _
#define GAIN_64              0x30 // _ _ 1 1 0 _ _ _
#define GAIN_128             0x38 // _ _ 1 1 1 _ _ _

#define DOUBLE_POLAR         0x00 // _ _ _ _ _ 0 _ _
#define SINGAL_POLAR         0x04 // _ _ _ _ _ 1 _ _

#define CLOSE_BUFFER         0x00 // _ _ _ _ _ _ 0 _ 
#define OPEN_BUFFER          0x02 // _ _ _ _ _ _ 1 _     

#define FSYNC                0x00 // _ _ _ _ _ _ _ 0

void AD7705_Init(void);
void AD7705_Write(unsigned char _data);
unsigned int AD7705_DATA(unsigned char channel);

#endif

