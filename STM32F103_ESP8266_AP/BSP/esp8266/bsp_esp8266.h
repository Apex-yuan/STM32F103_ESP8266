#ifndef __ESP8266_H
#define __ESP8266_H

#include "stm32f10x.h"

/******************************* ESP8266 �������Ͷ��� ***************************/
typedef enum{
	STA,
  AP,
  STA_AP  
} ESP8266_ModeEnumDef;


typedef enum{
	 enumTCP,
	 enumUDP,
} ESP8266_ProtocolEnumDef;
	

typedef enum{
	Multiple_ID_0 = 0,
	Multiple_ID_1 = 1,
	Multiple_ID_2 = 2,
	Multiple_ID_3 = 3,
	Multiple_ID_4 = 4,
	Single_ID_0 = 5,
} ENUM_ID_NO_TypeDef;
	

typedef enum{
	OPEN = 0,
	WEP = 1,
	WPA_PSK = 2,
	WPA2_PSK = 3,
	WPA_WPA2_PSK = 4,
} ESP8266_ApPwdModeEnumDef;


#define ESP8266_USART_BOUND  9600//115200

/******************************** ESP8266 �������Ŷ��� ***********************************/
#define      ESP8266_CH_PD_CLK                             RCC_APB2Periph_GPIOB  
#define      ESP8266_CH_PD_PORT                            GPIOB
#define      ESP8266_CH_PD_PIN                             GPIO_Pin_13

#define      ESP8266_RST_CLK                               RCC_APB2Periph_GPIOB
#define      ESP8266_RST_PORT                              GPIOB
#define      ESP8266_RST_PIN                               GPIO_Pin_14


#define   ESP8266_BUILD_AP_SSID         "ESP8266"      //Ҫ�������ȵ������
#define   ESP8266_BUILD_AP_ECN          (ESP8266_ApPwdModeEnumDef)4               //Ҫ�������ȵ�ļ��ܷ�ʽ
#define   ESP8266_BUILD_AP_PWD           "12345678"         //Ҫ�������ȵ����Կ

#define   ESP8266_TCPSERVER_IP         "192.168.1.115"//"192.168.123.169"      //������������IP��ַ
#define   ESP8266_TCPSERVER_PORT       "8086"             //�����������Ķ˿�   

#define   ESP8266_TCPSERVER_TIMEOUT    "5000"             //��������ʱʱ�䣨��λ���룩

void esp8266_init(void);
void esp8266_AP_test(void);


#endif /* __ESP8266_H */

