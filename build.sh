#!/usr/bin/fish

# Flags explaination:
#  -T link_src.ld      : Link with the specified linker script
#  -static             : Build a static executable
#  --specs=nano.specs  : This is a specific configuration file, provided by the toolkit, ships his own standard library if stdlib is in use
#  -mcpu=cortex-m0plus : Set target architecture
#  -mfloat-abi=soft    : The CPU do not have an hardware floating point unit, the compiler will place a software  version of it
#  -Os                 : Optimize for space
#  -mthumb             : Use the Thumb2 instruction set
#  -nostdlib           : Do not link with the standard lib
#  -Wall               : Enable all warnings
#  -ggdb               : Enable debugger symbols

arm-none-eabi-gcc\
  main.c boot.c\
  -T link_src.ld\
  -static\
  --specs=nano.specs\
  -mcpu=cortex-m0plus\
  -mfloat-abi=soft\
  -Os -mthumb -nostdlib -Wall -ggdb\
  -o ./build/output.o

# This requires st-utils to be running and connected to the host
arm-none-eabi-gdb --command=gdb-init build/output.o
