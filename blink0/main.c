extern void dummy ( unsigned int );

#define RCC_BASE  0x40021000
#define RCC_AHB2ENR     (*((volatile unsigned int *) (RCC_BASE+0x4C)))

#define GPIOA_BASE 0x48000000
#define GPIOA_MODER     (*((volatile unsigned int *) (GPIOA_BASE+0x00)))
#define GPIOA_BSRR      (*((volatile unsigned int *) (GPIOA_BASE+0x18)))

#define GPIOB_BASE 0x48000400
#define GPIOB_MODER     (*((volatile unsigned int *) (GPIOB_BASE+0x00)))
#define GPIOB_BSRR      (*((volatile unsigned int *) (GPIOB_BASE+0x18)))

#define GPIOE_BASE 0x48001000
#define GPIOE_MODER     (*((volatile unsigned int *) (GPIOE_BASE+0x00)))
#define GPIOE_BSRR      (*((volatile unsigned int *) (GPIOE_BASE+0x18)))

int main(void)
{
  unsigned int ra;

  RCC_AHB2ENR |= 1<<1; // GPIOB port clock enable
  ra=GPIOB_MODER;
  ra&=(~(3<<(2<<1))); 
  ra|=( (1<<(2<<1))); 
  GPIOB_MODER=ra;      // enabled for general purpose output

  RCC_AHB2ENR |= 1<<4; // GPIOE port clock enable
  ra=GPIOE_MODER;
  ra&=(~(3<<(8<<1))); 
  ra|=( (1<<(8<<1))); 
  GPIOE_MODER=ra;

  RCC_AHB2ENR |= 1<<0; // GPIOA port clock enable
  ra=GPIOA_MODER;
  ra&=(~(3<<(1<<1))); 
  ra|=( (1<<(1<<1))); 
  GPIOA_MODER=ra;

  // PA2 - clock already enabled for port A
  ra=GPIOA_MODER;
  ra&=(~(3<<(1<<2))); 
  ra|=( (1<<(1<<2))); 
  GPIOA_MODER=ra;

  while(1)
  {
     GPIOB_BSRR = 1<<(18);  // reset
     GPIOE_BSRR = 1<<(8);   // set
     GPIOA_BSRR = 1<<(1);   // pin 1 set
     GPIOA_BSRR = 1<<(2);   // pin 2 set
     for(ra=0;ra<0x200000;ra++) dummy(ra);
     GPIOB_BSRR = 1<<(2);   // set 
     GPIOE_BSRR = 1<<(24);  // reset
     GPIOA_BSRR = 1<<(17);  // pin 1 reset
     GPIOA_BSRR = 1<<(18);  // pin 2 reset
     for(ra=0;ra<0x200000;ra++) dummy(ra);
  }

     return(0);
}

