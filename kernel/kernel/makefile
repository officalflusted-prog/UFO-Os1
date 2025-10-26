SRCS = kernel_core.c kernel_remote.c storage.c ports.c storage_test.c
OBJS = $(SRCS:.c=.o)

CC = i686-elf-gcc
CFLAGS = -ffreestanding -m32 -O2 -Wall -Wextra
LD = i686-elf-ld

all: kernel.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel.bin: $(OBJS)
	$(LD) -m elf_i386 -Ttext 0x1000 $(OBJS) -o kernel.elf
	i686-elf-objcopy -O binary kernel.elf kernel.bin

clean:
	rm -f *.o kernel.elf kernel.bin
