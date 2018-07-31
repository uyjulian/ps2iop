
#include "irx_imports.h"

#define MODNAME "mcserv"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_mcserv;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_mcserv) != 0)
        return 1;

    return 0;
}
