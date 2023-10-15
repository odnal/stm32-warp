MEMORY
{
     rom : ORIGIN = 0x08000000, LENGTH = 1024K
     ram : ORIGIN = 0x20000000, LENGTH = 96K
}
SECTIONS
{
     .text    : { *(.text) } > rom
     .rodata  : { *(.rodata) } > rom
     .bss     : { *(.bss) } > rom
     .data    : { *(.data) } > ram AT> rom
}

