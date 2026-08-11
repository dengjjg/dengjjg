#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
 
 
/************************************************
 ALIENTEK战舰STM32开发板实验1
 跑马灯实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
 int main1(void);

 extern volatile u32 g_system_ms;

 #define RED_LIGHT_TIME     60000
 #define GREEN_LIGHT_TIME   30000
 #define YELLOW_LIGHT_TIME   5000

 int main(void)
 {
		u8 light_state=0;
		u32 state_start_time=0;
		u32 current_time;

		LED_Init();		  	//初始化与LED连接的硬件接口
		if(SysTick_Config(SystemCoreClock/1000))	//配置SysTick每1ms产生一次中断
		{
			while(1);
		}

		//初始状态为红灯
		LED0=0;
		LED1=1;

		while(1)
		{
			current_time=g_system_ms;

			switch(light_state)
			{
				case 0:	//红灯60秒
					if((u32)(current_time-state_start_time)>=RED_LIGHT_TIME)
					{
						light_state=1;
						state_start_time=current_time;
						LED0=1;
						LED1=0;
					}
					break;

				case 1:	//绿灯30秒
					if((u32)(current_time-state_start_time)>=GREEN_LIGHT_TIME)
					{
						light_state=2;
						state_start_time=current_time;
						LED0=0;
						LED1=0;
					}
					break;

				default:	//黄灯5秒
					if((u32)(current_time-state_start_time)>=YELLOW_LIGHT_TIME)
					{
						light_state=0;
						state_start_time=current_time;
						LED0=0;
						LED1=1;
					}
					break;
			}
		}
 }

 int main1(void)
 {
	 delay_init();	    //延时函数初始化	  
	 LED_Init();		  	//初始化与LED连接的硬件接口
	 while(1)
	 {
		 GPIO_ResetBits(GPIOB,GPIO_Pin_5);  //LED0对应引脚GPIOB.5拉低，亮  等同LED0
		 GPIO_SetBits(GPIOB,GPIO_Pin_6);    //LED1对应引脚GPIOB.6拉高，灭  等同LED1
		 delay_ms(300);	 //延时300ms
	 }
 }


 
 int main2(void)
 {
	 delay_init();	    //延时函数初始化	  
	 LED_Init();		  	//初始化与LED连接的硬件接口
	 while(1)
	 {
		 GPIO_ResetBits(GPIOB,GPIO_Pin_5);  //LED0对应引脚GPIOB.5拉低，亮  等同LED0
		 GPIO_SetBits(GPIOB,GPIO_Pin_6);    //LED1对应引脚GPIOB.6拉高，灭  等同LED1
		 delay_ms(300);	 //延时300ms
		 GPIO_ResetBits(GPIOB,GPIO_Pin_6);  //LED0对应引脚GPIOB.5拉低，亮  等同LED0
	 }//
	 delay_ms(300);	 //延时300ms
	 delay_ms(300);	 //延时300ms
	 delay_ms(300);	 //延时300ms
	 delay_ms(300);	 //延时300ms
	 delay_ms(300);	 //延时300ms
 }


  int main3(void)
 {
	 delay_init();	    //延时函数初始化	  
	 LED_Init();		  	//初始化与LED连接的硬件接口
	 while(1)
	 {
		 GPIO_ResetBits(GPIOB,GPIO_Pin_5);  //LED0对应引脚GPIOB.5拉低，亮  等同LED0
		 GPIO_SetBits(GPIOB,GPIO_Pin_6);    //LED1对应引脚GPIOB.6拉高，灭  等同LED1
		 delay_ms(300);	 //延时300ms
		 GPIO_ResetBits(GPIOB,GPIO_Pin_6);  //LED0对应引脚GPIOB.5拉低，亮  等同LED0
	 }//
	 delay_ms(300);	 //延时300ms
	 delay_ms(300);	 //延时300ms
	 delay_ms(300);	 //延时300ms
	 delay_ms(300);	 //延时300ms
	 delay_ms(300);	 //延时300ms
 }
 /**
 *****************下面注视的代码是通过调用库函数来实现IO控制的方法*****************************************
int main(void)
{ 
 
	delay_init();		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	while(1)
	{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);  //LED0对应引脚GPIOB.5拉低，亮  等同LED0=0;
			GPIO_SetBits(GPIOE,GPIO_Pin_5);   //LED1对应引脚GPIOE.5拉高，灭 等同LED1=1;
			delay_ms(300);  		   //延时300ms
			GPIO_SetBits(GPIOB,GPIO_Pin_5);	   //LED0对应引脚GPIOB.5拉高，灭  等同LED0=1;
			GPIO_ResetBits(GPIOE,GPIO_Pin_5); //LED1对应引脚GPIOE.5拉低，亮 等同LED1=0;
			delay_ms(300);                     //延时300ms
	}
} 
 
 ****************************************************************************************************
 ***/
 

	
/**
*******************下面注释掉的代码是通过 直接操作寄存器 方式实现IO口控制**************************************
int main(void)
{ 
 
	delay_init();		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	while(1)
	{
     GPIOB->BRR=GPIO_Pin_5;//LED0亮
	   GPIOE->BSRR=GPIO_Pin_5;//LED1灭
		 delay_ms(300);
     GPIOB->BSRR=GPIO_Pin_5;//LED0灭
	   GPIOE->BRR=GPIO_Pin_5;//LED1亮
		 delay_ms(300);

	 }
 }
**************************************************************************************************
**/

