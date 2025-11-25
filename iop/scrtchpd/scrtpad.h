
#ifndef _SCRTPAD_H
#define _SCRTPAD_H

extern void *scrtpad_getinternaldata(void);
extern void *AllocScratchPad(int mode);
extern int FreeScratchPad(void *alloced_addr);

#define scrtpad_IMPORTS_start DECLARE_IMPORT_TABLE(scrtpad, 1, 1)
#define scrtpad_IMPORTS_end END_IMPORT_TABLE

#define I_scrtpad_getinternaldata DECLARE_IMPORT(3, scrtpad_getinternaldata)
#define I_AllocScratchPad DECLARE_IMPORT(4, AllocScratchPad)
#define I_FreeScratchPad DECLARE_IMPORT(5, FreeScratchPad)

#endif
