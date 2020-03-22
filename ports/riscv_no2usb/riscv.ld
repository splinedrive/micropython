/*
    GNU linker script for RISC-V
*/

/* Specify the memory areas */
MEMORY
{
    SPRAM (rwx) : ORIGIN = 0x00020000, LENGTH = 0x20000
    BRAM  (rwx) : ORIGIN = 0x00000010, LENGTH = 0x003f0
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
    } >SPRAM
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
    } >SPRAM
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
    } >SPRAM
    .heap :
    {
        . = ALIGN(4);
        _heap_start = .;
    } >SPRAM
}
