
#include "irx_imports.h"

IRX_ID("S147CTRL", 2, 8);

struct watchdog_info_
{
  int g_watchdog_started;
  iop_sys_clock_t g_watchdog_clock;
};

struct s147_dev9_mem_mmio_
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
};

struct s147link_dev9_mem_mmio_
{
  vu8 m_pad00;
  vu8 m_unk01;
  vu8 m_pad02;
  vu8 m_unk03;
  vu8 m_pad04;
  vu8 m_node_unk05;
  vu8 m_pad06;
  vu8 m_unk07;
  vu8 m_pad08;
  vu8 m_unk09;
  vu8 m_pad0A;
  vu8 m_pad0B;
  vu8 m_pad0C;
  vu8 m_unk0D;
  vu8 m_pad0E;
  vu8 m_pad0F;
  vu8 m_pad10;
  vu8 m_pad11;
  vu8 m_stsH_unk12;
  vu8 m_stsL_unk13;
  vu8 m_unk14;
  vu8 m_unk15;
  vu8 m_pad16;
  vu8 m_unk17;
  vu8 m_pad18;
  vu8 m_pad19;
  vu8 m_pad1A;
  vu8 m_pad1B;
  vu8 m_unk1C;
  vu8 m_unk1D;
  vu8 m_rxfc_hi_unk1E;
  vu8 m_rxfc_lo_unk1F;
  vu8 m_pad20;
  vu8 m_unk21;
  vu8 m_unk22;
  vu8 m_unk23;
  vu8 m_unk24;
  vu8 m_unk25;
  vu8 m_pad26;
  vu8 m_pad27;
  vu8 m_unk28;
  vu8 m_unk29;
  vu8 m_pad2A;
  vu8 m_maxnode_unk2B;
  vu8 m_pad2C;
  vu8 m_mynode_unk2D;
  vu8 m_pad2E;
  vu8 m_unk2F;
  vu8 m_pad30;
  vu8 m_unk31;
  vu8 m_pad32;
  vu8 m_pad33;
  vu8 m_watchdog_flag_unk34;
};

struct sram_drv_privdata_
{
  u32 m_curpos;
  u32 m_maxpos;
};


//-------------------------------------------------------------------------
// Function declarations

static void setup_ac_delay_regs(void);
static int setup_ctrl_ioman_drv(const char *devpfx, const char *devname);
static unsigned int watchdog_alarm_cb(void *userdata);
static int ctrl_drv_op_nulldev(void);
static int ctrl_drv_op_init(iop_device_t *dev);
static int ctrl_drv_op_deinit(iop_device_t *dev);
static int ctrl_drv_op_open(iop_file_t *f, const char *name, int flags);
static int ctrl_drv_op_close(iop_file_t *f);
static int ctrl_drv_op_read(iop_file_t *f, void *ptr, int size);
static int ctrl_drv_op_write(iop_file_t *f, void *ptr, int size);
static int ctrl_drv_op_lseek(iop_file_t *f, int offset, int mode);
static int create_ctrl_sema(void);
static int ctrl_do_rtc_read(u32 *rtcbuf);
static int ctrl_do_rtc_read_inner(int flgcnt, int flgmsk);
static int ctrl_do_rtc_write(u32 *rtcbuf);
static void ctrl_do_rtc_write_inner(int inflg, int flgcnt, int flgmsk);
static int setup_sram_ioman_drv(const char *devpfx, const char *devname);
static int sram_drv_op_nulldev(void);
static int sram_drv_op_init(iop_device_t *dev);
static int sram_drv_op_deinit(iop_device_t *dev);
static int sram_drv_op_open(iop_file_t *f, const char *name, int flags);
static int sram_drv_op_close(iop_file_t *f);
static int sram_drv_op_read(iop_file_t *f, void *ptr, int size);
static int sram_drv_op_write(iop_file_t *f, void *ptr, int size);
static int sram_drv_op_lseek(iop_file_t *f, int offset, int mode);
static int do_rpc_start1(void);
static void rpc_thread1(void *userdata);
static void *rpc_1470000_handler(int fno, void *buffer, int length);
static void *rpc_1470001_handler(int fno, void *buffer, int length);
static void *rpc_1470002_handler(int fno, void *buffer, int length);
static void *rpc_1470003_handler(int fno, void *buffer, int length);
static int do_rpc_start2(void);
static void rpc_thread2(void *userdata);
static void *rpc_1470200_handler(int fno, void *buffer, int length);
static void *rpc_1470201_handler(int fno, void *buffer, int length);

//-------------------------------------------------------------------------
// Data declarations

iop_device_ops_t g_ops_ctrl_ioman =
{
  &ctrl_drv_op_init,
  &ctrl_drv_op_deinit,
  (void *)&ctrl_drv_op_nulldev,
  &ctrl_drv_op_open,
  &ctrl_drv_op_close,
  &ctrl_drv_op_read,
  &ctrl_drv_op_write,
  &ctrl_drv_op_lseek,
  (void *)&ctrl_drv_op_nulldev,
  (void *)&ctrl_drv_op_nulldev,
  (void *)&ctrl_drv_op_nulldev,
  (void *)&ctrl_drv_op_nulldev,
  (void *)&ctrl_drv_op_nulldev,
  (void *)&ctrl_drv_op_nulldev,
  (void *)&ctrl_drv_op_nulldev,
  (void *)&ctrl_drv_op_nulldev,
  (void *)&ctrl_drv_op_nulldev
}; // weak
int g_rpc_started = 0; // weak
int g_watchdog_count_1 = 0; // weak
char g_watchdog_flag_1 = '\x01'; // weak
u32 g_max_timer_counter = 0; // weak
iop_device_ops_t g_ops_sram_ioman =
{
  &sram_drv_op_init,
  &sram_drv_op_deinit,
  (void *)&sram_drv_op_nulldev,
  &sram_drv_op_open,
  &sram_drv_op_close,
  &sram_drv_op_read,
  &sram_drv_op_write,
  &sram_drv_op_lseek,
  (void *)&sram_drv_op_nulldev,
  (void *)&sram_drv_op_nulldev,
  (void *)&sram_drv_op_nulldev,
  (void *)&sram_drv_op_nulldev,
  (void *)&sram_drv_op_nulldev,
  (void *)&sram_drv_op_nulldev,
  (void *)&sram_drv_op_nulldev,
  (void *)&sram_drv_op_nulldev,
  (void *)&sram_drv_op_nulldev,
}; // weak
iop_device_t g_drv_ctrl_ioman; // idb
int g_rtc_flag; // weak
int g_timer_id; // idb
iop_sema_t g_ctrl_sema_param; // idb
int g_ctrl_sema_id; // idb
iop_device_t g_drv_sram_ioman; // idb
int g_rpc1_buf[8]; // weak
int g_rpc2_buf[260]; // weak
struct watchdog_info_ g_watchdog_info; // weak
struct s147_dev9_mem_mmio_ s147_dev9_mem_mmio; // weak
struct s147link_dev9_mem_mmio_ s147link_dev9_mem_mmio; // weak


//----- (00400000) --------------------------------------------------------
int _start(int ac, char **av)
{
  (void)ac;
  (void)av;
  Kprintf("\n");
  Kprintf("s147ctrl.irx: System147 Control/SRAM Driver v%d.%d\n", 2, 8);
  setup_ac_delay_regs();
  if ( setup_ctrl_ioman_drv("ctrl", "Ctrl") < 0 )
  {
    Kprintf("s147ctrl.irx: Ctrl initialize failed\n");
    return 1;
  }
  if ( setup_sram_ioman_drv("sram", "SRAM") < 0 )
  {
    Kprintf("s147ctrl.irx: Sram initialize failed\n");
    return 1;
  }
  return 0;
}

//----- (004000C0) --------------------------------------------------------
static void setup_ac_delay_regs(void)
{
  SetAcMemDelayReg(0x261A2122u);
  SetAcIoDelayReg(0xA61A0166);
}

//----- (00400100) --------------------------------------------------------
static int setup_ctrl_ioman_drv(const char *devpfx, const char *devname)
{
  g_watchdog_info.g_watchdog_started = 1;
  USec2SysClock(0x4E20u, &g_watchdog_info.g_watchdog_clock);
  SetAlarm(&g_watchdog_info.g_watchdog_clock, watchdog_alarm_cb, &g_watchdog_info);
  if ( create_ctrl_sema() < 0 )
    return -1;
  g_drv_ctrl_ioman.name = devpfx;
  g_drv_ctrl_ioman.type = 0x10;
  g_drv_ctrl_ioman.version = 0;
  g_drv_ctrl_ioman.desc = devname;
  g_drv_ctrl_ioman.ops = &g_ops_ctrl_ioman;
  DelDrv(devpfx);
  AddDrv(&g_drv_ctrl_ioman);
  return 0;
}
// 402900: using guessed type int (*g_ops_ctrl_ioman[17])();
// 402F70: using guessed type watchdog_info_ g_watchdog_info;

//----- (004001EC) --------------------------------------------------------
static unsigned int watchdog_alarm_cb(void *userdata)
{
  int state; // [sp+14h] [+14h] BYREF
  u8 unk34_tmp; // [sp+18h] [+18h]
  struct watchdog_info_ *wdi;

  wdi = (struct watchdog_info_ *)userdata;
  if ( wdi->g_watchdog_started != 1 )
  {
    s147_dev9_mem_mmio.m_led = 3;
    return 0;
  }
  CpuSuspendIntr(&state);
  s147link_dev9_mem_mmio.m_watchdog_flag_unk34 = 0;
  unk34_tmp = s147link_dev9_mem_mmio.m_watchdog_flag_unk34;
  CpuResumeIntr(state);
  if ( unk34_tmp == 0x3E )
  {
    s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
    s147_dev9_mem_mmio.m_led = g_watchdog_flag_1;
    g_watchdog_flag_1 = ( (((unsigned int)g_watchdog_count_1 >> 3) & 1) != 0 ) ? 2 : 1;
    ++g_watchdog_count_1;
  }
  return wdi->g_watchdog_clock.lo;
}
// 402948: using guessed type int g_watchdog_count_1;
// 40294C: using guessed type char g_watchdog_flag_1;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;
// B0800000: using guessed type s147link_dev9_mem_mmio_ s147link_dev9_mem_mmio;

//----- (0040030C) --------------------------------------------------------
static int ctrl_drv_op_nulldev(void)
{
  return 0;
}

//----- (00400330) --------------------------------------------------------
static int ctrl_drv_op_init(iop_device_t *dev)
{
  (void)dev;
  return 0;
}

//----- (00400358) --------------------------------------------------------
static int ctrl_drv_op_deinit(iop_device_t *dev)
{
  (void)dev;
  return 0;
}

//----- (00400380) --------------------------------------------------------
static int ctrl_drv_op_open(iop_file_t *f, const char *name, int flags)
{
  int state; // [sp+10h] [+10h] BYREF

  (void)flags;
  if ( f->unit != 99 )
    return 0;
  if ( !strcmp(name, "watchdog-start") )
  {
    Kprintf("s147ctrl.irx: wdt-start\n");
    CpuSuspendIntr(&state);
    g_watchdog_info.g_watchdog_started = 1;
    CpuResumeIntr(state);
  }
  else if ( !strcmp(name, "watchdog-stop") )
  {
    Kprintf("s147ctrl.irx: wdt-stop\n");
    CpuSuspendIntr(&state);
    g_watchdog_info.g_watchdog_started = 0;
    CpuResumeIntr(state);
  }
  else if ( !strcmp(name, "rpcserv-start") )
  {
    Kprintf("s147ctrl.irx: rpcserv-start\n");
    if ( !g_rpc_started )
    {
      do_rpc_start1();
      do_rpc_start2();
      CpuSuspendIntr(&state);
      g_rpc_started = 1;
      CpuResumeIntr(state);
    }
  }
  return 0;
}
// 402944: using guessed type int g_rpc_started;
// 402F70: using guessed type watchdog_info_ g_watchdog_info;

//----- (004004D4) --------------------------------------------------------
static int ctrl_drv_op_close(iop_file_t *f)
{
  (void)f;
  return 0;
}

//----- (004004FC) --------------------------------------------------------
static int ctrl_drv_op_read(iop_file_t *f, void *ptr, int size)
{
  int unit; // [sp+10h] [+10h]
  int retres; // [sp+14h] [+14h]

  unit = f->unit;
  switch ( unit )
  {
    case 4:
      if ( size != 0x1C )
        return -22;
      retres = ctrl_do_rtc_read(ptr);
      if ( retres < 0 )
        Kprintf("s147ctrl.irx: RTC Read failed (%d)\n", retres);
      return retres;
    case 12:
      if ( size != 2 )
        return -22;
      *(u8 *)ptr = s147_dev9_mem_mmio.m_security_unlock_set1;
      *((u8 *)ptr + 1) = s147_dev9_mem_mmio.m_security_unlock_set2;
      return 2;
    default:
      if ( size != 1 )
        return -22;
      *(u8 *)ptr = *(u8 *)(unit + 0xB0000000);
      return 1;
  }  
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00400690) --------------------------------------------------------
static int ctrl_drv_op_write(iop_file_t *f, void *ptr, int size)
{
  int unit; // [sp+10h] [+10h]
  int retres; // [sp+14h] [+14h]

  unit = f->unit;
  switch ( unit )
  {
    case 4:
      if ( size != 0x1C )
        return -22;
      retres = ctrl_do_rtc_write(ptr);
      if ( retres < 0 )
        Kprintf("s147ctrl.irx: RTC Write failed (%d)\n", retres);
      return retres;
    case 12:
      if ( size != 2 )
        return -22;
      s147_dev9_mem_mmio.m_security_unlock_set1 = *(u8 *)ptr;
      s147_dev9_mem_mmio.m_security_unlock_set2 = *((u8 *)ptr + 1);
      return 2;
    default:
      if ( size != 1 )
        return -22;
      *(u8 *)(unit + 0xB0000000) = *(u8 *)ptr;
      return 1;
  }
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00400820) --------------------------------------------------------
static int ctrl_drv_op_lseek(iop_file_t *f, int offset, int mode)
{
  (void)f;
  (void)offset;
  (void)mode;
  return 0;
}

//----- (00400850) --------------------------------------------------------
static int create_ctrl_sema(void)
{
  g_ctrl_sema_param.initial = 1;
  g_ctrl_sema_param.max = 1;
  g_ctrl_sema_param.attr = 1;
  g_ctrl_sema_id = CreateSema(&g_ctrl_sema_param);
  if ( g_ctrl_sema_id < 0 )
  {
    Kprintf("s147ctrl.irx: CreateSema error (%d)\n", g_ctrl_sema_id);
    return -1;
  }
  return 0;
}

//----- (004008EC) --------------------------------------------------------
static int ctrl_do_rtc_read(u32 *rtcbuf)
{
  WaitSema(g_ctrl_sema_id);
  g_timer_id = AllocHardTimer(1, 0x20, 1);
  if ( g_timer_id < 0 )
    return g_timer_id;
  SetupHardTimer(g_timer_id, 1, 0, 1);
  g_max_timer_counter = 0x40;
  StartHardTimer(g_timer_id);
  while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
    ;
  g_max_timer_counter += 0x40;
  s147_dev9_mem_mmio.m_rtc_flag = 1;
  while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
    ;
  g_max_timer_counter += 0x40;
  s147_dev9_mem_mmio.m_rtc_flag = 9;
  while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
    ;
  g_max_timer_counter += 0x40;
  rtcbuf[6] = ctrl_do_rtc_read_inner(8, 0x7F);
  rtcbuf[5] = ctrl_do_rtc_read_inner(8, 0x7F);
  rtcbuf[4] = ctrl_do_rtc_read_inner(8, 0x3F);
  rtcbuf[3] = ctrl_do_rtc_read_inner(4, 7);
  rtcbuf[2] = ctrl_do_rtc_read_inner(8, 0x3F);
  rtcbuf[1] = ctrl_do_rtc_read_inner(8, 0x1F);
  *rtcbuf = ctrl_do_rtc_read_inner(8, 0xFF);
  s147_dev9_mem_mmio.m_rtc_flag = 1;
  while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
    ;
  g_max_timer_counter += 0x40;
  s147_dev9_mem_mmio.m_rtc_flag = 1;
  while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
    ;
  g_max_timer_counter += 0x40;
  StopHardTimer(g_timer_id);
  FreeHardTimer(g_timer_id);
  g_max_timer_counter = 0;
  SignalSema(g_ctrl_sema_id);
  return 0x1C;
}
// 402950: using guessed type int g_max_timer_counter;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00400C40) --------------------------------------------------------
static int ctrl_do_rtc_read_inner(int flgcnt, int flgmsk)
{
  int i; // [sp+10h] [+10h]

  g_rtc_flag = 0;
  for ( i = 0; i < flgcnt; ++i )
  {
    s147_dev9_mem_mmio.m_rtc_flag = 0xB;
    while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
      ;
    g_max_timer_counter += 0x40;
    g_rtc_flag |= (s147_dev9_mem_mmio.m_rtc_flag & 1) << i;
    s147_dev9_mem_mmio.m_rtc_flag = 9;
    while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
      ;
    g_max_timer_counter += 0x40;
  }
  return g_rtc_flag & flgmsk;
}
// 402950: using guessed type int g_max_timer_counter;
// 4029E0: using guessed type int g_rtc_flag;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00400DB8) --------------------------------------------------------
static int ctrl_do_rtc_write(u32 *rtcbuf)
{
  WaitSema(g_ctrl_sema_id);
  g_timer_id = AllocHardTimer(1, 0x20, 1);
  if ( g_timer_id < 0 )
    return g_timer_id;
  SetupHardTimer(g_timer_id, 1, 0, 1);
  g_max_timer_counter = 0x40;
  StartHardTimer(g_timer_id);
  while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
    ;
  g_max_timer_counter += 0x40;
  s147_dev9_mem_mmio.m_rtc_flag = 5;
  while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
    ;
  g_max_timer_counter += 0x40;
  s147_dev9_mem_mmio.m_rtc_flag = 0xD;
  while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
    ;
  g_max_timer_counter += 0x40;
  ctrl_do_rtc_write_inner(rtcbuf[6], 8, 0x7F);
  ctrl_do_rtc_write_inner(rtcbuf[5], 8, 0x7F);
  ctrl_do_rtc_write_inner(rtcbuf[4], 8, 0x3F);
  ctrl_do_rtc_write_inner(rtcbuf[3], 4, 7);
  ctrl_do_rtc_write_inner(rtcbuf[2], 8, 0x3F);
  ctrl_do_rtc_write_inner(rtcbuf[1], 8, 0x1F);
  ctrl_do_rtc_write_inner(*rtcbuf, 8, 0xFF);
  s147_dev9_mem_mmio.m_rtc_flag = 5;
  while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
    ;
  g_max_timer_counter += 0x40;
  s147_dev9_mem_mmio.m_rtc_flag = 1;
  while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
    ;
  g_max_timer_counter += 0x40;
  StopHardTimer(g_timer_id);
  FreeHardTimer(g_timer_id);
  g_max_timer_counter = 0;
  SignalSema(g_ctrl_sema_id);
  return 0x1C;
}
// 402950: using guessed type int g_max_timer_counter;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (0040110C) --------------------------------------------------------
static void ctrl_do_rtc_write_inner(int inflg, int flgcnt, int flgmsk)
{
  int i; // [sp+10h] [+10h]
  unsigned int xval; // [sp+20h] [+20h]

  xval = inflg & flgmsk;
  for ( i = 0; i < flgcnt; ++i )
  {
    s147_dev9_mem_mmio.m_rtc_flag = (xval & 1) | 0xC;
    while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
      ;
    g_max_timer_counter += 0x40;
    s147_dev9_mem_mmio.m_rtc_flag = (xval & 1) | 0xE;
    while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
      ;
    g_max_timer_counter += 0x40;
    xval >>= 1;
  }
  s147_dev9_mem_mmio.m_rtc_flag = (xval & 1) | 0xC;
  while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
    ;
  g_max_timer_counter += 0x40;
}
// 402950: using guessed type int g_max_timer_counter;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (004012E0) --------------------------------------------------------
static int setup_sram_ioman_drv(const char *devpfx, const char *devname)
{
  g_drv_sram_ioman.name = devpfx;
  g_drv_sram_ioman.type = 0x10;
  g_drv_sram_ioman.version = 0;
  g_drv_sram_ioman.desc = devname;
  g_drv_sram_ioman.ops = &g_ops_sram_ioman;
  DelDrv(devpfx);
  AddDrv(&g_drv_sram_ioman);
  return 0;
}
// 402960: using guessed type int (*g_ops_sram_ioman[17])();

//----- (00401374) --------------------------------------------------------
static int sram_drv_op_nulldev(void)
{
  return 0;
}

//----- (00401398) --------------------------------------------------------
static int sram_drv_op_init(iop_device_t *dev)
{
  (void)dev;
  return 0;
}

//----- (004013C0) --------------------------------------------------------
static int sram_drv_op_deinit(iop_device_t *dev)
{
  (void)dev;
  return 0;
}

//----- (004013E8) --------------------------------------------------------
static int sram_drv_op_open(iop_file_t *f, const char *name, int flags)
{
  struct sram_drv_privdata_ *privdata; // [sp+10h] [+10h]
  int state; // [sp+14h] [+14h] BYREF

  (void)name;
  (void)flags;
  CpuSuspendIntr(&state);
  f->privdata = AllocSysMemory(0, sizeof(struct sram_drv_privdata_), 0);
  CpuResumeIntr(state);
  privdata = (struct sram_drv_privdata_ *)f->privdata;
  privdata->m_curpos = 0;
  privdata->m_maxpos = 0x8000;
  return 0;
}

//----- (00401480) --------------------------------------------------------
static int sram_drv_op_close(iop_file_t *f)
{
  int state; // [sp+10h] [+10h] BYREF

  if ( !f->privdata )
    return 0;
  CpuSuspendIntr(&state);
  FreeSysMemory(f->privdata);
  CpuResumeIntr(state);
  f->privdata = 0;
  return 0;
}

//----- (004014FC) --------------------------------------------------------
static int sram_drv_op_read(iop_file_t *f, void *ptr, int size)
{
  int sizeb; // $v0
  struct sram_drv_privdata_ *privdata; // [sp+10h] [+10h]

  privdata = (struct sram_drv_privdata_ *)f->privdata;
  if ( (s32)privdata->m_curpos >= (s32)privdata->m_maxpos )
    return 0;
  sizeb = ( (s32)privdata->m_maxpos < (s32)(privdata->m_curpos + size) ) ? (privdata->m_maxpos - privdata->m_curpos) : (u32)size;
  memcpy(ptr, (const void *)(privdata->m_curpos + 0xB0C00000), sizeb);
  privdata->m_curpos += sizeb;
  return sizeb;
}

//----- (00401620) --------------------------------------------------------
static int sram_drv_op_write(iop_file_t *f, void *ptr, int size)
{
  int sizeb; // $v0
  struct sram_drv_privdata_ *privdata; // [sp+10h] [+10h]

  privdata = (struct sram_drv_privdata_ *)f->privdata;
  if ( (s32)privdata->m_curpos >= (s32)privdata->m_maxpos )
    return 0;
  sizeb = ( (s32)privdata->m_maxpos < (s32)(privdata->m_curpos + size) ) ? (privdata->m_maxpos - privdata->m_curpos) : (u32)size;
  s147_dev9_mem_mmio.m_sram_write_flag = 1;
  memcpy((void *)(privdata->m_curpos + 0xB0C00000), ptr, sizeb);
  s147_dev9_mem_mmio.m_sram_write_flag = 0;
  privdata->m_curpos += sizeb;
  return sizeb;
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00401758) --------------------------------------------------------
static int sram_drv_op_lseek(iop_file_t *f, int offset, int mode)
{
  struct sram_drv_privdata_ *privdata; // [sp+0h] [+0h]

  privdata = (struct sram_drv_privdata_ *)f->privdata;
  switch ( mode )
  {
    case 0:
      privdata->m_curpos = offset;
      break;
    case 1:
      privdata->m_curpos += offset;
      break;
    case 2:
      privdata->m_curpos = privdata->m_maxpos + offset;
      break;
    default:
      return -22;
  }
  if ( (s32)privdata->m_maxpos >= (s32)privdata->m_curpos )
    return privdata->m_curpos;
  privdata->m_curpos = privdata->m_maxpos;
  return -22;
}

//----- (00401890) --------------------------------------------------------
static int do_rpc_start1(void)
{
  iop_thread_t thparam; // [sp+10h] [+10h] BYREF
  int thid; // [sp+28h] [+28h]

  thparam.attr = 0x2000000;
  thparam.thread = rpc_thread1;
  thparam.priority = 10;
  thparam.stacksize = 0x800;
  thparam.option = 0;
  thid = CreateThread(&thparam);
  if ( thid <= 0 )
    return 1;
  StartThread(thid, 0);
  return 0;
}

//----- (0040191C) --------------------------------------------------------
static void rpc_thread1(void *userdata)
{
  SifRpcDataQueue_t qd; // [sp+20h] [+20h] BYREF
  SifRpcServerData_t sd[4];

  (void)userdata;
  sceSifInitRpc(0);
  sceSifSetRpcQueue(&qd, GetThreadId());
  sceSifRegisterRpc(&sd[0], 0x1470000, rpc_1470000_handler, g_rpc1_buf, 0, 0, &qd);
  sceSifRegisterRpc(&sd[1], 0x1470001, rpc_1470001_handler, g_rpc1_buf, 0, 0, &qd);
  sceSifRegisterRpc(&sd[2], 0x1470002, rpc_1470002_handler, g_rpc1_buf, 0, 0, &qd);
  sceSifRegisterRpc(&sd[3], 0x1470003, rpc_1470003_handler, g_rpc1_buf, 0, 0, &qd);
  sceSifRpcLoop(&qd);
}
// 402A40: using guessed type int g_rpc1_buf[8];
// 40191C: using guessed type SifRpcServerData_t sd1;
// 40191C: using guessed type SifRpcServerData_t sd2;
// 40191C: using guessed type SifRpcServerData_t sd3;
// 40191C: using guessed type SifRpcServerData_t sd4;

//----- (00401A48) --------------------------------------------------------
static void *rpc_1470000_handler(int fno, void *buffer, int length)
{
  (void)length;
  switch ( fno )
  {
    case 1:
      s147_dev9_mem_mmio.m_led = *(u8 *)buffer;
      *(u32 *)buffer = 0;
      break;
    case 2:
      s147_dev9_mem_mmio.m_security_unlock_unlock = *(u8 *)buffer;
      *(u32 *)buffer = 0;
      break;
    case 3:
      s147_dev9_mem_mmio.m_unk03 = *(u8 *)buffer;
      *(u32 *)buffer = 0;
      break;
    case 4:
      s147_dev9_mem_mmio.m_rtc_flag = *(u8 *)buffer;
      *(u32 *)buffer = 0;
      break;
    case 5:
      s147_dev9_mem_mmio.m_watchdog_flag2 = *(u8 *)buffer;
      *(u32 *)buffer = 0;
      break;
    case 12:
      s147_dev9_mem_mmio.m_security_unlock_set1 = *(u8 *)buffer;
      *(u32 *)buffer = 0;
      break;
    case 13:
      s147_dev9_mem_mmio.m_security_unlock_set2 = *(u8 *)buffer;
      *(u32 *)buffer = 0;
      break;
    default:
      *(u32 *)buffer = -22;
      break;
  }
  return buffer;
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00401BA0) --------------------------------------------------------
static void *rpc_1470001_handler(int fno, void *buffer, int length)
{
  (void)length;
  switch ( fno )
  {
    case 0:
      *(u8 *)buffer = s147_dev9_mem_mmio.m_unk00;
      *((u32 *)buffer + 1) = 0;
      break;
    case 1:
      *(u8 *)buffer = s147_dev9_mem_mmio.m_led;
      *((u32 *)buffer + 1) = 0;
      break;
    case 2:
      *(u8 *)buffer = s147_dev9_mem_mmio.m_security_unlock_unlock;
      *((u32 *)buffer + 1) = 0;
      break;
    case 3:
      *(u8 *)buffer = s147_dev9_mem_mmio.m_unk03;
      *((u32 *)buffer + 1) = 0;
      break;
    case 4:
      *(u8 *)buffer = s147_dev9_mem_mmio.m_rtc_flag;
      *((u32 *)buffer + 1) = 0;
      break;
    case 5:
      *(u8 *)buffer = s147_dev9_mem_mmio.m_watchdog_flag2;
      *((u32 *)buffer + 1) = 0;
      break;
    case 6:
      *(u8 *)buffer = s147_dev9_mem_mmio.m_unk06;
      *((u32 *)buffer + 1) = 0;
      break;
    case 12:
      *(u8 *)buffer = s147_dev9_mem_mmio.m_security_unlock_set1;
      *((u32 *)buffer + 1) = 0;
      break;
    case 13:
      *(u8 *)buffer = s147_dev9_mem_mmio.m_security_unlock_set2;
      *((u32 *)buffer + 1) = 0;
      break;
    default:
      *(u8 *)buffer = 0;
      *((u32 *)buffer + 1) = -22;
      break;
  }
  return buffer;
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00401D30) --------------------------------------------------------
static void *rpc_1470002_handler(int fno, void *buffer, int length)
{
  (void)length;
  *(u32 *)buffer = ( fno == 4 ) ? ctrl_do_rtc_write(buffer) : -22;
  return buffer;
}

//----- (00401DCC) --------------------------------------------------------
static void *rpc_1470003_handler(int fno, void *buffer, int length)
{
  (void)length;
  if ( fno != 4 )
  {
    *(u32 *)buffer = 0;
    *((u32 *)buffer + 1) = 0;
    *((u32 *)buffer + 2) = 0;
    *((u32 *)buffer + 3) = 0;
    *((u32 *)buffer + 4) = 0;
    *((u32 *)buffer + 5) = 0;
    *((u32 *)buffer + 6) = 0;
    *((u32 *)buffer + 7) = -22;
    return buffer;
  }
  *((u32 *)buffer + 7) = ctrl_do_rtc_read(buffer);
  return buffer;
}

//----- (00401EB0) --------------------------------------------------------
static int do_rpc_start2(void)
{
  iop_thread_t thparam; // [sp+10h] [+10h] BYREF
  int thid; // [sp+28h] [+28h]

  thparam.attr = 0x2000000;
  thparam.thread = rpc_thread2;
  thparam.priority = 10;
  thparam.stacksize = 0x800;
  thparam.option = 0;
  thid = CreateThread(&thparam);
  if ( thid <= 0 )
    return 1;
  StartThread(thid, 0);
  return 0;
}

//----- (00401F3C) --------------------------------------------------------
static void rpc_thread2(void *userdata)
{
  SifRpcDataQueue_t qd; // [sp+20h] [+20h] BYREF
  SifRpcServerData_t sd[2];

  (void)userdata;
  sceSifInitRpc(0);
  sceSifSetRpcQueue(&qd, GetThreadId());
  sceSifRegisterRpc(&sd[0], 0x1470200, rpc_1470200_handler, g_rpc2_buf, 0, 0, &qd);
  sceSifRegisterRpc(&sd[1], 0x1470201, rpc_1470201_handler, g_rpc2_buf, 0, 0, &qd);
  sceSifRpcLoop(&qd);
}
// 402A60: using guessed type int g_rpc2_buf[260];
// 401F3C: using guessed type SifRpcServerData_t sd1;
// 401F3C: using guessed type SifRpcServerData_t sd2;

//----- (00401FFC) --------------------------------------------------------
static void *rpc_1470200_handler(int fno, void *buffer, int length)
{
  (void)length;
  if ( (unsigned int)fno >= 3 )
  {
    *(u32 *)buffer = -1;
    return buffer;
  }
  s147_dev9_mem_mmio.m_sram_write_flag = 1;
  memcpy((void *)(*((u32 *)buffer + 256) + 0xB0C00000), buffer, *((u32 *)buffer + 257));
  s147_dev9_mem_mmio.m_sram_write_flag = 0;
  *(u32 *)buffer = 0;
  return buffer;
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (004020E0) --------------------------------------------------------
static void *rpc_1470201_handler(int fno, void *buffer, int length)
{
  (void)length;
  if ( (unsigned int)fno >= 3 )
  {
    memset(buffer, 0, *((u32 *)buffer + 1));
    *((u32 *)buffer + 256) = -1;
    return buffer;
  }
  memcpy(buffer, (const void *)(*(u32 *)buffer + 0xB0C00000), *((u32 *)buffer + 1));
  *((u32 *)buffer + 256) = 0;
  return buffer;
}
