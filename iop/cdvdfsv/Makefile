IOP_BIN = cdvdfsv.irx

IOP_OBJS = imports.o exports.o

IOP_OBJS += cdvdfsv.o
IOP_OBJS += main.o
IOP_OBJS += ncmd.o
IOP_OBJS += scmd.o
IOP_OBJS += searchfile.o

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
