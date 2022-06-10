#include <stdint.h>
#include "sys_clock.h"
#include "tim1.h"

#define RCC_AHB2ENR           (*((volatile uint32_t *) (RCC_BASE+0x4C)))  // GPIO bus
#define GPIOE_BASE            0x48001000u
#define GPIOE_MODER           (*((volatile uint32_t *) (GPIOE_BASE+0x00)))
#define GPIOE_AFR             (*((volatile uint32_t *) (GPIOE_BASE+0x24)))

int main (void)
{
  unsigned int ra;

  // HSI clock source configured through PLL to output 80Mhz 
  System_Clock_Init();
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

  uint8_t intensity=0;
  unsigned int i;

  while(1) {
    // Dimming
    TIM1_CCR1 = 100-intensity;
    intensity += 1;

    // Brightening
    if (intensity > 100) {
      intensity = 0;
      while (TIM1_CCR1 != 100) {
        intensity += 1;
        TIM1_CCR1 = intensity;
        for(i=0; i<9000; i++);  // delay
        if (TIM1_CCR1 == 100) {
          intensity = 0;
        } 
      }
    }

    for (int i=0;i<9000;i++); // delay
  }

  return 0;
}
