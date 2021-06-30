IOP_BIN = cdvdman.irx

IOP_OBJS = imports.o exports.o
IOP_OBJS += cdvdman.o
IOP_OBJS += device-cdvd.o
IOP_OBJS += ioops.o
IOP_OBJS += ncmd.o
IOP_OBJS += scmd.o
IOP_OBJS += searchfile.o
IOP_OBJS += streaming.o

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
