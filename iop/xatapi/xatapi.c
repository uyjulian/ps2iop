
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
int xatapi_dev_devctl(const iop_file_t *f, const char *name, int cmd, void *args, unsigned int arglen, void *buf, unsigned int buflen);
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
void (*g_dev5_intr_cbs[16])(int);
void (*g_dev5_predma_cbs[4])(u32, int);
void (*g_dev5_postdma_cbs[4])(u32, int);
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
  int i; // $s1
  int retres; // $s0
  char pkt[12]; // [sp+20h] [-80h] BYREF
  char outbuf[56]; // [sp+40h] [-60h] BYREF

  retres = 1;
  for ( i = 0; retres && i < 16; i += 1 )
  {
    memset(pkt, 0, sizeof(pkt));
    pkt[0] = 0x12;
    pkt[4] = 0x38;
    retres = sceCdAtapiExecCmd_local(dev_nr, outbuf, 1, sizeof(outbuf), pkt, sizeof(pkt), 2);
    if ( retres )
      continue;
    retres = sceCdAtapiWaitResult_local();
    if ( retres )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive ATAPI_CMD_READ_EXT_INFO  NG\n");
      DelayThread(10000);
    }
  }
  if ( retres )
    return retres;
  do_hex_dump(outbuf, sizeof(outbuf));
  return strncmp(&outbuf[32], "BOOT", 4) ? 1 : 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (0040013C) --------------------------------------------------------
int do_atapi_request_test_unit_ready(s16 dev_nr, int *errptr, int *ctrlptr)
{
  int retres; // $s0
  char pkt[12]; // [sp+20h] [-10h] BYREF

  *errptr = 0;
  *ctrlptr = 0;
  memset(pkt, 0, sizeof(pkt));
  pkt[0] = 0;
  retres = xatapi_7_sceCdAtapiExecCmd(dev_nr, 0, 0, 0, pkt, sizeof(pkt), 1);
  if ( retres )
    return retres;
  retres = xatapi_8_sceCdAtapiWaitResult();
  *errptr = (u8)xatapi_11_sceAtaGetError();
  *ctrlptr = (u8)xatapi_12_get_ata_control();
  return retres;
}

//----- (004001F0) --------------------------------------------------------
int atapi_req_sense_get(s16 dev_nr, int *retptr)
{
  int result; // $v0
  char pkt[12]; // [sp+20h] [-50h] BYREF
  char outbuf[18]; // [sp+30h] [-40h] BYREF

  *retptr = 0;
  memset(pkt, 0, sizeof(pkt));
  pkt[0] = 3;
  pkt[4] = sizeof(outbuf);
  result = xatapi_7_sceCdAtapiExecCmd(dev_nr, outbuf, 1, sizeof(outbuf), pkt, sizeof(pkt), 2);
  if ( result )
    return result;
  result = xatapi_8_sceCdAtapiWaitResult();
  if ( result )
    return result;
  *retptr = ((outbuf[2] & 0xF) << 16) | ((u8)outbuf[12] << 8) | (u8)outbuf[13];
  return 0;
}

//----- (004002AC) --------------------------------------------------------
int atapi_exec_cmd_request_sense_03h_unused(s16 dev_nr, int *retptr)
{
  int result; // $v0
  char pkt[12]; // [sp+20h] [-50h] BYREF
  char outbuf[18]; // [sp+30h] [-40h] BYREF

  *retptr = 0;
  memset(pkt, 0, sizeof(pkt));
  pkt[0] = 3;
  pkt[4] = sizeof(outbuf);
  result = sceCdAtapiExecCmd_local(dev_nr, outbuf, 1, sizeof(outbuf), pkt, sizeof(pkt), 2);
  if ( result )
    return result;
  result = sceCdAtapiWaitResult_local();
  if ( result )
    return result;
  *retptr = ((outbuf[2] & 0xF) << 16) | ((u8)outbuf[12] << 8) | (u8)outbuf[13];
  return 0;
}

//----- (00400368) --------------------------------------------------------
int do_start_stop_unit_1bh_unused(void)
{
  int i; // $s1
  int retres; // $s0
  char pkt[12]; // [sp+20h] [-10h] BYREF

  retres = 1;
  for ( i = 0; i < 16 && retres && retres != -550; i += 1 )
  {
    memset(pkt, 0, sizeof(pkt));
    pkt[0] = 0x1B;
    pkt[4] = 2;
    pkt[5] = 0;
    retres = sceCdAtapiExecCmd_local(0, 0, 0, 0, pkt, sizeof(pkt), 1);
    if ( retres )
      continue;
    retres = sceCdAtapiWaitResult_local();
    if ( retres )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive EJECT NG\n");
      DelayThread(10000);
      continue;
    }
    if ( g_xatapi_verbose > 0 )
      Kprintf("Atapi Drive EJECT OK\n");
  }
  if ( !retres )
  {
    retres = 1;
    for ( i = 0; i < 16 && retres && retres != -550; i += 1 )
    {
      memset(pkt, 0, sizeof(pkt));
      pkt[0] = 0x1B;
      pkt[4] = 3;
      pkt[5] = 0;
      retres = sceCdAtapiExecCmd_local(0, 0, 0, 0, pkt, sizeof(pkt), 1);
      if ( retres )
        continue;
      retres = sceCdAtapiWaitResult_local();
      if ( retres )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("Atapi Drive Spindle  Start  NG %d\n", i);
        DelayThread(10000);
        continue;
      }
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive Spindle  Start  OK\n");
    }
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("  PS2 Eject On Atapi Unit Dummy Eject Ret %d\n", retres);
  return retres;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004005C8) --------------------------------------------------------
int chgsys_callback_cb(int *mediaptr, int want_atapi)
{
  int i; // $s1
  int tryres1; // $s0
  int retres; // $s0
  char pkt[12]; // [sp+20h] [-20h] BYREF
  char outbuf1[6]; // [sp+30h] [-10h] BYREF

  *mediaptr = 4;
  if ( want_atapi )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("Ps2 Drive Spindle -> Atapi \n");
    retres = 1;
    for ( i = 0; i < 10 && retres && retres != -550; i += 1 )
    {
      memset(pkt, 0, sizeof(pkt));
      pkt[0] = 0x1B;
      pkt[4] = 3;
      pkt[5] = 0;
      retres = sceCdAtapiExecCmd(0, 0, 0, 0, pkt, sizeof(pkt), 1);
      if ( retres )
        continue;
      retres = sceCdAtapiWaitResult_local();
      if ( retres )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("Atapi Drive Spindle Start NG %d\n", i);
        DelayThread(10000);
        continue;
      }
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive Spindle Start OK\n");
    }
    return retres;
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("Atapi Drive Spindle -> Ps2\n");
  tryres1 = 1;
  for ( i = 0; i < 16 && tryres1 && tryres1 != -550; i += 1 )
  {
    memset(pkt, 0, sizeof(pkt));
    pkt[0] = 0xF6;
    pkt[2] = 0xA0;
    pkt[8] = 6;
    tryres1 = sceCdAtapiExecCmd_local(0, outbuf1, 1, sizeof(outbuf1), pkt, sizeof(pkt), 2);
    if ( tryres1 )
      continue;
    tryres1 = sceCdAtapiWaitResult_local();
    if ( tryres1 )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive ATAPI_CMD_READ_EXT_INFO  NG\n");
      DelayThread(10000);
    }
  }
  if ( !tryres1 )
  {
    int maskchk; // $s0

    maskchk = (((u8)outbuf1[5] >> 1) ^ 1) & 1;
    if ( (outbuf1[3] & 0x10) )
    {
      char outbuf[8]; // [sp+30h] [-10h] BYREF

      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive Media found.\n");
      memset(pkt, 0, sizeof(pkt));
      pkt[0] = 0xF6;
      pkt[2] = 0xA2;
      pkt[8] = sizeof(outbuf);
      if ( !sceCdAtapiExecCmd_local(0, outbuf, 1, sizeof(outbuf), pkt, sizeof(pkt), 2) && !sceCdAtapiWaitResult_local() )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("Atapi Drive Media DVD:%d.\n", outbuf[5] & 0x20);
        *mediaptr = (outbuf[5] & 0x20) ? 3 : 2;
      }
    }
    else
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive No Media or Now checking.\n");
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive No Media or No SpinUp.\n");
      *mediaptr = 4;
    }
    if ( maskchk )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive Spin Up.\n");
      retres = 1;
      for ( i = 0; i < 16 && retres && retres != -550; i += 1 )
      {
        memset(pkt, 0, sizeof(pkt));
        pkt[0] = 0x1B;
        pkt[5] = 0;
        retres = sceCdAtapiExecCmd(0, 0, 0, 0, pkt, sizeof(pkt), 1);
        if ( retres )
          continue;
        retres = sceCdAtapiWaitResult_local();
        if ( retres )
        {
          if ( g_xatapi_verbose > 0 )
            Kprintf("Atapi Drive Spindle  Stop  NG\n");
          DelayThread(10000);
          continue;
        }
        if ( g_xatapi_verbose > 0 )
          Kprintf("Atapi Drive Spindle  Stop  OK\n");
      }
      return retres;
    }
    if ( g_xatapi_verbose > 0 )
      Kprintf("Atapi Drive Not Spin Up.\n");
    retres = 1;
    for ( i = 0; i < 16 && retres && retres != -550; i += 1 )
    {
      memset(pkt, 0, sizeof(pkt));
      pkt[0] = 0x1B;
      pkt[4] = 2;
      pkt[5] = 0;
      retres = sceCdAtapiExecCmd(0, 0, 0, 0, pkt, sizeof(pkt), 1);
      if ( retres )
        continue;
      retres = sceCdAtapiWaitResult_local();
      if ( retres )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("Atapi Drive EJECT NG\n");
        DelayThread(10000);
        continue;
      }
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive EJECT OK\n");
      *mediaptr = 256;
    }
    return retres;
  }
  return tryres1;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00400BB4) --------------------------------------------------------
int sceCdAtapi_SC(void)
{
  int i; // $s1
  int retres; // $s0
  char pkt[12]; // [sp+20h] [-10h] BYREF

  memset(pkt, 0, sizeof(pkt));
  retres = 1;
  pkt[0] = 0xF9;
  pkt[2] = 0xB1;
  pkt[8] = 0;
  for ( i = 0; i < 10 && retres; i += 1 )
  {
    retres = sceCdAtapiExecCmd_local(0, 0, 0, 0, pkt, sizeof(pkt), 1);
    if ( retres || (retres = sceCdAtapiWaitResult_local()) )
      DelayThread(10000);
  }
  if ( retres )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceCdAtapi SC fail\n");
    return retres;
  }
  *g_cd_sc_ffffffd9_ptr = 0;
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdAtapi SC OK\n");
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00400CEC) --------------------------------------------------------
int xatapi_15_exec_f6_f9_scsi(void)
{
  int i; // $s1
  int retres1; // $s0
  int retres2; // $s0
  char pkt[12]; // [sp+20h] [-30h] BYREF
  char outbuf[6]; // [sp+30h] [-20h] BYREF

  memset(pkt, 0, sizeof(pkt));
  retres1 = 1;
  pkt[0] = 0xF6;
  pkt[2] = 0xB1;
  pkt[8] = 6;
  for ( i = 0; i < 4 && retres1; i += 1 )
  {
    retres1 = sceCdAtapiExecCmd_local(0, outbuf, 1, sizeof(outbuf), pkt, sizeof(pkt), 2);
    if ( retres1 || (retres1 = sceCdAtapiWaitResult_local()) )
      DelayThread(10000);
  }
  if ( retres1 && !(outbuf[4] & 0x80) )
    return retres1;
  memset(pkt, 0, sizeof(pkt));
  retres2 = 1;
  pkt[0] = 0xF9;
  pkt[2] = 0xB2;
  pkt[8] = 0;
  for ( i = 0; i < 10 && retres2; i += 1 )
  {
    retres2 = sceCdAtapiExecCmd_local(0, 0, 0, 0, pkt, sizeof(pkt), 1);
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
  int i; // $s1
  int retres1; // $s0
  int retres2; // $s0
  int retres3; // $s0
  int retres4; // $s0
  int retres5; // $s0
  char pkt[12]; // [sp+20h] [-58h] BYREF
  iop_event_info_t efinfo; // [sp+50h] [-28h] BYREF
  u32 waresontmp; // [sp+70h] [-8h] BYREF
  u32 efbits; // [sp+74h] [-4h] BYREF
  int flg;
  char outbuf1[6];
  {
    memset(pkt, 0, sizeof(pkt));
    retres1 = 1;
    pkt[0] = 0xF6;
    pkt[2] = 0xB1;
    pkt[8] = sizeof(outbuf1);
    for ( i = 0; i < 10 && retres1; i += 1 )
    {
      retres1 = sceCdAtapiExecCmd_local(0, outbuf1, 1, sizeof(outbuf1), pkt, sizeof(pkt), 2);
      if ( retres1 || (retres1 = sceCdAtapiWaitResult_local()) )
        DelayThread(10000);
    }
  }
  if ( !retres1 || (outbuf1[4] & 0x80) )
  {
    memset(pkt, 0, sizeof(pkt));
    retres2 = 1;
    pkt[0] = 0xF9;
    pkt[2] = 0xB2;
    pkt[8] = 0;
    for ( i = 0; i < 10 && retres2; i += 1 )
    {
      retres2 = sceCdAtapiExecCmd_local(0, 0, 0, 0, pkt, sizeof(pkt), 1);
      if ( !retres2 )
      {
        retres2 = sceCdAtapiWaitResult_local();
        if ( !retres2 )
          continue;
      }
      DelayThread(10000);
    }
  }
  {
    char outbuf[6];

    memset(pkt, 0, sizeof(pkt));
    retres3 = 1;
    pkt[0] = 0xF6;
    pkt[2] = 0xB1;
    pkt[8] = sizeof(outbuf);
    for ( i = 0; i < 10 && retres3; i += 1 )
    {
      retres3 = sceCdAtapiExecCmd_local(0, outbuf, 1, sizeof(outbuf), pkt, sizeof(pkt), 2);
      if ( retres3 || (retres3 = sceCdAtapiWaitResult_local()) )
        DelayThread(10000);
    }
    if ( !retres3 && (outbuf[4] & 0x81) )
    {
      *g_cd_sc_ffffffd9_ptr = 1;
      return 1;
    }
  }
  {
    char outbuf[16];

    memset(pkt, 0, sizeof(pkt));
    retres4 = 1;
    pkt[0] = 0xF6;
    pkt[2] = 0xB0;
    pkt[8] = sizeof(outbuf);
    for ( i = 0; i < 10 && retres4; i += 1 )
    {
      retres4 = sceCdAtapiExecCmd_local(0, outbuf, 1, sizeof(outbuf), pkt, sizeof(pkt), 2);
      if ( retres4 || (retres4 = sceCdAtapiWaitResult_local()) )
        DelayThread(10000);
    }
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
    for ( i = 0; i < 100 && !retres4; i += 1 )
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
      for ( i = 0; i < 100 && !retres4; i += 1 )
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
        char outbuf[16];

        if ( g_should_wait_for_dma_flag )
          WaitEventFlag(g_adma_evfid, 1u, 16, &efbits);
        retres4 = 1;
        WaitEventFlag(g_acmd_evfid, 1u, 16, &efbits);
        memset(pkt, 0, sizeof(pkt));
        pkt[0] = 0xF9;
        pkt[2] = 0xB0;
        pkt[8] = sizeof(outbuf);
        for ( i = 0; i < 10 && retres4; i += 1 )
        {
          retres4 = sceCdAtapiExecCmd_local(0, outbuf, 1, sizeof(outbuf), pkt, sizeof(pkt), 3);
          if ( retres4 || (retres4 = sceCdAtapiWaitResult_local()) )
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
  {
    char outbuf[6];

    memset(pkt, 0, sizeof(pkt));
    retres5 = 1;
    pkt[0] = 0xF6;
    pkt[2] = 0xB1;
    pkt[8] = sizeof(outbuf);
    for ( i = 0; i < 10 && retres5; i += 1 )
    {
      retres5 = sceCdAtapiExecCmd_local(0, outbuf, 1, sizeof(outbuf), pkt, sizeof(pkt), 2);
      if ( retres5 || (retres5 = sceCdAtapiWaitResult_local()) )
        DelayThread(10000);
    }
    if ( retres5 )
      return retres4;
    *g_cd_sc_ffffffd9_ptr = (outbuf[4] & 0x81) ? 1 : 0;
  }
  return retres4;
}
// 40A640: using guessed type int g_should_wait_for_dma_flag;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00401514) --------------------------------------------------------
int atapi_spin_status_get(int unused_arg1, void *buf)
{
  int result; // $v0
  char pkt[12]; // [sp+20h] [-10h] BYREF

  (void)unused_arg1;
  memset(pkt, 0, sizeof(pkt));
  pkt[0] = 0xF6;
  pkt[2] = 0xA0;
  pkt[8] = 6;
  result = xatapi_7_sceCdAtapiExecCmd(0, buf, 1, 6, pkt, sizeof(pkt), 2);
  return ( !result ) ? xatapi_8_sceCdAtapiWaitResult() : result;
}

//----- (00401598) --------------------------------------------------------
int atapi_check_if_drive_ready(int check_nowait)
{
  u8 ata_control; // $v0
  int drive_err; // [sp+18h] [-10h] BYREF
  int unitreadyctrl; // [sp+1Ch] [-Ch] BYREF
  int senseret; // [sp+20h] [-8h] BYREF

  drive_err = 0;
  if ( g_xatapi_verbose > 0 )
    Kprintf("Atapi Drive Ready Call %d\n", check_nowait);
  ata_control = xatapi_12_get_ata_control();
  if ( g_xatapi_verbose > 0 )
    Kprintf("Atapi Drive Ready %04x\n", ata_control);
  if ( !check_nowait )
  {
    int req_test_unit_ready_tmp1; // $s1

    req_test_unit_ready_tmp1 = -1;
    while ( req_test_unit_ready_tmp1 < 0 )
    {
      char spinstatus_tmp[6]; // [sp+10h] [-18h] BYREF

      while ( (ata_control & 0xC0) != 64 )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("Drive Not Ready %04x\n", ata_control);
        DelayThread(2000);
        ata_control = xatapi_12_get_ata_control();
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
        if ( (spinstatus_tmp[3] & 2) || (spinstatus_tmp[3] & 0x80) )
          break;
      }
      if ( g_xatapi_verbose > 0 )
        Kprintf("Atapi Drive err %08x\n", drive_err);
    }
    return 2;
  }
  return ( (ata_control & 0xC0) == 64 && do_atapi_request_test_unit_ready(0, &drive_err, &unitreadyctrl) >= 0 && !drive_err ) ? 2 : 6;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004017A8) --------------------------------------------------------
int sceFsDevctlBlkIO(s16 dev_nr, void *buf, void *rwbuf, unsigned int nsec, int secsize, int rwtype)
{
  char *rwbuf_tmp; // $s3
  unsigned int nsec_tmp; // $s4
  int retres1; // $s0
  int seccnt; // $s1
  int i; // $s2
  char pkt[12]; // [sp+20h] [-18h] BYREF

  rwbuf_tmp = (char *)rwbuf;
  retres1 = 0;
  if ( g_xatapi_verbose > 0 )
    Kprintf("dma %c %08x, nsec %d\n", rwtype ? 'w' : 'r', rwbuf, nsec);
  for ( nsec_tmp = nsec; !retres1 && nsec_tmp; nsec_tmp -= seccnt )
  {
    seccnt = ( nsec_tmp >= 0x21 ) ? 32 : nsec_tmp;
    for ( i = 3; i < 3; i += 1 )
    {
      xatapi_9_sceCdSpdAtaDmaStart(rwtype);
      memset(pkt, 0, sizeof(pkt));
      pkt[0] = ( !rwtype ) ? 0x28 : 0x2A;
      pkt[2] = ((uiptr)rwbuf_tmp >> 24) & 0xFF;
      pkt[3] = ((uiptr)rwbuf_tmp >> 16) & 0xFF;
      pkt[4] = ((uiptr)rwbuf_tmp >> 8) & 0xFF;
      pkt[5] = ((uiptr)rwbuf_tmp) & 0xFF;
      pkt[8] = seccnt;
      retres1 = xatapi_7_sceCdAtapiExecCmd(dev_nr, buf, seccnt, secsize, pkt, sizeof(pkt), 4);
      if ( retres1 )
      {
        xatapi_10_sceCdSpdAtaDmaEnd();
        break;
      }
      retres1 = xatapi_8_sceCdAtapiWaitResult();
      xatapi_10_sceCdSpdAtaDmaEnd();
      if ( retres1 != -510 )
      {
        break;
      }
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
  if ( (*g_dev9_reg_power & 4) )
  {
    Kprintf("xatapi already Power On\n");
    *g_dev9_reg_1460 |= 2u;
    return;
  }
  Kprintf("xatapi Power On Start\n");
  *g_dev9_reg_power = (*g_dev9_reg_power & 0xFFFA) | 4;
  DelayThread(500000);
  *g_dev9_reg_1460 |= 2u;
  *g_dev9_reg_power |= 1u;
  DelayThread(500000);
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
  u32 buzzerres; // [sp+10h] [-8h] BYREF

  (void)unused_arg2;
  if ( is_eject != 1 )
    return 1;
  if ( g_xatapi_verbose > 0 )
    Kprintf("Eject intr : media removal\n");
  return sceCdBuzzerCtl(&buzzerres);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00401B94) --------------------------------------------------------
int xatapi_do_init(void)
{
  int (*oldcb)(int, void *); // $s0
  u32 *sc_tmp; // [sp+10h] [-10h] BYREF
  u32 trylocktmp; // [sp+14h] [-Ch] BYREF
  u32 traylock_ret; // [sp+18h] [-8h] BYREF

  if ( !create_event_flags() )
    return 0;
  sceCdSC(0xFFFFFFD9, (int *)&sc_tmp);
  g_cd_sc_ffffffd9_ptr = sc_tmp;
  sceCdSC(0xFFFFFFD7, (int *)&sc_tmp);
  g_bf40200a_is_set_ptr = (int)sc_tmp;
  oldcb = (int (*)(int, void *))sceCdSetAtapiEjectCallback((int (*)(int, void *))atapi_eject_interrupt_handler, 0);
  if ( !sceCdGetMediumRemoval(&trylocktmp, &traylock_ret) )
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("xatapi:sceCdGetMediumRemoval NG(%x) !!\n", traylock_ret);
    trylocktmp = 0;
  }
  if ( trylocktmp )
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("xatapi:Tray locked !!\n");
  }
  else if ( sceCdSetMediumRemoval(1u, &traylock_ret) )
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("xatapi:Tray lock\n");
  }
  else
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("xatapi:Tray lock NG(%x) !!\n", traylock_ret);
    trylocktmp = 0;
  }
  expbay_device_reset();
  if ( g_xatapi_verbose >= 0 )
    Kprintf("xatapi Dev5->Rainbow\n");
  sceCdChgSys(1u);
  if ( g_xatapi_verbose > 0 )
    Kprintf("xatapi Dev5->Rainbow end\n");
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceDev5Init Call\n");
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
    if ( !sceCdSetMediumRemoval(0, &traylock_ret) )
    {
      if ( g_xatapi_verbose >= 0 )
        Kprintf("xatapi:Tray unlock NG(%x) !!\n", traylock_ret);
      trylocktmp = 0;
    }
    else
    {
      if ( g_xatapi_verbose >= 0 )
        Kprintf("xatapi:Tray unlock\n");
    }
  }
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
  int sc_tmp; // [sp+10h] [-8h] BYREF

  (void)with_quit;
  sc_tmp = 0;
  sceCdSC(0xFFFFFFE1, &sc_tmp);
  sceCdSC(0xFFFFFFE5, &sc_tmp);
  sceCdSC(0xFFFFFFE0, &sc_tmp);
  sceCdSC(0xFFFFFFDF, &sc_tmp);
  sceCdSC(0xFFFFFFE4, &sc_tmp);
  Kprintf("libxatapi_terminate\n");
  return 0;
}

//----- (00401F60) --------------------------------------------------------
int xatapi_dev_devctl(
        const iop_file_t *f,
        const char *name,
        int cmd,
        void *args,
        unsigned int arglen,
        void *buf,
        unsigned int buflen)
{
  int retres1; // $s1
  u32 efbits; // [sp+20h] [-8h] BYREF

  (void)name;
  retres1 = 0;
  if ( g_xatapi_verbose > 0 )
    Kprintf("xatapi devctl: cmd:%08x arg:%d\n", cmd, *(u32 *)args);
  if ( cmd == 0x439B && PollEventFlag(g_io_event_flag, 1u, 0, &efbits) == -421 && *(u32 *)args == 1 )
  {
    *(u32 *)buf = 6;
    return 0;
  }
  WaitEventFlag(g_io_event_flag, 1u, 16, &efbits);
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
            retres1 = xatapi_7_sceCdAtapiExecCmd(f->unit, buf, 1, buflen, (char *)args + 8, *(u32 *)args, *((u32 *)args + 1));
            break;
          case 3:
          case 6:
            if ( *((u32 *)args + 250) )
            {
              retres1 = xatapi_7_sceCdAtapiExecCmd(f->unit, (char *)args + 40, 1, *((u32 *)args + 250), (char *)args + 8, *(u32 *)args, *((u32 *)args + 1));
            }
            else
            {
              retres1 = -22;
            }
            break;
          default:
            retres1 = xatapi_7_sceCdAtapiExecCmd(f->unit, 0, 0, 0, (char *)args + 8, *(u32 *)args, *((u32 *)args + 1));
            break;
        }
        if ( !retres1 )
          retres1 = xatapi_8_sceCdAtapiWaitResult();
      }
      break;
    case 0x4333:
      *(u32 *)buf = (u8)xatapi_11_sceAtaGetError();
      break;
    case 0x4334:
      *(u32 *)buf = (u8)xatapi_12_get_ata_control();
      break;
    case 0x4335:
      retres1 = sceCdAtapi_BC();
      if ( retres1 == 1 )
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
      else
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("pes scrambling control pack = %d\n", g_pes_scrambling_control_pack);
      }
      break;
    case 0x4339:
      DmaRun_spck((char *)args, arglen);
      break;
    case 0x433A:
      g_dma_mode_value = (*(u32 *)args & 0x40) ? 1 : 0;
      g_dma_speed_value = *(u32 *)args & 7;
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
      if ( *((u32 *)args + 3) != 2048 )
      {
        retres1 = -22;
        break;
      }
      if ( g_xatapi_verbose > 0 )
        Kprintf("sceFsDevctlBlkIO Lsn:%d nsec:%d buffer:%08x Type:%d\n", *(u32 *)args, *((u32 *)args + 1), *((u32 *)args + 2), *((u32 *)args + 4));
      retres1 = sceFsDevctlBlkIO(f->unit, *((void **)args + 2), *(void **)args, *((u32 *)args + 1), 2048, *((u32 *)args + 4));
      break;
    default:
      Kprintf("Un-support devctl %08x\n", cmd);
      retres1 = -5;
      break;
  }
  SetEventFlag(g_io_event_flag, 1u);
  if ( g_xatapi_verbose > 0 )
    Kprintf("xatapi devctl: cmd:%08x End.\n", cmd);
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
  if ( RegisterLibraryEntries(&_exp_xatapi) )
    return 1;
  DelDrv("xatapi");
  if ( AddDrv(&ata_ioman_device) )
  {
    xatapi_dev_deinit();
    return 1;
  }
  return !xatapi_do_init();
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
  int i; // $s2
  int j; // $s0

  if ( flag == 1 )
  {
    AtaEjectIntrHandle();
    return 0;
  }
  if ( (dev5_speed_regs.r_spd_intr_stat & 0x3EFC) )
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("SL3 register access failed(%x:%x) !!\n", dev5_speed_regs.r_spd_intr_stat, dev5_speed_regs.r_spd_intr_mask);
    return 0;
  }
  for ( i = 0; i < 3 && (u16)(dev5_speed_regs.r_spd_intr_stat & dev5_speed_regs.r_spd_intr_mask); i += 1 )
  {
    for ( j = 0; j < 16; j += 1 )
    {
      if ( g_dev5_intr_cbs[j] && (((int)(u16)(dev5_speed_regs.r_spd_intr_stat & dev5_speed_regs.r_spd_intr_mask) >> j) & 1) )
        g_dev5_intr_cbs[j](flag);
    }
  }
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00402714) --------------------------------------------------------
void speedIntrEnable(s16 mask)
{
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  dev5_speed_regs.r_spd_intr_mask &= ~mask;
  dev5_speed_regs.r_spd_intr_mask |= mask;
  CpuResumeIntr(state);
}

//----- (00402774) --------------------------------------------------------
void speedIntrDisable(s16 mask)
{
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  dev5_speed_regs.r_spd_intr_mask &= ~mask;
  CpuResumeIntr(state);
}

//----- (004027C4) --------------------------------------------------------
int SpdDmaTransfer(unsigned int device, void *buf, u32 bcr_in, int dir)
{
  int result; // $v0

  dmac_ch_set_chcr(3u, 0);
  dmac_ch_get_chcr(3u);
  if ( device >= 2 && (!g_dev5_predma_cbs[device] || !g_dev5_postdma_cbs[device]) )
    return -1;
  if ( g_xatapi_verbose > 0 )
    Kprintf("Wait Intr\n");
  result = WaitSema(g_dma_lock_sema);
  if ( result < 0 )
    return result;
  dev5_speed_regs.r_spd_dma_ctrl = ( dev5_speed_regs.r_spd_rev_1 >= 0x11u ) ? ((device & 1) | 6) : ((device & 3) | 4);
  if ( g_dev5_predma_cbs[device] )
    g_dev5_predma_cbs[device](bcr_in, dir);
  if ( g_xatapi_verbose > 0 )
    Kprintf("DMA Ch3 Set.\n");
  if ( g_xatapi_verbose > 0 )
    Kprintf("Set MADR3:%08x Set BCR3:%08x\n", buf, bcr_in);
  dmac_ch_set_madr(3u, (u32)buf);
  dmac_ch_set_bcr(3u, bcr_in);
  dmac_ch_set_chcr(3u, dir | 0x41000200);
  dmac_ch_get_chcr(3u);
  if ( g_xatapi_verbose > 0 )
    Kprintf("CHCR3:%08x MADR3:%08x BCR3:%08x\n", dmac_ch_get_chcr(3u), dmac_ch_get_madr(3u), dmac_ch_get_bcr(3u));
  while ( (dmac_ch_get_chcr(3u) & 0x1000000) );
  if ( g_xatapi_verbose > 0 )
    Kprintf("MADR3= %08x\n", dmac_ch_get_madr(3u));
  if ( g_dev5_postdma_cbs[device] )
    g_dev5_postdma_cbs[device](bcr_in, dir);
  if ( g_xatapi_verbose > 0 )
    Kprintf("SpdDmaTransfer End.\n");
  SignalSema(g_dma_lock_sema);
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00402A6C) --------------------------------------------------------
int SpdDmaTransfer_extrans_1(unsigned int device, void *buf, u32 bcr_in, int dir)
{
  int result; // $v0

  dmac_ch_set_chcr(3u, 0);
  dmac_ch_get_chcr(3u);
  if ( device >= 2 && (!g_dev5_predma_cbs[device] || !g_dev5_postdma_cbs[device]) )
    return -1;
  if ( g_xatapi_verbose > 0 )
    Kprintf("Wait Intr\n");
  result = WaitSema(g_dma_lock_sema);
  if ( result < 0 )
    return result;
  dev5_speed_regs.r_spd_dma_ctrl = ( dev5_speed_regs.r_spd_rev_1 >= 0x11u ) ? ((device & 1) | 6) : ((device & 3) | 4);
  if ( g_dev5_predma_cbs[device] )
    g_dev5_predma_cbs[device](bcr_in, dir);
  speedIntrDisable(256);
  FpgaLayer1On();
  FpgaXfrenOn();
  if ( g_xatapi_verbose > 0 )
    Kprintf("DMA Ch3 Set.\n");
  if ( g_xatapi_verbose > 0 )
    Kprintf("Set MADR3:%08x Set BCR3:%08x\n", buf, bcr_in);
  dmac_ch_set_madr(3u, (u32)buf);
  dmac_ch_set_bcr(3u, bcr_in);
  dmac_ch_set_chcr(3u, dir | 0x41000200);
  dmac_ch_get_chcr(3u);
  if ( g_xatapi_verbose > 0 )
    Kprintf("CHCR3:%08x MADR3:%08x BCR3:%08x\n", dmac_ch_get_chcr(3u), dmac_ch_get_madr(3u), dmac_ch_get_bcr(3u));
  while ( (dmac_ch_get_chcr(3u) & 0x1000000) );
  if ( g_xatapi_verbose > 0 )
    Kprintf("MADR3= %08x\n", dmac_ch_get_madr(3u));
  FpgaCheckWriteBuffer();
  FpgaXfrenOff();
  FpgaLayer1Off();
  speedIntrEnable(256);
  if ( g_dev5_postdma_cbs[device] )
    g_dev5_postdma_cbs[device](bcr_in, dir);
  if ( g_xatapi_verbose > 0 )
    Kprintf("SpdDmaTransfer_extrans End.\n");
  SignalSema(g_dma_lock_sema);
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00402D4C) --------------------------------------------------------
int SpdDmaTransfer_extrans_2(unsigned int device, void *buf, u32 bcr_in, int dir)
{
  int result; // $v0

  dmac_ch_set_chcr(3u, 0);
  dmac_ch_get_chcr(3u);
  if ( device >= 2 && (!g_dev5_predma_cbs[device] || !g_dev5_postdma_cbs[device]) )
    return -1;
  if ( g_xatapi_verbose > 0 )
    Kprintf("Wait Intr\n");
  result = WaitSema(g_dma_lock_sema);
  if ( result < 0 )
    return result;
  if ( g_xatapi_verbose > 0 )
    Kprintf("DMA Ch3 Set.\n");
  if ( g_xatapi_verbose > 0 )
    Kprintf("Set MADR3:%08x Set BCR3:%08x\n", buf, bcr_in);
  dmac_ch_set_madr(3u, (u32)buf);
  dmac_ch_set_bcr(3u, bcr_in);
  dmac_ch_set_chcr(3u, dir | 0x41000200);
  dmac_ch_get_chcr(3u);
  if ( g_xatapi_verbose > 0 )
    Kprintf("CHCR3:%08x MADR3:%08x BCR3:%08x\n", dmac_ch_get_chcr(3u), dmac_ch_get_madr(3u), dmac_ch_get_bcr(3u));
  while ( (dmac_ch_get_chcr(3u) & 0x1000000) );
  if ( g_xatapi_verbose > 0 )
    Kprintf("MADR3= %08x\n", dmac_ch_get_madr(3u));
  if ( g_xatapi_verbose > 0 )
    Kprintf("SpdDmaTransfer_extrans End.\n");
  SignalSema(g_dma_lock_sema);
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00402F68) --------------------------------------------------------
int SpdDmaTransfer_extrans_3(unsigned int device, void *buf, u32 bcr_in, int dir)
{
  int result; // $v0

  dmac_ch_set_chcr(3u, 0);
  dmac_ch_get_chcr(3u);
  if ( device >= 2 && (!g_dev5_predma_cbs[device] || !g_dev5_postdma_cbs[device]) )
    return -1;
  if ( g_xatapi_verbose > 0 )
    Kprintf("Wait Intr\n");
  result = WaitSema(g_dma_lock_sema);
  if ( result < 0 )
    return result;
  FpgaLayer1On();
  FpgaXfrenOn();
  if ( g_xatapi_verbose > 0 )
    Kprintf("DMA Ch3 Set.\n");
  if ( g_xatapi_verbose > 0 )
    Kprintf("Set MADR3:%08x Set BCR3:%08x\n", buf, bcr_in);
  dmac_ch_set_madr(3u, (u32)buf);
  dmac_ch_set_bcr(3u, bcr_in);
  dmac_ch_set_chcr(3u, dir | 0x41000200);
  dmac_ch_get_chcr(3u);
  if ( g_xatapi_verbose > 0 )
    Kprintf("CHCR3:%08x MADR3:%08x BCR3:%08x\n", dmac_ch_get_chcr(3u), dmac_ch_get_madr(3u), dmac_ch_get_bcr(3u));
  while ( (dmac_ch_get_chcr(3u) & 0x1000000) );
  if ( g_xatapi_verbose > 0 )
    Kprintf("MADR3= %08x\n", dmac_ch_get_madr(3u));
  FpgaCheckWriteBuffer2();
  FpgaXfrenOff();
  FpgaLayer1Off();
  if ( g_xatapi_verbose > 0 )
    Kprintf("SpdDmaTransfer_extrans End.\n");
  SignalSema(g_dma_lock_sema);
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004031AC) --------------------------------------------------------
void speedLEDCtl(int ctl)
{
  // Unofficial: was 8 bit access
  dev5_speed_regs.r_spd_pio_data = !ctl;
}

//----- (004031C4) --------------------------------------------------------
void speed_init(void)
{
  int i; // $v1
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
  for ( i = 15; i >= 0; i -= 1 )
  {
    g_dev5_intr_cbs[i] = 0;
  }
  for ( i = 0; i < 4; i += 1 )
  {
    g_dev5_predma_cbs[i] = 0;
    g_dev5_postdma_cbs[i] = 0;
  }
  speedLEDCtl(0);
  return;
}

//----- (00403284) --------------------------------------------------------
void speed_device_init(void)
{
  int idx; // $v1
  char *revtypes[8]; // [sp+0h] [-20h] BYREF

  revtypes[4] = "unknown";
  revtypes[5] = "TS";
  revtypes[6] = "ES1";
  revtypes[7] = "ES2";
  switch ( dev5_speed_regs.r_spd_rev_1 )
  {
  case 9:
    idx = 1;
    break;
  case 16:
    idx = 2;
    break;
  case 17:
    idx = 3;
    break;
  default:
    idx = 0;
    break;
  }
  if ( idx )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("Speed chip: %s\n", revtypes[idx + 4]);
  }
  else
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("Speed chip: Rev %x\n", dev5_speed_regs.r_spd_rev_1);
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("Speed version(rev3.rev8) = %04x.%04x\n", dev5_speed_regs.r_spd_rev_3, dev5_speed_regs.r_spd_rev_8);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004033A0) --------------------------------------------------------
void do_hex_dump(void *ptr, int len)
{
  int i; // $fp
  int charbuf_offs; // $s5
  int j; // $s1
  char charbuf[17]; // [sp+10h] [-20h] BYREF

  if ( !g_xatapi_verbose )
  {
    return;
  }
  Kprintf("Hex dump 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f");
  j = 0;
  for ( i = 0; i < len; i += 256 )
  {
    for ( j = 0; j < (( (len - i) > 256 ) ? 256 : (len - i)); j += 1 )
    {
      charbuf_offs = j & 0xF;
      if ( !charbuf_offs && j )
      {
        charbuf[16] = 0;
        Kprintf(" %s\n%08x", charbuf, i + j);
      }
      Kprintf(" %02x", (u8)((char *)ptr)[i + j]);
      charbuf[charbuf_offs] = ( ((char *)ptr)[i + j] >= 0 && isgraph(((char *)ptr)[i + j]) ) ? ((char *)ptr)[i + j] : '.';
    }
  }
  charbuf_offs = j & 0xF;
  for ( i = 0; (unsigned int)i < (unsigned int)((sizeof(charbuf) - 1) - charbuf_offs); i += 1 )
  {
    Kprintf("\t  ");
  }
  charbuf[charbuf_offs] = 0;
  Kprintf("%s\n", charbuf);
}
// 403414: conditional instruction was optimized away because $s4.4 is in (1..100|<0)
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403554) --------------------------------------------------------
void ata_pre_dma_cb(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("ata_pre_dma_handler:old %x\n", dev5_speed_regs.r_spd_xfr_ctrl);
  dev5_speed_regs.r_spd_xfr_ctrl |= 0x80;
  if ( g_xatapi_verbose > 0 )
    Kprintf("ata_pre_dma_handler:new %x\n", dev5_speed_regs.r_spd_xfr_ctrl);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004035CC) --------------------------------------------------------
void ata_post_dma_cb(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("ata_post_dma_handler:old %x\n", dev5_speed_regs.r_spd_xfr_ctrl);
  dev5_speed_regs.r_spd_xfr_ctrl &= 0xFF7F;
  if ( g_xatapi_verbose > 0 )
    Kprintf("ata_post_dma_handler:new %x\n", dev5_speed_regs.r_spd_xfr_ctrl);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403644) --------------------------------------------------------
int vReferEventFlagStatus(int ef, iop_event_info_t *info)
{
  return ( QueryIntrContext() ) ? iReferEventFlagStatus(ef, info) : ReferEventFlagStatus(ef, info);
}

//----- (00403694) --------------------------------------------------------
void xatapi_9_sceCdSpdAtaDmaStart(int dir)
{
  int spd_if_ctrl_manip_2; // $a1
  u32 efbits; // [sp+10h] [-8h] BYREF

  g_is_wait_busy = 0;
  WaitEventFlag(g_adma_evfid, 1u, 16, &efbits);
  g_should_wait_for_dma_flag = 1;
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdSpdAtaDmaStart Call %d :Read 0:Write 1\n", dir);
  dev5_speed_regs.r_spd_dbuf_stat = 3;
  spd_if_ctrl_manip_2 = (dev5_speed_regs.r_spd_if_ctrl & 1) | (dir ? 0x4C : 0x4E);
  dev5_speed_regs.r_spd_if_ctrl = spd_if_ctrl_manip_2;
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdSpdAtaDmaStart Write R_IF_CTR:%x\n", spd_if_ctrl_manip_2);
  dev5_speed_regs.r_spd_xfr_ctrl = dir | 6;
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdSpdAtaDmaStart R_IF_CTR:%x R_XFR_CTRL:%x\n", dev5_speed_regs.r_spd_if_ctrl, dev5_speed_regs.r_spd_xfr_ctrl);
}
// 40A640: using guessed type int g_should_wait_for_dma_flag;
// 40A644: using guessed type int g_is_wait_busy;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403790) --------------------------------------------------------
void xatapi_10_sceCdSpdAtaDmaEnd(void)
{
  iop_event_info_t efinfo; // [sp+10h] [-20h] BYREF

  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdSpdAtaDmaEnd Call\n");
  if ( !g_should_wait_for_dma_flag )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceCdSpdAtaDmaEnd No Start(flag)\n");
    return;
  }
  if ( vReferEventFlagStatus(g_adma_evfid, &efinfo) || (efinfo.currBits & 1) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceCdSpdAtaDmaEnd No Start\n");
    g_should_wait_for_dma_flag = 0;
    return;
  }
  dev5_speed_regs.r_spd_xfr_ctrl = 1;
  dev5_speed_regs.r_spd_if_ctrl &= ~0x4;
  dev5_speed_regs.r_spd_dbuf_stat = 3;
  dev5_speed_regs.r_spd_if_ctrl &= ~0x84;
  dev5_speed_regs.r_spd_if_ctrl |= 0x80;
  dev5_speed_regs.r_spd_if_ctrl &= ~0x84;
  ata_pio_mode(0);
  if ( g_dma_mode_value )
    ata_ultra_dma_mode(g_dma_speed_value);
  else
    ata_multiword_dma_mode(g_dma_speed_value);
  g_should_wait_for_dma_flag = 0;
  SetEventFlag(g_adma_evfid, 1u);
}
// 40A638: using guessed type int g_dma_mode_value;
// 40A640: using guessed type int g_should_wait_for_dma_flag;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403918) --------------------------------------------------------
void ata_pio_mode(int mode)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("SpdAtaSetPioTiming %d\n", mode);
  switch ( mode )
  {
    case 0:
    default:
      dev5_speed_regs.r_spd_pio_mode = 146;
      break;
    case 1:
      dev5_speed_regs.r_spd_pio_mode = 114;
      break;
    case 2:
      dev5_speed_regs.r_spd_pio_mode = 50;
      break;
    case 3:
      dev5_speed_regs.r_spd_pio_mode = 36;
      break;
    case 4:
      dev5_speed_regs.r_spd_pio_mode = 35;
      break;
  }
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004039D0) --------------------------------------------------------
void ata_multiword_dma_mode(int mode)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("SpdAtaSetMdmaTiming %d\n", mode);
  switch ( mode )
  {
    case 0:
    default:
      dev5_speed_regs.r_spd_mwdma_mode = 255;
      break;
    case 1:
      dev5_speed_regs.r_spd_mwdma_mode = 69;
      break;
    case 2:
      dev5_speed_regs.r_spd_mwdma_mode = 36;
      break;
  }
  dev5_speed_regs.r_spd_if_ctrl = (dev5_speed_regs.r_spd_if_ctrl & 0xFFB6) | 0x48;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403A64) --------------------------------------------------------
void ata_ultra_dma_mode(int mode)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("SpdAtaSetUdmaTiming %d\n", mode);
  switch ( mode )
  {
    case 0:
    default:
      dev5_speed_regs.r_spd_udma_mode = 167;
      break;
    case 1:
      dev5_speed_regs.r_spd_udma_mode = 133;
      break;
    case 2:
      dev5_speed_regs.r_spd_udma_mode = 99;
      break;
    case 3:
      dev5_speed_regs.r_spd_udma_mode = 98;
      break;
    case 4:
      dev5_speed_regs.r_spd_udma_mode = 97;
      break;
  }
  dev5_speed_regs.r_spd_if_ctrl = dev5_speed_regs.r_spd_if_ctrl | 0x49;
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
  u32 efbits; // [sp+10h] [-8h] BYREF

  if ( (unsigned int)(regaddr - 64) < 0x1D )
  {
    WaitEventFlag(g_acmd_evfid, 1u, 16, &efbits);
    *(vu16 *)((char *)&dev5_speed_regs.unv00 + regaddr) = regval;
    SetEventFlag(g_acmd_evfid, 1u);
  }
  return regval;
}

//----- (00403C98) --------------------------------------------------------
int xatapi_13_get_speed_reg(int regaddr)
{
  int tmpval; // $s0
  u32 efbits; // [sp+10h] [-8h] BYREF

  if ( (unsigned int)(regaddr - 64) >= 0x1D )
    return 0;
  WaitEventFlag(g_acmd_evfid, 1u, 16, &efbits);
  tmpval = *(u16 *)((char *)&dev5_speed_regs.unv00 + regaddr);
  SetEventFlag(g_acmd_evfid, 1u);
  return tmpval;
}

//----- (00403D08) --------------------------------------------------------
int xatapi_11_sceAtaGetError(void)
{
  u8 r_spd_ata_error; // $s0
  u32 efbits; // [sp+10h] [-8h] BYREF

  WaitEventFlag(g_acmd_evfid, 1u, 16, &efbits);
  r_spd_ata_error = dev5_speed_regs.r_spd_ata_error;
  SetEventFlag(g_acmd_evfid, 1u);
  return r_spd_ata_error;
}

//----- (00403D5C) --------------------------------------------------------
int xatapi_12_get_ata_control(void)
{
  u8 r_spd_ata_control; // $s0
  u32 efbits; // [sp+10h] [-8h] BYREF

  WaitEventFlag(g_acmd_evfid, 1u, 16, &efbits);
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
  unsigned int i; // $s0

  for ( i = 0; i < 0x50; i += 1 )
  {
    if ( !(dev5_speed_regs.r_spd_ata_control & 0x80) )
    {
      return 0;
    }
    if ( !(u16)expbay_get_has_power() )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: wait busy, power off.\n");
      return -551;
    }
    if ( g_is_wait_busy )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: wait busy, tray eject.\n");
      return -550;
    }
    switch ( i / 0xA )
    {
      case 0u:
        break;
      case 1u:
        DelayThread(100);
        break;
      case 2u:
        DelayThread(1000);
        break;
      case 3u:
        DelayThread(10000);
        break;
      case 4u:
        DelayThread(100000);
        break;
      default:
        DelayThread(1000000);
        break;
    }
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("DEV5 ATA: error: wait busy, timedout.\n", i / 0xA);
  return -502;
}
// 403F14: variable 'waitcnt_div' is possibly undefined
// 40A644: using guessed type int g_is_wait_busy;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00403F3C) --------------------------------------------------------
int ata_wait_busy2_busy(void)
{
  unsigned int i; // $s0

  for ( i = 0; i < 55; i += 1 )
  {
    if ( !(dev5_speed_regs.r_spd_ata_control & 0x80) )
    {
      return 0;
    }
    if ( !(u16)expbay_get_has_power() )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: wait busy, power off.\n");
      return -551;
    }
    if ( g_is_wait_busy )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: wait busy, tray eject.\n");
      return -550;
    }
    switch ( i / 0xA )
    {
      case 0u:
        break;
      case 1u:
        DelayThread(100);
        break;
      case 2u:
        DelayThread(1000);
        break;
      case 3u:
        DelayThread(10000);
        break;
      case 4u:
        DelayThread(100000);
        break;
      default:
        DelayThread(1000000);
        break;
    }
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("DEV5 ATA: error: wait busy, timedout.\n", i / 0xA);
  return -502;
}
// 40408C: variable 'waitcnt_div' is possibly undefined
// 40A644: using guessed type int g_is_wait_busy;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004040B4) --------------------------------------------------------
int ata_wait_bus_busy_busbusy(void)
{
  unsigned int i; // $s0

  for ( i = 0; i < 80; i += 1 )
  {
    if ( !(dev5_speed_regs.r_spd_ata_control & 0x88) )
    {
      return 0;
    }
    if ( !(u16)expbay_get_has_power() )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: wait busy, power off.\n");
      return -551;
    }
    if ( g_is_wait_busy )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: wait busbusy, tray eject.\n");
      return -550;
    }
    switch ( i / 0xA )
    {
      case 0u:
        break;
      case 1u:
        DelayThread(100);
        break;
      case 2u:
        DelayThread(1000);
        break;
      case 3u:
        DelayThread(10000);
        break;
      case 4u:
        DelayThread(100000);
        break;
      default:
        DelayThread(1000000);
        break;
    }
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("DEV5 ATA: error: wait busbusy, timedout.\n", i / 0xA);
  return -502;
}
// 404204: variable 'waitcnt_div' is possibly undefined
// 40A644: using guessed type int g_is_wait_busy;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (0040422C) --------------------------------------------------------
int ata_device_select(int device)
{
  int result; // $v0

  result = ata_wait_bus_busy_busbusy();
  if ( result < 0 )
  {
    return result;
  }
  if ( ((dev5_speed_regs.r_spd_ata_select >> 4) & 1) == device )
  {
    return 0;
  }
  dev5_speed_regs.r_spd_ata_select = (device ? 1 : 0) << 4;
  return ata_wait_bus_busy_busbusy();
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
  int result; // $v0
  int using_timeout; // $s0
  iop_sys_clock_t sysclk; // [sp+10h] [-10h] BYREF

  ClearEventFlag(g_atapi_event_flag, 0);
  g_is_wait_busy = 0;
  if ( !atad_devinfo[(select & 0x10) ? 1 : 0].exists )
    return -505;
  result = ata_device_select((select >> 4) & 1);
  if ( result )
  {
    return result;
  }
  if ( command == 142 || command == 176 )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("Not support Ata CMD\n");
    return -503;
  }
  atad_cmd_state.type = unk10;
  if ( !unk10 )
    return -506;
  atad_cmd_state.buf = buf;
  atad_cmd_state.blkcount = blkcount;
  if ( !(dev5_speed_regs.r_spd_ata_control & 0x40) && ((command < 0x90u && command != 8) || (command >= 0xA2u || command < 0xA0u)) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("DEV5 ATA: error: device not ready\n");
    return -501;
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
    if ( using_timeout )
    {
      USec2SysClock((command != 142 || feature != 244) ? 155000000 : 180000000, &sysclk);
      result = SetAlarm(&sysclk, AtaAlarmrHandle, 0);
      if ( result < 0 ) 
        return result;
    }
    if ( atad_cmd_state.type == 1 )
      speedIntrEnable(1);
    dev5_speed_regs.r_spd_ata_control = (!using_timeout) << 1;
  }
  dev5_speed_regs.r_spd_ata_error = feature;
  dev5_speed_regs.r_spd_ata_nsector = nsector;
  dev5_speed_regs.r_spd_ata_sector = sector;
  dev5_speed_regs.r_spd_ata_lcyl = lcyl;
  dev5_speed_regs.r_spd_ata_hcyl = hcyl;
  dev5_speed_regs.r_spd_ata_select = select | 0x40;
  dev5_speed_regs.r_spd_ata_status = command;
  speedLEDCtl(1);
  return 0;
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
  u32 efbits; // [sp+28h] [-8h] BYREF

  WaitEventFlag(g_acmd_evfid, 1u, 16, &efbits);
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
  u16 feature_tmp; // $s2
  int result; // $v0
  int using_timeout; // $s1
  int retres1; // $s0
  char ata_status_1; // $s0
  unsigned int i; // $s0
  iop_sys_clock_t sysclk; // [sp+28h] [-8h] BYREF

  feature_tmp = 0;
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdAtapiExecCmd Start. pkt_len %d proto %d\n", pkt_len, proto);
  do_hex_dump(pkt, 12);
  g_is_wait_busy = 0;
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
      switch ( *(u8 *)pkt )
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
      Kprintf("illegal stream\n");
    return -560;
  }
  if ( using_timeout )
  {
    USec2SysClock(0x93D1CC0u, &sysclk);
    result = SetAlarm(&sysclk, AtaAlarmrHandle, 0);
    if ( result < 0 )
      return result;
  }
  if ( atad_cmd_state.type_atapi == 1 )
    speedIntrEnable(1);
  dev5_speed_regs.r_spd_ata_control = (!using_timeout) << 1;
  result = sceAtaExecCmd(
             0,
             0,
             feature_tmp,
             0,
             0,
             (u8)((atad_cmd_state.blkcount_atapi & 0xFF) * (atad_cmd_state.blksize_atapi & 0xFF)),
             (u8)((u16)((atad_cmd_state.blkcount_atapi & 0xFFFF)
                                                * (atad_cmd_state.blksize_atapi & 0xFFFF)) >> 8),
             n << 4,
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
    int ata_status_2; // $a1

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
  if ( (ata_status_1 & 1) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("iocmd err 0x%02x, 0x%02x\n", ata_status_1, sceAtaGetError());
    if ( using_timeout )
    {
      CancelAlarm(AtaAlarmrHandle, 0);
    }
    return -503;
  }
  if ( !(ata_status_1 & 8) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceCdAtapiExecCmd_local ATA_NO_DREQ\n");
  }
  for ( i = 0; i < (pkt_len >> 1); i += 1 )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceCdAtapiExecCmd_local Packet %04x\n", ((u16 *)pkt)[i]);
    dev5_speed_regs.r_spd_ata_data = ((u16 *)pkt)[i];
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdAtapiExecCmd End. cmd %02x\n", *(u8 *)pkt);
  if ( g_is_wait_busy )
  {
    if ( using_timeout )
      CancelAlarm(AtaAlarmrHandle, 0);
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceCdAtapiExecCmd Tray Eject last\n", pkt_len >> 1);
    return -550;
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdAtapiExecCmd OK\n");
  return 0;
}
// 404AF0: variable 'ata_status_2' is possibly undefined
// 40A630: using guessed type int g_reset_scrambling_pack;
// 40A644: using guessed type int g_is_wait_busy;
// 40A648: using guessed type int g_xatapi_verbose;
// 40A710: using guessed type ata_cmd_state_t atad_cmd_state;

//----- (00404CEC) --------------------------------------------------------
int sceCdAtapiExecCmd(s16 n, void *buf, int nsec, int secsize, void *pkt, int pkt_len, int proto)
{
  if ( pkt_len )
  {
    int pkt_scsi_cmd_2; // $a1

    pkt_scsi_cmd_2 = *(u8 *)pkt;
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceCdAtapiExecCmd %08x\n", pkt_scsi_cmd_2);
    if ( (!(pkt_scsi_cmd_2 == 0x1B || pkt_scsi_cmd_2 == 0x12 || !pkt_scsi_cmd_2 || pkt_scsi_cmd_2 == 3 || *g_cd_sc_ffffffd9_ptr)) && !g_is_in_read_info && !sceCdAtapi_BC() )
    {
      ata_device_set_transfer_mode_outer(0);
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
  u32 efbits; // [sp+20h] [-8h] BYREF

  WaitEventFlag(g_acmd_evfid, 1u, 16, &efbits);
  retres = sceCdAtapiExecCmd(n, buf, nsec, secsize, pkt, pkt_len, proto);
  if ( retres )
  {
    SetEventFlag(g_acmd_evfid, 1u);
  }
  return retres;
}

//----- (00404ECC) --------------------------------------------------------
int ata_pio_transfer(ata_cmd_state_t *cmd_state)
{
  char r_spd_ata_status; // $s0

  r_spd_ata_status = dev5_speed_regs.r_spd_ata_status;
  if ( (r_spd_ata_status & 1) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("DEV5 ATA: error: ATA PIO iocmd err 0x%02x, 0x%02x\n", r_spd_ata_status, sceAtaGetError());
    return -503;
  }
  else if ( (r_spd_ata_status & 8) )
  {
    int i; // $a1

    switch ( cmd_state->type )
    {
      case 2:
      {
        for ( i = 0; i < 256; i += 1 )
        {
          cmd_state->buf16[i] = dev5_speed_regs.r_spd_ata_data;
        }
        cmd_state->buf16 += 256;
        break;
      }
      case 3:
      {
        for ( i = 0; i < 256; i += 1 )
        {
          dev5_speed_regs.r_spd_ata_data = cmd_state->buf16[i];
        }
        cmd_state->buf16 += 256;
        break;
      }
      case 11:
      {
        for ( i = 0; i < 256; i += 1 )
        {
          dev5_speed_regs.r_spd_ata_data = cmd_state->buf16[i];
        }
        cmd_state->buf16 += 256;
        for ( i = 0; i < 4; i += 1 )
        {
          dev5_speed_regs.r_spd_ata_data = cmd_state->buf8[512 + i];
        }
        cmd_state->buf8 += 4;
        break;
      }
      default:
        break;
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
  unsigned int lhcyl; // $s0
  unsigned int i; // $a1

  if ( g_xatapi_verbose > 0 )
    Kprintf("Pio trans %d\n", cmd_state->blkcount_atapi * cmd_state->blksize_atapi);
  result = ata_wait_busy1_busy();
  if ( result < 0 )
    return result;
  result = 0;
  for ( blktotal = cmd_state->blkcount_atapi * cmd_state->blksize_atapi; result >= 0 && blktotal; blktotal -= lhcyl )
  {
    char r_spd_ata_status; // $s0

    r_spd_ata_status = dev5_speed_regs.r_spd_ata_status;
    if ( (r_spd_ata_status & 1) )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: ATAPI PIO iocmd err 0x%02x, 0x%02x\n", r_spd_ata_status, sceAtaGetError());
      return -503;
    }
    if ( !(r_spd_ata_status & 8) )
      return -504;
    // Unofficial: was 8 bit access
    lhcyl = (dev5_speed_regs.r_spd_ata_lcyl & 0xFF) | ((dev5_speed_regs.r_spd_ata_hcyl & 0xFF) << 8);
    if ( g_xatapi_verbose > 0 )
      Kprintf("ByteCount Trans byte %04x\n", lhcyl);
    switch ( cmd_state->type_atapi )
    {
      case 2:
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("IoRun_atapi input trans %d\n", cmd_state->blksize_atapi);
        for ( i = 0; i < (lhcyl >> 1); i += 1 )
        {
          ((u16 *)((char *)cmd_state->buf_atapi))[i] = dev5_speed_regs.r_spd_ata_data;
        }
        if ( (lhcyl & 1) )
          *((u8 *)cmd_state->buf_atapi + 2 * i) = dev5_speed_regs.r_spd_ata_data;
        cmd_state->buf_atapi = (char *)cmd_state->buf_atapi + lhcyl;
        break;
      }
      case 3:
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("IoRun_atapi output trans %d\n", cmd_state->blksize_atapi);
        for ( i = 0; i < (lhcyl >> 1); i += 1 )
        {
          dev5_speed_regs.r_spd_ata_data = ((u16 *)cmd_state->buf_atapi)[i];
        }
        if ( (lhcyl & 1) )
          dev5_speed_regs.r_spd_ata_data = *((u8 *)cmd_state->buf_atapi + 2 * i);
        cmd_state->buf_atapi = (char *)cmd_state->buf_atapi + lhcyl;
        break;
      }
      default:
        break;
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
  unsigned int dbuf_stat_mask; // $s0
  int result; // $v0
  u8 Error; // $v0
  char spd_ata_status_tmp; // $s1
  u32 efbits; // [sp+10h] [-8h] BYREF
  int flg;

  for ( blkcount_tmp = blkcount; blkcount_tmp; blkcount_tmp -= (flg ? dbuf_stat_mask : 0) )
  {
    dbuf_stat_mask = 0;
    for ( i = 0; i < 20 && !dbuf_stat_mask; i += 1 )
    {
      dbuf_stat_mask = dev5_speed_regs.r_spd_dbuf_stat & 0x1F;
    }
    if ( g_xatapi_verbose > 0 )
      Kprintf("*SPD_RINTR_STAT %02x\n", dev5_speed_regs.r_spd_intr_stat);
    if ( g_xatapi_verbose > 0 )
      Kprintf("*R_DBUF_STAT %02x\n", dev5_speed_regs.r_spd_dbuf_stat);
    flg = 1;
    if ( !dbuf_stat_mask )
    {
      speedIntrEnable(3);
      if ( g_xatapi_verbose > 0 )
        Kprintf("Wait Event\n");
      WaitEventFlag(g_atapi_event_flag, 7u, 17, &efbits);
      if ( g_xatapi_verbose > 0 )
        Kprintf("Event come\n");
      if ( (efbits & 1) )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: DmaRun, ata timedout\n");
        return -502;
      }
      if ( (efbits & 4) )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: DmaRun, Media Eject\n");
        return -550;
      }
      if ( !(dev5_speed_regs.r_spd_intr_stat & 2) )
      {
        if ( (dev5_speed_regs.r_spd_ata_control & 1) )
        {
          spd_ata_status_tmp = dev5_speed_regs.r_spd_ata_status;
          Error = sceAtaGetError();
          if ( g_xatapi_verbose > 0 )
            Kprintf("DEV5 ATA: error: cmd err 0x%02x, 0x%02x, while DmaRun\n", spd_ata_status_tmp, Error);
          return ( !(Error & 0x80) ) ? -503 : -510;
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
      buf += dbuf_stat_mask << 9;
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
  unsigned int blkremainder; // $a1
  unsigned int blksectors; // $s3
  int i; // $v1
  unsigned int dbuf_stat_mask; // $s0
  int result; // $v0
  u8 Error; // $v0
  char spd_ata_status_tmp; // $s1
  unsigned int dbuf_stat_sectors; // $s2
  u32 efbits; // [sp+18h] [-8h] BYREF

  if ( g_xatapi_verbose > 0 )
    Kprintf("DmaRun_atapi start\n");
  blkremainder = (blkcount * blksize) & 0x1FF;
  for ( blksectors = (unsigned int)(blkcount * blksize) >> 9; blksectors; blksectors -= dbuf_stat_mask )
  {
    dbuf_stat_mask = 0;
    for ( i = 0; i < 20 && !dbuf_stat_mask; i += 1 )
    {
      dbuf_stat_mask = dev5_speed_regs.r_spd_dbuf_stat & 0x1F;
    }
    if ( !dbuf_stat_mask )
    {
      speedIntrEnable(3);
      WaitEventFlag(g_atapi_event_flag, 7u, 17, &efbits);
      if ( (efbits & 1) )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: DmaRun, ata timedout\n");
        return -502;
      }
      if ( (efbits & 4) )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: DmaRun, Media Eject\n");
        return -550;
      }
      if ( (dev5_speed_regs.r_spd_intr_stat & 2) )
      {
        dbuf_stat_mask = dev5_speed_regs.r_spd_dbuf_stat & 0x1F;
      }
      else
      {
        if ( (dev5_speed_regs.r_spd_ata_control & 1) )
        {
          spd_ata_status_tmp = dev5_speed_regs.r_spd_ata_status;
          Error = sceAtaGetError();
          if ( g_xatapi_verbose > 0 )
            Kprintf("DEV5 ATA: error: cmd err 0x%02x, 0x%02x, while DmaRun\n", spd_ata_status_tmp, Error);
          return ( !(Error & 0x80) ) ? -503 : -510;
        }
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: warning: ata intr without error.\n");
        continue;
      }
    }
    if ( blksectors < dbuf_stat_mask )
    {
      dbuf_stat_mask = blksectors;
    }
    dbuf_stat_sectors = dbuf_stat_mask << 9;
    if ( g_xatapi_verbose > 0 )
      Kprintf("DmaRun_atapi  cnt %d nblk %d secsize %d bcr %08x\n", dbuf_stat_mask, blksectors, blksize, (dbuf_stat_sectors << 9) | 0x20);
    result = SpdDmaTransfer(0, buf, (dbuf_stat_sectors << 9) | 0x20, dir);
    buf += dbuf_stat_sectors;
    if ( result < 0 )
      return result;
  }
  if ( blkremainder )
  {
    while ( !(dev5_speed_regs.r_spd_intr_stat & 1) );
    dev5_speed_regs.m_spd_unk36 += 512;
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
    Kprintf("DmaRun_atapi End.\n");
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
  int i; // $v1
  unsigned int dbuf_stat_mask; // $s0
  int result; // $v0
  u8 Error; // $v0
  char spd_ata_status_tmp; // $s1
  unsigned int dbuf_stat_sectors; // $s3
  u32 efbits; // [sp+18h] [-8h] BYREF

  if ( g_xatapi_verbose > 0 )
    Kprintf("DmaRun_atapi_extrans start\n");
  FpgaLayer2Off();
  FpgaClearBuffer();
  FpgaXfdir(dir);
  blkremainder = (blkcount * blksize) & 0x1FF;
  for ( blksectors = (unsigned int)(blkcount * blksize) >> 9; blksectors; blksectors -= dbuf_stat_mask )
  {
    dbuf_stat_mask = 0;
    for ( i = 0; i < 20 && !dbuf_stat_mask; i += 1 )
    {
      dbuf_stat_mask = dev5_speed_regs.r_spd_dbuf_stat & 0x1F;
    }
    if ( !dbuf_stat_mask )
    {
      speedIntrEnable(3);
      WaitEventFlag(g_atapi_event_flag, 7u, 17, &efbits);
      if ( (efbits & 1) )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: DmaRun_atapi_extrans, ata timedout\n");
        return -502;
      }
      if ( (efbits & 4) )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: DmaRun_atapi_extrans, Media Eject\n");
        return -550;
      }
      if ( (dev5_speed_regs.r_spd_intr_stat & 2) )
      {
        dbuf_stat_mask = dev5_speed_regs.r_spd_dbuf_stat & 0x1F;
      }
      else
      {
        if ( (dev5_speed_regs.r_spd_ata_control & 1) )
        {
          spd_ata_status_tmp = dev5_speed_regs.r_spd_ata_status;
          Error = sceAtaGetError();
          if ( g_xatapi_verbose > 0 )
            Kprintf("DEV5 ATA: error: cmd err 0x%02x, 0x%02x, while DmaRun\n", spd_ata_status_tmp, Error);
          return ( !(Error & 0x80) ) ? -503 : -510;
        }
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: warning: ata intr without error.\n");
        continue;
      }
    }
    if ( blksectors < dbuf_stat_mask )
    {
      dbuf_stat_mask = blksectors;
    }
    dbuf_stat_sectors = dbuf_stat_mask << 9;
    if ( g_xatapi_verbose > 0 )
      Kprintf("DmaRun_atapi_extrans  cnt %d nblk %d secsize %d bcr %08x\n", dbuf_stat_mask, blksectors, blksize, (dbuf_stat_sectors << 9) | 0x20);
    result = SpdDmaTransfer_extrans_1(0, buf, (dbuf_stat_sectors << 9) | 0x20, dir);
    buf += dbuf_stat_sectors;
    if ( result < 0 )
      return result;
  }
  if ( blkremainder )
  {
    while ( !(dev5_speed_regs.r_spd_intr_stat & 1) );
    dev5_speed_regs.m_spd_unk36 += 512;
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
    Kprintf("DmaRun_atapi_extrans End.\n");
  return 0;
}
// 4059FC: conditional instruction was optimized away because $s0.4==0
// 40A648: using guessed type int g_xatapi_verbose;
// 40A938: using guessed type int g_atapi_xfer_buf[130];

//----- (00405D04) --------------------------------------------------------
int DmaRun_atapi_extrans2(char *buf, int blkcount, int blksize, int dir)
{
  int result; // $v0
  unsigned int blksectors; // $s2
  int blkremainder; // $s6
  int i; // $s1
  unsigned int fpga_unk8148; // $s0
  u8 Error; // $v0
  int extransres; // $s1
  iop_sys_clock_t sysclk; // [sp+18h] [-10h] BYREF
  u32 efbits; // [sp+20h] [-8h] BYREF

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
    WaitEventFlag(g_atapi_event_flag, 7u, 17, &efbits);
    if ( (efbits & 1) )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: DmaRun_atapi_extrans, ata timedout\n");
      return -502;
    }
    if ( (efbits & 4) )
    {
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: DmaRun_atapi_extrans, Media Eject\n");
      return -550;
    }
    if ( (dev5_speed_regs.r_spd_intr_stat & 2) )
    {
      break;
    }
    if ( (dev5_speed_regs.r_spd_ata_control & 1) )
    {
      Error = sceAtaGetError();
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: cmd err 0x%02x, 0x%02x, while DmaRun\n", dev5_speed_regs.r_spd_ata_status, Error);
      return ( !(Error & 0x80) ) ? -503 : -510;
    }
    if ( g_xatapi_verbose > 0 )
      Kprintf("DEV5 ATA: warning: ata intr without error.\n");
  }
  dev5_speed_regs.r_spd_dma_ctrl = ( dev5_speed_regs.r_spd_rev_1 >= 0x11u ) ? 6 : 4;
  ata_pre_dma_cb();
  FpgaLayer1On();
  FpgaXfrenOn();
  blkremainder = (blkcount * blksize) & 0x1FF;
  extransres = 0;
  for ( blksectors = (unsigned int)(blkcount * blksize) >> 9; blksectors; blksectors -= fpga_unk8148 )
  {
    unsigned int unk8148_bytes; // $s3

    for ( i = 0; ; i += 1 )
    {
      fpga_unk8148 = do_fpga_check_unk8148();
      if ( fpga_unk8148 >= 3 || fpga_unk8148 >= blksectors )
        break;
      switch ( i / 500 )
      {
        case 0:
          break;
        case 1:
          DelayThread(100);
          break;
        default:
          DelayThread(10000);
          break;
      }
      PollEventFlag(g_atapi_event_flag, 5u, 17, &efbits);
      if ( (efbits & 1) )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: DmaRun_atapi_extrans, ata timedout\n");
        FpgaXfrenOff();
        FpgaLayer1Off();
        ata_post_dma_cb();
        if ( !(dev5_speed_regs.r_spd_intr_stat & 2) && (dev5_speed_regs.r_spd_ata_control & 1) )
        {
          Error = sceAtaGetError();
          if ( g_xatapi_verbose > 0 )
            Kprintf("DEV5 ATA: error: cmd err 0x%02x, 0x%02x, while DmaRun\n", dev5_speed_regs.r_spd_ata_status, Error);
          return ( !(Error & 0x80) ) ? -503 : -510;
        }
        return -502;
      }
      if ( (efbits & 4) )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: DmaRun_atapi_extrans, Media Eject\n");
        FpgaXfrenOff();
        FpgaLayer1Off();
        ata_post_dma_cb();
        return -550;
      }
    }
    if ( blksectors < fpga_unk8148 )
    {
      fpga_unk8148 = blksectors;
    }
    unk8148_bytes = fpga_unk8148 << 9;
    if ( g_xatapi_verbose > 0 )
      Kprintf("DmaRun_atapi_extrans  cnt %d nblk %d secsize %d bcr %08x\n", fpga_unk8148, blksectors, blksize, (unk8148_bytes << 9) | 0x20);
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
    while ( !(dev5_speed_regs.r_spd_intr_stat & 1) );
    dev5_speed_regs.m_spd_unk36 +=  512;
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
    Kprintf("DmaRun_atapi_extrans End.\n");
  return 0;
}
// 40A648: using guessed type int g_xatapi_verbose;
// 40A938: using guessed type int g_atapi_xfer_buf[130];

//----- (004062F4) --------------------------------------------------------
void DmaRun_spck(char *buf, unsigned int secsize)
{
  unsigned int secsize_sectors; // $s2
  unsigned int unk8148_val; // $s1

  if ( g_xatapi_verbose > 0 )
    Kprintf("DmaRun_spck start\n");
  FpgaSpckmodeOn();
  FpgaLayer2Off();
  FpgaClearBuffer();
  FpgaXfdir(0);
  for ( secsize_sectors = secsize >> 9; secsize_sectors; secsize_sectors -= unk8148_val )
  {
    unsigned int unk8148_bytes; // $s3

    for ( unk8148_val = 0; unk8148_val < 4; unk8148_val = do_fpga_check_unk8148() );
    if ( secsize_sectors < unk8148_val )
    {
      unk8148_val = secsize_sectors;
    }
    unk8148_bytes = unk8148_val << 9;
    if ( g_xatapi_verbose > 0 )
      Kprintf("DmaRun_spck  cnt %d nblk %d secsize %d bcr %08x\n", unk8148_val, secsize_sectors, secsize, (unk8148_bytes << 9) | 0x20);
    if ( SpdDmaTransfer_extrans_3(0, buf, (unk8148_bytes << 9) | 0x20, 1) < 0 )
    {
      FpgaSpckmodeOff();
      return;
    }
    buf += unk8148_bytes;
  }
  if ( (secsize & 0x1FF) )
  {
    dev5_speed_regs.m_spd_unk36 += 512;
    if ( g_xatapi_verbose > 0 )
      Kprintf("SpdDmaTransfer buf:%08x bcr:%d dir:%d\n", buf, 262176, 1);
    memcpy(g_atapi_xfer_buf, buf, secsize & 0x1FF);
    if ( SpdDmaTransfer_extrans_3(0, g_atapi_xfer_buf, 0x40020u, 1) < 0 )
    {
      return;
    }
  }
  FpgaSpckmodeOff();
  if ( g_xatapi_verbose > 0 )
    Kprintf("DmaRun_spck End.\n");
}
// 40A648: using guessed type int g_xatapi_verbose;
// 40A938: using guessed type int g_atapi_xfer_buf[130];

//----- (004064D4) --------------------------------------------------------
int sceAtaWaitResult(void)
{
  int res; // $s0
  int i; // $v1
  int intr_stat_msk; // [sp+10h] [-8h]
  u32 efbits; // [sp+14h] [-4h] BYREF
  int suc;

  suc = 0;
  res = 0;
  switch ( atad_cmd_state.type )
  {
    case 1:
    case 8:
      WaitEventFlag(g_atapi_event_flag, 7u, 17, &efbits);
      if ( (efbits & 1) )
      {
        res = -502;
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: ata timedout while non data command\n");
      }
      if ( (efbits & 4) )
      {
        res = -550;
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: DmaRun, Media Eject\n");
      }
      suc = 1;
      break;
    case 4:
    case 5:
    case 6:
      res = atapi_some_transfer_wrapper((char *)atad_cmd_state.buf, atad_cmd_state.blkcount, atad_cmd_state.dir);
      if ( res )
      {
        break;
      }
      intr_stat_msk = 0;
      for ( i = 0; i < 100 && !intr_stat_msk; i += 1 )
      {
        intr_stat_msk = dev5_speed_regs.r_spd_intr_stat & 1;
      }
      if ( !intr_stat_msk )
      {
        speedIntrEnable(1);
        WaitEventFlag(g_atapi_event_flag, 7u, 17, &efbits);
        if ( (efbits & 1) )
        {
          if ( g_xatapi_verbose > 0 )
            Kprintf("DEV5 ATA: error: ata timedout, buffer stat %04x\n", dev5_speed_regs.r_spd_dbuf_stat);
          if ( g_xatapi_verbose > 0 )
            Kprintf("DEV5 ATA: error: istat %x, ienable %x\n", dev5_speed_regs.r_spd_intr_stat, dev5_speed_regs.r_spd_intr_mask);
          res = -502;
        }
        if ( (efbits & 4) )
        {
          if ( g_xatapi_verbose > 0 )
            Kprintf("DEV5 ATA: error: ata eject, buffer stat %04x\n", dev5_speed_regs.r_spd_dbuf_stat);
          if ( g_xatapi_verbose > 0 )
            Kprintf("DEV5 ATA: error: istat %x, ienable %x\n", dev5_speed_regs.r_spd_intr_stat, dev5_speed_regs.r_spd_intr_mask);
          res = -550;
        }
      }
      suc = 1;
      break;
    default:
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
      break;
  }
  if ( suc && !res )
  {
    char status_tmp; // [sp+10h] [-8h]

    status_tmp = dev5_speed_regs.r_spd_ata_status;
    if ( (status_tmp & 0x80) )
    {
      res = ata_wait_busy1_busy();
      status_tmp = dev5_speed_regs.r_spd_ata_status;
    }
    if ( (status_tmp & 1) )
    {
      u8 Error; // $v0

      Error = sceAtaGetError();
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: cmd err 0x%02x, 0x%02x\n", status_tmp, Error);
      res = (Error & 0x80) ? -510 : -503;
    }
  }
  CancelAlarm(AtaAlarmrHandle, 0);
  speedLEDCtl(0);
  if ( res )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("DEV5 ATA: error: ATA failed, %d\n", res);
  }
  return res;
}
// 40A648: using guessed type int g_xatapi_verbose;
// 40A710: using guessed type ata_cmd_state_t atad_cmd_state;

//----- (004068B8) --------------------------------------------------------
int xatapi_6_sceAtaWaitResult(void)
{
  int restmp; // $s0
  iop_event_info_t efinfo; // [sp+10h] [-20h] BYREF

  if ( vReferEventFlagStatus(g_acmd_evfid, &efinfo) || (efinfo.currBits & 1) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceCdAtapiWaitResult Call Error\n");
    return -511;
  }
  restmp = sceAtaWaitResult();
  SetEventFlag(g_acmd_evfid, 1u);
  return restmp;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (0040694C) --------------------------------------------------------
int sceCdAtapiWaitResult_local(void)
{
  int res; // $s2
  int i; // $v1
  int intr_stat_msk; // [sp+10h] [-10h]
  u32 efbits; // [sp+14h] [-Ch] BYREF
  int padinfo; // [sp+18h] [-8h] BYREF

  res = 0;
  switch ( atad_cmd_state.type_atapi )
  {
    case 1:
    case 8:
      if ( g_xatapi_verbose > 0 )
        Kprintf("waitresult\n");
      WaitEventFlag(g_atapi_event_flag, 7u, 17, &efbits);
      if ( (efbits & 1) )
      {
        res = -502;
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: ata timedout while non data command\n");
      }
      if ( (efbits & 4) )
      {
        res = -550;
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: ata eject while non data command\n");
      }
      break;
    case 4:
    case 5:
    case 6:
      if ( g_xatapi_verbose > 0 )
        Kprintf("waitresult dma\n");
      if ( !g_reset_scrambling_pack )
      {
        res = DmaRun_atapi((char *)atad_cmd_state.buf_atapi, atad_cmd_state.blkcount_atapi, atad_cmd_state.blksize_atapi, atad_cmd_state.dir_atapi);
      }
      else if ( atad_cmd_state.dir_atapi )
      {
        int blktotal1; // $s3
        int blkoffs; // $s0

        blktotal1 = atad_cmd_state.blkcount_atapi * atad_cmd_state.blksize_atapi;
        for ( blkoffs = 0; blkoffs < blktotal1; blkoffs += atad_cmd_state.blkcount_atapi * atad_cmd_state.blksize_atapi )
        {
          int padres; // $v0

          padres = Mpeg2CheckPadding(
                     (char *)atad_cmd_state.buf_atapi + blkoffs,
                     blktotal1 - blkoffs,
                     &padinfo,
                     &g_pes_scrambling_control_pack);
          if ( padres < 0 )
          {
            res = DmaRun_atapi((char *)atad_cmd_state.buf_atapi, atad_cmd_state.blkcount_atapi, atad_cmd_state.blksize_atapi, atad_cmd_state.dir_atapi);
            break;
          }
          atad_cmd_state.blksize_atapi = 2048;
          atad_cmd_state.blkcount_atapi = padinfo;
          res = padres ? DmaRun_atapi_extrans1((char *)atad_cmd_state.buf_atapi + blkoffs, padinfo, 2048, atad_cmd_state.dir_atapi) : DmaRun_atapi((char *)atad_cmd_state.buf_atapi + blkoffs, padinfo, 2048, atad_cmd_state.dir_atapi);
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
      if ( res )
      {
        break;
      }
      intr_stat_msk = 0;
      for ( i = 0; i < 100 && !intr_stat_msk; i += 1 )
      {
        intr_stat_msk = dev5_speed_regs.r_spd_intr_stat & 1;
      }
      if ( intr_stat_msk )
      {
        break;
      }
      if ( g_xatapi_verbose > 0 )
        Kprintf("ata command not finished yet\n");
      speedIntrEnable(1);
      WaitEventFlag(g_atapi_event_flag, 7u, 17, &efbits);
      if ( (efbits & 1) )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: ata timedout, buffer stat %04x\n", dev5_speed_regs.r_spd_dbuf_stat);
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: istat %x, ienable %x\n", dev5_speed_regs.r_spd_intr_stat, dev5_speed_regs.r_spd_intr_mask);
        res = -502;
      }
      if ( (efbits & 4) )
      {
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: ata eject, buffer stat %04x\n", dev5_speed_regs.r_spd_dbuf_stat);
        if ( g_xatapi_verbose > 0 )
          Kprintf("DEV5 ATA: error: istat %x, ienable %x\n", dev5_speed_regs.r_spd_intr_stat, dev5_speed_regs.r_spd_intr_mask);
        res = -550;
      }
      break;
    default:
      res = IoRun_atapi(&atad_cmd_state);
      break;
  }
  if ( !res )
  {
    char ata_status_tmp; // [sp+10h] [-10h]

    ata_status_tmp = dev5_speed_regs.r_spd_ata_status;
    if ( (ata_status_tmp & 0x80) )
    {
      res = ata_wait_busy1_busy();
      ata_status_tmp = dev5_speed_regs.r_spd_ata_status;
    }
    if ( (ata_status_tmp & 1) )
    {
      u8 Error; // $v0

      Error = sceAtaGetError();
      if ( g_xatapi_verbose > 0 )
        Kprintf("DEV5 ATA: error: cmd status 0x%02x, error 0x%02x\n", ata_status_tmp, Error);
      res = (Error & 0x80) ? -510 : -503;
    }
  }
  CancelAlarm(AtaAlarmrHandle, 0);
  speedLEDCtl(0);
  if ( g_xatapi_verbose > 0 )
    Kprintf("sceCdAtapiWaitResult_local() End.\n");
  if ( res )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("DEV5 ATA: error: ATA failed, %d\n", res);
  }
  return res;
}
// 40A630: using guessed type int g_reset_scrambling_pack;
// 40A648: using guessed type int g_xatapi_verbose;
// 40A710: using guessed type ata_cmd_state_t atad_cmd_state;

//----- (00406E98) --------------------------------------------------------
int xatapi_8_sceCdAtapiWaitResult(void)
{
  int restmp; // $s0
  iop_event_info_t efinfo; // [sp+10h] [-20h] BYREF

  if ( vReferEventFlagStatus(g_acmd_evfid, &efinfo) || (efinfo.currBits & 1) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("sceCdAtapiWaitResult Call Error\n");
    return -511;
  }
  restmp = sceCdAtapiWaitResult_local();
  SetEventFlag(g_acmd_evfid, 1u);
  return restmp;
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
  if ( !(dev5_speed_regs.r_spd_if_ctrl & 0x40) )
    ata_bus_reset_inner();
  return ata_wait_busy2_busy();
}

//----- (00406FE0) --------------------------------------------------------
int xatapi_4_sceAtaSoftReset(void)
{
  if ( (dev5_speed_regs.r_spd_ata_control & 0x80) )
    return -501;
  dev5_speed_regs.r_spd_ata_control = 6;
  DelayThread(100);
  dev5_speed_regs.r_spd_ata_control = 2;
  DelayThread(3000);
  if ( g_xatapi_verbose > 0 )
    Kprintf("soft reset\n");
  return ata_wait_busy1_busy();
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (0040706C) --------------------------------------------------------
int sceAtaFlushCache(int device)
{
  int result; // $v0

  result = xatapi_5_sceAtaExecCmd(0, 1u, 0, 0, 0, 0, 0, device << 4, 0xE7u, 1u);
  return result ? result : xatapi_6_sceAtaWaitResult();
}

//----- (004070D0) --------------------------------------------------------
int ata_device_identify(int device, void *info)
{
  int result; // $v0

  result = xatapi_5_sceAtaExecCmd(info, 1u, 0, 0, 0, 0, 0, device << 4, 0xECu, 2u);
  return result ? result : xatapi_6_sceAtaWaitResult();
}

//----- (00407134) --------------------------------------------------------
int ata_device_pkt_identify(int device, void *info)
{
  int result; // $v0

  result = xatapi_5_sceAtaExecCmd(info, 1u, 0, 0, 0, 0, 0, device << 4, 0xA1u, 2u);
  return result ? result : xatapi_6_sceAtaWaitResult();
}

//----- (00407198) --------------------------------------------------------
int atapi_device_set_transfer_mode(int device, int type, int mode)
{
  int result; // $v0

  result = xatapi_5_sceAtaExecCmd(0, 1u, 3u, (u8)(mode | type), 0, 0, 0, device << 4, 0xEFu, 1u);
  if ( result )
    return result;
  result = xatapi_6_sceAtaWaitResult();
  if ( result )
    return result;
  switch ( type )
  {
    case 8:
      ata_pio_mode(mode);
      break;
    case 0x20:
      ata_multiword_dma_mode(mode);
      break;
    case 0x40:
      ata_ultra_dma_mode(mode);
      break;
    default:
      break;
  }
  return 0;
}

//----- (00407284) --------------------------------------------------------
int ata_device_set_transfer_mode(int device, int type, int mode)
{
  int result; // $v0

  result = sceAtaExecCmd(0, 1u, 3u, (u8)(mode | type), 0, 0, 0, device << 4, 0xEFu, 1u);
  if ( result )
    return result;
  result = sceAtaWaitResult();
  if ( result )
    return result;
  switch ( type )
  {
    case 8:
      ata_pio_mode(mode);
      break;
    case 32:
      ata_multiword_dma_mode(mode);
      break;
    case 64:
      ata_ultra_dma_mode(mode);
      break;
    default:
      break;
  }
  return 0;
}

//----- (00407370) --------------------------------------------------------
void ata_device_probe(ata_devinfo_t *devinfo)
{
  char r_spd_ata_lcyl; // $a1
  u8 r_spd_ata_hcyl; // $v1

  devinfo->exists = 0;
  devinfo->has_packet = 2;
  if ( (dev5_speed_regs.r_spd_ata_control & 0x88) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("FindDev ATA_BUSY\n");
    return;
  }
  r_spd_ata_lcyl = dev5_speed_regs.r_spd_ata_lcyl;
  r_spd_ata_hcyl = dev5_speed_regs.r_spd_ata_hcyl;
  if ( dev5_speed_regs.r_spd_ata_nsector != 1 || dev5_speed_regs.r_spd_ata_sector != 1 )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("FindDev ATA_NOT_CONNECT\n");
    return;
  }
  devinfo->exists = 1;
  if ( !r_spd_ata_lcyl && !r_spd_ata_hcyl )
    devinfo->has_packet = 0;
  if ( r_spd_ata_lcyl == 20 && r_spd_ata_hcyl == 235 )
    devinfo->has_packet = 1;
  dev5_speed_regs.r_spd_ata_lcyl = 85;
  dev5_speed_regs.r_spd_ata_hcyl = 170;
  // Unofficial: was 8 bit access
  if ( (dev5_speed_regs.r_spd_ata_lcyl & 0xFF) != 85 || (dev5_speed_regs.r_spd_ata_hcyl & 0xFF) != 170 )
    devinfo->exists = 0;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004074C8) --------------------------------------------------------
void atapi_device_set_transfer_mode_outer(int device)
{
  if ( g_dma_mode_value )
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("UDMA_mode Mode%d\n", 2);
    while ( atapi_device_set_transfer_mode(device, 64, (u8)g_dma_speed_value) < 0 )
    {
      DelayThread(2000000);
    }
  }
  else
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("MDMA_mode Mode%d\n", 2);
    while ( atapi_device_set_transfer_mode(device, 32, (u8)g_dma_speed_value) < 0 )
    {
      DelayThread(2000000);
    }
  }
}
// 40A638: using guessed type int g_dma_mode_value;
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407594) --------------------------------------------------------
void ata_device_set_transfer_mode_outer(int device)
{
  int i; // $s0

  if ( g_dma_mode_value )
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("UDMA_mode Mode%d\n", 2);
    for ( i = 0; i < 3 && ata_device_set_transfer_mode(device, 64, (u8)g_dma_speed_value); i += 1 )
    {
      DelayThread(2000000);
    }
  }
  else
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("MDMA_mode Mode%d\n", 2);
    for ( i = 0; i < 3 && ata_device_set_transfer_mode(device, 32, (u8)g_dma_speed_value); i += 1 )
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
  int i; // $s1

  if ( xatapi_4_sceAtaSoftReset() )
    return;
  ata_device_probe(&devinfo[0]);
  if ( !devinfo[0].exists )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("DEV5 ATA: error: there is no device0\n");
    devinfo[1].exists = 0;
    return;
  }
  if ( ata_device_select(1) )
    return;
  // Unofficial: was 8 bit access
  if ( (dev5_speed_regs.r_spd_ata_control & 0xFF) )
    ata_device_probe(&devinfo[1]);
  else
    devinfo[1].exists = 0;
  ata_pio_mode(0);
  g_is_in_read_info = 0;
  for ( i = 0; i < 2; i += 1 )
  {
    if ( !devinfo[i].exists )
    {
      continue;
    }
    if ( !devinfo[i].has_packet )
    {
      devinfo[i].exists = !ata_device_identify(i, ata_param);
    }
    if ( devinfo[i].has_packet == 1 )
      devinfo[i].exists = !ata_device_pkt_identify(i, ata_param);
    if ( g_xatapi_verbose > 0 )
      Kprintf("device%d connected, kind %d.\n", i, devinfo[i].has_packet);
    if ( !devinfo[i].exists || devinfo[i].has_packet != 1 )
    {
      continue;
    }
    do_hex_dump(ata_param, sizeof(ata_param));
    devinfo[i].lba48 = !do_atapi_cmd_inquiry_12h(i);
    if ( devinfo[i].lba48 )
    {
      g_is_in_read_info = 1;
      if ( g_xatapi_verbose >= 0 )
        Kprintf("Atapi Program Aria Brokun.\n");
      continue;
    }
    atapi_device_set_transfer_mode_outer(i);
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
    }
  }
  if ( g_atapi_event_flag >= 0 )
    DeleteEventFlag(g_atapi_event_flag);
  if ( g_acmd_evfid >= 0 )
    DeleteEventFlag(g_acmd_evfid);
  if ( g_adma_evfid >= 0 )
    DeleteEventFlag(g_adma_evfid);
  return 0;
}

//----- (00407B20) --------------------------------------------------------
void FpgaLayer1On(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_LAYER1 %x\n", "FpgaLayer1On", dev5_fpga_regs.r_fpga_layer1);
  dev5_fpga_regs.r_fpga_layer1 &= 0xFFFE;
  dev5_fpga_regs.r_fpga_layer1 |= 1;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_LAYER1 %x\n", "FpgaLayer1On", dev5_fpga_regs.r_fpga_layer1);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407BC4) --------------------------------------------------------
void FpgaLayer1Off(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_LAYER1 %x\n", "FpgaLayer1Off", dev5_fpga_regs.r_fpga_layer1);
  dev5_fpga_regs.r_fpga_layer1 &= 0xFFFE;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_LAYER1 %x\n", "FpgaLayer1Off", dev5_fpga_regs.r_fpga_layer1);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407C54) --------------------------------------------------------
void FpgaLayer2On(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_LAYER2 %x\n", "FpgaLayer2On", dev5_fpga_regs.r_fpga_layer2);
  dev5_fpga_regs.r_fpga_layer2 &= 0xFFFE;
  dev5_fpga_regs.r_fpga_layer2 |= 1;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_LAYER2 %x\n", "FpgaLayer2On", dev5_fpga_regs.r_fpga_layer2);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407CF8) --------------------------------------------------------
void FpgaLayer2Off(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_LAYER2 %x\n", "FpgaLayer2Off", dev5_fpga_regs.r_fpga_layer2);
  dev5_fpga_regs.r_fpga_layer2 &= 0xFFFE;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_LAYER2 %x\n", "FpgaLayer2Off", dev5_fpga_regs.r_fpga_layer2);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407D88) --------------------------------------------------------
void FpgaXfrenOn(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_XFREN %x\n", "FpgaXfrenOn", dev5_fpga_regs.r_fpga_xfren);
  dev5_fpga_regs.r_fpga_xfren &= 0xFFFE;
  dev5_fpga_regs.r_fpga_xfren |= 1;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_XFREN %x\n", "FpgaXfrenOn", dev5_fpga_regs.r_fpga_xfren);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407E2C) --------------------------------------------------------
void FpgaXfrenOff(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_XFREN %x\n", "FpgaXfrenOff", dev5_fpga_regs.r_fpga_xfren);
  dev5_fpga_regs.r_fpga_xfren &= 0xFFFE;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_XFREN %x\n", "FpgaXfrenOff", dev5_fpga_regs.r_fpga_xfren);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407EBC) --------------------------------------------------------
void FpgaSpckmodeOn(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_SPCKMODE %x\n", "FpgaSpckmodeOn", dev5_fpga_regs.r_fpga_unk32);
  dev5_fpga_regs.r_fpga_unk32 &= 0xFFFE;
  dev5_fpga_regs.r_fpga_unk32 |= 1;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_SPCKMODE %x\n", "FpgaSpckmodeOn", dev5_fpga_regs.r_fpga_unk32);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407F60) --------------------------------------------------------
void FpgaSpckmodeOff(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_SPCKMODE %x\n", "FpgaSpckmodeOff", dev5_fpga_regs.r_fpga_unk32);
  dev5_fpga_regs.r_fpga_unk32 &= 0xFFFE;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_SPCKMODE %x\n", "FpgaSpckmodeOff", dev5_fpga_regs.r_fpga_unk32);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00407FF0) --------------------------------------------------------
void FpgaXfdir(int dir)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_XFRDIR %x\n", "FpgaXfrdir", dev5_fpga_regs.r_fpga_xfrdir);
  dev5_fpga_regs.r_fpga_xfrdir &= 0xFFFE;
  if ( dir )
  {
    dev5_fpga_regs.r_fpga_xfrdir |= 1;
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_XFRDIR %x\n", "FpgaXfrdir", dev5_fpga_regs.r_fpga_xfrdir);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004080CC) --------------------------------------------------------
int FpgaGetRevision(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():FPGA_REVISION %x\n", "FpgaGetRevision", dev5_fpga_regs.r_fpga_revision);
  return (u16)dev5_fpga_regs.r_fpga_revision;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00408120) --------------------------------------------------------
unsigned int do_fpga_add_unused8120(void)
{
  return (dev5_fpga_regs.r_fpga_sl3bufd + (unsigned int)dev5_fpga_regs.r_fpga_exbufd) >> 7;
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

  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():in ...\n", "FpgaCheckWriteBuffer");
  for ( i = 0; i < 10000 && (dev5_fpga_regs.r_fpga_exbufe || dev5_fpga_regs.r_fpga_sl3bufe); i += 1 );
  if ( i == 10000 )
  {
    if ( g_xatapi_verbose >= 0 )
      Kprintf("exbuf enc=%x, sl3buf enc=%x\n", dev5_fpga_regs.r_fpga_exbufe, dev5_fpga_regs.r_fpga_sl3bufe);
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():out ...\n", "FpgaCheckWriteBuffer");
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00408250) --------------------------------------------------------
void FpgaCheckWriteBuffer2(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():in ...\n", "FpgaCheckWriteBuffer2");
  while ( dev5_fpga_regs.r_fpga_sl3bufd )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("%s():FPGA_SL3BUFD %x\n", "FpgaCheckWriteBuffer2", dev5_fpga_regs.r_fpga_sl3bufd);
    if ( g_xatapi_verbose > 0 )
      Kprintf("%s():FPGA_SL3BUFE %x\n", "FpgaCheckWriteBuffer2", dev5_fpga_regs.r_fpga_sl3bufe);
    if ( g_xatapi_verbose > 0 )
      Kprintf("%s():FPGA_EXBUFD %x\n", "FpgaCheckWriteBuffer2", dev5_fpga_regs.r_fpga_exbufd);
    if ( g_xatapi_verbose > 0 )
      Kprintf("%s():FPGA_EXBUFE %x\n", "FpgaCheckWriteBuffer2", dev5_fpga_regs.r_fpga_exbufe);
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():out ...\n", "FpgaCheckWriteBuffer2");
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (004083C8) --------------------------------------------------------
void FpgaClearBuffer(void)
{
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_SL3BUFD %x\n", "FpgaClearBuffer", dev5_fpga_regs.r_fpga_sl3bufd);
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_SL3BUFE %x\n", "FpgaClearBuffer", dev5_fpga_regs.r_fpga_sl3bufe);
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_EXBUFD %x\n", "FpgaClearBuffer", dev5_fpga_regs.r_fpga_exbufd);
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():old:FPGA_EXBUFE %x\n", "FpgaClearBuffer", dev5_fpga_regs.r_fpga_exbufe);
  dev5_fpga_regs.r_fpga_unk30 &= 0xFFFE;
  dev5_fpga_regs.r_fpga_unk30 |= 1;
  while ( (u16)(dev5_fpga_regs.r_fpga_exbufd) || dev5_fpga_regs.r_fpga_sl3bufd );
  while ( dev5_fpga_regs.r_fpga_exbufe || dev5_fpga_regs.r_fpga_sl3bufe );
  dev5_fpga_regs.r_fpga_unk30 &= 0xFFFE;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_SL3BUFD %x\n", "FpgaClearBuffer", dev5_fpga_regs.r_fpga_sl3bufd);
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_SL3BUFE %x\n", "FpgaClearBuffer", dev5_fpga_regs.r_fpga_sl3bufe);
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_EXBUFD %x\n", "FpgaClearBuffer", dev5_fpga_regs.r_fpga_exbufd);
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():new:FPGA_EXBUFE %x\n", "FpgaClearBuffer", dev5_fpga_regs.r_fpga_exbufe);
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00408600) --------------------------------------------------------
int Mpeg2CheckPadding(char *buf, unsigned int bufsize, int *retptr, int *pesscramblingpackptr)
{
  int bufchk; // $s0
  char *bufoffs1; // $a0
  const char *bufoffs2; // $v1
  int i; // $v0

  bufchk = 0;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():in\n", "Mpeg2CheckPadding");
  if ( (bufsize & 0x7FF) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("%s():Buffer size not aligne !!\n", "Mpeg2CheckPadding");
    return -1;
  }
  if ( !*buf && !buf[1] && buf[2] == 1 && (u8)buf[3] == 0xBA )
    bufchk = 1;
  for ( i = 0; (unsigned int)i < (bufsize >> 11); i += 1 )
  {
    bufoffs1 = &buf[i << 11];
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
          && (bufoffs2[6] & 0x60) )
        {
          ++*pesscramblingpackptr;
        }
      }
    }
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():out %d %s Pack\n", "Mpeg2CheckPadding", i, bufchk ? "RDI" : "NULL");
  *retptr = i;
  return bufchk;
}
// 40A648: using guessed type int g_xatapi_verbose;

//----- (00408884) --------------------------------------------------------
int Mpeg2CheckScramble(char *buf, unsigned int bufsize)
{
  int restmp; // $s1
  signed int i; // $a2
  char *bufcur; // $a0
  const char *bufbuf; // $v1
  int buf3; // $v0

  restmp = 0;
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():in\n", "Mpeg2CheckScramble");
  if ( (bufsize & 0x7FF) )
  {
    if ( g_xatapi_verbose > 0 )
      Kprintf("%s():Buffer size not aligne !!\n", "Mpeg2CheckScramble");
    return 0;
  }
  for ( i = 0; i < (int)(bufsize >> 11); i += 1 )
  {
    bufcur = buf + (i << 11);
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
          if ( (buf3 == 0xE0 || buf3 == 0xBD || buf3 == 0xC0 || buf3 == 0xD0) && (bufbuf[6] & 0x30) )
          {
            restmp = 0xFFFFFFFF;
            break;
          }
        }
      }
    }
  }
  if ( g_xatapi_verbose > 0 )
    Kprintf("%s():out\n", "Mpeg2CheckScramble");
  return restmp;
}
// 40A648: using guessed type int g_xatapi_verbose;
