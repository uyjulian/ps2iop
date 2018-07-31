
#include "irx_imports.h"

#define MODNAME "Multi_Thread_Manager"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_thbase;
extern struct irx_export_table _exp_thevent;
extern struct irx_export_table _exp_thsemap;
extern struct irx_export_table _exp_thmsgbx;
extern struct irx_export_table _exp_thfpool;
extern struct irx_export_table _exp_thvpool;
extern struct irx_export_table _exp_thrdman;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_thbase) != 0)
        return 1;
    if (RegisterLibraryEntries(&_exp_thevent) != 0)
        return 1;
    if (RegisterLibraryEntries(&_exp_thsemap) != 0)
        return 1;
    if (RegisterLibraryEntries(&_exp_thmsgbx) != 0)
        return 1;
    if (RegisterLibraryEntries(&_exp_thfpool) != 0)
        return 1;
    if (RegisterLibraryEntries(&_exp_thvpool) != 0)
        return 1;
    if (RegisterLibraryEntries(&_exp_thrdman) != 0)
        return 1;

    return 0;
}
