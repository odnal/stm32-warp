CC=arm-none-eabi
MACH=cortex-m4
CFLAGS=-c -g -mcpu=$(MACH) -mthumb -Wall -std=gnu11
AFLAGS= -mcpu=$(MACH) -mthumb -Wall
LDFLAGS=-nostdlib -nostartfiles -T linker.ld -Map=final.map

all: notmain.o boot.o final.elf

notmain.o: notmain.c
	$(CC)-gcc $(CFLAGS) notmain.c -o notmain.o

boot.o: boot.s
	$(CC)-as $(AFLAGS) boot.s -o boot.o

final.elf: boot.o notmain.o
	$(CC)-ld $(LDFLAGS) boot.o notmain.o -o final.elf

load:
	openocd -f board/stm32l4discovery.cfg


clean:
	rm -f *.o
	rm -f *elf
	rm -f *.map
