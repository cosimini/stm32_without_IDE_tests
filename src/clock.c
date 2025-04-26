/*
 * Configure clocks as needed
 */

#include "utils.h"

#define RCC_OFFSET  0x40021000
#define RCC_CFGR    0x08
#define RCC_IOPENR  0x34
#define RCC_AHBENR  0x38
#define RCC_ABPENR1 0x3C
#define RCC_CCIPR   0x54

void initClock(void) {
  // RCC_CR
  regConf conf = {.reg = ((uint32_t*) (RCC_OFFSET)), .idx = 0, .val = 0};
  setConf(&conf,  8, 1); // Enable HSI 16
  setConf(&conf, 11, 0); // 0. Set HSI divider to 1
  setConf(&conf, 12, 0); // 1. Set HSI divider to 1
  setConf(&conf, 13, 0); // 2. Set HSI divider to 1
  applyConf(&conf);

  // RCC_CFGR
  conf.reg = (uint32_t*) (RCC_OFFSET + RCC_CFGR);
  setConf(&conf,  0, 0); // 0. Set system clock to HSI
  setConf(&conf,  1, 0); // 1. Set system clock to HSI
  setConf(&conf,  2, 0); // 2. Set system clock to HSI
  setConf(&conf, 14, 0); // Set APB prescaler to 1
  setConf(&conf, 11, 0); // Set AHB prescaler to 1
  applyConf(&conf);

  // RCC_IOPENR
  conf.reg = (uint32_t*) (RCC_OFFSET + RCC_IOPENR);
  setConf(&conf, 0, 1); // PA, here USART2 is connected
  setConf(&conf, 2, 1); // PC, here the user LED is connected
  applyConf(&conf);

  // RCC_AHBENR
  conf.reg = (uint32_t*) (RCC_OFFSET + RCC_AHBENR);
  setConf(&conf, 0, 1); // DMA1 clock enable
  applyConf(&conf);

  // RCC_ABPENR1
  conf.reg = (uint32_t*) (RCC_OFFSET + RCC_ABPENR1);
  setConf(&conf,  0, 1); // Enable TIM2's clock
  setConf(&conf, 17, 1); // Enable USART2's clock
  applyConf(&conf);

  // RCC_CCIPR
  conf.reg = (uint32_t*) (RCC_OFFSET + RCC_CCIPR);
  setConf(&conf, 3, 1); // 0. Use HSI16 on USART2
  setConf(&conf, 2, 0); // 1. Use HSI16 on USART2
  applyConf(&conf);
}
