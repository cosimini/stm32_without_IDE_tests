#include <stdint.h>

// TODO: Right now I'm hardcoding the RAM size, this is not convenient. It is better to use the values provided by the linker.
// At the moment I'm unable to do so because the compiler is complaining about something.
//extern unsigned int _stack_reset_value;
const uint32_t RAM_END = 0x20002000;

extern int main(void); // Forward declare the main()

// Useful functions to fill the reset vector
void trap_loop(void) { while(1); }
void nop(void) {}

uint32_t __attribute__((section(".reset_vector"))) isr_vector[] = {
  (uint32_t) RAM_END,
  (uint32_t) main,
  (uint32_t) trap_loop,
  (uint32_t) 0,
  (uint32_t) 0,
  (uint32_t) 0,
  (uint32_t) 0,
  (uint32_t) 0,
  (uint32_t) 0,
  (uint32_t) 0,
  (uint32_t) nop,
  (uint32_t) 0,
  (uint32_t) 0,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) 0,
  // IRQs
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
  (uint32_t) nop,
};
