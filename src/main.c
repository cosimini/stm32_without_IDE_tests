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

  uint32_t* clock_reg = (uint32_t*) 0x40021034;
  uint32_t* moder_reg = (uint32_t*) (GPIO_OFFSET + GPIOC_OFFSET + GPIO_MODESET); // 0x50000800
  uint32_t* otype_reg = (uint32_t*) (GPIO_OFFSET + GPIOC_OFFSET + GPIO_TYPESET); // 0x50000804
  uint32_t* pupdr_reg = (uint32_t*) (GPIO_OFFSET + GPIOC_OFFSET + GPIO_PULLSET); // 0x5000080C
  uint32_t* outpt_reg = (uint32_t*) (GPIO_OFFSET + GPIOC_OFFSET + GPIO_OUT_SET); // 0x50000814;

  SET_BIT_32(clock_reg, 2, 1);     // Enable clock on GPIO C
  SET_PAIR_32(moder_reg, 6, 1, 0); // Set mode for GPIO C 6
  SET_BIT_32(otype_reg, 6, 0);     // Set output type on C 6
  SET_PAIR_32(pupdr_reg, 6, 0, 0); // Disable pull down/up
  SET_BIT_32(outpt_reg, 6, 1);     // Turn on bit 6 of GPIO C

  while(1) { /*infinite loop */ }
}
