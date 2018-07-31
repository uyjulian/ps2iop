
#include "irx_imports.h"

#define MODNAME "mcman"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_mcman;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_mcman) != 0)
        return 1;

    return 0;
}
