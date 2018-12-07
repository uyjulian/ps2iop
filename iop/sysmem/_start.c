
#include "irx_imports.h"

#define MODNAME "System_Memory_Manager"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_sysmem;

int _start(int argc, char* argv[]) {
    // if (RegisterLibraryEntries(&_exp_sysmem) != 0)
    //     return 1;

    return 0;
}
