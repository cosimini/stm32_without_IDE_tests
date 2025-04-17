#!/usr/bin/fish
# Create build folder
if not test -d "build"
  mkdir build
end
rm build/*

arm-none-eabi-gcc\
  src/*.c\
  -T src/link_src.ld\
  -Wall -Wextra -Werror -ggdb\
  -mcpu=cortex-m0plus\
  -mfloat-abi=soft -mthumb -nostdlib\
  -o build/output.o

if test "$status" -eq 0
  openocd --file board/st_nucleo_g0.cfg -c "program build/output.o verify reset exit"
end
