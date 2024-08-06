
#include <acmem.h>
#include <accore.h>
#include <irx_imports.h>

#define MODNAME "Arcade_Memory_Access"
IRX_ID(MODNAME, 1, 1);
// Text section hash:
// 697bf204c8fe9f91d78cf327c2247f48
// Known titles:
// NM00004
// NM00005
// NM00006
// NM00008
// Path strings:
// /home/ueda/tmp/psalm-0.1.3/mem-iop-0.1.4/src/
// /home/ueda/tmp/psalm-0.1.3/core-hdr-0.1.3/src/util/
// TODO: diff with module text hash 7a8be932b87c8e6ef19a48318cce1e0b

#define acMemEntry _start

extern struct irx_export_table _exp_acmem;

// acmem-entry.o

int acMemEntry(int argc, char **argv)
{
  int ret;

  ret = acMemModuleStart(argc, argv);
  // cppcheck-suppress knownConditionTrueFalse
  if ( ret < 0 )
  {
    return ret;
  }
  if ( RegisterLibraryEntries(&_exp_acmem) != 0 )
    return -16;
  return 0;
}

// memi.o

acMemT acMemSetup(acMemData *mem, void *buf, int size)
{
  if ( mem )
  {
    mem->m_buf = buf;
    mem->m_size = size;
    mem->m_id = 0;
    mem->m_attr = 0;
  }
  return mem;
}

int acMemSend(acMemT mem, acMemEEaddr addr, int size, int retry)
{
  int m_size;
  SifDmaTransfer_t dma_data;
  acSpl state;

  m_size = size;
  if ( !mem )
    return -22;
  if ( mem->m_buf == 0 )
  {
    return -14;
  }
  if ( mem->m_size < (acUint32)size )
    m_size = mem->m_size;
  if ( m_size > 0 )
  {
    dma_data.src = mem->m_buf;
    dma_data.dest = (void *)addr;
    dma_data.size = m_size;
    dma_data.attr = 0;
    while ( 1 )
    {
      unsigned int id;

      CpuSuspendIntr(&state);
      id = sceSifSetDma(&dma_data, 1);
      CpuResumeIntr(state);
      if ( id )
      {
        mem->m_id = id;
        return m_size;
      }
      DelayThread(100);
      --retry;
      if ( retry < 0 )
        return -116;
    }
  }
  return 0;
}

int acMemWait(acMemT mem, int threshold, int retry)
{
  unsigned int id;
  int v7;
  int count;
  int v9;

  if ( !mem )
    return -22;
  id = mem->m_id;
  v7 = retry + 1;
  if ( !id )
    return 0;
  count = 0;
  if ( v7 <= 0 )
    return -116;
  v9 = v7;
  while ( sceSifDmaStat(id) >= 0 )
  {
    if ( threshold <= 0 )
      DelayThread(100);
    else
      --threshold;
    if ( ++count >= v9 )
      return -116;
  }
  mem->m_id = 0;
  return count;
}

int acMemReceive(acMemT mem, acMemEEaddr addr, int size)
{
  void *m_buf;
  SifRpcReceiveData_t recv_data;

  if ( !mem )
    return -22;
  m_buf = mem->m_buf;
  if ( mem->m_buf == 0 )
  {
    return -14;
  }
  if ( mem->m_size < (acUint32)size )
    size = mem->m_size;
  if ( size > 0 )
  {
    mem->m_id = 0;
    if ( sceSifGetOtherData(&recv_data, (void *)addr, m_buf, size, 0) < 0 )
      return -5;
    return size;
  }
  return 0;
}

int acMemModuleStatus()
{
  return 0;
}

int acMemModuleStart(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  return 0;
}

int acMemModuleStop()
{
  return 0;
}

int acMemModuleRestart(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  return -88;
}
