/*
    GNU linker script for RISC-V
*/

/* Specify the memory areas */
MEMORY
{
    ROM  : ORIGIN = 0x20040000, LENGTH = 0x00fc0000
    SRAM : ORIGIN = 0x10000000, LENGTH = 0x00020000
}

/* top end of the stack */
_estack = ORIGIN(BRAM) + LENGTH(BRAM);

/* entry point */
ENTRY(_start)

/* define output sections */
SECTIONS {
    .text :
    {
        . = ALIGN(4);
        *(.text.start)
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        *(.srodata)
        *(.srodata*)
        . = ALIGN(4);
        _etext = .;
        _sidata = _etext;
    } >ROM
    .data : AT ( _sidata )
    {
        . = ALIGN(4);
        _sdata = .;
        _ram_start = .;
        . = ALIGN(4);
        *(.data)
        *(.data*)
        *(.sdata)
        *(.sdata*)
        . = ALIGN(4);
        _edata = .;
    } >SRAM
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(.sbss)
        *(.sbss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >SRAM
    .heap :
    {
        . = ALIGN(4);
        _heap_start = .;
    } >SRAM
}
