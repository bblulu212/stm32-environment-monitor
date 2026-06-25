#ifndef _BSP_DHT11_H_
#define _BSP_DHT11_H_

#include "stm32f10x.h"

//#define RCU_DHT11   RCC_APB2Periph_GPIOC
//#define PORT_DHT11  GPIOC
//#define GPIO_DHT11  GPIO_Pin_13

////设置DHT11输出高或低电平
//#define DATA_GPIO_OUT(x)    GPIO_WriteBit(PORT_DHT11, GPIO_DHT11, x ? Bit_SET : Bit_RESET)
////获取DHT11数据引脚高低电平状态
//#define DATA_GPIO_IN        GPIO_ReadInputDataBit(PORT_DHT11, GPIO_DHT11)

//extern float temperature;
//extern float humidity;

//void DHT11_GPIO_Init(void);//引脚初始化
//unsigned int DHT11_Read_Data(void);//读取模块数据
//float Get_temperature(void);//返回读取模块后的温度数据
//float Get_humidity(void);//返回读取模块后的湿度数据

#define DHT11_GPIO_PORT  GPIOC
#define DHT11_GPIO_PIN   GPIO_Pin_13
#define DHT11_GPIO_CLK   RCC_APB2Periph_GPIOC
/*********************END**********************/
 
//输出状态定义
#define OUT 1
#define IN  0
 
//控制DHT11引脚输出高低电平
#define DHT11_Low  GPIO_ResetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN)
#define DHT11_High GPIO_SetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN)
 
 
uint8_t DHT11_Init(void);//初始化DHT11
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi);//读取温湿度数据
uint8_t DHT11_Read_Byte(void);//读取一个字节的数据
uint8_t DHT11_Read_Bit(void);//读取一位的数据
void DHT11_Mode(uint8_t mode);//DHT11引脚输出模式控制
uint8_t DHT11_Check(void);//检测DHT11
void DHT11_Rst(void);//复位DHT11   


#endif
