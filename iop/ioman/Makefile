IOP_BIN = iomanX.irx

IOP_WARNFLAGS += -Wall -Wextra

IOP_CFLAGS += -DIOMANX_OLD_NAME_ADDDELDRV=0 -DIOMANX_OLD_NAME_COMPATIBILITY=0 -DIOMANX_ENABLE_LEGACY_IOMAN_HOOK

IOP_OBJS = imports.o exports.o main.o

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
