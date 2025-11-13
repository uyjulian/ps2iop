
#include "irx_imports.h"

IRX_ID("cdvd_xatapi_driver", 2, 3);

typedef struct _ata_cmd_state
{
  s32 type;
  union
  {
    void *buf;
    u8 *buf8;
    u16 *buf16;
  };
  u32 blkcount;
  s32 dir;
  s32 type_atapi;
  void *buf_atapi;
  u32 blkcount_atapi;
  u32 blksize_atapi;
  s32 dir_atapi;
} ata_cmd_state_t;

typedef struct _ata_devinfo
{
  s32 exists;
  s32 has_packet;
  u32 total_sectors;
  u32 security_status;
  u32 lba48;
} ata_devinfo_t;

struct dev5_speed_regs_
{
  vu16 unv00;
  vu16 r_spd_rev_1;
  vu16 r_spd_rev_3;
  vu16 unv06;
  vu16 unv08;
  vu16 unv0a;
  vu16 unv0c;
  vu16 r_spd_rev_8;
  vu16 unv10;
  vu16 unv12;
  vu16 unv14;
  vu16 unv16;
  vu16 unv18;
  vu16 unv1a;
  vu16 unv1c;
  vu16 unv1e;
  vu16 unv20;
  vu16 unv22;
  vu16 r_spd_dma_ctrl;
  vu16 unv26;
  vu16 r_spd_intr_stat;
  vu16 r_spd_intr_mask;
  vu16 unv2c;
  vu16 r_spd_pio_data;
  vu16 unv30;
  vu16 r_spd_xfr_ctrl;
  vu16 unv34;
  vu16 m_spd_unk36;
  vu16 r_spd_dbuf_stat;
  vu16 unv3a;
  vu16 unv3c;
  vu16 unv3e;
  vu16 r_spd_ata_data;
  vu16 r_spd_ata_error;
  vu16 r_spd_ata_nsector;
  vu16 r_spd_ata_sector;
  vu16 r_spd_ata_lcyl;
  vu16 r_spd_ata_hcyl;
  vu16 r_spd_ata_select;
  vu16 r_spd_ata_status;
  vu16 unv50;
  vu16 unv52;
  vu16 unv54;
  vu16 unv56;
  vu16 unv58;
  vu16 unv5a;
  vu16 r_spd_ata_control;
  vu16 unv5e;
  vu16 unv60;
  vu16 unv62;
  vu16 r_spd_if_ctrl;
  vu16 unv66;
  vu16 unv68;
  vu16 unv6a;
  vu16 unv6c;
  vu16 unv6e;
  vu16 r_spd_pio_mode;
  vu16 r_spd_mwdma_mode;
  vu16 r_spd_udma_mode;
};

struct dev5_fpga_regs_
{
  vu16 r_fpga_layer1;
  vu16 r_fpga_xfrdir;
  vu16 r_fpga_xfren;
  vu16 r_fpga_layer2;
  vu16 r_fpga_sl3bufe;
  vu16 r_fpga_sl3bufd;
  vu16 unv0c;
  vu16 unv0e;
  vu16 unv10;
  vu16 r_fpga_exbufd;
  vu16 r_fpga_exbufe;
  vu16 unv16;
  vu16 unv18;
  vu16 unv1a;
  vu16 unv1c;
  vu16 unv1e;
  vu16 unv20;
  vu16 unv22;
  vu16 unv24;
  vu16 unv26;
  vu16 unv28;
  vu16 unv2a;
  vu16 unv2c;
  vu16 unv2e;
  vu16 r_fpga_unk30;
  vu16 r_fpga_unk32;
  vu16 r_fpga_unk34;
  vu16 unvpad[2013];
  vu16 r_fpga_revision;
};

//-------------------------------------------------------------------------
// Function declarations

int do_atapi_cmd_inquiry_12h(s16 dev_nr);
int do_atapi_request_test_unit_ready(s16 dev_nr, int *errptr, int *ctrlptr);
int atapi_req_sense_get(s16 dev_nr, int *retptr);
int atapi_exec_cmd_request_sense_03h_unused(s16 dev_nr, int *retptr);
int do_start_stop_unit_1bh_unused(void);
int chgsys_callback_cb(int *mediaptr, int want_atapi);
int sceCdAtapi_SC(void);
int xatapi_15_exec_f6_f9_scsi(void);
int sceCdAtapi_BC(void);
int atapi_spin_status_get(int unused_arg1, void *buf);
int atapi_check_if_drive_ready(int check_nowait);
int sceFsDevctlBlkIO(s16 dev_nr, void *buf, void *rwbuf, unsigned int nsec, int secsize, int rwtype);
void expbay_device_reset(void);
int cd_atapi_intr_callback_cb(int cbarg);
void speedRegisterIntrDispatchCb(void *callback);
void sceDev5Init(void);
int atapi_eject_interrupt_handler(int is_eject, void *unused_arg2);
int xatapi_do_init(void);
int xatapi_nulldev0(void);
s64 xatapi_nulldev0_64bit(void);
int xatapi_dev_init(void);
int xatapi_dev_deinit(void);
int xatapi_2_terminate(int with_quit);
int xatapi_dev_devctl(iop_file_t *f, const char *name, int cmd, void *args, unsigned int arglen, void *buf, unsigned int buflen);
int _start(int ac, char **av);
int expbay_get_has_power(void);
void speedRegisterIntrCb(int intr, void *cb);
void speedRegisterPreDmaCb(int ctrl, void *cb);
void speedRegisterPostDmaCb(int ctrl, void *cb);
int speed_intr_dispatch(int flag);
void speedIntrEnable(s16 mask);
void speedIntrDisable(s16 mask);
int SpdDmaTransfer(unsigned int device, void *buf, u32 bcr_in, int dir);
int SpdDmaTransfer_extrans_1(unsigned int device, void *buf, u32 bcr_in, int dir);
int SpdDmaTransfer_extrans_2(unsigned int device, void *buf, u32 bcr_in, int dir);
int SpdDmaTransfer_extrans_3(unsigned int device, void *buf, u32 bcr_in, int dir);
void speedLEDCtl(int ctl);
void speed_init(void);
void speed_device_init(void);
void do_hex_dump(void *ptr, int len);
void ata_pre_dma_cb(void);
void ata_post_dma_cb(void);
int vReferEventFlagStatus(int ef, iop_event_info_t *info);
void xatapi_9_sceCdSpdAtaDmaStart(int dir);
void xatapi_10_sceCdSpdAtaDmaEnd(void);
void ata_pio_mode(int mode);
void ata_multiword_dma_mode(int mode);
void ata_ultra_dma_mode(int mode);
int ata_intr_cb(int flag);
void AtaEjectIntrHandle(void);
unsigned int AtaAlarmrHandle(void *usrdat);
int xatapi_14_set_speed_reg(int regaddr, u16 regval);
int xatapi_13_get_speed_reg(int regaddr);
int xatapi_11_sceAtaGetError(void);
int xatapi_12_get_ata_control(void);
int sceAtaGetError(void);
int ata_wait_busy1_busy(void);
int ata_wait_busy2_busy(void);
int ata_wait_bus_busy_busbusy(void);
int ata_device_select(int device);
int sceAtaExecCmd(void *buf, u32 blkcount, u16 feature, u16 nsector, u16 sector, u16 lcyl, u16 hcyl, u16 select, u16 command, u32 unk10);
int xatapi_5_sceAtaExecCmd(void *buf, u32 blkcount, u16 feature, u16 nsector, u16 sector, u16 lcyl, u16 hcyl, u16 select, u16 command, u32 unk10);
int sceCdAtapiExecCmd_local(s16 n, void *buf, int nsec, int secsize, void *pkt, unsigned int pkt_len, int proto);
int sceCdAtapiExecCmd(s16 n, void *buf, int nsec, int secsize, void *pkt, int pkt_len, int proto);
int xatapi_7_sceCdAtapiExecCmd(s16 n, void *buf, int nsec, int secsize, void *pkt, int pkt_len, int proto);
int ata_pio_transfer(ata_cmd_state_t *cmd_state);
int IoRun_atapi(ata_cmd_state_t *cmd_state);
int atapi_some_transfer_wrapper(char *buf, unsigned int blkcount, int dir);
int DmaRun_atapi(char *buf, int blkcount, int blksize, int dir);
int DmaRun_atapi_extrans1(char *buf, int blkcount, int blksize, int dir);
int DmaRun_atapi_extrans2(char *buf, int blkcount, int blksize, int dir);
void DmaRun_spck(char *buf, unsigned int secsize);
int sceAtaWaitResult(void);
int xatapi_6_sceAtaWaitResult(void);
int sceCdAtapiWaitResult_local(void);
int xatapi_8_sceCdAtapiWaitResult(void);
void ata_bus_reset_inner(void);
int ata_bus_reset(void);
int xatapi_4_sceAtaSoftReset(void);
int sceAtaFlushCache(int device);
int ata_device_identify(int device, void *info);
int ata_device_pkt_identify(int device, void *info);
int atapi_device_set_transfer_mode(int device, int type, int mode);
int ata_device_set_transfer_mode(int device, int type, int mode);
void ata_device_probe(ata_devinfo_t *devinfo);
void atapi_device_set_transfer_mode_outer(int device);
void ata_device_set_transfer_mode_outer(int device);
void ata_init_devices(ata_devinfo_t *devinfo);
void sceAtapiInit(int device);
void sceAtInterInit(void);
int create_event_flags(void);
void FpgaLayer1On(void);
void FpgaLayer1Off(void);
void FpgaLayer2On(void);
void FpgaLayer2Off(void);
void FpgaXfrenOn(void);
void FpgaXfrenOff(void);
void FpgaSpckmodeOn(void);
void FpgaSpckmodeOff(void);
void FpgaXfdir(int dir);
int FpgaGetRevision(void);
unsigned int do_fpga_add_unused8120(void);
int do_fpga_check_unk8148(void);
void FpgaCheckWriteBuffer(void);
void FpgaCheckWriteBuffer2(void);
void FpgaClearBuffer(void);
int Mpeg2CheckPadding(char *buf, unsigned int bufsize, int *retptr, int *pesscramblingpackptr);
int Mpeg2CheckScramble(char *buf, unsigned int bufsize);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_xatapi;
int g_devctl_retonly_unset = 0; // weak
vu16 *g_dev9_reg_1460 = (vu16 *)0xBF801460;
vu16 *g_dev9_reg_power = (vu16 *)0xBF80146C;
int (*p_dev5_intr_cb)(u32) = NULL; // weak
iop_device_ops_t ata_ioman_devops =
{
  (void *)&xatapi_dev_init,
  (void *)&xatapi_dev_deinit,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0_64bit,
  (void *)&xatapi_dev_devctl,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0,
  (void *)&xatapi_nulldev0
};
iop_device_t ata_ioman_device = { "xatapi", 268435472u, 1u, "CD-ROM_ATAPI", &ata_ioman_devops }; // idb
int g_reset_scrambling_pack = 0; // weak
int g_pes_scrambling_control_pack = 0; // idb
int g_dma_mode_value = 1; // weak
int g_dma_speed_value = 2; // idb
int g_should_wait_for_dma_flag = 0; // weak
int g_is_wait_busy = 0; // weak
int g_xatapi_verbose = 0; // weak
int g_ata_devinfo_init = 0; // weak
int g_bf40200a_is_set_ptr; // weak
u32 *g_cd_sc_ffffffd9_ptr;
int g_is_in_read_info; // weak
int g_io_event_flag; // idb
int g_adma_evfid; // idb
int g_acmd_evfid; // idb
int g_dma_lock_sema; // idb
void *g_dev5_intr_cbs[16];
void *g_dev5_predma_cbs[4];
void *g_dev5_postdma_cbs[4];
int g_atapi_event_flag; // idb
ata_devinfo_t atad_devinfo[2]; // weak
ata_cmd_state_t atad_cmd_state; // weak
int ata_param[128]; // weak
int g_atapi_xfer_buf[130]; // weak
struct dev5_speed_regs_ dev5_speed_regs; // weak
struct dev5_fpga_regs_ dev5_fpga_regs; // weak


//----- (00400000) --------------------------------------------------------
int do_atapi_cmd_inquiry_12h(s16 dev_nr)
{
  int trycnt; // $s1
  int retres; // $s0
  char pkt[32]; // [sp+20h] [-80h] BYREF
  char outbuf[56]; // [sp+40h] [-60h] BYREF

  retres = 1;
  for ( trycnt = 0; retres && trycnt < 16; trycnt += 1 )
  {
    memset(pkt, 0, 12);
    pkt[0] = 0x12;
    pkt[4] = 0x38;
    retres = sceCdAtapiExecCmd_local(dev_nr, outbuf, 1, 56, pkt, 0xCu, 2);
    if ( !retres )
    {
      retres = sceCdAtapiWaitResult_local();
      if ( retres )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("Atapi Drive ATAPI_CMD_READ_EXT_INFO  NG\n");
        DelayThread(10000);
      }
    }
  }
  if ( retres )
    return retres;
  do_hex_dump(outbuf, 56);
  return strncmp(&outbuf[32], "BOOT", 4) != 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (0040013C) --------------------------------------------------------
int do_atapi_request_test_unit_ready(s16 dev_nr, int *errptr, int *ctrlptr)
{
  int result; // $v0
  int retres; // $s0
  int ata_control; // $v1
  char pkt[16]; // [sp+20h] [-10h] BYREF

  *errptr = 0;
  *ctrlptr = 0;
  memset(pkt, 0, 12);
  pkt[0] = 0;
  result = xatapi_7_sceCdAtapiExecCmd(dev_nr, 0, 0, 0, pkt, 12, 1);
  if ( !result )
  {
    retres = xatapi_8_sceCdAtapiWaitResult();
    *errptr = (u8)xatapi_11_sceAtaGetError();
    ata_control = (u8)xatapi_12_get_ata_control();
    result = retres;
    *ctrlptr = ata_control;
  }
  return result;
}

//----- (004001F0) --------------------------------------------------------
int atapi_req_sense_get(s16 dev_nr, int *retptr)
{
  int result; // $v0
  char pkt[16]; // [sp+20h] [-50h] BYREF
  char outbuf[64]; // [sp+30h] [-40h] BYREF

  *retptr = 0;
  memset(pkt, 0, 12);
  pkt[0] = 3;
  pkt[4] = 18;
  result = xatapi_7_sceCdAtapiExecCmd(dev_nr, outbuf, 1, 18, pkt, 12, 2);
  if ( !result )
  {
    result = xatapi_8_sceCdAtapiWaitResult();
    if ( !result )
    {
      result = 0;
      *retptr = ((outbuf[2] & 0xF) << 16) | ((u8)outbuf[12] << 8) | (u8)outbuf[13];
    }
  }
  return result;
}

//----- (004002AC) --------------------------------------------------------
int atapi_exec_cmd_request_sense_03h_unused(s16 dev_nr, int *retptr)
{
  int result; // $v0
  char pkt[16]; // [sp+20h] [-50h] BYREF
  char outbuf[64]; // [sp+30h] [-40h] BYREF

  *retptr = 0;
  memset(pkt, 0, 12);
  pkt[0] = 3;
  pkt[4] = 0x12;
  result = sceCdAtapiExecCmd_local(dev_nr, outbuf, 1, 18, pkt, 0xCu, 2);
  if ( !result )
  {
    result = sceCdAtapiWaitResult_local();
    if ( !result )
    {
      result = 0;
      *retptr = ((outbuf[2] & 0xF) << 16) | ((u8)outbuf[12] << 8) | (u8)outbuf[13];
    }
  }
  return result;
}

//----- (00400368) --------------------------------------------------------
int do_start_stop_unit_1bh_unused(void)
{
  int trycnt1; // $s1
  int retres; // $s0
  int trycnt2; // $s1
  char pkt[16]; // [sp+20h] [-10h] BYREF

  retres = 1;
  for ( trycnt1 = 0; trycnt1 < 16 && retres && retres != -550; trycnt1 += 1 )
  {
    memset(pkt, 0, 12);
    pkt[0] = 0x1B;
    pkt[4] = 2;
    pkt[5] = 0;
    retres = sceCdAtapiExecCmd_local(0, 0, 0, 0, pkt, 0xCu, 1);
    if ( !retres )
    {
      retres = sceCdAtapiWaitResult_local();
      if ( retres )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("Atapi Drive EJECT NG\n");
        DelayThread(10000);
      }
      else
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("Atapi Drive EJECT OK\n");
      }
    }
  }
  if ( !retres )
  {
    retres = 1;
    for ( trycnt2 = 0; trycnt2 < 16 && retres && retres != -550; trycnt2 += 1 )
    {
      memset(pkt, 0, 12);
      pkt[0] = 0x1B;
      pkt[4] = 3;
      pkt[5] = 0;
      retres = sceCdAtapiExecCmd_local(0, 0, 0, 0, pkt, 0xCu, 1);
      if ( !retres )
      {
        retres = sceCdAtapiWaitResult_local();
        if ( retres )
        {
          if ( g_xatapi_verbose > 0 )
            Kprintf("Atapi Drive Spindle  Start  NG %d\n", trycnt2);
          DelayThread(10000);
          ++trycnt2;
          continue;
        }
        if ( g_xatapi_verbose > 0 )
          Kprintf("Atapi Drive Spindle  Start  OK\n");
      }
    }
  }
  if ( g_xatapi_verbose > 0 )
  {
    Kprintf("  PS2 Eject On Atapi Unit Dummy Eject Ret %d\n", retres);
  }
  return retres;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004005C8) --------------------------------------------------------
int chgsys_callback_cb(int *mediaptr, int want_atapi)
{
  int trycnt2; // $s1
  int tryres1; // $s0
  int maskchk; // $s0
  int mediaptr_tmp; // $v1
  int trycnt4; // $s1
  int retres; // $s0
  int trycnt3; // $s1
  int trycnt1; // $s1
  char pkt[16]; // [sp+20h] [-20h] BYREF
  char outbuf[6]; // [sp+30h] [-10h] BYREF

  *mediaptr = 4;
  if ( want_atapi )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("Ps2 Drive Spindle -> Atapi \n");
    retres = 1;
    for ( trycnt1 = 0; trycnt1 < 10 && retres && retres != -550; trycnt1 += 1 )
    {
      memset(pkt, 0, 12);
      pkt[0] = 0x1B;
      pkt[4] = 3;
      pkt[5] = 0;
      retres = sceCdAtapiExecCmd(0, 0, 0, 0, pkt, 12, 1);
      if ( !retres )
      {
        retres = sceCdAtapiWaitResult_local();
        if ( retres )
        {
          if ( g_xatapi_verbose > 0 )
            Kprintf("Atapi Drive Spindle Start NG %d\n", trycnt1);
          DelayThread(10000);
        }
        else
        {
          if ( g_xatapi_verbose > 0 )
            Kprintf("Atapi Drive Spindle Start OK\n");
        }
      }
    }
    return retres;
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("Atapi Drive Spindle -> Ps2\n");
  tryres1 = 1;
  for ( trycnt2 = 0; trycnt2 < 16 && tryres1 && tryres1 != -550; trycnt2 += 1 )
  {
    memset(pkt, 0, 12);
    pkt[0] = 0xF6;
    pkt[2] = 0xA0;
    pkt[8] = 6;
    tryres1 = sceCdAtapiExecCmd_local(0, outbuf, 1, 6, pkt, 0xCu, 2);
    if ( !tryres1 )
    {
      tryres1 = sceCdAtapiWaitResult_local();
      if ( tryres1 )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("Atapi Drive ATAPI_CMD_READ_EXT_INFO  NG\n");
        DelayThread(10000);
      }
    }
  }
  if ( !tryres1 )
  {
    maskchk = (((u8)outbuf[5] >> 1) ^ 1) & 1;
    if ( (outbuf[3] & 0x10) != 0 )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive Media found.\n");
      memset(pkt, 0, 12);
      pkt[0] = 0xF6;
      pkt[2] = 0xA2;
      pkt[8] = 8;
      if ( !sceCdAtapiExecCmd_local(0, outbuf, 1, 8, pkt, 0xCu, 2) && !sceCdAtapiWaitResult_local() )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("Atapi Drive Media DVD:%d.\n", outbuf[5] & 0x20);
        mediaptr_tmp = 2;
        if ( (outbuf[5] & 0x20) != 0 )
          mediaptr_tmp = 3;
        *mediaptr = mediaptr_tmp;
      }
    }
    else
    {
      if ( g_xatapi_verbose > 0 )
      {
        Kprintf("Atapi Drive No Media or Now checking.\n");
        if ( g_xatapi_verbose > 0 )
          Kprintf("Atapi Drive No Media or No SpinUp.\n");
      }
      *mediaptr = 4;
    }
    if ( maskchk )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive Spin Up.\n");
      retres = 1;
      for ( trycnt4 = 0; trycnt4 < 16 && retres && retres != -550; trycnt4 += 1 )
      {
        memset(pkt, 0, 12);
        pkt[0] = 0x1B;
        pkt[5] = 0;
        retres = sceCdAtapiExecCmd(0, 0, 0, 0, pkt, 12, 1);
        if ( !retres )
        {
          retres = sceCdAtapiWaitResult_local();
          if ( retres )
          {
            if ( g_xatapi_verbose > 0 )
              Kprintf("Atapi Drive Spindle  Stop  NG\n");
            DelayThread(10000);
          }
          else
          {
            if ( g_xatapi_verbose > 0 )
              Kprintf("Atapi Drive Spindle  Stop  OK\n");
          }
        }
      }
      return retres;
    }
    if ( g_xatapi_verbose > 0 )
      Kprintf("Atapi Drive Not Spin Up.\n");
    retres = 1;
    for ( trycnt3 = 0; trycnt3 < 16 && retres && retres != -550; trycnt3 += 1 )
    {
      memset(pkt, 0, 12);
      pkt[0] = 0x1B;
      pkt[4] = 2;
      pkt[5] = 0;
      retres = sceCdAtapiExecCmd(0, 0, 0, 0, pkt, 12, 1);
      if ( !retres )
      {
        retres = sceCdAtapiWaitResult_local();
        if ( retres )
        {
          if ( g_xatapi_verbose > 0 )
            Kprintf("Atapi Drive EJECT NG\n");
          DelayThread(10000);
        }
        else
        {
          if ( g_xatapi_verbose > 0 )
            Kprintf("Atapi Drive EJECT OK\n");
          *mediaptr = 256;
        }
      }
    }
    return retres;
  }
  return tryres1;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00400BB4) --------------------------------------------------------
int sceCdAtapi_SC(void)
{
  int trycnt; // $s1
  int retres; // $s0
  char pkt[16]; // [sp+20h] [-10h] BYREF

  memset(pkt, 0, 12);
  retres = 1;
  pkt[0] = 0xF9;
  pkt[2] = 0xB1;
  pkt[8] = 0;
  for ( trycnt = 0; trycnt < 10 && retres; trycnt += 1 )
  {
    retres = sceCdAtapiExecCmd_local(0, 0, 0, 0, pkt, 0xCu, 1);
    if ( retres || (retres = sceCdAtapiWaitResult_local()) != 0 )
      DelayThread(10000);
  }
  if ( !retres )
  {
    *g_cd_sc_ffffffd9_ptr = 0;
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceCdAtapi SC OK\n");
    return retres;
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdAtapi SC fail\n");
  return retres;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00400CEC) --------------------------------------------------------
int xatapi_15_exec_f6_f9_scsi(void)
{
  int trycnt1; // $s1
  int retres1; // $s0
  int trycnt2; // $s1
  int retres2; // $s0
  char pkt[16]; // [sp+20h] [-30h] BYREF
  char outbuf[32]; // [sp+30h] [-20h] BYREF

  memset(pkt, 0, 12);
  retres1 = 1;
  pkt[0] = 0xF6;
  pkt[2] = 0xB1;
  pkt[8] = 6;
  for ( trycnt1 = 0; trycnt1 < 4 && retres1; trycnt1 += 1 )
  {
    retres1 = sceCdAtapiExecCmd_local(0, outbuf, 1, 6, pkt, 0xCu, 2);
    if ( retres1 || (retres1 = sceCdAtapiWaitResult_local()) != 0 )
      DelayThread(10000);
  }
  if ( retres1 && (outbuf[4] & 0x80) == 0 )
    return retres1;
  memset(pkt, 0, 12);
  retres2 = 1;
  pkt[0] = 0xF9;
  pkt[2] = 0xB2;
  pkt[8] = 0;
  for ( trycnt2 = 0; trycnt2 < 10 && retres2; trycnt2 += 1 )
  {
    retres2 = sceCdAtapiExecCmd_local(0, 0, 0, 0, pkt, 0xCu, 1);
    if ( !retres2 )
    {
      retres2 = sceCdAtapiWaitResult_local();
      if ( !retres2 )
        continue;
    }
    DelayThread(10000);
  }
  return retres2;
}

//----- (00400E74) --------------------------------------------------------
int sceCdAtapi_BC(void)
{
  int trycnt1; // $s1
  int retres1; // $s0
  int trycnt2; // $s1
  int retres2; // $s0
  int trycnt3; // $s1
  int retres3; // $s0
  int trycnt4; // $s1
  int retres4; // $s0
  int trycnt5; // $s1
  int trycnt6; // $s1
  int trycnt7; // $s1
  int trycnt8; // $s1
  int retresx; // $s5
  int retres5; // $s0
  char pkt[16]; // [sp+20h] [-58h] BYREF
  char outbuf[16]; // [sp+30h] [-48h] BYREF
  iop_event_info_t efinfo; // [sp+50h] [-28h] BYREF
  u32 waresontmp; // [sp+70h] [-8h] BYREF
  u32 efbits; // [sp+74h] [-4h] BYREF
  int flg;

  memset(pkt, 0, 12);
  retres1 = 1;
  pkt[0] = 0xF6;
  pkt[2] = 0xB1;
  pkt[8] = 6;
  for ( trycnt1 = 0; trycnt1 < 10 && retres1; trycnt1 += 1 )
  {
    retres1 = sceCdAtapiExecCmd_local(0, outbuf, 1, 6, pkt, 0xCu, 2);
    if ( retres1 || (retres1 = sceCdAtapiWaitResult_local()) != 0 )
      DelayThread(10000);
  }
  if ( !retres1 || (outbuf[4] & 0x80) != 0 )
  {
    memset(pkt, 0, 12);
    retres2 = 1;
    pkt[0] = 0xF9;
    pkt[2] = 0xB2;
    pkt[8] = 0;
    for ( trycnt2 = 0; trycnt2 < 10 && retres2; trycnt2 += 1 )
    {
      retres2 = sceCdAtapiExecCmd_local(0, 0, 0, 0, pkt, 0xCu, 1);
      if ( !retres2 )
      {
        retres2 = sceCdAtapiWaitResult_local();
        if ( !retres2 )
          continue;
      }
      DelayThread(10000);
    }
  }
  memset(pkt, 0, 12);
  retres3 = 1;
  pkt[0] = 0xF6;
  pkt[2] = 0xB1;
  pkt[8] = 6;
  for ( trycnt3 = 0; trycnt3 < 10 && retres3; trycnt3 += 1 )
  {
    retres3 = sceCdAtapiExecCmd_local(0, outbuf, 1, 6, pkt, 0xCu, 2);
    if ( retres3 || (retres3 = sceCdAtapiWaitResult_local()) != 0 )
      DelayThread(10000);
  }
  if ( !retres3 )
  {
    if ( (outbuf[4] & 0x81) != 0 )
    {
      *g_cd_sc_ffffffd9_ptr = 1;
      return 1;
    }
  }
  memset(pkt, 0, 12);
  retres4 = 1;
  pkt[0] = 0xF6;
  pkt[2] = 0xB0;
  pkt[8] = 16;
  for ( trycnt4 = 0; trycnt4 < 10 && retres4; trycnt4 += 1 )
  {
    retres4 = sceCdAtapiExecCmd_local(0, outbuf, 1, 16, pkt, 0xCu, 2);
    if ( retres4 || (retres4 = sceCdAtapiWaitResult_local()) != 0 )
      DelayThread(10000);
  }
  if ( retres4 )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceCdAtapi BC 0 fail\n");
  }
  else
  {
    if ( g_should_wait_for_dma_flag && !ReferEventFlagStatus(g_adma_evfid, &efinfo) && !efinfo.currBits )
      SetEventFlag(g_adma_evfid, 1u);
    SetEventFlag(g_acmd_evfid, 1u);
    retres4 = 0;
    for ( trycnt5 = 0; trycnt5 < 100 && !retres4; trycnt5 += 1 )
    {
#if 0
      retres4 = sceCdResetWakeupReason((u32 *)outbuf, &waresontmp);
#else
      retres4 = 0;
      waresontmp = 0;
#endif
      if ( !retres4 || waresontmp )
        DelayThread(10000);
    }
    flg = 0;
    if ( !retres4 )
    {
      if ( g_xatapi_verbose >= 0 )
        Kprintf("sceCdAtapi BC 1 fail\n");
    }
    else
    {
      DelayThread(10000);
      retres4 = 0;
      for ( trycnt6 = 0; trycnt6 < 100 && !retres4; trycnt6 += 1 )
      {
#if 0
        retres4 = cdvdman_169((u32 *)outbuf, &waresontmp);
#else
        retres4 = 0;
        waresontmp = 0;
#endif
        if ( !retres4 || waresontmp )
          DelayThread(10000);
      }
      if ( !retres4 )
      {
        if ( g_xatapi_verbose >= 0 )
          Kprintf("sceCdAtapi BC 2 fail\n");
      }
      else
      {
        if ( g_should_wait_for_dma_flag )
          WaitEventFlag(g_adma_evfid, 1u, 16, &efbits);
        
        retres4 = 1;
        WaitEventFlag(g_acmd_evfid, 1u, 16, &efbits);
        memset(pkt, 0, 12);
        pkt[0] = 0xF9;
        pkt[2] = 0xB0;
        pkt[8] = 16;
        for ( trycnt7 = 0; trycnt7 < 10 && retres4; trycnt7 += 1 )
        {
          retres4 = sceCdAtapiExecCmd_local(0, outbuf, 1, 16, pkt, 0xCu, 3);
          if ( retres4 || (retres4 = sceCdAtapiWaitResult_local()) != 0 )
            DelayThread(10000);
        }
        if ( retres4 )
        {
          if ( g_xatapi_verbose > 0 )
            Kprintf("sceCdAtapi BC 3 fail\n");
        }
        else
        {
          if ( g_xatapi_verbose > 0 )
            Kprintf("sceCdAtapi BC OK\n");
        }
        flg = 1;
      }
    }
    if ( !flg )
    {
      if ( g_should_wait_for_dma_flag )
        WaitEventFlag(g_adma_evfid, 1u, 16, &efbits);
      WaitEventFlag(g_acmd_evfid, 1u, 16, &efbits);
    }
  }
  memset(pkt, 0, 12);
  retresx = retres4;
  retres5 = 1;
  pkt[0] = 0xF6;
  pkt[2] = 0xB1;
  pkt[8] = 6;
  for ( trycnt8 = 0; trycnt8 < 10 && retres5; trycnt8 += 1 )
  {
    retres5 = sceCdAtapiExecCmd_local(0, outbuf, 1, 6, pkt, 0xCu, 2);
    if ( retres5 || (retres5 = sceCdAtapiWaitResult_local()) != 0 )
      DelayThread(10000);
  }
  if ( retres5 )
    return retresx;
  *g_cd_sc_ffffffd9_ptr = (outbuf[4] & 0x81) != 0;
  return retresx;
}
// 40A640: using guessed type int g_should_wait_for_dma_flag;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00401514) --------------------------------------------------------
int atapi_spin_status_get(int unused_arg1, void *buf)
{
  int result; // $v0
  char pkt[16]; // [sp+20h] [-10h] BYREF

  (void)unused_arg1;
  memset(pkt, 0, 12);
  pkt[0] = 0xF6;
  pkt[2] = 0xA0;
  pkt[8] = 6;
  result = xatapi_7_sceCdAtapiExecCmd(0, buf, 1, 6, pkt, 12, 2);
  if ( !result )
    return xatapi_8_sceCdAtapiWaitResult();
  return result;
}

//----- (00401598) --------------------------------------------------------
int atapi_check_if_drive_ready(int check_nowait)
{
  u8 ata_control; // $v0
  int ata_ctrl_tmp; // $s0
  int req_test_unit_ready_tmp1; // $s1
  char spinstatus_tmp[6]; // [sp+10h] [-18h] BYREF
  int drive_err; // [sp+18h] [-10h] BYREF
  int unitreadyctrl; // [sp+1Ch] [-Ch] BYREF
  int senseret; // [sp+20h] [-8h] BYREF

  drive_err = 0;
  if ( g_xatapi_verbose > 0 )
    Kprintf("Atapi Drive Ready Call %d\n", check_nowait);
  ata_control = xatapi_12_get_ata_control();
  ata_ctrl_tmp = ata_control;
  if ( g_xatapi_verbose > 0 )
    Kprintf("Atapi Drive Ready %04x\n", ata_control);
  if ( !check_nowait )
  {
    req_test_unit_ready_tmp1 = -1;
    while ( req_test_unit_ready_tmp1 < 0 )
    {
      while ( (ata_ctrl_tmp & 0xC0) != 64 )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("Drive Not Ready %04x\n", ata_ctrl_tmp);
        DelayThread(2000);
        ata_ctrl_tmp = xatapi_12_get_ata_control();
      }
      req_test_unit_ready_tmp1 = do_atapi_request_test_unit_ready(0, &drive_err, &unitreadyctrl);
      if ( req_test_unit_ready_tmp1 < 0 )
        DelayThread(100000);
      if ( !atapi_req_sense_get(0, &senseret) )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("ReqSense %08x\n", senseret);
        if ( (senseret & 0xFFFFFF00) == 0x23A00 )
          break;
      }
      if ( !atapi_spin_status_get(0, spinstatus_tmp) )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("Spin Status 3:%02x 5:%02x\n", (u8)spinstatus_tmp[3], (u8)spinstatus_tmp[5]);
        if ( (spinstatus_tmp[3] & 2) != 0 )
          break;
        if ( (spinstatus_tmp[3] & 0x80) != 0 )
          break;
      }
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive err %08x\n", drive_err);
    }
    return 2;
  }
  if ( (ata_ctrl_tmp & 0xC0) == 64 )
  {
    if ( do_atapi_request_test_unit_ready(0, &drive_err, &unitreadyctrl) >= 0 )
    {
      if ( !drive_err )
        return 2;
    }
  }
  return 6;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004017A8) --------------------------------------------------------
int sceFsDevctlBlkIO(s16 dev_nr, void *buf, void *rwbuf, unsigned int nsec, int secsize, int rwtype)
{
  char *rwbuf_tmp; // $s3
  unsigned int nsec_tmp; // $s4
  int retres1; // $s0
  int rwchar; // $a1
  int seccnt; // $s1
  int trycnt1; // $s2
  char scsirwtype; // $v1
  int trycnt1x; // $v0
  char pkt_stk[16]; // [sp+20h] [-18h] BYREF
  char *pkt; // [sp+30h] [-8h]

  rwbuf_tmp = (char *)rwbuf;
  retres1 = 0;
  if ( g_xatapi_verbose > 0 )
  {
    rwchar = 'r';
    if ( rwtype )
      rwchar = 'w';
    Kprintf("dma %c %08x, nsec %d\n", rwchar, rwbuf, nsec);
  }
  pkt = pkt_stk;
  for ( nsec_tmp = nsec; !retres1 && nsec_tmp; nsec_tmp -= seccnt )
  {
    seccnt = nsec_tmp;
    if ( nsec_tmp >= 0x21 )
      seccnt = 32;
    trycnt1 = 3;
    while ( 1 )
    {
      xatapi_9_sceCdSpdAtaDmaStart(rwtype);
      memset(pkt_stk, 0, 12);
      scsirwtype = 0x2A;
      if ( !rwtype )
        scsirwtype = 0x28;
      pkt_stk[0] = scsirwtype;
      pkt_stk[2] = ((uiptr)rwbuf_tmp >> 24) & 0xFF;
      pkt_stk[3] = ((uiptr)rwbuf_tmp >> 16) & 0xFF;
      pkt_stk[4] = ((uiptr)rwbuf_tmp >> 8) & 0xFF;
      pkt_stk[5] = ((uiptr)rwbuf_tmp) & 0xFF;
      pkt_stk[8] = seccnt;
      retres1 = xatapi_7_sceCdAtapiExecCmd(dev_nr, buf, seccnt, secsize, pkt, 12, 4);
      if ( retres1 )
      {
        xatapi_10_sceCdSpdAtaDmaEnd();
        break;
      }
      retres1 = xatapi_8_sceCdAtapiWaitResult();
      xatapi_10_sceCdSpdAtaDmaEnd();
      trycnt1x = trycnt1;
      if ( retres1 == -510 )
      {
        --trycnt1;
        if ( trycnt1x > 0 )
          continue;
      }
      break;
    }
    rwbuf_tmp += seccnt;
    buf = (char *)buf + seccnt * secsize;
  }
  return retres1;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00401958) --------------------------------------------------------
void expbay_device_reset(void)
{
  if ( (*g_dev9_reg_power & 4) != 0 )
  {
    Kprintf("xatapi already Power On\n");
    *g_dev9_reg_1460 |= 2u;
  }
  else
  {
    Kprintf("xatapi Power On Start\n");
    *g_dev9_reg_power = (*g_dev9_reg_power & 0xFFFA) | 4;
    DelayThread(500000);
    *g_dev9_reg_1460 |= 2u;
    *g_dev9_reg_power |= 1u;
    DelayThread(500000);
  }
}

//----- (00401A38) --------------------------------------------------------
int cd_atapi_intr_callback_cb(int cbarg)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("dev5 interrupt\n");
  if ( p_dev5_intr_cb )
    p_dev5_intr_cb(cbarg);
  if ( g_xatapi_verbose > 0 )
    Kprintf("dev5 interrupt end\n");
  return 1;
}
// 40A5A8: using guessed type int (*p_dev5_intr_cb)(u32);
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00401AB8) --------------------------------------------------------
void speedRegisterIntrDispatchCb(void *callback)
{
  p_dev5_intr_cb = (int (*)(u32))callback;
}
// 40A5A8: using guessed type int (*p_dev5_intr_cb)(u32);

//----- (00401AC8) --------------------------------------------------------
void sceDev5Init(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("dev5 atapi Init start\n");
  sceCdSC(0xFFFFFFE5, (int *)cd_atapi_intr_callback_cb);
  speed_device_init();
  speed_init();
  if ( g_xatapi_verbose > 0 )
    Kprintf("dev5 atapi Init end\n");
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00401B48) --------------------------------------------------------
int atapi_eject_interrupt_handler(int is_eject, void *unused_arg2)
{
  u32 buzzerres[2]; // [sp+10h] [-8h] BYREF

  if ( is_eject == 1 )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("Eject intr : media removal\n", unused_arg2);
    return sceCdBuzzerCtl(buzzerres);
  }
  return 1;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00401B94) --------------------------------------------------------
int xatapi_do_init(void)
{
  int (*oldcb_x)(int, void *); // $s0
  int (*oldcb)(int, void *); // $a0
  u32 *sc_tmp; // [sp+10h] [-10h] BYREF
  u32 trylocktmp; // [sp+14h] [-Ch] BYREF
  u32 traylock_ret[2]; // [sp+18h] [-8h] BYREF

  if ( !create_event_flags() )
    return 0;
  sceCdSC(0xFFFFFFD9, (int *)&sc_tmp);
  g_cd_sc_ffffffd9_ptr = sc_tmp;
  sceCdSC(0xFFFFFFD7, (int *)&sc_tmp);
  g_bf40200a_is_set_ptr = (int)sc_tmp;
  oldcb_x = (int (*)(int, void *))sceCdSetAtapiEjectCallback(
                                               (int (*)(int, void *))atapi_eject_interrupt_handler,
                                               0);
  if ( !sceCdGetMediumRemoval(&trylocktmp, traylock_ret) )
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("xatapi:sceCdGetMediumRemoval NG(%x) !!\n", traylock_ret[0]);
    trylocktmp = 0;
  }
  if ( trylocktmp )
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("xatapi:Tray locked !!\n");
  }
  else if ( sceCdSetMediumRemoval(1u, traylock_ret) )
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("xatapi:Tray lock\n");
  }
  else
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("xatapi:Tray lock NG(%x) !!\n", traylock_ret[0]);
    trylocktmp = 0;
  }
  expbay_device_reset();
  if ( g_xatapi_verbose >= 0 )
    Kprintf("xatapi Dev5->Rainbow\n");
  sceCdChgSys(1u);
  if ( g_xatapi_verbose > 0 )
  {
    Kprintf("xatapi Dev5->Rainbow end\n");
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceDev5Init Call\n");
  }
  sceDev5Init();
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceAtInterInit Call\n");
  sceAtInterInit();
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceAtapiInit Call\n");
  sceAtapiInit(0);
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceAtapiInit end\n");
  sceCdSC(0xFFFFFFE1, (int *)chgsys_callback_cb);
  DelayThread(10000);
  if ( !trylocktmp )
  {
    if ( !sceCdSetMediumRemoval(0, traylock_ret) )
    {
      if ( g_xatapi_verbose >= 0 )
        Kprintf("xatapi:Tray unlock NG(%x) !!\n", traylock_ret[0]);
      trylocktmp = 0;
    }
    else
    {
      if ( g_xatapi_verbose >= 0 )
        Kprintf("xatapi:Tray unlock\n");
    }
  }
  oldcb = oldcb_x;
  sceCdSetAtapiEjectCallback(oldcb, 0);
  return 1;
}
// 40A648: using guessed type int g_xatapi_verbose;
// 40A650: using guessed type int g_bf40200a_is_set_ptr;

//----- (00401E88) --------------------------------------------------------
int xatapi_nulldev0(void)
{
  printf("nulldev0 call\n");
  return -5;
}

//----- (00401EB0) --------------------------------------------------------
s64 xatapi_nulldev0_64bit(void)
{
  printf("nulldev0 call\n");
  return -5LL;
}

//----- (00401EDC) --------------------------------------------------------
int xatapi_dev_init(void)
{
  return 0;
}

//----- (00401EE4) --------------------------------------------------------
int xatapi_dev_deinit(void)
{
  return 0;
}

//----- (00401EEC) --------------------------------------------------------
int xatapi_2_terminate(int with_quit)
{
  int sc_tmp[2]; // [sp+10h] [-8h] BYREF

  (void)with_quit;
  sc_tmp[0] = 0;
  sceCdSC(0xFFFFFFE1, sc_tmp);
  sceCdSC(0xFFFFFFE5, sc_tmp);
  sceCdSC(0xFFFFFFE0, sc_tmp);
  sceCdSC(0xFFFFFFDF, sc_tmp);
  sceCdSC(0xFFFFFFE4, sc_tmp);
  Kprintf("libxatapi_terminate\n");
  return 0;
}

//----- (00401F60) --------------------------------------------------------
int xatapi_dev_devctl(
        iop_file_t *f,
        const char *name,
        int cmd,
        void *args,
        unsigned int arglen,
        void *buf,
        unsigned int buflen)
{
  int retres1; // $s1
  int efres; // $v1
  int ata_control; // $v0
  int execres; // $v0
  int bcres; // $v0
  int argval1; // $v1
  int argmask1; // $v0
  u32 efbits[2]; // [sp+20h] [-8h] BYREF

  (void)name;
  retres1 = 0;
  if ( g_xatapi_verbose > 0 )
    Kprintf("xatapi devctl: cmd:%08x arg:%d\n", cmd, *(u32 *)args);
  efres = PollEventFlag(g_io_event_flag, 1u, 0, efbits);
  if ( cmd == 0x439B && efres == -421 && *(u32 *)args == 1 )
  {
    *(u32 *)buf = 6;
    return 0;
  }
  WaitEventFlag(g_io_event_flag, 1u, 16, efbits);
  if ( g_devctl_retonly_unset )
  {
    SetEventFlag(g_io_event_flag, 1u);
    return -5;
  }
  switch ( cmd )
  {
    case 0x4332:
      retres1 = -22;
      if ( *(u32 *)args )
      {
        switch ( *((u32 *)args + 1) )
        {
          case 2:
          case 5:
            if ( !buflen )
            {
              retres1 = -22;
              break;
            }
            execres = xatapi_7_sceCdAtapiExecCmd(
                        f->unit,
                        buf,
                        1,
                        buflen,
                        (char *)args + 8,
                        *(u32 *)args,
                        *((u32 *)args + 1));
            retres1 = execres;
            break;
          case 3:
          case 6:
            if ( *((u32 *)args + 250) )
            {
              execres = xatapi_7_sceCdAtapiExecCmd(
                          f->unit,
                          (char *)args + 40,
                          1,
                          *((u32 *)args + 250),
                          (char *)args + 8,
                          *(u32 *)args,
                          *((u32 *)args + 1));
              retres1 = execres;
            }
            else
            {
              retres1 = -22;
            }
            break;
          default:
            execres = xatapi_7_sceCdAtapiExecCmd(
                        f->unit,
                        0,
                        0,
                        0,
                        (char *)args + 8,
                        *(u32 *)args,
                        *((u32 *)args + 1));
            retres1 = execres;
            break;
        }
        if ( !retres1 )
          retres1 = xatapi_8_sceCdAtapiWaitResult();
      }
      break;
    case 0x4333:
      ata_control = (u8)xatapi_11_sceAtaGetError();
      *(u32 *)buf = ata_control;
      break;
    case 0x4334:
      ata_control = (u8)xatapi_12_get_ata_control();
      *(u32 *)buf = ata_control;
      break;
    case 0x4335:
      bcres = sceCdAtapi_BC();
      retres1 = bcres;
      if ( bcres == 1 )
        retres1 = 0;
      break;
    case 0x4336:
      retres1 = sceCdAtapi_SC();
      break;
    case 0x4337: //?
      g_xatapi_verbose = *(u32 *)args;
      break;
    case 0x4338:
      g_reset_scrambling_pack = *(u32 *)args;
      if ( g_reset_scrambling_pack )
      {
        g_pes_scrambling_control_pack = 0;
      }
      else if ( g_xatapi_verbose > 0 )
      {
        Kprintf("pes scrambling control pack = %d\n", g_pes_scrambling_control_pack);
      }
      break;
    case 0x4339:
      DmaRun_spck((char *)args, arglen);
      break;
    case 0x433A:
      argval1 = *(u32 *)args;
      if ( (*(u32 *)args & 0x40) != 0 )
      {
        g_dma_mode_value = 1;
        argmask1 = argval1 & 7;
      }
      else
      {
        argmask1 = *(u32 *)args & 7;
        g_dma_mode_value = 0;
      }
      g_dma_speed_value = argmask1;
      atapi_device_set_transfer_mode_outer(0);
      break;
    case 0x433B:
      if ( buf && buflen >= 2 )
        *(u16 *)buf = FpgaGetRevision();
      else
        Kprintf("CDIOC_ATAPI_GETFPGAREV:buffer NG\n");
      break;
    case 0x433C:
      if ( buf && buflen >= 4 )
        *(u32 *)buf = 0x4121300;
      else
        Kprintf("CDIOC_ATAPI_VERSION:buffer NG\n");
      break;
    case 0x433D:
      if ( buf && buflen >= 4 )
        *(u32 *)buf = g_pes_scrambling_control_pack;
      else
        Kprintf("CDIOC_ATAPI_GETPSCNT:buffer NG\n");
      break;
    case 0x439B:
      *(u32 *)buf = atapi_check_if_drive_ready(*(u32 *)args);
      break;
    case 0x4601:
      if ( *((u32 *)args + 3) == 2048 )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf(
            "sceFsDevctlBlkIO Lsn:%d nsec:%d buffer:%08x Type:%d\n",
            *(u32 *)args,
            *((u32 *)args + 1),
            *((u32 *)args + 2),
            *((u32 *)args + 4));
        retres1 = sceFsDevctlBlkIO(
                    f->unit,
                    *((void **)args + 2),
                    *(void **)args,
                    *((u32 *)args + 1),
                    2048,
                    *((u32 *)args + 4));
      }
      else
      {
        retres1 = -22;
      }
      break;
    default:
      Kprintf("Un-support devctl %08x\n", cmd);
      retres1 = -5;
      break;
  }
  SetEventFlag(g_io_event_flag, 1u);
  if ( g_xatapi_verbose > 0 )
  {
    Kprintf("xatapi devctl: cmd:%08x End.\n", cmd);
  }
  return retres1;
}
// 40A59C: using guessed type int g_devctl_retonly_unset;
// 40A630: using guessed type int g_reset_scrambling_pack;
// 40A638: using guessed type int g_dma_mode_value;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004024D0) --------------------------------------------------------
int _start(int ac, char **av)
{
  (void)ac;
  (void)av;

  Kprintf("xatapi_init Call\n");
  if ( RegisterLibraryEntries(&_exp_xatapi) == 0 )
  {
    DelDrv("xatapi");
    if ( AddDrv(&ata_ioman_device) )
    {
      xatapi_dev_deinit();
      return 1;
    }
    else
    {
      return xatapi_do_init() == 0;
    }
  }
  return 1;
}

//----- (00402554) --------------------------------------------------------
int expbay_get_has_power(void)
{
  return *g_dev9_reg_power & 4;
}

//----- (00402570) --------------------------------------------------------
void speedRegisterIntrCb(int intr, void *cb)
{
  g_dev5_intr_cbs[intr] = cb;
}

//----- (00402588) --------------------------------------------------------
void speedRegisterPreDmaCb(int ctrl, void *cb)
{
  g_dev5_predma_cbs[ctrl] = cb;
}

//----- (004025A0) --------------------------------------------------------
void speedRegisterPostDmaCb(int ctrl, void *cb)
{
  g_dev5_postdma_cbs[ctrl] = cb;
}

//----- (004025B8) --------------------------------------------------------
int speed_intr_dispatch(int flag)
{
  vu16 r_spd_intr_stat_1; // $v0
  vu16 r_spd_intr_mask_2; // $v0
  int r_spd_intr_stat_masked_1; // $v1
  int maskind2; // $s2
  int cbind1_1; // $s0
  void (*intr_cb)(int); // $a1
  vu16 r_spd_intr_mask_3; // $v1
  vu16 r_spd_intr_mask_4; // $v1
  vu16 r_spd_intr_stat_2; // $a1
  vu16 r_spd_intr_mask_1; // $a2

  if ( flag == 1 )
  {
    AtaEjectIntrHandle();
  }
  else
  {
    r_spd_intr_stat_1 = dev5_speed_regs.r_spd_intr_stat;
    if ( (r_spd_intr_stat_1 & 0x3EFC) != 0 )
    {
      if ( g_xatapi_verbose >= 0 )
      {
        r_spd_intr_stat_2 = dev5_speed_regs.r_spd_intr_stat;
        r_spd_intr_mask_1 = dev5_speed_regs.r_spd_intr_mask;
        Kprintf("SL3 register access failed(%x:%x) !!\n", r_spd_intr_stat_2, r_spd_intr_mask_1);
      }
    }
    else
    {
      r_spd_intr_mask_2 = dev5_speed_regs.r_spd_intr_mask;
      r_spd_intr_stat_masked_1 = (u16)(dev5_speed_regs.r_spd_intr_stat & r_spd_intr_mask_2);
      for ( maskind2 = 0; maskind2 < 3 && r_spd_intr_stat_masked_1; maskind2 += 1 )
      {
        for ( cbind1_1 = 0; cbind1_1 < 16; cbind1_1 += 1 )
        {
          intr_cb = (void (*)(int))g_dev5_intr_cbs[cbind1_1];
          if ( intr_cb )
          {
            r_spd_intr_mask_3 = dev5_speed_regs.r_spd_intr_mask;
            if ( ((int)(u16)(dev5_speed_regs.r_spd_intr_stat & r_spd_intr_mask_3) >> cbind1_1) & 1 )
              intr_cb(flag);
          }
        }
        r_spd_intr_mask_4 = dev5_speed_regs.r_spd_intr_mask;
        r_spd_intr_stat_masked_1 = (u16)(dev5_speed_regs.r_spd_intr_stat & r_spd_intr_mask_4);
      }
    }
  }
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00402714) --------------------------------------------------------
void speedIntrEnable(s16 mask)
{
  vu16 r_spd_intr_mask; // $v0
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  r_spd_intr_mask = dev5_speed_regs.r_spd_intr_mask;
  dev5_speed_regs.r_spd_intr_mask = r_spd_intr_mask & ~mask;
  dev5_speed_regs.r_spd_intr_mask = (r_spd_intr_mask & ~mask) | mask;
  CpuResumeIntr(state);
}

//----- (00402774) --------------------------------------------------------
void speedIntrDisable(s16 mask)
{
  vu16 r_spd_intr_mask; // $v0
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  r_spd_intr_mask = dev5_speed_regs.r_spd_intr_mask;
  dev5_speed_regs.r_spd_intr_mask = r_spd_intr_mask & ~mask;
  CpuResumeIntr(state);
}

//----- (004027C4) --------------------------------------------------------
int SpdDmaTransfer(unsigned int device, void *buf, u32 bcr_in, int dir)
{
  unsigned int device_1; // $v1
  int result; // $v0
  vu16 r_spd_rev_1; // $v0
  vu16 spd_dma_ctrl; // $v0
  void (*predma_cb)(u32, int); // $v0
  u32 chcr; // $s1
  u32 bcr; // $v0
  u32 madr_1; // $s0
  unsigned int device_2; // $v0
  u32 madr_2; // $v0
  void (*postdma_cb)(u32, int); // $v0

  dmac_ch_set_chcr(3u, 0);
  dmac_ch_get_chcr(3u);
  device_1 = device;
  if ( device < 2 || (g_dev5_predma_cbs[device_1] && g_dev5_postdma_cbs[device_1]) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("Wait Intr\n");
    result = WaitSema(g_dma_lock_sema);
    if ( result < 0 )
    {
      return result;
    }
    r_spd_rev_1 = dev5_speed_regs.r_spd_rev_1;
    if ( r_spd_rev_1 >= 0x11u )
      spd_dma_ctrl = (device & 1) | 6;
    else
      spd_dma_ctrl = (device & 3) | 4;
    dev5_speed_regs.r_spd_dma_ctrl = spd_dma_ctrl;
    predma_cb = (void (*)(u32, int))g_dev5_predma_cbs[device];
    if ( predma_cb )
      predma_cb(bcr_in, dir);
    if ( g_xatapi_verbose > 0 )
    {
      Kprintf("DMA Ch3 Set.\n");
      if ( g_xatapi_verbose > 0 )
        Kprintf("Set MADR3:%08x Set BCR3:%08x\n", buf, bcr_in);
    }
    dmac_ch_set_madr(3u, (u32)buf);
    dmac_ch_set_bcr(3u, bcr_in);
    dmac_ch_set_chcr(3u, dir | 0x41000200);
    dmac_ch_get_chcr(3u);
    if ( g_xatapi_verbose > 0 )
    {
      chcr = dmac_ch_get_chcr(3u);
      madr_1 = dmac_ch_get_madr(3u);
      bcr = dmac_ch_get_bcr(3u);
      Kprintf("CHCR3:%08x MADR3:%08x BCR3:%08x\n", chcr, madr_1, bcr);
    }
    while ( (dmac_ch_get_chcr(3u) & 0x1000000) != 0 );
    device_2 = device;
    if ( g_xatapi_verbose > 0 )
    {
      madr_2 = dmac_ch_get_madr(3u);
      Kprintf("MADR3= %08x\n", madr_2);
      device_2 = device;
    }
    postdma_cb = (void (*)(u32, int))g_dev5_postdma_cbs[device_2];
    if ( postdma_cb )
      postdma_cb(bcr_in, dir);
    if ( g_xatapi_verbose > 0 )
      Kprintf("SpdDmaTransfer End.\n");
    SignalSema(g_dma_lock_sema);
    return 0;
  }
  return -1;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00402A6C) --------------------------------------------------------
int SpdDmaTransfer_extrans_1(unsigned int device, void *buf, u32 bcr_in, int dir)
{
  unsigned int device_1; // $v1
  int result; // $v0
  vu16 r_spd_rev_1; // $v0
  vu16 spd_dma_ctrl; // $v0
  void (*predma_cb)(u32, int); // $v0
  u32 chcr; // $s1
  u32 bcr; // $v0
  u32 madr_1; // $s0
  u32 madr_2; // $v0
  void (*postdma_cb)(u32, int); // $v0

  dmac_ch_set_chcr(3u, 0);
  dmac_ch_get_chcr(3u);
  device_1 = device;
  if ( device < 2 || (g_dev5_predma_cbs[device_1] && g_dev5_postdma_cbs[device_1]) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("Wait Intr\n");
    result = WaitSema(g_dma_lock_sema);
    if ( result < 0 )
    {
      return result;
    }
    r_spd_rev_1 = dev5_speed_regs.r_spd_rev_1;
    if ( r_spd_rev_1 >= 0x11u )
      spd_dma_ctrl = (device & 1) | 6;
    else
      spd_dma_ctrl = (device & 3) | 4;
    dev5_speed_regs.r_spd_dma_ctrl = spd_dma_ctrl;
    predma_cb = (void (*)(u32, int))g_dev5_predma_cbs[device];
    if ( predma_cb )
      predma_cb(bcr_in, dir);
    speedIntrDisable(256);
    FpgaLayer1On();
    FpgaXfrenOn();
    if ( g_xatapi_verbose > 0 )
    {
      Kprintf("DMA Ch3 Set.\n");
      if ( g_xatapi_verbose > 0 )
        Kprintf("Set MADR3:%08x Set BCR3:%08x\n", buf, bcr_in);
    }
    dmac_ch_set_madr(3u, (u32)buf);
    dmac_ch_set_bcr(3u, bcr_in);
    dmac_ch_set_chcr(3u, dir | 0x41000200);
    dmac_ch_get_chcr(3u);
    if ( g_xatapi_verbose > 0 )
    {
      chcr = dmac_ch_get_chcr(3u);
      madr_1 = dmac_ch_get_madr(3u);
      bcr = dmac_ch_get_bcr(3u);
      Kprintf("CHCR3:%08x MADR3:%08x BCR3:%08x\n", chcr, madr_1, bcr);
    }
    while ( (dmac_ch_get_chcr(3u) & 0x1000000) != 0 );
    if ( g_xatapi_verbose > 0 )
    {
      madr_2 = dmac_ch_get_madr(3u);
      Kprintf("MADR3= %08x\n", madr_2);
    }
    FpgaCheckWriteBuffer();
    FpgaXfrenOff();
    FpgaLayer1Off();
    speedIntrEnable(256);
    postdma_cb = (void (*)(u32, int))g_dev5_postdma_cbs[device];
    if ( postdma_cb )
      postdma_cb(bcr_in, dir);
    if ( g_xatapi_verbose > 0 )
      Kprintf("SpdDmaTransfer_extrans End.\n");
    SignalSema(g_dma_lock_sema);
    return 0;
  }
  return -1;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00402D4C) --------------------------------------------------------
int SpdDmaTransfer_extrans_2(unsigned int device, void *buf, u32 bcr_in, int dir)
{
  unsigned int device_1; // $a0
  int result; // $v0
  u32 chcr; // $s1
  u32 bcr; // $v0
  u32 madr_1; // $s0
  u32 madr_2; // $v0

  dmac_ch_set_chcr(3u, 0);
  dmac_ch_get_chcr(3u);
  device_1 = device;
  if ( device < 2 || (g_dev5_predma_cbs[device_1] && g_dev5_postdma_cbs[device_1]) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("Wait Intr\n");
    result = WaitSema(g_dma_lock_sema);
    if ( result < 0 )
    {
      return result;
    }
    if ( g_xatapi_verbose > 0 )
    {
      Kprintf("DMA Ch3 Set.\n");
      if ( g_xatapi_verbose > 0 )
        Kprintf("Set MADR3:%08x Set BCR3:%08x\n", buf, bcr_in);
    }
    dmac_ch_set_madr(3u, (u32)buf);
    dmac_ch_set_bcr(3u, bcr_in);
    dmac_ch_set_chcr(3u, dir | 0x41000200);
    dmac_ch_get_chcr(3u);
    if ( g_xatapi_verbose > 0 )
    {
      chcr = dmac_ch_get_chcr(3u);
      madr_1 = dmac_ch_get_madr(3u);
      bcr = dmac_ch_get_bcr(3u);
      Kprintf("CHCR3:%08x MADR3:%08x BCR3:%08x\n", chcr, madr_1, bcr);
    }
    while ( (dmac_ch_get_chcr(3u) & 0x1000000) != 0 );
    if ( g_xatapi_verbose > 0 )
    {
      madr_2 = dmac_ch_get_madr(3u);
      Kprintf("MADR3= %08x\n", madr_2);
      if ( g_xatapi_verbose > 0 )
        Kprintf("SpdDmaTransfer_extrans End.\n");
    }
    SignalSema(g_dma_lock_sema);
    return 0;
  }
  return -1;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00402F68) --------------------------------------------------------
int SpdDmaTransfer_extrans_3(unsigned int device, void *buf, u32 bcr_in, int dir)
{
  unsigned int device_1; // $a0
  int result; // $v0
  u32 chcr; // $s1
  u32 bcr; // $v0
  u32 madr_1; // $s0
  u32 madr_2; // $v0

  dmac_ch_set_chcr(3u, 0);
  dmac_ch_get_chcr(3u);
  device_1 = device;
  if ( device < 2 || (g_dev5_predma_cbs[device_1] && g_dev5_postdma_cbs[device_1]) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("Wait Intr\n");
    result = WaitSema(g_dma_lock_sema);
    if ( result < 0 )
    {
      return result;
    }
    FpgaLayer1On();
    FpgaXfrenOn();
    if ( g_xatapi_verbose > 0 )
    {
      Kprintf("DMA Ch3 Set.\n");
      if ( g_xatapi_verbose > 0 )
        Kprintf("Set MADR3:%08x Set BCR3:%08x\n", buf, bcr_in);
    }
    dmac_ch_set_madr(3u, (u32)buf);
    dmac_ch_set_bcr(3u, bcr_in);
    dmac_ch_set_chcr(3u, dir | 0x41000200);
    dmac_ch_get_chcr(3u);
    if ( g_xatapi_verbose > 0 )
    {
      chcr = dmac_ch_get_chcr(3u);
      madr_1 = dmac_ch_get_madr(3u);
      bcr = dmac_ch_get_bcr(3u);
      Kprintf("CHCR3:%08x MADR3:%08x BCR3:%08x\n", chcr, madr_1, bcr);
    }
    while ( (dmac_ch_get_chcr(3u) & 0x1000000) != 0 );
    if ( g_xatapi_verbose > 0 )
    {
      madr_2 = dmac_ch_get_madr(3u);
      Kprintf("MADR3= %08x\n", madr_2);
    }
    FpgaCheckWriteBuffer2();
    FpgaXfrenOff();
    FpgaLayer1Off();
    if ( g_xatapi_verbose > 0 )
      Kprintf("SpdDmaTransfer_extrans End.\n");
    SignalSema(g_dma_lock_sema);
    return 0;
  }
  return -1;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004031AC) --------------------------------------------------------
void speedLEDCtl(int ctl)
{
  // Unofficial: was 8 bit access
  dev5_speed_regs.r_spd_pio_data = ctl == 0;
}

//----- (004031C4) --------------------------------------------------------
void speed_init(void)
{
  int i1; // $v1
  int i2; // $v1
  iop_sema_t semaparam; // [sp+10h] [-10h] BYREF

  semaparam.attr = 1;
  semaparam.initial = 1;
  semaparam.max = 1;
  semaparam.option = 0;
  g_dma_lock_sema = CreateSema(&semaparam);
  if ( g_dma_lock_sema <= 0 )
    return;
  speedIntrDisable(0xFFFF);
  speedRegisterIntrDispatchCb(speed_intr_dispatch);
  for ( i1 = 15; i1 >= 0; i1 -= 1 )
  {
    g_dev5_intr_cbs[i1] = 0;
  }
  for ( i2 = 0; i2 < 4; i2 += 1 )
  {
    g_dev5_predma_cbs[i2] = 0;
    g_dev5_postdma_cbs[i2] = 0;
  }
  speedLEDCtl(0);
  return;
}

//----- (00403284) --------------------------------------------------------
void speed_device_init(void)
{
  vu16 spdrev_1_1; // $v0
  int spdrev_1_1_tmp; // $v1
  int inbounds; // $v1
  vu16 spdrev_1_2; // $a1
  vu16 r_spd_rev_3; // $a1
  vu16 r_spd_rev_8; // $a2
  char *revtypes[8]; // [sp+0h] [-20h] BYREF

  spdrev_1_1 = dev5_speed_regs.r_spd_rev_1;
  revtypes[4] = "unknown";
  revtypes[5] = "TS";
  revtypes[6] = "ES1";
  revtypes[7] = "ES2";
  spdrev_1_1_tmp = spdrev_1_1;
  if ( spdrev_1_1 != 9 )
  {
    if ( (spdrev_1_1 < 9u)
      || (spdrev_1_1_tmp >= 18)
      || (inbounds = spdrev_1_1_tmp - 14, spdrev_1_1_tmp < 16) )
    {
      inbounds = 0;
    }
  }
  else
  {
    inbounds = 1;
  }
  if ( inbounds )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("Speed chip: %s\n", revtypes[inbounds + 4]);
  }
  else
  {
    if ( g_xatapi_verbose > 0 )
    {
      spdrev_1_2 = dev5_speed_regs.r_spd_rev_1;
      Kprintf("Speed chip: Rev %x\n", spdrev_1_2);
    }
  }
  if ( g_xatapi_verbose > 0 )
  {
    r_spd_rev_3 = dev5_speed_regs.r_spd_rev_3;
    r_spd_rev_8 = dev5_speed_regs.r_spd_rev_8;
    Kprintf("Speed version(rev3.rev8) = %04x.%04x\n", r_spd_rev_3, r_spd_rev_8);
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004033A0) --------------------------------------------------------
void do_hex_dump(void *ptr, int len)
{
  int offstotal; // $fp
  int totalx; // $s6
  int charbuf_offs; // $s5
  unsigned int curline; // $s4
  unsigned int curbyte; // $s1
  char *charbuf_ptr_ptr; // $s2
  char *chrbuf_ptr_ptr_ptr; // $s3
  char *ptr_ptr; // $s0
  int curchroffs; // $s6
  u8 fixme_chrbufbegin[16]; // [sp+0h] [-30h] BYREF
  char charbuf[24]; // [sp+10h] [-20h] BYREF
  int totalx_hi; // [sp+28h] [-8h]
  char *charbuf_ptr; // [sp+2Ch] [-4h]

  offstotal = 0;
  if ( g_xatapi_verbose )
  {
    totalx = 0;
    Kprintf("Hex dump 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f");
    charbuf_offs = 0;
    charbuf_ptr = charbuf;
    for ( ; len; len -= curline )
    {
      curline = 256;
      if ( len < 257 )
        curline = len;
      totalx_hi = totalx << 8;
      charbuf_ptr_ptr = &charbuf_ptr[charbuf_offs];
      for ( curbyte = 0; curbyte < curline; curbyte += 1 )
      {
        if ( !(curbyte & 0xF) )
        {
          charbuf_offs = 0;
          *charbuf_ptr_ptr = 0;
          charbuf_ptr_ptr = charbuf_ptr;
          Kprintf(" %s\n%08x", charbuf_ptr, curbyte + totalx_hi);
        }
        chrbuf_ptr_ptr_ptr = charbuf_ptr_ptr;
        ptr_ptr = (char *)ptr + offstotal + curbyte;
        ++charbuf_ptr_ptr;
        Kprintf(" %02x", (u8)*ptr_ptr);
        ++charbuf_offs;
        if ( *ptr_ptr >= 0 && isgraph(*ptr_ptr) )
          *chrbuf_ptr_ptr_ptr = *ptr_ptr;
        else
          *chrbuf_ptr_ptr_ptr = '.';
      }
      ++totalx;
      offstotal += curline;
    }
    fixme_chrbufbegin[charbuf_offs + 16] = 0;
    for ( curchroffs = 0; (unsigned int)curchroffs < (unsigned int)(16 - charbuf_offs); curchroffs += 1 )
    {
      Kprintf("\t  ");
    }
    Kprintf("%s\n", charbuf);
  }
}
// 403414: conditional instruction was optimized away because $s4.4 is in (1..100|<0)
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403554) --------------------------------------------------------
void ata_pre_dma_cb(void)
{
  vu16 spd_xfr_ctrl_1; // $a1
  vu16 spd_xfr_ctrl_2; // $v0
  int spd_xfr_ctrl_3; // $a1

  if ( g_xatapi_verbose > 0 )
  {
    spd_xfr_ctrl_1 = dev5_speed_regs.r_spd_xfr_ctrl;
    Kprintf("ata_pre_dma_handler:old %x\n", spd_xfr_ctrl_1);
  }
  spd_xfr_ctrl_2 = dev5_speed_regs.r_spd_xfr_ctrl;
  dev5_speed_regs.r_spd_xfr_ctrl = spd_xfr_ctrl_2 | 0x80;
  if ( g_xatapi_verbose > 0 )
  {
    spd_xfr_ctrl_3 = dev5_speed_regs.r_spd_xfr_ctrl;
    Kprintf("ata_pre_dma_handler:new %x\n", spd_xfr_ctrl_3);
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004035CC) --------------------------------------------------------
void ata_post_dma_cb(void)
{
  vu16 spd_xfr_ctrl_1; // $a1
  vu16 spd_xfr_ctrl_2; // $v0
  int spd_xfr_ctrl_3; // $a1

  if ( g_xatapi_verbose > 0 )
  {
    spd_xfr_ctrl_1 = dev5_speed_regs.r_spd_xfr_ctrl;
    Kprintf("ata_post_dma_handler:old %x\n", spd_xfr_ctrl_1);
  }
  spd_xfr_ctrl_2 = dev5_speed_regs.r_spd_xfr_ctrl;
  dev5_speed_regs.r_spd_xfr_ctrl = spd_xfr_ctrl_2 & 0xFF7F;
  if ( g_xatapi_verbose > 0 )
  {
    spd_xfr_ctrl_3 = dev5_speed_regs.r_spd_xfr_ctrl;
    Kprintf("ata_post_dma_handler:new %x\n", spd_xfr_ctrl_3);
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403644) --------------------------------------------------------
int vReferEventFlagStatus(int ef, iop_event_info_t *info)
{
  if ( QueryIntrContext() )
    return iReferEventFlagStatus(ef, info);
  else
    return ReferEventFlagStatus(ef, info);
}

//----- (00403694) --------------------------------------------------------
void xatapi_9_sceCdSpdAtaDmaStart(int dir)
{
  char spd_if_ctrl_1; // $v0
  int spd_if_ctrl_manip_1; // $v0
  int spd_if_ctrl_manip_2; // $a1
  vu16 spd_if_ctrl_2; // $a1
  int r_spd_xfr_ctrl; // $a2
  u32 efbits[2]; // [sp+10h] [-8h] BYREF

  g_is_wait_busy = 0;
  WaitEventFlag(g_adma_evfid, 1u, 16, efbits);
  g_should_wait_for_dma_flag = 1;
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdSpdAtaDmaStart Call %d :Read 0:Write 1\n", dir);
  dev5_speed_regs.r_spd_dbuf_stat = 3;
  spd_if_ctrl_1 = dev5_speed_regs.r_spd_if_ctrl;
  spd_if_ctrl_manip_1 = spd_if_ctrl_1 & 1;
  if ( dir )
    spd_if_ctrl_manip_2 = spd_if_ctrl_manip_1 | 0x4C;
  else
    spd_if_ctrl_manip_2 = spd_if_ctrl_manip_1 | 0x4E;
  dev5_speed_regs.r_spd_if_ctrl = spd_if_ctrl_manip_2;
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdSpdAtaDmaStart Write R_IF_CTR:%x\n", spd_if_ctrl_manip_2);
  dev5_speed_regs.r_spd_xfr_ctrl = dir | 6;
  if ( g_xatapi_verbose > 0 )
  {
    spd_if_ctrl_2 = dev5_speed_regs.r_spd_if_ctrl;
    r_spd_xfr_ctrl = dev5_speed_regs.r_spd_xfr_ctrl;
    Kprintf("sceCdSpdAtaDmaStart R_IF_CTR:%x R_XFR_CTRL:%x\n", spd_if_ctrl_2, r_spd_xfr_ctrl);
  }
}
// 40A640: using guessed type int g_should_wait_for_dma_flag;
// 40A644: using guessed type int g_is_wait_busy;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403790) --------------------------------------------------------
void xatapi_10_sceCdSpdAtaDmaEnd(void)
{
  vu16 r_spd_if_ctrl; // $v0
  iop_event_info_t efinfo; // [sp+10h] [-20h] BYREF

  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdSpdAtaDmaEnd Call\n");
  if ( g_should_wait_for_dma_flag )
  {
    if ( vReferEventFlagStatus(g_adma_evfid, &efinfo) || (efinfo.currBits & 1) != 0 )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("sceCdSpdAtaDmaEnd No Start\n");
      g_should_wait_for_dma_flag = 0;
    }
    else
    {
      dev5_speed_regs.r_spd_xfr_ctrl = 1;
      r_spd_if_ctrl = dev5_speed_regs.r_spd_if_ctrl;
      dev5_speed_regs.r_spd_if_ctrl = r_spd_if_ctrl & 0xFFFB;
      dev5_speed_regs.r_spd_dbuf_stat = 3;
      dev5_speed_regs.r_spd_if_ctrl = (r_spd_if_ctrl & 0xFF7B) | 0x80;
      dev5_speed_regs.r_spd_if_ctrl = r_spd_if_ctrl & 0xFF7B;
      ata_pio_mode(0);
      if ( g_dma_mode_value )
        ata_ultra_dma_mode(g_dma_speed_value);
      else
        ata_multiword_dma_mode(g_dma_speed_value);
      g_should_wait_for_dma_flag = 0;
      SetEventFlag(g_adma_evfid, 1u);
    }
  }
  else if ( g_xatapi_verbose > 0 )
  {
    Kprintf("sceCdSpdAtaDmaEnd No Start(flag)\n");
  }
}
// 40A638: using guessed type int g_dma_mode_value;
// 40A640: using guessed type int g_should_wait_for_dma_flag;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403918) --------------------------------------------------------
void ata_pio_mode(int mode)
{
  vu16 spd_pio_mode_rvalue; // $v0

  if ( g_xatapi_verbose > 0 )
    Kprintf("SpdAtaSetPioTiming %d\n", mode);
  switch ( mode )
  {
    case 0:
    default:
      spd_pio_mode_rvalue = 146;
      break;
    case 1:
      spd_pio_mode_rvalue = 114;
      break;
    case 2:
      spd_pio_mode_rvalue = 50;
      break;
    case 3:
      spd_pio_mode_rvalue = 36;
      break;
    case 4:
      spd_pio_mode_rvalue = 35;
      break;
  }
  dev5_speed_regs.r_spd_pio_mode = spd_pio_mode_rvalue;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004039D0) --------------------------------------------------------
void ata_multiword_dma_mode(int mode)
{
  vu16 spd_mwdma_mode_rval; // $v0
  vu16 r_spd_if_ctrl; // $v0

  if ( g_xatapi_verbose > 0 )
    Kprintf("SpdAtaSetMdmaTiming %d\n", mode);
  if ( mode == 1 )
  {
    spd_mwdma_mode_rval = 69;
  }
  else if ( mode == 2 )
  {
    spd_mwdma_mode_rval = 36;
  }
  else
  {
    spd_mwdma_mode_rval = 255;
  }
  dev5_speed_regs.r_spd_mwdma_mode = spd_mwdma_mode_rval;
  r_spd_if_ctrl = dev5_speed_regs.r_spd_if_ctrl;
  dev5_speed_regs.r_spd_if_ctrl = (r_spd_if_ctrl & 0xFFB6) | 0x48;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403A64) --------------------------------------------------------
void ata_ultra_dma_mode(int mode)
{
  vu16 spd_udma_mode_rval; // $v0
  vu16 r_spd_if_ctrl; // $v0

  if ( g_xatapi_verbose > 0 )
    Kprintf("SpdAtaSetUdmaTiming %d\n", mode);
  switch ( mode )
  {
    case 0:
    default:
      spd_udma_mode_rval = 167;
      break;
    case 1:
      spd_udma_mode_rval = 133;
      break;
    case 2:
      spd_udma_mode_rval = 99;
      break;
    case 3:
      spd_udma_mode_rval = 98;
      break;
    case 4:
      spd_udma_mode_rval = 97;
      break;
  }
  dev5_speed_regs.r_spd_udma_mode = spd_udma_mode_rval;
  r_spd_if_ctrl = dev5_speed_regs.r_spd_if_ctrl;
  dev5_speed_regs.r_spd_if_ctrl = r_spd_if_ctrl | 0x49;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403B34) --------------------------------------------------------
int ata_intr_cb(int flag)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("call AtaIntrHandle %d\n", flag);
  speedIntrDisable(3);
  iSetEventFlag(g_atapi_event_flag, 2u);
  return 1;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403B84) --------------------------------------------------------
void AtaEjectIntrHandle(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("call AtaEjectIntrHandle\n");
  g_is_wait_busy = 1;
  iSetEventFlag(g_atapi_event_flag, 4u);
}
// 40A644: using guessed type int g_is_wait_busy;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403BD8) --------------------------------------------------------
unsigned int AtaAlarmrHandle(void *usrdat)
{
  (void)usrdat;

  if ( g_xatapi_verbose > 0 )
    Kprintf("call AtaAlarmrHandle\n");
  iSetEventFlag(g_atapi_event_flag, 1u);
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403C1C) --------------------------------------------------------
int xatapi_14_set_speed_reg(int regaddr, u16 regval)
{
  u32 efbits[2]; // [sp+10h] [-8h] BYREF

  if ( (unsigned int)(regaddr - 64) < 0x1D )
  {
    WaitEventFlag(g_acmd_evfid, 1u, 16, efbits);
    *(vu16 *)((char *)&dev5_speed_regs.unv00 + regaddr) = regval;
    SetEventFlag(g_acmd_evfid, 1u);
  }
  return regval;
}

//----- (00403C98) --------------------------------------------------------
int xatapi_13_get_speed_reg(int regaddr)
{
  int tmpval; // $s0
  u32 efbits[2]; // [sp+10h] [-8h] BYREF

  if ( (unsigned int)(regaddr - 64) >= 0x1D )
    return 0;
  WaitEventFlag(g_acmd_evfid, 1u, 16, efbits);
  tmpval = *(u16 *)((char *)&dev5_speed_regs.unv00 + regaddr);
  SetEventFlag(g_acmd_evfid, 1u);
  return tmpval;
}

//----- (00403D08) --------------------------------------------------------
int xatapi_11_sceAtaGetError(void)
{
  u8 r_spd_ata_error; // $s0
  u32 efbits[2]; // [sp+10h] [-8h] BYREF

  WaitEventFlag(g_acmd_evfid, 1u, 16, efbits);
  r_spd_ata_error = dev5_speed_regs.r_spd_ata_error;
  SetEventFlag(g_acmd_evfid, 1u);
  return r_spd_ata_error;
}

//----- (00403D5C) --------------------------------------------------------
int xatapi_12_get_ata_control(void)
{
  u8 r_spd_ata_control; // $s0
  u32 efbits[2]; // [sp+10h] [-8h] BYREF

  WaitEventFlag(g_acmd_evfid, 1u, 16, efbits);
  r_spd_ata_control = dev5_speed_regs.r_spd_ata_control;
  SetEventFlag(g_acmd_evfid, 1u);
  return r_spd_ata_control;
}

//----- (00403DB0) --------------------------------------------------------
int sceAtaGetError(void)
{
  return (u8)dev5_speed_regs.r_spd_ata_error;
}

//----- (00403DC4) --------------------------------------------------------
int ata_wait_busy1_busy(void)
{
  unsigned int waitcnt; // $s0
  int waitcnt_div; // $a1
  int delaythread_period; // $a0

  waitcnt = 0;
  while ( 2 )
  {
    if ( (dev5_speed_regs.r_spd_ata_control & 0x80) != 0 )
    {
      if ( (u16)expbay_get_has_power() )
      {
        if ( g_is_wait_busy )
        {
          if ( g_xatapi_verbose > 0 )
          {
            Kprintf("DEV5 ATA: error: wait busy, tray eject.\n");
          }
          return -550;
        }
        else
        {
          waitcnt_div = (0xCCCCCCCD * (u64)waitcnt) >> 32;
          switch ( waitcnt / 0xA )
          {
            case 0u:
              delaythread_period = 0;
              break;
            case 1u:
              delaythread_period = 100;
              break;
            case 2u:
              delaythread_period = 1000;
              break;
            case 3u:
              delaythread_period = 10000;
              break;
            case 4u:
              delaythread_period = 100000;
              break;
            default:
              delaythread_period = 1000000;
              break;
          }
          if ( delaythread_period )
            DelayThread(delaythread_period);
          if ( ++waitcnt < 0x50 )
            continue;
          if ( g_xatapi_verbose > 0 )
          {
            Kprintf("DEV5 ATA: error: wait busy, timedout.\n", waitcnt_div);
          }
          return -502;
        }
      }
      else
      {
        if ( g_xatapi_verbose > 0 )
        {
          Kprintf("DEV5 ATA: error: wait busy, power off.\n");
        }
        return -551;
      }
    }
    return 0;
  }
}
// 403F14: variable 'waitcnt_div' is possibly undefined
// 40A644: using guessed type int g_is_wait_busy;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403F3C) --------------------------------------------------------
int ata_wait_busy2_busy(void)
{
  unsigned int waitcnt; // $s0
  int waitcnt_div; // $a1
  int delaythread_period; // $a0

  waitcnt = 0;
  while ( 2 )
  {
    if ( (dev5_speed_regs.r_spd_ata_control & 0x80) != 0 )
    {
      if ( (u16)expbay_get_has_power() )
      {
        if ( g_is_wait_busy )
        {
          if ( g_xatapi_verbose > 0 )
          {
            Kprintf("DEV5 ATA: error: wait busy, tray eject.\n");
          }
          return -550;
        }
        else
        {
          waitcnt_div = (0xCCCCCCCD * (u64)waitcnt) >> 32;
          switch ( waitcnt / 0xA )
          {
            case 0u:
              delaythread_period = 0;
              break;
            case 1u:
              delaythread_period = 100;
              break;
            case 2u:
              delaythread_period = 1000;
              break;
            case 3u:
              delaythread_period = 10000;
              break;
            case 4u:
              delaythread_period = 100000;
              break;
            default:
              delaythread_period = 1000000;
              break;
          }
          if ( delaythread_period )
            DelayThread(delaythread_period);
          if ( ++waitcnt < 55 )
            continue;
          if ( g_xatapi_verbose > 0 )
          {
            Kprintf("DEV5 ATA: error: wait busy, timedout.\n", waitcnt_div);
          }
          return -502;
        }
      }
      else
      {
        if ( g_xatapi_verbose > 0 )
        {
          Kprintf("DEV5 ATA: error: wait busy, power off.\n");
        }
        return -551;
      }
    }
    return 0;
  }
}
// 40408C: variable 'waitcnt_div' is possibly undefined
// 40A644: using guessed type int g_is_wait_busy;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004040B4) --------------------------------------------------------
int ata_wait_bus_busy_busbusy(void)
{
  unsigned int waitcnt; // $s0
  int waitcnt_div; // $a1
  int delaythread_period; // $a0

  waitcnt = 0;
  while ( 2 )
  {
    if ( (dev5_speed_regs.r_spd_ata_control & 0x88) != 0 )
    {
      if ( (u16)expbay_get_has_power() )
      {
        if ( g_is_wait_busy )
        {
          if ( g_xatapi_verbose > 0 )
          {
            Kprintf("DEV5 ATA: error: wait busbusy, tray eject.\n");
          }
          return -550;
        }
        else
        {
          waitcnt_div = (0xCCCCCCCD * (u64)waitcnt) >> 32;
          switch ( waitcnt / 0xA )
          {
            case 0u:
              delaythread_period = 0;
              break;
            case 1u:
              delaythread_period = 100;
              break;
            case 2u:
              delaythread_period = 1000;
              break;
            case 3u:
              delaythread_period = 10000;
              break;
            case 4u:
              delaythread_period = 100000;
              break;
            default:
              delaythread_period = 1000000;
              break;
          }
          if ( delaythread_period )
            DelayThread(delaythread_period);
          if ( ++waitcnt < 80 )
            continue;
          if ( g_xatapi_verbose > 0 )
          {
            Kprintf("DEV5 ATA: error: wait busbusy, timedout.\n", waitcnt_div);
          }
          return -502;
        }
      }
      else
      {
        if ( g_xatapi_verbose > 0 )
        {
          Kprintf("DEV5 ATA: error: wait busy, power off.\n");
        }
        return -551;
      }
    }
    return 0;
  }
}
// 404204: variable 'waitcnt_div' is possibly undefined
// 40A644: using guessed type int g_is_wait_busy;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (0040422C) --------------------------------------------------------
int ata_device_select(int device)
{
  int result; // $v0
  vu16 r_spd_ata_select; // $v0

  result = ata_wait_bus_busy_busbusy();
  if ( result >= 0 )
  {
    r_spd_ata_select = dev5_speed_regs.r_spd_ata_select;
    if ( ((r_spd_ata_select >> 4) & 1) == device )
    {
      return 0;
    }
    else
    {
      dev5_speed_regs.r_spd_ata_select = 16 * (device != 0);
      return ata_wait_bus_busy_busbusy();
    }
  }
  return result;
}

//----- (0040429C) --------------------------------------------------------
int sceAtaExecCmd(
        void *buf,
        u32 blkcount,
        u16 feature,
        u16 nsector,
        u16 sector,
        u16 lcyl,
        u16 hcyl,
        u16 select,
        u16 command,
        u32 unk10)
{
  int devinfo_item; // $v0
  int result; // $v0
  char r_spd_ata_control; // $v0
  int using_timeout; // $s0
  u32 usec_val; // $a0
  iop_sys_clock_t sysclk; // [sp+10h] [-10h] BYREF
  u16 nsector_tmp; // [sp+18h] [-8h]
  u16 hcyl_tmp; // [sp+1Ah] [-6h]

  nsector_tmp = nsector;
  hcyl_tmp = hcyl;
  ClearEventFlag(g_atapi_event_flag, 0);
  devinfo_item = 0;
  g_is_wait_busy = 0;
  if ( (select & 0x10) != 0 )
    devinfo_item = 1;
  if ( !atad_devinfo[devinfo_item].exists )
    return -505;
  result = ata_device_select((select >> 4) & 1);
  if ( !result )
  {
    if ( command == 142 || command == 176 )
    {
      if ( g_xatapi_verbose > 0 )
      {
        Kprintf("Not support Ata CMD\n");
      }
      return -503;
    }
    atad_cmd_state.type = unk10;
    if ( !unk10 )
      return -506;
    r_spd_ata_control = dev5_speed_regs.r_spd_ata_control;
    atad_cmd_state.buf = buf;
    atad_cmd_state.blkcount = blkcount;
    if ( (r_spd_ata_control & 0x40) == 0 )
    {
      if ( (command < 0x92u && command < 0x90u && command != 8) || (command >= 0xA2u || command < 0xA0u) )
      {
        if ( g_xatapi_verbose > 0 )
        {
          Kprintf("DEV5 ATA: error: device not ready\n");
        }
        return -501;
      }
    }
    switch ( atad_cmd_state.type )
    {
      case 1:
      case 8:
        using_timeout = 1;
        break;
      case 4:
        atad_cmd_state.dir = command != 0xC8;
        using_timeout = 1;
        break;
      case 5:
      case 6:
        using_timeout = 1;
        atad_cmd_state.dir = atad_cmd_state.type != 5;
        break;
      default:
        using_timeout = 0;
        break;
    }
    if ( atad_cmd_state.type != 9 )
    {
      if ( !using_timeout
        || (command != 142 || feature != 244 ? (usec_val = 155000000) : (usec_val = 180000000),
            USec2SysClock(usec_val, &sysclk),
            result = SetAlarm(&sysclk, AtaAlarmrHandle, 0),
            result >= 0) )
      {
        if ( atad_cmd_state.type == 1 )
          speedIntrEnable(1);
        dev5_speed_regs.r_spd_ata_control = 2 * (using_timeout == 0);
      }
      else
      {
        return result;
      }
    }
    dev5_speed_regs.r_spd_ata_error = feature;
    dev5_speed_regs.r_spd_ata_nsector = nsector_tmp;
    dev5_speed_regs.r_spd_ata_sector = sector;
    dev5_speed_regs.r_spd_ata_lcyl = lcyl;
    dev5_speed_regs.r_spd_ata_hcyl = hcyl_tmp;
    dev5_speed_regs.r_spd_ata_select = select | 0x40;
    dev5_speed_regs.r_spd_ata_status = command;
    speedLEDCtl(1);
    return 0;
  }
  return result;
}
// 40A644: using guessed type int g_is_wait_busy;
// 40A648: using guessed type int g_xatapi_verbose;
// 40A6E8: using guessed type ata_devinfo_t atad_devinfo[2];
// 40A710: using guessed type ata_cmd_state_t atad_cmd_state;

//----- (004045A8) --------------------------------------------------------
int xatapi_5_sceAtaExecCmd(
        void *buf,
        u32 blkcount,
        u16 feature,
        u16 nsector,
        u16 sector,
        u16 lcyl,
        u16 hcyl,
        u16 select,
        u16 command,
        u32 unk10)
{
  int retres; // $s0
  u32 efbits[2]; // [sp+28h] [-8h] BYREF

  WaitEventFlag(g_acmd_evfid, 1u, 16, efbits);
  retres = sceAtaExecCmd(buf, blkcount, feature, nsector, sector, lcyl, hcyl, select, command, unk10);
  if ( retres )
  {
    SetEventFlag(g_acmd_evfid, 1u);
  }
  return retres;
}

//----- (004046A4) --------------------------------------------------------
int sceCdAtapiExecCmd_local(
        s16 n,
        void *buf,
        int nsec,
        int secsize,
        void *pkt,
        unsigned int pkt_len,
        int proto)
{
  u16 *pkt_u16; // $s4
  u16 feature_tmp; // $s2
  u8 pkt_scsi_cmd; // $s6
  int result; // $v0
  int using_timeout; // $s1
  int retres1; // $s0
  char ata_status_1; // $s0
  int ata_status_2; // $a1
  u8 Error; // $v0
  unsigned int pkt_len_div2; // $a1
  unsigned int pkt_data_i; // $s0
  vu16 pkt_data_tmp; // $v0
  iop_sys_clock_t sysclk; // [sp+28h] [-8h] BYREF

  pkt_u16 = (u16 *)pkt;
  feature_tmp = 0;
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdAtapiExecCmd Start. pkt_len %d proto %d\n", pkt_len, proto);
  do_hex_dump(pkt, 12);
  g_is_wait_busy = 0;
  pkt_scsi_cmd = *(u8 *)pkt;
  if ( !proto )
    return -506;
  atad_cmd_state.type_atapi = proto;
  atad_cmd_state.buf_atapi = buf;
  atad_cmd_state.blkcount_atapi = nsec;
  atad_cmd_state.blksize_atapi = secsize;
  switch ( proto )
  {
    case 1:
    case 8:
      using_timeout = 1;
      break;
    case 4:
      switch ( pkt_scsi_cmd )
      {
        case 0x03:
        case 0x12:
        case 0x23:
        case 0x25:
        case 0x28:
        case 0x3C:
        case 0x46:
        case 0x4A:
        case 0x5A:
        case 0xA4:
        case 0xA8:
        case 0xB9:
        case 0xDA:
          atad_cmd_state.dir_atapi = 0;
          break;
        default:
          atad_cmd_state.dir_atapi = 1;
          break;
      }
      using_timeout = 1;
      feature_tmp = 1;
      break;
    case 5:
    case 6:
      using_timeout = 1;
      feature_tmp = 1;
      atad_cmd_state.dir_atapi = atad_cmd_state.type_atapi != 5;
      break;
    default:
      using_timeout = 0;
      break;
  }
  if ( !g_reset_scrambling_pack
    && atad_cmd_state.type_atapi == 4
    && atad_cmd_state.dir_atapi == 1
    && Mpeg2CheckScramble(
         (char *)atad_cmd_state.buf_atapi,
         atad_cmd_state.blkcount_atapi * atad_cmd_state.blksize_atapi) )
  {
    if ( g_xatapi_verbose >= 0 )
    {
      Kprintf("illegal stream\n");
    }
    return -560;
  }
  if ( !using_timeout
    || (USec2SysClock(0x93D1CC0u, &sysclk), result = SetAlarm(&sysclk, AtaAlarmrHandle, 0), result >= 0) )
  {
    if ( atad_cmd_state.type_atapi == 1 )
      speedIntrEnable(1);
    dev5_speed_regs.r_spd_ata_control = 2 * (using_timeout == 0);
    result = sceAtaExecCmd(
               0,
               0,
               feature_tmp,
               0,
               0,
               (u8)((atad_cmd_state.blkcount_atapi & 0xFF) * (atad_cmd_state.blksize_atapi & 0xFF)),
               (u8)((u16)((atad_cmd_state.blkcount_atapi & 0xFFFF)
                                                  * (atad_cmd_state.blksize_atapi & 0xFFFF)) >> 8),
               16 * n,
               0xA0u,
               9u);
    retres1 = result;
    if ( retres1 )
    {
      if ( using_timeout )
      {
        CancelAlarm(AtaAlarmrHandle, 0);
      }
      return retres1;
    }
    ata_status_1 = 0;
    while ( (ata_status_1 & 0x88) != 8 )
    {
      DelayThread(10000);
      ata_status_1 = dev5_speed_regs.r_spd_ata_status;
      ata_status_2 = dev5_speed_regs.r_spd_ata_status;
      if ( g_xatapi_verbose > 0 )
        Kprintf("Status 0x%02x BSY %x DRQ %x\n", ata_status_2, ata_status_1 & 0x80, ata_status_1 & 8);
      if ( g_is_wait_busy )
      {
        if ( using_timeout )
          CancelAlarm(AtaAlarmrHandle, 0);
        if ( g_xatapi_verbose > 0 )
          Kprintf("sceCdAtapiExecCmd Tray Eject while\n", ata_status_2);
        return -550;
      }
      if ( !(u16)expbay_get_has_power() )
      {
        if ( using_timeout )
        {
          CancelAlarm(AtaAlarmrHandle, 0);
        }
        return -551;
      }
    }
    if ( (ata_status_1 & 1) != 0 )
    {
      if ( g_xatapi_verbose > 0 )
      {
        Error = sceAtaGetError();
        Kprintf("iocmd err 0x%02x, 0x%02x\n", ata_status_1, Error);
      }
      if ( using_timeout )
      {
        CancelAlarm(AtaAlarmrHandle, 0);
      }
      return -503;
    }
    pkt_len_div2 = pkt_len >> 1;
    if ( (ata_status_1 & 8) == 0 && g_xatapi_verbose > 0 )
    {
      Kprintf("sceCdAtapiExecCmd_local ATA_NO_DREQ\n");
      pkt_len_div2 = pkt_len >> 1;
    }
    for ( pkt_data_i = 0; pkt_data_i < pkt_len_div2; pkt_data_i += 1 )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("sceCdAtapiExecCmd_local Packet %04x\n", *pkt_u16);
      pkt_data_tmp = *pkt_u16++;
      dev5_speed_regs.r_spd_ata_data = pkt_data_tmp;
    }
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceCdAtapiExecCmd End. cmd %02x\n", pkt_scsi_cmd);
    if ( g_is_wait_busy )
    {
      if ( using_timeout )
        CancelAlarm(AtaAlarmrHandle, 0);
      if ( g_xatapi_verbose > 0 )
      {
        Kprintf("sceCdAtapiExecCmd Tray Eject last\n", pkt_len_div2);
      }
      return -550;
    }
    else
    {
      if ( g_xatapi_verbose > 0 )
      {
        Kprintf("sceCdAtapiExecCmd OK\n");
      }
      return 0;
    }
  }
  return result;
}
// 404AF0: variable 'ata_status_2' is possibly undefined
// 404C84: variable 'pkt_len_div2' is possibly undefined
// 40A630: using guessed type int g_reset_scrambling_pack;
// 40A644: using guessed type int g_is_wait_busy;
// 40A648: using guessed type int g_xatapi_verbose;
// 40A710: using guessed type ata_cmd_state_t atad_cmd_state;

//----- (00404CEC) --------------------------------------------------------
int sceCdAtapiExecCmd(s16 n, void *buf, int nsec, int secsize, void *pkt, int pkt_len, int proto)
{
  u8 pkt_scsi_cmd_1; // $s0
  int pkt_scsi_cmd_2; // $a1

  if ( pkt_len )
  {
    pkt_scsi_cmd_1 = *(u8 *)pkt;
    pkt_scsi_cmd_2 = *(u8 *)pkt;
    if ( g_xatapi_verbose > 0 )
    {
      Kprintf("sceCdAtapiExecCmd %08x\n", *(u8 *)pkt);
      pkt_scsi_cmd_2 = pkt_scsi_cmd_1;
    }
    if ( !(pkt_scsi_cmd_2 == 0x1B || pkt_scsi_cmd_2 == 0x12 || !pkt_scsi_cmd_2 || pkt_scsi_cmd_2 == 3 || *g_cd_sc_ffffffd9_ptr) )
    {
      if ( !g_is_in_read_info )
      {
        if ( !sceCdAtapi_BC() )
        {
          ata_device_set_transfer_mode_outer(0);
        }
      }
    }
  }
  return sceCdAtapiExecCmd_local(n, buf, nsec, secsize, pkt, pkt_len, proto);
}
// 40A648: using guessed type int g_xatapi_verbose;
// 40A658: using guessed type int g_is_in_read_info;

//----- (00404E0C) --------------------------------------------------------
int xatapi_7_sceCdAtapiExecCmd(s16 n, void *buf, int nsec, int secsize, void *pkt, int pkt_len, int proto)
{
  int retres; // $s0
  u32 efbits[2]; // [sp+20h] [-8h] BYREF

  WaitEventFlag(g_acmd_evfid, 1u, 16, efbits);
  retres = sceCdAtapiExecCmd(n, buf, nsec, secsize, pkt, pkt_len, proto);
  if ( retres )
  {
    SetEventFlag(g_acmd_evfid, 1u);
    return retres;
  }
  return retres;
}

//----- (00404ECC) --------------------------------------------------------
int ata_pio_transfer(ata_cmd_state_t *cmd_state)
{
  char r_spd_ata_status; // $s0
  u8 Error; // $v0
  s32 type; // $v1
  int buf16_i_1; // $a1
  u16 *buf16_tmp_1; // $v0
  u16 rval_tmp_1; // $v1
  int buf16_i_3; // $a1
  u16 *buf16_tmp_3; // $v0
  vu16 r_spd_ata_data; // $v1
  int buf16_i_2; // $a1
  u16 *buf16_tmp_2; // $v0
  u16 tval_tmp_3; // $v1
  int buf8_i_1; // $a1
  u8 *buf8_tmp_1; // $v0
  vu16 rval_tmp_2; // $v1

  r_spd_ata_status = dev5_speed_regs.r_spd_ata_status;
  if ( (r_spd_ata_status & 1) != 0 )
  {
    if ( g_xatapi_verbose > 0 )
    {
      Error = sceAtaGetError();
      Kprintf("DEV5 ATA: error: ATA PIO iocmd err 0x%02x, 0x%02x\n", r_spd_ata_status, Error);
    }
    return -503;
  }
  else if ( (r_spd_ata_status & 8) != 0 )
  {
    type = cmd_state->type;
    if ( cmd_state->type == 3 )
    {
      for ( buf16_i_1 = 0; buf16_i_1 < 256; buf16_i_1 += 1 )
      {
        buf16_tmp_1 = cmd_state->buf16;
        rval_tmp_1 = *buf16_tmp_1;
        cmd_state->buf = buf16_tmp_1 + 1;
        dev5_speed_regs.r_spd_ata_data = rval_tmp_1;
      }
    }
    else if ( (u32)(cmd_state->type) >= 4u )
    {
      if ( type == 11 )
      {
        for ( buf16_i_2 = 0; buf16_i_2 < 256; buf16_i_2 += 1 )
        {
          buf16_tmp_2 = cmd_state->buf16;
          tval_tmp_3 = *buf16_tmp_2;
          cmd_state->buf = buf16_tmp_2 + 1;
          dev5_speed_regs.r_spd_ata_data = tval_tmp_3;
        }
        for ( buf8_i_1 = 0; buf8_i_1 < 4; buf8_i_1 += 1 )
        {
          buf8_tmp_1 = cmd_state->buf8;
          rval_tmp_2 = *buf8_tmp_1;
          cmd_state->buf = buf8_tmp_1 + 1;
          dev5_speed_regs.r_spd_ata_data = rval_tmp_2;
        }
      }
    }
    else
    {
      if ( type == 2 )
      {
        for ( buf16_i_3 = 0; buf16_i_3 < 256; buf16_i_3 += 1 )
        {
          buf16_tmp_3 = cmd_state->buf16;
          r_spd_ata_data = dev5_speed_regs.r_spd_ata_data;
          *buf16_tmp_3 = r_spd_ata_data;
          cmd_state->buf = buf16_tmp_3 + 1;
        }
      }
    }
  }
  else
  {
    return -504;
  }
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (0040505C) --------------------------------------------------------
int IoRun_atapi(ata_cmd_state_t *cmd_state)
{
  int result; // $v0
  u32 blktotal; // $s3
  char r_spd_ata_status; // $s0
  u8 Error; // $v0
  int lcyl_lo; // $v0
  int hcyl_hi; // $v1
  unsigned int lhcyl; // $s0
  s32 type_atapi; // $v1
  unsigned int lhcyl_div_2_1; // $a0
  unsigned int buf_atapi_i1; // $a1
  vu16 *buf_atapi; // $v1
  vu16 rvaltmp; // $v0
  unsigned int lhcyl_div_2_2; // $a2
  unsigned int buf_atapi_i2; // $a1
  int buf_atapi_offs; // $v0
  vu16 r_spd_ata_data; // $a0
  char ata_data_rval; // $a0

  if ( g_xatapi_verbose > 0 )
    Kprintf("Pio trans %d\n", cmd_state->blkcount_atapi * cmd_state->blksize_atapi);
  result = ata_wait_busy1_busy();
  if ( result < 0 )
    return result;
  result = 0;
  for ( blktotal = cmd_state->blkcount_atapi * cmd_state->blksize_atapi; result >= 0 && blktotal; blktotal -= lhcyl )
  {
    r_spd_ata_status = dev5_speed_regs.r_spd_ata_status;
    if ( (r_spd_ata_status & 1) != 0 )
    {
      if ( g_xatapi_verbose > 0 )
      {
        Error = sceAtaGetError();
        Kprintf("DEV5 ATA: error: ATAPI PIO iocmd err 0x%02x, 0x%02x\n", r_spd_ata_status, Error);
      }
      return -503;
    }
    if ( (r_spd_ata_status & 8) == 0 )
      return -504;
    // Unofficial: was 8 bit access
    lcyl_lo = (dev5_speed_regs.r_spd_ata_lcyl & 0xFF);
    // Unofficial: was 8 bit access
    hcyl_hi = (dev5_speed_regs.r_spd_ata_hcyl & 0xFF) << 8;
    lhcyl = lcyl_lo | hcyl_hi;
    if ( g_xatapi_verbose > 0 )
      Kprintf("ByteCount Trans byte %04x\n", lcyl_lo | hcyl_hi);
    type_atapi = cmd_state->type_atapi;
    if ( type_atapi == 2 )
    {
      lhcyl_div_2_2 = lhcyl >> 1;
      if ( g_xatapi_verbose > 0 )
      {
        Kprintf("IoRun_atapi input trans %d\n", cmd_state->blksize_atapi);
        lhcyl_div_2_2 = lhcyl >> 1;
      }
      for ( buf_atapi_i2 = 0; buf_atapi_i2 < lhcyl_div_2_2; buf_atapi_i2 += 1 )
      {
        buf_atapi_offs = 2 * buf_atapi_i2;
        r_spd_ata_data = dev5_speed_regs.r_spd_ata_data;
        *(u16 *)((char *)cmd_state->buf_atapi + buf_atapi_offs) = r_spd_ata_data;
      }
      if ( (lhcyl & 1) != 0 )
      {
        ata_data_rval = dev5_speed_regs.r_spd_ata_data;
        *((u8 *)cmd_state->buf_atapi + 2 * buf_atapi_i2) = ata_data_rval;
      }
      cmd_state->buf_atapi = (char *)cmd_state->buf_atapi + lhcyl;
    }
    else if ( type_atapi == 3 )
    {
      lhcyl_div_2_1 = lhcyl >> 1;
      if ( g_xatapi_verbose > 0 )
      {
        Kprintf("IoRun_atapi output trans %d\n", cmd_state->blksize_atapi);
        lhcyl_div_2_1 = lhcyl >> 1;
      }
      buf_atapi = (vu16 *)cmd_state->buf_atapi;
      for ( buf_atapi_i1 = 0; buf_atapi_i1 < lhcyl_div_2_1; buf_atapi_i1 += 1 )
      {
        rvaltmp = *buf_atapi++;
        dev5_speed_regs.r_spd_ata_data = rvaltmp;
      }
      if ( (lhcyl & 1) != 0 )
        dev5_speed_regs.r_spd_ata_data = *((u8 *)cmd_state->buf_atapi + 2 * buf_atapi_i1);
      cmd_state->buf_atapi = (char *)cmd_state->buf_atapi + lhcyl;
    }
    if ( g_xatapi_verbose > 0 )
      Kprintf("IoRun_atapi trans End\n");
    result = ata_wait_busy1_busy();
  }
  return result;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004052FC) --------------------------------------------------------
int atapi_some_transfer_wrapper(char *buf, unsigned int blkcount, int dir)
{
  unsigned int blkcount_tmp; // $s2
  int i; // $v1
  char r_spd_dbuf_stat; // $v0
  unsigned int dbuf_stat_mask; // $s0
  vu16 r_spd_intr_stat; // $a1
  int dbuf_stat_1; // $a1
  int result; // $v0
  char spd_intr_stat_1; // $v0
  char r_spd_ata_control; // $v0
  char r_spd_ata_status; // $v0
  u8 Error; // $v0
  char spd_ata_status_tmp; // $s1
  u8 error_tmp; // $s0
  u32 efbits[2]; // [sp+10h] [-8h] BYREF
  int flg;

  for ( blkcount_tmp = blkcount; blkcount_tmp; blkcount_tmp -= (flg ? dbuf_stat_mask : 0) )
  {
    dbuf_stat_mask = 0;
    for ( i = 0; i < 20 && !dbuf_stat_mask; i += 1 )
    {
      r_spd_dbuf_stat = dev5_speed_regs.r_spd_dbuf_stat;
      dbuf_stat_mask = r_spd_dbuf_stat & 0x1F;
    }
    if ( g_xatapi_verbose > 0 )
    {
      r_spd_intr_stat = dev5_speed_regs.r_spd_intr_stat;
      Kprintf("*SPD_RINTR_STAT %02x\n", r_spd_intr_stat);
      if ( g_xatapi_verbose > 0 )
      {
        dbuf_stat_1 = dev5_speed_regs.r_spd_dbuf_stat;
        Kprintf("*R_DBUF_STAT %02x\n", dbuf_stat_1);
      }
    }
    flg = 1;
    if ( !dbuf_stat_mask )
    {
      speedIntrEnable(3);
      if ( g_xatapi_verbose > 0 )
        Kprintf("Wait Event\n");
      WaitEventFlag(g_atapi_event_flag, 7u, 17, efbits);
      if ( g_xatapi_verbose > 0 )
        Kprintf("Event come\n");
      if ( (efbits[0] & 1) != 0 )
      {
        if ( g_xatapi_verbose > 0 )
        {
          Kprintf("DEV5 ATA: error: DmaRun, ata timedout\n");
        }
        return -502;
      }
      if ( (efbits[0] & 4) != 0 )
      {
        if ( g_xatapi_verbose > 0 )
        {
          Kprintf("DEV5 ATA: error: DmaRun, Media Eject\n");
        }
        return -550;
      }
      spd_intr_stat_1 = dev5_speed_regs.r_spd_intr_stat;
      if ( (spd_intr_stat_1 & 2) == 0 )
      {
        r_spd_ata_control = dev5_speed_regs.r_spd_ata_control;
        if ( (r_spd_ata_control & 1) != 0 )
        {
          r_spd_ata_status = dev5_speed_regs.r_spd_ata_status;
          spd_ata_status_tmp = r_spd_ata_status;
          Error = sceAtaGetError();
          error_tmp = Error;
          if ( g_xatapi_verbose > 0 )
            Kprintf("DEV5 ATA: error: cmd err 0x%02x, 0x%02x, while DmaRun\n", spd_ata_status_tmp, Error);
          if ( (error_tmp & 0x80) == 0 )
            return -503;
          return -510;
        }
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: warning: ata intr without error.\n");
        flg = 0;
      }
      else
      {
        dbuf_stat_mask = dev5_speed_regs.r_spd_dbuf_stat & 0x1F;
      }
    }
    if ( flg )
    {
      if ( blkcount_tmp < dbuf_stat_mask )
        dbuf_stat_mask = blkcount_tmp;
      result = SpdDmaTransfer(0, buf, (dbuf_stat_mask << 18) | 0x20, dir);
      buf += 512 * dbuf_stat_mask;
      if ( result < 0 )
        return result;
    }
  }
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004055B0) --------------------------------------------------------
int DmaRun_atapi(char *buf, int blkcount, int blksize, int dir)
{
  unsigned int blktotal; // $a1
  unsigned int blksectors; // $s3
  int blkremainder; // $s6
  int i; // $v1
  char r_spd_dbuf_stat; // $v0
  unsigned int dbuf_stat_mask; // $s0
  int result; // $v0
  char r_spd_intr_stat; // $v0
  char r_spd_ata_control; // $v0
  char r_spd_ata_status; // $v0
  u8 Error; // $v0
  char spd_ata_status_tmp; // $s1
  u8 error_tmp; // $s0
  char dbuf_stat_1; // $v0
  unsigned int dbuf_stat_sectors; // $s2
  vu16 m_spd_unk36; // $v1
  u32 efbits[2]; // [sp+18h] [-8h] BYREF

  blktotal = blkcount * blksize;
  blkremainder = blktotal & 0x1FF;
  if ( g_xatapi_verbose > 0 )
    Kprintf("DmaRun_atapi start\n");
  for ( blksectors = blktotal >> 9; blksectors; blksectors -= dbuf_stat_mask )
  {
    dbuf_stat_mask = 0;
    for ( i = 0; i < 20 && !dbuf_stat_mask; i += 1 )
    {
      r_spd_dbuf_stat = dev5_speed_regs.r_spd_dbuf_stat;
      dbuf_stat_mask = r_spd_dbuf_stat & 0x1F;
    }
    if ( !dbuf_stat_mask )
    {
      speedIntrEnable(3);
      WaitEventFlag(g_atapi_event_flag, 7u, 17, efbits);
      if ( (efbits[0] & 1) != 0 )
      {
        if ( g_xatapi_verbose > 0 )
        {
          Kprintf("DEV5 ATA: error: DmaRun, ata timedout\n");
        }
        return -502;
      }
      if ( (efbits[0] & 4) != 0 )
      {
        if ( g_xatapi_verbose > 0 )
        {
          Kprintf("DEV5 ATA: error: DmaRun, Media Eject\n");
        }
        return -550;
      }
      r_spd_intr_stat = dev5_speed_regs.r_spd_intr_stat;
      if ( (r_spd_intr_stat & 2) != 0 )
      {
        dbuf_stat_1 = dev5_speed_regs.r_spd_dbuf_stat;
        dbuf_stat_mask = dbuf_stat_1 & 0x1F;
      }
      else
      {
        r_spd_ata_control = dev5_speed_regs.r_spd_ata_control;
        if ( (r_spd_ata_control & 1) != 0 )
        {
          r_spd_ata_status = dev5_speed_regs.r_spd_ata_status;
          spd_ata_status_tmp = r_spd_ata_status;
          Error = sceAtaGetError();
          error_tmp = Error;
          if ( g_xatapi_verbose > 0 )
            Kprintf("DEV5 ATA: error: cmd err 0x%02x, 0x%02x, while DmaRun\n", spd_ata_status_tmp, Error);
          if ( (error_tmp & 0x80) == 0 )
            return -503;
          return -510;
        }
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: warning: ata intr without error.\n");
        continue;
      }
    }
    dbuf_stat_sectors = dbuf_stat_mask << 9;
    if ( blksectors < dbuf_stat_mask )
    {
      dbuf_stat_mask = blksectors;
      dbuf_stat_sectors = blksectors << 9;
    }
    if ( g_xatapi_verbose > 0 )
      Kprintf(
        "DmaRun_atapi  cnt %d nblk %d secsize %d bcr %08x\n",
        dbuf_stat_mask,
        blksectors,
        blksize,
        (dbuf_stat_sectors << 9) | 0x20);
    result = SpdDmaTransfer(0, buf, (dbuf_stat_sectors << 9) | 0x20, dir);
    buf += dbuf_stat_sectors;
    if ( result < 0 )
      return result;
  }
  if ( blkremainder )
  {
    while ( (dev5_speed_regs.r_spd_intr_stat & 1) == 0 );
    m_spd_unk36 = dev5_speed_regs.m_spd_unk36;
    dev5_speed_regs.m_spd_unk36 = m_spd_unk36 + 512;
    if ( g_xatapi_verbose > 0 )
      Kprintf("SpdDmaTransfer buf:%08x bcr:%d dir:%d\n", buf, 0x40020, dir);
    if ( dir )
    {
      memcpy(g_atapi_xfer_buf, buf, blkremainder);
      result = SpdDmaTransfer(0, g_atapi_xfer_buf, 0x40020u, dir);
      if ( result < 0 )
        return result;
    }
    else
    {
      result = SpdDmaTransfer(0, g_atapi_xfer_buf, 0x40020u, 0);
      if ( result < 0 )
        return result;
      memcpy(buf, g_atapi_xfer_buf, blkremainder);
    }
  }
  if ( g_xatapi_verbose > 0 )
  {
    Kprintf("DmaRun_atapi End.\n");
  }
  return 0;
}
// 405644: conditional instruction was optimized away because $s0.4==0
// 40A648: using guessed type int g_xatapi_verbose;
// 40A938: using guessed type int g_atapi_xfer_buf[130];

//----- (0040594C) --------------------------------------------------------
int DmaRun_atapi_extrans1(char *buf, int blkcount, int blksize, int dir)
{
  unsigned int blksectors; // $s2
  int blkremainder; // $s6
  int spd_dbuf_stat_i1; // $v1
  char r_spd_dbuf_stat; // $v0
  unsigned int dbuf_stat_mask; // $s0
  int result; // $v0
  char r_spd_intr_stat; // $v0
  char r_spd_ata_control; // $v0
  char r_spd_ata_status; // $v0
  u8 Error; // $v0
  char spd_ata_status_tmp; // $s1
  u8 error_tmp; // $s0
  char dbuf_stat_1; // $v0
  unsigned int dbuf_stat_sectors; // $s3
  vu16 m_spd_unk36; // $v1
  u32 efbits[2]; // [sp+18h] [-8h] BYREF

  if ( g_xatapi_verbose > 0 )
    Kprintf("DmaRun_atapi_extrans start\n");
  FpgaLayer2Off();
  FpgaClearBuffer();
  FpgaXfdir(dir);
  blkremainder = (blkcount * blksize) & 0x1FF;
  for ( blksectors = (unsigned int)(blkcount * blksize) >> 9; blksectors; blksectors -= dbuf_stat_mask )
  {
    dbuf_stat_mask = 0;
    for ( spd_dbuf_stat_i1 = 0; spd_dbuf_stat_i1 < 20 && !dbuf_stat_mask; spd_dbuf_stat_i1 += 1 )
    {
      r_spd_dbuf_stat = dev5_speed_regs.r_spd_dbuf_stat;
      dbuf_stat_mask = r_spd_dbuf_stat & 0x1F;
    }
    if ( !dbuf_stat_mask )
    {
      speedIntrEnable(3);
      WaitEventFlag(g_atapi_event_flag, 7u, 17, efbits);
      if ( (efbits[0] & 1) != 0 )
      {
        if ( g_xatapi_verbose > 0 )
        {
          Kprintf("DEV5 ATA: error: DmaRun_atapi_extrans, ata timedout\n");
        }
        return -502;
      }
      if ( (efbits[0] & 4) != 0 )
      {
        if ( g_xatapi_verbose > 0 )
        {
          Kprintf("DEV5 ATA: error: DmaRun_atapi_extrans, Media Eject\n");
        }
        return -550;
      }
      r_spd_intr_stat = dev5_speed_regs.r_spd_intr_stat;
      if ( (r_spd_intr_stat & 2) != 0 )
      {
        dbuf_stat_1 = dev5_speed_regs.r_spd_dbuf_stat;
        dbuf_stat_mask = dbuf_stat_1 & 0x1F;
      }
      else
      {
        r_spd_ata_control = dev5_speed_regs.r_spd_ata_control;
        if ( (r_spd_ata_control & 1) != 0 )
        {
          r_spd_ata_status = dev5_speed_regs.r_spd_ata_status;
          spd_ata_status_tmp = r_spd_ata_status;
          Error = sceAtaGetError();
          error_tmp = Error;
          if ( g_xatapi_verbose > 0 )
            Kprintf("DEV5 ATA: error: cmd err 0x%02x, 0x%02x, while DmaRun\n", spd_ata_status_tmp, Error);
          if ( (error_tmp & 0x80) == 0 )
            return -503;
          return -510;
        }
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: warning: ata intr without error.\n");
        continue;
      }
    }
    dbuf_stat_sectors = dbuf_stat_mask << 9;
    if ( blksectors < dbuf_stat_mask )
    {
      dbuf_stat_mask = blksectors;
      dbuf_stat_sectors = blksectors << 9;
    }
    if ( g_xatapi_verbose > 0 )
      Kprintf(
        "DmaRun_atapi_extrans  cnt %d nblk %d secsize %d bcr %08x\n",
        dbuf_stat_mask,
        blksectors,
        blksize,
        (dbuf_stat_sectors << 9) | 0x20);
    result = SpdDmaTransfer_extrans_1(0, buf, (dbuf_stat_sectors << 9) | 0x20, dir);
    buf += dbuf_stat_sectors;
    if ( result < 0 )
      return result;
  }
  if ( blkremainder )
  {
    while ( (dev5_speed_regs.r_spd_intr_stat & 1) == 0 );
    m_spd_unk36 = dev5_speed_regs.m_spd_unk36;
    dev5_speed_regs.m_spd_unk36 = m_spd_unk36 + 512;
    if ( g_xatapi_verbose > 0 )
      Kprintf("SpdDmaTransfer buf:%08x bcr:%d dir:%d\n", buf, 262176, dir);
    if ( dir )
    {
      memcpy(g_atapi_xfer_buf, buf, blkremainder);
      result = SpdDmaTransfer_extrans_1(0, g_atapi_xfer_buf, 0x40020u, dir);
      if ( result < 0 )
        return result;
    }
    else
    {
      result = SpdDmaTransfer_extrans_1(0, g_atapi_xfer_buf, 0x40020u, 0);
      if ( result < 0 )
        return result;
      memcpy(buf, g_atapi_xfer_buf, blkremainder);
    }
  }
  if ( g_xatapi_verbose > 0 )
  {
    Kprintf("DmaRun_atapi_extrans End.\n");
  }
  return 0;
}
// 4059FC: conditional instruction was optimized away because $s0.4==0
// 40A648: using guessed type int g_xatapi_verbose;
// 40A938: using guessed type int g_atapi_xfer_buf[130];

//----- (00405D04) --------------------------------------------------------
int DmaRun_atapi_extrans2(char *buf, int blkcount, int blksize, int dir)
{
  int result; // $v0
  char r_spd_intr_stat; // $v0
  char r_spd_ata_control; // $v0
  vu16 r_spd_rev_1; // $v0
  vu16 dma_ctrl_rval; // $v0
  s16 blktotal; // $v0
  unsigned int blksectors; // $s2
  int blkremainder; // $s6
  int i; // $s1
  unsigned int fpga_unk8148; // $s0
  int delaythread_period; // $a0
  u8 Error; // $v0
  u8 error_tmp; // $s0
  unsigned int unk8148_bytes; // $s3
  int extransres; // $s1
  vu16 m_spd_unk36; // $v1
  iop_sys_clock_t sysclk; // [sp+18h] [-10h] BYREF
  u32 efbits[2]; // [sp+20h] [-8h] BYREF

  if ( g_xatapi_verbose > 0 )
    Kprintf("DmaRun_atapi_extrans start\n");
  FpgaLayer2Off();
  FpgaClearBuffer();
  FpgaXfdir(dir);
  CancelAlarm(AtaAlarmrHandle, 0);
  USec2SysClock(0x989680u, &sysclk);
  result = SetAlarm(&sysclk, AtaAlarmrHandle, 0);
  if ( result < 0 )
  {
    return result;
  }
  while ( 1 )
  {
    speedIntrEnable(3);
    WaitEventFlag(g_atapi_event_flag, 7u, 17, efbits);
    if ( (efbits[0] & 1) != 0 )
    {
      if ( g_xatapi_verbose > 0 )
      {
        Kprintf("DEV5 ATA: error: DmaRun_atapi_extrans, ata timedout\n");
      }
      return -502;
    }
    if ( (efbits[0] & 4) != 0 )
    {
      if ( g_xatapi_verbose > 0 )
      {
        Kprintf("DEV5 ATA: error: DmaRun_atapi_extrans, Media Eject\n");
      }
      return -550;
    }
    r_spd_intr_stat = dev5_speed_regs.r_spd_intr_stat;
    if ( (r_spd_intr_stat & 2) != 0 )
    {
      break;
    }
    r_spd_ata_control = dev5_speed_regs.r_spd_ata_control;
    if ( (r_spd_ata_control & 1) != 0 )
    {
      Error = sceAtaGetError();
      error_tmp = Error;
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: cmd err 0x%02x, 0x%02x, while DmaRun\n", dev5_speed_regs.r_spd_ata_status, Error);
      if ( (error_tmp & 0x80) == 0 )
        return -503;
      return -510;
    }
    if ( g_xatapi_verbose > 0 )
      Kprintf("DEV5 ATA: warning: ata intr without error.\n");
  }
  r_spd_rev_1 = dev5_speed_regs.r_spd_rev_1;
  if ( r_spd_rev_1 >= 0x11u )
    dma_ctrl_rval = 6;
  else
    dma_ctrl_rval = 4;
  dev5_speed_regs.r_spd_dma_ctrl = dma_ctrl_rval;
  ata_pre_dma_cb();
  FpgaLayer1On();
  FpgaXfrenOn();
  blktotal = blkcount * blksize;
  blkremainder = blktotal & 0x1FF;
  for ( blksectors = (unsigned int)(blkcount * blksize) >> 9; blksectors; blksectors -= fpga_unk8148 )
  {
    for ( i = 0; ; i += 1 )
    {
      fpga_unk8148 = do_fpga_check_unk8148();
      if ( fpga_unk8148 >= 3 || fpga_unk8148 >= blksectors )
        break;
      if ( i / 500 )
      {
        delaythread_period = 10000;
        if ( i / 500 == 1 )
          delaythread_period = 100;
        DelayThread(delaythread_period);
      }
      PollEventFlag(g_atapi_event_flag, 5u, 17, efbits);
      if ( (efbits[0] & 1) != 0 )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: DmaRun_atapi_extrans, ata timedout\n");
        FpgaXfrenOff();
        FpgaLayer1Off();
        ata_post_dma_cb();
        if ( (dev5_speed_regs.r_spd_intr_stat & 2) == 0 && (dev5_speed_regs.r_spd_ata_control & 1) != 0 )
        {
          Error = sceAtaGetError();
          error_tmp = Error;
          if ( g_xatapi_verbose > 0 )
            Kprintf("DEV5 ATA: error: cmd err 0x%02x, 0x%02x, while DmaRun\n", dev5_speed_regs.r_spd_ata_status, Error);
          if ( (error_tmp & 0x80) == 0 )
            return -503;
          return -510;
        }
        return -502;
      }
      if ( (efbits[0] & 4) != 0 )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: DmaRun_atapi_extrans, Media Eject\n");
        FpgaXfrenOff();
        FpgaLayer1Off();
        ata_post_dma_cb();
        return -550;
      }
    }
    unk8148_bytes = fpga_unk8148 << 9;
    if ( blksectors < fpga_unk8148 )
    {
      fpga_unk8148 = blksectors;
      unk8148_bytes = blksectors << 9;
    }
    if ( g_xatapi_verbose > 0 )
      Kprintf(
        "DmaRun_atapi_extrans  cnt %d nblk %d secsize %d bcr %08x\n",
        fpga_unk8148,
        blksectors,
        blksize,
        (unk8148_bytes << 9) | 0x20);
    extransres = SpdDmaTransfer_extrans_2(0, buf, (unk8148_bytes << 9) | 0x20, dir);
    if ( extransres < 0 )
      break;
    buf += unk8148_bytes;
  }
  FpgaXfrenOff();
  FpgaLayer1Off();
  ata_post_dma_cb();
  if ( extransres >= 0 && blkremainder )
  {
    while ( (dev5_speed_regs.r_spd_intr_stat & 1) == 0 );
    m_spd_unk36 = dev5_speed_regs.m_spd_unk36;
    dev5_speed_regs.m_spd_unk36 = m_spd_unk36 + 512;
    if ( g_xatapi_verbose > 0 )
      Kprintf("SpdDmaTransfer buf:%08x bcr:%d dir:%d\n", buf, 0x40020, dir);
    ata_pre_dma_cb();
    FpgaLayer1On();
    FpgaXfrenOn();
    if ( dir )
    {
      memcpy(g_atapi_xfer_buf, buf, blkremainder);
      extransres = SpdDmaTransfer_extrans_2(0, g_atapi_xfer_buf, 0x40020u, dir);
    }
    else
    {
      extransres = SpdDmaTransfer_extrans_2(0, g_atapi_xfer_buf, 0x40020u, 0);
      if ( extransres >= 0 )
      {
        memcpy(buf, g_atapi_xfer_buf, blkremainder);
      }
    }
    FpgaXfrenOff();
    FpgaLayer1Off();
    ata_post_dma_cb();
  }
  if ( extransres < 0 )
  {
    return extransres;
  }
  if ( g_xatapi_verbose > 0 )
  {
    Kprintf("DmaRun_atapi_extrans End.\n");
  }
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;
// 40A938: using guessed type int g_atapi_xfer_buf[130];

//----- (004062F4) --------------------------------------------------------
void DmaRun_spck(char *buf, unsigned int secsize)
{
  unsigned int secsize_sectors; // $s2
  unsigned int unk8148_val; // $s1
  unsigned int unk8148_bytes; // $s3
  int xferres; // $s0
  vu16 m_spd_unk36; // $v1
  int result; // $v0

  if ( g_xatapi_verbose > 0 )
    Kprintf("DmaRun_spck start\n");
  FpgaSpckmodeOn();
  FpgaLayer2Off();
  FpgaClearBuffer();
  FpgaXfdir(0);
  for ( secsize_sectors = secsize >> 9; secsize_sectors; secsize_sectors -= unk8148_val )
  {
    for ( unk8148_val = 0; unk8148_val < 4; unk8148_val = do_fpga_check_unk8148() );
    unk8148_bytes = unk8148_val << 9;
    if ( secsize_sectors < unk8148_val )
    {
      unk8148_val = secsize_sectors;
      unk8148_bytes = secsize_sectors << 9;
    }
    if ( g_xatapi_verbose > 0 )
      Kprintf(
        "DmaRun_spck  cnt %d nblk %d secsize %d bcr %08x\n",
        unk8148_val,
        secsize_sectors,
        secsize,
        (unk8148_bytes << 9) | 0x20);
    xferres = SpdDmaTransfer_extrans_3(0, buf, (unk8148_bytes << 9) | 0x20, 1);
    
    if ( xferres < 0 )
    {
      FpgaSpckmodeOff();
      return;
    }
    buf += unk8148_bytes;
  }
  if ( (secsize & 0x1FF) != 0 )
  {
    m_spd_unk36 = dev5_speed_regs.m_spd_unk36;
    dev5_speed_regs.m_spd_unk36 = m_spd_unk36 + 512;
    if ( g_xatapi_verbose > 0 )
      Kprintf("SpdDmaTransfer buf:%08x bcr:%d dir:%d\n", buf, 262176, 1);
    memcpy(g_atapi_xfer_buf, buf, secsize & 0x1FF);
    result = SpdDmaTransfer_extrans_3(0, g_atapi_xfer_buf, 0x40020u, 1);
    if ( result < 0 )
    {
      return;
    }
  }
  FpgaSpckmodeOff();
  if ( g_xatapi_verbose > 0 )
  {
    Kprintf("DmaRun_spck End.\n");
  }
}
// 40A648: using guessed type int g_xatapi_verbose;
// 40A938: using guessed type int g_atapi_xfer_buf[130];

//----- (004064D4) --------------------------------------------------------
int sceAtaWaitResult(void)
{
  int res; // $s0
  int waittmp1; // $v1
  vu16 r_spd_dbuf_stat_1; // $a1
  int r_spd_intr_stat_1; // $a1
  vu16 r_spd_intr_mask_1; // $a2
  vu16 r_spd_dbuf_stat_2; // $a1
  vu16 r_spd_intr_stat_2; // $a1
  vu16 r_spd_intr_mask_2; // $a2
  char r_spd_ata_status; // $v0
  u8 Error; // $v0
  u8 error_tmp; // $s1
  int intr_stat_msk; // [sp+10h] [-8h]
  char status_tmp; // [sp+10h] [-8h]
  u32 efbits; // [sp+14h] [-4h] BYREF
  int suc;

  suc = 0;
  res = 0;
  if ( atad_cmd_state.type == 1 || atad_cmd_state.type == 8 )
  {
    WaitEventFlag(g_atapi_event_flag, 7u, 17, &efbits);
    if ( (efbits & 1) != 0 )
    {
      res = -502;
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: ata timedout while non data command\n");
    }
    if ( (efbits & 4) != 0 )
    {
      res = -550;
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: DmaRun, Media Eject\n");
    }
    suc = 1;
  }
  else if ( atad_cmd_state.type == 4 || atad_cmd_state.type == 6 || atad_cmd_state.type == 5 )
  {
    res = atapi_some_transfer_wrapper((char *)atad_cmd_state.buf, atad_cmd_state.blkcount, atad_cmd_state.dir);
    if ( !res )
    {
      intr_stat_msk = 0;
      for ( waittmp1 = 0; waittmp1 < 100 && !intr_stat_msk; waittmp1 += 1 )
      {
        intr_stat_msk = dev5_speed_regs.r_spd_intr_stat & 1;
      }
      if ( !intr_stat_msk )
      {
        speedIntrEnable(1);
        WaitEventFlag(g_atapi_event_flag, 7u, 17, &efbits);
        if ( (efbits & 1) != 0 )
        {
          if ( g_xatapi_verbose > 0 )
          {
            r_spd_dbuf_stat_1 = dev5_speed_regs.r_spd_dbuf_stat;
            Kprintf("DEV5 ATA: error: ata timedout, buffer stat %04x\n", r_spd_dbuf_stat_1);
            if ( g_xatapi_verbose > 0 )
            {
              r_spd_intr_stat_1 = dev5_speed_regs.r_spd_intr_stat;
              r_spd_intr_mask_1 = dev5_speed_regs.r_spd_intr_mask;
              Kprintf("DEV5 ATA: error: istat %x, ienable %x\n", r_spd_intr_stat_1, r_spd_intr_mask_1);
            }
          }
          res = -502;
        }
        if ( (efbits & 4) != 0 )
        {
          if ( g_xatapi_verbose > 0 )
          {
            r_spd_dbuf_stat_2 = dev5_speed_regs.r_spd_dbuf_stat;
            Kprintf("DEV5 ATA: error: ata eject, buffer stat %04x\n", r_spd_dbuf_stat_2);
            if ( g_xatapi_verbose > 0 )
            {
              r_spd_intr_stat_2 = dev5_speed_regs.r_spd_intr_stat;
              r_spd_intr_mask_2 = dev5_speed_regs.r_spd_intr_mask;
              Kprintf("DEV5 ATA: error: istat %x, ienable %x\n", r_spd_intr_stat_2, r_spd_intr_mask_2);
            }
          }
          res = -550;
        }
      }
      suc = 1;
    }
  }
  else
  {
    while ( 1 )
    {
      res = ata_wait_busy1_busy();
      if ( res < 0 )
      {
        break;
      }
      atad_cmd_state.blkcount--;
      if ( atad_cmd_state.blkcount == 0xFFFFFFFF )
      {
        suc = 1;
        break;
      }
      res = ata_pio_transfer(&atad_cmd_state);
      if ( res < 0 )
      {
        break;
      }
    }
  }
  if ( suc && !res )
  {
    r_spd_ata_status = dev5_speed_regs.r_spd_ata_status;
    status_tmp = r_spd_ata_status;
    if ( (r_spd_ata_status & 0x80) != 0 )
    {
      res = ata_wait_busy1_busy();
      status_tmp = dev5_speed_regs.r_spd_ata_status;
    }
    if ( (status_tmp & 1) != 0 )
    {
      Error = sceAtaGetError();
      error_tmp = Error;
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: cmd err 0x%02x, 0x%02x\n", status_tmp, Error);
      res = -503;
      if ( (error_tmp & 0x80) != 0 )
        res = -510;
    }
  }
  CancelAlarm(AtaAlarmrHandle, 0);
  speedLEDCtl(0);
  if ( res )
  {
    if ( g_xatapi_verbose > 0 )
    {
      Kprintf("DEV5 ATA: error: ATA failed, %d\n", res);
    }
    return res;
  }
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;
// 40A710: using guessed type ata_cmd_state_t atad_cmd_state;

//----- (004068B8) --------------------------------------------------------
int xatapi_6_sceAtaWaitResult(void)
{
  int restmp; // $s0
  iop_event_info_t efinfo; // [sp+10h] [-20h] BYREF

  if ( vReferEventFlagStatus(g_acmd_evfid, &efinfo) || (efinfo.currBits & 1) != 0 )
  {
    if ( g_xatapi_verbose > 0 )
    {
      Kprintf("sceCdAtapiWaitResult Call Error\n");
    }
    return -511;
  }
  else
  {
    restmp = sceAtaWaitResult();
    SetEventFlag(g_acmd_evfid, 1u);
    return restmp;
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (0040694C) --------------------------------------------------------
int sceCdAtapiWaitResult_local(void)
{
  int res; // $s2
  int blktotal1; // $s3
  int blkoffs; // $s0
  int padres; // $v0
  int dmares; // $v0
  int trycnt1; // $v1
  vu16 r_spd_dbuf_stat; // $a1
  int r_spd_intr_stat; // $a1
  vu16 r_spd_intr_mask; // $a2
  vu16 dbuf_stat_1; // $a1
  vu16 intr_stat_tmp1; // $a1
  vu16 intr_mask_tmp1; // $a2
  char r_spd_ata_status; // $v0
  u8 Error; // $v0
  u8 error_tmp; // $s0
  int intr_stat_msk; // [sp+10h] [-10h]
  char ata_status_tmp; // [sp+10h] [-10h]
  u32 efbits; // [sp+14h] [-Ch] BYREF
  int padinfo[2]; // [sp+18h] [-8h] BYREF

  res = 0;
  if ( atad_cmd_state.type_atapi == 1 || atad_cmd_state.type_atapi == 8 )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("waitresult\n");
    WaitEventFlag(g_atapi_event_flag, 7u, 17, &efbits);
    if ( (efbits & 1) != 0 )
    {
      res = -502;
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: ata timedout while non data command\n");
    }
    if ( (efbits & 4) != 0 )
    {
      res = -550;
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: ata eject while non data command\n");
    }
  }
  else if ( atad_cmd_state.type_atapi != 4 && atad_cmd_state.type_atapi != 6 && atad_cmd_state.type_atapi != 5 )
  {
    res = IoRun_atapi(&atad_cmd_state);
  }
  else
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("waitresult dma\n");
    if ( !g_reset_scrambling_pack )
    {
      res = DmaRun_atapi((char *)atad_cmd_state.buf_atapi, atad_cmd_state.blkcount_atapi, atad_cmd_state.blksize_atapi, atad_cmd_state.dir_atapi);
    }
    else if ( atad_cmd_state.dir_atapi )
    {
      blktotal1 = atad_cmd_state.blkcount_atapi * atad_cmd_state.blksize_atapi;
      for ( blkoffs = 0; blkoffs < blktotal1; blkoffs += atad_cmd_state.blkcount_atapi * atad_cmd_state.blksize_atapi )
      {
        padres = Mpeg2CheckPadding(
                   (char *)atad_cmd_state.buf_atapi + blkoffs,
                   blktotal1 - blkoffs,
                   padinfo,
                   &g_pes_scrambling_control_pack);
        if ( padres < 0 )
        {
          res = DmaRun_atapi((char *)atad_cmd_state.buf_atapi, atad_cmd_state.blkcount_atapi, atad_cmd_state.blksize_atapi, atad_cmd_state.dir_atapi);
          break;
        }
        atad_cmd_state.blksize_atapi = 2048;
        atad_cmd_state.blkcount_atapi = padinfo[0];
        if ( padres )
          dmares = DmaRun_atapi_extrans1(
                     (char *)atad_cmd_state.buf_atapi + blkoffs,
                     padinfo[0],
                     2048,
                     atad_cmd_state.dir_atapi);
        else
          dmares = DmaRun_atapi((char *)atad_cmd_state.buf_atapi + blkoffs, padinfo[0], 2048, atad_cmd_state.dir_atapi);
        res = dmares;
      }
    }
    else
    {
      res = DmaRun_atapi_extrans2(
              (char *)atad_cmd_state.buf_atapi,
              atad_cmd_state.blkcount_atapi,
              atad_cmd_state.blksize_atapi,
              0);
    }
    if ( !res )
    {
      intr_stat_msk = 0;
      for ( trycnt1 = 0; trycnt1 < 100 && !intr_stat_msk; trycnt1 += 1 )
      {
        intr_stat_msk = dev5_speed_regs.r_spd_intr_stat & 1;
      }
      if ( !intr_stat_msk )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("ata command not finished yet\n");
        speedIntrEnable(1);
        WaitEventFlag(g_atapi_event_flag, 7u, 17, &efbits);
        if ( (efbits & 1) != 0 )
        {
          if ( g_xatapi_verbose > 0 )
          {
            r_spd_dbuf_stat = dev5_speed_regs.r_spd_dbuf_stat;
            Kprintf("DEV5 ATA: error: ata timedout, buffer stat %04x\n", r_spd_dbuf_stat);
            if ( g_xatapi_verbose > 0 )
            {
              r_spd_intr_stat = dev5_speed_regs.r_spd_intr_stat;
              r_spd_intr_mask = dev5_speed_regs.r_spd_intr_mask;
              Kprintf("DEV5 ATA: error: istat %x, ienable %x\n", r_spd_intr_stat, r_spd_intr_mask);
            }
          }
          res = -502;
        }
        if ( (efbits & 4) != 0 )
        {
          if ( g_xatapi_verbose > 0 )
          {
            dbuf_stat_1 = dev5_speed_regs.r_spd_dbuf_stat;
            Kprintf("DEV5 ATA: error: ata eject, buffer stat %04x\n", dbuf_stat_1);
            if ( g_xatapi_verbose > 0 )
            {
              intr_stat_tmp1 = dev5_speed_regs.r_spd_intr_stat;
              intr_mask_tmp1 = dev5_speed_regs.r_spd_intr_mask;
              Kprintf("DEV5 ATA: error: istat %x, ienable %x\n", intr_stat_tmp1, intr_mask_tmp1);
            }
          }
          res = -550;
        }
      }
    }
  }
  if ( !res )
  {
    r_spd_ata_status = dev5_speed_regs.r_spd_ata_status;
    ata_status_tmp = r_spd_ata_status;
    if ( (r_spd_ata_status & 0x80) != 0 )
    {
      res = ata_wait_busy1_busy();
      ata_status_tmp = dev5_speed_regs.r_spd_ata_status;
    }
    if ( (ata_status_tmp & 1) != 0 )
    {
      Error = sceAtaGetError();
      error_tmp = Error;
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: cmd status 0x%02x, error 0x%02x\n", ata_status_tmp, Error);
      res = -503;
      if ( (error_tmp & 0x80) != 0 )
        res = -510;
    }
  }
  CancelAlarm(AtaAlarmrHandle, 0);
  speedLEDCtl(0);
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdAtapiWaitResult_local() End.\n");
  if ( res )
  {
    if ( g_xatapi_verbose > 0 )
    {
      Kprintf("DEV5 ATA: error: ATA failed, %d\n", res);
    }
    return res;
  }
  return 0;
}
// 40A630: using guessed type int g_reset_scrambling_pack;
// 40A648: using guessed type int g_xatapi_verbose;
// 40A710: using guessed type ata_cmd_state_t atad_cmd_state;
// 40694C: using guessed type s32 padinfo[2];

//----- (00406E98) --------------------------------------------------------
int xatapi_8_sceCdAtapiWaitResult(void)
{
  int restmp; // $s0
  iop_event_info_t efinfo; // [sp+10h] [-20h] BYREF

  if ( vReferEventFlagStatus(g_acmd_evfid, &efinfo) || (efinfo.currBits & 1) != 0 )
  {
    if ( g_xatapi_verbose > 0 )
    {
      Kprintf("sceCdAtapiWaitResult Call Error\n");
    }
    return -511;
  }
  else
  {
    restmp = sceCdAtapiWaitResult_local();
    SetEventFlag(g_acmd_evfid, 1u);
    return restmp;
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00406F2C) --------------------------------------------------------
void ata_bus_reset_inner(void)
{
  dev5_speed_regs.r_spd_if_ctrl = 128;
  DelayThread(100);
  dev5_speed_regs.r_spd_if_ctrl = 0;
  dev5_speed_regs.r_spd_if_ctrl = 72;
  DelayThread(3000);
  if ( g_xatapi_verbose > 0 )
    Kprintf("hard reset\n");
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00406F9C) --------------------------------------------------------
int ata_bus_reset(void)
{
  char r_spd_if_ctrl; // $v0

  r_spd_if_ctrl = dev5_speed_regs.r_spd_if_ctrl;
  if ( (r_spd_if_ctrl & 0x40) == 0 )
    ata_bus_reset_inner();
  return ata_wait_busy2_busy();
}

//----- (00406FE0) --------------------------------------------------------
int xatapi_4_sceAtaSoftReset(void)
{
  char r_spd_ata_control; // $v0

  r_spd_ata_control = dev5_speed_regs.r_spd_ata_control;
  if ( (r_spd_ata_control & 0x80) == 0 )
  {
    dev5_speed_regs.r_spd_ata_control = 6;
    DelayThread(100);
    dev5_speed_regs.r_spd_ata_control = 2;
    DelayThread(3000);
    if ( g_xatapi_verbose > 0 )
      Kprintf("soft reset\n");
    return ata_wait_busy1_busy();
  }
  return -501;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (0040706C) --------------------------------------------------------
int sceAtaFlushCache(int device)
{
  int result; // $v0

  result = xatapi_5_sceAtaExecCmd(0, 1u, 0, 0, 0, 0, 0, 16 * device, 0xE7u, 1u);
  if ( !result )
    return xatapi_6_sceAtaWaitResult();
  return result;
}

//----- (004070D0) --------------------------------------------------------
int ata_device_identify(int device, void *info)
{
  int result; // $v0

  result = xatapi_5_sceAtaExecCmd(info, 1u, 0, 0, 0, 0, 0, 16 * device, 0xECu, 2u);
  if ( !result )
    return xatapi_6_sceAtaWaitResult();
  return result;
}

//----- (00407134) --------------------------------------------------------
int ata_device_pkt_identify(int device, void *info)
{
  int result; // $v0

  result = xatapi_5_sceAtaExecCmd(info, 1u, 0, 0, 0, 0, 0, 16 * device, 0xA1u, 2u);
  if ( !result )
    return xatapi_6_sceAtaWaitResult();
  return result;
}

//----- (00407198) --------------------------------------------------------
int atapi_device_set_transfer_mode(int device, int type, int mode)
{
  u8 type_tmp; // $s1
  u8 mode_tmp; // $s0
  int result; // $v0

  type_tmp = type;
  mode_tmp = mode;
  result = xatapi_5_sceAtaExecCmd(0, 1u, 3u, (u8)(mode | type), 0, 0, 0, 16 * device, 0xEFu, 1u);
  if ( !result )
  {
    result = xatapi_6_sceAtaWaitResult();
    if ( !result )
    {
      if ( type_tmp == 0x20 )
      {
        ata_multiword_dma_mode(mode_tmp);
        return 0;
      }
      else if ( type_tmp >= 0x21u )
      {
        if ( type_tmp == 0x40 )
        {
          ata_ultra_dma_mode(mode_tmp);
        }
        return 0;
      }
      else
      {
        if ( type_tmp == 8 )
        {
          ata_pio_mode(mode_tmp);
        }
        return 0;
      }
    }
  }
  return result;
}

//----- (00407284) --------------------------------------------------------
int ata_device_set_transfer_mode(int device, int type, int mode)
{
  u8 type_tmp; // $s1
  u8 mode_tmp; // $s0
  int result; // $v0

  type_tmp = type;
  mode_tmp = mode;
  result = sceAtaExecCmd(0, 1u, 3u, (u8)(mode | type), 0, 0, 0, 16 * device, 0xEFu, 1u);
  if ( !result )
  {
    result = sceAtaWaitResult();
    if ( !result )
    {
      if ( type_tmp == 32 )
      {
        ata_multiword_dma_mode(mode_tmp);
        return 0;
      }
      else if ( type_tmp >= 0x21u )
      {
        if ( type_tmp == 64 )
        {
          ata_ultra_dma_mode(mode_tmp);
        }
        return 0;
      }
      else
      {
        if ( type_tmp == 8 )
        {
          ata_pio_mode(mode_tmp);
        }
        return 0;
      }
    }
  }
  return result;
}

//----- (00407370) --------------------------------------------------------
void ata_device_probe(ata_devinfo_t *devinfo)
{
  char r_spd_ata_control; // $v0
  char r_spd_ata_nsector; // $a2
  char r_spd_ata_sector; // $a0
  char r_spd_ata_lcyl; // $a1
  u8 r_spd_ata_hcyl; // $v1
  int r_spd_ata_hcyl_low; // $v1

  devinfo->exists = 0;
  r_spd_ata_control = dev5_speed_regs.r_spd_ata_control;
  devinfo->has_packet = 2;
  if ( (r_spd_ata_control & 0x88) != 0 )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("FindDev ATA_BUSY\n");
  }
  else
  {
    r_spd_ata_nsector = dev5_speed_regs.r_spd_ata_nsector;
    r_spd_ata_sector = dev5_speed_regs.r_spd_ata_sector;
    r_spd_ata_lcyl = dev5_speed_regs.r_spd_ata_lcyl;
    r_spd_ata_hcyl = dev5_speed_regs.r_spd_ata_hcyl;
    if ( r_spd_ata_nsector == 1 && r_spd_ata_sector == 1 )
    {
      devinfo->exists = 1;
      if ( !r_spd_ata_lcyl && !r_spd_ata_hcyl )
        devinfo->has_packet = 0;
      if ( r_spd_ata_lcyl == 20 && r_spd_ata_hcyl == 235 )
        devinfo->has_packet = 1;
      dev5_speed_regs.r_spd_ata_lcyl = 85;
      dev5_speed_regs.r_spd_ata_hcyl = 170;
      // Unofficial: was 8 bit access
      r_spd_ata_hcyl_low = (dev5_speed_regs.r_spd_ata_hcyl & 0xFF);
      // Unofficial: was 8 bit access
      if ( (dev5_speed_regs.r_spd_ata_lcyl & 0xFF) != 85 || r_spd_ata_hcyl_low != 170 )
        devinfo->exists = 0;
    }
    else if ( g_xatapi_verbose > 0 )
    {
      Kprintf("FindDev ATA_NOT_CONNECT\n");
    }
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004074C8) --------------------------------------------------------
void atapi_device_set_transfer_mode_outer(int device)
{
  int device_tmp; // $s0

  device_tmp = device;
  if ( g_dma_mode_value )
  {
    if ( g_xatapi_verbose >= 0 )
    {
      Kprintf("UDMA_mode Mode%d\n", 2);
      device = device_tmp;
    }
    while ( atapi_device_set_transfer_mode(device, 64, (u8)g_dma_speed_value) < 0 )
    {
      DelayThread(2000000);
      device = device_tmp;
    }
  }
  else
  {
    if ( g_xatapi_verbose >= 0 )
    {
      Kprintf("MDMA_mode Mode%d\n", 2);
      device = device_tmp;
    }
    while ( atapi_device_set_transfer_mode(device, 32, (u8)g_dma_speed_value) < 0 )
    {
      DelayThread(2000000);
      device = device_tmp;
    }
  }
}
// 40A638: using guessed type int g_dma_mode_value;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407594) --------------------------------------------------------
void ata_device_set_transfer_mode_outer(int device)
{
  int trycnt1; // $s0
  int trycnt2; // $s0

  if ( g_dma_mode_value )
  {
    if ( g_xatapi_verbose >= 0 )
    {
      Kprintf("UDMA_mode Mode%d\n", 2);
    }
    for ( trycnt1 = 0; trycnt1 < 3 && ata_device_set_transfer_mode(device, 64, (u8)g_dma_speed_value); trycnt1 += 1 )
    {
      DelayThread(2000000);
    }
  }
  else
  {
    if ( g_xatapi_verbose >= 0 )
    {
      Kprintf("MDMA_mode Mode%d\n", 2);
    }
    for ( trycnt2 = 0; trycnt2 < 3 && ata_device_set_transfer_mode(device, 32, (u8)g_dma_speed_value); trycnt2 += 1 )
    {
      DelayThread(2000000);
    }
  }
}
// 40A638: using guessed type int g_dma_mode_value;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004076A0) --------------------------------------------------------
void ata_init_devices(ata_devinfo_t *devinfo)
{
  int result; // $v0
  int identify_nr; // $s1
  s32 has_packet; // $v0

  result = xatapi_4_sceAtaSoftReset();
  if ( result )
    return;
  ata_device_probe(devinfo);
  if ( !devinfo->exists )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("DEV5 ATA: error: there is no device0\n");
    devinfo[1].exists = 0;
    return;
  }
  result = ata_device_select(1);
  if ( result )
    return;
  // Unofficial: was 8 bit access
  if ( (dev5_speed_regs.r_spd_ata_control & 0xFF) )
    ata_device_probe(devinfo + 1);
  else
    devinfo[1].exists = 0;
  ata_pio_mode(0);
  g_is_in_read_info = 0;
  for ( identify_nr = 0; identify_nr < 2; identify_nr += 1 )
  {
    if ( devinfo->exists )
    {
      has_packet = devinfo->has_packet;
      if ( !has_packet )
      {
        devinfo->exists = ata_device_identify(identify_nr, ata_param) == 0;
        has_packet = devinfo->has_packet;
      }
      if ( has_packet == 1 )
        devinfo->exists = ata_device_pkt_identify(identify_nr, ata_param) == 0;
      if ( g_xatapi_verbose > 0 )
        Kprintf("device%d connected, kind %d.\n", identify_nr, devinfo->has_packet);
      if ( devinfo->exists && devinfo->has_packet == 1 )
      {
        do_hex_dump(ata_param, 512);
        devinfo->lba48 = do_atapi_cmd_inquiry_12h(identify_nr) == 0;
        if ( !devinfo->lba48 )
        {
          atapi_device_set_transfer_mode_outer(identify_nr);
        }
        else
        {
          g_is_in_read_info = 1;
          if ( g_xatapi_verbose >= 0 )
            Kprintf("Atapi Program Aria Brokun.\n");
        }
      }
    }
    ++devinfo;
  }
}
// 40A648: using guessed type int g_xatapi_verbose;
// 40A658: using guessed type int g_is_in_read_info;
// 40A738: using guessed type int ata_param[128];

//----- (00407898) --------------------------------------------------------
void sceAtapiInit(int device)
{
  int resetval; // $v0

  (void)device;
  if ( g_ata_devinfo_init )
    return;
  g_ata_devinfo_init = 1;
  while ( 1 )
  {
    while ( 1 )
    {
      resetval = ata_bus_reset();
      if ( resetval != -550 )
        break;
      g_is_wait_busy = 0;
    }
    if ( !resetval )
      break;
    dev5_speed_regs.r_spd_if_ctrl = 0;
  }
  ata_init_devices(atad_devinfo);
}
// 40A644: using guessed type int g_is_wait_busy;
// 40A64C: using guessed type int g_ata_devinfo_init;
// 40A6E8: using guessed type ata_devinfo_t atad_devinfo[2];

//----- (00407968) --------------------------------------------------------
void sceAtInterInit(void)
{
  int sc_tmp; // [sp+10h] [-8h] BYREF

  speedRegisterIntrCb(1, ata_intr_cb);
  speedRegisterIntrCb(0, ata_intr_cb);
  speedRegisterPreDmaCb(0, ata_pre_dma_cb);
  speedRegisterPostDmaCb(0, ata_post_dma_cb);
  if ( sceCdSC(0xFFFFFFDC, &sc_tmp) )
    speedIntrEnable(256);
}

//----- (004079E4) --------------------------------------------------------
int create_event_flags(void)
{
  int efidx; // $a0
  iop_event_t efparam; // [sp+10h] [-10h] BYREF

  efparam.attr = 0;
  efparam.bits = 0;
  g_atapi_event_flag = CreateEventFlag(&efparam);
  if ( g_atapi_event_flag < 0 )
    return 1;
  efparam.attr = 2;
  efparam.option = 0;
  efparam.bits = 1;
  g_acmd_evfid = CreateEventFlag(&efparam);
  if ( g_acmd_evfid >= 0 )
  {
    efparam.bits = 1;
    g_adma_evfid = CreateEventFlag(&efparam);
    if ( g_adma_evfid >= 0 )
    {
      efparam.bits = 1;
      g_io_event_flag = CreateEventFlag(&efparam);
      if ( g_io_event_flag >= 0 )
      {
        sceCdSC(0xFFFFFFE0, &g_acmd_evfid);
        sceCdSC(0xFFFFFFDF, &g_adma_evfid);
        return 1;
      }
      DeleteEventFlag(g_atapi_event_flag);
      DeleteEventFlag(g_acmd_evfid);
      efidx = g_adma_evfid;
    }
    else
    {
      DeleteEventFlag(g_atapi_event_flag);
      efidx = g_acmd_evfid;
    }
  }
  else
  {
    efidx = g_atapi_event_flag;
  }
  DeleteEventFlag(efidx);
  return 0;
}

//----- (00407B20) --------------------------------------------------------
void FpgaLayer1On(void)
{
  vu16 r_fpga_layer1; // $a2
  vu16 layer1_tmp_1; // $v0
  int layer1_tmp_2; // $a2

  if ( g_xatapi_verbose > 0 )
  {
    r_fpga_layer1 = dev5_fpga_regs.r_fpga_layer1;
    Kprintf("%s():old:FPGA_LAYER1 %x\n", "FpgaLayer1On", r_fpga_layer1);
  }
  layer1_tmp_1 = dev5_fpga_regs.r_fpga_layer1;
  dev5_fpga_regs.r_fpga_layer1 = layer1_tmp_1 & 0xFFFE;
  dev5_fpga_regs.r_fpga_layer1 = (layer1_tmp_1 & 0xFFFE) | 1;
  if ( g_xatapi_verbose > 0 )
  {
    layer1_tmp_2 = dev5_fpga_regs.r_fpga_layer1;
    Kprintf("%s():new:FPGA_LAYER1 %x\n", "FpgaLayer1On", layer1_tmp_2);
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407BC4) --------------------------------------------------------
void FpgaLayer1Off(void)
{
  vu16 r_fpga_layer1; // $a2
  vu16 layer1_tmp_1; // $v0
  int layer1_tmp_2; // $a2

  if ( g_xatapi_verbose > 0 )
  {
    r_fpga_layer1 = dev5_fpga_regs.r_fpga_layer1;
    Kprintf("%s():old:FPGA_LAYER1 %x\n", "FpgaLayer1Off", r_fpga_layer1);
  }
  layer1_tmp_1 = dev5_fpga_regs.r_fpga_layer1;
  dev5_fpga_regs.r_fpga_layer1 = layer1_tmp_1 & 0xFFFE;
  if ( g_xatapi_verbose > 0 )
  {
    layer1_tmp_2 = dev5_fpga_regs.r_fpga_layer1;
    Kprintf("%s():new:FPGA_LAYER1 %x\n", "FpgaLayer1Off", layer1_tmp_2);
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407C54) --------------------------------------------------------
void FpgaLayer2On(void)
{
  vu16 r_fpga_layer2; // $a2
  vu16 layer2_tmp_1; // $v0
  int layer2_tmp_2; // $a2

  if ( g_xatapi_verbose > 0 )
  {
    r_fpga_layer2 = dev5_fpga_regs.r_fpga_layer2;
    Kprintf("%s():old:FPGA_LAYER2 %x\n", "FpgaLayer2On", r_fpga_layer2);
  }
  layer2_tmp_1 = dev5_fpga_regs.r_fpga_layer2;
  dev5_fpga_regs.r_fpga_layer2 = layer2_tmp_1 & 0xFFFE;
  dev5_fpga_regs.r_fpga_layer2 = (layer2_tmp_1 & 0xFFFE) | 1;
  if ( g_xatapi_verbose > 0 )
  {
    layer2_tmp_2 = dev5_fpga_regs.r_fpga_layer2;
    Kprintf("%s():new:FPGA_LAYER2 %x\n", "FpgaLayer2On", layer2_tmp_2);
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407CF8) --------------------------------------------------------
void FpgaLayer2Off(void)
{
  vu16 r_fpga_layer2; // $a2
  vu16 layer2_tmp_1; // $v0
  int layer2_tmp_2; // $a2

  if ( g_xatapi_verbose > 0 )
  {
    r_fpga_layer2 = dev5_fpga_regs.r_fpga_layer2;
    Kprintf("%s():old:FPGA_LAYER2 %x\n", "FpgaLayer2Off", r_fpga_layer2);
  }
  layer2_tmp_1 = dev5_fpga_regs.r_fpga_layer2;
  dev5_fpga_regs.r_fpga_layer2 = layer2_tmp_1 & 0xFFFE;
  if ( g_xatapi_verbose > 0 )
  {
    layer2_tmp_2 = dev5_fpga_regs.r_fpga_layer2;
    Kprintf("%s():new:FPGA_LAYER2 %x\n", "FpgaLayer2Off", layer2_tmp_2);
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407D88) --------------------------------------------------------
void FpgaXfrenOn(void)
{
  vu16 r_fpga_xfren; // $a2
  vu16 xfren_tmp_1; // $v0
  int xfren_tmp_2; // $a2

  if ( g_xatapi_verbose > 0 )
  {
    r_fpga_xfren = dev5_fpga_regs.r_fpga_xfren;
    Kprintf("%s():old:FPGA_XFREN %x\n", "FpgaXfrenOn", r_fpga_xfren);
  }
  xfren_tmp_1 = dev5_fpga_regs.r_fpga_xfren;
  dev5_fpga_regs.r_fpga_xfren = xfren_tmp_1 & 0xFFFE;
  dev5_fpga_regs.r_fpga_xfren = (xfren_tmp_1 & 0xFFFE) | 1;
  if ( g_xatapi_verbose > 0 )
  {
    xfren_tmp_2 = dev5_fpga_regs.r_fpga_xfren;
    Kprintf("%s():new:FPGA_XFREN %x\n", "FpgaXfrenOn", xfren_tmp_2);
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407E2C) --------------------------------------------------------
void FpgaXfrenOff(void)
{
  vu16 r_fpga_xfren; // $a2
  vu16 xfren_tmp_1; // $v0
  int xfren_tmp_2; // $a2

  if ( g_xatapi_verbose > 0 )
  {
    r_fpga_xfren = dev5_fpga_regs.r_fpga_xfren;
    Kprintf("%s():old:FPGA_XFREN %x\n", "FpgaXfrenOff", r_fpga_xfren);
  }
  xfren_tmp_1 = dev5_fpga_regs.r_fpga_xfren;
  dev5_fpga_regs.r_fpga_xfren = xfren_tmp_1 & 0xFFFE;
  if ( g_xatapi_verbose > 0 )
  {
    xfren_tmp_2 = dev5_fpga_regs.r_fpga_xfren;
    Kprintf("%s():new:FPGA_XFREN %x\n", "FpgaXfrenOff", xfren_tmp_2);
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407EBC) --------------------------------------------------------
void FpgaSpckmodeOn(void)
{
  vu16 r_fpga_unk32; // $a2
  vu16 spckmode_tmp_1; // $v0
  int spckmode_tmp_2; // $a2

  if ( g_xatapi_verbose > 0 )
  {
    r_fpga_unk32 = dev5_fpga_regs.r_fpga_unk32;
    Kprintf("%s():old:FPGA_SPCKMODE %x\n", "FpgaSpckmodeOn", r_fpga_unk32);
  }
  spckmode_tmp_1 = dev5_fpga_regs.r_fpga_unk32;
  dev5_fpga_regs.r_fpga_unk32 = spckmode_tmp_1 & 0xFFFE;
  dev5_fpga_regs.r_fpga_unk32 = (spckmode_tmp_1 & 0xFFFE) | 1;
  if ( g_xatapi_verbose > 0 )
  {
    spckmode_tmp_2 = dev5_fpga_regs.r_fpga_unk32;
    Kprintf("%s():new:FPGA_SPCKMODE %x\n", "FpgaSpckmodeOn", spckmode_tmp_2);
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407F60) --------------------------------------------------------
void FpgaSpckmodeOff(void)
{
  vu16 r_fpga_unk32; // $a2
  vu16 spckmode_tmp_1; // $v0
  int spckmode_tmp_2; // $a2

  if ( g_xatapi_verbose > 0 )
  {
    r_fpga_unk32 = dev5_fpga_regs.r_fpga_unk32;
    Kprintf("%s():old:FPGA_SPCKMODE %x\n", "FpgaSpckmodeOff", r_fpga_unk32);
  }
  spckmode_tmp_1 = dev5_fpga_regs.r_fpga_unk32;
  dev5_fpga_regs.r_fpga_unk32 = spckmode_tmp_1 & 0xFFFE;
  if ( g_xatapi_verbose > 0 )
  {
    spckmode_tmp_2 = dev5_fpga_regs.r_fpga_unk32;
    Kprintf("%s():new:FPGA_SPCKMODE %x\n", "FpgaSpckmodeOff", spckmode_tmp_2);
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407FF0) --------------------------------------------------------
void FpgaXfdir(int dir)
{
  vu16 r_fpga_xfrdir; // $a2
  vu16 xfrdir_tmp_1; // $v1
  vu16 xfrdir_tmp_2; // $v0
  vu16 xfrdir_tmp_3; // $a2

  if ( g_xatapi_verbose > 0 )
  {
    r_fpga_xfrdir = dev5_fpga_regs.r_fpga_xfrdir;
    Kprintf("%s():old:FPGA_XFRDIR %x\n", "FpgaXfrdir", r_fpga_xfrdir);
  }
  if ( dir )
  {
    xfrdir_tmp_1 = dev5_fpga_regs.r_fpga_xfrdir;
    dev5_fpga_regs.r_fpga_xfrdir = xfrdir_tmp_1 & 0xFFFE;
    dev5_fpga_regs.r_fpga_xfrdir = (xfrdir_tmp_1 & 0xFFFE) | 1;
  }
  else
  {
    xfrdir_tmp_2 = dev5_fpga_regs.r_fpga_xfrdir;
    dev5_fpga_regs.r_fpga_xfrdir = xfrdir_tmp_2 & 0xFFFE;
  }
  if ( g_xatapi_verbose > 0 )
  {
    xfrdir_tmp_3 = dev5_fpga_regs.r_fpga_xfrdir;
    Kprintf("%s():new:FPGA_XFRDIR %x\n", "FpgaXfrdir", xfrdir_tmp_3);
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004080CC) --------------------------------------------------------
int FpgaGetRevision(void)
{
  vu16 r_fpga_revision; // $a2

  if ( g_xatapi_verbose > 0 )
  {
    r_fpga_revision = dev5_fpga_regs.r_fpga_revision;
    Kprintf("%s():FPGA_REVISION %x\n", "FpgaGetRevision", r_fpga_revision);
  }
  return (u16)dev5_fpga_regs.r_fpga_revision;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00408120) --------------------------------------------------------
unsigned int do_fpga_add_unused8120(void)
{
  vu16 r_fpga_exbufd; // $v1
  vu16 r_fpga_sl3bufd; // $v0

  r_fpga_exbufd = dev5_fpga_regs.r_fpga_exbufd;
  r_fpga_sl3bufd = dev5_fpga_regs.r_fpga_sl3bufd;
  return (r_fpga_sl3bufd + (unsigned int)r_fpga_exbufd) >> 7;
}

//----- (00408148) --------------------------------------------------------
int do_fpga_check_unk8148(void)
{
  return (u16)dev5_fpga_regs.r_fpga_unk34;
}

//----- (0040815C) --------------------------------------------------------
void FpgaCheckWriteBuffer(void)
{
  int i; // $v1
  vu16 r_fpga_sl3bufe; // $v0
  vu16 r_fpga_exbufe; // $a1
  vu16 sl3bufe_tmp1; // $a2

  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():in ...\n", "FpgaCheckWriteBuffer");
  for ( i = 0; i < 10000; i += 1 )
  {
    if ( (u16)(dev5_fpga_regs.r_fpga_exbufe) == 0 )
    {
      r_fpga_sl3bufe = dev5_fpga_regs.r_fpga_sl3bufe;
      if ( r_fpga_sl3bufe == 0 )
        break;
    }
  }
  if ( i == 10000 )
  {
    if ( g_xatapi_verbose < 0 )
      return;
    r_fpga_exbufe = dev5_fpga_regs.r_fpga_exbufe;
    sl3bufe_tmp1 = dev5_fpga_regs.r_fpga_sl3bufe;
    Kprintf("exbuf enc=%x, sl3buf enc=%x\n", r_fpga_exbufe, sl3bufe_tmp1);
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():out ...\n", "FpgaCheckWriteBuffer");
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00408250) --------------------------------------------------------
void FpgaCheckWriteBuffer2(void)
{
  int r_fpga_sl3bufd; // $a2
  int r_fpga_sl3bufe; // $a2
  int r_fpga_exbufd; // $a2
  int r_fpga_exbufe; // $a2

  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():in ...\n", "FpgaCheckWriteBuffer2");
  while ( dev5_fpga_regs.r_fpga_sl3bufd )
  {
    if ( g_xatapi_verbose > 0 )
    {
      r_fpga_sl3bufd = dev5_fpga_regs.r_fpga_sl3bufd;
      Kprintf("%s():FPGA_SL3BUFD %x\n", "FpgaCheckWriteBuffer2", r_fpga_sl3bufd);
      if ( g_xatapi_verbose > 0 )
      {
        r_fpga_sl3bufe = dev5_fpga_regs.r_fpga_sl3bufe;
        Kprintf("%s():FPGA_SL3BUFE %x\n", "FpgaCheckWriteBuffer2", r_fpga_sl3bufe);
        if ( g_xatapi_verbose > 0 )
        {
          r_fpga_exbufd = dev5_fpga_regs.r_fpga_exbufd;
          Kprintf("%s():FPGA_EXBUFD %x\n", "FpgaCheckWriteBuffer2", r_fpga_exbufd);
          if ( g_xatapi_verbose > 0 )
          {
            r_fpga_exbufe = dev5_fpga_regs.r_fpga_exbufe;
            Kprintf("%s():FPGA_EXBUFE %x\n", "FpgaCheckWriteBuffer2", r_fpga_exbufe);
          }
        }
      }
    }
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():out ...\n", "FpgaCheckWriteBuffer2");
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004083C8) --------------------------------------------------------
void FpgaClearBuffer(void)
{
  vu16 r_fpga_sl3bufd; // $a2
  vu16 r_fpga_sl3bufe; // $a2
  vu16 r_fpga_exbufd; // $a2
  vu16 r_fpga_exbufe; // $a2
  vu16 r_fpga_unk30; // $v0
  vu16 unk30_tmp_1; // $v1
  vu16 sl3bufd_tmp2; // $a2
  vu16 sl3bufe_tmp1; // $a2
  vu16 exbufd_tmp; // $a2
  vu16 efbufe_tmp; // $a2

  if ( g_xatapi_verbose > 0 )
  {
    r_fpga_sl3bufd = dev5_fpga_regs.r_fpga_sl3bufd;
    Kprintf("%s():old:FPGA_SL3BUFD %x\n", "FpgaClearBuffer", r_fpga_sl3bufd);
  }
  if ( g_xatapi_verbose > 0 )
  {
    r_fpga_sl3bufe = dev5_fpga_regs.r_fpga_sl3bufe;
    Kprintf("%s():old:FPGA_SL3BUFE %x\n", "FpgaClearBuffer", r_fpga_sl3bufe);
    if ( g_xatapi_verbose > 0 )
    {
      r_fpga_exbufd = dev5_fpga_regs.r_fpga_exbufd;
      Kprintf("%s():old:FPGA_EXBUFD %x\n", "FpgaClearBuffer", r_fpga_exbufd);
      if ( g_xatapi_verbose > 0 )
      {
        r_fpga_exbufe = dev5_fpga_regs.r_fpga_exbufe;
        Kprintf("%s():old:FPGA_EXBUFE %x\n", "FpgaClearBuffer", r_fpga_exbufe);
      }
    }
  }
  r_fpga_unk30 = dev5_fpga_regs.r_fpga_unk30;
  dev5_fpga_regs.r_fpga_unk30 = r_fpga_unk30 & 0xFFFE;
  dev5_fpga_regs.r_fpga_unk30 = (r_fpga_unk30 & 0xFFFE) | 1;
  while ( (u16)(dev5_fpga_regs.r_fpga_exbufd) || dev5_fpga_regs.r_fpga_sl3bufd );
  while ( dev5_fpga_regs.r_fpga_exbufe || dev5_fpga_regs.r_fpga_sl3bufe );
  unk30_tmp_1 = dev5_fpga_regs.r_fpga_unk30;
  dev5_fpga_regs.r_fpga_unk30 = unk30_tmp_1 & 0xFFFE;
  if ( g_xatapi_verbose > 0 )
  {
    sl3bufd_tmp2 = dev5_fpga_regs.r_fpga_sl3bufd;
    Kprintf("%s():new:FPGA_SL3BUFD %x\n", "FpgaClearBuffer", sl3bufd_tmp2);
    if ( g_xatapi_verbose > 0 )
    {
      sl3bufe_tmp1 = dev5_fpga_regs.r_fpga_sl3bufe;
      Kprintf("%s():new:FPGA_SL3BUFE %x\n", "FpgaClearBuffer", sl3bufe_tmp1);
      if ( g_xatapi_verbose > 0 )
      {
        exbufd_tmp = dev5_fpga_regs.r_fpga_exbufd;
        Kprintf("%s():new:FPGA_EXBUFD %x\n", "FpgaClearBuffer", exbufd_tmp);
        if ( g_xatapi_verbose > 0 )
        {
          efbufe_tmp = dev5_fpga_regs.r_fpga_exbufe;
          Kprintf("%s():new:FPGA_EXBUFE %x\n", "FpgaClearBuffer", efbufe_tmp);
        }
      }
    }
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00408600) --------------------------------------------------------
int Mpeg2CheckPadding(char *buf, unsigned int bufsize, int *retptr, int *pesscramblingpackptr)
{
  int bufchk; // $s0
  signed int buf_2048units; // $a1
  char *bufoffs1; // $a0
  char *bufoffs2; // $v1
  int bufcuri; // $v0
  const char *strtmp; // $a3

  bufchk = 0;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():in\n", "Mpeg2CheckPadding");
  if ( (bufsize & 0x7FF) != 0 )
  {
    if ( g_xatapi_verbose > 0 )
    {
      Kprintf("%s():Buffer size not aligne !!\n", "Mpeg2CheckPadding");
    }
    return -1;
  }
  else
  {
    buf_2048units = bufsize >> 11;
    if ( !*buf && !buf[1] && buf[2] == 1 && (u8)buf[3] == 0xBA )
      bufchk = 1;
    for ( bufcuri = 0; bufcuri < buf_2048units; bufcuri += 1 )
    {
      bufoffs1 = &buf[2048 * bufcuri];
      if ( *bufoffs1 || bufoffs1[1] || bufoffs1[2] != 1 || (u8)bufoffs1[3] != 0xBA )
      {
        if ( bufchk )
          break;
      }
      else
      {
        if ( !bufchk )
          break;
        bufoffs2 = bufoffs1 + 14;
        if ( !bufoffs1[14] )
        {
          if ( !bufoffs1[15] && bufoffs1[16] == 1 && (u8)bufoffs1[17] == 0xBB )
            bufoffs2 = bufoffs1 + 38;
          if ( !*bufoffs2
            && !bufoffs2[1]
            && bufoffs2[2] == 1
            && (u8)bufoffs2[3] != 0xBF
            && (bufoffs2[6] & 0x60) != 0 )
          {
            ++*pesscramblingpackptr;
          }
        }
      }
    }
    if ( g_xatapi_verbose > 0 )
    {
      strtmp = "NULL";
      if ( bufchk )
        strtmp = "RDI";
      Kprintf("%s():out %d %s Pack\n", "Mpeg2CheckPadding", bufcuri, strtmp);
    }
    *retptr = bufcuri;
    return bufchk;
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00408884) --------------------------------------------------------
int Mpeg2CheckScramble(char *buf, unsigned int bufsize)
{
  int restmp; // $s1
  signed int bufi; // $a2
  char *bufcur; // $a0
  char *bufbuf; // $v1
  int buf3; // $v0

  restmp = 0;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():in\n", "Mpeg2CheckScramble");
  if ( (bufsize & 0x7FF) != 0 )
  {
    if ( g_xatapi_verbose > 0 )
    {
      Kprintf("%s():Buffer size not aligne !!\n", "Mpeg2CheckScramble");
    }
    return 0;
  }
  else
  {
    bufcur = buf;
    for ( bufi = 0; bufi < (int)(bufsize >> 11); bufi += 1 )
    {
      if ( !*bufcur && !bufcur[1] && bufcur[2] == 1 && (u8)bufcur[3] == 0xBA )
      {
        bufbuf = bufcur + 14;
        if ( !bufcur[14] )
        {
          if ( !bufcur[15] && bufcur[16] == 1 && (u8)bufcur[17] == 0xBB )
            bufbuf = bufcur + 38;
          if ( !*bufbuf && !bufbuf[1] && bufbuf[2] == 1 )
          {
            buf3 = (u8)bufbuf[3];
            if ( (buf3 == 0xE0 || buf3 == 0xBD || buf3 == 0xC0 || buf3 == 0xD0) && (bufbuf[6] & 0x30) != 0 )
            {
              restmp = 0xFFFFFFFF;
              break;
            }
          }
        }
      }
      bufcur += 2048;
    }
    if ( g_xatapi_verbose > 0 )
    {
      Kprintf("%s():out\n", "Mpeg2CheckScramble");
    }
    return restmp;
  }
}
// 40A648: using guessed type int g_xatapi_verbose;
