
#define PWR_BASE      0x40007000
#define PWR_CR1       (*((volatile unsigned int *) (PWR_BASE+0x00)))

#define RTC_BASE      0x40002800
#define RTC_WPR       (*((volatile unsigned int *) (RTC_BASE+0x24)))

#define RCC_BASE  0x40021000
#define RCC_BDCR          (*((volatile unsigned int *) (RCC_BASE+0x90)))   
#define RCC_CSR          (*((volatile unsigned int *) (RCC_BASE+0x94)))   
#define RCC_AHB2ENR      (*((volatile unsigned int *) (RCC_BASE+0x4C)))     // GPIO bus
#define RCC_APB1ENR1     (*((volatile unsigned int *) (RCC_BASE+0x58))) // LCD bus
#define RCC_APB1ENR1_LCDEN  0x00000200

// Pinouts
#define GPIOA_BASE  0x48000000
#define GPIOB_BASE  0x48000400
#define GPIOC_BASE  0x48000800
#define GPIOD_BASE  0x48000C00
#define GPIOE_BASE  0x48001000

#define GPIOA_MODER   (*((volatile unsigned int *) (GPIOA_BASE+0x00))) 
#define GPIOB_MODER   (*((volatile unsigned int *) (GPIOB_BASE+0x00))) 
#define GPIOC_MODER   (*((volatile unsigned int *) (GPIOC_BASE+0x00))) 
#define GPIOD_MODER   (*((volatile unsigned int *) (GPIOD_BASE+0x00))) 
#define GPIOE_MODER   (*((volatile unsigned int *) (GPIOE_BASE+0x00))) 

// all gpio lcd alternate functions seem to be at AF11
//#define AF11 0xB0000BBB //(1011)
#define GPIOA_AFRH   (*((volatile unsigned int *) (GPIOA_BASE+0x24))) 
#define GPIOA_AFRL   (*((volatile unsigned int *) (GPIOA_BASE+0x20))) 
#define GPIOB_AFR   (*((volatile unsigned int *) (GPIOB_BASE+0x24)))
#define GPIOC_AFRL   (*((volatile unsigned int *) (GPIOC_BASE+0x20)))
#define GPIOD_AFR   (*((volatile unsigned int *) (GPIOD_BASE+0x24))) 
#define GPIOE_AFR   (*((volatile unsigned int *) (GPIOE_BASE+0x24)))


#define LCD_BASE  0x40002400
#define LCD_CR            (*((volatile unsigned int *) (LCD_BASE+0x00)))
#define LCD_FCR           (*((volatile unsigned int *) (LCD_BASE+0x04)))
#define LCD_SR            (*((volatile unsigned int *) (LCD_BASE+0x08)))
#define LCD_CLR           (*((volatile unsigned int *) (LCD_BASE+0x0C)))
// COM ports
#define LCD_RAM0           (*((volatile unsigned int *) (LCD_BASE+0x14)))
//#define LCD_RAM0_0           (*((volatile unsigned int *) (LCD_BASE+0x18)))
//#define LCD_RAM1           (*((volatile unsigned int *) (LCD_BASE+0x1C)))
//#define LCD_RAM1_1           (*((volatile unsigned int *) (LCD_BASE+0x20)))
//#define LCD_RAM2           (*((volatile unsigned int *) (LCD_BASE+0x24)))
//#define LCD_RAM2_2           (*((volatile unsigned int *) (LCD_BASE+0x28)))
//#define LCD_RAM3           (*((volatile unsigned int *) (LCD_BASE+0x2C)))
//#define LCD_RAM3_3           (*((volatile unsigned int *) (LCD_BASE+0x30)))
//#define LCD_RAM4           (*((volatile unsigned int *) (LCD_BASE+0x34)))
//#define LCD_RAM4_4           (*((volatile unsigned int *) (LCD_BASE+0x38)))
//#define LCD_RAM5           (*((volatile unsigned int *) (LCD_BASE+0x3C)))
//#define LCD_RAM5_5           (*((volatile unsigned int *) (LCD_BASE+0x40)))
//#define LCD_RAM6           (*((volatile unsigned int *) (LCD_BASE+0x44)))
//#define LCD_RAM6_6           (*((volatile unsigned int *) (LCD_BASE+0x48)))
//#define LCD_RAM7           (*((volatile unsigned int *) (LCD_BASE+0x4C)))
//#define LCD_RAM7_7           (*((volatile unsigned int *) (LCD_BASE+0x50)))

void delay(unsigned int x) {
  for (int c=0; c <x; c++);
}

int main(void) {

  unsigned int ra;
  /* INIT */
  // enable gpio port clocks
  RCC_AHB2ENR |= 0x1f; // enable gpio a,b,c,d,e
  // enable alternate function mode on PA8 (com 0) and PA1 (seg 0)
  ra = GPIOA_MODER;
  ra ^= (1<<2);
  ra ^= (1<<16);
  GPIOA_MODER = ra;

  ra = GPIOC_MODER;
  ra ^= (1<<8);
  GPIOC_MODER = ra;

  // bunch of clock stuff to do before getting lcd clock source to work - write protection stuff we need to get rid of
  /*RCC_APB1ENR1 |= 0x10000000; // enable power interface clock
  delay(1000000);
  PWR_CR1 |= 0x100; // setting disable domain write protection bit
  while ((PWR_CR1 & 0x100) == 0); // ensuring bit is set otherwise stuck in loop
  RTC_WPR |= 0xCA;
  RTC_WPR |= 0x53;
 
  RCC_BDCR &= ~(0x1 |0x4);
  RCC_BDCR |= 0x00010000;
  RCC_BDCR &= ~(0x00010000);

  while ((RCC_BDCR & 0x2) == 0) {
    RCC_BDCR |= 0x1; // selecting lse oscillator
  }
  //select lse as RTC clock source
  RCC_BDCR |= 0x100;

  RCC_APB1ENR1 &= 0x00000000; // disable power interface clock*/

  RCC_APB1ENR1 |= 0x200; // enable lcd clock reg 

  // configure lcd gpio pins as alternatefunction mode
  GPIOA_AFRH |= 0xb0000bbb; // NOTE: these pins are found from the alternate function table (pins 8,9,10,15) more will need to be defined to use all gpio a lcd features
  //GPIOA_AFRL |= 0xbb00bbb0;
  GPIOC_AFRL |= 0x000b0000;

  // configure the lcd controller

  /* LOAD DATA */
  //LCD_RAM0 |= 0x7; // com 0 is this variable and 0x7 includes seg 0 (bit 0) being set 
  LCD_RAM0 |= (1<<22);

  /* PROGRAM FRAM RATE */

  /* ENABLE DISPLAY */
  LCD_CR |= 0x1;

  //LCD_SR |= (1<<2);
  //while((LCD_SR & 0x8) == 0);
  return 0;
}
