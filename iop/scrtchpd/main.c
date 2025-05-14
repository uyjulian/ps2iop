
#include "irx_imports.h"

IRX_ID("ScratchPad_service", 1, 1);

const struct irx_export_table exports =
{
  1103101952u,
  NULL,
  257u,
  0u,
  { 115u, 99u, 114u, 116u, 112u, 97u, 100u, 0u },
  { 0 }
};
int g_scrtpad_is_allocated;
int g_scrtpad_alloc_count;

int _start(int ac, char **av)
{
  int libreg_res;
  int state;

  (void)ac;
  (void)av;

  CpuSuspendIntr(&state);
  libreg_res = RegisterLibraryEntries((struct irx_export_table *)&exports);
  CpuResumeIntr(state);
  if ( libreg_res )
  {
    return 1;
  }
  g_scrtpad_is_allocated = 0;
  g_scrtpad_alloc_count = 0;
  return 2;
}

void *AllocScratchPad(int mode)
{
  int alloc_addr;
  int state;

  if ( mode )
    return (void *)-405;
  CpuSuspendIntr(&state);
  if ( g_scrtpad_is_allocated )
  {
    CpuResumeIntr(state);
    return (void *)-429;
  }
  g_scrtpad_is_allocated = 1;
  g_scrtpad_alloc_count += 1;
  alloc_addr = ( (g_scrtpad_alloc_count & 1) != 0 ) ? 0x1F800800 : 0x1F800C00;
  *((vu32 *)0xFFFE0144) = alloc_addr;
  CpuResumeIntr(state);
  return (void *)alloc_addr;
}

int FreeScratchPad(void *alloced_addr)
{
  int state;

  CpuSuspendIntr(&state);
  if ( !g_scrtpad_is_allocated )
  {
    CpuResumeIntr(state);
    return -430;
  }
  if ( *((vu32 *)0xFFFE0144) != (( (g_scrtpad_alloc_count & 1) != 0 ) ? 0x1F800800 : 0x1F800C00) )
  {
    CpuResumeIntr(state);
    return -428;
  }
  *((vu32 *)0xFFFE0144) = 0x1F800000;
  g_scrtpad_is_allocated = 0;
  CpuResumeIntr(state);
  return 0;
}

void _deinit(int disintr)
{
  if ( !disintr )
  {
  	*((vu32 *)0xFFFE0144) = 0x1F800000;
    g_scrtpad_is_allocated = 0;
  }
}

int *scrtpad_getinternaldata(void)
{
  return &g_scrtpad_is_allocated;
}
