#!/usr/bin/fish

# Create build folder
if not test -d "build"
  mkdir build
end
rm build/*

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
  src/*.c\
  -T src/link_src.ld\
  -Wall -Wextra -Werror -ggdb\
  -mcpu=cortex-m0plus\
  -mfloat-abi=soft -mthumb -nostdlib\
  -o build/output.o

#  Flags I'm not using
#
#  -Os\
#  --specs=nano.specs\
#  -static\

if test "$status" -eq 0
  # This requires st-utils to be running and connected to the host
  arm-none-eabi-gdb --command=gdb-init build/output.o
end
