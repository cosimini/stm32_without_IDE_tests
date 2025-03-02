#include <stdint.h>

int main(void) {
  // I should be able to see this at the beginning of the stack
  char string[] = "hello, word!";
  // Same for those
  uint32_t c = 0;
  uint32_t a = 42;
  // Increment the value of c. This is useful to check that the processor is running.
  while(1) {
    c++;
  }
}
