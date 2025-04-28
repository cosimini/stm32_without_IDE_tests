# My test building stm32 binaries

Those are my tests trying to program stm32 based boards without using IDEs.
Successed in running simple code and verified whith gdb everything is fine.
I'm using st-link at the moment, which still feels too magic to me, will use openocd in the future.

For the time being, the project builds with the bash script build.sh, which also starts gdb.

TODOs:
- [X] Write a basis and simple hal for the GPIO
- [X] Write a configuration for the clock hardware
- [X] Try to configure a timer with an associated callback
- [X] Try to write to the serial interface
- [X] Receive from USART
- [X] Use DMA controller
- [ ] Write proper initialization, consistent and with a single, main, init call in the reset_handler
- [ ] Use OpenOCD for debugging too
- [ ] Implement a delay() function using systick
- [ ] Interface some other periferals, ADC and temperature sensor
- [ ] Try using sleep modes
