#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Buzzer.h"
#include "Key.h"
#include "Timer.h"
#include "DHT11.h"
#include "adc.h"
#include "bsp_bmp180.h"


uint8_t temp,humi,QUA,key_num=0;
uint8_t max=80,min=20;

int main(void)
{
	OLED_Init();
	Key_Init();
	Buzzer_Init();
	DHT11_Init();
	ADC_init();
	BMP180_GPIO_Init();
	Buzzer_ON();
	Delay_ms(100);
	
	
	while (1)
	{
		key_num=Key_GetState();
		if(key_num==1)
		{
			max++;
		}
		else if(key_num==2)
		{
			max--;
		}
		else if(key_num==3)
		{
			min++;
		}
		else if(key_num==4)
		{
			min--;
		}
		DHT11_Read_Data(&temp,&humi);
		QUA=Get_Adc_Percentage_value(4);
		OLED_Printf(0, 0, OLED_6X8, "temp: %dC",temp);
		OLED_Printf(0, 8, OLED_6X8, "humi: %d%%",humi);
		OLED_Printf(0, 16, OLED_6X8, "CO: %d%%",Get_Adc_Percentage_value(1));
		OLED_Printf(0, 24, OLED_6X8, "QUA: %d%%",Get_Adc_Percentage_value(4));
		OLED_Printf(0, 32, OLED_6X8, "ILL: %d%%",Get_Adc_Percentage_value(0));		
		OLED_Printf(0, 40, OLED_6X8, "PRE: %.2f",BMP180_Get_Pressure());
		OLED_Printf(0, 56, OLED_6X8, "MAX:%d",max);
		OLED_Printf(72, 56, OLED_6X8, "MIN:%d",min);

		if(QUA>=max||QUA<=min)
		{
			Buzzer_OFF();
		}
		else
		{
			Buzzer_ON();
		}
		OLED_Update();
		Delay_ms(100);		
	}
}

