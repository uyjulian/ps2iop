
#include "irx_imports.h"

#define MODNAME "secrman_for_cex"
IRX_ID(MODNAME, 1, 3);

extern struct irx_export_table _exp_secrman;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_secrman) != 0)
        return 1;

    return 0;
}
