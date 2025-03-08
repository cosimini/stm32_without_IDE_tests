#include <stdint.h>

int main(void) {
  // Dummy execution that might be useful
  // for(int k = 0; k < 100; k++) {}

  // Turn on LED
  // LED is connected on PC6, i.e. GPIOC on bit 6
  // MODE : 01
  // OTYPE : 0
  // PUPD  : 0 0 
  volatile uint32_t* clock_reg = (volatile uint32_t*) 0x40021034;
  volatile uint32_t* moder_reg = (volatile uint32_t*) 0x50000800;
  volatile uint32_t* otype_reg = (volatile uint32_t*) 0x50000804;
  volatile uint32_t* pupdr_reg = (volatile uint32_t*) 0x5000080C;
  volatile uint32_t* outpt_reg = (volatile uint32_t*) 0x50000814;

  volatile uint32_t value = 0;

  // Enable clocks
  value = *clock_reg;
  *clock_reg = value | 0b00000000000000000000000000111111;
  // set mode
  value = *moder_reg & 0b11111111111111111100111111111111;
  *moder_reg = value | 0b00000000000000000001000000000000;
  // set type
  value = *otype_reg & 0b11111111111111111111111110111111;
  *otype_reg = value | 0b00000000000000000000000000000000;
  // set pull up/down
  value = *pupdr_reg & 0b11111111111111111100111111111111;
  *pupdr_reg = value | 0b00000000000000000000000000000000;
  // Turn on
  value = *outpt_reg & 0b11111111111111111111111110111111;
  *outpt_reg = value | 0b00000000000000000000000001000000;

  // Infinite loop
  while(1) { }
}
