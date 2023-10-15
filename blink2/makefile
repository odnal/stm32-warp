CC=arm-none-eabi
MACH=cortex-m4
CFLAGS=-c -g -mcpu=$(MACH) -mthumb -Wall -ffreestanding -std=gnu11
AFLAGS=-mcpu=$(MACH) -mthumb -Wall -g
LDFLAGS=-nostdlib -nostartfiles -T linker.ld -Map=final.map

all: boot.o prog.o final.elf

prog.o: prog.s
	$(CC)-as $(AFLAGS) prog.s -o prog.o

#notmain.o: notmain.c
	#$(CC)-gcc $(CFLAGS) notmain.c -o notmain.o

boot.o: boot.s
	$(CC)-as $(AFLAGS) boot.s -o boot.o

final.elf: boot.o prog.o
	$(CC)-ld $(LDFLAGS) boot.o prog.o -o final.elf

load:
	openocd -f board/stm32l4discovery.cfg


clean:
	rm -f *.o
	rm -f *elf
	rm -f *.map
