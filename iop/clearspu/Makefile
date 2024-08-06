IOP_BIN = clearspu.irx

IOP_OBJS = _start.o imports.o main.o

IOP_WARNFLAGS ?= -Wall -Wextra

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
