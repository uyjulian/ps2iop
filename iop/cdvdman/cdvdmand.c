#include "cdvdman-internal.h"

/* cdvdman DATA segment */

iop_device_ops_t cdvdman_cdops =
    {
        cdrom_init,
        cdrom_deinit,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
        (void *)cdrom_nulldev,
};

iop_device_t cdvdman_cddev = {cdvdman_cdrom, IOP_DT_FS, 1, "CD-ROM ", &cdvdman_cdops};

int cdvdman_clk_flg = 0;
int cdvdman_ee_ncmd = 0;
int cdvdman_mmode = 0;   /* Media Mode set by sceCdMmode() call */
int cdvdman_brkfunc = 0; /* Cancelled ncmd function set by sceCdBreak() call */
int cdvdman_minver10700 = 0; /* Enables "PAUSE" after TOC reading and read speed change */
int cdvdman_minver20200 = 0; /* Disables DEC MODE 0x00 */
int cdvdman_minver20400 = 0; /* Enables "Cancel Power-off RDY" S-Command */
int cdvdman_minver20800 = 0; /* Enables N-Command 0Eh (disc reading) */
u8 cdvdman_ncmd = CDVD_NCMD_READ;
int cdvdman_chmedia = 0;
int cdvdman_chflags[4] = {1, 1, 1, 1}; /* four copies of "Media Change" */
int cdvdman_rtindex = 0;
int cdvdman_retries = 0;
/* Timeouts (default values) */
int cdvdman_sync_to = 15000; /* TimeOut value for the certain sceCdSync call modes */


int cdvdman_verbose = 0; /* Enables debug output via printf & Kprintf calls */

/* cdvdman SBSS segment */

u8 *cdvdman_ptoc;    /* sbss:0000  - pointer to buffer used to read TOC */
int cdvdman_scmd_ef;   /* sbss:0004  - event flag #2 - s-commands syncronization */
int cdvdman_ncmd_ef;   /* sbss:0010  - event flag #3 - n-commands syncronization */
int cdvdman_read_ef;   /* sbss:0014  - event flag #5 - disk reading syncronization */
int cdvdman_intr_ef;   /* sbss:0018  - event flag #1 - hw interrupt syncronization */

sceCdCBFunc cdvdman_user_cb; /* set by sceCdCallback */

sceCdCLOCK cdvdman_clock;        /* Cached Real-Time Clock value */
int cdvdman_cmdfunc;

u32 cdvdman_readptr;

iop_sys_clock_t cdvdman_racb_to;
iop_sys_clock_t cdvdman_ncmd_to;
void *cdvdman_readbuf;

iop_sys_clock_t cdvdman_poff_to;

u8 toc_buffer[TOC_BUFFSIZE];

/* The data below is probably a some very big (0xC0 bytes or even bigger) internal structure */
u8 cdvdman_command;
u8 cdvdman_cderror; /* next byte after the cdvdman_command */
u8 cdvdman_unused1;
u8 cdvdman_unused2;
int cdvdman_waf; /* +4 */
int cdvdman_thrd_id;
int cdvdman_read2_flg;
u32 cdvdman_readlsn;
void *cdvdman_rbuffer;
u32 cdvdman_nsec;
u32 cdvdman_csec;
u32 cdvdman_rdsectc;
u32 cdvdman_pattern;
sceCdRMode cdvdman_cdrmode;
u32 cdvdman_recstat;
u32 cdvdman_dvdflag;
u32 cdvdman_rd_lsn;
void *cdvdman_rd_buf;
u32 cdvdman_rd_sec;
sceCdRMode cdvdman_rdmode;
u32 cdvdman_unk1;
u32 cdvdman_dintrlsn;
void *cdvdman_read_cb;
u32 cdvdman_rdchunk;
/* s-cmd related stuff & some unknown variables here*/
char cdvdman_scmd_flg;
char cdvdman_scmd;
int cdvdman_sdlen;
char cdvdman_rdlen;
char cdvdman_scmd_sd[0x10];
char cdvdman_scmd_rd[0x10];
u32 cdvdman_syncerr; /* increased by 1 during read_cdvd_cb() call - error counter */
int cdvdman_read_to;
u32 cdvdman_pwr_flg;
u32 cdvdman_layer1;
u8 cdvdman_usetoc;
u8 cdvdman_dldvd;
DMA3PARAM cdvdman_dma3prm;
u32 cdvdman_dma3sec; /* increased by by dma3_csectors value during DMA Ch.3 interrupt handler */
int cdvdman_dr_flg;
u16 cdvdman_unk2; /* +0xC0 */
u16 cdvdman_unk3; /* +0xC2 */
int cdvdman_waf2;
