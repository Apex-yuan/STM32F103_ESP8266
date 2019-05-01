#include "stm32f10x.h"

#include "bsp.h"
#include "ap_test.h"
#include "sta_test.h"
#include "ap_sta_test.h"


int main(int argc, char **argv)
{
  bsp_init();

  #if 0
   esp8266_apTcpServer_test();
  #elif 0
   esp8266_staTcpServer_test();
  #elif 1
   esp8266_apStaTcpServer_test();
  #endif
  while(1)
  {
    
  }
}
