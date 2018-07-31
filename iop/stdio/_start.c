
#include "irx_imports.h"

#define MODNAME "Stdio"
IRX_ID(MODNAME, 1, 2);

extern struct irx_export_table _exp_stdio;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_stdio) != 0)
        return 1;

    return 0;
}
