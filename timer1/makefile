CC=arm-none-eabi
MACH=cortex-m4
CFLAGS=-c -g -mcpu=$(MACH) -mthumb -Wall -std=gnu11
AFLAGS= -mcpu=$(MACH) -mthumb -Wall
LDFLAGS=-nostdlib -nostartfiles -T linker.ld -Map=final.map

all: main.o boot.o sys_clock.o tim1.o final.elf

main.o: main.c
	$(CC)-gcc $(CFLAGS) main.c -o main.o

boot.o: boot.s
	$(CC)-as $(AFLAGS) boot.s -o boot.o

sys_clock.o: sys_clock.c
	$(CC)-gcc $(CFLAGS) sys_clock.c -o sys_clock.o

tim1.o: tim1.c
	$(CC)-gcc $(CFLAGS) tim1.c -o tim1.o

final.elf: boot.o main.o sys_clock.o
	$(CC)-ld $(LDFLAGS) boot.o main.o sys_clock.o tim1.o -o final.elf

load:
	openocd -f board/stm32l4discovery.cfg


clean:
	rm -f *.o
	rm -f *elf
	rm -f *.map
