
#include "irx_imports.h"

#define MODNAME "Timer_Manager"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_timrman;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_timrman) != 0)
        return 1;

    return 0;
}
