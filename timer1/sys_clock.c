#include "sys_clock.h"

/* This code currently as I know it outputs 80Mhz frequency to the AHB/APB bus */
void System_Clock_Init (void) 
{

  // Flash memory is not fast enough for the 80Mhz clock source change, so adding latency - p.100
  FLASH_ACR &= 0x0;
  FLASH_ACR |= FLASH_ACR_LATENCY_2WS;

  // Enable the HSI oscillator and wait until the ready bit/flag is set
  RCC_CR |= RCC_CR_HSION;
  while ((RCC_CR & RCC_CR_HSIRDY) == 0);

  // Disbale the PLL and wait for ready flag to clear (already cleared but done here for completeness)
  RCC_CR &= ~RCC_CR_PLLON;
  while ((RCC_CR & RCC_CR_PLLRDY) == RCC_CR_PLLRDY);

  // Clear and set clock source to HSI as PLL
  RCC_PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;
  RCC_PLLCFGR |= RCC_PLLCFGR_PLLSRC;
  
  // Configure the PLL clock settings to 80Mhz
  RCC_PLLCFGR = (RCC_PLLCFGR & ~RCC_PLLCFGR_PLLM) | RCC_PLLCFGR_PLLM;
  RCC_PLLCFGR = (RCC_PLLCFGR & ~RCC_PLLCFGR_PLLN) | RCC_PLLCFGR_PLLN;

  // Take the 160Mhz and divide by 2 to get 80Mhz and enable the output
  RCC_PLLCFGR |= RCC_PLLCFGR_PLLR;
  RCC_PLLCFGR |= RCC_PLLCFGR_PLLREN;

  RCC_CR |= RCC_CR_PLLON;
  while ((RCC_CR & RCC_CR_PLLRDY) == 0);

  // Select PLL as the system clock - wait for hardware to update the status bit
  RCC_CFGR |= RCC_CFGR_SW;
  while ((RCC_CFGR & RCC_CFGR_SWS) != 0xC);
  
}
