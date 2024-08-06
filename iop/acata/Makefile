IOP_BIN = clearspu.irx

IOP_CFLAGS += -I../00accommon

IOP_OBJS = \
	acata-entry.o \
	ata.o \
	atacmd.o \
	atapicmd.o \
	imports.o \
	exports.o

IOP_WARNFLAGS ?= -Wall -Wextra

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
