include ../Makefile.inc

MODULE=sampleCodeModule.bin
SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard *.asm)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS=$(SOURCES:.c=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld $(OBJECTS) $(OBJECTS_ASM) -o ../$(MODULE)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@	

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o

.PHONY: all clean
