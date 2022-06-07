#include <stdint.h>

/* DEFINES */
#define RCC_BASE              0x40021000u
#define RCC_AHB2ENR           (*((volatile uint32_t *) (RCC_BASE+0x4C)))  // GPIO bus
#define RCC_APB2ENR           (*((volatile uint32_t *) (RCC_BASE+0x60)))  // TIM1 bus

#define RCC_APB2ENR_TIM1EN    0x00000800u
#define RCC_AHB2ENR_GPIOE     0x00000010u

#define GPIOE_BASE            0x48001000u
#define GPIOE_MODER           (*((volatile uint32_t *) (GPIOE_BASE+0x00)))
#define GPIOE_AFR             (*((volatile uint32_t *) (GPIOE_BASE+0x24)))

#define TIM1_BASE             0x40012C00u
#define TIM1_CR1              (*((volatile uint32_t *) (TIM1_BASE+0x00)))
#define TIM1_PSC              (*((volatile uint32_t *) (TIM1_BASE+0x28)))
#define TIM1_ARR              (*((volatile uint32_t *) (TIM1_BASE+0x2c)))
#define TIM1_CCR1             (*((volatile uint32_t *) (TIM1_BASE+0x34)))
#define TIM1_CCER             (*((volatile uint32_t *) (TIM1_BASE+0x20)))
#define TIM1_BDTR             (*((volatile uint32_t *) (TIM1_BASE+0x44)))
#define TIM1_CCMR1            (*((volatile uint32_t *) (TIM1_BASE+0x18)))

int main (void)
{
  unsigned int ra;

  // clock enable GPIOE
  RCC_AHB2ENR |= RCC_AHB2ENR_GPIOE; // 1<<4

  // configure GPIOE to alternate function mode: '10'
  ra=GPIOE_MODER;
  ra&=(~(3<<(8<<1))); 
  ra|=( (2<<(8<<1))); 
  GPIOE_MODER=ra;

  // setting up alternate function for TIM1_CH1N
  GPIOE_AFR &= ~(0xF);  // clearing bits
  GPIOE_AFR |= 0x1u;    // 0001: AF1

  // clock enable TIM1
  RCC_APB2ENR |= RCC_APB2ENR_TIM1EN; // 1<<11

  // declare an up-counter: '0'
  TIM1_CR1 |= 1<<4;
  TIM1_CR1 ^= 1<<4;

  // NOTE: start up clock is the MSI oscillator at 4Mhz
  // adjust timer frequencies
  /*
   * freq_c = current frequency (whatever the system frequency is, 80Mhz)
   * freq_t = timer frequency
   * prescaler (PSC) = [2^0-2^16]
   * freq_t = freq_c/prescaler+1
   * period = (1 + ARR)(1/freq_t)
   * duty cycle: CCR/ARR+1
  */ 
  TIM1_PSC = 39;  // (39+1) makes 100khz
  TIM1_ARR = 99;  // inturn makes the period .001s for pwm
  TIM1_CCR1 = 50; // duty cycle - 50% since counting from 0-99, will now be adjusted in the while loop
  
  // Main output enable (MOE)
  TIM1_BDTR |= 1<<15;

  // clear output compare mode bits in capture/compare mode register bits 16, [6:4]
  // for channel 1
  ra=TIM1_CCMR1;
  ra&=(~(1<<16));
  ra&=(~(7<<(1<<2)));

  // set to toggle (mode 0011)
  //ra|=( (3<<(1<<2))); // toggle mode (0011)
  ra|=( (6<<(1<<2))); // pwm mode 1 (0110)
  TIM1_CCMR1=ra;

  // select output polarity - active high '0' by default - commented out to prevent a little glitch at the very 
  // beginning of loading the program because of the register write and the processor performing that unnecessary 
  // instruction since 0 is the default
  //TIM1_CCER |= (~(1<<3));   // CC1NP (N stands for complementary, since this is a inverted timer channel

  // enable channel 1 complementary output
  TIM1_CCER |= (1<<2);

  // enable counter
  TIM1_CR1 |= 0x1u;

  uint8_t intensity=0;
  unsigned int i;

  while(1) {

    // dimming
    TIM1_CCR1 = 100-intensity;

    intensity += 1;

    // brightening
    if (intensity > 100) {
      intensity = 0;
      while (TIM1_CCR1 != 100) {
        intensity += 1;
        TIM1_CCR1 = intensity;
        for(i=0; i<9000; i++);
        if (TIM1_CCR1 == 100) {
          intensity = 0;
        }
      }
    }

    for (int i=0;i<9000;i++); 
  }

  return 0;
}
