
#include "irx_imports.h"

#define MODNAME "Exception_Manager"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_excepman;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_excepman) != 0)
        return 1;

    return 0;
}
