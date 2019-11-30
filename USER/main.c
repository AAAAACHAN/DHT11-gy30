#include "led.h"
#include "delay.h"
#include "sys.h"
#include "beep.h"
#include "usart.h"
#include "dht11.h"
#include "oled.h"
#include "bh1750.h"

 int main(void)
 {
	u8 t=0;			    
	u8 temperature;  	    
	u8 humidity;
	extern float result_lx;

	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
	uart_init(9600);
	LED_Init();          //初始化LED，低电平触发
  BEEP_Init();         //初始化蜂鸣器,低电平触发
	OLED_Init();         //初始化OLED
	Init_BH1750();			 //初始化BH1750
	 
 	while(DHT11_Init())	//DHT11初始化	
	{
		OLED_ShowString(3,3,"Initializing...");
		delay_ms(200);
		OLED_Clear();
 		delay_ms(200);
	}		

	
	OLED_ShowString(0,0,"Warning:");
 	OLED_ShowString(0,2,"Temp:  C");	 
 	OLED_ShowString(0,4,"Humi:  %");
	OLED_ShowString(0,6,"light:     lx");
	
	
	while(1)
	{	    	    
 		if(t%10==0)//每100ms读取一次
		{
			Start_BH1750();
			delay_ms(180);
			Read_BH1750();
			Convert_BH1750();
			DHT11_Read_Data(&temperature,&humidity);		//读取温湿度值					    
			OLED_ShowNum(40,2,temperature,2,16);	//显示温度	   		   
			OLED_ShowNum(40,4,humidity,2,16);		//显示湿度
			OLED_ShowNum(48,6,result_lx,5,16);  //显示光强度
			
			//报警范围设置
			if(temperature>30 | temperature<25 | humidity>70 | humidity<55 | result_lx >5000 | result_lx <20)
			{
				if(temperature>30 | temperature<25)
				{
					LED0 = 0;
					OLED_ShowNum(70,0,1,1,16);
				}
				else
				{
					LED0 = 1;
					OLED_ShowString(68,0,"   ");
				}
				if(humidity>70 | humidity<60)
				{
					LED1 = 0;
					OLED_ShowNum(80,0,2,1,16);
				}
				else
				{
					LED1 = 1;
					OLED_ShowString(78,0,"   ");
				}
				if(result_lx >5000 | result_lx <20)
				{
					OLED_ShowNum(90,0,3,1,16);
				}
				else
				{
					OLED_ShowString(88,0,"   ");
				}
			}
			if(temperature>30 | temperature<25 | humidity>70 | humidity<55 | result_lx >5000 | result_lx <20)
			{
				beep=!beep;
			}
			if(temperature<30 & temperature>25 & humidity<70 & humidity>55 & result_lx <5000 & result_lx >20)
			{
				beep = 1;
				LED0 = 1;
				LED1 = 1;
				OLED_ShowString(60,0,"        ");
			}
			/*
			if((temperature<30 & temperature>25) | (humidity<70 & humidity>60))
			{
				if(temperature<30 & temperature>25)
				{
					LED0 = 1;
				}
				if(humidity<70 & humidity>60)
				{
					LED1 = 1;
				}
			}*/
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
		}
	}
}




