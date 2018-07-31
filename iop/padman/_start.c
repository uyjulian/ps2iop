
#include "irx_imports.h"

#define MODNAME "padman"
IRX_ID(MODNAME, 1, 20);

extern struct irx_export_table _exp_padman;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_padman) != 0)
        return 1;

    return 0;
}
