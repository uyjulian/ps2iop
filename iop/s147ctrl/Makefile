IOP_BIN = s147ctrl.irx

IOP_OBJS = imports.o main.o

IOP_CFLAGS += -Wall -Wextra

all: $(IOP_BIN)

clean:
	rm -f $(IOP_OBJS) *.irx *.elf

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
