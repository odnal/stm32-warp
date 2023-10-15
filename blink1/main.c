#include <stdint.h>
#include "GPIO.h"
#include "RCC.h"
#include "types.h"


int main (void) 
{

  unsigned int ra;

  // Initialize the clock and bus for gpio port
  RCC_AHB2ENR |= RCC_AHB2ENR_GPIOB | RCC_AHB2ENR_GPIOE;

  ra = GPIOB->MODER;
  ra =  (~(3u<<(1<<2)));         // clear bits
  ra |= ( (1u<<(1<<2)));         // set bits  (01) - output mode
  GPIOB->MODER = ra;

  GPIOB->ODR |= 0x14; // odr offset
  GPIOB->ODR |= (1<<2);

  ra = GPIOE->MODER;
  ra =  (~(3u<<(1<<4)));         // clear bits
  ra |= ( (1u<<(1<<4)));         // set bits  (01) - output mode
  GPIOE->MODER = ra;

  GPIOE->ODR |= 0x14; // odr offset
  GPIOE->ODR |= (1<<8);

  //TODO: reset functions and blink the led
  //while (1) {}

  return 0;
}

