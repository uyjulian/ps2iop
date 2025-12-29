IOP_BIN = romwrite.irx

IOP_OBJS = imports.o main.o

IOP_CFLAGS += -Wall -Wextra -Iinclude -I../s147nand/include

all: $(IOP_BIN)

clean:
	rm -f $(IOP_OBJS) *.irx *.elf

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
