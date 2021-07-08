
#define __CDVDMAN_ALL__


#ifdef __CDVDMAN_NEWBIOS__
#ifndef __CDVDMAN_BIOS__
#define __CDVDMAN_BIOS__
#endif
#endif

#ifdef __CDVDMAN_ALL__
#define __CDVDMAN_BB_NAV__
#define __CDVDMAN_BIOS__
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
#include <iomanX.h>

#include "cdvdstm.h"

/* Sizes of internal buffers */
#define FSVR_BUFFER_SIZE 2340  /* Minimum size */
#define TOC_BUFFSIZE     21068 /* Real size unknown */

/* For sceCdInit() */
#define SCECdINIT 0x0
#define SCECdEXIT 0x5

/* IOP logical device attributes */
#define IOP_DT_FS    0x10
#define IOP_DT_FSEXT 0x10000000


#if 0
#define EA_SINGLE 0x0
#define EA_MULTI  0x2
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
/* #define CDVD_NCMD_???         0xB - ndata[1], nodma3 */
/* #define CDVD_NCMD_???         0xC - used in cdvdman_35() */
/* #define CDVD_NCMD_READ???     0xE - supposed to be similar to CDVD_NCMD_READFULL in some way - used by cdvdman_76() */

/* C/DVD Func */
#define SCECdFuncRead     1
#define SCECdFuncReadCDDA 2
#define SCECdFuncGetToc   3
#define SCECdFuncSeek     4
#define SCECdFuncStandby  5
#define SCECdFuncStop     6
#define SCECdFuncPause    7
#define SCECdFuncBreak    8


/* IOP interrupt numbers */
#define INUM_CDROM 0x2
#define INUM_DMA_3 0x23

/* IOP interrupt handler types */
#define HTYPE_C 0x1

/* DMA Ch Cr flags */
#define DMAf_CO 0x00000200
#define DMAf_TR 0x01000000


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

#define CdlDataReady  0x1
#define CdlCdComplete 0x2
#define CdlDataEnd    0x4
#define SCECdNotReady 0x6


/* Misc */
#if 0
#define TOC_BUFFSIZE 2064 /* Probably wrong size */
#endif

/* For event flags */
#define EF_WAIT_AND   0x00
#define EF_WAIT_OR    0x01
#define EF_WAIT_CLEAR 0x10


/* CDVDMAN tray control commands */
#define SCECdTrayOpen  0x0
#define SCECdTrayClose 0x1
#define SCECdTrayCheck 0x2

/* CDVDMAN Error Codes */
#define SCECdErNO      0x00
#define SCECdErABRT    0x01
#define SCECdErCMD     0x10
#define SCECdErOPENS   0x11
#define SCECdErNODISC  0x12
#define SCECdErNORDY   0x13
#define SCECdErCUD     0x14
#define SCECdErIPI     0x20
#define SCECdErILI     0x21
#define SCECdErPRM     0x22
#define SCECdErREAD    0x30
#define SCECdErTRMOPN  0x31
#define SCECdErEOM     0x32
#define SCECdErSFRMTNG 0x38
#define SCECdErREADCF  0xFD
#define SCECdErREADCFR 0xFE

/* file open modes */
#define SCE_CdCACHE  0x10000000
#define SCE_CdSTREAM 0x40000000

/* for "cdrom" devctl */
#define CDIOC_READCLOCK       0x430C
#define CDIOC_GETDISKTYP      0x431F
#define CDIOC_GETERROR        0x4320
#define CDIOC_TRAYREQ         0x4321
#define CDIOC_STATUS          0x4322
#define CDIOC_POWEROFF        0x4323
#define CDIOC_MMODE           0x4324
#define CDIOC_DISKRDY         0x4325
#define CDIOC_STREAMINIT      0x4327
#define CDIOC_BREAK           0x4328
#define CDIOC_SPINNOM         0x4380
#define CDIOC_SPINSTM         0x4381
#define CDIOC_TRYCNT          0x4382
#define CDIOC_SEEK            0x4383
#define CDIOC_STANDBY         0x4384
#define CDIOC_STOP            0x4385
#define CDIOC_PAUSE           0x4386
#define CDIOC_GETTOC          0x4387
#define CDIOC_SETTIMEOUT      0x4388
#define CDIOC_READDVDDUALINFO 0x4389
#define CDIOC_INIT            0x438A
#define CDIOC_APPLYSCMD       0x4392
#define CDIOC_FSCACHEINIT     0x4395
#define CDIOC_FSCACHEDELETE   0x4397

/* for "cdrom" ioctl2 */
#define CIOCSTREAMPAUSE  0x630D
#define CIOCSTREAMRESUME 0x630E
#define CIOCSTREAMSTAT   0x630F

#if 0
typedef struct
{
    const char *name;
    const u16 version;
} ModuleInfo;
#endif


#if 0
/* IOP device structures */
struct _iop_device_ops;

typedef struct _iop_device
{
    const char *name;
    u32 type;
    u32 version;
    const char *desc;
    struct _iop_device_ops *ops;
} iop_device;

typedef struct _iop_file
{
    u32 mode;
    u32 unit;
    iop_device *pdev;
    void *data;
} iop_file;
#endif

#if 0
typedef struct _iop_device_ops
{
    int (*init)();
    int (*deinit)();
    int (*format)(iop_file *, const char *, const char *, void *, int);
    int (*open)(iop_file *, const char *, int, ...);
    int (*close)(iop_file *);
    int (*read)(iop_file *, void *, int);
    int (*write)(iop_file *, void *, int);
    int (*lseek)(iop_file *, unsigned long, int);
    int (*ioctl)(iop_file *, unsigned long, void *);
    int (*remove)(iop_file *, const char *);
    int (*mkdir)(iop_file *, const char *, int);
    int (*rmdir)(iop_file *, const char *);
    int (*dopen)(iop_file *, const char *);
    int (*dclose)(iop_file *);
    int (*dread)(iop_file *, void *);
    int (*getstat)(iop_file *, const char *, void *);
    int (*chstat)(iop_file *, const char *, void *, u32);
    int (*rename)(iop_file *, const char *, const char *);
    int (*chdir)(iop_file *, const char *);
    int (*sync)(iop_file *, const char *, int);
    int (*mount)(iop_file *, const char *, const char *, int, void *, u32);
    int (*umount)(iop_file *, const char *);
    int (*lseek64)(iop_file *, s64, int);
    int (*devctl)(iop_file *, const char *, int, void *, u32, void *, u32);
    int (*symlink)(iop_file *, const char *, const char *);
    int (*readlink)(iop_file *, const char *, char *, u32);
    int (*ioctl2)(iop_file *, int, void *, u32, void *, u32);
} iop_device_ops;
#endif


int cdrom_init(iop_device_t *);
int cdrom_deinit(iop_device_t *);
int cdrom_open(iop_file_t *, const char *, int, int);
int cdrom_close(iop_file_t *);
int cdrom_read(iop_file_t *, void *, int);
int cdrom_lseek(iop_file_t *, int, int);
int cdrom_ioctl(iop_file_t *, int, void *);
int cdrom_dopen(iop_file_t *, const char *);
int cdrom_dread(iop_file_t *, iox_dirent_t *);
int cdrom_getstat(iop_file_t *, const char *, iox_stat_t *);
int cdrom_ioctl2(iop_file_t *, int, void *, size_t, void *, size_t);
int cdrom_devctl(iop_file_t *, const char *, int, void *, unsigned int, void *, unsigned int);
int cdrom_nulldev(iop_file_t *nuldev, ...);
s64 cdrom_nulldev64(iop_file_t *nuldev, ...);


#if 0
typedef struct
{
    u8 trycount;
    u8 spindlctrl;
    u8 datapattern;
    u8 pad;
} sceCdRMode;


typedef struct
{
    u8 stat;
    u8 second;
    u8 minute;
    u8 hour;
    u8 pad;
    u8 day;
    u8 month;
    u8 year;
} sceCdCLOCK;
#endif

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


#if 0
typedef struct _sceCdlFILE
{
    u32 lsn;
    u32 size;
    char name[16];
    u8 date[8];
    u32 flag;
} sceCdlFILE;
#endif

/* Internal structure (size: 30h bytes) */
typedef struct _CDVDMAN_FILEDATA
{
    u32 file_lsn; /* LSN of file on disc */
    u32 read_pos; /* current position in file */
    u32 filesize; /* size of file */
    u32 filemode;
    int fd_flags;           /* Handle flags: 01h - valid, 04h - cached, 08h - streamed */
    int fd_layer;           /* Device unit - layer of DL DVD */
    int fd_cf_fd;           /* Descriptor of cache file */
    void *fd_rcvbuf;        /* buffer */
    u32 fd_rbsize; /* size of rcvbuf */
    void *unk1;
    void *unk2;
    int *unk3;
} CDVDMAN_FILEDATA;

#if 0
typedef struct _sceCdlLOCCD
{
    u8 minute;
    u8 second;
    u8 sector;
    u8 track;
} sceCdlLOCCD;
#endif

#define SCE_CST_MODE 0x01
#define SCE_CST_ATTR 0x02
#define SCE_CST_SIZE 0x04
#define SCE_CST_CT   0x08
#define SCE_CST_AT   0x10
#define SCE_CST_MT   0x20
#define SCE_CST_PRVT 0x40

#define SCE_STM_R 0x01
#define SCE_STM_W 0x02
#define SCE_STM_X 0x04
#define SCE_STM_C 0x08
#define SCE_STM_F 0x10
#define SCE_STM_D 0x20

struct sce_stat
{
    u32 st_mode;
    u32 st_attr;
    u32 st_size;
    u8 st_ctime[8];
    u8 st_atime[8];
    u8 st_mtime[8];
    u32 st_hisize;
    u32 st_private[6];
};

struct sce_dirent
{
    struct sce_stat d_stat;
    char d_name[256];
    void *d_private;
};


#if 0
#define CdlMAXFILE  0x40
#define CdlMAXDIR   0x80
#define CdlMAXLEVEL 0x08
#endif

typedef struct _CD_DIR_ENTRY
{
    int number;
    int parent;
    int extent;
    char name[0x20];
} CD_DIR_ENTRY;

#define SMEM_High 0x01


#define PIOCALLOC 0x7001


#define VAR_int(x)    0
//*(int *)((char *)common + ((char *)&x - (char *)&cdvdman_commmand))
#define VAR_void(x)   0
//*(void **)((char *)common + ((char *)&x - (char *)&cdvdman_commmand))
#define VAR_ushort(x) 0
//*(u16 *)((char *)common + ((char *)&x - (char *)&cdvdman_commmand))
#define VAR_uchar(x)  0
//*(u8 *)((char *)common + ((char *)&x - (char *)&cdvdman_commmand))

/* cdvdman RODATA segment */

#define cdvdman_cdrom "cdrom"

#define cdvdman_rootdir "\\."

#define cdvdman_sect_p0 2048
#define cdvdman_sect_p1 2328
#define cdvdman_sect_p2 2340

#define cdvdman_stmdev "cdrom_stm0:"

/* cdvdman DATA segment */

extern struct irx_export_table _exp_cdvdman;

extern char cdvdman_cachedir[0x100];
extern u32 cdvdman_rcvbsec;
extern int cdvdman_srchspd;
extern int cdvdman_spinctl;
extern int cdvdman_spinnom;
extern int cdvdman_trycnt;
extern int cdvdman_iocache;
extern int cdvdman_ioc_lsn;
extern int cdvdman_ioc_sec;
extern int cdvdman_strmerr;
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
extern int cdvdman_emudvd9;
extern int cdvdman_minver30601;
extern int cdvdman_minver50000;
#ifdef __CDVDMAN_NEWBIOS__
extern int cdvdman_minver50200;
extern int cdvdman_minver50400;

extern int cdvdman_minver60000;
extern int cdvdman_nontray;
#endif

extern char *cdvdman_masterd;
extern u8 cdvdman_ncmd;
extern int cdvdman_chmedia;
extern int cdvdman_chflags[4];
extern int cdvdman_rtindex;
extern int cdvdman_retries;
/* Timeouts (default values) */
extern int cdvdman_sync_to;
extern int TimeOut2;


extern int cdvdman_verbose;
extern void *cdvdman_pathtbl;


extern u32 cdvdman_ptblsize;

extern int cdvdman_cache_fd;
extern int cdvdman_fs_cdsec;
extern int cdvdman_fs_layer;
extern int cdvdman_fs_cache;
extern int cdvdman_fs_base2;

/* cdvdman SBSS segment */

extern u8 *cdvdman_ptoc;
extern int cdvdman_scmd_ef;
extern char *cdvdman_pb_fsvr;
extern int cdvdman_srch_ef;
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

/* cdvdman BSS segment */
extern CDVDMAN_FILEDATA cdvdman_handles[0x10];

extern u32 cdvdman_readptr;

extern iop_sys_clock_t cdvdman_racb_to;
extern iop_sys_clock_t cdvdman_ncmd_to;
extern void *cdvdman_readbuf;

extern iop_sys_clock_t cdvdman_poff_to;

extern char cdvdman_sfname[0x400];
extern sceCdlFILE cdvdman_filetbl[CdlMAXFILE];
extern CD_DIR_ENTRY cdvdman_dirtbl[CdlMAXDIR];
extern int cdvdman_ptblflag;

extern char cdvdman_fs_rbuf[0x800];

extern char cdvdman_fsvrbuf[FSVR_BUFFER_SIZE];
extern u8 toc_buffer[TOC_BUFFSIZE];

/* The data below is probably a some very big (0xC0 bytes or even bigger) internal structure */
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
extern u8 cdvdman_curdvd;
extern u8 cdvdman_dlemu;
extern u32 cdvdman_elayer;
extern int cdvdman_xorvalue;
extern u32 cdvdman_decshift;
extern int cdvdman_decstate;
extern int cdvdman_nodecflg;
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
extern int cdvdman_ncmd0Ch(int arg1, u32 arg2, u32 arg3);
extern int CdSearchFile(sceCdlFILE *fp, const char *name, int layer);
extern int _sceCdSearchDir(char *dirname, int layer);
extern int _sceCdReadDir(sceCdlFILE *fp, int dsec, int index, int layer);
extern int cdvdman_cmpname(const char *fn1, const char *fn2);
extern int CD_newmedia(int layer);
extern int cdvdman_finddir(int parent, char *name);
extern int CD_cachefile(int dsec, int layer);
extern int cdvdman_send_scmd2(int cmd, const void *sdata, int sdlen, void *rdata, int rdlen, int check_sef);
extern int sceCdRead0_Rty(u32 lsn, u32 nsec, void *buf, sceCdRMode *mode, int ncmd, int dintrsec, void *func);
extern int cdvdman_syncdec(int decflag, int decxor, int shift, u32 data);
extern int disc_read(int size, int loc, void *buffer, int layer);
extern int intrh_dma_3(void *common);
extern int cdvdman_cacheinit(u32 blocks, char *fname, int action);
extern u32 sceCdLsnDualChg(u32 lsn);

// cdvdmanf
extern int cdvdman_devready();
extern int cdvdman_l0check(int layer);
extern void cdvdman_iormode(sceCdRMode *rmode, int fmode, int layer);
extern void cdvdman_fillstat(void *dummy, iox_stat_t *buf, sceCdlFILE *fp);
extern int cdvdman_cdfname(char *filename);
extern int cdvd_odcinit(CDVDMAN_FILEDATA *fh, int mode, int id);
extern int cdvdman_cacheinvl(CDVDMAN_FILEDATA *fd, int index);
extern int cdvdman_invcaches();
extern int cdvdman_ioread(iop_file_t *f, void *buf, int nbytes);
extern int cdvdman_stread(iop_file_t *f, void *buf, int nbyte);

// Temporary prototype until it gets implemented in ps2sdk
extern int sceCdRV(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int arg5, void *cb);

extern void break_read_timeout_callback(void);
