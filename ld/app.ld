MEMORY {
  FLASH (rx)  : ORIGIN = ld_mem_rom_base, LENGTH = ld_mem_rom_size
  RAM   (rwx) : ORIGIN = ld_mem_ram_base, LENGTH = ld_mem_ram_size
}

ENTRY(sys_isr_reset)

SECTIONS {
  ld_stack_top = ORIGIN(RAM) + LENGTH(RAM);
  ld_data_source = LOADADDR(.data);

  /* Interrupt vectors and code get stuffed into ROM. */
  . = ORIGIN(FLASH);

  /*
  .isr.vector : {
    LONG(ld_stack_top)
    KEEP(*(.isr.vector))
  } >FLASH */

  .text ALIGN(4) : {
    LONG(ld_stack_top)
    KEEP(*(.isr.vector))
    *(.text*)

    . = ALIGN(4);
    *(.rodata*)

    . = ALIGN(4);
  } >FLASH

  /* Data and BSS end up in RAM. */
  . = ORIGIN(RAM);

  .data ALIGN(4) : {
    ld_data_targetstart = .;

    *(.data)
    *(.data*)
    . = ALIGN(4);

    ld_data_targetend = .;
  } >RAM AT >FLASH


  .bss ALIGN(4) (NOLOAD) : {
    ld_bss_start = .;

    *(.bss)
    *(.bss*)
    . = ALIGN(4);

    ld_bss_end = .;
  } >RAM
}
