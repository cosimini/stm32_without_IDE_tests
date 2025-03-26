#include <stdbool.h>
#include <stdint.h>

void setClock();
void initGPIO();
void setLED(bool state);
void setUSART();
void USART_send();

int main(void) {
  // Configure hardware
  setClock();
  initGPIO();
  setUSART();
  // Send greetings over usart
  char greet[] = "Hello, word!\n";
  for(uint32_t k = 0; k < sizeof(greet); k++) USART_send(greet[k]);
  // Turn on LED
  setLED(true);
  // Busy loop for eternity
  while(1); // Trap execution at the end of main
}
