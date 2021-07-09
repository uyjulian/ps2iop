
#include "irx_imports.h"

#define MODNAME "fls"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_fls;

extern s32 flash_detect();

int _start(int argc, char* argv[])
{
    if (RegisterLibraryEntries(&_exp_fls) != 0)
    {
    	flash_detect();
        return 1;
    }

    return 0;
}
