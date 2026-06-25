#ifndef _ADC_H
#define _ADC_H

#include "stm32f10x.h"

extern uint16_t adc_value_ch0; 
extern uint16_t adc_value_ch1; 
extern uint16_t adc_value_ch4; 


void ADC_init(void); // ADC初始化
uint16_t Get_ADC_Value(uint8_t channel); // 读取单个通道ADC值
uint16_t Get_Adc_Average(uint8_t channel); // 获取指定通道平均值
unsigned int Get_Adc_Percentage_value(uint8_t channel);


#endif

