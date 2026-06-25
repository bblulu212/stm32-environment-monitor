#include "bsp_mq135.h"
#include "Delay.h"

/******************************************************************
 * 函 数 名 称：ADC_MQ135_Init
 * 函 数 说 明：初始化ADC功能
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void ADC_MQ135_Init(void)
{
        RCC_APB2PeriphClockCmd (RCC_MQ135_GPIO_AO, ENABLE); // 使能时钟
	    RCC_APB2PeriphClockCmd (RCC_MQ135_GPIO_DO, ENABLE); // 使能时钟
        RCC_APB2PeriphClockCmd (RCC_MQ135_ADC, ENABLE); // 使能ADC时钟

        GPIO_InitTypeDef  GPIO_InitStructure; // GPIO配置结构体

        GPIO_InitStructure.GPIO_Pin = GPIO_MQ135_AO;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;    //模拟输入

        GPIO_Init(PORT_MQ135_GPIO_AO, &GPIO_InitStructure); // 初始化GPIO

        GPIO_InitStructure.GPIO_Pin = GPIO_MQ135_DO;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    //输入

        GPIO_Init(PORT_MQ135_GPIO_DO, &GPIO_InitStructure); // 初始化GPIO

        ADC_DeInit(MQ135_PORT_ADC);//ADC复位

        /* ADC特定配置 */
        ADC_InitTypeDef ADC_InitStruct; // ADC特定配置结构体

        // ADC 模式配置
        ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;// 只使用一个ADC，独立模式
        ADC_InitStruct.ADC_ScanConvMode = DISABLE ;// 禁止扫描模式，单通道不需要扫描
        ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;// 连续转换模式
        ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;// 软件触发转换
        ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;// 数据右对齐
        ADC_InitStruct.ADC_NbrOfChannel = 1;// 转换通道1个

        // 初始化ADC
        ADC_Init(MQ135_PORT_ADC, &ADC_InitStruct);

        // 配置ADC时钟PCLK2的6分频，即12MHz
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);

        // 配置 ADC 通道转换顺序为1，第一个转换，采样时间为55.5个时钟周期
        // 通道为5
        ADC_RegularChannelConfig(MQ135_PORT_ADC, MQ135_CHANNEL_ADC, 2, ADC_SampleTime_55Cycles5);

        //ADC使能
        ADC_Cmd(MQ135_PORT_ADC, ENABLE);

        // 初始化ADC 校准寄存器
        ADC_ResetCalibration(MQ135_PORT_ADC);
        // 等待校准寄存器初始化完成
        while (ADC_GetResetCalibrationStatus(MQ135_PORT_ADC));

        // ADC开始校准
        ADC_StartCalibration(MQ135_PORT_ADC);
        // 等待校准完成
        while (ADC_GetCalibrationStatus(MQ135_PORT_ADC));

        // 使用软件触发ADC转换
        ADC_SoftwareStartConvCmd(MQ135_PORT_ADC, ENABLE);
}

/******************************************************************
 * 函 数 名 称：Get_Adc_MQ135_Value
 * 函 数 说 明：
 * 函 数 形 参：
 * 函 数 返 回：对应扫描的ADC值
 * 作       者：LC
 * 备       注：无
******************************************************************/
unsigned int Get_Adc_MQ135_Value(void)
{
        uint32_t Data = 0;

        for(int i = 0; i < SAMPLES; i++)
        {
                Data += ADC_GetConversionValue(MQ135_PORT_ADC);

                Delay_ms(5);
        }

        Data = Data / SAMPLES;

        return Data;
}

/******************************************************************
 * 函 数 名 称：Get_MQ135_Percentage_value
 * 函 数 说 明：读取MQ135值，并且返回百分比
 * 函 数 形 参：无
 * 函 数 返 回：返回百分比
 * 作       者：LC
 * 备       注：无
******************************************************************/
unsigned int Get_MQ135_Percentage_value(void)
{
    int adc_max = 4095;
    int adc_new = 0;
    int Percentage_value = 0;

    adc_new = Get_Adc_MQ135_Value();

    Percentage_value = ((float)adc_new / (float)adc_max) * 100.f;
    return Percentage_value;
}

/******************************************************************
 * 函 数 名 称：Get_MQ135_DO_value
 * 函 数 说 明：获取MQ135DO引脚的电平状态
 * 函 数 形 参：无
 * 函 数 返 回：0=未检测到高于灵敏度的酒精值 1=检测到高于灵敏度的酒精值
 * 作       者：LC
 * 备       注：调整模块上的滑动电阻即可调整灵敏度
******************************************************************/
char Get_MQ135_DO_value(void)
{
    if( GPIO_ReadInputDataBit(PORT_MQ135_GPIO_DO, GPIO_MQ135_DO) == RESET )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
