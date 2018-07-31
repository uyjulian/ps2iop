
#include "irx_imports.h"

#define MODNAME "Moldule_File_loader"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_modload;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_modload) != 0)
        return 1;

    return 0;
}
