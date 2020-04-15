#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "24l01.h"
#include "MX1508.h"
#include "USER_HARDWARE_CONFIG.h"

#define RC_STOP  0
#define RC_RUN_F 1
#define RC_RUN_B 2


char RunState = RC_STOP;
	
char INA1_PWM = 0;//Right wheel go backward
char INB1_PWM = 0;//Right wheel go forward
char INA2_PWM = 0;//Left wheel go forward
char INB2_PWM = 0;//Left wheel go backward

	u16 t=0;	
	u8 tmp_buf[33];		
	u8  Send_State;

	float HCSR_Value;

 int main(void)
 {
	u8 silentcount = 0;
 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	MX1508_Init();
	TIM2_Int_Init(5,7200);    // New time base: 72M / 7200 = 10000Hz; Every inttrupt time gap: 1/10000Hz * 5 = 0.5ms  	   	 

	NRF24L01_Init();    		//��ʼ��NRF24L01 
	LED0 = 0;
	NRF24L01_RX_Mode();		  
			
	for(t=0;t<32;t++)
	{
		tmp_buf[t]='A';	
	}	  
	tmp_buf[32]=0;//���������		 
	while(1)
	{			
		
		if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
			{
				silentcount = 0;
				tmp_buf[32]=0;//�����ַ���������
				if(tmp_buf[0] == NRF_COMMAND_YDCF) //��Ծ����桱 ����
				{
					LED0=!LED0;
				}
				if(tmp_buf[0] == NRF_COMMAND_T)    //��ͣ��
				{
					RunState = RC_STOP;
					INA1_PWM = 0;
					INB1_PWM = 0;
					INA2_PWM = 0;
					INB2_PWM = 0;
				}
				if(tmp_buf[0] == NRF_COMMAND_QJ)   //��ǰ����
				{
					if(RunState == RC_STOP || RunState == RC_RUN_F)
					{
						INA1_PWM = 0;
						INB1_PWM = 70;
						INA2_PWM = 70;
						INB2_PWM = 0;
						RunState = RC_RUN_F;
					}
				}
				if(tmp_buf[0] == NRF_COMMAND_JS)   //�����١�
				{
					if(RunState == RC_STOP || RunState == RC_RUN_F)
					{
						INA1_PWM = 0;
						INB1_PWM = 95;
						INA2_PWM = 95;
						INB2_PWM = 0;
						RunState = RC_RUN_F;
					}
				}
				if(tmp_buf[0] == NRF_COMMAND_HT)   //�����ˡ�
				{
					if(RunState == RC_STOP)
					{
						INA1_PWM = 70;
						INB1_PWM = 0;
						INA2_PWM = 0;
						INB2_PWM = 70;
						RunState = RC_RUN_B;
					}
				}
				if(tmp_buf[0] == NRF_COMMAND_XZ)   //������
				{
					if(RunState == RC_STOP || RunState == RC_RUN_F)
					{
						INA1_PWM = 0;
						INB1_PWM = 80;
						INA2_PWM = 45;
						INB2_PWM = 0;
						RunState = RC_RUN_F;
					}
				}
				if(tmp_buf[0] == NRF_COMMAND_XY)   //�����ҡ�
				{
					if(RunState == RC_STOP || RunState == RC_RUN_F)
					{
						INA1_PWM = 0;
						INB1_PWM = 45;
						INA2_PWM = 80;
						INB2_PWM = 0;
						RunState = RC_RUN_F;
					}
				}
			}
			else
			{
					silentcount ++;
					if(silentcount == 20)  //����20��ѭ��û�н��յ�ң����Ϣ�����Զ�ֹͣ
					{
						RunState = RC_STOP;
						INA1_PWM = 0;
						INB1_PWM = 0;
						INA2_PWM = 0;
						INB2_PWM = 0;
						silentcount = 0;
					}
					delay_ms(10);	  
			}
	}	 
 }

