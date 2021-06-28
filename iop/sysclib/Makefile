IOP_BIN = sysclib.irx

IOP_OBJS = _start.o imports.o exports.o main.o

IOP_OBJS += embeddedartistry_libc/stdlib/strtol.o
IOP_OBJS += embeddedartistry_libc/stdlib/strtoul.o

IOP_OBJS += musl/ctype/tolower.o
IOP_OBJS += musl/ctype/toupper.o
IOP_OBJS += musl/string/memchr.o
IOP_OBJS += musl/string/memcmp.o
IOP_OBJS += musl/string/memmove.o
IOP_OBJS += musl/string/memrchr.o
IOP_OBJS += musl/string/bcmp.o
IOP_OBJS += musl/string/bcopy.o
IOP_OBJS += musl/string/bzero.o
IOP_OBJS += musl/string/stpcpy.o
IOP_OBJS += musl/string/stpncpy.o
IOP_OBJS += musl/string/strcat.o
IOP_OBJS += musl/string/strchr.o
IOP_OBJS += musl/string/strchrnul.o
IOP_OBJS += musl/string/strcpy.o
IOP_OBJS += musl/string/strcspn.o
IOP_OBJS += musl/string/index.o
IOP_OBJS += musl/string/rindex.o
IOP_OBJS += musl/string/strncat.o
IOP_OBJS += musl/string/strncmp.o
IOP_OBJS += musl/string/strpbrk.o
IOP_OBJS += musl/string/strrchr.o
IOP_OBJS += musl/string/strspn.o
IOP_OBJS += musl/string/strstr.o
IOP_OBJS += musl/string/strtok.o

IOP_OBJS += mpaland_printf/printf.o

IOP_OBJS += newlib/libc/machine/mips/setjmp.o

# Use MIPS or C version?
USE_MIPS_ASM = 1
ifneq (x$(USE_MIPS_ASM),x0)
IOP_OBJS += newlib/libc/machine/mips/memcpy.o
IOP_OBJS += newlib/libc/machine/mips/memset.o
IOP_OBJS += newlib/libc/machine/mips/strcmp.o
IOP_OBJS += newlib/libc/machine/mips/strlen.o
IOP_OBJS += newlib/libc/machine/mips/strncpy.o
else
IOP_OBJS += musl/string/memcpy.o
IOP_OBJS += musl/string/memset.o
IOP_OBJS += musl/string/strcmp.o
IOP_OBJS += musl/string/strlen.o
IOP_OBJS += musl/string/strncpy.o
endif

# Use full version of printf? This will massively increase the file size
USE_FULL_PRINTF = 0
ifneq (x$(USE_FULL_PRINTF),x0)
IOP_LIBS += -lgcc
else
IOP_CFLAGS += -DPRINTF_DISABLE_SUPPORT_FLOAT -DPRINTF_DISABLE_SUPPORT_EXPONENTIAL -DPRINTF_DISABLE_SUPPORT_LONG_LONG
endif

IOP_CFLAGS += -D_COMPILING_NEWLIB

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
