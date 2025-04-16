# My test building stm32 binaries

Those are my tests trying to program stm32 based boards without using IDEs.
Successed in running simple code and verified whith gdb everything is fine.
I'm using st-link at the moment, which still feels too magic to me, will use openocd in the future.

For the time being, the project builds with the bash script build.sh, which also starts gdb.

TODOs:
- [~] Write a basis and simple hal for the GPIO
- [X] Write a configuration for the clock hardware
- [X] Try to configure a timer with an associated callback
- [X] Try to use the serial interface
- [ ] Use DMA controller
- [ ] Write proper initialization

## Useful commands
 - st-util: Conect to the hardware and listen for gdb
 - arm-none-eabi-gdb build/output.o: Launch gdb with the pecified file as target

 Whithin the debugger:
 - target extended-remote :4242 -> Connect to st-lisk
 - load -> flash the memory
 - continue -> continue execution
 - p <var> -> print a variable
 - x/<size>[xc][wb] 0x20000xxx -> read chunk of memory
