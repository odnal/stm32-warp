.thumb

.globl _start
_start:

.word 0x20001000 // re-initializes the stack (also this addr is the end of sram1)
.word reset

.thumb_func
reset:
  bl main
  b .
