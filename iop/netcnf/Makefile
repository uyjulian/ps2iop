IOP_BIN = netcnf.irx

IOP_OBJS = imports.o exports.o main.o

IOP_CFLAGS += -I../00common

IOP_WARNFLAGS += -Wall -Wextra

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
