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

void uart_init() {
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
  //ra = GET32(USART2_BASE+0x0);
  //ra |= (1<<28) | (1<<12);
  //ra ^= (1<<28) | (1<<12);
  //PUT32(USART2_BASE+0x0, ra);

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
  //PUT32(USART2_BASE+0x04, 0x0);

  // 4. Enable USART by writing the UE bit 
  PUT32(USART2_BASE+0x0, 0x1);

  // 5. Selct DMA for multibuffer communication - SKIP dont think needed atm
  //PUT32(USART2_BASE+0x08, 0x0080);

  // 6. Set the TE bit in USART_CR1 to send idle frame in first transmission
  ra = GET32(USART2_BASE+0x0);
  ra |= (1<<3);
  PUT32(USART2_BASE+0x0, ra);

}

void uart_send (unsigned int data) {
  while (((GET32(USART2_BASE+0x1C)) & 0x40) == 0) continue;
  PUT32(USART2_BASE+0x28, data);
}

void hexstrings (unsigned int data) {
  unsigned int ra, rb;
  unsigned int offset_dec = 0x30;
  unsigned int offset_char = 0x37;

  rb = 32;
  while (1) {
    rb -= 4;
    ra = (data>>rb)&0xF;
    if (ra > 9) ra += offset_char; else ra += offset_dec;
    uart_send(ra);
    if (rb == 0) break;
  }

  uart_send(0x20); // <space> (use if you want data side by side on screen for better visual)
}

void binstrings (unsigned int data) {
  unsigned int ra, rb;
  unsigned int offset_dec = 0x30;

  rb = 32;
  while (1) {
    rb -= 1;
    ra = (data>>rb)&0x1;
    ra += 0x30;
    uart_send(ra);
    if (rb == 0) break;
  }

  uart_send(0x0D);  // return character
  uart_send(0x0A);  // new line
  //uart_send(0x20); 

}

void hexstring (unsigned int data) {
  hexstrings(data);
  uart_send(0x0D);  // return character
  uart_send(0x0A);  // new line
}

int main(void) 
{

  uart_init();
  // 7. Write the data to send in the transmit data register
  // 8. Wait for transmission complete bit to be set (0x40)

  hexstrings(0xaaaabbbb); hexstring(0x9);
  binstrings(0xaaaabbbb);
  binstrings(0x9);

  return 0;
}


