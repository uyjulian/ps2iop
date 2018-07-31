
#include "irx_imports.h"

#define MODNAME "Interrupt_Manager"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_intrman;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_intrman) != 0)
        return 1;

    return 0;
}
