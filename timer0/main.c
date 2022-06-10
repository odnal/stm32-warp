#include <stdint.h>
#include "tim1.h"

#define RCC_AHB2ENR           (*((volatile uint32_t *) (RCC_BASE+0x4C)))  // GPIO bus
#define GPIOE_BASE            0x48001000u
#define GPIOE_MODER           (*((volatile uint32_t *) (GPIOE_BASE+0x00)))
#define GPIOE_AFR             (*((volatile uint32_t *) (GPIOE_BASE+0x24)))

int main (void)
{
  unsigned int ra;

  // Init timer 1 with toggle mode
  TIM1_Toggle_Init();

  /* GPIOE Init */
  // clock enable GPIOE
  RCC_AHB2ENR |= 1<<4;

  // configure GPIOE to alternate function mode: '10'
  ra=GPIOE_MODER;
  ra&=(~(3<<(8<<1))); 
  ra|=( (2<<(8<<1))); 
  GPIOE_MODER=ra;

  // setting up alternate function for TIM1_CH1N
  GPIOE_AFR &= ~(0xF);  // clearing bits
  GPIOE_AFR |= 0x1u;    // 0001: AF1

  while(1);

  return 0;
}
