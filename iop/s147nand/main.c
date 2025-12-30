
#include <irx_imports.h>
#include <s147nand.h>
#include <iop_mmio_hwport.h>

IRX_ID("S147NAN2", 5, 2);

#define _break(...) __builtin_trap()

typedef struct s147_dev9_mem_mmio_x
{
  vu8 m_unk00;
  vu8 m_led;
  vu8 m_security_unlock_unlock;
  vu8 m_unk03;
  vu8 m_rtc_flag;
  vu8 m_watchdog_flag2;
  vu8 m_unk06;
  vu8 m_sram_write_flag;
  vu8 m_pad08;
  vu8 m_pad09;
  vu8 m_pad0A;
  vu8 m_pad0B;
  vu8 m_security_unlock_set1;
  vu8 m_security_unlock_set2;
} s147_dev9_mem_mmio_;

typedef struct s147nand_dev9_io_mmio_x
{
  vu8 m_nand_waitflag;
  vu8 m_nand_cmd_enable;
  vu8 m_nand_cmd_sel;
  vu8 m_nand_cmd_offs;
  vu8 m_nand_write_cmd_unlock;
  vu8 m_pad05;
  vu8 m_pad06;
  vu8 m_pad07;
  vu8 m_nand_outbyte;
} s147nand_dev9_io_mmio_;


typedef struct nand_direntry_stru_x
{
  char m_name[16];
  u32 m_unk;
  u8 m_type;
  u8 m_pad[3];
  u32 m_size;
  u32 m_offset;
} nand_direntry_stru_;


typedef struct nand_dir_stru_x
{
  char m_sig[8];
  u16 m_ver;
  char m_unk0[6];
  u32 m_entrycnt;
  u32 m_unk1;
  u32 m_unk2;
  u32 m_unk3;
  nand_direntry_stru_ m_direntry[63];
} nand_dir_stru_;


typedef struct nand_mdev_privdata_stru_x
{
  int m_seek_cur;
  int m_flags;
  int m_seek_max;
  int m_partition_offset;
} nand_mdev_privdata_stru_;


//-------------------------------------------------------------------------
// Function declarations

static int do_register_nand_to_mdev(const char *drv_name, const char *drv_desc);
static int nand_mdev_op_nulldev(void);
static int nand_mdev_op_init(iop_device_t *dev);
static int nand_mdev_op_deinit(iop_device_t *dev);
static int nand_mdev_op_open(iop_file_t *f, const char *name, int flags);
static int nand_mdev_op_close(iop_file_t *f);
static int nand_mdev_op_read(iop_file_t *f, void *ptr, int size);
static int nand_mdev_op_write(iop_file_t *f, void *ptr, int size);
static int nand_mdev_op_lseek(iop_file_t *f, int offset, int mode);
static int do_nand_open_inner1(nand_mdev_privdata_stru_ *privdat, int part, const char *name);
static int do_nand_open_inner2(nand_mdev_privdata_stru_ *privdat, const char *name);
static u32 do_get_nand_direntry(nand_mdev_privdata_stru_ *privdat, const char *name, size_t idx, char typ);
static int do_nand_bytes2sector(int pageoffs, int byteoffs);
static int do_nand_bytes2sector_remainder(int byteoffs);
static int do_nand_sector_rw(void *ptr, int pageoffs, int byteoffs, size_t size);
static int get_nand_partition_offset(int part);
static int nand_mdev_open_special(iop_file_t *f, const char *name);
static size_t nand_mdev_read_special(iop_file_t *f, void *ptr, size_t size);
static int nand_mdev_write_special(iop_file_t *f, void *ptr, int size);
static size_t do_nand_copy_seccode_from_buf(iop_file_t *f, void *ptr, size_t size);
static size_t do_nand_copy_videomode_from_buf(iop_file_t *f, void *ptr, size_t size);
static int nand_lowlevel_read_dma(void *ptr, int pageoffs, int byteoffs, int bytecnt);
static int nand_lowlevel_read_pio(void *ptr, int pageoffs, int byteoffs, int bytecnt);
static int nand_lowlevel_write_dma(void *ptr, int pageoffs, int byteoffs, int bytecnt);
static int nand_lowlevel_write_pio(void *ptr, int pageoffs, int byteoffs, int bytecnt);
static int nand_lowlevel_blockerase(int pageoffs);
static int nand_lowlevel_readid(void *ptr);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_s147nand;
static iop_device_ops_t nand_mdev_ops =
{
  &nand_mdev_op_init,
  &nand_mdev_op_deinit,
  (void *)&nand_mdev_op_nulldev,
  &nand_mdev_op_open,
  &nand_mdev_op_close,
  &nand_mdev_op_read,
  &nand_mdev_op_write,
  &nand_mdev_op_lseek,
  (void *)&nand_mdev_op_nulldev,
  (void *)&nand_mdev_op_nulldev,
  (void *)&nand_mdev_op_nulldev,
  (void *)&nand_mdev_op_nulldev,
  (void *)&nand_mdev_op_nulldev,
  (void *)&nand_mdev_op_nulldev,
  (void *)&nand_mdev_op_nulldev,
  (void *)&nand_mdev_op_nulldev,
  (void *)&nand_mdev_op_nulldev
}; // weak
static void *g_nand_unaligned_buf = NULL;
static int g_nand_unaligned_buf_alloced = 0; // weak
static int g_probunusd_dword_4051D0 = 0; // weak
static int g_nand_watchdog_enabled = 0; // weak
static nand_info_stru_ g_nand_info = { 2048, 2112, 64, 2048, 131072 }; // weak
static iop_device_t g_drv; // idb
static void *g_nand_sector_buffer; // idb
static const char *g_dev_name;
static iop_sema_t g_sema_param_dev; // idb
static int g_sema_id_dev; // idb
static iop_sema_t g_seama_param_1; // idb
static int g_sema_id_init; // idb
static nand_header_stru_ g_nand_header; // weak
static u16 *g_logical_addr_tbl;
static iop_sema_t g_sema_param; // idb
static int g_sema_id_nand; // idb
static int g_thid; // idb
iop_mmio_hwport_t iop_mmio_hwport_lo; // weak
s147_dev9_mem_mmio_ s147_dev9_mem_mmio; // weak
s147nand_dev9_io_mmio_ s147nand_dev9_io_mmio; // weak


//----- (00400000) --------------------------------------------------------
int _start(int ac, char **av)
{
  (void)ac;
  (void)av;
  Kprintf("\ns147nand.irx: System147 NAND-Flash File System Driver v%d.%d\n", 5, 2);
  if ( do_register_nand_to_mdev("nand", "NAND-Flash") )
    return 1;
  if ( RegisterLibraryEntries(&_exp_s147nand) )
  {
    Kprintf("s147nand.irx: RegisterLibraryEntries - Failed.\n");
    return 1;
  }
  Kprintf("s147nand.irx: RegisterLibraryEntries - OK.\n");
  return 0;
}

//----- (004000B0) --------------------------------------------------------
static int do_register_nand_to_mdev(const char *drv_name, const char *drv_desc)
{
  if ( s147nand_5_outerinit() < 0 )
    return -1;
  g_sema_param_dev.initial = 1;
  g_sema_param_dev.max = 1;
  g_sema_param_dev.attr = 1;
  g_sema_id_dev = CreateSema(&g_sema_param_dev);
  if ( g_sema_id_dev < 0 )
  {
    Kprintf("s147nand.irx: CreateSema error (%d)\n", g_sema_id_dev);
    return -1;
  }
  g_drv.name = drv_name;
  g_drv.type = 16;
  g_drv.version = 0;
  g_drv.desc = drv_desc;
  g_drv.ops = &nand_mdev_ops;
  s147mdev_5_delfs(0);
  s147mdev_4_addfs(&g_drv, 0);
  g_dev_name = drv_name;
  return 0;
}
// 405170: using guessed type int (*nand_mdev_ops[17])();

//----- (004001D4) --------------------------------------------------------
static int nand_mdev_op_nulldev(void)
{
  return 0;
}

//----- (004001F8) --------------------------------------------------------
static int nand_mdev_op_init(iop_device_t *dev)
{
  int state; // [sp+10h] [+10h] BYREF

  (void)dev;
  Kprintf("s147nand.irx: SectorBuffer=%d, FileParam=%d\n", 0, 1);
  CpuSuspendIntr(&state);
  g_nand_sector_buffer = AllocSysMemory(0, 2048, 0);
  CpuResumeIntr(state);
  if ( g_nand_sector_buffer )
    return 0;
  Kprintf("s147nand.irx: AllocSysMemory failed (s147file_Init)\n");
  return -12;
}

//----- (00400298) --------------------------------------------------------
static int nand_mdev_op_deinit(iop_device_t *dev)
{
  int state; // [sp+10h] [+10h] BYREF

  (void)dev;
  if ( g_nand_sector_buffer )
  {
    CpuSuspendIntr(&state);
    FreeSysMemory(g_nand_sector_buffer);
    CpuResumeIntr(state);
  }
  return 0;
}

//----- (00400300) --------------------------------------------------------
static int nand_mdev_op_open(iop_file_t *f, const char *name, int flags)
{
  nand_mdev_privdata_stru_ *privdat; // [sp+10h] [+10h]
  int state; // [sp+14h] [+14h] BYREF
  int retres; // [sp+18h] [+18h]

  (void)flags;
  retres = 0;
  WaitSema(g_sema_id_dev);
  if ( f->unit == 9 )
  {
    retres = nand_mdev_open_special(f, name);
    SignalSema(g_sema_id_dev);
    return retres;
  }
  CpuSuspendIntr(&state);
  f->privdata = AllocSysMemory(1, 16, 0);
  CpuResumeIntr(state);
  if ( !f->privdata )
  {
    Kprintf("s147nand.irx: AllocSysMemory failed (Open)\n");
    retres = -12;
  }
  if ( retres >= 0 )
  {
    privdat = (nand_mdev_privdata_stru_ *)f->privdata;
    memset(privdat, 0, sizeof(nand_mdev_privdata_stru_));
    retres = do_nand_open_inner1(privdat, f->unit, name);
  }
  if ( retres < 0 )
  {
    // Unofficial: check if not NULL
    if ( f->privdata )
    {
      CpuSuspendIntr(&state);
      FreeSysMemory(f->privdata);
      CpuResumeIntr(state);
    }
    SignalSema(g_sema_id_dev);
    return retres;
  }
  privdat->m_seek_cur = 0;
  SignalSema(g_sema_id_dev);
  return 0;
}

//----- (004004C4) --------------------------------------------------------
static int nand_mdev_op_close(iop_file_t *f)
{
  int state; // [sp+10h] [+10h] BYREF

  WaitSema(g_sema_id_dev);
  if ( f->privdata )
  {
    CpuSuspendIntr(&state);
    FreeSysMemory(f->privdata);
    CpuResumeIntr(state);
    f->privdata = 0;
  }
  SignalSema(g_sema_id_dev);
  return 0;
}

//----- (00400560) --------------------------------------------------------
static int nand_mdev_op_read(iop_file_t *f, void *ptr, int size)
{
  int xsize3; // $s0
  nand_mdev_privdata_stru_ *privdat; // [sp+18h] [+18h]
  int xsector1; // [sp+20h] [+20h]
  int xsector2; // [sp+24h] [+24h]
  int xsize2; // [sp+28h] [+28h]
  int cursz; // [sp+2Ch] [+2Ch]

  privdat = (nand_mdev_privdata_stru_ *)f->privdata;
  WaitSema(g_sema_id_dev);
  if ( privdat->m_seek_cur >= privdat->m_seek_max )
  {
    SignalSema(g_sema_id_dev);
    return 0;
  }
  xsize2 = ( privdat->m_seek_max >= privdat->m_seek_cur + size ) ? size : ( privdat->m_seek_max - privdat->m_seek_cur);
  if ( privdat->m_seek_cur < 0 || privdat->m_seek_max < 0 )
    Kprintf(
      "s147file: CallBack_Read -> Param=0x%08x Seek=%d/%d Count=%d CountEnd=%d\n",
      privdat,
      privdat->m_seek_cur,
      privdat->m_seek_max,
      size,
      xsize2);
  if ( f->unit == 9 )
  {
    int special; // [sp+34h] [+34h]

    special = nand_mdev_read_special(f, ptr, size);
    SignalSema(g_sema_id_dev);
    return special;
  }
  xsector1 = do_nand_bytes2sector(privdat->m_partition_offset, privdat->m_seek_cur + xsize2);
  xsector2 = do_nand_bytes2sector_remainder(privdat->m_seek_cur + xsize2);
  for ( cursz = 0; cursz < xsize2; cursz += xsize3 )
  {
    int pageoffs; // [sp+38h] [+38h]

    pageoffs = do_nand_bytes2sector(privdat->m_partition_offset, privdat->m_seek_cur);
    xsize3 = (( pageoffs >= xsector1 ) ? xsector2 : 2048) - do_nand_bytes2sector_remainder(privdat->m_seek_cur);
    do_nand_sector_rw(((char *)ptr) + cursz, pageoffs, do_nand_bytes2sector_remainder(privdat->m_seek_cur), xsize3);
    privdat->m_seek_cur += xsize3;
  }
  SignalSema(g_sema_id_dev);
  return xsize2;
}

//----- (004008BC) --------------------------------------------------------
static int nand_mdev_op_write(iop_file_t *f, void *ptr, int size)
{
  WaitSema(g_sema_id_dev);
  if ( f->unit == 9 )
  {
    int retres; // [sp+14h] [+14h]

    retres = nand_mdev_write_special(f, ptr, size);
    SignalSema(g_sema_id_dev);
    return retres;
  }
  SignalSema(g_sema_id_dev);
  return size;
}

//----- (00400980) --------------------------------------------------------
static int nand_mdev_op_lseek(iop_file_t *f, int offset, int mode)
{
  nand_mdev_privdata_stru_ *privdat; // [sp+10h] [+10h]

  privdat = (nand_mdev_privdata_stru_ *)f->privdata;
  WaitSema(g_sema_id_dev);
  switch (mode)
  {
  case 0:
    privdat->m_seek_cur = offset;
    break;
  case 1:
    privdat->m_seek_cur += offset;
    break;
  case 2:
    privdat->m_seek_cur = privdat->m_seek_max + offset;
    break;
  default:
    SignalSema(g_sema_id_dev);
    return -22;
  }
  if ( privdat->m_seek_max < privdat->m_seek_cur )
  {
    Kprintf("s147nand.irx: Out of range (seek=%d, filesize=%d)\n", privdat->m_seek_cur, privdat->m_seek_max);
    privdat->m_seek_cur = privdat->m_seek_max;
    SignalSema(g_sema_id_dev);
    return -22;
  }
  SignalSema(g_sema_id_dev);
  return privdat->m_seek_cur;
}

//----- (00400B20) --------------------------------------------------------
int s147nand_4_dumpprintinfo(int part)
{
  const nand_dir_stru_ *hdrbuf; // [sp+14h] [+14h]
  int retres; // [sp+1Ch] [+1Ch]
  int nand_partition_offset; // [sp+20h] [+20h]
  int i; // [sp+28h] [+28h]
  int j; // [sp+2Ch] [+2Ch]
  int dircnt; // [sp+30h] [+30h]
  int filcnt; // [sp+34h] [+34h]
  int finished;
  char pathtmp[24]; // [sp+38h] [+38h] BYREF

  retres = -1;
  dircnt = 0;
  filcnt = 0;
  finished = 0;
  nand_partition_offset = get_nand_partition_offset(part);
  if ( nand_partition_offset < 0 )
    return -19;
  for ( i = 0; i < 64; i += 1 )
  {
    nand_direntry_stru_ *dirbuf; // [sp+10h] [+10h]

    s147nand_7_multi_read_dma(g_nand_sector_buffer, nand_partition_offset + i, 1);
    dirbuf = (nand_direntry_stru_ *)g_nand_sector_buffer;
    for ( j = 0; j < 64; j += 1 )
    {
      if ( (i << 6) - 1 + j == -1 )
      {
        hdrbuf = (nand_dir_stru_ *)g_nand_sector_buffer;
        if ( strncmp((const char *)g_nand_sector_buffer, "S147ROM", 8) )
        {
          Kprintf(" \"%s%d:\" ... No data\n", g_dev_name, part);
          Kprintf(" -----------------------------\n\n");
          return -19;
        }
        retres = hdrbuf->m_entrycnt;
        Kprintf(" \"%s%d:\"\n", g_dev_name, part);
        Kprintf(" -----------------------------\n");
      }
      else
      {
        if ( (i << 6) - 1 + j >= retres )
        {
          finished = 1;
          break;
        }
        strcpy(pathtmp, dirbuf[j].m_name);
        if ( dirbuf[j].m_type == 'D' )
        {
          strcat(pathtmp, "/");
          dircnt += 1;
        }
        else
        {
          filcnt += 1;
        }
        Kprintf(" %9d  %s\n", dirbuf[j].m_size, pathtmp);
      }
    }
    if ( finished )
      break;
  }
  Kprintf(" -----------------------------\n");
  Kprintf("   %d directories, %d files\n", dircnt, filcnt);
  Kprintf("\n");
  return retres;
}

//----- (00400E28) --------------------------------------------------------
static int do_nand_open_inner1(nand_mdev_privdata_stru_ *privdat, int part, const char *name)
{
  int nand_partition_offset; // [sp+10h] [+10h]

  nand_partition_offset = get_nand_partition_offset(part);
  if ( nand_partition_offset < 0 )
  {
    Kprintf("s147nand.irx: Error invalid unit number\n");
    return -19;
  }
  privdat->m_partition_offset = nand_partition_offset;
  return do_nand_open_inner2(privdat, name + (( *name == '/' ) ? 1 : 0));
}

//----- (00400EF8) --------------------------------------------------------
static int do_nand_open_inner2(nand_mdev_privdata_stru_ *privdat, const char *name)
{
  size_t i; // [sp+10h] [+10h]

  for ( i = 0; name[i] && name[i] != '/'; i += 1 );
  if ( name[i] == '/' )
  {
    int nand_direntry; // [sp+14h] [+14h]

    nand_direntry = do_get_nand_direntry(privdat, name, i, 'D');
    return ( nand_direntry >= 0 ) ? do_nand_open_inner2(privdat, &name[i + 1]) : nand_direntry;
  }
  return do_get_nand_direntry(privdat, name, i, 'F');
}

//----- (0040101C) --------------------------------------------------------
static u32 do_get_nand_direntry(nand_mdev_privdata_stru_ *privdat, const char *name, size_t idx, char typ)
{
  int lvtyp; // $v0
  nand_direntry_stru_ *dirbuf; // [sp+14h] [+14h]
  nand_dir_stru_ *p; // [sp+18h] [+18h]
  size_t size; // [sp+1Ch] [+1Ch]
  int hdrret; // [sp+24h] [+24h]
  int offscnt; // [sp+2Ch] [+2Ch]
  int i; // [sp+30h] [+30h]
  char name_trunc[24]; // [sp+38h] [+38h] BYREF

  hdrret = -1;
  size = ( idx > 16 ) ? 16 : idx;
  strncpy(name_trunc, name, size);
  name_trunc[size] = 0;
  for ( offscnt = 0; offscnt < 64; offscnt += 1 )
  {
    s147nand_7_multi_read_dma(g_nand_sector_buffer, privdat->m_partition_offset + offscnt, 1);
    dirbuf = (nand_direntry_stru_ *)g_nand_sector_buffer;
    for ( i = 0; i < 64; i += 1 )
    {
      if ( (offscnt << 6) - 1 + i == -1 )
      {
        p = (nand_dir_stru_ *)g_nand_sector_buffer;
        if ( strncmp((const char *)g_nand_sector_buffer, "S147ROM", 8) )
        {
          Kprintf("s147nand.irx: No directory entries\n");
          return -19;
        }
        if ( p->m_ver >= 0x101u )
        {
          Kprintf("s147nand.irx: Version 0x%04x format is not supported\n", p->m_ver);
          return -19;
        }
        hdrret = p->m_entrycnt;
      }
      else
      {
        if ( (offscnt << 6) - 1 + i >= hdrret )
          return -2;
        lvtyp = (char)dirbuf[i].m_type;
        if ( (((lvtyp == 'D') && typ == 'D') || ((lvtyp == 'F' || lvtyp == '\x00') && typ == 'F')) && (!strcmp(dirbuf[i].m_name, name_trunc)) )
        {
          privdat->m_seek_max = dirbuf[i].m_size;
          privdat->m_partition_offset += dirbuf[i].m_offset;
          return dirbuf[i].m_size;
        }
      }
    }
  }
  return -2;
}
// 40101C: using guessed type char name_trunc[24];

//----- (004013E8) --------------------------------------------------------
static int do_nand_bytes2sector(int pageoffs, int byteoffs)
{
  return pageoffs + byteoffs / 2048;
}

//----- (0040142C) --------------------------------------------------------
static int do_nand_bytes2sector_remainder(int byteoffs)
{
  return byteoffs % 2048;
}

//----- (00401480) --------------------------------------------------------
int s147nand_5_outerinit(void)
{
  int initres; // [sp+10h] [+10h]

  initres = s147nand_15_nandinit();
  if ( initres )
  {
    Kprintf("s147nand.irx: NAND initialize failed (%d)\n", initres);
    return -1;
  }
  g_seama_param_1.initial = 1;
  g_seama_param_1.max = 1;
  g_seama_param_1.attr = 1;
  g_sema_id_init = CreateSema(&g_seama_param_1);
  if ( g_sema_id_init < 0 )
  {
    Kprintf("s147nand.irx: CreateSema error (%d)\n", g_sema_id_init);
    return -1;
  }
  s147nand_6_checkformat();
  return 0;
}

//----- (00401558) --------------------------------------------------------
void s147nand_6_checkformat(void)
{
  int state; // [sp+10h] [+10h] BYREF
  nand_info_stru_ *nandinf; // [sp+14h] [+14h]

  nandinf = s147nand_16_getnandinfo();
  s147nand_20_nand_read_dma(&g_nand_header, 0, 0, 160);
  if ( strncmp(g_nand_header.m_hdr, "S147NAND", 9) )
  {
    Kprintf("s147nand.irx: Unformatted device\n");
    Kprintf("\n");
    return;
  }
  Kprintf(
    "s147nand.irx: BootSector format version = %d.%d\n",
    g_nand_header.m_bootsector_ver_1,
    g_nand_header.m_bootsector_ver_2);
  if ( (u32)g_nand_header.m_bootsector_ver_1 < 2u )
  {
    Kprintf("s147nand.irx: Old version format, 256MB-NAND only\n", g_nand_header.m_nand_desc);
  }
  else
  {
    Kprintf("s147nand.irx: %-.32s\n", (const char *)g_nand_header.m_nand_desc);
    CpuSuspendIntr(&state);
    nandinf->m_page_size_noecc = g_nand_header.m_page_size_noecc;
    nandinf->m_page_size_withecc = g_nand_header.m_page_size_withecc;
    nandinf->m_pages_per_block = g_nand_header.m_pages_per_block;
    nandinf->m_block_size = g_nand_header.m_block_size;
    nandinf->m_page_count = g_nand_header.m_block_size * g_nand_header.m_pages_per_block;
    CpuResumeIntr(state);
  }
  Kprintf(
    "s147nand.irx: PageSize    = %d + %d (Bytes)\n",
    nandinf->m_page_size_noecc,
    nandinf->m_page_size_withecc - nandinf->m_page_size_noecc);
  Kprintf("s147nand.irx: Pages/Block = %d (Pages)\n", nandinf->m_pages_per_block);
  Kprintf("s147nand.irx: BlockSize   = %d (Blocks)\n", nandinf->m_block_size);
  Kprintf("s147nand.irx: PageSize    = %d (Pages)\n", nandinf->m_page_count);
  Kprintf("\n");
}
// 405258: using guessed type nand_header_stru_ g_nand_header;

//----- (00401768) --------------------------------------------------------
static void do_update_acdelay(void)
{
  int state; // [sp+18h] [+18h] BYREF

  Kprintf("s147nand.irx: Update Acdelay\n", g_nand_header.m_bootsector_ver_1, g_nand_header.m_bootsector_ver_2);
  DelayThread(10000);
  if ( (u32)g_nand_header.m_bootsector_ver_1 < 2u )
  {
    Kprintf("s147nand.irx: Old version format, no update\n");
    DelayThread(10000);
    return;
  }
  if ( !g_nand_header.m_acmem_delay_val || (int)g_nand_header.m_acmem_delay_val == -1 )
  {
    Kprintf("s147nand.irx: AcMem = 0x%08x (Default)\n", g_nand_header.m_acmem_delay_val);
  }
  else
  {
    CpuSuspendIntr(&state);
    SetAcMemDelayReg(g_nand_header.m_acmem_delay_val);
    CpuResumeIntr(state);
    Kprintf(
      "s147nand.irx: AcMem = 0x%08x (DMA=%d, Read=%d, Write=%d)\n",
      g_nand_header.m_acmem_delay_val,
      ((g_nand_header.m_acmem_delay_val & 0xF000000) >> 24) + 1,
      ((u8)(g_nand_header.m_acmem_delay_val & 0xF0) >> 4) + 1,
      (g_nand_header.m_acmem_delay_val & 0xF) + 1);
  }
  DelayThread(10000);
  if ( !g_nand_header.m_acio_delay_val || (int)g_nand_header.m_acio_delay_val == -1 )
  {
    Kprintf("s147nand.irx: AcIo  = 0x%08x (Default)\n", g_nand_header.m_acio_delay_val);
  }
  else
  {
    CpuSuspendIntr(&state);
    SetAcIoDelayReg(g_nand_header.m_acio_delay_val);
    CpuResumeIntr(state);
    Kprintf(
      "s147nand.irx: AcIo  = 0x%08x (DMA=%d, Read=%d, Write=%d)\n",
      g_nand_header.m_acio_delay_val,
      ((g_nand_header.m_acio_delay_val & 0xF000000) >> 24) + 1,
      ((u8)(g_nand_header.m_acio_delay_val & 0xF0) >> 4) + 1,
      (g_nand_header.m_acio_delay_val & 0xF) + 1);
  }
  DelayThread(10000);
  Kprintf("\n");
  DelayThread(10000);
}
// 405258: using guessed type nand_header_stru_ g_nand_header;

//----- (004019C4) --------------------------------------------------------
static int do_nand_sector_rw(void *ptr, int pageoffs, int byteoffs, size_t size)
{
  int dma; // [sp+10h] [+10h]

  WaitSema(g_sema_id_init);
  if ( ((uiptr)ptr & 3) != 0 || (byteoffs & 3) != 0 || (size & 3) != 0 )
  {
    dma = s147nand_20_nand_read_dma(g_nand_unaligned_buf, s147nand_14_translate_pageoffs(pageoffs), 0, s147nand_16_getnandinfo()->m_page_size_noecc);
    memcpy(ptr, (char *)g_nand_unaligned_buf + byteoffs, size);
  }
  else
  {
    dma = s147nand_20_nand_read_dma(ptr, s147nand_14_translate_pageoffs(pageoffs), byteoffs, size);
  }
  SignalSema(g_sema_id_init);
  return dma;
}

//----- (00401AF4) --------------------------------------------------------
int s147nand_7_multi_read_dma(void *ptr, int pageoffs, int pagecnt)
{
  int i; // [sp+14h] [+14h]
  int retres; // [sp+18h] [+18h]

  // Unofficial: initialize retres
  retres = 0;
  WaitSema(g_sema_id_init);
  for ( i = 0; i < pagecnt; i += 1 )
  {
    retres = s147nand_20_nand_read_dma((char *)ptr + 4 * (s147nand_16_getnandinfo()->m_page_size_noecc >> 2) * i, s147nand_14_translate_pageoffs(pageoffs + i), 0, s147nand_16_getnandinfo()->m_page_size_noecc);
    if ( retres )
      return retres;
  }
  SignalSema(g_sema_id_init);
  return retres;
}
// 401C18: variable 'retres' is possibly undefined

//----- (00401C38) --------------------------------------------------------
int s147nand_8_multi_write_dma(void *ptr, int pageoffs, int pagecnt)
{
  int i; // [sp+14h] [+14h]
  int retres; // [sp+18h] [+18h]

  // Unofficial: initialize retres
  retres = 0;
  for ( i = 0; i < pagecnt; i += 1 )
  {
    retres = s147nand_22_nand_write_dma((char *)ptr + 4 * (s147nand_16_getnandinfo()->m_page_size_noecc >> 2) * i, s147nand_14_translate_pageoffs(pageoffs + i), 0, s147nand_16_getnandinfo()->m_page_size_noecc);
    if ( retres )
      return retres;
  }
  return retres;
}
// 401D3C: variable 'retres' is possibly undefined

//----- (00401D5C) --------------------------------------------------------
int s147nand_9_get_nand_partition(int part)
{
  if ( part == 8 )
    return g_nand_header.m_nand_partition_8;
  if ( part >= 0 && part < 8 )
    return g_nand_header.m_nand_partition_info[2 * part];
  return 0;
}
// 405258: using guessed type nand_header_stru_ g_nand_header;

//----- (00401E14) --------------------------------------------------------
static int get_nand_partition_offset(int part)
{
  return s147nand_9_get_nand_partition(part) * g_nand_header.m_pages_per_block;
}
// 405258: using guessed type nand_header_stru_ g_nand_header;

//----- (00401E70) --------------------------------------------------------
int s147nand_10_get_nand_partition_size(int part)
{
  if ( part == 8 )
    return g_nand_header.m_nand_partition_8_size;
  if ( part >= 0 && part < 8 )
    return g_nand_header.m_nand_partition_info[(2 * part) + 1];
  return 0;
}
// 405258: using guessed type nand_header_stru_ g_nand_header;

//----- (00401F28) --------------------------------------------------------
static int nand_mdev_open_special(iop_file_t *f, const char *name)
{
  nand_mdev_privdata_stru_ *privdat; // [sp+10h] [+10h]
  int state; // [sp+14h] [+14h] BYREF

  CpuSuspendIntr(&state);
  f->privdata = AllocSysMemory(0, 16, 0);
  CpuResumeIntr(state);
  if ( !f->privdata )
  {
    Kprintf("s147nand.irx: AllocSysMemory failed (9:Open)\n");
    // Unofficial: return early on error
    return -2;
  }
  privdat = (nand_mdev_privdata_stru_ *)f->privdata;
  memset(privdat, 0, sizeof(nand_mdev_privdata_stru_));
  privdat->m_seek_cur = 0;
  if ( !strcmp(name, "watchdog-enable") )
  {
    s147nand_18_enable_nand_watchdog();
    privdat->m_flags = 0;
    privdat->m_seek_max = 0;
    privdat->m_partition_offset = 0;
    privdat->m_seek_cur = 0;
    Kprintf("s147nand.irx: WatchDogTimer Enable\n");
    DelayThread(10000);
  }
  else if ( !strcmp(name, "acdelay") )
  {
    do_update_acdelay();
    privdat->m_flags = 0;
    privdat->m_seek_max = 0;
    privdat->m_partition_offset = 0;
    privdat->m_seek_cur = 0;
  }
  else if ( !strcmp(name, "seccode") )
  {
    privdat->m_flags = 0x10000;
    privdat->m_seek_max = 2;
    privdat->m_partition_offset = 0;
    privdat->m_seek_cur = 0;
  }
  else if ( !strcmp(name, "videomode") )
  {
    privdat->m_flags = 0x40000;
    privdat->m_seek_max = 4;
    privdat->m_partition_offset = 0;
    privdat->m_seek_cur = 0;
  }
  else if ( !strcmp(name, "info") )
  {
    privdat->m_flags = 0x100000;
    privdat->m_seek_max = 2048;
    privdat->m_partition_offset = (s147nand_9_get_nand_partition(8) - 1) * g_nand_header.m_pages_per_block;
    privdat->m_seek_cur = 0;
  }
  else if ( !strcmp(name, "romwrite-tmp") )
  {
    privdat->m_flags = 0x3000000;
    privdat->m_seek_max = 0;
    privdat->m_partition_offset = s147nand_9_get_nand_partition(8) * g_nand_header.m_pages_per_block;
    privdat->m_seek_cur = 0;
  }
  else
  {
    CpuSuspendIntr(&state);
    FreeSysMemory(f->privdata);
    CpuResumeIntr(state);
    return -2;
  }
  return 0;
}
// 405258: using guessed type nand_header_stru_ g_nand_header;

//----- (00402260) --------------------------------------------------------
static size_t nand_mdev_read_special(iop_file_t *f, void *ptr, size_t size)
{
  nand_mdev_privdata_stru_ *privdata; // [sp+10h] [+10h]
  int retres1; // [sp+14h] [+14h]

  privdata = (nand_mdev_privdata_stru_ *)f->privdata;
  if ( (privdata->m_flags & 0x10000) != 0 )
    return do_nand_copy_seccode_from_buf(f, ptr, size);
  if ( (privdata->m_flags & 0x40000) != 0 )
    return do_nand_copy_videomode_from_buf(f, ptr, size);
  if ( (privdata->m_flags & 0x100000) != 0 )
  {
    retres1 = do_nand_sector_rw(ptr, privdata->m_partition_offset, privdata->m_seek_cur, size);
    if ( retres1 < 0 )
      return retres1;
    privdata->m_seek_cur += size;
    return size;
  }
  if ( (privdata->m_flags & 0x1000000) != 0 )
  {
    retres1 = do_nand_sector_rw(ptr, privdata->m_partition_offset, privdata->m_seek_cur, size);
    if ( retres1 < 0 )
      return retres1;
    privdata->m_seek_cur += size;
    return size;
  }
  return -2;
}

//----- (0040246C) --------------------------------------------------------
static int nand_mdev_write_special(iop_file_t *f, void *ptr, int size)
{
  nand_mdev_privdata_stru_ *privdata; // [sp+10h] [+10h]
  int retres1; // [sp+14h] [+14h]
  int xsz; // [sp+18h] [+18h]

  privdata = (nand_mdev_privdata_stru_ *)f->privdata;
  xsz = g_nand_header.m_nand_partition_8_size * g_nand_header.m_pages_per_block * g_nand_header.m_page_size_noecc;
  if ( (privdata->m_flags & 0x1000000) == 0 )
    return -22;
  if ( xsz < privdata->m_seek_cur + size )
  {
    Kprintf("s147nand.irx: Out of rewritable partition, lseek(%d) > max(%d)\n", privdata->m_seek_cur + size, xsz);
    return -27;
  }
  if ( (privdata->m_flags & 0x2000000) != 0 )
  {
    int i; // [sp+1Ch] [+1Ch]

    retres1 = 0;
    for ( i = 0; i < g_nand_header.m_nand_partition_8_size; i += 1 )
      retres1 = s147nand_11_erasetranslatepageoffs(s147nand_27_blocks2pages(i + g_nand_header.m_nand_partition_8));
    privdata->m_flags &= ~0x2000000u;
    if ( retres1 )
      return retres1;
  }
  if ( !g_nand_header.m_page_size_noecc )
    _break(7u, 0);
  if ( g_nand_header.m_page_size_noecc == -1 && privdata->m_seek_cur == (int)0x80000000 )
    _break(6u, 0);
  if ( !g_nand_header.m_page_size_noecc )
    _break(7u, 0);
  if ( g_nand_header.m_page_size_noecc == -1 && size == (int)0x80000000 )
    _break(6u, 0);
  retres1 = s147nand_8_multi_write_dma(
              ptr,
              privdata->m_seek_cur / g_nand_header.m_page_size_noecc + privdata->m_partition_offset,
              size / g_nand_header.m_page_size_noecc);
  if ( retres1 < 0 )
    return retres1;
  privdata->m_seek_cur += size;
  privdata->m_seek_max = privdata->m_seek_cur;
  return size;
}
// 40260C: variable 'retres1' is possibly undefined
// 405258: using guessed type nand_header_stru_ g_nand_header;

//----- (0040274C) --------------------------------------------------------
static size_t do_nand_copy_seccode_from_buf(iop_file_t *f, void *ptr, size_t size)
{
  nand_mdev_privdata_stru_ *privdata; // [sp+10h] [+10h]
  size_t xsize; // [sp+14h] [+14h]

  privdata = (nand_mdev_privdata_stru_ *)f->privdata;
  if ( privdata->m_seek_cur >= privdata->m_seek_max )
    return 0;
  xsize = ( privdata->m_seek_max >= (int)(privdata->m_seek_cur + size) ) ? size : (size_t)(privdata->m_seek_max - privdata->m_seek_cur);
  memcpy(ptr, &g_nand_header.m_nand_seccode[privdata->m_seek_cur], xsize);
  privdata->m_seek_cur += xsize;
  return xsize;
}
// 405258: using guessed type nand_header_stru_ g_nand_header;

//----- (0040287C) --------------------------------------------------------
static size_t do_nand_copy_videomode_from_buf(iop_file_t *f, void *ptr, size_t size)
{
  nand_mdev_privdata_stru_ *privdata; // [sp+10h] [+10h]
  size_t xsize; // [sp+14h] [+14h]

  privdata = (nand_mdev_privdata_stru_ *)f->privdata;
  if ( privdata->m_seek_cur >= privdata->m_seek_max )
    return 0;
  xsize = ( privdata->m_seek_max >= (int)(privdata->m_seek_cur + size) ) ? size : (size_t)(privdata->m_seek_max - privdata->m_seek_cur);
  memcpy(ptr, &g_nand_header.m_nand_vidmode[privdata->m_seek_cur], xsize);
  privdata->m_seek_cur += xsize;
  return xsize;
}
// 405258: using guessed type nand_header_stru_ g_nand_header;

//----- (004029AC) --------------------------------------------------------
int s147nand_11_erasetranslatepageoffs(int pageoffs)
{
  return s147nand_24_eraseoffset(s147nand_14_translate_pageoffs(pageoffs));
}

//----- (004029FC) --------------------------------------------------------
int s147nand_12_load_logaddrtable(void)
{
  nand_header_stru_ hdr; // [sp+10h] [+10h] BYREF
  int state; // [sp+B0h] [+B0h] BYREF

  s147nand_20_nand_read_dma(&hdr, 0, 0, 160);
  if ( strncmp(hdr.m_hdr, "S147NAND", 9) )
  {
    Kprintf("s147nand.irx: Unformatted device error.\n");
    return -19;
  }
  CpuSuspendIntr(&state);
  g_logical_addr_tbl = (u16 *)AllocSysMemory(0, 2 * hdr.m_block_size, 0);
  CpuResumeIntr(state);
  s147nand_19_logaddr_read(g_logical_addr_tbl, 1, 2 * hdr.m_block_size);
  CpuSuspendIntr(&state);
  g_nand_unaligned_buf = AllocSysMemory(0, s147nand_16_getnandinfo()->m_page_size_noecc, 0);
  CpuResumeIntr(state);
  if ( !g_nand_unaligned_buf )
  {
    Kprintf("s147nand.irx: AllocSysMemory failed (LogAddrTable)\n");
    return -1;
  }
  g_nand_unaligned_buf_alloced = 1;
  return 0;
}
// 4051C4: using guessed type int g_nand_unaligned_buf_alloced;

//----- (00402B44) --------------------------------------------------------
int s147nand_13_translate_blockoffs(int blockoffs)
{
  int tbladdr; // [sp+10h] [+10h]

  if ( blockoffs <= 0 || blockoffs >= s147nand_16_getnandinfo()->m_block_size )
  {
    Kprintf("s147nand.irx: Invalid logical block address %d\n", blockoffs);
    return -1470010;
  }
  if ( !g_nand_unaligned_buf_alloced )
  {
    int logaddrtable; // [sp+14h] [+14h]

    logaddrtable = s147nand_12_load_logaddrtable();
    if ( logaddrtable < 0 )
      return logaddrtable;
  }
  tbladdr = g_logical_addr_tbl[blockoffs];
  switch ( tbladdr )
  {
    case 0xAAAA:
      return blockoffs;
    case 0xCCCC:
    case 0xEEEE:
      return -1470010;
    default:
      return tbladdr;
  }
}
// 4051C4: using guessed type int g_nand_unaligned_buf_alloced;

//----- (00402CB8) --------------------------------------------------------
int s147nand_14_translate_pageoffs(int pageoffs)
{
  int tblockoffs; // [sp+10h] [+10h]

  tblockoffs = s147nand_13_translate_blockoffs(s147nand_28_pages2blocks(pageoffs));
  if ( tblockoffs == -1470010 )
    return -1470010;
  if ( !g_nand_header.m_pages_per_block )
    _break(7u, 0);
  if ( g_nand_header.m_pages_per_block == -1 && pageoffs == (int)0x80000000 )
    _break(6u, 0);
  return s147nand_27_blocks2pages(tblockoffs) + (pageoffs % g_nand_header.m_pages_per_block);
}
// 405258: using guessed type nand_header_stru_ g_nand_header;

//----- (00402D80) --------------------------------------------------------
static int dev9_intr_handler(void *unusd)
{
  (void)unusd;

  iWakeupThread(g_thid);
  return 1;
}

//----- (00402DC0) --------------------------------------------------------
int s147nand_15_nandinit(void)
{
  int intrstate; // [sp+10h] [+10h] BYREF

  DisableIntr(41, &intrstate);
  ReleaseIntrHandler(41);
  RegisterIntrHandler(41, 1, dev9_intr_handler, &g_probunusd_dword_4051D0);
  EnableIntr(41);
  dmac_disable(8u);
  dmac_ch_set_dpcr(8u, 7u);
  dmac_enable(8u);
  iop_mmio_hwport_lo.ssbus2.ind_B_address = 0xB4000008;
  g_sema_param.initial = 1;
  g_sema_param.max = 1;
  g_sema_param.attr = 1;
  g_sema_id_nand = CreateSema(&g_sema_param);
  if ( g_sema_id_nand >= 0 )
    return 0;
  printf("nand_Init: CreateSema error (%d)\n", g_sema_id_nand);
  return -1;
}
// 4051D0: using guessed type int g_probunusd_dword_4051D0;
// 1F800000: using guessed type iop_mmio_hwport_t iop_mmio_hwport_lo;

//----- (00402EC0) --------------------------------------------------------
nand_info_stru_ *s147nand_16_getnandinfo(void)
{
  return &g_nand_info;
}
// 4051D8: using guessed type nand_info_stru_ g_nand_info;

//----- (00402EE8) --------------------------------------------------------
int s147nand_17_get_sema(void)
{
  return g_sema_id_nand;
}

//----- (00402F5C) --------------------------------------------------------
void s147nand_18_enable_nand_watchdog(void)
{
  g_nand_watchdog_enabled = 1;
}
// 4051D4: using guessed type int g_nand_watchdog_enabled;

//----- (00402F84) --------------------------------------------------------
int s147nand_19_logaddr_read(u16 *tbl, int pageoffs, int bytecnt)
{
  int i; // [sp+10h] [+10h]
  int pagecnt; // [sp+18h] [+18h]

  pagecnt = s147nand_30_bytes2pagesnoeccround(bytecnt);
  for ( i = 0; i < pagecnt; i += 1 )
  {
    int retres; // [sp+14h] [+14h]

    retres = s147nand_20_nand_read_dma(
               &tbl[2 * (g_nand_info.m_page_size_noecc >> 2) * i],
               pageoffs + i,
               0,
               g_nand_info.m_page_size_noecc);
    if ( retres )
      return retres;
  }
  return 0;
}
// 4051D8: using guessed type nand_info_stru_ g_nand_info;

//----- (00403084) --------------------------------------------------------
int s147nand_20_nand_read_dma(void *ptr, int pageoffs, int byteoffs, int bytecnt)
{
  int retres; // [sp+10h] [+10h]

  WaitSema(g_sema_id_nand);
  retres = nand_lowlevel_read_dma(ptr, pageoffs, byteoffs, bytecnt);
  SignalSema(g_sema_id_nand);
  return retres;
}

//----- (00403104) --------------------------------------------------------
int s147nand_21_nand_read_pio(void *ptr, int pageoffs, int byteoffs, int bytecnt)
{
  int retres; // [sp+10h] [+10h]
  int state; // [sp+14h] [+14h] BYREF

  WaitSema(g_sema_id_nand);
  CpuSuspendIntr(&state);
  retres = nand_lowlevel_read_pio(ptr, pageoffs, byteoffs, bytecnt);
  CpuResumeIntr(state);
  SignalSema(g_sema_id_nand);
  return retres;
}

//----- (0040319C) --------------------------------------------------------
int s147nand_22_nand_write_dma(void *ptr, int pageoffs, int byteoffs, int bytecnt)
{
  int retres; // [sp+10h] [+10h]

  WaitSema(g_sema_id_nand);
  retres = nand_lowlevel_write_dma(ptr, pageoffs, byteoffs, bytecnt);
  SignalSema(g_sema_id_nand);
  return retres;
}

//----- (0040321C) --------------------------------------------------------
int s147nand_23_nand_write_pio(void *ptr, int pageoffs, int byteoffs, int bytecnt)
{
  int retres; // [sp+10h] [+10h]
  int state; // [sp+14h] [+14h] BYREF

  WaitSema(g_sema_id_nand);
  CpuSuspendIntr(&state);
  retres = nand_lowlevel_write_pio(ptr, pageoffs, byteoffs, bytecnt);
  CpuResumeIntr(state);
  SignalSema(g_sema_id_nand);
  return retres;
}

//----- (004032B4) --------------------------------------------------------
int s147nand_24_eraseoffset(int pageoffs)
{
  int retres; // [sp+10h] [+10h]
  int state; // [sp+14h] [+14h] BYREF
  char v8[8]; // [sp+18h] [+18h] BYREF

  s147nand_21_nand_read_pio(v8, s147nand_27_blocks2pages(s147nand_28_pages2blocks(pageoffs)), g_nand_info.m_page_size_noecc, 1);
  s147nand_21_nand_read_pio(&v8[1], s147nand_27_blocks2pages(s147nand_28_pages2blocks(pageoffs)) + 1, g_nand_info.m_page_size_noecc, 1);
  if ( (u8)v8[0] != 255 || (u8)v8[1] != 255 )
    return -1470020;
  WaitSema(g_sema_id_nand);
  CpuSuspendIntr(&state);
  retres = nand_lowlevel_blockerase(pageoffs);
  CpuResumeIntr(state);
  SignalSema(g_sema_id_nand);
  return retres;
}
// 4051D8: using guessed type nand_info_stru_ g_nand_info;

//----- (004033D4) --------------------------------------------------------
int s147nand_25_nand_blockerase(int pageoffs)
{
  int retres; // [sp+10h] [+10h]
  int state; // [sp+14h] [+14h] BYREF

  WaitSema(g_sema_id_nand);
  CpuSuspendIntr(&state);
  retres = nand_lowlevel_blockerase(pageoffs);
  CpuResumeIntr(state);
  SignalSema(g_sema_id_nand);
  return retres;
}

//----- (00403454) --------------------------------------------------------
int s147nand_26_nand_readid(void *ptr)
{
  int retres; // [sp+10h] [+10h]
  int state; // [sp+14h] [+14h] BYREF

  WaitSema(g_sema_id_nand);
  CpuSuspendIntr(&state);
  retres = nand_lowlevel_readid(ptr);
  CpuResumeIntr(state);
  SignalSema(g_sema_id_nand);
  return retres;
}

//----- (004034D4) --------------------------------------------------------
static int nand_lowlevel_read_dma(void *ptr, int pageoffs, int byteoffs, int bytecnt)
{
  int state; // [sp+18h] [+18h] BYREF

  if ( pageoffs < 0 || pageoffs >= g_nand_info.m_page_count )
    return -1470010;
  if ( byteoffs < 0 || byteoffs >= g_nand_info.m_page_size_withecc )
    return -1470010;
  if ( bytecnt < 4 || g_nand_info.m_page_size_withecc < byteoffs + bytecnt )
    return -1470010;
  CpuSuspendIntr(&state);
  s147nand_dev9_io_mmio.m_nand_cmd_enable = 1;
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (u16)(byteoffs);
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (u16)(byteoffs & 0xF00) >> 8;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = pageoffs;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (u16)(pageoffs & 0xFF00) >> 8;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (pageoffs & 0xFF0000u) >> 16;
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0x30;
  CpuResumeIntr(state);
  while ( (s147nand_dev9_io_mmio.m_nand_waitflag & 1) != 0 );
  CpuSuspendIntr(&state);
  s147_dev9_mem_mmio.m_security_unlock_unlock = 0;
  dmac_request(8u, ptr, bytecnt >> 2, 1u, 0);
  g_thid = GetThreadId();
  CpuResumeIntr(state);
  dmac_transfer(8u);
  SleepThread();
  s147nand_dev9_io_mmio.m_nand_cmd_enable = 0;
  if ( g_nand_watchdog_enabled == 1 )
    s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
  return 0;
}
// 4051D4: using guessed type int g_nand_watchdog_enabled;
// 4051D8: using guessed type nand_info_stru_ g_nand_info;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;
// B4000000: using guessed type s147nand_dev9_io_mmio_ s147nand_dev9_io_mmio;

//----- (00403748) --------------------------------------------------------
static int nand_lowlevel_read_pio(void *ptr, int pageoffs, int byteoffs, int bytecnt)
{
  int i; // [sp+0h] [+0h]

  if ( pageoffs < 0 || pageoffs >= g_nand_info.m_page_count )
    return -1470010;
  if ( byteoffs < 0 || byteoffs >= g_nand_info.m_page_size_withecc )
    return -1470010;
  if ( bytecnt <= 0 || g_nand_info.m_page_size_withecc < byteoffs + bytecnt )
    return -1470010;
  while ( (s147nand_dev9_io_mmio.m_nand_waitflag & 1) != 0 );
  s147nand_dev9_io_mmio.m_nand_cmd_enable = 1;
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = byteoffs;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (u16)(byteoffs & 0xF00) >> 8;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = pageoffs;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (u16)(pageoffs & 0xFF00) >> 8;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (pageoffs & 0xFF0000u) >> 16;
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0x30;
  while ( (s147nand_dev9_io_mmio.m_nand_waitflag & 1) != 0 );
  for ( i = 0; i < bytecnt; i += 1 )
    ((u8 *)ptr)[i] = s147nand_dev9_io_mmio.m_nand_outbyte;
  s147nand_dev9_io_mmio.m_nand_cmd_enable = 0;
  if ( g_nand_watchdog_enabled == 1 )
    s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
  return 0;
}
// 4051D4: using guessed type int g_nand_watchdog_enabled;
// 4051D8: using guessed type nand_info_stru_ g_nand_info;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;
// B4000000: using guessed type s147nand_dev9_io_mmio_ s147nand_dev9_io_mmio;

//----- (004039C4) --------------------------------------------------------
static int nand_lowlevel_write_dma(void *ptr, int pageoffs, int byteoffs, int bytecnt)
{
  int state; // [sp+18h] [+18h] BYREF
  u8 flgtmp; // [sp+20h] [+20h]

  if ( pageoffs < 0 || pageoffs >= g_nand_info.m_page_count )
    return -1470010;
  if ( byteoffs < 0 || byteoffs >= g_nand_info.m_page_size_withecc )
    return -1470010;
  if ( bytecnt < 4 || g_nand_info.m_page_size_withecc < byteoffs + bytecnt )
    return -1470010;
  CpuSuspendIntr(&state);
  s147nand_dev9_io_mmio.m_nand_write_cmd_unlock = 0xA5;
  s147nand_dev9_io_mmio.m_nand_cmd_enable = 1;
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0x80;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (u16)(byteoffs);
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (u16)(byteoffs & 0xF00) >> 8;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = pageoffs;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (u16)(pageoffs & 0xFF00) >> 8;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (pageoffs & 0xFF0000u) >> 16;
  s147_dev9_mem_mmio.m_security_unlock_unlock = 0;
  dmac_request(8u, ptr, bytecnt >> 2, 1u, 1);
  g_thid = GetThreadId();
  CpuResumeIntr(state);
  dmac_transfer(8u);
  SleepThread();
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0x10;
  while ( (s147nand_dev9_io_mmio.m_nand_waitflag & 1) != 0 );
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0x70;
  flgtmp = s147nand_dev9_io_mmio.m_nand_outbyte;
  s147nand_dev9_io_mmio.m_nand_cmd_enable = 0;
  s147nand_dev9_io_mmio.m_nand_write_cmd_unlock = 0;
  if ( g_nand_watchdog_enabled == 1 )
    s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
  if ( (flgtmp & 0x80) == 0 )
    return -1470030;
  if ( (flgtmp & 1) != 0 )
    return -1470020;
  return 0;
}
// 4051D4: using guessed type int g_nand_watchdog_enabled;
// 4051D8: using guessed type nand_info_stru_ g_nand_info;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;
// B4000000: using guessed type s147nand_dev9_io_mmio_ s147nand_dev9_io_mmio;

//----- (00403CAC) --------------------------------------------------------
static int nand_lowlevel_write_pio(void *ptr, int pageoffs, int byteoffs, int bytecnt)
{
  u8 flgtmp; // $v0
  int i; // [sp+0h] [+0h]

  if ( pageoffs < 0 || pageoffs >= g_nand_info.m_page_count )
    return -1470010;
  if ( byteoffs < 0 || byteoffs >= g_nand_info.m_page_size_withecc )
    return -1470010;
  if ( bytecnt <= 0 || g_nand_info.m_page_size_withecc < byteoffs + bytecnt )
    return -1470010;
  s147nand_dev9_io_mmio.m_nand_write_cmd_unlock = 0xA5;
  s147nand_dev9_io_mmio.m_nand_cmd_enable = 1;
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0x80;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = byteoffs;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (u16)(byteoffs & 0xF00) >> 8;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = pageoffs;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (u16)(pageoffs & 0xFF00) >> 8;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (pageoffs & 0xFF0000u) >> 16;
  for ( i = 0; i < bytecnt; i += 1 )
    s147nand_dev9_io_mmio.m_nand_outbyte = ((u8 *)ptr)[i];
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0x10;
  while ( (s147nand_dev9_io_mmio.m_nand_waitflag & 1) != 0 );
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0x70;
  flgtmp = s147nand_dev9_io_mmio.m_nand_outbyte;
  s147nand_dev9_io_mmio.m_nand_cmd_enable = 0;
  s147nand_dev9_io_mmio.m_nand_write_cmd_unlock = 0;
  if ( g_nand_watchdog_enabled == 1 )
    s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
  if ( (flgtmp & 0x80) == 0 )
    return -1470030;
  if ( (flgtmp & 1) != 0 )
    return -1470020;
  return 0;
}
// 4051D4: using guessed type int g_nand_watchdog_enabled;
// 4051D8: using guessed type nand_info_stru_ g_nand_info;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;
// B4000000: using guessed type s147nand_dev9_io_mmio_ s147nand_dev9_io_mmio;

//----- (00403F74) --------------------------------------------------------
static int nand_lowlevel_blockerase(int pageoffs)
{
  u8 flgtmp; // $v0

  if ( pageoffs < 0 || pageoffs >= g_nand_info.m_page_count )
    return -1470010;
  s147nand_dev9_io_mmio.m_nand_write_cmd_unlock = 0xA5;
  s147nand_dev9_io_mmio.m_nand_cmd_enable = 1;
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0x60;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = pageoffs & 0xC0;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (u16)(pageoffs & 0xFF00) >> 8;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = (pageoffs & 0xFF0000u) >> 16;
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0xD0;
  while ( (s147nand_dev9_io_mmio.m_nand_waitflag & 1) != 0 );
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0x70;
  flgtmp = s147nand_dev9_io_mmio.m_nand_outbyte;
  s147nand_dev9_io_mmio.m_nand_cmd_enable = 0;
  s147nand_dev9_io_mmio.m_nand_write_cmd_unlock = 0;
  if ( g_nand_watchdog_enabled == 1 )
    s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
  if ( (flgtmp & 0x80) == 0 )
    return -1470030;
  if ( (flgtmp & 1) != 0 )
    return -1470020;
  return 0;
}
// 4051D4: using guessed type int g_nand_watchdog_enabled;
// 4051D8: using guessed type nand_info_stru_ g_nand_info;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;
// B4000000: using guessed type s147nand_dev9_io_mmio_ s147nand_dev9_io_mmio;

//----- (00404128) --------------------------------------------------------
static int nand_lowlevel_readid(void *ptr)
{
  int i; // [sp+0h] [+0h]

  if ( !ptr )
    return -1470010;
  s147nand_dev9_io_mmio.m_nand_cmd_enable = 1;
  s147nand_dev9_io_mmio.m_nand_cmd_sel = 0x90;
  s147nand_dev9_io_mmio.m_nand_cmd_offs = 0;
  for ( i = 0; i < 5; i += 1 )
    ((u8 *)ptr)[i] = s147nand_dev9_io_mmio.m_nand_outbyte;
  s147nand_dev9_io_mmio.m_nand_cmd_enable = 0;
  if ( g_nand_watchdog_enabled == 1 )
    s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
  return 0;
}
// 4051D4: using guessed type int g_nand_watchdog_enabled;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;
// B4000000: using guessed type s147nand_dev9_io_mmio_ s147nand_dev9_io_mmio;

//----- (00404204) --------------------------------------------------------
int s147nand_27_blocks2pages(int blocks)
{
  return blocks * g_nand_info.m_pages_per_block;
}
// 4051D8: using guessed type nand_info_stru_ g_nand_info;

//----- (00404244) --------------------------------------------------------
int s147nand_28_pages2blocks(int pages)
{
  if ( !g_nand_info.m_pages_per_block )
    _break(7u, 0);
  if ( g_nand_info.m_pages_per_block == -1 && pages == (int)0x80000000 )
    _break(6u, 0);
  return pages / g_nand_info.m_pages_per_block;
}
// 4051D8: using guessed type nand_info_stru_ g_nand_info;

//----- (004042A0) --------------------------------------------------------
int s147nand_29_pages2blockround(int pages)
{
  int blocks; // [sp+0h] [+0h]

  if ( !g_nand_info.m_pages_per_block )
    _break(7u, 0);
  if ( g_nand_info.m_pages_per_block == -1 && pages == (int)0x80000000 )
    _break(6u, 0);
  if ( !g_nand_info.m_pages_per_block )
    _break(7u, 0);
  blocks = pages / g_nand_info.m_pages_per_block;
  if ( g_nand_info.m_pages_per_block == -1 && pages == (int)0x80000000 )
    _break(6u, 0);
  return blocks + (( pages % g_nand_info.m_pages_per_block ) ? 1 : 0);
}
// 4051D8: using guessed type nand_info_stru_ g_nand_info;

//----- (00404354) --------------------------------------------------------
int s147nand_30_bytes2pagesnoeccround(int bytes)
{
  int pages; // [sp+0h] [+0h]

  if ( !g_nand_info.m_page_size_noecc )
    _break(7u, 0);
  if ( g_nand_info.m_page_size_noecc == -1 && bytes == (int)0x80000000 )
    _break(6u, 0);
  if ( !g_nand_info.m_page_size_noecc )
    _break(7u, 0);
  pages = bytes / g_nand_info.m_page_size_noecc;
  if ( g_nand_info.m_page_size_noecc == -1 && bytes == (int)0x80000000 )
    _break(6u, 0);
  return pages + (( bytes % g_nand_info.m_page_size_noecc ) ? 1 : 0);
}
// 4051D8: using guessed type nand_info_stru_ g_nand_info;
