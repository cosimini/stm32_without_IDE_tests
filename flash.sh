#!/usr/bin/fish
# Create build folder
if not test -d "build"
  mkdir build
end
rm build/*

arm-none-eabi-gcc\
  src/*.c\
  -T src/link_src.ld\
  -static \
  -Wall -Wextra -Werror -ggdb\
  -mcpu=cortex-m0plus\
  -mfloat-abi=soft -mthumb -nostdlib\
  -o build/output.o \
  -l:libgcc.a \
  -L:/usr/lib/gcc/arm-none-eabi/9.3.0/

if test "$status" -eq 0
  openocd --file board/st_nucleo_g0.cfg -c "program build/output.o verify reset exit"
end
