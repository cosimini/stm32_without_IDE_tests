/*
 * Set up the ADCs
 * For the time being, only used to sample the IC temperature
 */

#include <stdint.h>

#define ADC_OFFSET  0x40012400
#define ADC_ISR     (ADC_OFFSET + 0x000)
#define ADC_IER     (ADC_OFFSET + 0x000)
#define ADC_CR      (ADC_OFFSET + 0x008)
#define ADC_CFGR1   (ADC_OFFSET + 0x00C)
#define ADC_CFGR2   (ADC_OFFSET + 0x010)
#define ADC_SMPR    (ADC_OFFSET + 0x014)
#define ADC_AWD1TR  (ADC_OFFSET + 0x020)
#define ADC_AWD2TR  (ADC_OFFSET + 0x024)
#define ADC_CHSELR  (ADC_OFFSET + 0x028)
#define ADC_AWD3TR  (ADC_OFFSET + 0x02C)
#define ADC_DR      (ADC_OFFSET + 0x040)
#define ADC_AWD2CR  (ADC_OFFSET + 0x0A0)
#define ADC_AWD3CR  (ADC_OFFSET + 0x0A4)
#define ADC_CALFACT (ADC_OFFSET + 0x0B4)
#define ADC_CCR     (ADC_OFFSET + 0x308)

void initADCs(void) {
  *(uint32_t*) ADC_CR |= (1 << 28); // Enable ADC voltage generator
  *(uint32_t*) ADC_CFGR1 |= (1 << 16);  //DISCEN Discontinuous mode
  *(uint32_t*) ADC_CHSELR |= (1 << 12);  // Enable channel 17
  *(uint32_t*) ADC_CCR |= (1 << 23);
  // Enable ADCs, to do at the end
  *(uint32_t*) ADC_CR |= 1; 
  while(((*(uint32_t*) ADC_ISR) &= 1) == 0); // Wait for the ADC to be ready
}

uint32_t getDataADC(void) {
  uint32_t* controlRegister = (uint32_t*) ADC_CR;
  *controlRegister |= (1 << 2);            // Start conversion
  //while(*controlRegister &= (1 << 2) > 0); // Wait the end of the conversion
  while(((*(uint32_t*) ADC_ISR) &= (1 << 2)) == 0); // Check the EOC bit
  uint32_t data = *(uint32_t*) ADC_DR;
  return data;
}
