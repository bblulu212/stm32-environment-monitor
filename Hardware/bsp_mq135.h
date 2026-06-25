#ifndef _BSP_MQ135_H_
#define _BSP_MQ135_H_

#include "stm32f10x.h"

#define RCC_MQ135_GPIO_AO       RCC_APB2Periph_GPIOA
#define RCC_MQ135_GPIO_DO       RCC_APB2Periph_GPIOB

#define RCC_MQ135_ADC        RCC_APB2Periph_ADC1

#define MQ135_PORT_ADC          ADC1
#define MQ135_CHANNEL_ADC       ADC_Channel_4

#define PORT_MQ135_GPIO_AO      GPIOA
#define PORT_MQ135_GPIO_DO      GPIOB

#define GPIO_MQ135_AO        GPIO_Pin_4
#define GPIO_MQ135_DO        GPIO_Pin_11

 //采样次数
#define SAMPLES           30

void ADC_MQ135_Init(void);
unsigned int Get_Adc_MQ135_Value(void);
unsigned int Get_MQ135_Percentage_value(void);
char Get_MQ135_DO_value(void);

#endif
