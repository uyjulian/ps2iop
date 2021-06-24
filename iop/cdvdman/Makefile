IOP_BIN = cdvdman.irx

IOP_OBJS = imports.o exports.o cdvdmanc.o cdvdmand.o cdvdmanf.o cdvdmans.o

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
