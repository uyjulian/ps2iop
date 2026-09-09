IOP_BIN = cxtmdm.irx

IOP_OBJS = imports.o main.o

IOP_CFLAGS += -Wall -Wextra -Wdouble-promotion -Wduplicated-branches -Wduplicated-cond -Wzero-as-null-pointer-constant -Wshadow -Wundef -Wbad-function-cast -Wdate-time -Wjump-misses-init -Wlogical-op -Wfree-labels -Wstrict-prototypes -Wold-style-definition -Wdeprecated-non-prototype -Wmissing-parameter-name

all: $(IOP_BIN)

clean:
	rm -f $(IOP_OBJS) *.irx *.elf

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
