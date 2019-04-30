#include "bsp_systick.h"

volatile uint32_t _us_tick;
volatile uint32_t _ms_tick;

void systick_init(void) 
{
  _us_tick = 0;
  _ms_tick = 0;  
  
	if(SysTick_Config(SystemCoreClock / 1000000))
  {
    /*capture error*/
    while(1);
  }
  
  /* Configure the SysTick handler priority */
  NVIC_SetPriority(SysTick_IRQn, 0x0);
}

void delay_ms(uint32_t millis) 
{ 
	uint32_t target;
	
	target = _ms_tick + millis;
	while(_ms_tick < target);
} 
void delay_us(uint32_t uillis)
{ 
	uint32_t target;
	target = _us_tick + uillis;
	while(_us_tick < target);
}

uint32_t millis(void) 
{
	return _ms_tick;
}

uint32_t micros(void)
{
  return _us_tick;
}

void reset(void) 
{
	_us_tick = 0;
  _ms_tick = 0;
}

void SysTick_Handler(void)
{
	_us_tick++;
  _ms_tick = _us_tick / 1000;
}

