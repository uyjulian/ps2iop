
#include "irx_imports.h"

IRX_ID("S147CTRL", 2, 8);

#define __fastcall
#define __cdecl
#define _BYTE u8
#define _WORD u16
#define _DWORD u32
#define __int32 int

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

int _start();
int setup_ac_delay_regs();
int __fastcall setup_ctrl_ioman_drv(const char *devpfx, const char *devname);
u32 __fastcall watchdog_alarm_cb(struct watchdog_info_ *userdata);
int ctrl_drv_op_nulldev();
int __cdecl ctrl_drv_op_init(iop_device_t *dev);
int __cdecl ctrl_drv_op_deinit(iop_device_t *dev);
int __cdecl ctrl_drv_op_open(iop_file_t *f, const char *name, int flags);
int __cdecl ctrl_drv_op_close(iop_file_t *f);
int __cdecl ctrl_drv_op_read(iop_file_t *f, void *ptr, int size);
int __cdecl ctrl_drv_op_write(iop_file_t *f, void *ptr, int size);
int __cdecl ctrl_drv_op_lseek(iop_file_t *f, int offset, int mode);
int create_ctrl_sema();
int __fastcall ctrl_do_rtc_read(_DWORD *rtcbuf);
int __fastcall ctrl_do_rtc_read_inner(int flgcnt, int flgmsk);
int __fastcall ctrl_do_rtc_write(_DWORD *rtcbuf);
int __fastcall ctrl_do_rtc_write_inner(int inflg, int flgcnt, int flgmsk);
int __fastcall setup_sram_ioman_drv(const char *devpfx, const char *devname);
int sram_drv_op_nulldev();
int __cdecl sram_drv_op_init(iop_device_t *dev);
int __cdecl sram_drv_op_deinit(iop_device_t *dev);
int __cdecl sram_drv_op_open(iop_file_t *f, const char *name, int flags);
int __cdecl sram_drv_op_close(iop_file_t *f);
int __cdecl sram_drv_op_read(iop_file_t *f, void *ptr, int size);
int __cdecl sram_drv_op_write(iop_file_t *f, void *ptr, int size);
int __cdecl sram_drv_op_lseek(iop_file_t *f, int offset, int mode);
int do_rpc_start1();
int rpc_thread1();
void *__fastcall rpc_1470000_handler(int fno, void *buffer, int length);
void *__fastcall rpc_1470001_handler(int fno, void *buffer, int length);
void *__fastcall rpc_1470002_handler(int fno, void *buffer, int length);
void *__fastcall rpc_1470003_handler(int fno, void *buffer, int length);
int do_rpc_start2();
int rpc_thread2();
void *__fastcall rpc_1470200_handler(int fno, void *buffer, int length);
void *__fastcall rpc_1470201_handler(int fno, void *buffer, int length);

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
int g_max_timer_counter = 0; // weak
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
int _start()
{
  Kprintf("\n");
  Kprintf("s147ctrl.irx: System147 Control/SRAM Driver v%d.%d\n", 2, 8);
  setup_ac_delay_regs();
  if ( setup_ctrl_ioman_drv("ctrl", "Ctrl") >= 0 )
  {
    if ( setup_sram_ioman_drv("sram", "SRAM") >= 0 )
    {
      return 0;
    }
    else
    {
      Kprintf("s147ctrl.irx: Sram initialize failed\n");
      return 1;
    }
  }
  else
  {
    Kprintf("s147ctrl.irx: Ctrl initialize failed\n");
    return 1;
  }
}

//----- (004000C0) --------------------------------------------------------
int setup_ac_delay_regs()
{
  SetAcMemDelayReg(0x261A2122u);
  return SetAcIoDelayReg(0xA61A0166);
}

//----- (00400100) --------------------------------------------------------
int __fastcall setup_ctrl_ioman_drv(const char *devpfx, const char *devname)
{
  g_watchdog_info.g_watchdog_started = 1;
  USec2SysClock(0x4E20u, &g_watchdog_info.g_watchdog_clock);
  SetAlarm(&g_watchdog_info.g_watchdog_clock, (unsigned int (__cdecl *)(void *))watchdog_alarm_cb, &g_watchdog_info);
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
u32 __fastcall watchdog_alarm_cb(struct watchdog_info_ *userdata)
{
  vu8 m_watchdog_flag_unk34; // $v0
  char v2; // $v0
  int state; // [sp+14h] [+14h] BYREF
  vu8 v6; // [sp+18h] [+18h]

  if ( userdata->g_watchdog_started == 1 )
  {
    CpuSuspendIntr(&state);
    s147link_dev9_mem_mmio.m_watchdog_flag_unk34 = 0;
    m_watchdog_flag_unk34 = s147link_dev9_mem_mmio.m_watchdog_flag_unk34;
    v6 = m_watchdog_flag_unk34;
    CpuResumeIntr(state);
    if ( v6 == 0x3E )
    {
      s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
      s147_dev9_mem_mmio.m_led = g_watchdog_flag_1;
      if ( (((unsigned int)g_watchdog_count_1 >> 3) & 1) != 0 )
        v2 = 2;
      else
        v2 = 1;
      g_watchdog_flag_1 = v2;
      ++g_watchdog_count_1;
    }
    return userdata->g_watchdog_clock.lo;
  }
  else
  {
    s147_dev9_mem_mmio.m_led = 3;
    return 0;
  }
}
// 402948: using guessed type int g_watchdog_count_1;
// 40294C: using guessed type char g_watchdog_flag_1;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;
// B0800000: using guessed type s147link_dev9_mem_mmio_ s147link_dev9_mem_mmio;

//----- (0040030C) --------------------------------------------------------
int ctrl_drv_op_nulldev()
{
  return 0;
}

//----- (00400330) --------------------------------------------------------
int __cdecl ctrl_drv_op_init(iop_device_t *dev)
{
  return 0;
}

//----- (00400358) --------------------------------------------------------
int __cdecl ctrl_drv_op_deinit(iop_device_t *dev)
{
  return 0;
}

//----- (00400380) --------------------------------------------------------
int __cdecl ctrl_drv_op_open(iop_file_t *f, const char *name, int flags)
{
  int state[2]; // [sp+10h] [+10h] BYREF

  if ( f->unit == 99 )
  {
    if ( !strcmp(name, "watchdog-start") )
    {
      Kprintf("s147ctrl.irx: wdt-start\n");
      CpuSuspendIntr(state);
      g_watchdog_info.g_watchdog_started = 1;
      CpuResumeIntr(state[0]);
    }
    else if ( !strcmp(name, "watchdog-stop") )
    {
      Kprintf("s147ctrl.irx: wdt-stop\n");
      CpuSuspendIntr(state);
      g_watchdog_info.g_watchdog_started = 0;
      CpuResumeIntr(state[0]);
    }
    else if ( !strcmp(name, "rpcserv-start") )
    {
      Kprintf("s147ctrl.irx: rpcserv-start\n");
      if ( !g_rpc_started )
      {
        do_rpc_start1();
        do_rpc_start2();
        CpuSuspendIntr(state);
        g_rpc_started = 1;
        CpuResumeIntr(state[0]);
      }
    }
  }
  return 0;
}
// 402944: using guessed type int g_rpc_started;
// 402F70: using guessed type watchdog_info_ g_watchdog_info;

//----- (004004D4) --------------------------------------------------------
int __cdecl ctrl_drv_op_close(iop_file_t *f)
{
  return 0;
}

//----- (004004FC) --------------------------------------------------------
int __cdecl ctrl_drv_op_read(iop_file_t *f, void *ptr, int size)
{
  vu8 m_security_unlock_set1; // $v1
  vu8 m_security_unlock_set2; // $v1
  int unit; // [sp+10h] [+10h]
  int retres; // [sp+14h] [+14h]

  unit = f->unit;
  if ( unit == 4 )
  {
    if ( size != 0x1C )
      return -22;
    retres = ctrl_do_rtc_read(ptr);
    if ( retres < 0 )
    {
      Kprintf("s147ctrl.irx: RTC Read failed (%d)\n", retres);
      return retres;
    }
  }
  else if ( unit == 12 )
  {
    if ( size != 2 )
      return -22;
    m_security_unlock_set1 = s147_dev9_mem_mmio.m_security_unlock_set1;
    *(_BYTE *)ptr = m_security_unlock_set1;
    m_security_unlock_set2 = s147_dev9_mem_mmio.m_security_unlock_set2;
    *((_BYTE *)ptr + 1) = m_security_unlock_set2;
    return 2;
  }
  else
  {
    if ( size != 1 )
      return -22;
    *(_BYTE *)ptr = *(_BYTE *)(unit + 0xB0000000);
    return 1;
  }
  return retres;
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00400690) --------------------------------------------------------
int __cdecl ctrl_drv_op_write(iop_file_t *f, void *ptr, int size)
{
  int unit; // [sp+10h] [+10h]
  int retres; // [sp+14h] [+14h]

  unit = f->unit;
  if ( unit == 4 )
  {
    if ( size != 0x1C )
      return -22;
    retres = ctrl_do_rtc_write(ptr);
    if ( retres < 0 )
    {
      Kprintf("s147ctrl.irx: RTC Write failed (%d)\n", retres);
      return retres;
    }
  }
  else if ( unit == 12 )
  {
    if ( size != 2 )
      return -22;
    s147_dev9_mem_mmio.m_security_unlock_set1 = *(_BYTE *)ptr;
    s147_dev9_mem_mmio.m_security_unlock_set2 = *((_BYTE *)ptr + 1);
    return 2;
  }
  else
  {
    if ( size != 1 )
      return -22;
    *(_BYTE *)(unit + 0xB0000000) = *(_BYTE *)ptr;
    return 1;
  }
  return retres;
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00400820) --------------------------------------------------------
int __cdecl ctrl_drv_op_lseek(iop_file_t *f, int offset, int mode)
{
  return 0;
}

//----- (00400850) --------------------------------------------------------
int create_ctrl_sema()
{
  g_ctrl_sema_param.initial = 1;
  g_ctrl_sema_param.max = 1;
  g_ctrl_sema_param.attr = 1;
  g_ctrl_sema_id = CreateSema(&g_ctrl_sema_param);
  if ( g_ctrl_sema_id >= 0 )
    return 0;
  Kprintf("s147ctrl.irx: CreateSema error (%d)\n", g_ctrl_sema_id);
  return -1;
}

//----- (004008EC) --------------------------------------------------------
int __fastcall ctrl_do_rtc_read(_DWORD *rtcbuf)
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
int __fastcall ctrl_do_rtc_read_inner(int flgcnt, int flgmsk)
{
  vu8 m_rtc_flag; // $v0
  int i; // [sp+10h] [+10h]

  g_rtc_flag = 0;
  for ( i = 0; i < flgcnt; ++i )
  {
    s147_dev9_mem_mmio.m_rtc_flag = 0xB;
    while ( GetTimerCounter(g_timer_id) < g_max_timer_counter )
      ;
    g_max_timer_counter += 0x40;
    m_rtc_flag = s147_dev9_mem_mmio.m_rtc_flag;
    g_rtc_flag |= (m_rtc_flag & 1) << i;
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
int __fastcall ctrl_do_rtc_write(_DWORD *rtcbuf)
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
int __fastcall ctrl_do_rtc_write_inner(int inflg, int flgcnt, int flgmsk)
{
  int result; // $v0
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
  result = g_max_timer_counter;
  g_max_timer_counter += 0x40;
  return result;
}
// 402950: using guessed type int g_max_timer_counter;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (004012E0) --------------------------------------------------------
int __fastcall setup_sram_ioman_drv(const char *devpfx, const char *devname)
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
int sram_drv_op_nulldev()
{
  return 0;
}

//----- (00401398) --------------------------------------------------------
int __cdecl sram_drv_op_init(iop_device_t *dev)
{
  return 0;
}

//----- (004013C0) --------------------------------------------------------
int __cdecl sram_drv_op_deinit(iop_device_t *dev)
{
  return 0;
}

//----- (004013E8) --------------------------------------------------------
int __cdecl sram_drv_op_open(iop_file_t *f, const char *name, int flags)
{
  struct sram_drv_privdata_ *privdata; // [sp+10h] [+10h]
  int state; // [sp+14h] [+14h] BYREF

  CpuSuspendIntr(&state);
  f->privdata = AllocSysMemory(0, 8, 0);
  CpuResumeIntr(state);
  privdata = (struct sram_drv_privdata_ *)f->privdata;
  privdata->m_curpos = 0;
  privdata->m_maxpos = 0x8000;
  return 0;
}

//----- (00401480) --------------------------------------------------------
int __cdecl sram_drv_op_close(iop_file_t *f)
{
  int state; // [sp+10h] [+10h] BYREF

  if ( f->privdata )
  {
    CpuSuspendIntr(&state);
    FreeSysMemory(f->privdata);
    CpuResumeIntr(state);
    f->privdata = 0;
  }
  return 0;
}

//----- (004014FC) --------------------------------------------------------
int __cdecl sram_drv_op_read(iop_file_t *f, void *ptr, int size)
{
  int sizeb; // $v0
  struct sram_drv_privdata_ *privdata; // [sp+10h] [+10h]
  int sizea; // [sp+18h] [+18h]

  privdata = (struct sram_drv_privdata_ *)f->privdata;
  if ( (signed __int32)privdata->m_curpos >= (signed __int32)privdata->m_maxpos )
    return 0;
  if ( (signed __int32)privdata->m_maxpos >= (signed __int32)(privdata->m_curpos + size) )
    sizeb = size;
  else
    sizeb = privdata->m_maxpos - privdata->m_curpos;
  sizea = sizeb;
  memcpy(ptr, (const void *)(privdata->m_curpos + 0xB0C00000), sizeb);
  privdata->m_curpos += sizea;
  return sizea;
}

//----- (00401620) --------------------------------------------------------
int __cdecl sram_drv_op_write(iop_file_t *f, void *ptr, int size)
{
  int sizeb; // $v0
  struct sram_drv_privdata_ *privdata; // [sp+10h] [+10h]
  int sizea; // [sp+18h] [+18h]

  privdata = (struct sram_drv_privdata_ *)f->privdata;
  if ( (signed __int32)privdata->m_curpos >= (signed __int32)privdata->m_maxpos )
    return 0;
  if ( (signed __int32)privdata->m_maxpos >= (signed __int32)(privdata->m_curpos + size) )
    sizeb = size;
  else
    sizeb = privdata->m_maxpos - privdata->m_curpos;
  sizea = sizeb;
  s147_dev9_mem_mmio.m_sram_write_flag = 1;
  memcpy((void *)(privdata->m_curpos + 0xB0C00000), ptr, sizeb);
  s147_dev9_mem_mmio.m_sram_write_flag = 0;
  privdata->m_curpos += sizea;
  return sizea;
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00401758) --------------------------------------------------------
int __cdecl sram_drv_op_lseek(iop_file_t *f, int offset, int mode)
{
  struct sram_drv_privdata_ *privdata; // [sp+0h] [+0h]

  privdata = (struct sram_drv_privdata_ *)f->privdata;
  if ( mode == 1 )
  {
    privdata->m_curpos += offset;
  }
  else if ( mode >= 2 )
  {
    if ( mode != 2 )
      return -22;
    privdata->m_curpos = privdata->m_maxpos + offset;
  }
  else
  {
    if ( mode )
      return -22;
    privdata->m_curpos = offset;
  }
  if ( (signed __int32)privdata->m_maxpos >= (signed __int32)privdata->m_curpos )
    return privdata->m_curpos;
  privdata->m_curpos = privdata->m_maxpos;
  return -22;
}

//----- (00401890) --------------------------------------------------------
int do_rpc_start1()
{
  iop_thread_t thparam; // [sp+10h] [+10h] BYREF
  int thid; // [sp+28h] [+28h]

  thparam.attr = 0x2000000;
  thparam.thread = (void (__cdecl *)(void *))rpc_thread1;
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
int rpc_thread1()
{
  int ThreadId; // $v0
  SifRpcDataQueue_t qd; // [sp+20h] [+20h] BYREF
  SifRpcServerData_t sd1; // [sp+38h] [+38h] BYREF
  SifRpcServerData_t sd2; // [sp+80h] [+80h] BYREF
  SifRpcServerData_t sd3; // [sp+C8h] [+C8h] BYREF
  SifRpcServerData_t sd4; // [sp+110h] [+110h] BYREF

  sceSifInitRpc(0);
  ThreadId = GetThreadId();
  sceSifSetRpcQueue(&qd, ThreadId);
  sceSifRegisterRpc(&sd1, 0x1470000, (SifRpcFunc_t)rpc_1470000_handler, g_rpc1_buf, 0, 0, &qd);
  sceSifRegisterRpc(&sd2, 0x1470001, (SifRpcFunc_t)rpc_1470001_handler, g_rpc1_buf, 0, 0, &qd);
  sceSifRegisterRpc(&sd3, 0x1470002, (SifRpcFunc_t)rpc_1470002_handler, g_rpc1_buf, 0, 0, &qd);
  sceSifRegisterRpc(&sd4, 0x1470003, (SifRpcFunc_t)rpc_1470003_handler, g_rpc1_buf, 0, 0, &qd);
  sceSifRpcLoop(&qd);
  return 0;
}
// 402A40: using guessed type int g_rpc1_buf[8];
// 40191C: using guessed type SifRpcServerData_t sd1;
// 40191C: using guessed type SifRpcServerData_t sd2;
// 40191C: using guessed type SifRpcServerData_t sd3;
// 40191C: using guessed type SifRpcServerData_t sd4;

//----- (00401A48) --------------------------------------------------------
void *__fastcall rpc_1470000_handler(int fno, void *buffer, int length)
{
  void *result; // $v0

  switch ( fno )
  {
    case 1:
      s147_dev9_mem_mmio.m_led = *(_BYTE *)buffer;
      *(_DWORD *)buffer = 0;
      result = buffer;
      break;
    case 2:
      s147_dev9_mem_mmio.m_security_unlock_unlock = *(_BYTE *)buffer;
      *(_DWORD *)buffer = 0;
      result = buffer;
      break;
    case 3:
      s147_dev9_mem_mmio.m_unk03 = *(_BYTE *)buffer;
      *(_DWORD *)buffer = 0;
      result = buffer;
      break;
    case 4:
      s147_dev9_mem_mmio.m_rtc_flag = *(_BYTE *)buffer;
      *(_DWORD *)buffer = 0;
      result = buffer;
      break;
    case 5:
      s147_dev9_mem_mmio.m_watchdog_flag2 = *(_BYTE *)buffer;
      *(_DWORD *)buffer = 0;
      result = buffer;
      break;
    case 12:
      s147_dev9_mem_mmio.m_security_unlock_set1 = *(_BYTE *)buffer;
      *(_DWORD *)buffer = 0;
      result = buffer;
      break;
    case 13:
      s147_dev9_mem_mmio.m_security_unlock_set2 = *(_BYTE *)buffer;
      *(_DWORD *)buffer = 0;
      result = buffer;
      break;
    default:
      *(_DWORD *)buffer = -22;
      result = buffer;
      break;
  }
  return result;
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00401BA0) --------------------------------------------------------
void *__fastcall rpc_1470001_handler(int fno, void *buffer, int length)
{
  vu8 m_unk00; // $v1
  vu8 m_led; // $v1
  vu8 m_security_unlock_unlock; // $v1
  vu8 m_unk03; // $v1
  vu8 m_rtc_flag; // $v1
  vu8 m_watchdog_flag2; // $v1
  vu8 m_unk06; // $v1
  vu8 m_security_unlock_set1; // $v1
  vu8 m_security_unlock_set2; // $v1
  void *result; // $v0

  switch ( fno )
  {
    case 0:
      m_unk00 = s147_dev9_mem_mmio.m_unk00;
      *(_BYTE *)buffer = m_unk00;
      *((_DWORD *)buffer + 1) = 0;
      result = buffer;
      break;
    case 1:
      m_led = s147_dev9_mem_mmio.m_led;
      *(_BYTE *)buffer = m_led;
      *((_DWORD *)buffer + 1) = 0;
      result = buffer;
      break;
    case 2:
      m_security_unlock_unlock = s147_dev9_mem_mmio.m_security_unlock_unlock;
      *(_BYTE *)buffer = m_security_unlock_unlock;
      *((_DWORD *)buffer + 1) = 0;
      result = buffer;
      break;
    case 3:
      m_unk03 = s147_dev9_mem_mmio.m_unk03;
      *(_BYTE *)buffer = m_unk03;
      *((_DWORD *)buffer + 1) = 0;
      result = buffer;
      break;
    case 4:
      m_rtc_flag = s147_dev9_mem_mmio.m_rtc_flag;
      *(_BYTE *)buffer = m_rtc_flag;
      *((_DWORD *)buffer + 1) = 0;
      result = buffer;
      break;
    case 5:
      m_watchdog_flag2 = s147_dev9_mem_mmio.m_watchdog_flag2;
      *(_BYTE *)buffer = m_watchdog_flag2;
      *((_DWORD *)buffer + 1) = 0;
      result = buffer;
      break;
    case 6:
      m_unk06 = s147_dev9_mem_mmio.m_unk06;
      *(_BYTE *)buffer = m_unk06;
      *((_DWORD *)buffer + 1) = 0;
      result = buffer;
      break;
    case 12:
      m_security_unlock_set1 = s147_dev9_mem_mmio.m_security_unlock_set1;
      *(_BYTE *)buffer = m_security_unlock_set1;
      *((_DWORD *)buffer + 1) = 0;
      result = buffer;
      break;
    case 13:
      m_security_unlock_set2 = s147_dev9_mem_mmio.m_security_unlock_set2;
      *(_BYTE *)buffer = m_security_unlock_set2;
      *((_DWORD *)buffer + 1) = 0;
      result = buffer;
      break;
    default:
      *(_BYTE *)buffer = 0;
      *((_DWORD *)buffer + 1) = -22;
      result = buffer;
      break;
  }
  return result;
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00401D30) --------------------------------------------------------
void *__fastcall rpc_1470002_handler(int fno, void *buffer, int length)
{
  if ( fno == 4 )
    *(_DWORD *)buffer = ctrl_do_rtc_write(buffer);
  else
    *(_DWORD *)buffer = -22;
  return buffer;
}

//----- (00401DCC) --------------------------------------------------------
void *__fastcall rpc_1470003_handler(int fno, void *buffer, int length)
{
  if ( fno == 4 )
  {
    *((_DWORD *)buffer + 7) = ctrl_do_rtc_read(buffer);
  }
  else
  {
    *(_DWORD *)buffer = 0;
    *((_DWORD *)buffer + 1) = 0;
    *((_DWORD *)buffer + 2) = 0;
    *((_DWORD *)buffer + 3) = 0;
    *((_DWORD *)buffer + 4) = 0;
    *((_DWORD *)buffer + 5) = 0;
    *((_DWORD *)buffer + 6) = 0;
    *((_DWORD *)buffer + 7) = -22;
  }
  return buffer;
}

//----- (00401EB0) --------------------------------------------------------
int do_rpc_start2()
{
  iop_thread_t thparam; // [sp+10h] [+10h] BYREF
  int thid; // [sp+28h] [+28h]

  thparam.attr = 0x2000000;
  thparam.thread = (void (__cdecl *)(void *))rpc_thread2;
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
int rpc_thread2()
{
  int ThreadId; // $v0
  SifRpcDataQueue_t qd; // [sp+20h] [+20h] BYREF
  SifRpcServerData_t sd1; // [sp+38h] [+38h] BYREF
  SifRpcServerData_t sd2; // [sp+80h] [+80h] BYREF

  sceSifInitRpc(0);
  ThreadId = GetThreadId();
  sceSifSetRpcQueue(&qd, ThreadId);
  sceSifRegisterRpc(&sd1, 0x1470200, (SifRpcFunc_t)rpc_1470200_handler, g_rpc2_buf, 0, 0, &qd);
  sceSifRegisterRpc(&sd2, 0x1470201, (SifRpcFunc_t)rpc_1470201_handler, g_rpc2_buf, 0, 0, &qd);
  sceSifRpcLoop(&qd);
  return 0;
}
// 402A60: using guessed type int g_rpc2_buf[260];
// 401F3C: using guessed type SifRpcServerData_t sd1;
// 401F3C: using guessed type SifRpcServerData_t sd2;

//----- (00401FFC) --------------------------------------------------------
void *__fastcall rpc_1470200_handler(int fno, void *buffer, int length)
{
  if ( (unsigned int)fno >= 3 )
  {
    *(_DWORD *)buffer = -1;
  }
  else
  {
    s147_dev9_mem_mmio.m_sram_write_flag = 1;
    memcpy((void *)(*((_DWORD *)buffer + 256) + 0xB0C00000), buffer, *((_DWORD *)buffer + 257));
    s147_dev9_mem_mmio.m_sram_write_flag = 0;
    *(_DWORD *)buffer = 0;
  }
  return buffer;
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (004020E0) --------------------------------------------------------
void *__fastcall rpc_1470201_handler(int fno, void *buffer, int length)
{
  if ( (unsigned int)fno >= 3 )
  {
    memset(buffer, 0, *((_DWORD *)buffer + 1));
    *((_DWORD *)buffer + 256) = -1;
  }
  else
  {
    memcpy(buffer, (const void *)(*(_DWORD *)buffer + 0xB0C00000), *((_DWORD *)buffer + 1));
    *((_DWORD *)buffer + 256) = 0;
  }
  return buffer;
}
