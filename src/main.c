#include <stdint.h>

// GPIO stuff
#define GPIO_OFFSET 0x50000000
#define GPIOC_OFFSET 0x800
#define GPIO_MODESET 0x000
#define GPIO_TYPESET 0x004
#define GPIO_PULLSET 0x00C
#define GPIO_OUT_SET 0x014

#define SET_BIT_32(reg, idx, val) *reg = (*reg & ~((uint32_t) 0b01 << idx)) | ((uint32_t) val << idx)
#define SET_PAIR_32(reg, idx, val_0, val_1) *reg = (*reg & ~((uint32_t) 0b11 << (2 * idx)) | ((uint32_t) (val_0 | (val_1 << 1)) << (2 * idx)))

int main(void) {
  // Dummy execution that might be useful
  // for(int k = 0; k < 100; k++) {}

  // Turn on LED
  // LED is connected on PC6, i.e. GPIOC on bit 6
  // MODE : 01
  // OTYPE : 0
  // PUPD  : 0 0 

  // TODO: Make it easyer to address this
  uint32_t* clock_reg = (uint32_t*) 0x40021034;
  //GPIO_OFFSET + GPIOC_OFFSET + GPIO_MODESET
  uint32_t* moder_reg = (uint32_t*) 0x50000800;
  //GPIO_OFFSET + GPIOC_OFFSET + GPIO_TYPESET
  uint32_t* otype_reg = (uint32_t*) 0x50000804;
  //GPIO_OFFSET + GPIOC_OFFSET + GPIO_PULLSET
  uint32_t* pupdr_reg = (uint32_t*) 0x5000080C;
  //GPIO_OFFSET + GPIOC_OFFSET + GPIO_OUT_SET
  uint32_t* outpt_reg = (uint32_t*) 0x50000814;


  uint32_t value = 0;

  // Enable clocks
  SET_BIT_32(clock_reg, 2, 1);
  // set mode
  SET_PAIR_32(moder_reg, 6, 1, 0);
  // set type
  SET_BIT_32(otype_reg, 6, 0);
  // set pull up/down
  SET_PAIR_32(pupdr_reg, 6, 0, 0);
  // Turn on
  SET_BIT_32(outpt_reg, 6, 1);

  // Infinite loop
  while(1) { }
}
