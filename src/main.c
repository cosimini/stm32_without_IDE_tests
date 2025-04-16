#include <stdbool.h>
#include <stdint.h>

void initClock();
void initGPIO();
void initUSART();
void initTIM2(void);

void setLED(bool state);
void USARTwrite(char c);
void clearTIM2Interrupt(void);

void IRQ15(void) {
  setLED(false);
  char message[] = "IRQ 15 called\r\n";
  for(uint32_t k = 0; k < sizeof(message); k++) USARTwrite(message[k]);
  clearTIM2Interrupt();
}

int main(void) {
  // Configure hardware
  initClock();
  initGPIO();
  initUSART();
  initTIM2();
  // Send greetings over usart
  setLED(true);
  char greet[] = "Hello, word!\r\n";
  for(uint32_t k = 0; k < sizeof(greet); k++) USARTwrite(greet[k]);
  while(1) { /* MAIN INFINITE LOOP */ }
}
