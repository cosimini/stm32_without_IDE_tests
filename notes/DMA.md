# Using DMA to send/receive on USART

Based on page 1026, section 33.5.19

DMAT and DMAR bits (7 and 6) are DMA transmitter and receiver enable bits, in USART_CR3 (0x08).

What the fuck -> Clear the TC flag in USART_ISR by setting TCCF bit in USART_ICR register
