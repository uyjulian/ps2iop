IOP_BIN = sysclib.irx

IOP_OBJS = _start.o imports.o exports.o

# Use MIPS or C version?
USE_MIPS_ASM ?= 1

# Use size optimized or normal version?
USE_SIZE_OPTIMIZED ?= 0

# Use full version of printf? This will massively increase the file size
USE_FULL_PRINTF ?= 0

IOP_OBJS += nonstd/atob.o
IOP_OBJS += nonstd/ctype.o
IOP_OBJS += nonstd/_wmemcopy.o
IOP_OBJS += nonstd/_wmemset.o

ifneq (x$(USE_SIZE_OPTIMIZED),x0)
IOP_OBJS += size_optimized/strtol.o
IOP_OBJS += size_optimized/strtoul.o
IOP_OBJS += size_optimized/sysclib_determine_base.o
else
IOP_OBJS += embeddedartistry_libc/stdlib/strtol.o
IOP_OBJS += embeddedartistry_libc/stdlib/strtoul.o
endif

ifneq (x$(USE_SIZE_OPTIMIZED),x0)
IOP_OBJS += size_optimized/memchr.o
IOP_OBJS += size_optimized/memmove.o
IOP_OBJS += size_optimized/strchr.o
IOP_OBJS += size_optimized/rindex.o
IOP_OBJS += size_optimized/strrchr.o
IOP_OBJS += size_optimized/strspn.o
IOP_OBJS += size_optimized/strstr.o
IOP_OBJS += size_optimized/strtok_r.o
IOP_OBJS += size_optimized/strtok.o
else
IOP_OBJS += musl/string/memchr.o
IOP_OBJS += musl/string/memmove.o
IOP_OBJS += musl/string/strchr.o
IOP_OBJS += musl/string/rindex.o
IOP_OBJS += musl/string/strrchr.o
IOP_OBJS += musl/string/strspn.o
IOP_OBJS += musl/string/strstr.o
IOP_OBJS += musl/string/strtok_r.o
IOP_OBJS += musl/string/strtok.o
endif

IOP_OBJS += musl/ctype/tolower.o
IOP_OBJS += musl/ctype/toupper.o
IOP_OBJS += musl/string/memcmp.o
IOP_OBJS += musl/string/memrchr.o
IOP_OBJS += musl/string/bcmp.o
IOP_OBJS += musl/string/bcopy.o
IOP_OBJS += musl/string/bzero.o
IOP_OBJS += musl/string/stpcpy.o
IOP_OBJS += musl/string/stpncpy.o
IOP_OBJS += musl/string/strcat.o
IOP_OBJS += musl/string/strchrnul.o
IOP_OBJS += musl/string/strcpy.o
IOP_OBJS += musl/string/strcspn.o
IOP_OBJS += musl/string/index.o
IOP_OBJS += musl/string/strncat.o
IOP_OBJS += musl/string/strncmp.o
IOP_OBJS += musl/string/strpbrk.o

IOP_OBJS += mpaland_printf/printf.o

IOP_OBJS += newlib/libc/machine/mips/setjmp.o

ifneq (x$(USE_MIPS_ASM),x0)
IOP_OBJS += newlib/libc/machine/mips/memcpy.o
IOP_OBJS += newlib/libc/machine/mips/memset.o
IOP_OBJS += newlib/libc/machine/mips/strcmp.o
IOP_OBJS += newlib/libc/machine/mips/strlen.o
IOP_OBJS += newlib/libc/machine/mips/strncpy.o
else
ifneq (x$(USE_SIZE_OPTIMIZED),x0)
IOP_OBJS += size_optimized/memcpy.o
IOP_OBJS += size_optimized/memset.o
IOP_OBJS += size_optimized/strcmp.o
else
IOP_OBJS += musl/string/memcpy.o
IOP_OBJS += musl/string/memset.o
IOP_OBJS += musl/string/strcmp.o
endif
IOP_OBJS += musl/string/strlen.o
IOP_OBJS += musl/string/strncpy.o
endif

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
