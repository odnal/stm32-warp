CC=arm-none-eabi
MACH=cortex-m4
CFLAGS=-c -g -mcpu=$(MACH) -mthumb -Wall -std=gnu11
AFLAGS= -mcpu=$(MACH) -mthumb -Wall
LDFLAGS=-nostdlib -nostartfiles -T linker.ld -Map=final.map

all: main.o boot.o final.elf

main.o: main.c
	$(CC)-gcc $(CFLAGS) main.c -o main.o

boot.o: boot.s
	$(CC)-as $(AFLAGS) boot.s -o boot.o

final.elf: boot.o main.o
	$(CC)-ld $(LDFLAGS) boot.o main.o -o final.elf

load:
	openocd -f board/stm32l4discovery.cfg


clean:
	rm -f *.o
	rm -f *elf
	rm -f *.map
