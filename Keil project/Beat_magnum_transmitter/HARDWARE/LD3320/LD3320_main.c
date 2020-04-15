#include    <stm32f10x.h>
#include "stm32f10x_conf.h"
#include "LDchip.h"
#include "Reg_RW.h"
#include "USER_HARDWARE_CONFIG.h"



extern u8  tmp_buf[33];	
extern u8  Send_State;


/************************************************************************************
//	nAsrStatus ������main�������б�ʾ�������е�״̬������LD3320оƬ�ڲ���״̬�Ĵ���
//	LD_ASR_NONE:		��ʾû������ASRʶ��
//	LD_ASR_RUNING��		��ʾLD3320������ASRʶ����
//	LD_ASR_FOUNDOK:		��ʾһ��ʶ�����̽�������һ��ʶ����
//	LD_ASR_FOUNDZERO:	��ʾһ��ʶ�����̽�����û��ʶ����
//	LD_ASR_ERROR:		��ʾһ��ʶ��������LD3320оƬ�ڲ����ֲ���ȷ��״̬
*********************************************************************************/
u8 nAsrStatus = LD_ASR_NONE;	

void LD3320_Init(void);

u8 RunASR(void);
void ProcessInt0(void);
void LD3320_EXTI_Cfg(void);
void LD3320_Spi_cfg(void);
void LD3320_GPIO_Cfg(void);

/***********************************************************
* ��    �ƣ� LD3320_main(void)
* ��    �ܣ� ������LD3320�������
**********************************************************/ 

void  LD3320_main(void)
{
	u8 nAsrRes=0;
 	switch(nAsrStatus)
		{
			case LD_ASR_RUNING:
												break;
			case LD_ASR_ERROR:		
											tmp_buf[0]='D';	
												break;
			case LD_ASR_NONE:
											nAsrStatus=LD_ASR_RUNING;
											if (RunASR()==0)	//	����һ��ASRʶ�����̣�ASR��ʼ����ASR��ӹؼ��������ASR����
											{		
												nAsrStatus = LD_ASR_ERROR;
											}
											break;

			case LD_ASR_FOUNDOK:
											 nAsrRes = LD_GetResult( );	//	һ��ASRʶ�����̽�����ȥȡASRʶ����	
												 switch(nAsrRes)		   
												  {
													  case CODE_YDCF:			/*Beat magnum*/
														tmp_buf[0] = NRF_COMMAND_YDCF;	
																						 break;
														case CODE_QJ:	      /*Go forward*/
														tmp_buf[0] = NRF_COMMAND_QJ;															
																						 break;
														case CODE_T:		    /*Stop*/
														tmp_buf[0] = NRF_COMMAND_T;															
																						break;
														case CODE_HT:		    /*Go backward*/
														tmp_buf[0] = NRF_COMMAND_HT;																								
																						break;
														case CODE_JS:       /*Accelerate*/
														tmp_buf[0] = NRF_COMMAND_JS;																								
																						break;
														case CODE_XZ:       /*Turn left*/
														tmp_buf[0] = NRF_COMMAND_XZ;																								
																						break;
														case CODE_XY:       /*Turn rught*/
														tmp_buf[0] = NRF_COMMAND_XY;																							
																						break;
														default:break;
													}

												nAsrStatus = LD_ASR_NONE;
											break;
			case LD_ASR_FOUNDZERO:
			default:
								nAsrStatus = LD_ASR_NONE;
								break;
			}

}
/***********************************************************
* ��    �ƣ�LD3320_Init(void)
* ��    �ܣ�ģ�������˿ڳ�ʼ����
**********************************************************/ 
void LD3320_Init(void)
{
	LD3320_GPIO_Cfg();	
	LD3320_EXTI_Cfg();
	LD3320_Spi_cfg();	 

	LD_reset();
}

/***********************************************************
* ��    �ƣ�	LD3320_delay(unsigned long uldata)
* ��    �ܣ�	�Ǿ�ȷ��ʱ
**********************************************************/ 
void Delay_( int i)
 {     
    while( i--)
       {	

        }
 }	

 void  LD3320_delay(unsigned long uldata)
{
	unsigned int j  =  0;
	unsigned int g  =  0;
	for (j=0;j<5;j++)
	{
		for (g=0;g<uldata;g++)
		{
			Delay_(10);
		}
	}
}

/***********************************************************
* ��    �ƣ�	RunASR(void)
* ��    �ܣ�	����ASR
**********************************************************/ 
u8 RunASR(void)
{
	u8 i=0;
	u8 asrflag=0;
	for (i=0; i<5; i++)			//	��ֹ����Ӳ��ԭ����LD3320оƬ����������������һ������5������ASRʶ������
	{
		LD_AsrStart();			//��ʼ��ASR
		LD3320_delay(20);
		if (LD_AsrAddFixed()==0)	
		{
			LD_reset();			
			LD3320_delay(20);			
			continue;
		}

		LD3320_delay(10);

		if (LD_AsrRun() == 0)
		{
			LD_reset();			
			LD3320_delay(20);			
			continue;
		}

		asrflag=1;
		break;					
	}

	return asrflag;
}


void LD3320_GPIO_Cfg(void)
{	
	 GPIO_InitTypeDef GPIO_InitStructure;
	   //io������
		//LD_CS	/LD_RST /LD_A0
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =PIN_LD_CE|PIN_LD_RST|PIN_LD_A0;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOA,&GPIO_InitStructure);

		GPIO_SetBits(PORT_LD_A0,PIN_LD_A0);	/*A0Ĭ������*/
}
/***********************************************************
* ��    �ƣ�LD3320_Spi_cfg(void)
* ��    �ܣ�����SPI���ܺͶ˿ڳ�ʼ��
**********************************************************/ 
void LD3320_Spi_cfg(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	   
  
	GPIO_InitStructure.GPIO_Pin = PIN_LD_SPIS;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(PORT_LD_SPIS, &GPIO_InitStructure);
  
	//P0/P1/P2 ��������SPIͨ��,��ʹ�����ģ��SPIͨ��
	GPIO_InitStructure.GPIO_Pin = PIN_LD_SPI_SCK | PIN_LD_SPI_MOSI;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(PORT_LD_SPI,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PIN_LD_SPI_MISO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(PORT_LD_SPI,&GPIO_InitStructure);
	
	LD_CS_H();
	LD_MOSI_H();
	LD_SCK_H();
}
/***********************************************************
* ��    �ƣ� LD3320_EXTI_Cfg(void) 
* ��    �ܣ� �ⲿ�жϹ������ú���ض˿�����
**********************************************************/ 
void LD3320_EXTI_Cfg(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  //�ж���������
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = PIN_LD_IRQ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PORT_LD_IRQ, &GPIO_InitStructure);
	//�ⲿ�ж�������
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  EXTI_GenerateSWInterrupt(EXTI_Line1);
		
	GPIO_SetBits(PORT_LD_IRQ,PIN_LD_IRQ);	 //Ĭ�������ж�����

	EXTI_ClearFlag(EXTI_Line1);
	EXTI_ClearITPendingBit(EXTI_Line1);
	//�ж�Ƕ������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


/***********************************************************
* ��    �ƣ�  EXTI1_IRQHandler(void)
* ��    �ܣ� �ⲿ�жϺ���
**********************************************************/ 
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!= RESET ) 
	{
 		ProcessInt0(); 
		EXTI_ClearFlag(EXTI_Line1);
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}


