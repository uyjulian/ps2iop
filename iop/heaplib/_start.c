
#include "irx_imports.h"

#define MODNAME "Heap_lib"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_heaplib;

int _start(int argc, char* argv[]) {
    if (RegisterLibraryEntries(&_exp_heaplib) != 0)
        return 1;

    return 0;
}
