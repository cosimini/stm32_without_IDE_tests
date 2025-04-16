/*
 * Setting up the Cortex M0+ core
 */
#include <stdint.h>
#include "utils.h"

#define NVIC_ISER 0xE000E100
#define NVIC_ICPR 0xE000E280
#define TIM2_OFFSET 0x40000000
#define TIM2_SR     0x0010 // Status register

void initCore(void) {
  uint32_t* NVIC_set_reset_register = (uint32_t*) NVIC_ISER;
  setbit32(NVIC_set_reset_register, 15, 1);
}

void resetInterrupt(int idx) {
  uint32_t* NVIC_clear_interrupts_register = (uint32_t*) NVIC_ISER;
  *NVIC_clear_interrupts_register = 0b1 << idx;
}
