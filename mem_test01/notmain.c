//After each device reset, all peripheral clocks are disabled (except for the SRAM1/2 and
//Flash memory interface). Before using a peripheral you have to enable its clock in the
//RCC_AHBxENR and the RCC_APBxENR registers.

extern void dummy(unsigned int);
extern void PUT32(unsigned int, unsigned int);
extern unsigned int GET32(unsigned int);

#define RCC_BASE  0x40021000
#define RCC_AHB2ENR     (*((volatile unsigned int *) (RCC_BASE+0x4C)))

#define GPIOE_BASE 0x48001000
#define GPIOE_MODER     (*((volatile unsigned int *) (GPIOE_BASE+0x00)))
#define GPIOE_BSRR      (*((volatile unsigned int *) (GPIOE_BASE+0x18)))

#define SIZE        0x8000
#define SRAM2_BASE  0x10000000 

int notmain(void) {

  unsigned int ra;

  RCC_AHB2ENR |= 1<<4; // GPIOE port clock enable
  ra=GPIOE_MODER;
  ra&=(~(3<<(8<<1))); 
  ra|=( (1<<(8<<1))); 
  GPIOE_MODER=ra;
  

  //PUT32(SRAM2_BASE, 0x77777777);
  // Write to sram 
  for (ra=0; ra<SIZE; ra+=4) {
    PUT32(SRAM2_BASE+ra, ra);
  }

  // read sram - green led stays lit if no incorrect reads (may flicker if there are incorrect reads)
  while (1) {
    for (ra=0; ra<SIZE; ra+=4) {
      if (GET32(SRAM2_BASE+ra) != ra) 
        GPIOE_BSRR = 1<<(24); // reset
      else
        GPIOE_BSRR = 1<<(8);  // set
    }
  }

  return 0;
}
