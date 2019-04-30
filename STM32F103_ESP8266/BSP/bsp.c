#include "bsp.h"

void bsp_init(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  usart1_init(115200);
  systick_init();
  //usart1_init(115200);
  //usart3_init(115200);
  esp8266_init();  
}