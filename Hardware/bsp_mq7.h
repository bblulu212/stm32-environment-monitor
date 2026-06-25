#ifndef _BSP_MQ7_H_
#define _BSP_MQ7_H_

#include "stm32f10x.h"

#define RCC_MQ_GPIO_AO       RCC_APB2Periph_GPIOA
#define RCC_MQ_GPIO_DO       RCC_APB2Periph_GPIOB

#define RCC_MQ_ADC        RCC_APB2Periph_ADC1

#define PORT_ADC          ADC1
#define CHANNEL_ADC       ADC_Channel_1

#define PORT_MQ_GPIO_AO      GPIOA
#define PORT_MQ_GPIO_DO      GPIOB

#define GPIO_MQ_AO        GPIO_Pin_1
#define GPIO_MQ_DO        GPIO_Pin_10

 //采样次数
#define SAMPLES         30

void ADC_MQ7_Init(void);
unsigned int Get_Adc_MQ7_Value(void);
unsigned int Get_MQ7_Percentage_value(void);
char Get_MQ7_DO_value(void);

#endif
