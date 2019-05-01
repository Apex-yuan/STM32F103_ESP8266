#include "ap_sta_test.h"
#include "bsp.h"


void esp8266_apStaTcpServer_test(void)
{
  char pAPIP[20];
  
  printf("\r\n********ESP8266 AP server + STA server test********\r\n");
  
  printf("\r\n-------------Start Config--------------\r\n");
  
  while(!esp8266_sendCmd ( "AT", "OK", 1000 ));
  printf("\r\n");
  while(!esp8266_modeChoose(STA_AP));
  printf("\r\n");
  while(!esp8266_buildAP(ESP8266_BUILD_AP_SSID,ESP8266_BUILD_AP_PWD,ESP8266_BUILD_AP_ECN));
  printf("\r\n");
  while(!esp8266_joinAP(ESP8266_AP_SSID,ESP8266_AP_PWD));
  printf("\r\n");
  esp8266_multipleIdCmd(ENABLE);
  printf("\r\n");
  esp8266_startServer(ESP8266_TCPSERVER_PORT);
  printf("\r\n");
  esp8266_setTimeout(ESP8266_TCPSERVER_TIMEOUT);
  printf("\r\n");
  esp8266_getAPIP(pAPIP);
  printf("\r\n");
  printf("\r\n--------------Config End---------------\r\n");
  
  rxFram.length = 0;
  rxFram.finishFlag = RESET;
  
  while(1)
  {
    if(rxFram.finishFlag == SET)
    {
      /*一帧数据接收完成*/
      USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
      rxFram.rxbuffer[rxFram.length] = '\0';  //为帧数据增加结束标记
      
      /*处理接收到的数据*/
      printf("%s",rxFram.rxbuffer); //将接收到的数据通过串口1原样输出
      
      /*处理结束后丢弃该帧数据，准备下一次接收*/
      rxFram.length = 0;
      rxFram.finishFlag = RESET;
      USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //开启串口接收中断
    }
  }
}

