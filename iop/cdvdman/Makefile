IOP_BIN = cdvdman.irx

IOP_OBJS = cdvdman.o imports.o exports.o

IOP_WARNFLAGS += -Wextra

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
