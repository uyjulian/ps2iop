
#include <acjv.h>
#include <irx_imports.h>

#define MODNAME "Arcade_JV"
IRX_ID(MODNAME, 1, 1);
// Text section hash:
// 8a8acf790934d8eb0dffdd8b57c06374
// Known titles:
// NM00005
// NM00008
// Path strings:
// /usr/local/sys246/psalm-0.1.3/jv-iop-0.1.4/src/
// TODO: diff with module text hash cda3a00a245ec5ea8c478da1b1743e3b

extern struct irx_export_table _exp_acjv;

#define acJvEntry _start

typedef volatile acUint16 *acJvReg;

// acjv-entry.o

int acJvEntry(int argc, char **argv)
{
  int ret;

  ret = acJvModuleStart(argc, argv);
  // cppcheck-suppress knownConditionTrueFalse
  if ( ret < 0 )
  {
    return ret;
  }
  if ( RegisterLibraryEntries((struct irx_export_table *)&_exp_acjv) != 0 )
    return -16;
  return 0;
}

// jv.o

int acJvRead(acJvAddr addr, void *buf, int size)
{
  acJvReg src;
  int i;

  src = (acJvReg)(2 * (addr & 0x3FFF) + 0xB2400000);
  for ( i = size; i > 0; buf = (acUint8 *)buf + 1 )
  {
    --i;
    *(acUint8 *)buf = *src++;
  }
  return size - i;
}

int acJvWrite(acJvAddr addr, void *buf, int size)
{
  acJvReg dst;
  int i;

  dst = (acJvReg)(2 * (addr & 0x3FFF) + 0xB2400000);
  for ( i = size; i > 0; ++dst )
  {
    --i;
    *dst = *(acUint8 *)buf;
    buf = (acUint8 *)buf + 1;
  }
  return size - i;
}

int acJvGet(acJvAddr addr)
{
  return ((*(volatile acUint16 *)(2 * (addr & 0x3FFF) + 0xB2400000 + 2) << 8) & 0xFF) | ((*(volatile acUint16 *)(2 * (addr & 0x3FFF) + 0xB2400000)) & 0xFF);
}

int acJvPut(acJvAddr addr, int value)
{
  volatile acUint16 *v3;

  v3 = (volatile acUint16 *)(2 * (addr & 0x3FFF) + 0xB2400000);
  *v3 = value;
  v3[1] = value >> 8;
  return value;
}

int acJvModuleStart(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  *((volatile acUint16 *)0xB2416002) = 0;
  return 0;
}

int acJvModuleStop()
{
  *((volatile acUint16 *)0xB2416000) = 0;
  return 0;
}

int acJvModuleRestart(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  return -88;
}

int acJvModuleStatus()
{
  return -88;
}

