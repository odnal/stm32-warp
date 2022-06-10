#ifndef TIM1_H
#define TIM1_H

#include <stdint.h>

/* DEFINES */
#define RCC_BASE              0x40021000u
#define RCC_APB2ENR           (*((volatile uint32_t *) (RCC_BASE+0x60)))  // TIM1 bus
#define RCC_APB2ENR_TIM1EN    0x00000800u

#define TIM1_BASE             0x40012C00u
#define TIM1_CR1              (*((volatile uint32_t *) (TIM1_BASE+0x00)))
#define TIM1_PSC              (*((volatile uint32_t *) (TIM1_BASE+0x28)))
#define TIM1_ARR              (*((volatile uint32_t *) (TIM1_BASE+0x2c)))
#define TIM1_CCR1             (*((volatile uint32_t *) (TIM1_BASE+0x34)))
#define TIM1_CCER             (*((volatile uint32_t *) (TIM1_BASE+0x20)))
#define TIM1_BDTR             (*((volatile uint32_t *) (TIM1_BASE+0x44)))
#define TIM1_CCMR1            (*((volatile uint32_t *) (TIM1_BASE+0x18)))

void TIM1_Toggle_Init (void);

#endif
