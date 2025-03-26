# Notes for USART

The word lenght can be set with setting bits 12 and 28 of the USART_CR1 register
         12 28
* 7 bits: 0  1
* 8 bits: 0  0
* 9 bits: 1  0

There's a FIFO mode for both input and output, the buffer can store a single round in any case.

Stop bits are configures by two flags in USART_CR2, by default it is 1 so who cares.

Transmission procedure (page 994):
1. Program the word length in USART_CR1
2. Select boud rate using USART_BRR
3. Select the number of stop bits in USART_CR2
4. Enable the USART by setting UE bit in USART_CR1 to 1
5. Set up DMA if DMA is used
6. Set TE bit in USART_CR1 to send idle as first transmission
7. Write data to USART_TDR register
8. Wait until TC bit of USART_TDR is = 1
