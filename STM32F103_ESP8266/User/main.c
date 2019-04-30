#include "stm32f10x.h"

#include "bsp.h"

int main(void)
{
  bsp_init();

  //esp8266_AP_test();
  esp8266_sta_tcpServer_test();
  while(1)
  {
    
  }
}
