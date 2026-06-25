#ifndef _BSP_BMP180_H_
#define _BSP_BMP180_H_

#include "stm32f10x.h"

//端口移植
#define RCC_BMP180         RCC_APB2Periph_GPIOB
#define PORT_BMP180        GPIOB

#define GPIO_SDA           GPIO_Pin_4
#define GPIO_SCL           GPIO_Pin_3

//设置SDA输出模式
#define SDA_OUT()   {\
                        GPIO_InitTypeDef  GPIO_InitStructure;\
                        GPIO_InitStructure.GPIO_Pin = GPIO_SDA;\
                        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;\
                        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
                        GPIO_Init(PORT_BMP180, &GPIO_InitStructure);\
                     }
//设置SDA输入模式
#define SDA_IN()    {\
                        GPIO_InitTypeDef  GPIO_InitStructure;\
                        GPIO_InitStructure.GPIO_Pin = GPIO_SDA;\
                        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;\
                        GPIO_Init(PORT_BMP180, &GPIO_InitStructure);\
                    }
//获取SDA引脚的电平变化
#define SDA_GET()       GPIO_ReadInputDataBit(PORT_BMP180, GPIO_SDA)
//SDA与SCL输出
#define SDA(x)          GPIO_WriteBit(PORT_BMP180, GPIO_SDA, (x?Bit_SET:Bit_RESET) )
#define SCL(x)          GPIO_WriteBit(PORT_BMP180, GPIO_SCL, (x?Bit_SET:Bit_RESET) )

void BMP180_GPIO_Init(void);
float BMP180_Get_Temperature(void);
float BMP180_Get_Pressure(void);
void BMP180_Write_Cmd(uint8_t regaddr,uint8_t cmd);
void BMP180_Get_param(void);
float BMP180_Get_Altitude(float p);

#endif

					