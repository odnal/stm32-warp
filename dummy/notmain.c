extern void dummy (unsigned int);
extern void PUT32 (unsigned int, unsigned int);
extern unsigned int GET32 (unsigned int);

#define SRAM2_BASE 0x10000000

// TODO: figure out why dummy is needed after what I am hoping is a simple count loop
// used as a delay
// ANSWER: -O2 ...optimizations done by the compiler
// to avoid the loop being optimized out, have to do something that can not be 
// easily optimized like branching to the link register... or reading a volatile var
int notmain(void) {

  unsigned int ra;
  for (ra=0; ra<0x00800000; ra+=4);

  //volatile int ra;
  //for (ra=0; ra<0x00800000; ra+=4);

  //unsigned int ra;
  //for (ra=0; ra<0x00800000; ra+=4) dummy(ra);

  return 0;
}
