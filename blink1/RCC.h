#ifndef RCC_H
#define RCC_H

#include "types.h"

/*
 *  RCC Base Declaration
 *  @brief Reset Control Clock
*/
#define RCC_BASE                0x40021000

/*
 *  @brief AHB2ENR address offset to be able to clock enable the
 *  GPIO ports by setting the corresponding bit high (p.252)
*/
#define RCC_AHB2ENR             (*((__IO unsigned int*)(RCC_BASE + 0x4C)))



/*
 *  @brief clock enable port bits
*/
#define RCC_AHB2ENR_GPIOA       (uint32_t)0x00000001
#define RCC_AHB2ENR_GPIOB       (uint32_t)0x00000002
#define RCC_AHB2ENR_GPIOC       (uint32_t)0x00000004
#define RCC_AHB2ENR_GPIOD       (uint32_t)0x00000008
#define RCC_AHB2ENR_GPIOE       (uint32_t)0x00000010
#define RCC_AHB2ENR_GPIOF       (uint32_t)0x00000020
#define RCC_AHB2ENR_GPIOG       (uint32_t)0x00000040
#define RCC_AHB2ENR_GPIOH       (uint32_t)0x00000080


#endif
