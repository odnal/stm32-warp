// Program turns on/off green led forever
.thumb
.globl prog

.thumb_func
prog:
  // Set up GPIO clock bus (RCC_AHB2ENR)
  ldr r0, =RCC_BASE
  mov r1, #0x4C         // RCC_AHB2ENR offset
  orr r0, r1
  //str r0, [r0]
  
  // Enable GPIOE in the RCC_AHB2ENR register
  mov r1, #1
  lsl r1, r1, #4        // GPIOE port enable bit
  str r1, [r0]          // store value in RCC_AHB2ENR 

  // Set up GPIO_MODER register to general purpose output mode: 01
  ldr r0, =GPIOE_BASE   // MODER register has offset 0x00
  mov r1, #1
  lsl r1, r1, #17       // the bit we want to change
  ldr r2, [r0]          // r2 has reset value of 0xffffffff
  eor r2, r1            // value changed to output mode for GPIOE
  str r2, [r0]          // store result to GPIOE_MODER (address)
  
  mov r1, #0x18         // GPIOE_BSRR offset value 
  orr r0, r1            // GPIOE_BSRR address is now contained in r0
  //str r0, [r0]

  led_loop:
    mov r1, #1
    lsl r1, r1, #8      // set bit
    str r1, [r0]
    ldr r3, =counter
    bl delay
    mov r1, #1
    lsl r1, r1, #24     // reset bit
    str r1, [r0]
    ldr r3, =counter
    bl delay

  bl led_loop
    
  delay:
    sub r3, #1
    bne delay
    bx lr
    



.thumb_func
forever:
  b .

.section .data
  .equ RCC_BASE,    0x40021000 
  .equ GPIOE_BASE,  0x48001000

  .equ counter,     0x00200000 
