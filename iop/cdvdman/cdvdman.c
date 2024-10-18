
#include "irx_imports.h"
#include "../00common/defs.h"

IRX_ID("cdvd_driver", 2, 38);

extern struct irx_export_table _exp_cdvdman;

//-------------------------------------------------------------------------
// Function declarations

int __cdecl _start(int argc, char **argv);
void *sceGetFsvRbuf(void);
int __cdecl cdrom_init(iop_device_t *dev);
void __fastcall cdvdman_termcall(int with_stop);
int __cdecl cdrom_deinit();
int __cdecl cdvdman_devready();
int __cdecl cdvdman_l0check(int layer);
void __cdecl cdvdman_iormode(sceCdRMode *rmode, int fmode, int layer);
int __cdecl cdrom_dopen(iop_file_t *f, const char *dirname);
void __cdecl cdvdman_fillstat(void *dummy, iox_stat_t *buf, CDVDMAN_FILETBL_ENTRY_T *fp);
int __cdecl cdvdman_cdfname(char *filename);
int __cdecl cdrom_getstat(iop_file_t *f, const char *name, iox_stat_t *buf);
int __cdecl cdrom_dread(iop_file_t *f, iox_dirent_t *buf);
int __cdecl cdvd_odcinit(CDVDMAN_FILEDATA *fh, int open_or_close, int id);
int __cdecl cdvdman_cache_invalidate(CDVDMAN_FILEDATA *filedata, int index);
int __cdecl cdvdman_invcaches();
int __fastcall cdrom_internal_cache_read(const iop_file_t *f, int nbytes);
int __fastcall cdrom_internal_write_cache(const iop_file_t *f, unsigned int nbytes);
int __cdecl cdvdfile_cache_read(const iop_file_t *f, void *buf, int nbyte);
int __cdecl cdvdfile_cache_fill_read(const iop_file_t *f, void *buf, int nbytes);
int __cdecl cdrom_open(iop_file_t *f, const char *name, int mode, int arg4);
int __cdecl cdrom_close(iop_file_t *f);
int __fastcall cdrom_internal_read(const iop_file_t *f, char *addr, int nbytes);
int __fastcall cdrom_stream_read(const iop_file_t *f, char *bbuf, int nbytes);
int __cdecl cdrom_read(iop_file_t *f, void *buf, int nbytes);
int __fastcall cdrom_ioctl(iop_file_t *f, int arg, void *param);
int __cdecl cdrom_ioctl2(iop_file_t *f, int request, void *argp, size_t arglen, void *bufp, size_t buflen);
int __cdecl cdrom_devctl(iop_file_t *f, const char *, int cmd, void *argp, unsigned int arglen, void *bufp, unsigned int buflen);
int __cdecl cdrom_lseek(iop_file_t *f, int offset, int pos);
int __cdecl cdrom_nulldev();
s64 __cdecl cdrom_nulldev64();
int __cdecl sync_timeout_func(iop_sys_clock_t *timeout_ptr);
int __cdecl sceCdSetTimeout(int param, int timeout);
int __cdecl sceCdSync(int mode);
int __cdecl sceCdSpinCtrlIOP(u32 speed);
int __cdecl sceCdLayerSearchFile(sceCdlFILE *fp, const char *path, int layer);
int __cdecl sceCdSearchFile(sceCdlFILE *file, const char *name);
int __cdecl sceCdGetToc(u8 *toc);
int __cdecl sceCdDiskReady(int mode);
int sceCdGetDiskType(void);
int sceCdStatus(void);
sceCdlLOCCD *__cdecl sceCdIntToPos(u32 i, sceCdlLOCCD *p);
u32 __cdecl sceCdPosToInt(sceCdlLOCCD *p);
int __fastcall read_id_from_rom(int mode, int *buf);
int __cdecl query_boot_mode_6_nonzero();
int __cdecl query_boot_mode_6_zero();
int __cdecl cdvdman_readID(int mode, int *buf);
int __cdecl sceCdReadGUID(u64 *guid);
int __cdecl sceCdReadModelID(unsigned int *id);
int __cdecl sceCdStInit(u32 bufmax, u32 bankmax, void *buffer);
int __cdecl sceCdStStart(u32 lbn, sceCdRMode *mode);
int __cdecl sceCdStSeekF(unsigned int lsn);
int __cdecl sceCdStSeek(u32 lbn);
int sceCdStStop(void);
int __cdecl sceCdStRead(u32 sectors, u32 *buffer, u32 mode, u32 *error);
int sceCdStPause(void);
int sceCdStResume(void);
int sceCdStStat(void);
int __cdecl CdSearchFileInner(CDVDMAN_FILETBL_ENTRY_T *fp, const char *name, int layer);
int __cdecl sceCdSearchDir(char *dirname, int layer);
int __cdecl sceCdReadDir(sceCdlFILE *fp, int dsec, int index, int layer);
int __cdecl cdvdman_cmpname(const char *p, const char *q);
int __cdecl CD_newmedia(int arg);
int __fastcall cdvdman_finddir(int target_parent, const char *target_name);
int __fastcall CD_cachefile(int dsec, int layer);
int __cdecl disc_read(int size, int loc, void *buffer, int layer);
int __cdecl path_tbl_init(u32 blocks, char *fname, int action);
void __fastcall unused_40BA90(unsigned int *, int);
unsigned int __fastcall cdvdman_memcpy(char *dst, const char *src, unsigned int n);
void __cdecl cdvdman_1();
int __cdecl cdvdman_retonly();
void __fastcall hex_dump(u8 *addr_start, int length);
int __cdecl cdvdman_initcfg();
int __fastcall vSetAlarm(iop_sys_clock_t *sys_clock, unsigned int (__cdecl *alarm_cb)(void *), void *arg);
int __fastcall vCancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg);
s32 __cdecl vSignalSema(s32 sema_id);
int __fastcall vSetEventFlag(int ef, u32 bits);
int __fastcall vClearEventFlag(int ef, u32 bits);
int __fastcall vReferEventFlagStatus(int ef, iop_event_info_t *info);
int __fastcall vDelayThread(int usec);
BOOL __fastcall alarm_cb_read(iop_sys_clock_t *a1);
sceCdCBFunc __cdecl sceCdCallback(sceCdCBFunc function);
void *__cdecl sceCdPOffCallback(void (__cdecl *func)(void *), void *addr);
int __cdecl sceCdstm0Cb(void (__cdecl *p)(int));
int __cdecl sceCdstm1Cb(void (__cdecl *p)(int));
int __fastcall cdvdman_intr_cb(cdvdman_internal_struct_t *s);
int __fastcall intrh_cdrom(cdvdman_internal_struct_t *s);
u32 __cdecl cdvdman_l1start(const u8 *toc);
int __cdecl DvdDual_infochk();
u32 __cdecl sceCdLsnDualChg(u32 lsn);
int __cdecl sceCdReadDvdDualInfo(int *on_dual, unsigned int *layer1_start);
int __cdecl sceCdSC(int code, int *param);
void __cdecl nullsub_2();
void __cdecl cdvdman_init();
int __cdecl sceCdInit(int mode);
int __cdecl set_prev_command(int cmd, const char *sdata, int sdlen, char *rdata, int rdlen, int check_sef);
void __cdecl cdvdman_write_scmd(cdvdman_internal_struct_t *s);
int __cdecl cdvdman_send_scmd2(int cmd, const void *sdata, int sdlen, void *rdata, int rdlen, int check_sef);
int __cdecl sceCdApplySCmd(u8 cmdNum, const void *inBuff, u16 inBuffSize, void *outBuff);
int __cdecl sceCdApplySCmd2(u8 cmdNum, const void *inBuff, unsigned long int inBuffSize, void *outBuff);
int __fastcall sceCdApplySCmd3(u8 cmdNum, const void *inBuff, unsigned long int inBuffSize, void *outBuff);
int sceCdBreak(void);
int __fastcall cd_ncmd_timeout_callback(iop_sys_clock_t *sys_clock);
int __fastcall intrh_dma_3(cdvdman_internal_struct_t *s);
int __cdecl cdvdman_setdma3(DMA3PARAM *b18);
int __cdecl cdvdman_send_ncmd(int ncmd, const void *ndata, int ndlen, int func, DMA3PARAM *b18, int check_cb);
int __cdecl sceCdApplyNCmd(u8 cmdNum, const void *inBuff, u16 inBuffSize);
int sceCdCheckCmd(void);
int __cdecl cdvdman_mediactl(int code);
int sceCdGetError(void);
int __cdecl cdvdman_get_last_command();
int sceCdNop(void);
int __cdecl cdvdman_ncmd_sender_01();
int __cdecl cdvdman_ncmd_sender_06();
int sceCdStandby(void);
int sceCdStop(void);
int sceCdPause(void);
int __cdecl cdvdman_ncmd_sender_0B();
int __fastcall readtoc_timeout_func(iop_sys_clock_t *s);
int __cdecl cdvdman_readtoc(u8 *toc, int param, int func);
int __cdecl cdvdman_gettoc(u8 *toc);
u32 sceCdGetReadPos(void);
int __cdecl cdvdman_speedctl(u32 spindlctrl, int dvdflag, u32 maxlsn);
int __cdecl cdvdman_isdvd();
int __cdecl sceCdRead0_Rty(u32 lsn, u32 nsec, void *buf, const sceCdRMode *mode, int ncmd, int dintrsec, void *func);
int __cdecl sceCdRead0(u32 lsn, u32 sectors, void *buffer, sceCdRMode *mode, int csec, void *callback);
int __cdecl read_cdvd_cb(cdvdman_internal_struct_t *common);
int __cdecl cdvdman_read(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int decflag, int shift, int ef1, int ef2);
int __cdecl sceCdRE(unsigned int lsn, unsigned int sectors, void *buf, sceCdRMode *mode);
int __cdecl sceCdRead(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode);
int __cdecl cdvdman_syncdec(int decflag, int decxor, int shift, u32 data);
int __cdecl dummy_nullsub();
void __cdecl Read2intrCDVD(int read2_flag);
int __cdecl sceCdReadChain(sceCdRChain *tag, sceCdRMode *mode);
int __cdecl cdvdman_readfull(u32 lsn, u32 sectors, void *buf, const sceCdRMode *mode, int flag);
int __cdecl sceCdReadCDDA(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode);
int __cdecl sceCdRV(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int arg5, void *cb);
int __cdecl sceCdSeek(u32 lbn);
int __cdecl sceCdRI(u8 *buffer, u32 *result);
int __cdecl sceCdRM(char *buffer, u32 *status);
int __cdecl sceCdGetMVersion(u8 *buffer, u32 *status);
int __fastcall cdvdman_scmd_sender_03_48(u8 *buf, u32 *status);
int __cdecl sceCdMmode(int media);
int __cdecl sceCdCancelPOffRdy(u32 *result);
unsigned int __fastcall alarm_cb_poff(cdvdman_internal_struct_t *s);
int __cdecl sceCdPowerOff(u32 *result);
int __cdecl sceCdCtrlADout(int mode, u32 *status);
int __cdecl sceCdReadClock(sceCdCLOCK *clock);
int __cdecl sceCdRC(sceCdCLOCK *clock);
int __cdecl sceCdTrayReq(int param, u32 *traychk);
int __fastcall cdvdman_scmd_sender_3B(int arg1);
int __cdecl sceCdReadDiskID(unsigned int *id);
int __cdecl cdvdman_179(u32 *status);
int __cdecl cdvdman_ncmd_sender_0C(int arg1, u32 arg2, u32 arg3);
int __cdecl sceCdDecSet(u8 enable_xor, u8 enable_shift, u8 shiftval);
#if 0
void *__cdecl AllocSysMemory(int mode, int size, void *ptr);
int __cdecl FreeSysMemory(void *ptr);
int Kprintf(const char *format, ...);
int __cdecl RegisterLibraryEntries(struct irx_export_table *exports);
int *__cdecl QueryBootMode(int mode);
int __cdecl SetRebootTimeLibraryHandlingMode(struct irx_export_table *exports, int mode);
int __cdecl RegisterIntrHandler(int irq, int mode, int (__cdecl *handler)(void *), void *arg);
int __cdecl ReleaseIntrHandler(int irq);
int __cdecl EnableIntr(int irq);
int __cdecl DisableIntr(int irq, int *res);
int __cdecl CpuSuspendIntr(int *state);
int __cdecl CpuResumeIntr(int state);
int QueryIntrContext(void);
int printf(const char *format, ...);
void __cdecl dmac_ch_set_madr(u32 channel, u32 val);
u32 __cdecl dmac_ch_get_madr(u32 channel);
void __cdecl dmac_ch_set_bcr(u32 channel, u32 val);
void __cdecl dmac_ch_set_chcr(u32 channel, u32 val);
u32 __cdecl dmac_ch_get_chcr(u32 channel);
void __cdecl dmac_set_dpcr(u32 val);
u32 dmac_get_dpcr(void);
int GetThreadId(void);
int __cdecl DelayThread(int usec);
int __cdecl GetSystemTime(iop_sys_clock_t *sys_clock);
int __cdecl SetAlarm(iop_sys_clock_t *sys_clock, unsigned int (__cdecl *alarm_cb)(void *), void *arg);
int __cdecl iSetAlarm(iop_sys_clock_t *sys_clock, unsigned int (__cdecl *alarm_cb)(void *), void *arg);
int __cdecl CancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg);
int __cdecl iCancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg);
int __cdecl CreateEventFlag(iop_event_t *event);
int __cdecl DeleteEventFlag(int ef);
int __cdecl SetEventFlag(int ef, u32 bits);
int __cdecl iSetEventFlag(int ef, u32 bits);
int __cdecl ClearEventFlag(int ef, u32 bits);
int __cdecl iClearEventFlag(int ef, u32 bits);
int __cdecl WaitEventFlag(int ef, u32 bits, int mode, u32 *resbits);
int __cdecl PollEventFlag(int ef, u32 bits, int mode, u32 *resbits);
int __cdecl ReferEventFlagStatus(int ef, iop_event_info_t *info);
int __cdecl iReferEventFlagStatus(int ef, iop_event_info_t *info);
int __cdecl SignalSema(int semid);
int __cdecl iSignalSema(int semid);
void *__cdecl memcpy(void *dest, const void *src, size_t size);
void *__cdecl memset(void *ptr, int c, size_t size);
int sprintf(char *str, const char *format, ...);
char *__cdecl strcat(char *dest, const char *src);
int __cdecl strcmp(const char *p, const char *q);
size_t __cdecl strlen(const char *s);
int __cdecl strncmp(const char *p, const char *q, size_t size);
char *__cdecl strncpy(char *dest, const char *src, size_t size);
int __cdecl strtol(const char *s, char **endptr, int base);
int open(const char *name, int flags, ...);
int __cdecl close(int fd);
int __cdecl read(int fd, void *ptr, int size);
int __cdecl write(int fd, void *ptr, int size);
int __cdecl lseek(int fd, int pos, int mode);
int __cdecl remove(const char *name);
int __cdecl AddDrv(iop_device_t *device);
int __cdecl DelDrv(const char *name);
int __cdecl devctl(const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
int __cdecl ioctl2(int fd, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
#endif

//-------------------------------------------------------------------------
// Data declarations

char g_cdvdman_cache_name[256] = "host0:"; // weak
int g_cdvdman_cache_sector_size_count = 1;
int g_cdvdman_srchspd = 0;
int g_cdvdman_spinctl = -1;
int g_cdvdman_spinnom = -1;
int g_cdvdman_trycnt = -1;
int g_cdvdman_iocache = 0;
unsigned int g_cdvdman_lcn_offset = 0;
unsigned int g_cdvdman_numbytes_offset = 0;
int g_cdvdman_strmerr = 0;
static iop_device_ops_t g_cdvdman_cddev_ops =
    {
        &cdrom_init,
        &cdrom_deinit,
        (void *)&cdrom_nulldev,
        &cdrom_open,
        &cdrom_close,
        &cdrom_read,
        (void *)&cdrom_nulldev,
        &cdrom_lseek,
        &cdrom_ioctl,
        (void *)&cdrom_nulldev,
        (void *)&cdrom_nulldev,
        (void *)&cdrom_nulldev,
        &cdrom_dopen,
        &cdrom_close,
        &cdrom_dread,
        &cdrom_getstat,
        (void *)&cdrom_nulldev,
        (void *)&cdrom_nulldev,
        (void *)&cdrom_nulldev,
        (void *)&cdrom_nulldev,
        (void *)&cdrom_nulldev,
        (void *)&cdrom_nulldev,
        (void *)&cdrom_nulldev64,
        &cdrom_devctl,
        (void *)&cdrom_nulldev,
        (void *)&cdrom_nulldev,
        &cdrom_ioctl2,
    };
iop_device_t g_cdvdman_cddev = { "cdrom", 268435472u, 1u, "CD-ROM ", &g_cdvdman_cddev_ops };
int g_cdvdman_sync_to = 15000;
int g_TimeOut2 = 5000;
iop_sys_clock_t g_readid_systemtime = { 0u, 0u }; // weak
int g_verbose_level = 0;
CDVDMAN_PATHTBL_T *g_cdvdman_pathtbl = NULL;
unsigned int g_cache_count = 0;
unsigned int g_cache_table = 0;
unsigned int g_cdvdman_pathtblsize = 0;
int g_cache_path_size = 0;
int g_cache_path_fd = -1;
int g_cdvdman_fs_cdsec = 0;
int g_cdvdman_fs_layer = -1;
int g_cdvdman_fs_cache = 0;
int g_cdvdman_fs_base2 = 0;
int g_cdvdman_clk_flg = 0;
int g_cdvdman_cd36key = 0;
int g_cdvdman_strm_id = 0;
int g_cdvdman_mmode = 0;
int g_cdvdman_last_cmdfunc = 0;
int g_cdvdman_minver_10700 = 0;
int g_cdvdman_minver_20200 = 0;
int g_cdvdman_minver_20400 = 0;
int g_cdvdman_minver_20800 = 0;
int g_cdvdman_emudvd9 = 0;
int g_cdvdman_minver_50000 = 0;
int g_cdvdman_minver_50200 = 0;
int g_cdvdman_minver_50400 = 0;
int g_cdvdman_minver_50600 = 0;
int g_cdvdman_minver_60000 = 0;
int g_cdvdman_minver_60200 = 0;
int g_cdvdman_minver_x_model_15 = 0;
char *g_masterdisc_header = "PlayStation Master Disc"; // weak
char g_cdvdman_ncmd = '\x06'; // weak
int g_cdvdman_chmedia = 0;
int g_cdvdman_chflags[4] = { 1, 1, 1, 1 };
int g_cdvdman_rtindex = 0;
int g_cdvdman_retries = 0;
u8 *g_cdvdman_ptoc;
int g_scmd_evid; // idb
void *g_cdvdman_temp_buffer_ptr;
int g_sfile_evid; // idb
int g_ncmd_evid; // idb
int g_fio_fsv_evid; // idb
int g_cdvdman_intr_efid; // idb
sceCdCBFunc g_cdvdman_user_cb;
void *g_cdvdman_poffarg;
void (__cdecl *g_cdvdman_cdstm0cb)(int);
sceCdCLOCK g_cdvdman_clock;
void (__cdecl *g_cdvdman_poff_cb)(void *userdata);
void (__cdecl *g_cdvdman_cdstm1cb)(int);
int g_cdvdman_cmdfunc;
CDVDMAN_FILEDATA g_cdvdman_handles[16];
char g_cdvdman_sfname[1024];
CDVDMAN_FILETBL_ENTRY_T g_cdvdman_filetbl[64];
CD_DIR_ENTRY g_cdvdman_dirtbl[128];
int g_cdvdman_pathtblflag;
char g_cdvdman_fs_rbuf[2048];
int g_cdvdman_readptr;
iop_sys_clock_t g_cdvdman_racb_to;
iop_sys_clock_t g_cdvdman_ncmd_to;
void *g_cdvdman_readbuf;
iop_sys_clock_t g_cdvdman_poff_to; // weak
char g_cdvdman_fsvrbuf[42128];
cdvdman_internal_struct_t g_cdvdman_istruct;
dev5_regs_t dev5_regs; // weak


//----- (00400000) --------------------------------------------------------
int __cdecl _start(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	if ( RegisterLibraryEntries(&_exp_cdvdman) != 0 )
	{
		return 1;
	}
	DelDrv("cdrom");
	if ( AddDrv(&g_cdvdman_cddev) )
	{
		cdrom_deinit();
		return 1;
	}
	g_cdvdman_ptoc = (u8 *)&g_cdvdman_fsvrbuf[2340];
	g_cdvdman_temp_buffer_ptr = g_cdvdman_fsvrbuf;
	cdvdman_init();
#if 0
	// FIXME workaround
	SetRebootTimeLibraryHandlingMode(&_exp_cdvdman, 2);
#endif
	return 0;
}

//----- (004000A0) --------------------------------------------------------
void *sceGetFsvRbuf(void)
{
	return g_cdvdman_fsvrbuf;
}

//----- (004000B0) --------------------------------------------------------
int __cdecl cdrom_init(iop_device_t *dev)
{
	unsigned int i; // $v1
	iop_event_t event; // [sp+10h] [-18h] BYREF
	int cd_sc_tmp; // [sp+20h] [-8h] BYREF

	(void)dev;

	PRINTF("cdvdman Init\n");
	g_cdvdman_istruct.m_wait_flag = 1;
	g_cdvdman_istruct.m_scmd_flag = 1;
	g_cdvdman_istruct.m_read2_flag = 0;
	g_cdvdman_istruct.m_stream_flag = 0;
	g_cdvdman_istruct.m_last_error = 0;
	g_cdvdman_istruct.m_layer_1_lsn = 0;
	g_cdvdman_istruct.m_use_toc = 0;
	g_cdvdman_istruct.m_read_to = 0;
	g_cdvdman_istruct.m_power_flag = 0;
	g_cdvdman_istruct.m_current_dvd = 0;
	g_cdvdman_istruct.m_dual_layer_emulation = 0;
	g_cdvdman_istruct.m_dec_state = 0;
	g_cdvdman_istruct.m_check_version = 0;
	g_cdvdman_istruct.m_dec_shift = 0;
	g_cdvdman_istruct.m_opo_or_para = -1;
	g_cdvdman_istruct.m_no_dec_flag = 0;
	g_cdvdman_istruct.m_cd_inited = 0;
	g_cdvdman_istruct.m_tray_is_open = 0;
	g_cdvdman_strm_id = 0;
	g_cdvdman_spinctl = -1;
	event.attr = 2;
	event.bits = 0;
	event.option = 0;
	g_cdvdman_intr_efid = CreateEventFlag(&event);
	g_scmd_evid = CreateEventFlag(&event);
	g_ncmd_evid = CreateEventFlag(&event);
	g_sfile_evid = CreateEventFlag(&event);
	g_fio_fsv_evid = CreateEventFlag(&event);
	ClearEventFlag(g_cdvdman_intr_efid, 0xFFFFFFFB);
	ClearEventFlag(g_cdvdman_intr_efid, 0xFFFFFFEF);
	SetEventFlag(g_cdvdman_intr_efid, 0x29u);
	SetEventFlag(g_ncmd_evid, 1u);
	SetEventFlag(g_scmd_evid, 1u);
	SetEventFlag(g_sfile_evid, 1u);
	SetEventFlag(g_fio_fsv_evid, 1u);
	g_cdvdman_spinnom = -1;
	g_cdvdman_trycnt = -1;
	sceCdSC(0xFFFFFFF3, &cd_sc_tmp);
	for ( i = 0; i < (sizeof(g_cdvdman_handles)/sizeof(g_cdvdman_handles[0])); i += 1 )
	{
		g_cdvdman_handles[i].m_fd_flags = 0;
	}
	return 0;
}

//----- (00400254) --------------------------------------------------------
void __fastcall cdvdman_termcall(int with_stop)
{
	int i; // $s0
	int oldstate; // [sp+10h] [-8h] BYREF

	VERBOSE_KPRINTF(1, "CDVD:library Terminate Call %d\n", with_stop);
	if ( with_stop )
	{
		return;
	}
	sceCdBreak();
	sceCdSync(0);
	if ( g_cdvdman_istruct.m_cd_inited )
	{
		cdvdman_ncmd_sender_06();
	}
	for ( i = 0; i < 50000; i += 1 )
	{
		if ( (dev5_regs.m_dev5_reg_017 & 0x80) == 0 )
		{
			break;
		}
		DelayThread(100);
	}
	sceCdDecSet(0, 0, 0);
	if ( (dmac_ch_get_chcr(3u) & 0x1000000) != 0 )
	{
		dev5_regs.m_dev5_reg_007 = 1;
	}
	dmac_ch_set_chcr(3u, 0);
	DisableIntr(35, &oldstate);
	ReleaseIntrHandler(35);
	DisableIntr(2, &oldstate);
	ReleaseIntrHandler(2);
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00400390) --------------------------------------------------------
int __cdecl cdrom_deinit()
{
	unsigned int i; // $v1

	for ( i = 0; i < (sizeof(g_cdvdman_handles)/sizeof(g_cdvdman_handles[0])); i += 1 )
	{
		g_cdvdman_handles[i].m_fd_flags = 0;
	}
	DeleteEventFlag(g_fio_fsv_evid);
	DeleteEventFlag(g_cdvdman_intr_efid);
	DeleteEventFlag(g_ncmd_evid);
	DeleteEventFlag(g_scmd_evid);
	DeleteEventFlag(g_sfile_evid);
	return 0;
}

//----- (00400418) --------------------------------------------------------
int __cdecl cdvdman_devready()
{
	int i; // $s0

	for ( i = 0; i < 100; i += 1 )
	{
		if ( (dev5_regs.m_dev5_reg_00A & 1) != 0 )
		{
			g_cdvdman_iocache = 0;
			return -5;
		}
		if ( (dev5_regs.m_dev5_reg_005 & 0xC0) == 64 && !g_cdvdman_istruct.m_read2_flag && !g_cdvdman_strm_id )
		{
			return 1;
		}
		DelayThread(10000);
	}
	return -16;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (004004E0) --------------------------------------------------------
int __cdecl cdvdman_l0check(int layer)
{
	return !layer
			&& (g_cdvdman_istruct.m_dual_layer_emulation || g_cdvdman_istruct.m_opo_or_para == 1 || g_cdvdman_istruct.m_opo_or_para == 2);
}

//----- (00400528) --------------------------------------------------------
void __cdecl cdvdman_iormode(sceCdRMode *rmode, int fmode, int layer)
{
	rmode->datapattern = 0;
	rmode->trycount = ( g_cdvdman_trycnt == -1 ) ? 16 : g_cdvdman_trycnt;
	if ( cdvdman_l0check(layer) )
	{
		if ( g_cdvdman_spinnom == -1 )
		{
			rmode->spindlctrl = ( fmode == 2 || fmode == 20 ) ? fmode : 0;
			return;
		}
		if ( fmode != 2 && fmode != 20 )
		{
			rmode->spindlctrl = 0;
			return;
		}
	}
	else if ( g_cdvdman_spinnom == -1 )
	{
		switch ( fmode )
		{
			case 0:
				rmode->spindlctrl = 0;
				break;
			case 1:
				rmode->spindlctrl = 1;
				break;
			case 2:
				rmode->spindlctrl = 2;
				break;
			case 3:
				rmode->spindlctrl = 3;
				break;
			case 4:
				rmode->spindlctrl = 4;
				break;
			case 5:
				rmode->spindlctrl = 5;
				break;
			case 20:
				rmode->spindlctrl = 20;
				break;
			default:
				rmode->spindlctrl = 1;
				break;
		}
		return;
	}
	rmode->spindlctrl = (u8)g_cdvdman_spinnom;
}

//----- (00400658) --------------------------------------------------------
int __cdecl cdrom_dopen(iop_file_t *f, const char *dirname)
{
	unsigned int i; // $v1
	int is_devready; // $s0
	size_t path_name_ind; // $a0
	int file_lsn_tmp; // $v0
	char path_name[128]; // [sp+10h] [-88h] BYREF
	u32 efbits[2]; // [sp+90h] [-8h] BYREF

	VERBOSE_PRINTF(1, "fileIO DOPEN name= %s layer %d\n", dirname, f->unit);
	WaitEventFlag(g_fio_fsv_evid, 1u, 16, efbits);
	for ( i = 0; (i < (sizeof(g_cdvdman_handles)/sizeof(g_cdvdman_handles[0]))) && g_cdvdman_handles[i].m_fd_flags; i += 1 )
	{
	}
	if ( i == (sizeof(g_cdvdman_handles)/sizeof(g_cdvdman_handles[0])) )
	{
		SetEventFlag(g_fio_fsv_evid, 1u);
		return -24;
	}
	f->privdata = (void *)i;
	is_devready = cdvdman_devready();
	if ( is_devready < 0 )
	{
		SetEventFlag(g_fio_fsv_evid, 1u);
		return is_devready;
	}
	strncpy(path_name, dirname, sizeof(path_name));
	if ( !strcmp(path_name, ".") )
	{
		strcpy(path_name, "\\.");
	}
	path_name_ind = strlen(path_name);
	path_name_ind -= ( path_name_ind >= 2 ) ? 2 : 0;
	if ( strcmp(&path_name[path_name_ind], "\\.") )
	{
		strcat(path_name, "\\.");
	}
	if ( (unsigned int)(f->unit) >= 2u )
	{
		PRINTF("open fail name %s\n", path_name);
		SetEventFlag(g_fio_fsv_evid, 1u);
		return -2;
	}
	g_cdvdman_handles[i].m_file_lsn = 0;
	g_cdvdman_srchspd = 0;
	file_lsn_tmp = sceCdSearchDir(path_name, f->unit);
	if ( file_lsn_tmp < 0 )
	{
		PRINTF("open fail directory %s\n", path_name);
		SetEventFlag(g_fio_fsv_evid, 1u);
		return -2;
	}
	g_cdvdman_handles[i].m_file_lsn = file_lsn_tmp;
	g_cdvdman_handles[i].m_read_pos = 0;
	g_cdvdman_handles[i].m_filemode = 0;
	g_cdvdman_handles[i].m_fd_flags = 1;
	g_cdvdman_handles[i].m_fd_layer = f->unit;
	SetEventFlag(g_fio_fsv_evid, 1u);
	return 0;
}

//----- (00400878) --------------------------------------------------------
void __cdecl cdvdman_fillstat(void *dummy, iox_stat_t *buf, CDVDMAN_FILETBL_ENTRY_T *fp)
{
	unsigned int i; // $a0

	(void)dummy;

	buf->attr = 0;
	buf->private_5 = 0;
	buf->private_4 = 0;
	buf->private_3 = 0;
	buf->private_2 = 0;
	buf->private_1 = 0;
	buf->private_0 = 0;
	buf->hisize = 0;
	for ( i = 0; i < (sizeof(buf->mtime)/sizeof(buf->mtime[0])); i += 1 )
	{
		buf->mtime[i] = fp->m_file_struct.date[i];
		buf->atime[i] = fp->m_file_struct.date[i];
		buf->ctime[i] = fp->m_file_struct.date[i];
	}
	buf->size = fp->m_file_struct.size;
	buf->mode = (((fp->m_file_properties & 2) != 0) ? 0x1049 : 0x2000) | 0x124;
}

//----- (004008F4) --------------------------------------------------------
int __cdecl cdvdman_cdfname(char *filename)
{
	size_t filename_len; // $v0

	filename_len = strlen(filename);
	if ( filename_len >= 3 && !(filename[filename_len - 2] != 59 && filename[filename_len - 1] != 49) )
	{
		return 0;
	}
	strcat(filename, ";1");
	return 1;
}

//----- (00400964) --------------------------------------------------------
int __cdecl cdrom_getstat(iop_file_t *f, const char *name, iox_stat_t *buf)
{
	int devready_tmp; // $s0
	CDVDMAN_FILETBL_ENTRY_T filetble; // [sp+10h] [-B0h] BYREF
	char filename[128]; // [sp+38h] [-88h] BYREF
	u32 efbits[2]; // [sp+B8h] [-8h] BYREF

	VERBOSE_PRINTF(1, "fileIO GETSTAT name= %s layer= %d\n", name, f->unit);
	WaitEventFlag(g_fio_fsv_evid, 1u, 16, efbits);
	devready_tmp = cdvdman_devready();
	if ( devready_tmp < 0 )
	{
		SetEventFlag(g_fio_fsv_evid, 1u);
		return devready_tmp;
	}
	strncpy(filename, name, sizeof(filename));
	if ( !strcmp(filename, ".") )
	{
		strcpy(filename, "\\.");
	}
	if ( !strcmp(filename, "\\") )
	{
		strcpy(filename, "\\.");
	}
	if ( !strlen(filename) )
	{
		strcpy(filename, "\\.");
	}
	g_cdvdman_srchspd = 0;
	// Unofficial: initialize to 0
	memset(&filetble, 0, sizeof(filetble));
	if ( !sceCdLayerSearchFile(&filetble.m_file_struct, filename, f->unit)
		&& !(cdvdman_cdfname(filename) && sceCdLayerSearchFile(&filetble.m_file_struct, filename, f->unit)) )
	{
		PRINTF("open fail name %s\n", name);
		SetEventFlag(g_fio_fsv_evid, 1u);
		return -2;
	}
	cdvdman_fillstat(filename, buf, &filetble);
	SetEventFlag(g_fio_fsv_evid, 1u);
	return 1;
}
// 400964: using guessed type sceCdlFILE filetble;

//----- (00400B28) --------------------------------------------------------
int __cdecl cdrom_dread(iop_file_t *f, iox_dirent_t *buf)
{
	int devready_tmp; // $s1
	CDVDMAN_FILEDATA *filedata; // $s0
	CDVDMAN_FILETBL_ENTRY_T fileinfo; // [sp+10h] [-30h] BYREF
	u32 efbits[2]; // [sp+38h] [-8h] BYREF

	memset(&fileinfo, 0, sizeof(fileinfo));
	VERBOSE_PRINTF(1, "fileIO DREAD\n");
	WaitEventFlag(g_fio_fsv_evid, 1u, 16, efbits);
	devready_tmp = cdvdman_devready();
	if ( devready_tmp < 0 )
	{
		SetEventFlag(g_fio_fsv_evid, 1u);
		return devready_tmp;
	}
	filedata = &g_cdvdman_handles[(int)f->privdata];
	g_cdvdman_srchspd = 0;
	devready_tmp = sceCdReadDir(&fileinfo.m_file_struct, filedata->m_file_lsn, filedata->m_read_pos, filedata->m_fd_layer);
	if ( devready_tmp < 0 )
	{
		SetEventFlag(g_fio_fsv_evid, 1u);
		return -2;
	}
	if ( devready_tmp )
	{
		++filedata->m_read_pos;
		devready_tmp = strlen(fileinfo.m_file_struct.name);
	}
	strncpy(buf->name, fileinfo.m_file_struct.name, sizeof(buf->name));
	cdvdman_fillstat(fileinfo.m_file_struct.name, &buf->stat, &fileinfo);
	SetEventFlag(g_fio_fsv_evid, 1u);
	return devready_tmp;
}

//----- (00400C5C) --------------------------------------------------------
int __cdecl cdvd_odcinit(CDVDMAN_FILEDATA *fh, int open_or_close, int id)
{
	int cache_remove_result; // $s5
	int cache_result; // $s1
	int cache_file_fd_new; // $s4
	u32 file_size_bsr_3; // $s7
	unsigned int file_size_bsr_17; // $fp
	char cache_filename[512]; // [sp+20h] [-208h] BYREF
	int state; // [sp+220h] [-8h] BYREF
	unsigned int ioctl_arg; // [sp+224h] [-4h] BYREF

	g_cdvdman_iocache = 0;
	sprintf(cache_filename, "%sCache_%d_%d_%d_%d", g_cdvdman_cache_name, fh->m_fd_layer, (int)fh->m_file_lsn, (int)fh->m_file_size, id);
	cache_remove_result = 0;
	VERBOSE_KPRINTF(1, "Cachefile:%s Open_or_Close:%d\n", cache_filename, open_or_close);
	cache_result = 0;
	if ( open_or_close )
	{
		u32 i; // $s0

		CpuSuspendIntr(&state);
		fh->m_fd_rbsize = g_cdvdman_cache_sector_size_count ? (g_cdvdman_cache_sector_size_count << 11) : 2048;
		fh->m_fd_rcvbuf = (u8 *)AllocSysMemory(1, fh->m_fd_rbsize, 0);
		if ( !fh->m_fd_rcvbuf )
		{
			VERBOSE_KPRINTF(1, "Rcvbuf MemAlloc Fail\n");
			CpuResumeIntr(state);
			return -12;
		}
		CpuResumeIntr(state);
		fh->m_cache_file_fd = -1;
		cache_result = open(cache_filename, 1539, 511);
		cache_file_fd_new = cache_result;
		if ( cache_result >= 0 )
		{
			u32 file_size_sectors; // $a0
			unsigned int file_size_bsr_6; // $v1

			file_size_sectors = (fh->m_file_size >> 11) + ((( (fh->m_file_size & 0x7FF) != 0 ) ? 1 : 0));
			file_size_bsr_3 = (file_size_sectors >> 3) + (( file_size_sectors & 7 ) ? 1 : 0);
			file_size_bsr_6 = (file_size_bsr_3 >> 3) + (( (file_size_bsr_3 & 7) != 0 ) ? 1 : 0);
			file_size_bsr_17 = (file_size_bsr_6 >> 11) + (( (file_size_bsr_6 & 0x7FF) != 0 ) ? 1 : 0);
			ioctl_arg = (file_size_bsr_17 + file_size_sectors + 8) << 11;
			for ( i = 0; i < fh->m_fd_rbsize; i += 1 )
			{
				fh->m_fd_rcvbuf[i] = 0;
			}
			if ( !strncmp(cache_filename, "pfs", 3) )
			{
				cache_result = ioctl2(cache_file_fd_new, 28673, &ioctl_arg, 4u, 0, 0);
			}
		}
		if ( cache_result >= 0 )
		{
			cache_result = lseek(cache_file_fd_new, 0, 0);
		}
		if ( cache_result >= 0 )
		{
			for ( i = 0; i <= 0x7FFF; i += 1 )
			{
				((char *)g_cdvdman_temp_buffer_ptr)[i] = 0;
			}
			for ( i = 0; (int)i < (int)(ioctl_arg >> 15); i += 1 )
			{
				cache_result = write(cache_file_fd_new, g_cdvdman_temp_buffer_ptr, 0x8000);
				if ( cache_result != 0x8000 )
				{
					if ( cache_result >= 0 )
					{
						cache_result = -5;
					}
					break;
				}
			}
		}
		if ( cache_result >= 0 )
		{
			for ( i = 0; (int)i < (int)((ioctl_arg >> 11) - 16 * (ioctl_arg >> 15)); i += 1 )
			{
				cache_result = write(cache_file_fd_new, fh->m_fd_rcvbuf, 2048);
				if ( cache_result != 2048 )
				{
					if ( cache_result >= 0 )
					{
						cache_result = -5;
					}
					break;
				}
			}
		}
	}
	if ( !open_or_close || cache_result < 0 )
	{
		if ( fh->m_cache_file_fd != -1 )
		{
			cache_remove_result = close(fh->m_cache_file_fd);
			VERBOSE_KPRINTF(1, "Cache File Close: %d\n", cache_remove_result);
			if ( cache_remove_result >= 0 )
			{
				if ( !strncmp(cache_filename, "pfs", 3) )
				{
					cache_remove_result = remove(cache_filename);
				}
				else if ( !strncmp(cache_filename, "host", 4) )
				{
					cache_remove_result = 0;
					remove(cache_filename);
				}
				VERBOSE_KPRINTF(1, "Cache File %s remove: %d\n", cache_filename, cache_remove_result);
			}
		}
		fh->m_cache_file_fd = -1;
		fh->m_max_cluster = 0;
		fh->m_cluster_cur = -1;
		fh->m_sector_count_total = 0;
		CpuSuspendIntr(&state);
		FreeSysMemory(fh->m_fd_rcvbuf);
		CpuResumeIntr(state);
		fh->m_fd_rcvbuf = 0;
		if ( cache_result < 0 )
		{
			VERBOSE_KPRINTF(1, "cdvd_odcinit Open  Error %d\n", cache_result);
		}
		if ( cache_remove_result < 0 )
		{
			VERBOSE_KPRINTF(1, "cdvd_odcinit Close Error %d\n", cache_remove_result);
		}
		return (!open_or_close) ? cache_remove_result : cache_result;
	}
	fh->m_sector_count_total = file_size_bsr_17 << 11;
	fh->m_cache_file_fd = cache_file_fd_new;
	fh->m_max_cluster = (void *)file_size_bsr_3;
	fh->m_cluster_cur = -1;
	VERBOSE_KPRINTF(1, "Cache File Maked\n");
	return 0;
}
// 400F58: conditional instruction was optimized away because $s1.4>=0

//----- (0040111C) --------------------------------------------------------
int __cdecl cdvdman_cache_invalidate(CDVDMAN_FILEDATA *filedata, int index)
{
	u32 i; // $s0
	int fileio_res; // $s1

	if ( filedata->m_cluster_cur == -1 )
	{
		return 0;
	}
	filedata->m_cluster_cur = -1;
	for ( i = 0; i < filedata->m_fd_rbsize; i += 1 )
	{
		filedata->m_fd_rcvbuf[i] = 0;
	}
	fileio_res = lseek(filedata->m_cache_file_fd, 0, 0);
	if ( fileio_res >= 0 )
	{
		for ( i = 0; i < ((unsigned int)filedata->m_sector_count_total >> 11); i += 1 )
		{
			fileio_res = write(filedata->m_cache_file_fd, filedata->m_fd_rcvbuf, 2048);
			if ( fileio_res < 0 )
			{
				break;
			}
		}
		if ( fileio_res >= 0 )
		{
			return fileio_res;
		}
	}
	filedata->m_fd_flags &= ~4u;
	cdvd_odcinit(filedata, 0, index);
	return fileio_res;
}

//----- (00401228) --------------------------------------------------------
int __cdecl cdvdman_invcaches()
{
	unsigned int i; // $s0

	for ( i = 0; i < (sizeof(g_cdvdman_handles)/sizeof(g_cdvdman_handles[0])); i += 1 )
	{
		if ( (g_cdvdman_handles[i].m_fd_flags & 4) != 0 )
		{
			cdvdman_cache_invalidate(&g_cdvdman_handles[i], i);
		}
	}
	return 0;
}

//----- (004012A0) --------------------------------------------------------
int __fastcall cdrom_internal_cache_read(const iop_file_t *f, int nbytes)
{
	CDVDMAN_FILEDATA *filedata; // $s0
	s16 readpos_plus_nbytes; // $v0
	unsigned int readpos_plus_nbytes_bsr_14; // $s2
	int readpos_bsr_14; // $s3
	int cluster_cur; // $a1
	unsigned int i; // $a0

	filedata = &g_cdvdman_handles[(int)f->privdata];
	if ( cdvdman_devready() < 0 )
	{
		g_cdvdman_iocache = 0;
		return -16;
	}
	if ( filedata->m_cluster_cur == -1 )
	{
		if ( (void *)(8 * filedata->m_fd_rbsize) < filedata->m_max_cluster )
		{
			filedata->m_cluster_cur = (filedata->m_read_pos >> 14) & 0xFFFFFFF8;
			if ( lseek(filedata->m_cache_file_fd, filedata->m_cluster_cur >> 3, 0) < 0
				|| read(filedata->m_cache_file_fd, filedata->m_fd_rcvbuf, filedata->m_fd_rbsize) < 0 )
			{
				filedata->m_cluster_cur = -1;
				return -5;
			}
		}
		else
		{
			filedata->m_cluster_cur = -2;
		}
	}
	readpos_plus_nbytes = filedata->m_read_pos + nbytes;
	readpos_plus_nbytes_bsr_14 = (readpos_plus_nbytes >> 14) - (( (readpos_plus_nbytes & 0x3FFF) == 0 ) ? 1 : 0);
	readpos_bsr_14 = filedata->m_read_pos >> 14;
	VERBOSE_KPRINTF(1, "max_claster %d meta_size_clst %d claster_cur %d\n", filedata->m_max_cluster, 8 * filedata->m_fd_rbsize, filedata->m_cluster_cur);
	cluster_cur = filedata->m_cluster_cur;
	if ( cluster_cur < 0 )
	{
		cluster_cur = 0;
	}
	else if ( (unsigned int)readpos_bsr_14 < (unsigned int)cluster_cur
				 || readpos_plus_nbytes_bsr_14 >= cluster_cur + 8 * filedata->m_fd_rbsize )
	{
		int cluster_write_tmp2; // $s1
		unsigned int readpos_band; // $v0

		if ( lseek(filedata->m_cache_file_fd, cluster_cur >> 3, 0) < 0 )
		{
			filedata->m_cluster_cur = -1;
			return -5;
		}
		cluster_write_tmp2 = (unsigned int)filedata->m_max_cluster >= filedata->m_cluster_cur + 8 * filedata->m_fd_rbsize ? filedata->m_fd_rbsize : ((unsigned int)filedata->m_max_cluster - filedata->m_cluster_cur + 7) >> 3;
		if ( write(filedata->m_cache_file_fd, filedata->m_fd_rcvbuf, cluster_write_tmp2) != cluster_write_tmp2 )
		{
			filedata->m_cluster_cur = -1;
			return -5;
		}
		readpos_band = readpos_bsr_14 & 0xFFFFFFF8;
		filedata->m_cluster_cur = readpos_band;
		readpos_band += ( readpos_bsr_14 < 0 ) ? 7 : 0;
		if ( (lseek(filedata->m_cache_file_fd, readpos_band >> 3, 0) < 0) || (read(filedata->m_cache_file_fd, filedata->m_fd_rcvbuf, ( (unsigned int)filedata->m_max_cluster < filedata->m_cluster_cur + 8 * filedata->m_fd_rbsize ) ? (((unsigned int)filedata->m_max_cluster - filedata->m_cluster_cur + 7) >> 3) : (filedata->m_fd_rbsize)) < 0) )
		{
			filedata->m_cluster_cur = -1;
			return -5;
		}
		cluster_cur = filedata->m_cluster_cur;
	}
	for ( i = readpos_bsr_14; i <= readpos_plus_nbytes_bsr_14; i += 1 )
	{
		if ( !(((int)filedata->m_fd_rcvbuf[(i - cluster_cur) >> 3] >> ((i - cluster_cur) & 7)) & 1) )
		{
			break;
		}
	}
	return i <= readpos_plus_nbytes_bsr_14;
}

//----- (00401560) --------------------------------------------------------
int __fastcall cdrom_internal_write_cache(const iop_file_t *f, unsigned int nbytes)
{
	int lseek_result; // $v0
	CDVDMAN_FILEDATA *filedata; // $s1
	unsigned int cur; // $s7
	unsigned int rst; // $s3
	int cluster_cur; // $fp
	int write_ret; // $s0
	unsigned int i; // $s2
	int tray_open; // $s0
	int Error; // $a1
	sceCdRMode rmode[2]; // [sp+18h] [-8h] BYREF

	g_cdvdman_iocache = 0;
	if ( cdvdman_devready() < 0 )
	{
		return -16;
	}
	filedata = &g_cdvdman_handles[(int)f->privdata];
	if ( nbytes > filedata->m_file_size - filedata->m_read_pos )
	{
		nbytes = filedata->m_file_size - filedata->m_read_pos;
	}
	if ( !nbytes )
	{
		return 0;
	}
	VERBOSE_KPRINTF(1, "_cdvdfile_cache_read %d<->%d\n", filedata->m_read_pos, filedata->m_read_pos + nbytes);
	cur = ((filedata->m_read_pos + nbytes) >> 14) - (( ((filedata->m_read_pos + nbytes) & 0x3FFF) == 0 ) ? 1 : 0);
	rst = filedata->m_read_pos >> 14;
	cluster_cur = ( filedata->m_cluster_cur < 0 ) ? 0 : filedata->m_cluster_cur;
	cdvdman_iormode(rmode, filedata->m_filemode, f->unit);
	write_ret = 0;
	VERBOSE_KPRINTF(1, "cache_fill rst:%d<->%d cur:%d cnt:%d\n", rst, cur, filedata->m_read_pos, nbytes);
	for ( i = rst; i <= cur; i += 1 )
	{
		VERBOSE_KPRINTF(1, "FIO Usr addr LSN:%d SEC:%d ADDR:%08x cpos= %d\n", filedata->m_file_lsn + 8 * i, 8, g_cdvdman_temp_buffer_ptr, (i * 0x4000) + filedata->m_sector_count_total);
		if ( (((int)filedata->m_fd_rcvbuf[(i - cluster_cur) >> 3] >> ((i - cluster_cur) & 7)) & 1) == 0 )
		{
			tray_open = 0;
			while ( !sceCdRE(filedata->m_file_lsn + 8 * i, 8u, g_cdvdman_temp_buffer_ptr, rmode) )
			{
				if ( (sceCdStatus() & 1) != 0 )
				{
					g_cdvdman_iocache = 0;
					tray_open = 1;
					break;
				}
				DelayThread(10000);
			}
			sceCdSync(0);
			Error = sceCdGetError();
			if ( Error || tray_open )
			{
				VERBOSE_KPRINTF(0, "Read Error= 0x%02x\n", Error);
				return -70;
			}
			lseek_result = lseek(filedata->m_cache_file_fd, (i * 0x4000) + filedata->m_sector_count_total, 0);
			if ( lseek_result < 0 )
			{
				return lseek_result;
			}
			write_ret = write(filedata->m_cache_file_fd, g_cdvdman_temp_buffer_ptr, 0x4000);
			if ( write_ret != 0x4000 )
			{
				VERBOSE_KPRINTF(1, "write: ret:%d\n", write_ret);
				if ( write_ret >= 0 )
				{
					return -5;
				}
				break;
			}
			filedata->m_fd_rcvbuf[(i - cluster_cur) >> 3] |= 1 << ((i - cluster_cur) & 7);
		}
	}
	return write_ret;
}

//----- (00401878) --------------------------------------------------------
int __cdecl cdvdfile_cache_read(const iop_file_t *f, void *buf, int nbyte)
{
	int nbyte_tmp; // $s1
	int fd_result; // $v0
	CDVDMAN_FILEDATA *filedata; // $s0

	nbyte_tmp = nbyte;
	if ( nbyte < 0 )
	{
		return -22;
	}
	filedata = &g_cdvdman_handles[(int)f->privdata];
	if ( (unsigned int)nbyte > filedata->m_file_size - filedata->m_read_pos )
	{
		nbyte_tmp = filedata->m_file_size - filedata->m_read_pos;
	}
	VERBOSE_KPRINTF(1, "_cdvdfile_cache_read %d<->%d\n", filedata->m_read_pos, filedata->m_read_pos + nbyte_tmp);
	fd_result = 0;
	if ( nbyte_tmp > 0 )
	{
		fd_result = lseek(filedata->m_cache_file_fd, filedata->m_read_pos + filedata->m_sector_count_total, 0);
		if ( fd_result >= 0 )
		{
			fd_result = read(filedata->m_cache_file_fd, buf, nbyte_tmp);
			filedata->m_read_pos += ( fd_result >= 0 ) ? fd_result : 0;
		}
	}
	return fd_result;
}

//----- (00401970) --------------------------------------------------------
int __cdecl cdvdfile_cache_fill_read(const iop_file_t *f, void *buf, int nbytes)
{
	int op_result; // $v0

	op_result = cdvdman_devready();
	if ( op_result >= 0 )
	{
		op_result = cdrom_internal_write_cache(f, nbytes);
		if ( op_result >= 0 )
		{
			op_result = cdvdfile_cache_read(f, buf, nbytes);
		}
	}
	else
	{
		g_cdvdman_iocache = 0;
	}
	return op_result;
}

//----- (004019E0) --------------------------------------------------------
int __cdecl cdrom_open(iop_file_t *f, const char *name, int mode, int arg4)
{
	int fds1; // $s1
	unsigned int i; // $s0
	int emptyfdfound; // $a0
	int streamfdfound; // $a1
	CDVDMAN_FILEDATA *filedata; // $s1
	int devready_tmp; // $s0
	char filename[128]; // [sp+18h] [-C8h] BYREF
	sceCdlFILE fileinfo; // [sp+98h] [-48h] BYREF
	u32 efbits; // [sp+D8h] [-8h] BYREF

	(void)arg4;
	devready_tmp = 0;
	fds1 = 0;
	VERBOSE_PRINTF(1, "fileIO OPEN name= %s mode= 0x%08x layer %d\n", name, mode, f->unit);
	WaitEventFlag(g_fio_fsv_evid, 1u, 16, &efbits);
	emptyfdfound = 0;
	streamfdfound = 0;
	for ( i = 0; i < (sizeof(g_cdvdman_handles)/sizeof(g_cdvdman_handles[0])); i += 1 )
	{
		if ( !g_cdvdman_handles[i].m_fd_flags && !emptyfdfound )
		{
			fds1 = i;
			emptyfdfound = 1;
		}
		if ( (g_cdvdman_handles[i].m_fd_flags & 8) != 0 )
		{
			streamfdfound = 1;
		}
	}
	if ( !emptyfdfound || streamfdfound )
	{
		PRINTF("open fail name %s\n", name);
		SetEventFlag(g_fio_fsv_evid, 1u);
		return -24;
	}
	f->privdata = (void *)fds1;
	filedata = &g_cdvdman_handles[fds1];
	strncpy(filename, name, sizeof(filename));
	cdvdman_cdfname(filename);
	g_cdvdman_srchspd = ( (mode & 0x40000000) != 0 || cdvdman_l0check(f->unit) ) ? 0 : ((g_cdvdman_spinnom == -1) ? (unsigned __int16)mode : g_cdvdman_spinnom != 0);
	if ( (unsigned int)(f->unit) >= 2u )
	{
		devready_tmp = -2;
	}
	else
	{
		if ( !strncmp(name, "sce_cdvd_lsn", 12) )
		{
			strncpy(filename, name, sizeof(filename));
			// Unofficial: Avoid out of bounds access
			for ( i = 12; i < (sizeof(filename) - 5) && filename[i] && filename[i] != 95; i += 1 );
			if ( !filename[i] || i >= (sizeof(filename) - 5) )
			{
				devready_tmp = -2;
			}
			else
			{
				fileinfo.size = strtol(&filename[i + 5], 0, 10);
				filename[i] = 0;
				fileinfo.lsn = strtol(&filename[12], 0, 10);
				if ( f->unit )
				{
					if ( cdvdman_devready() < 0 || !DvdDual_infochk() )
					{
						devready_tmp = -2;
					}
					else
					{
						fileinfo.lsn += g_cdvdman_istruct.m_layer_1_lsn;
					}
				}
			}
		}
		else
		{
			devready_tmp = cdvdman_devready();
			if ( devready_tmp < 0 )
			{
				SetEventFlag(g_fio_fsv_evid, 1u);
				return devready_tmp;
			}
			if ( !sceCdLayerSearchFile(&fileinfo, filename, f->unit) )
			{
				devready_tmp = -2;
			}
		}
	}
	if ( devready_tmp < 0 )
	{
		PRINTF("open fail name %s\n", filename);
		SetEventFlag(g_fio_fsv_evid, 1u);
		return devready_tmp;
	}
	filedata->m_fd_flags = 1;
	g_cdvdman_srchspd = 0;
	if ( (mode & 0x40000000) != 0 )
	{
		sceCdRMode rmode;
		memset(&rmode, 0, sizeof(rmode));
		rmode.datapattern = 0;
		rmode.spindlctrl = 0;
		rmode.trycount = (g_cdvdman_trycnt == -1) ? 0 : g_cdvdman_trycnt;
		// The following call to sceCdStStart was inlined
		if ( !sceCdStStart(fileinfo.lsn, &rmode) )
		{
			filedata->m_fd_flags = 0;
			SetEventFlag(g_fio_fsv_evid, 1u);
			return -2;
		}
		g_cdvdman_strmerr = 0;
		filedata->m_fd_flags |= 8;
	}
	filedata->m_file_lsn = fileinfo.lsn;
	filedata->m_read_pos = 0;
	filedata->m_filemode = mode & 0xBFFFFFFF;
	filedata->m_file_size = fileinfo.size;
	filedata->m_fd_layer = f->unit;
	if ( (mode & 0x50000000) == 0x10000000 )
	{
		devready_tmp = -19;
		if ( g_cache_path_fd != -1 )
		{
			devready_tmp = cdvd_odcinit(filedata, 1, (int)f->privdata);
			if ( devready_tmp >= 0 )
			{
				filedata->m_fd_flags |= 4u;
			}
		}
	}
	if ( devready_tmp < 0 )
	{
		filedata->m_fd_flags = 0;
		filedata->m_fd_layer = 0;
		filedata->m_filemode = 0;
		filedata->m_read_pos = 0;
		filedata->m_file_size = 0;
		filedata->m_file_lsn = 0;
		SetEventFlag(g_fio_fsv_evid, 1u);
		return devready_tmp;
	}
	f->mode = 1;
	SetEventFlag(g_fio_fsv_evid, 1u);
	return 0;
}

//----- (00401EF0) --------------------------------------------------------
int __cdecl cdrom_close(iop_file_t *f)
{
	CDVDMAN_FILEDATA *filedata; // $s0
	u32 efbits; // [sp+30h] [-8h] BYREF

	VERBOSE_PRINTF(1, "fileIO CLOSE\n");
	WaitEventFlag(g_fio_fsv_evid, 1u, 16, &efbits);
	filedata = &g_cdvdman_handles[(int)f->privdata];
	if ( (filedata->m_fd_flags & 8) != 0 )
	{
		g_cdvdman_strmerr = 0;
		// The following call to sceCdStStop was inlined
		if ( !sceCdStStop() )
		{
			SetEventFlag(g_fio_fsv_evid, 1u);
			return -5;
		}
	}
	if ( ((filedata->m_fd_flags & 0xC) == 4 && cdvd_odcinit(filedata, 0, (int)f->privdata) < 0) )
	{
		SetEventFlag(g_fio_fsv_evid, 1u);
		return -5;
	}
	filedata->m_file_lsn = 0;
	filedata->m_file_size = 0;
	filedata->m_read_pos = 0;
	filedata->m_fd_flags = 0;
	filedata->m_fd_layer = 0;
	filedata->m_filemode = 1;
	f->mode = 0;
	SetEventFlag(g_fio_fsv_evid, 1u);
	return 0;
}

//----- (00402050) --------------------------------------------------------
int __fastcall cdrom_internal_read(const iop_file_t *f, char *addr, int nbytes)
{
	unsigned int sectors; // $s6
	int op_result; // $v0
	int nbytes_segment; // $s5
	int nbytes_div_2048; // $a1
	unsigned int sec; // $s2
	int read_error; // $v0
	unsigned int sectors_count; // $s0
	int Error; // $v0
	sceCdRMode rmode[2]; // [sp+10h] [-28h] BYREF
	int i; // [sp+18h] [-20h]
	unsigned int filesize_bsr_11; // [sp+28h] [-10h]
	CDVDMAN_FILEDATA *filedata; // [sp+30h] [-8h]
	void *buf; // [sp+34h] [-4h]

	sectors = 1;
	VERBOSE_PRINTF(1, "cdvd fileIO read start\n");
	op_result = cdvdman_devready();
	if ( op_result < 0 )
	{
		g_cdvdman_iocache = 0;
		return op_result;
	}
	filedata = &g_cdvdman_handles[(_DWORD)f->privdata];
	cdvdman_iormode(rmode, filedata->m_filemode, f->unit);
	if ( nbytes < 0 )
	{
		return -22;
	}
	if ( (unsigned int)nbytes > filedata->m_file_size - filedata->m_read_pos )
	{
		nbytes = filedata->m_file_size - filedata->m_read_pos;
	}
	filesize_bsr_11 = (filedata->m_file_size >> 11) + (( (filedata->m_file_size & 0x7FF) != 0 ) ? 1 : 0) + filedata->m_file_lsn;
	VERBOSE_PRINTF(1, "fds= %d read file_lbn= %d offset= %d\n", (int)(uiptr)f->privdata, (int)filedata->m_file_lsn, (int)filedata->m_read_pos);
	buf = 0;
	for ( i = 0; i < nbytes; i += nbytes_segment )
	{
		unsigned int lbn; // $s1
		int pos_extra; // $s4
		int lbn_tmp; // [sp+1Ch] [-1Ch]
		int pos_sub_2048; // [sp+2Ch] [-Ch]
		int nbytes_cur;

		nbytes_cur = nbytes - i;
		if ( g_cdvdman_spinctl != -1 )
		{
			rmode[0].spindlctrl = g_cdvdman_spinctl;
			switch ( g_cdvdman_spinctl )
			{
				case 0:
					filedata->m_filemode = 0;
					break;
				case 1:
					filedata->m_filemode = 1;
					break;
				case 2:
					filedata->m_filemode = 2;
					break;
				case 3:
					filedata->m_filemode = 3;
					break;
				case 4:
					filedata->m_filemode = 4;
					break;
				case 5:
					filedata->m_filemode = 5;
					break;
				default:
					filedata->m_filemode = 1;
					break;
			}
		}
		pos_sub_2048 = 0;
		lbn = filedata->m_file_lsn + ((filedata->m_read_pos + i) >> 11);
		lbn_tmp = lbn;
		pos_extra = (filedata->m_read_pos + i) & 0x7FF;
		if ( nbytes_cur <= 0x4000 )
		{
			nbytes_segment = nbytes_cur;
			nbytes_div_2048 = (nbytes_cur / 2048) + (( (nbytes_cur & 0x7FF) != 0 ) ? 1 : 0);
			sectors = nbytes_div_2048 + (pos_extra != 0);
		}
		else
		{
			nbytes_segment = 0x4000;
			if ( buf && ((filedata->m_read_pos + i) & 0x7FF) != 0 && g_cdvdman_iocache )
			{
				++lbn;
				pos_sub_2048 = 2048 - pos_extra;
				cdvdman_memcpy(
					addr + i,
					(const char *)g_cdvdman_temp_buffer_ptr + 2048 * (sectors - 1) + pos_extra,
					2048 - pos_extra);
				g_cdvdman_iocache = 0;
				sectors = 8;
			}
			else
			{
				sectors = 8 + (( ((filedata->m_read_pos + i) & 0x7FF) != 0 ) ? 1 : 0);
			}
		}
		buf = g_cdvdman_temp_buffer_ptr;
		if ( (unsigned int)(sectors) > filesize_bsr_11 - lbn )
		{
			sectors = filesize_bsr_11 - lbn;
		}
		VERBOSE_PRINTF(1, "sce_Read LBN= %d sectors= %d\n", (int)lbn, (int)sectors);
		if ( g_cdvdman_iocache && (lbn >= g_cdvdman_lcn_offset) && (g_cdvdman_lcn_offset + g_cdvdman_numbytes_offset >= lbn + sectors) )
		{
			cdvdman_memcpy(addr + i, (char *)buf + 2048 * (lbn - g_cdvdman_lcn_offset) + pos_extra, nbytes_segment);
		}
		else if ( ((uiptr)(addr + i) & 3) || pos_extra || (nbytes_segment != 0x4000) )
		{
			sec = ( sectors >= 8 ) ? sectors : 8;
			if ( sec > filesize_bsr_11 - lbn )
			{
				sec = filesize_bsr_11 - lbn;
			}
			VERBOSE_PRINTF(1, "FIO Cache LSN:%d SEC:%d ADDR:%08x\n", (int)lbn, (int)sec, (unsigned int)(uiptr)buf);
			sectors_count = ( sec >= 9 ) ? (sec - 8) : 0;
			if ( sectors_count )
			{
				while ( !sceCdRE(lbn, sectors_count, buf, rmode) )
				{
					VERBOSE_PRINTF(1, "sce_Read ON Delay\n");
					if ( (sceCdStatus() & 1) != 0 )
					{
						g_cdvdman_iocache = 0;
						g_cdvdman_spinctl = -1;
						return -5;
					}
					DelayThread(10000);
				}
				sceCdSync(0);
				Error = sceCdGetError();
				if ( Error )
				{
					PRINTF("Read Error= 0x%02x\n", Error);
					g_cdvdman_iocache = 0;
					break;
				}
			}
			while ( !sceCdRE(lbn + sectors_count, sec - sectors_count, (char *)buf + 2048 * sectors_count, rmode) )
			{
				VERBOSE_PRINTF(1, "sce_Read ON Delay\n");
				if ( (sceCdStatus() & 1) != 0 )
				{
					g_cdvdman_iocache = 0;
					g_cdvdman_spinctl = -1;
					return -5;
				}
				DelayThread(10000);
			}
			sceCdSync(0);
			Error = sceCdGetError();
			if ( Error )
			{
				PRINTF("Read Error= 0x%02x\n", Error);
				g_cdvdman_iocache = 0;
				break;
			}
			g_cdvdman_lcn_offset = lbn_tmp;
			g_cdvdman_numbytes_offset = sec;
			g_cdvdman_iocache = 1;
			cdvdman_memcpy(((char *)&addr[pos_sub_2048] + i), (const char *)g_cdvdman_temp_buffer_ptr + (pos_sub_2048 ? 0 : pos_extra), nbytes_segment - pos_sub_2048);
		}
		else
		{
			VERBOSE_PRINTF(1, "FIO Usr addr LSN:%d SEC:%d ADDR:%08x\n", (int)lbn, (int)sectors, (unsigned int)(uiptr)(addr + i));
			while ( !sceCdRE(lbn, sectors, addr + i, rmode) )
			{
				VERBOSE_PRINTF(1, "sce_Read ON Delay\n");
				if ( (sceCdStatus() & 1) != 0 )
				{
					g_cdvdman_iocache = 0;
					g_cdvdman_spinctl = -1;
					return -5;
				}
				DelayThread(10000);
			}
			sceCdSync(0);
			read_error = sceCdGetError();
			g_cdvdman_iocache = 0;
			if ( read_error )
			{
				PRINTF("Read Error= 0x%02x\n", read_error);
				break;
			}
		}
		if ( nbytes_segment <= 0 )
		{
			g_cdvdman_spinctl = -1;
			return nbytes_segment;
		}
	}
	filedata->m_read_pos += i;
	VERBOSE_PRINTF(1, "fileIO read ended\n");
	g_cdvdman_spinctl = -1;
	return i;
}

//----- (00402740) --------------------------------------------------------
int __fastcall cdrom_stream_read(const iop_file_t *f, char *bbuf, int nbytes)
{
	CDVDMAN_FILEDATA *filedata; // $s0
	sceCdRMode rmode; // [sp+18h] [-28h] BYREF
	int buf; // [sp+38h] [-8h] BYREF

	filedata = &g_cdvdman_handles[(int)f->privdata];
	g_cdvdman_strmerr = 0;
	cdvdman_iormode(&rmode, filedata->m_filemode, f->unit);
	rmode.spindlctrl = 0;
	rmode.trycount = 0;
	// The following sceCdStRead call was inlined
	buf = sceCdStRead(nbytes >> 11, (u32 *)bbuf, 0, (u32 *)&g_cdvdman_strmerr);
	filedata->m_read_pos += buf << 11;
	return buf << 11;
}

//----- (00402828) --------------------------------------------------------
int __cdecl cdrom_read(iop_file_t *f, void *buf, int nbytes)
{
	CDVDMAN_FILEDATA *filedata; // $s1
	int rc; // $s0
	u32 efbits[2]; // [sp+10h] [-8h] BYREF

	if ( nbytes < 0 )
	{
		return -22;
	}
	WaitEventFlag(g_fio_fsv_evid, 1u, 16, efbits);
	filedata = &g_cdvdman_handles[(int)f->privdata];
	if ( cdvdman_mediactl(2) )
	{
		g_cdvdman_iocache = 0;
		cdvdman_invcaches();
	}
	if ( (filedata->m_fd_flags & 8) != 0 )
	{
		rc = cdrom_stream_read(f, (char *)buf, nbytes);
	}
	else
	{
		if ( (filedata->m_fd_flags & 4) == 0 )
		{
			rc = cdrom_internal_read(f, (char *)buf, nbytes);
		}
		else
		{
			rc = cdrom_internal_cache_read(f, nbytes);
			if ( rc )
			{
				if ( rc != -16 )
				{
					if ( rc != 1 )
					{
						filedata->m_fd_flags &= ~4u;
						rc = -5;
						cdvd_odcinit(filedata, 0, (int)f->privdata);
					}
					else
					{
						rc = cdvdfile_cache_fill_read(f, buf, nbytes);
						VERBOSE_KPRINTF(1, "called _cdvdfile_cache_fill_read %d\n", rc);
					}
				}
			}
			else
			{
				rc = cdvdfile_cache_read(f, buf, nbytes);
				VERBOSE_KPRINTF(1, "called _cdvdfile_cache_read %d\n", rc);
			}
			if ( rc == -16 || rc == -70 )
			{
				cdvdman_cache_invalidate(filedata, (int)f->privdata);
				KPRINTF("_cdvdfile_cache Read_err OR Drive_not_ready\n", rc);
			}
			if ( rc < 0 )
			{
				rc = cdrom_internal_read(f, (char *)buf, nbytes);
			}			
		}
	}
	SetEventFlag(g_fio_fsv_evid, 1u);
	return rc;
}

//----- (00402A2C) --------------------------------------------------------
int __fastcall cdrom_ioctl(iop_file_t *f, int arg, void *param)
{
	(void)f;

	switch ( arg )
	{
		case 0x10000:
			g_cdvdman_spinnom = -1;
			sceCdSpinCtrlIOP((u32)param);
			return 0;
		default:
			return -5;
	}
}

//----- (00402A7C) --------------------------------------------------------
int __cdecl cdrom_ioctl2(iop_file_t *f, int request, void *argp, size_t arglen, void *bufp, size_t buflen)
{
	const CDVDMAN_FILEDATA *filedata; // $v1
	int retval; // $s0
	u32 efbits; // [sp+30h] [-8h] BYREF

	(void)argp;
	(void)arglen;
	(void)bufp;
	(void)buflen;

	WaitEventFlag(g_fio_fsv_evid, 1u, 16, &efbits);
	filedata = &g_cdvdman_handles[(int)f->privdata];
	retval = -5;
	if ( (filedata->m_fd_flags & 8) != 0 )
	{
		switch ( request )
		{
			case 0x630d:
				// The following call to sceCdStPause was inlined
				if ( sceCdStPause() )
				{
					retval = 0;
				}
				break;
			case 0x630e:
				// The following call to sceCdStResume was inlined
				if ( sceCdStResume() )
				{
					retval = 0;
				}
				break;
			case 0x630f:
				// The following call to sceCdStStat was inlined
				// Unofficial: return 0 instead of negative value
				retval = sceCdStStat();
				break;
			default:
				break;
		}
	}
	SetEventFlag(g_fio_fsv_evid, 1u);
	return retval;
}

//----- (00402C44) --------------------------------------------------------
int __cdecl cdrom_devctl(
				iop_file_t *f,
				const char *a2,
				int cmd,
				void *argp,
				unsigned int arglen,
				void *bufp,
				unsigned int buflen)
{
	unsigned int i; // $s0
	int retval2; // $s1
	char *sc_tmp_2; // $v1
	unsigned int sc_tmp_3; // $a1
	u32 efbits; // [sp+30h] [-10h] BYREF
	int on_dual_tmp; // [sp+34h] [-Ch] BYREF

	(void)f;
	(void)a2;
	(void)buflen;

	retval2 = 0;
	if ( cmd == 0x4328 )
	{
		if ( !sceCdBreak() )
		{
			retval2 = -5;
		}
		sceCdSync(4);
		return retval2;
	}
	WaitEventFlag(g_fio_fsv_evid, 1u, 16, &efbits);
	switch ( cmd )
	{
		case 0x430C:
			for ( i = 0; i < 3 && !retval2; i += 1 )
			{
				WaitEventFlag(g_scmd_evid, 1u, 0, &efbits);
				retval2 = sceCdReadClock((sceCdCLOCK *)bufp);
			}
			retval2 = (retval2 != 1) ? -5 : 0;
			break;
		case 0x431D:
			for ( i = 0; i < 3 && !retval2; i += 1 )
			{
				WaitEventFlag(g_scmd_evid, 1u, 0, &efbits);
				retval2 = sceCdReadGUID((u64 *)bufp);
			}
			retval2 = (retval2 != 1) ? -5 : 0;
			break;
		case 0x431E:
			retval2 = (sceCdReadDiskID((unsigned int *)bufp) != 1) ? -5 : 0;
			break;
		case 0x431F:
			*(_DWORD *)bufp = sceCdGetDiskType();
			break;
		case 0x4320:
			*(_DWORD *)bufp = g_cdvdman_strmerr ? g_cdvdman_strmerr : sceCdGetError();
			break;
		case 0x4321:
			retval2 = (sceCdTrayReq(*(_DWORD *)argp, (u32 *)bufp) != 1) ? -5 : 0;
			break;
		case 0x4322:
			*(_DWORD *)bufp = sceCdStatus();
			break;
		case 0x4323:
			for ( i = 0; i < 3 && !retval2; i += 1 )
			{
				WaitEventFlag(g_scmd_evid, 1u, 0, &efbits);
				retval2 = sceCdPowerOff((u32 *)bufp);
			}
			retval2 = (retval2 != 1) ? -5 : 0;
			break;
		case 0x4324:
			sceCdMmode(*(_DWORD *)argp);
			break;
		case 0x4325:
			*(_DWORD *)bufp = sceCdDiskReady(*(_DWORD *)argp);
			break;
		case 0x4326:
			for ( i = 0; i < 3 && !retval2; i += 1 )
			{
				WaitEventFlag(g_scmd_evid, 1u, 0, &efbits);
				retval2 = sceCdReadModelID((unsigned int *)bufp);
			}
			retval2 = (retval2 != 1) ? -5 : 0;
			break;
		case 0x4327:
			// The following call to sceCdStInit was inlined
			retval2 = ( sceCdStInit(*(_DWORD *)argp, *((_DWORD *)argp + 1), (void *)*((_DWORD *)argp + 2)) ) ? 0 : -5;
			break;
		case 0x4380:
			g_cdvdman_spinnom = 1;
			break;
		case 0x4381:
			g_cdvdman_spinnom = 0;
			break;
		case 0x4382:
			g_cdvdman_trycnt = *(unsigned __int8 *)argp;
			break;
		case 0x4383:
			retval2 = (sceCdSeek(*(_DWORD *)argp) != 1) ? -5 : 0;
			sceCdSync(6);
			break;
		case 0x4384:
			retval2 = (sceCdStandby() != 1) ? -5 : 0;
			sceCdSync(4);
			break;
		case 0x4385:
			retval2 = (sceCdStop() != 1) ? -5 : 0;
			sceCdSync(4);
			break;
		case 0x4386:
			retval2 = (sceCdPause() != 1) ? -5 : 0;
			sceCdSync(6);
			break;
		case 0x4387:
			switch ( sceCdGetDiskType() )
			{
				case 16:
				case 17:
				case 18:
				case 19:
					retval2 = (sceCdGetToc((u8 *)bufp) != 1) ? -5 : 0;
					break;
				default:
					break;
			}
			break;
		case 0x4388:
			retval2 = (sceCdSetTimeout(1, *(_DWORD *)argp) != 1) ? -5 : 0;
			break;
		case 0x4389:
			retval2 = (!sceCdReadDvdDualInfo(&on_dual_tmp, (unsigned int *)bufp)) ? -5 : 0;
			break;
		case 0x438A:
			sceCdInit(*(_DWORD *)argp);
			retval2 = 0;
			break;
		case 0x438C:
			g_cdvdman_spinnom = 2;
			break;
		case 0x438D:
			g_cdvdman_spinnom = 3;
			break;
		case 0x438E:
			g_cdvdman_spinnom = 4;
			break;
		case 0x438F:
			g_cdvdman_spinnom = 5;
			break;
		case 0x4390:
			g_cdvdman_spinnom = 20;
			break;
		case 0x4391:
			*(_DWORD *)bufp = sceCdSC('\xF5', &on_dual_tmp);
			break;
		case 0x4392:
			retval2 = (sceCdApplySCmd(*(_BYTE *)argp, (char *)argp + 4, arglen - 4, bufp) != 1) ? -5 : 0;
			break;
		case 0x4395:
			retval2 = -16;
			if ( g_cache_path_fd != -1 )
			{
				break;
			}
			retval2 = -22;
			sc_tmp_2 = (char *)argp;
			for ( i = 0; i < arglen && sc_tmp_2[i] && sc_tmp_2[i] != ','; i += 1 )
			{
				g_cdvdman_cache_name[i] = sc_tmp_2[i];
			}
			sc_tmp_3 = i;
			if ( i <= arglen )
			{
				i += 1;
				for ( ; (i < arglen) && sc_tmp_2[i] && sc_tmp_2[i] != ','; i += 1 )
				{
				}
			}
			if ( i <= arglen )
			{
				sc_tmp_2[i] = 0;
				g_cdvdman_cache_sector_size_count = strtol((const char *)argp + sc_tmp_3, 0, 10);
				retval2 = path_tbl_init(strtol(&sc_tmp_2[i + 1], 0, 10), g_cdvdman_cache_name, 1);
			}
			break;
		case 0x4397:
			for ( i = 0; i < (sizeof(g_cdvdman_handles)/sizeof(g_cdvdman_handles[0])); i += 1 )
			{
				if ( (g_cdvdman_handles[i].m_fd_flags & 4) != 0 )
				{
					break;
				}
			}
			retval2 = -16;
			if ( i == 16 )
			{
				retval2 = path_tbl_init(0, 0, 0);
			}
			break;
		default:
			retval2 = -5;
			break;
	}
	SetEventFlag(g_fio_fsv_evid, 1u);
	return retval2;
}
// 402ED0: conditional instruction was optimized away because $v1.4 is in (<10u|>=12u)

//----- (004032AC) --------------------------------------------------------
int __cdecl cdrom_lseek(iop_file_t *f, int offset, int pos)
{
	int retval; // $s1
	CDVDMAN_FILEDATA *filedata; // $s0
	u32 efbits; // [sp+30h] [-8h] BYREF

	retval = -1;
	VERBOSE_PRINTF(1, "fileIO SEEK\n");
	WaitEventFlag(g_fio_fsv_evid, 1u, 16, &efbits);
	filedata = &g_cdvdman_handles[(int)f->privdata];
	switch ( pos )
	{
		case 0:
			retval = offset;
			break;
		case 1:
			retval = filedata->m_read_pos + offset;
			break;
		case 2:
			retval = filedata->m_file_size - offset;
			break;
		default:
			break;
	}
	if ( retval > (int)(filedata->m_file_size) )
	{
		retval = filedata->m_file_size;
	}
	filedata->m_read_pos = retval;
	if ( (filedata->m_fd_flags & 8) != 0 )
	{
		// The following call to sceCdStSeekF was inlined
		if ( !sceCdStSeekF(filedata->m_file_lsn + retval / 2048) )
		{
			retval = -5;
		}
	}
	SetEventFlag(g_fio_fsv_evid, 1u);
	return retval;
}

//----- (00403464) --------------------------------------------------------
int __cdecl cdrom_nulldev()
{
	PRINTF("nulldev0 call\n");
	return -5;
}

//----- (0040348C) --------------------------------------------------------
s64 __cdecl cdrom_nulldev64()
{
	PRINTF("nulldev0 call\n");
	return -5LL;
}

//----- (004034C0) --------------------------------------------------------
int __cdecl sync_timeout_func(iop_sys_clock_t *timeout_ptr)
{
	KPRINTF("Cdvd Time Out %d(msec)\n", timeout_ptr->lo / 0x9000);
	return sceCdBreak() == 0;
}

//----- (00403504) --------------------------------------------------------
int __cdecl sceCdSetTimeout(int param, int timeout)
{
	if ( sceCdCheckCmd() == 0 || g_cdvdman_istruct.m_read2_flag )
	{
		return 0;
	}
	switch ( param )
	{
		case 1:
			g_cdvdman_sync_to = timeout;
			return 1;
		case 2:
			g_TimeOut2 = timeout;
			return 1;
		default:
			return 0;
	}
}

//----- (00403588) --------------------------------------------------------
int __cdecl sceCdSync(int mode)
{
	iop_sys_clock_t sysclk; // [sp+10h] [-30h] BYREF
	iop_event_info_t efinfo; // [sp+18h] [-28h] BYREF
	u32 resbits[2]; // [sp+38h] [-8h] BYREF

	VERBOSE_KPRINTF(1, "sceCdSync: Call mode %d Com %x\n", mode, (unsigned __int8)g_cdvdman_istruct.m_cdvdman_command);
	switch ( mode )
	{
		case 0:
			while ( !sceCdCheckCmd() || g_cdvdman_istruct.m_read2_flag )
			{
				WaitEventFlag(g_cdvdman_intr_efid, 1u, 0, resbits);
			}
			break;
		case 1:
			return (!sceCdCheckCmd() || (g_cdvdman_istruct.m_read2_flag != 0)) ? 1 : 0;
		case 3:
			sysclk.hi = 0;
			sysclk.lo = 0x9000 * g_cdvdman_sync_to;
			vSetAlarm(&sysclk, (unsigned int (__cdecl *)(void *))sync_timeout_func, &sysclk);
			while ( !sceCdCheckCmd() || g_cdvdman_istruct.m_read2_flag )
			{
				WaitEventFlag(g_cdvdman_intr_efid, 1u, 0, resbits);
			}
			vCancelAlarm((unsigned int (__cdecl *)(void *))sync_timeout_func, &sysclk);
			break;
		case 4:
			sysclk.hi = 0;
			sysclk.lo = 0x41EB0000;
			vSetAlarm(&sysclk, (unsigned int (__cdecl *)(void *))sync_timeout_func, &sysclk);
			while ( !sceCdCheckCmd() || g_cdvdman_istruct.m_read2_flag )
			{
				WaitEventFlag(g_cdvdman_intr_efid, 1u, 0, resbits);
			}
			vCancelAlarm((unsigned int (__cdecl *)(void *))sync_timeout_func, &sysclk);
			break;
		case 5:
			while ( !sceCdCheckCmd() )
			{
				WaitEventFlag(g_cdvdman_intr_efid, 1u, 0, resbits);
			}
			break;
		case 6:
			sysclk.hi = 0;
			sysclk.lo = 0x9000 * g_cdvdman_sync_to;
			vSetAlarm(&sysclk, (unsigned int (__cdecl *)(void *))sync_timeout_func, &sysclk);
			while ( !sceCdCheckCmd() || g_cdvdman_istruct.m_read2_flag )
			{
				WaitEventFlag(g_cdvdman_intr_efid, 1u, 0, resbits);
			}
			vCancelAlarm((unsigned int (__cdecl *)(void *))sync_timeout_func, &sysclk);
			break;
		case 16:
			while ( !sceCdCheckCmd() || g_cdvdman_istruct.m_read2_flag || g_cdvdman_strm_id || g_cdvdman_istruct.m_stream_flag )
			{
				WaitEventFlag(g_cdvdman_intr_efid, 1u, 0, resbits);
				if ( g_cdvdman_strm_id )
				{
					DelayThread(8000);
				}
			}
			break;
		case 17:
			return (!sceCdCheckCmd() || g_cdvdman_istruct.m_read2_flag || g_cdvdman_strm_id || (g_cdvdman_istruct.m_stream_flag != 0)) ? 1 : 0;
		case 32:
			WaitEventFlag(g_cdvdman_intr_efid, 0x21u, 1, resbits);
			ReferEventFlagStatus(g_cdvdman_intr_efid, &efinfo);
			if ( (efinfo.currBits & 0x20) == 0 )
			{
				if ( g_cdvdman_istruct.m_last_error )
				{
					SetEventFlag(g_cdvdman_intr_efid, 0x20u);
				}
				else
				{
					WaitEventFlag(g_cdvdman_intr_efid, 0x20u, 0, resbits);
				}
			}
			break;
		default:
			while ( !sceCdCheckCmd() || g_cdvdman_istruct.m_read2_flag )
			{
				WaitEventFlag(g_cdvdman_intr_efid, 1u, 0, resbits);
			}
			break;
	}
	VERBOSE_KPRINTF(1, "sceCdSync: Command= %d Error= %d\n", (unsigned __int8)g_cdvdman_istruct.m_cdvdman_command, (unsigned __int8)g_cdvdman_istruct.m_last_error);
	return 0;
}

//----- (004039C4) --------------------------------------------------------
int __cdecl sceCdSpinCtrlIOP(u32 speed)
{
	VERBOSE_KPRINTF(1, "sceCdSpinCtrlIOP speed= %d\n", speed);
	g_cdvdman_spinctl = speed;
	return 1;
}

//----- (00403A0C) --------------------------------------------------------
int __cdecl sceCdLayerSearchFile(sceCdlFILE *fp, const char *path, int layer)
{
	unsigned int i; // $a3
	int search_res; // $s0
	u32 efbits[2]; // [sp+10h] [-8h] BYREF

	if ( PollEventFlag(g_sfile_evid, 1u, 16, efbits) == -421 )
	{
		return 0;
	}
	for ( i = 0; i < ((sizeof(g_cdvdman_sfname)/sizeof(g_cdvdman_sfname[0])) - 1) && path[i]; i += 1 )
	{
		g_cdvdman_sfname[i] = path[i];
	}
	g_cdvdman_sfname[i] = 0;
	g_cdvdman_srchspd = 1;
	search_res = CdSearchFileInner((CDVDMAN_FILETBL_ENTRY_T *)fp, g_cdvdman_sfname, layer);
	vSetEventFlag(g_sfile_evid, 1u);
	return search_res;
}

//----- (00403AE4) --------------------------------------------------------
int __cdecl sceCdSearchFile(sceCdlFILE *file, const char *name)
{
	return sceCdLayerSearchFile(file, name, 0);
}

//----- (00403B04) --------------------------------------------------------
int __cdecl sceCdGetToc(u8 *toc)
{
	return cdvdman_gettoc(toc);
}

//----- (00403B24) --------------------------------------------------------
int __cdecl sceCdDiskReady(int mode)
{
	u32 efbits[2]; // [sp+10h] [-8h] BYREF

	efbits[0] = 0;
	VERBOSE_KPRINTF(1, "DISK READY call from iop\n");
	if ( mode == 0 )
	{
		VERBOSE_KPRINTF(1, "Wait Drive Ready %x\n", dev5_regs.m_dev5_reg_005);
		while ( 1 )
		{
			if ( !g_cdvdman_istruct.m_read2_flag )
			{
				return 2;
			}
			// The following call to sceCdGetDiskType was inlined
			switch ( sceCdGetDiskType() )
			{
				case 1:
				case 2:
				case 3:
				case 4:
					break;
				default:
					return 2;
			}
			while ( (dev5_regs.m_dev5_reg_005 & 0xC0) != 64 )
			{
				vDelayThread(2000);
				WaitEventFlag(g_cdvdman_intr_efid, 1u, 0, efbits);
			}
		}
	}
	if ( mode == 8 )
	{
		return (unsigned __int8)dev5_regs.m_dev5_reg_005;
	}
	if ( (dev5_regs.m_dev5_reg_005 & 0xC0) == 64 && !g_cdvdman_istruct.m_read2_flag )
	{
		return 2;
	}
	VERBOSE_KPRINTF(1, "Drive Not Ready\n");
	return 6;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00403CC8) --------------------------------------------------------
int sceCdGetDiskType(void)
{
	return (unsigned __int8)dev5_regs.m_dev5_reg_00F;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00403CDC) --------------------------------------------------------
int sceCdStatus(void)
{
	int reg_00A_tmp; // $s0
	u32 status_tmp; // [sp+14h] [-4h] BYREF

	reg_00A_tmp = dev5_regs.m_dev5_reg_00A;
	// The following call to sceCdGetDiskType was inlined
	if ( !sceCdGetDiskType() )
	{
		u8 rdata_tmp[4]; // [sp+10h] [-8h] BYREF

		if ( !g_cdvdman_istruct.m_tray_is_open && cdvdman_scmd_sender_03_48(rdata_tmp, &status_tmp) == 1 && !status_tmp )
		{
			reg_00A_tmp &= 0xFEu;
			if ( (rdata_tmp[0] & 8) != 0 )
			{
				reg_00A_tmp |= 1u;
			}
		}
		if ( (reg_00A_tmp & 0x1E) != 0 )
		{
			reg_00A_tmp = 0;
		}
	}
	if ( g_cdvdman_istruct.m_use_toc )
	{
		reg_00A_tmp &= ~1u;
	}
	if ( g_cdvdman_istruct.m_power_flag )
	{
		return -1;
	}
	return reg_00A_tmp;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00403DB4) --------------------------------------------------------
sceCdlLOCCD *__cdecl sceCdIntToPos(u32 i, sceCdlLOCCD *p)
{
	p->sector = 16 * ((i + 150) % 75 / 10) + (i + 150) % 75 % 10;
	p->second = 16 * ((i + 150) / 75 % 60 / 10) + (i + 150) / 75 % 60 % 10;
	p->minute = 16 * ((i + 150) / 75 / 60 / 10) + (i + 150) / 75 / 60 % 10;
	return p;
}

//----- (00403EB8) --------------------------------------------------------
u32 __cdecl sceCdPosToInt(sceCdlLOCCD *p)
{
	return 75 * (60 * (10 * (p->minute >> 4) + (p->minute & 0xF)) + 10 * (p->second >> 4) + (p->second & 0xF))
			 + 10 * (p->sector >> 4)
			 + (p->sector & 0xF)
			 - 150;
}

//----- (00403F38) --------------------------------------------------------
int __fastcall read_id_from_rom(int mode, int *buf)
{
	int chksumint; // $a1
	unsigned int i; // $t1
	unsigned int j; // $v1
	int idinfo[0x20];
	int chksumstk;

	chksumint = 0;
	chksumstk = 0;
	for ( i = 0; i < (sizeof(idinfo)/sizeof(idinfo[0])); i += 1 )
	{
		for ( j = 0; j < sizeof(chksumstk); j += 1 )
		{
			((char *)&idinfo)[(i * 4) + j] = ((char *)0xBFBF0000)[(i * 4) + j];
			((char *)&chksumstk)[j] = ((char *)0xBFBF0000)[(i * 4) + j];
		}
		chksumint += chksumstk;
	}
	for ( ; i < 0x4000; i += 1 )
	{
		for ( j = 0; j < sizeof(chksumstk); j += 1 )
		{
			((char *)&chksumstk)[j] = ((char *)0xBFBF0000)[(i * 4) + j];
		}
		chksumint += chksumstk;
	}
	if ( chksumint )
	{
		KPRINTF("# checksum error %d\n", chksumint);
		return 0;
	}
	if ( mode )
	{
		*buf = idinfo[11];
	}
	else
	{
		*buf = idinfo[2];
		buf[1] = idinfo[3];
	}
	return 1;
}

//----- (0040403C) --------------------------------------------------------
int __cdecl query_boot_mode_6_nonzero()
{
	int *BootMode; // $v0

	BootMode = QueryBootMode(6);
	return !( !BootMode || (*(_WORD *)BootMode & 0xFFFC) != 96 );
}

//----- (0040407C) --------------------------------------------------------
int __cdecl query_boot_mode_6_zero()
{
	return QueryBootMode(6) == 0;
}

//----- (0040409C) --------------------------------------------------------
int __cdecl cdvdman_readID(int mode, int *buf)
{
	u8 id_val[8]; // [sp+10h] [-18h] BYREF
	iop_sys_clock_t sysclk; // [sp+18h] [-10h] BYREF
	u32 id_result[2]; // [sp+20h] [-8h] BYREF

	id_result[0] = -1;
	if ( query_boot_mode_6_nonzero() )
	{
		if ( read_id_from_rom(mode, buf) != 0 && mode == 1 )
		{
			if ( *buf == -1 )
			{
				*buf = 0x1A0002;
			}
			return 1;
		}
		return 0;
	}
	else
	{
		if ( query_boot_mode_6_zero() )
		{
			if ( sceCdRI(id_val, id_result) == 0 || id_result[0] )
			{
				return 0;
			}
		}
		else
		{
			if ( !g_readid_systemtime.lo && !g_readid_systemtime.hi )
			{
				GetSystemTime(&sysclk);
				g_readid_systemtime = sysclk;
			}
			*(iop_sys_clock_t *)id_val = g_readid_systemtime;
		}
		if ( mode )
		{
			*buf = *(_DWORD *)id_val >> 8;
		}
		else
		{
			*buf = id_val[0] | 0x8004600;
			buf[1] = *(_DWORD *)&id_val[4];
		}
		return 1;
	}
}
// 40E588: using guessed type iop_sys_clock_t g_readid_systemtime;

//----- (004041EC) --------------------------------------------------------
int __cdecl sceCdReadGUID(u64 *guid)
{
	return cdvdman_readID(0, (int *)guid);
}

//----- (00404210) --------------------------------------------------------
int __cdecl sceCdReadModelID(unsigned int *id)
{
	return cdvdman_readID(1, (int *)id);
}

//----- (00404234) --------------------------------------------------------
int __cdecl sceCdStInit(u32 bufmax, u32 bankmax, void *buffer)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.m_cmdid = 5;
	devctl_req.m_posszarg1 = bufmax;
	devctl_req.m_posszarg2 = bankmax;
	devctl_req.m_buffer = buffer;
	return (devctl("cdrom_stm0:", 0x4393, &devctl_req, 0x18u, &buf, 4u) < 0) ? 0 : buf;
}

//----- (004042C8) --------------------------------------------------------
int __cdecl sceCdStStart(u32 lbn, sceCdRMode *mode)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.m_rmode.datapattern = mode->datapattern;
	devctl_req.m_rmode.spindlctrl = mode->spindlctrl;
	devctl_req.m_cmdid = 1;
	devctl_req.m_posszarg1 = lbn;
	devctl_req.m_rmode.trycount = mode->trycount;
	return (devctl("cdrom_stm0:", 0x4393, &devctl_req, 0x18u, &buf, 4u) < 0) ? 0 : buf;
}

//----- (00404360) --------------------------------------------------------
int __cdecl sceCdStSeekF(unsigned int lsn)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.m_cmdid = 9;
	devctl_req.m_posszarg1 = lsn;
	return (devctl("cdrom_stm0:", 0x4393, &devctl_req, 0x18u, &buf, 4u) < 0) ? 0 : buf;
}

//----- (004043D4) --------------------------------------------------------
int __cdecl sceCdStSeek(u32 lbn)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.m_posszarg1 = lbn;
	devctl_req.m_cmdid = 4;
	return (devctl("cdrom_stm0:", 0x4393, &devctl_req, 0x18u, &buf, 4u) < 0) ? 0 : buf;
}

//----- (00404444) --------------------------------------------------------
int sceCdStStop(void)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.m_cmdid = 3;
	return (devctl("cdrom_stm0:", 0x4393, &devctl_req, 0x18u, &buf, 4u) < 0) ? 0 : buf;
}

//----- (004044AC) --------------------------------------------------------
int __cdecl sceCdStRead(u32 sectors, u32 *buffer, u32 mode, u32 *error)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	(void)mode;

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.m_cmdid = 1;
	devctl_req.m_posszarg2 = sectors;
	devctl_req.m_buffer = buffer;
	if ( devctl("cdrom_stm0:", 0x4394, &devctl_req, 0x18u, &buf, 4u) < 0 )
	{
		buf = 0;
	}
	*error = devctl_req.m_error;
	return buf;
}

//----- (00404540) --------------------------------------------------------
int sceCdStPause(void)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.m_cmdid = 7;
	return (devctl("cdrom_stm0:", 0x4393, &devctl_req, 0x18u, &buf, 4u) < 0) ? 0 : buf;
}

//----- (004045A8) --------------------------------------------------------
int sceCdStResume(void)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.m_cmdid = 8;
	return (devctl("cdrom_stm0:", 0x4393, &devctl_req, 0x18u, &buf, 4u) < 0) ? 0 : buf;
}

//----- (00404610) --------------------------------------------------------
int sceCdStStat(void)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.m_cmdid = 6;
	return (devctl("cdrom_stm0:", 0x4393, &devctl_req, 0x18u, &buf, 4u) < 0) ? 0 : buf;
}

//----- (00404680) --------------------------------------------------------
int __cdecl CdSearchFileInner(CDVDMAN_FILETBL_ENTRY_T *fp, const char *name, int layer)
{
	int parent_level; // $a0
	int i; // $s2
	unsigned int j; // $s2
	char name_buf[32]; // [sp+10h] [-20h] BYREF

	VERBOSE_PRINTF(1, "CdSearchFile: start name= %s layer= %d\n", name, layer);
	if ( g_cdvdman_fs_layer != layer )
	{
		g_cdvdman_fs_cache = 0;
	}
	if ( !cdvdman_mediactl(0) && g_cdvdman_fs_cache )
	{
		VERBOSE_KPRINTF(1, "CdSearchFile: cache dir data used\n");
	}
	else
	{
		VERBOSE_PRINTF(1, "CdSearchFile Topen= %s\n", name);
		if ( !CD_newmedia(layer) )
		{
			g_cdvdman_fs_cache = 0;
			return 0;
		}
		g_cdvdman_fs_cache = 1;
	}
	if ( *name != '\\' )
	{
		return 0;
	}
	name_buf[0] = 0;
	parent_level = 1;
	j = 0;
	for ( i = 0; i < 8 && name[i]; i += 1 )
	{
		for ( j = 0; name[i + j] != '\\'; j += 1 )
		{
			name_buf[j] = name[i + j];
		}
		name_buf[j] = 0;
		parent_level = cdvdman_finddir(parent_level, name_buf);
		if ( parent_level == -1 )
		{
			name_buf[0] = 0;
			break;
		}
	}
	if ( i >= 8 )
	{
		VERBOSE_PRINTF(1, "%s: path level (%d) error\n", name, i);
		return 0;
	}
	if ( !name_buf[0] )
	{
		VERBOSE_PRINTF(1, "%s: dir was not found\n", name);
		return 0;
	}
	name_buf[j] = 0;
	if ( !CD_cachefile(parent_level, layer) )
	{
		VERBOSE_PRINTF(1, "CdSearchFile: disc error\n");
		return 0;
	}
	VERBOSE_PRINTF(2, "CdSearchFile: searching %s...\n", name_buf);
	for ( j = 0; j < (sizeof(g_cdvdman_filetbl)/sizeof(g_cdvdman_filetbl[0])) && g_cdvdman_filetbl[j].m_file_struct.name[0]; j += 1 )
	{
		VERBOSE_PRINTF(1, "%d %s %s\n", (int)j, g_cdvdman_filetbl[j].m_file_struct.name, name_buf);
		if ( cdvdman_cmpname(g_cdvdman_filetbl[j].m_file_struct.name, name_buf) )
		{
			VERBOSE_PRINTF(2, "%s:\t found\n", name_buf);
			// The following memcpy was inlined
			memcpy(fp, &g_cdvdman_filetbl[j], sizeof(CDVDMAN_FILETBL_ENTRY_T));
			fp->m_file_struct.lsn += layer ? g_cdvdman_fs_base2 : 0;
			return 1;
		}
	}
	VERBOSE_PRINTF(1, "%s: not found\n", name_buf);
	return 0;
}

//----- (00404A68) --------------------------------------------------------
int __cdecl sceCdSearchDir(char *dirname, int layer)
{
	sceCdlFILE fileinfo; // [sp+10h] [-28h] BYREF

	VERBOSE_PRINTF(1, "_sceCdSearchDir: dir name %s layer %d\n", dirname, layer);
	return sceCdLayerSearchFile(&fileinfo, dirname, layer) != 0 ? g_cdvdman_fs_cdsec : -2;
}
// 404A68: using guessed type sceCdlFILE fileinfo;

//----- (00404AD4) --------------------------------------------------------
int __cdecl sceCdReadDir(sceCdlFILE *fp, int dsec, int index, int layer)
{
	VERBOSE_PRINTF(1, "_sceCdReadDir: current= %d dsec= %d layer= %d\n", g_cdvdman_fs_cdsec, dsec, layer);
	if ( g_cdvdman_fs_cdsec != dsec || g_cdvdman_fs_layer != layer )
	{
		int dsec_tmp; // $a0

		dsec_tmp = dsec;
		if ( g_cdvdman_fs_layer != layer )
		{
			if ( !CD_newmedia(layer) )
			{
				return -2;
			}
			g_cdvdman_fs_cache = 1;
		}
		if ( CD_cachefile(dsec_tmp, layer) == 0 )
		{
			return -2;
		}
	}
	if ( g_cdvdman_filetbl[index].m_file_struct.name[0] )
	{
		VERBOSE_PRINTF(1, "%s:\t found dir_point %d\n", g_cdvdman_filetbl[index].m_file_struct.name, index);
		// The following memcpy was inlined
		memcpy(fp, &g_cdvdman_filetbl[index], sizeof(CDVDMAN_FILETBL_ENTRY_T));
		return 1;
	}
	return 0;
}

//----- (00404C4C) --------------------------------------------------------
int __cdecl cdvdman_cmpname(const char *p, const char *q)
{
	return strncmp(p, q, 12) == 0;
}

//----- (00404C6C) --------------------------------------------------------
int __cdecl CD_newmedia(int arg)
{
	unsigned int DiskType; // $s0
	unsigned int i; // $a1
	char *fs_rbuf_cur; // $s1
	int state; // [sp+18h] [-8h] BYREF
	int ptsector; // [sp+1Ch] [-4h]

	ptsector = 0;
	DiskType = sceCdGetDiskType();
	switch ( DiskType )
	{
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 252:
		case 254:
		case 255:
			break;
		default:
			VERBOSE_PRINTF(1, "CD_newmedia: Illegal disc media type =%d\n", (int)DiskType);
			return 0;
	}
	g_cdvdman_fs_base2 = 0;
	if ( DiskType == 20 )
	{
		if ( !DvdDual_infochk() )
		{
			VERBOSE_PRINTF(1, "CD_newmedia: Get DvdDual_infochk fail\n");
			return 0;
		}
		g_cdvdman_fs_base2 = arg ? g_cdvdman_istruct.m_layer_1_lsn : 0;
	}
	if ( disc_read(1, g_cdvdman_fs_base2 + 16, g_cdvdman_fs_rbuf, arg) != 1 )
	{
		VERBOSE_PRINTF(1, "CD_newmedia: Read error in disc_read(PVD)\n");
		return 0;
	}
	CpuSuspendIntr(&state);
	for ( i = 0; i < g_cdvdman_pathtblsize; i += 1 )
	{
		g_cdvdman_pathtbl[i].m_cache_hit_count = 0;
		g_cdvdman_pathtbl[i].m_layer = 0;
		g_cdvdman_pathtbl[i].m_nsec = 0;
		g_cdvdman_pathtbl[i].m_lsn = 0;
		g_cdvdman_pathtbl[i].m_cache_path_sz = 0;
	}
	g_cache_count = 0;
	g_cache_table = 0;
	g_cache_path_size = 0;
	CpuResumeIntr(state);
	if ( strncmp(&g_cdvdman_fs_rbuf[1], "CD001", 5) )
	{
		VERBOSE_PRINTF(1, "CD_newmedia: Disc format error in cd_read(PVD)\n");
		return 0;
	}
	switch ( DiskType )
	{
		case 16:
		case 17:
		case 18:
		case 19:
			VERBOSE_PRINTF(1, "CD_newmedia: CD Read mode\n");
			ptsector = *(_DWORD *)&g_cdvdman_fs_rbuf[140];
			break;
		case 20:
		case 252:
		case 254:
			VERBOSE_PRINTF(1, "CD_newmedia: DVD Read mode\n");
			ptsector = 257;
			break;
	}
	if ( disc_read(1, g_cdvdman_fs_base2 + ptsector, g_cdvdman_fs_rbuf, arg) != 1 )
	{
		VERBOSE_PRINTF(1, "CD_newmedia: Read error (PT:%08x)\n", ptsector);
		return 0;
	}
	VERBOSE_PRINTF(2, "CD_newmedia: sarching dir..\n");
	for ( i = 0, fs_rbuf_cur = g_cdvdman_fs_rbuf; i < (sizeof(g_cdvdman_dirtbl)/sizeof(g_cdvdman_dirtbl[0])) && fs_rbuf_cur < &g_cdvdman_fs_rbuf[2048] && *fs_rbuf_cur; i += 1, fs_rbuf_cur += (unsigned __int8)*fs_rbuf_cur + (*fs_rbuf_cur & 1) + 8 )
	{
		g_cdvdman_dirtbl[i].m_extent = *(_DWORD *)(fs_rbuf_cur + 2);
		g_cdvdman_dirtbl[i].m_number = i;
		g_cdvdman_dirtbl[i].m_parent = (unsigned __int8)fs_rbuf_cur[6];
		memcpy(g_cdvdman_dirtbl[i].m_name, fs_rbuf_cur + 8, (unsigned __int8)*fs_rbuf_cur);
		g_cdvdman_dirtbl[i].m_name[(unsigned __int8)*fs_rbuf_cur] = 0;
		VERBOSE_PRINTF(2, "\t%08x,%04x,%04x,%s\n", g_cdvdman_dirtbl[i].m_extent, g_cdvdman_dirtbl[i].m_number, g_cdvdman_dirtbl[i].m_parent, g_cdvdman_dirtbl[i].m_name);
	}
	if ( i < (sizeof(g_cdvdman_dirtbl)/sizeof(g_cdvdman_dirtbl[0])) )
	{
		g_cdvdman_dirtbl[i].m_parent = 0;
	}
	g_cdvdman_fs_cdsec = 0;
	g_cdvdman_fs_layer = arg;
	VERBOSE_PRINTF(2, "CD_newmedia: %d dir entries found\n", (int)i);
	return 1;
}
// 404EA0: conditional instruction was optimized away because $s0.4 is in (10..13)

//----- (00405168) --------------------------------------------------------
int __fastcall cdvdman_finddir(int target_parent, const char *target_name)
{
	unsigned int i; // $s0

	for ( i = 0; i < (sizeof(g_cdvdman_dirtbl)/sizeof(g_cdvdman_dirtbl[0])) && g_cdvdman_dirtbl[i].m_parent; i += 1 )
	{
		if ( g_cdvdman_dirtbl[i].m_parent == target_parent && !strcmp(target_name, g_cdvdman_dirtbl[i].m_name) )
		{
			return i + 1;
		}
	}
	return -1;
}

//----- (0040520C) --------------------------------------------------------
int __fastcall CD_cachefile(int dsec, int layer)
{
	struct dirTocEntry *toc1; // $s0
	unsigned int i; // $s2
	u32 loc; // [sp+30h] [-18h]

	if ( dsec == g_cdvdman_fs_cdsec )
	{
		return 1;
	}
	if ( layer )                                  // This actually accesses g_cdvdman_dirtbl
	{
		loc = g_cdvdman_fs_base2 + *(&g_cdvdman_filetbl[63].m_file_struct.lsn + 11 * dsec);
	}
	else
	{
		loc = *(&g_cdvdman_filetbl[63].m_file_struct.lsn + 11 * dsec);
	}
	if ( disc_read(1, loc, g_cdvdman_fs_rbuf, layer) != 1 )
	{
		VERBOSE_PRINTF(1, "CD_cachefile: dir not found\n");
		g_cdvdman_fs_cdsec = 0;
		return 0;
	}
	VERBOSE_PRINTF(2, "CD_cachefile: searching...\n");
	for ( i = 0, toc1 = (struct dirTocEntry *)g_cdvdman_fs_rbuf; i < (sizeof(g_cdvdman_filetbl)/sizeof(g_cdvdman_filetbl[0])) && toc1 < (struct dirTocEntry *)&g_cdvdman_fs_rbuf[2048]; i += 1, toc1 = (struct dirTocEntry *)((char *)toc1 + LOBYTE(toc1->m_length)) )
	{
		int file_year; // $s1

		if ( !LOBYTE(toc1->m_length) )
		{
			break;
		}
		g_cdvdman_filetbl[i].m_file_struct.lsn = toc1->m_fileLBA;
		g_cdvdman_filetbl[i].m_file_struct.size = toc1->m_fileSize;
		file_year = toc1->m_dateStamp[0] + 1900;
		g_cdvdman_filetbl[i].m_file_struct.date[7] = BYTE1(file_year);
		g_cdvdman_filetbl[i].m_file_struct.date[6] = file_year;
		g_cdvdman_filetbl[i].m_file_struct.date[5] = toc1->m_dateStamp[1];
		g_cdvdman_filetbl[i].m_file_struct.date[4] = toc1->m_dateStamp[2];
		g_cdvdman_filetbl[i].m_file_struct.date[3] = toc1->m_dateStamp[3];
		g_cdvdman_filetbl[i].m_file_struct.date[2] = toc1->m_dateStamp[4];
		g_cdvdman_filetbl[i].m_file_struct.date[1] = toc1->m_dateStamp[5];
		g_cdvdman_filetbl[i].m_file_properties = toc1->m_fileProperties;
		switch ( i )
		{
			case 0:
				strcpy(g_cdvdman_filetbl[i].m_file_struct.name, ".");
				break;
			case 1:
				strcpy(g_cdvdman_filetbl[i].m_file_struct.name, "..");
				break;
			default:
				memcpy(g_cdvdman_filetbl[i].m_file_struct.name, toc1->m_filename, toc1->m_filenameLength);
				g_cdvdman_filetbl[i].m_file_struct.name[toc1->m_filenameLength] = 0;
				break;
		}
		VERBOSE_PRINTF(2, "\t lsn %d size %d name:%d:%s %d/%d/%d %d:%d:%d\n", (int)(g_cdvdman_filetbl[i].m_file_struct.lsn), (int)(g_cdvdman_filetbl[i].m_file_struct.size), toc1->m_filenameLength, g_cdvdman_filetbl[i].m_file_struct.name, file_year, g_cdvdman_filetbl[i].m_file_struct.date[5], g_cdvdman_filetbl[i].m_file_struct.date[4], g_cdvdman_filetbl[i].m_file_struct.date[3], g_cdvdman_filetbl[i].m_file_struct.date[2], g_cdvdman_filetbl[i].m_file_struct.date[1]);
	}
	g_cdvdman_fs_cdsec = dsec;
	if ( i < (sizeof(g_cdvdman_filetbl)/sizeof(g_cdvdman_filetbl[0])) )
	{
		g_cdvdman_filetbl[i].m_file_struct.name[0] = 0;
	}
	VERBOSE_PRINTF(2, "CD_cachefile: %d files found\n", (int)i);
	return 1;
}

//----- (00405628) --------------------------------------------------------
int __cdecl disc_read(int size, int loc, void *buffer, int layer)
{
	int f; // $s6
	int i; // $s0
	sceCdRMode rmode[2]; // [sp+20h] [-8h] BYREF
	int has_success;

	has_success = 1;
	f = 0;
	rmode[0].trycount = 16;
	VERBOSE_PRINTF(1, "cd_read:lsn= %d size= %d layer= %d\n", loc, size, layer);
	if ( cdvdman_l0check(layer) )
	{
		g_cdvdman_srchspd = 0;
	}
	switch ( g_cdvdman_srchspd )
	{
		case 2:
		case 3:
		case 4:
			rmode[0].spindlctrl = g_cdvdman_srchspd;
			break;
		case 0:
		case 1:
			rmode[0].spindlctrl = g_cdvdman_srchspd != 0;
			break;
		default:
			rmode[0].spindlctrl = 1;
			break;
	}
	rmode[0].datapattern = 0;
	if ( !g_cdvdman_pathtblflag )
	{
		has_success = 1;
	}
	if ( !has_success )
	{
		int pathcachecnt; // $s2

		pathcachecnt = ( g_cache_count < g_cdvdman_pathtblsize ) ? g_cache_count : g_cdvdman_pathtblsize;
		for ( i = 0; i < pathcachecnt; i += 1 )
		{
			VERBOSE_KPRINTF(1, "Path table Cache Search lsn:%d:%d nsec:%d:%d layer%d:%d\n", g_cdvdman_pathtbl[i].m_lsn, loc, g_cdvdman_pathtbl[i].m_nsec, size, g_cdvdman_pathtbl[i].m_layer, layer);
			if ( g_cdvdman_pathtbl[i].m_lsn == loc && g_cdvdman_pathtbl[i].m_nsec == (unsigned int)size && g_cdvdman_pathtbl[i].m_layer == layer )
			{
				break;
			}
		}
		if ( i != pathcachecnt )
		{
			VERBOSE_KPRINTF(1, "Path table Cache ON:%d\n", g_cdvdman_pathtbl[i].m_cache_path_sz);
			if ( lseek(g_cache_path_fd, g_cdvdman_pathtbl[i].m_cache_path_sz, 0) >= 0 )
			{
				read(g_cache_path_fd, buffer, size << 11);
				f = 1;
				g_cdvdman_pathtbl[i].m_cache_hit_count += 1;
			}
			has_success = 1;
		}
		if ( !has_success )
		{
			if ( sceCdRE(loc, size, buffer, rmode) == 0 )
			{
				return 0;
			}
			sceCdSync(3);
		}
	}
	if ( !has_success && !sceCdGetError() )
	{
		int cache_path_sz; // $s1

		if ( g_cache_count >= g_cdvdman_pathtblsize )
		{
			int cachetblo1; // $a2
			unsigned int cacheblo2; // $a1

			g_cache_table += 1;
			if ( g_cache_table >= g_cdvdman_pathtblsize )
			{
				g_cache_table = 0;
			}
			cachetblo1 = g_cache_table;
			cacheblo2 = cachetblo1;
			for ( i = 0; (unsigned int)i < g_cache_count; i += 1 )
			{
				if ( cacheblo2 >= g_cdvdman_pathtblsize )
				{
					cacheblo2 = 0;
				}
				if ( g_cdvdman_pathtbl[cacheblo2].m_nsec >= (unsigned int)size
					&& g_cdvdman_pathtbl[cacheblo2].m_cache_hit_count < (unsigned int)g_cdvdman_pathtbl[cachetblo1].m_cache_hit_count )
				{
					cachetblo1 = cacheblo2;
				}
				++cacheblo2;
			}
			cache_path_sz = g_cdvdman_pathtbl[cachetblo1].m_cache_path_sz;
			g_cache_table = cachetblo1;
		}
		else
		{
			cache_path_sz = g_cache_path_size;
			g_cache_table = g_cache_count;
			g_cache_count += 1;
		}
		if ( lseek(g_cache_path_fd, cache_path_sz, 0) >= 0 )
		{
			int ptbl_wcache_write_res; // $a2

			ptbl_wcache_write_res = write(g_cache_path_fd, buffer, size << 11);
			if ( ptbl_wcache_write_res == size << 11 )
			{
				f = 1;
				g_cdvdman_pathtbl[g_cache_table].m_cache_path_sz = cache_path_sz;
				g_cdvdman_pathtbl[g_cache_table].m_lsn = loc;
				g_cdvdman_pathtbl[g_cache_table].m_nsec = size;
				g_cdvdman_pathtbl[g_cache_table].m_layer = layer;
				g_cdvdman_pathtbl[g_cache_table].m_cache_hit_count = 0;
				g_cache_path_size += ( g_cache_count < g_cdvdman_pathtblsize ) ? ptbl_wcache_write_res : 0;
			}
			else
			{
				VERBOSE_KPRINTF(1, "Ptbl_WCache:write %d", ptbl_wcache_write_res);
				g_cdvdman_pathtbl[g_cache_table].m_cache_hit_count = 0;
				g_cdvdman_pathtbl[g_cache_table].m_layer = 0;
				g_cdvdman_pathtbl[g_cache_table].m_nsec = 0;
				g_cdvdman_pathtbl[g_cache_table].m_lsn = 0;
			}
		}
		has_success = 1;
	}
	if ( has_success )
	{
		if ( f )
		{
			return size;
		}
		if ( sceCdRE(loc, size, buffer, rmode) == 0 )
		{
			return 0;
		}
		sceCdSync(3);
		if ( sceCdGetError() == 0 )
		{
			return size;
		}
	}
	VERBOSE_KPRINTF(1, "cd_read: error code %x\n", sceCdGetError());
	return 0;
}

//----- (00405B68) --------------------------------------------------------
int __cdecl path_tbl_init(u32 blocks, char *fname, int action)
{
	int num; // $s3
	int v; // $s1
	char cachedir[512]; // [sp+18h] [-208h] BYREF
	int state; // [sp+218h] [-8h] BYREF
	u32 blocksbs; // [sp+21Ch] [-4h] BYREF

	num = 0;
	v = 0;
	if ( action )
	{
		CpuSuspendIntr(&state);
		g_cdvdman_pathtbl = (CDVDMAN_PATHTBL_T *)AllocSysMemory(1, 20 * blocks, 0);
		if ( !g_cdvdman_pathtbl )
		{
			CpuResumeIntr(state);
			g_cdvdman_pathtblflag = 0;
			return -12;
		}
		CpuResumeIntr(state);
		sprintf(cachedir, "%sCache_Path", fname);
		v = open(cachedir, 1539, 511);
		if ( v >= 0 )
		{
			u32 i; // $s0

			g_cache_path_fd = v;
			if ( strncmp(cachedir, "pfs", 3) == 0 )
			{
				blocksbs = blocks << 11;
				ioctl2(g_cache_path_fd, 28673, &blocksbs, 4u, 0, 0);
			}
			for ( i = 0; i < blocks; i += 1 )
			{
				v = write(g_cache_path_fd, g_cdvdman_fs_rbuf, 2048);
				if ( v < 0 )
				{
					break;
				}
			}
			if ( v >= 0 )
			{
				CpuSuspendIntr(&state);
				g_cdvdman_pathtblsize = blocks;
				for ( i = 0; i < blocks; i += 1 )
				{
					g_cdvdman_pathtbl[i].m_cache_hit_count = 0;
					g_cdvdman_pathtbl[i].m_layer = 0;
					g_cdvdman_pathtbl[i].m_nsec = 0;
					g_cdvdman_pathtbl[i].m_lsn = 0;
					g_cdvdman_pathtbl[i].m_cache_path_sz = 0;
				}
				g_cache_path_size = 0;
				g_cache_count = 0;
				g_cache_table = 0;
				g_cdvdman_pathtblflag = 1;
				CpuResumeIntr(state);
				return 0;
			}
		}
	}
	if ( g_cache_path_fd != -1 )
	{
		num = close(g_cache_path_fd);
		if ( num >= 0 )
		{
			if ( !strncmp(cachedir, "pfs", 3) )
			{
				num = remove(cachedir);
			}
			else if ( !strncmp(cachedir, "host", 4) )
			{
				num = 0;
				remove(cachedir);
			}
		}
	}
	CpuSuspendIntr(&state);
	g_cache_path_fd = -1;
	g_cache_count = 0;
	g_cache_table = 0;
	g_cache_path_size = 0;
	g_cdvdman_pathtblflag = 0;
	g_cdvdman_pathtblsize = 0;
	FreeSysMemory(g_cdvdman_pathtbl);
	g_cdvdman_pathtbl = 0;
	CpuResumeIntr(state);
	if ( v < 0 )
	{
		VERBOSE_KPRINTF(1, "path_tbl_init Error %d\n", v);
	}
	return (!action) ? num : v;
}

//----- (00405E60) --------------------------------------------------------
void __fastcall unused_40BA90(unsigned int *a1, int a2)
{
	int v2; // $v0
	int v4; // $t1
	int v5; // $t0
	int v6; // $v1
	bool v7; // dc

	v2 = 0;
	for ( ; a2; a2 -= 4 )
	{
		unsigned int v3; // $t7

		v3 = *a1;
		for ( v4 = 4; v4; v4 -= 1 )
		{
			v6 = (unsigned __int8)v3;
			for ( v5 = 8; v5; v5 -= 1 )
			{
				v7 = v2 >= 0;
				v2 *= 2;
				if ( !v7 )
				{
					v2 ^= 0x80000011;
				}
				v7 = (v6 & 0x80) == 0;
				v6 *= 2;
				if ( !v7 )
				{
					v2 ^= 1u;
				}
			}
			v3 >>= 8;
		}
		++a1;
	}
}

//----- (00405ECC) --------------------------------------------------------
unsigned int __fastcall cdvdman_memcpy(char *dst, const char *src, unsigned int n)
{
	int v3; // $a3
	int v4; // $v1
	int v5; // $v1
	int v6; // $t0
	int v7; // $t1
	int v8; // $t2
	int v9; // $t3
	int v10; // $t4
	int v11; // $t5
	int v12; // $t6
	int v13; // $t7
	int v14; // $t8
	int v15; // $t9
	int v16; // $a3
	int v17; // $v1
	int v18; // $v1
	int v19; // $t0
	int v20; // $t1
	int v21; // $t2
	int v22; // $t3
	int v23; // $t4
	int v24; // $t5
	int v25; // $t6
	int v26; // $t7
	int v27; // $t8
	int v28; // $t9
	int v29; // $a3
	int v30; // $v1
	int v31; // $v1
	int v32; // $t0
	int v33; // $t1
	int v34; // $t2
	int v35; // $t3
	int v36; // $t4
	int v37; // $t5
	int v38; // $t6
	int v39; // $t7
	int v40; // $t8
	int v41; // $t9
	int v42; // $a3
	int v43; // $v1
	int v44; // $v1
	int v45; // $t0
	int v46; // $t1
	int v47; // $t2
	int v48; // $t3
	int v49; // $t4
	int v50; // $t5
	int v51; // $t6
	int v52; // $t7
	int v53; // $t8
	int v54; // $t9
	unsigned int v55; // $v1

	if ( n >> 2 )
	{
		if ( (((uiptr)dst | (uiptr)src) & 3) != 0 )
		{
			if ( ((uiptr)dst & 3) != 0 && ((uiptr)src & 3) != 0 )
			{
				v16 = (int)(n >> 2) / 12;
				v17 = (int)(n >> 2) % 12;
				if ( !v17 )
				{
					goto LABEL_30;
				}
				do
				{
					--v17;
					*(_DWORD *)dst = *(_DWORD *)src;
					src += 4;
					dst += 4;
				}
				while ( v17 );
				if ( v16 )
				{
LABEL_30:
					do
					{
						v18 = *((_DWORD *)src + 1);
						v19 = *((_DWORD *)src + 2);
						v20 = *((_DWORD *)src + 3);
						v21 = *((_DWORD *)src + 4);
						v22 = *((_DWORD *)src + 5);
						v23 = *((_DWORD *)src + 6);
						v24 = *((_DWORD *)src + 7);
						v25 = *((_DWORD *)src + 8);
						v26 = *((_DWORD *)src + 9);
						v27 = *((_DWORD *)src + 10);
						v28 = *((_DWORD *)src + 11);
						--v16;
						*(_DWORD *)dst = *(_DWORD *)src;
						*((_DWORD *)dst + 1) = v18;
						*((_DWORD *)dst + 2) = v19;
						*((_DWORD *)dst + 3) = v20;
						*((_DWORD *)dst + 4) = v21;
						*((_DWORD *)dst + 5) = v22;
						*((_DWORD *)dst + 6) = v23;
						*((_DWORD *)dst + 7) = v24;
						*((_DWORD *)dst + 8) = v25;
						*((_DWORD *)dst + 9) = v26;
						*((_DWORD *)dst + 10) = v27;
						*((_DWORD *)dst + 11) = v28;
						src += 48;
						dst += 48;
					}
					while ( v16 );
				}
			}
			else if ( ((uiptr)dst & 3) != 0 )
			{
				v29 = (int)(n >> 2) / 12;
				v30 = (int)(n >> 2) % 12;
				if ( !v30 )
				{
					goto LABEL_31;
				}
				do
				{
					--v30;
					*(_DWORD *)dst = *(_DWORD *)src;
					src += 4;
					dst += 4;
				}
				while ( v30 );
				if ( v29 )
				{
LABEL_31:
					do
					{
						v31 = *((_DWORD *)src + 1);
						v32 = *((_DWORD *)src + 2);
						v33 = *((_DWORD *)src + 3);
						v34 = *((_DWORD *)src + 4);
						v35 = *((_DWORD *)src + 5);
						v36 = *((_DWORD *)src + 6);
						v37 = *((_DWORD *)src + 7);
						v38 = *((_DWORD *)src + 8);
						v39 = *((_DWORD *)src + 9);
						v40 = *((_DWORD *)src + 10);
						v41 = *((_DWORD *)src + 11);
						--v29;
						*(_DWORD *)dst = *(_DWORD *)src;
						*((_DWORD *)dst + 1) = v31;
						*((_DWORD *)dst + 2) = v32;
						*((_DWORD *)dst + 3) = v33;
						*((_DWORD *)dst + 4) = v34;
						*((_DWORD *)dst + 5) = v35;
						*((_DWORD *)dst + 6) = v36;
						*((_DWORD *)dst + 7) = v37;
						*((_DWORD *)dst + 8) = v38;
						*((_DWORD *)dst + 9) = v39;
						*((_DWORD *)dst + 10) = v40;
						*((_DWORD *)dst + 11) = v41;
						src += 48;
						dst += 48;
					}
					while ( v29 );
				}
			}
			else
			{
				v42 = (int)(n >> 2) / 12;
				v43 = (int)(n >> 2) % 12;
				if ( !v43 )
				{
					goto LABEL_32;
				}
				do
				{
					--v43;
					*(_DWORD *)dst = *(_DWORD *)src;
					src += 4;
					dst += 4;
				}
				while ( v43 );
				if ( v42 )
				{
LABEL_32:
					do
					{
						v44 = *((_DWORD *)src + 1);
						v45 = *((_DWORD *)src + 2);
						v46 = *((_DWORD *)src + 3);
						v47 = *((_DWORD *)src + 4);
						v48 = *((_DWORD *)src + 5);
						v49 = *((_DWORD *)src + 6);
						v50 = *((_DWORD *)src + 7);
						v51 = *((_DWORD *)src + 8);
						v52 = *((_DWORD *)src + 9);
						v53 = *((_DWORD *)src + 10);
						v54 = *((_DWORD *)src + 11);
						--v42;
						*(_DWORD *)dst = *(_DWORD *)src;
						*((_DWORD *)dst + 1) = v44;
						*((_DWORD *)dst + 2) = v45;
						*((_DWORD *)dst + 3) = v46;
						*((_DWORD *)dst + 4) = v47;
						*((_DWORD *)dst + 5) = v48;
						*((_DWORD *)dst + 6) = v49;
						*((_DWORD *)dst + 7) = v50;
						*((_DWORD *)dst + 8) = v51;
						*((_DWORD *)dst + 9) = v52;
						*((_DWORD *)dst + 10) = v53;
						*((_DWORD *)dst + 11) = v54;
						src += 48;
						dst += 48;
					}
					while ( v42 );
				}
			}
		}
		else
		{
			v3 = (int)(n >> 2) / 12;
			v4 = (int)(n >> 2) % 12;
			if ( !v4 )
			{
				goto LABEL_33;
			}
			do
			{
				--v4;
				*(_DWORD *)dst = *(_DWORD *)src;
				src += 4;
				dst += 4;
			}
			while ( v4 );
			if ( v3 )
			{
LABEL_33:
				do
				{
					v5 = *((_DWORD *)src + 1);
					v6 = *((_DWORD *)src + 2);
					v7 = *((_DWORD *)src + 3);
					v8 = *((_DWORD *)src + 4);
					v9 = *((_DWORD *)src + 5);
					v10 = *((_DWORD *)src + 6);
					v11 = *((_DWORD *)src + 7);
					v12 = *((_DWORD *)src + 8);
					v13 = *((_DWORD *)src + 9);
					v14 = *((_DWORD *)src + 10);
					v15 = *((_DWORD *)src + 11);
					--v3;
					*(_DWORD *)dst = *(_DWORD *)src;
					*((_DWORD *)dst + 1) = v5;
					*((_DWORD *)dst + 2) = v6;
					*((_DWORD *)dst + 3) = v7;
					*((_DWORD *)dst + 4) = v8;
					*((_DWORD *)dst + 5) = v9;
					*((_DWORD *)dst + 6) = v10;
					*((_DWORD *)dst + 7) = v11;
					*((_DWORD *)dst + 8) = v12;
					*((_DWORD *)dst + 9) = v13;
					*((_DWORD *)dst + 10) = v14;
					*((_DWORD *)dst + 11) = v15;
					src += 48;
					dst += 48;
				}
				while ( v3 );
			}
		}
	}
	v55 = n & 3;
	if ( (n & 3) != 0 )
	{
		do
		{
			--v55;
			*dst++ = *src++;
		}
		while ( v55 );
	}
	return n;
}

//----- (004065E4) --------------------------------------------------------
void __cdecl cdvdman_1()
{
	;
}

//----- (004065EC) --------------------------------------------------------
int __cdecl cdvdman_retonly()
{
	return 0;
}

//----- (00406600) --------------------------------------------------------
void __fastcall hex_dump(u8 *addr_start, int length)
{
	int i; // $s0

	KPRINTF("Hex Dump addr %08x\n", addr_start);
	for ( i = 0; i < length; i += 1 )
	{
		if ( !(i & 0xF) && i )
		{
			PRINTF("\n");
		}
		KPRINTF(" %02x", addr_start[i]);
	}
	KPRINTF("\n");
}

//----- (004066A4) --------------------------------------------------------
int __cdecl cdvdman_initcfg()
{
	int i; // $s0
	u8 m_version[5]; // [sp+18h] [-18h] BYREF
	u32 eflag[2]; // [sp+28h] [-8h] BYREF

	eflag[0] = 0;
	for ( i = 0; i < 101; i += 1 )
	{
		unsigned int mvored; // $s0

		if ( !sceCdGetMVersion(m_version, eflag) && (eflag[0] & 0x80) != 0 )
		{
			vDelayThread(2000);
			VERBOSE_KPRINTF(1, "_sceCdMV error\n");
		}
		mvored = m_version[3] | (m_version[2] << 8) | (m_version[1] << 16);
		g_cdvdman_emudvd9 = m_version[2] & 1;
		VERBOSE_KPRINTF(1, "MV %02x %02x %02x %02x\n", m_version[0], m_version[1], m_version[2], m_version[3]);
		g_cdvdman_minver_10700 = mvored > 0x106FF;
		g_cdvdman_minver_20200 = mvored > 0x201FF;
		g_cdvdman_minver_20400 = mvored > 0x203FF;
		g_cdvdman_minver_20800 = mvored > 0x207FF;
		g_cdvdman_minver_50000 = mvored > 0x4FFFF;
		g_cdvdman_minver_50200 = mvored > 0x501FF;
		g_cdvdman_minver_50400 = mvored > 0x503FF;
		g_cdvdman_minver_50600 = mvored > 0x505FF;
		g_cdvdman_minver_x_model_15 = (mvored & 0xF) == 1;
		g_cdvdman_minver_60000 = mvored > 0x5FFFF;
		g_cdvdman_minver_60200 = mvored > 0x601FF;
		return 1;
	}
	return 0;
}

//----- (0040694C) --------------------------------------------------------
int __fastcall vSetAlarm(iop_sys_clock_t *sys_clock, unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	return (QueryIntrContext() ? iSetAlarm : SetAlarm)(sys_clock, alarm_cb, arg);
}

//----- (004069B0) --------------------------------------------------------
int __fastcall vCancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	return (QueryIntrContext() ? iCancelAlarm : CancelAlarm)(alarm_cb, arg);
}

//----- (00406A00) --------------------------------------------------------
s32 __cdecl vSignalSema(s32 sema_id)
{
	return (QueryIntrContext() ? iSignalSema : SignalSema)(sema_id);
}

//----- (00406A44) --------------------------------------------------------
int __fastcall vSetEventFlag(int ef, u32 bits)
{
	return (QueryIntrContext() ? iSetEventFlag : SetEventFlag)(ef, bits);
}

//----- (00406A94) --------------------------------------------------------
int __fastcall vClearEventFlag(int ef, u32 bits)
{
	return (QueryIntrContext() ? iClearEventFlag : ClearEventFlag)(ef, bits);
}

//----- (00406AE4) --------------------------------------------------------
int __fastcall vReferEventFlagStatus(int ef, iop_event_info_t *info)
{
	return (QueryIntrContext() ? iReferEventFlagStatus : ReferEventFlagStatus)(ef, info);
}

//----- (00406B34) --------------------------------------------------------
int __fastcall vDelayThread(int usec)
{
	int intrval; // $s0
	int state; // [sp+10h] [-8h] BYREF

	intrval = CpuSuspendIntr(&state);
	CpuResumeIntr(state);
	return ( QueryIntrContext() == 0 && !intrval ) ? DelayThread(usec) : 0;
}

//----- (00406B90) --------------------------------------------------------
BOOL __fastcall alarm_cb_read(iop_sys_clock_t *a1)
{
	int rdto[2]; // [sp+10h] [-8h] BYREF

	rdto[0] = a1->lo / 0x9000;
	KPRINTF("Read Time Out %d(msec)\n", rdto[0]);
	sceCdSC(-18, rdto);
	return sceCdBreak() == 0;
}
// 406B90: using guessed type u32 rdto[2];

//----- (00406BE4) --------------------------------------------------------
sceCdCBFunc __cdecl sceCdCallback(sceCdCBFunc function)
{
	void (__cdecl *rc)(int); // $s0
	u32 efbits[2]; // [sp+10h] [-8h] BYREF

	if ( sceCdSync(1) != 0 || PollEventFlag(g_ncmd_evid, 1u, 16, efbits) == -421 )
	{
		return 0;
	}
	rc = g_cdvdman_user_cb;
	g_cdvdman_user_cb = function;
	vSetEventFlag(g_ncmd_evid, 1u);
	return rc;
}

//----- (00406C64) --------------------------------------------------------
void *__cdecl sceCdPOffCallback(void (__cdecl *func)(void *), void *addr)
{
	void (__cdecl *old_cb)(void *); // $s1
	int state; // [sp+10h] [-8h] BYREF

	CpuSuspendIntr(&state);
	old_cb = g_cdvdman_poff_cb;
	g_cdvdman_poff_cb = func;
	g_cdvdman_poffarg = addr;
	CpuResumeIntr(state);
	return old_cb;
}

//----- (00406CC8) --------------------------------------------------------
int __cdecl sceCdstm0Cb(void (__cdecl *p)(int))
{
	g_cdvdman_cdstm0cb = p;
	return 0;
}

//----- (00406CD8) --------------------------------------------------------
int __cdecl sceCdstm1Cb(void (__cdecl *p)(int))
{
	g_cdvdman_cdstm1cb = p;
	return 0;
}

//----- (00406CE8) --------------------------------------------------------
int __fastcall cdvdman_intr_cb(cdvdman_internal_struct_t *s)
{
	sceCdRMode cdrmode; // [sp+28h] [-10h] BYREF
	int oldstate; // [sp+30h] [-8h] BYREF
	int ext_passthrough;

	ext_passthrough = 0;
	s->m_wait_flag = s->m_waf_set_test;
	iSetEventFlag(g_cdvdman_intr_efid, 0x29u);
	DisableIntr(35, &oldstate);
	if ( *(_WORD *)&s->m_cdvdman_command == 12549 )
	{
		s->m_last_error = (sceCdStatus() == -1) ? 49 : 0;
	}
	if ( s->m_last_error == 50 )
	{
		s->m_last_error = 0;
	}
	VERBOSE_KPRINTF(1, "Intr call func_num: %d Err= %02x OnTout= %d\n", g_cdvdman_cmdfunc, (unsigned __int8)s->m_last_error, s->m_read_to);
	if ( !s->m_scmd_flag )
	{
		cdvdman_write_scmd(s);
	}
	if ( (((unsigned __int8)s->m_last_error == 48 && g_cdvdman_cmdfunc == 1) || ((unsigned __int8)s->m_last_error == 1 && s->m_read_to && g_cdvdman_last_cmdfunc == 1))
		&& !g_cdvdman_minver_20200
		&& !s->m_stream_flag
		&& !s->m_dvd_flag
		&& !s->m_recover_status
		&& s->m_read_mode.trycount != 1 )
	{
		s->m_sync_error = 0;
		s->m_interupt_read_state = 0;
		if ( s->m_dec_mode_set )
		{
			s->m_dec_mode_last_set = 1;
		}
		else
		{
			VERBOSE_KPRINTF(1, "dec mode 0x00\n");
			s->m_read_chunk_reprocial_32 = 1 + (0x20 / ((!s->m_read_chunk) ? s->m_read_sectors : s->m_read_chunk));
			s->m_dintrlsn = ( s->m_read_lsn < 0x61 ) ? (s->m_read_lsn + s->m_read_sectors + 48) : (s->m_read_lsn - 80);
			s->m_read_mode.spindlctrl = 16;
			if ( !sceCdRead0_Rty(s->m_dintrlsn, (!s->m_read_chunk) ? s->m_read_sectors : s->m_read_chunk, s->m_read_buf, &s->m_read_mode, (unsigned __int8)s->m_cdvdman_command, 0, 0) )
			{
				s->m_last_error = 48;
				s->m_recover_status = 0;
			}
			else
			{
				ext_passthrough = 1;
			}
		}
	}
	if ( !ext_passthrough )
	{
		char dev5_reg_013_masked; // $s1

		VERBOSE_KPRINTF(1, "Recover_Stat:%d\n", s->m_recover_status);
		dev5_reg_013_masked = dev5_regs.m_dev5_reg_013 & 0xF;
		if ( dev5_reg_013_masked != 0 )
		{
			if ( ((unsigned __int8)s->m_last_error == 48 || ((unsigned __int8)s->m_last_error == 1 && s->m_read_to))
				&& !s->m_recover_status
				&& !s->m_stream_flag
				&& g_cdvdman_cmdfunc != 9
				&& g_cdvdman_cmdfunc != 2
				&& (unsigned int)s->m_read_mode.trycount - 1 >= 4 )
			{
				s->m_sync_error = 0;
				s->m_interupt_read_state = 0;
				if ( s->m_dec_mode_set )
				{
					s->m_dec_mode_last_set = 2;
				}
				else
				{
					VERBOSE_KPRINTF(1, "dec mode 0x01\n");
					cdrmode.trycount = s->m_read_mode.trycount;
					cdrmode.spindlctrl = dev5_reg_013_masked + 13;
					cdrmode.datapattern = s->m_read_mode.datapattern;
					if ( sceCdRead0_Rty(
								 s->m_read_lsn,
								 s->m_read_sectors,
								 s->m_read_buf,
								 &cdrmode,
								 (unsigned __int8)s->m_cdvdman_command,
								 s->m_read_chunk,
								 s->m_read_callback) )
					{
						s->m_last_error = 0;
						return 1;
					}
					s->m_last_error = 48;
				}
			}
		}
		s->m_read_to = 0;
		switch ( s->m_recover_status )
		{
			case 1:
				s->m_sync_error = 0;
				s->m_interupt_read_state = 0;
				if ( s->m_last_error
					|| !sceCdRead0_Rty(s->m_dintrlsn, (!s->m_read_chunk) ? s->m_read_sectors : s->m_read_chunk, s->m_read_buf, &s->m_read_mode, (unsigned __int8)s->m_cdvdman_command, 0, 0) )
				{
					s->m_last_error = 48;
					s->m_recover_status = 0;
				}
				else
				{
					ext_passthrough = 1;
				}
				break;
			case 2:
				s->m_sync_error = 0;
				s->m_interupt_read_state = 0;
				if ( sceCdRead0(
												 s->m_read_lsn,
												 s->m_read_sectors,
												 s->m_read_buf,
												 &s->m_read_mode,
												 s->m_read_chunk,
												 s->m_read_callback) != 0 )
				{
					s->m_last_error = 0;
					s->m_recover_status = 3;
					return 1;
				}
				s->m_last_error = 48;
				s->m_recover_status = 0;
				break;
			case 3:
				s->m_recover_status = 0;
				break;
			default:
				break;
		}
	}
	if ( ext_passthrough )
	{
		s->m_last_error = 0;
		s->m_dintrlsn += s->m_read_sectors;
		s->m_read_chunk_reprocial_32 -= 1;
		s->m_recover_status = (!s->m_read_chunk_reprocial_32) ? 2 : 1;
		return 1;
	}
	if ( s->m_dec_state )
	{
		sceCdDecSet(0, 0, 0);
	}
	if ( (s->m_read2_flag == 1 || s->m_read2_flag == 3) && !s->m_use_toc )
	{
		VERBOSE_KPRINTF(1, "call Read2intrCDVD()\n");
		Read2intrCDVD(s->m_read2_flag);
	}
	s->m_sync_error = 0;
	s->m_interupt_read_state = 0;
	if ( s->m_dec_state == 2 )
	{
		s->m_dec_state = 0;
	}
	if ( s->m_stream_flag == 1 && !s->m_use_toc && !s->m_read2_flag )
	{
		if ( g_cdvdman_cdstm0cb )
		{
			g_cdvdman_cdstm0cb(1);
		}
		else
		{
			VERBOSE_KPRINTF(1, "Intr func0 no seting");
		}
	}
	if ( s->m_stream_flag == 2 && !s->m_use_toc )
	{
		if ( !s->m_read2_flag )
		{
			if ( g_cdvdman_cdstm1cb )
			{
				g_cdvdman_cdstm1cb(1);
			}
			else
			{
				VERBOSE_KPRINTF(1, "Intr func1 no seting");
			}
		}
	}
	else
	{
		if ( !s->m_read2_flag )
		{
			g_cdvdman_readptr = 0;
		}
	}
	VERBOSE_KPRINTF(1, "Intr call user callback func_addr %08x num %d flg %d\n", g_cdvdman_user_cb, g_cdvdman_cmdfunc, s->m_read2_flag);
	if ( g_cdvdman_user_cb && g_cdvdman_cmdfunc && !s->m_read2_flag && !s->m_use_toc )
	{
		int cmdfunc_tmp; // $a0

		cmdfunc_tmp = g_cdvdman_cmdfunc;
		g_cdvdman_cmdfunc = 0;
		if ( cmdfunc_tmp == 14 || cmdfunc_tmp == 9 )
		{
			cmdfunc_tmp = 1;
		}
		g_cdvdman_user_cb(cmdfunc_tmp);
	}
	if ( !g_cdvdman_user_cb )
	{
		g_cdvdman_cmdfunc = 0;
	}
	return 1;
}
// 406EC0: conditional instruction was optimized away because $v1.4!=0
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00407458) --------------------------------------------------------
int __fastcall intrh_cdrom(cdvdman_internal_struct_t *s)
{
	int conds1; // $s2
	iop_event_info_t efinfo; // [sp+18h] [-20h] BYREF

	conds1 = 0;
	s->m_waf_set_test = s->m_wait_flag;
	if ( (unsigned __int8)s->m_last_error != 1 )
	{
		s->m_last_error = dev5_regs.m_dev5_reg_006;
	}
	if ( (dev5_regs.m_dev5_reg_008 & 1) != 0 )
	{
		s->m_waf_set_test = ( (dev5_regs.m_dev5_reg_005 & 1) == 0 ) ? 1 : -1;
		dev5_regs.m_dev5_reg_008 = 1;
		conds1 = 1;
	}
	if ( (dev5_regs.m_dev5_reg_008 & 4) != 0 )
	{
		dev5_regs.m_dev5_reg_008 = 4;
		iSetEventFlag(g_cdvdman_intr_efid, 4u);
		iSetEventFlag(g_cdvdman_intr_efid, 0x10u);
		if ( g_cdvdman_poff_cb )
		{
			g_cdvdman_poff_cb(g_cdvdman_poffarg);
		}
		if ( !conds1 )
		{
			return 1;
		}
	}
	else
	{
		s->m_waf_set_test = 1;
		s->m_ncmd_intr_count += 1;
		dev5_regs.m_dev5_reg_008 = 2;
	}
	iReferEventFlagStatus(g_cdvdman_intr_efid, &efinfo);
	if ( (efinfo.currBits & 0x20) == 0 )
	{
		if ( !s->m_last_error )
		{
			s->m_drive_interupt_request = 1;
			return 1;
		}
		if ( s->m_last_error == 50 )
		{
			intrh_dma_3(s);
		}
	}
	return cdvdman_intr_cb(s);
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00407644) --------------------------------------------------------
u32 __cdecl cdvdman_l1start(const u8 *toc)
{
	return toc[23] + (toc[22] << 8) + (toc[21] << 16) - 196608 + 1;
}

//----- (00407670) --------------------------------------------------------
int __cdecl DvdDual_infochk()
{
	if ( QueryIntrContext() != 0 || !(cdvdman_mediactl(3) || (unsigned __int8)g_cdvdman_istruct.m_opo_or_para == 255) )
	{
		return 1;
	}
	g_cdvdman_istruct.m_use_toc = 1;
	if ( !cdvdman_gettoc(g_cdvdman_ptoc) )
	{
		g_cdvdman_istruct.m_use_toc = 0;
		g_cdvdman_istruct.m_opo_or_para = -1;
		return 0;
	}
	g_cdvdman_istruct.m_use_toc = 0;
	g_cdvdman_istruct.m_layer_1_lsn = cdvdman_l1start(g_cdvdman_ptoc);
	g_cdvdman_istruct.m_opo_or_para = ( (g_cdvdman_ptoc[14] & 0x60) != 0 ) ? (( (g_cdvdman_ptoc[14] & 0x10) != 0 ) ? 2 : 1) : 0;
	if ( g_cdvdman_istruct.m_dual_layer_emulation )
	{
		VERBOSE_KPRINTF(1, "CDVD:DualEmuON\n");
		g_cdvdman_istruct.m_layer_1_lsn = g_cdvdman_istruct.m_current_dvd_lsn;
		g_cdvdman_istruct.m_opo_or_para = 0;
	}
	VERBOSE_KPRINTF(1, "DvdDual_info: %02x\tLayer1_LSN:%d opo_or_para %d\n", g_cdvdman_ptoc[14], g_cdvdman_istruct.m_layer_1_lsn, (unsigned __int8)g_cdvdman_istruct.m_opo_or_para);
	return 1;
}

//----- (004077D0) --------------------------------------------------------
u32 __cdecl sceCdLsnDualChg(u32 lsn)
{
	int layer_disk_needed; // $s1
	u32 change_lsn; // $s0
	sceCdRMode cdrmode; // [sp+18h] [-10h] BYREF
	int has_change_lsn;

	layer_disk_needed = 2;
	has_change_lsn = 0;
	if ( cdvdman_isdvd() != 0 && DvdDual_infochk() != 0 )
	{
		if ( g_cdvdman_istruct.m_dual_layer_emulation )
		{
			if ( !g_cdvdman_istruct.m_current_dvd && lsn >= g_cdvdman_istruct.m_current_dvd_lsn )
			{
				layer_disk_needed = 1;
			}
			if ( g_cdvdman_istruct.m_current_dvd && lsn < g_cdvdman_istruct.m_current_dvd_lsn )
			{
				layer_disk_needed = 0;
			}
			if ( layer_disk_needed == 2 )
			{
				change_lsn = lsn - (( g_cdvdman_istruct.m_current_dvd ) ? g_cdvdman_istruct.m_current_dvd_lsn : 0);
				has_change_lsn = 1;
			}
			else if ( QueryIntrContext() == 0 )
			{
				u32 traycnt[2]; // [sp+20h] [-8h] BYREF

				VERBOSE_KPRINTF(0, "CDVD: Exchange it for the Layer_%d_Disk Please.\n", layer_disk_needed);
				while ( g_cdvdman_minver_60200 ? !cdvdman_scmd_sender_3B(0) : !sceCdTrayReq(0, traycnt) )
				{
					;
				}
				cdrmode.trycount = 0;
				cdrmode.spindlctrl = 0;
				cdrmode.datapattern = 0;
				g_cdvdman_istruct.m_use_toc = 1;
				while ( layer_disk_needed != 2 )
				{
					if ( cdvdman_isdvd() )
					{
						int read0_result; // $s0

						read0_result = sceCdRead0(0xEu, 1u, g_cdvdman_ptoc, &cdrmode, 0, 0);
						sceCdSync(3);
						if ( !g_cdvdman_istruct.m_last_error || read0_result )
						{
							int i; // $a1

							for ( i = 0; i < 20; i += 1 )
							{
								if ( g_cdvdman_ptoc[i + 104] != g_masterdisc_header[i] )
								{
									break;
								}
							}
							if ( i == 20 && g_cdvdman_ptoc[131] == 2 && (g_cdvdman_ptoc[132] & 2) != 0 )
							{
								if ( layer_disk_needed == g_cdvdman_ptoc[133] )
								{
									g_cdvdman_istruct.m_current_dvd = layer_disk_needed;
									layer_disk_needed = 2;
								}
								else
								{
									VERBOSE_KPRINTF(0, "CDVD: Layer_%d Disk not Found\n", layer_disk_needed);
									VERBOSE_KPRINTF(0, "CDVD: Exchange it for the Layer_%d_Disk Please.\n", layer_disk_needed);
									if ( !g_cdvdman_istruct.m_current_dvd && lsn >= g_cdvdman_istruct.m_current_dvd_lsn )
									{
										layer_disk_needed = 1;
									}
									while ( g_cdvdman_minver_60200 ? !cdvdman_scmd_sender_3B(0) : !sceCdTrayReq(0, traycnt) )
									{
										;
									}
								}
							}
							else
							{
								VERBOSE_KPRINTF(0, "CDVD: Not Master Disk %s\n", (const char *)&g_cdvdman_ptoc[i + 104]);
								while ( g_cdvdman_minver_60200 ? !cdvdman_scmd_sender_3B(0) : !sceCdTrayReq(0, traycnt) )
								{
									;
								}
							}
						}
						else
						{
							VERBOSE_KPRINTF(1, "CDVD: LsnDualChg Read Error %02x, %d\n", (unsigned __int8)g_cdvdman_istruct.m_last_error, 0);
						}
					}
					else
					{
						vDelayThread(16000);
					}
				}
				change_lsn = lsn - (( g_cdvdman_istruct.m_current_dvd ) ? g_cdvdman_istruct.m_current_dvd_lsn : 0);
				g_cdvdman_istruct.m_use_toc = 0;
				has_change_lsn = 1;
			}
		}
		else
		{
			change_lsn = lsn - (( g_cdvdman_istruct.m_opo_or_para && (lsn >= (u32)g_cdvdman_istruct.m_layer_1_lsn) ) ? 16 : 0);
			has_change_lsn = 1;
		}
	}
	if ( has_change_lsn )
	{
		VERBOSE_KPRINTF(1, "CDVD: sceCdLsnDualChg lsn %d: change lsn %d\n", lsn, change_lsn);
	}
	return has_change_lsn ? change_lsn : lsn;
}
// 40E604: using guessed type char *g_masterdisc_header;

//----- (00407C5C) --------------------------------------------------------
int __cdecl sceCdReadDvdDualInfo(int *on_dual, unsigned int *layer1_start)
{
	int read0_result; // $s1
	int i; // $a1
	sceCdRMode cdrmode; // [sp+18h] [-8h] BYREF

	*on_dual = 0;
	*layer1_start = 0;
	g_cdvdman_istruct.m_dual_layer_emulation = 0;
	if ( cdvdman_isdvd() == 0 )
	{
		return 1;
	}
	if ( !g_cdvdman_emudvd9 )
	{
		if ( DvdDual_infochk() == 0 )
		{
			return 0;
		}
		*on_dual = g_cdvdman_istruct.m_opo_or_para != 0;
		*layer1_start = g_cdvdman_istruct.m_layer_1_lsn;
		return 1;
	}
	if ( g_cdvdman_mmode != 2 && g_cdvdman_mmode != 255 )
	{
		return 0;
	}
	cdrmode.trycount = 0;
	cdrmode.spindlctrl = 0;
	cdrmode.datapattern = 0;
	read0_result = sceCdRead0(0xEu, 1u, g_cdvdman_ptoc, &cdrmode, 0, 0);
	sceCdSync(3);
	if ( g_cdvdman_istruct.m_last_error && !read0_result )
	{
		VERBOSE_KPRINTF(1, "CDVD: ReadDvdDualInfo Read Error %02x, %d\n", (unsigned __int8)g_cdvdman_istruct.m_last_error, 0);
		return 0;
	}
	for ( i = 0; i < 20; i += 1 )
	{
		if ( g_cdvdman_ptoc[i + 104] != g_masterdisc_header[i] )
		{
			break;
		}
	}
	if ( i != 20 )
	{
		if ( DvdDual_infochk() == 0 )
		{
			return 0;
		}
		*on_dual = g_cdvdman_istruct.m_opo_or_para != 0;
		*layer1_start = g_cdvdman_istruct.m_layer_1_lsn;
		return 1;
	}
	if ( g_cdvdman_ptoc[131] != 2 || (g_cdvdman_ptoc[132] & 2) == 0 )
	{
		return 1;
	}
	g_cdvdman_istruct.m_current_dvd = g_cdvdman_ptoc[133];
	g_cdvdman_istruct.m_current_dvd_lsn = g_cdvdman_ptoc[134]
																	+ (g_cdvdman_ptoc[135] << 8)
																	+ (g_cdvdman_ptoc[136] << 16)
																	+ (g_cdvdman_ptoc[137] << 24)
																	+ 1;
	g_cdvdman_istruct.m_opo_or_para = 0;
	g_cdvdman_istruct.m_layer_1_lsn = g_cdvdman_istruct.m_current_dvd_lsn;
	g_cdvdman_istruct.m_dual_layer_emulation = 1;
	*on_dual = 1;
	*layer1_start = g_cdvdman_istruct.m_layer_1_lsn;
	VERBOSE_KPRINTF(1, "sceCdReadDvdDualInfo():Cur_Disk %d layer1_start %d\n", (unsigned __int8)g_cdvdman_istruct.m_current_dvd, g_cdvdman_istruct.m_current_dvd_lsn);
	return 1;
}
// 40E604: using guessed type char *g_masterdisc_header;

//----- (00407EE8) --------------------------------------------------------
int __cdecl sceCdSC(int code, int *param)
{
	void *poffarg_tmp; // $s0
	int *BootMode; // $v0
	int state; // [sp+10h] [-8h] BYREF
	u32 efbits; // [sp+14h] [-4h] BYREF

	switch ( code )
	{
		case 0xFFFFFFE6:
			CpuSuspendIntr(&state);
			*param = (int)g_cdvdman_poff_cb;
			poffarg_tmp = g_cdvdman_poffarg;
			CpuResumeIntr(state);
			return (int)poffarg_tmp;
		case 0xFFFFFFE7:
			return g_scmd_evid;
		case 0xFFFFFFE9:
			return sceCdLsnDualChg(*param);
		case 0xFFFFFFEA:
			return DvdDual_infochk();
		case 0xFFFFFFEE:
			g_cdvdman_istruct.m_read_to = *param;
			return 0;
		case 0xFFFFFFEF:
			return g_TimeOut2;
		case 0xFFFFFFF0:
			*param = (int)&g_verbose_level;
			return 255;
		case 0xFFFFFFF1:
			return g_cdvdman_sync_to;
		case 0xFFFFFFF2:
			*param = (int)&g_cdvdman_istruct;
			return 255;
		case 0xFFFFFFF3:
			BootMode = QueryBootMode(4);
			if ( BootMode )
			{
				switch ( *(unsigned __int8 *)BootMode )
				{
					case 0:
					case 1:
					case 2:
						g_cdvdman_mmode = 255;
						break;
					case 3:
						g_cdvdman_mmode = 0;
						break;
				}
			}
			return 1;
		case 0xFFFFFFF4:
			// The following call to sceCdGetDiskType was inlined
			switch ( sceCdGetDiskType() )
			{
				case 16:
				case 17:
				case 18:
				case 19:
					return g_cdvdman_mmode == 1 || g_cdvdman_mmode == 255;
				case 20:
					return g_cdvdman_mmode == 2 || g_cdvdman_mmode == 255;
				case 253:
					return g_cdvdman_mmode == 255;
				default:
					return 0;
			}
		case 0xFFFFFFF5:
			return g_cdvdman_intr_efid;
		case 0xFFFFFFF6:
			if ( *param )
			{
				WaitEventFlag(g_fio_fsv_evid, 1u, 16, &efbits);
			}
			else
			{
				SetEventFlag(g_fio_fsv_evid, 1u);
			}
			g_cdvdman_strm_id = *param;
			VERBOSE_KPRINTF(1, "EE_ncmd_working code= %d\n", *param);
			return g_cdvdman_strm_id;
		case 0xFFFFFFF7:
			return (unsigned __int16)_irx_id.v;
		case 0xFFFFFFF8:
			g_cdvdman_spinctl = *param;
			return 1;
		case 0xFFFFFFFC:
			return g_cdvdman_cd36key;
		case 0xFFFFFFFD:
			return g_cdvdman_istruct.m_read2_flag;
		case 0xFFFFFFFE:
			g_cdvdman_istruct.m_last_error = *(_BYTE *)param;
			return (unsigned __int8)g_cdvdman_istruct.m_last_error;
		case 0xFFFFFFFF:
		case 0:
		case 1:
		case 2:
			*param = (unsigned __int8)g_cdvdman_istruct.m_last_error;
			if ( code != -1 )
			{
				g_cdvdman_istruct.m_stream_flag = code;
			}
			return g_cdvdman_istruct.m_stream_flag;
		default:
			VERBOSE_KPRINTF(1, "sceCdSC func_num Not found %d\n", code);
			return 0;
	}
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00408224) --------------------------------------------------------
void __cdecl nullsub_2()
{
	;
}

//----- (0040822C) --------------------------------------------------------
void __cdecl cdvdman_init()
{
	int *BootMode; // $v0
	unsigned int i; // $s0
	int scres; // [sp+10h] [-8h] BYREF
	u32 argres; // [sp+14h] [-4h] BYREF

	g_cdvdman_user_cb = 0;
	g_cdvdman_poff_cb = 0;
	g_cdvdman_cmdfunc = 0;
	g_cdvdman_istruct.m_drive_interupt_request = 0;
	RegisterIntrHandler(2, 1, (int (__cdecl *)(void *))intrh_cdrom, &g_cdvdman_istruct);
	RegisterIntrHandler(35, 1, (int (__cdecl *)(void *))intrh_dma_3, &g_cdvdman_istruct);
	EnableIntr(2);
	sceCdSC(0xFFFFFFF3, &scres);
	dmac_set_dpcr(dmac_get_dpcr() | 0x8000);
	dmac_ch_set_chcr(3u, 0);
	if ( (dev5_regs.m_dev5_reg_008 & 4) != 0 )
	{
		dev5_regs.m_dev5_reg_008 = 4;
	}
	if ( (dev5_regs.m_dev5_reg_008 & 1) != 0 )
	{
		dev5_regs.m_dev5_reg_008 = 1;
	}
	g_cdvdman_clk_flg = sceCdReadClock(&g_cdvdman_clock) ? (g_cdvdman_clock.stat == 0) : 0;
	g_cdvdman_istruct.m_tray_is_open = (dev5_regs.m_dev5_reg_00A ^ 1) & 1;
	cdvdman_initcfg();
	BootMode = QueryBootMode(6);
	g_cdvdman_istruct.m_no_dec_flag = BootMode ? ((*(_WORD *)BootMode & 0xFFFC) == 0x60) : 0;
	for ( i = 0; i < 0x3D && (!sceCdCancelPOffRdy(&argres) || argres); i += 1 )
	{
		DelayThread(16000);
	}
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (004083E8) --------------------------------------------------------
int __cdecl sceCdInit(int mode)
{
	VERBOSE_PRINTF(1, "sceCdInit called mode= %d\n", mode);
	if ( mode == 5 )
	{
		int oldstate[2]; // [sp+10h] [-8h] BYREF

		g_cdvdman_istruct.m_cd_inited = 0;
		sceCdBreak();
		sceCdSync(3);
		cdvdman_ncmd_sender_06();
		sceCdSync(0);
		VERBOSE_PRINTF(1, "Cdvdman Exit\n");
		DisableIntr(2, oldstate);
		ReleaseIntrHandler(2);
		DisableIntr(35, oldstate);
		ReleaseIntrHandler(35);
	}
	else
	{
		VERBOSE_PRINTF(1, "Cdvdman Init\n");
		g_cdvdman_istruct.m_read2_flag = 0;
		g_cdvdman_istruct.m_dec_shift = 0;
		g_cdvdman_istruct.m_check_version = 0;
		g_cdvdman_istruct.m_dec_state = 0;
		sceCdDecSet(0, 0, 0);
		cdvdman_init();
		g_cdvdman_istruct.m_cd_inited = 1;
	}
	if ( !mode )
	{
		vu8 ready_status_tmp; // $s1
		vu8 ready_status; // $s0
		int ready_status_mask_c0h; // $v0

		ready_status_tmp = 0;
		VERBOSE_PRINTF(1, "sceCdInit Ready check start.\n");
		for ( ready_status_mask_c0h = 0; ready_status_mask_c0h != 64; ready_status_mask_c0h = ready_status & 0xC0 )
		{
			ready_status = dev5_regs.m_dev5_reg_005;
			vDelayThread(10000);
			if ( ready_status != ready_status_tmp )
			{
				ready_status_tmp = ready_status;
				VERBOSE_PRINTF(1, "sceCdInit Dev5 Status %x\n", ready_status);
			}
		}
		VERBOSE_PRINTF(1, "sceCdInit Ready check end.\n");
	}
	g_cdvdman_istruct.m_wait_flag = 1;
	g_cdvdman_istruct.m_scmd_flag = 1;
	g_cdvdman_istruct.m_last_error = 0;
	g_cdvdman_istruct.m_read_to = 0;
	g_cdvdman_spinctl = -1;
	SetEventFlag(g_cdvdman_intr_efid, 0x29u);
	SetEventFlag(g_ncmd_evid, 1u);
	SetEventFlag(g_scmd_evid, 1u);
	SetEventFlag(g_sfile_evid, 1u);
	return 1;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00408660) --------------------------------------------------------
int __cdecl set_prev_command(int cmd, const char *sdata, int sdlen, char *rdata, int rdlen, int check_sef)
{
	int i; // $s0
	int delaybackoff; // $s1
	int j; // $s0
	u32 efbits[2]; // [sp+10h] [-8h] BYREF

	if ( check_sef == 1 && PollEventFlag(g_scmd_evid, 1u, 16, efbits) == -421 )
	{
		return 0;
	}
	g_cdvdman_istruct.m_scmd = cmd;
	g_cdvdman_istruct.m_sdlen = sdlen;
	g_cdvdman_istruct.m_rdlen = rdlen;
	for ( i = 0; i < sdlen; i += 1 )
	{
		g_cdvdman_istruct.m_scmd_sd[i] = sdata[i];
	}
	if ( g_cdvdman_istruct.m_wait_flag )
	{
		g_cdvdman_istruct.m_scmd_flag = 1;
		cdvdman_write_scmd(&g_cdvdman_istruct);
	}
	else if ( QueryIntrContext() )
	{
		while ( (dmac_ch_get_chcr(3u) & 0x1000000) != 0 && !g_cdvdman_istruct.m_wait_flag )
		{
			VERBOSE_KPRINTF(1, "set_prev_command: DMA Wait\n");
		}
		g_cdvdman_istruct.m_scmd_flag = 1;
		cdvdman_write_scmd(&g_cdvdman_istruct);
	}
	else
	{
		g_cdvdman_istruct.m_scmd_flag = 0;
	}
	delaybackoff = 1;
	for ( i = 0; i < 500; i += delaybackoff )
	{
		if ( g_cdvdman_istruct.m_scmd_flag )
		{
			for ( j = 0; j < rdlen; j += 1 )
			{
				rdata[j] = g_cdvdman_istruct.m_scmd_rd[j];
			}
			if ( check_sef == 1 )
			{
				vSetEventFlag(g_scmd_evid, 1u);
			}
			return (unsigned __int8)g_cdvdman_istruct.m_scmd;
		}
		vDelayThread(1000 * delaybackoff);
		if ( (i & 1) != 0 && delaybackoff < 16 )
		{
			delaybackoff *= 2;
		}
	}
	g_cdvdman_istruct.m_scmd_flag = 1;
	if ( check_sef == 1 )
	{
		vSetEventFlag(g_scmd_evid, 1u);
	}	
	return 0;
}
// 408834: conditional instruction was optimized away because $s0.4<1F4

//----- (004088EC) --------------------------------------------------------
void __cdecl cdvdman_write_scmd(cdvdman_internal_struct_t *s)
{
	int i; // $s5
	unsigned int j;
	unsigned int rdcnt;
	char rdptr1[64]; // [sp+18h] [-40h] BYREF

	for ( i = 0; i <= 0; i += 1 )
	{
		int overflowcond; // $a2

		if ( (dev5_regs.m_dev5_reg_017 & 0x80) != 0 )
		{
			*(_WORD *)&s->m_scmd_flag = 1;
			return;
		}
		while ( (dev5_regs.m_dev5_reg_017 & 0x40) == 0 )
		{
			;
		}
		for ( j = 0; j < (unsigned __int8)s->m_sdlen; j += 1 )
		{
			dev5_regs.m_dev5_reg_017 = s->m_scmd_sd[j];
		}
		dev5_regs.m_dev5_reg_016 = s->m_scmd;
		if ( QueryIntrContext() )
		{
			for ( j = 0; (dev5_regs.m_dev5_reg_017 & 0x80) != 0; j += 1 )
			{
				if ( j > 12500000 )
				{
					*(_WORD *)&s->m_scmd_flag = 1;
					return;
				}
			}
		}
		else
		{
			for ( j = 0; (dev5_regs.m_dev5_reg_017 & 0x80) != 0; j += 1 )
			{
				DelayThread(100);
				if ( j > 50000 )
				{
					*(_WORD *)&s->m_scmd_flag = 1;
					return;
				}
			}
		}
		overflowcond = 0;
		for ( j = 0; j < (unsigned __int8)s->m_rdlen; j += 1 )
		{
			if ( (dev5_regs.m_dev5_reg_017 & 0x40) != 0 )
			{
				break;
			}
			rdptr1[j] = dev5_regs.m_dev5_reg_018;
		}
		if ( j >= (unsigned __int8)s->m_rdlen )
		{
			overflowcond = 1;
			VERBOSE_KPRINTF(1, "Prev Cmd Result Over Flow\n", rdptr1);
		}
		rdcnt = j;
		if ( (!overflowcond && j >= (unsigned __int8)s->m_rdlen) || s->m_rdlen == 16 )
		{
			break;
		}
		VERBOSE_KPRINTF(1, "Prev Cmd Result Illegal Size Try count:%d\n", i);
	}
	if ( i == 1 )
	{
		*(_WORD *)&s->m_scmd_flag = 1;
	}
	else
	{
		for ( j = 0; j < (sizeof(s->m_scmd_rd)/sizeof(s->m_scmd_rd[0])); j += 1 )
		{
			s->m_scmd_rd[j] = 0;
		}
		if ( s->m_rdlen != (sizeof(s->m_scmd_rd)/sizeof(s->m_scmd_rd[0])) )
		{
			rdcnt = (unsigned __int8)s->m_rdlen;
		}
		for ( j = 0; j < rdcnt; j += 1 )
		{
			s->m_scmd_rd[j] = rdptr1[j];
		}
		s->m_scmd_flag = 1;
		s->m_scmd = 1;
	}
}
// BF402000: using guessed type dev5_regs_t dev5_regs;
// 4088EC: using guessed type char rdptr1[64];

//----- (00408C10) --------------------------------------------------------
int __cdecl cdvdman_send_scmd2(int cmd, const void *sdata, int sdlen, void *rdata, int rdlen, int check_sef)
{
	int i; // $s3
	int j; // $s0
	char rdstart[64]; // [sp+18h] [-50h] BYREF
	u32 efbits; // [sp+58h] [-10h] BYREF

	if ( check_sef == 1 && PollEventFlag(g_scmd_evid, 1u, 16, &efbits) == -421 )
	{
		return 0;
	}
	for ( i = 0; i <= 0; i += 1 )
	{
		int cmdresoverflow; // $a1

		if ( (dev5_regs.m_dev5_reg_017 & 0x80) != 0 )
		{
			if ( check_sef == 1 )
			{
				vSetEventFlag(g_scmd_evid, 1u);
			}
			return 0;
		}
		while ( (dev5_regs.m_dev5_reg_017 & 0x40) == 0 )
		{
			;
		}
		for ( j = 0; j < sdlen; j += 1 )
		{
			dev5_regs.m_dev5_reg_017 = ((_BYTE *)sdata)[j];
		}
		dev5_regs.m_dev5_reg_016 = cmd;
		while ( (dev5_regs.m_dev5_reg_017 & 0x80) != 0 )
		{
			DelayThread(100);
		}
		cmdresoverflow = 0;
		for ( j = 0; (dev5_regs.m_dev5_reg_017 & 0x40) == 0; j += 1 )
		{
			if ( j >= rdlen )
			{
				cmdresoverflow = 1;
				VERBOSE_KPRINTF(1, "Prev Cmd Result Over Flow\n");
				break;
			}
			rdstart[j] = dev5_regs.m_dev5_reg_018;
		}
		if ( (!cmdresoverflow && j >= rdlen) || rdlen == 16 )
		{
			break;
		}
		VERBOSE_KPRINTF(1, "Prev Cmd Result Illegal Size Try count:%d\n", i);
		while ( (dev5_regs.m_dev5_reg_017 & 0x20) == 0 )
		{
			;
		}
		for ( j = 0; j < 16 - rdlen; j += 1 );
	}
	if ( i == 1 )
	{
		if ( check_sef == 1 )
		{
			vSetEventFlag(g_scmd_evid, 1u);
		}
		return 0;
	}
	for ( i = 0; i < rdlen; i += 1 )
	{
		((char *)rdata)[i] = rdstart[i];
	}
	if ( check_sef == 1 )
	{
		vSetEventFlag(g_scmd_evid, 1u);
	}
	return 1;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;
// 408C10: using guessed type char rdstart[64];

//----- (00408F50) --------------------------------------------------------
int __cdecl sceCdApplySCmd(u8 cmdNum, const void *inBuff, u16 inBuffSize, void *outBuff)
{
	int i; // $s0

	for ( i = 0; i < 2501; i += 1 )
	{
		if ( set_prev_command(cmdNum, (const char *)inBuff, inBuffSize, (char *)outBuff, 16, 1) )
		{
			DelayThread(2000);
			return 1;
		}
		DelayThread(2000);
	}
	KPRINTF("CDVD: set_prev_command TIMEOUT 5(SEC)\n");
	return 0;
}

//----- (00409014) --------------------------------------------------------
int __cdecl sceCdApplySCmd2(u8 cmdNum, const void *inBuff, unsigned long int inBuffSize, void *outBuff)
{
	int i; // $s0

	for ( i = 0; i < 2501; i += 1 )
	{
		if ( cdvdman_send_scmd2(cmdNum, inBuff, inBuffSize, outBuff, 16, 1) != 0 )
		{
			return 1;
		}
		DelayThread(2000);
	}
	KPRINTF("CDVD: set_prev_command TIMEOUT 5(SEC)\n");
	return 0;
}

//----- (004090C8) --------------------------------------------------------
int __fastcall sceCdApplySCmd3(u8 cmdNum, const void *inBuff, unsigned long int inBuffSize, void *outBuff)
{
	int i; // $s0

	for ( i = 0; i < 2501; i += 1 )
	{
		DelayThread(2000);
		if ( set_prev_command((unsigned __int8)cmdNum, inBuff, inBuffSize, outBuff, 16, 1) )
		{
			DelayThread(2000);
			return 1;
		}
	}
	KPRINTF("CDVD: set_prev_command TIMEOUT 5(SEC)\n");
	return 0;
}

//----- (0040918C) --------------------------------------------------------
int sceCdBreak(void)
{
	u32 efbits; // [sp+18h] [-10h] BYREF
	int state; // [sp+1Ch] [-Ch] BYREF
	int oldstate; // [sp+20h] [-8h] BYREF

	if ( PollEventFlag(g_ncmd_evid, 1u, 16, &efbits) == -421 )
	{
		return 0;
	}
	CpuSuspendIntr(&state);
	VERBOSE_KPRINTF(1, "Break call: read2_flg= %d func= %d lsn= %d csec= %d nsec= %d\n", g_cdvdman_istruct.m_read2_flag, g_cdvdman_cmdfunc, g_cdvdman_istruct.m_cdvdman_lsn, g_cdvdman_istruct.m_cdvdman_csec, g_cdvdman_istruct.m_cdvdman_nsec);
	if ( g_cdvdman_istruct.m_read_to )
	{
		g_cdvdman_istruct.m_read2_flag = 0;
	}
	g_cdvdman_istruct.m_last_error = 1;
	g_cdvdman_istruct.m_thread_id = GetThreadId();
	g_cdvdman_istruct.m_break_cdvdfsv_readchain = 1;
	if ( g_cdvdman_istruct.m_dec_state )
	{
		g_cdvdman_istruct.m_dec_shift = 0;
		g_cdvdman_istruct.m_check_version = 0;
		g_cdvdman_istruct.m_dec_state = 0;
		sceCdDecSet(0, 0, 0);
	}
	g_cdvdman_istruct.m_recover_status = 0;
	if ( QueryIntrContext() )
	{
		iSetEventFlag(g_cdvdman_intr_efid, 0x29u);
		iCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb_read, &g_cdvdman_racb_to);
	}
	else
	{
		SetEventFlag(g_cdvdman_intr_efid, 0x29u);
		CancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb_read, &g_cdvdman_racb_to);
	}
	if ( !g_cdvdman_istruct.m_wait_flag || g_cdvdman_istruct.m_read_to )
	{
		if ( (dev5_regs.m_dev5_reg_005 & 0xC0) == 64 )
		{
			VERBOSE_KPRINTF(1, "cdvd: NonInter END\n");
			g_cdvdman_istruct.m_wait_flag = 1;
		}
		g_cdvdman_last_cmdfunc = g_cdvdman_cmdfunc;
		g_cdvdman_cmdfunc = 8;
		dev5_regs.m_dev5_reg_007 = 1;
		if ( g_cdvdman_istruct.m_read_to )
		{
			DisableIntr(35, &oldstate);
		}
		g_cdvdman_istruct.m_drive_interupt_request = 0;
		VERBOSE_KPRINTF(1, "cdvd: Abort command On\n");
	}
	vSetEventFlag(g_ncmd_evid, 1u);
	CpuResumeIntr(state);
	return 1;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (004093F4) --------------------------------------------------------
int __fastcall cd_ncmd_timeout_callback(iop_sys_clock_t *sys_clock)
{
	KPRINTF("Cmd Time Out %d(msec)\n", sys_clock->lo / 0x9000);
	sys_clock->lo = 0;
	return 0;
}

//----- (00409440) --------------------------------------------------------
int __fastcall intrh_dma_3(cdvdman_internal_struct_t *s)
{
	int dmacbres; // $a2
	int oldstate; // [sp+14h] [-4h] BYREF

	s->m_dma3prm.m_dma3_msectors -= s->m_dma3prm.m_dma3_csectors;
	dmacbres = s->m_dma3prm.m_dma3_callback ? s->m_dma3prm.m_dma3_callback() : 1;
	s->m_cdvdman_dma3sec += s->m_dma3prm.m_dma3_csectors;
	s->m_dma3prm.m_dma3_csectors = ((u32)s->m_read_chunk > (u32)s->m_dma3prm.m_dma3_msectors) ? (u32)s->m_dma3prm.m_dma3_msectors : (u32)s->m_read_chunk;
	if ( dmacbres )
	{
		if ( s->m_dma3prm.m_dma3_msectors )
		{
			dmac_ch_set_chcr(3u, 0);
			dmac_ch_get_chcr(3u);
			dmac_ch_set_madr(3u, (u32)s->m_dma3prm.m_dma3_maddress);
			dmac_ch_set_bcr(3u, ((s->m_dma3prm.m_dma3_blkcount * s->m_dma3prm.m_dma3_csectors) << 16) | s->m_dma3prm.m_dma3_blkwords);
			dmac_ch_set_chcr(3u, 0x41000200u);
			dmac_ch_get_chcr(3u);
			iClearEventFlag(g_cdvdman_intr_efid, 0xFFFFFFDF);
		}
		else
		{
			DisableIntr(35, &oldstate);
			iSetEventFlag(g_cdvdman_intr_efid, 0x20u);
		}
	}
	if ( !s->m_dma3prm.m_dma3_msectors && s->m_drive_interupt_request )
	{
		cdvdman_intr_cb(s);
		s->m_drive_interupt_request = 0;
	}
	return 1;
}

//----- (004095AC) --------------------------------------------------------
int __cdecl cdvdman_setdma3(DMA3PARAM *b18)
{
	if ( (dmac_ch_get_chcr(3u) & 0x1000000) != 0 )
	{
		dev5_regs.m_dev5_reg_007 = 1;
	}
	g_cdvdman_istruct.m_drive_interupt_request = 0;
	g_cdvdman_istruct.m_dma3prm.m_dma3_blkwords = b18->m_dma3_blkwords;
	g_cdvdman_istruct.m_dma3prm.m_dma3_blkcount = b18->m_dma3_blkcount;
	g_cdvdman_istruct.m_dma3prm.m_dma3_maddress = b18->m_dma3_maddress;
	g_cdvdman_istruct.m_dma3prm.m_dma3_callback = b18->m_dma3_callback;
	g_cdvdman_istruct.m_dma3prm.m_dma3_csectors = b18->m_dma3_csectors;
	g_cdvdman_istruct.m_dma3prm.m_cdvdreg_howto = b18->m_cdvdreg_howto;
	g_cdvdman_istruct.m_dma3prm.m_dma3_msectors = b18->m_dma3_msectors;
	g_cdvdman_istruct.m_cdvdman_dma3sec = 0;
	dmac_ch_set_chcr(3u, 0);
	dmac_ch_get_chcr(3u);
	if ( b18->m_dma3_csectors )
	{
		vClearEventFlag(g_cdvdman_intr_efid, 0xFFFFFFDF);
		EnableIntr(35);
	}
	dev5_regs.m_dev5_reg_006 = b18->m_cdvdreg_howto;
	dmac_ch_set_madr(3u, (u32)b18->m_dma3_maddress);
	dmac_ch_set_bcr(3u, (b18->m_dma3_blkcount * (b18->m_dma3_csectors ? b18->m_dma3_csectors : 1)) << 16 | b18->m_dma3_blkwords);
	dmac_ch_set_chcr(3u, 0x41000200u);
	return dmac_ch_get_chcr(3u);
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (004096F4) --------------------------------------------------------
int __cdecl cdvdman_send_ncmd(int ncmd, const void *ndata, int ndlen, int func, DMA3PARAM *b18, int check_cb)
{
	int i; // $v1
	u32 efbits; // [sp+14h] [-4h] BYREF

	if ( check_cb == 1 && PollEventFlag(g_ncmd_evid, 1u, 16, &efbits) == -421 )
	{
		return -1;
	}
	if ( (dev5_regs.m_dev5_reg_005 & 0xC0) != 64
		|| !g_cdvdman_istruct.m_wait_flag
		|| !(g_cdvdman_istruct.m_read2_flag != 1 || ncmd == 8)
		|| !(g_cdvdman_istruct.m_read2_flag != 2 || ncmd == 6) )
	{
		if ( check_cb == 1 )
		{
			vSetEventFlag(g_ncmd_evid, 1u);
		}
		VERBOSE_KPRINTF(1, "set_cd_commnad Error\tstat %02x\n", (unsigned __int8)dev5_regs.m_dev5_reg_005);
		return -1;
	}
	g_cdvdman_iocache = 0;
	if ( b18 )
	{
		cdvdman_setdma3(b18);
	}
	g_cdvdman_cmdfunc = func;
	// The following call to sceCdGetDiskType was inlined
	if ( !g_cdvdman_minver_10700
		&& g_cdvdman_ncmd == 6
		&& ncmd
		&& ncmd != g_cdvdman_ncmd
		&& ncmd != 7
		&& ncmd != 14
		&& ncmd != 8
		&& (sceCdGetDiskType() != 253 || ncmd == 3) )
	{
		g_cdvdman_ncmd_to.hi = 0;
		g_cdvdman_ncmd_to.lo = 0x6978000;
		vSetAlarm(&g_cdvdman_ncmd_to, (unsigned int (__cdecl *)(void *))cd_ncmd_timeout_callback, &g_cdvdman_ncmd_to);
		while ( dev5_regs.m_dev5_reg_00A != 10 )
		{
			VERBOSE_KPRINTF(1, "Read Pause 1 chk status 0x%02x\n", dev5_regs.m_dev5_reg_00A);
			if ( !g_cdvdman_ncmd_to.lo )
			{
				g_cdvdman_ncmd = ncmd;
				if ( check_cb == 1 )
				{
					vSetEventFlag(g_ncmd_evid, 1u);
				}
				KPRINTF("Time Out Pause WAIT set_cd_commnad\n");
				return -1;
			}
			vDelayThread(1000);
		}
		vCancelAlarm((unsigned int (__cdecl *)(void *))cd_ncmd_timeout_callback, &g_cdvdman_ncmd_to);
	}
	g_cdvdman_ncmd = ncmd;
	if ( g_cdvdman_istruct.m_dec_state )
	{
		sceCdDecSet(g_cdvdman_istruct.m_dec_shift != 0, 1u, g_cdvdman_istruct.m_dec_shift);
	}
	g_cdvdman_istruct.m_read_to = 0;
	g_cdvdman_istruct.m_cdvdman_command = ncmd;
	g_cdvdman_istruct.m_last_error = 0;
	g_cdvdman_istruct.m_wait_flag = 0;
	g_cdvdman_istruct.m_thread_id = GetThreadId();
	if ( QueryIntrContext() )
	{
		iClearEventFlag(g_cdvdman_intr_efid, 0xFFFFFFFE);
	}
	else
	{
		ClearEventFlag(g_cdvdman_intr_efid, 0xFFFFFFFE);
	}
	for ( i = 0; i < ndlen; i += 1 )
	{
		dev5_regs.m_dev5_reg_005 = ((u8 *)ndata)[i];
	}
	dev5_regs.m_dev5_reg_004 = ncmd;
	if ( check_cb == 1 )
	{
		vSetEventFlag(g_ncmd_evid, 1u);
	}
	return 0;
}
// 40E608: using guessed type char g_cdvdman_ncmd;
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00409AB8) --------------------------------------------------------
int __cdecl sceCdApplyNCmd(u8 cmdNum, const void *inBuff, u16 inBuffSize)
{
	VERBOSE_KPRINTF(1, "Apply NCmd call cmd= 0x%02x\n", cmdNum);
	while ( cdvdman_send_ncmd(cmdNum, inBuff, inBuffSize, 0, 0, 1) < 0 )
	{
		vDelayThread(2000);
	}
	sceCdSync(4);
	return 1;
}

//----- (00409B58) --------------------------------------------------------
int sceCdCheckCmd(void)
{
	return g_cdvdman_istruct.m_wait_flag;
}

//----- (00409B6C) --------------------------------------------------------
int __cdecl cdvdman_mediactl(int code)
{
	int reg_00B_tmp_1; // $a1
	int restmp; // $s0
	u32 efbits; // [sp+18h] [-8h] BYREF
	int rdata; // [sp+1Ch] [-4h] BYREF

	rdata = 0;
	if ( PollEventFlag(g_scmd_evid, 1u, 16, &efbits) == -421 )
	{
		return 0;
	}
	reg_00B_tmp_1 = dev5_regs.m_dev5_reg_00B & 1;
	if ( reg_00B_tmp_1 == g_cdvdman_chmedia )
	{
		restmp = 0;
		if ( g_cdvdman_chflags[code] )
		{
			g_cdvdman_chflags[code] = 0;
			restmp = 1;
		}
	}
	else
	{
		unsigned int i; // $a0

		for ( i = 0; i < (sizeof(g_cdvdman_chflags)/sizeof(g_cdvdman_chflags[0])); i += 1 )
		{
			g_cdvdman_chflags[i] = i != (unsigned int)code;
		}
		restmp = 1;
	}
	if ( ((dev5_regs.m_dev5_reg_00A) & 1) != reg_00B_tmp_1 )
	{
		while ( !set_prev_command(5, 0, 0, (char *)&rdata, 1, 0) || rdata )
		{
			vDelayThread(4000);
		}
	}
	g_cdvdman_chmedia = dev5_regs.m_dev5_reg_00B & 1;
	vSetEventFlag(g_scmd_evid, 1u);
	return restmp;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00409CD4) --------------------------------------------------------
int sceCdGetError(void)
{
	if ( g_cdvdman_istruct.m_last_error )
	{
		VERBOSE_KPRINTF(1, "sceCdGetError: 0x%02x\n", (unsigned __int8)g_cdvdman_istruct.m_last_error);
	}
	return (unsigned __int8)g_cdvdman_istruct.m_last_error;
}

//----- (00409D38) --------------------------------------------------------
int __cdecl cdvdman_get_last_command()
{
	return (unsigned __int8)g_cdvdman_istruct.m_cdvdman_command;
}

//----- (00409D4C) --------------------------------------------------------
int sceCdNop(void)
{
	return cdvdman_send_ncmd(0, 0, 0, 0, 0, 1) >= 0;
}

//----- (00409D88) --------------------------------------------------------
int __cdecl cdvdman_ncmd_sender_01()
{
	return cdvdman_send_ncmd(1, 0, 0, 0, 0, 1) >= 0;
}

//----- (00409DC4) --------------------------------------------------------
int __cdecl cdvdman_ncmd_sender_06()
{
	int i; // $s0
	DMA3PARAM b18; // [sp+18h] [-28h] BYREF
	char ndata[16]; // [sp+30h] [-10h] BYREF

	// The following call to sceCdGetDiskType was inlined
	if ( !sceCdGetDiskType() )
	{
		return 1;
	}
	for ( i = 0; i < 48; i += 8 )
	{
		KPRINTF("CMD_READP call\n");
		ndata[0] = i + 17;
		ndata[3] = 0;
		ndata[2] = 0;
		ndata[1] = 0;
		ndata[4] = 8;
		ndata[7] = 0;
		ndata[6] = 0;
		ndata[5] = 0;
		ndata[8] = 0;
		ndata[9] = 1;
		ndata[10] = 0;
		b18.m_cdvdreg_howto = 128;
		b18.m_dma3_blkwords = 32;
		b18.m_dma3_blkcount = 128;
		b18.m_dma3_csectors = 0;
		b18.m_dma3_msectors = 0;
		b18.m_dma3_callback = 0;
		b18.m_dma3_maddress = g_cdvdman_ptoc;
		if ( cdvdman_send_ncmd(6, ndata, 11, 5, &b18, 1) < 0 )
		{
			return 0;
		}
		sceCdSync(3);
	}
	return 1;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00409EE4) --------------------------------------------------------
int sceCdStandby(void)
{
	DMA3PARAM b18; // [sp+18h] [-28h] BYREF
	char ndata[16]; // [sp+30h] [-10h] BYREF

	// The following call to sceCdGetDiskType was inlined
	switch ( sceCdGetDiskType() )
	{
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
			ndata[0] = 16;
			ndata[4] = 1;
			ndata[9] = 1;
			b18.m_cdvdreg_howto = 128;
			b18.m_dma3_blkwords = 32;
			b18.m_dma3_blkcount = 16;
			ndata[3] = 0;
			ndata[2] = 0;
			ndata[1] = 0;
			ndata[7] = 0;
			ndata[6] = 0;
			ndata[5] = 0;
			ndata[8] = 0;
			ndata[10] = 0;
			b18.m_dma3_csectors = 0;
			b18.m_dma3_msectors = 0;
			b18.m_dma3_callback = 0;
			b18.m_dma3_maddress = g_cdvdman_ptoc;
			return cdvdman_send_ncmd(6, ndata, 11, 5, &b18, 1) >= 0;
		default:
			return cdvdman_send_ncmd(2, 0, 0, 5, 0, 1) >= 0;
	}
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00409FD0) --------------------------------------------------------
int sceCdStop(void)
{
	return cdvdman_send_ncmd(3, 0, 0, 6, 0, 1) >= 0;
}

//----- (0040A00C) --------------------------------------------------------
int sceCdPause(void)
{
	return cdvdman_send_ncmd(4, 0, 0, 7, 0, 1) >= 0;
}

//----- (0040A048) --------------------------------------------------------
int __cdecl cdvdman_ncmd_sender_0B()
{
	char ndata[16]; // [sp+18h] [-10h] BYREF

	ndata[0] = 1;
	return cdvdman_send_ncmd(11, ndata, 1, 0, 0, 1) >= 0;
}
// 40A048: using guessed type char ndata[16];

//----- (0040A08C) --------------------------------------------------------
int __fastcall readtoc_timeout_func(iop_sys_clock_t *s)
{
	KPRINTF("Cmd Time Out %d(msec)\n", s->lo / 0x9000);
	dev5_regs.m_dev5_reg_007 = 1;
	s->lo = 0;
	return 0;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (0040A0EC) --------------------------------------------------------
int __cdecl cdvdman_readtoc(u8 *toc, int param, int func)
{
	int errcond; // $s0
	DMA3PARAM b18; // [sp+18h] [-28h] BYREF
	iop_sys_clock_t clk; // [sp+30h] [-10h] BYREF
	char ndata[8]; // [sp+38h] [-8h] BYREF

	// The following call to sceCdGetDiskType was inlined
	switch ( sceCdGetDiskType() )
	{
		case 20:
		case 252:
		case 254:
			b18.m_cdvdreg_howto = 132;
			b18.m_dma3_blkwords = 4;
			b18.m_dma3_blkcount = 129;
			b18.m_dma3_maddress = toc;
			b18.m_dma3_msectors = 0;
			b18.m_dma3_csectors = 0;
			b18.m_dma3_callback = 0;
			ndata[0] = param;
			break;
		case 16:
		case 17:
		case 18:
		case 19:
			b18.m_cdvdreg_howto = 128;
			b18.m_dma3_blkwords = 32;
			b18.m_dma3_blkcount = 8;
			b18.m_dma3_maddress = toc;
			b18.m_dma3_msectors = 0;
			b18.m_dma3_csectors = 0;
			b18.m_dma3_callback = 0;
			ndata[0] = 0;
			break;
		case 253:
			break;
		default:
			return 0;
	}
	if ( cdvdman_send_ncmd(9, ndata, 1, func, &b18, 1) < 0 )
	{
		return 0;
	}
	clk.hi = 0;
	clk.lo = 368640000;
	vSetAlarm(&clk, (unsigned int (__cdecl *)(void *))readtoc_timeout_func, &clk);
	sceCdSync(3);
	vCancelAlarm((unsigned int (__cdecl *)(void *))readtoc_timeout_func, &clk);
	errcond = sceCdGetError() == 0;
	if ( g_cdvdman_minver_10700 && !sceCdPause() )
	{
		return 0;
	}
	sceCdSync(3);
	return errcond;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;
// 40A0EC: using guessed type char ndata[8];

//----- (0040A280) --------------------------------------------------------
int __cdecl cdvdman_gettoc(u8 *toc)
{
	return cdvdman_readtoc(toc, 0, 3);
}

//----- (0040A2A4) --------------------------------------------------------
u32 sceCdGetReadPos(void)
{
	int sector_sizes[4]; // [sp+10h] [-10h]

	sector_sizes[0] = 2048;
	sector_sizes[1] = 2328;
	sector_sizes[2] = 2340;
	if ( g_cdvdman_istruct.m_recover_status && g_cdvdman_istruct.m_recover_status != 3 )
	{
		return 0;
	}
	if ( g_cdvdman_cmdfunc == 2 || g_cdvdman_cmdfunc == 12 )
	{
		return dmac_ch_get_madr(3u) - (_DWORD)g_cdvdman_readbuf;
	}
	if ( g_cdvdman_istruct.m_read2_flag )
	{
		return g_cdvdman_readptr * sector_sizes[g_cdvdman_istruct.m_cdvdman_pattern];
	}
	if ( g_cdvdman_cmdfunc == 1 )
	{
		return dmac_ch_get_madr(3u) - (_DWORD)g_cdvdman_readbuf;
	}
	return 0;
}

//----- (0040A398) --------------------------------------------------------
int __cdecl cdvdman_speedctl(u32 spindlctrl, int dvdflag, u32 maxlsn)
{
	u32 maxlsn_chk; // $v0

	switch ( spindlctrl )
	{
		case 0u:
			return dvdflag ? 2 : 4;
		case 1u:
			if ( !dvdflag )
			{
				return 133;
			}
			if ( g_cdvdman_minver_10700 )
			{
				return 131;
			}
			maxlsn_chk = 0x128000;
			if ( g_cdvdman_istruct.m_opo_or_para )
			{
				maxlsn -= ( maxlsn >= (u32)g_cdvdman_istruct.m_layer_1_lsn ) ? g_cdvdman_istruct.m_layer_1_lsn : 0;
				maxlsn_chk = 0x165000;
			}
			if ( maxlsn >= maxlsn_chk )
			{
				VERBOSE_KPRINTF(1, "Kprob Spd D lsn= %d\n", maxlsn);
				return 130;
			}
			return 133;
		case 2u:
		case 0xEu:
			return 1;
		case 3u:
			return 2;
		case 4u:
			return dvdflag ? 2 : 131;
		case 5u:
			return dvdflag ? 3 : 4;
		case 0xAu:
			return 64;
		case 0xCu:
			return dvdflag ? 4 : 2;
		case 0xFu:
			return 130;
		case 0x10u:
			return dvdflag ? 130 : 131;
		case 0x11u:
			return dvdflag ? 130 : 132;
		case 0x12u:
			return dvdflag ? 1 : 131;
		case 0x14u:
			return dvdflag ? 3 : 5;
		default:
			return dvdflag ? 131 : 133;
	}
}

//----- (0040A4F8) --------------------------------------------------------
int __cdecl cdvdman_isdvd()
{
	// The following call to sceCdGetDiskType was inlined
	switch ( sceCdGetDiskType() )
	{
		case 16:
		case 17:
		case 18:
		case 19:
			g_cdvdman_istruct.m_tray_is_open = 1;
			return 0;
		case 20:
			g_cdvdman_istruct.m_tray_is_open = 1;
			return 1;
		case 252:
		case 254:
			g_cdvdman_istruct.m_tray_is_open = 1;
			return 1;
		case 253:
			g_cdvdman_istruct.m_tray_is_open = 1;
			return 0;
		default:
			return 0;
	}	
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (0040A5A8) --------------------------------------------------------
int __cdecl sceCdRead0_Rty(u32 lsn, u32 nsec, void *buf, const sceCdRMode *mode, int ncmd, int dintrsec, void *func)
{
	DMA3PARAM b18; // [sp+18h] [-28h] BYREF
	char ndata[11]; // [sp+30h] [-10h] BYREF

	g_cdvdman_readbuf = buf;
	VERBOSE_KPRINTF(1, "sceCdRead0_Rty Lsn:%d nsec:%d dintrnsec %d func %08x\n", lsn, nsec, dintrsec, func);
	*(_DWORD *)ndata = lsn;
	*(_DWORD *)&ndata[4] = nsec;
	ndata[8] = mode->trycount;
	ndata[9] = cdvdman_speedctl(mode->spindlctrl, cdvdman_isdvd(), lsn + nsec);
	b18.m_dma3_csectors = dintrsec;
	b18.m_dma3_callback = (int (__cdecl *)(void))func;
	b18.m_dma3_msectors = nsec;
	b18.m_dma3_maddress = buf;
	b18.m_dma3_blkcount = (!(_WORD)dintrsec) ? nsec : 1;
	if ( ncmd == 6 )
	{
		ndata[10] = mode->datapattern;
		switch ( mode->datapattern )
		{
			case 1:
				b18.m_dma3_blkwords = 6;
				b18.m_dma3_blkcount *= 97;
				b18.m_cdvdreg_howto = 134;
				break;
			case 2:
				b18.m_dma3_blkwords = 15;
				b18.m_dma3_blkcount *= 39;
				b18.m_cdvdreg_howto = 143;
				break;
			case 0:
			default:
				b18.m_dma3_blkwords = 32;
				b18.m_dma3_blkcount *= 16;
				b18.m_cdvdreg_howto = 128;
				break;
		}
		if ( cdvdman_send_ncmd(ncmd, ndata, 11, 1, &b18, 0) >= 0 )
		{
			return 1;
		}
	}
	if ( ncmd == 8 )
	{
		b18.m_dma3_blkwords = 12;
		b18.m_dma3_blkcount *= 43;
		b18.m_cdvdreg_howto = 140;
		ndata[10] = 0;
		if ( cdvdman_send_ncmd(ncmd, ndata, 11, 14, &b18, 0) >= 0 )
		{
			return 1;
		}
	}
	return 0;
}

//----- (0040A79C) --------------------------------------------------------
int __cdecl sceCdRead0(u32 lsn, u32 sectors, void *buffer, sceCdRMode *mode, int csec, void *callback)
{
	DMA3PARAM b18; // [sp+20h] [-30h] BYREF
	char ndata[11]; // [sp+38h] [-18h] BYREF
	u32 efbits[2]; // [sp+48h] [-8h] BYREF

	if ( PollEventFlag(g_ncmd_evid, 1u, 16, efbits) == -421 )
	{
		return 0;
	}
	VERBOSE_KPRINTF(1, "DVD/CD sceCdRead0 sec %d num %d spin %d trycnt %d dptn %d adr %08x\n", lsn, sectors, mode->spindlctrl, mode->trycount, mode->datapattern, buffer);
	g_cdvdman_readbuf = buffer;
	b18.m_dma3_csectors = ( csec && (sectors < (u32)csec) ) ? sectors : (u32)csec;
	b18.m_dma3_callback = (int (__cdecl *)(void))callback;
	b18.m_dma3_msectors = sectors;
	b18.m_dma3_blkcount = (!csec) ? sectors : 1;
	switch ( mode->datapattern )
	{
		case 1:
			b18.m_dma3_blkwords = 6;
			b18.m_dma3_blkcount *= 97;
			b18.m_cdvdreg_howto = 134;
			break;
		case 2:
			b18.m_dma3_blkwords = 15;
			b18.m_dma3_blkcount *= 39;
			b18.m_cdvdreg_howto = 143;
			break;
		case 0:
		default:
			b18.m_dma3_blkwords = 32;
			b18.m_dma3_blkcount *= 16;
			b18.m_cdvdreg_howto = 128;
			break;
	}
	// The following call to sceCdGetDiskType was inlined
	switch ( sceCdGetDiskType() )
	{
		case 16:
		case 17:
		case 18:
		case 19:
			if ( g_cdvdman_mmode != 1 && g_cdvdman_mmode != 255 )
			{
				vSetEventFlag(g_ncmd_evid, 1u);
				return 0;
			}
			g_cdvdman_istruct.m_dvd_flag = 0;
			break;
		case 20:
			if ( g_cdvdman_mmode != 2 && g_cdvdman_mmode != 255 )
			{
				vSetEventFlag(g_ncmd_evid, 1u);
				return 0;
			}
			g_cdvdman_istruct.m_dvd_flag = 1;
			break;
		default:
			vSetEventFlag(g_ncmd_evid, 1u);
			return 0;
	}
	g_cdvdman_istruct.m_read_mode = *mode;
	g_cdvdman_istruct.m_read_callback = callback;
	g_cdvdman_istruct.m_read_chunk = b18.m_dma3_csectors;
	g_cdvdman_istruct.m_read_lsn = lsn;
	g_cdvdman_istruct.m_read_sectors = sectors;
	*(_DWORD *)ndata = lsn;
	*(_DWORD *)&ndata[4] = sectors;
	ndata[8] = mode->trycount;
	ndata[9] = cdvdman_speedctl(mode->spindlctrl, g_cdvdman_istruct.m_dvd_flag, lsn + sectors);
	g_cdvdman_istruct.m_read_buf = buffer;
	ndata[10] = mode->datapattern;
	b18.m_dma3_maddress = buffer;
	VERBOSE_KPRINTF(1, "Read Command call\n");
	if ( cdvdman_send_ncmd(6, ndata, 11, 1, &b18, 0) < 0 )
	{
		vSetEventFlag(g_ncmd_evid, 1u);
		return 0;
	}
	vSetEventFlag(g_ncmd_evid, 1u);
	return 1;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (0040AA9C) --------------------------------------------------------
int __cdecl read_cdvd_cb(cdvdman_internal_struct_t *common)
{
	int sblock; // $s5
	int i; // $s2
	u32 cdreadlsn; // $s1
	int syncdec_res_1; // $s1
	sceCdlLOCCD cdrloc; // [sp+10h] [-8h] BYREF

	sblock = 0;
	for ( i = 0; i < common->m_dma3prm.m_dma3_csectors; i += 1 )
	{
		char syncdec_res_4; // $v1
		int errlsn; // $a1

		syncdec_res_4 = 0;
		if ( common->m_read2_flag == 3 )
		{
			sblock = 2340;
			cdrloc.minute = cdvdman_syncdec(
												common->m_dec_state,
												common->m_check_version,
												common->m_dec_shift,
												g_cdvdman_ptoc[(i * sblock)]);
			cdrloc.second = cdvdman_syncdec(
												common->m_dec_state,
												common->m_check_version,
												common->m_dec_shift,
												g_cdvdman_ptoc[(i * sblock) + 1]);
			cdrloc.sector = cdvdman_syncdec(
												common->m_dec_state,
												common->m_check_version,
												common->m_dec_shift,
												g_cdvdman_ptoc[(i * sblock) + 2]);
			cdreadlsn = sceCdPosToInt(&cdrloc);
		}
		else
		{
			sblock = 2064;
			syncdec_res_1 = (unsigned __int8)cdvdman_syncdec(
																				 common->m_dec_state,
																				 common->m_check_version,
																				 common->m_dec_shift,
																				 g_cdvdman_ptoc[(i * sblock) + 3]);
			syncdec_res_1 += (unsigned __int8)cdvdman_syncdec(
																					common->m_dec_state,
																					common->m_check_version,
																					common->m_dec_shift,
																					g_cdvdman_ptoc[(i * sblock) + 2]) << 8;
			syncdec_res_1 += (unsigned __int8)cdvdman_syncdec(
																					common->m_dec_state,
																					common->m_check_version,
																					common->m_dec_shift,
																					g_cdvdman_ptoc[(i * sblock) + 1]) << 16;
			syncdec_res_4 = cdvdman_syncdec(
												common->m_dec_state,
												common->m_check_version,
												common->m_dec_shift,
												g_cdvdman_ptoc[(i * 2064)]);
			if ( !common->m_cdvdman_dma3sec && !common->m_interupt_read_state )
			{
				common->m_interupt_read_state = (syncdec_res_4 & 0xC) | (( (syncdec_res_4 & 0xC) && i ) ? 0x80 : 0);
			}
			cdreadlsn = (syncdec_res_1 - 196608) + (( common->m_opo_or_para && ((unsigned int)(common->m_cdvdman_lsn + common->m_cdvdman_csec + i) >= common->m_layer_1_lsn && common->m_opo_or_para == 1) ) ? common->m_layer_1_lsn : 0);
		}
		errlsn = common->m_cdvdman_lsn + common->m_cdvdman_csec + common->m_cdvdman_dma3sec + i;
		if ( cdreadlsn != (u32)errlsn )
		{
			VERBOSE_KPRINTF(1, "Read_IOP Sector_ID error lsn= %d readlsn= %d layer= %d\n", errlsn, cdreadlsn, (syncdec_res_4 & 1));
			break;
		}
	}
	if ( i == common->m_dma3prm.m_dma3_csectors )
	{
		unsigned int size; // $s3

		size = 0;
		switch ( common->m_cdvdman_pattern )
		{
			case 0:
				size = 2048;
				break;
			case 1:
			default:
				size = 2328;
				break;
			case 2:
				cdvdman_memcpy(
					(char *)(common->m_cdvdman_rbuffer + 2340 * common->m_cdvdman_dma3sec),
					(const char *)g_cdvdman_ptoc,
					2340 * i);
				break;
		}
		if ( size )
		{
			for ( i = 0; i < common->m_dma3prm.m_dma3_csectors; i += 1 )
			{
				cdvdman_memcpy((char *)(common->m_cdvdman_rbuffer + (common->m_cdvdman_dma3sec + i) * size), (const char *)&g_cdvdman_ptoc[12 + (i * sblock)], size);
			}
		}
		g_cdvdman_readptr = common->m_cdvdman_csec + common->m_cdvdman_dma3sec;
	}
	else
	{
		++common->m_sync_error;
	}
	return 1;
}

//----- (0040AE20) --------------------------------------------------------
int __cdecl cdvdman_read(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int decflag, int shift, int ef1, int ef2)
{
	int read_res; // $v0
	int state; // [sp+18h] [-10h] BYREF
	int sc_result; // [sp+1Ch] [-Ch] BYREF
	int dvd; // [sp+20h] [-8h]

	dvd = cdvdman_isdvd();
	if ( dvd )
	{
		if ( !DvdDual_infochk() )
		{
			if ( ef1 )
			{
				vSetEventFlag(ef1, ef2);
			}
			return 0;
		}
		lsn = sceCdLsnDualChg(lsn);
	}
	else if ( mode->datapattern == 1 || (g_cdvdman_cd36key && !g_cdvdman_istruct.m_dec_state) )
	{
		int read0_res; // $s0

		if ( g_cdvdman_cd36key && !g_cdvdman_istruct.m_dec_state && mode->spindlctrl == 1 )
		{
			mode->spindlctrl = 0;
		}
		CpuSuspendIntr(&state);
		read0_res = sceCdRead0(lsn, sectors, buf, mode, 0, 0);
		if ( ef1 )
		{
			vSetEventFlag(ef1, ef2);
		}
		CpuResumeIntr(state);
		return read0_res;
	}
	CpuSuspendIntr(&state);
	if ( (sceCdDiskReady(8) & 0xC0) != 64 || g_cdvdman_istruct.m_read2_flag )
	{
		VERBOSE_KPRINTF(1, "sceCdRead: Double Booking error r2f= %d waf= %d\n", g_cdvdman_istruct.m_read2_flag, g_cdvdman_istruct.m_wait_flag);
		if ( ef1 )
		{
			vSetEventFlag(ef1, ef2);
		}
		CpuResumeIntr(state);
		return 0;
	}
	if ( decflag )
	{
		g_cdvdman_istruct.m_dec_shift = shift;
		g_cdvdman_istruct.m_dec_state = 1;
	}
	g_cdvdman_readbuf = buf;
	g_cdvdman_readptr = 0;
	g_cdvdman_istruct.m_cdvdman_lsn = lsn;
	g_cdvdman_istruct.m_cdvdman_csec = 0;
	g_cdvdman_istruct.m_cdvdman_nsec = sectors;
	g_cdvdman_istruct.m_cdvdman_rbuffer = (int)buf;
	g_cdvdman_istruct.m_cdvdman_pattern = dvd ? 0 : mode->datapattern;
	g_cdvdman_istruct.m_cdvdman_cdrmode.trycount = mode->trycount;
	g_cdvdman_istruct.m_cdvdman_cdrmode.spindlctrl = mode->spindlctrl;
	g_cdvdman_istruct.m_cdvdman_cdrmode.datapattern = dvd ? 0 : 2;
	g_cdvdman_istruct.m_read2_flag = dvd ? 1 : 3;
	g_cdvdman_istruct.m_sync_error = 0;
	g_cdvdman_istruct.m_interupt_read_state = 0;
	g_cdvdman_istruct.m_cdvdman_rsec = ( sectors >= 0x41 ) ? (( (lsn & 0xF) != 0 ) ? (16 - (lsn & 0xF)) : 64) : sectors;
	g_cdvdman_racb_to.hi = 0;
	g_cdvdman_racb_to.lo = 0x9000 * sceCdSC(0xFFFFFFF1, &sc_result);
	vSetAlarm(&g_cdvdman_racb_to, (unsigned int (__cdecl *)(void *))alarm_cb_read, &g_cdvdman_racb_to);
	read_res = (dvd ? sceCdRV : sceCdRead0)(lsn, g_cdvdman_istruct.m_cdvdman_rsec, g_cdvdman_ptoc, dvd ? mode : &g_cdvdman_istruct.m_cdvdman_cdrmode, 16, read_cdvd_cb);
	if ( !read_res )
	{
		g_cdvdman_istruct.m_last_error = -2;
		g_cdvdman_istruct.m_cdvdman_rsec = 0;
		g_cdvdman_istruct.m_read2_flag = 0;
		if ( g_cdvdman_istruct.m_dec_state )
		{
			g_cdvdman_istruct.m_dec_shift = 0;
			g_cdvdman_istruct.m_check_version = 0;
			g_cdvdman_istruct.m_dec_state = 0;
			sceCdDecSet(0, 0, 0);
		}
		vCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb_read, &g_cdvdman_racb_to);
	}
	if ( ef1 )
	{
		vSetEventFlag(ef1, ef2);
	}
	CpuResumeIntr(state);
	return !!read_res;
}

//----- (0040B1EC) --------------------------------------------------------
int __cdecl sceCdRE(unsigned int lsn, unsigned int sectors, void *buf, sceCdRMode *mode)
{
	return cdvdman_read(lsn, sectors, buf, mode, 0, 0, 0, 0);
}

//----- (0040B218) --------------------------------------------------------
int __cdecl sceCdRead(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode)
{
	iop_event_info_t efinfo; // [sp+20h] [-28h] BYREF
	int state; // [sp+40h] [-8h] BYREF

	// Unofficial: initialize to 0
	memset(&efinfo, 0, sizeof(efinfo));
	CpuSuspendIntr(&state);
	vReferEventFlagStatus(g_fio_fsv_evid, &efinfo);
	if ( (efinfo.currBits & 1) == 0 )
	{
		CpuResumeIntr(state);
		return 0;
	}
	vClearEventFlag(g_fio_fsv_evid, 0xFFFFFFFE);
	CpuResumeIntr(state);
	return cdvdman_read(lbn, sectors, buffer, mode, 0, 0, g_fio_fsv_evid, 1);
}

//----- (0040B2EC) --------------------------------------------------------
int __cdecl cdvdman_syncdec(int decflag, int decxor, int shift, u32 data)
{
	return decflag ? ((unsigned __int8)(((unsigned __int8)data << (shift % 8)) | ((unsigned __int8)data >> (8 - shift % 8))) ^ (unsigned __int8)decxor) : (unsigned __int8)data;
}

//----- (0040B338) --------------------------------------------------------
int __cdecl dummy_nullsub()
{
	return 0;
}

//----- (0040B340) --------------------------------------------------------
void __cdecl Read2intrCDVD(int read2_flag)
{
	iCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb_read, &g_cdvdman_racb_to);
	if ( g_cdvdman_istruct.m_last_error || g_cdvdman_retries >= 5 )
	{
		if ( !g_cdvdman_istruct.m_last_error )
		{
			g_cdvdman_istruct.m_last_error = -3;
		}
		g_cdvdman_istruct.m_read2_flag = 0;
		g_cdvdman_retries = 0;
		g_cdvdman_rtindex = 0;
		g_cdvdman_readptr = 0;
		if ( g_cdvdman_istruct.m_dec_state )
		{
			g_cdvdman_istruct.m_dec_shift = 0;
			g_cdvdman_istruct.m_check_version = 0;
			g_cdvdman_istruct.m_dec_state = 0;
		}
		g_cdvdman_istruct.m_interupt_read_state = 0;
	}
	else if ( !g_cdvdman_istruct.m_interupt_read_state || g_cdvdman_istruct.m_cdvdman_csec )
	{
		int sc_result[2]; // [sp+18h] [-8h] BYREF

		g_cdvdman_istruct.m_interupt_read_state = 0;
		if ( g_cdvdman_istruct.m_sync_error )
		{
			u32 lsn_tmp; // $a0

			if ( !g_cdvdman_rtindex )
			{
				g_cdvdman_rtindex = 3;
				++g_cdvdman_retries;
			}
			g_cdvdman_istruct.m_sync_error = 0;
			lsn_tmp = g_cdvdman_istruct.m_cdvdman_lsn + g_cdvdman_istruct.m_cdvdman_csec;
			if ( lsn_tmp >= 0x30 )
			{
				lsn_tmp -= 16 * (g_cdvdman_rtindex - 1);
			}
			else
			{
				lsn_tmp += 16 * (g_cdvdman_rtindex - 1);
			}
			if ( (( read2_flag == 3 ) ? sceCdRead0 : sceCdRV)(
										lsn_tmp,
										g_cdvdman_istruct.m_cdvdman_rsec,
										g_cdvdman_ptoc,
										&g_cdvdman_istruct.m_cdvdman_cdrmode,
										16,
										read_cdvd_cb) )
			{
				g_cdvdman_racb_to.hi = 0;
				g_cdvdman_racb_to.lo = 0x9000 * sceCdSC(0xFFFFFFF1, sc_result);
				iSetAlarm(&g_cdvdman_racb_to, (unsigned int (__cdecl *)(void *))alarm_cb_read, &g_cdvdman_racb_to);
			}
			else
			{
				VERBOSE_KPRINTF(1, "Retry Read Fatal Error\n");
				g_cdvdman_istruct.m_last_error = 19;
				g_cdvdman_istruct.m_read2_flag = 0;
				g_cdvdman_retries = 0;
				g_cdvdman_rtindex = 0;
				g_cdvdman_readptr = 0;
				if ( g_cdvdman_istruct.m_dec_state )
				{
					g_cdvdman_istruct.m_dec_shift = 0;
					g_cdvdman_istruct.m_check_version = 0;
					g_cdvdman_istruct.m_dec_state = 0;
				}
			}
			g_cdvdman_rtindex -= g_cdvdman_rtindex ? 1 : 0;
		}
		else
		{
			int cdsectorsz; // $v1

			g_cdvdman_retries = 0;
			switch ( g_cdvdman_istruct.m_cdvdman_pattern )
			{
				case 0:
					cdsectorsz = 2048;
					break;
				case 1:
				default:
					cdsectorsz = 2328;
					break;
				case 2:
					cdsectorsz = 2340;
					break;
			}
			g_cdvdman_istruct.m_cdvdman_rbuffer += cdsectorsz * g_cdvdman_istruct.m_cdvdman_rsec;
			g_cdvdman_istruct.m_cdvdman_csec += g_cdvdman_istruct.m_cdvdman_rsec;
			if ( (unsigned int)g_cdvdman_istruct.m_cdvdman_csec < (unsigned int)g_cdvdman_istruct.m_cdvdman_nsec )
			{
				g_cdvdman_istruct.m_cdvdman_rsec = ((unsigned int)(g_cdvdman_istruct.m_cdvdman_csec + 64) < (unsigned int)g_cdvdman_istruct.m_cdvdman_nsec) ? 64 : (g_cdvdman_istruct.m_cdvdman_nsec - g_cdvdman_istruct.m_cdvdman_csec);
				if ( (( read2_flag == 3 ) ? sceCdRead0 : sceCdRV)(
											g_cdvdman_istruct.m_cdvdman_lsn + g_cdvdman_istruct.m_cdvdman_csec,
											g_cdvdman_istruct.m_cdvdman_rsec,
											g_cdvdman_ptoc,
											&g_cdvdman_istruct.m_cdvdman_cdrmode,
											16,
											read_cdvd_cb) )
				{
					g_cdvdman_racb_to.hi = 0;
					g_cdvdman_racb_to.lo = 0x9000 * sceCdSC(0xFFFFFFF1, sc_result);
					iSetAlarm(&g_cdvdman_racb_to, (unsigned int (__cdecl *)(void *))alarm_cb_read, &g_cdvdman_racb_to);
				}
				else
				{
					g_cdvdman_istruct.m_last_error = 19;
					g_cdvdman_istruct.m_read2_flag = 0;
					g_cdvdman_readptr = 0;
					if ( g_cdvdman_istruct.m_dec_state )
					{
						g_cdvdman_istruct.m_dec_shift = 0;
						g_cdvdman_istruct.m_check_version = 0;
						g_cdvdman_istruct.m_dec_state = 0;
					}
				}
			}
			else
			{
				g_cdvdman_istruct.m_read2_flag = 0;
				g_cdvdman_readptr = 0;
				if ( g_cdvdman_istruct.m_dec_state )
				{
					g_cdvdman_istruct.m_dec_shift = 0;
					g_cdvdman_istruct.m_check_version = 0;
					g_cdvdman_istruct.m_dec_state = 0;
				}
			}
		}
	}
	else
	{
		g_cdvdman_istruct.m_last_error = ((g_cdvdman_istruct.m_interupt_read_state & 0x80) != 0) ? -3 : 32;
		g_cdvdman_istruct.m_interupt_read_state = 0;
		VERBOSE_KPRINTF(1, "IPIerr emu Hit Dummy Err %02x\n", (unsigned __int8)g_cdvdman_istruct.m_last_error);
		g_cdvdman_istruct.m_read2_flag = 0;
		g_cdvdman_retries = 0;
		g_cdvdman_rtindex = 0;
		g_cdvdman_readptr = 0;
		if ( g_cdvdman_istruct.m_dec_state )
		{
			g_cdvdman_istruct.m_dec_shift = 0;
			g_cdvdman_istruct.m_check_version = 0;
			g_cdvdman_istruct.m_dec_state = 0;
		}
	}
}

//----- (0040B89C) --------------------------------------------------------
int __cdecl sceCdReadChain(sceCdRChain *tag, sceCdRMode *mode)
{
	(void)tag;
	(void)mode;

	return 0;
}

//----- (0040B8A4) --------------------------------------------------------
int __cdecl cdvdman_readfull(u32 lsn, u32 sectors, void *buf, const sceCdRMode *mode, int flag)
{
	DMA3PARAM b18; // [sp+18h] [-28h] BYREF
	char ndata[11]; // [sp+30h] [-10h] BYREF

	VERBOSE_KPRINTF(1, "lsn:%d nsec:%d buf:% cmdmode:%d\n", lsn, sectors, buf, flag);
	g_cdvdman_readbuf = buf;
	b18.m_dma3_csectors = 0;
	b18.m_dma3_msectors = 0;
	b18.m_dma3_callback = 0;
	b18.m_dma3_blkcount = sectors;
	switch ( mode->datapattern )
	{
		case 1:
			b18.m_dma3_blkwords = 8;
			b18.m_dma3_blkcount *= 74;
			b18.m_cdvdreg_howto = 136;
			break;
		case 2:
			b18.m_dma3_blkwords = 12;
			b18.m_dma3_blkcount *= 51;
			b18.m_cdvdreg_howto = 140;
			break;
		case 0:
		default:
			b18.m_dma3_blkwords = 12;
			b18.m_dma3_blkcount *= 49;
			b18.m_cdvdreg_howto = 140;
			break;
	}
	// The following call to sceCdGetDiskType() was inlined
	switch ( sceCdGetDiskType() )
	{
		case 17:
		case 19:
		case 253:
			break;
		default:
			return 0;
	}
	if ( g_cdvdman_mmode != 1 && g_cdvdman_mmode != 255 )
	{
		return 0;
	}
	*(_DWORD *)ndata = lsn;
	*(_DWORD *)&ndata[4] = sectors;
	ndata[8] = mode->trycount;
	ndata[9] = cdvdman_speedctl(mode->spindlctrl, 0, lsn + sectors);
	b18.m_dma3_maddress = buf;
	ndata[10] = mode->datapattern;
	return cdvdman_send_ncmd((!flag) ? 7 : 14, ndata, 11, (!flag) ? 2 : 12, &b18, 1) >= 0;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (0040BA94) --------------------------------------------------------
int __cdecl sceCdReadCDDA(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode)
{
	return cdvdman_readfull(lbn, sectors, buffer, mode, 0);
}

//----- (0040BAB4) --------------------------------------------------------
int __cdecl sceCdRV(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int arg5, void *cb)
{
	DMA3PARAM b18; // [sp+18h] [-30h] BYREF
	char ndata[11]; // [sp+30h] [-18h] BYREF
	u32 efbits[2]; // [sp+40h] [-8h] BYREF

	// The following call to sceCdGetDiskType was inlined
	if ( sceCdGetDiskType() != 20 || (g_cdvdman_mmode != 2 && g_cdvdman_mmode != 255) || (PollEventFlag(g_ncmd_evid, 1u, 16, efbits) == -421) )
	{
		return 0;
	}
	VERBOSE_KPRINTF(1, "RV read: sec %d num %d spin %d trycnt %d  addr %08x\n", lsn, sectors, mode->spindlctrl, mode->trycount, buf);
	g_cdvdman_readbuf = buf;
	g_cdvdman_istruct.m_dvd_flag = cdvdman_isdvd();
	g_cdvdman_istruct.m_read_mode = *mode;
	g_cdvdman_istruct.m_read_lsn = lsn;
	g_cdvdman_istruct.m_read_sectors = sectors;
	*(_DWORD *)ndata = lsn;
	*(_DWORD *)&ndata[4] = sectors;
	ndata[8] = mode->trycount;
	ndata[9] = cdvdman_speedctl(mode->spindlctrl, 1, lsn + sectors);
	ndata[10] = 0;
	b18.m_dma3_csectors = ( arg5 && (sectors < (u32)arg5) ) ? sectors : (u32)arg5;
	g_cdvdman_istruct.m_read_chunk = b18.m_dma3_csectors;
	b18.m_cdvdreg_howto = 140;
	b18.m_dma3_blkwords = 12;
	g_cdvdman_istruct.m_read_buf = buf;
	b18.m_dma3_blkcount = (!arg5) ? sectors : 1;
	b18.m_dma3_blkcount *= 43;
	b18.m_dma3_msectors = sectors;
	b18.m_dma3_callback = (int (__cdecl *)(void))cb;
	g_cdvdman_istruct.m_read_callback = cb;
	b18.m_dma3_maddress = buf;
	if ( cdvdman_send_ncmd(8, ndata, 11, 14, &b18, 0) < 0 )
	{
		vSetEventFlag(g_ncmd_evid, 1u);
		return 0;
	}
	vSetEventFlag(g_ncmd_evid, 1u);
	return 1;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (0040BCE8) --------------------------------------------------------
int __cdecl sceCdSeek(u32 lbn)
{
	u32 ndata; // [sp+20h] [+8h] BYREF

	ndata = lbn;
	if ( cdvdman_isdvd() )
	{
		if ( DvdDual_infochk() == 0 )
		{
			return 0;
		}
		ndata = sceCdLsnDualChg(ndata);
	}
	return cdvdman_send_ncmd(5, &ndata, 4, 4, 0, 1) >= 0;
}

//----- (0040BD58) --------------------------------------------------------
int __cdecl sceCdRI(u8 *buffer, u32 *result)
{
	int command; // $v0
	u8 rdata[9]; // [sp+18h] [-10h] BYREF

	command = set_prev_command(18, 0, 0, (char *)rdata, 9, 1);
	*result = rdata[0];
	*(_DWORD *)buffer = *(_DWORD *)&rdata[1];
	*((_DWORD *)buffer + 1) = *(_DWORD *)&rdata[5];
	return command;
}

//----- (0040BDD4) --------------------------------------------------------
int __cdecl sceCdRM(char *buffer, u32 *status)
{
	int command; // $v0
	int cmd_tmp2; // $v0
	u8 rdata[9]; // [sp+18h] [-20h] BYREF
	char wdata[8]; // [sp+28h] [-10h] BYREF
	u32 efbits[2]; // [sp+30h] [-8h] BYREF

	*status = 0;
	if ( sceCdGetMVersion(rdata, status) != 1 || (unsigned int)(rdata[3] | (rdata[2] << 8) | (rdata[1] << 16)) <= 0x104FFu )
	{
		strcpy(buffer, "M_NAME_UNKNOWN");
		buffer[15] = 0;
		*status |= 0x40u;
		return 1;
	}
	if ( PollEventFlag(g_scmd_evid, 1u, 16, efbits) == -421 )
	{
		return 0;
	}
	DelayThread(2000);
	wdata[0] = 0;
	command = set_prev_command(0x17, wdata, 1, (char *)rdata, 9, 0);
	*status = rdata[0];
	*(_DWORD *)buffer = *(_DWORD *)&rdata[1];
	*((_DWORD *)buffer + 1) = *(_DWORD *)&rdata[5];
	DelayThread(2000);
	wdata[0] = 8;
	cmd_tmp2 = set_prev_command(0x17, wdata, 1, (char *)rdata, 9, 0);
	*status |= rdata[0];
	*((_DWORD *)buffer + 2) = *(_DWORD *)&rdata[1];
	*((_DWORD *)buffer + 3) = *(_DWORD *)&rdata[5];
	vSetEventFlag(g_scmd_evid, 1u);
	return command ? (cmd_tmp2 != 0) : 0;
}

//----- (0040BFC0) --------------------------------------------------------
int __cdecl sceCdGetMVersion(u8 *buffer, u32 *status)
{
	int command; // $v0
	char rdata[4]; // [sp+18h] [-10h] BYREF
	char wdata[8]; // [sp+20h] [-8h] BYREF

	wdata[0] = 0;
	command = set_prev_command(3, wdata, 1, rdata, 4, 1);
	*status = rdata[0] & 0x80;
	VERBOSE_KPRINTF(1, "MV 0x%02x,0x%02x,0x%02x,0x%02x\n", (unsigned __int8)rdata[0], (unsigned __int8)rdata[1], (unsigned __int8)rdata[2], (unsigned __int8)rdata[3]);
	rdata[0] &= ~0x80u;
	*(_DWORD *)buffer = *(_DWORD *)rdata;
	return command;
}
// 40BFC0: using guessed type char wdata[8];

//----- (0040C07C) --------------------------------------------------------
int __fastcall cdvdman_scmd_sender_03_48(u8 *buf, u32 *status)
{
	int retval; // $v0
	char rdata[16]; // [sp+18h] [-18h] BYREF
	char wdata[8]; // [sp+28h] [-8h] BYREF

	if ( g_cdvdman_minver_50000 )
	{
		return 0;
	}
	wdata[0] = 48;
	wdata[1] = 2;
	retval = set_prev_command(3, wdata, 2, rdata, 2, 1);
	*status = (unsigned __int8)rdata[0];
	*buf = rdata[1];
	return retval;
}

//----- (0040C108) --------------------------------------------------------
int __cdecl sceCdMmode(int media)
{
	g_cdvdman_mmode = media;
	return 1;
}

//----- (0040C118) --------------------------------------------------------
int __cdecl sceCdCancelPOffRdy(u32 *result)
{
	char wdata[8]; // [sp+18h] [-8h] BYREF

	memset(wdata, 0, sizeof(wdata));
	*result = 0;
	return g_cdvdman_minver_20400 ? set_prev_command(27, wdata, 0, (char *)result, 1, 1) : 1;
	
}
// 40C118: using guessed type char wdata[8];

//----- (0040C164) --------------------------------------------------------
unsigned int __fastcall alarm_cb_poff(cdvdman_internal_struct_t *s)
{
	s->m_power_flag = 0;
	return 0;
}

//----- (0040C170) --------------------------------------------------------
int __cdecl sceCdPowerOff(u32 *result)
{
	int command; // $s1

	*result = 0;
	VERBOSE_KPRINTF(1, "sceCdPowerOff Call\n");
	if ( !g_cdvdman_minver_x_model_15 )
	{
		while ( (sceCdStatus() & 1) != 0 )
		{
			u32 trayreq[2]; // [sp+18h] [-8h] BYREF

			sceCdTrayReq(1, trayreq);
			vDelayThread(250000);
		}
	}
	command = set_prev_command(0xF, 0, 0, (char *)result, 1, 1);
	if ( !command )
	{
		g_cdvdman_istruct.m_power_flag = 0;
		return 0;
	}
	KPRINTF("PowerOff Start...\n");
	g_cdvdman_istruct.m_power_flag = 1;
	g_cdvdman_poff_to.hi = 0;
	g_cdvdman_poff_to.lo = 0xAFC8000;
	vSetAlarm(&g_cdvdman_poff_to, (unsigned int (__cdecl *)(void *))alarm_cb_poff, &g_cdvdman_istruct);
	return command;
}
// 4114C0: using guessed type iop_sys_clock_t g_cdvdman_poff_to;

//----- (0040C290) --------------------------------------------------------
int __cdecl sceCdCtrlADout(int mode, u32 *status)
{
	char wdata[4]; // [sp+20h] [+8h] BYREF

	*(_DWORD *)wdata = mode;
	*status = 0;
	DelayThread(2000);
	VERBOSE_KPRINTF(1, "Audio Digital Out: Set param %d\n", *(_DWORD *)wdata);
	return set_prev_command(20, wdata, 1, (char *)status, 1, 1);
}

//----- (0040C308) --------------------------------------------------------
int __cdecl sceCdReadClock(sceCdCLOCK *clock)
{
	int retval; // $v0

	retval = set_prev_command(8, 0, 0, (char *)clock, 8, 1);
	clock->pad = 0;
	clock->month &= 0x7F;
	if ( retval && !clock->stat )
	{
		*(_DWORD *)&g_cdvdman_clock.stat = *(_DWORD *)&clock->stat;
		*(_DWORD *)&g_cdvdman_clock.pad = *(_DWORD *)&clock->pad;
		g_cdvdman_clk_flg = 1;
	}
	else if ( g_cdvdman_clk_flg )
	{
		*(_DWORD *)&clock->stat = *(_DWORD *)&g_cdvdman_clock.stat;
		*(_DWORD *)&clock->pad = *(_DWORD *)&g_cdvdman_clock.pad;
	}
	else
	{
		clock->month = 3;
		clock->day = 4;
		clock->hour = 5;
		clock->minute = 6;
		clock->year = 0;
		clock->second = 7;
	}
	return retval;
}

//----- (0040C424) --------------------------------------------------------
int __cdecl sceCdRC(sceCdCLOCK *clock)
{
	return set_prev_command(8, 0, 0, (char *)clock, 8, 1);
}

//----- (0040C460) --------------------------------------------------------
int __cdecl sceCdTrayReq(int param, u32 *traychk)
{
	char wdata; // [sp+18h] [-8h] BYREF
	char rdata[7]; // [sp+19h] [-7h] BYREF

	if ( param == 2 )
	{
		*traychk = cdvdman_mediactl(1);
		VERBOSE_KPRINTF(1, "Tray Req test = %d\n", *traychk);
		return 1;
	}
	if ( g_cdvdman_minver_x_model_15 && param == 1 )
	{
		return 1;
	}
	wdata = param;
	g_cdvdman_iocache = 0;
	if ( set_prev_command(6, &wdata, 1, rdata, 1, 1) != 0 && !rdata[0] )
	{
		vDelayThread(11000);
		return 1;
	}
	return 0;
	
}
// 40C460: using guessed type char rdata[7];

//----- (0040C534) --------------------------------------------------------
int __fastcall cdvdman_scmd_sender_3B(int arg1)
{
	char wdata; // [sp+18h] [-8h] BYREF
	char rdata[7]; // [sp+19h] [-7h] BYREF

	if ( g_cdvdman_minver_x_model_15 && arg1 == 1 )
	{
		return 1;
	}
	wdata = arg1;
	g_cdvdman_iocache = 0;
	if ( set_prev_command(59, &wdata, 1, rdata, 1, 1) != 0 && !rdata[0] )
	{
		vDelayThread(11000);
		return 1;
	}
	return 0;
}
// 40C534: using guessed type char rdata[7];

//----- (0040C5B8) --------------------------------------------------------
int __cdecl sceCdReadDiskID(unsigned int *id)
{
	sceCdRMode rmode; // [sp+18h] [-810h] BYREF
	char sectbuf[2048]; // [sp+20h] [-808h] BYREF
	u32 efbits[2]; // [sp+820h] [-8h] BYREF

	*((_BYTE *)id + 4) = 0;
	*((_BYTE *)id + 3) = 0;
	*((_BYTE *)id + 2) = 0;
	*((_BYTE *)id + 1) = 0;
	*(_BYTE *)id = 0;
	switch ( sceCdGetDiskType() )
	{
		case 18:
		case 19:
		case 20:
			break;
		default:
			return 0;
	}
	rmode.spindlctrl = 18;
	rmode.datapattern = 0;
	rmode.trycount = 0;
	sceCdRead0(0x4Bu, 1u, sectbuf, &rmode, 0, 0);
	sceCdSync(3);
	if ( cdvdman_ncmd_sender_0C(0, 0, 0x4Bu) == 0 )
	{
		return 0;
	}
	sceCdSync(3);
	if ( g_cdvdman_istruct.m_last_error )
	{
		return 0;
	}
	WaitEventFlag(g_scmd_evid, 1u, 0, efbits);
	if ( (dev5_regs.m_dev5_reg_038 & 4) == 0 )
	{
		vSetEventFlag(g_scmd_evid, 1u);
		return 0;
	}
	*(_BYTE *)id = dev5_regs.m_dev5_reg_030 ^ dev5_regs.m_dev5_reg_039;
	*((_BYTE *)id + 1) = dev5_regs.m_dev5_reg_031 ^ dev5_regs.m_dev5_reg_039;
	*((_BYTE *)id + 2) = dev5_regs.m_dev5_reg_032 ^ dev5_regs.m_dev5_reg_039;
	*((_BYTE *)id + 3) = dev5_regs.m_dev5_reg_033 ^ dev5_regs.m_dev5_reg_039;
	*((_BYTE *)id + 4) = dev5_regs.m_dev5_reg_034 ^ dev5_regs.m_dev5_reg_039;
	vSetEventFlag(g_scmd_evid, 1u);
	return 1;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;
// 40C5B8: using guessed type char sectbuf[2048];

//----- (0040C764) --------------------------------------------------------
int __cdecl sceCdDoesUniqueKeyExist(u32 *status)
{
	int disktype_tmp; // $s0
	vu8 dev5_reg_038; // $s0
	sceCdRMode rmode[2]; // [sp+18h] [-18h] BYREF
	char ndata[7]; // [sp+20h] [-10h] BYREF
	int state; // [sp+28h] [-8h] BYREF
	u32 efbits; // [sp+2Ch] [-4h] BYREF

	disktype_tmp = 0;
	if ( !g_cdvdman_istruct.m_cd_inited )
	{
		*status = 20;
		return 0;
	}
	*status = 0;
	switch ( sceCdGetDiskType() )
	{
		case 18:
		case 19:
			disktype_tmp = 1;
			break;
		case 20:
			break;
		default:
			*status = 20;
			return 0;
	}
	CpuSuspendIntr(&state);
	if ( g_cdvdman_istruct.m_stream_flag || g_cdvdman_istruct.m_read2_flag )
	{
		*status = 253;
		CpuResumeIntr(state);
		return 0;
	}
	if ( (sceCdStatus() & 2) != 0 )
	{
		CpuResumeIntr(state);
	}
	else
	{
		dev5_regs.m_dev5_reg_007 = 1;
		CpuResumeIntr(state);
		sceCdSync(3);
	}
	CpuSuspendIntr(&state);
	rmode[0].spindlctrl = 18;
	rmode[0].datapattern = 0;
	rmode[0].trycount = 0;
	if ( disktype_tmp )
	{
		unsigned int i; // $s0

		for ( i = 0; i < 0x14; i += 1 )
		{
			sceCdRead0(75 + (16 * i), 0x10u, g_cdvdman_ptoc, rmode, 0, 0);
			CpuResumeIntr(state);
			sceCdSync(3);
			CpuSuspendIntr(&state);
		}
		CpuResumeIntr(state);
	}
	else
	{
		sceCdRead0(0x4Bu, 1u, g_cdvdman_ptoc, rmode, 0, 0);
		CpuResumeIntr(state);
		sceCdSync(3);
	}
	WaitEventFlag(g_scmd_evid, 1u, 0, &efbits);
	CpuSuspendIntr(&state);
	if ( g_cdvdman_istruct.m_stream_flag || g_cdvdman_istruct.m_read2_flag )
	{
		*status = 253;
		CpuResumeIntr(state);
		vSetEventFlag(g_scmd_evid, 1u);
		return 0;
	}
	strcpy(&ndata[3], "K");
	ndata[6] = 0;
	ndata[5] = 0;
	ndata[2] = 0;
	ndata[1] = 0;
	ndata[0] = 0;
	if ( cdvdman_send_ncmd(12, ndata, 7, 0, 0, 1) < 0 )
	{
		*status = 253;
		CpuResumeIntr(state);
		vSetEventFlag(g_scmd_evid, 1u);
		return 0;
	}
	CpuResumeIntr(state);
	sceCdSync(3);
	if ( g_cdvdman_istruct.m_last_error )
	{
		*status = (unsigned __int8)g_cdvdman_istruct.m_last_error;
		vSetEventFlag(g_scmd_evid, 1u);
		return 0;
	}
	dev5_reg_038 = dev5_regs.m_dev5_reg_038;
	vSetEventFlag(g_scmd_evid, 1u);
	return (dev5_reg_038 & 5) == 5;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (0040CAE0) --------------------------------------------------------
int __cdecl cdvdman_ncmd_sender_0C(int arg1, u32 arg2, u32 arg3)
{
	char ndata[7]; // [sp+18h] [-8h] BYREF

	ndata[1] = arg2 != 0;
	ndata[0] = arg1;
	ndata[2] = arg2 >> 8 != 0;
	*(_DWORD *)&ndata[3] = arg1 ? 0 : arg3;
	return cdvdman_send_ncmd(12, ndata, 7, 0, 0, 1) >= 0;
}

//----- (0040CB64) --------------------------------------------------------
int __cdecl sceCdDecSet(u8 enable_xor, u8 enable_shift, u8 shiftval)
{
	g_cdvdman_cd36key = enable_shift | shiftval;
	dev5_regs.m_dev5_reg_03A = (16 * (shiftval & 7)) | (enable_xor ? 2 : 0) | (enable_shift ? 1 : 0);
	return 1;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

#if 0
//----- (0040CBC4) --------------------------------------------------------
void *__cdecl AllocSysMemory(int mode, int size, void *ptr)
{
	void *result; // $v0

	return result;
}
// 40CBC4: variable 'result' is possibly undefined

//----- (0040CBCC) --------------------------------------------------------
int __cdecl FreeSysMemory(void *ptr)
{
	int result; // $v0

	return result;
}
// 40CBCC: variable 'result' is possibly undefined

//----- (0040CBD4) --------------------------------------------------------
int Kprintf(const char *format, ...)
{
	int result; // $v0

	return result;
}
// 40CBD4: variable 'result' is possibly undefined

//----- (0040CBF8) --------------------------------------------------------
int __cdecl RegisterLibraryEntries(struct irx_export_table *exports)
{
	int result; // $v0

	return result;
}
// 40CBF8: variable 'result' is possibly undefined

//----- (0040CC00) --------------------------------------------------------
int *__cdecl QueryBootMode(int mode)
{
	int *result; // $v0

	return result;
}
// 40CC00: variable 'result' is possibly undefined

//----- (0040CC08) --------------------------------------------------------
int __cdecl SetRebootTimeLibraryHandlingMode(struct irx_export_table *exports, int mode)
{
	int result; // $v0

	return result;
}
// 40CC08: variable 'result' is possibly undefined

//----- (0040CC2C) --------------------------------------------------------
int __cdecl RegisterIntrHandler(int irq, int mode, int (__cdecl *handler)(void *), void *arg)
{
	int result; // $v0

	return result;
}
// 40CC2C: variable 'result' is possibly undefined

//----- (0040CC34) --------------------------------------------------------
int __cdecl ReleaseIntrHandler(int irq)
{
	int result; // $v0

	return result;
}
// 40CC34: variable 'result' is possibly undefined

//----- (0040CC3C) --------------------------------------------------------
int __cdecl EnableIntr(int irq)
{
	int result; // $v0

	return result;
}
// 40CC3C: variable 'result' is possibly undefined

//----- (0040CC44) --------------------------------------------------------
int __cdecl DisableIntr(int irq, int *res)
{
	int result; // $v0

	return result;
}
// 40CC44: variable 'result' is possibly undefined

//----- (0040CC4C) --------------------------------------------------------
int __cdecl CpuSuspendIntr(int *state)
{
	int result; // $v0

	return result;
}
// 40CC4C: variable 'result' is possibly undefined

//----- (0040CC54) --------------------------------------------------------
int __cdecl CpuResumeIntr(int state)
{
	int result; // $v0

	return result;
}
// 40CC54: variable 'result' is possibly undefined

//----- (0040CC5C) --------------------------------------------------------
int QueryIntrContext(void)
{
	int result; // $v0

	return result;
}
// 40CC5C: variable 'result' is possibly undefined

//----- (0040CC80) --------------------------------------------------------
int printf(const char *format, ...)
{
	int result; // $v0

	return result;
}
// 40CC80: variable 'result' is possibly undefined

//----- (0040CCA4) --------------------------------------------------------
void __cdecl dmac_ch_set_madr(u32 channel, u32 val)
{
	;
}

//----- (0040CCAC) --------------------------------------------------------
u32 __cdecl dmac_ch_get_madr(u32 channel)
{
	u32 result; // $v0

	return result;
}
// 40CCAC: variable 'result' is possibly undefined

//----- (0040CCB4) --------------------------------------------------------
void __cdecl dmac_ch_set_bcr(u32 channel, u32 val)
{
	;
}

//----- (0040CCBC) --------------------------------------------------------
void __cdecl dmac_ch_set_chcr(u32 channel, u32 val)
{
	;
}

//----- (0040CCC4) --------------------------------------------------------
u32 __cdecl dmac_ch_get_chcr(u32 channel)
{
	u32 result; // $v0

	return result;
}
// 40CCC4: variable 'result' is possibly undefined

//----- (0040CCCC) --------------------------------------------------------
void __cdecl dmac_set_dpcr(u32 val)
{
	;
}

//----- (0040CCD4) --------------------------------------------------------
u32 dmac_get_dpcr(void)
{
	u32 result; // $v0

	return result;
}
// 40CCD4: variable 'result' is possibly undefined

//----- (0040CCF8) --------------------------------------------------------
int GetThreadId(void)
{
	int result; // $v0

	return result;
}
// 40CCF8: variable 'result' is possibly undefined

//----- (0040CD00) --------------------------------------------------------
int __cdecl DelayThread(int usec)
{
	int result; // $v0

	return result;
}
// 40CD00: variable 'result' is possibly undefined

//----- (0040CD08) --------------------------------------------------------
int __cdecl GetSystemTime(iop_sys_clock_t *sys_clock)
{
	int result; // $v0

	return result;
}
// 40CD08: variable 'result' is possibly undefined

//----- (0040CD10) --------------------------------------------------------
int __cdecl SetAlarm(iop_sys_clock_t *sys_clock, unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	int result; // $v0

	return result;
}
// 40CD10: variable 'result' is possibly undefined

//----- (0040CD18) --------------------------------------------------------
int __cdecl iSetAlarm(iop_sys_clock_t *sys_clock, unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	int result; // $v0

	return result;
}
// 40CD18: variable 'result' is possibly undefined

//----- (0040CD20) --------------------------------------------------------
int __cdecl CancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	int result; // $v0

	return result;
}
// 40CD20: variable 'result' is possibly undefined

//----- (0040CD28) --------------------------------------------------------
int __cdecl iCancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	int result; // $v0

	return result;
}
// 40CD28: variable 'result' is possibly undefined

//----- (0040CD4C) --------------------------------------------------------
int __cdecl CreateEventFlag(iop_event_t *event)
{
	int result; // $v0

	return result;
}
// 40CD4C: variable 'result' is possibly undefined

//----- (0040CD54) --------------------------------------------------------
int __cdecl DeleteEventFlag(int ef)
{
	int result; // $v0

	return result;
}
// 40CD54: variable 'result' is possibly undefined

//----- (0040CD5C) --------------------------------------------------------
int __cdecl SetEventFlag(int ef, u32 bits)
{
	int result; // $v0

	return result;
}
// 40CD5C: variable 'result' is possibly undefined

//----- (0040CD64) --------------------------------------------------------
int __cdecl iSetEventFlag(int ef, u32 bits)
{
	int result; // $v0

	return result;
}
// 40CD64: variable 'result' is possibly undefined

//----- (0040CD6C) --------------------------------------------------------
int __cdecl ClearEventFlag(int ef, u32 bits)
{
	int result; // $v0

	return result;
}
// 40CD6C: variable 'result' is possibly undefined

//----- (0040CD74) --------------------------------------------------------
int __cdecl iClearEventFlag(int ef, u32 bits)
{
	int result; // $v0

	return result;
}
// 40CD74: variable 'result' is possibly undefined

//----- (0040CD7C) --------------------------------------------------------
int __cdecl WaitEventFlag(int ef, u32 bits, int mode, u32 *resbits)
{
	int result; // $v0

	return result;
}
// 40CD7C: variable 'result' is possibly undefined

//----- (0040CD84) --------------------------------------------------------
int __cdecl PollEventFlag(int ef, u32 bits, int mode, u32 *resbits)
{
	int result; // $v0

	return result;
}
// 40CD84: variable 'result' is possibly undefined

//----- (0040CD8C) --------------------------------------------------------
int __cdecl ReferEventFlagStatus(int ef, iop_event_info_t *info)
{
	int result; // $v0

	return result;
}
// 40CD8C: variable 'result' is possibly undefined

//----- (0040CD94) --------------------------------------------------------
int __cdecl iReferEventFlagStatus(int ef, iop_event_info_t *info)
{
	int result; // $v0

	return result;
}
// 40CD94: variable 'result' is possibly undefined

//----- (0040CDB8) --------------------------------------------------------
int __cdecl SignalSema(int semid)
{
	int result; // $v0

	return result;
}
// 40CDB8: variable 'result' is possibly undefined

//----- (0040CDC0) --------------------------------------------------------
int __cdecl iSignalSema(int semid)
{
	int result; // $v0

	return result;
}
// 40CDC0: variable 'result' is possibly undefined

//----- (0040CDE4) --------------------------------------------------------
void *__cdecl memcpy(void *dest, const void *src, size_t size)
{
	void *result; // $v0

	return result;
}
// 40CDE4: variable 'result' is possibly undefined

//----- (0040CDEC) --------------------------------------------------------
void *__cdecl memset(void *ptr, int c, size_t size)
{
	void *result; // $v0

	return result;
}
// 40CDEC: variable 'result' is possibly undefined

//----- (0040CDF4) --------------------------------------------------------
int sprintf(char *str, const char *format, ...)
{
	int result; // $v0

	return result;
}
// 40CDF4: variable 'result' is possibly undefined

//----- (0040CDFC) --------------------------------------------------------
char *__cdecl strcat(char *dest, const char *src)
{
	char *result; // $v0

	return result;
}
// 40CDFC: variable 'result' is possibly undefined

//----- (0040CE04) --------------------------------------------------------
int __cdecl strcmp(const char *p, const char *q)
{
	int result; // $v0

	return result;
}
// 40CE04: variable 'result' is possibly undefined

//----- (0040CE0C) --------------------------------------------------------
size_t __cdecl strlen(const char *s)
{
	size_t result; // $v0

	return result;
}
// 40CE0C: variable 'result' is possibly undefined

//----- (0040CE14) --------------------------------------------------------
int __cdecl strncmp(const char *p, const char *q, size_t size)
{
	int result; // $v0

	return result;
}
// 40CE14: variable 'result' is possibly undefined

//----- (0040CE1C) --------------------------------------------------------
char *__cdecl strncpy(char *dest, const char *src, size_t size)
{
	char *result; // $v0

	return result;
}
// 40CE1C: variable 'result' is possibly undefined

//----- (0040CE24) --------------------------------------------------------
int __cdecl strtol(const char *s, char **endptr, int base)
{
	int result; // $v0

	return result;
}
// 40CE24: variable 'result' is possibly undefined

//----- (0040CE48) --------------------------------------------------------
int open(const char *name, int flags, ...)
{
	int result; // $v0

	return result;
}
// 40CE48: variable 'result' is possibly undefined

//----- (0040CE50) --------------------------------------------------------
int __cdecl close(int fd)
{
	int result; // $v0

	return result;
}
// 40CE50: variable 'result' is possibly undefined

//----- (0040CE58) --------------------------------------------------------
int __cdecl read(int fd, void *ptr, int size)
{
	int result; // $v0

	return result;
}
// 40CE58: variable 'result' is possibly undefined

//----- (0040CE60) --------------------------------------------------------
int __cdecl write(int fd, void *ptr, int size)
{
	int result; // $v0

	return result;
}
// 40CE60: variable 'result' is possibly undefined

//----- (0040CE68) --------------------------------------------------------
int __cdecl lseek(int fd, int pos, int mode)
{
	int result; // $v0

	return result;
}
// 40CE68: variable 'result' is possibly undefined

//----- (0040CE70) --------------------------------------------------------
int __cdecl remove(const char *name)
{
	int result; // $v0

	return result;
}
// 40CE70: variable 'result' is possibly undefined

//----- (0040CE78) --------------------------------------------------------
int __cdecl AddDrv(iop_device_t *device)
{
	int result; // $v0

	return result;
}
// 40CE78: variable 'result' is possibly undefined

//----- (0040CE80) --------------------------------------------------------
int __cdecl DelDrv(const char *name)
{
	int result; // $v0

	return result;
}
// 40CE80: variable 'result' is possibly undefined

//----- (0040CE88) --------------------------------------------------------
int __cdecl devctl(const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen)
{
	int result; // $v0

	return result;
}
// 40CE88: variable 'result' is possibly undefined

//----- (0040CE90) --------------------------------------------------------
int __cdecl ioctl2(int fd, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen)
{
	int result; // $v0

	return result;
}
// 40CE90: variable 'result' is possibly undefined
#endif

// nfuncs=214 queued=214 decompiled=214 lumina nreq=0 worse=0 better=0
// ALL OK, 214 function(s) have been successfully decompiled
