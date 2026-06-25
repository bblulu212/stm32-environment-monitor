#include "ADC.h"
#include "Delay.h"

uint16_t adc_value_ch0 = 0; // 光照强度
uint16_t adc_value_ch1 = 0; // CO
uint16_t adc_value_ch4 = 0; // 空气质量


void ADC_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE); // 使能时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // ADC时钟72MHz/6=12MHz

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_4; // PA0,PA1配置为模拟输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // 独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE; // 关闭扫描模式，使用单通道转换
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // 单次转换
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1; // 单通道转换
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1, ENABLE); // 使能ADC

    ADC_ResetCalibration(ADC1); // 复位校准
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1); // 开始校准
    while(ADC_GetCalibrationStatus(ADC1));
}

// 读取单个通道ADC值
uint16_t Get_ADC_Value(uint8_t channel)
{
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5); // 配置通道
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 启动转换
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)); // 等待转换完成
    return ADC_GetConversionValue(ADC1); // 返回转换结果
}

// 获取指定通道的平均值
uint16_t Get_Adc_Average(uint8_t channel)
{
    uint32_t temp_val = 0;
    uint8_t t;
    
    for(t = 0; t < 10; t++)
    {
        temp_val += Get_ADC_Value(channel);
        Delay_ms(5); // 延时5ms
    }
    
    return temp_val / 10; // 返回平均值
}

unsigned int Get_Adc_Percentage_value(uint8_t channel)
{
    int adc_max = 4095;
    int adc_new = 0;
    int Percentage_value = 0;
	
    adc_new = Get_Adc_Average(channel);
    Percentage_value = ((float)adc_new / (float)adc_max) * 100.f;
	if(channel==1)
	{
		 Percentage_value +=18;
	}
    return Percentage_value;
}
