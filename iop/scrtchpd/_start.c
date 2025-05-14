
#include "irx_imports.h"

#define MODNAME "Vblank_service"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_vblank;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_vblank) != 0)
        return 1;

    return 0;
}
