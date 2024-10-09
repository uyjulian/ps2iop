
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
int __cdecl cdvdman_cache_invalidate(CDVDMAN_FILEDATA *filedata1, int index);
int __cdecl cdvdman_invcaches();
int __fastcall cdrom_internal_cache_read(iop_file_t *f, int nbytes);
int __fastcall cdrom_internal_write_cache(iop_file_t *f, unsigned int nbytes);
int __cdecl cdvdfile_cache_read(iop_file_t *f, void *buf, int nbyte);
int __cdecl cdvdfile_cache_fill_read(iop_file_t *f, void *buf, int nbytes);
int __cdecl cdrom_open(iop_file_t *f, const char *name, int mode, int arg4);
int __cdecl cdrom_close(iop_file_t *f);
int __fastcall cdrom_internal_read(iop_file_t *f, char *addr, int nbytes);
int __fastcall cdrom_stream_read(iop_file_t *f, char *bbuf, int nbytes);
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
int __fastcall unused_40BA90(unsigned int *, int);
unsigned int __fastcall cdvdman_memcpy(char *dst, const char *src, unsigned int n);
void __cdecl cdvdman_1();
int __cdecl cdvdman_retonly();
int __fastcall hex_dump(u8 *addr_start, int length);
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
u32 __cdecl cdvdman_l1start(u8 *toc);
int __cdecl DvdDual_infochk();
u32 __cdecl sceCdLsnDualChg(u32 lsn);
int __cdecl sceCdReadDvdDualInfo(int *on_dual, unsigned int *layer1_start);
int __cdecl sceCdSC(int code, int *param);
void __cdecl nullsub_2();
int __cdecl cdvdman_init();
int __cdecl sceCdInit(int init_mode);
int __cdecl set_prev_command(int cmd, const char *sdata, int sdlen, char *rdata, int rdlen, int check_sef);
void __cdecl cdvdman_write_scmd(cdvdman_internal_struct_t *s);
int __cdecl cdvdman_send_scmd2(int cmd, const void *sdata, int sdlen, void *rdata, int rdlen, int check_sef);
int __cdecl sceCdApplySCmd(u8 cmdNum, const void *inBuff, u16 inBuffSize, void *outBuff);
int __cdecl sceCdApplySCmd2(u8 cmdNum, const void *inBuff, unsigned long int inBuffSize, void *outBuff);
int __fastcall cdvdman_125(char cmd, char *wdata, int wdlen, char *rdata);
int sceCdBreak(void);
int __fastcall cd_ncmd_timeout_callback(iop_sys_clock_t *sys_clock);
int __fastcall intrh_dma_3(cdvdman_internal_struct_t *s, int cbbits);
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
int __cdecl sceCdRead0_Rty(u32 lsn, u32 nsec, void *buf, sceCdRMode *mode, int ncmd, int dintrsec, void *func);
int __cdecl sceCdRead0(u32 lsn, u32 sectors, void *buffer, sceCdRMode *mode, int csec, void *callback);
int __cdecl read_cdvd_cb(cdvdman_internal_struct_t *common);
int __cdecl cdvdman_read(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int decflag, int shift, int ef1, int ef2);
int __cdecl sceCdRE(unsigned int lsn, unsigned int sectors, void *buf, sceCdRMode *mode);
int __cdecl sceCdRead(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode);
int __cdecl cdvdman_syncdec(int decflag, int decxor, int shift, u32 data);
int __cdecl dummy_nullsub();
void __cdecl Read2intrCDVD(int read2_flag);
int __cdecl sceCdReadChain(sceCdRChain *tag, sceCdRMode *mode);
int __cdecl cdvdman_readfull(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int flag);
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
int __cdecl sceCdCtrlADout(int arg1, u32 *status);
int __cdecl sceCdReadClock(sceCdCLOCK *clock);
int __cdecl sceCdRC(sceCdCLOCK *clock);
int __cdecl sceCdTrayReq(int param, u32 *traychk);
int __fastcall cdvdman_scmd_sender_3B(int arg1);
int __cdecl sceCdReadDiskID(unsigned int *id);
int __cdecl cdvdman_179(u32 *status);
int __cdecl cdvdman_ncmd_sender_0C(int arg1, u32 arg2, u32 arg3);
int __cdecl sceCdDecSet(u8 arg1, u8 arg2, u8 shift);
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

char aHost0[7] = "host0:"; // weak
int cdvdman_cache_sector_size_count = 1;
int cdvdman_srchspd = 0;
int cdvdman_spinctl = -1;
int cdvdman_spinnom = -1;
int cdvdman_trycnt = -1;
int cdvdman_iocache = 0;
int cdvdman_lcn_offset = 0;
int cdvdman_numbytes_offset = 0;
int cdvdman_strmerr = 0;
static iop_device_ops_t cdvdman_cddev_ops =
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
iop_device_t cdvdman_cddev = { "cdrom", 268435472u, 1u, "CD-ROM ", &cdvdman_cddev_ops };
int cdvdman_sync_to = 15000;
int TimeOut2 = 5000;
iop_sys_clock_t readid_systemtime = { 0u, 0u }; // weak
int cdvdman_verbose = 0;
CDVDMAN_PATHTBL_T *cdvdman_pathtbl = NULL;
int cache_count = 0;
int cache_table = 0;
int cdvdman_pathtblsize = 0;
int cache_path_size = 0;
int cache_path_fd = -1;
int cdvdman_fs_cdsec = 0;
int cdvdman_fs_layer = -1;
int cdvdman_fs_cache = 0;
int cdvdman_fs_base2 = 0;
int cdvdman_clk_flg = 0;
int cdvdman_cd36key = 0;
int cdvdman_strm_id = 0;
int cdvdman_mmode = 0;
int cdvdman_last_cmdfunc = 0;
int cdvdman_minver_10700 = 0;
int cdvdman_minver_20200 = 0;
int cdvdman_minver_20400 = 0;
int cdvdman_minver_20800 = 0;
int cdvdman_emudvd9 = 0;
int cdvdman_minver_50000 = 0;
int cdvdman_minver_50200 = 0;
int cdvdman_minver_50400 = 0;
int cdvdman_minver_50600 = 0;
int cdvdman_minver_60000 = 0;
int cdvdman_minver_60200 = 0;
int cdvdman_minver_x_model_15 = 0;
char *masterdisc_header = "PlayStation Master Disc"; // weak
char cdvdman_ncmd = '\x06'; // weak
int cdvdman_chmedia = 0;
int cdvdman_chflags[4] = { 1, 1, 1, 1 };
int cdvdman_rtindex = 0;
int cdvdman_retries = 0;
u8 *cdvdman_ptoc;
int scmd_evid; // idb
void *cdvdman_temp_buffer_ptr;
int sfile_evid; // idb
int ncmd_evid; // idb
int fio_fsv_evid; // idb
int cdvdman_intr_efid; // idb
sceCdCBFunc cdvdman_user_cb;
void *cdvdman_poffarg;
void (__cdecl *cdvdman_cdstm0cb)(int);
sceCdCLOCK cdvdman_clock;
int (__cdecl *cdvdman_poff_cb)(void *userdata);
void (__cdecl *cdvdman_cdstm1cb)(int);
int cdvdman_cmdfunc;
CDVDMAN_FILEDATA cdvdman_handles[16];
char cdvdman_sfname[1024];
CDVDMAN_FILETBL_ENTRY_T cdvdman_filetbl[64];
CD_DIR_ENTRY cdvdman_dirtbl[128];
int cdvdman_pathtblflag;
char cdvdman_fs_rbuf[2048];
char cdvdman_end_fs_rbuf[24];
int cdvdman_readptr;
iop_sys_clock_t cdvdman_racb_to;
iop_sys_clock_t cdvdman_ncmd_to;
void *cdvdman_readbuf;
iop_sys_clock_t cdvdman_poff_to; // weak
char cdvdman_fsvrbuf[42128];
cdvdman_internal_struct_t cdvdman_istruct;
dev5_regs_t dev5_regs; // weak


//----- (00400000) --------------------------------------------------------
int __cdecl _start(int argc, char **argv)
{
	bool condtmp; // dc
	int result; // $v0

	condtmp = RegisterLibraryEntries(&_exp_cdvdman) != 0;
	result = 1;
	if ( !condtmp )
	{
		DelDrv("cdrom");
		if ( AddDrv(&cdvdman_cddev) )
		{
			cdrom_deinit();
			return 1;
		}
		else
		{
			cdvdman_ptoc = (u8 *)&cdvdman_fsvrbuf[2340];
			cdvdman_temp_buffer_ptr = cdvdman_fsvrbuf;
			cdvdman_init();
#if 0
			// FIXME workaround
			SetRebootTimeLibraryHandlingMode(&_exp_cdvdman, 2);
#endif
			return 0;
		}
	}
	return result;
}

//----- (004000A0) --------------------------------------------------------
void *sceGetFsvRbuf(void)
{
	return cdvdman_fsvrbuf;
}

//----- (004000B0) --------------------------------------------------------
int __cdecl cdrom_init(iop_device_t *dev)
{
	int handlei1; // $v1
	int handlei2; // $v0
	iop_event_t event; // [sp+10h] [-18h] BYREF
	int cd_sc_tmp; // [sp+20h] [-8h] BYREF

	printf("cdvdman Init\n");
	cdvdman_istruct.wait_flag = 1;
	cdvdman_istruct.scmd_flag = 1;
	cdvdman_istruct.read2_flag = 0;
	cdvdman_istruct.stream_flag = 0;
	cdvdman_istruct.last_error = 0;
	cdvdman_istruct.layer_1_lsn = 0;
	cdvdman_istruct.use_toc = 0;
	cdvdman_istruct.read_to = 0;
	cdvdman_istruct.power_flag = 0;
	cdvdman_istruct.current_dvd = 0;
	cdvdman_istruct.dual_layer_emulation = 0;
	cdvdman_istruct.dec_state = 0;
	cdvdman_istruct.check_version = 0;
	cdvdman_istruct.dec_shift = 0;
	cdvdman_istruct.opo_or_para = -1;
	cdvdman_istruct.no_dec_flag = 0;
	cdvdman_istruct.cd_inited = 0;
	cdvdman_istruct.tray_is_open = 0;
	cdvdman_strm_id = 0;
	cdvdman_spinctl = -1;
	event.attr = 2;
	event.bits = 0;
	event.option = 0;
	cdvdman_intr_efid = CreateEventFlag(&event);
	scmd_evid = CreateEventFlag(&event);
	ncmd_evid = CreateEventFlag(&event);
	sfile_evid = CreateEventFlag(&event);
	fio_fsv_evid = CreateEventFlag(&event);
	ClearEventFlag(cdvdman_intr_efid, 0xFFFFFFFB);
	ClearEventFlag(cdvdman_intr_efid, 0xFFFFFFEF);
	SetEventFlag(cdvdman_intr_efid, 0x29u);
	SetEventFlag(ncmd_evid, 1u);
	SetEventFlag(scmd_evid, 1u);
	SetEventFlag(sfile_evid, 1u);
	SetEventFlag(fio_fsv_evid, 1u);
	cdvdman_spinnom = -1;
	cdvdman_trycnt = -1;
	sceCdSC(0xFFFFFFF3, &cd_sc_tmp);
	handlei1 = 15;
	handlei2 = 15;
	do
	{
		cdvdman_handles[handlei2].fd_flags = 0;
		--handlei1;
		--handlei2;
	}
	while ( handlei1 >= 0 );
	return 0;
}

//----- (00400254) --------------------------------------------------------
void __fastcall cdvdman_termcall(int with_stop)
{
	int i; // $s0
	vu8 dev5_reg_017; // $v0
	int oldstate; // [sp+10h] [-8h] BYREF

	i = 0;
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("CDVD:library Terminate Call %d\n", with_stop);
	}
	if ( !with_stop )
	{
		sceCdBreak();
		sceCdSync(0);
		if ( cdvdman_istruct.cd_inited )
		{
			cdvdman_ncmd_sender_06();
		}
		dev5_reg_017 = dev5_regs.dev5_reg_017;
		if ( (dev5_reg_017 & 0x80) != 0 )
		{
			do
			{
				if ( i > 49999 )
				{
					break;
				}
				DelayThread(100);
				++i;
			}
			while ( (dev5_regs.dev5_reg_017 & 0x80) != 0 );
		}
		sceCdDecSet(0, 0, 0);
		if ( (dmac_ch_get_chcr(3u) & 0x1000000) != 0 )
		{
			dev5_regs.dev5_reg_007 = 1;
		}
		dmac_ch_set_chcr(3u, 0);
		DisableIntr(35, &oldstate);
		ReleaseIntrHandler(35);
		DisableIntr(2, &oldstate);
		ReleaseIntrHandler(2);
	}
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00400390) --------------------------------------------------------
int __cdecl cdrom_deinit()
{
	int i1; // $v1
	int i2; // $v0

	i1 = 15;
	i2 = 15;
	do
	{
		cdvdman_handles[i2].fd_flags = 0;
		--i1;
		--i2;
	}
	while ( i1 >= 0 );
	DeleteEventFlag(fio_fsv_evid);
	DeleteEventFlag(cdvdman_intr_efid);
	DeleteEventFlag(ncmd_evid);
	DeleteEventFlag(scmd_evid);
	DeleteEventFlag(sfile_evid);
	return 0;
}

//----- (00400418) --------------------------------------------------------
int __cdecl cdvdman_devready()
{
	int i; // $s0
	int result; // $v0
	BOOL condtmp2; // $v0
	bool condtmp1; // dc

	for ( i = 0; ; ++i )
	{
		result = -5;
		if ( (dev5_regs.dev5_reg_00A & 1) != 0 )
		{
			cdvdman_iocache = 0;
			return result;
		}
		condtmp2 = i < 100;
		if ( (dev5_regs.dev5_reg_005 & 0xC0) == 64 )
		{
			condtmp2 = i < 100;
			if ( !cdvdman_istruct.read2_flag )
			{
				condtmp2 = i < 100;
				if ( !cdvdman_strm_id )
				{
					break;
				}
			}
		}
		condtmp1 = !condtmp2;
		result = -16;
		if ( condtmp1 )
		{
			return result;
		}
		DelayThread(10000);
	}
	return 1;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (004004E0) --------------------------------------------------------
int __cdecl cdvdman_l0check(int layer)
{
	return !layer
			&& (cdvdman_istruct.dual_layer_emulation || cdvdman_istruct.opo_or_para == 1 || cdvdman_istruct.opo_or_para == 2);
}

//----- (00400528) --------------------------------------------------------
void __cdecl cdvdman_iormode(sceCdRMode *rmode, int fmode, int layer)
{
	u8 trycnt_tmp; // $v0
	u8 spindlctrl_tmp; // $v0

	rmode->datapattern = 0;
	if ( cdvdman_trycnt == -1 )
	{
		trycnt_tmp = 16;
	}
	else
	{
		trycnt_tmp = cdvdman_trycnt;
	}
	rmode->trycount = trycnt_tmp;
	if ( cdvdman_l0check(layer) )
	{
		if ( cdvdman_spinnom == -1 )
		{
			if ( fmode == 2 || fmode == 20 )
			{
				rmode->spindlctrl = fmode;
			}
			else
			{
LABEL_14:
				rmode->spindlctrl = 0;
			}
			return;
		}
		if ( fmode != 2 && fmode != 20 )
		{
			rmode->spindlctrl = 0;
			return;
		}
	}
	else if ( cdvdman_spinnom == -1 )
	{
		switch ( fmode )
		{
			case 0:
				goto LABEL_14;
			case 1:
				spindlctrl_tmp = 1;
				goto LABEL_23;
			case 2:
				spindlctrl_tmp = 2;
				goto LABEL_23;
			case 3:
				spindlctrl_tmp = 3;
				goto LABEL_23;
			case 4:
				spindlctrl_tmp = 4;
				goto LABEL_23;
			case 5:
				spindlctrl_tmp = 5;
				goto LABEL_23;
			case 20:
				spindlctrl_tmp = 20;
				goto LABEL_23;
			default:
				spindlctrl_tmp = 1;
				goto LABEL_23;
		}
	}
	spindlctrl_tmp = cdvdman_spinnom;
LABEL_23:
	rmode->spindlctrl = spindlctrl_tmp;
}

//----- (00400658) --------------------------------------------------------
int __cdecl cdrom_dopen(iop_file_t *f, const char *dirname)
{
	int handle_ind1; // $v1
	int handle_ind2; // $a0
	CDVDMAN_FILEDATA *handle; // $s1
	int is_devready; // $s0
	size_t path_name_len; // $v1
	size_t path_name_ind; // $a0
	int unit; // $a1
	int file_lsn_tmp; // $v0
	int file_fsv_evid_tmp; // $a0
	int fd_layer_tmp; // $v1
	char path_name[128]; // [sp+10h] [-88h] BYREF
	u32 efbits[2]; // [sp+90h] [-8h] BYREF

	if ( cdvdman_verbose > 0 )
	{
		printf("fileIO DOPEN name= %s layer %d\n", dirname, f->unit);
	}
	WaitEventFlag(fio_fsv_evid, 1u, 16, efbits);
	handle_ind1 = 0;
	handle_ind2 = 0;
	do
	{
		if ( !cdvdman_handles[handle_ind2].fd_flags )
		{
			break;
		}
		++handle_ind1;
		++handle_ind2;
	}
	while ( handle_ind1 < 16 );
	if ( handle_ind1 == 16 )
	{
		SetEventFlag(fio_fsv_evid, 1u);
		return -24;
	}
	f->privdata = (void *)handle_ind1;
	handle = &cdvdman_handles[handle_ind1];
	is_devready = cdvdman_devready();
	if ( is_devready < 0 )
	{
		SetEventFlag(fio_fsv_evid, 1u);
		return is_devready;
	}
	strncpy(path_name, dirname, 128);
	if ( !strcmp(path_name, ".") )
	{
		strcpy(path_name, "\\.");
	}
	path_name_len = strlen(path_name);
	path_name_ind = 0;
	if ( path_name_len >= 2 )
	{
		path_name_ind = path_name_len - 2;
	}
	if ( strcmp(&path_name[path_name_ind], "\\.") )
	{
		strcat(path_name, "\\.");
	}
	if ( f->unit < 2u )
	{
		handle->file_lsn = 0;
		unit = f->unit;
		cdvdman_srchspd = 0;
		file_lsn_tmp = sceCdSearchDir(path_name, unit);
		if ( file_lsn_tmp >= 0 )
		{
			file_fsv_evid_tmp = fio_fsv_evid;
			handle->file_lsn = file_lsn_tmp;
			fd_layer_tmp = f->unit;
			handle->read_pos = 0;
			handle->filemode = 0;
			handle->fd_flags = 1;
			handle->fd_layer = fd_layer_tmp;
			SetEventFlag(file_fsv_evid_tmp, 1u);
			return 0;
		}
		printf("open fail directory %s\n", path_name);
	}
	else
	{
		printf("open fail name %s\n", path_name);
	}
	SetEventFlag(fio_fsv_evid, 1u);
	return -2;
}

//----- (00400878) --------------------------------------------------------
void __cdecl cdvdman_fillstat(void *dummy, iox_stat_t *buf, CDVDMAN_FILETBL_ENTRY_T *fp)
{
	int offi; // $a0
	iox_stat_t *buftmp; // $v1
	u8 datetmp; // $v0
	int mode_tmp; // $v1

	offi = 0;
	buf->attr = 0;
	buf->private_5 = 0;
	buf->private_4 = 0;
	buf->private_3 = 0;
	buf->private_2 = 0;
	buf->private_1 = 0;
	buf->private_0 = 0;
	buf->hisize = 0;
	buftmp = buf;
	do
	{
		datetmp = fp->file_struct.date[offi++];
		buftmp->mtime[0] = datetmp;
		buftmp->atime[0] = datetmp;
		buftmp->ctime[0] = datetmp;
		buftmp = (iox_stat_t *)((char *)buf + offi);
	}
	while ( offi < 8 );                           // This is a memset 0
	buf->size = fp->file_struct.size;
	mode_tmp = 0x2000;
	if ( (fp->file_properties & 2) != 0 )
	{
		mode_tmp = 4169;
	}
	buf->mode = mode_tmp | 0x124;
}

//----- (004008F4) --------------------------------------------------------
int __cdecl cdvdman_cdfname(char *filename)
{
	size_t filename_len; // $v0
	char *filename_posptr; // $a0
	int result; // $v0

	filename_len = strlen(filename);
	filename_posptr = &filename[filename_len];
	if ( filename_len < 3 )
	{
LABEL_4:
		strcat(filename, ";1");
		return 1;
	}
	if ( *(filename_posptr - 2) != 59 )
	{
		result = 0;
		if ( *(filename_posptr - 1) == 49 )
		{
			return result;
		}
		goto LABEL_4;
	}
	return 0;
}

//----- (00400964) --------------------------------------------------------
int __cdecl cdrom_getstat(iop_file_t *f, const char *name, iox_stat_t *buf)
{
	int devready_tmp; // $s0
	int unit; // $a2
	CDVDMAN_FILETBL_ENTRY_T filetble; // [sp+10h] [-B0h] BYREF
	char filename[128]; // [sp+38h] [-88h] BYREF
	u32 efbits[2]; // [sp+B8h] [-8h] BYREF

	if ( cdvdman_verbose > 0 )
	{
		printf("fileIO GETSTAT name= %s layer= %d\n", name, f->unit);
	}
	WaitEventFlag(fio_fsv_evid, 1u, 16, efbits);
	devready_tmp = cdvdman_devready();
	if ( devready_tmp >= 0 )
	{
		strncpy(filename, name, 128);
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
		unit = f->unit;
		cdvdman_srchspd = 0;
		if ( sceCdLayerSearchFile(&filetble.file_struct, filename, unit)
			|| cdvdman_cdfname(filename) && sceCdLayerSearchFile(&filetble.file_struct, filename, f->unit) )
		{
			cdvdman_fillstat(filename, buf, &filetble);
			SetEventFlag(fio_fsv_evid, 1u);
			return 1;
		}
		else
		{
			printf("open fail name %s\n", name);
			SetEventFlag(fio_fsv_evid, 1u);
			return -2;
		}
	}
	else
	{
		SetEventFlag(fio_fsv_evid, 1u);
		return devready_tmp;
	}
}
// 400964: using guessed type sceCdlFILE filetble;

//----- (00400B28) --------------------------------------------------------
int __cdecl cdrom_dread(iop_file_t *f, iox_dirent_t *buf)
{
	int devready_tmp; // $s1
	CDVDMAN_FILEDATA *filedata; // $s0
	int file_lsn; // $a1
	int read_pos; // $a2
	int fd_layer; // $a3
	int Dir; // $v0
	CDVDMAN_FILETBL_ENTRY_T fileinfo; // [sp+10h] [-30h] BYREF
	u32 efbits[2]; // [sp+38h] [-8h] BYREF

	if ( cdvdman_verbose > 0 )
	{
		printf("fileIO DREAD\n");
	}
	WaitEventFlag(fio_fsv_evid, 1u, 16, efbits);
	devready_tmp = cdvdman_devready();
	if ( devready_tmp >= 0 )
	{
		filedata = &cdvdman_handles[(int)f->privdata];
		file_lsn = filedata->file_lsn;
		read_pos = filedata->read_pos;
		fd_layer = filedata->fd_layer;
		cdvdman_srchspd = 0;
		Dir = sceCdReadDir(&fileinfo.file_struct, file_lsn, read_pos, fd_layer);
		devready_tmp = Dir;
		if ( Dir < 0 )
		{
			SetEventFlag(fio_fsv_evid, 1u);
			return -2;
		}
		if ( Dir )
		{
			++filedata->read_pos;
			devready_tmp = strlen(fileinfo.file_struct.name);
		}
		strncpy(buf->name, fileinfo.file_struct.name, 256);
		cdvdman_fillstat(fileinfo.file_struct.name, &buf->stat, &fileinfo);
	}
	SetEventFlag(fio_fsv_evid, 1u);
	return devready_tmp;
}

//----- (00400C5C) --------------------------------------------------------
int __cdecl cdvd_odcinit(CDVDMAN_FILEDATA *fh, int open_or_close, int id)
{
	u32 file_size; // $v0
	int cache_remove_result; // $s5
	int cache_fd1; // $s1
	int rbsize_tmp; // $a1
	u8 *rcvbuf_tmp; // $v0
	int result; // $v0
	int cache_fd2; // $s4
	u32 file_size_sectors; // $a0
	int file_size_band_7; // $v0
	u32 file_size_bsr_3; // $s7
	unsigned int file_size_bsr_6; // $v1
	unsigned int file_size_bsr_17; // $fp
	u32 rcvbufi; // $s0
	bool condtmp; // dc
	int is_pfs_res; // $v0
	int cache_fd3; // $a0
	int i; // $s0
	_BYTE *tmp_ptr; // $v0
	unsigned int ioctl_arg3; // $v0
	int ioctl_arg2; // $s2
	int sector_ind1; // $s0
	int cache_fd4; // $a0
	signed int ioctl_arg4; // $s2
	signed int sector_ind2; // $s0
	int cache_fd5; // $a0
	int verbose_tmp; // $v1
	int cache_file_fd; // $a0
	int cache_close_result; // $v0
	void *buf; // [sp+10h] [-218h]
	char cache_filename[512]; // [sp+20h] [-208h] BYREF
	int state; // [sp+220h] [-8h] BYREF
	unsigned int ioctl_arg; // [sp+224h] [-4h] BYREF

	buf = (void *)fh->file_lsn;
	file_size = fh->file_size;
	cdvdman_iocache = 0;
	sprintf(cache_filename, "%sCache_%d_%d_%d_%d", aHost0, fh->fd_layer, (int)(uiptr)buf, (int)file_size, id);
	cache_remove_result = 0;
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("Cachefile:%s Open_or_Close:%d\n", cache_filename, open_or_close);
		cache_remove_result = 0;
	}
	cache_fd1 = 0;
	if ( !open_or_close )
	{
		goto LABEL_39;
	}
	CpuSuspendIntr(&state);
	rbsize_tmp = 2048;
	if ( cdvdman_cache_sector_size_count )
	{
		rbsize_tmp = cdvdman_cache_sector_size_count << 11;
	}
	fh->fd_rbsize = rbsize_tmp;
	rcvbuf_tmp = (u8 *)AllocSysMemory(1, rbsize_tmp, 0);
	fh->fd_rcvbuf = rcvbuf_tmp;
	if ( !rcvbuf_tmp )
	{
		if ( cdvdman_verbose > 0 )
		{
			Kprintf("Rcvbuf MemAlloc Fail\n");
		}
		CpuResumeIntr(state);
		return -12;
	}
	CpuResumeIntr(state);
	fh->cache_file_fd = -1;
	cache_fd1 = open(cache_filename, 1539, 511);
	cache_fd2 = cache_fd1;
	if ( cache_fd1 < 0 )
	{
		goto LABEL_39;
	}
	file_size_sectors = fh->file_size >> 11;
	file_size_band_7 = file_size_sectors & 7;
	if ( (fh->file_size & 0x7FF) != 0 )
	{
		file_size_band_7 = ++file_size_sectors & 7;
	}
	file_size_bsr_3 = file_size_sectors >> 3;
	if ( file_size_band_7 )
	{
		++file_size_bsr_3;
	}
	file_size_bsr_6 = file_size_bsr_3 >> 3;
	if ( (file_size_bsr_3 & 7) != 0 )
	{
		++file_size_bsr_6;
	}
	file_size_bsr_17 = file_size_bsr_6 >> 11;
	if ( (file_size_bsr_6 & 0x7FF) != 0 )
	{
		++file_size_bsr_17;
	}
	rcvbufi = 0;
	condtmp = fh->fd_rbsize == 0;
	ioctl_arg = (file_size_bsr_17 + file_size_sectors + 8) << 11;
	if ( !condtmp )
	{
		do
		{
			fh->fd_rcvbuf[rcvbufi++] = 0;
		}
		while ( rcvbufi < fh->fd_rbsize );
	}
	is_pfs_res = strncmp(cache_filename, "pfs", 3);
	cache_fd3 = cache_fd1;
	if ( !is_pfs_res )
	{
		cache_fd1 = ioctl2(cache_fd1, 28673, &ioctl_arg, 4u, 0, 0);
		cache_fd3 = cache_fd2;
		if ( cache_fd1 < 0 )
		{
			goto LABEL_39;
		}
	}
	cache_fd1 = lseek(cache_fd3, 0, 0);
	i = 0;
	if ( cache_fd1 < 0 )
	{
		goto LABEL_39;
	}
	do
	{
		tmp_ptr = (char *)cdvdman_temp_buffer_ptr + i++;
		*tmp_ptr = 0;
	}
	while ( i <= 0x7FFF );
	ioctl_arg3 = ioctl_arg;
	ioctl_arg2 = ioctl_arg >> 15;
	sector_ind1 = 0;
	if ( ioctl_arg >> 15 )
	{
		cache_fd4 = cache_fd2;
		while ( 1 )
		{
			cache_fd1 = write(cache_fd4, cdvdman_temp_buffer_ptr, 0x8000);
			if ( cache_fd1 != 0x8000 )
			{
				goto LABEL_33;
			}
			++sector_ind1;
			cache_fd4 = cache_fd2;
			if ( sector_ind1 >= ioctl_arg2 )
			{
				ioctl_arg3 = ioctl_arg;
				break;
			}
		}
	}
	ioctl_arg4 = (ioctl_arg3 >> 11) - 16 * ioctl_arg2;
	sector_ind2 = 0;
	if ( ioctl_arg4 > 0 )
	{
		cache_fd5 = cache_fd2;
		while ( 1 )
		{
			cache_fd1 = write(cache_fd5, fh->fd_rcvbuf, 2048);
			if ( cache_fd1 != 2048 )
			{
				break;
			}
			++sector_ind2;
			cache_fd5 = cache_fd2;
			if ( sector_ind2 >= ioctl_arg4 )
			{
				goto LABEL_36;
			}
		}
LABEL_33:
		if ( cache_fd1 >= 0 )
		{
			cache_fd1 = -5;
		}
LABEL_39:
		cache_file_fd = fh->cache_file_fd;
		if ( cache_file_fd != -1 )
		{
			cache_close_result = close(cache_file_fd);
			cache_remove_result = cache_close_result;
			if ( cdvdman_verbose > 0 )
			{
				Kprintf("Cache File Close: %d\n", cache_close_result);
			}
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
				if ( cdvdman_verbose > 0 )
				{
					Kprintf("Cache File %s remove: %d\n", cache_filename, cache_remove_result);
				}
			}
		}
		fh->cache_file_fd = -1;
		fh->max_cluster = 0;
		fh->cluster_cur = -1;
		fh->sector_count_total = 0;
		CpuSuspendIntr(&state);
		FreeSysMemory(fh->fd_rcvbuf);
		CpuResumeIntr(state);
		fh->fd_rcvbuf = 0;
		if ( cache_fd1 < 0 && cdvdman_verbose > 0 )
		{
			Kprintf("cdvd_odcinit Open  Error %d\n", cache_fd1);
		}
		if ( cache_remove_result < 0 && cdvdman_verbose > 0 )
		{
			Kprintf("cdvd_odcinit Close Error %d\n", cache_remove_result);
		}
		result = cache_fd1;
		if ( !open_or_close )
		{
			return cache_remove_result;
		}
		return result;
	}
LABEL_36:
	verbose_tmp = cdvdman_verbose;
	fh->sector_count_total = file_size_bsr_17 << 11;
	fh->cache_file_fd = cache_fd2;
	fh->max_cluster = (void *)file_size_bsr_3;
	fh->cluster_cur = -1;
	if ( verbose_tmp > 0 )
	{
		Kprintf("Cache File Maked\n");
	}
	return 0;
}
// 400F58: conditional instruction was optimized away because $s1.4>=0

//----- (0040111C) --------------------------------------------------------
int __cdecl cdvdman_cache_invalidate(CDVDMAN_FILEDATA *filedata1, int index)
{
	int result; // $v0
	u32 fd_rbsize; // $v0
	u32 i1; // $s0
	unsigned int sector_count_bsr_11; // $s3
	int fileio_res; // $s1
	CDVDMAN_FILEDATA *filedata2; // $a0
	unsigned int i2; // $s0

	if ( filedata1->cluster_cur == -1 )
	{
		return 0;
	}
	fd_rbsize = filedata1->fd_rbsize;
	i1 = 0;
	filedata1->cluster_cur = -1;
	if ( fd_rbsize )
	{
		do
		{
			filedata1->fd_rcvbuf[i1++] = 0;
		}
		while ( i1 < filedata1->fd_rbsize );
	}
	sector_count_bsr_11 = (unsigned int)filedata1->sector_count_total >> 11;
	fileio_res = lseek(filedata1->cache_file_fd, 0, 0);
	filedata2 = filedata1;
	if ( fileio_res >= 0 )
	{
		i2 = 0;
		if ( sector_count_bsr_11 )
		{
			while ( 1 )
			{
				fileio_res = write(filedata1->cache_file_fd, filedata1->fd_rcvbuf, 2048);
				++i2;
				if ( fileio_res < 0 )
				{
					break;
				}
				if ( i2 >= sector_count_bsr_11 )
				{
					goto LABEL_9;
				}
			}
		}
		else
		{
LABEL_9:
			result = fileio_res;
			if ( fileio_res >= 0 )
			{
				return result;
			}
		}
		filedata2 = filedata1;
	}
	filedata2->fd_flags &= ~4u;
	cdvd_odcinit(filedata2, 0, index);
	return fileio_res;
}

//----- (00401228) --------------------------------------------------------
int __cdecl cdvdman_invcaches()
{
	int i1; // $s0
	CDVDMAN_FILEDATA *fileinfo; // $s2
	int i2; // $s1

	i1 = 0;
	fileinfo = cdvdman_handles;
	i2 = 0;
	do
	{
		if ( (cdvdman_handles[i2].fd_flags & 4) != 0 )
		{
			cdvdman_cache_invalidate(fileinfo, i1);
		}
		++fileinfo;
		++i1;
		++i2;
	}
	while ( i1 < 16 );
	return 0;
}

//----- (004012A0) --------------------------------------------------------
int __fastcall cdrom_internal_cache_read(iop_file_t *f, int nbytes)
{
	CDVDMAN_FILEDATA *filedata; // $s0
	int result; // $v0
	unsigned int cluster_cur_tmp; // $v0
	u32 read_pos; // $v1
	s16 readpos_plus_nbytes; // $v0
	unsigned int readpos_plus_nbytes_bsr_14; // $s2
	int readpos_bsr_14; // $s3
	int cluster_cur; // $a1
	unsigned int readpos_bsr_14_2; // $a0
	int cluster_cur_tmp2; // $a0
	unsigned int max_cluster; // $v1
	int cluster_write_tmp2; // $s1
	unsigned int readpos_band; // $v0
	int cluster_cur_tmp3; // $a0
	unsigned int max_cluster_tmp3; // $v1
	int fd_rbsize; // $s1
	unsigned int readpos_minus_cluster_cur; // $v0
	int filedata_bw; // $v1
	u32 condtmp1; // $v0

	filedata = &cdvdman_handles[(int)f->privdata];
	if ( cdvdman_devready() < 0 )
	{
		cdvdman_iocache = 0;
		return -16;
	}
	if ( filedata->cluster_cur == -1 )
	{
		if ( (void *)(8 * filedata->fd_rbsize) < filedata->max_cluster )
		{
			cluster_cur_tmp = (filedata->read_pos >> 14) & 0xFFFFFFF8;
			filedata->cluster_cur = cluster_cur_tmp;
			if ( lseek(filedata->cache_file_fd, cluster_cur_tmp >> 3, 0) < 0
				|| read(filedata->cache_file_fd, filedata->fd_rcvbuf, filedata->fd_rbsize) < 0 )
			{
				filedata->cluster_cur = -1;
				return -5;
			}
		}
		else
		{
			filedata->cluster_cur = -2;
		}
	}
	read_pos = filedata->read_pos;
	readpos_plus_nbytes = read_pos + nbytes;
	readpos_plus_nbytes_bsr_14 = (read_pos + nbytes) >> 14;
	readpos_bsr_14 = read_pos >> 14;
	if ( (readpos_plus_nbytes & 0x3FFF) == 0 )
	{
		--readpos_plus_nbytes_bsr_14;
	}
	if ( cdvdman_verbose > 0 )
	{
		Kprintf(
			"max_claster %d meta_size_clst %d claster_cur %d\n",
			filedata->max_cluster,
			8 * filedata->fd_rbsize,
			filedata->cluster_cur);
	}
	cluster_cur = filedata->cluster_cur;
	readpos_bsr_14_2 = readpos_bsr_14;
	if ( cluster_cur < 0 )
	{
		cluster_cur = 0;
	}
	else if ( readpos_bsr_14 < (unsigned int)cluster_cur
				 || readpos_plus_nbytes_bsr_14 >= cluster_cur + 8 * filedata->fd_rbsize )
	{
		if ( lseek(filedata->cache_file_fd, cluster_cur >> 3, 0) < 0 )
		{
			goto LABEL_28;
		}
		cluster_cur_tmp2 = filedata->cluster_cur;
		max_cluster = (unsigned int)filedata->max_cluster;
		cluster_write_tmp2 = max_cluster >= cluster_cur_tmp2 + 8 * filedata->fd_rbsize ? filedata->fd_rbsize : (max_cluster - cluster_cur_tmp2 + 7) >> 3;
		if ( write(filedata->cache_file_fd, filedata->fd_rcvbuf, cluster_write_tmp2) != cluster_write_tmp2 )
		{
			goto LABEL_28;
		}
		readpos_band = readpos_bsr_14 & 0xFFFFFFF8;
		filedata->cluster_cur = readpos_bsr_14 & 0xFFFFFFF8;
		if ( readpos_bsr_14 < 0 )
		{
			readpos_band += 7;
		}
		if ( lseek(filedata->cache_file_fd, readpos_band >> 3, 0) < 0
			|| ((cluster_cur_tmp3 = filedata->cluster_cur,
					 max_cluster_tmp3 = (unsigned int)filedata->max_cluster,
					 max_cluster_tmp3 >= cluster_cur_tmp3 + 8 * filedata->fd_rbsize) ? (fd_rbsize = filedata->fd_rbsize) : (fd_rbsize = (max_cluster_tmp3 - cluster_cur_tmp3 + 7) >> 3),
					read(filedata->cache_file_fd, filedata->fd_rcvbuf, fd_rbsize) < 0) )
		{
LABEL_28:
			filedata->cluster_cur = -1;
			return -5;
		}
		cluster_cur = filedata->cluster_cur;
		readpos_bsr_14_2 = readpos_bsr_14;
	}
	result = readpos_plus_nbytes_bsr_14 >= readpos_bsr_14_2;
	if ( readpos_plus_nbytes_bsr_14 >= readpos_bsr_14_2 )
	{
		readpos_minus_cluster_cur = readpos_bsr_14_2 - cluster_cur;
		while ( 1 )
		{
			filedata_bw = ((int)filedata->fd_rcvbuf[readpos_minus_cluster_cur >> 3] >> (readpos_minus_cluster_cur & 7)) & 1;
			condtmp1 = readpos_plus_nbytes_bsr_14 < readpos_bsr_14_2;
			if ( !filedata_bw )
			{
				break;
			}
			readpos_minus_cluster_cur = ++readpos_bsr_14_2 - cluster_cur;
			if ( readpos_plus_nbytes_bsr_14 < readpos_bsr_14_2 )
			{
				condtmp1 = readpos_plus_nbytes_bsr_14 < readpos_bsr_14_2;
				return condtmp1 ^ 1;
			}
		}
		return condtmp1 ^ 1;
	}
	return result;
}

//----- (00401560) --------------------------------------------------------
int __fastcall cdrom_internal_write_cache(iop_file_t *f, unsigned int nbytes)
{
	bool condtmp; // dc
	int result; // $v0
	CDVDMAN_FILEDATA *filedata; // $s1
	u32 read_pos; // $a1
	u32 file_size; // $v1
	u32 read_pos_tmp; // $v1
	unsigned int cur; // $s7
	unsigned int rst; // $s3
	int cluster_cur; // $fp
	int write_ret; // $s0
	unsigned int rst_tmp; // $s2
	unsigned int i; // $s4
	int rstcalc1; // $s3
	unsigned int rstcalc2; // $s5
	char rst_unalign; // $s6
	unsigned int rst_calc3; // $a0
	int tray_open; // $s0
	int Error; // $a1
	sceCdRMode rmode[2]; // [sp+18h] [-8h] BYREF

	cdvdman_iocache = 0;
	condtmp = cdvdman_devready() < 0;
	result = -16;
	if ( condtmp )
	{
		return result;
	}
	filedata = &cdvdman_handles[(int)f->privdata];
	read_pos = filedata->read_pos;
	file_size = filedata->file_size;
	if ( file_size < read_pos + nbytes )
	{
		nbytes = file_size - read_pos;
	}
	result = 0;
	if ( !nbytes )
	{
		return result;
	}
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("_cdvdfile_cache_read %d<->%d\n", read_pos, read_pos + nbytes);
	}
	read_pos_tmp = filedata->read_pos;
	cur = (read_pos_tmp + nbytes) >> 14;
	rst = read_pos_tmp >> 14;
	if ( ((read_pos_tmp + nbytes) & 0x3FFF) == 0 )
	{
		--cur;
	}
	cluster_cur = 0;
	if ( filedata->cluster_cur >= 0 )
	{
		cluster_cur = filedata->cluster_cur;
	}
	cdvdman_iormode(rmode, filedata->filemode, f->unit);
	write_ret = 0;
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("cache_fill rst:%d<->%d cur:%d cnt:%d\n", rst, cur, filedata->read_pos, nbytes);
	}
	rst_tmp = rst;
	result = 0;
	if ( cur < rst )
	{
		return result;
	}
	for ( i = rst << 14; ; i += 0x4000 )
	{
		rstcalc1 = filedata->file_lsn + 8 * rst_tmp;
		if ( cdvdman_verbose > 0 )
		{
			Kprintf(
				"FIO Usr addr LSN:%d SEC:%d ADDR:%08x cpos= %d\n",
				filedata->file_lsn + 8 * rst_tmp,
				8,
				cdvdman_temp_buffer_ptr,
				i + filedata->sector_count_total);
		}
		rstcalc2 = (rst_tmp - cluster_cur) >> 3;
		rst_unalign = (rst_tmp - cluster_cur) & 7;
		rst_calc3 = rstcalc1;
		if ( (((int)filedata->fd_rcvbuf[rstcalc2] >> rst_unalign) & 1) != 0 )
		{
			goto LABEL_34;
		}
		tray_open = 0;
		while ( !sceCdRE(rst_calc3, 8u, cdvdman_temp_buffer_ptr, rmode) )
		{
			if ( (sceCdStatus() & 1) != 0 )
			{
				cdvdman_iocache = 0;
				tray_open = 1;
				break;
			}
			DelayThread(10000);
			rst_calc3 = rstcalc1;
		}
		sceCdSync(0);
		Error = sceCdGetError();
		if ( Error || tray_open )
		{
			write_ret = -70;
			if ( cdvdman_verbose >= 0 )
			{
				Kprintf("Read Error= 0x%02x\n", Error);
				return -70;
			}
			return write_ret;
		}
		result = lseek(filedata->cache_file_fd, i + filedata->sector_count_total, 0);
		if ( result < 0 )
		{
			return result;
		}
		write_ret = write(filedata->cache_file_fd, cdvdman_temp_buffer_ptr, 0x4000);
		if ( write_ret != 0x4000 )
		{
			break;
		}
		filedata->fd_rcvbuf[rstcalc2] |= 1 << rst_unalign;
LABEL_34:
		if ( cur < ++rst_tmp )
		{
			return write_ret;
		}
	}
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("write: ret:%d\n", write_ret);
	}
	result = write_ret;
	if ( write_ret >= 0 )
	{
		return -5;
	}
	return result;
}

//----- (00401878) --------------------------------------------------------
int __cdecl cdvdfile_cache_read(iop_file_t *f, void *buf, int nbyte)
{
	int nbyte_tmp; // $s1
	int result; // $v0
	CDVDMAN_FILEDATA *filedata; // $s0
	u32 read_pos; // $a1
	unsigned int file_size; // $v1

	nbyte_tmp = nbyte;
	if ( nbyte < 0 )
	{
		return -22;
	}
	filedata = &cdvdman_handles[(int)f->privdata];
	read_pos = filedata->read_pos;
	file_size = filedata->file_size;
	if ( file_size < read_pos + nbyte )
	{
		nbyte_tmp = file_size - read_pos;
	}
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("_cdvdfile_cache_read %d<->%d\n", read_pos, read_pos + nbyte_tmp);
	}
	result = 0;
	if ( nbyte_tmp > 0 )
	{
		result = lseek(filedata->cache_file_fd, filedata->read_pos + filedata->sector_count_total, 0);
		if ( result >= 0 )
		{
			result = read(filedata->cache_file_fd, buf, nbyte_tmp);
			if ( result >= 0 )
			{
				filedata->read_pos += result;
			}
		}
	}
	return result;
}

//----- (00401970) --------------------------------------------------------
int __cdecl cdvdfile_cache_fill_read(iop_file_t *f, void *buf, int nbytes)
{
	int result; // $v0

	result = cdvdman_devready();
	if ( result >= 0 )
	{
		result = cdrom_internal_write_cache(f, nbytes);
		if ( result >= 0 )
		{
			return cdvdfile_cache_read(f, buf, nbytes);
		}
	}
	else
	{
		cdvdman_iocache = 0;
	}
	return result;
}

//----- (004019E0) --------------------------------------------------------
int __cdecl cdrom_open(iop_file_t *f, const char *name, int mode, int arg4)
{
	int fds1; // $s1
	int fds2; // $s0
	int opensuccess1; // $a0
	int opensuccess2; // $a1
	int *p_fd_flags; // $v1
	int fdflags_band_8h; // $v0
	CDVDMAN_FILEDATA *filedata1; // $s1
	int srchspd; // $v0
	int underscoreind; // $s0
	u32 condtmp1; // $v0
	int devready_tmp; // $s0
	int fsv_evid_tmp1; // $a0
	int fsv_evid_tmp2; // $a0
	u8 trycnt_tmp; // $v0
	int fd_flags; // $v0
	u32 size; // $v1
	int fio_fsv_evid_tmp; // $a0
	char filename[128]; // [sp+18h] [-C8h] BYREF
	sceCdlFILE fileinfo; // [sp+98h] [-48h] BYREF
	cdrom_stm_devctl_t devctl_req; // [sp+C0h] [-20h] BYREF
	u32 efbits; // [sp+D8h] [-8h] BYREF
	int buf; // [sp+DCh] [-4h] BYREF

	fds1 = 0;
	if ( cdvdman_verbose > 0 )
	{
		printf("fileIO OPEN name= %s mode= 0x%08x layer %d\n", name, mode, f->unit);
	}
	fds2 = 0;
	WaitEventFlag(fio_fsv_evid, 1u, 16, &efbits);
	opensuccess1 = 0;
	opensuccess2 = 0;
	p_fd_flags = &cdvdman_handles[0].fd_flags;
	do
	{
		fdflags_band_8h = *p_fd_flags & 8;
		if ( !*p_fd_flags )
		{
			if ( !opensuccess1 )
			{
				fds1 = fds2;
				opensuccess1 = 1;
			}
			fdflags_band_8h = *p_fd_flags & 8;
		}
		if ( fdflags_band_8h )
		{
			opensuccess2 = 1;
		}
		++fds2;
		p_fd_flags += 12;
	}
	while ( fds2 < 16 );
	if ( !opensuccess1 || opensuccess2 )
	{
		printf("open fail name %s\n", name);
		SetEventFlag(fio_fsv_evid, 1u);
		return -24;
	}
	f->privdata = (void *)fds1;
	filedata1 = &cdvdman_handles[fds1];
	strncpy(filename, name, 128);
	cdvdman_cdfname(filename);
	if ( (mode & 0x40000000) != 0 || cdvdman_l0check(f->unit) )
	{
		cdvdman_srchspd = 0;
	}
	else
	{
		srchspd = cdvdman_spinnom != 0;
		if ( cdvdman_spinnom == -1 )
		{
			srchspd = (unsigned __int16)mode;
		}
		cdvdman_srchspd = srchspd;
	}
	if ( f->unit >= 2u )
	{
		goto LABEL_36;
	}
	if ( !strncmp(name, "sce_cdvd_lsn", 12) )
	{
		strncpy(filename, name, 128);
		underscoreind = 12;
		if ( filename[12] != 95 )
		{
			condtmp1 = 1;
			while ( condtmp1 )
			{
				if ( !filename[underscoreind++] )
				{
					break;
				}
				condtmp1 = underscoreind < 128;
				if ( filename[underscoreind] == 95 )
				{
					goto LABEL_28;
				}
			}
			goto LABEL_36;
		}
LABEL_28:
		fileinfo.size = strtol(&filename[underscoreind + 5], 0, 10);
		filename[underscoreind] = 0;
		fileinfo.lsn = strtol(&filename[12], 0, 10);
		if ( f->unit )
		{
			if ( cdvdman_devready() < 0 || !DvdDual_infochk() )
			{
				goto LABEL_36;
			}
			fileinfo.lsn += cdvdman_istruct.layer_1_lsn;
		}
	}
	else
	{
		devready_tmp = cdvdman_devready();
		if ( devready_tmp < 0 )
		{
			fsv_evid_tmp1 = fio_fsv_evid;
LABEL_52:
			SetEventFlag(fsv_evid_tmp1, 1u);
			return devready_tmp;
		}
		if ( !sceCdLayerSearchFile(&fileinfo, filename, f->unit) )
		{
LABEL_36:
			printf("open fail name %s\n", filename);
			fsv_evid_tmp2 = fio_fsv_evid;
LABEL_44:
			SetEventFlag(fsv_evid_tmp2, 1u);
			return -2;
		}
	}
	filedata1->fd_flags = 1;
	cdvdman_srchspd = 0;
	if ( (mode & 0x40000000) != 0 )
	{
		memset(&devctl_req, 0, sizeof(devctl_req));
		devctl_req.rmode.datapattern = 0;
		devctl_req.rmode.spindlctrl = 0;
		if ( cdvdman_trycnt == -1 )
		{
			trycnt_tmp = 0;
		}
		else
		{
			trycnt_tmp = cdvdman_trycnt;
		}
		devctl_req.rmode.trycount = trycnt_tmp;
		devctl_req.cmdid = 1;
		devctl_req.posszarg1 = fileinfo.lsn;
		if ( devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u) < 0 || !buf )
		{
			fsv_evid_tmp2 = fio_fsv_evid;
			filedata1->fd_flags = 0;
			goto LABEL_44;
		}
		fd_flags = filedata1->fd_flags;
		cdvdman_strmerr = 0;
		filedata1->fd_flags = fd_flags | 8;
	}
	filedata1->file_lsn = fileinfo.lsn;
	size = fileinfo.size;
	filedata1->read_pos = 0;
	filedata1->filemode = mode & 0xBFFFFFFF;
	filedata1->file_size = size;
	filedata1->fd_layer = f->unit;
	if ( (mode & 0x50000000) == 0x10000000 )
	{
		devready_tmp = -19;
		if ( cache_path_fd != -1 )
		{
			devready_tmp = cdvd_odcinit(filedata1, 1, (int)f->privdata);
			if ( devready_tmp < 0 )
			{
LABEL_51:
				fsv_evid_tmp1 = fio_fsv_evid;
				filedata1->fd_flags = 0;
				filedata1->fd_layer = 0;
				filedata1->filemode = 0;
				filedata1->read_pos = 0;
				filedata1->file_size = 0;
				filedata1->file_lsn = 0;
				goto LABEL_52;
			}
			filedata1->fd_flags |= 4u;
		}
		if ( devready_tmp < 0 )
		{
			goto LABEL_51;
		}
	}
	fio_fsv_evid_tmp = fio_fsv_evid;
	f->mode = 1;
	SetEventFlag(fio_fsv_evid_tmp, 1u);
	return 0;
}

//----- (00401EF0) --------------------------------------------------------
int __cdecl cdrom_close(iop_file_t *f)
{
	CDVDMAN_FILEDATA *filedata; // $s0
	int evid_tmp; // $a0
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	u32 efbits; // [sp+30h] [-8h] BYREF
	int buf; // [sp+34h] [-4h] BYREF

	if ( cdvdman_verbose > 0 )
	{
		printf("fileIO CLOSE\n");
	}
	WaitEventFlag(fio_fsv_evid, 1u, 16, &efbits);
	filedata = &cdvdman_handles[(int)f->privdata];
	if ( (filedata->fd_flags & 8) != 0
		&& ((cdvdman_strmerr = 0,
				 memset(&devctl_req, 0, sizeof(devctl_req)),
				 devctl_req.cmdid = 3,
				 devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u) < 0)
		 || !buf)
		|| (filedata->fd_flags & 0xC) == 4 && cdvd_odcinit(filedata, 0, (int)f->privdata) < 0 )
	{
		SetEventFlag(fio_fsv_evid, 1u);
		return -5;
	}
	else
	{
		evid_tmp = fio_fsv_evid;
		filedata->file_lsn = 0;
		filedata->file_size = 0;
		filedata->read_pos = 0;
		filedata->fd_flags = 0;
		filedata->fd_layer = 0;
		filedata->filemode = 1;
		f->mode = 0;
		SetEventFlag(evid_tmp, 1u);
		return 0;
	}
}

//----- (00402050) --------------------------------------------------------
int __fastcall cdrom_internal_read(iop_file_t *f, char *addr, int nbytes)
{
	unsigned int sectors; // $s6
	int result; // $v0
	void *privdata; // $s0
	int unit; // $a2
	unsigned int readpos_end; // $v0
	u32 file_size; // $v1
	CDVDMAN_FILEDATA *filedata1; // $t0
	int nbytes_tmp; // $s5
	unsigned int lbn; // $s1
	int pos_extra; // $s4
	unsigned int sectors_minus_1; // $a1
	unsigned int lbn_plus_8; // $v0
	int nbytes_div_2048; // $a1
	int addr_unaligned; // $v0
	char *addr_tmp; // $a0
	unsigned int nbytes_tmp2; // $a2
	const char *pos_tmp2; // $a1
	unsigned int sec; // $s2
	u32 condtmp1; // $v0
	unsigned int lbn_tmp3; // $a0
	int read_error; // $v0
	u32 condtmp2; // $v0
	unsigned int sectors_count; // $s0
	unsigned int lbn_tmp2; // $a0
	int Error; // $v0
	unsigned int i; // $a0
	bool condtmp3; // dc
	sceCdRMode rmode[2]; // [sp+10h] [-28h] BYREF
	int read_res; // [sp+18h] [-20h]
	int lbn_tmp; // [sp+1Ch] [-1Ch]
	u32 file_lsn; // [sp+20h] [-18h]
	unsigned int read_pos; // [sp+24h] [-14h]
	unsigned int filesize_bsr_11; // [sp+28h] [-10h]
	int pos_sub_2048; // [sp+2Ch] [-Ch]
	CDVDMAN_FILEDATA *filedata2; // [sp+30h] [-8h]
	void *buf; // [sp+34h] [-4h]

	sectors = 1;
	if ( cdvdman_verbose > 0 )
	{
		printf("cdvd fileIO read start\n");
	}
	result = cdvdman_devready();
	if ( result < 0 )
	{
		cdvdman_iocache = 0;
		return result;
	}
	privdata = f->privdata;
	unit = f->unit;
	filedata2 = &cdvdman_handles[(_DWORD)privdata];
	cdvdman_iormode(rmode, filedata2->filemode, unit);
	result = -22;
	if ( nbytes >= 0 )
	{
		read_res = 0;
		readpos_end = filedata2->read_pos + nbytes;
		read_pos = filedata2->read_pos;
		file_size = filedata2->file_size;
		file_lsn = filedata2->file_lsn;
		if ( file_size < readpos_end )
		{
			nbytes = file_size - read_pos;
		}
		filesize_bsr_11 = file_size >> 11;
		if ( (file_size & 0x7FF) != 0 )
		{
			filesize_bsr_11 = (file_size >> 11) + 1;
		}
		filesize_bsr_11 += file_lsn;
		if ( cdvdman_verbose > 0 )
		{
			printf("fds= %d read file_lbn= %d offset= %d\n", privdata, file_lsn, read_pos);
		}
		buf = 0;
		if ( !nbytes )
		{
LABEL_87:
			condtmp3 = cdvdman_verbose <= 0;
			filedata2->read_pos = read_pos;
			if ( !condtmp3 )
			{
				printf("fileIO read ended\n");
			}
			cdvdman_spinctl = -1;
			return read_res;
		}
		while ( 1 )
		{
			if ( cdvdman_spinctl != -1 )
			{
				rmode[0].spindlctrl = cdvdman_spinctl;
				switch ( cdvdman_spinctl )
				{
					case 0:
						filedata2->filemode = 0;
						break;
					case 1:
						filedata1 = filedata2;
						goto LABEL_26;
					case 2:
						filedata2->filemode = 2;
						break;
					case 3:
						filedata2->filemode = 3;
						break;
					case 4:
						filedata2->filemode = 4;
						break;
					case 5:
						filedata2->filemode = 5;
						break;
					default:
						filedata1 = filedata2;
LABEL_26:
						filedata1->filemode = 1;
						break;
				}
			}
			nbytes_tmp = nbytes;
			pos_sub_2048 = 0;
			lbn = file_lsn + (read_pos >> 11);
			lbn_tmp = lbn;
			pos_extra = read_pos & 0x7FF;
			if ( nbytes < 16385 )
			{
				nbytes_div_2048 = nbytes / 2048;
				if ( (nbytes & 0x7FF) != 0 )
				{
					++nbytes_div_2048;
				}
				sectors = nbytes_div_2048 + (pos_extra != 0);
			}
			else
			{
				nbytes_tmp = 0x4000;
				if ( buf && (read_pos & 0x7FF) != 0 && cdvdman_iocache )
				{
					sectors_minus_1 = sectors - 1;
					sectors = 8;
					++lbn;
					pos_sub_2048 = 2048 - pos_extra;
					cdvdman_memcpy(
						addr,
						(const char *)cdvdman_temp_buffer_ptr + 2048 * sectors_minus_1 + pos_extra,
						2048 - pos_extra);
					cdvdman_iocache = 0;
					lbn_plus_8 = lbn + 8;
					goto LABEL_38;
				}
				sectors = 8;
				if ( (read_pos & 0x7FF) != 0 )
				{
					sectors = 9;
				}
			}
			lbn_plus_8 = lbn + sectors;
LABEL_38:
			buf = cdvdman_temp_buffer_ptr;
			if ( filesize_bsr_11 < lbn_plus_8 )
			{
				sectors = filesize_bsr_11 - lbn;
			}
			if ( cdvdman_verbose > 0 )
			{
				printf("sce_Read LBN= %d sectors= %d\n", lbn, sectors);
			}
			addr_unaligned = (uiptr)addr & 3;
			if ( cdvdman_iocache )
			{
				addr_unaligned = (uiptr)addr & 3;
				if ( lbn >= cdvdman_lcn_offset )
				{
					addr_unaligned = (uiptr)addr & 3;
					if ( cdvdman_lcn_offset + cdvdman_numbytes_offset >= lbn + sectors )
					{
						addr_tmp = addr;
						nbytes_tmp2 = nbytes_tmp;
						pos_tmp2 = (char *)buf + 2048 * (lbn - cdvdman_lcn_offset) + pos_extra;
						goto LABEL_84;
					}
				}
			}
			sec = 8;
			if ( addr_unaligned )
			{
				condtmp1 = sectors < 8;
LABEL_59:
				if ( !condtmp1 )
				{
					sec = sectors;
				}
				if ( filesize_bsr_11 < lbn + sec )
				{
					sec = filesize_bsr_11 - lbn;
				}
				condtmp2 = sec < 9;
				if ( cdvdman_verbose > 0 )
				{
					printf("FIO Cache LSN:%d SEC:%d ADDR:%08x\n", lbn, sec, buf);
					condtmp2 = sec < 9;
				}
				sectors_count = 0;
				if ( !condtmp2 )
				{
					sectors_count = sec - 8;
				}
				lbn_tmp2 = lbn;
				if ( sectors_count )
				{
					while ( !sceCdRE(lbn_tmp2, sectors_count, buf, rmode) )
					{
						if ( cdvdman_verbose > 0 )
						{
							printf("sce_Read ON Delay\n");
						}
						if ( (sceCdStatus() & 1) != 0 )
						{
LABEL_7:
							cdvdman_iocache = 0;
							cdvdman_spinctl = -1;
							return -5;
						}
						DelayThread(10000);
						lbn_tmp2 = lbn;
					}
					sceCdSync(0);
					Error = sceCdGetError();
					if ( Error )
					{
						goto LABEL_8;
					}
				}
				for ( i = lbn + sectors_count;
							!sceCdRE(i, sec - sectors_count, (char *)buf + 2048 * sectors_count, rmode);
							i = lbn + sectors_count )
				{
					if ( cdvdman_verbose > 0 )
					{
						printf("sce_Read ON Delay\n");
					}
					if ( (sceCdStatus() & 1) != 0 )
					{
						goto LABEL_7;
					}
					DelayThread(10000);
				}
				sceCdSync(0);
				Error = sceCdGetError();
				if ( Error )
				{
LABEL_8:
					printf("Read Error= 0x%02x\n", Error);
					cdvdman_iocache = 0;
					goto LABEL_87;
				}
				cdvdman_lcn_offset = lbn_tmp;
				cdvdman_numbytes_offset = sec;
				cdvdman_iocache = 1;
				addr_tmp = &addr[pos_sub_2048];
				if ( pos_sub_2048 )
				{
					pos_tmp2 = (const char *)cdvdman_temp_buffer_ptr;
					nbytes_tmp2 = nbytes_tmp - pos_sub_2048;
				}
				else
				{
					addr_tmp = addr;
					nbytes_tmp2 = nbytes_tmp;
					pos_tmp2 = (char *)cdvdman_temp_buffer_ptr + pos_extra;
				}
LABEL_84:
				cdvdman_memcpy(addr_tmp, pos_tmp2, nbytes_tmp2);
				goto LABEL_85;
			}
			condtmp1 = sectors < 8;
			if ( pos_extra )
			{
				goto LABEL_59;
			}
			condtmp1 = sectors < 8;
			if ( nbytes_tmp != 0x4000 )
			{
				goto LABEL_59;
			}
			lbn_tmp3 = lbn;
			if ( cdvdman_verbose > 0 )
			{
				printf("FIO Usr addr LSN:%d SEC:%d ADDR:%08x\n", lbn, sectors, addr);
				lbn_tmp3 = lbn;
			}
			while ( !sceCdRE(lbn_tmp3, sectors, addr, rmode) )
			{
				if ( cdvdman_verbose > 0 )
				{
					printf("sce_Read ON Delay\n");
				}
				if ( (sceCdStatus() & 1) != 0 )
				{
					goto LABEL_7;
				}
				DelayThread(10000);
				lbn_tmp3 = lbn;
			}
			sceCdSync(0);
			read_error = sceCdGetError();
			cdvdman_iocache = 0;
			if ( read_error )
			{
				printf("Read Error= 0x%02x\n", read_error);
				goto LABEL_87;
			}
LABEL_85:
			addr += nbytes_tmp;
			if ( nbytes_tmp <= 0 )
			{
				cdvdman_spinctl = -1;
				return nbytes_tmp;
			}
			nbytes -= nbytes_tmp;
			read_pos += nbytes_tmp;
			read_res += nbytes_tmp;
			if ( !nbytes )
			{
				goto LABEL_87;
			}
		}
	}
	return result;
}

//----- (00402740) --------------------------------------------------------
int __fastcall cdrom_stream_read(iop_file_t *f, char *bbuf, int nbytes)
{
	int unit; // $a2
	CDVDMAN_FILEDATA *filedata; // $s0
	int filemode; // $a1
	int strmerr; // $a0
	int result; // $v0
	sceCdRMode rmode; // [sp+18h] [-28h] BYREF
	cdrom_stm_devctl_t devctl_req; // [sp+20h] [-20h] BYREF
	int buf; // [sp+38h] [-8h] BYREF

	unit = f->unit;
	filedata = &cdvdman_handles[(int)f->privdata];
	filemode = filedata->filemode;
	cdvdman_strmerr = 0;
	cdvdman_iormode(&rmode, filemode, unit);
	rmode.spindlctrl = 0;
	rmode.trycount = 0;
	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.cmdid = 1;
	devctl_req.posszarg2 = nbytes >> 11;
	devctl_req.buffer = bbuf;
	devctl("cdrom_stm0:", 17300, &devctl_req, 0x18u, &buf, 4u);
	strmerr = devctl_req.error;
	result = buf << 11;
	filedata->read_pos += buf << 11;
	cdvdman_strmerr = strmerr;
	return result;
}

//----- (00402828) --------------------------------------------------------
int __cdecl cdrom_read(iop_file_t *f, void *buf, int nbytes)
{
	CDVDMAN_FILEDATA *filedata1; // $s1
	int fd_flags; // $v1
	int rc; // $s0
	CDVDMAN_FILEDATA *filedata2; // $a0
	u32 efbits[2]; // [sp+10h] [-8h] BYREF

	if ( nbytes < 0 )
	{
		return -22;
	}
	WaitEventFlag(fio_fsv_evid, 1u, 16, efbits);
	filedata1 = &cdvdman_handles[(int)f->privdata];
	if ( cdvdman_mediactl(2) )
	{
		cdvdman_iocache = 0;
		cdvdman_invcaches();
	}
	fd_flags = filedata1->fd_flags;
	if ( (fd_flags & 8) == 0 )
	{
		if ( (fd_flags & 4) == 0 )
		{
			goto LABEL_23;
		}
		rc = cdrom_internal_cache_read(f, nbytes);
		if ( rc )
		{
			if ( rc <= 0 )
			{
				filedata2 = filedata1;
				if ( rc == -16 )
				{
					goto LABEL_21;
				}
				goto LABEL_18;
			}
			filedata2 = filedata1;
			if ( rc != 1 )
			{
LABEL_18:
				filedata1->fd_flags &= ~4u;
				rc = -5;
				cdvd_odcinit(filedata2, 0, (int)f->privdata);
				goto LABEL_19;
			}
			rc = cdvdfile_cache_fill_read(f, buf, nbytes);
			if ( cdvdman_verbose > 0 )
			{
				Kprintf("called _cdvdfile_cache_fill_read %d\n", rc);
			}
		}
		else
		{
			rc = cdvdfile_cache_read(f, buf, nbytes);
			if ( cdvdman_verbose > 0 )
			{
				Kprintf("called _cdvdfile_cache_read %d\n", rc);
			}
		}
LABEL_19:
		if ( rc != -16 && rc != -70 )
		{
LABEL_22:
			if ( rc >= 0 )
			{
				goto LABEL_24;
			}
LABEL_23:
			rc = cdrom_internal_read(f, (char *)buf, nbytes);
			goto LABEL_24;
		}
LABEL_21:
		cdvdman_cache_invalidate(filedata1, (int)f->privdata);
		Kprintf("_cdvdfile_cache Read_err OR Drive_not_ready\n", rc);
		goto LABEL_22;
	}
	rc = cdrom_stream_read(f, (char *)buf, nbytes);
LABEL_24:
	SetEventFlag(fio_fsv_evid, 1u);
	return rc;
}

//----- (00402A2C) --------------------------------------------------------
int __fastcall cdrom_ioctl(iop_file_t *f, int arg, void *param)
{
	if ( arg != 0x10000 )
	{
		return -5;
	}
	cdvdman_spinnom = -1;
	sceCdSpinCtrlIOP((u32)param);
	return 0;
}

//----- (00402A7C) --------------------------------------------------------
int __cdecl cdrom_ioctl2(iop_file_t *f, int request, void *argp, size_t arglen, void *bufp, size_t buflen)
{
	CDVDMAN_FILEDATA *filedata; // $v1
	int retval1; // $s0
	u32 reqind; // $v0
	bool condtmp1; // dc
	int retval2; // $v0
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	u32 efbits; // [sp+30h] [-8h] BYREF
	int buf; // [sp+34h] [-4h] BYREF

	WaitEventFlag(fio_fsv_evid, 1u, 16, &efbits);
	filedata = &cdvdman_handles[(int)f->privdata];
	if ( request == 25358 )
	{
		if ( (filedata->fd_flags & 8) != 0 )
		{
			memset(&devctl_req, 0, sizeof(devctl_req));
			reqind = 8;
			goto LABEL_9;
		}
LABEL_18:
		retval1 = -5;
		goto LABEL_19;
	}
	if ( request < 25359 )
	{
		retval1 = -5;
		if ( request != 25357 )
		{
			goto LABEL_19;
		}
		if ( (filedata->fd_flags & 8) != 0 )
		{
			memset(&devctl_req, 0, sizeof(devctl_req));
			reqind = 7;
LABEL_9:
			devctl_req.cmdid = reqind;
			condtmp1 = devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u) < 0;
			retval2 = -5;
			if ( !condtmp1 )
			{
				retval2 = 0;
				if ( !buf )
				{
					retval2 = -5;
				}
			}
			goto LABEL_17;
		}
		goto LABEL_18;
	}
	retval1 = -5;
	if ( request != 25359 )
	{
		goto LABEL_19;
	}
	if ( (filedata->fd_flags & 8) == 0 )
	{
		goto LABEL_18;
	}
	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.cmdid = 6;
	retval1 = devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u);
	if ( retval1 >= 0 )
	{
		retval2 = buf;
LABEL_17:
		retval1 = retval2;
	}
LABEL_19:
	SetEventFlag(fio_fsv_evid, 1u);
	return retval1;
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
	unsigned int sc_tmp; // $s0
	int retval1; // $s1
	int retval2; // $s1
	int seek_pause_res; // $v0
	int standby_stop_res; // $v0
	int Clock; // $s1
	int DiskType; // $v0
	int Toc; // $v0
	int disk_type_res; // $v1
	bool condtmp1; // dc
	void *strm_req; // $v1
	int retval3; // $v0
	unsigned int sc_tmp_ex; // $s0
	char *sc_tmp_2; // $v1
	unsigned int sc_tmp_3; // $a1
	unsigned int sc_tmp_4; // $s0
	u8 *sc_tmp_4_addptr; // $a0
	BOOL condtmp2; // $v0
	int sc_str_as_int; // $a0
	char *cachedev; // $a1
	int cacheaction; // $a2
	unsigned int sc_tmp_5; // $s0
	int sc_tmp_6; // $v1
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-28h] BYREF
	u32 efbits; // [sp+30h] [-10h] BYREF
	int on_dual_tmp; // [sp+34h] [-Ch] BYREF
	int condtmpstk; // [sp+38h] [-8h] BYREF

	sc_tmp = 0;
	if ( cmd == 0x4328 )
	{
		retval1 = 0;
		if ( !sceCdBreak() )
		{
			retval1 = -5;
		}
		sceCdSync(4);
		return retval1;
	}
	else
	{
		retval2 = 0;
		WaitEventFlag(fio_fsv_evid, 1u, 16, &efbits);
		switch ( cmd )
		{
			case 0x430C:
				do
				{
					WaitEventFlag(scmd_evid, 1u, 0, &efbits);
					Clock = sceCdReadClock((sceCdCLOCK *)bufp);
					if ( Clock )
					{
						break;
					}
				}
				while ( sc_tmp++ < 3 );
				goto LABEL_46;
			case 0x431D:
				do
				{
					WaitEventFlag(scmd_evid, 1u, 0, &efbits);
					Clock = sceCdReadGUID((u64 *)bufp);
					if ( Clock )
					{
						break;
					}
				}
				while ( sc_tmp++ < 3 );
				goto LABEL_46;
			case 0x431E:
				Toc = sceCdReadDiskID((unsigned int *)bufp);
				retval2 = 0;
				goto LABEL_27;
			case 0x431F:
				DiskType = sceCdGetDiskType();
				goto LABEL_23;
			case 0x4320:
				DiskType = cdvdman_strmerr;
				if ( cdvdman_strmerr )
				{
LABEL_23:
					*(_DWORD *)bufp = DiskType;
				}
				else
				{
					*(_DWORD *)bufp = sceCdGetError();
				}
				goto LABEL_88;
			case 0x4321:
				retval2 = 0;
				Toc = sceCdTrayReq(*(_DWORD *)argp, (u32 *)bufp);
				goto LABEL_27;
			case 0x4322:
				*(_DWORD *)bufp = sceCdStatus();
				goto LABEL_88;
			case 0x4323:
				do
				{
					WaitEventFlag(scmd_evid, 1u, 0, &efbits);
					Clock = sceCdPowerOff((u32 *)bufp);
					if ( Clock )
					{
						break;
					}
				}
				while ( sc_tmp++ < 3 );
				goto LABEL_46;
			case 0x4324:
				sceCdMmode(*(_DWORD *)argp);
				goto LABEL_88;
			case 0x4325:
				*(_DWORD *)bufp = sceCdDiskReady(*(_DWORD *)argp);
				goto LABEL_88;
			case 0x4326:
				do
				{
					WaitEventFlag(scmd_evid, 1u, 0, &efbits);
					Clock = sceCdReadModelID((unsigned int *)bufp);
					if ( Clock )
					{
						break;
					}
				}
				while ( sc_tmp++ < 3 );
LABEL_46:
				condtmp1 = Clock == 1;
				retval2 = 0;
				if ( !condtmp1 )
				{
					retval2 = -5;
				}
				goto LABEL_88;
			case 0x4327:
				memset(&devctl_req, 0, sizeof(devctl_req));
				devctl_req.posszarg1 = *(_DWORD *)argp;
				devctl_req.posszarg2 = *((_DWORD *)argp + 1);
				strm_req = (void *)*((_DWORD *)argp + 2);
				devctl_req.cmdid = 5;
				devctl_req.buffer = strm_req;
				condtmp1 = devctl("cdrom_stm0:", 0x4393, &devctl_req, 0x18u, &condtmpstk, 4u) < 0;
				retval3 = -5;
				if ( !condtmp1 )
				{
					retval3 = 0;
					if ( !condtmpstk )
					{
						retval3 = -5;
					}
				}
				goto LABEL_86;
			case 0x4380:
				cdvdman_spinnom = 1;
				goto LABEL_88;
			case 0x4381:
				cdvdman_spinnom = 0;
				goto LABEL_88;
			case 0x4382:
				cdvdman_trycnt = *(unsigned __int8 *)argp;
				goto LABEL_88;
			case 0x4383:
				retval2 = 0;
				seek_pause_res = sceCdSeek(*(_DWORD *)argp);
				goto LABEL_16;
			case 0x4384:
				retval2 = 0;
				standby_stop_res = sceCdStandby();
				goto LABEL_12;
			case 0x4385:
				retval2 = 0;
				standby_stop_res = sceCdStop();
LABEL_12:
				if ( standby_stop_res != 1 )
				{
					retval2 = -5;
				}
				sceCdSync(4);
				goto LABEL_88;
			case 0x4386:
				retval2 = 0;
				seek_pause_res = sceCdPause();
LABEL_16:
				if ( seek_pause_res != 1 )
				{
					retval2 = -5;
				}
				sceCdSync(6);
				goto LABEL_88;
			case 0x4387:
				disk_type_res = sceCdGetDiskType();
				if ( (unsigned int)(disk_type_res - 18) < 2 || disk_type_res == 16 || disk_type_res == 17 )
				{
					Toc = sceCdGetToc((u8 *)bufp);
					retval2 = 0;
LABEL_27:
					if ( Toc != 1 )
					{
						retval2 = -5;
					}
				}
				else
				{
					retval2 = -5;
				}
				goto LABEL_88;
			case 0x4388:
				retval2 = 0;
				Toc = sceCdSetTimeout(1, *(_DWORD *)argp);
				goto LABEL_27;
			case 0x4389:
				retval2 = 0;
				if ( !sceCdReadDvdDualInfo(&on_dual_tmp, (unsigned int *)bufp) )
				{
					retval2 = -5;
				}
				goto LABEL_88;
			case 0x438A:
				retval2 = 0;
				if ( !sceCdInit(*(_DWORD *)argp) )
				{
					retval2 = -5;
				}
				goto LABEL_88;
			case 0x438C:
				cdvdman_spinnom = 2;
				goto LABEL_88;
			case 0x438D:
				cdvdman_spinnom = 3;
				goto LABEL_88;
			case 0x438E:
				cdvdman_spinnom = 4;
				goto LABEL_88;
			case 0x438F:
				cdvdman_spinnom = 5;
				goto LABEL_88;
			case 0x4390:
				cdvdman_spinnom = 20;
				goto LABEL_88;
			case 0x4391:
				*(_DWORD *)bufp = sceCdSC('\xF5', &on_dual_tmp);
				goto LABEL_88;
			case 0x4392:
				retval2 = 0;
				Toc = sceCdApplySCmd(*(_BYTE *)argp, (char *)argp + 4, arglen - 4, bufp);
				goto LABEL_27;
			case 0x4395:
				retval2 = -16;
				if ( cache_path_fd != -1 )
				{
					goto LABEL_88;
				}
				sc_tmp_ex = 0;
				if ( arglen && *(_BYTE *)argp != ',' )
				{
					sc_tmp_2 = (char *)argp;
					do
					{
						if ( !*sc_tmp_2 )
						{
							break;
						}
						aHost0[sc_tmp_ex++] = *sc_tmp_2++;
						if ( sc_tmp_ex >= arglen )
						{
							break;
						}
					}
					while ( *sc_tmp_2 != ',' );
				}
				sc_tmp_3 = sc_tmp_ex;
				if ( arglen < sc_tmp_ex )
				{
					goto LABEL_78;
				}
				sc_tmp_4 = sc_tmp_ex + 1;
				sc_tmp_4_addptr = (u8 *)argp + sc_tmp_4;
				if ( sc_tmp_4 >= arglen || *sc_tmp_4_addptr == 44 )
				{
					goto LABEL_76;
				}
				break;
			case 0x4397:
				sc_tmp_5 = 0;
				sc_tmp_6 = 0;
				do
				{
					if ( (cdvdman_handles[sc_tmp_6].fd_flags & 4) != 0 )
					{
						break;
					}
					++sc_tmp_5;
					++sc_tmp_6;
				}
				while ( sc_tmp_5 < 0x10 );
				retval2 = -16;
				if ( sc_tmp_5 != 16 )
				{
					goto LABEL_88;
				}
				sc_str_as_int = 0;
				cachedev = 0;
				cacheaction = 0;
				goto LABEL_85;
			default:
				retval2 = -5;
				goto LABEL_88;
		}
		while ( 1 )
		{
			condtmp2 = arglen < sc_tmp_4;
			if ( !*sc_tmp_4_addptr )
			{
				break;
			}
			++sc_tmp_4;
			sc_tmp_4_addptr = (u8 *)argp + sc_tmp_4;
			if ( sc_tmp_4 >= arglen || *sc_tmp_4_addptr == 44 )
			{
LABEL_76:
				condtmp2 = arglen < sc_tmp_4;
				break;
			}
		}
		if ( condtmp2 )
		{
LABEL_78:
			retval2 = -22;
		}
		else
		{
			*((_BYTE *)argp + sc_tmp_4) = 0;
			cdvdman_cache_sector_size_count = strtol((const char *)argp + sc_tmp_3, 0, 10);
			sc_str_as_int = strtol((const char *)argp + sc_tmp_4 + 1, 0, 10);
			cachedev = aHost0;
			cacheaction = 1;
LABEL_85:
			retval3 = path_tbl_init(sc_str_as_int, cachedev, cacheaction);
LABEL_86:
			retval2 = retval3;
		}
LABEL_88:
		SetEventFlag(fio_fsv_evid, 1u);
		return retval2;
	}
}
// 402ED0: conditional instruction was optimized away because $v1.4 is in (<10u|>=12u)

//----- (004032AC) --------------------------------------------------------
int __cdecl cdrom_lseek(iop_file_t *f, int offset, int pos)
{
	int retval; // $s1
	CDVDMAN_FILEDATA *filedata; // $s0
	int readpos_tmp; // $v0
	u32 file_size; // $v1
	u32 file_lsn; // $v1
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	u32 efbits; // [sp+30h] [-8h] BYREF
	int buf; // [sp+34h] [-4h] BYREF

	retval = -1;
	if ( cdvdman_verbose > 0 )
	{
		printf("fileIO SEEK\n");
	}
	WaitEventFlag(fio_fsv_evid, 1u, 16, &efbits);
	filedata = &cdvdman_handles[(int)f->privdata];
	if ( pos == 1 )
	{
		readpos_tmp = filedata->read_pos + offset;
		goto LABEL_12;
	}
	if ( pos >= 2 )
	{
		if ( pos != 2 )
		{
			goto LABEL_13;
		}
		readpos_tmp = filedata->file_size - offset;
LABEL_12:
		retval = readpos_tmp;
		filedata->read_pos = readpos_tmp;
		goto LABEL_13;
	}
	if ( !pos )
	{
		filedata->read_pos = offset;
		retval = offset;
	}
LABEL_13:
	file_size = filedata->file_size;
	if ( file_size < filedata->read_pos )
	{
		filedata->read_pos = file_size;
		retval = file_size;
	}
	if ( (filedata->fd_flags & 8) != 0 )
	{
		memset(&devctl_req, 0, sizeof(devctl_req));
		file_lsn = filedata->file_lsn;
		devctl_req.cmdid = 9;
		devctl_req.posszarg1 = file_lsn + retval / 2048;
		if ( devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u) < 0 || !buf )
		{
			retval = -5;
		}
	}
	SetEventFlag(fio_fsv_evid, 1u);
	return retval;
}

//----- (00403464) --------------------------------------------------------
int __cdecl cdrom_nulldev()
{
	printf("nulldev0 call\n");
	return -5;
}

//----- (0040348C) --------------------------------------------------------
s64 __cdecl cdrom_nulldev64()
{
	printf("nulldev0 call\n");
	return -5LL;
}

//----- (004034C0) --------------------------------------------------------
int __cdecl sync_timeout_func(iop_sys_clock_t *timeout_ptr)
{
	Kprintf("Cdvd Time Out %d(msec)\n", timeout_ptr->lo / 0x9000);
	return sceCdBreak() == 0;
}

//----- (00403504) --------------------------------------------------------
int __cdecl sceCdSetTimeout(int param, int timeout)
{
	bool condtmp; // dc
	int result; // $v0

	condtmp = sceCdCheckCmd() == 0;
	result = 0;
	if ( !condtmp )
	{
		result = 0;
		if ( !cdvdman_istruct.read2_flag )
		{
			if ( param == 1 )
			{
				cdvdman_sync_to = timeout;
				return 1;
			}
			else
			{
				result = 0;
				if ( param == 2 )
				{
					TimeOut2 = timeout;
					return 1;
				}
			}
		}
	}
	return result;
}

//----- (00403588) --------------------------------------------------------
int __cdecl sceCdSync(int mode)
{
	int read2_flag; // $v0
	bool condtmp; // dc
	int result; // $v0
	iop_sys_clock_t sysclk; // [sp+10h] [-30h] BYREF
	iop_event_info_t efinfo; // [sp+18h] [-28h] BYREF
	u32 resbits[2]; // [sp+38h] [-8h] BYREF

	if ( cdvdman_verbose > 0 )
	{
		Kprintf("sceCdSync: Call mode %d Com %x\n", mode, (unsigned __int8)cdvdman_istruct.cdvdman_command);
	}
	switch ( mode )
	{
		case 0:
			while ( !sceCdCheckCmd() || cdvdman_istruct.read2_flag )
			{
				WaitEventFlag(cdvdman_intr_efid, 1u, 0, resbits);
			}
			goto LABEL_43;
		case 1:
			if ( !sceCdCheckCmd() )
			{
				goto LABEL_35;
			}
			read2_flag = cdvdman_istruct.read2_flag;
			goto LABEL_34;
		case 3:
			sysclk.hi = 0;
			sysclk.lo = 0x9000 * cdvdman_sync_to;
			vSetAlarm(&sysclk, (unsigned int (__cdecl *)(void *))sync_timeout_func, &sysclk);
			while ( !sceCdCheckCmd() || cdvdman_istruct.read2_flag )
			{
				WaitEventFlag(cdvdman_intr_efid, 1u, 0, resbits);
			}
			goto LABEL_23;
		case 4:
			sysclk.hi = 0;
			sysclk.lo = 0x41EB0000;
			vSetAlarm(&sysclk, (unsigned int (__cdecl *)(void *))sync_timeout_func, &sysclk);
			while ( !sceCdCheckCmd() || cdvdman_istruct.read2_flag )
			{
				WaitEventFlag(cdvdman_intr_efid, 1u, 0, resbits);
			}
			goto LABEL_23;
		case 5:
			while ( !sceCdCheckCmd() )
			{
				WaitEventFlag(cdvdman_intr_efid, 1u, 0, resbits);
			}
			goto LABEL_43;
		case 6:
			sysclk.hi = 0;
			sysclk.lo = 0x9000 * cdvdman_sync_to;
			vSetAlarm(&sysclk, (unsigned int (__cdecl *)(void *))sync_timeout_func, &sysclk);
			while ( !sceCdCheckCmd() || cdvdman_istruct.read2_flag )
			{
				WaitEventFlag(cdvdman_intr_efid, 1u, 0, resbits);
			}
LABEL_23:
			vCancelAlarm((unsigned int (__cdecl *)(void *))sync_timeout_func, &sysclk);
			goto LABEL_43;
		case 16:
			while ( !sceCdCheckCmd() || cdvdman_istruct.read2_flag || cdvdman_strm_id || cdvdman_istruct.stream_flag )
			{
				WaitEventFlag(cdvdman_intr_efid, 1u, 0, resbits);
				if ( cdvdman_strm_id )
				{
					DelayThread(8000);
				}
			}
			goto LABEL_43;
		case 17:
			if ( !sceCdCheckCmd() || cdvdman_istruct.read2_flag || cdvdman_strm_id )
			{
				goto LABEL_35;
			}
			read2_flag = cdvdman_istruct.stream_flag;
LABEL_34:
			condtmp = read2_flag == 0;
			result = 0;
			if ( !condtmp )
			{
LABEL_35:
				result = 1;
			}
			break;
		case 32:
			WaitEventFlag(cdvdman_intr_efid, 0x21u, 1, resbits);
			ReferEventFlagStatus(cdvdman_intr_efid, &efinfo);
			if ( (efinfo.currBits & 0x20) == 0 )
			{
				if ( cdvdman_istruct.last_error )
				{
					SetEventFlag(cdvdman_intr_efid, 0x20u);
				}
				else
				{
					WaitEventFlag(cdvdman_intr_efid, 0x20u, 0, resbits);
				}
			}
			goto LABEL_43;
		default:
			while ( !sceCdCheckCmd() || cdvdman_istruct.read2_flag )
			{
				WaitEventFlag(cdvdman_intr_efid, 1u, 0, resbits);
			}
LABEL_43:
			result = 0;
			if ( cdvdman_verbose > 0 )
			{
				Kprintf(
					"sceCdSync: Command= %d Error= %d\n",
					(unsigned __int8)cdvdman_istruct.cdvdman_command,
					(unsigned __int8)cdvdman_istruct.last_error);
				result = 0;
			}
			break;
	}
	return result;
}

//----- (004039C4) --------------------------------------------------------
int __cdecl sceCdSpinCtrlIOP(u32 speed)
{
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("sceCdSpinCtrlIOP speed= %d\n", speed);
	}
	cdvdman_spinctl = speed;
	return 1;
}

//----- (00403A0C) --------------------------------------------------------
int __cdecl sceCdLayerSearchFile(sceCdlFILE *fp, const char *path, int layer)
{
	int efret; // $v0
	int pathlen; // $a3
	const char *pathptrtmp; // $v0
	char pathchrtmp; // $v0
	CDVDMAN_FILETBL_ENTRY_T *ftble; // $a0
	int search_res; // $s0
	u32 efbits[2]; // [sp+10h] [-8h] BYREF

	efret = PollEventFlag(sfile_evid, 1u, 16, efbits);
	pathlen = 0;
	if ( efret == -421 )
	{
		return 0;
	}
	pathptrtmp = path;
	while ( 1 )
	{
		pathchrtmp = *pathptrtmp;
		ftble = (CDVDMAN_FILETBL_ENTRY_T *)fp;
		if ( !pathchrtmp )
		{
			break;
		}
		cdvdman_sfname[pathlen++] = pathchrtmp;
		pathptrtmp = &path[pathlen];
		if ( pathlen >= 1023 )
		{
			ftble = (CDVDMAN_FILETBL_ENTRY_T *)fp;
			break;
		}
	}
	cdvdman_sfname[pathlen] = 0;
	cdvdman_srchspd = 1;
	search_res = CdSearchFileInner(ftble, cdvdman_sfname, layer);
	vSetEventFlag(sfile_evid, 1u);
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
	vu8 dev5_reg_005; // $a1
	vu8 dev5_reg_00F; // $v1
	vu8 reg005_fmp1; // $v0
	int result; // $v0
	vu8 reg00F_tmp1; // $v0
	vu8 reg005_tmp2; // $v1
	int reg00F_tmp2; // $a0
	int reg005_bcheck_c0h; // $v0
	u32 efbits[2]; // [sp+10h] [-8h] BYREF

	efbits[0] = 0;
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("DISK READY call from iop\n");
	}
	if ( mode )
	{
		if ( mode == 8 )
		{
			LOBYTE(result) = dev5_regs.dev5_reg_005;
			return (unsigned __int8)result;
		}
		else
		{
			reg005_bcheck_c0h = dev5_regs.dev5_reg_005 & 0xC0;
			if ( reg005_bcheck_c0h != 64 || (result = 2, cdvdman_istruct.read2_flag) )
			{
				result = 6;
				if ( cdvdman_verbose > 0 )
				{
					Kprintf("Drive Not Ready\n");
					return 6;
				}
			}
		}
	}
	else
	{
		if ( cdvdman_verbose > 0 )
		{
			dev5_reg_005 = dev5_regs.dev5_reg_005;
			Kprintf("Wait Drive Ready %x\n", dev5_reg_005);
		}
		dev5_reg_00F = dev5_regs.dev5_reg_00F;
		reg005_fmp1 = dev5_regs.dev5_reg_005;
		if ( (reg005_fmp1 & 0xC0) != 64 || cdvdman_istruct.read2_flag || (result = 2, (unsigned int)dev5_reg_00F - 1 < 4) )
		{
			while ( 1 )
			{
				do
				{
					vDelayThread(2000);
					WaitEventFlag(cdvdman_intr_efid, 1u, 0, efbits);
					reg00F_tmp1 = dev5_regs.dev5_reg_00F;
					reg005_tmp2 = dev5_regs.dev5_reg_005;
					reg00F_tmp2 = reg00F_tmp1;
				}
				while ( (reg005_tmp2 & 0xC0) != 64 );
				if ( !cdvdman_istruct.read2_flag )
				{
					result = 2;
					if ( (unsigned int)(reg00F_tmp2 - 1) >= 4 )
					{
						break;
					}
				}
			}
		}
	}
	return result;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00403CC8) --------------------------------------------------------
int sceCdGetDiskType(void)
{
	int result; // $v0

	LOBYTE(result) = dev5_regs.dev5_reg_00F;
	return (unsigned __int8)result;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00403CDC) --------------------------------------------------------
int sceCdStatus(void)
{
	vu8 dev5_reg_00F; // $v1
	vu8 dev5_reg_00A; // $v0
	int reg_00A_tmp; // $s0
	int reg_00A_band_1Eh_tmp; // $v0
	bool condtmp; // dc
	int reg_00A_tmp2; // $v1
	int result; // $v0
	u8 rdata_tmp[4]; // [sp+10h] [-8h] BYREF
	u32 status_tmp; // [sp+14h] [-4h] BYREF

	dev5_reg_00F = dev5_regs.dev5_reg_00F;
	dev5_reg_00A = dev5_regs.dev5_reg_00A;
	reg_00A_tmp = dev5_reg_00A;
	if ( !dev5_reg_00F )
	{
		reg_00A_band_1Eh_tmp = dev5_reg_00A & 0x1E;
		if ( !cdvdman_istruct.tray_is_open )
		{
			condtmp = cdvdman_scmd_sender_03_48(rdata_tmp, &status_tmp) != 1;
			reg_00A_band_1Eh_tmp = reg_00A_tmp & 0x1E;
			if ( !condtmp )
			{
				reg_00A_band_1Eh_tmp = reg_00A_tmp & 0x1E;
				if ( !status_tmp )
				{
					reg_00A_tmp &= 0xFEu;
					if ( (rdata_tmp[0] & 8) != 0 )
					{
						reg_00A_tmp |= 1u;
					}
					reg_00A_band_1Eh_tmp = reg_00A_tmp & 0x1E;
				}
			}
		}
		reg_00A_tmp2 = 0;
		if ( !reg_00A_band_1Eh_tmp )
		{
			reg_00A_tmp2 = reg_00A_tmp;
		}
		reg_00A_tmp = reg_00A_tmp2;
	}
	if ( cdvdman_istruct.use_toc )
	{
		reg_00A_tmp &= ~1u;
	}
	result = reg_00A_tmp;
	if ( cdvdman_istruct.power_flag )
	{
		return -1;
	}
	return result;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00403DB4) --------------------------------------------------------
sceCdlLOCCD *__cdecl sceCdIntToPos(u32 i, sceCdlLOCCD *p)
{
	s32 i_plus_150; // $a0
	sceCdlLOCCD *result; // $v0

	i_plus_150 = i + 150;
	result = p;
	p->sector = 16 * (i_plus_150 % 75 / 10) + i_plus_150 % 75 % 10;
	p->second = 16 * (i_plus_150 / 75 % 60 / 10) + i_plus_150 / 75 % 60 % 10;
	p->minute = 16 * (i_plus_150 / 75 / 60 / 10) + i_plus_150 / 75 / 60 % 10;
	return result;
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
	char *rdstart; // $a3
	char *rdstackptr1; // $t0
	int rdpos; // $a1
	unsigned int i; // $t1
	int *ptr1; // $a2
	unsigned int rdind1; // $v1
	char rdtmp1; // $v0
	int *rdstackptr2; // $a2
	unsigned int rdind2; // $v1
	char rdtmp2; // $v0
	struct
	{
		char m_unk10; // [sp+10h] [-88h] BYREF
		int m_unk18; // [sp+18h] [-80h]
		int m_unk1c; // [sp+1Ch] [-7Ch]
		int m_unk3c; // [sp+3Ch] [-5Ch]
		int m_unk90[2]; // [sp+90h] [-8h] BYREF
	} rdstack;

	rdstart = (char *)0xBFBF0000;
	rdstackptr1 = (char *)&rdstack;
	rdpos = 0;
	for ( i = 0; i < 0x20; ++i )
	{
		ptr1 = rdstack.m_unk90;
		rdind1 = 0;
		do
		{
			++rdind1;
			rdtmp1 = *rdstart++;
			*rdstackptr1++ = rdtmp1;
			*(_BYTE *)ptr1 = rdtmp1;
			ptr1 = (int *)((char *)ptr1 + 1);
		}
		while ( rdind1 < 4 );
		rdpos += rdstack.m_unk90[0];
	}
	for ( ; i < 0x4000; rdpos += rdstack.m_unk90[0] )
	{
		rdstackptr2 = rdstack.m_unk90;
		rdind2 = 0;
		do
		{
			++rdind2;
			rdtmp2 = *rdstart++;
			*(_BYTE *)rdstackptr2 = rdtmp2;
			rdstackptr2 = (int *)((char *)rdstackptr2 + 1);
		}
		while ( rdind2 < 4 );
		++i;
	}
	if ( rdpos )
	{
		Kprintf("# checksum error %d\n", rdpos);
		return 0;
	}
	else
	{
		if ( mode )
		{
			*buf = rdstack.m_unk3c;
		}
		else
		{
			*buf = rdstack.m_unk18;
			buf[1] = rdstack.m_unk1c;
		}
		return 1;
	}
}

//----- (0040403C) --------------------------------------------------------
int __cdecl query_boot_mode_6_nonzero()
{
	int *BootMode; // $v0
	int boot_mode_6_mask; // $v1
	int result; // $v0

	BootMode = QueryBootMode(6);
	if ( !BootMode )
	{
		return 0;
	}
	boot_mode_6_mask = *(_WORD *)BootMode & 0xFFFC;
	result = 1;
	if ( boot_mode_6_mask != 96 )
	{
		return 0;
	}
	return result;
}

//----- (0040407C) --------------------------------------------------------
int __cdecl query_boot_mode_6_zero()
{
	return QueryBootMode(6) == 0;
}

//----- (0040409C) --------------------------------------------------------
int __cdecl cdvdman_readID(int mode, int *buf)
{
	int result; // $v0
	bool condtmp; // dc
	u8 id_val[8]; // [sp+10h] [-18h] BYREF
	iop_sys_clock_t sysclk; // [sp+18h] [-10h] BYREF
	u32 id_result[2]; // [sp+20h] [-8h] BYREF

	id_result[0] = -1;
	if ( query_boot_mode_6_nonzero() )
	{
		result = read_id_from_rom(mode, buf);
		if ( result == 1 && mode == 1 )
		{
			if ( *buf == -1 )
			{
				*buf = 0x1A0002;
			}
			return 1;
		}
	}
	else
	{
		if ( query_boot_mode_6_zero() )
		{
			condtmp = sceCdRI(id_val, id_result) == 0;
			result = 0;
			if ( condtmp )
			{
				return result;
			}
			result = 0;
			if ( id_result[0] )
			{
				return result;
			}
		}
		else
		{
			if ( !readid_systemtime.lo && !readid_systemtime.hi )
			{
				GetSystemTime(&sysclk);
				readid_systemtime = sysclk;
			}
			*(iop_sys_clock_t *)id_val = readid_systemtime;
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
	return result;
}
// 40E588: using guessed type iop_sys_clock_t readid_systemtime;

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
	devctl_req.cmdid = 5;
	devctl_req.posszarg1 = bufmax;
	devctl_req.posszarg2 = bankmax;
	devctl_req.buffer = buffer;
	if ( devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u) < 0 )
	{
		return 0;
	}
	return buf;
}

//----- (004042C8) --------------------------------------------------------
int __cdecl sceCdStStart(u32 lbn, sceCdRMode *mode)
{
	u8 trycount; // $v1
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.rmode.datapattern = mode->datapattern;
	devctl_req.rmode.spindlctrl = mode->spindlctrl;
	trycount = mode->trycount;
	devctl_req.cmdid = 1;
	devctl_req.posszarg1 = lbn;
	devctl_req.rmode.trycount = trycount;
	if ( devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u) < 0 )
	{
		return 0;
	}
	return buf;
}

//----- (00404360) --------------------------------------------------------
int __cdecl sceCdStSeekF(unsigned int lsn)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.cmdid = 9;
	devctl_req.posszarg1 = lsn;
	if ( devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u) < 0 )
	{
		return 0;
	}
	return buf;
}

//----- (004043D4) --------------------------------------------------------
int __cdecl sceCdStSeek(u32 lbn)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.posszarg1 = lbn;
	devctl_req.cmdid = 4;
	if ( devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u) < 0 )
	{
		return 0;
	}
	return buf;
}

//----- (00404444) --------------------------------------------------------
int sceCdStStop(void)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.cmdid = 3;
	if ( devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u) < 0 )
	{
		return 0;
	}
	return buf;
}

//----- (004044AC) --------------------------------------------------------
int __cdecl sceCdStRead(u32 sectors, u32 *buffer, u32 mode, u32 *error)
{
	int devctl_res; // $v0
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.cmdid = 1;
	devctl_req.posszarg2 = sectors;
	devctl_req.buffer = buffer;
	devctl_res = devctl("cdrom_stm0:", 17300, &devctl_req, 0x18u, &buf, 4u);
	*error = devctl_req.error;
	if ( devctl_res < 0 )
	{
		return 0;
	}
	return buf;
}

//----- (00404540) --------------------------------------------------------
int sceCdStPause(void)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.cmdid = 7;
	if ( devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u) < 0 )
	{
		return 0;
	}
	return buf;
}

//----- (004045A8) --------------------------------------------------------
int sceCdStResume(void)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.cmdid = 8;
	if ( devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u) < 0 )
	{
		return 0;
	}
	return buf;
}

//----- (00404610) --------------------------------------------------------
int sceCdStStat(void)
{
	cdrom_stm_devctl_t devctl_req; // [sp+18h] [-20h] BYREF
	int buf; // [sp+30h] [-8h] BYREF

	memset(&devctl_req, 0, sizeof(devctl_req));
	devctl_req.cmdid = 6;
	if ( devctl("cdrom_stm0:", 17299, &devctl_req, 0x18u, &buf, 4u) < 0 )
	{
		return 0;
	}
	return buf;
}

//----- (00404680) --------------------------------------------------------
int __cdecl CdSearchFileInner(CDVDMAN_FILETBL_ENTRY_T *fp, const char *name, int layer)
{
	int result; // $v0
	int parent_level; // $a0
	const char *nameptr1; // $s0
	int path_level; // $s2
	int name_chr1; // $v0
	int name_chr2; // $v1
	char *nameptr2; // $s1
	u32 condtmp2; // $v0
	bool condtmp1; // dc
	int pathcnt; // $s2
	CDVDMAN_FILETBL_ENTRY_T *filetbl; // $s3
	char *filename; // $s0
	int filetblind; // $s1
	CDVDMAN_FILETBL_ENTRY_T *fptmp1; // $v1
	CDVDMAN_FILETBL_ENTRY_T *filetbltmp1; // $v0
	u32 size; // $t1
	int namecpytmp1; // $t2
	int namecpytmp2; // $t3
	char name_buf[32]; // [sp+10h] [-20h] BYREF

	if ( cdvdman_verbose > 0 )
	{
		printf("CdSearchFile: start name= %s layer= %d\n", name, layer);
	}
	if ( cdvdman_fs_layer != layer )
	{
		cdvdman_fs_cache = 0;
	}
	if ( !cdvdman_mediactl(0) && cdvdman_fs_cache )
	{
		if ( cdvdman_verbose > 0 )
		{
			Kprintf("CdSearchFile: cache dir data used\n");
		}
	}
	else
	{
		if ( cdvdman_verbose > 0 )
		{
			printf("CdSearchFile Topen= %s\n", name);
		}
		if ( !CD_newmedia(layer) )
		{
			cdvdman_fs_cache = 0;
			return 0;
		}
		cdvdman_fs_cache = 1;
	}
	result = 0;
	if ( *name == 92 )
	{
		name_buf[0] = 0;
		parent_level = 1;
		nameptr1 = name;
		path_level = 0;
		while ( 1 )
		{
			name_chr1 = *nameptr1;
			name_chr2 = *(unsigned __int8 *)nameptr1;
			nameptr2 = name_buf;
			if ( name_chr1 != 92 )
			{
				break;
			}
LABEL_22:
			condtmp1 = name_chr1 == 0;
			condtmp2 = path_level < 8;
			if ( condtmp1 )
			{
				goto LABEL_26;
			}
			++nameptr1;
			*nameptr2 = 0;
			parent_level = cdvdman_finddir(parent_level, name_buf);
			if ( parent_level == -1 )
			{
				name_buf[0] = 0;
LABEL_25:
				condtmp2 = path_level < 8;
				goto LABEL_26;
			}
			if ( ++path_level >= 8 )
			{
				goto LABEL_25;
			}
		}
		while ( 1 )
		{
			condtmp2 = path_level < 8;
			if ( !name_chr2 )
			{
				break;
			}
			++nameptr1;
			*nameptr2 = name_chr2;
			name_chr2 = *(unsigned __int8 *)nameptr1;
			++nameptr2;
			if ( *nameptr1 == 92 )
			{
				name_chr1 = *nameptr1;
				goto LABEL_22;
			}
		}
LABEL_26:
		if ( condtmp2 )
		{
			if ( name_buf[0] )
			{
				*nameptr2 = 0;
				if ( !CD_cachefile(parent_level, layer) )
				{
					result = 0;
					if ( cdvdman_verbose > 0 )
					{
						printf("CdSearchFile: disc error\n");
						return 0;
					}
					return result;
				}
				pathcnt = 0;
				if ( cdvdman_verbose >= 2 )
				{
					printf("CdSearchFile: searching %s...\n", name_buf);
					pathcnt = 0;
				}
				filetbl = cdvdman_filetbl;
				filename = cdvdman_filetbl[0].file_struct.name;
				filetblind = 0;
				do
				{
					if ( !cdvdman_filetbl[filetblind].file_struct.name[0] )
					{
						break;
					}
					if ( cdvdman_verbose > 0 )
					{
						printf("%d %s %s\n", pathcnt, filename, name_buf);
					}
					if ( cdvdman_cmpname(filename, name_buf) )
					{
						if ( cdvdman_verbose >= 2 )
						{
							printf("%s:\t found\n", name_buf);
						}
						fptmp1 = fp;
						filetbltmp1 = filetbl;
						do
						{
							size = filetbltmp1->file_struct.size;
							namecpytmp1 = *(_DWORD *)filetbltmp1->file_struct.name;
							namecpytmp2 = *(_DWORD *)&filetbltmp1->file_struct.name[4];
							fptmp1->file_struct.lsn = filetbltmp1->file_struct.lsn;
							fptmp1->file_struct.size = size;
							*(_DWORD *)fptmp1->file_struct.name = namecpytmp1;
							*(_DWORD *)&fptmp1->file_struct.name[4] = namecpytmp2;
							filetbltmp1 = (CDVDMAN_FILETBL_ENTRY_T *)((char *)filetbltmp1 + 16);
							fptmp1 = (CDVDMAN_FILETBL_ENTRY_T *)((char *)fptmp1 + 16);
						}
						while ( filetbltmp1 != (CDVDMAN_FILETBL_ENTRY_T *)&filetbl->file_properties );
						fptmp1->file_struct.lsn = filetbltmp1->file_struct.lsn;
						if ( layer )
						{
							fp->file_struct.lsn += cdvdman_fs_base2;
						}
						return 1;
					}
					++filetbl;
					filename += 36;
					++pathcnt;
					++filetblind;
				}
				while ( pathcnt < 64 );
				if ( cdvdman_verbose > 0 )
				{
					printf("%s: not found\n", name_buf);
				}
			}
			else if ( cdvdman_verbose > 0 )
			{
				printf("%s: dir was not found\n", name);
			}
		}
		else if ( cdvdman_verbose > 0 )
		{
			printf("%s: path level (%d) error\n", name, path_level);
			return 0;
		}
		return 0;
	}
	return result;
}

//----- (00404A68) --------------------------------------------------------
int __cdecl sceCdSearchDir(char *dirname, int layer)
{
	bool condtmp; // dc
	int result; // $v0
	sceCdlFILE fileinfo; // [sp+10h] [-28h] BYREF

	if ( cdvdman_verbose > 0 )
	{
		printf("_sceCdSearchDir: dir name %s layer %d\n", dirname, layer);
	}
	condtmp = sceCdLayerSearchFile(&fileinfo, dirname, layer) == 0;
	result = -2;
	if ( !condtmp )
	{
		return cdvdman_fs_cdsec;
	}
	return result;
}
// 404A68: using guessed type sceCdlFILE fileinfo;

//----- (00404AD4) --------------------------------------------------------
int __cdecl sceCdReadDir(sceCdlFILE *fp, int dsec, int index, int layer)
{
	int index_mul_8; // $v0
	int dsec_tmp; // $a0
	bool condtmp; // dc
	int result; // $v0
	int dir_point; // $s0
	sceCdlFILE *cdf; // $a0
	char *filetbl_offs; // $v0
	u32 cpytmp1; // $t1
	int cpytmp2; // $t2
	int cpytmp3; // $t3

	if ( cdvdman_verbose > 0 )
	{
		printf("_sceCdReadDir: current= %d dsec= %d layer= %d\n", cdvdman_fs_cdsec, dsec, layer);
	}
	if ( cdvdman_fs_cdsec != dsec || (index_mul_8 = 8 * index, cdvdman_fs_layer != layer) )
	{
		dsec_tmp = dsec;
		if ( cdvdman_fs_layer != layer )
		{
			if ( !CD_newmedia(layer) )
			{
				return -2;
			}
			cdvdman_fs_cache = 1;
			dsec_tmp = dsec;
		}
		condtmp = CD_cachefile(dsec_tmp, layer) != 0;
		index_mul_8 = 8 * index;
		if ( !condtmp )
		{
			return -2;
		}
	}
	dir_point = 4 * (index_mul_8 + index);
	result = 0;
	if ( cdvdman_filetbl[0].file_struct.name[dir_point] )
	{
		if ( cdvdman_verbose > 0 )
		{
			printf("%s:\t found dir_point %d\n", &cdvdman_filetbl[0].file_struct.name[dir_point], index);
		}
		cdf = fp;
		filetbl_offs = (char *)cdvdman_filetbl + dir_point;
		do
		{
			cpytmp1 = *((_DWORD *)filetbl_offs + 1);
			cpytmp2 = *((_DWORD *)filetbl_offs + 2);
			cpytmp3 = *((_DWORD *)filetbl_offs + 3);
			cdf->lsn = *(_DWORD *)filetbl_offs;
			cdf->size = cpytmp1;
			*(_DWORD *)cdf->name = cpytmp2;
			*(_DWORD *)&cdf->name[4] = cpytmp3;
			filetbl_offs += 16;
			cdf = (sceCdlFILE *)((char *)cdf + 16);
		}
		while ( filetbl_offs != (char *)&cdvdman_filetbl[0].file_properties + dir_point );
		cdf->lsn = *(_DWORD *)filetbl_offs;
		return 1;
	}
	return result;
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
	int result; // $v0
	unsigned int pathtblsize_tmp; // $a0
	unsigned int pathtblind; // $a1
	CDVDMAN_PATHTBL_T *pathtbl_cur; // $v1
	char *fs_rbuf_cur; // $s1
	int dirind1; // $a1
	int dirind2; // $s0
	int parent_name; // $v0
	int dirind3; // $s3
	int state; // [sp+18h] [-8h] BYREF
	int ptsector; // [sp+1Ch] [-4h]

	ptsector = 0;
	DiskType = sceCdGetDiskType();
	if ( DiskType != 20
		&& DiskType != 18
		&& DiskType != 19
		&& DiskType != 16
		&& DiskType != 17
		&& DiskType != 255
		&& DiskType != 254
		&& DiskType != 252 )
	{
		if ( cdvdman_verbose > 0 )
		{
			printf("CD_newmedia: Illegal disc media type =%d\n", DiskType);
		}
		return 0;
	}
	cdvdman_fs_base2 = 0;
	if ( DiskType == 20 )
	{
		if ( !DvdDual_infochk() )
		{
			result = 0;
			if ( cdvdman_verbose > 0 )
			{
				printf("CD_newmedia: Get DvdDual_infochk fail\n");
				return 0;
			}
			return result;
		}
		if ( arg )
		{
			cdvdman_fs_base2 = cdvdman_istruct.layer_1_lsn;
		}
		else
		{
			cdvdman_fs_base2 = 0;
		}
	}
	if ( disc_read(1, cdvdman_fs_base2 + 16, cdvdman_fs_rbuf, arg) != 1 )
	{
		result = 0;
		if ( cdvdman_verbose > 0 )
		{
			printf("CD_newmedia: Read error in disc_read(PVD)\n");
			return 0;
		}
		return result;
	}
	CpuSuspendIntr(&state);
	pathtblsize_tmp = cdvdman_pathtblsize;
	pathtblind = 0;
	if ( cdvdman_pathtblsize )
	{
		pathtbl_cur = cdvdman_pathtbl;
		do
		{
			pathtbl_cur->cache_hit_count = 0;
			pathtbl_cur->layer = 0;
			pathtbl_cur->nsec = 0;
			pathtbl_cur->lsn = 0;
			pathtbl_cur->cache_path_sz = 0;
			++pathtblind;
			++pathtbl_cur;
		}
		while ( pathtblind < pathtblsize_tmp );
	}
	cache_count = 0;
	cache_table = 0;
	cache_path_size = 0;
	CpuResumeIntr(state);
	if ( strncmp(&cdvdman_fs_rbuf[1], "CD001", 5) )
	{
		result = 0;
		if ( cdvdman_verbose > 0 )
		{
			printf("CD_newmedia: Disc format error in cd_read(PVD)\n");
			return 0;
		}
		return result;
	}
	if ( DiskType == 20 )
	{
		goto LABEL_31;
	}
	if ( DiskType < 0x15 )
	{
		if ( cdvdman_verbose > 0 )
		{
			printf("CD_newmedia: CD Read mode\n");
		}
		ptsector = *(_DWORD *)&cdvdman_fs_rbuf[140];
		goto LABEL_37;
	}
	if ( DiskType == 252 || DiskType == 254 )
	{
LABEL_31:
		if ( cdvdman_verbose > 0 )
		{
			printf("CD_newmedia: DVD Read mode\n");
		}
		ptsector = 257;
	}
LABEL_37:
	if ( disc_read(1, cdvdman_fs_base2 + ptsector, cdvdman_fs_rbuf, arg) != 1 )
	{
		result = 0;
		if ( cdvdman_verbose <= 0 )
		{
			return result;
		}
		printf("CD_newmedia: Read error (PT:%08x)\n", ptsector);
		return 0;
	}
	fs_rbuf_cur = cdvdman_fs_rbuf;
	if ( cdvdman_verbose >= 2 )
	{
		printf("CD_newmedia: sarching dir..\n");
	}
	dirind1 = 0;
	if ( cdvdman_fs_rbuf < cdvdman_end_fs_rbuf )
	{
		while ( *fs_rbuf_cur )
		{
			dirind2 = dirind1;
			cdvdman_dirtbl[dirind2].extent = *(_DWORD *)(fs_rbuf_cur + 2);
			parent_name = (unsigned __int8)fs_rbuf_cur[6];
			dirind3 = dirind1 + 1;
			cdvdman_dirtbl[dirind2].number = dirind1 + 1;
			cdvdman_dirtbl[dirind2].parent = parent_name;
			memcpy(cdvdman_dirtbl[dirind1].name, fs_rbuf_cur + 8, (unsigned __int8)*fs_rbuf_cur);
			cdvdman_dirtbl[0].name[(unsigned __int8)*fs_rbuf_cur + dirind2 * 44] = 0;
			fs_rbuf_cur += (unsigned __int8)*fs_rbuf_cur + (*fs_rbuf_cur & 1) + 8;
			if ( cdvdman_verbose >= 2 )
			{
				printf(
					"\t%08x,%04x,%04x,%s\n",
					cdvdman_dirtbl[dirind2].extent,
					cdvdman_dirtbl[dirind2].number,
					cdvdman_dirtbl[dirind2].parent,
					cdvdman_dirtbl[dirind2].name);
			}
			dirind1 = dirind3;
			if ( dirind3 >= 128 )
			{
				goto LABEL_51;
			}
			if ( fs_rbuf_cur >= cdvdman_end_fs_rbuf )
			{
				break;
			}
		}
	}
	if ( dirind1 < 128 )
	{
		cdvdman_dirtbl[dirind1].parent = 0;
	}
LABEL_51:
	cdvdman_fs_cdsec = 0;
	cdvdman_fs_layer = arg;
	result = 1;
	if ( cdvdman_verbose >= 2 )
	{
		printf("CD_newmedia: %d dir entries found\n", dirind1);
		return 1;
	}
	return result;
}
// 404EA0: conditional instruction was optimized away because $s0.4 is in (10..13)

//----- (00405168) --------------------------------------------------------
int __fastcall cdvdman_finddir(int target_parent, const char *target_name)
{
	int i; // $s0
	char *name; // $s2
	int j; // $s1
	int parent; // $v0
	int cmpres; // $v0

	i = 0;
	name = cdvdman_dirtbl[0].name;
	j = 0;
	do
	{
		parent = cdvdman_dirtbl[j].parent;
		if ( !parent )
		{
			break;
		}
		if ( parent == target_parent )
		{
			cmpres = strcmp(target_name, name);
			name += 44;
			if ( !cmpres )
			{
				return i + 1;
			}
		}
		else
		{
			name += 44;
		}
		++i;
		++j;
	}
	while ( i < 128 );
	return -1;
}

//----- (0040520C) --------------------------------------------------------
int __fastcall CD_cachefile(int dsec, int layer)
{
	struct dirTocEntry *toc1; // $s0
	int result; // $v0
	int filecnt; // $s3
	u32 *sizeptr1; // $t1
	u8 *date1ptr; // $t0
	u8 *date2ptr; // $v1
	u8 *date3ptr; // $fp
	u8 *date4ptr; // $s7
	u8 *date5ptr; // $s6
	char *nameptr; // $s5
	CDVDMAN_FILETBL_ENTRY_T *filetble; // $s4
	int filetbli; // $s2
	int file_year; // $s1
	u32 loc; // [sp+30h] [-18h]
	u32 *sizeptr2; // [sp+34h] [-14h]
	u8 *date2ptrtmp1; // [sp+38h] [-10h]
	u8 *date2ptrtmp2; // [sp+38h] [-10h]
	u8 *date1ptrtmp1; // [sp+3Ch] [-Ch]
	u8 *date1ptrtmp2; // [sp+3Ch] [-Ch]
	u32 *sizeptr1tmp1; // [sp+40h] [-8h]
	u32 *sizeptr1tmp2; // [sp+40h] [-8h]

	if ( dsec == cdvdman_fs_cdsec )
	{
		return 1;
	}
	if ( layer )                                  // This actually accesses cdvdman_dirtbl
	{
		loc = cdvdman_fs_base2 + *(&cdvdman_filetbl[63].file_struct.lsn + 11 * dsec);
	}
	else
	{
		loc = *(&cdvdman_filetbl[63].file_struct.lsn + 11 * dsec);
	}
	toc1 = (struct dirTocEntry *)cdvdman_fs_rbuf;
	if ( disc_read(1, loc, cdvdman_fs_rbuf, layer) != 1 )
	{
		if ( cdvdman_verbose > 0 )
		{
			printf("CD_cachefile: dir not found\n");
		}
		cdvdman_fs_cdsec = 0;
		return 0;
	}
	if ( cdvdman_verbose >= 2 )
	{
		printf("CD_cachefile: searching...\n");
	}
	filecnt = 0;
	if ( cdvdman_fs_rbuf < cdvdman_end_fs_rbuf )
	{
		sizeptr1 = &cdvdman_filetbl[0].file_struct.size;
		date1ptr = &cdvdman_filetbl[0].file_struct.date[1];
		date2ptr = &cdvdman_filetbl[0].file_struct.date[2];
		date3ptr = &cdvdman_filetbl[0].file_struct.date[3];
		date4ptr = &cdvdman_filetbl[0].file_struct.date[4];
		date5ptr = &cdvdman_filetbl[0].file_struct.date[5];
		nameptr = cdvdman_filetbl[0].file_struct.name;
		filetble = cdvdman_filetbl;
		filetbli = 0;
		sizeptr2 = &cdvdman_filetbl[0].file_struct.size;
		do
		{
			if ( !LOBYTE(toc1->length) )
			{
				break;
			}
			filetble->file_struct.lsn = toc1->fileLBA;
			*sizeptr2 = toc1->fileSize;
			file_year = toc1->dateStamp[0] + 1900;
			cdvdman_filetbl[filetbli].file_struct.date[7] = BYTE1(file_year);
			cdvdman_filetbl[filetbli].file_struct.date[6] = file_year;
			*date5ptr = toc1->dateStamp[1];
			*date4ptr = toc1->dateStamp[2];
			*date3ptr = toc1->dateStamp[3];
			*date2ptr = toc1->dateStamp[4];
			*date1ptr = toc1->dateStamp[5];
			cdvdman_filetbl[filetbli].file_properties = toc1->fileProperties;
			if ( filecnt )
			{
				if ( filecnt == 1 )
				{
					strcpy((char *)sizeptr1 + 40, "..");
				}
				else
				{
					date2ptrtmp1 = date2ptr;
					date1ptrtmp1 = date1ptr;
					sizeptr1tmp1 = sizeptr1;
					memcpy(nameptr, toc1->filename, toc1->filenameLength);
					cdvdman_filetbl[filetbli].file_struct.name[toc1->filenameLength] = 0;
					sizeptr1 = sizeptr1tmp1;
					date1ptr = date1ptrtmp1;
					date2ptr = date2ptrtmp1;
				}
			}
			else
			{
				strcpy((char *)sizeptr1 + 4, ".");
			}
			if ( cdvdman_verbose >= 2 )
			{
				date2ptrtmp2 = date2ptr;
				date1ptrtmp2 = date1ptr;
				sizeptr1tmp2 = sizeptr1;
				printf(
					"\t lsn %d size %d name:%d:%s %d/%d/%d %d:%d:%d\n",
					filetble->file_struct.lsn,
					cdvdman_filetbl[filetbli].file_struct.size,
					toc1->filenameLength,
					nameptr,
					file_year,
					*date5ptr,
					*date4ptr,
					*date3ptr,
					*date2ptr,
					*date1ptr);
				sizeptr1 = sizeptr1tmp2;
				date1ptr = date1ptrtmp2;
				date2ptr = date2ptrtmp2;
			}
			date1ptr += 36;
			date2ptr += 36;
			date3ptr += 36;
			date4ptr += 36;
			date5ptr += 36;
			nameptr += 36;
			++filetble;
			sizeptr2 += 9;
			++filecnt;
			toc1 = (struct dirTocEntry *)((char *)toc1 + LOBYTE(toc1->length));
			++filetbli;
			if ( filecnt >= 64 )
			{
				break;
			}
		}
		while ( toc1 < (struct dirTocEntry *)cdvdman_end_fs_rbuf );
	}
	cdvdman_fs_cdsec = dsec;
	if ( filecnt < 64 )
	{
		cdvdman_filetbl[filecnt].file_struct.name[0] = 0;
	}
	result = 1;
	if ( cdvdman_verbose >= 2 )
	{
		printf("CD_cachefile: %d files found\n", filecnt);
		return 1;
	}
	return result;
}

//----- (00405628) --------------------------------------------------------
int __cdecl disc_read(int size, int loc, void *buffer, int layer)
{
	int f; // $s6
	int pathcachecnt; // $s2
	int pathcachei; // $s0
	int pathcacheo; // $s1
	CDVDMAN_PATHTBL_T *pathcaches; // $v1
	int pathcachei2; // $s0
	bool condtmp; // dc
	int result; // $v0
	int cache_path_sz; // $s1
	int cachetblo1; // $a2
	unsigned int cachebli1; // $s0
	unsigned int cacheblo2; // $a1
	CDVDMAN_PATHTBL_T *cachebls1; // $a0
	int ptbl_wcache_write_res; // $a2
	CDVDMAN_PATHTBL_T *pathtbls2; // $v1
	unsigned int pathtblsz1; // $a1
	unsigned int cachecnt1; // $v1
	CDVDMAN_PATHTBL_T *pathtbls1; // $v0
	int Error; // $v0
	sceCdRMode rmode[2]; // [sp+20h] [-8h] BYREF

	f = 0;
	rmode[0].trycount = 16;
	if ( cdvdman_verbose > 0 )
	{
		printf("cd_read:lsn= %d size= %d layer= %d\n", loc, size, layer);
	}
	if ( cdvdman_l0check(layer) )
	{
		cdvdman_srchspd = 0;
	}
	if ( cdvdman_srchspd == 2 )
	{
		goto LABEL_10;
	}
	if ( cdvdman_srchspd < 3 )
	{
		rmode[0].spindlctrl = cdvdman_srchspd != 0;
		goto LABEL_12;
	}
	if ( cdvdman_srchspd == 3 || cdvdman_srchspd == 4 )
	{
LABEL_10:
		rmode[0].spindlctrl = cdvdman_srchspd;
	}
	else
	{
		rmode[0].spindlctrl = 1;
	}
LABEL_12:
	rmode[0].datapattern = 0;
	if ( !cdvdman_pathtblflag )
	{
		goto LABEL_50;
	}
	pathcachecnt = cdvdman_pathtblsize;
	if ( cache_count < (unsigned int)cdvdman_pathtblsize )
	{
		pathcachecnt = cache_count;
	}
	pathcachei = 0;
	if ( pathcachecnt > 0 )
	{
		pathcacheo = 0;
		do
		{
			if ( cdvdman_verbose > 0 )
			{
				Kprintf(
					"Path table Cache Search lsn:%d:%d nsec:%d:%d layer%d:%d\n",
					cdvdman_pathtbl[pathcacheo].lsn,
					loc,
					cdvdman_pathtbl[pathcacheo].nsec,
					size,
					cdvdman_pathtbl[pathcacheo].layer,
					layer);
			}
			pathcaches = &cdvdman_pathtbl[pathcacheo];
			if ( cdvdman_pathtbl[pathcacheo].lsn == loc && pathcaches->nsec == size && pathcaches->layer == layer )
			{
				break;
			}
			++pathcachei;
			++pathcacheo;
		}
		while ( pathcachei < pathcachecnt );
	}
	if ( pathcachei != pathcachecnt )
	{
		if ( cdvdman_verbose > 0 )
		{
			Kprintf("Path table Cache ON:%d\n", cdvdman_pathtbl[pathcachei].cache_path_sz);
		}
		pathcachei2 = pathcachei;
		if ( lseek(cache_path_fd, cdvdman_pathtbl[pathcachei2].cache_path_sz, 0) >= 0 )
		{
			read(cache_path_fd, buffer, size << 11);
			f = 1;
			++cdvdman_pathtbl[pathcachei2].cache_hit_count;
		}
		goto LABEL_50;
	}
	condtmp = sceCdRE(loc, size, buffer, rmode) == 0;
	result = 0;
	if ( condtmp )
	{
		return result;
	}
	sceCdSync(3);
	if ( !sceCdGetError() )
	{
		if ( cache_count >= (unsigned int)cdvdman_pathtblsize )
		{
			if ( ++cache_table >= (unsigned int)cdvdman_pathtblsize )
			{
				cache_table = 0;
			}
			cachetblo1 = cache_table;
			cachebli1 = 0;
			cacheblo2 = cache_table;
			if ( cache_count )
			{
				cachebls1 = &cdvdman_pathtbl[cache_table];
				do
				{
					if ( cacheblo2 >= cdvdman_pathtblsize )
					{
						cachebls1 = cdvdman_pathtbl;
						cacheblo2 = 0;
					}
					if ( cachebls1->nsec >= (unsigned int)size
						&& cachebls1->cache_hit_count < (unsigned int)cdvdman_pathtbl[cachetblo1].cache_hit_count )
					{
						cachetblo1 = cacheblo2;
					}
					++cachebli1;
					++cachebls1;
					++cacheblo2;
				}
				while ( cachebli1 < cache_count );
			}
			cache_table = cachetblo1;
			cache_path_sz = cdvdman_pathtbl[cachetblo1].cache_path_sz;
		}
		else
		{
			cache_path_sz = cache_path_size;
			cache_table = cache_count++;
		}
		if ( lseek(cache_path_fd, cache_path_sz, 0) >= 0 )
		{
			ptbl_wcache_write_res = write(cache_path_fd, buffer, size << 11);
			if ( ptbl_wcache_write_res == size << 11 )
			{
				f = 1;
				pathtblsz1 = cdvdman_pathtblsize;
				cachecnt1 = cache_count;
				pathtbls1 = &cdvdman_pathtbl[cache_table];
				pathtbls1->cache_path_sz = cache_path_sz;
				pathtbls1->lsn = loc;
				pathtbls1->nsec = size;
				pathtbls1->layer = layer;
				pathtbls1->cache_hit_count = 0;
				if ( cachecnt1 < pathtblsz1 )
				{
					cache_path_size += ptbl_wcache_write_res;
				}
			}
			else
			{
				if ( cdvdman_verbose > 0 )
				{
					Kprintf("Ptbl_WCache:write %d", ptbl_wcache_write_res);
				}
				pathtbls2 = &cdvdman_pathtbl[cache_table];
				pathtbls2->cache_hit_count = 0;
				pathtbls2->layer = 0;
				pathtbls2->nsec = 0;
				pathtbls2->lsn = 0;
			}
		}
LABEL_50:
		result = size;
		if ( f )
		{
			return result;
		}
		condtmp = sceCdRE(loc, size, buffer, rmode) == 0;
		result = 0;
		if ( condtmp )
		{
			return result;
		}
		sceCdSync(3);
		condtmp = sceCdGetError() == 0;
		result = size;
		if ( condtmp )
		{
			return result;
		}
	}
	if ( cdvdman_verbose > 0 )
	{
		Error = sceCdGetError();
		Kprintf("cd_read: error code %x\n", Error);
	}
	return 0;
}

//----- (00405B68) --------------------------------------------------------
int __cdecl path_tbl_init(u32 blocks, char *fname, int action)
{
	int num; // $s3
	int v; // $s1
	int result; // $v0
	int fd; // $v0
	bool condtmp1; // dc
	u32 condtmp2; // $v0
	u32 blocksi; // $s0
	u32 pathtbli1; // $s0
	CDVDMAN_PATHTBL_T *pathtbls1; // $v1
	char cachedir[512]; // [sp+18h] [-208h] BYREF
	int state; // [sp+218h] [-8h] BYREF
	u32 blocksbs; // [sp+21Ch] [-4h] BYREF

	num = 0;
	v = 0;
	if ( action )
	{
		CpuSuspendIntr(&state);
		cdvdman_pathtbl = (CDVDMAN_PATHTBL_T *)AllocSysMemory(1, 20 * blocks, 0);
		if ( !cdvdman_pathtbl )
		{
			CpuResumeIntr(state);
			cdvdman_pathtblflag = 0;
			return -12;
		}
		CpuResumeIntr(state);
		sprintf(cachedir, "%sCache_Path", fname);
		fd = open(cachedir, 1539, 511);
		v = fd;
		if ( fd >= 0 )
		{
			cache_path_fd = fd;
			condtmp1 = strncmp(cachedir, "pfs", 3) != 0;
			condtmp2 = blocks != 0;
			if ( !condtmp1 )
			{
				blocksbs = blocks << 11;
				ioctl2(cache_path_fd, 28673, &blocksbs, 4u, 0, 0);
				condtmp2 = blocks != 0;
			}
			blocksi = 0;
			if ( !condtmp2 )
			{
LABEL_10:
				CpuSuspendIntr(&state);
				cdvdman_pathtblsize = blocks;
				pathtbli1 = 0;
				if ( blocks )
				{
					pathtbls1 = cdvdman_pathtbl;
					do
					{
						pathtbls1->cache_hit_count = 0;
						pathtbls1->layer = 0;
						pathtbls1->nsec = 0;
						pathtbls1->lsn = 0;
						pathtbls1->cache_path_sz = 0;
						++pathtbli1;
						++pathtbls1;
					}
					while ( pathtbli1 < blocks );
				}
				cache_path_size = 0;
				cache_count = 0;
				cache_table = 0;
				cdvdman_pathtblflag = 1;
				CpuResumeIntr(state);
				return 0;
			}
			while ( 1 )
			{
				v = write(cache_path_fd, cdvdman_fs_rbuf, 2048);
				++blocksi;
				if ( v < 0 )
				{
					break;
				}
				if ( blocksi >= blocks )
				{
					goto LABEL_10;
				}
			}
		}
	}
	if ( cache_path_fd != -1 )
	{
		num = close(cache_path_fd);
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
	cache_path_fd = -1;
	cache_count = 0;
	cache_table = 0;
	cache_path_size = 0;
	cdvdman_pathtblflag = 0;
	cdvdman_pathtblsize = 0;
	FreeSysMemory(cdvdman_pathtbl);
	cdvdman_pathtbl = 0;
	CpuResumeIntr(state);
	if ( v < 0 && cdvdman_verbose > 0 )
	{
		Kprintf("path_tbl_init Error %d\n", v);
	}
	result = v;
	if ( !action )
	{
		return num;
	}
	return result;
}

//----- (00405E60) --------------------------------------------------------
int __fastcall unused_40BA90(unsigned int *a1, int a2)
{
	int result; // $v0
	unsigned int v3; // $t7
	int v4; // $t1
	int v5; // $t0
	int v6; // $v1
	bool v7; // dc

	result = 0;
	do
	{
		v3 = *a1;
		v4 = 4;
		do
		{
			v5 = 8;
			v6 = (unsigned __int8)v3;
			do
			{
				v7 = result >= 0;
				result *= 2;
				if ( !v7 )
				{
					result ^= 0x80000011;
				}
				v7 = (v6 & 0x80) == 0;
				v6 *= 2;
				if ( !v7 )
				{
					result ^= 1u;
				}
				--v5;
			}
			while ( v5 );
			--v4;
			v3 >>= 8;
		}
		while ( v4 );
		a2 -= 4;
		++a1;
	}
	while ( a2 );
	return result;
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
int __fastcall hex_dump(u8 *addr_start, int length)
{
	int ind1; // $s0
	int ind2; // $v0
	int tmpbyte; // $a1

	Kprintf("Hex Dump addr %08x\n", addr_start);
	ind1 = 0;
	if ( length > 0 )
	{
		ind2 = 0;
		do
		{
			if ( !ind2 && ind1 )
			{
				printf("\n");
			}
			tmpbyte = addr_start[ind1++];
			Kprintf(" %02x", tmpbyte);
			ind2 = ind1 & 0xF;
		}
		while ( ind1 < length );
	}
	return Kprintf("\n");
}

//----- (004066A4) --------------------------------------------------------
int __cdecl cdvdman_initcfg()
{
	int count; // $s0
	int result; // $v0
	unsigned int mvored; // $s0
	u8 m_version[5]; // [sp+18h] [-18h] BYREF
	u32 eflag[2]; // [sp+28h] [-8h] BYREF

	count = 0;
	eflag[0] = 0;
	while ( !sceCdGetMVersion(m_version, eflag) && (eflag[0] & 0x80) != 0 )
	{
		result = 0;
		if ( count >= 101 )
		{
			return result;
		}
		vDelayThread(2000);
		++count;
		if ( cdvdman_verbose > 0 )
		{
			Kprintf("_sceCdMV error\n");
		}
	}
	mvored = m_version[3] | (m_version[2] << 8) | (m_version[1] << 16);
	cdvdman_emudvd9 = m_version[2] & 1;
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("MV %02x %02x %02x %02x\n", m_version[0], m_version[1], m_version[2], m_version[3]);
	}
	cdvdman_minver_10700 = mvored > 0x106FF;
	cdvdman_minver_20200 = mvored > 0x201FF;
	cdvdman_minver_20400 = mvored > 0x203FF;
	cdvdman_minver_20800 = mvored > 0x207FF;
	cdvdman_minver_50000 = mvored > 0x4FFFF;
	cdvdman_minver_50200 = mvored > 0x501FF;
	cdvdman_minver_50400 = mvored > 0x503FF;
	cdvdman_minver_50600 = mvored > 0x505FF;
	cdvdman_minver_x_model_15 = (mvored & 0xF) == 1;
	cdvdman_minver_60000 = mvored > 0x5FFFF;
	cdvdman_minver_60200 = mvored > 0x601FF;
	return 1;
}

//----- (0040694C) --------------------------------------------------------
int __fastcall vSetAlarm(iop_sys_clock_t *sys_clock, unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	if ( QueryIntrContext() )
	{
		return iSetAlarm(sys_clock, alarm_cb, arg);
	}
	else
	{
		return SetAlarm(sys_clock, alarm_cb, arg);
	}
}

//----- (004069B0) --------------------------------------------------------
int __fastcall vCancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	if ( QueryIntrContext() )
	{
		return iCancelAlarm(alarm_cb, arg);
	}
	else
	{
		return CancelAlarm(alarm_cb, arg);
	}
}

//----- (00406A00) --------------------------------------------------------
s32 __cdecl vSignalSema(s32 sema_id)
{
	if ( QueryIntrContext() )
	{
		return iSignalSema(sema_id);
	}
	else
	{
		return SignalSema(sema_id);
	}
}

//----- (00406A44) --------------------------------------------------------
int __fastcall vSetEventFlag(int ef, u32 bits)
{
	if ( QueryIntrContext() )
	{
		return iSetEventFlag(ef, bits);
	}
	else
	{
		return SetEventFlag(ef, bits);
	}
}

//----- (00406A94) --------------------------------------------------------
int __fastcall vClearEventFlag(int ef, u32 bits)
{
	if ( QueryIntrContext() )
	{
		return iClearEventFlag(ef, bits);
	}
	else
	{
		return ClearEventFlag(ef, bits);
	}
}

//----- (00406AE4) --------------------------------------------------------
int __fastcall vReferEventFlagStatus(int ef, iop_event_info_t *info)
{
	if ( QueryIntrContext() )
	{
		return iReferEventFlagStatus(ef, info);
	}
	else
	{
		return ReferEventFlagStatus(ef, info);
	}
}

//----- (00406B34) --------------------------------------------------------
int __fastcall vDelayThread(int usec)
{
	int intrval; // $s0
	bool condtmp; // dc
	int result; // $v0
	int state; // [sp+10h] [-8h] BYREF

	intrval = CpuSuspendIntr(&state);
	CpuResumeIntr(state);
	condtmp = QueryIntrContext() != 0;
	result = 0;
	if ( !condtmp && !intrval )
	{
		return DelayThread(usec);
	}
	return result;
}

//----- (00406B90) --------------------------------------------------------
BOOL __fastcall alarm_cb_read(iop_sys_clock_t *a1)
{
	int rdto[2]; // [sp+10h] [-8h] BYREF

	rdto[0] = a1->lo / 0x9000;
	Kprintf("Read Time Out %d(msec)\n", rdto[0]);
	sceCdSC(-18, rdto);
	return sceCdBreak() == 0;
}
// 406B90: using guessed type u32 rdto[2];

//----- (00406BE4) --------------------------------------------------------
sceCdCBFunc __cdecl sceCdCallback(sceCdCBFunc function)
{
	bool condtmp; // dc
	sceCdCBFunc result; // $v0
	void (__cdecl *rc)(int); // $s0
	u32 efbits[2]; // [sp+10h] [-8h] BYREF

	condtmp = sceCdSync(1) != 0;
	result = 0;
	if ( !condtmp )
	{
		condtmp = PollEventFlag(ncmd_evid, 1u, 16, efbits) == -421;
		result = 0;
		if ( !condtmp )
		{
			rc = cdvdman_user_cb;
			cdvdman_user_cb = function;
			vSetEventFlag(ncmd_evid, 1u);
			return rc;
		}
	}
	return result;
}

//----- (00406C64) --------------------------------------------------------
void *__cdecl sceCdPOffCallback(void (__cdecl *func)(void *), void *addr)
{
	int (__cdecl *old_cb)(void *); // $s1
	int state; // [sp+10h] [-8h] BYREF

	CpuSuspendIntr(&state);
	old_cb = cdvdman_poff_cb;
	cdvdman_poff_cb = (int (__cdecl *)(void *))func;
	cdvdman_poffarg = addr;
	CpuResumeIntr(state);
	return old_cb;
}

//----- (00406CC8) --------------------------------------------------------
int __cdecl sceCdstm0Cb(void (__cdecl *p)(int))
{
	cdvdman_cdstm0cb = p;
	return 0;
}

//----- (00406CD8) --------------------------------------------------------
int __cdecl sceCdstm1Cb(void (__cdecl *p)(int))
{
	cdvdman_cdstm1cb = p;
	return 0;
}

//----- (00406CE8) --------------------------------------------------------
int __fastcall cdvdman_intr_cb(cdvdman_internal_struct_t *s)
{
	int intr_ef; // $a0
	int last_error; // $a0
	int dec_mode_set; // $v0
	unsigned int read_chunk; // $v1
	int read_chunk_tmp; // $v0
	unsigned int read_lsn; // $v1
	int read_lsn_tmp; // $v0
	int read_sectors; // $a1
	int ncmd; // $v1
	int dintrlsn; // $v0
	int read_sectors_tmp; // $a0
	int read_chunk_reprocial_32; // $v1
	int recover_status_tmp; // $a1
	vu8 dev5_reg_013; // $v0
	char dev5_reg_013_masked; // $s1
	int last_error_tmp; // $v1
	int dec_mode_set_tmp; // $v0
	u8 datapattern; // $v1
	unsigned int recover_status; // $v1
	int rty_sec; // $a1
	int read_chunk_tmp1; // $v0
	bool read0_result; // dc
	int result; // $v0
	int read2_flag; // $v1
	int dec_state; // $v1
	int stream_flag; // $v1
	int cmdfunc_tmp; // $a0
	sceCdRMode cdrmode; // [sp+28h] [-10h] BYREF
	int oldstate; // [sp+30h] [-8h] BYREF

	intr_ef = cdvdman_intr_efid;
	s->wait_flag = s->waf_set_test;
	iSetEventFlag(intr_ef, 0x29u);
	DisableIntr(35, &oldstate);
	if ( *(_WORD *)&s->cdvdman_command == 12549 )
	{
		if ( sceCdStatus() == -1 )
		{
			s->last_error = 49;
		}
		else
		{
			s->last_error = 0;
		}
	}
	if ( s->last_error == 50 )
	{
		s->last_error = 0;
	}
	if ( cdvdman_verbose > 0 )
	{
		Kprintf(
			"Intr call func_num: %d Err= %02x OnTout= %d\n",
			cdvdman_cmdfunc,
			(unsigned __int8)s->last_error,
			s->read_to);
	}
	if ( !s->scmd_flag )
	{
		cdvdman_write_scmd(s);
	}
	last_error = (unsigned __int8)s->last_error;
	if ( (last_error == 48 && cdvdman_cmdfunc == 1 || last_error == 1 && s->read_to && cdvdman_last_cmdfunc == 1)
		&& !cdvdman_minver_20200
		&& !s->stream_flag
		&& !s->dvd_flag
		&& !s->recover_status
		&& s->read_mode.trycount != 1 )
	{
		dec_mode_set = s->dec_mode_set;
		s->sync_error = 0;
		s->interupt_read_state = 0;
		if ( dec_mode_set )
		{
			s->dec_mode_last_set = 1;
		}
		else
		{
			if ( cdvdman_verbose > 0 )
			{
				Kprintf("dec mode 0x00\n");
			}
			read_chunk = s->read_chunk;
			if ( !read_chunk )
			{
				read_chunk = s->read_sectors;
			}
			s->read_chunk_reprocial_32 = 0x20 / read_chunk;
			read_chunk_tmp = 1;
			if ( 0x20 / read_chunk )
			{
				read_chunk_tmp = 0x20 / read_chunk + 1;
			}
			read_lsn = s->read_lsn;
			s->read_chunk_reprocial_32 = read_chunk_tmp;
			read_lsn_tmp = read_lsn - 80;
			if ( read_lsn < 0x61 )
			{
				read_lsn_tmp = read_lsn + s->read_sectors + 48;
			}
			read_sectors = s->read_chunk;
			s->dintrlsn = read_lsn_tmp;
			if ( !read_sectors )
			{
				read_sectors = s->read_sectors;
			}
			ncmd = (unsigned __int8)s->cdvdman_command;
			s->read_mode.spindlctrl = 16;
			if ( sceCdRead0_Rty(s->dintrlsn, read_sectors, s->read_buf, &s->read_mode, ncmd, 0, 0) )
			{
				goto LABEL_35;
			}
			s->last_error = 48;
			s->recover_status = 0;
		}
	}
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("Recover_Stat:%d\n", s->recover_status);
	}
	dev5_reg_013 = dev5_regs.dev5_reg_013;
	dev5_reg_013_masked = dev5_reg_013 & 0xF;
	if ( (dev5_reg_013 & 0xF) != 0 )
	{
		last_error_tmp = (unsigned __int8)s->last_error;
		if ( (last_error_tmp == 48 || last_error_tmp == 1 && s->read_to)
			&& !s->recover_status
			&& !s->stream_flag
			&& cdvdman_cmdfunc != 9
			&& cdvdman_cmdfunc != 2
			&& (unsigned int)s->read_mode.trycount - 1 >= 4 )
		{
			dec_mode_set_tmp = s->dec_mode_set;
			s->sync_error = 0;
			s->interupt_read_state = 0;
			if ( dec_mode_set_tmp )
			{
				s->dec_mode_last_set = 2;
			}
			else
			{
				if ( cdvdman_verbose > 0 )
				{
					Kprintf("dec mode 0x01\n");
				}
				cdrmode.trycount = s->read_mode.trycount;
				datapattern = s->read_mode.datapattern;
				cdrmode.spindlctrl = dev5_reg_013_masked + 13;
				cdrmode.datapattern = datapattern;
				if ( sceCdRead0_Rty(
							 s->read_lsn,
							 s->read_sectors,
							 s->read_buf,
							 &cdrmode,
							 (unsigned __int8)s->cdvdman_command,
							 s->read_chunk,
							 s->read_callback) )
				{
					s->last_error = 0;
					return 1;
				}
				s->last_error = 48;
			}
		}
	}
	recover_status = s->recover_status;
	s->read_to = 0;
	if ( recover_status == 2 )
	{
		read_chunk_tmp1 = s->read_chunk;
		s->sync_error = 0;
		s->interupt_read_state = 0;
		read0_result = sceCdRead0(
										 s->read_lsn,
										 s->read_sectors,
										 s->read_buf,
										 &s->read_mode,
										 read_chunk_tmp1,
										 s->read_callback) == 0;
		result = 1;
		if ( !read0_result )
		{
			s->last_error = 0;
			s->recover_status = 3;
			return result;
		}
LABEL_66:
		s->last_error = 48;
		goto LABEL_69;
	}
	if ( recover_status < 3 )
	{
		if ( recover_status != 1 )
		{
			goto LABEL_70;
		}
		rty_sec = s->read_chunk;
		s->sync_error = 0;
		s->interupt_read_state = 0;
		if ( !rty_sec )
		{
			rty_sec = s->read_sectors;
		}
		if ( s->last_error
			|| !sceCdRead0_Rty(s->dintrlsn, rty_sec, s->read_buf, &s->read_mode, (unsigned __int8)s->cdvdman_command, 0, 0) )
		{
			goto LABEL_66;
		}
LABEL_35:
		dintrlsn = s->dintrlsn;
		read_sectors_tmp = s->read_sectors;
		read_chunk_reprocial_32 = s->read_chunk_reprocial_32;
		recover_status_tmp = 1;
		s->last_error = 0;
		--read_chunk_reprocial_32;
		s->dintrlsn = dintrlsn + read_sectors_tmp;
		s->read_chunk_reprocial_32 = read_chunk_reprocial_32;
		if ( !read_chunk_reprocial_32 )
		{
			recover_status_tmp = 2;
		}
		s->recover_status = recover_status_tmp;
		return 1;
	}
	if ( recover_status == 3 )
	{
LABEL_69:
		s->recover_status = 0;
	}
LABEL_70:
	if ( s->dec_state )
	{
		sceCdDecSet(0, 0, 0);
	}
	read2_flag = s->read2_flag;
	if ( (read2_flag == 1 || read2_flag == 3) && !s->use_toc )
	{
		if ( cdvdman_verbose > 0 )
		{
			Kprintf("call Read2intrCDVD()\n");
		}
		Read2intrCDVD(s->read2_flag);
	}
	dec_state = s->dec_state;
	s->sync_error = 0;
	s->interupt_read_state = 0;
	if ( dec_state == 2 )
	{
		s->dec_state = 0;
	}
	stream_flag = s->stream_flag;
	if ( stream_flag == 1 && !s->use_toc && !s->read2_flag )
	{
		if ( cdvdman_cdstm0cb )
		{
			cdvdman_cdstm0cb(1);
		}
		else if ( cdvdman_verbose > 0 )
		{
			Kprintf("Intr func0 no seting");
		}
		stream_flag = s->stream_flag;
	}
	if ( stream_flag == 2 && !s->use_toc )
	{
		if ( s->read2_flag )
		{
			goto LABEL_97;
		}
		if ( cdvdman_cdstm1cb )
		{
			cdvdman_cdstm1cb(1);
		}
		else if ( cdvdman_verbose > 0 )
		{
			Kprintf("Intr func1 no seting");
		}
	}
	if ( !s->read2_flag )
	{
		cdvdman_readptr = 0;
	}
LABEL_97:
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("Intr call user callback func_addr %08x num %d flg %d\n", cdvdman_user_cb, cdvdman_cmdfunc, s->read2_flag);
	}
	if ( !cdvdman_user_cb )
	{
		goto LABEL_108;
	}
	if ( cdvdman_cmdfunc && !s->read2_flag && !s->use_toc )
	{
		cmdfunc_tmp = cdvdman_cmdfunc;
		cdvdman_cmdfunc = 0;
		if ( cmdfunc_tmp == 14 || cmdfunc_tmp == 9 )
		{
			cmdfunc_tmp = 1;
		}
		cdvdman_user_cb(cmdfunc_tmp);
	}
	result = 1;
	if ( !cdvdman_user_cb )
	{
LABEL_108:
		cdvdman_cmdfunc = 0;
		return 1;
	}
	return result;
}
// 406EC0: conditional instruction was optimized away because $v1.4!=0
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00407458) --------------------------------------------------------
int __fastcall intrh_cdrom(cdvdman_internal_struct_t *s)
{
	int conds1; // $s2
	char *some_internal_struct_ptr; // $a1
	int last_error; // $v1
	int *p_waf_set_test; // $a0
	char dev5_reg_006; // $v0
	vu8 dev5_reg_008; // $v0
	vu8 dev5_reg_005; // $v0
	bool checkreg5_1; // dc
	int waftest; // $v0
	vu8 dev_reg_008_tmp; // $v0
	int result; // $v0
	int curbits; // $a1
	iop_event_info_t efinfo; // [sp+18h] [-20h] BYREF

	conds1 = 0;
	curbits = 0;
	some_internal_struct_ptr = &s->field_002[1];
	last_error = (unsigned __int8)s->last_error;
	s->waf_set_test = s->wait_flag;
	p_waf_set_test = &s->waf_set_test;
	if ( last_error != 1 )
	{
		dev5_reg_006 = dev5_regs.dev5_reg_006;
		s->last_error = dev5_reg_006;
		s->last_error = dev5_reg_006;
	}
	dev5_reg_008 = dev5_regs.dev5_reg_008;
	if ( (dev5_reg_008 & 1) != 0 )
	{
		dev5_reg_005 = dev5_regs.dev5_reg_005;
		checkreg5_1 = (dev5_reg_005 & 1) != 0;
		waftest = -1;
		if ( !checkreg5_1 )
		{
			waftest = 1;
		}
		s->waf_set_test = waftest;
		*p_waf_set_test = waftest;
		dev5_regs.dev5_reg_008 = 1;
		conds1 = 1;
	}
	dev_reg_008_tmp = dev5_regs.dev5_reg_008;
	if ( (dev_reg_008_tmp & 4) != 0 )
	{
		dev5_regs.dev5_reg_008 = 4;
		iSetEventFlag(cdvdman_intr_efid, 4u);
		iSetEventFlag(cdvdman_intr_efid, 0x10u);
		if ( cdvdman_poff_cb )
		{
			cdvdman_poff_cb(cdvdman_poffarg);
		}
		result = 1;
		if ( !conds1 )
		{
			return result;
		}
	}
	else
	{
		s->waf_set_test = 1;
		*p_waf_set_test = 1;
		++s->field_002[1];
		++*some_internal_struct_ptr;
		dev5_regs.dev5_reg_008 = 2;
	}
	iReferEventFlagStatus(cdvdman_intr_efid, &efinfo);
	if ( (efinfo.currBits & 0x20) == 0 )
	{
		if ( !s->last_error )
		{
			result = 1;
			s->drive_interupt_request = 1;
			return result;
		}
		if ( s->last_error == 50 )
		{
			intrh_dma_3(s, curbits);
		}
	}
	return cdvdman_intr_cb(s);
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00407644) --------------------------------------------------------
u32 __cdecl cdvdman_l1start(u8 *toc)
{
	return toc[23] + (toc[22] << 8) + (toc[21] << 16) - 196608 + 1;
}

//----- (00407670) --------------------------------------------------------
int __cdecl DvdDual_infochk()
{
	bool condtmp; // dc
	int result; // $v0
	u8 *ptoc_tmp; // $s1
	char opo_or_para_tmp; // $a0

	condtmp = QueryIntrContext() != 0;
	result = 1;
	if ( !condtmp )
	{
		if ( cdvdman_mediactl(3) || (result = 1, (unsigned __int8)cdvdman_istruct.opo_or_para == 255) )
		{
			ptoc_tmp = cdvdman_ptoc;
			cdvdman_istruct.use_toc = 1;
			if ( cdvdman_gettoc(cdvdman_ptoc) )
			{
				cdvdman_istruct.use_toc = 0;
				cdvdman_istruct.layer_1_lsn = cdvdman_l1start(ptoc_tmp);
				if ( (ptoc_tmp[14] & 0x60) != 0 )
				{
					opo_or_para_tmp = 1;
					if ( (ptoc_tmp[14] & 0x10) != 0 )
					{
						opo_or_para_tmp = 2;
					}
					cdvdman_istruct.opo_or_para = opo_or_para_tmp;
				}
				else
				{
					cdvdman_istruct.opo_or_para = 0;
				}
				if ( cdvdman_istruct.dual_layer_emulation )
				{
					if ( cdvdman_verbose > 0 )
					{
						Kprintf("CDVD:DualEmuON\n");
					}
					cdvdman_istruct.layer_1_lsn = cdvdman_istruct.current_dvd_lsn;
					cdvdman_istruct.opo_or_para = 0;
				}
				result = 1;
				if ( cdvdman_verbose > 0 )
				{
					Kprintf(
						"DvdDual_info: %02x\tLayer1_LSN:%d opo_or_para %d\n",
						ptoc_tmp[14],
						cdvdman_istruct.layer_1_lsn,
						(unsigned __int8)cdvdman_istruct.opo_or_para);
					return 1;
				}
			}
			else
			{
				result = 0;
				cdvdman_istruct.use_toc = 0;
				cdvdman_istruct.opo_or_para = -1;
			}
		}
	}
	return result;
}

//----- (004077D0) --------------------------------------------------------
u32 __cdecl sceCdLsnDualChg(u32 lsn)
{
	int layer_disk_needed; // $s1
	bool condtmp; // dc
	u32 result; // $v0
	u32 change_lsn; // $s0
	u8 *ptoc_tmp; // $s2
	int read0_result; // $s0
	int i; // $a1
	u8 *ptoc_tmp2; // $v0
	int master_disk_offs; // $a1
	sceCdRMode cdrmode; // [sp+18h] [-10h] BYREF
	u32 traycnt[2]; // [sp+20h] [-8h] BYREF

	layer_disk_needed = 2;
	condtmp = cdvdman_isdvd() == 0;
	result = lsn;
	if ( !condtmp )
	{
		condtmp = DvdDual_infochk() == 0;
		result = lsn;
		if ( !condtmp )
		{
			if ( cdvdman_istruct.dual_layer_emulation )
			{
				if ( !cdvdman_istruct.current_dvd && lsn >= cdvdman_istruct.current_dvd_lsn )
				{
					layer_disk_needed = 1;
				}
				if ( cdvdman_istruct.current_dvd && lsn < cdvdman_istruct.current_dvd_lsn )
				{
					layer_disk_needed = 0;
				}
				if ( layer_disk_needed == 2 )
				{
					change_lsn = lsn;
					if ( cdvdman_istruct.current_dvd )
					{
						change_lsn = lsn - cdvdman_istruct.current_dvd_lsn;
					}
					result = change_lsn;
					if ( cdvdman_verbose > 0 )
					{
						goto LABEL_64;
					}
				}
				else
				{
					condtmp = QueryIntrContext() != 0;
					result = lsn;
					if ( !condtmp )
					{
						if ( cdvdman_verbose >= 0 )
						{
							Kprintf("CDVD: Exchange it for the Layer_%d_Disk Please.\n", layer_disk_needed);
						}
						if ( cdvdman_minver_60200 )
						{
							while ( !cdvdman_scmd_sender_3B(0) )
							{
								;
							}
						}
						else
						{
							while ( !sceCdTrayReq(0, traycnt) )
							{
								;
							}
						}
						ptoc_tmp = cdvdman_ptoc;
						cdrmode.trycount = 0;
						cdrmode.spindlctrl = 0;
						cdrmode.datapattern = 0;
						cdvdman_istruct.use_toc = 1;
						do
						{
							if ( cdvdman_isdvd() )
							{
								read0_result = sceCdRead0(0xEu, 1u, ptoc_tmp, &cdrmode, 0, 0);
								sceCdSync(3);
								i = 0;
								if ( !cdvdman_istruct.last_error || read0_result )
								{
									ptoc_tmp2 = ptoc_tmp;
									do
									{
										if ( ptoc_tmp2[104] != masterdisc_header[i] )
										{
											break;
										}
										ptoc_tmp2 = &ptoc_tmp[++i];
									}
									while ( i < 20 );
									if ( i == 20 && ptoc_tmp[131] == 2 && (ptoc_tmp[132] & 2) != 0 )
									{
										if ( layer_disk_needed == ptoc_tmp[133] )
										{
											cdvdman_istruct.current_dvd = layer_disk_needed;
											layer_disk_needed = 2;
										}
										else
										{
											if ( cdvdman_verbose >= 0 )
											{
												Kprintf("CDVD: Layer_%d Disk not Found\n", layer_disk_needed);
												if ( cdvdman_verbose >= 0 )
												{
													Kprintf("CDVD: Exchange it for the Layer_%d_Disk Please.\n", layer_disk_needed);
												}
											}
											if ( !cdvdman_istruct.current_dvd && lsn >= cdvdman_istruct.current_dvd_lsn )
											{
												layer_disk_needed = 1;
											}
											if ( cdvdman_minver_60200 )
											{
												while ( !cdvdman_scmd_sender_3B(0) )
												{
													;
												}
											}
											else
											{
												while ( !sceCdTrayReq(0, traycnt) )
												{
													;
												}
											}
										}
									}
									else
									{
										master_disk_offs = i + 104;
										if ( cdvdman_verbose >= 0 )
										{
											Kprintf("CDVD: Not Master Disk %s\n", (const char *)&ptoc_tmp[master_disk_offs]);
										}
										if ( cdvdman_minver_60200 )
										{
											while ( !cdvdman_scmd_sender_3B(0) )
											{
												;
											}
										}
										else
										{
											while ( !sceCdTrayReq(0, traycnt) )
											{
												;
											}
										}
									}
								}
								else if ( cdvdman_verbose > 0 )
								{
									Kprintf("CDVD: LsnDualChg Read Error %02x, %d\n", (unsigned __int8)cdvdman_istruct.last_error, 0);
								}
							}
							else
							{
								vDelayThread(16000);
							}
						}
						while ( layer_disk_needed != 2 );
						change_lsn = lsn;
						if ( cdvdman_istruct.current_dvd )
						{
							change_lsn = lsn - cdvdman_istruct.current_dvd_lsn;
						}
						cdvdman_istruct.use_toc = 0;
						result = change_lsn;
						if ( cdvdman_verbose > 0 )
						{
							goto LABEL_64;
						}
					}
				}
			}
			else
			{
				change_lsn = lsn;
				if ( cdvdman_istruct.opo_or_para )
				{
					if ( lsn >= cdvdman_istruct.layer_1_lsn )
					{
						change_lsn = lsn - 16;
					}
				}
				result = change_lsn;
				if ( cdvdman_verbose > 0 )
				{
LABEL_64:
					Kprintf("CDVD: sceCdLsnDualChg lsn %d: change lsn %d\n", lsn, change_lsn);
					return change_lsn;
				}
			}
		}
	}
	return result;
}
// 40E604: using guessed type char *masterdisc_header;

//----- (00407C5C) --------------------------------------------------------
int __cdecl sceCdReadDvdDualInfo(int *on_dual, unsigned int *layer1_start)
{
	bool condtmp; // dc
	int result; // $v0
	int layer_1_lsn; // $v1
	u8 *ptoc_tmp; // $s0
	int read0_result; // $s1
	int i; // $a1
	u8 *ptoc_tmp2; // $v0
	sceCdRMode cdrmode; // [sp+18h] [-8h] BYREF

	*on_dual = 0;
	*layer1_start = 0;
	cdvdman_istruct.dual_layer_emulation = 0;
	condtmp = cdvdman_isdvd() == 0;
	result = 1;
	if ( !condtmp )
	{
		if ( !cdvdman_emudvd9 )
		{
			condtmp = DvdDual_infochk() == 0;
			result = 0;
			if ( condtmp )
			{
				return result;
			}
			*on_dual = cdvdman_istruct.opo_or_para != 0;
			layer_1_lsn = cdvdman_istruct.layer_1_lsn;
			result = 1;
LABEL_18:
			*layer1_start = layer_1_lsn;
			return result;
		}
		if ( cdvdman_mmode != 2 && cdvdman_mmode != 255 )
		{
			return 0;
		}
		ptoc_tmp = cdvdman_ptoc;
		cdrmode.trycount = 0;
		cdrmode.spindlctrl = 0;
		cdrmode.datapattern = 0;
		read0_result = sceCdRead0(0xEu, 1u, cdvdman_ptoc, &cdrmode, 0, 0);
		sceCdSync(3);
		if ( !cdvdman_istruct.last_error || read0_result )
		{
			i = 0;
			ptoc_tmp2 = ptoc_tmp;
			do
			{
				if ( ptoc_tmp2[104] != masterdisc_header[i] )
				{
					break;
				}
				ptoc_tmp2 = &ptoc_tmp[++i];
			}
			while ( i < 20 );
			if ( i != 20 )
			{
				condtmp = DvdDual_infochk() == 0;
				result = 0;
				if ( condtmp )
				{
					return result;
				}
				*on_dual = cdvdman_istruct.opo_or_para != 0;
				layer_1_lsn = cdvdman_istruct.layer_1_lsn;
				result = 1;
				goto LABEL_18;
			}
			result = 1;
			if ( ptoc_tmp[131] == 2 )
			{
				result = 1;
				if ( (ptoc_tmp[132] & 2) != 0 )
				{
					cdvdman_istruct.current_dvd = ptoc_tmp[133];
					cdvdman_istruct.current_dvd_lsn = ptoc_tmp[134]
																					+ (ptoc_tmp[135] << 8)
																					+ (ptoc_tmp[136] << 16)
																					+ (ptoc_tmp[137] << 24)
																					+ 1;
					cdvdman_istruct.opo_or_para = 0;
					cdvdman_istruct.layer_1_lsn = cdvdman_istruct.current_dvd_lsn;
					cdvdman_istruct.dual_layer_emulation = 1;
					*on_dual = 1;
					*layer1_start = cdvdman_istruct.layer_1_lsn;
					result = 1;
					if ( cdvdman_verbose > 0 )
					{
						Kprintf(
							"sceCdReadDvdDualInfo():Cur_Disk %d layer1_start %d\n",
							(unsigned __int8)cdvdman_istruct.current_dvd,
							cdvdman_istruct.current_dvd_lsn);
						return 1;
					}
				}
			}
		}
		else
		{
			result = 0;
			if ( cdvdman_verbose > 0 )
			{
				Kprintf("CDVD: ReadDvdDualInfo Read Error %02x, %d\n", (unsigned __int8)cdvdman_istruct.last_error, 0);
				return 0;
			}
		}
	}
	return result;
}
// 40E604: using guessed type char *masterdisc_header;

//----- (00407EE8) --------------------------------------------------------
int __cdecl sceCdSC(int code, int *param)
{
	void *poffarg_tmp; // $s0
	int result; // $v0
	int *BootMode; // $v0
	unsigned int bootmode4res; // $v1
	vu8 dev5_reg_00F; // $v0
	int reg_00F_tmp; // $v1
	bool condtmp1; // dc
	u32 condtmp2; // $v0
	int cdvdman_mmode_tmp; // $v1
	int mmode_rval_cmp; // $v0
	int ee_ncmd_working_code; // $a1
	int state; // [sp+10h] [-8h] BYREF
	u32 efbits; // [sp+14h] [-4h] BYREF

	switch ( code )
	{
		case 0xFFFFFFE6:
			CpuSuspendIntr(&state);
			*param = (int)cdvdman_poff_cb;
			poffarg_tmp = cdvdman_poffarg;
			CpuResumeIntr(state);
			return (int)poffarg_tmp;
		case 0xFFFFFFE7:
			return scmd_evid;
		case 0xFFFFFFE9:
			return sceCdLsnDualChg(*param);
		case 0xFFFFFFEA:
			return DvdDual_infochk();
		case 0xFFFFFFEE:
			result = 0;
			cdvdman_istruct.read_to = *param;
			return result;
		case 0xFFFFFFEF:
			return TimeOut2;
		case 0xFFFFFFF0:
			*param = (int)&cdvdman_verbose;
			return 255;
		case 0xFFFFFFF1:
			return cdvdman_sync_to;
		case 0xFFFFFFF2:
			*param = (int)&cdvdman_istruct;
			return 255;
		case 0xFFFFFFF3:
			BootMode = QueryBootMode(4);
			if ( !BootMode )
			{
				return 1;
			}
			bootmode4res = *(unsigned __int8 *)BootMode;
			if ( bootmode4res < 3 )
			{
				cdvdman_mmode = 255;
				return 1;
			}
			else
			{
				result = 1;
				if ( bootmode4res == 3 )
				{
					cdvdman_mmode = 0;
				}
			}
			return result;
		case 0xFFFFFFF4:
			dev5_reg_00F = dev5_regs.dev5_reg_00F;
			reg_00F_tmp = dev5_reg_00F;
			condtmp1 = dev5_reg_00F == 20;
			condtmp2 = dev5_reg_00F < 0x15u;
			if ( condtmp1 )
			{
				cdvdman_mmode_tmp = cdvdman_mmode;
				mmode_rval_cmp = 2;
			}
			else
			{
				if ( condtmp2 )
				{
					result = 0;
					if ( reg_00F_tmp < 16 )
					{
						return result;
					}
				}
				else
				{
					result = 0;
					if ( reg_00F_tmp != 253 )
					{
						return result;
					}
				}
				cdvdman_mmode_tmp = cdvdman_mmode;
				mmode_rval_cmp = 1;
			}
			if ( cdvdman_mmode_tmp == mmode_rval_cmp )
			{
				return 1;
			}
			result = 0;
			if ( cdvdman_mmode_tmp == 255 )
			{
				return 1;
			}
			return result;
		case 0xFFFFFFF5:
			return cdvdman_intr_efid;
		case 0xFFFFFFF6:
			if ( *param )
			{
				WaitEventFlag(fio_fsv_evid, 1u, 16, &efbits);
			}
			else
			{
				SetEventFlag(fio_fsv_evid, 1u);
			}
			ee_ncmd_working_code = *param;
			cdvdman_strm_id = *param;
			if ( cdvdman_verbose > 0 )
			{
				Kprintf("EE_ncmd_working code= %d\n", ee_ncmd_working_code);
			}
			return cdvdman_strm_id;
		case 0xFFFFFFF7:
			return (unsigned __int16)_irx_id.v;
		case 0xFFFFFFF8:
			cdvdman_spinctl = *param;
			return 1;
		case 0xFFFFFFFC:
			return cdvdman_cd36key;
		case 0xFFFFFFFD:
			return cdvdman_istruct.read2_flag;
		case 0xFFFFFFFE:
			cdvdman_istruct.last_error = *(_BYTE *)param;
			return (unsigned __int8)cdvdman_istruct.last_error;
		case 0xFFFFFFFF:
		case 0:
		case 1:
		case 2:
			*param = (unsigned __int8)cdvdman_istruct.last_error;
			if ( code != -1 )
			{
				cdvdman_istruct.stream_flag = code;
			}
			return cdvdman_istruct.stream_flag;
		default:
			result = 0;
			if ( cdvdman_verbose > 0 )
			{
				Kprintf("sceCdSC func_num Not found %d\n", code);
				return 0;
			}
			return result;
	}
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00408224) --------------------------------------------------------
void __cdecl nullsub_2()
{
	;
}

//----- (0040822C) --------------------------------------------------------
int __cdecl cdvdman_init()
{
	u32 dpcr; // $v0
	vu8 dev5_reg_008; // $v0
	int clk_flag_tmp; // $s0
	vu8 dev5_reg_00A; // $v0
	int *BootMode; // $v0
	int no_dec_flag_tmp; // $v1
	unsigned int i; // $s0
	int poffready_tmp; // $s1
	int result; // $v0
	int scres; // [sp+10h] [-8h] BYREF
	u32 argres; // [sp+14h] [-4h] BYREF

	cdvdman_user_cb = 0;
	cdvdman_poff_cb = 0;
	cdvdman_cmdfunc = 0;
	cdvdman_istruct.drive_interupt_request = 0;
	RegisterIntrHandler(2, 1, (int (__cdecl *)(void *))intrh_cdrom, &cdvdman_istruct);
	RegisterIntrHandler(35, 1, (int (__cdecl *)(void *))intrh_dma_3, &cdvdman_istruct);
	EnableIntr(2);
	sceCdSC(0xFFFFFFF3, &scres);
	dpcr = dmac_get_dpcr();
	dmac_set_dpcr(dpcr | 0x8000);
	dmac_ch_set_chcr(3u, 0);
	dev5_reg_008 = dev5_regs.dev5_reg_008;
	if ( (dev5_reg_008 & 4) != 0 )
	{
		dev5_regs.dev5_reg_008 = 4;
	}
	if ( (dev5_regs.dev5_reg_008 & 1) != 0 )
	{
		dev5_regs.dev5_reg_008 = 1;
	}
	clk_flag_tmp = 0;
	if ( sceCdReadClock(&cdvdman_clock) )
	{
		clk_flag_tmp = cdvdman_clock.stat == 0;
	}
	dev5_reg_00A = dev5_regs.dev5_reg_00A;
	cdvdman_clk_flg = clk_flag_tmp;
	cdvdman_istruct.tray_is_open = (dev5_reg_00A ^ 1) & 1;
	cdvdman_initcfg();
	BootMode = QueryBootMode(6);
	no_dec_flag_tmp = 0;
	if ( BootMode )
	{
		no_dec_flag_tmp = (*(_WORD *)BootMode & 0xFFFC) == 0x60;
	}
	cdvdman_istruct.no_dec_flag = no_dec_flag_tmp;
	i = 0;
	while ( 1 )
	{
		poffready_tmp = sceCdCancelPOffRdy(&argres);
		if ( !poffready_tmp || argres )
		{
			DelayThread(16000);
		}
		result = ++i < 0x3D;
		if ( i >= 0x3D )
		{
			break;
		}
		if ( poffready_tmp )
		{
			result = argres;
			if ( !argres )
			{
				break;
			}
		}
	}
	return result;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (004083E8) --------------------------------------------------------
int __cdecl sceCdInit(int init_mode)
{
	vu8 ready_status_tmp; // $s1
	vu8 ready_status; // $s0
	int ready_status_mask_c0h; // $v0
	int oldstate[2]; // [sp+10h] [-8h] BYREF

	if ( cdvdman_verbose > 0 )
	{
		printf("sceCdInit called mode= %d\n", init_mode);
	}
	if ( init_mode >= 0 && init_mode >= 2 && init_mode == 5 )
	{
		cdvdman_istruct.cd_inited = 0;
		sceCdBreak();
		sceCdSync(3);
		cdvdman_ncmd_sender_06();
		sceCdSync(0);
		if ( cdvdman_verbose > 0 )
		{
			printf("Cdvdman Exit\n");
		}
		DisableIntr(2, oldstate);
		ReleaseIntrHandler(2);
		DisableIntr(35, oldstate);
		ReleaseIntrHandler(35);
	}
	else
	{
		if ( cdvdman_verbose > 0 )
		{
			printf("Cdvdman Init\n");
		}
		cdvdman_istruct.read2_flag = 0;
		cdvdman_istruct.dec_shift = 0;
		cdvdman_istruct.check_version = 0;
		cdvdman_istruct.dec_state = 0;
		sceCdDecSet(0, 0, 0);
		cdvdman_init();
		cdvdman_istruct.cd_inited = 1;
	}
	if ( !init_mode )
	{
		ready_status_tmp = 0;
		if ( cdvdman_verbose > 0 )
		{
			printf("sceCdInit Ready check start.\n");
		}
		do
		{
			ready_status = dev5_regs.dev5_reg_005;
			vDelayThread(10000);
			ready_status_mask_c0h = ready_status & 0xC0;
			if ( ready_status != ready_status_tmp )
			{
				ready_status_tmp = ready_status;
				if ( cdvdman_verbose > 0 )
				{
					printf("sceCdInit Dev5 Status %x\n", ready_status);
				}
				ready_status_mask_c0h = ready_status & 0xC0;
			}
		}
		while ( ready_status_mask_c0h != 64 );
		if ( cdvdman_verbose > 0 )
		{
			printf("sceCdInit Ready check end.\n");
		}
	}
	cdvdman_istruct.wait_flag = 1;
	cdvdman_istruct.scmd_flag = 1;
	cdvdman_istruct.last_error = 0;
	cdvdman_istruct.read_to = 0;
	cdvdman_spinctl = -1;
	SetEventFlag(cdvdman_intr_efid, 0x29u);
	SetEventFlag(ncmd_evid, 1u);
	SetEventFlag(scmd_evid, 1u);
	SetEventFlag(sfile_evid, 1u);
	return 1;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00408660) --------------------------------------------------------
int __cdecl set_prev_command(int cmd, const char *sdata, int sdlen, char *rdata, int rdlen, int check_sef)
{
	char cmd_1; // $s2
	int extrasd; // $s0
	const char *sdata_tmp; // $v0
	int delaytmp; // $s0
	int delaybackoff; // $s1
	int readtmp; // $s0
	char *rdataptr_tmp; // $v1
	char rdataptr_tmp2; // $v0
	u32 efbits[2]; // [sp+10h] [-8h] BYREF

	cmd_1 = cmd;
	if ( check_sef == 1 )
	{
		extrasd = 0;
		if ( PollEventFlag(scmd_evid, 1u, 16, efbits) == -421 )
		{
			return 0;
		}
	}
	else
	{
		extrasd = 0;
	}
	cdvdman_istruct.scmd = cmd_1;
	cdvdman_istruct.sdlen = sdlen;
	cdvdman_istruct.rdlen = rdlen;
	sdata_tmp = sdata;
	if ( sdlen > 0 )
	{
		do
		{
			cdvdman_istruct.scmd_sd[extrasd++] = *sdata_tmp;
			sdata_tmp = &sdata[extrasd];
		}
		while ( extrasd < sdlen );
	}
	if ( cdvdman_istruct.wait_flag )
	{
		cdvdman_istruct.scmd_flag = 1;
LABEL_15:
		delaytmp = 0;
		cdvdman_write_scmd(&cdvdman_istruct);
		goto LABEL_17;
	}
	if ( QueryIntrContext() )
	{
		while ( (dmac_ch_get_chcr(3u) & 0x1000000) != 0 && !cdvdman_istruct.wait_flag )
		{
			if ( cdvdman_verbose > 0 )
			{
				Kprintf("set_prev_command: DMA Wait\n");
			}
		}
		cdvdman_istruct.scmd_flag = 1;
		goto LABEL_15;
	}
	cdvdman_istruct.scmd_flag = 0;
	delaytmp = 0;
LABEL_17:
	delaybackoff = 1;
	if ( cdvdman_istruct.scmd_flag )
	{
LABEL_26:
		readtmp = 0;
		if ( rdlen > 0 )
		{
			rdataptr_tmp = rdata;
			do
			{
				rdataptr_tmp2 = cdvdman_istruct.scmd_rd[readtmp++];
				*rdataptr_tmp = rdataptr_tmp2;
				rdataptr_tmp = &rdata[readtmp];
			}
			while ( readtmp < rdlen );
		}
		if ( check_sef == 1 )
		{
			vSetEventFlag(scmd_evid, 1u);
		}
		return (unsigned __int8)cdvdman_istruct.scmd;
	}
	else
	{
		while ( 1 )
		{
			vDelayThread(1000 * delaybackoff);
			if ( (delaytmp & 1) != 0 && delaybackoff < 16 )
			{
				delaybackoff *= 2;
			}
			delaytmp += delaybackoff;
			if ( delaytmp >= 500 )
			{
				break;
			}
			if ( cdvdman_istruct.scmd_flag )
			{
				goto LABEL_26;
			}
		}
		cdvdman_istruct.scmd_flag = 1;
		if ( check_sef != 1 )
		{
			return 0;
		}
		vSetEventFlag(scmd_evid, 1u);
		return 0;
	}
}
// 408834: conditional instruction was optimized away because $s0.4<1F4

//----- (004088EC) --------------------------------------------------------
void __cdecl cdvdman_write_scmd(cdvdman_internal_struct_t *s)
{
	int i; // $s5
	int sdi; // $s0
	cdvdman_internal_struct_t *stmp1; // $v0
	int delaymax; // $s0
	int rdcnt; // $s0
	int overflowcond; // $a2
	int trycndmx; // $a0
	char *curptrx; // $v0
	int rdcnt2; // $a0
	char *rdptr; // $v0
	int rdx2; // $a0
	cdvdman_internal_struct_t *stmp2; // $v1
	char stmp3; // $v0
	char rdptr1[64]; // [sp+18h] [-40h] BYREF

	for ( i = 0; i <= 0; ++i )
	{
		if ( (dev5_regs.dev5_reg_017 & 0x80) != 0 )
		{
			goto LABEL_36;
		}
		while ( (dev5_regs.dev5_reg_017 & 0x40) == 0 )
		{
			;
		}
		sdi = 0;
		if ( s->sdlen )
		{
			stmp1 = s;
			do
			{
				dev5_regs.dev5_reg_017 = stmp1->scmd_sd[0];
				++sdi;
				stmp1 = (cdvdman_internal_struct_t *)((char *)s + sdi);
			}
			while ( sdi < (unsigned __int8)s->sdlen );
		}
		dev5_regs.dev5_reg_016 = s->scmd;
		delaymax = 0;
		if ( QueryIntrContext() )
		{
			if ( (dev5_regs.dev5_reg_017 & 0x80) != 0 )
			{
				while ( delaymax <= 12500000 )
				{
					++delaymax;
					if ( (dev5_regs.dev5_reg_017 & 0x80) == 0 )
					{
						rdcnt = 0;
						goto LABEL_16;
					}
				}
LABEL_36:
				*(_WORD *)&s->scmd_flag = 1;
				return;
			}
		}
		else
		{
			for ( ; (dev5_regs.dev5_reg_017 & 0x80) != 0; ++delaymax )
			{
				DelayThread(100);
				if ( delaymax > 50000 )
				{
					goto LABEL_36;
				}
			}
		}
		rdcnt = 0;
LABEL_16:
		overflowcond = 0;
		if ( (dev5_regs.dev5_reg_017 & 0x40) == 0 )
		{
			while ( rdcnt < (unsigned __int8)s->rdlen )
			{
				rdptr1[rdcnt++] = dev5_regs.dev5_reg_018;
				if ( (dev5_regs.dev5_reg_017 & 0x40) != 0 )
				{
					goto LABEL_21;
				}
			}
			overflowcond = 1;
			if ( cdvdman_verbose > 0 )
			{
				Kprintf("Prev Cmd Result Over Flow\n", rdptr1);
				overflowcond = 1;
			}
		}
LABEL_21:
		if ( !overflowcond && rdcnt >= (unsigned __int8)s->rdlen || s->rdlen == 16 )
		{
			break;
		}
		if ( cdvdman_verbose > 0 )
		{
			Kprintf("Prev Cmd Result Illegal Size Try count:%d\n", i);
		}
	}
	trycndmx = 15;
	if ( i == 1 )
	{
		*(_WORD *)&s->scmd_flag = 1;
	}
	else
	{
		curptrx = (char *)&s->stream_flag + 3;
		do
		{
			curptrx[108] = 0;
			--trycndmx;
			--curptrx;
		}
		while ( trycndmx >= 0 );
		if ( s->rdlen == 16 )
		{
			rdx2 = 0;
			if ( rdcnt > 0 )
			{
				stmp2 = s;
				do
				{
					stmp3 = rdptr1[rdx2++];
					stmp2->scmd_rd[0] = stmp3;
					stmp2 = (cdvdman_internal_struct_t *)((char *)s + rdx2);
				}
				while ( rdx2 < rdcnt );
			}
		}
		else
		{
			rdcnt2 = 0;
			if ( s->rdlen )
			{
				rdptr = rdptr1;
				do
				{
					s->scmd_rd[rdcnt2++] = *rdptr;
					rdptr = &rdptr1[rdcnt2];
				}
				while ( rdcnt2 < (unsigned __int8)s->rdlen );
			}
		}
		s->scmd_flag = 1;
		s->scmd = 1;
	}
}
// BF402000: using guessed type dev5_regs_t dev5_regs;
// 4088EC: using guessed type char rdptr1[64];

//----- (00408C10) --------------------------------------------------------
int __cdecl cdvdman_send_scmd2(int cmd, const void *sdata, int sdlen, void *rdata, int rdlen, int check_sef)
{
	int trycnt; // $s3
	int result; // $v0
	int i; // $s0
	vu8 sdatatmp; // $v0
	int rdlecnt; // $s0
	int cmdresoverflow; // $a1
	int rdextra; // $a0
	int rdcpy1; // $a0
	char *rdtmp1; // $v0
	char *rdtmp2; // $v1
	char rdstart[64]; // [sp+18h] [-50h] BYREF
	u32 efbits; // [sp+58h] [-10h] BYREF
	vu8 cmdtmp; // [sp+5Ch] [-Ch]
	int rdlenremain; // [sp+60h] [-8h]

	cmdtmp = cmd;
	if ( check_sef == 1 )
	{
		trycnt = 0;
		if ( PollEventFlag(scmd_evid, 1u, 16, &efbits) == -421 )
		{
			return 0;
		}
	}
	else
	{
		trycnt = 0;
	}
	rdlenremain = 16 - rdlen;
	do
	{
		if ( (dev5_regs.dev5_reg_017 & 0x80) != 0 )
		{
			if ( check_sef != 1 )
			{
				return 0;
			}
			goto LABEL_8;
		}
		while ( (dev5_regs.dev5_reg_017 & 0x40) == 0 )
		{
			;
		}
		for ( i = 0; i < sdlen; dev5_regs.dev5_reg_017 = sdatatmp )
		{
			sdatatmp = *((_BYTE *)sdata + i++);
		}
		dev5_regs.dev5_reg_016 = cmdtmp;
		while ( (dev5_regs.dev5_reg_017 & 0x80) != 0 )
		{
			DelayThread(100);
		}
		rdlecnt = 0;
		cmdresoverflow = 0;
		if ( (dev5_regs.dev5_reg_017 & 0x40) == 0 )
		{
			while ( rdlecnt < rdlen )
			{
				rdstart[rdlecnt++] = dev5_regs.dev5_reg_018;
				if ( (dev5_regs.dev5_reg_017 & 0x40) != 0 )
				{
					goto LABEL_19;
				}
			}
			cmdresoverflow = 1;
			if ( cdvdman_verbose > 0 )
			{
				Kprintf("Prev Cmd Result Over Flow\n");
				cmdresoverflow = 1;
			}
		}
LABEL_19:
		if ( !cmdresoverflow && rdlecnt >= rdlen || rdlen == 16 )
		{
			break;
		}
		if ( cdvdman_verbose > 0 )
		{
			Kprintf("Prev Cmd Result Illegal Size Try count:%d\n", trycnt);
		}
		while ( (dev5_regs.dev5_reg_017 & 0x20) == 0 )
		{
			;
		}
		rdextra = 0;
		if ( rdlenremain > 0 )
		{
			do
			{
				++rdextra;
			}
			while ( rdextra < 16 - rdlen );
		}
		++trycnt;
	}
	while ( trycnt <= 0 );
	if ( trycnt == 1 )
	{
		if ( check_sef == 1 )
		{
LABEL_8:
			vSetEventFlag(scmd_evid, 1u);
			return 0;
		}
		return 0;
	}
	rdcpy1 = 0;
	if ( rdlen > 0 )
	{
		rdtmp1 = rdstart;
		do
		{
			rdtmp2 = (char *)rdata + rdcpy1++;
			*rdtmp2 = *rdtmp1;
			rdtmp1 = &rdstart[rdcpy1];
		}
		while ( rdcpy1 < rdlen );
	}
	result = 1;
	if ( check_sef == 1 )
	{
		vSetEventFlag(scmd_evid, 1u);
		return 1;
	}
	return result;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;
// 408C10: using guessed type char rdstart[64];

//----- (00408F50) --------------------------------------------------------
int __cdecl sceCdApplySCmd(u8 cmdNum, const void *inBuff, u16 inBuffSize, void *outBuff)
{
	int wdlen_tmp; // $s5
	int timeout_tmp; // $s0

	wdlen_tmp = inBuffSize;
	timeout_tmp = 0;
	while ( !set_prev_command(cmdNum, (const char *)inBuff, wdlen_tmp, (char *)outBuff, 16, 1) )
	{
		DelayThread(2000);
		if ( timeout_tmp++ >= 2501 )
		{
			Kprintf("CDVD: set_prev_command TIMEOUT 5(SEC)\n");
			return 0;
		}
	}
	DelayThread(2000);
	return 1;
}

//----- (00409014) --------------------------------------------------------
int __cdecl sceCdApplySCmd2(u8 cmdNum, const void *inBuff, unsigned long int inBuffSize, void *outBuff)
{
	int i; // $s0
	bool condtmp; // dc
	int result; // $v0

	i = 0;
	while ( 1 )
	{
		condtmp = cdvdman_send_scmd2(cmdNum, inBuff, inBuffSize, outBuff, 16, 1) != 0;
		result = 1;
		if ( condtmp )
		{
			break;
		}
		DelayThread(2000);
		condtmp = i++ < 2501;
		if ( !condtmp )
		{
			Kprintf("CDVD: set_prev_command TIMEOUT 5(SEC)\n");
			return 0;
		}
	}
	return result;
}

//----- (004090C8) --------------------------------------------------------
int __fastcall cdvdman_125(char cmd, char *wdata, int wdlen, char *rdata)
{
	int timeoutcnt; // $s0

	timeoutcnt = 0;
	while ( !set_prev_command((unsigned __int8)cmd, wdata, wdlen, rdata, 16, 1) )
	{
		DelayThread(2000);
		if ( timeoutcnt++ >= 2501 )
		{
			Kprintf("CDVD: set_prev_command TIMEOUT 5(SEC)\n");
			return 0;
		}
	}
	DelayThread(2000);
	return 1;
}

//----- (0040918C) --------------------------------------------------------
int sceCdBreak(void)
{
	bool condtmp; // dc
	int result; // $v0
	vu8 dev5_reg_005; // $v0
	u32 efbits; // [sp+18h] [-10h] BYREF
	int state; // [sp+1Ch] [-Ch] BYREF
	int oldstate; // [sp+20h] [-8h] BYREF

	condtmp = PollEventFlag(ncmd_evid, 1u, 16, &efbits) == -421;
	result = 0;
	if ( !condtmp )
	{
		CpuSuspendIntr(&state);
		if ( cdvdman_verbose > 0 )
		{
			Kprintf(
				"Break call: read2_flg= %d func= %d lsn= %d csec= %d nsec= %d\n",
				cdvdman_istruct.read2_flag,
				cdvdman_cmdfunc,
				cdvdman_istruct.cdvdman_lsn,
				cdvdman_istruct.cdvdman_csec,
				cdvdman_istruct.cdvdman_nsec);
		}
		if ( cdvdman_istruct.read_to )
		{
			cdvdman_istruct.read2_flag = 0;
		}
		cdvdman_istruct.last_error = 1;
		cdvdman_istruct.thread_id = GetThreadId();
		cdvdman_istruct.m_break_cdvdfsv_readchain = 1;
		if ( cdvdman_istruct.dec_state )
		{
			cdvdman_istruct.dec_shift = 0;
			cdvdman_istruct.check_version = 0;
			cdvdman_istruct.dec_state = 0;
			sceCdDecSet(0, 0, 0);
		}
		cdvdman_istruct.recover_status = 0;
		if ( QueryIntrContext() )
		{
			iSetEventFlag(cdvdman_intr_efid, 0x29u);
			iCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb_read, &cdvdman_racb_to);
		}
		else
		{
			SetEventFlag(cdvdman_intr_efid, 0x29u);
			CancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb_read, &cdvdman_racb_to);
		}
		if ( !cdvdman_istruct.wait_flag || cdvdman_istruct.read_to )
		{
			dev5_reg_005 = dev5_regs.dev5_reg_005;
			if ( (dev5_reg_005 & 0xC0) == 64 )
			{
				if ( cdvdman_verbose > 0 )
				{
					Kprintf("cdvd: NonInter END\n");
				}
				cdvdman_istruct.wait_flag = 1;
			}
			cdvdman_last_cmdfunc = cdvdman_cmdfunc;
			cdvdman_cmdfunc = 8;
			dev5_regs.dev5_reg_007 = 1;
			if ( cdvdman_istruct.read_to )
			{
				DisableIntr(35, &oldstate);
			}
			cdvdman_istruct.drive_interupt_request = 0;
			if ( cdvdman_verbose > 0 )
			{
				Kprintf("cdvd: Abort command On\n");
			}
		}
		vSetEventFlag(ncmd_evid, 1u);
		CpuResumeIntr(state);
		return 1;
	}
	return result;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (004093F4) --------------------------------------------------------
int __fastcall cd_ncmd_timeout_callback(iop_sys_clock_t *sys_clock)
{
	Kprintf("Cmd Time Out %d(msec)\n", sys_clock->lo / 0x9000);
	sys_clock->lo = 0;
	return 0;
}

//----- (00409440) --------------------------------------------------------
int __fastcall intrh_dma_3(cdvdman_internal_struct_t *s, int cbbits)
{
	int (*dma3_callback)(void); // $v0
	int dmacbres; // $a2
	unsigned int read_chunk; // $a0
	u32 dma3_msectors; // $a1
	int oldstate; // [sp+14h] [-4h] BYREF

	s->dma3prm.dma3_msectors -= s->dma3prm.dma3_csectors;
	dma3_callback = (int (*)(void))s->dma3prm.dma3_callback;
	if ( dma3_callback )
	{
		dmacbres = dma3_callback();
	}
	else
	{
		dmacbres = 1;
	}
	read_chunk = s->read_chunk;
	dma3_msectors = s->dma3prm.dma3_msectors;
	s->cdvdman_dma3sec += s->dma3prm.dma3_csectors;
	if ( dma3_msectors < read_chunk )
	{
		read_chunk = dma3_msectors;
	}
	s->dma3prm.dma3_csectors = read_chunk;
	if ( dmacbres )
	{
		if ( s->dma3prm.dma3_msectors )
		{
			dmac_ch_set_chcr(3u, 0);
			dmac_ch_get_chcr(3u);
			dmac_ch_set_madr(3u, (u32)s->dma3prm.dma3_maddress);
			dmac_ch_set_bcr(3u, ((s->dma3prm.dma3_blkcount * s->dma3prm.dma3_csectors) << 16) | s->dma3prm.dma3_blkwords);
			dmac_ch_set_chcr(3u, 0x41000200u);
			dmac_ch_get_chcr(3u);
			iClearEventFlag(cdvdman_intr_efid, 0xFFFFFFDF);
		}
		else
		{
			DisableIntr(35, &oldstate);
			iSetEventFlag(cdvdman_intr_efid, 0x20u);
		}
	}
	if ( !s->dma3prm.dma3_msectors && s->drive_interupt_request )
	{
		cdvdman_intr_cb(s);
		s->drive_interupt_request = 0;
	}
	return 1;
}

//----- (004095AC) --------------------------------------------------------
int __cdecl cdvdman_setdma3(DMA3PARAM *b18)
{
	void *dma3_maddress; // $a3
	int (__cdecl *dma3_callback)(void *, int, int); // $t0
	void *maddr_tmp; // $a1
	int blkcnt_tmp; // $a1

	if ( (dmac_ch_get_chcr(3u) & 0x1000000) != 0 )
	{
		dev5_regs.dev5_reg_007 = 1;
	}
	cdvdman_istruct.drive_interupt_request = 0;
	dma3_maddress = b18->dma3_maddress;
	dma3_callback = b18->dma3_callback;
	cdvdman_istruct.dma3prm.dma3_blkwords = b18->dma3_blkwords;
	cdvdman_istruct.dma3prm.dma3_blkcount = b18->dma3_blkcount;
	cdvdman_istruct.dma3prm.dma3_maddress = dma3_maddress;
	cdvdman_istruct.dma3prm.dma3_callback = dma3_callback;
	cdvdman_istruct.dma3prm.dma3_csectors = b18->dma3_csectors;
	cdvdman_istruct.dma3prm.cdvdreg_howto = b18->cdvdreg_howto;
	cdvdman_istruct.dma3prm.dma3_msectors = b18->dma3_msectors;
	cdvdman_istruct.cdvdman_dma3sec = 0;
	dmac_ch_set_chcr(3u, 0);
	dmac_ch_get_chcr(3u);
	if ( b18->dma3_csectors )
	{
		vClearEventFlag(cdvdman_intr_efid, 0xFFFFFFDF);
		EnableIntr(35);
	}
	maddr_tmp = b18->dma3_maddress;
	dev5_regs.dev5_reg_006 = b18->cdvdreg_howto;
	dmac_ch_set_madr(3u, (u32)maddr_tmp);
	if ( b18->dma3_csectors )
	{
		blkcnt_tmp = (b18->dma3_blkcount * b18->dma3_csectors) << 16;
	}
	else
	{
		blkcnt_tmp = b18->dma3_blkcount << 16;
	}
	dmac_ch_set_bcr(3u, blkcnt_tmp | b18->dma3_blkwords);
	dmac_ch_set_chcr(3u, 0x41000200u);
	return dmac_ch_get_chcr(3u);
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (004096F4) --------------------------------------------------------
int __cdecl cdvdman_send_ncmd(int ncmd, const void *ndata, int ndlen, int func, DMA3PARAM *b18, int check_cb)
{
	char ncmd_tmp1; // $s1
	vu8 dev5_reg_005; // $v0
	int disk_ready_status; // $a1
	vu8 dev5_reg_00F; // $v0
	vu8 dev5_reg_00A; // $v1
	int reg_00A_tmp1; // $a1
	int reg_00A_tmp2; // $v0
	int ndlencur; // $v1
	vu8 *ndataptr; // $v0
	u32 efbits; // [sp+14h] [-4h] BYREF

	ncmd_tmp1 = ncmd;
	if ( check_cb == 1 && PollEventFlag(ncmd_evid, 1u, 16, &efbits) == -421 )
	{
		return -1;
	}
	dev5_reg_005 = dev5_regs.dev5_reg_005;
	if ( (dev5_reg_005 & 0xC0) == 64
		&& cdvdman_istruct.wait_flag
		&& (cdvdman_istruct.read2_flag != 1 || ncmd_tmp1 == 8)
		&& (cdvdman_istruct.read2_flag != 2 || ncmd_tmp1 == 6) )
	{
		cdvdman_iocache = 0;
		if ( b18 )
		{
			cdvdman_setdma3(b18);
		}
		cdvdman_cmdfunc = func;
		dev5_reg_00F = dev5_regs.dev5_reg_00F;
		if ( !cdvdman_minver_10700
			&& cdvdman_ncmd == 6
			&& ncmd_tmp1
			&& ncmd_tmp1 != cdvdman_ncmd
			&& ncmd_tmp1 != 7
			&& ncmd_tmp1 != 14
			&& ncmd_tmp1 != 8
			&& (dev5_reg_00F != 253 || ncmd_tmp1 == 3) )
		{
			cdvdman_ncmd_to.hi = 0;
			cdvdman_ncmd_to.lo = 0x6978000;
			vSetAlarm(&cdvdman_ncmd_to, (unsigned int (__cdecl *)(void *))cd_ncmd_timeout_callback, &cdvdman_ncmd_to);
			dev5_reg_00A = dev5_regs.dev5_reg_00A;
			if ( dev5_reg_00A != 10 )
			{
				while ( 1 )
				{
					if ( cdvdman_verbose > 0 )
					{
						reg_00A_tmp1 = dev5_regs.dev5_reg_00A;
						Kprintf("Read Pause 1 chk status 0x%02x\n", reg_00A_tmp1);
					}
					if ( !cdvdman_ncmd_to.lo )
					{
						break;
					}
					vDelayThread(1000);
					reg_00A_tmp2 = dev5_regs.dev5_reg_00A;
					if ( reg_00A_tmp2 == 10 )
					{
						goto LABEL_33;
					}
				}
				cdvdman_ncmd = ncmd_tmp1;
				if ( check_cb == 1 )
				{
					vSetEventFlag(ncmd_evid, 1u);
				}
				Kprintf("Time Out Pause WAIT set_cd_commnad\n");
				return -1;
			}
LABEL_33:
			vCancelAlarm((unsigned int (__cdecl *)(void *))cd_ncmd_timeout_callback, &cdvdman_ncmd_to);
		}
		cdvdman_ncmd = ncmd_tmp1;
		if ( cdvdman_istruct.dec_state )
		{
			sceCdDecSet(cdvdman_istruct.dec_shift != 0, 1u, cdvdman_istruct.dec_shift);
		}
		cdvdman_istruct.read_to = 0;
		cdvdman_istruct.cdvdman_command = ncmd_tmp1;
		cdvdman_istruct.last_error = 0;
		cdvdman_istruct.wait_flag = 0;
		cdvdman_istruct.thread_id = GetThreadId();
		if ( QueryIntrContext() )
		{
			iClearEventFlag(cdvdman_intr_efid, 0xFFFFFFFE);
		}
		else
		{
			ClearEventFlag(cdvdman_intr_efid, 0xFFFFFFFE);
		}
		ndlencur = 0;
		if ( ndlen > 0 )
		{
			ndataptr = (vu8 *)ndata;
			do
			{
				++ndlencur;
				dev5_regs.dev5_reg_005 = *ndataptr;
				ndataptr = (vu8 *)ndata + ndlencur;
			}
			while ( ndlencur < ndlen );
		}
		dev5_regs.dev5_reg_004 = ncmd_tmp1;
		if ( check_cb == 1 )
		{
			vSetEventFlag(ncmd_evid, 1u);
		}
		return 0;
	}
	if ( check_cb == 1 )
	{
		vSetEventFlag(ncmd_evid, 1u);
	}
	if ( cdvdman_verbose <= 0 )
	{
		return -1;
	}
	LOBYTE(disk_ready_status) = dev5_regs.dev5_reg_005;
	Kprintf("set_cd_commnad Error\tstat %02x\n", (unsigned __int8)disk_ready_status);
	return -1;
}
// 40E608: using guessed type char cdvdman_ncmd;
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00409AB8) --------------------------------------------------------
int __cdecl sceCdApplyNCmd(u8 cmdNum, const void *inBuff, u16 inBuffSize)
{
	int inbuffsize_tmp; // $s3
	int i; // $a0

	inbuffsize_tmp = inBuffSize;
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("Apply NCmd call cmd= 0x%02x\n", cmdNum);
	}
	for ( i = cmdNum; cdvdman_send_ncmd(i, inBuff, inbuffsize_tmp, 0, 0, 1) < 0; i = cmdNum )
	{
		vDelayThread(2000);
	}
	sceCdSync(4);
	return 1;
}

//----- (00409B58) --------------------------------------------------------
int sceCdCheckCmd(void)
{
	return cdvdman_istruct.wait_flag;
}

//----- (00409B6C) --------------------------------------------------------
int __cdecl cdvdman_mediactl(int code)
{
	vu8 dev5_reg_00B; // $v0
	int reg_00B_tmp_1; // $a1
	int chflags_tmp; // $a0
	int chflags_tmp2; // $v0
	int restmp; // $s0
	int code_tmp1; // $a0
	int chflags_tmp3; // $v0
	vu8 dev5_reg_00A; // $v0
	vu8 reg_00B_tmp_2; // $v0
	u32 efbits; // [sp+18h] [-8h] BYREF
	int rdata; // [sp+1Ch] [-4h] BYREF

	rdata = 0;
	if ( PollEventFlag(scmd_evid, 1u, 16, &efbits) == -421 )
	{
		return 0;
	}
	dev5_reg_00B = dev5_regs.dev5_reg_00B;
	reg_00B_tmp_1 = dev5_reg_00B & 1;
	chflags_tmp = 0;
	if ( reg_00B_tmp_1 == cdvdman_chmedia )
	{
		code_tmp1 = code;
		chflags_tmp3 = cdvdman_chflags[code];
		restmp = 1;
		if ( chflags_tmp3 )
		{
			cdvdman_chflags[code_tmp1] = 0;
		}
		else
		{
			restmp = 0;
		}
	}
	else
	{
		chflags_tmp2 = 0;
		do
		{
			cdvdman_chflags[chflags_tmp2] = chflags_tmp++ != code;
			chflags_tmp2 = chflags_tmp;
		}
		while ( chflags_tmp < 4 );
		restmp = 1;
	}
	dev5_reg_00A = dev5_regs.dev5_reg_00A;
	if ( (dev5_reg_00A & 1) != reg_00B_tmp_1 )
	{
		while ( !set_prev_command(5, 0, 0, (char *)&rdata, 1, 0) || rdata )
		{
			vDelayThread(4000);
		}
	}
	reg_00B_tmp_2 = dev5_regs.dev5_reg_00B;
	cdvdman_chmedia = reg_00B_tmp_2 & 1;
	vSetEventFlag(scmd_evid, 1u);
	return restmp;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00409CD4) --------------------------------------------------------
int sceCdGetError(void)
{
	if ( cdvdman_istruct.last_error && cdvdman_verbose > 0 )
	{
		Kprintf("sceCdGetError: 0x%02x\n", (unsigned __int8)cdvdman_istruct.last_error);
	}
	return (unsigned __int8)cdvdman_istruct.last_error;
}

//----- (00409D38) --------------------------------------------------------
int __cdecl cdvdman_get_last_command()
{
	return (unsigned __int8)cdvdman_istruct.cdvdman_command;
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
	vu8 dev5_reg_00F; // $v0
	int i; // $s0
	bool condtmp; // dc
	int result; // $v0
	DMA3PARAM b18; // [sp+18h] [-28h] BYREF
	char ndata[16]; // [sp+30h] [-10h] BYREF

	dev5_reg_00F = dev5_regs.dev5_reg_00F;
	i = 0;
	if ( !dev5_reg_00F )
	{
		return 1;
	}
	while ( 1 )
	{
		Kprintf("CMD_READP call\n");
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
		b18.cdvdreg_howto = 128;
		b18.dma3_blkwords = 32;
		b18.dma3_blkcount = 128;
		b18.dma3_csectors = 0;
		b18.dma3_msectors = 0;
		b18.dma3_callback = 0;
		b18.dma3_maddress = cdvdman_ptoc;
		condtmp = cdvdman_send_ncmd(6, ndata, 11, 5, &b18, 1) < 0;
		result = 0;
		if ( condtmp )
		{
			break;
		}
		sceCdSync(3);
		i += 8;
		if ( i >= 48 )
		{
			return 1;
		}
	}
	return result;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (00409EE4) --------------------------------------------------------
int sceCdStandby(void)
{
	u8 disk_type; // $v0
	bool condtmp; // dc
	BOOL condtmp2; // $v0
	int ncmdres; // $v0
	DMA3PARAM b18; // [sp+18h] [-28h] BYREF
	char ndata[16]; // [sp+30h] [-10h] BYREF

	disk_type = dev5_regs.dev5_reg_00F;
	condtmp = disk_type >= 0x14u;
	condtmp2 = disk_type < 0x10u;
	if ( condtmp || condtmp2 )
	{
		ncmdres = cdvdman_send_ncmd(2, 0, 0, 5, 0, 1);
	}
	else
	{
		ndata[0] = 16;
		ndata[4] = 1;
		ndata[9] = 1;
		b18.cdvdreg_howto = 128;
		b18.dma3_blkwords = 32;
		b18.dma3_blkcount = 16;
		ndata[3] = 0;
		ndata[2] = 0;
		ndata[1] = 0;
		ndata[7] = 0;
		ndata[6] = 0;
		ndata[5] = 0;
		ndata[8] = 0;
		ndata[10] = 0;
		b18.dma3_csectors = 0;
		b18.dma3_msectors = 0;
		b18.dma3_callback = 0;
		b18.dma3_maddress = cdvdman_ptoc;
		ncmdres = cdvdman_send_ncmd(6, ndata, 11, 5, &b18, 1);
	}
	return ncmdres >= 0;
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
	Kprintf("Cmd Time Out %d(msec)\n", s->lo / 0x9000);
	dev5_regs.dev5_reg_007 = 1;
	s->lo = 0;
	return 0;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (0040A0EC) --------------------------------------------------------
int __cdecl cdvdman_readtoc(u8 *toc, int param, int func)
{
	vu8 dev5_reg_00F; // $v0
	int disk_type; // $v1
	int result; // $v0
	int errcond; // $s0
	DMA3PARAM b18; // [sp+18h] [-28h] BYREF
	iop_sys_clock_t clk; // [sp+30h] [-10h] BYREF
	char ndata[8]; // [sp+38h] [-8h] BYREF

	dev5_reg_00F = dev5_regs.dev5_reg_00F;
	disk_type = dev5_reg_00F;
	if ( dev5_reg_00F == 20 )
	{
LABEL_12:
		b18.cdvdreg_howto = 132;
		b18.dma3_blkwords = 4;
		b18.dma3_blkcount = 129;
		b18.dma3_maddress = toc;
		b18.dma3_msectors = 0;
		b18.dma3_csectors = 0;
		b18.dma3_callback = 0;
		ndata[0] = param;
		goto LABEL_13;
	}
	if ( dev5_reg_00F < 0x15u )
	{
		result = 0;
		if ( disk_type < 16 )
		{
			return result;
		}
		goto LABEL_11;
	}
	if ( dev5_reg_00F != 253 )
	{
		if ( dev5_reg_00F >= 0xFEu )
		{
			result = 0;
			if ( disk_type != 254 )
			{
				return result;
			}
		}
		else
		{
			result = 0;
			if ( disk_type != 252 )
			{
				return result;
			}
		}
		goto LABEL_12;
	}
LABEL_11:
	b18.cdvdreg_howto = 128;
	b18.dma3_blkwords = 32;
	b18.dma3_blkcount = 8;
	b18.dma3_maddress = toc;
	b18.dma3_msectors = 0;
	b18.dma3_csectors = 0;
	b18.dma3_callback = 0;
	ndata[0] = 0;
LABEL_13:
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
	if ( cdvdman_minver_10700 )
	{
		if ( !sceCdPause() )
		{
			return 0;
		}
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
	u32 result; // $v0
	int sector_sizes[4]; // [sp+10h] [-10h]

	sector_sizes[0] = 2048;
	sector_sizes[1] = 2328;
	sector_sizes[2] = 2340;
	if ( !cdvdman_istruct.recover_status || (result = 0, cdvdman_istruct.recover_status == 3) )
	{
		if ( cdvdman_cmdfunc == 2 || cdvdman_cmdfunc == 12 )
		{
			return dmac_ch_get_madr(3u) - (_DWORD)cdvdman_readbuf;
		}
		if ( cdvdman_istruct.read2_flag )
		{
			return cdvdman_readptr * sector_sizes[cdvdman_istruct.cdvdman_pattern];
		}
		if ( cdvdman_cmdfunc == 1 )
		{
			return dmac_ch_get_madr(3u) - (_DWORD)cdvdman_readbuf;
		}
		else
		{
			return 0;
		}
	}
	return result;
}

//----- (0040A398) --------------------------------------------------------
int __cdecl cdvdman_speedctl(u32 spindlctrl, int dvdflag, u32 maxlsn)
{
	int retval; // $v1
	u32 maxlsn_chk; // $v0

	switch ( spindlctrl )
	{
		case 0u:
			retval = 4;
			goto LABEL_14;
		case 1u:
			retval = 133;
			if ( dvdflag )
			{
				retval = 131;
				if ( !cdvdman_minver_10700 )
				{
					if ( cdvdman_istruct.opo_or_para )
					{
						if ( maxlsn >= cdvdman_istruct.layer_1_lsn )
						{
							maxlsn -= cdvdman_istruct.layer_1_lsn;
						}
						maxlsn_chk = 0x165000;
					}
					else
					{
						maxlsn_chk = 0x128000;
					}
					if ( maxlsn >= maxlsn_chk )
					{
						retval = 130;
						if ( cdvdman_verbose > 0 )
						{
							Kprintf("Kprob Spd D lsn= %d\n", maxlsn);
							return 130;
						}
					}
				}
			}
			return retval;
		case 2u:
		case 0xEu:
			goto LABEL_28;
		case 3u:
			return 2;
		case 4u:
			retval = 131;
LABEL_14:
			if ( dvdflag )
			{
				return 2;
			}
			return retval;
		case 5u:
			retval = 4;
			goto LABEL_21;
		case 0xAu:
			return 64;
		case 0xCu:
			retval = 2;
			if ( dvdflag )
			{
				return 4;
			}
			return retval;
		case 0xFu:
			goto LABEL_26;
		case 0x10u:
			retval = 131;
			goto LABEL_25;
		case 0x11u:
			retval = 132;
LABEL_25:
			if ( dvdflag )
			{
LABEL_26:
				retval = 130;
			}
			break;
		case 0x12u:
			retval = 131;
			if ( dvdflag )
			{
LABEL_28:
				retval = 1;
			}
			break;
		case 0x14u:
			retval = 5;
LABEL_21:
			if ( dvdflag )
			{
				retval = 3;
			}
			break;
		default:
			retval = 133;
			if ( dvdflag )
			{
				retval = 131;
			}
			break;
	}
	return retval;
}

//----- (0040A4F8) --------------------------------------------------------
int __cdecl cdvdman_isdvd()
{
	vu8 dev5_reg_00F; // $v0
	int disk_type; // $v1
	bool condtmp1; // dc
	u32 condtmp2; // $v0

	dev5_reg_00F = dev5_regs.dev5_reg_00F;
	disk_type = dev5_reg_00F;
	condtmp1 = dev5_reg_00F == 20;
	condtmp2 = dev5_reg_00F < 0x15u;
	if ( condtmp1 )
	{
LABEL_12:
		cdvdman_istruct.tray_is_open = 1;
		return 1;
	}
	if ( !condtmp2 )
	{
		if ( disk_type == 253 )
		{
LABEL_11:
			cdvdman_istruct.tray_is_open = 1;
			return 0;
		}
		if ( disk_type >= 254 )
		{
			if ( disk_type != 254 )
			{
				return 0;
			}
		}
		else if ( disk_type != 252 )
		{
			return 0;
		}
		goto LABEL_12;
	}
	if ( disk_type >= 16 )
	{
		goto LABEL_11;
	}
	return 0;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (0040A5A8) --------------------------------------------------------
int __cdecl sceCdRead0_Rty(u32 lsn, u32 nsec, void *buf, sceCdRMode *mode, int ncmd, int dintrsec, void *func)
{
	int is_dvd; // $v0
	char speedctl_res; // $v0
	s16 nsec_tmp; // $v1
	int datapattern; // $a3
	u16 howto_tmp; // $v0
	int ncmd_in; // $a0
	int ncmd_out; // $a3
	bool ncmd_res; // dc
	int result; // $v0
	DMA3PARAM b18; // [sp+18h] [-28h] BYREF
	char ndata[11]; // [sp+30h] [-10h] BYREF

	cdvdman_readbuf = buf;
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("sceCdRead0_Rty Lsn:%d nsec:%d dintrnsec %d func %08x\n", lsn, nsec, dintrsec, func);
	}
	*(_DWORD *)ndata = lsn;
	*(_DWORD *)&ndata[4] = nsec;
	ndata[8] = mode->trycount;
	is_dvd = cdvdman_isdvd();
	speedctl_res = cdvdman_speedctl(mode->spindlctrl, is_dvd, lsn + nsec);
	nsec_tmp = 1;
	ndata[9] = speedctl_res;
	b18.dma3_csectors = dintrsec;
	b18.dma3_callback = (int (__cdecl *)(void *, int, int))func;
	b18.dma3_msectors = nsec;
	b18.dma3_maddress = buf;
	if ( !(_WORD)dintrsec )
	{
		nsec_tmp = nsec;
	}
	if ( ncmd == 6 )
	{
		ndata[10] = mode->datapattern;
		datapattern = mode->datapattern;
		if ( datapattern == 1 )
		{
			b18.dma3_blkcount = 97 * nsec_tmp;
			howto_tmp = 134;
			b18.dma3_blkwords = 6;
		}
		else if ( mode->datapattern >= 2u && datapattern == 2 )
		{
			b18.dma3_blkwords = 15;
			b18.dma3_blkcount = 39 * nsec_tmp;
			howto_tmp = 143;
		}
		else
		{
			b18.dma3_blkwords = 32;
			b18.dma3_blkcount = 16 * nsec_tmp;
			howto_tmp = 128;
		}
		b18.cdvdreg_howto = howto_tmp;
		ncmd_in = 6;
		ncmd_out = 1;
LABEL_16:
		ncmd_res = cdvdman_send_ncmd(ncmd_in, ndata, 11, ncmd_out, &b18, 0) >= 0;
		result = 1;
		if ( ncmd_res )
		{
			return result;
		}
		return 0;
	}
	ncmd_in = 8;
	if ( ncmd == 8 )
	{
		ncmd_out = 14;
		b18.cdvdreg_howto = 140;
		b18.dma3_blkwords = 12;
		b18.dma3_blkcount = 43 * nsec_tmp;
		ndata[10] = 0;
		goto LABEL_16;
	}
	return 0;
}

//----- (0040A79C) --------------------------------------------------------
int __cdecl sceCdRead0(u32 lsn, u32 sectors, void *buffer, sceCdRMode *mode, int csec, void *callback)
{
	bool condtmp; // dc
	int result; // $v0
	s16 nsec_tmp; // $a0
	int datapattern; // $v1
	u16 howto_tmp; // $v0
	vu8 dev5_reg_00F; // $v0
	int reg_00F_tmp; // $v1
	u32 condtmp2; // $v0
	int dvd_flag; // $a1
	int ncmd_evid_tmp; // $a0
	u8 datapattern_tmp; // $a0
	DMA3PARAM b18; // [sp+20h] [-30h] BYREF
	char ndata[11]; // [sp+38h] [-18h] BYREF
	u32 efbits[2]; // [sp+48h] [-8h] BYREF

	condtmp = PollEventFlag(ncmd_evid, 1u, 16, efbits) == -421;
	result = 0;
	if ( !condtmp )
	{
		if ( cdvdman_verbose > 0 )
		{
			Kprintf(
				"DVD/CD sceCdRead0 sec %d num %d spin %d trycnt %d dptn %d adr %08x\n",
				lsn,
				sectors,
				mode->spindlctrl,
				mode->trycount,
				mode->datapattern,
				buffer);
		}
		cdvdman_readbuf = buffer;
		if ( csec )
		{
			if ( sectors < csec )
			{
				b18.dma3_csectors = sectors;
			}
			else
			{
				b18.dma3_csectors = csec;
			}
		}
		else
		{
			b18.dma3_csectors = 0;
		}
		nsec_tmp = 1;
		b18.dma3_callback = (int (__cdecl *)(void *, int, int))callback;
		b18.dma3_msectors = sectors;
		if ( !csec )
		{
			nsec_tmp = sectors;
		}
		datapattern = mode->datapattern;
		if ( datapattern == 1 )
		{
			b18.dma3_blkwords = 6;
			b18.dma3_blkcount = 97 * nsec_tmp;
			howto_tmp = 134;
		}
		else if ( mode->datapattern >= 2u && datapattern == 2 )
		{
			b18.dma3_blkwords = 15;
			b18.dma3_blkcount = 39 * nsec_tmp;
			howto_tmp = 143;
		}
		else
		{
			b18.dma3_blkwords = 32;
			b18.dma3_blkcount = 16 * nsec_tmp;
			howto_tmp = 128;
		}
		b18.cdvdreg_howto = howto_tmp;
		dev5_reg_00F = dev5_regs.dev5_reg_00F;
		reg_00F_tmp = dev5_reg_00F;
		condtmp = dev5_reg_00F < 0x10u;
		condtmp2 = dev5_reg_00F < 0x14u;
		if ( condtmp )
		{
			goto LABEL_32;
		}
		if ( condtmp2 )
		{
			dvd_flag = 0;
			if ( cdvdman_mmode != 1 && cdvdman_mmode != 255 )
			{
				goto LABEL_32;
			}
		}
		else
		{
			if ( reg_00F_tmp != 20 )
			{
LABEL_32:
				ncmd_evid_tmp = ncmd_evid;
				goto LABEL_33;
			}
			dvd_flag = 1;
			if ( cdvdman_mmode != 2 && cdvdman_mmode != 255 )
			{
				ncmd_evid_tmp = ncmd_evid;
LABEL_33:
				vSetEventFlag(ncmd_evid_tmp, 1u);
				return 0;
			}
		}
		cdvdman_istruct.dvd_flag = dvd_flag;
		cdvdman_istruct.read_mode = *mode;
		cdvdman_istruct.read_callback = callback;
		cdvdman_istruct.read_chunk = b18.dma3_csectors;
		cdvdman_istruct.read_lsn = lsn;
		cdvdman_istruct.read_sectors = sectors;
		*(_DWORD *)ndata = lsn;
		*(_DWORD *)&ndata[4] = sectors;
		ndata[8] = mode->trycount;
		ndata[9] = cdvdman_speedctl(mode->spindlctrl, dvd_flag, lsn + sectors);
		datapattern_tmp = mode->datapattern;
		cdvdman_istruct.read_buf = buffer;
		ndata[10] = datapattern_tmp;
		b18.dma3_maddress = buffer;
		if ( cdvdman_verbose > 0 )
		{
			Kprintf("Read Command call\n");
		}
		if ( cdvdman_send_ncmd(6, ndata, 11, 1, &b18, 0) >= 0 )
		{
			vSetEventFlag(ncmd_evid, 1u);
			return 1;
		}
		goto LABEL_32;
	}
	return result;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (0040AA9C) --------------------------------------------------------
int __cdecl read_cdvd_cb(cdvdman_internal_struct_t *common)
{
	int cdlayer; // $s6
	int sblock; // $s5
	int sectorcnti; // $s2
	int dvoff; // $s3
	int cdoff; // $s4
	u32 cdreadlsn; // $s1
	int syncdec_res_1; // $s1
	int syncdec_res_2; // $s1
	int syncdec_res_3; // $s1
	char syncdec_res_4; // $v1
	int intr_read_state_tmp; // $v0
	unsigned int layer_1_lsn; // $v1
	int errlsn; // $a1
	int cdvdman_pattern; // $v1
	unsigned int size; // $s3
	int index_; // $s2
	int offset_; // $s1
	const char *tocptr; // $a1
	sceCdlLOCCD cdrloc; // [sp+10h] [-8h] BYREF

	cdlayer = 0;
	sblock = 0;
	sectorcnti = 0;
	if ( common->dma3prm.dma3_csectors )
	{
		dvoff = 0;
		cdoff = 0;
		while ( 1 )
		{
			if ( common->read2_flag == 3 )
			{
				sblock = 2340;
				cdrloc.minute = cdvdman_syncdec(
													common->dec_state,
													common->check_version,
													common->dec_shift,
													cdvdman_ptoc[cdoff]);
				cdrloc.second = cdvdman_syncdec(
													common->dec_state,
													common->check_version,
													common->dec_shift,
													cdvdman_ptoc[cdoff + 1]);
				cdrloc.sector = cdvdman_syncdec(
													common->dec_state,
													common->check_version,
													common->dec_shift,
													cdvdman_ptoc[cdoff + 2]);
				cdreadlsn = sceCdPosToInt(&cdrloc);
			}
			else
			{
				sblock = 2064;
				syncdec_res_1 = (unsigned __int8)cdvdman_syncdec(
																					 common->dec_state,
																					 common->check_version,
																					 common->dec_shift,
																					 cdvdman_ptoc[dvoff + 3]);
				syncdec_res_2 = syncdec_res_1
											+ ((unsigned __int8)cdvdman_syncdec(
																						common->dec_state,
																						common->check_version,
																						common->dec_shift,
																						cdvdman_ptoc[dvoff + 2]) << 8);
				syncdec_res_3 = syncdec_res_2
											+ ((unsigned __int8)cdvdman_syncdec(
																						common->dec_state,
																						common->check_version,
																						common->dec_shift,
																						cdvdman_ptoc[dvoff + 1]) << 16);
				syncdec_res_4 = cdvdman_syncdec(
													common->dec_state,
													common->check_version,
													common->dec_shift,
													cdvdman_ptoc[dvoff]);
				cdlayer = syncdec_res_4 & 1;
				if ( !common->cdvdman_dma3sec && !common->interupt_read_state )
				{
					intr_read_state_tmp = syncdec_res_4 & 0xC;
					if ( (syncdec_res_4 & 0xC) != 0 )
					{
						common->interupt_read_state = intr_read_state_tmp;
						if ( sectorcnti )
						{
							common->interupt_read_state = intr_read_state_tmp | 0x80;
						}
					}
				}
				cdreadlsn = syncdec_res_3 - 196608;
				if ( common->opo_or_para )
				{
					layer_1_lsn = common->layer_1_lsn;
					if ( common->cdvdman_lsn + common->cdvdman_csec + sectorcnti >= layer_1_lsn && common->opo_or_para == 1 )
					{
						cdreadlsn += layer_1_lsn;
					}
				}
			}
			errlsn = common->cdvdman_lsn + common->cdvdman_csec + common->cdvdman_dma3sec + sectorcnti;
			if ( cdreadlsn != errlsn )
			{
				break;
			}
			dvoff += 2064;
			++sectorcnti;
			cdoff += 2340;
			if ( sectorcnti >= common->dma3prm.dma3_csectors )
			{
				goto LABEL_18;
			}
		}
		if ( cdvdman_verbose > 0 )
		{
			Kprintf("Read_IOP Sector_ID error lsn= %d readlsn= %d layer= %d\n", errlsn, cdreadlsn, cdlayer);
		}
	}
LABEL_18:
	if ( sectorcnti == common->dma3prm.dma3_csectors )
	{
		cdvdman_pattern = common->cdvdman_pattern;
		if ( cdvdman_pattern == 2 )
		{
			cdvdman_memcpy(
				(char *)(common->cdvdman_rbuffer + 2340 * common->cdvdman_dma3sec),
				(const char *)cdvdman_ptoc,
				2340 * sectorcnti);
		}
		else
		{
			size = 2328;
			if ( !cdvdman_pattern )
			{
				size = 2048;
			}
			index_ = 0;
			if ( common->dma3prm.dma3_csectors )
			{
				offset_ = 12;
				do
				{
					tocptr = (const char *)&cdvdman_ptoc[offset_];
					offset_ += sblock;
					cdvdman_memcpy((char *)(common->cdvdman_rbuffer + (common->cdvdman_dma3sec + index_++) * size), tocptr, size);
				}
				while ( index_ < common->dma3prm.dma3_csectors );
			}
		}
		cdvdman_readptr = common->cdvdman_csec + common->cdvdman_dma3sec;
	}
	else
	{
		++common->sync_error;
	}
	return 1;
}

//----- (0040AE20) --------------------------------------------------------
int __cdecl cdvdman_read(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int decflag, int shift, int ef1, int ef2)
{
	int read0_res; // $s0
	u32 sectors_tmp; // $s2
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
				return 0;
			}
			return 0;
		}
		lsn = sceCdLsnDualChg(lsn);
	}
	else if ( mode->datapattern == 1 )
	{
LABEL_12:
		CpuSuspendIntr(&state);
		read0_res = sceCdRead0(lsn, sectors, buf, mode, 0, 0);
		if ( ef1 )
		{
			vSetEventFlag(ef1, ef2);
		}
		CpuResumeIntr(state);
		return read0_res;
	}
	if ( cdvdman_cd36key && !cdvdman_istruct.dec_state )
	{
		if ( mode->spindlctrl == 1 )
		{
			mode->spindlctrl = 0;
		}
		goto LABEL_12;
	}
	CpuSuspendIntr(&state);
	if ( (sceCdDiskReady(8) & 0xC0) != 64 || cdvdman_istruct.read2_flag )
	{
		if ( cdvdman_verbose > 0 )
		{
			Kprintf(
				"sceCdRead: Double Booking error r2f= %d waf= %d\n",
				cdvdman_istruct.read2_flag,
				cdvdman_istruct.wait_flag);
		}
LABEL_32:
		if ( ef1 )
		{
			vSetEventFlag(ef1, ef2);
		}
		CpuResumeIntr(state);
		return 0;
	}
	if ( decflag )
	{
		cdvdman_istruct.dec_shift = shift;
		cdvdman_istruct.dec_state = 1;
	}
	cdvdman_readbuf = buf;
	cdvdman_readptr = 0;
	cdvdman_istruct.cdvdman_lsn = lsn;
	cdvdman_istruct.cdvdman_csec = 0;
	cdvdman_istruct.cdvdman_nsec = sectors;
	cdvdman_istruct.cdvdman_rbuffer = (int)buf;
	cdvdman_istruct.cdvdman_pattern = 0;
	cdvdman_istruct.cdvdman_cdrmode.trycount = mode->trycount;
	cdvdman_istruct.cdvdman_cdrmode.spindlctrl = mode->spindlctrl;
	cdvdman_istruct.sync_error = 0;
	cdvdman_istruct.interupt_read_state = 0;
	sectors_tmp = sectors;
	if ( sectors >= 0x41 )
	{
		if ( (lsn & 0xF) != 0 )
		{
			sectors_tmp = 16 - (lsn & 0xF);
		}
		else
		{
			sectors_tmp = 64;
		}
	}
	cdvdman_istruct.cdvdman_rsec = sectors_tmp;
	cdvdman_racb_to.hi = 0;
	cdvdman_racb_to.lo = 0x9000 * sceCdSC(0xFFFFFFF1, &sc_result);
	vSetAlarm(&cdvdman_racb_to, (unsigned int (__cdecl *)(void *))alarm_cb_read, &cdvdman_racb_to);
	if ( dvd )
	{
		cdvdman_istruct.cdvdman_cdrmode.datapattern = 0;
		cdvdman_istruct.read2_flag = 1;
		read_res = sceCdRV(lsn, sectors_tmp, cdvdman_ptoc, mode, 16, read_cdvd_cb);
	}
	else
	{
		cdvdman_istruct.cdvdman_cdrmode.datapattern = 2;
		cdvdman_istruct.cdvdman_pattern = mode->datapattern;
		cdvdman_istruct.read2_flag = 3;
		read_res = sceCdRead0(lsn, sectors_tmp, cdvdman_ptoc, &cdvdman_istruct.cdvdman_cdrmode, 16, read_cdvd_cb);
	}
	if ( !read_res )
	{
		cdvdman_istruct.last_error = -2;
		cdvdman_istruct.cdvdman_rsec = 0;
		cdvdman_istruct.read2_flag = 0;
		if ( cdvdman_istruct.dec_state )
		{
			cdvdman_istruct.dec_shift = 0;
			cdvdman_istruct.check_version = 0;
			cdvdman_istruct.dec_state = 0;
			sceCdDecSet(0, 0, 0);
		}
		vCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb_read, &cdvdman_racb_to);
		goto LABEL_32;
	}
	if ( ef1 )
	{
		vSetEventFlag(ef1, ef2);
	}
	CpuResumeIntr(state);
	return 1;
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

	CpuSuspendIntr(&state);
	vReferEventFlagStatus(fio_fsv_evid, &efinfo);
	if ( (efinfo.currBits & 1) != 0 )
	{
		vClearEventFlag(fio_fsv_evid, 0xFFFFFFFE);
		CpuResumeIntr(state);
		return cdvdman_read(lbn, sectors, buffer, mode, 0, 0, fio_fsv_evid, 1);
	}
	else
	{
		CpuResumeIntr(state);
		return 0;
	}
}

//----- (0040B2EC) --------------------------------------------------------
int __cdecl cdvdman_syncdec(int decflag, int decxor, int shift, u32 data)
{
	if ( decflag )
	{
		return (unsigned __int8)(((unsigned __int8)data << (shift % 8)) | ((unsigned __int8)data >> (8 - shift % 8))) ^ (unsigned __int8)decxor;
	}
	else
	{
		return (unsigned __int8)data;
	}
}

//----- (0040B338) --------------------------------------------------------
int __cdecl dummy_nullsub()
{
	return 0;
}

//----- (0040B340) --------------------------------------------------------
void __cdecl Read2intrCDVD(int read2_flag)
{
	char interupt_read_state; // $a0
	char last_err_tmp; // $v1
	int lsn_csec_tmp; // $a0
	u32 lsn_tmp; // $a0
	int read_res1; // $v0
	int cdsectorsz; // $v1
	int rsec_tmp; // $v1
	int read_res2; // $v0
	int sc_result[2]; // [sp+18h] [-8h] BYREF

	iCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb_read, &cdvdman_racb_to);
	if ( cdvdman_istruct.last_error || cdvdman_retries >= 5 )
	{
		if ( !cdvdman_istruct.last_error )
		{
			cdvdman_istruct.last_error = -3;
		}
		cdvdman_istruct.read2_flag = 0;
		cdvdman_retries = 0;
		cdvdman_rtindex = 0;
		cdvdman_readptr = 0;
		if ( cdvdman_istruct.dec_state )
		{
			cdvdman_istruct.dec_shift = 0;
			cdvdman_istruct.check_version = 0;
			cdvdman_istruct.dec_state = 0;
		}
		cdvdman_istruct.interupt_read_state = 0;
	}
	else if ( !cdvdman_istruct.interupt_read_state
				 || (interupt_read_state = cdvdman_istruct.interupt_read_state,
						 cdvdman_istruct.interupt_read_state = 0,
						 cdvdman_istruct.cdvdman_csec) )
	{
		if ( cdvdman_istruct.sync_error )
		{
			if ( !cdvdman_rtindex )
			{
				cdvdman_rtindex = 3;
				++cdvdman_retries;
			}
			cdvdman_istruct.sync_error = 0;
			lsn_csec_tmp = cdvdman_istruct.cdvdman_lsn + cdvdman_istruct.cdvdman_csec;
			if ( (unsigned int)(cdvdman_istruct.cdvdman_lsn + cdvdman_istruct.cdvdman_csec) >= 0x30 )
			{
				lsn_tmp = lsn_csec_tmp - 16 * (cdvdman_rtindex - 1);
			}
			else
			{
				lsn_tmp = lsn_csec_tmp + 16 * (cdvdman_rtindex - 1);
			}
			if ( read2_flag == 3 )
			{
				read_res1 = sceCdRead0(
											lsn_tmp,
											cdvdman_istruct.cdvdman_rsec,
											cdvdman_ptoc,
											&cdvdman_istruct.cdvdman_cdrmode,
											16,
											read_cdvd_cb);
			}
			else
			{
				read_res1 = sceCdRV(
											lsn_tmp,
											cdvdman_istruct.cdvdman_rsec,
											cdvdman_ptoc,
											&cdvdman_istruct.cdvdman_cdrmode,
											16,
											read_cdvd_cb);
			}
			if ( read_res1 )
			{
				cdvdman_racb_to.hi = 0;
				cdvdman_racb_to.lo = 0x9000 * sceCdSC(0xFFFFFFF1, sc_result);
				iSetAlarm(&cdvdman_racb_to, (unsigned int (__cdecl *)(void *))alarm_cb_read, &cdvdman_racb_to);
			}
			else
			{
				if ( cdvdman_verbose > 0 )
				{
					Kprintf("Retry Read Fatal Error\n");
				}
				cdvdman_istruct.last_error = 19;
				cdvdman_istruct.read2_flag = 0;
				cdvdman_retries = 0;
				cdvdman_rtindex = 0;
				cdvdman_readptr = 0;
				if ( cdvdman_istruct.dec_state )
				{
					cdvdman_istruct.dec_shift = 0;
					cdvdman_istruct.check_version = 0;
					cdvdman_istruct.dec_state = 0;
				}
			}
			if ( cdvdman_rtindex )
			{
				--cdvdman_rtindex;
			}
		}
		else
		{
			cdvdman_retries = 0;
			cdsectorsz = 2340;
			if ( cdvdman_istruct.cdvdman_pattern != 2 )
			{
				cdsectorsz = 2328;
				if ( !cdvdman_istruct.cdvdman_pattern )
				{
					cdsectorsz = 2048;
				}
			}
			cdvdman_istruct.cdvdman_rbuffer += cdsectorsz * cdvdman_istruct.cdvdman_rsec;
			cdvdman_istruct.cdvdman_csec += cdvdman_istruct.cdvdman_rsec;
			if ( cdvdman_istruct.cdvdman_csec < (unsigned int)cdvdman_istruct.cdvdman_nsec )
			{
				if ( (unsigned int)(cdvdman_istruct.cdvdman_csec + 64) < cdvdman_istruct.cdvdman_nsec )
				{
					rsec_tmp = 64;
				}
				else
				{
					rsec_tmp = cdvdman_istruct.cdvdman_nsec - cdvdman_istruct.cdvdman_csec;
				}
				cdvdman_istruct.cdvdman_rsec = rsec_tmp;
				if ( read2_flag == 3 )
				{
					read_res2 = sceCdRead0(
												cdvdman_istruct.cdvdman_lsn + cdvdman_istruct.cdvdman_csec,
												cdvdman_istruct.cdvdman_rsec,
												cdvdman_ptoc,
												&cdvdman_istruct.cdvdman_cdrmode,
												16,
												read_cdvd_cb);
				}
				else
				{
					read_res2 = sceCdRV(
												cdvdman_istruct.cdvdman_lsn + cdvdman_istruct.cdvdman_csec,
												cdvdman_istruct.cdvdman_rsec,
												cdvdman_ptoc,
												&cdvdman_istruct.cdvdman_cdrmode,
												16,
												read_cdvd_cb);
				}
				if ( read_res2 )
				{
					cdvdman_racb_to.hi = 0;
					cdvdman_racb_to.lo = 0x9000 * sceCdSC(0xFFFFFFF1, sc_result);
					iSetAlarm(&cdvdman_racb_to, (unsigned int (__cdecl *)(void *))alarm_cb_read, &cdvdman_racb_to);
				}
				else
				{
					cdvdman_istruct.last_error = 19;
					cdvdman_istruct.read2_flag = 0;
					cdvdman_readptr = 0;
					if ( cdvdman_istruct.dec_state )
					{
						cdvdman_istruct.dec_shift = 0;
						cdvdman_istruct.check_version = 0;
						cdvdman_istruct.dec_state = 0;
					}
				}
			}
			else
			{
				cdvdman_istruct.read2_flag = 0;
				cdvdman_readptr = 0;
				if ( cdvdman_istruct.dec_state )
				{
					cdvdman_istruct.dec_shift = 0;
					cdvdman_istruct.check_version = 0;
					cdvdman_istruct.dec_state = 0;
				}
			}
		}
	}
	else
	{
		last_err_tmp = 32;
		if ( (interupt_read_state & 0x80) != 0 )
		{
			last_err_tmp = -3;
		}
		cdvdman_istruct.last_error = last_err_tmp;
		if ( cdvdman_verbose > 0 )
		{
			Kprintf("IPIerr emu Hit Dummy Err %02x\n", (unsigned __int8)cdvdman_istruct.last_error);
		}
		cdvdman_istruct.read2_flag = 0;
		cdvdman_retries = 0;
		cdvdman_rtindex = 0;
		cdvdman_readptr = 0;
		if ( cdvdman_istruct.dec_state )
		{
			cdvdman_istruct.dec_shift = 0;
			cdvdman_istruct.check_version = 0;
			cdvdman_istruct.dec_state = 0;
		}
	}
}

//----- (0040B89C) --------------------------------------------------------
int __cdecl sceCdReadChain(sceCdRChain *tag, sceCdRMode *mode)
{
	return 0;
}

//----- (0040B8A4) --------------------------------------------------------
int __cdecl cdvdman_readfull(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int flag)
{
	int datapattern; // $v1
	u16 howto_tmp; // $v0
	u16 blktmp_tmp; // $v0
	vu8 dev5_reg_00F; // $v0
	int disk_type; // $v1
	bool condtmp; // dc
	u32 condtmp2; // $v0
	int result; // $v0
	int ncmd_num; // $s1
	u8 datapattern_tmp; // $v0
	int outlen; // $a3
	DMA3PARAM b18; // [sp+18h] [-28h] BYREF
	char ndata[11]; // [sp+30h] [-10h] BYREF

	if ( cdvdman_verbose > 0 )
	{
		Kprintf("lsn:%d nsec:%d buf:% cmdmode:%d\n", lsn, sectors, buf, flag);
	}
	cdvdman_readbuf = buf;
	b18.dma3_csectors = 0;
	b18.dma3_msectors = 0;
	b18.dma3_callback = 0;
	datapattern = mode->datapattern;
	if ( datapattern == 1 )
	{
		b18.dma3_blkwords = 8;
		b18.dma3_blkcount = 74 * sectors;
		howto_tmp = 136;
		goto LABEL_12;
	}
	if ( mode->datapattern < 2u )
	{
		b18.dma3_blkwords = 12;
		goto LABEL_10;
	}
	if ( datapattern != 2 )
	{
		b18.dma3_blkwords = 12;
LABEL_10:
		blktmp_tmp = 49 * sectors;
		goto LABEL_11;
	}
	b18.dma3_blkwords = 12;
	blktmp_tmp = 51 * sectors;
LABEL_11:
	b18.dma3_blkcount = blktmp_tmp;
	howto_tmp = 140;
LABEL_12:
	b18.cdvdreg_howto = howto_tmp;
	dev5_reg_00F = dev5_regs.dev5_reg_00F;
	disk_type = dev5_reg_00F;
	condtmp = dev5_reg_00F == 19;
	condtmp2 = dev5_reg_00F < 0x14u;
	if ( !condtmp )
	{
		if ( condtmp2 )
		{
			result = 0;
			if ( disk_type != 17 )
			{
				return result;
			}
		}
		else
		{
			result = 0;
			if ( disk_type != 253 )
			{
				return result;
			}
		}
	}
	if ( cdvdman_mmode == 1 || (result = 0, cdvdman_mmode == 255) )
	{
		ncmd_num = 14;
		if ( !flag )
		{
			ncmd_num = 7;
		}
		*(_DWORD *)ndata = lsn;
		*(_DWORD *)&ndata[4] = sectors;
		ndata[8] = mode->trycount;
		ndata[9] = cdvdman_speedctl(mode->spindlctrl, 0, lsn + sectors);
		datapattern_tmp = mode->datapattern;
		outlen = 12;
		b18.dma3_maddress = buf;
		ndata[10] = datapattern_tmp;
		if ( !flag )
		{
			outlen = 2;
		}
		return cdvdman_send_ncmd(ncmd_num, ndata, 11, outlen, &b18, 1) >= 0;
	}
	return result;
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
	vu8 dev5_reg_00F; // $v0
	int result; // $v0
	bool condtmp; // dc
	s16 sectors_tmp; // $t1
	DMA3PARAM b18; // [sp+18h] [-30h] BYREF
	char ndata[11]; // [sp+30h] [-18h] BYREF
	u32 efbits[2]; // [sp+40h] [-8h] BYREF

	dev5_reg_00F = dev5_regs.dev5_reg_00F;
	if ( dev5_reg_00F != 20 )
	{
		return 0;
	}
	if ( cdvdman_mmode == 2 || (result = 0, cdvdman_mmode == 255) )
	{
		condtmp = PollEventFlag(ncmd_evid, 1u, 16, efbits) == -421;
		result = 0;
		if ( !condtmp )
		{
			if ( cdvdman_verbose > 0 )
			{
				Kprintf(
					"RV read: sec %d num %d spin %d trycnt %d  addr %08x\n",
					lsn,
					sectors,
					mode->spindlctrl,
					mode->trycount,
					buf);
			}
			cdvdman_readbuf = buf;
			cdvdman_istruct.dvd_flag = cdvdman_isdvd();
			cdvdman_istruct.read_mode = *mode;
			cdvdman_istruct.read_lsn = lsn;
			cdvdman_istruct.read_sectors = sectors;
			*(_DWORD *)ndata = lsn;
			*(_DWORD *)&ndata[4] = sectors;
			ndata[8] = mode->trycount;
			ndata[9] = cdvdman_speedctl(mode->spindlctrl, 1, lsn + sectors);
			ndata[10] = 0;
			if ( arg5 )
			{
				if ( sectors < arg5 )
				{
					b18.dma3_csectors = sectors;
				}
				else
				{
					b18.dma3_csectors = arg5;
				}
			}
			else
			{
				b18.dma3_csectors = 0;
			}
			sectors_tmp = 1;
			cdvdman_istruct.read_chunk = b18.dma3_csectors;
			if ( !arg5 )
			{
				sectors_tmp = sectors;
			}
			b18.cdvdreg_howto = 140;
			b18.dma3_blkwords = 12;
			cdvdman_istruct.read_buf = buf;
			b18.dma3_blkcount = 43 * sectors_tmp;
			b18.dma3_msectors = sectors;
			b18.dma3_callback = (int (__cdecl *)(void *, int, int))cb;
			cdvdman_istruct.read_callback = cb;
			b18.dma3_maddress = buf;
			if ( cdvdman_send_ncmd(8, ndata, 11, 14, &b18, 0) >= 0 )
			{
				vSetEventFlag(ncmd_evid, 1u);
				return 1;
			}
			vSetEventFlag(ncmd_evid, 1u);
			return 0;
		}
	}
	return result;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (0040BCE8) --------------------------------------------------------
int __cdecl sceCdSeek(u32 lbn)
{
	bool condtmp; // dc
	int result; // $v0
	u32 ndata; // [sp+20h] [+8h] BYREF

	ndata = lbn;
	if ( cdvdman_isdvd() )
	{
		condtmp = DvdDual_infochk() == 0;
		result = 0;
		if ( condtmp )
		{
			return result;
		}
		ndata = sceCdLsnDualChg(ndata);
	}
	return cdvdman_send_ncmd(5, &ndata, 4, 4, 0, 1) >= 0;
}

//----- (0040BD58) --------------------------------------------------------
int __cdecl sceCdRI(u8 *buffer, u32 *result)
{
	int command; // $v0
	int outres1; // $t1
	u8 rdata[9]; // [sp+18h] [-10h] BYREF

	command = set_prev_command(18, 0, 0, (char *)rdata, 9, 1);
	*result = rdata[0];
	outres1 = *(_DWORD *)&rdata[5];
	*(_DWORD *)buffer = *(_DWORD *)&rdata[1];
	*((_DWORD *)buffer + 1) = outres1;
	return command;
}

//----- (0040BDD4) --------------------------------------------------------
int __cdecl sceCdRM(char *buffer, u32 *status)
{
	int result; // $v0
	int command; // $v0
	int rdata_tmp1; // $t1
	int cmd_tmp1; // $s2
	int cmd_tmp2; // $v0
	int rdata_tmp2; // $t1
	int cmd_tmp3; // $s0
	u8 rdata[9]; // [sp+18h] [-20h] BYREF
	char wdata[8]; // [sp+28h] [-10h] BYREF
	u32 efbits[2]; // [sp+30h] [-8h] BYREF

	*status = 0;
	if ( sceCdGetMVersion(rdata, status) == 1 && (rdata[3] | (rdata[2] << 8) | (rdata[1] << 16)) > 0x104FFu )
	{
		if ( PollEventFlag(scmd_evid, 1u, 16, efbits) == -421 )
		{
			return 0;
		}
		else
		{
			DelayThread(2000);
			wdata[0] = 0;
			command = set_prev_command(0x17, wdata, 1, (char *)rdata, 9, 0);
			*status = rdata[0];
			rdata_tmp1 = *(_DWORD *)&rdata[5];
			*(_DWORD *)buffer = *(_DWORD *)&rdata[1];
			*((_DWORD *)buffer + 1) = rdata_tmp1;
			cmd_tmp1 = command;
			DelayThread(2000);
			wdata[0] = 8;
			cmd_tmp2 = set_prev_command(0x17, wdata, 1, (char *)rdata, 9, 0);
			*status |= rdata[0];
			rdata_tmp2 = *(_DWORD *)&rdata[5];
			*((_DWORD *)buffer + 2) = *(_DWORD *)&rdata[1];
			*((_DWORD *)buffer + 3) = rdata_tmp2;
			cmd_tmp3 = cmd_tmp2;
			vSetEventFlag(scmd_evid, 1u);
			result = 0;
			if ( cmd_tmp1 )
			{
				return cmd_tmp3 != 0;
			}
		}
	}
	else
	{
		strcpy(buffer, "M_NAME_UNKNOWN");
		buffer[15] = 0;
		result = 1;
		*status |= 0x40u;
	}
	return result;
}

//----- (0040BFC0) --------------------------------------------------------
int __cdecl sceCdGetMVersion(u8 *buffer, u32 *status)
{
	int command; // $v0
	int res_tmp; // $s0
	int result; // $v0
	char rdata[4]; // [sp+18h] [-10h] BYREF
	char wdata[8]; // [sp+20h] [-8h] BYREF

	wdata[0] = 0;
	command = set_prev_command(3, wdata, 1, rdata, 4, 1);
	*status = rdata[0] & 0x80;
	res_tmp = command;
	if ( cdvdman_verbose > 0 )
	{
		Kprintf(
			"MV 0x%02x,0x%02x,0x%02x,0x%02x\n",
			(unsigned __int8)rdata[0],
			(unsigned __int8)rdata[1],
			(unsigned __int8)rdata[2],
			(unsigned __int8)rdata[3]);
	}
	result = res_tmp;
	rdata[0] &= ~0x80u;
	*(_DWORD *)buffer = *(_DWORD *)rdata;
	return result;
}
// 40BFC0: using guessed type char wdata[8];

//----- (0040C07C) --------------------------------------------------------
int __fastcall cdvdman_scmd_sender_03_48(u8 *buf, u32 *status)
{
	int result; // $v0
	char rdata[16]; // [sp+18h] [-18h] BYREF
	char wdata[8]; // [sp+28h] [-8h] BYREF

	if ( cdvdman_minver_50000 )
	{
		return 0;
	}
	wdata[0] = 48;
	wdata[1] = 2;
	result = set_prev_command(3, wdata, 2, rdata, 2, 1);
	*status = (unsigned __int8)rdata[0];
	*buf = rdata[1];
	return result;
}

//----- (0040C108) --------------------------------------------------------
int __cdecl sceCdMmode(int media)
{
	cdvdman_mmode = media;
	return 1;
}

//----- (0040C118) --------------------------------------------------------
int __cdecl sceCdCancelPOffRdy(u32 *result)
{
	int retval; // $v0
	char wdata[8]; // [sp+18h] [-8h] BYREF

	memset(wdata, 0, sizeof(wdata));
	*result = 0;
	retval = 1;
	if ( cdvdman_minver_20400 )
	{
		return set_prev_command(27, wdata, 0, (char *)result, 1, 1);
	}
	return retval;
}
// 40C118: using guessed type char wdata[8];

//----- (0040C164) --------------------------------------------------------
unsigned int __fastcall alarm_cb_poff(cdvdman_internal_struct_t *s)
{
	s->power_flag = 0;
	return 0;
}

//----- (0040C170) --------------------------------------------------------
int __cdecl sceCdPowerOff(u32 *result)
{
	int command; // $s1
	u32 trayreq[2]; // [sp+18h] [-8h] BYREF

	*result = 0;
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("sceCdPowerOff Call\n");
	}
	if ( !cdvdman_minver_x_model_15 )
	{
		while ( (sceCdStatus() & 1) != 0 )
		{
			sceCdTrayReq(1, trayreq);
			vDelayThread(250000);
		}
	}
	command = set_prev_command(0xF, 0, 0, (char *)result, 1, 1);
	if ( command )
	{
		Kprintf("PowerOff Start...\n");
		cdvdman_istruct.power_flag = 1;
		cdvdman_poff_to.hi = 0;
		cdvdman_poff_to.lo = 0xAFC8000;
		vSetAlarm(&cdvdman_poff_to, (unsigned int (__cdecl *)(void *))alarm_cb_poff, &cdvdman_istruct);
		return command;
	}
	else
	{
		cdvdman_istruct.power_flag = 0;
		return 0;
	}
}
// 4114C0: using guessed type iop_sys_clock_t cdvdman_poff_to;

//----- (0040C290) --------------------------------------------------------
int __cdecl sceCdCtrlADout(int arg1, u32 *status)
{
	char wdata[4]; // [sp+20h] [+8h] BYREF

	*(_DWORD *)wdata = arg1;
	*status = 0;
	DelayThread(2000);
	if ( cdvdman_verbose > 0 )
	{
		Kprintf("Audio Digital Out: Set param %d\n", *(_DWORD *)wdata);
	}
	return set_prev_command(20, wdata, 1, (char *)status, 1, 1);
}

//----- (0040C308) --------------------------------------------------------
int __cdecl sceCdReadClock(sceCdCLOCK *clock)
{
	int result; // $v0
	u8 month; // $v1
	int padtmp1; // $t1
	int padtmp2; // $t1

	result = set_prev_command(8, 0, 0, (char *)clock, 8, 1);
	month = clock->month;
	clock->pad = 0;
	clock->month = month & 0x7F;
	if ( result && !clock->stat )
	{
		padtmp2 = *(_DWORD *)&clock->pad;
		*(_DWORD *)&cdvdman_clock.stat = *(_DWORD *)&clock->stat;
		*(_DWORD *)&cdvdman_clock.pad = padtmp2;
		cdvdman_clk_flg = 1;
	}
	else if ( cdvdman_clk_flg )
	{
		padtmp1 = *(_DWORD *)&cdvdman_clock.pad;
		*(_DWORD *)&clock->stat = *(_DWORD *)&cdvdman_clock.stat;
		*(_DWORD *)&clock->pad = padtmp1;
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
	return result;
}

//----- (0040C424) --------------------------------------------------------
int __cdecl sceCdRC(sceCdCLOCK *clock)
{
	return set_prev_command(8, 0, 0, (char *)clock, 8, 1);
}

//----- (0040C460) --------------------------------------------------------
int __cdecl sceCdTrayReq(int param, u32 *traychk)
{
	int mediactl_res; // $a1
	int result; // $v0
	bool condtmp; // dc
	char wdata; // [sp+18h] [-8h] BYREF
	char rdata[7]; // [sp+19h] [-7h] BYREF

	if ( param == 2 )
	{
		mediactl_res = cdvdman_mediactl(1);
		*traychk = mediactl_res;
		result = 1;
		if ( cdvdman_verbose > 0 )
		{
			Kprintf("Tray Req test = %d\n", mediactl_res);
			return 1;
		}
	}
	else
	{
		result = 1;
		if ( !cdvdman_minver_x_model_15 || param != 1 )
		{
			wdata = param;
			cdvdman_iocache = 0;
			condtmp = set_prev_command(6, &wdata, 1, rdata, 1, 1) == 0;
			result = 0;
			if ( !condtmp )
			{
				result = 0;
				if ( !rdata[0] )
				{
					vDelayThread(11000);
					return 1;
				}
			}
		}
	}
	return result;
}
// 40C460: using guessed type char rdata[7];

//----- (0040C534) --------------------------------------------------------
int __fastcall cdvdman_scmd_sender_3B(int arg1)
{
	int result; // $v0
	bool condtmp; // dc
	char wdata; // [sp+18h] [-8h] BYREF
	char rdata[7]; // [sp+19h] [-7h] BYREF

	if ( !cdvdman_minver_x_model_15 || (result = 1, arg1 != 1) )
	{
		wdata = arg1;
		cdvdman_iocache = 0;
		condtmp = set_prev_command(59, &wdata, 1, rdata, 1, 1) == 0;
		result = 0;
		if ( !condtmp )
		{
			result = 0;
			if ( !rdata[0] )
			{
				vDelayThread(11000);
				return 1;
			}
		}
	}
	return result;
}
// 40C534: using guessed type char rdata[7];

//----- (0040C5B8) --------------------------------------------------------
int __cdecl sceCdReadDiskID(unsigned int *id)
{
	int disk_type; // $v0
	bool condtmp1; // dc
	u32 condtmp2; // $v0
	int result; // $v0
	vu8 dev5_reg_038; // $v0
	int retval; // $s1
	vu8 dev5_reg_030; // $v0
	vu8 dev5_reg_039; // $a1
	vu8 dev5_reg_031; // $v0
	vu8 reg_039_tmp2; // $a1
	vu8 dev5_reg_032; // $v0
	vu8 reg_039_tmp3; // $a1
	vu8 dev5_reg_033; // $v0
	vu8 reg_039_tmp4; // $a1
	vu8 dev5_reg_034; // $v0
	vu8 reg_039_tmp5; // $a1
	sceCdRMode rmode; // [sp+18h] [-810h] BYREF
	char sectbuf[2048]; // [sp+20h] [-808h] BYREF
	u32 efbits[2]; // [sp+820h] [-8h] BYREF

	*((_BYTE *)id + 4) = 0;
	*((_BYTE *)id + 3) = 0;
	*((_BYTE *)id + 2) = 0;
	*((_BYTE *)id + 1) = 0;
	*(_BYTE *)id = 0;
	disk_type = sceCdGetDiskType();
	condtmp1 = disk_type >= 21;
	condtmp2 = disk_type < 18;
	if ( condtmp1 )
	{
		return 0;
	}
	condtmp1 = condtmp2 != 0;
	result = 0;
	if ( !condtmp1 )
	{
		rmode.spindlctrl = 18;
		rmode.datapattern = 0;
		rmode.trycount = 0;
		sceCdRead0(0x4Bu, 1u, sectbuf, &rmode, 0, 0);
		sceCdSync(3);
		condtmp1 = cdvdman_ncmd_sender_0C(0, 0, 0x4Bu) == 0;
		result = 0;
		if ( !condtmp1 )
		{
			sceCdSync(3);
			if ( cdvdman_istruct.last_error )
			{
				return 0;
			}
			WaitEventFlag(scmd_evid, 1u, 0, efbits);
			dev5_reg_038 = dev5_regs.dev5_reg_038;
			retval = 0;
			if ( (dev5_reg_038 & 4) != 0 )
			{
				dev5_reg_030 = dev5_regs.dev5_reg_030;
				*(_BYTE *)id = dev5_reg_030;
				dev5_reg_039 = dev5_regs.dev5_reg_039;
				*(_BYTE *)id = dev5_reg_030 ^ dev5_reg_039;
				dev5_reg_031 = dev5_regs.dev5_reg_031;
				*((_BYTE *)id + 1) = dev5_reg_031;
				reg_039_tmp2 = dev5_regs.dev5_reg_039;
				*((_BYTE *)id + 1) = dev5_reg_031 ^ reg_039_tmp2;
				dev5_reg_032 = dev5_regs.dev5_reg_032;
				*((_BYTE *)id + 2) = dev5_reg_032;
				reg_039_tmp3 = dev5_regs.dev5_reg_039;
				*((_BYTE *)id + 2) = dev5_reg_032 ^ reg_039_tmp3;
				dev5_reg_033 = dev5_regs.dev5_reg_033;
				*((_BYTE *)id + 3) = dev5_reg_033;
				reg_039_tmp4 = dev5_regs.dev5_reg_039;
				*((_BYTE *)id + 3) = dev5_reg_033 ^ reg_039_tmp4;
				dev5_reg_034 = dev5_regs.dev5_reg_034;
				*((_BYTE *)id + 4) = dev5_reg_034;
				reg_039_tmp5 = dev5_regs.dev5_reg_039;
				retval = 1;
				*((_BYTE *)id + 4) = dev5_reg_034 ^ reg_039_tmp5;
			}
			vSetEventFlag(scmd_evid, 1u);
			return retval;
		}
	}
	return result;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;
// 40C5B8: using guessed type char sectbuf[2048];

//----- (0040C764) --------------------------------------------------------
int __cdecl sceCdDoesUniqueKeyExist(u32 *status)
{
	int disktype_tmp; // $s0
	int disk_type; // $v1
	u8 *ptoc_tmp; // $s2
	unsigned int retrycnt; // $s0
	u32 sectoroffset; // $s1
	vu8 dev5_reg_038; // $s0
	sceCdRMode rmode[2]; // [sp+18h] [-18h] BYREF
	char ndata[7]; // [sp+20h] [-10h] BYREF
	int state; // [sp+28h] [-8h] BYREF
	u32 efbits; // [sp+2Ch] [-4h] BYREF

	disktype_tmp = 0;
	if ( !cdvdman_istruct.cd_inited )
	{
		*status = 20;
		return 0;
	}
	*status = 0;
	disk_type = sceCdGetDiskType();
	if ( disk_type < 18 )
	{
		goto LABEL_7;
	}
	if ( disk_type >= 20 )
	{
		if ( disk_type == 20 )
		{
			goto LABEL_8;
		}
LABEL_7:
		*status = 20;
		return 0;
	}
	disktype_tmp = 1;
LABEL_8:
	CpuSuspendIntr(&state);
	if ( cdvdman_istruct.stream_flag || cdvdman_istruct.read2_flag )
	{
		goto LABEL_10;
	}
	if ( (sceCdStatus() & 2) != 0 )
	{
		CpuResumeIntr(state);
	}
	else
	{
		dev5_regs.dev5_reg_007 = 1;
		CpuResumeIntr(state);
		sceCdSync(3);
	}
	CpuSuspendIntr(&state);
	if ( cdvdman_istruct.stream_flag || cdvdman_istruct.read2_flag )
	{
LABEL_10:
		*status = 253;
		CpuResumeIntr(state);
		return 0;
	}
	ptoc_tmp = cdvdman_ptoc;
	rmode[0].spindlctrl = 18;
	rmode[0].datapattern = 0;
	rmode[0].trycount = 0;
	if ( disktype_tmp )
	{
		retrycnt = 0;
		sectoroffset = 75;
		do
		{
			sceCdRead0(sectoroffset, 0x10u, ptoc_tmp, rmode, 0, 0);
			sectoroffset += 16;
			++retrycnt;
			CpuResumeIntr(state);
			sceCdSync(3);
			CpuSuspendIntr(&state);
		}
		while ( retrycnt < 0x14 );
		CpuResumeIntr(state);
	}
	else
	{
		sceCdRead0(0x4Bu, 1u, cdvdman_ptoc, rmode, 0, 0);
		CpuResumeIntr(state);
		sceCdSync(3);
	}
	WaitEventFlag(scmd_evid, 1u, 0, &efbits);
	CpuSuspendIntr(&state);
	if ( cdvdman_istruct.stream_flag
		|| cdvdman_istruct.read2_flag
		|| (strcpy(&ndata[3], "K"),
				ndata[6] = 0,
				ndata[5] = 0,
				ndata[2] = 0,
				ndata[1] = 0,
				ndata[0] = 0,
				cdvdman_send_ncmd(12, ndata, 7, 0, 0, 1) < 0) )
	{
		*status = 253;
		CpuResumeIntr(state);
	}
	else
	{
		CpuResumeIntr(state);
		sceCdSync(3);
		if ( !cdvdman_istruct.last_error )
		{
			dev5_reg_038 = dev5_regs.dev5_reg_038;
			vSetEventFlag(scmd_evid, 1u);
			return (dev5_reg_038 & 5) == 5;
		}
		*status = (unsigned __int8)cdvdman_istruct.last_error;
	}
	vSetEventFlag(scmd_evid, 1u);
	return 0;
}
// BF402000: using guessed type dev5_regs_t dev5_regs;

//----- (0040CAE0) --------------------------------------------------------
int __cdecl cdvdman_ncmd_sender_0C(int arg1, u32 arg2, u32 arg3)
{
	char ndata[7]; // [sp+18h] [-8h] BYREF

	if ( arg1 )
	{
		arg3 = 0;
	}
	ndata[1] = arg2 != 0;
	ndata[0] = arg1;
	ndata[2] = arg2 >> 8 != 0;
	*(_DWORD *)&ndata[3] = arg3;
	return cdvdman_send_ncmd(12, ndata, 7, 0, 0, 1) >= 0;
}

//----- (0040CB64) --------------------------------------------------------
int __cdecl sceCdDecSet(u8 arg1, u8 arg2, u8 shift)
{
	vu8 shift1; // $a2
	vu8 shift2; // $v1

	cdvdman_cd36key = arg2 | shift;
	shift1 = 16 * (shift & 7);
	shift2 = shift1;
	if ( arg1 )
	{
		shift2 = shift1 | 2;
	}
	if ( arg2 )
	{
		shift2 |= 1u;
	}
	dev5_regs.dev5_reg_03A = shift2;
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
