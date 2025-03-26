#include <stdint.h>

//extern unsigned int _stack_reset_value;
const uint32_t RAM_END = 0x20001FFF;

int main(void);  // Forward declare the main()
void trap(void); // Trap the execution indefietely
void noop(void); // Do nothing

// The vector table
uint32_t __attribute__((section(".reset_vector"))) isr_vector[] = {
  (uint32_t) RAM_END,  //  0 - Initial SP value
  (uint32_t) main,     //  1 - Reset handler
  (uint32_t) noop,     //  2 - NMI
  (uint32_t) trap,     //  3 - Hard fault handler
  (uint32_t) 0,        //  4 - reserved
  (uint32_t) 0,        //  5 - reserved
  (uint32_t) 0,        //  6 - reserved
  (uint32_t) 0,        //  7 - reserved
  (uint32_t) 0,        //  8 - reserved
  (uint32_t) 0,        //  9 - reserved
  (uint32_t) 0,        // 10 - reserved
  (uint32_t) noop,     // 11 - SVCall
  (uint32_t) 0,        // 12 - reserved
  (uint32_t) 0,        // 13 - reserved
  (uint32_t) noop,     // 14 - PendSV
  (uint32_t) noop,     // 15 - SysTick
  (uint32_t) noop,     // 16 - IRQ 0
  (uint32_t) noop,     // 17 - IRQ 1
  (uint32_t) noop,     // 18 - IRQ 2
  (uint32_t) noop,     // 19 - IRQ 3
  (uint32_t) noop,     // 20 - IRQ 4
  (uint32_t) noop,     // 21 - IRQ 5
  (uint32_t) noop,     // 22 - IRQ 6
  (uint32_t) noop,     // 23 - IRQ 7
  (uint32_t) noop,     // 24 - IRQ 8
  (uint32_t) noop,     // 25 - IRQ 9
  (uint32_t) noop,     // 26 - IRQ 10
  (uint32_t) noop,     // 27 - IRQ 11
  (uint32_t) noop,     // 28 - IRQ 12
  (uint32_t) noop,     // 29 - IRQ 13
  (uint32_t) noop,     // 30 - IRQ 14
  (uint32_t) noop,     // 31 - IRQ 15
  (uint32_t) noop,     // 32 - IRQ 16
  (uint32_t) noop,     // 33 - IRQ 17
  (uint32_t) noop,     // 34 - IRQ 18
  (uint32_t) noop,     // 35 - IRQ 19
  (uint32_t) noop,     // 36 - IRQ 20
  (uint32_t) noop,     // 37 - IRQ 21
  (uint32_t) noop,     // 38 - IRQ 22
  (uint32_t) noop,     // 39 - IRQ 23
  (uint32_t) noop,     // 40 - IRQ 24
  (uint32_t) noop,     // 41 - IRQ 25
  (uint32_t) noop,     // 42 - IRQ 26
  (uint32_t) noop,     // 43 - IRQ 27
  (uint32_t) noop,     // 44 - IRQ 28
  (uint32_t) noop,     // 45 - IRQ 29
  (uint32_t) noop,     // 46 - IRQ 30
  (uint32_t) noop,     // 47 - IRQ 31
};

// Useful functions to fill the reset vector
void trap(void) { while(1); }  // Trap the execution indefietely
void noop(void) {}             // Do nothing

