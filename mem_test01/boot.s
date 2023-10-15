.thumb

.globl _start
_start:

.word 0x20001000 // re-initializes the stack (also this addr is the end of sram1)
.word reset

.thumb_func
reset:
  bl notmain
  b .


.globl PUT32
.thumb_func
PUT32:
  str r1, [r0]
  bx lr

.globl GET32
.thumb_func
GET32:
  ldr r0, [r0]
  bx lr

.globl dummy
.thumb_func
dummy:
  bx lr

