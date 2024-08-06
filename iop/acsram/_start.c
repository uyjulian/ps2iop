
#include <acsram.h>
#include <irx_imports.h>

#define MODNAME "Arcade_SRAM"
IRX_ID(MODNAME, 1, 1);
// Text section hash:
// 9678b9c8dededca0a021cc70826d49d4
// Known titles:
// NM00004
// NM00005
// NM00006
// NM00008
// Path strings:
// /home/ueda/tmp/psalm-0.1.3/sram-iop-0.1.4/src/
// TODO: diff with module text hash 747b6206ea65e1fe9b9944b74e7e1b51

extern struct irx_export_table _exp_acsram;

#define acSramEntry _start

// acsram-entry.o

int acSramEntry(int argc, char **argv)
{
  int ret;

  ret = acSramModuleStart(argc, argv);
  // cppcheck-suppress knownConditionTrueFalse
  if ( ret < 0 )
  {
    return ret;
  }
  if ( RegisterLibraryEntries(&_exp_acsram) != 0 )
    return -16;
  return 0;
}

// sram.o

int acSramRead(acSramAddr addr, void *buf, int size)
{
  volatile acUint16 *src;
  int i;

  src = (volatile acUint16 *)(2 * (addr & 0x7FFF) + 0xB2500000);
  for ( i = size; i > 0; buf = (acUint8 *)buf + 1 )
  {
    --i;
    *(acUint8 *)buf = *(volatile acUint8 *)src++;
  }
  return size - i;
}

int acSramWrite(acSramAddr addr, void *buf, int size)
{
  volatile acUint16 *dst;
  int i;

  dst = (volatile acUint16 *)(2 * (addr & 0x7FFF) + 0xB2500000);
  for ( i = size; i > 0; ++dst )
  {
    --i;
    *dst = *(acUint8 *)buf;
    buf = (acUint8 *)buf + 1;
  }
  return size - i;
}

int acSramModuleStart(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  return 0;
}

int acSramModuleStop()
{
  return 0;
}

int acSramModuleRestart(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  return 0;
}

int acSramModuleStatus()
{
  return 1;
}
