# UFO OS Build System

CC = i686-elf-gcc
LD = i686-elf-ld
CFLAGS = -ffreestanding -O2 -Wall -Wextra

all: kernel.bin

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

kernel.bin: kernel.o
	$(LD) -Ttext 0x1000 --oformat binary kernel.o -o kernel.bin

clean:
	rm -f *.o *.bin
