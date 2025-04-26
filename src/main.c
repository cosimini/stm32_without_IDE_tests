#include <stdbool.h>
#include <stdint.h>

#define USART2_RX_BUFFER_SIZE 255

// Forward declare initialization functions
void initClock(void);
void initCore(void);
void initGPIO(void);
void initUSART(void);
void initTIM2(void);
void initDMA(uint8_t* buf);

// Forward declaration of used functions
void setLED(bool state);
void USARTwrite(char c);
void clearTIM2Interrupt(void);
void receiveDataUSART2(int size);

// The good, old, global variables
bool ledStatus;
int IRQsCounter;
uint8_t USART2_buffer[USART2_RX_BUFFER_SIZE];

// Interrupt  9 handler
void clearDMAInterruptFlags(int ch, int b);
void IRQ09(void) {
  clearDMAInterruptFlags(0, 5);
  receiveDataUSART2(16);
  for(uint32_t k = 0; k < USART2_RX_BUFFER_SIZE; k++) {
    if(USART2_buffer[k] > 0) USARTwrite(USART2_buffer[k]);
  }
  USARTwrite('\r');
  USARTwrite('\n');
}

// Interrupt 15 handler
void IRQ15(void) {
  ledStatus = !ledStatus;
  IRQsCounter++;
  setLED(ledStatus);
  char message[] = "beep\r\n";
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
  initDMA(USART2_buffer);
  // Init global variables
  ledStatus = true;
  IRQsCounter = 0;
  for(int k = 0; k < USART2_RX_BUFFER_SIZE; k++) { USART2_buffer[k] = 0; }
  // Send greetings over usart
  char greet[] = "Hello, word!\r\n";
  for(uint32_t k = 0; k < sizeof(greet); k++) USARTwrite(greet[k]);
  // Enable USART2 receiver via DMA
  receiveDataUSART2(16);
  while(1) { /* MAIN INFINITE LOOP */ }
}
