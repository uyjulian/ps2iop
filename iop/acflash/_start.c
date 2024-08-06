
#include <acflash.h>
#include <accore.h>
#include <irx_imports.h>

#define MODNAME "Arcade_Flash_Memory"
IRX_ID(MODNAME, 1, 1);
// Text section hash:
// 83c44942d316812471a189fd2015bbc9
// Known titles:
// NM00005
// NM00006
// NM00008
// Path strings:
// /home/ueda/tmp/psalm-0.1.3/flash-iop-0.1.2/src/
// TODO: diff with module text hash 1437cb87136e2564482cd3f609ab4023

#define acFlashEntry _start

extern struct irx_export_table _exp_acflash;

typedef acUint16 flash_data_t;
typedef acUint32 flash_addr_t;
typedef volatile flash_data_t *flash_ptr_t;

struct flash_ops
{
  // cppcheck-suppress unusedStructMember
  char *fo_name;
  acUint32 fo_bsize;
  acUint32 fo_blocks;
  // cppcheck-suppress unusedStructMember
  int fo_padding;
  int (*fo_erase)(flash_addr_t addr);
  int (*fo_program)(flash_addr_t addr, const flash_data_t *buf, int size);
  int (*fo_reset)(flash_addr_t addr);
  int (*fo_status)(flash_addr_t addr);
};

typedef struct flash_ops *flash_ops_t;

struct flash_softc
{
  acInt32 status;
  acInt32 size;
  flash_ops_t ops;
  acUint32 padding;
};

typedef flash_ops_t (*flash_probe_t)(flash_addr_t addr);

static int flash_erase(flash_addr_t addr);
static int flash_program(flash_addr_t addr, const flash_data_t *buf, int size);
static int flash_reset(flash_addr_t addr);
flash_ops_t flash_probe_i28f640f5(flash_addr_t addr);
static int flash_status(flash_addr_t addr);
static int flash_erase_0(flash_addr_t addr);
static int flash_program_0(flash_addr_t addr, const flash_data_t *buf, int size);
static int flash_reset_0(flash_addr_t addr);
static int flash_status_0(flash_addr_t addr);
flash_ops_t flash_probe_mbm29f033c(flash_addr_t addr);

static flash_probe_t probes_22[2] = { &flash_probe_i28f640f5, &flash_probe_mbm29f033c };
static struct flash_ops ops_30 =
{
  "Intel 28F640J5",
  131072u,
  64u,
  0,
  &flash_erase,
  &flash_program,
  &flash_reset,
  &flash_status
};
static struct flash_ops ops_22 =
{
  "Fujitsu 29F033C",
  131072u,
  64u,
  0,
  &flash_erase_0,
  &flash_program_0,
  &flash_reset_0,
  &flash_status_0
};
static struct flash_softc Flashc;

// acflash-entry.o

int acFlashEntry(int argc, char **argv)
{
  int ret;

  ret = acFlashModuleStart(argc, argv);
  if ( ret < 0 )
  {
    return ret;
  }
  if ( RegisterLibraryEntries((struct irx_export_table *)&_exp_acflash) != 0 )
    return -16;
  return 0;
}

// flash.o

int acFlashStart()
{
  if ( Flashc.status == 2 )
    return -11;
  if ( Flashc.status != 1 )
  {
    return -6;
  }
  *((volatile acUint16 *)0xB2416006) = 0;
  Flashc.status = 2;
  return 0;
}

int acFlashStop()
{
  flash_ops_t ops;
  int bsize;
  int blocks;
  acFlashAddr addr;
  acFlashAddr v5;

  if ( Flashc.status == 1 )
    return 0;
  if ( Flashc.status != 2 )
  {
    return -6;
  }
  ops = Flashc.ops;
  bsize = Flashc.ops->fo_bsize;
  blocks = Flashc.ops->fo_blocks - 1;
  addr = 0xB0000000;
  v5 = 0xB0000000;
  while ( blocks >= 0 )
  {
    addr += bsize;
    --blocks;
    ops->fo_reset(v5);
    v5 = addr;
  }
  Flashc.status = 1;
  *((volatile acUint16 *)0xB2416004) = 0;
  return 0;
}

int acFlashErase(acFlashAddr addr)
{
  if ( Flashc.status == 1 )
    return -13;
  if ( Flashc.status != 2 )
  {
    return -6;
  }
  if ( addr >= (acUint32)Flashc.size )
    return -34;
  return Flashc.ops->fo_erase(addr + 0xB0000000);
}

int acFlashProgram(acFlashAddr addr, void *buf, int count)
{
  if ( Flashc.status == 1 )
    return -13;
  if ( Flashc.status != 2 )
  {
    return -6;
  }
  if ( (addr & 1) != 0 )
  {
    return -14;
  }
  if ( addr >= (acUint32)Flashc.size )
    return -34;
  return Flashc.ops->fo_program(addr + 0xB0000000, (flash_data_t *)buf, count);
}

int acFlashRead(acFlashAddr addr, void *buf, int count)
{
  void *v3;
  flash_addr_t v6;
  int size;
  signed int v8;
  struct flash_softc *flashc;

  v3 = buf;
  if ( Flashc.status == 0 )
  {
    return -6;
  }
  if ( (addr & 1) != 0 )
  {
    return -14;
  }
  if ( addr + count >= (acUint32)Flashc.size )
  {
    return -34;
  }
  v6 = (flash_addr_t)(addr + 0xB0000000);
  if ( Flashc.status >= 2 )
  {
    Flashc.ops->fo_reset(v6);
    buf = v3;
  }
  size = count;
  v8 = (unsigned int)count >> 1;
  for ( flashc = (struct flash_softc *)v6; v8 > 0; buf = (char *)buf + 2 )
  {
    --v8;
    *(acUint16 *)buf = flashc->status;
    flashc = (struct flash_softc *)((char *)flashc + 2);
  }
  return size - 2 * v8;
}

int acFlashVerify(acFlashAddr addr, void *buf, int count)
{
  void *v3;
  flash_addr_t v6;
  int size;
  signed int v8;
  struct flash_softc *flashc;

  v3 = buf;
  if ( Flashc.status == 0 )
  {
    return -6;
  }
  if ( (addr & 1) != 0 )
  {
    return -14;
  }
  if ( addr + count >= (acUint32)Flashc.size )
  {
    return -34;
  }
  v6 = (flash_addr_t)(addr + 0xB0000000);
  if ( Flashc.status >= 2 )
  {
    Flashc.ops->fo_reset(v6);
    buf = v3;
  }
  size = count;
  v8 = (unsigned int)count >> 1;
  for ( flashc = (struct flash_softc *)v6; v8 > 0; --v8 )
  {
    int status_low;
    int v11;

    status_low = flashc->status & 0xFFFF;
    flashc = (struct flash_softc *)((char *)flashc + 2);
    v11 = *(acUint16 *)buf;
    buf = (char *)buf + 2;
    if ( v11 != status_low )
      break;
  }
  return size - 2 * v8;  
}

int acFlashStatus(acFlashAddr addr)
{
  if ( Flashc.status == 1 )
    return 1;
  if ( Flashc.status == 2 )
  {
    if ( addr >= (acUint32)Flashc.size )
      return -34;
    return Flashc.ops->fo_status(addr + 0xB0000000);
  }
  return -6;
}

int acFlashInfo(acFlashInfoData *info)
{
  flash_ops_t ops;
  struct flash_softc *flashc;

  if ( info == NULL )
  {
    return -22;
  }
  if ( Flashc.status == 0 )
  {
    return -6;
  }
  ops = Flashc.ops;
  info->fi_blocks = Flashc.ops->fo_blocks;
  flashc = (struct flash_softc *)ops->fo_bsize;
  info->fi_bsize = (acUint32)flashc;
  return 0;  
}

int acFlashModuleStatus()
{
  return Flashc.status;
}

int acFlashModuleStart(int argc, char **argv)
{
  acInt32 v4;
  int v5;
  int index;
  struct flash_ops *v9;

  (void)argc;
  (void)argv;
  if ( acFlashModuleStatus() != 0 )
  {
    return -16;
  }
  *((volatile acUint16 *)0xB2416006) = 0;
  DelayThread(100000);
  index = 0;
  while ( (unsigned int)index < 2 )
  {
    if ( *(probes_22[index]) )
    {
      v9 = (probes_22[index])(0xB0000000);
      if ( v9 )
      {
        Flashc.status = 1;
        v4 = v9->fo_bsize * v9->fo_blocks;
        Flashc.ops = v9;
        v5 = 0;
        Flashc.size = v4;
        break;
      }
    }
    ++index;
  }
  if ( (unsigned int)index >= 2 )
  {
    printf("acflash: no flash\n");
    v5 = -6;
  }
  *((volatile acUint16 *)0xB2416004) = 0;
  return v5;
}

int acFlashModuleStop()
{
  if ( acFlashModuleStatus() != 0 )
  {
    acFlashStop();
  }
  return 0;
}

int acFlashModuleRestart(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  return -88;
}

// i28f640j5.o

static int flash_wait(flash_ptr_t ptr, int tick, int count)
{
  int threshold;

  threshold = tick - 1;
  while ( threshold >= 0 )
  {
    int sr;

    *ptr = 0x70;
    sr = *ptr;
    if ( (sr & 0x80) == 0 )
      sr = -116;
    if ( sr >= 0 )
      return sr;
    threshold--;
  }
  do
  {
    int sr_v3;

    DelayThread(tick);
    *ptr = 0x70;
    sr_v3 = *ptr;
    if ( (sr_v3 & 0x80) == 0 )
      sr_v3 = -116;
    if ( sr_v3 >= 0 )
      return sr_v3;
    --count;
  }
  while ( count >= 0 );
  return -116;
}

static int flash_erase(flash_addr_t addr)
{
  *(volatile acUint16 *)addr = 0x20;
  *(volatile acUint16 *)addr = 0xD0;
  return ((acUint32)(~flash_wait((flash_ptr_t)addr, 400, 2)) >> 31) & 0x20000;
}

static int flash_program(flash_addr_t addr, const flash_data_t *buf, int size)
{
  int rest;
  int xlen;
  int count;
  int threshold;
  int v12;
  unsigned int v14;
  int xlen_v9;

  rest = size;
  while ( 1 )
  {
    int blen;

    if ( rest <= 0 )
      return size - rest;
    blen = 0x20000 - (addr & 0x1FFFF);
    if ( rest < blen )
      blen = rest;
    rest -= blen;
    while ( blen > 0 )
    {
      flash_addr_t v8;

      v8 = addr & 0xF;
      xlen = 16 - v8;
      count = 2;
      if ( blen < (int)(16 - v8) )
        xlen = blen;
      threshold = 399;
      while ( 1 )
      {
        *(volatile acUint16 *)addr = 0xE8;
        v12 = *(acUint16 *)addr;
        if ( (v12 & 0x80) != 0 )
          break;
        threshold--;
        if ( threshold < 0 )
        {
          while ( count >= 0 )
          {
            DelayThread(400);
            *(volatile acUint16 *)addr = 0xE8;
            v12 = *(volatile acUint16 *)addr;
            // cppcheck-suppress knownConditionTrueFalse
            if ( (v12 & 0x80) != 0 )
              break;
            --count;
            v12 = -116;
          }
          break;
        }
      }
      v14 = xlen + 1;
      if ( v12 < 0 )
        break;
      blen -= xlen;
      *(volatile acUint16 *)addr = v14 >> 1;
      xlen_v9 = (v14 >> 1) - 1;
      for ( *(volatile acUint16 *)addr = *buf; xlen_v9 >= 0; addr += 2 )
      {
        --xlen_v9;
        *(volatile acUint16 *)addr = *buf++;
      }
      *(volatile acUint16 *)(addr - 2) = 0xD0;
    }
    if ( flash_wait((flash_ptr_t)(addr - 2), 400, 2) < 0 || blen > 0 )
      return rest + blen - size;
  }
}

static int flash_reset(flash_addr_t addr)
{
  *(acUint16 *)addr = 0xFF;
  return 0x800000;
}

flash_ops_t flash_probe_i28f640f5(flash_addr_t addr)
{
  acUint16 vendor;
  acUint16 device;

  *(volatile acUint16 *)addr = 0xFF;
  *(volatile acUint16 *)addr = 0x90;
  vendor = *(volatile acUint16 *)addr;
  *(volatile acUint16 *)addr = 0x90;
  device = *(volatile acUint16 *)(addr + 2);
  *(volatile acUint16 *)addr = 0xFF;
  // cppcheck-suppress knownConditionTrueFalse
  if ( vendor != 0x89 || device != 0x15 )
    return 0;
  return &ops_30;
}

static int flash_status(flash_addr_t addr)
{
  *(volatile acUint16 *)addr = 0x70;
  // cppcheck-suppress knownConditionTrueFalse
  if ( (*(volatile acUint16 *)addr & 0x80) != 0 )
    return 1;
  return 2;
}

// mbm29f033c.o

static void flash_delay(int x)
{
  int v1;

  v1 = x - 1;
  while ( v1-- >= 0 )
    ;
}

static int flash_erase_0(flash_addr_t addr)
{
  int count;
  int pass;
  int i;
  unsigned int v8;
  int v9;

  count = 0;
  pass = 0;
  i = 1;
  *(volatile acUint16 *)addr = 0xAAAA;
  *(volatile acUint16 *)addr = 0x5555;
  *(volatile acUint16 *)addr = 0x8080;
  *(volatile acUint16 *)addr = 0xAAAA;
  *(volatile acUint16 *)addr = 0x5555;
  *(volatile acUint16 *)addr = 0x3030;
  while ( i >= 0 )
  {
    int threshold;
    int shift;
    acUint16 tmp_var;

    threshold = 200;
    shift = 8 * i;
    tmp_var = *(volatile acUint16 *)addr >> (8 * i);
    do
    {
      v8 = tmp_var ^ (*(volatile acUint16 *)addr >> (shift & 0xFF));
      tmp_var = *(volatile acUint16 *)addr >> (shift & 0xFF);
      if ( ((v8 >> 6) & 1) == 0 )
        break;
      if ( threshold <= 0 )
        DelayThread(200);
      else
        --threshold;
      ++count;
    }
    while ( ((uiptr)tmp_var & 0x20) == 0 );
    if ( ((tmp_var ^ ((*(volatile acUint16 *)addr >> (shift & 0xFF)) & 0xFF)) & 0x40) == 0 )
      ++pass;
    --i;
  }
  v9 = -116;
  if ( pass == 2 )
    v9 = count;
  if ( v9 < 0 )
    return -116;
  return 0x20000;
}

static int flash_program_0(flash_addr_t addr, const flash_data_t *buf, int size)
{
  int v4;
  int rest;
  acUint8 d;
  int threshold;
  int v15;
  acUint8 x;

  v4 = size;
  rest = size;
  while ( 1 )
  {
    int count;
    int pass;
    int i;
    flash_data_t data;
    int v11;
    int shift;
    int tmp_v12;

    if ( rest <= 0 )
      return v4 - rest;
    count = 0;
    pass = 0;
    i = 1;
    data = *buf;
    *(volatile acUint16 *)addr = 0xAAAA;
    *(volatile acUint16 *)addr = 0x5555;
    *(volatile acUint16 *)addr = 0xA0A0;
    v11 = data;
    *(volatile acUint16 *)addr = data;
    shift = 8;
    while ( i >= 0 )
    {
      d = (v11 >> (shift & 0xFF)) & 0xFF;
      threshold = 200;
      v15 = (v11 >> (shift & 0xFF)) & 0xFF;
      do
      {
        x = ((int)*(volatile acUint16 *)addr >> (shift & 0xFF)) & 0xFF;
        if ( v15 == x )
          break;
        if ( threshold <= 0 )
        {
          DelayThread(200);
        }
        else
        {
          --threshold;
        }
        ++count;
      }
      while ( (x & 0x20) == 0 );
      if ( d == (((int)*(volatile acUint16 *)addr >> (shift & 0xFF)) & 0xFF) )
        ++pass;
      shift = 8 * --i;
    }
    tmp_v12 = -116;
    if ( pass == 2 )
      tmp_v12 = count;
    if ( tmp_v12 < 0 )
      return rest - v4;
    ++buf;
    rest -= 2;
  }
}

static int flash_reset_0(flash_addr_t addr)
{
  *(acUint16 *)addr = 0xF0F0;
  flash_delay(100);
  return 0x800000;
}

static int flash_status_0(flash_addr_t addr)
{
  int pass;
  int i;

  (void)addr;
  pass = 0;
  for ( i = 1; i >= 0; --i )
    ++pass;
  if ( pass == 2 )
    return 1;
  return 2;
}

flash_ops_t flash_probe_mbm29f033c(flash_addr_t addr)
{
  int vendor;
  int device;

  flash_reset_0(addr);
  *(volatile acUint16 *)addr = 0xAAAA;
  *(volatile acUint16 *)addr = 0x5555;
  *(volatile acUint16 *)addr = 0x9090;
  DelayThread(500);
  vendor = *(volatile acUint16 *)addr;
  device = *(volatile acUint16 *)(addr + 2);
  flash_reset_0(addr);
  // cppcheck-suppress knownConditionTrueFalse
  if ( vendor != 0x404 || device != 0xD4D4 )
  {
    return 0;
  }
  return &ops_22;
}
