#ifndef GPIO_H
#define GPIO_H

#include "types.h"

/*
 *  AHB2 Bus Base Declaration
 *  @brief this bus houses the GPIO ports
*/
#define AHB2_BASE                ((uint32_t)0x48000000)


/*
 *  GPIO Port Declarations - offset gathered from the mem map of the data sheet (p.108)
*/
#define GPIOA_BASE                    (AHB2_BASE + 0x0000)
#define GPIOB_BASE                    (AHB2_BASE + 0x0400)
#define GPIOC_BASE                    (AHB2_BASE + 0x0800)
#define GPIOD_BASE                    (AHB2_BASE + 0x0C00)
#define GPIOE_BASE                    (AHB2_BASE + 0x1000)
#define GPIOF_BASE                    (AHB2_BASE + 0x1400)
#define GPIOG_BASE                    (AHB2_BASE + 0x1800)
#define GPIOH_BASE                    (AHB2_BASE + 0x1C00)

/*
 *  @brief GPIO
*/
typedef struct 
{
  __IO uint32_t MODER;
  __IO uint32_t OTYPER;
  __IO uint32_t OSPEEDR;
  __IO uint32_t PUPDR;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t LCKR;
  __IO uint32_t AFRL;
  __IO uint32_t AFRH;
  __IO uint32_t BRR;
  __IO uint32_t ASCR;
} GPIOx_TypeDef;

#define GPIOA                ((GPIOx_TypeDef *) GPIOA_BASE)
#define GPIOB                ((GPIOx_TypeDef *) GPIOB_BASE)
#define GPIOE                ((GPIOx_TypeDef *) GPIOE_BASE)

#endif
