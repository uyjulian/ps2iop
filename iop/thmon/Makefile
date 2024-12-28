IOP_BIN = thmon.irx

IOP_OBJS = imports.o main.o

IOP_INCS += -I/Volumes/public_share/ps2src/ps2dev/ps2sdk/iop/system/threadman/src
IOP_WARNFLAGS += -Wall -Wextra

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
