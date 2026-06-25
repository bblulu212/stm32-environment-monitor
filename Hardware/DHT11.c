#include "stm32f10x.h"                  // Device header
#include "DHT11.h"
#include "Delay.h"
#include "stdio.h"

//float temperature = 0;
//float humidity = 0;

///******************************************************************
// * 函 数 名 称：DHT11_GPIO_Init
// * 函 数 说 明：DHT11温湿度传感器初始化
// * 函 数 形 参：无
// * 函 数 返 回：无
// * 作       者：LC
// * 备       注：无
//******************************************************************/
//void DHT11_GPIO_Init(void)
//{
//        GPIO_InitTypeDef  GPIO_InitStructure;

//        // 开启时钟
//        RCC_APB2PeriphClockCmd(RCU_DHT11, ENABLE);

//        GPIO_InitStructure.GPIO_Pin = GPIO_DHT11;
//        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//        GPIO_Init(PORT_DHT11, &GPIO_InitStructure);

//        DATA_GPIO_OUT(1);
//}

///******************************************************************
// * 函 数 名 称：DHT11_GPIO_Mode_OUT
// * 函 数 说 明：配置DHT11的数据引脚为输出模式
// * 函 数 形 参：无
// * 函 数 返 回：无
// * 作       者：LC
// * 备       注：无
//******************************************************************/
//void DHT11_GPIO_Mode_OUT(void)
//{
//    GPIO_InitTypeDef  GPIO_InitStructure;

//        GPIO_InitStructure.GPIO_Pin = GPIO_DHT11;
//        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

//    GPIO_Init(PORT_DHT11, &GPIO_InitStructure);

//}

///******************************************************************
// * 函 数 名 称：DHT11_GPIO_Mode_IN
// * 函 数 说 明：配置DHT11的数据引脚为输入模式
// * 函 数 形 参：无
// * 函 数 返 回：无
// * 作       者：LC
// * 备       注：无
//******************************************************************/
//void DHT11_GPIO_Mode_IN(void)
//{
//        GPIO_InitTypeDef  GPIO_InitStructure;

//        GPIO_InitStructure.GPIO_Pin = GPIO_DHT11;
//        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入模式

//        GPIO_Init(PORT_DHT11, &GPIO_InitStructure);
//}

///******************************************************************
// * 函 数 名 称：DHT11_Read_Data
// * 函 数 说 明：根据时序读取温湿度数据
// * 函 数 形 参：无
// * 函 数 返 回：0=数据校验失败  其他=温湿度未处理的数据
// * 作       者：LC
// * 备       注：无
//******************************************************************/
//unsigned int DHT11_Read_Data(void)
//{
//    int i;
//    long long val=0;
//    int timeout=0;
//    float small_point=0;
//    unsigned char verify_num = 0;//验证值

//    DATA_GPIO_OUT(0);//数据线输出低电平
//    Delay_ms(19);  //起始信号保持时间19ms
//    DATA_GPIO_OUT(1);//主机释放总线
//    Delay_us( 20 );//拉高等待

//    DHT11_GPIO_Mode_IN();//数据线转为输入模式
//    //如果前面没有错误，则模块会发出低电平的应答信号，所以直接等待DHT11拉高，80us
//    timeout = 5000;
//    while( (! DATA_GPIO_IN ) && ( timeout >0 ) )timeout--;         //等待高电平的到来

//    //模块当前处于拉高准备输出数据，所以直接等待DHT11拉低，80us
//    timeout = 5000;//设置超时时间
//    //DATA_GPIO_IN=0时,while条件不成立退出while 说明接收到响应信号
//    //当timeout<=0时，while条件不成立退出while  说明超时
//    while( DATA_GPIO_IN && ( timeout >0 ) )timeout-- ;         //等待低电平的到来

//    #define CHECK_TIME 28 //实测发现超过0值的高电平时间
//    for(i=0;i<40;i++)//循环接收40位数据
//    {
//        timeout = 5000;
//        while( ( !DATA_GPIO_IN ) && (timeout > 0) ) timeout--;         //等待低电平过去

//        Delay_us(CHECK_TIME);//超过0值的高电平时间
//        if ( DATA_GPIO_IN )//如果还是高电平，说明是1值
//        {
//            val=(val<<1)+1;
//        }
//        else //如果是低电平，说明是0值
//        {
//            val<<=1;
//        }

//        timeout = 5000;
//        while( DATA_GPIO_IN && (timeout > 0) ) timeout-- ;         //如果还是高电平
//    }

//    DHT11_GPIO_Mode_OUT();//转为输出模式
//    DATA_GPIO_OUT(1);//主机释放总线

//    //           湿高8     + 湿低8      + 温高8     + 温低8
//    verify_num = (val>>32) + (val>>24) + (val>>16) + (val>>8);
//    //计算的校验和 与 接收的校验和 的差为0说明一致，不为0说明不一致
//    verify_num = verify_num - (val&0xff);
//    //进行校验
//    if( verify_num  )
//    {
////      校验错误
//        return 0;
//    }
//    else //校验成功
//    {
//        //数据处理
//        humidity = (val>>32)&0xff;//湿度前8位（小数点前数据）
//        small_point = (val>>24)&0x00ff;//湿度后8位（小数点后数据）
//        small_point = small_point * 0.1;//换算为小数点
//        humidity = humidity + small_point;//小数前+小数后
////        printf("湿度：%.2f\r\n",humidity);

//        temperature = (val>>16)&0x0000ff;//温度前8位（小数点前数据）
//        small_point = (val>>8)&0x000000ff;//温度后8位（小数点后数据）
//        small_point = small_point * 0.1;//换算为小数点
//        temperature = temperature + small_point;//小数前+小数后
////        printf("温度：%.2f\r\n",temperature);

//        return val>>8; //返回未处理的数据
//    }
//}

///******************************************************************
// * 函 数 名 称：Get_temperature
// * 函 数 说 明：获取温度数据
// * 函 数 形 参：无
// * 函 数 返 回：温度值
// * 作       者：LC
// * 备       注：使用前必须先调用 DHT11_Read_Data 读取有数据
//******************************************************************/
//float Get_temperature(void)
//{
//    return temperature;
//}

///******************************************************************
// * 函 数 名 称：Get_humidity
// * 函 数 说 明：获取湿度数据
// * 函 数 形 参：无
// * 函 数 返 回：湿度值
// * 作       者：LC
// * 备       注：使用前必须先调用 DHT11_Read_Data 读取有数据
//******************************************************************/
//float Get_humidity(void)
//{
//    return humidity;
//}

void DHT11_Rst(void)	   //复位DHT11
{
	//SET OUTPUT
	DHT11_Mode(OUT);
	//拉低DQ
	DHT11_Low;
	//主机拉低18~30ms
	Delay_ms(20);
	//拉高DQ
	DHT11_High;
	//主机拉高10~35us
	Delay_us(13);     	
}
 
 
/*==========================================================
Name：		DHT11_Check
Function：	等待DHT11的回应
pars:		无
return：	1:未检测到DHT11的存在
			0:检测到DHT11的存在
notes：		无
==========================================================*/
uint8_t DHT11_Check(void) 	   
{   
	uint8_t retry=0;
	DHT11_Mode(IN);//SET INPUT	 
    while (GPIO_ReadInputDataBit(DHT11_GPIO_PORT,DHT11_GPIO_PIN)&&retry<100)//DHT11会拉低40~80us
	{
		retry++;
		Delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!GPIO_ReadInputDataBit(DHT11_GPIO_PORT,DHT11_GPIO_PIN)&&retry<100)//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		Delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
 
/*==========================================================
Name：		DHT11_Read_Bit
Function：	读取DHT11一位
pars:		无
return：	1/0
notes：		无
==========================================================*/
uint8_t DHT11_Read_Bit(void) 			 
{
 	uint8_t retry=0;
	while(GPIO_ReadInputDataBit(DHT11_GPIO_PORT,DHT11_GPIO_PIN)&&retry<100)//等待变为低电平
	{
		retry++;
		Delay_us(1);
	}
	retry=0;
	while(!GPIO_ReadInputDataBit(DHT11_GPIO_PORT,DHT11_GPIO_PIN)&&retry<100)//等待变高电平
	{
		retry++;
		Delay_us(1);
	}
	Delay_us(40);//等待40us
	if(GPIO_ReadInputDataBit(DHT11_GPIO_PORT,DHT11_GPIO_PIN))return 1;
	else return 0;		   
}
 
 
/*==========================================================
Name：		DHT11_Read_Byte
Function：	读取DHT11一个字节
pars:		无
return：	读到的数据
notes：		无
==========================================================*/
uint8_t DHT11_Read_Byte(void)    
{        
	uint8_t i,dat;
	dat=0;
	for (i=0;i<8;i++) 
	{
		dat<<=1; 
		dat|=DHT11_Read_Bit();
	}						    
	return dat;
}
 
/*==========================================================
Name：		DHT11_Read_Data
Function：	读取DHT11数据
pars:		temp:温度
			humi:湿度
return：	0-读取成功
			1-读取失败
notes：		无
==========================================================*/
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi)    
{
 	uint8_t buff[5];
	uint8_t i;
	DHT11_Rst(); //发送起始信号
	if(DHT11_Check()==0) //等待响应
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buff[i]=DHT11_Read_Byte();
		}
		if((buff[0]+buff[1]+buff[2]+buff[3])==buff[4])
		{
			*humi=buff[0];		//温度数据
			*temp=buff[2];		//湿度数据
		}
	}
	else return 1;
	return 0;	    
}
 
/*==========================================================
Name：		DHT11_Init
Function：	初始化DHT11的IO口，同时检测DHT11的存在
pars:		temp:温度
			humi:湿度
return：	0-存在 
			1-不存在
notes：		无
==========================================================*/
uint8_t DHT11_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;	
 	RCC_APB2PeriphClockCmd(DHT11_GPIO_CLK, ENABLE);	 	//使能PA端口时钟
 	GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;		//端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);	//初始化IO口
 	GPIO_SetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN);		//输出高电平
			    
	DHT11_Rst();  //发送起始信号
	return DHT11_Check();//等待DHT11的回应
} 
 
void DHT11_Mode(uint8_t mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	if(mode)
	{
		GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	}
	else
	{
		GPIO_InitStructure.GPIO_Pin =  DHT11_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	}
	GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);
}
