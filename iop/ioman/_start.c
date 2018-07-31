
#include "irx_imports.h"

#define MODNAME "IO/File_Manager"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_ioman;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_ioman) != 0)
        return 1;

    return 0;
}
