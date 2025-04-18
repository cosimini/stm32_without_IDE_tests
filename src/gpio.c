#include <stdint.h>
#include <stdbool.h>
#include "utils.h"

#define GPIOA_OFFSET 0x50000000
#define GPIOB_OFFSET 0x50000400
#define GPIOC_OFFSET 0x50000800
#define GPIOD_OFFSET 0x50000C00
#define GPIOE_OFFSET 0x50001000
#define GPIOF_OFFSET 0x50001400

#define GPIO_MODESET 0x0000
#define GPIO_TYPESET 0x0004
#define GPIO_OSPEEDR 0x0008
#define GPIO_PULLSET 0x000C
#define GPIO_OUT_SET 0x0014
#define GPIO_ALTFUNR 0x0020

void initGPIO() {
  regConf conf = {0, 0, 0};
  // Port A - PA2 and PA3's AF1 is USART2
  conf.reg = (uint32_t*) (GPIOA_OFFSET + GPIO_MODESET);
  setConf(&conf, 4, 0);  // Set pin to use AF
  setConf(&conf, 5, 1);  // Set pin to use AF
  setConf(&conf, 6, 0);  // Set pin to use AF
  setConf(&conf, 7, 1);  // Set pin to use AF
  applyConf(&conf);
  conf.reg =(uint32_t*) (GPIOA_OFFSET + GPIO_OSPEEDR);
  setConf(&conf, 4 ,1);  // Set max speed
  setConf(&conf, 5 ,1);  // Set max speed
  setConf(&conf, 6 ,1);  // Set max speed
  setConf(&conf, 7 ,1);  // Set max speed
  applyConf(&conf);
  conf.reg = (uint32_t*) (GPIOA_OFFSET + GPIO_ALTFUNR);
  setConf(&conf,  8, 1); // Select AF1
  setConf(&conf, 12, 1); // Select AF1
  applyConf(&conf);

  // Port C - PC6 is connected to the user LED
  conf.reg = (uint32_t*) (GPIOC_OFFSET + GPIO_MODESET);
  setConf(&conf, 12, 1); // Output
  setConf(&conf, 13, 0); // Output
  applyConf(&conf);
  conf.reg =(uint32_t*) (GPIOC_OFFSET + GPIO_TYPESET);
  setConf(&conf, 6 ,0);
  applyConf(&conf);
  conf.reg = (uint32_t*) (GPIOC_OFFSET + GPIO_PULLSET);
  setConf(&conf, 6, 0); // No push/pull
  setConf(&conf, 7, 0); // No push/pull
  applyConf(&conf);
}

// Set/unset PC6 depending on bool 'state'
void setLED(bool state) {
  if(state) 
    *(uint32_t*) (GPIOC_OFFSET + GPIO_OUT_SET) |= (1 << 6);
  else
    *(uint32_t*) (GPIOC_OFFSET + GPIO_OUT_SET) &= ~(1 << 6);
}
