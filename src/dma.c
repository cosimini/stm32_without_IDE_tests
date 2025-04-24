/*
 * Configure the DMA controller
 */

#include <stdint.h>

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
#define DMAMUX_C0CR  (DMA1_OFFSET + (0x04 * 0))
#define DMAMUX_C1CR  (DMA1_OFFSET + (0x04 * 1))
#define DMAMUX_C2CR  (DMA1_OFFSET + (0x04 * 2))
#define DMAMUX_C3CR  (DMA1_OFFSET + (0x04 * 3))
#define DMAMUX_C4CR  (DMA1_OFFSET + (0x04 * 4))
#define DMAMUX_C5CR  (DMA1_OFFSET + (0x04 * 5))
#define DMAMUX_C6CR  (DMA1_OFFSET + (0x04 * 6))
#define DMAMUX_CSR   (DMA1_OFFSET + 0x80)
#define DMAMUX_CFR   (DMA1_OFFSET + 0x84)
#define DMAMUX_RG0CR (DMA1_OFFSET + 0x100 + (0x04 * 0))
#define DMAMUX_RG1CR (DMA1_OFFSET + 0x100 + (0x04 * 1))
#define DMAMUX_RG2CR (DMA1_OFFSET + 0x100 + (0x04 * 2))
#define DMAMUX_RGSR  (DMA1_OFFSET + 0x140)
#define DMAMUX_RGCFR (DMA1_OFFSET + 0x144)

void initDMA(uint8_t* buf) {
  // Configure DMA
  // Channel 1 - Used for the USART communication
  *(uint32_t*) DMA1_CCR1 &= 0b0 << 4;  // DIR : Set direction to READ
  //*(uint32_t*) DMA1_CCR1 |= 0b1 << 4;  // DIR : Set direction to WRITE
  // TODO: Use the interrupts, expecially for the transfer errors
  //*(uint32_t*) DMA1_CCR1 |= 0b1 << 3;  // TEIE : Enable transfer error interrupt
  //*(uint32_t*) DMA1_CCR1 |= 0b1 << 1;  // TCIE : Enable transfer complete interrupt
  *(uint32_t*) DMA1_CCR1 |= 0b1;  // EN : enable DMA controller
  *(uint32_t*) DMA1_CPAR1 = 0x40004428;  // CPAR : periferal address
  *(uint8_t**) DMA1_CMAR1 = buf;

  // Configure MUX
  //    - 52 : USART2 RX
  //    - 53 : USART2 TX
}

int getDMAChannelStatus(int DMAChannel) {
  if(DMAChannel > 5 || DMAChannel < 0) return -1;
  return ((*((uint32_t*) DMA1_ISR)) >> (4 * DMAChannel) & 0b1111);
}

void clearDMAInterruptFlags(int DMAChannel, int kind) {
  if(DMAChannel > 5 || DMAChannel < 0) return;
  int mask;
  if(kind >= 5) mask = 0b1111;
  else mask = 0b1 << kind;
  *(uint32_t*) DMA1_IFCR = (mask << (4 * DMAChannel));
}
