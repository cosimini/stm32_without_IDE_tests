#include <stdint.h>
#include "utils.h"

#define USART2_OFFSET 0x40004400
#define USART2_CR2 0x0004
#define USART2_CR3 0x0008
#define USART2_BRR 0x000C
#define USART2_TDR 0x0028
#define USART2_ISR 0x001C

void initUSART(void) {
  // USART2_CR1
  regConf conf = {.reg = ((uint32_t*) (USART2_OFFSET + 0x0000)), .idx = 0, .val = 0};
  setConf(&conf, 28, 0); // 1. Set word length
  setConf(&conf, 12, 0); // 0. Set word length
  setConf(&conf, 15, 0); // Oversampling by 16
  applyConf(&conf);

  // USART2_CR2
  conf.reg = (uint32_t*) (USART2_OFFSET + USART2_CR2);
  setConf(&conf, 13, 0); // 1. 1 stop bits
  setConf(&conf, 12, 0); // 0. 1 stop bits
  setConf(&conf, 11, 0); // Enable clock pin
  applyConf(&conf);

  // USART2_CR3
  conf.reg = (uint32_t*) (USART2_OFFSET + USART2_CR3);
  setConf(&conf, 6, 1); // Enable DMA receive
  applyConf(&conf);

  // USART2_BRR
  uint32_t* usart_brr_register = (uint32_t*) (USART2_OFFSET + USART2_BRR);
  *usart_brr_register = (*usart_brr_register & 0xffff0000) | 139;  // Prescaler: 16M / 139 ~= 115200

  // Enable
  conf.reg = ((uint32_t*) (USART2_OFFSET + 0x0000));
  setConf(&conf, 2, 1);  // Enable receiver
  setConf(&conf, 0, 1);  // Enable USART2 after the configuration is done
  applyConf(&conf);
}

void USARTwrite(char c) {
  uint32_t* CR1 = (uint32_t*) (USART2_OFFSET);
  char* TDR = (char*) (USART2_OFFSET + USART2_TDR);
  volatile uint32_t* ISR = (uint32_t*) (USART2_OFFSET + USART2_ISR); // volatile is needed if -Os is enabled
  setbit32(CR1, 3, 1);              // Set TE bit
  *TDR = c;                         // Write the data
  while((*ISR & (0b1 << 6)) == 0);  // Wait until the Transmission Complete bit is set
  setbit32(CR1, 3, 0);              // Reset TE bit
}
