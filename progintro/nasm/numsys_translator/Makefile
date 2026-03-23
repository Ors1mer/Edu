CC = nasm
CFLAGS = -f elf
LD = ld
LDFLAGS = -m elf_i386
RM = rm

SRCMODULES = strlen.asm str_to_int.asm int_to_str.asm
OBJMODULES = $(SRCMODULES:.asm=.o)

numtr: numsys_translator.o $(OBJMODULES)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.asm
	$(CC) $(CFLAGS) $^

.PHONY:
clean:
	$(RM) -f *.o

