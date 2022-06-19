
#include "irx_imports.h"

#define MODNAME "System_C_lib"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_sysclib;
extern struct irx_export_table _exp_stdio;

int _start(int argc, char* argv[]) {
	(void)argc;
	(void)argv;

    if (RegisterLibraryEntries(&_exp_sysclib) != 0)
        return 1;
    if (RegisterLibraryEntries(&_exp_stdio) != 0)
        return 1;

    return 0;
}
