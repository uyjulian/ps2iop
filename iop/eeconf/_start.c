
#include "irx_imports.h"

#define MODNAME "EEConfig"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_eeconfig;

int _start(int argc, char* argv[]) {
    // if (RegisterLibraryEntries(&_exp_eeconfig) != 0)
    //     return 1;

    return 0;
}
