#ifndef USER_HARDWARE_CONFIG_H
#define USER_HARDWARE_CONFIG_H 	

/********************NRF24L01��Ϣ********************
 * NRF24L01_IRQ         PB6
 * NRF24L01_CSN      	  PB7
 * NRF24L01_CE          PB8
 * NRF24L01_SCK         PB13
 * NRF24L01_MISO        PB14
 * NRF24L01_MOSI        PB15
*****************************************/
/********************MX1508��Ϣ********************
 * INA1                 PA1
 * INB1                 PA2
 * INA2                 PA3
 * INB2                 PA4
*****************************************/

#define PORT_NRF24L01       GPIOB
#define PIN_NRF24L01_IRQ    GPIO_Pin_6
#define PIN_NRF24L01_CSN    GPIO_Pin_7
#define PIN_NRF24L01_CE     GPIO_Pin_8
#define PIN_NRF24L01_SCK    GPIO_Pin_13
#define PIN_NRF24L01_MISO   GPIO_Pin_14
#define PIN_NRF24L01_MOSI   GPIO_Pin_15

#define PORT_MX1508         GPIOA
#define PIN_INA1            GPIO_Pin_1
#define PIN_INB1            GPIO_Pin_2
#define PIN_INA2            GPIO_Pin_3
#define PIN_INB2            GPIO_Pin_4

#define PORT_LED            GPIOC
#define PIN_LED             GPIO_Pin_13

//����ΪNRF24L01���͵�����
#define NRF_COMMAND_YDCF  'Y'
#define NRF_COMMAND_QJ    'Q'
#define NRF_COMMAND_T     'T'
#define NRF_COMMAND_HT    'H'
#define NRF_COMMAND_JS    'J'
#define NRF_COMMAND_XZ    'L'
#define NRF_COMMAND_XY    'R' 

#define NRF24L01_CE   PBout(8) //24L01Ƭѡ�ź�
#define NRF24L01_CSN  PBout(7) //SPIƬѡ�ź�	   
#define NRF24L01_IRQ  PBin(6)  //IRQ������������


#define LED0 PCout(13)
#define INA1 PAout(1)	
#define INB1 PAout(2)	
#define INA2 PAout(3)	
#define INB2 PAout(4)	


//*****************************************************************
//*****************************************************************

#endif
