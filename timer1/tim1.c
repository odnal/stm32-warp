#include "tim1.h"

void TIM1_Toggle_Init (void)
{
  unsigned int ra;

  // clock enable TIM1
  RCC_APB2ENR |= RCC_APB2ENR_TIM1EN; // 1<<11

  // declare an up-counter: '0'
  TIM1_CR1 |= 1<<4;
  TIM1_CR1 ^= 1<<4;

  // adjust timer frequencies (current bus freq 80Mhz)
  /*
   * freq_c = current frequency (whatever the system frequency is, 80Mhz)
   * freq_t = timer frequency
   * T_period = (1+ARR)(1/freq_t)
   * PSC = prescaler
   * freq_t = freq_c / PSC+1
   * 
  */ 
  TIM1_PSC = 0x0; // keep frequecy at 80Mhz
  TIM1_ARR = 99;  // value of which we count up to at the rate of the frequency set by the PSC
  TIM1_CCR1 = 50; // duty cycle - 50% of the ARR value
  
  // Main output enable (MOE)
  TIM1_BDTR |= 1<<15;

  // clear output compare mode bits in capture/compare mode register bits 16, [6:4] 
  ra=TIM1_CCMR1;
  ra&=(~(1<<16));
  ra&=(~(7<<(1<<2)));

  // set mode
  //ra|=( (3<<(1<<2))); // toggle mode (0011)
  ra|=( (6<<(1<<2))); // pmw mode (0110)
  TIM1_CCMR1=ra;

  // select output polarity - active high '0' by default - commented out to prevent a little glitch at the very 
  // beginning of loading the program because of the register write and the processor performing that unnecessary 
  // instruction since 0 is the reset value
  //TIM1_CCER |= (~(1<<3));   // CC1NP (N stands for complementary, since this is a inverted timer channel

  // enable channel 1 complementary output
  TIM1_CCER |= (1<<2);

  // enable counter
  TIM1_CR1 |= 0x1u;

}
