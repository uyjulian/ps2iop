
#include "irx_imports.h"

IRX_ID("S147MDEV", 2, 1);

#define __fastcall
#define __cdecl
#define _BYTE u8
#define _WORD u16
#define _DWORD u32
#define __int32 int

//-------------------------------------------------------------------------
// Function declarations

int _start();
int __fastcall register_atfile_ioman_device(const char *atfile_name, const char *atfile_desc);
int __fastcall s147mdev_4_addfs(iop_device_t *drv, int unit10);
int __fastcall s147mdev_5_delfs(int unit10);
int __fastcall atfile_drv_op_nulldev(iop_file_t *f);
int __cdecl atfile_drv_op_init(iop_device_t *dev);
int __cdecl atfile_drv_op_deinit(iop_device_t *dev);
int __cdecl atfile_drv_op_open(iop_file_t *f, const char *name, int flags);
int __cdecl atfile_drv_op_close(iop_file_t *f);
int __cdecl atfile_drv_op_read(iop_file_t *f, void *ptr, int size);
int __cdecl atfile_drv_op_write(iop_file_t *f, void *ptr, int size);
int __cdecl atfile_drv_op_lseek(iop_file_t *f, int offset, int mode);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_s147mdev;
iop_device_ops_t atfile_drv_ops =
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
iop_device_t g_atfile_device; // idb
iop_device_t *g_atfile_unit_info[10];

//----- (00400000) --------------------------------------------------------
int _start()
{
  Kprintf("\ns147mdev.irx: System147 Multi Device File System Manager v%d.%d\n", 2, 1);
  register_atfile_ioman_device("atfile", "Multi Device File System");
  if ( RegisterLibraryEntries(&_exp_s147mdev) )
  {
    Kprintf("s147mdev.irx: RegisterLibraryEntries - Failed.\n");
    return 1;
  }
  else
  {
    Kprintf("s147mdev.irx: RegisterLibraryEntries - OK.\n");
    return 0;
  }
}

//----- (004000A0) --------------------------------------------------------
int __fastcall register_atfile_ioman_device(const char *atfile_name, const char *atfile_desc)
{
  int i; // [sp+10h] [+10h]

  for ( i = 0; i < 10; ++i )
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
int __fastcall s147mdev_4_addfs(iop_device_t *drv, int unit10)
{
  int retval; // [sp+10h] [+10h]

  if ( unit10 >= 0 && unit10 < 100 )
  {
    if ( drv )
    {
      retval = ((int (__fastcall *)(iop_device_t *))drv->ops->init)(drv);
      if ( retval >= 0 )
        g_atfile_unit_info[unit10 / 10] = drv;
      return retval;
    }
    else
    {
      Kprintf("s147mdev.irx: Invalid device table\n");
      return -1;
    }
  }
  else
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -1;
  }
}

//----- (004002A4) --------------------------------------------------------
int __fastcall s147mdev_5_delfs(int unit10)
{
  int retval; // [sp+10h] [+10h]

  if ( unit10 >= 0 && unit10 < 100 )
  {
    retval = 0;
    if ( g_atfile_unit_info[unit10 / 10] )
      retval = ((int (__fastcall *)(iop_device_t *))g_atfile_unit_info[unit10 / 10]->ops->deinit)(g_atfile_unit_info[unit10 / 10]);
    if ( retval >= 0 )
      g_atfile_unit_info[unit10 / 10] = 0;
    return retval;
  }
  else
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -1;
  }
}
// 4003C0: variable 'retval' is possibly undefined

//----- (00400430) --------------------------------------------------------
int __fastcall atfile_drv_op_nulldev(iop_file_t *f)
{
  int unit; // [sp+10h] [+10h]

  unit = f->unit;
  if ( g_atfile_unit_info[unit / 10] )
    return 0;
  Kprintf("s147mdev.irx: Undefined unit number (%d), do nothing\n", unit);
  return -19;
}

//----- (004004D8) --------------------------------------------------------
int __cdecl atfile_drv_op_init(iop_device_t *dev)
{
  return 0;
}

//----- (00400500) --------------------------------------------------------
int __cdecl atfile_drv_op_deinit(iop_device_t *dev)
{
  return 0;
}

//----- (00400528) --------------------------------------------------------
int __cdecl atfile_drv_op_open(iop_file_t *f, const char *name, int flags)
{
  iop_file_t fstk; // [sp+10h] [+10h] BYREF
  int unit; // [sp+20h] [+20h]
  int retres; // [sp+24h] [+24h]

  unit = f->unit;
  if ( unit >= 0 && unit < 100 )
  {
    fstk.mode = f->mode;
    fstk.unit = f->unit % 10;
    fstk.device = f->device;
    if ( g_atfile_unit_info[unit / 10] )
    {
      retres = ((int (__fastcall *)(iop_file_t *, const char *, int))g_atfile_unit_info[unit / 10]->ops->open)(
                 &fstk,
                 name,
                 flags);
      f->privdata = fstk.privdata;
      return retres;
    }
    else
    {
      Kprintf("s147mdev.irx: Undefined unit number (%d), do nothing\n", unit);
      return -19;
    }
  }
  else
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -19;
  }
}

//----- (004006F0) --------------------------------------------------------
int __cdecl atfile_drv_op_close(iop_file_t *f)
{
  iop_file_t fstk; // [sp+10h] [+10h] BYREF
  int unit; // [sp+20h] [+20h]

  unit = f->unit;
  if ( unit >= 0 && unit < 100 )
  {
    fstk.mode = f->mode;
    fstk.unit = f->unit % 10;
    fstk.device = f->device;
    fstk.privdata = f->privdata;
    if ( g_atfile_unit_info[unit / 10] )
    {
      return ((int (__fastcall *)(iop_file_t *))g_atfile_unit_info[unit / 10]->ops->close)(&fstk);
    }
    else
    {
      Kprintf("s147mdev.irx: Undefined unit number (%d), do nothing\n", unit);
      return -19;
    }
  }
  else
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -19;
  }
}

//----- (004008AC) --------------------------------------------------------
int __cdecl atfile_drv_op_read(iop_file_t *f, void *ptr, int size)
{
  iop_file_t fstk; // [sp+10h] [+10h] BYREF
  int unit; // [sp+20h] [+20h]

  unit = f->unit;
  if ( unit >= 0 && unit < 100 )
  {
    fstk.mode = f->mode;
    fstk.unit = f->unit % 10;
    fstk.device = f->device;
    fstk.privdata = f->privdata;
    if ( g_atfile_unit_info[unit / 10] )
    {
      return ((int (__fastcall *)(iop_file_t *, void *, int))g_atfile_unit_info[unit / 10]->ops->read)(&fstk, ptr, size);
    }
    else
    {
      Kprintf("s147mdev.irx: Undefined unit number (%d), do nothing\n", unit);
      return -19;
    }
  }
  else
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -19;
  }
}

//----- (00400A78) --------------------------------------------------------
int __cdecl atfile_drv_op_write(iop_file_t *f, void *ptr, int size)
{
  iop_file_t fstk; // [sp+10h] [+10h] BYREF
  int unit; // [sp+20h] [+20h]

  unit = f->unit;
  if ( unit >= 0 && unit < 100 )
  {
    fstk.mode = f->mode;
    fstk.unit = f->unit % 10;
    fstk.device = f->device;
    fstk.privdata = f->privdata;
    if ( g_atfile_unit_info[unit / 10] )
    {
      return ((int (__fastcall *)(iop_file_t *, void *, int))g_atfile_unit_info[unit / 10]->ops->write)(
               &fstk,
               ptr,
               size);
    }
    else
    {
      Kprintf("s147mdev.irx: Undefined unit number (%d), do nothing\n", unit);
      return -19;
    }
  }
  else
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -19;
  }
}

//----- (00400C44) --------------------------------------------------------
int __cdecl atfile_drv_op_lseek(iop_file_t *f, int offset, int mode)
{
  iop_file_t fstk; // [sp+10h] [+10h] BYREF
  int unit; // [sp+20h] [+20h]

  unit = f->unit;
  if ( unit >= 0 && unit < 100 )
  {
    fstk.mode = f->mode;
    fstk.unit = f->unit % 10;
    fstk.device = f->device;
    fstk.privdata = f->privdata;
    if ( g_atfile_unit_info[unit / 10] )
    {
      return ((int (__fastcall *)(iop_file_t *, int, int))g_atfile_unit_info[unit / 10]->ops->lseek)(
               &fstk,
               offset,
               mode);
    }
    else
    {
      Kprintf("s147mdev.irx: Undefined unit number (%d), do nothing\n", unit);
      return -19;
    }
  }
  else
  {
    Kprintf("s147mdev.irx: Invalid unit number\n");
    return -19;
  }
}
