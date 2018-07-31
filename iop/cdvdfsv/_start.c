
#include "irx_imports.h"

#define MODNAME "cdvd_ee_driver"
IRX_ID(MODNAME, 1, 4);

extern struct irx_export_table _exp_cdvdfsv;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_cdvdfsv) != 0)
        return 1;

    return 0;
}
