
#include "irx_imports.h"

IRX_ID("S147MDEV", 2, 1);

//-------------------------------------------------------------------------
// Function declarations

static int register_atfile_ioman_device(const char *atfile_name, const char *atfile_desc);
int s147mdev_4_addfs(iop_device_t *drv, int unit10);
int s147mdev_5_delfs(int unit10);
static int atfile_drv_op_nulldev(const iop_file_t *f);
static int atfile_drv_op_init(iop_device_t *dev);
static int atfile_drv_op_deinit(iop_device_t *dev);
static int atfile_drv_op_open(iop_file_t *f, const char *name, int flags);
static int atfile_drv_op_close(iop_file_t *f);
static int atfile_drv_op_read(iop_file_t *f, void *ptr, int size);
static int atfile_drv_op_write(iop_file_t *f, void *ptr, int size);
static int atfile_drv_op_lseek(iop_file_t *f, int offset, int mode);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_s147mdev;
static iop_device_ops_t atfile_drv_ops =
{
  &atfile_drv_op_init,
  &atfile_drv_op_deinit,
  (void *)&atfile_drv_op_nulldev,
  &atfile_drv_op_open,
  &atfile_drv_op_close,
  &atfile_drv_op_read,
  &atfile_drv_op_write,
  &atfile_drv_op_lseek,
  (void *)&atfile_drv_op_nulldev,
  (void *)&atfile_drv_op_nulldev,
  (void *)&atfile_drv_op_nulldev,
  (void *)&atfile_drv_op_nulldev,
  (void *)&atfile_drv_op_nulldev,
  (void *)&atfile_drv_op_nulldev,
  (void *)&atfile_drv_op_nulldev,
  (void *)&atfile_drv_op_nulldev,
  (void *)&atfile_drv_op_nulldev,
}; // weak
static iop_device_t g_atfile_device; // idb
static iop_device_t *g_atfile_unit_info[10];

//----- (00400000) --------------------------------------------------------
int _start(int ac, char **av)
{
  (void)ac;
  (void)av;
  Kprintf("\ns147mdev.irx: System147 Multi Device File System Manager v%d.%d\n", 2, 1);
  register_atfile_ioman_device("atfile", "Multi Device File System");
  if ( RegisterLibraryEntries(&_exp_s147mdev) )
  {
    Kprintf("s147mdev.irx: RegisterLibraryEntries - Failed.\n");
    return 1;
  }
  Kprintf("s147mdev.irx: RegisterLibraryEntries - OK.\n");
  return 0;
}

//----- (004000A0) --------------------------------------------------------
static int register_atfile_ioman_device(const char *atfile_name, const char *atfile_desc)
{
  int i; // [sp+10h] [+10h]

  for ( i = 0; i < 10; i += 1 )
    g_atfile_unit_info[i] = 0;
  g_atfile_device.name = atfile_name;
  g_atfile_device.type = 16;
  g_atfile_device.version = 0;
  g_atfile_device.desc = atfile_desc;
  g_atfile_device.ops = &atfile_drv_ops;
  DelDrv(atfile_name);
  AddDrv(&g_atfile_device);
  return 0;
}
// 401330: using guessed type int (*atfile_drv_ops[17])();

//----- (00400184) --------------------------------------------------------
int s147mdev_4_addfs(iop_device_t *drv, int unit10)
{
  int retres; // [sp+10h] [+10h]

  if ( unit10 < 0 || unit10 >= 100 )
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -1;
  }
  if ( !drv )
  {
    Kprintf("s147mdev.irx: Invalid device table\n");
    return -1;
  }
  retres = drv->ops->init(drv);
  if ( retres >= 0 )
    g_atfile_unit_info[unit10 / 10] = drv;
  return retres;
}

//----- (004002A4) --------------------------------------------------------
int s147mdev_5_delfs(int unit10)
{
  int retres; // [sp+10h] [+10h]

  if ( unit10 < 0 || unit10 >= 100 )
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -1;
  }
  retres = ( g_atfile_unit_info[unit10 / 10] ) ? g_atfile_unit_info[unit10 / 10]->ops->deinit(g_atfile_unit_info[unit10 / 10]) : 0;
  if ( retres >= 0 )
    g_atfile_unit_info[unit10 / 10] = 0;
  return retres;
}
// 4003C0: variable 'retres' is possibly undefined

//----- (00400430) --------------------------------------------------------
static int atfile_drv_op_nulldev(const iop_file_t *f)
{
  int unit; // [sp+10h] [+10h]

  unit = f->unit;
  if ( !g_atfile_unit_info[unit / 10] )
  {
    Kprintf("s147mdev.irx: Undefined unit number (%d), do nothing\n", unit);
    return -19;
  }
  return 0;
}

//----- (004004D8) --------------------------------------------------------
static int atfile_drv_op_init(iop_device_t *dev)
{
  (void)dev;
  return 0;
}

//----- (00400500) --------------------------------------------------------
static int atfile_drv_op_deinit(iop_device_t *dev)
{
  (void)dev;
  return 0;
}

//----- (00400528) --------------------------------------------------------
static int atfile_drv_op_open(iop_file_t *f, const char *name, int flags)
{
  iop_file_t fstk; // [sp+10h] [+10h] BYREF
  int unit; // [sp+20h] [+20h]
  int retres; // [sp+24h] [+24h]

  unit = f->unit;
  if ( unit < 0 || unit >= 100 )
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -19;
  }
  fstk.mode = f->mode;
  fstk.unit = f->unit % 10;
  fstk.device = f->device;
  if ( !g_atfile_unit_info[unit / 10] )
  {
    Kprintf("s147mdev.irx: Undefined unit number (%d), do nothing\n", unit);
    return -19;
  }
  retres = g_atfile_unit_info[unit / 10]->ops->open(&fstk, name, flags);
  f->privdata = fstk.privdata;
  return retres;
}

//----- (004006F0) --------------------------------------------------------
static int atfile_drv_op_close(iop_file_t *f)
{
  iop_file_t fstk; // [sp+10h] [+10h] BYREF
  int unit; // [sp+20h] [+20h]

  unit = f->unit;
  if ( unit < 0 || unit >= 100 )
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -19;
  }
  fstk.mode = f->mode;
  fstk.unit = f->unit % 10;
  fstk.device = f->device;
  fstk.privdata = f->privdata;
  if ( !g_atfile_unit_info[unit / 10] )
  {
    Kprintf("s147mdev.irx: Undefined unit number (%d), do nothing\n", unit);
    return -19;
  }
  return g_atfile_unit_info[unit / 10]->ops->close(&fstk);
}

//----- (004008AC) --------------------------------------------------------
static int atfile_drv_op_read(iop_file_t *f, void *ptr, int size)
{
  iop_file_t fstk; // [sp+10h] [+10h] BYREF
  int unit; // [sp+20h] [+20h]

  unit = f->unit;
  if ( unit < 0 || unit >= 100 )
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -19;
  }
  fstk.mode = f->mode;
  fstk.unit = f->unit % 10;
  fstk.device = f->device;
  fstk.privdata = f->privdata;
  if ( !g_atfile_unit_info[unit / 10] )
  {
    Kprintf("s147mdev.irx: Undefined unit number (%d), do nothing\n", unit);
    return -19;
  }
  return g_atfile_unit_info[unit / 10]->ops->read(&fstk, ptr, size);
}

//----- (00400A78) --------------------------------------------------------
static int atfile_drv_op_write(iop_file_t *f, void *ptr, int size)
{
  iop_file_t fstk; // [sp+10h] [+10h] BYREF
  int unit; // [sp+20h] [+20h]

  unit = f->unit;
  if ( unit < 0 || unit >= 100 )
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -19;
  }
  fstk.mode = f->mode;
  fstk.unit = f->unit % 10;
  fstk.device = f->device;
  fstk.privdata = f->privdata;
  if ( !g_atfile_unit_info[unit / 10] )
  {
    Kprintf("s147mdev.irx: Undefined unit number (%d), do nothing\n", unit);
    return -19;
  }
  return g_atfile_unit_info[unit / 10]->ops->write(&fstk, ptr, size);
}

//----- (00400C44) --------------------------------------------------------
static int atfile_drv_op_lseek(iop_file_t *f, int offset, int mode)
{
  iop_file_t fstk; // [sp+10h] [+10h] BYREF
  int unit; // [sp+20h] [+20h]

  unit = f->unit;
  if ( unit < 0 || unit >= 100 )
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -19;
  }
  fstk.mode = f->mode;
  fstk.unit = f->unit % 10;
  fstk.device = f->device;
  fstk.privdata = f->privdata;
  if ( !g_atfile_unit_info[unit / 10] )
  {
    Kprintf("s147mdev.irx: Undefined unit number (%d), do nothing\n", unit);
    return -19;
  }
  return g_atfile_unit_info[unit / 10]->ops->lseek(&fstk, offset, mode);
}
