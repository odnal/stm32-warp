.globl _start
_start:

.word 0x20001000 // initializing stack pointer
.word reset      // address in flash memory where execution of program will start

.thumb_func
reset:
  bl prog
  b .
