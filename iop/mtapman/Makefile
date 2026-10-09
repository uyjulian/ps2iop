IOP_BIN = mtapman.irx

IOP_OBJS = mtapman.o imports.o exports.o

IOP_WARNFLAGS ?= -Wall

all: $(IOP_BIN)

clean:
	rm -f $(IOP_OBJS) *.irx *.elf

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
