/*
 * Setting up the Cortex M0+ core
 */
#include <stdint.h>

#define NVIC_ISER 0xE000E100
#define NVIC_ICPR 0xE000E280

void initCore(void) {
  *(volatile uint32_t*) NVIC_ISER |= (1 << 9); // Enable IRQ 9
  *(volatile uint32_t*) NVIC_ISER |= (1 << 15); // Enable IRQ 15
}

void resetInterrupt(int IRQnumber) {  // Reset the specified interrupt
  if(IRQnumber < 0 || IRQnumber > 31) return;
  *(volatile uint32_t*) NVIC_ISER = (1 << IRQnumber);
}
