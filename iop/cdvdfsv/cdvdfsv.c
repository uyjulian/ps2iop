
#include "irx_imports.h"
#include "../00common/defs.h"

IRX_ID("cdvd_ee_driver", 2, 38);

extern struct irx_export_table _exp_cdvdfsv;

//-------------------------------------------------------------------------
// Function declarations

int __fastcall cdvdfsv_checkdmastat(int trid);
int __cdecl cdvdfsv_cleanuprpc();
int __fastcall _start(int ac, char **av);
int __cdecl cdvdfsv_init();
void __cdecl cdvdfsv_main_th(void *arg);
int *__fastcall cdvdfsv_4(int arg1);
void __cdecl cdvdfsv_parseargs(int ac, char **av);
int __cdecl sceCdChangeThreadPriority(int priority);
CDVDInitResult *__fastcall cbrpc_rpc1_cdinit(int fno, void *buffer, int length);
void __fastcall cdvdfsv_rpc3h_16_break(void *inbuf, int buflen, void *outbuf);
CDVDSearchResult *__fastcall cbrpc_rpc4_fscall(int fno, void *buffer, int length);
int __fastcall alarm_cb(void *a1);
void __cdecl cdvdfsv_rpc5h_0D_iopmread(cdvdfsv_rpc5h_0D_packet *inbuf, int buflen, void *outbuf);
u8 __cdecl cdvdfsv_syncdec(int flag, int xorkey, int arg2, u8 data);
int __cdecl cdvdfsv_cb_read();
int __cdecl cdvdfsv_checksid(u32 lsn, u32 sectors, u32 ps2dvd, void *buf, int decflag, int decshift, u32 *syncdec_mask);
int __fastcall readproc2(u32 lsn, u32 nsec, sceCdRMode *mode, u32 sector_size_selection, int do_multi_retries, int enable_dec_shift, int dec_shift, char *ee_addr, int fssift, int secsize, int dmasize, SifDmaTransfer_t *post_dmat);
int __fastcall readproc1(unsigned int lsn, u32 nsec, void *retptr, sceCdRMode *rmode, int ps2dvd, int enable_retries, int dec_shift_enable, int dec_shift_value);
void __cdecl cdvdfsv_rpc5h_01_readee(cdvdfsv_rpc5h_01_packet *inbuf, int buflen, void *outbuf, u32 ps2dvd, int sync, int decflag);
int __fastcall cdvdfsv_chreadee(int secoffs, int seccount, char *ee_addr, const sceCdRMode *in_rmode, u32 disktype_14, int sync);
void __fastcall cdvdfsv_rpc5h_0F_readchain(cdvdfsv_rpc5h_0F_packet *inbuf, int buflen, void *outbuf);
void __fastcall cdvdfsv_rpc5h_02_readcdda(cdvdfsv_rpc5h_02_packet *inbuf, int buflen, void *outbuf);
int *__fastcall cbrpc_rpc2_diskready(int fno, void *buffer, int length);
void __fastcall cdvdfsv_rpc5h_04_gettoc(void *inbuf, int buflen, cdvdfsv_rpc5h_04_outpacket *outbuf);
void __fastcall cdvdfsv_rpc3h_03_disktype(void *inbuf, int buflen, void *outbuf);
void __fastcall cdvdfsv_rpc3h_0C_cdstatus(void *inbuf, int buflen, void *outbuf);
void __cdecl cdvdfsv_rpc3h_06_ri(void *inbuf, int buflen, cdvdfsv_rpc3h_06_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_1A_rm(void *inbuf, int buflen, cdvdfsv_rpc3h_1A_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_24_readguid(void *inbuf, int buflen, cdvdfsv_rpc3h_24_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_26_readmodelid(void *inbuf, int buflen, cdvdfsv_rpc3h_26_outpacket *outbuf);
void __fastcall cdvdfsv_rpc3h_22_mmode(const cdvdfsv_rpc3h_22_packet *inbuf, int buflen, void *outbuf);
void __fastcall cdvdfsv_rpc3h_23_changethreadpriority(void *inbuf, int buflen, void *outbuf);
void __cdecl cdvdfsv_rpc3h_21_poweroff(void *inbuf, int buflen, cdvdfsv_rpc3h_21_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_15_ctrladout(void *inbuf, int buflen, cdvdfsv_rpc3h_15_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_01_readclock(void *inbuf, int buflen, cdvdfsv_rpc3h_01_outpacke *outbuf);
void __fastcall cdvdfsv_rpc5h_11_readdiskid(void *inbuf, int buflen, cdvdfsv_rpc5h_11_outpacket *outbuf);
void __fastcall cdvdfsv_rpc5h_17_doesuniquekeyexist(void *inbuf, int buflen, cdvdfsv_rpc5h_17_outpacket *outbuf);
void __fastcall cdvdfsv_rpc3h_0B_applyscmd(cdvdfsv_rpc3h_0B_packet *inbuf, int buflen, cdvdfsv_rpc3h_0B_outpacket *outbuf);
void __fastcall cdvdfsv_rpc5h_0C_applyncmd(cdvdfsv_rpc5h_0C_packet *inbuf, int buflen, void *outbuf);
void __fastcall cdvdfsv_rpc3h_04_geterror(void *inbuf, int buflen, void *outbuf);
void __cdecl cdvdfsv_rpc3h_05_trayreq(void *inbuf, int buflen, cdvdfsv_rpc3h_05_outpacket *outbuf);
void __fastcall cdvdfsv_rpc3h_25_settimeout(const cdvdfsv_rpc3h_25_packet *inbuf, int buflen, void *outbuf);
void __fastcall cdvdfsv_rpc3h_27_readdvddualinfo(void *inbuf, int buflen, cdvdfsv_rpc3h_27_outpacket *outbuf);
int __cdecl cdvdfsv_rpc5h_0E_diskready();
CDVDReadResult *__fastcall cbrpc_rpc5_cdvdncmds(int fno, void *buffer, int length);
CDVDCmdResult *__fastcall cbrpc_rpc3_cdvdscmds(int fno, void *buffer, int length);
void __cdecl cdvdfsv_poffloop();
void __cdecl cdvdfsv_rpc1_th(void *arg);
void __cdecl cdvdfsv_rpc3_th(void *arg);
void __cdecl cdvdfsv_rpc2_th(void *arg);
void __fastcall cdvdfsv_unused_xorfun(unsigned int *, int);
unsigned int __fastcall cdvdfsv_memcpy(_DWORD *a1, _DWORD *a2, unsigned int a3);
void cdvdfsv_1();
#if 0
int Kprintf(const char *format, ...);
int __cdecl RegisterLibraryEntries(struct irx_export_table *exports);
int __cdecl ReleaseLibraryEntries(struct irx_export_table *exports);
void *__cdecl QueryLibraryEntryTable(iop_library_t *library);
int *__cdecl QueryBootMode(int mode);
int __cdecl DisableIntr(int irq, int *res);
int __cdecl CpuSuspendIntr(int *state);
int __cdecl CpuResumeIntr(int state);
int QueryIntrContext(void);
int printf(const char *format, ...);
void __cdecl dmac_ch_set_madr(u32 channel, u32 val);
void __cdecl dmac_ch_set_bcr(u32 channel, u32 val);
void __cdecl dmac_ch_set_chcr(u32 channel, u32 val);
u32 __cdecl dmac_ch_get_chcr(u32 channel);
int __cdecl CreateThread(iop_thread_t *thread);
int __cdecl DeleteThread(int thid);
int __cdecl StartThread(int thid, void *arg);
int __cdecl ExitDeleteThread();
int __cdecl TerminateThread(int thid);
int __cdecl ChangeThreadPriority(int thid, int priority);
int GetThreadId(void);
int __cdecl ReferThreadStatus(int thid, iop_thread_info_t *info);
int __cdecl DelayThread(int usec);
int __cdecl SetAlarm(iop_sys_clock_t *sys_clock, unsigned int (__cdecl *alarm_cb)(void *), void *arg);
int __cdecl CancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg);
int __cdecl iSetEventFlag(int ef, u32 bits);
int __cdecl ClearEventFlag(int ef, u32 bits);
int __cdecl WaitEventFlag(int ef, u32 bits, int mode, u32 *resbits);
unsigned int __cdecl sceSifSendCmd(int cmd, void *packet, int packet_size, void *src_extra, void *dest_extra, int size_extra);
void __cdecl sceSifInitRpc(int mode);
void __cdecl sceSifRegisterRpc(SifRpcServerData_t *sd, int sid, SifRpcFunc_t func, void *buf, SifRpcFunc_t cfunc, void *cbuf, SifRpcDataQueue_t *qd);
SifRpcDataQueue_t *__cdecl sceSifSetRpcQueue(SifRpcDataQueue_t *q, int thread_id);
void __cdecl sceSifRpcLoop(SifRpcDataQueue_t *qd);
SifRpcServerData_t *__cdecl sceSifRemoveRpc(SifRpcServerData_t *sd, SifRpcDataQueue_t *qd);
SifRpcDataQueue_t *__cdecl sceSifRemoveRpcQueue(SifRpcDataQueue_t *qd);
void __cdecl sceSifInit();
int __cdecl sceSifSetDma(SifDmaTransfer_t *dmat, int count);
int __cdecl sceSifDmaStat(int trid);
int __cdecl sceSifCheckInit();
int __cdecl strncmp(const char *p, const char *q, size_t size);
int __cdecl strtol(const char *s, char **endptr, int base);
int __cdecl devctl(const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
int __cdecl sceCdInit(int mode);
int sceCdStandby(void);
int __cdecl sceCdSeek(u32 lbn);
int sceCdGetError(void);
int __cdecl sceCdGetToc(u8 *toc);
int __cdecl sceCdSearchFile(sceCdlFILE *file, const char *name);
int __cdecl sceCdSync(int mode);
int sceCdGetDiskType(void);
int __cdecl sceCdTrayReq(int param, u32 *traychk);
int sceCdStop(void);
u32 __cdecl sceCdPosToInt(sceCdlLOCCD *p);
int __cdecl sceCdRI(u8 *buffer, u32 *result);
int __cdecl sceCdReadClock(sceCdCLOCK *clock);
int sceCdStatus(void);
int __cdecl sceCdApplySCmd(u8 cmdNum, const void *inBuff, u16 inBuffSize, void *outBuff, u16 outBuffSize);
int sceCdPause(void);
int sceCdBreak(void);
int __cdecl sceCdReadCDDA(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode);
u32 sceCdGetReadPos(void);
int __cdecl sceCdCtrlADout(int arg1, u32 *status);
void *sceGetFsvRbuf(void);
int __cdecl sceCdSC(int code, int *param);
int __cdecl sceCdApplyNCmd(u8 cmdNum, const void *inBuff, u16 inBuffSize);
int __cdecl sceCdRead0(u32 lsn, u32 sectors, void *buffer, sceCdRMode *mode, int csec, void *callback);
int __cdecl sceCdRV(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int arg5, void *cb);
int __cdecl sceCdRM(char *buffer, u32 *status);
int __cdecl sceCdPowerOff(u32 *result);
int __cdecl sceCdMmode(int media);
int __cdecl sceCdReadDiskID(unsigned int *id);
int __cdecl sceCdReadGUID(u64 *guid);
int __cdecl sceCdSetTimeout(int param, int timeout);
int __cdecl sceCdReadModelID(unsigned int *id);
int __cdecl sceCdReadDvdDualInfo(int *on_dual, unsigned int *layer1_start);
int __cdecl sceCdLayerSearchFile(sceCdlFILE *fp, const char *path, int layer);
int __cdecl sceCdRE(unsigned int lsn, unsigned int sectors, void *buf, sceCdRMode *mode);
int __cdecl sceCdDoesUniqueKeyExist(u32 *status);
#endif

//-------------------------------------------------------------------------
// Data declarations

int cdvdfsv_def_pri = 81;
int g_verbose_level = 0;
int cdvdfsv_spinctl = -1;
int cdvdfsv_plbreak = 0;
int cdvdfsv_nopocm = 0;
int cdvdfsv_rpc5flg = 0;
int cdvdfsv_rpc3flg = 0; // weak
iop_library_t modload_libinfo = { NULL, NULL, 256u, 0u, "modload", { NULL } }; // idb
int cdvdfsv_r2retry = 0;
int cdvdfsv_r2count = 0;
int cdvdfsv_sid_err_recover_cnt = 0; // weak
int cdvdfsv_err_count = 0; // weak
int dword_405750[2]; // weak
void *cdvdfsv_fsvrbuf;
int dword_40575C; // weak
u8 *cdvdfsv_rtocbuf; // idb
SifDmaTransfer_t cdvdfsv_fssdd; // idb
SifDmaTransfer_t cdvdfsv_iomrsdd; // idb
SifDmaTransfer_t cdvdfsv_rdp2sdd; // idb
SifDmaTransfer_t cdvdfsv_multi_dmat[16];
sceCdRMode cdvdfsv_rmodeee;
SifDmaTransfer_t cdvdfsv_datasdd; // idb
SifDmaTransfer_t cdvdfsv_eerpsdd; // idb
SifDmaTransfer_t cdvdfsv_chrdsdd; // idb
SifDmaTransfer_t cdvdfsv_eereadfull_dma1; // idb
SifDmaTransfer_t cdvdfsv_eereadfull_dma2; // idb
SifDmaTransfer_t cdvdfsv_rtocsdd; // idb
iop_sys_clock_t cdvdfsv_read_to; // idb
int cdvdfsv_ef; // idb
int cdvdman_scmd_ef; // idb
int cdvdfsv_thids[4];
cdvdman_internal_struct_t *cdvdfsv_cdvdman_internal_struct_ptr;
CDVDInitResult cdvdfsv_initres; // weak
CDVDReadExtra cdvdfsv_eereadx;
SifRpcDataQueue_t rpc_qdata2;
SifRpcDataQueue_t rpc_qdata1;
SifRpcDataQueue_t rpc_qdata3;
SifRpcServerData_t rpc_sdata1; // idb
SifRpcServerData_t rpc_sdata4; // idb
SifRpcServerData_t rpc_sdata5; // idb
SifRpcServerData_t rpc_sdata2; // idb
SifRpcServerData_t rpc_sdata6; // idb
SifRpcServerData_t rpc_sdata3; // idb
CDVDSearchResult cdvdfsv_srchres;
int cdvdfsv_readpos;
int cdvdfsv_rderror; // idb
int diskready_res; // weak
int crr[16];
cdvdfsv_rpc3h_27_outpacket outbuf; // idb
int rpc_buffer3[260];
int rpc_buffer5[256];
int rpc_buffer1[4];
int rpc_buffer4[76];
int rpc_buffer2[4];


//----- (00400000) --------------------------------------------------------
int __fastcall cdvdfsv_checkdmastat(int trid)
{
	int retval; // $s0
	int state; // [sp+10h] [-8h] BYREF

	if ( QueryIntrContext() )
		return sceSifDmaStat(trid);
	CpuSuspendIntr(&state);
	retval = sceSifDmaStat(trid);
	CpuResumeIntr(state);
	return retval;
}

//----- (00400058) --------------------------------------------------------
int __cdecl cdvdfsv_cleanuprpc()
{
	unsigned int i; // $s1

	sceSifRemoveRpc(&rpc_sdata1, &rpc_qdata1);
	sceSifRemoveRpc(&rpc_sdata2, &rpc_qdata1);
	sceSifRemoveRpc(&rpc_sdata3, &rpc_qdata1);
	sceSifRemoveRpc(&rpc_sdata6, &rpc_qdata3);
	sceSifRemoveRpc(&rpc_sdata4, &rpc_qdata2);
	sceSifRemoveRpc(&rpc_sdata5, &rpc_qdata2);
	sceSifRemoveRpcQueue(&rpc_qdata1);
	sceSifRemoveRpcQueue(&rpc_qdata2);
	sceSifRemoveRpcQueue(&rpc_qdata3);
	cdvdfsv_nopocm = 1;
	cdvdfsv_plbreak = 1;
	for ( i = 0; i < (sizeof(cdvdfsv_thids)/sizeof(cdvdfsv_thids[0])); i += 1 )
	{
		TerminateThread(cdvdfsv_thids[i]);
		DeleteThread(cdvdfsv_thids[i]);
	}
	return 1;
}

//----- (00400158) --------------------------------------------------------
int __fastcall _start(int ac, char **av)
{
	const unsigned __int16 *LibraryEntryTable; // $v0
	int state[2]; // [sp+10h] [-8h] BYREF

	if ( ac < 0 )
	{
		int error_code; // $s0

		// cppcheck-suppress knownConditionTrueFalse
		if ( cdvdfsv_rpc5flg || cdvdfsv_rpc3flg || cdvdfsv_cleanuprpc() == 0 )
		{
			return 2;
		}
		CpuSuspendIntr(state);
		error_code = ReleaseLibraryEntries(&_exp_cdvdfsv);
		CpuResumeIntr(state[0]);
		if ( error_code && error_code != -213 )
		{
			KPRINTF("ReleaseLibraryEntries Error code %d\n", error_code);
			return 2;
		}
		return 1;
	}
	if ( RegisterLibraryEntries(&_exp_cdvdfsv) != 0 )
	{
		return 1;
	}
	cdvdfsv_fsvrbuf = sceGetFsvRbuf();
	dword_40575C = (int)dword_405750;
	cdvdfsv_rtocbuf = (u8 *)cdvdfsv_fsvrbuf;
	cdvdfsv_parseargs(ac, av);
	cdvdfsv_init();
	CpuSuspendIntr(state);
	LibraryEntryTable = (unsigned __int16 *)QueryLibraryEntryTable(&modload_libinfo);
	CpuResumeIntr(state[0]);
	if ( !LibraryEntryTable || (*(LibraryEntryTable - 6) < 0x104u) )
	{
		KPRINTF("Warning cdvdfsv.irx: Unload function can't be used.\n");
		return 0;
	}
	return 2;
}
// 405720: using guessed type int cdvdfsv_rpc3flg;
// 405750: using guessed type int dword_405750[2];
// 40575C: using guessed type int dword_40575C;

//----- (004002C0) --------------------------------------------------------
int __cdecl cdvdfsv_init()
{
	const int *BootMode; // $v0
	iop_thread_t thparam; // [sp+10h] [-20h] BYREF
	int scres; // [sp+28h] [-8h] BYREF

	BootMode = QueryBootMode(3);
	if ( BootMode && (BootMode[1] & 2) != 0 )
	{
		PRINTF(" No cdvd driver \n");
		return 1;
	}
	sceCdSC(0xFFFFFFF2, (int *)&cdvdfsv_cdvdman_internal_struct_ptr);
	cdvdman_scmd_ef = sceCdSC(0xFFFFFFE7, &scres);
	thparam.attr = 0x2000000;
	thparam.thread = cdvdfsv_main_th;
	thparam.stacksize = 2048;
	thparam.option = 0;
	thparam.priority = cdvdfsv_def_pri - 1;
	cdvdfsv_thids[0] = CreateThread(&thparam);
	if ( cdvdfsv_thids[0] <= 0 )
	{
		return 1;
	}
	StartThread(cdvdfsv_thids[0], 0);
	return 0;
}

//----- (00400394) --------------------------------------------------------
void __cdecl cdvdfsv_main_th(void *arg)
{
	iop_thread_t thparam1; // [sp+10h] [-30h] BYREF
	iop_thread_t thparam2; // [sp+28h] [-18h] BYREF

	(void)arg;

	if ( !sceSifCheckInit() )
		sceSifInit();
	sceSifInitRpc(0);
	PRINTF("cdvd driver module version 0.1.1 (C)SCEI\n");
	thparam2.thread = cdvdfsv_rpc1_th;
	thparam2.attr = 0x2000000;
	thparam2.stacksize = 6400;
	thparam2.option = 0;
	thparam2.priority = cdvdfsv_def_pri;
	cdvdfsv_thids[1] = CreateThread(&thparam2);
	StartThread(cdvdfsv_thids[1], 0);
	thparam1.attr = 0x2000000;
	thparam1.thread = cdvdfsv_rpc2_th;
	thparam1.stacksize = 6400;
	thparam1.option = 0;
	thparam1.priority = cdvdfsv_def_pri;
	cdvdfsv_thids[2] = CreateThread(&thparam1);
	StartThread(cdvdfsv_thids[2], 0);
	thparam1.thread = cdvdfsv_rpc3_th;
	thparam1.attr = 0x2000000;
	thparam1.stacksize = 2048;
	thparam1.option = 0;
	thparam1.priority = cdvdfsv_def_pri;
	cdvdfsv_thids[3] = CreateThread(&thparam1);
	StartThread(cdvdfsv_thids[3], 0);
	cdvdfsv_poffloop();
	ExitDeleteThread();
}

//----- (004004D4) --------------------------------------------------------
int *__fastcall cdvdfsv_4(int arg1)
{
	VERBOSE_PRINTF(1, "Dummy Entry Called\n");
	if ( arg1 != 128 )
		return 0;
	return &g_verbose_level;
}

//----- (00400528) --------------------------------------------------------
void __cdecl cdvdfsv_parseargs(int ac, char **av)
{
	int i; // $s1

	cdvdfsv_def_pri = 81;
	for ( i = 1; i < ac; i += 1 )
	{
		if ( !strncmp(av[i], "thpri=", 6) )
		{
			cdvdfsv_def_pri = strtol(av[i] + 6, 0, 10);
			if ( (unsigned int)(cdvdfsv_def_pri - 9) >= 0x73 )
			{
				PRINTF("Cdvdfsv:thpri=%d Illegal priority\n", cdvdfsv_def_pri);
				cdvdfsv_def_pri = 81;
			}
			if ( cdvdfsv_def_pri == 9 )
				cdvdfsv_def_pri = 10;
		}
	}
}

//----- (004005F8) --------------------------------------------------------
int __cdecl sceCdChangeThreadPriority(int priority)
{
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	if ( (unsigned int)(priority - 9) >= 0x73 )
		return -403;
	if ( priority == 9 )
		priority = 10;
	ReferThreadStatus(0, &thinfo);
	ChangeThreadPriority(0, 8);
	ChangeThreadPriority(cdvdfsv_thids[0], priority - 1);
	ChangeThreadPriority(cdvdfsv_thids[2], priority);
	ChangeThreadPriority(cdvdfsv_thids[1], priority);
	ChangeThreadPriority(cdvdfsv_thids[3], priority);
	return 0;
}
// 4005F8: using guessed type iop_thread_info_t thinfo;

//----- (00400694) --------------------------------------------------------
CDVDInitResult *__fastcall cbrpc_rpc1_cdinit(int fno, void *buffer, int length)
{
	int scres; // [sp+10h] [-8h] BYREF

	(void)fno;
	(void)length;

	VERBOSE_PRINTF(1, "sceCdInit call\n");
	sceCdInit(*(_DWORD *)buffer);
	cdvdfsv_spinctl = -1;
	cdvdfsv_initres.debug_mode = g_verbose_level ? 254 : 0;
	cdvdfsv_initres.cdvdfsv_ver = (unsigned __int16)_irx_id.v;
	cdvdfsv_initres.cdvdman_ver = sceCdSC(0xFFFFFFF7, &scres);
	VERBOSE_PRINTF(1, "sceCdInit end\n");
	cdvdfsv_initres.result = 1;
	return &cdvdfsv_initres;
}
// 405940: using guessed type CDVDInitResult cdvdfsv_initres;

//----- (00400760) --------------------------------------------------------
void __fastcall cdvdfsv_rpc3h_16_break(void *inbuf, int buflen, void *outbuf)
{
	(void)inbuf;
	(void)buflen;

	VERBOSE_PRINTF(1, "sceCdAbort call\n");
	sceCdBreak();
	*(_DWORD *)outbuf = 1;
}

//----- (004007AC) --------------------------------------------------------
CDVDSearchResult *__fastcall cbrpc_rpc4_fscall(int fno, void *buffer, int length)
{
	int scres; // [sp+10h] [-8h] BYREF
	int state; // [sp+14h] [-4h] BYREF

	(void)fno;

	scres = 255;
	sceCdSC(0xFFFFFFF6, &scres);
	VERBOSE_PRINTF(1, "search file name %s call struct_siz %d\n", (const char *)buffer + 36, length);
	switch ( length )
	{
		case 300:
			cdvdfsv_srchres.result = sceCdLayerSearchFile((sceCdlFILE *)buffer, (const char *)buffer + 36, *((_DWORD *)buffer + 74));
			cdvdfsv_fssdd.src = buffer;
			cdvdfsv_fssdd.dest = (void *)*((_DWORD *)buffer + 73);
			cdvdfsv_fssdd.size = 36;
			break;
		case 296:
			PRINTF("sceCdSearchFile: Called from Not_Dual_layer Version.\n");
			cdvdfsv_srchres.result = sceCdSearchFile((sceCdlFILE *)buffer, (const char *)buffer + 36);
			cdvdfsv_fssdd.src = buffer;
			cdvdfsv_fssdd.dest = (void *)*((_DWORD *)buffer + 73);
			cdvdfsv_fssdd.size = 36;
			break;
		default:
			PRINTF("Warning sceCdSearchFile: Called from Old liblary.\n");
			cdvdfsv_srchres.result = sceCdSearchFile((sceCdlFILE *)buffer, (const char *)buffer + 32);
			cdvdfsv_fssdd.src = buffer;
			cdvdfsv_fssdd.dest = (void *)*((_DWORD *)buffer + 72);
			cdvdfsv_fssdd.size = 32;
			break;
	}
	cdvdfsv_fssdd.attr = 0;
	while ( 1 )
	{
		int trid; // $s0

		CpuSuspendIntr(&state);
		trid = sceSifSetDma(&cdvdfsv_fssdd, 1);
		CpuResumeIntr(state);
		if ( trid )
			break;
		DelayThread(500);
	}
	scres = 0;
	sceCdSC(0xFFFFFFF6, &scres);
	return &cdvdfsv_srchres;
}

//----- (00400920) --------------------------------------------------------
int __fastcall alarm_cb(void *a1)
{
	unsigned int time_out_msec; // [sp+10h] [-8h] BYREF

	time_out_msec = *(_DWORD *)a1 / 0x9000u;
	KPRINTF("Read Time Out %d(msec)\n", time_out_msec);
	sceCdSC(0xFFFFFFEE, (int *)&time_out_msec);
	return sceCdBreak() == 0;
}

//----- (00400974) --------------------------------------------------------
void __cdecl cdvdfsv_rpc5h_0D_iopmread(cdvdfsv_rpc5h_0D_packet *inbuf, int buflen, void *outbuf)
{
	int cmd_error; // $s1
	int trid; // $s0
	int error_code; // [sp+10h] [-8h] BYREF
	int state; // [sp+14h] [-4h] BYREF

	(void)buflen;
	(void)outbuf;

	cdvdfsv_rderror = 254;
	cdvdfsv_read_to.hi = 0;
	cdvdfsv_read_to.lo = 36864 * sceCdSC(0xFFFFFFF1, &error_code);
	cdvdfsv_iomrsdd.src = &cdvdfsv_readpos;
	cdvdfsv_iomrsdd.size = 4;
	cdvdfsv_iomrsdd.attr = 0;
	cdvdfsv_iomrsdd.dest = (void *)inbuf->readpos_dest_addr;
	VERBOSE_PRINTF(1, "sceCdReadIOPm addr= 0x%08x sector= %d\n", (unsigned int)(uiptr)(inbuf->buf), (int)(inbuf->sectors));
	cmd_error = sceCdRE(inbuf->lsn, inbuf->sectors, inbuf->buf, &inbuf->mode);
	while ( sceCdSync(1) )
	{
		cdvdfsv_readpos = sceCdGetReadPos();
		while ( 1 )
		{
			CpuSuspendIntr(&state);
			trid = sceSifSetDma(&cdvdfsv_iomrsdd, 1);
			CpuResumeIntr(state);
			if ( trid )
				break;
			DelayThread(500);
		}
		DelayThread(8000);
		while ( cdvdfsv_checkdmastat(trid) >= 0 )
			;
	}
	error_code = sceCdGetError();
	if ( error_code || !cmd_error )
	{
		if ( !cmd_error )
			sceCdSC(0xFFFFFFFE, &cdvdfsv_rderror);
		VERBOSE_PRINTF(1, "Read error code %x cmd error %d\n", error_code, cmd_error);
	}
}

//----- (00400B0C) --------------------------------------------------------
u8 __cdecl cdvdfsv_syncdec(int flag, int xorkey, int arg2, u8 data)
{
	return flag ? (((data << (arg2 % 8)) | (data >> (8 - arg2 % 8))) ^ xorkey) : data;
}

//----- (00400B58) --------------------------------------------------------
int __cdecl cdvdfsv_cb_read()
{
	iSetEventFlag(cdvdfsv_ef, 0x20u);
	return 0;
}

//----- (00400B80) --------------------------------------------------------
int __cdecl cdvdfsv_checksid(u32 lsn, u32 sectors, u32 ps2dvd, void *buf, int decflag, int decshift, u32 *syncdec_mask)
{
	int scret; // $s1
	u32 i; // $s5
	u32 readlsn; // $s0
	int syncdec; // $s0
	u8 syncdec_4; // $v0
	sceCdlLOCCD rpos; // [sp+18h] [-10h] BYREF
	int scres; // [sp+20h] [-8h] BYREF
	int ipi_emu; // [sp+24h] [-4h]

	ipi_emu = 0;
	*syncdec_mask = 0;
	scret = decflag ? sceCdSC(0xFFFFFFE8, &scres) : 0;
	syncdec_4 = 0;
	for ( i = 0; i < sectors; i += 1 )
	{
		if ( ps2dvd )
		{
			syncdec = cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 2064))[3]);
			syncdec += cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 2064))[2]) << 8;
			syncdec += cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 2064))[1]) << 16;
			syncdec_4 = cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 2064))[0]);
			if ( i && !*syncdec_mask )
			{
				ipi_emu = syncdec_4 & 0xC;
			}
			else if ( !i )
			{
				*syncdec_mask = syncdec_4 & 0xC;
			}
			readlsn = syncdec - 0x30000;
			if ( cdvdfsv_cdvdman_internal_struct_ptr->opo_or_para
				&& (lsn + i) >= cdvdfsv_cdvdman_internal_struct_ptr->layer_1_lsn
				&& cdvdfsv_cdvdman_internal_struct_ptr->opo_or_para == 1 )
			{
				readlsn += cdvdfsv_cdvdman_internal_struct_ptr->layer_1_lsn;
			}
		}
		else
		{
			rpos.minute = cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 2340))[0]);
			rpos.second = cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 2340))[1]);
			rpos.sector = cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 2340))[2]);
			readlsn = sceCdPosToInt(&rpos);
		}
		if ( readlsn != (lsn + i) || ipi_emu )
		{
			VERBOSE_PRINTF(1, "Read_EE Sector_ID error lsn= %d readlsn= %d layer= %d layer1_start %d\n", (int)(lsn + i), (int)readlsn, (syncdec_4 & 1), (int)(cdvdfsv_cdvdman_internal_struct_ptr->layer_1_lsn));
			return 0;
		}
	}
	if ( *syncdec_mask )
	{
		VERBOSE_PRINTF(1, "Read_EE NO_Data_zone error lsn= %d layer= %d SecID %02x\n", (int)lsn, (syncdec_4 & 1), (int)(*syncdec_mask));
	}
	return 1;
}

//----- (00400E40) --------------------------------------------------------
int __fastcall readproc2(
				u32 lsn,
				u32 nsec,
				sceCdRMode *mode,
				u32 sector_size_selection,
				int do_multi_retries,
				int enable_dec_shift,
				int dec_shift,
				char *ee_addr,
				int fssift,
				int secsize,
				int dmasize,
				SifDmaTransfer_t *post_dmat)
{
	unsigned int i; // $v0
	int csec; // $s5
	int read_res_tmp; // $s0
	int trid; // $s0
	int j; // $s4
	int size_2; // $s4
	int sector_sizes[2]; // [sp+20h] [-40h] BYREF
	int sc_fffffff1_res; // [sp+28h] [-38h] BYREF
	int state; // [sp+2Ch] [-34h] BYREF
	u32 syncdec_mask; // [sp+30h] [-30h] BYREF
	u32 chcr; // [sp+34h] [-2Ch] BYREF
	int sc_fffffffe_res; // [sp+38h] [-28h] BYREF
	char *ee_addr_tmp; // [sp+3Ch] [-24h]
	int dmasize_tmp; // [sp+40h] [-20h]
	int csec_comm; // [sp+44h] [-1Ch]
	int nsec_div_cdvdfsv_sectors; // [sp+48h] [-18h]
	int retry_flag1; // [sp+4Ch] [-14h]
	int retry_flag2; // [sp+50h] [-10h]
	int sector_size; // [sp+5Ch] [-4h]

	sc_fffffffe_res = 0;
	sector_sizes[0] = 2340;
	sector_sizes[1] = 2064;
	cdvdfsv_read_to.hi = 0;
	cdvdfsv_read_to.lo = 36864 * sceCdSC(0xFFFFFFF1, &sc_fffffff1_res);
	cdvdfsv_rderror = 253;
	cdvdfsv_r2retry = 0;
	cdvdfsv_r2count = 0;
	if ( secsize != 2340 && !fssift )
	{
		for ( i = 0; i < (sizeof(cdvdfsv_multi_dmat)/sizeof(cdvdfsv_multi_dmat[0])); i += 1 )
		{
			cdvdfsv_multi_dmat[i].attr = 0;
			cdvdfsv_multi_dmat[i].size = secsize;
		}
	}
	sector_size = sector_sizes[sector_size_selection];
	while ( 1 )
	{
		while ( 1 )
		{
			csec = ( nsec < 0x11 ) ? nsec : 16;
			nsec_div_cdvdfsv_sectors = (nsec >> 4) + (( (nsec & 0xF) != 0 ) ? 1 : 0);
			retry_flag2 = 0;
			ee_addr_tmp = ee_addr;
			dmasize_tmp = dmasize;
			cdvdfsv_cdvdman_internal_struct_ptr->dec_mode_set = 1;
			cdvdfsv_cdvdman_internal_struct_ptr->dec_mode_last_set = 0;
			CpuSuspendIntr(&state);
			if ( enable_dec_shift )
			{
				cdvdfsv_cdvdman_internal_struct_ptr->dec_shift = dec_shift;
				cdvdfsv_cdvdman_internal_struct_ptr->dec_state = 2;
			}
			if ( cdvdfsv_r2retry )
			{
				VERBOSE_KPRINTF(1, "Rty_Read\n");
				read_res_tmp = (sector_size_selection ? sceCdRV : sceCdRead0)(( lsn >= 0x60 ) ? (lsn - 16 * cdvdfsv_r2retry) : (lsn + 16 * cdvdfsv_r2retry + 96), 0x10u, cdvdfsv_rtocbuf + 4680, mode, 0, 0);
				CpuResumeIntr(state);
			}
			else
			{
				read_res_tmp = (sector_size_selection ? sceCdRV : sceCdRead0)(lsn, nsec, cdvdfsv_rtocbuf + 4680, mode, csec, cdvdfsv_cb_read);
				CpuResumeIntr(state);
				if ( read_res_tmp )
				{
					SetAlarm(&cdvdfsv_read_to, (unsigned int (__cdecl *)(void *))alarm_cb, &cdvdfsv_read_to);
					csec_comm = 0;
					retry_flag1 = 0;
					break;
				}
			}
			if ( !read_res_tmp )
			{
				cdvdfsv_cdvdman_internal_struct_ptr->dec_state = 0;
				cdvdfsv_cdvdman_internal_struct_ptr->dec_mode_set = 0;
				sceCdSC(-2, &cdvdfsv_rderror);
				return 0;
			}
			sceCdSync(3);
			--cdvdfsv_r2retry;
		}
		for ( i = 0; (int)i < nsec_div_cdvdfsv_sectors; i += 1 )
		{
			sceCdSync(32);
			if ( cdvdfsv_cdvdman_internal_struct_ptr->dec_mode_last_set )
				break;
			if ( !sceCdGetError() )
			{
				if ( cdvdfsv_checksid(
							 lsn + csec_comm,
							 csec,
							 sector_size_selection,
							 cdvdfsv_rtocbuf + 4680,
							 enable_dec_shift,
							 dec_shift,
							 &syncdec_mask) )
				{
					if ( do_multi_retries && syncdec_mask && !i )
					{
						retry_flag1 = 1;
						sc_fffffffe_res = 32;
					}
				}
				else if ( do_multi_retries )
				{
					retry_flag2 = 1;
					retry_flag1 = 1;
				}
				if ( retry_flag1 || cdvdfsv_r2retry )
				{
				}
				else if ( secsize == 2340 && !sector_size_selection )
				{
					if ( fssift )
					{
						if ( i )
						{
							cdvdfsv_memcpy((unsigned int *)(cdvdfsv_rtocbuf + 2340), (_DWORD *)((char *)((unsigned int *)cdvdfsv_rtocbuf) + fssift), 2340 - fssift);
							cdvdfsv_memcpy((unsigned int *)cdvdfsv_rtocbuf, (_DWORD *)&(cdvdfsv_rtocbuf + 4680)[2340 * csec - 2340], 0x924u);
							cdvdfsv_rdp2sdd.size = ((int)i == nsec_div_cdvdfsv_sectors - 1) ? dmasize_tmp : (2340 * (csec - 1) + fssift);
							cdvdfsv_memcpy((_DWORD *)((char *)((unsigned int *)(cdvdfsv_rtocbuf + 2340)) + 2340 - fssift), (_DWORD *)(cdvdfsv_rtocbuf + 4680), cdvdfsv_rdp2sdd.size);
						}
						else
						{
							cdvdfsv_memcpy((unsigned int *)cdvdfsv_rtocbuf, (_DWORD *)&(cdvdfsv_rtocbuf + 4680)[2340 * (csec - 1)], 0x924u);
							cdvdfsv_rdp2sdd.size = ((int)i == nsec_div_cdvdfsv_sectors - 1) ? dmasize_tmp : (2340 * (csec - 1));
							cdvdfsv_memcpy((unsigned int *)(cdvdfsv_rtocbuf + 2340), (_DWORD *)&(cdvdfsv_rtocbuf + 4680)[fssift], cdvdfsv_rdp2sdd.size);
						}
						cdvdfsv_rdp2sdd.src = (unsigned int *)(cdvdfsv_rtocbuf + 2340);
					}
					else
					{
						cdvdfsv_rdp2sdd.src = cdvdfsv_rtocbuf + 4680;
						cdvdfsv_rdp2sdd.size = 2340 * csec;
					}
					cdvdfsv_rdp2sdd.attr = 0;
					cdvdfsv_rdp2sdd.dest = ee_addr_tmp;
					ee_addr_tmp += cdvdfsv_rdp2sdd.size;
					dmasize_tmp -= cdvdfsv_rdp2sdd.size;
					while ( 1 )
					{
						CpuSuspendIntr(&state);
						trid = sceSifSetDma(&cdvdfsv_rdp2sdd, 1);
						CpuResumeIntr(state);
						if ( trid )
							break;
						DelayThread(500);
					}
					while ( cdvdfsv_checkdmastat(trid) >= 0 )
						;
				}
				else if ( !fssift )
				{
					for ( j = 0; j < csec; j += 1 )
					{
						cdvdfsv_multi_dmat[j].dest = &ee_addr[(csec_comm + j) * secsize];
						cdvdfsv_multi_dmat[j].src = &(cdvdfsv_rtocbuf + 4680)[(j * sector_size) + 12];
					}
					while ( 1 )
					{
						CpuSuspendIntr(&state);
						trid = sceSifSetDma(cdvdfsv_multi_dmat, csec);
						CpuResumeIntr(state);
						if ( trid )
							break;
						DelayThread(500);
					}
					while ( cdvdfsv_checkdmastat(trid) >= 0 )
						;
				}
				else
				{
					size_2 = ((int)i != nsec_div_cdvdfsv_sectors - 1) ? fssift : secsize;
					cdvdfsv_rdp2sdd.size = dmasize_tmp;
					if ( i )
					{
						cdvdfsv_memcpy((unsigned int *)(cdvdfsv_rtocbuf + 2340), (_DWORD *)((char *)((unsigned int *)cdvdfsv_rtocbuf) + fssift + 12), secsize - fssift);
						cdvdfsv_memcpy((unsigned int *)cdvdfsv_rtocbuf, (_DWORD *)&(cdvdfsv_rtocbuf + 4680)[(csec - 1) * sector_size], sector_size);
						for ( j = 0; j < csec - 1; j += 1 )
						{
							cdvdfsv_memcpy((_DWORD *)((char *)((unsigned int *)(cdvdfsv_rtocbuf + 2340)) + secsize - fssift + (j * secsize)), (_DWORD *)((char *)(cdvdfsv_rtocbuf + 4680) + 12 + (j * sector_size)), secsize);
						}
						cdvdfsv_memcpy((_DWORD *)((char *)((unsigned int *)(cdvdfsv_rtocbuf + 2340)) + secsize - fssift + ((csec - 1) * secsize)), (_DWORD *)((char *)(cdvdfsv_rtocbuf + 4680) + 12 + ((csec - 1) * sector_size)), size_2);
						if ( (int)i != nsec_div_cdvdfsv_sectors - 1 )
						{
							cdvdfsv_rdp2sdd.size = secsize * csec;
						}
					}
					else
					{
						cdvdfsv_memcpy((unsigned int *)cdvdfsv_rtocbuf, (_DWORD *)&(cdvdfsv_rtocbuf + 4680)[(csec - 1) * sector_size], sector_size);
						cdvdfsv_memcpy((unsigned int *)(cdvdfsv_rtocbuf + 2340), (_DWORD *)&(cdvdfsv_rtocbuf + 4680)[fssift + 12], secsize - fssift);
						for ( j = 0; j < csec - 2; j += 1 )
						{
							cdvdfsv_memcpy((_DWORD *)((char *)((unsigned int *)(cdvdfsv_rtocbuf + 2340)) + secsize - fssift + (j * secsize)), (_DWORD *)&(cdvdfsv_rtocbuf + 4680)[sector_size + 12 + (j * sector_size)], secsize);
						}
						cdvdfsv_memcpy((_DWORD *)((char *)((unsigned int *)(cdvdfsv_rtocbuf + 2340)) + secsize - fssift + ((csec - 2) * secsize)), (_DWORD *)&(cdvdfsv_rtocbuf + 4680)[sector_size + 12 + ((csec - 2) * sector_size)], size_2);
						if ( (int)i != nsec_div_cdvdfsv_sectors - 1 )
						{
							cdvdfsv_rdp2sdd.size = secsize * (csec - 1);
						}
					}
					cdvdfsv_rdp2sdd.src = (unsigned int *)(cdvdfsv_rtocbuf + 2340);
					cdvdfsv_rdp2sdd.attr = 0;
					cdvdfsv_rdp2sdd.dest = ee_addr_tmp;
					ee_addr_tmp += cdvdfsv_rdp2sdd.size;
					dmasize_tmp -= cdvdfsv_rdp2sdd.size;
					while ( 1 )
					{
						CpuSuspendIntr(&state);
						trid = sceSifSetDma(&cdvdfsv_rdp2sdd, 1);
						CpuResumeIntr(state);
						if ( trid )
							break;
						DelayThread(500);
					}
					while ( cdvdfsv_checkdmastat(trid) >= 0 )
						;
				}
			}
			else
			{
				retry_flag1 = 1;
			}
			CpuSuspendIntr(&state);
			if ( (int)i == nsec_div_cdvdfsv_sectors - 1 )
			{
				DisableIntr(35, (int *)&chcr);
			}
			else
			{
				csec_comm = csec_comm + csec;
				csec = ( (unsigned int)csec > nsec - (unsigned int)csec_comm ) ? (nsec - (unsigned int)csec_comm) : 16;
				ClearEventFlag(cdvdfsv_ef, 0xFFFFFFDF);
				dmac_ch_set_chcr(3u, 0);
				dmac_ch_get_chcr(3u);
				cdvdfsv_cdvdman_internal_struct_ptr->dma3prm.dma3_maddress = cdvdfsv_rtocbuf + 4680;
				dmac_ch_set_madr(3u, (u32)(cdvdfsv_rtocbuf + 4680));
				dmac_ch_set_bcr(
					3u,
					cdvdfsv_cdvdman_internal_struct_ptr->dma3prm.dma3_blkwords | ((cdvdfsv_cdvdman_internal_struct_ptr->dma3prm.dma3_blkcount
																																			 * csec) << 16));
				dmac_ch_set_chcr(3u, 0x41000200u);
				chcr = dmac_ch_get_chcr(3u);
				if ( post_dmat )
				{
					cdvdfsv_readpos += secsize * csec;
					sceSifSetDma(post_dmat, 1);
				}
			}
			CpuResumeIntr(state);
		}
		sceCdSync(5);
		CancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &cdvdfsv_read_to);
		cdvdfsv_cdvdman_internal_struct_ptr->dec_mode_set = 0;
		cdvdfsv_cdvdman_internal_struct_ptr->dec_state = 0;
		sc_fffffff1_res = sceCdGetError();
		if ( (unsigned __int16)cdvdfsv_cdvdman_internal_struct_ptr->dec_mode_last_set )
		{
			retry_flag2 = 1;
			sc_fffffff1_res = 0;
			mode->spindlctrl = 16;
		}
		if ( sc_fffffff1_res || cdvdfsv_r2count >= 5 )
			break;
		if ( !retry_flag2 )
		{
			if ( !sc_fffffffe_res )
				return 1;
			sceCdSC(0xFFFFFFFE, &sc_fffffffe_res);
			VERBOSE_KPRINTF(1, "secid_chk_ee_trns lsn %d nsec %d IPI Err\n", lsn, nsec);
			return 0;
		}
		if ( !cdvdfsv_r2retry )
		{
			++cdvdfsv_r2count;
			VERBOSE_PRINTF(1, "Read_CD/DVD-ROM Error Recover Start\n");
			cdvdfsv_r2retry = 3;
		}
	}
	if ( cdvdfsv_r2count >= 5 && !sc_fffffff1_res )
	{
		sceCdSC(-2, &cdvdfsv_rderror);
	}
	return 0;
}

//----- (00401A5C) --------------------------------------------------------
int __fastcall readproc1(
				unsigned int lsn,
				u32 nsec,
				void *retptr,
				sceCdRMode *rmode,
				int ps2dvd,
				int enable_retries,
				int dec_shift_enable,
				int dec_shift_value)
{
	int Error; // [sp+20h] [-10h] BYREF
	int state; // [sp+24h] [-Ch] BYREF
	u32 syncdec_mask; // [sp+28h] [-8h] BYREF
	int sc_fffffffe_tmp; // [sp+2Ch] [-4h] BYREF

	sc_fffffffe_tmp = 0;
	cdvdfsv_read_to.hi = 0;
	cdvdfsv_read_to.lo = 36864 * sceCdSC(0xFFFFFFF1, &Error);
	cdvdfsv_rderror = 253;
	cdvdfsv_sid_err_recover_cnt = 0;
	cdvdfsv_err_count = 0;
	while ( 1 )
	{
		int cmd_error; // $s0

		CpuSuspendIntr(&state);
		if ( dec_shift_enable )
		{
			cdvdfsv_cdvdman_internal_struct_ptr->dec_shift = dec_shift_value;
			cdvdfsv_cdvdman_internal_struct_ptr->dec_state = 2;
		}
		cmd_error = (ps2dvd ? sceCdRV : sceCdRead0)(( lsn >= 0x30 ) ? (lsn - 16 * cdvdfsv_sid_err_recover_cnt) : (lsn + 16 * cdvdfsv_sid_err_recover_cnt), nsec, retptr, rmode, 0, 0);
		CpuResumeIntr(state);
		if ( cmd_error )
			SetAlarm(&cdvdfsv_read_to, (unsigned int (__cdecl *)(void *))alarm_cb, &cdvdfsv_read_to);
		sceCdSync(5);
		CancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &cdvdfsv_read_to);
		cdvdfsv_cdvdman_internal_struct_ptr->dec_state = 0;
		Error = sceCdGetError();
		if ( Error || !cmd_error || cdvdfsv_err_count >= 5 )
		{
			VERBOSE_KPRINTF(1, "Read error error code %x cmd error %d\n", Error, cmd_error);
			if ( (!cmd_error || cdvdfsv_err_count >= 5) && (!Error) )
			{
				sceCdSC(0xFFFFFFFE, &cdvdfsv_rderror);
			}
			return 0;
		}
		if ( cdvdfsv_checksid(lsn, nsec, ps2dvd, retptr, dec_shift_enable, dec_shift_value, &syncdec_mask) )
		{
			if ( enable_retries && syncdec_mask )
				sc_fffffffe_tmp = 32;
			break;
		}
		if ( !enable_retries )
			break;
		if ( !cdvdfsv_sid_err_recover_cnt )
		{
			++cdvdfsv_err_count;
			VERBOSE_PRINTF(1, "Read_CD/DVD-ROM Sector_ID Error Recover Start\n");
			cdvdfsv_sid_err_recover_cnt = 3;
		}
		cdvdfsv_sid_err_recover_cnt -= 1;
	}
	if ( !sc_fffffffe_tmp )
		return 1;
	sceCdSC(0xFFFFFFFE, &sc_fffffffe_tmp);
	VERBOSE_KPRINTF(1, "secid_chk lsn %d nsec %d IPI Err\n", lsn, nsec);
	return 0;
}
// 405740: using guessed type int cdvdfsv_sid_err_recover_cnt;
// 405744: using guessed type int cdvdfsv_err_count;

//----- (00401DC4) --------------------------------------------------------
void __cdecl cdvdfsv_rpc5h_01_readee(
				cdvdfsv_rpc5h_01_packet *inbuf,
				int buflen,
				void *outbuf,
				u32 ps2dvd,
				int sync,
				int decflag)
{
	unsigned int secsize; // $s1
	unsigned int bsize; // $s5
	unsigned int bsize_tmp;
	unsigned int psize; // $s7
	unsigned int ssize; // $s6
	unsigned int i; // $a0
	int sizestuff; // $s2
	u32 needed_offset; // $s0
	int sector_sizes[2]; // [sp+30h] [-38h]
	int sc_ffffffea_tmp; // [sp+38h] [-30h] BYREF
	int sc_ffffffe9_tmp; // [sp+3Ch] [-2Ch] BYREF
	int state; // [sp+40h] [-28h] BYREF
	unsigned int buf_offs_sum; // [sp+44h] [-24h]
	unsigned int paddr; // [sp+48h] [-20h]
	int saddr; // [sp+4Ch] [-1Ch]
	int datapattern; // [sp+50h] [-18h]
	unsigned int len2_plus_sec2; // [sp+54h] [-14h]
	int trid; // [sp+58h] [-10h]
	int decval; // [sp+5Ch] [-Ch]
	cdvdfsv_rpc5h_01_packet *pkt_tmp; // [sp+60h] [-8h]
	int early_break;

	(void)buflen;

	early_break = 0;
	trid = 0;
	buf_offs_sum = 0;
	sector_sizes[0] = 2340;
	sector_sizes[1] = 2064;
	pkt_tmp = inbuf;
	cdvdfsv_rmodeee = inbuf->rmodeee;
	sc_ffffffe9_tmp = inbuf->lsn;
	decval = decflag ? pkt_tmp[1].flag : 0;
	cdvdfsv_eerpsdd.src = &cdvdfsv_readpos;
	cdvdfsv_eerpsdd.size = 4;
	cdvdfsv_eerpsdd.attr = 0;
	cdvdfsv_eerpsdd.dest = (void *)pkt_tmp[1].sec;
	if ( ps2dvd )
	{
		if ( !sceCdSC(0xFFFFFFEA, &sc_ffffffea_tmp) )
		{
			cdvdfsv_rderror = 254;
			sceCdSC(0xFFFFFFFE, &cdvdfsv_rderror);
			bsize = 0;
			psize = 0;
			ssize = 0;
			saddr = 0;
			paddr = 0;
			early_break = 1;
		}
		else
		{
			int sc_ffffffe9_res; // $v0

			sc_ffffffe9_res = sceCdSC(0xFFFFFFE9, &sc_ffffffe9_tmp);
			secsize = 2048;
			datapattern = 0;
			pkt_tmp->lsn = sc_ffffffe9_res;
			sc_ffffffe9_tmp = sc_ffffffe9_res;
			cdvdfsv_rmodeee.datapattern = 0;
		}
	}
	else
	{
		datapattern = cdvdfsv_rmodeee.datapattern;
		switch ( datapattern )
		{
			case 1:
				secsize = 2328;
				break;
			case 2:
				secsize = 2340;
				break;
			case 0:
			default:
				secsize = 2048;
				break;
		}
		cdvdfsv_rmodeee.datapattern = 2;
	}
	len2_plus_sec2 = pkt_tmp->lsn + pkt_tmp->sec;
	if ( !early_break )
	{
		int all_sec_bytes; // $lo

		all_sec_bytes = secsize * inbuf->sec;
		if ( cdvdfsv_spinctl != -1 )
			cdvdfsv_rmodeee.spindlctrl = cdvdfsv_spinctl;
		psize = ( (inbuf->flag & 0x3F) != 0 ) ? ((inbuf->flag & 0xFFFFFFC0) - (inbuf->flag - 64)) : 0;
		paddr = inbuf->flag;
		bsize = ((inbuf->flag + all_sec_bytes) & 0xFFFFFFC0) - (inbuf->flag + psize);
		ssize = inbuf->flag + all_sec_bytes - ((inbuf->flag + all_sec_bytes) & 0xFFFFFFC0);
		saddr = (inbuf->flag + all_sec_bytes) & 0xFFFFFFC0;
		VERBOSE_KPRINTF(1, "CD/DVD-ROM lsn= %d sec= %d\n", sc_ffffffe9_tmp, inbuf->sec);
		VERBOSE_KPRINTF(1, "f psize= %d bsize= %d ssize= %d\n", psize, bsize, ssize);
	}
	if ( psize )
	{
		u32 sectors; // $s0

		sectors = ( len2_plus_sec2 < sc_ffffffe9_tmp + buf_offs_sum / secsize + 2 ) ? 1 : 2;
		VERBOSE_PRINTF(1, "0 CD_READ LBN= %d sectors= %d all= %d\n", (int)(sc_ffffffe9_tmp + buf_offs_sum / secsize), (int)sectors, (int)inbuf->sec);
		if ( !readproc1(
						sc_ffffffe9_tmp + buf_offs_sum / secsize,
						sectors,
						cdvdfsv_rtocbuf,
						&cdvdfsv_rmodeee,
						ps2dvd,
						sync,
						decflag,
						decval) )
		{
			ssize = 0;
			psize = 0;
			bsize = 0;
		}
		else
		{
			if ( datapattern != 2 || ps2dvd )
			{
				int rtoc_ind; // $a1

				rtoc_ind = 12;
				for ( i = 0; i < psize; i += 1 )
				{
					rtoc_ind += ( i && !(i % secsize) ) ? (sector_sizes[ps2dvd] - secsize) : 0;
					cdvdfsv_eereadx.pbuf1[i] = cdvdfsv_rtocbuf[rtoc_ind + i];
				}
			}
			else
			{
				for ( i = 0; i < psize; i += 1 )
					cdvdfsv_eereadx.pbuf1[i] = cdvdfsv_rtocbuf[i];
			}
			buf_offs_sum += psize;
		}
	}
	bsize_tmp = bsize;
	for ( i = 0; i < bsize; i += sizestuff )
	{
		u32 offs_sector_only; // $a0

		bsize_tmp = bsize - i;
		if ( cdvdfsv_spinctl != -1 )
			cdvdfsv_rmodeee.spindlctrl = cdvdfsv_spinctl;
		offs_sector_only = sc_ffffffe9_tmp + buf_offs_sum / secsize;
		if ( (unsigned int)(secsize << 6) >= bsize_tmp )
		{
			needed_offset = (bsize_tmp / secsize) + (( bsize_tmp % secsize ) ? 1 : 0);
			sizestuff = bsize_tmp;
		}
		else
		{
			needed_offset = ( ((offs_sector_only & 0xF) != 0) && ((secsize & 0xF) == 0) ) ? (16 - (offs_sector_only & 0xF)) : 64;
			sizestuff = secsize * needed_offset;
		}
		needed_offset += ( (buf_offs_sum + i) % secsize ) ? 1 : 0;
		if ( len2_plus_sec2 < offs_sector_only + needed_offset )
			needed_offset = len2_plus_sec2 - (sc_ffffffe9_tmp + (buf_offs_sum + i) / secsize);
		cdvdfsv_readpos = buf_offs_sum + i;
		if ( !readproc2(
						offs_sector_only,
						needed_offset,
						&cdvdfsv_rmodeee,
						ps2dvd,
						sync,
						decflag,
						decval,
						(char *)(inbuf->flag + psize) + i,
						(buf_offs_sum + i) % secsize,
						secsize,
						sizestuff,
						&cdvdfsv_eerpsdd) )
		{
			bsize_tmp = 0;
			early_break = 1;
			break;
		}
		while ( cdvdfsv_checkdmastat(trid) >= 0 )
			;
		CpuSuspendIntr(&state);
		trid = sceSifSetDma(&cdvdfsv_eerpsdd, 1);
		CpuResumeIntr(state);
	}
	buf_offs_sum += i;
	bsize = bsize_tmp;
	if ( !early_break && ssize )
	{
		u32 sectors_1; // $s0
		unsigned int buf_offs_sum_bytes_in_sector; // $s3

		buf_offs_sum_bytes_in_sector = buf_offs_sum % secsize;
		sectors_1 = ( len2_plus_sec2 < sc_ffffffe9_tmp + buf_offs_sum / secsize + 2 ) ? 1 : 2;
		VERBOSE_PRINTF(1, "2 CD_READ LBN= %d sectors= %d\n", (int)(sc_ffffffe9_tmp + buf_offs_sum / secsize), (int)sectors_1);
		if ( !readproc1(
						sc_ffffffe9_tmp + buf_offs_sum / secsize,
						sectors_1,
						cdvdfsv_rtocbuf,
						&cdvdfsv_rmodeee,
						ps2dvd,
						sync,
						decflag,
						decval) )
		{
			bsize = 0;
		}
		else
		{
			if ( datapattern != 2 || ps2dvd )
			{
				int i2_offs; // $a1

				i2_offs = 12;
				for ( i = 0; i < ssize; i += 1 )
				{
					i2_offs += ( (i + buf_offs_sum_bytes_in_sector) && (i % secsize) == (secsize - (buf_offs_sum_bytes_in_sector ? buf_offs_sum_bytes_in_sector : secsize)) ) ? (sector_sizes[ps2dvd] - secsize) : 0;
					cdvdfsv_eereadx.pbuf2[i] = cdvdfsv_rtocbuf[buf_offs_sum_bytes_in_sector + i2_offs + i];
				}
			}
			else
			{
				for ( i = 0; i < ssize; i += 1 )
					cdvdfsv_eereadx.pbuf2[i] = cdvdfsv_rtocbuf[buf_offs_sum_bytes_in_sector + i];
			}
			buf_offs_sum += ssize;
		}
	}
	cdvdfsv_eereadx.b1len = psize;
	cdvdfsv_eereadx.b2len = ssize;
	cdvdfsv_eereadx.b1dst = paddr;
	cdvdfsv_eereadx.b2dst = saddr;
	VERBOSE_PRINTF(1, "b psize= %d paddr= %08x bsize= %d ssize= %d saddr %08x\n", (int)psize, paddr, (int)bsize, (int)ssize, saddr);
	while ( cdvdfsv_checkdmastat(trid) >= 0 )
		;
	cdvdfsv_datasdd.src = &cdvdfsv_eereadx;
	cdvdfsv_datasdd.size = 144;
	cdvdfsv_datasdd.attr = 0;
	cdvdfsv_readpos = buf_offs_sum;
	cdvdfsv_datasdd.dest = (void *)pkt_tmp[1].lsn;
	while ( 1 )
	{
		CpuSuspendIntr(&state);
		trid = sceSifSetDma(&cdvdfsv_datasdd, 1);
		sceSifSetDma(&cdvdfsv_eerpsdd, 1);
		CpuResumeIntr(state);
		if ( trid )
			break;
		DelayThread(500);
	}
	while ( cdvdfsv_checkdmastat(trid) >= 0 )
		;
	cdvdfsv_spinctl = -1;
	VERBOSE_PRINTF(1, "read end\n");
	*(_DWORD *)outbuf = buf_offs_sum;
}
// 402038: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 402090: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 402118: conditional instruction was optimized away because $s7.4!=0
// 402158: conditional instruction was optimized away because $s7.4!=0
// 40217C: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 402214: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 40228C: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 4022D0: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 4023A8: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 402404: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 40247C: conditional instruction was optimized away because $s6.4!=0
// 4024C4: conditional instruction was optimized away because $s6.4!=0
// 4024E8: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 402560: conditional instruction was optimized away because $s6.4!=0
// 40257C: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)

//----- (00402744) --------------------------------------------------------
int __fastcall cdvdfsv_chreadee(
				int secoffs,
				int seccount,
				char *ee_addr,
				const sceCdRMode *in_rmode,
				u32 disktype_14,
				int sync)
{
	unsigned int secsize; // $s1
	unsigned int i; // $s4
	int readsize_bytes; // $s2
	sceCdRMode rmode; // [sp+30h] [-10h] BYREF
	int scres1; // [sp+38h] [-8h] BYREF
	int sc_ffffffe9_res; // [sp+68h] [+28h] BYREF

	sc_ffffffe9_res = secoffs;
	rmode = *in_rmode;
	if ( disktype_14 )
	{
		if ( !sceCdSC(0xFFFFFFEA, &scres1) )
		{
			cdvdfsv_rderror = 254;
			sceCdSC(0xFFFFFFFE, &cdvdfsv_rderror);
			return 1;
		}
		secsize = 2048;
		sc_ffffffe9_res = sceCdSC(0xFFFFFFE9, &sc_ffffffe9_res);
		rmode.datapattern = 0;
	}
	else
	{
		switch ( rmode.datapattern )
		{
			case 1:
				secsize = 2328;
				break;
			case 2:
				secsize = 2340;
				break;
			case 0:
			default:
				secsize = 2048;
				break;
		}
		rmode.datapattern = 2;
	}
	for ( i = 0; i < (unsigned int)(secsize * seccount); i += readsize_bytes )
	{
		unsigned int bytescount; // $s0
		int sectors_partial; // $a1
		int bytescount_in_sectors; // $a1

		bytescount = (unsigned int)(secsize * seccount) - i;
		sectors_partial = (sc_ffffffe9_res + i / secsize) & 0xF;
		bytescount_in_sectors = 16;
		readsize_bytes = secsize * bytescount_in_sectors;
		if ( (unsigned int)readsize_bytes >= bytescount )
		{
			bytescount_in_sectors = (bytescount / secsize) + (( bytescount % secsize ) ? 1 : 0);
			readsize_bytes = bytescount;
		}
		else if ( sectors_partial && (secsize & 0xF) == 0 )
		{
			bytescount_in_sectors -= sectors_partial;
		}
		if ( !readproc2(
											sc_ffffffe9_res + i / secsize,
											bytescount_in_sectors,
											&rmode,
											disktype_14,
											sync,
											0,
											0,
											ee_addr + i,
											0,
											secsize,
											readsize_bytes,
											0) )
		{
			break;
		}
	}
	return 1;
}
// 402844: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 4028A0: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 402744: using guessed type sceCdRMode rmode;

//----- (0040293C) --------------------------------------------------------
void __fastcall cdvdfsv_rpc5h_0F_readchain(cdvdfsv_rpc5h_0F_packet *inbuf, int buflen, void *outbuf)
{
	int sector_size; // $s7
	unsigned int i; // $s5
	sceCdRChain *chain; // $s4
	void *buf; // $s1
	int re_result; // $s0
	int trid; // $s0
	int sc_fffffffc_tmp; // [sp+18h] [-8h] BYREF
	int state; // [sp+1Ch] [-4h] BYREF

	(void)buflen;
	(void)outbuf;

	cdvdfsv_rderror = 254;
	cdvdfsv_readpos = 0;
	cdvdfsv_cdvdman_internal_struct_ptr->m_break_cdvdfsv_readchain = 0;
	cdvdfsv_chrdsdd.src = &cdvdfsv_readpos;
	cdvdfsv_chrdsdd.size = 4;
	cdvdfsv_chrdsdd.attr = 0;
	cdvdfsv_chrdsdd.dest = (void *)inbuf->readPos;
	switch ( inbuf->scecdrmode30C.datapattern )
	{
		case 1:
			sector_size = 2328;
			break;
		case 2:
			sector_size = 2340;
			break;
		case 0:
		default:
			sector_size = 2048;
			break;
	}
	chain = (sceCdRChain *)inbuf;
	for ( i = 0; i < 0x40; i += 1 )
	{
		if ( cdvdfsv_cdvdman_internal_struct_ptr->m_break_cdvdfsv_readchain )
		{
			VERBOSE_PRINTF(1, "ReadChain cnt %d on sceCdBreak()\n", (int)i);
			return;
		}
		if ( chain[i].lbn == 0xFFFFFFFF || chain[i].sectors == 0xFFFFFFFF || chain[i].buffer == 0xFFFFFFFF )
			return;
		if ( (chain[i].buffer & 1) != 0 )
		{
			buf = (void *)(chain[i].buffer & 0xFFFFFFFE);
			VERBOSE_PRINTF(1, "ReadChain lsn= %d nsec= %d buf= %08x secsize= %d\n", (int)(chain[i].lbn), (int)(chain[i].sectors), (unsigned int)(uiptr)buf, inbuf->scecdrmode30C.datapattern);
			re_result = sceCdRE(chain[i].lbn, chain[i].sectors, buf, &(inbuf->scecdrmode30C));
			if ( re_result == 1 )
			{
				sceCdSync(0);
				re_result = sceCdGetError() == 0;
			}
			else
			{
				sceCdSC(0xFFFFFFFE, &cdvdfsv_rderror);
			}
		}
		else
		{
			VERBOSE_PRINTF(1, "ReadChain EE  Memory addr= 0x%08x sector= %d\n", (unsigned int)(chain[i].lbn), (int)(chain[i].sectors));
			// The following call to sceCdGetDiskType was inlined
			re_result = cdvdfsv_chreadee(chain[i].lbn, chain[i].sectors, (char *)chain[i].buffer, &(inbuf->scecdrmode30C), sceCdGetDiskType() == 0x14, sceCdSC(0xFFFFFFFC, &sc_fffffffc_tmp) == 0);
		}
		if ( !re_result )
		{
			VERBOSE_PRINTF(1, "ReadChain error code= 0x%02x\n", sceCdGetError());
			break;
		}
		cdvdfsv_readpos += chain[i].sectors * sector_size;
		while ( 1 )
		{
			CpuSuspendIntr(&state);
			trid = sceSifSetDma(&cdvdfsv_chrdsdd, 1);
			CpuResumeIntr(state);
			if ( trid )
				break;
			DelayThread(500);
		}
		while ( cdvdfsv_checkdmastat(trid) >= 0 )
			;
	}
}

//----- (00402C40) --------------------------------------------------------
void __fastcall cdvdfsv_rpc5h_02_readcdda(cdvdfsv_rpc5h_02_packet *inbuf, int buflen, void *outbuf)
{
	int trid1; // $s7
	unsigned int sector_size; // $s3
	int all_sec_bytes; // $t5
	unsigned int buf_1_toalign; // $v0
	int cmd_error; // $s1
	int error_code; // $s0
	unsigned int i; // $v1
	int trid2; // $s7
	int state; // [sp+10h] [-40h] BYREF
	int error_code_tmp; // [sp+14h] [-3Ch] BYREF
	unsigned int buf_offs; // [sp+18h] [-38h]
	unsigned int buf_toalign; // [sp+1Ch] [-34h]
	unsigned int buf_sec_tmp; // [sp+20h] [-30h]
	unsigned int lbn_1_end; // [sp+34h] [-1Ch]
	cdvdfsv_rpc5h_02_packet *pkt_tmp; // [sp+40h] [-10h]

	trid1 = 0;
	cdvdfsv_rderror = 254;
	error_code_tmp = 0;
	pkt_tmp = inbuf;
	cdvdfsv_eereadfull_dma2.src = &cdvdfsv_readpos;
	cdvdfsv_eereadfull_dma2.size = 4;
	cdvdfsv_eereadfull_dma2.attr = 0;
	cdvdfsv_eereadfull_dma2.dest = (void *)inbuf->eedest;
	switch ( inbuf->scecdrmodeC.datapattern )
	{
		case 1:
			sector_size = 2368;
			break;
		case 0:
		case 2:
		default:
			sector_size = 2352;
			break;
	}
	buf_offs = 0;
	all_sec_bytes = sector_size * inbuf->nsectors;
	lbn_1_end = inbuf->lbn + inbuf->nsectors;
	buf_toalign = ( (inbuf->buf & 0x3F) != 0 ) ? ((inbuf->buf & 0xFFFFFFC0) - (inbuf->buf - 64)) : 0;
	buf_1_toalign = (inbuf->buf + all_sec_bytes) & 0xFFFFFFC0;
	buf_sec_tmp = all_sec_bytes - (buf_1_toalign - inbuf->buf);
	if ( buf_toalign )
	{
		unsigned int buf_offs_sectors; // $lo
		u32 sectors_1; // $s0

		buf_offs_sectors = buf_offs / sector_size;
		sectors_1 = ( lbn_1_end < inbuf->lbn + buf_offs / sector_size + 2 ) ? 1 : 2;
		VERBOSE_PRINTF(1, "0 CD_READ LBN= %d sectors= %d all= %d\n", (int)(inbuf->lbn + buf_offs_sectors), (int)sectors_1, (int)inbuf->nsectors);
		cmd_error = sceCdReadCDDA(inbuf->lbn + buf_offs_sectors, sectors_1, cdvdfsv_rtocbuf, &inbuf->scecdrmodeC);
		sceCdSync(3);
		error_code = sceCdGetError();
		if ( error_code || !cmd_error )
		{
			if ( !cmd_error )
				sceCdSC(0xFFFFFFFE, &cdvdfsv_rderror);
			VERBOSE_PRINTF(1, "Read error code %x cmd error %d\n", error_code, cmd_error);
			if ( error_code == 50 || error_code == 56 )
				error_code_tmp = error_code;
			else
			{
				buf_toalign = 0;
			}
		}
		if ( error_code_tmp != 0 && error_code_tmp != 50 && error_code_tmp != 56 )
		{
			for ( i = 0; i < buf_toalign; i += 1 )
			{
				cdvdfsv_eereadx.pbuf1[i] = cdvdfsv_rtocbuf[i];
			}
			buf_offs += buf_toalign;
		}
	}
	if ( error_code_tmp != 0 && error_code_tmp != 50 && error_code_tmp != 56 )
	{
		unsigned int sector_count_in_bytes; // $s5
		unsigned int buf_aligned; // [sp+28h] [-28h]

		for ( buf_aligned = inbuf->buf + buf_toalign; buf_aligned < buf_1_toalign; buf_aligned += sector_count_in_bytes )
		{
			unsigned int buf_align_remain; // $s2
			unsigned int buf_offs_mod_sector_size; // $s4
			u32 lsn_2; // $s1
			u32 sector_count; // $s0

			buf_align_remain = buf_1_toalign - buf_aligned;
			buf_offs_mod_sector_size = buf_offs % sector_size;
			lsn_2 = inbuf->lbn + buf_offs / sector_size;
			sector_count_in_bytes = 8 * sector_size;
			if ( sector_count_in_bytes >= buf_align_remain )
			{
				sector_count_in_bytes = buf_align_remain;
				sector_count = (buf_align_remain / sector_size) + (( buf_align_remain % sector_size ) ? 1 : 0) + (buf_offs_mod_sector_size != 0);
			}
			else
			{
				sector_count = 8 + (( buf_offs % sector_size ) ? 1 : 0);
			}
			if ( sector_count > lbn_1_end - lsn_2 )
				sector_count = lbn_1_end - lsn_2;
			while ( cdvdfsv_checkdmastat(trid1) >= 0 )
				;
			cmd_error = sceCdReadCDDA(lsn_2, sector_count, cdvdfsv_rtocbuf, &inbuf->scecdrmodeC);
			sceCdSync(3);
			error_code = sceCdGetError();
			if ( error_code || !cmd_error )
			{
				if ( !cmd_error )
					sceCdSC(0xFFFFFFFE, &cdvdfsv_rderror);
				VERBOSE_PRINTF(1, "Read error code %x cmd error %d\n", error_code, cmd_error);
				if ( error_code == 50 || error_code == 56 )
				{
					error_code_tmp = error_code;
					break;
				}
			}
			if ( buf_offs_mod_sector_size )
				cdvdfsv_memcpy((_DWORD *)cdvdfsv_rtocbuf, (_DWORD *)&cdvdfsv_rtocbuf[buf_offs_mod_sector_size], sector_count_in_bytes);
			cdvdfsv_eereadfull_dma1.src = cdvdfsv_rtocbuf;
			cdvdfsv_eereadfull_dma1.size = sector_count_in_bytes;
			cdvdfsv_eereadfull_dma1.attr = 0;
			cdvdfsv_eereadfull_dma1.dest = (char *)buf_aligned;
			cdvdfsv_readpos = buf_offs;
			while ( 1 )
			{
				CpuSuspendIntr(&state);
				trid1 = sceSifSetDma(&cdvdfsv_eereadfull_dma1, 1);
				CpuResumeIntr(state);
				if ( trid1 )
					break;
				DelayThread(500);
			}
			if ( (unsigned int)buflen >= 0x19 )
			{
				CpuSuspendIntr(&state);
				sceSifSetDma(&cdvdfsv_eereadfull_dma2, 1);
				CpuResumeIntr(state);
			}
			buf_offs += sector_count_in_bytes;
		}
	}
	if ( (error_code_tmp != 0 && error_code_tmp != 50 && error_code_tmp != 56) && buf_sec_tmp )
	{
		u32 sectors_3; // $s0
		u32 lsn_3; // $s1

		lsn_3 = inbuf->lbn + buf_offs / sector_size;
		sectors_3 = ( lbn_1_end < lsn_3 + 2 ) ? 1 : 2;
		VERBOSE_PRINTF(1, "0 CD_READ LBN= %d sectors= %d all= %d\n", (int)(inbuf->lbn + buf_offs / sector_size), (int)sectors_3, (int)inbuf->nsectors);
		VERBOSE_PRINTF(1, "2 CD_READ LBN= %d sectors= %d\n", (int)lsn_3, (int)sectors_3);
		cmd_error = sceCdReadCDDA(lsn_3, sectors_3, cdvdfsv_rtocbuf, &inbuf->scecdrmodeC);
		sceCdSync(3);
		error_code = sceCdGetError();
		if ( error_code || !cmd_error )
		{
			if ( !cmd_error )
				sceCdSC(0xFFFFFFFE, &cdvdfsv_rderror);
			VERBOSE_PRINTF(1, "Read error code %x cmd error %d\n", error_code, cmd_error);
			if ( error_code == 50 || error_code == 56 )
				error_code_tmp = error_code;
			else
				buf_sec_tmp = 0;
		}
		for ( i = 0; i < buf_sec_tmp; i += 1 )
		{
			cdvdfsv_eereadx.pbuf2[i] = cdvdfsv_rtocbuf[(buf_offs % sector_size) + i];
		}
		buf_offs += buf_sec_tmp;
	}
	cdvdfsv_eereadx.b1len = buf_toalign;
	cdvdfsv_eereadx.b2len = buf_sec_tmp;
	cdvdfsv_eereadx.b1dst = inbuf->buf;
	cdvdfsv_eereadx.b2dst = buf_1_toalign;
	while ( cdvdfsv_checkdmastat(trid1) >= 0 )
		;
	cdvdfsv_eereadfull_dma1.src = &cdvdfsv_eereadx;
	cdvdfsv_eereadfull_dma1.size = 144;
	cdvdfsv_eereadfull_dma1.attr = 0;
	cdvdfsv_readpos = buf_offs;
	cdvdfsv_eereadfull_dma1.dest = (void *)pkt_tmp->eeremaindest;
	while ( 1 )
	{
		CpuSuspendIntr(&state);
		trid2 = sceSifSetDma(&cdvdfsv_eereadfull_dma1, 1);
		if ( (unsigned int)buflen >= 0x19 )
			sceSifSetDma(&cdvdfsv_eereadfull_dma2, 1);
		CpuResumeIntr(state);
		if ( trid2 )
			break;
		DelayThread(500);
	}
	while ( cdvdfsv_checkdmastat(trid2) >= 0 )
		;
	if ( error_code_tmp )
		sceCdSC(0xFFFFFFFE, &error_code_tmp);
	VERBOSE_PRINTF(1, "read end\n");
	*(_DWORD *)outbuf = buf_offs;
}
// 402D80: conditional instruction was optimized away because $s3.4 is in (==930|==940)
// 402E80: conditional instruction was optimized away because %buf_toalign.4!=0
// 402ED4: conditional instruction was optimized away because $s3.4 is in (==930|==940)
// 402F14: conditional instruction was optimized away because $s3.4 is in (==930|==940)
// 4030DC: conditional instruction was optimized away because $s3.4 is in (==930|==940)
// 403140: conditional instruction was optimized away because $s3.4 is in (==930|==940)

//----- (004033BC) --------------------------------------------------------
int *__fastcall cbrpc_rpc2_diskready(int fno, void *buffer, int length)
{
	(void)fno;
	(void)length;

	// The following call to sceCdStatus was inlined
	VERBOSE_KPRINTF(1, "DISK READY call 0x%02x\n", sceCdStatus());
	// The following call to sceCdDiskReady was inlined
	diskready_res = sceCdDiskReady(*(_DWORD *)buffer);
	return &diskready_res;
}
// 405BF0: using guessed type int diskready_res;

//----- (0040358C) --------------------------------------------------------
void __fastcall cdvdfsv_rpc5h_04_gettoc(void *inbuf, int buflen, cdvdfsv_rpc5h_04_outpacket *outbuf)
{
	int trid; // $s0
	int state; // [sp+10h] [-8h] BYREF

	(void)buflen;

	VERBOSE_PRINTF(1, "GET TOC call 0x%08x\n", (int)inbuf);
	outbuf->dword0 = sceCdGetToc(cdvdfsv_rtocbuf);
	VERBOSE_PRINTF(1, "GET TOC called\n");
	cdvdfsv_rtocsdd.src = cdvdfsv_rtocbuf;
	cdvdfsv_rtocsdd.size = 2064;
	cdvdfsv_rtocsdd.attr = 0;
	cdvdfsv_rtocsdd.dest = *(void **)inbuf;
	while ( 1 )
	{
		CpuSuspendIntr(&state);
		trid = sceSifSetDma(&cdvdfsv_rtocsdd, 1);
		CpuResumeIntr(state);
		if ( trid )
			break;
		DelayThread(500);
	}
	while ( cdvdfsv_checkdmastat(trid) >= 0 )
		;
	// The following call to sceCdGetDiskType was inlined
	switch ( sceCdGetDiskType() )
	{
		case 20:
		case 252:
		case 254:
			outbuf->dword4 = 1;
			break;
		default:
			outbuf->dword4 = 0;
			break;
	}
}

//----- (004036EC) --------------------------------------------------------
void __fastcall cdvdfsv_rpc3h_03_disktype(void *inbuf, int buflen, void *outbuf)
{
	(void)inbuf;
	(void)buflen;

	*(_DWORD *)outbuf = sceCdGetDiskType();
}

//----- (00403714) --------------------------------------------------------
void __fastcall cdvdfsv_rpc3h_0C_cdstatus(void *inbuf, int buflen, void *outbuf)
{
	(void)inbuf;
	(void)buflen;

	*(_DWORD *)outbuf = sceCdStatus();
}

//----- (0040373C) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_06_ri(void *inbuf, int buflen, cdvdfsv_rpc3h_06_outpacket *outbuf)
{
	int i; // $s1
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	(void)inbuf;
	(void)buflen;

	outbuf->dword0 = 0;
	for ( i = 0; i < 3 && !outbuf->dword0; i += 1 )
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		outbuf->dword0 = sceCdRI(&outbuf->buffer, &outbuf->result);
	}
}

//----- (004037A4) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_1A_rm(void *inbuf, int buflen, cdvdfsv_rpc3h_1A_outpacket *outbuf)
{
	int i; // $s1
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	(void)inbuf;
	(void)buflen;

	outbuf->dword0 = 0;
	for ( i = 0; i < 3 && !outbuf->dword0; i += 1 )
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		outbuf->dword0 = sceCdRM(&outbuf->buffer, &outbuf->status);
	}
}

//----- (0040380C) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_24_readguid(void *inbuf, int buflen, cdvdfsv_rpc3h_24_outpacket *outbuf)
{
	int i; // $s0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	(void)inbuf;
	(void)buflen;

	outbuf->dword0 = 0;
	for ( i = 0; i < 3 && !outbuf->dword0; i += 1 )
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		outbuf->dword0 = sceCdReadGUID(&outbuf->guid);
	}
}

//----- (00403870) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_26_readmodelid(void *inbuf, int buflen, cdvdfsv_rpc3h_26_outpacket *outbuf)
{
	int i; // $s0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	(void)inbuf;
	(void)buflen;

	outbuf->dword0 = 0;
	for ( i = 0; i < 3 && !outbuf->dword0; i += 1 )
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		outbuf->dword0 = sceCdReadModelID(&outbuf->id);
	}
}

//----- (004038D4) --------------------------------------------------------
void __fastcall cdvdfsv_rpc3h_22_mmode(const cdvdfsv_rpc3h_22_packet *inbuf, int buflen, void *outbuf)
{
	if ( buflen == 4 || inbuf->char4 == 0 )
	{
		*(_DWORD *)outbuf = sceCdMmode(inbuf->media);
	}
}

//----- (0040391C) --------------------------------------------------------
void __fastcall cdvdfsv_rpc3h_23_changethreadpriority(void *inbuf, int buflen, void *outbuf)
{
	(void)buflen;

	*(_DWORD *)outbuf = sceCdChangeThreadPriority(*(_DWORD *)inbuf);
}

//----- (00403948) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_21_poweroff(void *inbuf, int buflen, cdvdfsv_rpc3h_21_outpacket *outbuf)
{
	int i; // $s0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	(void)inbuf;
	(void)buflen;

	outbuf->dword0 = 0;
	for ( i = 0; i < 3 && !outbuf->dword0; i += 1 )
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		outbuf->dword0 = sceCdPowerOff(&outbuf->result);
	}
}

//----- (004039AC) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_15_ctrladout(void *inbuf, int buflen, cdvdfsv_rpc3h_15_outpacket *outbuf)
{
	int i; // $s0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	(void)inbuf;
	(void)buflen;

	for ( i = 0; i < 3 && !outbuf->dword0; i += 1 )
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		outbuf->dword0 = sceCdCtrlADout(*(_DWORD *)inbuf, &outbuf->status);
	}
}

//----- (00403A20) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_01_readclock(void *inbuf, int buflen, cdvdfsv_rpc3h_01_outpacke *outbuf)
{
	int i; // $s0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	(void)inbuf;
	(void)buflen;

	for ( i = 0; i < 3 && !outbuf->dword0; i += 1 )
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		outbuf->dword0 = sceCdReadClock(&outbuf->clock);
	}
}

//----- (00403A84) --------------------------------------------------------
void __fastcall cdvdfsv_rpc5h_11_readdiskid(void *inbuf, int buflen, cdvdfsv_rpc5h_11_outpacket *outbuf)
{
	u8 diskid_tmp[6]; // [sp+10h] [-10h] BYREF

	(void)inbuf;
	(void)buflen;

	outbuf->dword0 = sceCdReadDiskID((unsigned int *)diskid_tmp);
	outbuf->dword4 = *(_DWORD *)diskid_tmp;
	outbuf->word8 = *(_WORD *)&diskid_tmp[4];
}

//----- (00403AC0) --------------------------------------------------------
void __fastcall cdvdfsv_rpc5h_17_doesuniquekeyexist(void *inbuf, int buflen, cdvdfsv_rpc5h_17_outpacket *outbuf)
{
	(void)inbuf;
	(void)buflen;

	outbuf->dword0 = sceCdDoesUniqueKeyExist(&outbuf->arg1);
}

//----- (00403AEC) --------------------------------------------------------
void __fastcall cdvdfsv_rpc3h_0B_applyscmd(
				cdvdfsv_rpc3h_0B_packet *inbuf,
				int buflen,
				cdvdfsv_rpc3h_0B_outpacket *outbuf)
{
	int buf_tmp[4]; // [sp+10h] [-10h] BYREF

	(void)buflen;

	sceCdApplySCmd(inbuf->cmdNum, &inbuf->inBuff, inbuf->inBuffSize, buf_tmp);
	outbuf->dword0 = buf_tmp[0];
	outbuf->dword4 = buf_tmp[1];
	outbuf->dword8 = buf_tmp[2];
	outbuf->dwordC = buf_tmp[3];
}

//----- (00403B64) --------------------------------------------------------
void __fastcall cdvdfsv_rpc5h_0C_applyncmd(cdvdfsv_rpc5h_0C_packet *inbuf, int buflen, void *outbuf)
{
	(void)buflen;

	*(_DWORD *)outbuf = sceCdApplyNCmd(inbuf->cmdNum, &inbuf->inBuff, inbuf->inBuffSize);
	sceCdSync(2);
}

//----- (00403BA4) --------------------------------------------------------
void __fastcall cdvdfsv_rpc3h_04_geterror(void *inbuf, int buflen, void *outbuf)
{
	(void)inbuf;
	(void)buflen;

	*(_DWORD *)outbuf = sceCdGetError();
}

//----- (00403BCC) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_05_trayreq(void *inbuf, int buflen, cdvdfsv_rpc3h_05_outpacket *outbuf)
{
	int i; // $s0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	(void)buflen;

	for ( i = 0; i < 3 && !outbuf->dword0; i += 1 )
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		outbuf->dword0 = sceCdTrayReq(*(_DWORD *)inbuf, &outbuf->traychk);
	}
}

//----- (00403C40) --------------------------------------------------------
void __fastcall cdvdfsv_rpc3h_25_settimeout(const cdvdfsv_rpc3h_25_packet *inbuf, int buflen, void *outbuf)
{
	(void)buflen;

	*(_DWORD *)outbuf = sceCdSetTimeout(inbuf->param, inbuf->timeout);
}

//----- (00403C74) --------------------------------------------------------
void __fastcall cdvdfsv_rpc3h_27_readdvddualinfo(void *inbuf, int buflen, cdvdfsv_rpc3h_27_outpacket *outbuf)
{
	(void)inbuf;
	(void)buflen;

	outbuf->dword0 = sceCdReadDvdDualInfo(&outbuf->on_dual, &outbuf->layer1_start);
}

//----- (00403CA4) --------------------------------------------------------
int __cdecl cdvdfsv_rpc5h_0E_diskready()
{
	int is_detecting; // $s1
	int scval_tmp[2]; // [sp+10h] [-8h] BYREF

	is_detecting = 0;
	// The following call to sceCdGetDiskType was inlined
	switch ( sceCdGetDiskType() )
	{
		case 1:
		case 2:
		case 3:
		case 4:
			is_detecting = 1;
			break;
		default:
			break;
	}
	// The following call to sceCdDiskReady was inlined
	if ( (sceCdDiskReady(8) & 0xC0) != 64
		|| sceCdSC(0xFFFFFFFD, scval_tmp)
		|| !sceCdSC(0xFFFFFFF4, scval_tmp)
		|| is_detecting)
	{
		VERBOSE_PRINTF(1, "Drive Not Ready\n");
		return 6;
	}
	return 2;
}

//----- (00403D4C) --------------------------------------------------------
CDVDReadResult *__fastcall cbrpc_rpc5_cdvdncmds(int fno, void *buffer, int length)
{
	int sc_fffffff6_in[2]; // [sp+18h] [-8h] BYREF
	int fno_1; // [sp+30h] [+10h] BYREF

	fno_1 = fno;
	VERBOSE_PRINTF(1, "sce_cdvd N cmd start %d\n", fno);
	cdvdfsv_rpc5flg = 1;
	sceCdSC(-10, &fno_1);
	switch ( fno )
	{
		case 1:
			// The following call to sceCdGetDiskType was inlined
			cdvdfsv_rpc5h_01_readee((cdvdfsv_rpc5h_01_packet *)buffer, length, crr, (sceCdGetDiskType() ^ 0x14) == 0, sceCdSC(-4, sc_fffffff6_in) == 0, 0);
			break;
		case 2:
			cdvdfsv_rpc5h_02_readcdda((cdvdfsv_rpc5h_02_packet *)buffer, length, crr);
			break;
		case 4:
			cdvdfsv_rpc5h_04_gettoc(buffer, length, (cdvdfsv_rpc5h_04_outpacket *)crr);
			break;
		case 5:
			VERBOSE_PRINTF(1, "Call Seek lsn= %d\n", (int)(*(_DWORD *)buffer));
			crr[0] = sceCdSeek(*(_DWORD *)buffer);
			VERBOSE_PRINTF(1, "Call Seek end\n");
			sceCdSync(6);
			break;
		case 6:
			VERBOSE_PRINTF(1, "Call Standby\n");
			crr[0] = sceCdStandby();
			sceCdSync(4);
			VERBOSE_PRINTF(1, "Call Standby called\n");
			break;
		case 7:
			VERBOSE_PRINTF(1, "Call Stop\n");
			crr[0] = sceCdStop();
			sceCdSync(4);
			break;
		case 8:
			VERBOSE_PRINTF(1, "Call Pause\n");
			crr[0] = sceCdPause();
			sceCdSync(6);
			break;
		case 9:
			if ( devctl("cdrom_stm0:", 0x4396, buffer, length, crr, 4u) < 0 )
				crr[0] = 0;
			break;
		case 10:
			if ( devctl("cdrom_stm0:", 0x4398, buffer, length, crr, 4u) < 0 )
				crr[0] = 0;
			break;
		case 12:
			cdvdfsv_rpc5h_0C_applyncmd((cdvdfsv_rpc5h_0C_packet *)buffer, length, crr);
			break;
		case 13:
			cdvdfsv_rpc5h_0D_iopmread((cdvdfsv_rpc5h_0D_packet *)buffer, length, crr);
			break;
		case 14:
			crr[0] = cdvdfsv_rpc5h_0E_diskready();
			break;
		case 15:
			cdvdfsv_rpc5h_0F_readchain((cdvdfsv_rpc5h_0F_packet *)buffer, length, crr);
			break;
		case 17:
			cdvdfsv_rpc5h_11_readdiskid(buffer, length, (cdvdfsv_rpc5h_11_outpacket *)crr);
			break;
		case 19:
			// The following call to sceCdGetDiskType was inlined
			cdvdfsv_rpc5h_01_readee(
				(cdvdfsv_rpc5h_01_packet *)buffer,
				length,
				crr,
				(sceCdGetDiskType() ^ 0x14) == 0,
				1,
				cdvdfsv_cdvdman_internal_struct_ptr->no_dec_flag == 0);
			break;
		case 23:
			cdvdfsv_rpc5h_17_doesuniquekeyexist(buffer, length, (cdvdfsv_rpc5h_17_outpacket *)crr);
			break;
		default:
			VERBOSE_PRINTF(1, "sce_cdvd no block IO :unrecognized code %x\n", fno);
			crr[0] = 0;
			break;
	}
	sc_fffffff6_in[0] = 0;
	sceCdSC(-10, sc_fffffff6_in);
	cdvdfsv_rpc5flg = 0;
	VERBOSE_PRINTF(1, "sce_cdvd N cmd end\n");
	return (CDVDReadResult *)crr;
}

//----- (00404160) --------------------------------------------------------
CDVDCmdResult *__fastcall cbrpc_rpc3_cdvdscmds(int fno, void *buffer, int length)
{
	VERBOSE_PRINTF(1, "sce_cdvd S cmd start %d\n", fno);
	cdvdfsv_rpc3flg = 1;
	switch ( fno )
	{
		case 1:
			cdvdfsv_rpc3h_01_readclock(buffer, length, (cdvdfsv_rpc3h_01_outpacke *)&outbuf);
			break;
		case 3:
			cdvdfsv_rpc3h_03_disktype(buffer, length, &outbuf);
			break;
		case 4:
			cdvdfsv_rpc3h_04_geterror(buffer, length, &outbuf);
			break;
		case 5:
			cdvdfsv_rpc3h_05_trayreq(buffer, length, (cdvdfsv_rpc3h_05_outpacket *)&outbuf);
			break;
		case 6:
			cdvdfsv_rpc3h_06_ri(buffer, length, (cdvdfsv_rpc3h_06_outpacket *)&outbuf);
			break;
		case 11:
			cdvdfsv_rpc3h_0B_applyscmd((cdvdfsv_rpc3h_0B_packet *)buffer, length, (cdvdfsv_rpc3h_0B_outpacket *)&outbuf);
			break;
		case 12:
			cdvdfsv_rpc3h_0C_cdstatus(buffer, length, &outbuf);
			break;
		case 21:
			cdvdfsv_rpc3h_15_ctrladout(buffer, length, (cdvdfsv_rpc3h_15_outpacket *)&outbuf);
			break;
		case 22:
			cdvdfsv_rpc3h_16_break(buffer, length, &outbuf);
			break;
		case 26:
			cdvdfsv_rpc3h_1A_rm(buffer, length, (cdvdfsv_rpc3h_1A_outpacket *)&outbuf);
			break;
		case 33:
			cdvdfsv_rpc3h_21_poweroff(buffer, length, (cdvdfsv_rpc3h_21_outpacket *)&outbuf);
			break;
		case 34:
			cdvdfsv_rpc3h_22_mmode((cdvdfsv_rpc3h_22_packet *)buffer, length, &outbuf);
			break;
		case 35:
			cdvdfsv_rpc3h_23_changethreadpriority(buffer, length, &outbuf);
			break;
		case 36:
			cdvdfsv_rpc3h_24_readguid(buffer, length, (cdvdfsv_rpc3h_24_outpacket *)&outbuf);
			break;
		case 37:
			cdvdfsv_rpc3h_25_settimeout((cdvdfsv_rpc3h_25_packet *)buffer, length, &outbuf);
			break;
		case 38:
			cdvdfsv_rpc3h_26_readmodelid(buffer, length, (cdvdfsv_rpc3h_26_outpacket *)&outbuf);
			break;
		case 39:
			cdvdfsv_rpc3h_27_readdvddualinfo(buffer, length, &outbuf);
			break;
		default:
			VERBOSE_PRINTF(1, "sce_cdvd block IO :unrecognized code 0x%02x\n", fno);
			outbuf.dword0 = 0;
			break;
	}
	VERBOSE_PRINTF(1, "sce_cdvd S cmd end\n");
	cdvdfsv_rpc3flg = 0;
	return (CDVDCmdResult *)&outbuf;
}
// 405720: using guessed type int cdvdfsv_rpc3flg;

//----- (00404424) --------------------------------------------------------
void __cdecl cdvdfsv_poffloop()
{
	int trid; // $s0
	char cmdpkt[16]; // [sp+18h] [-18h] BYREF
	int scres; // [sp+28h] [-8h] BYREF
	u32 efres; // [sp+2Ch] [-4h] BYREF

	cdvdfsv_ef = sceCdSC(0xFFFFFFF5, &scres);
	while ( 1 )
	{
		ClearEventFlag(cdvdfsv_ef, 0xFFFFFFFB);
		WaitEventFlag(cdvdfsv_ef, 4u, 0, &efres);
		if ( cdvdfsv_nopocm )
			break;
		if ( !cdvdfsv_plbreak )
		{
			while ( 1 )
			{
				trid = sceSifSendCmd(0x80000012, cmdpkt, 16, 0, 0, 0);
				if ( trid )
					break;
				DelayThread(500);
			}
			while ( cdvdfsv_checkdmastat(trid) >= 0 )
				;
		}
	}
}
// 404424: using guessed type char cmdpkt[16];

//----- (004044F4) --------------------------------------------------------
void __cdecl cdvdfsv_rpc1_th(void *arg)
{
	(void)arg;

	sceSifSetRpcQueue(&rpc_qdata1, GetThreadId());
	sceSifRegisterRpc(&rpc_sdata1, 0x80000592, (SifRpcFunc_t)cbrpc_rpc1_cdinit, rpc_buffer1, 0, 0, &rpc_qdata1);
	sceSifRegisterRpc(&rpc_sdata2, 0x8000059A, (SifRpcFunc_t)cbrpc_rpc2_diskready, rpc_buffer2, 0, 0, &rpc_qdata1);
	sceSifRegisterRpc(&rpc_sdata3, 0x80000593, (SifRpcFunc_t)cbrpc_rpc3_cdvdscmds, rpc_buffer3, 0, 0, &rpc_qdata1);
	sceSifRpcLoop(&rpc_qdata1);
	ExitDeleteThread();
}

//----- (004045CC) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3_th(void *arg)
{
	(void)arg;

	sceSifSetRpcQueue(&rpc_qdata3, GetThreadId());
	sceSifRegisterRpc(&rpc_sdata6, 0x8000059C, (SifRpcFunc_t)cbrpc_rpc2_diskready, rpc_buffer2, 0, 0, &rpc_qdata3);
	sceSifRpcLoop(&rpc_qdata3);
	ExitDeleteThread();
}

//----- (00404644) --------------------------------------------------------
void __cdecl cdvdfsv_rpc2_th(void *arg)
{
	(void)arg;

	sceSifSetRpcQueue(&rpc_qdata2, GetThreadId());
	sceSifRegisterRpc(&rpc_sdata4, 0x80000597, (SifRpcFunc_t)cbrpc_rpc4_fscall, rpc_buffer4, 0, 0, &rpc_qdata2);
	sceSifRegisterRpc(&rpc_sdata5, 0x80000595, (SifRpcFunc_t)cbrpc_rpc5_cdvdncmds, rpc_buffer5, 0, 0, &rpc_qdata2);
	sceSifRpcLoop(&rpc_qdata2);
	ExitDeleteThread();
}

//----- (004046F0) --------------------------------------------------------
void __fastcall cdvdfsv_unused_xorfun(unsigned int *a1, int a2)
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
					v2 ^= 0x80000011;
				v7 = (v6 & 0x80) == 0;
				v6 *= 2;
				if ( !v7 )
					v2 ^= 1u;
			}
			v3 >>= 8;
		}
		++a1;
	}
}

//----- (0040475C) --------------------------------------------------------
unsigned int __fastcall cdvdfsv_memcpy(_DWORD *a1, _DWORD *a2, unsigned int a3)
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

	if ( a3 >> 2 )
	{
		if ( (((uiptr)a1 | (uiptr)a2) & 3) != 0 )
		{
			if ( ((uiptr)a1 & 3) != 0 && ((uiptr)a2 & 3) != 0 )
			{
				v16 = (int)(a3 >> 2) / 12;
				v17 = (int)(a3 >> 2) % 12;
				if ( !v17 )
					goto LABEL_30;
				do
				{
					--v17;
					*a1++ = *a2++;
				}
				while ( v17 );
				if ( v16 )
				{
LABEL_30:
					do
					{
						v18 = a2[1];
						v19 = a2[2];
						v20 = a2[3];
						v21 = a2[4];
						v22 = a2[5];
						v23 = a2[6];
						v24 = a2[7];
						v25 = a2[8];
						v26 = a2[9];
						v27 = a2[10];
						v28 = a2[11];
						--v16;
						*a1 = *a2;
						a1[1] = v18;
						a1[2] = v19;
						a1[3] = v20;
						a1[4] = v21;
						a1[5] = v22;
						a1[6] = v23;
						a1[7] = v24;
						a1[8] = v25;
						a1[9] = v26;
						a1[10] = v27;
						a1[11] = v28;
						a2 += 12;
						a1 += 12;
					}
					while ( v16 );
				}
			}
			else if ( ((uiptr)a1 & 3) != 0 )
			{
				v29 = (int)(a3 >> 2) / 12;
				v30 = (int)(a3 >> 2) % 12;
				if ( !v30 )
					goto LABEL_31;
				do
				{
					--v30;
					*a1++ = *a2++;
				}
				while ( v30 );
				if ( v29 )
				{
LABEL_31:
					do
					{
						v31 = a2[1];
						v32 = a2[2];
						v33 = a2[3];
						v34 = a2[4];
						v35 = a2[5];
						v36 = a2[6];
						v37 = a2[7];
						v38 = a2[8];
						v39 = a2[9];
						v40 = a2[10];
						v41 = a2[11];
						--v29;
						*a1 = *a2;
						a1[1] = v31;
						a1[2] = v32;
						a1[3] = v33;
						a1[4] = v34;
						a1[5] = v35;
						a1[6] = v36;
						a1[7] = v37;
						a1[8] = v38;
						a1[9] = v39;
						a1[10] = v40;
						a1[11] = v41;
						a2 += 12;
						a1 += 12;
					}
					while ( v29 );
				}
			}
			else
			{
				v42 = (int)(a3 >> 2) / 12;
				v43 = (int)(a3 >> 2) % 12;
				if ( !v43 )
					goto LABEL_32;
				do
				{
					--v43;
					*a1++ = *a2++;
				}
				while ( v43 );
				if ( v42 )
				{
LABEL_32:
					do
					{
						v44 = a2[1];
						v45 = a2[2];
						v46 = a2[3];
						v47 = a2[4];
						v48 = a2[5];
						v49 = a2[6];
						v50 = a2[7];
						v51 = a2[8];
						v52 = a2[9];
						v53 = a2[10];
						v54 = a2[11];
						--v42;
						*a1 = *a2;
						a1[1] = v44;
						a1[2] = v45;
						a1[3] = v46;
						a1[4] = v47;
						a1[5] = v48;
						a1[6] = v49;
						a1[7] = v50;
						a1[8] = v51;
						a1[9] = v52;
						a1[10] = v53;
						a1[11] = v54;
						a2 += 12;
						a1 += 12;
					}
					while ( v42 );
				}
			}
		}
		else
		{
			v3 = (int)(a3 >> 2) / 12;
			v4 = (int)(a3 >> 2) % 12;
			if ( !v4 )
				goto LABEL_33;
			do
			{
				--v4;
				*a1++ = *a2++;
			}
			while ( v4 );
			if ( v3 )
			{
LABEL_33:
				do
				{
					v5 = a2[1];
					v6 = a2[2];
					v7 = a2[3];
					v8 = a2[4];
					v9 = a2[5];
					v10 = a2[6];
					v11 = a2[7];
					v12 = a2[8];
					v13 = a2[9];
					v14 = a2[10];
					v15 = a2[11];
					--v3;
					*a1 = *a2;
					a1[1] = v5;
					a1[2] = v6;
					a1[3] = v7;
					a1[4] = v8;
					a1[5] = v9;
					a1[6] = v10;
					a1[7] = v11;
					a1[8] = v12;
					a1[9] = v13;
					a1[10] = v14;
					a1[11] = v15;
					a2 += 12;
					a1 += 12;
				}
				while ( v3 );
			}
		}
	}
	v55 = a3 & 3;
	if ( (a3 & 3) != 0 )
	{
		do
		{
			--v55;
			*(_BYTE *)a1 = *(_BYTE *)a2;
			a2 = (_DWORD *)((char *)a2 + 1);
			a1 = (_DWORD *)((char *)a1 + 1);
		}
		while ( v55 );
	}
	return a3;
}

//----- (00404B90) --------------------------------------------------------
void cdvdfsv_1()
{
	;
}

#if 0
//----- (00404BB4) --------------------------------------------------------
int Kprintf(const char *format, ...)
{
	int result; // $v0

	return result;
}
// 404BB4: variable 'result' is possibly undefined

//----- (00404BD8) --------------------------------------------------------
int __cdecl RegisterLibraryEntries(struct irx_export_table *exports)
{
	int result; // $v0

	return result;
}
// 404BD8: variable 'result' is possibly undefined

//----- (00404BE0) --------------------------------------------------------
int __cdecl ReleaseLibraryEntries(struct irx_export_table *exports)
{
	int result; // $v0

	return result;
}
// 404BE0: variable 'result' is possibly undefined

//----- (00404BE8) --------------------------------------------------------
void *__cdecl QueryLibraryEntryTable(iop_library_t *library)
{
	void *result; // $v0

	return result;
}
// 404BE8: variable 'result' is possibly undefined

//----- (00404BF0) --------------------------------------------------------
int *__cdecl QueryBootMode(int mode)
{
	int *result; // $v0

	return result;
}
// 404BF0: variable 'result' is possibly undefined

//----- (00404C14) --------------------------------------------------------
int __cdecl DisableIntr(int irq, int *res)
{
	int result; // $v0

	return result;
}
// 404C14: variable 'result' is possibly undefined

//----- (00404C1C) --------------------------------------------------------
int __cdecl CpuSuspendIntr(int *state)
{
	int result; // $v0

	return result;
}
// 404C1C: variable 'result' is possibly undefined

//----- (00404C24) --------------------------------------------------------
int __cdecl CpuResumeIntr(int state)
{
	int result; // $v0

	return result;
}
// 404C24: variable 'result' is possibly undefined

//----- (00404C2C) --------------------------------------------------------
int QueryIntrContext(void)
{
	int result; // $v0

	return result;
}
// 404C2C: variable 'result' is possibly undefined

//----- (00404C50) --------------------------------------------------------
int printf(const char *format, ...)
{
	int result; // $v0

	return result;
}
// 404C50: variable 'result' is possibly undefined

//----- (00404C74) --------------------------------------------------------
void __cdecl dmac_ch_set_madr(u32 channel, u32 val)
{
	;
}

//----- (00404C7C) --------------------------------------------------------
void __cdecl dmac_ch_set_bcr(u32 channel, u32 val)
{
	;
}

//----- (00404C84) --------------------------------------------------------
void __cdecl dmac_ch_set_chcr(u32 channel, u32 val)
{
	;
}

//----- (00404C8C) --------------------------------------------------------
u32 __cdecl dmac_ch_get_chcr(u32 channel)
{
	u32 result; // $v0

	return result;
}
// 404C8C: variable 'result' is possibly undefined

//----- (00404CB0) --------------------------------------------------------
int __cdecl CreateThread(iop_thread_t *thread)
{
	int result; // $v0

	return result;
}
// 404CB0: variable 'result' is possibly undefined

//----- (00404CB8) --------------------------------------------------------
int __cdecl DeleteThread(int thid)
{
	int result; // $v0

	return result;
}
// 404CB8: variable 'result' is possibly undefined

//----- (00404CC0) --------------------------------------------------------
int __cdecl StartThread(int thid, void *arg)
{
	int result; // $v0

	return result;
}
// 404CC0: variable 'result' is possibly undefined

//----- (00404CC8) --------------------------------------------------------
int __cdecl ExitDeleteThread()
{
	int result; // $v0

	return result;
}
// 404CC8: variable 'result' is possibly undefined

//----- (00404CD0) --------------------------------------------------------
int __cdecl TerminateThread(int thid)
{
	int result; // $v0

	return result;
}
// 404CD0: variable 'result' is possibly undefined

//----- (00404CD8) --------------------------------------------------------
int __cdecl ChangeThreadPriority(int thid, int priority)
{
	int result; // $v0

	return result;
}
// 404CD8: variable 'result' is possibly undefined

//----- (00404CE0) --------------------------------------------------------
int GetThreadId(void)
{
	int result; // $v0

	return result;
}
// 404CE0: variable 'result' is possibly undefined

//----- (00404CE8) --------------------------------------------------------
int __cdecl ReferThreadStatus(int thid, iop_thread_info_t *info)
{
	int result; // $v0

	return result;
}
// 404CE8: variable 'result' is possibly undefined

//----- (00404CF0) --------------------------------------------------------
int __cdecl DelayThread(int usec)
{
	int result; // $v0

	return result;
}
// 404CF0: variable 'result' is possibly undefined

//----- (00404CF8) --------------------------------------------------------
int __cdecl SetAlarm(iop_sys_clock_t *sys_clock, unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	int result; // $v0

	return result;
}
// 404CF8: variable 'result' is possibly undefined

//----- (00404D00) --------------------------------------------------------
int __cdecl CancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	int result; // $v0

	return result;
}
// 404D00: variable 'result' is possibly undefined

//----- (00404D24) --------------------------------------------------------
int __cdecl iSetEventFlag(int ef, u32 bits)
{
	int result; // $v0

	return result;
}
// 404D24: variable 'result' is possibly undefined

//----- (00404D2C) --------------------------------------------------------
int __cdecl ClearEventFlag(int ef, u32 bits)
{
	int result; // $v0

	return result;
}
// 404D2C: variable 'result' is possibly undefined

//----- (00404D34) --------------------------------------------------------
int __cdecl WaitEventFlag(int ef, u32 bits, int mode, u32 *resbits)
{
	int result; // $v0

	return result;
}
// 404D34: variable 'result' is possibly undefined

//----- (00404D58) --------------------------------------------------------
unsigned int __cdecl sceSifSendCmd(
				int cmd,
				void *packet,
				int packet_size,
				void *src_extra,
				void *dest_extra,
				int size_extra)
{
	unsigned int result; // $v0

	return result;
}
// 404D58: variable 'result' is possibly undefined

//----- (00404D60) --------------------------------------------------------
void __cdecl sceSifInitRpc(int mode)
{
	;
}

//----- (00404D68) --------------------------------------------------------
void __cdecl sceSifRegisterRpc(
				SifRpcServerData_t *sd,
				int sid,
				SifRpcFunc_t func,
				void *buf,
				SifRpcFunc_t cfunc,
				void *cbuf,
				SifRpcDataQueue_t *qd)
{
	;
}

//----- (00404D70) --------------------------------------------------------
SifRpcDataQueue_t *__cdecl sceSifSetRpcQueue(SifRpcDataQueue_t *q, int thread_id)
{
	SifRpcDataQueue_t *result; // $v0

	return result;
}
// 404D70: variable 'result' is possibly undefined

//----- (00404D78) --------------------------------------------------------
void __cdecl sceSifRpcLoop(SifRpcDataQueue_t *qd)
{
	;
}

//----- (00404D80) --------------------------------------------------------
SifRpcServerData_t *__cdecl sceSifRemoveRpc(SifRpcServerData_t *sd, SifRpcDataQueue_t *qd)
{
	SifRpcServerData_t *result; // $v0

	return result;
}
// 404D80: variable 'result' is possibly undefined

//----- (00404D88) --------------------------------------------------------
SifRpcDataQueue_t *__cdecl sceSifRemoveRpcQueue(SifRpcDataQueue_t *qd)
{
	SifRpcDataQueue_t *result; // $v0

	return result;
}
// 404D88: variable 'result' is possibly undefined

//----- (00404DAC) --------------------------------------------------------
void __cdecl sceSifInit()
{
	;
}

//----- (00404DB4) --------------------------------------------------------
int __cdecl sceSifSetDma(SifDmaTransfer_t *dmat, int count)
{
	int result; // $v0

	return result;
}
// 404DB4: variable 'result' is possibly undefined

//----- (00404DBC) --------------------------------------------------------
int __cdecl sceSifDmaStat(int trid)
{
	int result; // $v0

	return result;
}
// 404DBC: variable 'result' is possibly undefined

//----- (00404DC4) --------------------------------------------------------
int __cdecl sceSifCheckInit()
{
	int result; // $v0

	return result;
}
// 404DC4: variable 'result' is possibly undefined

//----- (00404DE8) --------------------------------------------------------
int __cdecl strncmp(const char *p, const char *q, size_t size)
{
	int result; // $v0

	return result;
}
// 404DE8: variable 'result' is possibly undefined

//----- (00404DF0) --------------------------------------------------------
int __cdecl strtol(const char *s, char **endptr, int base)
{
	int result; // $v0

	return result;
}
// 404DF0: variable 'result' is possibly undefined

//----- (00404E14) --------------------------------------------------------
int __cdecl devctl(const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen)
{
	int result; // $v0

	return result;
}
// 404E14: variable 'result' is possibly undefined

//----- (00404E38) --------------------------------------------------------
int __cdecl sceCdInit(int mode)
{
	int result; // $v0

	return result;
}
// 404E38: variable 'result' is possibly undefined

//----- (00404E40) --------------------------------------------------------
int sceCdStandby(void)
{
	int result; // $v0

	return result;
}
// 404E40: variable 'result' is possibly undefined

//----- (00404E48) --------------------------------------------------------
int __cdecl sceCdSeek(u32 lbn)
{
	int result; // $v0

	return result;
}
// 404E48: variable 'result' is possibly undefined

//----- (00404E50) --------------------------------------------------------
int sceCdGetError(void)
{
	int result; // $v0

	return result;
}
// 404E50: variable 'result' is possibly undefined

//----- (00404E58) --------------------------------------------------------
int __cdecl sceCdGetToc(u8 *toc)
{
	int result; // $v0

	return result;
}
// 404E58: variable 'result' is possibly undefined

//----- (00404E60) --------------------------------------------------------
int __cdecl sceCdSearchFile(sceCdlFILE *file, const char *name)
{
	int result; // $v0

	return result;
}
// 404E60: variable 'result' is possibly undefined

//----- (00404E68) --------------------------------------------------------
int __cdecl sceCdSync(int mode)
{
	int result; // $v0

	return result;
}
// 404E68: variable 'result' is possibly undefined

//----- (00404E70) --------------------------------------------------------
int sceCdGetDiskType(void)
{
	int result; // $v0

	return result;
}
// 404E70: variable 'result' is possibly undefined

//----- (00404E78) --------------------------------------------------------
int __cdecl sceCdTrayReq(int param, u32 *traychk)
{
	int result; // $v0

	return result;
}
// 404E78: variable 'result' is possibly undefined

//----- (00404E80) --------------------------------------------------------
int sceCdStop(void)
{
	int result; // $v0

	return result;
}
// 404E80: variable 'result' is possibly undefined

//----- (00404E88) --------------------------------------------------------
u32 __cdecl sceCdPosToInt(sceCdlLOCCD *p)
{
	u32 result; // $v0

	return result;
}
// 404E88: variable 'result' is possibly undefined

//----- (00404E90) --------------------------------------------------------
int __cdecl sceCdRI(u8 *buffer, u32 *result)
{
	int v2; // $v0

	return v2;
}
// 404E90: variable 'v2' is possibly undefined

//----- (00404E98) --------------------------------------------------------
int __cdecl sceCdReadClock(sceCdCLOCK *clock)
{
	int result; // $v0

	return result;
}
// 404E98: variable 'result' is possibly undefined

//----- (00404EA0) --------------------------------------------------------
int sceCdStatus(void)
{
	int result; // $v0

	return result;
}
// 404EA0: variable 'result' is possibly undefined

//----- (00404EA8) --------------------------------------------------------
int __cdecl sceCdApplySCmd(u8 cmdNum, const void *inBuff, u16 inBuffSize, void *outBuff, u16 outBuffSize)
{
	int result; // $v0

	return result;
}
// 404EA8: variable 'result' is possibly undefined

//----- (00404EB0) --------------------------------------------------------
int sceCdPause(void)
{
	int result; // $v0

	return result;
}
// 404EB0: variable 'result' is possibly undefined

//----- (00404EB8) --------------------------------------------------------
int sceCdBreak(void)
{
	int result; // $v0

	return result;
}
// 404EB8: variable 'result' is possibly undefined

//----- (00404EC0) --------------------------------------------------------
int __cdecl sceCdReadCDDA(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode)
{
	int result; // $v0

	return result;
}
// 404EC0: variable 'result' is possibly undefined

//----- (00404EC8) --------------------------------------------------------
u32 sceCdGetReadPos(void)
{
	u32 result; // $v0

	return result;
}
// 404EC8: variable 'result' is possibly undefined

//----- (00404ED0) --------------------------------------------------------
int __cdecl sceCdCtrlADout(int arg1, u32 *status)
{
	int result; // $v0

	return result;
}
// 404ED0: variable 'result' is possibly undefined

//----- (00404ED8) --------------------------------------------------------
void *sceGetFsvRbuf(void)
{
	void *result; // $v0

	return result;
}
// 404ED8: variable 'result' is possibly undefined

//----- (00404EE0) --------------------------------------------------------
int __cdecl sceCdSC(int code, int *param)
{
	int result; // $v0

	return result;
}
// 404EE0: variable 'result' is possibly undefined

//----- (00404EE8) --------------------------------------------------------
int __cdecl sceCdApplyNCmd(u8 cmdNum, const void *inBuff, u16 inBuffSize)
{
	int result; // $v0

	return result;
}
// 404EE8: variable 'result' is possibly undefined

//----- (00404EF0) --------------------------------------------------------
int __cdecl sceCdRead0(u32 lsn, u32 sectors, void *buffer, sceCdRMode *mode, int csec, void *callback)
{
	int result; // $v0

	return result;
}
// 404EF0: variable 'result' is possibly undefined

//----- (00404EF8) --------------------------------------------------------
int __cdecl sceCdRV(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int arg5, void *cb)
{
	int result; // $v0

	return result;
}
// 404EF8: variable 'result' is possibly undefined

//----- (00404F00) --------------------------------------------------------
int __cdecl sceCdRM(char *buffer, u32 *status)
{
	int result; // $v0

	return result;
}
// 404F00: variable 'result' is possibly undefined

//----- (00404F08) --------------------------------------------------------
int __cdecl sceCdPowerOff(u32 *result)
{
	int v1; // $v0

	return v1;
}
// 404F08: variable 'v1' is possibly undefined

//----- (00404F10) --------------------------------------------------------
int __cdecl sceCdMmode(int media)
{
	int result; // $v0

	return result;
}
// 404F10: variable 'result' is possibly undefined

//----- (00404F18) --------------------------------------------------------
int __cdecl sceCdReadDiskID(unsigned int *id)
{
	int result; // $v0

	return result;
}
// 404F18: variable 'result' is possibly undefined

//----- (00404F20) --------------------------------------------------------
int __cdecl sceCdReadGUID(u64 *guid)
{
	int result; // $v0

	return result;
}
// 404F20: variable 'result' is possibly undefined

//----- (00404F28) --------------------------------------------------------
int __cdecl sceCdSetTimeout(int param, int timeout)
{
	int result; // $v0

	return result;
}
// 404F28: variable 'result' is possibly undefined

//----- (00404F30) --------------------------------------------------------
int __cdecl sceCdReadModelID(unsigned int *id)
{
	int result; // $v0

	return result;
}
// 404F30: variable 'result' is possibly undefined

//----- (00404F38) --------------------------------------------------------
int __cdecl sceCdReadDvdDualInfo(int *on_dual, unsigned int *layer1_start)
{
	int result; // $v0

	return result;
}
// 404F38: variable 'result' is possibly undefined

//----- (00404F40) --------------------------------------------------------
int __cdecl sceCdLayerSearchFile(sceCdlFILE *fp, const char *path, int layer)
{
	int result; // $v0

	return result;
}
// 404F40: variable 'result' is possibly undefined

//----- (00404F48) --------------------------------------------------------
int __cdecl sceCdRE(unsigned int lsn, unsigned int sectors, void *buf, sceCdRMode *mode)
{
	int result; // $v0

	return result;
}
// 404F48: variable 'result' is possibly undefined

//----- (00404F50) --------------------------------------------------------
int __cdecl sceCdDoesUniqueKeyExist(u32 *status)
{
	int result; // $v0

	return result;
}
// 404F50: variable 'result' is possibly undefined
#endif

// nfuncs=131 queued=131 decompiled=131 lumina nreq=0 worse=0 better=0
// ALL OK, 131 function(s) have been successfully decompiled
