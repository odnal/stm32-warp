ENTRY(_start)

MEMORY
{
  rom : ORIGIN = 0x08000000, LENGTH = 1024K
}

SECTIONS
{
  .text    : { *(.text) } > rom
}
