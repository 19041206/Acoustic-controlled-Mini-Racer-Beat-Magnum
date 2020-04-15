
#ifndef LD_CHIP_H
#define LD_CHIP_H

#include "sys.h"
#include "USER_HARDWARE_CONFIG.h"


#define LD_MODE_IDLE		  0x00
#define LD_MODE_ASR_RUN		0x08
#define LD_MODE_MP3		 	  0x40


//	�������״̬����������¼������������ASRʶ������е��ĸ�״̬
#define LD_ASR_NONE				  0x00	//	��ʾû������ASRʶ��
#define LD_ASR_RUNING			  0x01	//	��ʾLD3320������ASRʶ����
#define LD_ASR_FOUNDOK			0x10	//	��ʾһ��ʶ�����̽�������һ��ʶ����
#define LD_ASR_FOUNDZERO 		0x11	//	��ʾһ��ʶ�����̽�����û��ʶ����
#define LD_ASR_ERROR	 		  0x31	//	��ʾһ��ʶ��������LD3320оƬ�ڲ����ֲ���ȷ��״̬


#define LD_PLL_11			  (u8)((CLK_IN/2.0)-1)
#define LD_PLL_MP3_19		0x0f
#define LD_PLL_MP3_1B		0x18
#define LD_PLL_MP3_1D   	(u8)(((90.0*((LD_PLL_11)+1))/(CLK_IN))-1)

#define LD_PLL_ASR_19 		(u8)(CLK_IN*32.0/(LD_PLL_11+1) - 0.51)
#define LD_PLL_ASR_1B 		0x48
#define LD_PLL_ASR_1D 		0x1f


#define        RESUM_OF_MUSIC               0x01
#define        CAUSE_MP3_SONG_END           0x20

#define        MASK_INT_SYNC				0x10
#define        MASK_INT_FIFO				0x04
#define    	   MASK_AFIFO_INT				0x01
#define        MASK_FIFO_STATUS_AFULL		0x08


void LD_reset(void);
void LD_Init_Common(void);
void LD_Init_ASR(void);
void LD_ReloadMp3Data(void);
void LD_ReloadMp3Data_2(void);
u8 LD_ProcessAsr(u32 RecogAddr);
void LD_AsrStart(void);
u8 LD_AsrRun(void);
u8 LD_AsrAddFixed(void);
u8 LD_GetResult(void);
void LD_ReadMemoryBlock(u8 dev, u8 * ptr, u32 addr, u8 count);
void LD_WriteMemoryBlock(u8 dev, u8 * ptr, u32 addr, u8 count);
extern u8  nLD_Mode;
void  LD3320_delay(unsigned long uldata);

#endif

