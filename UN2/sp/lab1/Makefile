CC = nasm
CFLAGS = -g -f elf
LD = ld
LDFLAGS = -m elf_i386

SRCMODULES = strlen.asm
OBJMODULES = $(SRCMODULES:.asm=.o)

pyramid: main.o $(OBJMODULES)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.asm
	$(CC) $(CFLAGS) $^

.PHONY:
clean:
	rm -f *.o

