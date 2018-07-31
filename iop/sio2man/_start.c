
#include "irx_imports.h"

#define MODNAME "sio2man"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_sio2man;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_sio2man) != 0)
        return 1;

    return 0;
}
