
#include "irx_imports.h"

#define MODNAME "IOP_SIF_manager"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_sifman;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_sifman) != 0)
        return 1;

    return 0;
}
