
#include "irx_imports.h"

#define MODNAME "IOP_SIF_rpc_interface"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_sifcmd;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_sifcmd) != 0)
        return 1;

    return 0;
}
