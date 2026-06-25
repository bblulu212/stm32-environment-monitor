#ifndef _BSP_MQ135_H_
#define _BSP_MQ135_H_

#include "stm32f10x.h"

#define RCC_MQ_GPIO       RCC_APB2Periph_GPIOA

#define RCC_MQ_ADC        RCC_APB2Periph_ADC1

#define PORT_ADC          ADC1
#define CHANNEL_ADC       ADC_Channel_5

#define PORT_MQ_GPIO      GPIOA

#define GPIO_MQ_AO        GPIO_Pin_5
#define GPIO_MQ_DO        GPIO_Pin_1

 //采样次数
#define SAMPLES           30

void ADC_MQ135_Init(void);
unsigned int Get_Adc_MQ135_Value(void);
unsigned int Get_MQ135_Percentage_value(void);
char Get_MQ135_DO_value(void);

#endif