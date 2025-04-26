/*
 * Configure the DMA controller
 */

#include <stdint.h>

void resetInterrupt(int ch);

typedef enum {
  GLOBAL,
  COMPLETE,
  HALF,
  ERROR,
  ALL
} DMA_INTERRUPTS_KIND;

#define DMA1_OFFSET 0x40020000
#define DMA1_ISR     (DMA1_OFFSET + 0x00)
#define DMA1_IFCR    (DMA1_OFFSET + 0x04)
#define DMA1_CCR1    (DMA1_OFFSET + 0x08 + (0x14 * (1 - 1)))
#define DMA1_CCR2    (DMA1_OFFSET + 0x08 + (0x14 * (2 - 1)))
#define DMA1_CCR3    (DMA1_OFFSET + 0x08 + (0x14 * (3 - 1)))
#define DMA1_CCR4    (DMA1_OFFSET + 0x08 + (0x14 * (4 - 1)))
#define DMA1_CCR5    (DMA1_OFFSET + 0x08 + (0x14 * (5 - 1)))
#define DMA1_CNDTR1  (DMA1_OFFSET + 0x0C + (0x14 * (1 - 1)))
#define DMA1_CNDTR2  (DMA1_OFFSET + 0x0C + (0x14 * (2 - 1)))
#define DMA1_CNDTR3  (DMA1_OFFSET + 0x0C + (0x14 * (3 - 1)))
#define DMA1_CNDTR4  (DMA1_OFFSET + 0x0C + (0x14 * (4 - 1)))
#define DMA1_CNDTR5  (DMA1_OFFSET + 0x0C + (0x14 * (5 - 1)))
#define DMA1_CPAR1   (DMA1_OFFSET + 0x10 + (0x14 * (1 - 1)))
#define DMA1_CPAR2   (DMA1_OFFSET + 0x10 + (0x14 * (2 - 1)))
#define DMA1_CPAR3   (DMA1_OFFSET + 0x10 + (0x14 * (3 - 1)))
#define DMA1_CPAR4   (DMA1_OFFSET + 0x10 + (0x14 * (4 - 1)))
#define DMA1_CPAR5   (DMA1_OFFSET + 0x10 + (0x14 * (5 - 1)))
#define DMA1_CMAR1   (DMA1_OFFSET + 0x14 + (0x14 * (1 - 1)))
#define DMA1_CMAR2   (DMA1_OFFSET + 0x14 + (0x14 * (2 - 1)))
#define DMA1_CMAR3   (DMA1_OFFSET + 0x14 + (0x14 * (3 - 1)))
#define DMA1_CMAR4   (DMA1_OFFSET + 0x14 + (0x14 * (4 - 1)))
#define DMA1_CMAR5   (DMA1_OFFSET + 0x14 + (0x14 * (5 - 1)))

#define DMAMUX_OFFSET 0x40020800
#define DMAMUX_C0CR  (DMAMUX_OFFSET + (0x04 * 0))
#define DMAMUX_C1CR  (DMAMUX_OFFSET + (0x04 * 1))
#define DMAMUX_C2CR  (DMAMUX_OFFSET + (0x04 * 2))
#define DMAMUX_C3CR  (DMAMUX_OFFSET + (0x04 * 3))
#define DMAMUX_C4CR  (DMAMUX_OFFSET + (0x04 * 4))
#define DMAMUX_C5CR  (DMAMUX_OFFSET + (0x04 * 5))
#define DMAMUX_C6CR  (DMAMUX_OFFSET + (0x04 * 6))
#define DMAMUX_CSR   (DMAMUX_OFFSET + 0x80)
#define DMAMUX_CFR   (DMAMUX_OFFSET + 0x84)
#define DMAMUX_RG0CR (DMAMUX_OFFSET + 0x100 + (0x04 * 0))
#define DMAMUX_RG1CR (DMAMUX_OFFSET + 0x100 + (0x04 * 1))
#define DMAMUX_RG2CR (DMAMUX_OFFSET + 0x100 + (0x04 * 2))
#define DMAMUX_RGSR  (DMAMUX_OFFSET + 0x140)
#define DMAMUX_RGCFR (DMAMUX_OFFSET + 0x144)

int getDMAChannelStatus(int DMAChannel) {
  if(DMAChannel > 5 || DMAChannel < 0) return -1;
  return ((*((uint32_t*) DMA1_ISR)) >> (4 * DMAChannel) & 0b1111);
}

void clearDMAInterruptFlags(int DMAChannel, int kind) {
  if(DMAChannel > 5 || DMAChannel < 0) return;
  resetInterrupt(9);
  uint32_t mask;
  if(kind >= 5) mask = 0b1111;
  else mask = 0b1 << kind;
  *(uint32_t*) DMA1_IFCR = (mask << (4 * DMAChannel));
  *(uint32_t*) DMAMUX_CFR &= ~(0b1 << DMAChannel);
}

void receiveDataUSART2(int size) {
  *(uint32_t*) DMA1_CCR1 &= ~((uint32_t) 1);
  clearDMAInterruptFlags(0, ALL);
  *(uint32_t*) DMA1_CNDTR1 = (*(uint32_t*) DMA1_CNDTR1 & 0xffff0000) | ((uint32_t) size);  // Number of data transfers
  *(uint32_t*) DMA1_CCR1 |= 0b1;
}

void initDMA(uint8_t* buf) {
  // Configure DMA
  // Channel 1 - Used for the USART communication
  *(uint32_t*) DMA1_CCR1 |= 0b1 << 7;  // MINC : Memory increment
  *(uint32_t*) DMA1_CCR1 &= ~(0b1 << 4);  // DIR : Set direction to READ
  //*(uint32_t*) DMA1_CCR1 |= 0b1 << 3;  // TEIE : Enable transfer error interrupt TODO: Use this
  *(uint32_t*) DMA1_CCR1 |= 0b1 << 1;  // TCIE : Enable transfer complete interrupt
  *(uint32_t*) DMA1_CPAR1 = 0x40004424;  // CPAR : periferal address
  *(uint32_t*) DMA1_CMAR1 = (uint32_t) buf;  // Used memory location

  // Configure MUX
  *(uint32_t*) DMAMUX_C0CR = 52;  // 52 is USART2 receive, 53 USART2 transmit
}
