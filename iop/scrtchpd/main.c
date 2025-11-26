
#include "irx_imports.h"
#include <scrtpad.h>
#include <kerr.h>

#ifdef _IOP
IRX_ID("ScratchPad_service", 1, 1);
#endif
// Based on the module from SCE SDK 3.1.0.

struct scratchpad_internal_data
{
  int m_scrtpad_is_allocated;
  int m_scrtpad_alloc_count;
};

extern struct irx_export_table _exp_scrtpad;
static struct scratchpad_internal_data g_scrtpad_internal_data;

int _start(int ac, char **av)
{
  int libreg_res;
  int state;

  (void)ac;
  (void)av;

  CpuSuspendIntr(&state);
  libreg_res = RegisterLibraryEntries(&_exp_scrtpad);
  CpuResumeIntr(state);
  if ( libreg_res )
    return MODULE_NO_RESIDENT_END;
  g_scrtpad_internal_data.m_scrtpad_is_allocated = 0;
  g_scrtpad_internal_data.m_scrtpad_alloc_count = 0;
  // Unofficial: use MODULE_RESIDENT_END (not unloadable)
  return MODULE_RESIDENT_END;
}

void *AllocScratchPad(int mode)
{
  int alloc_addr;
  int state;

  if ( mode )
    return (void *)KE_ILLEGAL_MODE;
  CpuSuspendIntr(&state);
  if ( g_scrtpad_internal_data.m_scrtpad_is_allocated )
  {
    CpuResumeIntr(state);
    return (void *)KE_SPAD_INUSE;
  }
  g_scrtpad_internal_data.m_scrtpad_is_allocated = 1;
  g_scrtpad_internal_data.m_scrtpad_alloc_count += 1;
  alloc_addr = (g_scrtpad_internal_data.m_scrtpad_alloc_count & 1) ? 0x1F800800 : 0x1F800C00;
  *((vu32 *)0xFFFE0144) = alloc_addr;
  CpuResumeIntr(state);
  return (void *)alloc_addr;
}

int FreeScratchPad(void *alloced_addr)
{
  int state;

  (void)alloced_addr;
  CpuSuspendIntr(&state);
  if ( !g_scrtpad_internal_data.m_scrtpad_is_allocated )
  {
    CpuResumeIntr(state);
    return KE_SPAD_NOT_INUSE;
  }
  if ( *((vu32 *)0xFFFE0144) != ((g_scrtpad_internal_data.m_scrtpad_alloc_count & 1) ? 0x1F800800 : 0x1F800C00) )
  {
    CpuResumeIntr(state);
    return KE_ILLEGAL_SPADADDR;
  }
  *((vu32 *)0xFFFE0144) = 0x1F800000;
  g_scrtpad_internal_data.m_scrtpad_is_allocated = 0;
  CpuResumeIntr(state);
  return 0;
}

void _deinit(int disintr)
{
  if ( disintr )
    return;
  *((vu32 *)0xFFFE0144) = 0x1F800000;
  g_scrtpad_internal_data.m_scrtpad_is_allocated = 0;
}

void *scrtpad_getinternaldata(void)
{
  return &g_scrtpad_internal_data;
}
