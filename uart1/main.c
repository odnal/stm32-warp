#include <stdio.h>


extern void PUT32 (unsigned int, unsigned int);
extern unsigned int GET32 (unsigned int);

// Pin A2 USART2_TX
// Pin A3 USART2_RX
#define USART2_BASE     0x40004400


#define RCC_BASE        0x40021000
#define RCC_APB1ENR     (RCC_BASE+0x58)  // usart2 b17
#define RCC_AHB2ENR     (RCC_BASE+0x4C)

#define GPIOA_BASE      0x48000000
#define GPIOA_MODER     (GPIOA_BASE+0x00)
#define GPIOA_AFRL      (GPIOA_BASE+0x20)

unsigned int *uart_send(int *c);

int main(void) 
{
  unsigned int ra;

  // Init clocks
  ra = GET32(RCC_APB1ENR);
  ra |= (1<<17);
  PUT32(RCC_APB1ENR, ra);

  ra = GET32(RCC_AHB2ENR);
  ra |= 0x1;
  PUT32(RCC_AHB2ENR, ra);

  // Set up PA3 as alternate function mode
  ra = GET32(GPIOA_MODER);
  ra ^= (1<<4);
  PUT32(GPIOA_MODER, ra);
  PUT32(GPIOA_AFRL, (7<<8));
  
  // following character transmission procedure p.1347
  // 1. 8 data bits
  ra = GET32(USART2_BASE+0x0);
  ra |= (1<<28) | (1<<12);
  ra ^= (1<<28) | (1<<12);
  PUT32(USART2_BASE+0x0, ra);

  // 2. Select baud rate
  /*
   *  baud = fclk/usart_div
   *
   *  115200 = 4Mhz/usart_div
   *  usart_div = 34.7222
   *  BRR = usart_div = 34.7222 = h22
   */
  PUT32(USART2_BASE+0x0C, 0x0022);
  //PUT32(USART2_BASE+0x04, 0x00100000);

  // 3. Program number of stop bits
  PUT32(USART2_BASE+0x04, 0x0);

  // 4. Enable USART by writing the UE bit 
  PUT32(USART2_BASE+0x0, 0x1);

  // 5. Selct DMA for multibuffer communication - SKIP dont think needed atm
  //PUT32(USART2_BASE+0x08, 0x0080);

  // 6. Set the TE bit in USART_CR1 to send idle frame in first transmission
  ra = GET32(USART2_BASE+0x0);
  ra |= (1<<3);
  PUT32(USART2_BASE+0x0, ra);


  // 7. Write the data to send in the transmit data register
  // 8. Wait for transmission complete bit to be set

  unsigned int count = 1;
  char *txBuf = {0};
  //sprintf(txBuf, "%d \r\n", count);
  //printf("%d", count);
  while (1) {
    while ( (GET32(USART2_BASE+0x1C) & 0x40) == 0);
    //PUT32(USART2_BASE+0x28, 0x55);
    uart_send("A");
    while ( (GET32(USART2_BASE+0x1C) & 0x40) == 0);
    PUT32(USART2_BASE+0x28, 0x0D);
    while ( (GET32(USART2_BASE+0x1C) & 0x40) == 0);
    PUT32(USART2_BASE+0x28, 0x0A);
    for (int i = 0; i<10000; i++);
  }

  return 0;
}


unsigned int *uart_send(unsigned int *c)
{
  unsigned int *transmit_reg = GET32(USART2_BASE+0x28);
  transmit_reg |= c;

  return transmit_reg;
}

