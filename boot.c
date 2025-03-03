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
/*  0 */ (uint32_t) RAM_END,    // Initial SP value
/*  1 */ (uint32_t) main,       // Reset handler
/*  2 */ (uint32_t) nop,        // NMI
/*  3 */ (uint32_t) trap_loop,  // Hard fault handler
/*  4 */ (uint32_t) 0,          // reserved
/*  5 */ (uint32_t) 0,          // reserved
/*  6 */ (uint32_t) 0,          // reserved
/*  7 */ (uint32_t) 0,          // reserved
/*  8 */ (uint32_t) 0,          // reserved
/*  9 */ (uint32_t) 0,          // reserved
/* 10 */ (uint32_t) 0,          // reserved
/* 11 */ (uint32_t) nop,        // SVCall
/* 12 */ (uint32_t) 0,          // reserved
/* 13 */ (uint32_t) 0,          // reserved
/* 14 */ (uint32_t) nop,        // PendSV
/* 15 */ (uint32_t) nop,        // SysTick
/* 17 */ // IRQs
/* 16 */ (uint32_t) nop,
/* 18 */ (uint32_t) nop,
/* 19 */ (uint32_t) nop,
/* 20 */ (uint32_t) nop,
/* 21 */ (uint32_t) nop,
/* 22 */ (uint32_t) nop,
/* 23 */ (uint32_t) nop,
/* 24 */ (uint32_t) nop,
/* 25 */ (uint32_t) nop,
/* 26 */ (uint32_t) nop,
/* 27 */ (uint32_t) nop,
/* 28 */ (uint32_t) nop,
/* 29 */ (uint32_t) nop,
/* 30 */ (uint32_t) nop,
/* 31 */ (uint32_t) nop,
/* 32 */ (uint32_t) nop,
/* 33 */ (uint32_t) nop,
/* 34 */ (uint32_t) nop,
/* 35 */ (uint32_t) nop,
/* 36 */ (uint32_t) nop,
/* 37 */ (uint32_t) nop,
/* 38 */ (uint32_t) nop,
/* 39 */ (uint32_t) nop,
/* 40 */ (uint32_t) nop,
/* 41 */ (uint32_t) nop,
/* 42 */ (uint32_t) nop,
/* 43 */ (uint32_t) nop,
/* 44 */ (uint32_t) nop,
/* 45 */ (uint32_t) nop,
/* 46 */ (uint32_t) nop,
/* 47 */ (uint32_t) nop,
};
