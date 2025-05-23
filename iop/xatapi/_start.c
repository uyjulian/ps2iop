
#include "irx_imports.h"

#define MODNAME "dmacman"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_dmacman;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_dmacman) != 0)
        return 1;

    return 0;
}
