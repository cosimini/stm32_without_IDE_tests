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
- [ ] Receive from USART
- [ ] Write proper initialization
- [ ] Use OpenOCD for debugging too
- [ ] Use DMA controller

## Useful stuff
 - 'st-util': Connect to the debugger, GDB interface available on port 4242
 - 'arm-none-eabi-gdb build/output.o': Launch gdb with the specified file as target
    - 'target extended-remote :4242' : Connect to st-lisk
    - 'load' : flash the target
