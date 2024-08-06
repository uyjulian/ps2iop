
#include <accdvd.h>
#include <irx_imports.h>

#define MODNAME "CD/DVD_Compatible"
IRX_ID(MODNAME, 1, 1);
// Text section hash:
// 0530902ecc03cd3839dfd4b9d9367440
// Known titles:
// NM00005
// NM00006
// NM00008
// Path strings:
// /home/ueda/tmp/psalm-0.1.3/cdvd-iop-0.1.9/src/
// /home/ueda/tmp/psalm-0.1.3/core-hdr-0.1.3/src/util/
// TODO: diff with module text hash 3b63ef6314122a3f5bf1ae695def643b

extern struct irx_export_table _exp_accdvd;

typedef acUint32 acd_lsn_t;

struct acd;

typedef void (*acd_done_t)(struct acd *acd, void *arg, int ret);

struct acd
{
  acAtapiData c_atapi;
  acd_done_t c_done;
  void *c_arg;
  acInt32 c_thid;
  acInt32 c_tmout;
};

typedef void (*cdc_done_t)(int eveid);

struct cdc_read_stru
{
  acUint8 *buf;
  acInt32 size;
  acInt32 bsize;
  acInt32 pos;
  acInt32 bank;
  acd_lsn_t lsn;
  cdc_xfer_t xfer;
  acInt16 spindle;
  acUint16 maxspeed;
};

struct cdc_stream_stru
{
  acUint8 *buf;
  acInt32 size;
  acInt32 bsize;
  acInt32 head;
  acInt32 tail;
  acd_lsn_t lsn;
  acUint32 reqlsn;
  acInt32 flag;
};

struct cdc_softc
{
  acInt32 lockid;
  acInt32 syncid;
  acInt32 error;
  acCdvdsifId fno;
  acUint8 *buf;
  cdc_done_t done;
  acUint32 cdsize;
  acUint16 tray;
  acUint16 stat;
  struct cdc_read_stru rd;
  struct cdc_stream_stru st;
  struct acd acd;
};

struct iso9660_desc
{
  // cppcheck-suppress unusedStructMember
  unsigned char type[1];
  // cppcheck-suppress unusedStructMember
  unsigned char id[5];
  // cppcheck-suppress unusedStructMember
  unsigned char version[1];
  // cppcheck-suppress unusedStructMember
  unsigned char unused1[1];
  // cppcheck-suppress unusedStructMember
  unsigned char system_id[32];
  // cppcheck-suppress unusedStructMember
  unsigned char volume_id[32];
  // cppcheck-suppress unusedStructMember
  unsigned char unused2[8];
  // cppcheck-suppress unusedStructMember
  unsigned char volume_space_size[8];
  // cppcheck-suppress unusedStructMember
  unsigned char unused3[32];
  // cppcheck-suppress unusedStructMember
  unsigned char volume_set_size[4];
  // cppcheck-suppress unusedStructMember
  unsigned char volume_sequence_number[4];
  // cppcheck-suppress unusedStructMember
  unsigned char logical_block_size[4];
  // cppcheck-suppress unusedStructMember
  unsigned char path_table_size[8];
  // cppcheck-suppress unusedStructMember
  unsigned char type_l_path_table[4];
  // cppcheck-suppress unusedStructMember
  unsigned char opt_type_l_path_table[4];
  // cppcheck-suppress unusedStructMember
  unsigned char type_m_path_table[4];
  // cppcheck-suppress unusedStructMember
  unsigned char opt_type_m_path_table[4];
  // cppcheck-suppress unusedStructMember
  unsigned char root_directory_record[34];
  // cppcheck-suppress unusedStructMember
  unsigned char volume_set_id[128];
  // cppcheck-suppress unusedStructMember
  unsigned char publisher_id[128];
  // cppcheck-suppress unusedStructMember
  unsigned char preparer_id[128];
  // cppcheck-suppress unusedStructMember
  unsigned char application_id[128];
  // cppcheck-suppress unusedStructMember
  unsigned char copyright_file_id[37];
  // cppcheck-suppress unusedStructMember
  unsigned char abstract_file_id[37];
  // cppcheck-suppress unusedStructMember
  unsigned char bibliographic_file_id[37];
  // cppcheck-suppress unusedStructMember
  unsigned char creation_date[17];
  // cppcheck-suppress unusedStructMember
  unsigned char modification_date[17];
  // cppcheck-suppress unusedStructMember
  unsigned char expiration_date[17];
  // cppcheck-suppress unusedStructMember
  unsigned char effective_date[17];
  // cppcheck-suppress unusedStructMember
  unsigned char file_structure_version[1];
  // cppcheck-suppress unusedStructMember
  unsigned char unused4[1];
  // cppcheck-suppress unusedStructMember
  unsigned char application_data[512];
  // cppcheck-suppress unusedStructMember
  unsigned char unused5[653];
};

struct iso9660_dirent
{
  unsigned char length[1];
  unsigned char ext_attr_length[1];
  unsigned char extent[8];
  unsigned char size[8];
  unsigned char date[7];
  unsigned char flags[1];
  unsigned char file_unit_size[1];
  unsigned char interleave[1];
  unsigned char volume_sequence_number[4];
  unsigned char name_len[1];
  unsigned char name[];
};

struct iso9660_path
{
  unsigned char name_len[2];
  unsigned char extent[4];
  unsigned char parent[2];
  unsigned char name[];
};

struct cdfs_ptable
{
  struct iso9660_path *path;
  acUint32 size;
};

struct cdfs_softc
{
  acInt32 semid;
  acUint32 all;
  struct cdfs_ptable *ptable;
  acInt32 ptnum;
  acUint32 rootlsn;
  acUint32 rootsize;
  acInt32 rootidx;
  struct iso9660_dirent *dcache;
  acUint32 dclsn;
  acUint32 dcsize;
  struct iso9660_path *pcache;
  acUint32 pcsize;
  // cppcheck-suppress unusedStructMember
  acInt32 padding[4];
  acUint8 buf[2048];
};

struct atapi_mode_h
{
  acUint8 h_len[2];
  acUint8 h_mtype;
  // cppcheck-suppress unusedStructMember
  acUint8 h_nblocks;
  // cppcheck-suppress unusedStructMember
  acUint8 h_padding[4];
};

struct atapi_mode
{
  // cppcheck-suppress unusedStructMember
  acUint8 d_pgcode;
  // cppcheck-suppress unusedStructMember
  acUint8 d_pglen;
};

struct atapi_mode_error
{
  struct atapi_mode_h me_h;
  // cppcheck-suppress unusedStructMember
  struct atapi_mode me_d;
  // cppcheck-suppress unusedStructMember
  acUint8 me_param;
  acUint8 me_rretry;
  // cppcheck-suppress unusedStructMember
  acUint8 me_unused1[4];
  // cppcheck-suppress unusedStructMember
  acUint8 me_wretry;
  // cppcheck-suppress unusedStructMember
  acUint8 me_unused2[3];
};

struct atapi_mode_drive
{
  struct atapi_mode_h md_h;
  // cppcheck-suppress unusedStructMember
  struct atapi_mode md_d;
  // cppcheck-suppress unusedStructMember
  acUint8 md_unused;
  acUint8 md_timer;
  // cppcheck-suppress unusedStructMember
  acUint8 md_spm[2];
  // cppcheck-suppress unusedStructMember
  acUint8 md_fps[2];
};

struct atapi_mode_capmach
{
  struct atapi_mode_h mc_h;
  // cppcheck-suppress unusedStructMember
  struct atapi_mode mc_d;
  // cppcheck-suppress unusedStructMember
  acUint8 mc_mer;
  // cppcheck-suppress unusedStructMember
  acUint8 mc_padding;
  // cppcheck-suppress unusedStructMember
  acUint8 mc_cap[4];
  acUint8 mc_maxspeed[2];
  // cppcheck-suppress unusedStructMember
  acUint8 mc_novl[2];
  // cppcheck-suppress unusedStructMember
  acUint8 mc_bufsize[2];
  acUint8 mc_speed[2];
  // cppcheck-suppress unusedStructMember
  acUint8 mc_padding2;
  // cppcheck-suppress unusedStructMember
  acUint8 mc_flags2;
  // cppcheck-suppress unusedStructMember
  acUint8 mc_padding3[2];
};

struct atapi_read_capacity
{
  acUint8 lba[4];
  // cppcheck-suppress unusedStructMember
  acUint8 blen[4];
};

struct acd_softc
{
  acInt32 active;
  acUint32 status;
  acUint32 drive;
  acCdvdsifId dma;
  acCdvdsifId medium;
  acInt32 sense;
  acUint32 dmamap;
  acUint32 padding;
  struct atapi_mode_drive timer;
  struct atapi_mode_error retry;
  struct atapi_mode_capmach speed;
};

struct cdfs_time
{
  acUint8 t_padding;
  acUint8 t_sec;
  acUint8 t_min;
  acUint8 t_hour;
  acUint8 t_day;
  acUint8 t_mon;
  acUint16 t_year;
};

struct cdfs_dirent
{
  acUint32 d_lsn;
  acUint32 d_size;
  acUint32 d_vol;
  // cppcheck-suppress unusedStructMember
  acUint32 d_padding;
  acUint8 d_ftype;
  acUint8 d_namlen;
  char d_name[14];
  struct cdfs_time d_time;
};

struct cdfs_file
{
  acUint32 f_lsn;
  acUint32 f_pos;
  acUint32 f_size;
  acUint32 f_padding;
};

struct cdvd_modules
{
  int (*cm_restart)(int argc, char **argv);
  int (*cm_start)(int argc, char **argv);
  int (*cm_status)();
  int (*cm_stop)();
};

struct cdc_module
{
  int (*start)(int argc, char **argv);
  int (*stop)();
  int (*status)();
};

struct acd_ata
{
  acAtaData a_ata;
  acInt32 a_thid;
  acInt32 a_result;
  acUint32 a_padding[2];
};

struct cdi_softc
{
  // cppcheck-suppress unusedStructMember
  acInt32 error;
  cdc_done_t done;
  // cppcheck-suppress unusedStructMember
  acUint32 padding[2];
};

#define acCdvdEntry _start

struct acd *acd_setup(struct acd *acd, acd_done_t done, void *arg, int tmout);
int acd_module_status();
int acd_module_start(int argc, char **argv);
int acd_module_stop();
int acd_module_restart(int argc, char **argv);
static int cddrv_adddrv(iop_device_t *drv);
static int cddrv_deldrv(iop_device_t *drv);
static int cddrv_open(iop_file_t *io, const char *name, int flg);
static int cddrv_close(iop_file_t *io);
static int cddrv_read(iop_file_t *io, void *buf, int cnt);
static int cddrv_write(iop_file_t *io, void *buf, int cnt);
static int cddrv_lseek(iop_file_t *io, int offset, int whence);
static int cddrv_ioctl(iop_file_t *io, int cmd, void *arg);
static int cddrv_dummy();
int cddrv_module_start(int argc, char **argv);
int cddrv_module_stop();
int cddrv_module_restart(int argc, char **argv);
int cddrv_module_status();
int cdfs_umount();
int cdfs_recover(int ret);
int cdfs_lookup(struct cdfs_dirent *result, const char *path, int pathlen);
int cdfs_read(struct cdfs_file *file, void *buf, int size);
int cdfs_module_status();
int cdfs_module_start(int argc, char **argv);
int cdfs_module_stop();
int cdfs_module_restart(int argc, char **argv);

static struct cdvd_modules Cdvd_modules[4] =
{
  {
    &acd_module_restart,
    &acd_module_start,
    &acd_module_status,
    &acd_module_stop
  },
  {
    &cdfs_module_restart,
    &cdfs_module_start,
    &cdfs_module_status,
    &cdfs_module_stop
  },
  {
    &cddrv_module_restart,
    &cddrv_module_start,
    &cddrv_module_status,
    &cddrv_module_stop
  },
  {
    &cdc_module_restart,
    &cdc_module_start,
    &cdc_module_status,
    &cdc_module_stop
  }
};
static struct cdc_module mods_120[3] =
{
  { &acAtaModuleStart, &acAtaModuleStop, &acAtaModuleStatus },
  { &acd_module_start, &acd_module_stop, &acd_module_status },
  { &cdfs_module_start, &cdfs_module_stop, &cdfs_module_status }
};
static char *argv_20[2] = {"sceCdInit", 0};
static iop_device_ops_t Cddrv_ops =
{
  &cddrv_adddrv,
  &cddrv_deldrv,
  &cddrv_dummy,
  &cddrv_open,
  &cddrv_close,
  &cddrv_read,
  &cddrv_write,
  &cddrv_lseek,
  &cddrv_ioctl,
  &cddrv_dummy,
  &cddrv_dummy,
  &cddrv_dummy,
  &cddrv_dummy,
  &cddrv_dummy,
  &cddrv_dummy,
  &cddrv_dummy,
  &cddrv_dummy
};

static iop_device_t Cddrv = { "cdrom", 16u, 0u, "ATAPI_C/DVD-ROM", &Cddrv_ops };
static struct acd_softc Acdc;
static struct cdc_softc Cdcc;
static struct cdi_softc Cdic;
static struct cdfs_softc Cdfsc;

// accdvdi-entry.o

int acCdvdModuleRestart(int argc, char **argv)
{
  int v2;
  int index;

  v2 = argc;
  for ( index = 0; (unsigned int)index < 4; ++index )
  {
    int v5;
    int ret;

    v5 = Cdvd_modules[index].cm_restart(argc, argv);
    ret = v5;
    if ( v5 < 0 )
    {
      printf("accdvd:init_restart:%d: error %d\n", index, v5);
      return ret;
    }
    argc = v2;
  }
  return 0;
}

int acCdvdModuleStart(int argc, char **argv)
{
  int v2;
  int index;

  v2 = argc;
  for ( index = 0; (unsigned int)index < 4; ++index )
  {
    int v5;
    int ret;

    v5 = Cdvd_modules[index].cm_start(argc, argv);
    ret = v5;
    if ( v5 < 0 )
    {
      printf("accdvd:init_start:%d: error %d\n", index, v5);
      return ret;
    }
    argc = v2;
  }
  return 0;
}

int acCdvdModuleStatus()
{
  int status;
  int index;

  status = 0;
  index = 0;
  while ( (unsigned int)index < 4 )
  {
    int ret;

    ret = Cdvd_modules[index].cm_status();
    if ( ret < 0 )
    {
      printf("accdvd:init_status:%d: error %d\n", index, ret);
      return ret;
    }
    if ( status < ret )
      status = ret;
    index++;
  }
  return status;
}

int acCdvdModuleStop()
{
  int index;

  index = 3;
  while ( index >= 0 )
  {
    int v2;
    int ret;

    v2 = Cdvd_modules[index].cm_stop();
    ret = v2;
    if ( v2 < 0 )
    {
      printf("accdvd:init_stop:%d: error %d\n", index, v2);
      return ret;
    }
    index--;
  }
  return 0;
}

int acCdvdEntry(int argc, char **argv)
{
  int ret;

  ret = acCdvdModuleStart(argc, argv);
  DelayThread(1000);
  if ( ret < 0 )
    return ret;
  if ( RegisterLibraryEntries(&_exp_accdvd) != 0 )
    return -16;
  return 0;
}

// acd.o

static void acd_done(struct acd *acd, struct acd_softc *arg, int ret)
{
  acInt32 tmout;
  int thid;
  int tmout_v2;
  acd_done_t done;
  acSpl state;

  CpuSuspendIntr(&state);
  tmout = arg->active;
  arg->sense = ret;
  tmout--;
  arg->active = tmout;
  if ( tmout < 0 )
    arg->active = 0;
  CpuResumeIntr(state);
  thid = acd->c_thid;
  tmout_v2 = acd->c_tmout;
  done = acd->c_done;
  acd->c_thid = ret;
  if ( !tmout_v2 )
    acd->c_tmout = 1;
  if ( done )
    done(acd, acd->c_arg, ret);
  if ( thid )
    WakeupThread(thid);
}

static void acd_atapi_done(acAtapiT atapi, void *arg, int ret)
{
  struct acd_softc *argt;

  argt = (struct acd_softc *)arg;
  acd_done((struct acd *)atapi, argt, ret);
}

static int acd_request_in(
        struct acd *acd,
        int flag,
        acAtapiPacketT packet,
        void *buffer,
        int size,
        acAtapiDone done,
        char *name)
{
  int status;
  int ret;
  int ret_v10;
  int tmout;
  int v16;
  int ret_v13;
  int ret_v15;
  int state;
  int state_2;

  (void)name;
  if ( (Acdc.status & 1) == 0 )
    return -6;
  ret = acd->c_tmout;
  if ( ret <= 0 )
  {
    acd->c_thid = 0;
    ret = -ret;
  }
  else
  {
    acd->c_thid = GetThreadId();
  }
  acAtapiSetup(&acd->c_atapi, done ? done : acd_atapi_done, &Acdc, ret);
  CpuSuspendIntr(&state);
  ret_v10 = Acdc.drive;
  ++Acdc.active;
  CpuResumeIntr(state);
  status = ret_v10;
  if ( status < 0 )
  {
    return status;
  }
  tmout = acd->c_tmout;
  v16 = flag | ret_v10;
  if ( tmout > 0 )
    acd->c_tmout = 0;
  status = acAtapiRequest(&acd->c_atapi, v16, packet, buffer, size);
  ret_v13 = status;
  if ( status < 0 )
  {
    CpuSuspendIntr(&state_2);
    Acdc.active--;
    if ( Acdc.active < 0 )
      Acdc.active = 0;
    CpuResumeIntr(state_2);
    return ret_v13;
  }
  if ( tmout <= 0 )
  {
    return status;
  }
  while ( 1 )
  {
    int status_v14;

    status_v14 = SleepThread();
    if ( status_v14 == -418 )
    {
      ret_v15 = -116;
      break;
    }
    if ( status_v14 )
    {
      ret_v15 = -5;
      break;
    }
    if ( acd->c_tmout )
    {
      ret_v15 = acd->c_thid;
      acd->c_tmout = tmout;
      return ret_v15;
    }
  }
  acd->c_tmout = tmout;
  return ret_v15;
}

static void acd_read_done(acAtapiT atapi, struct acd_softc *arg, int ret)
{
  if ( ret >= 0 )
    ret >>= 11;
  acd_done((struct acd *)atapi, arg, ret);
}

int acd_read(struct acd *acd, acd_lsn_t lsn, void *buf, int sectors)
{
  int flag;
  union
  {
    struct
    {
      acUint8 opcode;
      acUint8 lun;
      acUint8 lba[4];
      // cppcheck-suppress unusedStructMember
      acUint8 padding;
      acUint8 len[2];
      // cppcheck-suppress unusedStructMember
      acUint8 padding2[3];
    };
    acAtapiPacketData pkt;
  } u;

  if ( !acd || !buf )
    return -22;
  if ( sectors == 0 )
  {
    return 0;
  }
  memset(&u, 0, sizeof(u));
  flag = 2;
  if ( Acdc.dma )
    flag = 3;
  u.opcode = 40;
  u.lun = 0;
  u.lba[0] = (lsn & 0xFF000000) >> 24;
  u.lba[1] = (lsn & 0xFF0000) >> 16;
  u.lba[2] = (lsn & 0xFF00) >> 8;
  u.lba[3] = lsn;
  u.len[0] = (sectors & 0xFF00) >> 8;
  u.len[1] = sectors & 0xFF;
  return acd_request_in(acd, flag, &u.pkt, buf, sectors << 11, (acAtapiDone)acd_read_done, "read");
}

int acd_readtoc(struct acd *acd, void *buf, int size)
{
  acAtapiPacketData v4;

  if ( !acd || !buf )
    return -22;
  if ( !size )
    return 0;
  memset(&v4, 0, sizeof(v4));
  v4.u_h[2] = 0;
  v4.u_w[0] = 579;
  v4.u_b[7] = (size & 0xFF00) >> 8;
  v4.u_b[6] = 0;
  v4.u_w[2] = size & 0xFF;
  return acd_request_in(acd, 2, &v4, buf, size, 0, "readtoc");
}

int acd_seek(struct acd *acd, acd_lsn_t lsn)
{
  acAtapiPacketData v3;

  if ( !acd )
    return -22;
  memset(&v3, 0, sizeof(v3));
  v3.u_h[0] = 40;
  v3.u_b[2] = (lsn & 0xFF000000) >> 24;
  v3.u_b[3] = (lsn & 0xFF0000) >> 16;
  v3.u_w[1] = (lsn & 0xFF00) >> 8;
  v3.u_w[2] = 0;
  v3.u_b[5] = lsn;
  return acd_request_in(acd, 2, &v3, 0, 0, 0, "seek");
}

static void acd_opentray_done(acAtapiT atapi, struct acd_softc *arg, int ret)
{
  acSpl state;

  if ( ret >= 0 )
  {
    CpuSuspendIntr(&state);
    arg->status = (arg->status | 6) ^ 4;
    CpuResumeIntr(state);
  }
  acd_done((struct acd *)atapi, arg, ret);
}

static void acd_closetray_done(acAtapiT atapi, struct acd_softc *arg, int ret)
{
  acSpl state;

  if ( ret >= 0 )
  {
    CpuSuspendIntr(&state);
    arg->status = (arg->status | 6) ^ 2;
    CpuResumeIntr(state);
  }
  acd_done((struct acd *)atapi, arg, ret);
}

int acd_ioctl(struct acd *acd, int cmd)
{
  acAtapiDone done;
  char *name;
  union
  {
    struct
    {
      acUint8 opcode;
      acUint8 imm;
      // cppcheck-suppress unusedStructMember
      acUint8 padding3[2];
      acUint8 op;
      // cppcheck-suppress unusedStructMember
      acUint8 padding4[7];
    };
    acAtapiPacketData pkt;
  } u;

  if ( !acd )
    return -22;
  memset(&u, 0, sizeof(u));
  done = 0;
  if ( cmd == 17 )
  {
    u.opcode = 40;
    name = "ioctl:seek+start";
  }
  else if ( (cmd & 5) != 0 )
  {
    u.opcode = 27;
    u.imm = (cmd & 0x80) != 0;
    u.op = cmd & 3;
    if ( (cmd & 2) != 0 )
    {
      done = (acAtapiDone)acd_opentray_done;
      if ( (cmd & 1) != 0 )
        done = (acAtapiDone)acd_closetray_done;
    }
    name = "ioctl:startstop";
  }
  else
  {
    return -22;
  }
  return acd_request_in(acd, 2, &u.pkt, 0, 0, done, name);
}

static int acd_mode_sense(struct acd *acd, int pgcode, void *buffer, int size, acAtapiDone done, char *name)
{
  acAtapiPacketData v7;

  memset(&v7, 0, sizeof(v7));
  v7.u_b[0] = 0x5A;
  v7.u_b[2] = pgcode;
  v7.u_b[7] = (size & 0xFF00) >> 8;
  v7.u_w[2] = size & 0xFF;
  return acd_request_in(acd, 2, &v7, buffer, size, done, name);
}

static int acd_mode_select(struct acd *acd, void *buffer, int size, acAtapiDone done, char *name)
{
  acAtapiPacketData v6;

  memset(&v6, 0, sizeof(v6));
  v6.u_b[0] = 0x55;
  v6.u_b[1] = 0x10;
  v6.u_b[7] = (size & 0xFF00) >> 8;
  v6.u_w[2] = size & 0xFF;
  return acd_request_in(acd, 6, &v6, buffer, size, done, name);
}

static void acd_getmedium_done(acAtapiT atapi, struct acd_softc *arg, int ret)
{
  int h_mtype;
  acSpl state;

  h_mtype = ret;
  if ( ret >= 0 )
  {
    acUint32 status;
    int v7;

    CpuSuspendIntr(&state);
    h_mtype = arg->retry.me_h.h_mtype;
    status = arg->status | 6;
    arg->medium = h_mtype;
    if ( h_mtype == 113 )
      v7 = status ^ 4;
    else
      v7 = status ^ 2;
    arg->status = v7 | 0xA00;
    CpuResumeIntr(state);
  }
  acd_done((struct acd *)atapi, arg, h_mtype);
}

int acd_getmedium(struct acd *acd)
{
  int ret;
  acSpl state;

  if ( acd )
    return acd_mode_sense(acd, 1, &Acdc.retry, 20, (acAtapiDone)acd_getmedium_done, "getmedium");
  CpuSuspendIntr(&state);
  ret = -61;
  if ( (Acdc.status & 0x800) != 0 )
    ret = Acdc.medium;
  CpuResumeIntr(state);
  return ret;
}

static void acd_retry_done(acAtapiT atapi, struct acd_softc *arg, int ret)
{
  int me_rretry;
  acSpl state;

  me_rretry = ret;
  if ( ret >= 0 )
  {
    acCdvdsifId h_mtype;
    acUint32 status;
    int v8;

    CpuSuspendIntr(&state);
    h_mtype = arg->retry.me_h.h_mtype;
    status = arg->status | 6;
    arg->medium = h_mtype;
    if ( h_mtype == 113 )
      v8 = status ^ 4;
    else
      v8 = status ^ 2;
    arg->status = v8 | 0xA00;
    me_rretry = arg->retry.me_rretry;
    CpuResumeIntr(state);
  }
  acd_done((struct acd *)atapi, arg, me_rretry);
}

int acd_getretry(struct acd *acd)
{
  if ( !acd )
    return -22;
  return acd_mode_sense(acd, 1, &Acdc.retry, 20, (acAtapiDone)acd_retry_done, "getretry");    
}

int acd_setretry(struct acd *acd, int rretry)
{
  int size;
  acSpl state;

  if ( acd == 0 )
  {
    return -22;
  }
  if ( (Acdc.status & 0x200) == 0 )
  {
    return -61;
  }
  CpuSuspendIntr(&state);
  size = 0;
  if ( rretry != Acdc.retry.me_rretry )
  {
    Acdc.retry.me_rretry = rretry;
    size = (Acdc.retry.me_h.h_len[0] << 8) + Acdc.retry.me_h.h_len[1] + 2;
  }
  CpuResumeIntr(state);
  if ( !size )
    return rretry;
  return acd_mode_select(acd, &Acdc.retry, size, (acAtapiDone)acd_retry_done, "setretry");
}

static void acd_getspeed_done(acAtapiT atapi, struct acd_softc *arg, int ret)
{
  int v4;
  acSpl state;

  v4 = ret;
  if ( ret >= 0 )
  {
    acCdvdsifId speed;
    acUint32 status;
    int v8;

    CpuSuspendIntr(&state);
    speed = arg->speed.mc_h.h_mtype;
    v4 = (arg->speed.mc_speed[0] << 8) + arg->speed.mc_speed[1];
    status = arg->status | 6;
    arg->medium = speed;
    if ( speed == 113 )
      v8 = status ^ 4;
    else
      v8 = status ^ 2;
    arg->status = v8 | 0xC00;
    CpuResumeIntr(state);
  }
  acd_done((struct acd *)atapi, arg, v4);
}

static void acd_getmaxspeed_done(acAtapiT atapi, struct acd_softc *arg, int ret)
{
  int v4;
  acSpl state;

  v4 = ret;
  if ( ret >= 0 )
  {
    acCdvdsifId speed;
    acUint32 status;
    int v8;

    CpuSuspendIntr(&state);
    speed = arg->speed.mc_h.h_mtype;
    v4 = (arg->speed.mc_maxspeed[0] << 8) + arg->speed.mc_maxspeed[1];
    status = arg->status | 6;
    arg->medium = speed;
    if ( speed == 113 )
      v8 = status ^ 4;
    else
      v8 = status ^ 2;
    arg->status = v8 | 0xC00;
    CpuResumeIntr(state);
  }
  acd_done((struct acd *)atapi, arg, v4);
}

int acd_getspeed(struct acd *acd, int maxspeed)
{
  acAtapiDone done;

  if ( acd == 0 )
  {
    return -22;
  }
  done = (acAtapiDone)acd_getspeed_done;
  if ( maxspeed )
    done = (acAtapiDone)acd_getmaxspeed_done;
  return acd_mode_sense(acd, 42, &Acdc.speed, 28, done, "getspeed");
}

int acd_setspeed(struct acd *acd, int speed)
{
  int v3;
  int ospeed;
  union
  {
    struct
    {
      acUint8 opcode;
      acUint8 lun;
      acUint8 speed[2];
      // cppcheck-suppress unusedStructMember
      acUint8 padding[8];
    };
    acAtapiPacketData pkt;
  } u;
  acSpl state;

  v3 = speed;
  if ( speed < 0 )
    return -22;
  CpuSuspendIntr(&state);
  if ( (Acdc.status & 0x400) != 0 )
    ospeed = (Acdc.speed.mc_speed[0] << 8) + Acdc.speed.mc_speed[1];
  else
    ospeed = -1;
  CpuResumeIntr(state);
  if ( v3 > 0xFFFF )
    v3 = 0xFFFF;
  if ( v3 == ospeed )
    return 0;
  memset(&u, 0, sizeof(u));
  u.opcode = 0xbb;
  u.lun = 0;
  u.speed[0] = (v3 & 0xFF00) >> 8;
  u.speed[1] = v3;
  return acd_request_in(acd, 2, &u.pkt, 0, 0, 0, "setspeed");
}

static void acd_timer_done(acAtapiT atapi, struct acd_softc *arg, int ret)
{
  int v4;
  acSpl state;

  v4 = ret;
  if ( ret >= 0 )
  {
    acCdvdsifId h_mtype;
    acUint32 status;
    int status_v3;

    CpuSuspendIntr(&state);
    h_mtype = arg->timer.md_h.h_mtype;
    status = arg->status | 6;
    arg->medium = h_mtype;
    if ( h_mtype == 113 )
      status_v3 = status ^ 4;
    else
      status_v3 = status ^ 2;
    arg->status = status_v3 | 0x900;
    v4 = arg->timer.md_timer & 0xF;
    CpuResumeIntr(state);
  }
  acd_done((struct acd *)atapi, arg, v4);
}

int acd_gettimer(struct acd *acd)
{
  if ( !acd )
    return -22;
  return acd_mode_sense(acd, 13, &Acdc.timer, 16, (acAtapiDone)acd_timer_done, "gettimer");
}

int acd_settimer(struct acd *acd, int time)
{
  char v3;
  int acdc;
  int state;

  v3 = time;
  if ( acd == 0 )
  {
    return -22;
  }
  if ( (Acdc.status & 0x100) == 0 )
  {
    return -61;
  }
  CpuSuspendIntr(&state);
  Acdc.timer.md_timer = v3 & 0xF;
  acdc = ((Acdc.timer.md_h.h_len[0] << 8) + Acdc.timer.md_h.h_len[1] + 2);
  CpuResumeIntr(state);
  return acd_mode_select(acd, &Acdc.timer, acdc, (acAtapiDone)acd_timer_done, "settimer");
}

int acd_ready(struct acd *acd)
{
  acAtapiPacketData v2;

  if ( !acd )
    return -22;
  memset(&v2, 0, sizeof(v2));
  return acd_request_in(acd, 2, &v2, 0, 0, 0, "ready");
}

int acd_readcapacity()
{
  int ret;
  struct acd acd_data;
  struct atapi_read_capacity capacity;
  union
  {
    struct
    {
      acUint8 opcode;
      acUint8 lun;
      // cppcheck-suppress unusedStructMember
      acUint8 padding1[10];
    };
    acAtapiPacketData pkt;
  } u;

  acd_setup(&acd_data, 0, 0, 5000000);
  memset(&u, 0, sizeof(u));
  u.opcode = 0x25;
  u.lun = 0;
  ret = acd_request_in(&acd_data, 2, &u.pkt, &capacity, 8, 0, "readcapacity");
  if ( ret >= 0 )
  {
    unsigned int val;

    val = *(unsigned int *)capacity.lba;
    return (val << 24) + ((val & 0xFF00) << 8) + ((val >> 8) & 0xFF00) + ((val >> 24) & 0xFF);
  }
  return ret;
}

int acd_delay()
{
  iop_sys_clock_t t;
  u32 s;
  u32 us;

  GetSystemTime(&t);
  SysClock2USec(&t, &s, &us);
  if ( s >= 0xD )
    return 0;
  return 1000000 * (13 - s) - us;
}

int acd_getsense()
{
  return Acdc.sense;
}

acCdvdsifId acd_gettray()
{
  if ( (Acdc.status & 8) != 0 )
    return 3;
  if ( (Acdc.status & 2) != 0 )
    return 1;
  return (Acdc.status >> 1) & 2;
}

struct acd *acd_setup(struct acd *acd, acd_done_t done, void *arg, int tmout)
{
  if ( acd )
  {
    acd->c_done = done;
    acd->c_arg = arg;
    acd->c_thid = 0;
    acd->c_tmout = tmout;
    if ( !tmout )
      acd->c_tmout = 5000000;
  }
  return acd;
}

int acd_sync(struct acd *acd, int nblocking, int *resultp)
{
  int ret;
  acSpl state;

  CpuSuspendIntr(&state);
  ret = -11;
  if ( !acd->c_thid )
  {
    int v7;

    v7 = acAtapiStatus(&acd->c_atapi);
    ret = v7;
    if ( v7 > 0 )
    {
      ret = 0;
      acd->c_thid = GetThreadId();
    }
    else if ( v7 == 0 )
    {
      ret = 1;
    }
  }
  CpuResumeIntr(state);
  if ( !(ret | nblocking) )
  {
    ret = 1;
    SleepThread();
  }
  if ( ret > 0 && resultp )
  {
    *resultp = acd->c_thid;
  }
  return ret;
}

static void acd_ata_done(acAtaT ata, void *arg, int ret)
{
  int thid;
  struct acd_ata *acdata;

  (void)arg;
  acdata = (struct acd_ata *)ata;
  thid = acdata->a_thid;
  acdata->a_result = ret;
  if ( thid )
    WakeupThread(thid);
}

int acd_ata_request(int flag, acAtaCommandT cmd, int items, acAtaDone done, char *name)
{
  int ret;
  struct acd_ata acdata;

  (void)name;
  acAtaSetup(&acdata.a_ata, done ? done : acd_ata_done, 0, 0x4C4B40u);
  // cppcheck-suppress unreadVariable
  acdata.a_thid = GetThreadId();
  acdata.a_result = 0;
  ret = acAtaRequest(&acdata.a_ata, flag, cmd, items, 0, 0);
  if ( ret < 0 )
  {
    return ret;
  }
  SleepThread();
  return acdata.a_result;
}

static void acd_getstatus_done(acAtaT ata, void *arg, int ret)
{
  int thid;
  struct acd_ata *acdata;
  (void)arg;
  acdata = (struct acd_ata *)ata;
  if ( ret >= 0 )
    ret = *(acUint8 *)acAtaReply(&acdata->a_ata);
  thid = acdata->a_thid;
  acdata->a_result = ret;
  if ( thid )
    WakeupThread(thid);
}

int acd_getstatus()
{
  acAtaCommandData v1[4];

  v1[1] = 2021;
  v1[0] = (Acdc.drive & 0xFF) | 0x2600;
  return acd_ata_request(Acdc.drive | 2, v1, 2, acd_getstatus_done, "getstatus");
}

static int acd_setfeatures(int feature, int value)
{
  acAtaCommandData v3[4];

  v3[2] = (value & 0xFF) | 0x200;
  v3[1] = (feature & 0xFF) | 0x100;
  v3[3] = 2031;
  v3[0] = (Acdc.drive & 0xFF) | 0x600;
  return acd_ata_request(Acdc.drive | 2, v3, 4, 0, "setfeatures");
}

int acd_setdma(acCdvdsifId dma)
{
  acCdvdsifId v1;
  int mode;
  int ret;
  int ret_v3;

  v1 = dma;
  mode = dma;
  if ( !dma )
  {
    Acdc.dma = AC_CDVDSIF_ID_NOP;
    return 0;
  }
  if ( dma == 32 )
  {
    mode = 18;
    ret_v3 = 0x40000;
    while ( mode >= 0 )
    {
      if ( (Acdc.dmamap & ret_v3) != 0 )
        break;
      mode--;
      ret_v3 = 1 << mode;
    }
    v1 = mode;
    if ( mode < 0 )
      return -134;
  }
  if ( (Acdc.dmamap & (1 << v1)) == 0 )
  {
    return -134;
  }
  if ( (unsigned int)v1 < AC_CDVDSIF_ID_PAUSES )
  {
    if ( (unsigned int)v1 < AC_CDVDSIF_ID_STOP )
    {
      if ( (unsigned int)v1 >= AC_CDVDSIF_ID_PAUSE )
        mode = v1 + 8;
    }
    else
    {
      mode = v1 + 16;
    }
  }
  else
  {
    mode = v1 + 40;
  }
  ret = acd_setfeatures(3, mode);
  if ( ret < 0 )
  {
    return ret;
  }
  ret = acd_setfeatures(102, 0);
  if ( ret < 0 )
  {
    return ret;
  }
  Acdc.dma = v1;
  return v1;
}

acCdvdsifId acd_getdma()
{
  return Acdc.dma;
}

static int acd_identify(int drive)
{
  int flag;
  int ret;
  acUint16 ident[256];
  struct acd_ata acdata;
  acAtaCommandData cmd[2];

  flag = 16 * (drive != 0);
  cmd[0] = flag | 0x600;
  cmd[1] = 1953;
  acAtaSetup(&acdata.a_ata, acd_ata_done, 0, 0x4C4B40u);
  // cppcheck-suppress unreadVariable
  acdata.a_thid = GetThreadId();
  acdata.a_result = 0;
  ret = acAtaRequest(&acdata.a_ata, flag | 2, cmd, 2, ident, 512);
  if ( ret >= 0 )
  {
    SleepThread();
    ret = acdata.a_result;
  }
  if ( ret < 0 )
  {
    return ret;
  }
  if ( (ident[0] & 0xFF00) != 0x8500 )
    return -6;
  return ((ident[62] & 0xFF) << 8) | ((ident[63] & 0xFF) << 16) | ((ident[88] & 0xFF) << 24);
}

static int acd_softreset(int drive)
{
  (void)drive;

  return 0;
}

int acd_module_status()
{
  int ret;
  int state;

  CpuSuspendIntr(&state);
  ret = 0;
  if ( (Acdc.status & 1) != 0 )
  {
    ret = 1;
    if ( Acdc.active > 0 )
      ret = 2;
  }
  CpuResumeIntr(state);
  return ret;
}

int acd_module_start(int argc, char **argv)
{
  int ret;
  int drive;
  int ret_v2;

  (void)argc;
  (void)argv;
  ret = acd_module_status();
  drive = 0;
  if ( ret )
  {
    return ret;
  }
  while ( 1 )
  {
    acd_softreset(drive);
    ret_v2 = acd_identify(drive);
    if ( ret_v2 >= 0 )
      break;
    ++drive;
    ret = -6;
    if ( drive >= 2 )
      return ret;
  }
  if ( drive )
    Acdc.drive = 16;
  else
    Acdc.drive = 0;
  Acdc.status = 1;
  Acdc.medium = -1;
  Acdc.dmamap = ret_v2;
  acd_setdma((acCdvdsifId)32);
  return 0;
}

int acd_module_stop()
{
  int ret;

  ret = acd_module_status();
  if ( ret )
  {
    return ret;
  }
  Acdc.status = 0;
  return 0;
}

int acd_module_restart(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  return -88;
}

// cdc.o

static int cdc_errno_set(struct cdc_softc *cdcc, int ret)
{
  if ( ret )
  {
    if ( ret >= 256 )
    {
      if ( ret >> 16 == 6 )
      {
        cdfs_umount();
        ret = 49;
      }
      else
      {
        int asc;

        asc = ret & 0xFFFF;
        ret = 48;
        if ( asc == 8448 )
          ret = 50;
      }
    }
    else
    {
      switch ( ret )
      {
        case 14:
          ret = 32;
          break;
        case 16:
          ret = 19;
          break;
        case 22:
          ret = 33;
          break;
        case 34:
          ret = 50;
          break;
        default:
          ret = 48;
          break;
      }
    }
  }
  cdcc->error = ret;
  return ret;
}

static int cdc_eve_alloc()
{
  int ret;
  iop_event_t param;

  param.attr = 2;
  param.bits = 0;
  param.option = 0;
  ret = CreateEventFlag(&param);
  if ( ret <= 0 )
  {
    printf("accdvd:cdc:eve_alloc: error %d\n", ret);
  }
  return ret;
}

static int cdc_sem_alloc()
{
  int ret;
  iop_sema_t param;

  param.attr = 0;
  param.initial = 1;
  param.max = 1;
  param.option = 0;
  ret = CreateSema(&param);
  if ( ret <= 0 )
  {
    printf("accdvd:cdc:sem_alloc: error %d\n", ret);
  }
  return ret;
}

static int cdc_unlock(struct cdc_softc *cdcc, int ret, acCdvdsifId fno)
{
  int lockid;
  unsigned int v8;

  lockid = cdcc->lockid;
  if ( fno )
  {
    int v6;
    int eveid;

    v6 = 0;
    if ( ret < 0 )
      v6 = -ret;
    cdc_errno_set(cdcc, v6);
    eveid = cdcc->syncid;
    cdcc->stat = 0;
    cdcc->fno = AC_CDVDSIF_ID_NOP;
    if ( eveid > 0 )
      SetEventFlag(eveid, 3u);
  }
  if ( lockid > 0 )
  {
    SignalSema(lockid);
  }
  v8 = ~ret;
  return v8 >> 31;
}

int cdc_getfno()
{
  return Cdcc.fno;
}

int cdc_geterrno()
{
  return Cdcc.error;
}

int cdc_seterrno(int ret)
{
  Cdcc.error = ret;
  return 0;
}

static void cdc_done(struct acd *acd, struct cdc_softc *arg, int ret)
{
  int v3;
  cdc_done_t done;
  int eveid;

  (void)acd;
  v3 = 0;
  if ( ret < 0 )
    v3 = -ret;
  cdc_errno_set(arg, v3);
  done = arg->done;
  arg->done = 0;
  if ( done )
  {
    int type;

    switch ( arg->fno )
    {
      case AC_CDVDSIF_ID_PAUSE:
        type = 7;
        break;
      case AC_CDVDSIF_ID_READ:
        type = 1;
        break;
      case AC_CDVDSIF_ID_SEEK:
        type = 4;
        break;
      case AC_CDVDSIF_ID_STANDBY:
        type = 5;
        break;
      case AC_CDVDSIF_ID_STOP:
        type = 6;
        break;
      default:
        type = 0;
        break;
    }
    done(type);
  }
  eveid = arg->syncid;
  arg->stat = 0;
  arg->fno = AC_CDVDSIF_ID_NOP;
  if ( eveid > 0 )
    SetEventFlag(eveid, 3u);
}

int cdc_sync(int nonblocking)
{
  u32 bits;

  if ( !Cdcc.fno )
  {
    return 0;
  }
  if ( nonblocking > 0 )
  {
    return 1;
  }
  bits = 1;
  if ( nonblocking < 0 )
    bits = 3;
  if ( Cdcc.syncid > 0 )
    WaitEventFlag(Cdcc.syncid, bits, 1, &bits);
  return ((bits & 0xFF) ^ 1) & 1;
}

int cdc_ready(int nonblocking)
{
  struct acd *acd;
  int ret;
  int v4;
  int asc;
  struct acd acd_data;
  struct acd acd_data_v8;

  acd = acd_setup(&acd_data, 0, 0, 5000000);
  Cdcc.error = 0;
  ret = -1;
  while ( ret < 0 )
  {
    int delay;

    ret = acd_ready(acd);
    delay = -1;
    if ( ret >= 0 )
    {
      v4 = acd_readcapacity();
      if ( v4 < 0 )
        v4 = 0;
      Cdcc.cdsize = v4;
      ret = 2;
    }
    else if ( ret < -255 )
    {
      asc = (acUint16)-(ret & 0xFFFF);
      if ( -ret >> 16 != 6 )
      {
        if ( asc != 0x401 )
        {
          if ( asc == 0x3A00 )
          {
            Cdcc.cdsize = 0;
            ret = 2;
          }
        }
        else
        {
          delay = 1000000;
        }
      }
      else
      {
        delay = 0;
        if ( asc == 10496 )
          delay = acd_delay();
      }
    }
    else
    {
      if ( ret == -116 )
      {
        delay = 1000000;
      }
      else
      {
        ret = 6;
      }
    }
    if ( nonblocking )
      break;
    if ( delay > 0 )
      DelayThread(delay);
  }
  if ( ret == 2 )
  {
    acd_getmedium(acd_setup(&acd_data_v8, 0, 0, 5000000));
    Cdcc.tray = acd_gettray();
  }
  return ret;
}

int cdc_medium()
{
  struct acd *v0;
  int v1;
  int ret;
  int v3;
  struct acd acd_data;

  v0 = acd_setup(&acd_data, 0, 0, 5000000);
  v1 = acd_getmedium(v0);
  ret = v1;
  v3 = 0;
  if ( v1 < 0 )
    v3 = -v1;
  cdc_errno_set(&Cdcc, v3);
  switch ( ret )
  {
    case 1:
    case 5:
    case 33:
    case 37:
      return 18;
    case 2:
    case 6:
    case 34:
    case 38:
      return 253;
    case 3:
    case 7:
    case 35:
    case 39:
      return 19;
    case 65:
    case 69:
      return 20;
    case 112:
    case 113:
      return 0;
    default:
      return 255;
  }
}

int cdc_error()
{
  return Cdcc.error;
}

int cdc_stat()
{
  int ret;
  int v2;
  struct acd acd_data;

  ret = acd_getmedium(0);
  acd_setup(&acd_data, 0, 0, 5000000);
  if ( ret == -61 )
    ret = acd_getmedium(&acd_data);
  if ( ret == 113 )
  {
    return 1;
  }
  if ( Cdcc.stat )
  {
    return Cdcc.stat;
  }
  v2 = acd_getstatus();
  if ( v2 < 0 )
    return 32;
  return (v2 != 0) ? 2 : 0;
}

int cdc_readtoc(unsigned char *toc, cdc_xfer_t xfer)
{
  acInt32 ret;
  int v7;
  int ret_v3;

  if ( Cdcc.lockid )
  {
    ret = 0;
    if ( WaitSema(Cdcc.lockid) )
      ret = 19;
  }
  else
  {
    ret = 17;
  }
  if ( ret )
  {
    Cdcc.error = ret;
    return 0;
  }
  v7 = -16;
  if ( Cdcc.fno == AC_CDVDSIF_ID_NOP )
  {
    v7 = 6;
    Cdcc.fno = AC_CDVDSIF_ID_READTOC;
    Cdcc.stat = 6;
    if ( Cdcc.syncid > 0 )
      ClearEventFlag(Cdcc.syncid, 0);
  }
  ret_v3 = v7;
  if ( v7 > 0 )
  {
    ret_v3 = acd_readtoc(acd_setup(&Cdcc.acd, 0, 0, 5000000), Cdcc.buf, 1024);
    if ( ret_v3 > 0 )
    {
      if ( ret_v3 < 1024 )
        memset(&Cdcc.buf[ret_v3], 0, 1024 - ret_v3);
      ret_v3 = xfer(toc, Cdcc.buf, 1024, CDC_XFER_OUT);
    }
  }
  return cdc_unlock(&Cdcc, ret_v3, AC_CDVDSIF_ID_READTOC);
}

int cdc_lookup(sceCdlFILE *fp, const char *name, int namlen, cdc_xfer_t xfer)
{
  acInt32 ret;
  int ret_v2;
  int ret_v3;
  struct cdfs_dirent dirent;

  if ( Cdcc.lockid )
  {
    ret = 0;
    if ( WaitSema(Cdcc.lockid) )
      ret = 19;
  }
  else
  {
    ret = 17;
  }
  if ( ret )
  {
    Cdcc.error = ret;
    return 0;
  }
  ret_v2 = -16;
  if ( Cdcc.fno )
  {
    ret_v3 = ret_v2;
  }
  else
  {
    ret_v2 = 12;
    ret_v3 = 12;
    Cdcc.fno = AC_CDVDSIF_ID_LOOKUP;
    Cdcc.stat = 0;
    if ( Cdcc.syncid > 0 )
    {
      ClearEventFlag(Cdcc.syncid, 0);
      ret_v3 = ret_v2;
    }
  }
  if ( ret_v3 > 0 )
  {
    ret_v3 = 0;
    if ( xfer )
    {
      ret_v3 = xfer(Cdcc.buf, (void *)((uiptr)name - ((uiptr)name & 0xF)), (((uiptr)name & 0xF) + namlen + 0xF) & 0xFFFFFFF0, CDC_XFER_IN);
      name = (char *)&Cdcc.buf[(uiptr)name & 0xF];
    }
    while ( ret_v3 > 0 )
    {
      int ret_v4;

      ret_v4 = cdfs_lookup(&dirent, name, namlen);
      if ( ret_v4 >= 0 )
      {
        int d_namlen;

        *(acUint32 *)fp->date = *(acUint32 *)&dirent.d_time.t_padding;
        *(acUint32 *)&fp->date[4] = *(acUint32 *)&dirent.d_time.t_day;
        d_namlen = dirent.d_namlen;
        fp->lsn = dirent.d_lsn;
        fp->size = dirent.d_size;
        fp->name[d_namlen] = 59;
        fp->name[d_namlen + 1] = (dirent.d_vol & 0xFF) + 48;
        fp->name[d_namlen + 2] = 0;
        memcpy(fp->name, dirent.d_name, d_namlen);
        ret_v3 = 0;
      }
      else
      {
        ret_v3 = cdfs_recover(ret_v4);
      }
    }
  }
  return cdc_unlock(&Cdcc, ret_v3, AC_CDVDSIF_ID_LOOKUP);
}

int cdc_seek(unsigned int lsn, cdc_done_t done)
{
  acCdvdsifId fno;
  acInt32 v5;
  int v8;
  int ret_v4;

  fno = AC_CDVDSIF_ID_SEEK;
  if ( Cdcc.lockid )
  {
    v5 = 0;
    if ( WaitSema(Cdcc.lockid) )
      v5 = 19;
  }
  else
  {
    v5 = 17;
  }
  if ( v5 )
  {
    Cdcc.error = v5;
    return 0;
  }
  v8 = -16;
  if ( Cdcc.fno == AC_CDVDSIF_ID_NOP )
  {
    v8 = 13;
    Cdcc.fno = AC_CDVDSIF_ID_SEEK;
    Cdcc.stat = 18;
    if ( Cdcc.syncid > 0 )
      ClearEventFlag(Cdcc.syncid, 0);
  }
  ret_v4 = v8;
  if ( v8 <= 0 )
  {
    fno = AC_CDVDSIF_ID_NOP;
  }
  else if ( lsn < Cdcc.cdsize )
  {
    Cdcc.done = done;
    ret_v4 = acd_seek(acd_setup(&Cdcc.acd, (acd_done_t)cdc_done, &Cdcc, -5000000), lsn);
    if ( ret_v4 >= 0 )
      fno = AC_CDVDSIF_ID_NOP;
  }
  else
  {
    ret_v4 = 0;
  }
  return cdc_unlock(&Cdcc, ret_v4, fno);
}

static int cdc_ioctl(acCdvdsifId fno, int state, int tmout, cdc_done_t done)
{
  acInt32 ret;
  int ret_v2;
  acCdvdsifId v12;
  int ret_v4;

  if ( Cdcc.lockid )
  {
    ret = 0;
    if ( WaitSema(Cdcc.lockid) )
      ret = 19;
  }
  else
  {
    ret = 17;
  }
  if ( ret )
  {
    Cdcc.error = ret;
    return 0;
  }
  if ( state == 4 )
  {
    ret_v2 = 0;
  }
  else if ( state >= 5 )
  {
    if ( state == 6 )
    {
      ret_v2 = 1;
    }
    else
    {
      ret_v2 = 10;
      if ( state == 16 )
        ret_v2 = 18;
    }
  }
  else
  {
    ret_v2 = 10;
    if ( state == 1 )
      ret_v2 = 2;
  }
  if ( fno )
  {
    v12 = -16;
    if ( Cdcc.fno == AC_CDVDSIF_ID_NOP )
    {
      v12 = fno;
      Cdcc.fno = fno;
      Cdcc.stat = ret_v2;
      if ( Cdcc.syncid > 0 )
        ClearEventFlag(Cdcc.syncid, 0);
    }
  }
  else
  {
    Cdcc.stat = 0;
    Cdcc.fno = AC_CDVDSIF_ID_NOP;
    if ( Cdcc.syncid > 0 )
      SetEventFlag(Cdcc.syncid, 3u);
    v12 = AC_CDVDSIF_ID_NOP;
  }
  ret_v4 = v12;
  if ( v12 < AC_CDVDSIF_ID_NOP )
  {
    fno = AC_CDVDSIF_ID_NOP;
  }
  else
  {
    Cdcc.done = done;
    ret_v4 = acd_ioctl(acd_setup(&Cdcc.acd, (acd_done_t)cdc_done, &Cdcc, tmout), state);
    if (ret_v4 >= 0)
    {
      fno = AC_CDVDSIF_ID_NOP;
    }
  }
  return cdc_unlock(&Cdcc, ret_v4, fno);
}

int cdc_pause(cdc_done_t done)
{
  return cdc_ioctl(AC_CDVDSIF_ID_PAUSE, 1, -5000000, done);
}

int cdc_standby(cdc_done_t done)
{
  return cdc_ioctl(AC_CDVDSIF_ID_STANDBY, 17, -5000000, done);
}

int cdc_stop(cdc_done_t done)
{
  return cdc_ioctl(AC_CDVDSIF_ID_STOP, 4, -5000000, done);
}

int cdc_tray(int mode, u32 *traycnt)
{
  acCdvdsifId tray;
  int v5;
  acCdvdsifId v8;
  struct acd v10;

  tray = Cdcc.tray;
  v5 = 1;
  if ( mode == 2 )
  {
    acd_getmedium(acd_setup(&v10, 0, 0, 5000000));
  }
  else
  {
    int ret;

    ret = 134;
    if ( mode )
      ret = 131;
    v5 = cdc_ioctl(AC_CDVDSIF_ID_TRAY, ret, 5000000, 0);
  }
  v8 = acd_gettray();
  Cdcc.tray = v8;
  *traycnt = tray != v8;
  return v5;
}

int cdc_getpos()
{
  acInt32 v0;
  int ret;

  v0 = 17;
  if ( Cdcc.lockid )
  {
    v0 = 0;
    if ( WaitSema(Cdcc.lockid) )
      v0 = 19;
  }
  if ( v0 )
  {
    Cdcc.error = v0;
    return 0;
  }
  if ( Cdcc.fno )
  {
    if ( Cdcc.fno == AC_CDVDSIF_ID_READ )
    {
      ret = Cdcc.rd.pos << 11;
    }
    else
    {
      Cdcc.error = 19;
      ret = 0;
    }
  }
  else
  {
    ret = 0;
  }
  if ( Cdcc.lockid > 0 )
  {
    SignalSema(Cdcc.lockid);
  }
  return ret;
}

static int cdc_rmode(struct cdc_softc *cdcc, const sceCdRMode *mode)
{
  int spindlctrl;
  struct acd *v5;
  int speed;
  struct acd *acd;
  int v8;
  int trycount;
  struct acd *acd_v7;

  spindlctrl = mode->spindlctrl;
  v5 = acd_setup(&cdcc->acd, 0, 0, 5000000);
  speed = cdcc->rd.maxspeed;
  acd = v5;
  v8 = 0;
  if ( !cdcc->rd.maxspeed )
  {
    v8 = acd_getspeed(v5, 1);
    speed = v8;    
  }
  if ( v8 >= 0 )
  {
    cdcc->rd.maxspeed = v8;
    if ( spindlctrl == 1 )
    {
      int v9;

      v9 = 3 * (speed - 1);
      speed = v9 >> 2;
      if ( v9 < 0 )
        speed = (v9 + 3) >> 2;
    }
    if ( acd_setspeed(acd, speed) >= 0 )
      cdcc->rd.spindle = spindlctrl;
  }
  trycount = mode->trycount - 1;
  acd_v7 = acd_setup(&cdcc->acd, 0, 0, 5000000);
  if ( trycount < 0 )
    trycount = 254;
  while ( acd_setretry(acd_v7, trycount) == -61 && acd_getretry(acd_v7) >= 0 )
    ;
  return 0;
}

static void cdc_read_done(struct acd *acd, struct cdc_softc *arg, int ret)
{
  cdc_xfer_t xfer;
  acInt32 npos;
  unsigned char *buf;
  int rlen;
  unsigned char *buf_v9;
  unsigned char *src;

  if ( ret >= 0 )
  {
    acInt32 cpos;
    acInt32 size;
    acInt32 xlen;
    acInt32 bsize;

    cpos = arg->rd.pos;
    size = arg->rd.size;
    xfer = arg->rd.xfer;
    npos = cpos + ret;
    xlen = size - cpos;
    buf = &arg->rd.buf[2048 * cpos];
    bsize = arg->rd.bsize;
    rlen = size - (cpos + ret);
    if ( size < cpos + ret )
      npos = arg->rd.size;
    if ( bsize < rlen )
      rlen = arg->rd.bsize;
    if ( bsize < xlen )
      xlen = arg->rd.bsize;
    arg->rd.pos = npos;
    if ( xfer )
    {
      unsigned char *size_v10;
      acInt32 cpos_v11;
      acInt32 bsize_v13;

      size_v10 = buf;
      cpos_v11 = bsize << 11;
      src = arg->buf;
      bsize_v13 = arg->rd.bank;
      buf_v9 = &src[cpos_v11];
      if ( bsize_v13 )
      {
        src += cpos_v11;
        buf_v9 = arg->buf;
      }
      arg->rd.bank = bsize_v13 ^ 1;
      ret = xfer(size_v10, src, xlen << 11, CDC_XFER_OUT);
    }
    else
    {
      buf_v9 = &buf[2048 * ret];
    }
  }
  if ( ret >= 0 )
  {
    ret = npos;
    if ( rlen )
    {
      int size_v14;

      size_v14 = arg->syncid;
      if ( size_v14 > 0 )
        SetEventFlag(size_v14, 2u);
      ret = acd_read(acd, arg->rd.lsn + npos, buf_v9, rlen);
    }
  }
  if ( ret >= 0 )
  {
    if ( rlen )
    {
      int size_v15;

      size_v15 = arg->syncid;
      if ( size_v15 > 0 )
        ClearEventFlag(size_v15, 0xFFFFFFFD);
      return;
    }
  }
  cdc_done(acd, arg, ret);
}

int cdc_read(unsigned int lsn, void *buf, int sectors, const sceCdRMode *mode, cdc_xfer_t xfer, cdc_done_t done)
{
  acCdvdsifId fno;
  acInt32 v11;
  int v14;
  int ret_v4;
  unsigned int n;
  struct acd *ret_v6;

  fno = AC_CDVDSIF_ID_READ;
  if ( Cdcc.lockid )
  {
    v11 = 0;
    if ( WaitSema(Cdcc.lockid) )
      v11 = 19;
  }
  else
  {
    v11 = 17;
  }
  if ( v11 )
  {
    Cdcc.error = v11;
    return 0;
  }
  v14 = -16;
  if ( Cdcc.fno == AC_CDVDSIF_ID_NOP )
  {
    v14 = 9;
    Cdcc.fno = AC_CDVDSIF_ID_READ;
    Cdcc.stat = 6;
    if ( Cdcc.syncid > 0 )
      ClearEventFlag(Cdcc.syncid, 0);
  }
  ret_v4 = v14;
  if ( v14 <= 0 )
  {
    fno = AC_CDVDSIF_ID_NOP;
    return cdc_unlock(&Cdcc, ret_v4, fno);
  }
  n = 16;
  if ( lsn >= Cdcc.cdsize )
  {
    ret_v4 = -34;
  }
  else
  {
    if ( lsn + sectors >= Cdcc.cdsize )
      sectors = Cdcc.cdsize - lsn;
    Cdcc.rd.buf = (acUint8 *)buf;
    Cdcc.done = done;
    Cdcc.rd.size = sectors;
    Cdcc.rd.bsize = 16;
    Cdcc.rd.lsn = lsn;
    Cdcc.rd.xfer = xfer;
    Cdcc.rd.pos = 0;
    Cdcc.rd.bank = 0;
    if ( xfer )
      buf = Cdcc.buf;
    if ( (unsigned int)sectors < 0x10 )
      n = sectors;
    ret_v4 = cdc_rmode(&Cdcc, mode);
    // cppcheck-suppress knownConditionTrueFalse
    if ( ret_v4 < 0 )
      return cdc_unlock(&Cdcc, ret_v4, fno);
    ret_v6 = acd_setup(&Cdcc.acd, (acd_done_t)cdc_read_done, &Cdcc, -5000000);
    ret_v4 = acd_read(ret_v6, lsn, buf, n);
    if ( ret_v4 >= 0 )
    {
      fno = AC_CDVDSIF_ID_NOP;
    }
  }
  return cdc_unlock(&Cdcc, ret_v4, fno);
}

int cdc_xfer(void *dst, void *src, int len, enum cdc_xfer_dir dir)
{
  if ( dir )
    memcpy(dst, src, len);
  return len;
}

static int cdc_unlocks(struct cdc_softc *cdcc, int ret, acCdvdsifId fno)
{
  int lockid;

  lockid = cdcc->lockid;
  if ( ret < 0 )
    cdc_errno_set(cdcc, -ret);
  if ( cdcc->fno == fno )
  {
    int eveid;

    eveid = cdcc->syncid;
    cdcc->fno = AC_CDVDSIF_ID_NOP;
    if ( eveid > 0 )
      SetEventFlag(eveid, 3u);
  }
  if ( lockid > 0 )
  {
    SignalSema(lockid);
  }
  return ret >= 0;
}

static void cdc_stream_done(struct acd *acd, struct cdc_softc *arg, int ret)
{
  int v4;
  int v21;
  acSpl state;
  int flg;

  flg = 0;
  v4 = ret;
  if ( ret <= 0 )
  {
    arg->st.flag = 0;
    arg->fno = AC_CDVDSIF_ID_NOP;
    v21 = 0;
    flg = 1;
  }
  else
  {
    unsigned int flag;
    acInt32 tail;
    acInt32 size;
    acInt32 bsize;
    unsigned int cdsize;
    acInt32 head;
    unsigned int lsn;
    int xlen;
    unsigned int v15;
    unsigned char *buf;
    unsigned int size_v12;

    CpuSuspendIntr(&state);
    flag = arg->st.flag;
    tail = arg->st.tail;
    size = arg->st.size;
    bsize = arg->st.bsize;
    cdsize = arg->cdsize;
    head = arg->st.head + v4;
    if ( head >= size )
      head = 0;
    lsn = arg->st.lsn + v4;
    if ( (flag & 0x10) != 0 )
    {
      head = 0;
      tail = 0;
      lsn = arg->st.reqlsn;
      flag = (flag | 0x14) ^ 0x14;
      arg->st.tail = 0;
    }
    else
    {
      if ( head == tail )
      {
        flag = (flag | 6) ^ 2;
      }
    }
    xlen = tail - head;
    if ( head >= tail )
      xlen = size - head;
    v15 = lsn + xlen;
    if ( bsize < xlen )
    {
      xlen = bsize;
      v15 = lsn + bsize;
    }
    if ( v15 >= cdsize )
      xlen = cdsize - lsn;
    buf = &arg->st.buf[2048 * head];
    size_v12 = flag & 0x28;
    if ( size_v12 == 32 )
    {
      arg->st.flag = flag & 0xFFFFFFFD;
    }
    else
    {
      if ( ((flag & 0x28) >= 0x21) ? (size_v12 != 40) : (size_v12 != 8) )
      {
        arg->st.flag = flag;
      }
      else
      {
        arg->st.flag = flag & 4;
      }
    }
    arg->st.head = head;
    arg->st.lsn = lsn;
    CpuResumeIntr(state);
    if ( (flag & 8) != 0 )
    {
      arg->fno = AC_CDVDSIF_ID_NOP;
      v4 = 0;
      v21 = 0;
      flg = 1;
    }
    else
    {
      v4 = 0;
      if ( (flag & 0x20) != 0 )
      {
        v21 = 0;
        flg = 1;
      }
      else
      {
        v4 = -34;
        if ( !xlen )
        {
          v21 = 0;
          flg = 1;
        }
        else
        {
          int eveid;
          eveid = arg->syncid;
          if ( eveid > 0 )
            SetEventFlag(arg->syncid, 3u);
          if ( (flag & 4) == 0 )
          {
            if ( eveid > 0 )
              ClearEventFlag(eveid, 0);
            v4 = acd_read(acd, lsn, buf, xlen);
            if ( v4 < 0 )
            {
              v21 = 0;
              flg = 1;
            }
          }
        }
      }
    }
  }
  if (flg)
  {
    int eveid_v17;

    if ( v4 < 0 )
      v21 = -v4;
    cdc_errno_set(arg, v21);
    eveid_v17 = arg->syncid;
    if ( eveid_v17 > 0 )
      SetEventFlag(eveid_v17, 3u);
  }
}

static int cdc_stream(struct cdc_softc *cdcc)
{
  int ret;
  int head;
  int tail;
  int xlen;
  int flag;
  unsigned char *buf;
  unsigned int lsn;
  int tail_v9;
  struct acd *ret_v10;
  acSpl state;

  if ( cdcc->fno != AC_CDVDSIF_ID_STREAM )
  {
    return -16;
  }
  CpuSuspendIntr(&state);
  head = cdcc->st.head;
  tail = cdcc->st.tail;
  xlen = tail - head;
  if ( head >= tail )
    xlen = cdcc->st.size - head;
  flag = cdcc->st.flag;
  if ( cdcc->st.bsize < xlen )
    xlen = cdcc->st.bsize;
  buf = &cdcc->st.buf[2048 * head];
  if ( (flag & 6) != 0 || (flag & 0x28) != 0 || (flag & 1) == 0 )
    xlen = 0;
  lsn = 0;
  if ( xlen )
  {
    unsigned int head_v7;

    flag |= 2u;
    head_v7 = cdcc->cdsize;
    if ( (flag & 0x10) != 0 )
    {
      lsn = cdcc->st.reqlsn;
      flag ^= 0x10u;
      cdcc->st.tail = 0;
      cdcc->st.head = 0;
      cdcc->st.lsn = lsn;
    }
    else
    {
      lsn = cdcc->st.lsn;
    }
    if ( lsn + xlen >= head_v7 )
    {
      xlen = head_v7 - lsn;
      if ( head_v7 == lsn )
        flag ^= 2u;
    }
  }
  cdcc->st.flag = flag;
  CpuResumeIntr(state);
  if ( !xlen )
  {
    return 0;
  }
  tail_v9 = cdcc->syncid;
  if ( tail_v9 > 0 )
    ClearEventFlag(tail_v9, 0);
  ret_v10 = acd_setup(&cdcc->acd, (acd_done_t)cdc_stream_done, cdcc, -5000000);
  ret = acd_read(ret_v10, lsn, buf, xlen);
  if ( ret < 0 )
    cdcc->st.flag = 0;
  return ret;
}

int cdc_reads(void *buf, int sectors, int mode, int *errp, cdc_xfer_t xfer)
{
  int v5;
  int v7;
  unsigned char *v11;
  acInt32 rlen;
  int ret_v8;
  acInt32 head;
  int rlen_v10;
  int v17;
  int rlen_v13;
  int xlen;
  unsigned char *tmp;
  int v21;
  acInt32 ret_v17;
  int xlen_v20;
  int ret_v21;
  int rlen_v22;
  int rlen_v23;
  acSpl state;
  int state_2;
  int state_3;
  int v33;
  unsigned char *dst;
  u32 *resbits;

  v5 = sectors;
  dst = (unsigned char *)buf;
  resbits = (u32 *)&v33;
  while ( v5 > 0 )
  {
    acInt32 v6;
    acInt32 ret;
    int len;

    v6 = 17;
    if ( Cdcc.lockid )
    {
      v7 = WaitSema(Cdcc.lockid);
      v6 = 0;
      if ( v7 )
        v6 = 19;
    }
    if ( v6 )
    {
      Cdcc.error = v6;
      break;
    }
    ret = 27;
    if ( Cdcc.fno != AC_CDVDSIF_ID_STREAM )
    {
      ret = -16;
      if ( Cdcc.fno == AC_CDVDSIF_ID_NOP )
      {
        ret = 19;
        Cdcc.fno = AC_CDVDSIF_ID_READS;
        if ( Cdcc.syncid > 0 )
          ClearEventFlag(Cdcc.syncid, 0);
      }
    }
    len = v5;
    if ( ret <= 0 )
    {
      rlen_v23 = 0;
      printf("accdvd:cdc:reads: ACTIVE\n");
    }
    else
    {
      v11 = dst;
      CpuSuspendIntr(&state);
      rlen = Cdcc.st.tail;
      ret_v8 = Cdcc.st.flag;
      head = Cdcc.st.head;
      rlen_v10 = Cdcc.st.lsn >= Cdcc.cdsize;
      CpuResumeIntr(state);
      if ( (ret_v8 & 0x10) != 0 )
      {
        ret = 0;
      }
      if ( ((ret_v8 & 4) == 0) && (head == rlen) )
      {
        v17 = 0;
        if ( rlen_v10 )
          v17 = -34;
        ret = v17;
      }
      else
      {
        int flg;

        flg = 1;
        rlen_v13 = 0;
        if ( rlen >= head )
        {
          xlen = Cdcc.st.size - rlen;
          tmp = v11;
          if ( v5 < Cdcc.st.size - rlen )
            xlen = v5;
          len = v5 - xlen;
          v11 += 2048 * xlen;
          rlen_v13 = xlen;
          v21 = xlen;
          if ( xlen )
          {
            v21 = xfer(tmp, &Cdcc.st.buf[2048 * rlen], xlen * 2048, CDC_XFER_OUT);
            if ( v21 >= 0 )
            {
              CpuSuspendIntr(&state_2);
              ret_v17 = rlen + rlen_v13;
              if ( rlen + rlen_v13 >= Cdcc.st.size )
                ret_v17 = 0;
              Cdcc.st.tail = ret_v17;
              Cdcc.st.flag &= ~4u;
              CpuResumeIntr(state_2);
              v21 = ret_v17;
            }
          }
          rlen = v21;
          if ( rlen < 0 )
          {
            ret = rlen;
            flg = 0;
          }
        }
        if ( rlen < head )
        {
          xlen_v20 = head - rlen;
          ret = head - rlen;
          if ( len < head - rlen )
          {
            xlen_v20 = len;
            ret = len;
          }
          rlen_v13 += xlen_v20;
          rlen_v22 = 0;
          if ( ret )
          {
            ret_v21 = xfer(v11, &Cdcc.st.buf[2048 * rlen], ret << 11, CDC_XFER_OUT);
            if ( ret_v21 >= 0 )
            {
              CpuSuspendIntr(&state_3);
              ret += rlen;
              if ( ret >= Cdcc.st.size )
                ret = 0;
              Cdcc.st.tail = ret;
              Cdcc.st.flag &= ~4u;
              CpuResumeIntr(state_3);
              rlen_v22 = ret;
            }
            ret = ret_v21;
          }
          else
          {
            rlen_v22 = ret;
          }
          if ( rlen_v22 < 0 )
            flg = 0;
        }
        if ( flg )
        {
          ret = rlen_v13;
          if ( rlen_v13 > 0 && xfer )
          {
            xfer(0, 0, 0, CDC_XFER_SYNC);
          }
        }
      }
      rlen_v23 = ret;
      if ( ret < 0 )
      {
        rlen_v23 = 0;
        printf("accdvd:cdc:reads: READ\n");
      }
      else
      {
        v5 -= ret;
        dst += 2048 * ret;
        ret = cdc_stream(&Cdcc);
      }
    }
    cdc_unlocks(&Cdcc, ret, AC_CDVDSIF_ID_READS);
    if ( ret < 0 )
      break;
    if ( rlen_v23 <= 0 )
    {
      if ( !mode )
        break;
      v33 = 1;
      if ( Cdcc.syncid > 0 )
        WaitEventFlag(Cdcc.syncid, 1u, 1, resbits);
    }
  }
  *errp = Cdcc.error;
  return sectors - v5;
}

int cdc_starts(unsigned int lsn, const sceCdRMode *mode)
{
  acInt32 v4;
  int v7;
  int ret;
  acSpl state;

  if ( Cdcc.lockid )
  {
    v4 = 0;
    if ( WaitSema(Cdcc.lockid) )
      v4 = 19;
  }
  else
  {
    v4 = 17;
  }
  if ( v4 )
  {
    Cdcc.error = v4;
    return 0;
  }
  v7 = 27;
  if ( Cdcc.fno != AC_CDVDSIF_ID_STREAM )
  {
    v7 = -16;
    if ( Cdcc.fno == AC_CDVDSIF_ID_NOP )
    {
      v7 = 21;
      Cdcc.fno = AC_CDVDSIF_ID_STARTS;
      if ( Cdcc.syncid > 0 )
        ClearEventFlag(Cdcc.syncid, 0);
    }
  }
  ret = v7;
  if ( v7 > 0 )
  {
    acInt32 flag;

    CpuSuspendIntr(&state);
    flag = Cdcc.st.flag;
    if ( (Cdcc.st.flag & 2) != 0 )
    {
      Cdcc.st.reqlsn = lsn;
      Cdcc.st.flag |= 0x10u;
    }
    else
    {
      flag = 0;
      Cdcc.st.flag = 1;
      Cdcc.st.lsn = lsn;
    }
    CpuResumeIntr(state);
    if ( !flag )
    {
      acCdvdsifId flag_v5;

      flag_v5 = Cdcc.fno;
      Cdcc.fno = AC_CDVDSIF_ID_STREAM;
      ret = cdc_rmode(&Cdcc, mode);
      // cppcheck-suppress knownConditionTrueFalse
      if ( ret < 0 || (ret = cdc_stream(&Cdcc), ret < 0) )
        Cdcc.fno = flag_v5;
    }
  }
  return cdc_unlocks(&Cdcc, ret, AC_CDVDSIF_ID_STARTS);
}

int cdc_stops()
{
  acInt32 v0;
  int sync;
  int ret;
  int sync_v5;
  int ret_v6;
  int state;
  u32 pattern;

  v0 = 17;
  if ( Cdcc.lockid )
  {
    v0 = 0;
    if ( WaitSema(Cdcc.lockid) )
      v0 = 19;
  }
  if ( v0 )
  {
    Cdcc.error = v0;
    return 0;
  }
  sync = 27;
  if ( Cdcc.fno != AC_CDVDSIF_ID_STREAM )
  {
    sync = -16;
    if ( Cdcc.fno == AC_CDVDSIF_ID_NOP )
    {
      sync = 23;
      Cdcc.fno = AC_CDVDSIF_ID_STOPS;
      if ( Cdcc.syncid > 0 )
        ClearEventFlag(Cdcc.syncid, 0);
    }
  }
  ret = sync;
  sync_v5 = 0;
  if ( sync > 0 )
  {
    CpuSuspendIntr(&state);
    sync_v5 = Cdcc.st.flag | 8;
    if ( (Cdcc.st.flag & 2) == 0 )
    {
      Cdcc.fno = AC_CDVDSIF_ID_STOPS;
      sync_v5 = 0;
    }
    Cdcc.st.flag = sync_v5;
    CpuResumeIntr(state);
  }
  ret_v6 = cdc_unlocks(&Cdcc, ret, AC_CDVDSIF_ID_STOPS);
  if ( sync_v5 )
  {
    pattern = 1;
    if ( Cdcc.syncid > 0 )
      WaitEventFlag(Cdcc.syncid, 1u, 1, &pattern);
  }
  return ret_v6;
}

int cdc_pauses()
{
  acInt32 v0;
  int sync;
  int ret;
  int sync_v5;
  int ret_v7;
  int state;
  u32 pattern;

  v0 = 17;
  if ( Cdcc.lockid )
  {
    v0 = 0;
    if ( WaitSema(Cdcc.lockid) )
      v0 = 19;
  }
  if ( v0 )
  {
    Cdcc.error = v0;
    return 0;
  }
  sync = 27;
  if ( Cdcc.fno != AC_CDVDSIF_ID_STREAM )
  {
    sync = -16;
    if ( Cdcc.fno == AC_CDVDSIF_ID_NOP )
    {
      sync = 24;
      Cdcc.fno = AC_CDVDSIF_ID_PAUSES;
      if ( Cdcc.syncid > 0 )
        ClearEventFlag(Cdcc.syncid, 0);
    }
  }
  ret = sync;
  sync_v5 = 0;
  if ( sync > 0 )
  {
    int sync_v6;

    CpuSuspendIntr(&state);
    sync_v6 = Cdcc.st.flag;
    if ( (Cdcc.st.flag & 2) != 0 )
    {
      sync_v6 = Cdcc.st.flag | 0x20;
      Cdcc.st.flag |= 0x20u;
    }
    sync_v5 = sync_v6 & 2;
    CpuResumeIntr(state);
  }
  ret_v7 = cdc_unlocks(&Cdcc, ret, AC_CDVDSIF_ID_PAUSES);
  if ( sync_v5 )
  {
    pattern = 1;
    if ( Cdcc.syncid > 0 )
      WaitEventFlag(Cdcc.syncid, 1u, 1, &pattern);
  }
  return ret_v7;
}

int cdc_resumes()
{
  acInt32 v0;
  int ret_v2;
  int ret_v3;
  acSpl state;

  v0 = 17;
  if ( Cdcc.lockid )
  {
    v0 = 0;
    if ( WaitSema(Cdcc.lockid) )
      v0 = 19;
  }
  if ( v0 )
  {
    Cdcc.error = v0;
    return 0;
  }
  ret_v2 = 27;
  if ( Cdcc.fno == AC_CDVDSIF_ID_STREAM )
  {
    ret_v3 = ret_v2;
  }
  else
  {
    ret_v2 = -16;
    if ( Cdcc.fno )
    {
      ret_v3 = ret_v2;
    }
    else
    {
      ret_v2 = 25;
      ret_v3 = 25;
      Cdcc.fno = AC_CDVDSIF_ID_RESUMES;
      if ( Cdcc.syncid > 0 )
      {
        ClearEventFlag(Cdcc.syncid, 0);
        ret_v3 = ret_v2;
      }
    }
  }
  if ( ret_v3 > 0 )
  {
    int flag;

    CpuSuspendIntr(&state);
    flag = Cdcc.st.flag;
    if ( (Cdcc.st.flag & 2) == 0 && (Cdcc.st.flag & 0x20) != 0 )
      Cdcc.st.flag ^= 0x20u;
    CpuResumeIntr(state);
    ret_v3 = 0;
    if ( (flag & 0x20) != 0 )
      ret_v3 = cdc_stream(&Cdcc);
  }
  return cdc_unlocks(&Cdcc, ret_v3, AC_CDVDSIF_ID_RESUMES);
}

int cdc_inits(void *buf, unsigned int size, unsigned int bsize)
{
  acInt32 ret;
  int v9;
  int ret_v3;

  if ( Cdcc.lockid )
  {
    ret = 0;
    if ( WaitSema(Cdcc.lockid) )
      ret = 19;
  }
  else
  {
    ret = 17;
  }
  if ( ret )
  {
    Cdcc.error = ret;
    return 0;
  }
  v9 = -16;
  if ( Cdcc.fno == AC_CDVDSIF_ID_NOP )
  {
    v9 = 18;
    Cdcc.fno = AC_CDVDSIF_ID_INITS;
    Cdcc.stat = 0;
    if ( Cdcc.syncid > 0 )
      ClearEventFlag(Cdcc.syncid, 0);
  }
  ret_v3 = v9;
  if ( v9 > 0 )
  {
    ret_v3 = 1;
    Cdcc.st.buf = (acUint8 *)buf;
    Cdcc.st.size = size;
    Cdcc.st.bsize = bsize;
    Cdcc.st.head = 0;
    Cdcc.st.tail = 0;
    Cdcc.st.lsn = 0;
    Cdcc.st.reqlsn = 0;
    Cdcc.st.flag = 0;
  }
  return cdc_unlock(&Cdcc, ret_v3, AC_CDVDSIF_ID_INITS);
}

int cdc_seeks(unsigned int lsn)
{
  acInt32 v2;
  int v5;
  int ret;
  acSpl state;

  v2 = 17;
  if ( Cdcc.lockid )
  {
    v2 = 0;
    if ( WaitSema(Cdcc.lockid) )
      v2 = 19;
  }
  if ( v2 )
  {
    Cdcc.error = v2;
    return 0;
  }
  v5 = 27;
  if ( Cdcc.fno != AC_CDVDSIF_ID_STREAM )
  {
    v5 = -16;
    if ( Cdcc.fno == AC_CDVDSIF_ID_NOP )
    {
      v5 = 20;
      Cdcc.fno = AC_CDVDSIF_ID_SEEKS;
      if ( Cdcc.syncid > 0 )
        ClearEventFlag(Cdcc.syncid, 0);
    }
  }
  ret = v5;
  if ( v5 > 0 )
  {
    CpuSuspendIntr(&state);
    Cdcc.st.reqlsn = lsn;
    Cdcc.st.flag |= 0x10u;
    CpuResumeIntr(state);
    ret = 1;
  }
  return cdc_unlocks(&Cdcc, ret, AC_CDVDSIF_ID_SEEKS);
}

int cdc_stats()
{
  acInt32 v0;
  int ret;
  acSpl state;

  v0 = 17;
  if ( Cdcc.lockid )
  {
    v0 = 0;
    if ( WaitSema(Cdcc.lockid) )
      v0 = 19;
  }
  if ( v0 )
  {
    Cdcc.error = v0;
    return 0;
  }
  ret = 27;
  if ( Cdcc.fno != AC_CDVDSIF_ID_STREAM )
  {
    ret = -16;
    if ( Cdcc.fno == AC_CDVDSIF_ID_NOP )
    {
      ret = 22;
      Cdcc.fno = AC_CDVDSIF_ID_STATS;
      if ( Cdcc.syncid > 0 )
        ClearEventFlag(Cdcc.syncid, 0);
    }
  }
  if ( ret > 0 )
  {
    CpuSuspendIntr(&state);
    ret = Cdcc.st.size;
    if ( Cdcc.st.head == Cdcc.st.tail )
    {
      if ( (Cdcc.st.flag & 4) == 0 )
        ret = 0;
    }
    else if ( Cdcc.st.head < Cdcc.st.tail )
    {
      ret = Cdcc.st.size + Cdcc.st.head - Cdcc.st.tail;
    }
    else
    {
      ret = Cdcc.st.head - Cdcc.st.tail;
    }
    CpuResumeIntr(state);
  }
  if ( Cdcc.fno == AC_CDVDSIF_ID_STATS )
  {
    Cdcc.fno = AC_CDVDSIF_ID_NOP;
    if ( Cdcc.syncid > 0 )
      SetEventFlag(Cdcc.syncid, 3u);
  }
  if ( Cdcc.lockid > 0 )
  {
    SignalSema(Cdcc.lockid);
  }
  if ( ret < 0 )
    return 0;
  return ret;
}

int cdc_module_status()
{
  int ret;
  int state;

  CpuSuspendIntr(&state);
  if ( Cdcc.fno )
    ret = 2;
  else
    ret = Cdcc.lockid > 0;
  CpuResumeIntr(state);
  return ret;
}

int cdc_module_start(int argc, char **argv)
{
  int ret;
  int index;
  int v6;
  int ret_v4;
  int ret_v5;
  int lockid;
  acUint8 *buf_v7;
  int syncid;
  acUint8 *buf;

  (void)argc;
  (void)argv;
  ret = cdc_module_status();
  index = 0;
  if ( ret )
  {
    return ret;
  }
  v6 = 0;
  ret_v4 = 0;
  while ( (unsigned int)index < 3 )
  {
    int ret_v3;

    ret_v3 = mods_120[v6].status();
    ret_v4 = ret_v3;
    if ( ret_v3 <= 0 )
    {
      if ( !ret_v3 )
        ret_v4 = mods_120[v6].start(argc, argv);
    }
    else
    {
      ret_v4 = 0;
    }
    if ( ret_v4 < 0 )
    {
      printf("cdc:init_modules:S:%d: error %d\n", index, ret_v4);
      break;
    }
    ++index;
    ++v6;
  }
  ret_v5 = ret_v4;
  if ( ret_v5 <= 0 )
  {
    return ret_v5;
  }
  lockid = cdc_sem_alloc();
  syncid = cdc_eve_alloc();
  buf_v7 = (acUint8 *)AllocSysMemory(0, 0x10000, 0);
  buf = buf_v7;
  if ( lockid > 0 )
  {
    if ( buf_v7 )
    {
      memset(&Cdcc, 0, sizeof(Cdcc));
      Cdcc.syncid = syncid;
      Cdcc.lockid = lockid;
      Cdcc.buf = buf;
      Cdcc.cdsize = 0;
      Cdcc.rd.spindle = -1;
      Cdcc.rd.maxspeed = 0;
      if ( syncid > 0 )
        SetEventFlag(syncid, 3u);
      return ret_v5;
    }
    DeleteSema(lockid);
  }
  if ( syncid > 0 )
    DeleteEventFlag(syncid);
  if ( buf )
  {
    FreeSysMemory(buf);
  }
  return -6;
}

int cdc_module_stop()
{
  int ret;
  int lockid;
  int i;
  int lockid_v6;
  u32 pattern;

  ret = cdc_module_status();
  if ( ret == 0 )
  {
    return 0;
  }
  lockid = Cdcc.lockid;
  if ( Cdcc.lockid <= 0 )
    return 0;
  cdc_stops();
  WaitSema(lockid);
  pattern = 1;
  if ( Cdcc.syncid > 0 )
    WaitEventFlag(Cdcc.syncid, 1u, 1, &pattern);
  if ( Cdcc.syncid > 0 )
    DeleteEventFlag(Cdcc.syncid);
  if ( Cdcc.buf )
    FreeSysMemory(Cdcc.buf);
  memset(&Cdcc, 0, sizeof(Cdcc));
  SignalSema(lockid);
  DeleteSema(lockid);
  for ( i = 2; ; --i )
  {
    int ret_v5;

    ret_v5 = mods_120[i].status();
    lockid_v6 = ret_v5;
    if ( ret_v5 < 0 )
    {
      lockid_v6 = 0;
    }
    if ( ret_v5 > 0 )
    {
      lockid_v6 = mods_120[i].stop();
      if ( lockid_v6 < 0 )
      {
        printf("cdc:init_modules:E:%d: error %d\n", i, lockid_v6);
        return lockid_v6;
      }
    }
  }
  return lockid_v6;
}

int cdc_module_restart(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  return -88;
}

// cdi.o

sceCdCBFunc sceCdCallback(sceCdCBFunc func)
{
  sceCdCBFunc result;

  result = (sceCdCBFunc)Cdic.done;
  Cdic.done = (cdc_done_t)func;
  return (sceCdCBFunc)result;
}

int sceCdBreak()
{
  return 0;
}

int sceCdDiskReady(int mode)
{
  return cdc_ready(mode);
}

int sceCdGetDiskType()
{
  return cdc_medium();
}

int sceCdGetError()
{
  return cdc_error();
}

u32 sceCdGetReadPos(void)
{
  return cdc_getpos() / 16;
}

static int cdi_xfer(void *dst, void *src, int len, enum cdc_xfer_dir dir)
{
  if ( dir )
    memcpy(dst, src, len);
  return len;
}

int sceCdGetToc(unsigned char *toc)
{
  if ( !toc )
    return cdc_seterrno(34);
  return cdc_readtoc(toc, cdi_xfer);
}

int sceCdInit(int mode)
{
  if ( mode < 0 )
    return 0;
  if ( mode >= 2 )
    return mode == 5 && cdc_module_stop() >= 0;
  if ( cdc_module_status() > 0 && cdc_module_stop() < 0 )
  {
    return 0;
  }
  if ( cdc_module_start(1, argv_20) < 0 )
  {
    return 0;
  }
  memset(&Cdic, 0, sizeof(Cdic));
  if ( !mode )
  {
    cdc_ready(0);
  }
  return 1;
}

int sceCdMmode(int media)
{
  (void)media;

  return 1;
}

int sceCdPause()
{
  return cdc_pause(Cdic.done);
}

int sceCdRead(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode)
{
  if ( !mode || !buffer || ((uiptr)buffer & 3) != 0 )
  {
    return cdc_seterrno(34);
  }
  if ( !sectors )
    return cdc_seterrno(0);
  return cdc_read(lbn, buffer, sectors, mode, 0, Cdic.done);
}

int sceCdSync(int mode)
{
  return cdc_sync(mode != 0);
}

int sceCdSearchFile(sceCdlFILE *file, const char *name)
{
  int namlen;

  namlen = 0;
  if ( file && name )
  {
    const char *v3;

    v3 = name;
    while ( 1 )
    {
      if ( *v3 == 0 )
        break;
      v3 = &name[++namlen];
      if ( namlen >= 1024 )
      {
        break;
      }
    }
    if ( namlen >= 1024 )
      namlen = 0;
  }
  if ( !namlen )
    return cdc_seterrno(34);
  return cdc_lookup(file, name, namlen, cdi_xfer);
}

int sceCdSeek(u32 lbn)
{
  return cdc_seek(lbn, Cdic.done);
}

int sceCdStandby()
{
  return cdc_standby(Cdic.done);
}

int sceCdStatus()
{
  return cdc_stat();
}

int sceCdStop()
{
  return cdc_stop(Cdic.done);
}

int sceCdTrayReq(int param, u32 *traychk)
{
  return cdc_tray(param, traychk);
}

int sceCdStInit(u32 bufmax, u32 bankmax, void *buffer)
{
  unsigned int v4;

  if ( !bufmax || !bankmax || !buffer || ((uiptr)buffer & 3) != 0 )
    return cdc_seterrno(34);
  v4 = bufmax / bankmax;
  if ( !(bufmax / bankmax) )
    v4 = 1;
  return cdc_inits((void *)buffer, bufmax, v4);
}

int sceCdStRead(u32 sectors, u32 *buffer, u32 mode, u32 *error)
{
  if ( mode >= 2 )
    buffer = 0;
  if ( !buffer || ((uiptr)buffer & 3) != 0 || !error )
  {
    if ( error )
      *error = 34;
    return cdc_seterrno(34);
  }
  if ( !sectors )
  {
    *error = 0;
    return 0;
  }
  return cdc_reads(buffer, sectors, mode, (int *)error, cdc_xfer);
}

int sceCdStSeek(u32 lbn)
{
  return cdc_seeks(lbn);
}

int sceCdStStart(u32 lbn, sceCdRMode *mode)
{
  if ( !mode )
    return cdc_seterrno(34);
  return cdc_starts(lbn, mode);
}

int sceCdStStat()
{
  return cdc_stats();
}

int sceCdStStop()
{
  return cdc_stops();
}

int sceCdStPause()
{
  return cdc_pauses();
}

int sceCdStResume()
{
  return cdc_resumes();
}

// cddrv.o

static int cddrv_adddrv(iop_device_t *drv)
{
  (void)drv;

  return 0;
}

static int cddrv_deldrv(iop_device_t *drv)
{
  (void)drv;

  return 0;
}

static int cddrv_open(iop_file_t *io, const char *name, int flg)
{
  int ret;
  struct cdfs_file *v9;
  struct cdfs_file *file;
  acUint32 d_size;
  struct cdfs_dirent dirent;

  ret = 1;
  while ( ret > 0 )
  {
    int ret_v2;

    if ( io->unit )
    {
      return -6;
    }
    if ( flg != 1 )
    {
      return -22;
    }
    ret_v2 = cdfs_lookup(&dirent, name, strlen(name));
    if ( ret_v2 >= 0 )
    {
      break;
    }
    ret = cdfs_recover(ret_v2);
  }
  if ( (dirent.d_ftype & 2) != 0 )
  {
    return -21;
  }
  v9 = (struct cdfs_file *)AllocSysMemory(1, 16, 0);
  file = v9;
  if ( !v9 )
  {
    return -12;
  }
  io->privdata = v9;
  v9->f_lsn = dirent.d_lsn;
  d_size = dirent.d_size;
  file->f_pos = 0;
  file->f_size = d_size;
  return 0;
}

static int cddrv_close(iop_file_t *io)
{
  void *ptr;

  ptr = io->privdata;
  io->privdata = 0;
  if ( ptr )
    FreeSysMemory(ptr);
  return 0;
}

static int cddrv_read(iop_file_t *io, void *buf, int cnt)
{
  if ( !buf || !cnt )
    return 0;
  return cdfs_read((struct cdfs_file *)io->privdata, buf, cnt);
}

static int cddrv_write(iop_file_t *io, void *buf, int cnt)
{
  (void)io;
  (void)buf;
  (void)cnt;

  return -30;
}

static int cddrv_lseek(iop_file_t *io, int offset, int whence)
{
  struct cdfs_file *file;
  acUint32 size;

  file = (struct cdfs_file *)io->privdata;
  size = file->f_size;
  if ( whence == 1 )
  {
    offset += file->f_pos;
  }
  else if ( whence == 2 )
  {
    offset += size;
  }
  if ( size < (unsigned int)offset )
    offset = file->f_size;
  file->f_pos = offset;
  return offset;
}

static int cddrv_ioctl(iop_file_t *io, int cmd, void *arg)
{
  (void)io;
  (void)cmd;
  (void)arg;

  return -22;
}

static int cddrv_dummy()
{
  return -22;
}

int cddrv_module_start(int argc, char **argv)
{
  int v2;
  int v3;

  (void)argc;
  (void)argv;
  v2 = AddDrv(&Cddrv);
  v3 = 0;
  if ( v2 < 0 )
    return -16;
  return v3;
}

int cddrv_module_stop()
{
  int v0;
  int v1;

  v0 = DelDrv(Cddrv.name);
  v1 = 0;
  if ( v0 < 0 )
    return -16;
  return v1;
}

int cddrv_module_restart(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  return -88;
}

int cddrv_module_status()
{
  return 0;
}

// cdfs.o

static void cdfs_reset(struct cdfs_softc *cdfsc)
{
  cdfsc->all = 0;
  cdfsc->ptable = 0;
  cdfsc->ptnum = 0;
  cdfsc->rootlsn = 0;
  cdfsc->rootsize = 0;
  cdfsc->rootidx = -1;
  cdfsc->dcache = 0;
  cdfsc->dclsn = 0;
  cdfsc->dcsize = 0;
  cdfsc->pcache = 0;
  cdfsc->pcsize = 0;
}

static int cdfs_path_init(struct cdfs_ptable *ptable, struct iso9660_path *path, unsigned int size)
{
  int count;

  for ( count = 0; size; ++count )
  {
    unsigned int v4;

    v4 = ((path->name_len[0] | (path->name_len[1] << 8)) + 1) & 0xFFFFFFFE;
    if ( ptable )
    {
      ptable->path = path;
      ptable->size = 0;
      ++ptable;
    }
    size = size - 8 - v4;
    path = (struct iso9660_path *)((char *)path + v4 + 8);
  }
  return count;
}

static void cdfs_ready_done(struct acd *acd, const struct cdfs_softc *arg, int ret)
{
  int flg;

  flg = 0;
  if ( ret >= -255 )
  {
    flg = 1;
  }
  else
  {
    int asc;
    int delay;

    asc = (acUint16)-(ret & 0xFFFF);
    if ( -ret >> 16 == 6 )
    {
      delay = 0;
      if ( asc == 10496 )
        delay = acd_delay();
    }
    else
    {
      delay = -1;
      if ( asc == 1025 )
        delay = 1000000;
    }
    if ( delay < 0 )
      flg = 1;
    else
    {
      if ( delay > 0 )
        DelayThread(delay);
      if ( acd_ready(acd) < 0 )
      {
        flg = 1;
      }
    }
  }
  if ( flg )
  {
    if ( arg->semid > 0 )
      SignalSema(arg->semid);
  }
}

static void cdfs_detach(struct cdfs_softc *cdfsc)
{
  void *ptr;
  void *ptr_v1;
  void *ptr_v2;

  ptr = cdfsc->ptable;
  if ( ptr )
    FreeSysMemory(ptr);
  ptr_v1 = cdfsc->pcache;
  if ( ptr_v1 )
    FreeSysMemory(ptr_v1);
  ptr_v2 = cdfsc->dcache;
  if ( ptr_v2 )
    FreeSysMemory(ptr_v2);
  cdfs_reset(cdfsc);
}

static int cdfs_attach(struct cdfs_softc *cdfsc, struct acd *acd, int remount)
{
  int semid;
  int active;
  int active_v3;
  int active_v6;
  int ret;
  struct iso9660_path *pcache_v17;
  struct cdfs_ptable *ptable_v19;

  semid = cdfsc->semid;
  if ( semid <= 0 )
    active = -9;
  else
    active = WaitSema(semid);
  if ( active >= 0 )
  {
    acd_setup((struct acd *)cdfsc->buf, (acd_done_t)cdfs_ready_done, cdfsc, -5000000);
    if ( acd_ready((struct acd *)cdfsc->buf) < 0 )
    {
      if ( cdfsc->semid > 0 )
        SignalSema(cdfsc->semid);
    }
  }
  active_v3 = -9;
  if ( cdfsc->semid > 0 )
    active_v3 = WaitSema(cdfsc->semid);
  if ( active_v3 < 0 )
  {
    return -6;
  }
  active_v6 = cdfsc->all;
  if ( remount )
  {
    if ( active_v6 != 0 )
    {
      cdfs_detach(cdfsc);
      active_v6 = 0;
    }
  }
  ret = -16;
  if ( active_v6 == 0 )
  {
    acUint8 *buf;
    acd_lsn_t v17;

    buf = cdfsc->buf;
    v17 = 16;
    while ( 1 )
    {
      int active_v12;

      FlushDcache();
      active_v12 = acd_read(acd, v17, buf, 1);
      ret = active_v12;
      if ( active_v12 < 0 )
      {
        printf("cdfs:super:read: error %d\n", active_v12);
        break;
      }
      if ( !strncmp((const char *)buf + 1, "CD001", 5u) )
      {
        int active_v13;

        active_v13 = *buf;
        if ( active_v13 == 255 )
        {
          printf("cdfs:%u:invalid descriptor\n", (unsigned int)v17);
          ret = -6;
          break;
        }
        if ( active_v13 == 1 )
        {
          cdfsc->all = *((acUint32 *)buf + 20);
          cdfsc->rootlsn = *(acUint32 *)(buf + 158);
          cdfsc->rootsize = *(acUint32 *)(buf + 166);
          ret = 0;
          break;
        }
      }
      ++v17;
      ret = -6;
      if ( v17 >= 0x64 )
        break;
    }
    if ( !ret )
    {
      int ret_v14;
      acd_lsn_t lsn;
      int ret_v16;

      ret_v14 = *(acUint32 *)&cdfsc->buf[132];
      lsn = *(acUint32 *)&cdfsc->buf[140];
      cdfsc->pcsize = ret_v14;
      ret_v16 = (unsigned int)(ret_v14 + 2047) >> 11;
      FlushDcache();
      pcache_v17 = (struct iso9660_path *)AllocSysMemory(0, ret_v16 << 11, 0);
      cdfsc->pcache = pcache_v17;
      if ( pcache_v17 == 0 )
      {
        ret = -12;
      }
      else
      {
        ret = acd_read(acd, lsn, pcache_v17, ret_v16);
        if ( ret >= 0 )
        {
          int active_v18;

          active_v18 = cdfs_path_init(0, cdfsc->pcache, cdfsc->pcsize);
          cdfsc->ptnum = active_v18;
          if ( (8 * active_v18 == 0)
            || (ptable_v19 = (struct cdfs_ptable *)AllocSysMemory(0, 8 * active_v18, 0),
                (cdfsc->ptable = ptable_v19) != 0) )
          {
            int n;
            int i;
            struct cdfs_ptable *ptable;
            int active_v24;

            n = cdfs_path_init(cdfsc->ptable, cdfsc->pcache, cdfsc->pcsize);
            i = 0;
            ptable = cdfsc->ptable;
            active_v24 = 0;
            while ( i < n )
            {
              if ( cdfsc->rootlsn == *(acUint32 *)ptable[active_v24].path->extent )
              {
                ptable[active_v24].size = cdfsc->rootsize;
                cdfsc->rootidx = i;
                break;
              }
              i++;
              active_v24 = i;
            }
            ret = 0;
          }
          else
          {
            void *ptr;

            printf("accdvd:cdfs:path_read: malloc failed\n");
            ptr = cdfsc->pcache;
            if ( ptr )
              FreeSysMemory(ptr);
            cdfsc->pcache = 0;
            ret = -12;
          }
        }
      }
    }
  }
  if ( cdfsc->semid > 0 )
  {
    SignalSema(cdfsc->semid);
  }
  return ret;
}

int cdfs_mount()
{
  struct acd v1;

  acd_setup(&v1, 0, 0, 5000000);
  return cdfs_attach(&Cdfsc, &v1, 0);
}

int cdfs_umount()
{
  int ret;

  if ( Cdfsc.semid <= 0 )
    return -9;
  ret = WaitSema(Cdfsc.semid);
  if ( ret < 0 )
  {
    return ret;
  }
  cdfs_detach(&Cdfsc);
  if ( Cdfsc.semid > 0 )
  {
    SignalSema(Cdfsc.semid);
  }
  return 0;
}

int cdfs_recover(int ret)
{
  int v1;
  struct acd acd_data;

  v1 = -ret;
  while ( 1 )
  {
    int v3;

    if ( !(v1 >= 255 && (v1 >> 16 == 6 || (v1 & 0xFFFF) == 1025 || (v1 & 0xFFFF) == 10240)) )
      return -5;
    v3 = cdfs_attach(&Cdfsc, &acd_data, 1);
    v1 = -v3;
    if ( v3 >= 0 )
      return 1;
  }
}

int cdfs_lookup(struct cdfs_dirent *result, const char *path, int pathlen)
{
  const char *v9;
  char *dirent;
  int len;
  int idx;
  int namlen;
  struct iso9660_dirent *name_v8;
  int namlen_v9;
  int idx_v10;
  int high;
  int low;
  int ret;
  int v21;
  struct iso9660_path *path_v16;
  int v23;
  int ret_v18;
  int len_v19;
  unsigned char *s2;
  int idx_v21;
  struct iso9660_dirent *dirent_v22;
  int len_v23;
  struct iso9660_path *path_v24;
  unsigned int dcsize;
  unsigned char *pt;
  unsigned int v33;
  unsigned int lsn;
  signed int size_v29;
  int ret_v30;
  int ret_v31;
  struct iso9660_dirent *dirent_v32;
  int idx_v33;
  int v40;
  unsigned int n;
  struct iso9660_path *path_v36;
  void *dirent_v37;
  struct iso9660_dirent *dirent_v38;
  int n_v39;
  int i_v40;
  int rest;
  int v48;
  const acUint8 *len_v43;
  int idx_v44;
  unsigned char *s2_v45;
  int v52;
  int v53;
  char *path_v48;
  int v55;
  int v57;
  unsigned int t0;
  size_t d_namlen;
  struct acd acd_data;
  struct acd *acd;

  acd_setup(&acd_data, 0, 0, 5000000);
  while ( 1 )
  {
    int v6;
    int v8;

    v6 = -9;
    if ( Cdfsc.semid > 0 )
      v6 = WaitSema(Cdfsc.semid);
    if ( v6 < 0 )
      return -6;
    if ( Cdfsc.all )
    {
      int ret_v57;

      acd = &acd_data;
      ret_v57 = -2;
      v9 = path + 1;
      if ( pathlen <= 0 || *path == 92 )
      {
        len = pathlen - 1;
        idx = Cdfsc.rootidx;
        while ( 1 )
        {
          namlen = len;
          name_v8 = (struct iso9660_dirent *)v9;
          while ( len > 0 )
          {
            if ( *v9 == 92 )
              break;
            --len;
            ++v9;
          }
          if ( len <= 0 )
          {
            path_v24 = (struct iso9660_path *)(8 * idx);
            dirent = 0;
            if ( namlen )
            {
              dcsize = Cdfsc.dcsize;
              pt = &path_v24->name_len[(unsigned int)Cdfsc.ptable];
              v33 = *(acUint32 *)&path_v24->extent[(unsigned int)Cdfsc.ptable + 2];
              lsn = *(acUint32 *)(*(acUint32 *)pt + 2);
              FlushDcache();
              size_v29 = 0;
              if ( lsn != Cdfsc.dclsn )
              {
                ret_v30 = acd_read(acd, lsn, Cdfsc.buf, 1);
                if ( ret_v30 < 0 )
                {
                  Cdfsc.dclsn = 0;
                }
                else
                {
                  ret_v31 = v33 - 1;
                  if ( !v33 )
                  {
                    dirent_v32 = (struct iso9660_dirent *)Cdfsc.buf;
                    idx_v33 = 2048;
                    v33 = 0;
                    while ( idx_v33 )
                    {
                      v40 = dirent_v32->length[0];
                      if ( !dirent_v32->length[0] )
                        break;
                      if ( dirent_v32->name_len[0] == 1 && !dirent_v32->name[0] )
                      {
                        v33 = *(acUint32 *)dirent_v32->size;
                        break;
                      }
                      idx_v33 -= v40;
                      dirent_v32 = (struct iso9660_dirent *)((char *)dirent_v32 + v40);
                    }
                    *((acUint32 *)pt + 1) = v33;
                    ret_v31 = v33 - 1;
                  }
                  if ( !v33 )
                  {
                    ret_v30 = 0;
                  }
                  else
                  {
                    n = (unsigned int)ret_v31 >> 11;
                    if ( dcsize >= (unsigned int)ret_v31 >> 11 )
                    {
                      dirent_v37 = Cdfsc.dcache;
                    }
                    else
                    {
                      if ( Cdfsc.dcache )
                        FreeSysMemory(Cdfsc.dcache);
                      path_v36 = (struct iso9660_path *)AllocSysMemory(0, n << 11, 0);
                      dirent_v37 = path_v36;
                      Cdfsc.dcache = (struct iso9660_dirent *)path_v36;
                      if ( path_v36 )
                        Cdfsc.dcsize = n;
                      else
                        Cdfsc.dcsize = 0;
                      if ( !path_v36 )
                        lsn = 0;
                    }
                    ret_v30 = 0;
                    if ( lsn )
                    {
                      if ( n )
                      {
                        ret_v30 = v33;
                        if ( acd_read(acd, lsn + 1, dirent_v37, n) < 0 )
                        {
                          lsn = 0;
                          ret_v30 = 0;
                        }
                      }
                      else
                      {
                        ret_v30 = v33;
                      }
                    }
                    Cdfsc.dclsn = lsn;
                  }
                }
                size_v29 = ret_v30;
              }
              dirent_v38 = (struct iso9660_dirent *)Cdfsc.buf;
              if ( size_v29 >= 0 )
              {
                n_v39 = 1;
                for ( i_v40 = 1; i_v40 >= 0; --i_v40 )
                {
                  while ( 1 )
                  {
                    --n_v39;
                    rest = 2048;
                    if ( n_v39 < 0 )
                      break;
                    if ( size_v29 < 2048 )
                      rest = size_v29;
                    size_v29 -= rest;
                    while ( rest > 0 )
                    {
                      v48 = dirent_v38->length[0];
                      if ( !v48 )
                      {
                        break;
                      }
                      if ( namlen == dirent_v38->name_len[0] )
                      {
                        len_v43 = (acUint8 *)name_v8;
                        idx_v44 = namlen - 1;
                        s2_v45 = dirent_v38->name;
                        while ( idx_v44 >= 0 )
                        {
                          v52 = *len_v43++;
                          v53 = *s2_v45 - v52;
                          if ( *s2_v45++ != v52 )
                            break;
                          idx_v44--;
                        }
                        if ( idx_v44 < 0 )
                        {
                          v53 = 0;
                        }
                        rest -= v48;
                        if ( !v53 )
                        {
                          ret_v57 = 0;
                          path_v48 = (char *)dirent_v38;
                          dirent = path_v48;
                        }
                      }
                      else
                      {
                        rest -= dirent_v38->length[0];
                      }
                      if ( dirent )
                      {
                        break;
                      }
                      dirent_v38 = (struct iso9660_dirent *)((char *)dirent_v38 + v48);
                    }
                    if ( dirent )
                    {
                      break;
                    }
                    dirent_v38 = (struct iso9660_dirent *)((char *)dirent_v38 + rest);
                  }
                  if ( dirent )
                  {
                    break;
                  }
                  dirent_v38 = Cdfsc.dcache;
                  v55 = size_v29 + 2047;
                  if ( size_v29 + 2047 < 0 )
                    v55 = size_v29 + 4094;
                  n_v39 = v55 >> 11;
                }
              }
              else
              {
                ret_v57 = size_v29;
              }
            }
            if ( dirent )
            {
              result->d_lsn = *(acUint32 *)(dirent + 2);
              result->d_size = *(acUint32 *)(dirent + 10);
              result->d_vol = (dirent[28] & 0xFF) | ((dirent[29] & 0xFF) << 8);
              v57 = dirent[32];
              result->d_ftype = dirent[25];
              result->d_namlen = v57;
              t0 = v57 & 0xFF;
              result->d_name[t0] = 0;
              d_namlen = result->d_namlen;
              result->d_time.t_mon = dirent[19];
              result->d_time.t_day = dirent[20];
              result->d_time.t_hour = dirent[21];
              result->d_time.t_padding = 0;
              result->d_time.t_min = dirent[22];
              result->d_time.t_sec = dirent[23];
              result->d_time.t_year = (dirent[18] & 0xFF) + 1900;
              memcpy(result->d_name, dirent + 33, d_namlen);
              ret_v57 = 0;
            }
            break;
          }
          namlen_v9 = namlen - len;
          idx_v10 = idx;
          if ( namlen_v9 && (namlen_v9 != 1 || name_v8->length[0] != 46) )
          {
            if ( namlen_v9 == 2 && name_v8->length[0] == 46 && name_v8->ext_attr_length[0] == 46 )
            {
              idx = (Cdfsc.ptable[idx].path->parent[0] | (Cdfsc.ptable[idx].path->parent[1] << 8)) - 1;
            }
            else
            {
              high = Cdfsc.ptnum;
              low = idx;
              v21 = high;
              for ( ;; )
              {
                ret = low + high;
                if ( low >= v21 )
                {
                  idx = -1;
                  break;
                }
                v21 = ret / 2;
                path_v16 = Cdfsc.ptable[ret / 2].path;
                v23 = path_v16->parent[1] << 8;
                ret_v18 = (path_v16->parent[0] | v23) - 1 - idx_v10;
                if ( (path_v16->parent[0] | v23) - 1 == idx_v10 )
                {
                  len_v19 = path_v16->name_len[0] | (path_v16->name_len[1] << 8);
                  s2 = path_v16->name;
                  if ( namlen_v9 < len_v19 )
                    len_v19 = namlen_v9;
                  idx_v21 = len_v19 - 1;
                  dirent_v22 = name_v8;
                  while ( idx_v21 >= 0 )
                  {
                    len_v23 = dirent_v22->length[0];
                    dirent_v22 = (struct iso9660_dirent *)((char *)dirent_v22 + 1);
                    ret_v18 = *s2 - len_v23;
                    if ( *s2++ != len_v23 )
                      break;
                    idx_v21--;
                  }
                  if ( idx_v21 < 0 )
                  {
                    ret_v18 = 0;
                  }
                }
                if ( ret_v18 < 0 )
                {
                  low = v21 + 1;
                  v21 = high;
                }
                else
                {
                  high = v21;
                  if ( ret_v18 <= 0 )
                  {
                    idx = v21;
                    break;
                  }
                }
              }
            }
          }
          ++v9;
          if ( idx < 0 )
            break;
          --len;
        }
      }
      if ( Cdfsc.semid > 0 )
        SignalSema(Cdfsc.semid);
      return ret_v57;
    }
    if ( Cdfsc.semid > 0 )
      SignalSema(Cdfsc.semid);
    v8 = cdfs_attach(&Cdfsc, &acd_data, 1);
    if ( v8 < 0 )
      return v8;
  }
}

int cdfs_read(struct cdfs_file *file, void *buf, int size)
{
  int ret;
  unsigned int cpos;
  unsigned int f_size;
  unsigned int off;
  unsigned int npos;
  signed int len;
  unsigned int lsn;
  unsigned char *data;
  int rest;
  unsigned int cpos_v14;
  unsigned int npos_v15;
  unsigned int npos_v16;
  unsigned int lsn_v17;
  int len_v18;
  unsigned char *data_v33;
  int rest_v34;
  unsigned int cpos_v35;
  unsigned int npos_v36;
  int len_v37;
  unsigned int lsn_v38;
  int rest_v42;
  struct acd acd_data;

  if ( !Cdfsc.semid )
    return -6;
  acd_setup(&acd_data, 0, 0, 5000000);
  cpos = file->f_pos;
  f_size = file->f_size;
  off = cpos & 0x7FF;
  npos = cpos - (off - 2048);
  if ( (cpos & 0x7FF) == 0 )
  {
    ret = 0;
  }
  else
  {
    if ( cpos + size < f_size )
    {
      f_size = cpos + size;
    }
    len = 2048 - (cpos & 0x7FF);
    if ( f_size < npos )
    {
      npos = f_size;
      len = f_size - cpos;
    }
    lsn = file->f_lsn + (cpos >> 11);
    if ( len <= 0 )
    {
      ret = len;
    }
    else
    {
      int ret_v8;

      ret_v8 = -9;
      if ( Cdfsc.semid > 0 )
        ret_v8 = WaitSema(Cdfsc.semid);
      ret = -6;
      if ( ret_v8 >= 0 )
      {
        int ret_v10;

        ret_v10 = -11;
        if ( Cdfsc.all )
        {
          if ( lsn )
          {
            if ( Cdfsc.dclsn == lsn )
            {
              ret_v10 = 1;
            }
          }
          if ( ret_v10 <= 0 )
          {
            ret_v10 = acd_read(&acd_data, lsn, Cdfsc.buf, 1);
          }
        }
        if ( ret_v10 <= 0 )
        {
          len = ret_v10;
          lsn = 0;
        }
        else
        {
          memcpy(buf, &Cdfsc.buf[off], len);
          file->f_pos = npos;
        }
        Cdfsc.dclsn = lsn;
        if ( Cdfsc.semid > 0 )
          SignalSema(Cdfsc.semid);
        ret = len;
      }
    }
  }
  data = (unsigned char *)buf + ret;
  if ( ret < 0 )
    return ret;
  rest = size - ret;
  cpos_v14 = file->f_pos;
  npos_v15 = cpos_v14 + rest;
  if ( file->f_size < cpos_v14 + rest )
    npos_v15 = file->f_size;
  npos_v16 = npos_v15 - (npos_v15 & 0x7FF);
  lsn_v17 = file->f_lsn + (cpos_v14 >> 11);
  len_v18 = npos_v16 - cpos_v14;
  if ( (int)(npos_v16 - cpos_v14) < 2048 )
  {
    len_v18 = 0;
    ret = len_v18;
  }
  else
  {
    unsigned char *ptr;
    ptr = data;
    if ( ((uiptr)data & 3) == 0 )
    {
      int ret_v32;

      ret_v32 = acd_read(&acd_data, file->f_lsn + (cpos_v14 >> 11), data, len_v18 / 2048);
      if ( ret_v32 <= 0 )
        len_v18 = ret_v32;
      else
        file->f_pos = npos_v16;
      ret = len_v18;
    }
    else
    {
      signed int rest_v20;
      int flg;

      flg = 0;
      rest_v20 = npos_v16 - cpos_v14;
      while ( 1 )
      {
        int ret_v21;
        int ret_v22;

        if ( rest_v20 <= 0 )
        {
          flg = 1;
          break;
        }
        ret_v21 = -9;
        if ( Cdfsc.semid > 0 )
          ret_v21 = WaitSema(Cdfsc.semid);
        ret = -6;
        if ( ret_v21 < 0 )
          break;
        ret_v22 = -11;
        if ( Cdfsc.all )
        {
          if ( lsn_v17 )
          {
            if ( Cdfsc.dclsn == lsn_v17 )
            {
              ret_v22 = 1;
            }
          }
          if ( ret_v22 <= 0 )
          {
            ret_v22 = acd_read(&acd_data, lsn_v17, Cdfsc.buf, 1);
          }
        }
        if ( ret_v22 <= 0 )
        {
          Cdfsc.dclsn = 0;
          len_v18 = ret_v22;
          flg = 1;
          break;
        }
        memcpy(ptr, &Cdfsc, sizeof(Cdfsc));
        ptr += 2048;
        rest_v20 -= 2048;
        Cdfsc.dclsn = lsn_v17++;
        if ( Cdfsc.semid > 0 )
          SignalSema(Cdfsc.semid);
      }
      if (flg)
      {
        ret = len_v18;
        if ( !rest_v20 )
          file->f_pos = npos_v16;
      }
    }
  }
  data_v33 = &data[ret];
  if ( ret < 0 )
    return ret;
  rest_v34 = rest - ret;
  cpos_v35 = file->f_pos;
  npos_v36 = cpos_v35 + rest_v34;
  if ( file->f_size < cpos_v35 + rest_v34 )
    npos_v36 = file->f_size;
  len_v37 = npos_v36 - cpos_v35;
  lsn_v38 = file->f_lsn + (cpos_v35 >> 11);
  ret = len_v37;
  if ( (int)(npos_v36 - cpos_v35) > 0 )
  {
    int ret_v39;

    ret_v39 = -9;
    if ( Cdfsc.semid > 0 )
      ret_v39 = WaitSema(Cdfsc.semid);
    if ( ret_v39 < 0 )
    {
      ret = -6;
    }
    else
    {
      int ret_v40;

      ret_v40 = -11;
      if ( Cdfsc.all )
      {
        if ( lsn_v38 )
        {
          if ( Cdfsc.dclsn == lsn_v38 )
          {
            ret_v40 = 1;
          }
        }
        if ( ret_v40 <= 0 )
        {
          ret_v40 = acd_read(&acd_data, lsn_v38, Cdfsc.buf, 1);
        }
      }
      if ( ret_v40 <= 0 )
      {
        len_v37 = ret_v40;
        lsn_v38 = 0;
      }
      else
      {
        memcpy(data_v33, Cdfsc.buf, len_v37);
        file->f_pos = npos_v36;
      }
      Cdfsc.dclsn = lsn_v38;
      if ( Cdfsc.semid > 0 )
        SignalSema(Cdfsc.semid);
      ret = len_v37;
    }
  }
  rest_v42 = rest_v34 - ret;
  if ( ret >= 0 )
    return size - rest_v42;
  return ret;
}

int cdfs_module_status()
{
  return Cdfsc.semid > 0;
}

int cdfs_module_start(int argc, char **argv)
{
  int ret;
  int v4;
  acInt32 v5;
  iop_sema_t param;

  (void)argc;
  (void)argv;
  ret = cdfs_module_status();
  if ( ret != 0 )
  {
    return ret;
  }
  param.attr = 0;
  param.initial = 1;
  param.max = 1;
  param.option = 0;
  v4 = CreateSema(&param);
  v5 = v4;
  if ( v4 <= 0 )
    printf("accdvd:cdfs:sem_alloc: error %d\n", v4);
  if ( v5 <= 0 )
    return -6;
  Cdfsc.semid = v5;
  cdfs_reset(&Cdfsc);
  return 0;
}

int cdfs_module_stop()
{
  int ret;
  int semid;

  ret = cdfs_module_status();
  if ( ret == 0 )
  {
    return ret;
  }
  semid = Cdfsc.semid;
  if ( Cdfsc.semid )
  {
    if ( Cdfsc.semid > 0 )
      WaitSema(Cdfsc.semid);
    cdfs_detach(&Cdfsc);
    Cdfsc.semid = 0;
    if ( semid > 0 )
      SignalSema(semid);
    DeleteSema(semid);
  }
  return 0;
}

int cdfs_module_restart(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  return -88;
}
