
#define __CDVDMAN_ALL__

#ifdef __CDVDMAN_ALL__
#define __CDVDMAN_BB_NAV__
#define __CDVDMAN_BIOS__
#define __CDVDMAN_NEWBIOS__
#endif


#ifdef __CDVDMAN_NEWBIOS__
#ifndef __CDVDMAN_BIOS__
#define __CDVDMAN_BIOS__
#endif
#endif

#ifdef __CDVDMAN_BB_NAV__
#ifndef __CDVDMAN_SW_E19__
#define __CDVDMAN_SW_E19__
#endif
#ifndef __CDVDMAN_SW_E20__
#define __CDVDMAN_SW_E20__
#endif
#ifndef __CDVDMAN_SW_E35__
#define __CDVDMAN_SW_E35__
#endif
#ifndef __CDVDMAN_SW_E36__
#define __CDVDMAN_SW_E36__
#endif
#ifndef __CDVDMAN_SW_E90__
#define __CDVDMAN_SW_E90__
#endif
#endif

#ifdef __CDVDMAN_BIOS__
#ifndef __CDVDMAN_SW_E19__
#define __CDVDMAN_SW_E19__
#endif
#ifndef __CDVDMAN_SW_E20__
#define __CDVDMAN_SW_E20__
#endif
#ifndef __CDVDMAN_SW_E35__
#define __CDVDMAN_SW_E35__
#endif
#ifndef __CDVDMAN_SW_E36__
#define __CDVDMAN_SW_E36__
#endif
#ifndef __CDVDMAN_SW_E66__
#define __CDVDMAN_SW_E66__
#endif
#endif

#include <tamtypes.h>
#include <cdvdman.h>
#include <xloadcore.h>
#include <thbase.h>
#include <dmacman.h>
#include <intrman.h>
#include <thevent.h>
#include <sysmem.h>
#include <sysclib.h>
#include <stdio.h>
#include <ioman.h>

/* Sizes of internal buffers */
#if 0
#define FSVR_BUFFER_SIZE 2340  /* Minimum size */
#define TOC_BUFFSIZE     21068 /* Real size unknown */
#endif

/* C/DVD N-Commands */
#define CDVD_NCMD_NOP      0x0
#define CDVD_NCMD_NOP1     0x1
#define CDVD_NCMD_STANDBY  0x2
#define CDVD_NCMD_STOP     0x3
#define CDVD_NCMD_PAUSE    0x4
#define CDVD_NCMD_SEEK     0x5
#define CDVD_NCMD_READ     0x6
#define CDVD_NCMD_READFULL 0x7
#define CDVD_NCMD_DVDREAD  0x8
#define CDVD_NCMD_GETTOC   0x9

/* IOP interrupt handler types */
#define HTYPE_C 0x1

/* PS2 C/DVD hardware registers */
#define CDVDreg_NCOMMAND (*(volatile u8 *)0xBF402004)
#define CDVDreg_READY    (*(volatile u8 *)0xBF402005)
#define CDVDreg_NDATAIN  (*(volatile u8 *)0xBF402005)
#define CDVDreg_ERROR    (*(volatile u8 *)0xBF402006)
#define CDVDreg_HOWTO    (*(volatile u8 *)0xBF402006)
#define CDVDreg_ABORT    (*(volatile u8 *)0xBF402007)
#define CDVDreg_PWOFF    (*(volatile u8 *)0xBF402008)
#define CDVDreg_9        (*(volatile u8 *)0xBF402008)
#define CDVDreg_STATUS   (*(volatile u8 *)0xBF40200A)
#define CDVDreg_B        (*(volatile u8 *)0xBF40200B)
#define CDVDreg_C        (*(volatile u8 *)0xBF40200C)
#define CDVDreg_D        (*(volatile u8 *)0xBF40200D)
#define CDVDreg_E        (*(volatile u8 *)0xBF40200E)
#define CDVDreg_TYPE     (*(volatile u8 *)0xBF40200F)
#define CDVDreg_13       (*(volatile u8 *)0xBF402013)
#define CDVDreg_15       (*(volatile u8 *)0xBF402015)
#define CDVDreg_SCOMMAND (*(volatile u8 *)0xBF402016)
#define CDVDreg_SDATAIN  (*(volatile u8 *)0xBF402017)
#define CDVDreg_SDATAOUT (*(volatile u8 *)0xBF402018)
#define CDVDreg_KEYSTATE (*(volatile u8 *)0xBF402038)
#define CDVDreg_KEYXOR   (*(volatile u8 *)0xBF402039)
#define CDVDreg_DEC      (*(volatile u8 *)0xBF40203A)

/* Bits for CDVDreg_SDATAIN register (read) */
/*
 0x20 - set when there is no data to read in CDVDreg_SDATAOUT register (?) (s-cmd send #2)
 0x40 - set when there is no data to read in CDVDreg_SDATAOUT register (?) (standard)
 0x80 - set when processing S-Command (?)
 */

/* Misc */
#define TOC_BUFFSIZE 2064 /* Probably wrong size */

int cdrom_init(iop_device_t *);
int cdrom_deinit(iop_device_t *);
int cdrom_nulldev(iop_file_t *nuldev, ...);
s64 cdrom_nulldev64(iop_file_t *nuldev, ...);

/*
 INTR Event Flag:
 0x01 - set when n-cmd is complete, clear before n-cmd sent, used by sceCdSync()
 0x04 - set by CDROM interrupt handler, used by CDVDFSV to trigger a Power-Off callback on EE
 0x08 - set by CDVDSTM module, set by cdvdman_intrcall()
 0x10 - set by CDROM interrupt handler, user by FILEIO to trigger a Power-Off callback on EE
 0x20 - set by DMA Ch.3 handler when transfer is complete, clear before DMA Ch.3 transfer start
 */

/* internal structure (size: 14h bytes) */
typedef struct _DMA3PARAM
{
    u16 dma3_blkwords;
    u16 dma3_blkcount;
    void *dma3_maddress;
    int (*dma3_callback)(void *);
    u16 dma3_csectors;
    u16 cdvdreg_howto;
    u32 dma3_msectors;
} DMA3PARAM;

/* cdvdman RODATA segment */

#define cdvdman_cdrom "cdrom"

#define cdvdman_sect_p0 2048
#define cdvdman_sect_p1 2328
#define cdvdman_sect_p2 2340

/* cdvdman DATA segment */

extern struct irx_export_table _exp_cdvdman;

extern iop_device_ops_t cdvdman_cdops;

extern iop_device_t cdvdman_cddev;

extern int cdvdman_clk_flg;
extern u32 cdvdman_cd36key;
extern int cdvdman_ee_ncmd;
extern int cdvdman_mmode;
extern int cdvdman_brkfunc;
extern int cdvdman_minver10700;
extern int cdvdman_minver20200;
extern int cdvdman_minver20400;
extern int cdvdman_minver20800;
extern u8 cdvdman_ncmd;
extern int cdvdman_chmedia;
extern int cdvdman_chflags[4];
extern int cdvdman_rtindex;
extern int cdvdman_retries;
/* Timeouts (default values) */
extern int cdvdman_sync_to;
extern int TimeOut2;


extern int cdvdman_verbose;

/* cdvdman SBSS segment */

extern u8 *cdvdman_ptoc;
extern int cdvdman_scmd_ef;
#if 0
extern char *cdvdman_pb_fsvr;
#endif
extern int cdvdman_ncmd_ef;
extern int cdvdman_read_ef;
extern int cdvdman_intr_ef;

extern sceCdCBFunc cdvdman_user_cb;
extern void *cdvdman_poffarg;
extern void (*cdvdman_cdstm0cb)(int);

extern sceCdCLOCK cdvdman_clock;
extern void (*cdvdman_poff_cb)(void *);
extern void (*cdvdman_cdstm1cb)(int);
extern int cdvdman_cmdfunc;

extern u32 cdvdman_readptr;

extern iop_sys_clock_t cdvdman_racb_to;
extern iop_sys_clock_t cdvdman_ncmd_to;
extern void *cdvdman_readbuf;

extern iop_sys_clock_t cdvdman_poff_to;

#if 0
extern char cdvdman_fsvrbuf[FSVR_BUFFER_SIZE];
#endif
extern u8 toc_buffer[TOC_BUFFSIZE];

/* The data below is a very big (0xC0 bytes or even bigger) internal structure */
extern u8 cdvdman_command;
extern u8 cdvdman_cderror;
extern u8 cdvdman_unused1;
extern u8 cdvdman_unused2;
extern int cdvdman_waf;
extern int cdvdman_thrd_id;
extern int cdvdman_strm_id;
extern int cdvdman_read2_flg;
extern u32 cdvdman_readlsn;
extern void *cdvdman_rbuffer;
extern u32 cdvdman_nsec;
extern u32 cdvdman_csec;
extern u32 cdvdman_rdsectc;
extern u32 cdvdman_pattern;
extern sceCdRMode cdvdman_cdrmode;
extern u32 cdvdman_recstat;
extern u32 cdvdman_dvdflag;
extern u32 cdvdman_rd_lsn;
extern void *cdvdman_rd_buf;
extern u32 cdvdman_rd_sec;
extern sceCdRMode cdvdman_rdmode;
extern u32 cdvdman_unk1;
extern u32 cdvdman_dintrlsn;
extern void *cdvdman_read_cb;
extern u32 cdvdman_rdchunk;
/* s-cmd related stuff & some unknown variables here*/
extern char cdvdman_scmd_flg;
extern char cdvdman_scmd;
extern int cdvdman_sdlen;
extern char cdvdman_rdlen;
extern char cdvdman_scmd_sd[0x10];
extern char cdvdman_scmd_rd[0x10];
extern u32 cdvdman_syncerr;
extern int cdvdman_read_to;
extern u32 cdvdman_pwr_flg;
extern u32 cdvdman_layer1;
extern u8 cdvdman_usetoc;
extern u8 cdvdman_dldvd;
extern DMA3PARAM cdvdman_dma3prm;
extern u32 cdvdman_dma3sec;
extern int cdvdman_dr_flg;
extern u16 cdvdman_unk2;
extern u16 cdvdman_unk3;
extern int cdvdman_waf2;

#define DPRINTF(...)

// cdvdmans
extern int set_alarm(iop_sys_clock_t *clock, unsigned int (*handler)(void *), void *common);
extern int cancel_alarm(unsigned int (*handler)(void *), void *common);
extern int clear_ev_flag(int evfid, u32 bitpattern);
extern int set_ev_flag(int evfid, u32 bitpattern);
extern int refer_ef_status(int evfid, iop_event_info_t *info);
extern int delay_thread(u32 usec);

// cdvdmanc
extern int cdvdman_initcfg();
extern int cdvdman_intr_cb(void *common);
extern int DvdDual_infochk();
extern void cdvdman_init();
extern int cdvdman_send_scmd(int cmd, const void *sdata, int sdlen, void *rdata, int rdlen, int check_sef);
extern void cdvdman_write_scmd(void *common);
extern int cdvdman_send_ncmd(int ncmd, const void *ndata, int ndlen, int func, DMA3PARAM *b18, int check_cb);
extern int cdvdman_mediactl(int code);
extern int cdvdman_readtoc(u8 *toc, int param, int func);
extern int cdvdman_gettoc(u8 *toc);
extern int cdvdman_speedctl(u32 spindlctrl, int dvdflag, u32 maxlsn);
extern int cdvdman_isdvd();
extern int cdvdman_read(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int decflag, int shift);
extern void Read2intrCDVD(int read2_flag);
extern int cdvdman_readfull(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int flag);
extern int cdvdman_send_scmd2(int cmd, const void *sdata, int sdlen, void *rdata, int rdlen, int check_sef);
extern int sceCdRead0_Rty(u32 lsn, u32 nsec, void *buf, sceCdRMode *mode, int ncmd, int dintrsec, void *func);
extern int intrh_dma_3(void *common);
extern u32 sceCdLsnDualChg(u32 lsn);

extern void break_read_timeout_callback(void);
