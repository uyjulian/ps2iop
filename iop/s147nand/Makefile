IOP_BIN = s147nand.irx

IOP_OBJS = imports.o exports.o main.o

IOP_CFLAGS += -Iinclude -I../s147mdev/include

all: $(IOP_BIN)

clean:
	rm -f $(IOP_OBJS) *.irx *.elf

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
