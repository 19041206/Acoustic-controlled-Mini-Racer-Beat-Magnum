#ifndef USER_HARDWARE_CONFIG_H
#define USER_HARDWARE_CONFIG_H 	

#include "sys.h"

/*************LD3320 �˿���Ϣ********************
 * RST      PA3
 * CS   	  PA2
 * WR/SPIS  PA0
 * P2/SDCK  PA5
 * P1/SDO   PA6
 * P0/SDI   PA7
 * IRQ      PB1
 * A0				PA4
*****************************************/
/********************NRF24L01��Ϣ********************
 * NRF24L01_IRQ         PB6
 * NRF24L01_CSN      	  PB7
 * NRF24L01_CE          PB8
 * NRF24L01_SCK         PB13
 * NRF24L01_MISO        PB14
 * NRF24L01_MOSI        PB15
*****************************************/
/********************������Ϣ********************
 * KEY_UP(ǰ��)         PA8
 * KEY_DOWN(����)   	  PA11
 * KEY_LEFT(����)       PA12
 * KEY_RIGHT(����)      PA15
 * KEY_STOP(ֹͣ)       PB9
*****************************************/

#define PORT_LD_SPI         GPIOA //LD��MOSI\MISO\SCK����GPIOA��
#define PORT_LD_CE          GPIOA
#define PORT_LD_RST         GPIOA
#define PORT_LD_A0          GPIOA
#define PORT_LD_SPIS        GPIOA
#define PORT_LD_IRQ         GPIOB

#define PIN_LD_SPI_SCK      GPIO_Pin_5
#define PIN_LD_SPI_MISO     GPIO_Pin_6
#define PIN_LD_SPI_MOSI     GPIO_Pin_7
#define PIN_LD_CE           GPIO_Pin_2
#define PIN_LD_RST          GPIO_Pin_3
#define PIN_LD_A0           GPIO_Pin_4
#define PIN_LD_SPIS         GPIO_Pin_0
#define PIN_LD_IRQ          GPIO_Pin_1

#define PORT_NRF24L01       GPIOB
#define PIN_NRF24L01_IRQ    GPIO_Pin_6
#define PIN_NRF24L01_CSN    GPIO_Pin_7
#define PIN_NRF24L01_CE     GPIO_Pin_8
#define PIN_NRF24L01_SCK    GPIO_Pin_13
#define PIN_NRF24L01_MISO   GPIO_Pin_14
#define PIN_NRF24L01_MOSI   GPIO_Pin_15


#define PORT_KEY_MOVE       GPIOA
#define PORT_KEY_STOP       GPIOB
#define PIN_KEY_UP          GPIO_Pin_8
#define PIN_KEY_DOWN        GPIO_Pin_11
#define PIN_KEY_LEFT        GPIO_Pin_12
#define PIN_KEY_RIGHT       GPIO_Pin_15
#define PIN_KEY_STOP        GPIO_Pin_9


#define DATE_A           7     /*ʶ���������*/
#define DATE_B           20		/*���������ƴ���ܳ�������(���79)*/

//������pCode������и�ֵ���м����������Ҫ���м����궨�壬��������ֿ����Զ��壬���ǽ���������������
#define CODE_YDCF	       1	 /*Ծ�����*/
#define CODE_QJ	         2	 /*ǰ��*/
#define CODE_T	         3	 /*ͣ*/
#define CODE_HT	         4	 /*����*/
#define CODE_JS          5   /*����*/
#define CODE_XZ          6   /*����*/
#define CODE_XY          7   /*����*/

#define CLK_IN           8	 /* LD3320ʹ�õľ���Ƶ�ʣ���λ��Mhz��*/
#define MIC_VOL          0x10 //�������� 00H-7FH��ԽС��Ҫ����Խ������ʶ�𣬶���Զ���ĸ��ž���һ���ĵֿ�����
#define Vad_Silence_End  0x0A //����LD3320��B5�Ĵ�����ÿһ��λ����10���롣��ʾ��⵽�����κ����������ô��ʱ���������Ϊ����������
#define Vad_Length       0xA  //����LD3320��B6�Ĵ�����ÿһ��λ����100���롣�����⵽�����κ�������õ�����ʶ��

//����ΪNRF24L01���͵�����
#define NRF_COMMAND_YDCF  'Y'
#define NRF_COMMAND_QJ    'Q'
#define NRF_COMMAND_T     'T'
#define NRF_COMMAND_HT    'H'
#define NRF_COMMAND_JS    'J'
#define NRF_COMMAND_XZ    'L'
#define NRF_COMMAND_XY    'R' 

//NRF24L01������
#define NRF24L01_CE   PBout(8) //24L01Ƭѡ�ź�
#define NRF24L01_CSN  PBout(7) //SPIƬѡ�ź�	   
#define NRF24L01_IRQ  PBin(6)  //IRQ������������


//*****************************************************************
//*****************************************************************
//�������ݿ��Բ����޸ģ�����ĺ궨����������������//
//*****************************************************************
//*****************************************************************
#define KEY_UP      GPIO_ReadInputDataBit(PORT_KEY_MOVE,PIN_KEY_UP)
#define KEY_DOWN    GPIO_ReadInputDataBit(PORT_KEY_MOVE,PIN_KEY_DOWN)
#define KEY_LEFT    GPIO_ReadInputDataBit(PORT_KEY_MOVE,PIN_KEY_LEFT)
#define KEY_RIGHT   GPIO_ReadInputDataBit(PORT_KEY_MOVE,PIN_KEY_RIGHT) 
#define KEY_STOP    GPIO_ReadInputDataBit(PORT_KEY_STOP,PIN_KEY_STOP) 

#define LD_RST_H() GPIO_SetBits(PORT_LD_RST, PIN_LD_RST )
#define LD_RST_L() GPIO_ResetBits(PORT_LD_RST, PIN_LD_RST )

#define LD_CS_H()	GPIO_SetBits(PORT_LD_CE, PIN_LD_CE)
#define LD_CS_L()	GPIO_ResetBits(PORT_LD_CE, PIN_LD_CE)

#define LD_MOSI_H()	GPIO_SetBits(PORT_LD_SPI, PIN_LD_SPI_MOSI)
#define LD_MOSI_L()	GPIO_ResetBits(PORT_LD_SPI, PIN_LD_SPI_MOSI)

#define LD_SCK_H()	GPIO_SetBits(PORT_LD_SPI, PIN_LD_SPI_SCK)
#define LD_SCK_L()	GPIO_ResetBits(PORT_LD_SPI, PIN_LD_SPI_SCK)

#define LD_SPIS_H()  GPIO_SetBits(PORT_LD_SPIS, PIN_LD_SPIS)
#define LD_SPIS_L()  GPIO_ResetBits(PORT_LD_SPIS, PIN_LD_SPIS)

#define LD_MISO      GPIO_ReadInputDataBit(PORT_LD_SPI,PIN_LD_SPI_MISO)

extern u8  sRecog[DATE_A][DATE_B];
extern u8  pCode[DATE_A];
//*****************************************************************
//*****************************************************************

#endif
