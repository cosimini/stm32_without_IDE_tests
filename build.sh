#!/usr/bin/fish
arm-none-eabi-gcc\
  main.c boot.c\
  -T link_src.ld\
  -static\
  -mcpu=cortex-m0plus\
  -mfloat-abi=soft\
  -mthumb -nostdlib -Wall -ggdb\
  -o ./build/output.o\

# Useful flags
# --specs=nano.specs\ link with a stdlib provided by the toolkit

# This requires st-utils to be running and to be connected to the host
arm-none-eabi-gdb --command=gdb-init build/output.o
