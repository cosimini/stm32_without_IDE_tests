#include <stdbool.h>
#include <stdint.h>

// Forward declare initialization functions
void initClock(void);
void initCore(void);
void initGPIO(void);
void initUSART(void);
void initTIM2(void);

// Forward declaration of used functions
void setLED(bool state);
void USARTwrite(char c);
void clearTIM2Interrupt(void);

// The good, old, global variables
bool ledStatus;
int IRQsCounter;

// Interrupt 15 handler
void IRQ15(void) {
  ledStatus = !ledStatus;
  IRQsCounter++;
  setLED(ledStatus);
  char message[] = "IRQ 15 called\r\n";
  for(uint32_t k = 0; k < sizeof(message); k++) USARTwrite(message[k]);
  clearTIM2Interrupt();
}

int main(void) {
  // Configure hardware
  initClock();
  initCore();
  initGPIO();
  initUSART();
  initTIM2();
  // Send greetings over usart
  ledStatus = false;
  IRQsCounter = 0;
  char greet[] = "Hello, word!\r\n";
  for(uint32_t k = 0; k < sizeof(greet); k++) USARTwrite(greet[k]);
  while(1) { /* MAIN INFINITE LOOP */ }
}
