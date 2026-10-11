IOP_BIN = padman.irx

IOP_OBJS = imports.o exports.o padman.o

all: $(IOP_BIN)

clean:
	rm -f $(IOP_OBJS) *.irx *.elf

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
