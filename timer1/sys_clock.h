#ifndef   SYS_CLOCK_H
#define SYS_CLOCK_H

#include <stdint.h>

/* DEFINES */
#define RCC_BASE                0x40021000u
#define RCC_CR                  (*((volatile uint32_t *) (RCC_BASE+0x00)))
//#define RCC_ICSR                (*((volatile uint32_t *) (RCC_BASE+0x04)))
#define RCC_CFGR                (*((volatile uint32_t *) (RCC_BASE+0x08)))
#define RCC_PLLCFGR             (*((volatile uint32_t *) (RCC_BASE+0x0C)))


/* Internal register bit maps */
#define RCC_CR_HSION                 0x00000100u
#define RCC_CR_HSIRDY                0x00000400u
#define RCC_CR_PLLON                 0x01000000u
#define RCC_CR_PLLRDY                0x02000000u

#define RCC_PLLCFGR_PLLSRC           0x00000002u
#define RCC_PLLCFGR_PLLM             0x00000010u
#define RCC_PLLCFGR_PLLN             0x00001400u
#define RCC_PLLCFGR_PLLR             0x00000000u  // divide by 2
#define RCC_PLLCFGR_PLLREN           0x01000000u

#define RCC_CFGR_SW                  0x00000003u
#define RCC_CFGR_SWS                 0x0000000Cu

#define FLASH_BASE                   0x40022000u
#define FLASH_ACR                    (*((volatile uint32_t *) (FLASH_BASE+0x00)))
#define FLASH_ACR_LATENCY_2WS        0x00000002u

void System_Clock_Init (void);

#endif
