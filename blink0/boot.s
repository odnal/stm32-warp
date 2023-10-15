.thumb

.globl _start
_start:

.word 0x20001000 // end of sram1
.word reset

.thumb_func
reset:
  bl notmain
  b .

.globl dummy
.thumb_func
dummy:
  bx lr
