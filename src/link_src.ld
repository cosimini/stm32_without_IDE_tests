/* Define the stack reset value to be the end of the SRAM */
/* end_of_ram = ORIGIN(SRAM) + LENGTH(SRAM)*/
PROVIDE(_stack_reset_value = ORIGIN(SRAM) + LENGTH(SRAM));

MEMORY
{
  FLASH (rx): ORIGIN = 0x08000000, LENGTH = 64K
  SRAM (rwx): ORIGIN = 0x20000000, LENGTH = 8K
}

/*
 * An simpler version of this just define .text
 * The section .text is defined by the compiler, hence, if not explicitly put after the 
 * isr_vector, it will be placed at zero,

  SECTIONS
  {
    .text : {
      *(.reset_vector)
      *(.text*)
      . = ALIGN(4);
    } > FLASH
  }
 */

SECTIONS
{
  .isr_vector : {
    *(.reset_vector)
    . = ALIGN(4);
  } > FLASH
  .text : {
    *(.text*)
    . = ALIGN(4);
  } > FLASH
}
