#include "utils.h"

#define TIM2_OFFSET 0x40000000

#define TIM2_CR1    0x0000 // Control register 1
#define TIM2_DIER   0x000C // Interrupt enable register
#define TIM2_SR     0x0010 // Status register
#define TIM2_PSC    0x0028 // Prescaler value
#define TIM2_ARR    0x002C // Auto reload

void clearTIM2Interrupt(void) {
  // Reset the interrupt in the interrupts register
  resetInterrupt(15);
  // Reset the interrupt bits in the timer status register
  // TODO: Only a couple of bits need to be set to 0
  // But being the register initialized to 0, this was easier
  *(uint32_t*) (TIM2_OFFSET + TIM2_SR) = 0;
}

void initTIM2(void) {
  // Set the timer prescaler
  *(uint16_t*) (TIM2_OFFSET + TIM2_PSC) = (uint16_t) 16;
  // Enable interrupt
  *(uint16_t*) (TIM2_OFFSET + TIM2_DIER) |= 1;
  // Auto reload value
  *(uint32_t*) (TIM2_OFFSET + TIM2_ARR) = (uint32_t) 1000000;
  // Enable counter (CEN, bit 0)
  *(uint16_t*) (TIM2_OFFSET + TIM2_CR1) |= 1;
  // Iterrupts need to be clean in order for the NVIC to operate
  clearTIM2Interrupt();
}
