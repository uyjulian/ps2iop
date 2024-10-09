
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
int __cdecl cdvdfsv_parseargs(int ac, char **av);
int __cdecl sceCdChangeThreadPriority(int priority);
CDVDInitResult *__fastcall cbrpc_rpc1_cdinit(int fno, void *buffer, int length);
int __fastcall cdvdfsv_rpc3h_16_break(void *inbuf, int buflen, void *outbuf);
CDVDSearchResult *__fastcall cbrpc_rpc4_fscall(int fno, void *buffer, int length);
int __fastcall alarm_cb(void *a1);
void __cdecl cdvdfsv_rpc5h_0D_iopmread(cdvdfsv_rpc5h_0D_packet *inbuf, int buflen, void *outbuf);
u8 __cdecl cdvdfsv_syncdec(int flag, int xorkey, int arg2, u8 data);
int __cdecl cdvdfsv_cb_read();
int __cdecl cdvdfsv_checksid(u32 lsn, u32 sectors, u32 ps2dvd, void *buf, int decflag, int decshift, u32 *syncdec_mask);
int __fastcall readproc2(u32 lsn, u32 nsec, sceCdRMode *mode, u32 sector_size_selection, int do_multi_retries, int enable_dec_shift, int dec_shift, char *ee_addr, int fssift, int secsize, int dmasize, SifDmaTransfer_t *post_dmat);
int __fastcall readproc1(unsigned int lsn, u32 nsec, void *retptr, sceCdRMode *rmode, int ps2dvd, int enable_retries, int dec_shift_enable, int dec_shift_value);
void __cdecl cdvdfsv_rpc5h_01_readee(cdvdfsv_rpc5h_01_packet *inbuf, int buflen, void *outbuf, u32 ps2dvd, int sync, int decflag);
int __fastcall cdvdfsv_chreadee(int secoffs, int seccount, char *ee_addr, sceCdRMode *in_rmode, u32 disktype_14, int sync);
int __fastcall cdvdfsv_rpc5h_0F_readchain(cdvdfsv_rpc5h_0F_packet *inbuf, int buflen, void *outbuf);
int __fastcall cdvdfsv_rpc5h_02_readcdda(cdvdfsv_rpc5h_02_packet *inbuf, int buflen, void *outbuf);
int *__fastcall cbrpc_rpc2_diskready(int fno, void *buffer, int length);
int __fastcall cdvdfsv_rpc5h_04_gettoc(void *inbuf, int buflen, cdvdfsv_rpc5h_04_outpacket *outbuf);
int __fastcall cdvdfsv_rpc3h_03_disktype(void *inbuf, int buflen, void *outbuf);
int __fastcall cdvdfsv_rpc3h_0C_cdstatus(void *inbuf, int buflen, void *outbuf);
void __cdecl cdvdfsv_rpc3h_06_ri(void *inbuf, int buflen, cdvdfsv_rpc3h_06_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_1A_rm(void *inbuf, int buflen, cdvdfsv_rpc3h_1A_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_24_readguid(void *inbuf, int buflen, cdvdfsv_rpc3h_24_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_26_readmodelid(void *inbuf, int buflen, cdvdfsv_rpc3h_26_outpacket *outbuf);
int __fastcall cdvdfsv_rpc3h_22_mmode(cdvdfsv_rpc3h_22_packet *inbuf, int buflen, void *outbuf);
int __fastcall cdvdfsv_rpc3h_23_changethreadpriority(void *inbuf, int buflen, void *outbuf);
void __cdecl cdvdfsv_rpc3h_21_poweroff(void *inbuf, int buflen, cdvdfsv_rpc3h_21_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_15_ctrladout(void *inbuf, int buflen, cdvdfsv_rpc3h_15_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_01_readclock(void *inbuf, int buflen, cdvdfsv_rpc3h_01_outpacke *outbuf);
int __fastcall cdvdfsv_rpc5h_11_readdiskid(void *inbuf, int buflen, cdvdfsv_rpc5h_11_outpacket *outbuf);
int __fastcall cdvdfsv_rpc5h_17_doesuniquekeyexist(void *inbuf, int buflen, cdvdfsv_rpc5h_17_outpacket *outbuf);
int __fastcall cdvdfsv_rpc3h_0B_applyscmd(cdvdfsv_rpc3h_0B_packet *inbuf, int buflen, cdvdfsv_rpc3h_0B_outpacket *outbuf);
int __fastcall cdvdfsv_rpc5h_0C_applyncmd(cdvdfsv_rpc5h_0C_packet *inbuf, int buflen, void *outbuf);
int __fastcall cdvdfsv_rpc3h_04_geterror(void *inbuf, int buflen, void *outbuf);
void __cdecl cdvdfsv_rpc3h_05_trayreq(void *inbuf, int buflen, cdvdfsv_rpc3h_05_outpacket *outbuf);
int __fastcall cdvdfsv_rpc3h_25_settimeout(cdvdfsv_rpc3h_25_packet *inbuf, int buflen, void *outbuf);
int __fastcall cdvdfsv_rpc3h_27_readdvddualinfo(void *inbuf, int buflen, cdvdfsv_rpc3h_27_outpacket *outbuf);
int __cdecl cdvdfsv_rpc5h_0E_diskready();
CDVDReadResult *__fastcall cbrpc_rpc5_cdvdncmds(int fno, void *buffer, int length);
CDVDCmdResult *__fastcall cbrpc_rpc3_cdvdscmds(int fno, void *buffer, int length);
int __cdecl cdvdfsv_poffloop();
void __cdecl cdvdfsv_rpc1_th(void *arg);
void __cdecl cdvdfsv_rpc3_th(void *arg);
void __cdecl cdvdfsv_rpc2_th(void *arg);
int __fastcall cdvdfsv_unused_xorfun(unsigned int *, int);
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
int cdvdfsv_verbose = 0;
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
SifDmaTransfer_t cdvdfsv_multi_dmat[17];
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
	int i; // $s1
	int *tid_cur; // $s0
	int tid_val; // $a0
	int result; // $v0

	sceSifRemoveRpc(&rpc_sdata1, &rpc_qdata1);
	sceSifRemoveRpc(&rpc_sdata2, &rpc_qdata1);
	sceSifRemoveRpc(&rpc_sdata3, &rpc_qdata1);
	sceSifRemoveRpc(&rpc_sdata6, &rpc_qdata3);
	sceSifRemoveRpc(&rpc_sdata4, &rpc_qdata2);
	sceSifRemoveRpc(&rpc_sdata5, &rpc_qdata2);
	sceSifRemoveRpcQueue(&rpc_qdata1);
	sceSifRemoveRpcQueue(&rpc_qdata2);
	sceSifRemoveRpcQueue(&rpc_qdata3);
	i = 0;
	tid_cur = cdvdfsv_thids;
	cdvdfsv_nopocm = 1;
	cdvdfsv_plbreak = 1;
	do
	{
		++i;
		TerminateThread(*tid_cur);
		tid_val = *tid_cur++;
		DeleteThread(tid_val);
		result = 1;
	}
	while ( i < 4 );
	return result;
}

//----- (00400158) --------------------------------------------------------
int __fastcall _start(int ac, char **av)
{
	bool condtmp1; // dc
	int result; // $v0
	u32 condtmp2; // $s0
	unsigned __int16 *LibraryEntryTable; // $v0
	int error_code; // $s0
	int state[2]; // [sp+10h] [-8h] BYREF

	if ( ac < 0 )
	{
		result = 2;
		if ( !cdvdfsv_rpc5flg )
		{
			result = 2;
			if ( !cdvdfsv_rpc3flg )
			{
				condtmp1 = cdvdfsv_cleanuprpc() == 0;
				result = 2;
				if ( !condtmp1 )
				{
					CpuSuspendIntr(state);
					error_code = ReleaseLibraryEntries(&_exp_cdvdfsv);
					CpuResumeIntr(state[0]);
					if ( error_code && error_code != -213 )
					{
						Kprintf("ReleaseLibraryEntries Error code %d\n", error_code);
						return 2;
					}
					else
					{
						return 1;
					}
				}
			}
		}
	}
	else
	{
		condtmp1 = RegisterLibraryEntries(&_exp_cdvdfsv) != 0;
		result = 1;
		if ( !condtmp1 )
		{
			cdvdfsv_fsvrbuf = sceGetFsvRbuf();
			dword_40575C = (int)dword_405750;
			cdvdfsv_rtocbuf = (u8 *)cdvdfsv_fsvrbuf;
			cdvdfsv_parseargs(ac, av);
			condtmp2 = 0;
			cdvdfsv_init();
			CpuSuspendIntr(state);
			LibraryEntryTable = (unsigned __int16 *)QueryLibraryEntryTable(&modload_libinfo);
			if ( LibraryEntryTable )
				condtmp2 = *(LibraryEntryTable - 6) >= 0x104u;
			CpuResumeIntr(state[0]);
			result = 2;
			if ( !condtmp2 )
			{
				Kprintf("Warning cdvdfsv.irx: Unload function can't be used.\n");
				return 0;
			}
		}
	}
	return result;
}
// 405720: using guessed type int cdvdfsv_rpc3flg;
// 405750: using guessed type int dword_405750[2];
// 40575C: using guessed type int dword_40575C;

//----- (004002C0) --------------------------------------------------------
int __cdecl cdvdfsv_init()
{
	int *BootMode; // $v0
	iop_thread_t thparam; // [sp+10h] [-20h] BYREF
	int scres; // [sp+28h] [-8h] BYREF

	BootMode = QueryBootMode(3);
	if ( BootMode && (BootMode[1] & 2) != 0 )
	{
		printf(" No cdvd driver \n");
		return 1;
	}
	else
	{
		sceCdSC(0xFFFFFFF2, (int *)&cdvdfsv_cdvdman_internal_struct_ptr);
		cdvdman_scmd_ef = sceCdSC(0xFFFFFFE7, &scres);
		thparam.attr = 0x2000000;
		thparam.thread = cdvdfsv_main_th;
		thparam.stacksize = 2048;
		thparam.option = 0;
		thparam.priority = cdvdfsv_def_pri - 1;
		cdvdfsv_thids[0] = CreateThread(&thparam);
		if ( cdvdfsv_thids[0] > 0 )
		{
			StartThread(cdvdfsv_thids[0], 0);
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

//----- (00400394) --------------------------------------------------------
void __cdecl cdvdfsv_main_th(void *arg)
{
	int thid1; // $s0
	int thid2; // $s0
	int thid3; // $s0
	iop_thread_t thparam1; // [sp+10h] [-30h] BYREF
	iop_thread_t thparam2; // [sp+28h] [-18h] BYREF

	if ( !sceSifCheckInit() )
		sceSifInit();
	sceSifInitRpc(0);
	printf("cdvd driver module version 0.1.1 (C)SCEI\n");
	thparam2.thread = cdvdfsv_rpc1_th;
	thparam2.attr = 0x2000000;
	thparam2.stacksize = 6400;
	thparam2.option = 0;
	thparam2.priority = cdvdfsv_def_pri;
	thid1 = CreateThread(&thparam2);
	StartThread(thid1, 0);
	cdvdfsv_thids[1] = thid1;
	thparam1.attr = 0x2000000;
	thparam1.thread = cdvdfsv_rpc2_th;
	thparam1.stacksize = 6400;
	thparam1.option = 0;
	thparam1.priority = cdvdfsv_def_pri;
	thid2 = CreateThread(&thparam1);
	StartThread(thid2, 0);
	cdvdfsv_thids[2] = thid2;
	thparam1.thread = cdvdfsv_rpc3_th;
	thparam1.attr = 0x2000000;
	thparam1.stacksize = 2048;
	thparam1.option = 0;
	thparam1.priority = cdvdfsv_def_pri;
	thid3 = CreateThread(&thparam1);
	StartThread(thid3, 0);
	cdvdfsv_thids[3] = thid3;
	cdvdfsv_poffloop();
	ExitDeleteThread();
}

//----- (004004D4) --------------------------------------------------------
int *__fastcall cdvdfsv_4(int arg1)
{
	int *result; // $v0

	if ( cdvdfsv_verbose > 0 )
		printf("Dummy Entry Called\n");
	result = &cdvdfsv_verbose;
	if ( arg1 != 128 )
		return 0;
	return result;
}

//----- (00400528) --------------------------------------------------------
int __cdecl cdvdfsv_parseargs(int ac, char **av)
{
	int curargind; // $s1
	int result; // $v0
	const char **curargptr; // $s0
	int thpri; // $a1

	curargind = 1;
	cdvdfsv_def_pri = 81;
	result = ac > 1;
	if ( ac > 1 )
	{
		curargptr = (const char **)(av + 1);
		do
		{
			if ( !strncmp(*curargptr, "thpri=", 6) )
			{
				thpri = strtol(*curargptr + 6, 0, 10);
				if ( (unsigned int)(thpri - 9) >= 0x73 )
				{
					printf("Cdvdfsv:thpri=%d Illegal priority\n", thpri);
					thpri = 81;
				}
				if ( thpri == 9 )
					thpri = 10;
				cdvdfsv_def_pri = thpri;
			}
			result = ++curargind < ac;
			++curargptr;
		}
		while ( curargind < ac );
	}
	return result;
}

//----- (004005F8) --------------------------------------------------------
int __cdecl sceCdChangeThreadPriority(int priority)
{
	int priority_tmp; // $s1
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	priority_tmp = priority;
	if ( (unsigned int)(priority - 9) >= 0x73 )
		return -403;
	if ( priority == 9 )
		priority_tmp = 10;
	ReferThreadStatus(0, &thinfo);
	ChangeThreadPriority(0, 8);
	ChangeThreadPriority(cdvdfsv_thids[0], priority_tmp - 1);
	ChangeThreadPriority(cdvdfsv_thids[2], priority_tmp);
	ChangeThreadPriority(cdvdfsv_thids[1], priority_tmp);
	ChangeThreadPriority(cdvdfsv_thids[3], priority_tmp);
	return 0;
}
// 4005F8: using guessed type iop_thread_info_t thinfo;

//----- (00400694) --------------------------------------------------------
CDVDInitResult *__fastcall cbrpc_rpc1_cdinit(int fno, void *buffer, int length)
{
	int scres; // [sp+10h] [-8h] BYREF

	if ( cdvdfsv_verbose > 0 )
		printf("sceCdInit call\n");
	sceCdInit(*(_DWORD *)buffer);
	cdvdfsv_spinctl = -1;
	if ( cdvdfsv_verbose )
		cdvdfsv_initres.debug_mode = 254;
	else
		cdvdfsv_initres.debug_mode = 0;
	cdvdfsv_initres.cdvdfsv_ver = (unsigned __int16)_irx_id.v;
	cdvdfsv_initres.cdvdman_ver = sceCdSC(0xFFFFFFF7, &scres);
	if ( cdvdfsv_verbose > 0 )
		printf("sceCdInit end\n");
	cdvdfsv_initres.result = 1;
	return &cdvdfsv_initres;
}
// 405940: using guessed type CDVDInitResult cdvdfsv_initres;

//----- (00400760) --------------------------------------------------------
int __fastcall cdvdfsv_rpc3h_16_break(void *inbuf, int buflen, void *outbuf)
{
	int result; // $v0

	if ( cdvdfsv_verbose > 0 )
		printf("sceCdAbort call\n");
	sceCdBreak();
	result = 1;
	*(_DWORD *)outbuf = 1;
	return result;
}

//----- (004007AC) --------------------------------------------------------
CDVDSearchResult *__fastcall cbrpc_rpc4_fscall(int fno, void *buffer, int length)
{
	int searchfile_res; // $s1
	void *bufdest_ptr; // $a0
	int bufsz; // $v1
	int trid; // $s0
	CDVDSearchResult *result; // $v0
	int scres; // [sp+10h] [-8h] BYREF
	int state; // [sp+14h] [-4h] BYREF

	scres = 255;
	sceCdSC(0xFFFFFFF6, &scres);
	if ( cdvdfsv_verbose > 0 )
		printf("search file name %s call struct_siz %d\n", (const char *)buffer + 36, length);
	if ( length == 300 )
	{
		searchfile_res = sceCdLayerSearchFile((sceCdlFILE *)buffer, (const char *)buffer + 36, *((_DWORD *)buffer + 74));
		cdvdfsv_fssdd.src = buffer;
		bufdest_ptr = (void *)*((_DWORD *)buffer + 73);
		bufsz = 36;
	}
	else if ( length == 296 )
	{
		printf("sceCdSearchFile: Called from Not_Dual_layer Version.\n");
		searchfile_res = sceCdSearchFile((sceCdlFILE *)buffer, (const char *)buffer + 36);
		cdvdfsv_fssdd.src = buffer;
		bufdest_ptr = (void *)*((_DWORD *)buffer + 73);
		bufsz = 36;
	}
	else
	{
		printf("Warning sceCdSearchFile: Called from Old liblary.\n");
		searchfile_res = sceCdSearchFile((sceCdlFILE *)buffer, (const char *)buffer + 32);
		cdvdfsv_fssdd.src = buffer;
		bufdest_ptr = (void *)*((_DWORD *)buffer + 72);
		bufsz = 32;
	}
	cdvdfsv_fssdd.size = bufsz;
	cdvdfsv_fssdd.dest = bufdest_ptr;
	cdvdfsv_fssdd.attr = 0;
	while ( 1 )
	{
		CpuSuspendIntr(&state);
		trid = sceSifSetDma(&cdvdfsv_fssdd, 1);
		CpuResumeIntr(state);
		if ( trid )
			break;
		DelayThread(500);
	}
	scres = 0;
	sceCdSC(0xFFFFFFF6, &scres);
	result = &cdvdfsv_srchres;
	cdvdfsv_srchres.result = searchfile_res;
	return result;
}

//----- (00400920) --------------------------------------------------------
int __fastcall alarm_cb(void *a1)
{
	unsigned int time_out_msec; // [sp+10h] [-8h] BYREF

	time_out_msec = *(_DWORD *)a1 / 0x9000u;
	Kprintf("Read Time Out %d(msec)\n", time_out_msec);
	sceCdSC(0xFFFFFFEE, (int *)&time_out_msec);
	return sceCdBreak() == 0;
}

//----- (00400974) --------------------------------------------------------
void __cdecl cdvdfsv_rpc5h_0D_iopmread(cdvdfsv_rpc5h_0D_packet *inbuf, int buflen, void *outbuf)
{
	void *readpos_dest_addr; // $a0
	int cmd_error; // $s1
	int trid; // $s0
	int error_code; // [sp+10h] [-8h] BYREF
	int state; // [sp+14h] [-4h] BYREF

	cdvdfsv_rderror = 254;
	cdvdfsv_read_to.hi = 0;
	cdvdfsv_read_to.lo = 36864 * sceCdSC(0xFFFFFFF1, &error_code);
	cdvdfsv_iomrsdd.src = &cdvdfsv_readpos;
	readpos_dest_addr = (void *)inbuf->readpos_dest_addr;
	cdvdfsv_iomrsdd.size = 4;
	cdvdfsv_iomrsdd.attr = 0;
	cdvdfsv_iomrsdd.dest = readpos_dest_addr;
	if ( cdvdfsv_verbose > 0 )
		printf("sceCdReadIOPm addr= 0x%08x sector= %d\n", inbuf->buf, inbuf->sectors);
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
		if ( cdvdfsv_verbose > 0 )
			printf("Read error code %x cmd error %d\n", error_code, cmd_error);
	}
}

//----- (00400B0C) --------------------------------------------------------
u8 __cdecl cdvdfsv_syncdec(int flag, int xorkey, int arg2, u8 data)
{
	if ( flag )
		return ((data << (arg2 % 8)) | (data >> (8 - arg2 % 8))) ^ xorkey;
	else
		return data;
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
	int layer; // $fp
	int scret; // $s1
	u32 i; // $s5
	unsigned int lsn_tmp; // $s4
	u8 *error_lsn; // $s2
	u8 *buf_tmp; // $s3
	u32 readlsn; // $s0
	int syncdec_1; // $s0
	int syncdec_2; // $s0
	int syncdec_3; // $s0
	u8 syncdec_4; // $v0
	int result; // $v0
	sceCdlLOCCD rpos; // [sp+18h] [-10h] BYREF
	int scres; // [sp+20h] [-8h] BYREF
	int ipi_emu; // [sp+24h] [-4h]

	layer = 0;
	ipi_emu = 0;
	*syncdec_mask = 0;
	if ( decflag )
		scret = sceCdSC(0xFFFFFFE8, &scres);
	else
		scret = 0;
	i = 0;
	if ( sectors )
	{
		lsn_tmp = lsn;
		error_lsn = (u8 *)buf;
		buf_tmp = (u8 *)buf;
		while ( 1 )
		{
			if ( ps2dvd )
			{
				syncdec_1 = cdvdfsv_syncdec(decflag, scret, decshift, error_lsn[3]);
				syncdec_2 = syncdec_1 + (cdvdfsv_syncdec(decflag, scret, decshift, error_lsn[2]) << 8);
				syncdec_3 = syncdec_2 + (cdvdfsv_syncdec(decflag, scret, decshift, error_lsn[1]) << 16);
				syncdec_4 = cdvdfsv_syncdec(decflag, scret, decshift, *error_lsn);
				layer = syncdec_4 & 1;
				if ( i )
				{
					if ( !*syncdec_mask )
						ipi_emu = syncdec_4 & 0xC;
				}
				else
				{
					*syncdec_mask = syncdec_4 & 0xC;
				}
				readlsn = syncdec_3 - 0x30000;
				if ( cdvdfsv_cdvdman_internal_struct_ptr->opo_or_para
					&& lsn_tmp >= cdvdfsv_cdvdman_internal_struct_ptr->layer_1_lsn
					&& cdvdfsv_cdvdman_internal_struct_ptr->opo_or_para == 1 )
				{
					readlsn += cdvdfsv_cdvdman_internal_struct_ptr->layer_1_lsn;
				}
			}
			else
			{
				rpos.minute = cdvdfsv_syncdec(decflag, scret, decshift, *buf_tmp);
				rpos.second = cdvdfsv_syncdec(decflag, scret, decshift, buf_tmp[1]);
				rpos.sector = cdvdfsv_syncdec(decflag, scret, decshift, buf_tmp[2]);
				readlsn = sceCdPosToInt(&rpos);
			}
			if ( readlsn != lsn_tmp )
				break;
			error_lsn += 2064;
			if ( ipi_emu )
				break;
			++lsn_tmp;
			++i;
			buf_tmp += 2340;
			if ( i >= sectors )
				goto LABEL_22;
		}
		if ( cdvdfsv_verbose > 0 )
			printf(
				"Read_EE Sector_ID error lsn= %d readlsn= %d layer= %d layer1_start %d\n",
				lsn_tmp,
				readlsn,
				layer,
				cdvdfsv_cdvdman_internal_struct_ptr->layer_1_lsn);
		return 0;
	}
	else
	{
LABEL_22:
		result = 1;
		if ( *syncdec_mask )
		{
			result = 1;
			if ( cdvdfsv_verbose > 0 )
			{
				printf("Read_EE NO_Data_zone error lsn= %d layer= %d SecID %02x\n", lsn, layer, *syncdec_mask);
				return 1;
			}
		}
	}
	return result;
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
	u8 *rtocbuf_plus_4680; // $s7
	int i1_1; // $s6
	int i1; // $v0
	int csec; // $s5
	cdvdman_internal_struct_t *si1; // $v1
	u32 lsnmul; // $a0
	int read_res1; // $v0
	int read_res1_tmp; // $s0
	int read_res2; // $v0
	int read_res2_tmp; // $s0
	int i2; // $s6
	int nsec_div_cdvdfsv_sectors_1; // $t0
	BOOL condtmp1; // $fp
	int csec_minus_one; // $s0
	_DWORD *rtocbuf_dest_1; // $a0
	int size_1; // $a2
	u8 *rtocbuf_src_1; // $a1
	int trid; // $s0
	int i3; // $s4
	char *ee_addr_offs; // $a0
	int bytes_size; // $lo
	int i3_1; // $v1
	int size_2; // $s4
	_DWORD *rtocbuf_dest_3; // $s2
	u8 *rtocbuf_src_3; // $s0
	int i5; // $s1
	int csec_bytes; // $lo
	_DWORD *rtocbuf_src_2; // $s0
	_DWORD *rtocbuf_src_tmp_2; // $s2
	int i4; // $s1
	_DWORD *rtocbuf_dest_2; // $a0
	unsigned int csec_comm_tmp; // $t0
	cdvdman_internal_struct_t *si3; // $v0
	int Error; // $v0
	int dec_mode_last_set; // $v1
	int result; // $v0
	cdvdman_internal_struct_t *si2; // $v0
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
	_DWORD *rtocbuf_plus_2340; // [sp+54h] [-Ch]
	_DWORD *rtocbuf_tmp; // [sp+58h] [-8h]
	int *p_sector_size; // [sp+5Ch] [-4h]

	sc_fffffffe_res = 0;
	sector_sizes[0] = 2340;
	sector_sizes[1] = 2064;
	cdvdfsv_read_to.hi = 0;
	cdvdfsv_read_to.lo = 36864 * sceCdSC(0xFFFFFFF1, &sc_fffffff1_res);
	rtocbuf_plus_4680 = cdvdfsv_rtocbuf + 4680;
	rtocbuf_tmp = (unsigned int *)cdvdfsv_rtocbuf;
	cdvdfsv_rderror = 253;
	cdvdfsv_r2retry = 0;
	cdvdfsv_r2count = 0;
	rtocbuf_plus_2340 = (unsigned int *)(cdvdfsv_rtocbuf + 2340);
	if ( secsize != 2340 && !fssift )
	{
		i1_1 = 0;
		i1 = 0;
		do
		{
			++i1_1;
			cdvdfsv_multi_dmat[i1].attr = 0;
			cdvdfsv_multi_dmat[i1].size = secsize;
			i1 = i1_1;
		}
		while ( i1_1 < 16 );
	}
	p_sector_size = &sector_sizes[sector_size_selection];
	while ( 1 )
	{
		while ( 1 )
		{
			csec = 16;
			if ( nsec < 0x11 )
				csec = nsec;
			nsec_div_cdvdfsv_sectors = nsec >> 4;
			if ( (nsec & 0xF) != 0 )
				nsec_div_cdvdfsv_sectors = (nsec >> 4) + 1;
			retry_flag2 = 0;
			ee_addr_tmp = ee_addr;
			dmasize_tmp = dmasize;
			cdvdfsv_cdvdman_internal_struct_ptr->dec_mode_set = 1;
			cdvdfsv_cdvdman_internal_struct_ptr->dec_mode_last_set = 0;
			CpuSuspendIntr(&state);
			if ( enable_dec_shift )
			{
				si1 = cdvdfsv_cdvdman_internal_struct_ptr;
				cdvdfsv_cdvdman_internal_struct_ptr->dec_shift = dec_shift;
				si1->dec_state = 2;
			}
			if ( !cdvdfsv_r2retry )
				break;
			if ( cdvdfsv_verbose > 0 )
				Kprintf("Rty_Read\n");
			if ( lsn >= 0x60 )
				lsnmul = lsn - 16 * cdvdfsv_r2retry;
			else
				lsnmul = lsn + 16 * cdvdfsv_r2retry + 96;
			if ( sector_size_selection )
				read_res1 = sceCdRV(lsnmul, 0x10u, rtocbuf_plus_4680, mode, 0, 0);
			else
				read_res1 = sceCdRead0(lsnmul, 0x10u, rtocbuf_plus_4680, mode, 0, 0);
			read_res1_tmp = read_res1;
			CpuResumeIntr(state);
			if ( !read_res1_tmp )
			{
LABEL_104:
				si2 = cdvdfsv_cdvdman_internal_struct_ptr;
				cdvdfsv_cdvdman_internal_struct_ptr->dec_state = 0;
				si2->dec_mode_set = 0;
LABEL_105:
				sceCdSC(-2, &cdvdfsv_rderror);
				return 0;
			}
			sceCdSync(3);
			--cdvdfsv_r2retry;
		}
		if ( sector_size_selection )
			read_res2 = sceCdRV(lsn, nsec, rtocbuf_plus_4680, mode, csec, cdvdfsv_cb_read);
		else
			read_res2 = sceCdRead0(lsn, nsec, rtocbuf_plus_4680, mode, csec, cdvdfsv_cb_read);
		read_res2_tmp = read_res2;
		CpuResumeIntr(state);
		if ( !read_res2_tmp )
			goto LABEL_104;
		SetAlarm(&cdvdfsv_read_to, (unsigned int (__cdecl *)(void *))alarm_cb, &cdvdfsv_read_to);
		i2 = 0;
		csec_comm = 0;
		retry_flag1 = 0;
		if ( nsec_div_cdvdfsv_sectors )
		{
			nsec_div_cdvdfsv_sectors_1 = nsec_div_cdvdfsv_sectors;
			while ( 1 )
			{
				condtmp1 = i2 == nsec_div_cdvdfsv_sectors_1 - 1;
				sceCdSync(32);
				if ( cdvdfsv_cdvdman_internal_struct_ptr->dec_mode_last_set )
					goto LABEL_89;
				if ( !sceCdGetError() )
					break;
				retry_flag1 = 1;
LABEL_82:
				CpuSuspendIntr(&state);
				if ( condtmp1 )
				{
					DisableIntr(35, (int *)&chcr);
				}
				else
				{
					csec_comm_tmp = csec_comm + csec;
					csec = 16;
					csec_comm = csec_comm_tmp;
					if ( nsec < csec_comm_tmp + 16 )
						csec = nsec - csec_comm_tmp;
					ClearEventFlag(cdvdfsv_ef, 0xFFFFFFDF);
					dmac_ch_set_chcr(3u, 0);
					chcr = dmac_ch_get_chcr(3u);
					cdvdfsv_cdvdman_internal_struct_ptr->dma3prm.dma3_maddress = rtocbuf_plus_4680;
					dmac_ch_set_madr(3u, (u32)rtocbuf_plus_4680);
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
				++i2;
				CpuResumeIntr(state);
				nsec_div_cdvdfsv_sectors_1 = nsec_div_cdvdfsv_sectors;
				if ( i2 >= nsec_div_cdvdfsv_sectors )
					goto LABEL_89;
			}
			if ( cdvdfsv_checksid(
						 lsn + csec_comm,
						 csec,
						 sector_size_selection,
						 rtocbuf_plus_4680,
						 enable_dec_shift,
						 dec_shift,
						 &syncdec_mask) )
			{
				if ( do_multi_retries && syncdec_mask && !i2 )
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
				goto LABEL_82;
			if ( secsize == 2340 && !sector_size_selection )
			{
				if ( fssift )
				{
					csec_minus_one = csec - 1;
					if ( i2 )
					{
						cdvdfsv_memcpy(rtocbuf_plus_2340, (_DWORD *)((char *)rtocbuf_tmp + fssift), 2340 - fssift);
						cdvdfsv_memcpy(rtocbuf_tmp, (_DWORD *)&rtocbuf_plus_4680[2340 * csec - 2340], 0x924u);
						if ( condtmp1 )
							cdvdfsv_rdp2sdd.size = dmasize_tmp;
						else
							cdvdfsv_rdp2sdd.size = 2340 * (csec - 1) + fssift;
						rtocbuf_src_1 = rtocbuf_plus_4680;
						size_1 = cdvdfsv_rdp2sdd.size;
						rtocbuf_dest_1 = (_DWORD *)((char *)rtocbuf_plus_2340 + 2340 - fssift);
					}
					else
					{
						cdvdfsv_memcpy(rtocbuf_tmp, (_DWORD *)&rtocbuf_plus_4680[2340 * csec_minus_one], 0x924u);
						if ( condtmp1 )
							cdvdfsv_rdp2sdd.size = dmasize_tmp;
						else
							cdvdfsv_rdp2sdd.size = 2340 * csec_minus_one;
						rtocbuf_dest_1 = rtocbuf_plus_2340;
						size_1 = cdvdfsv_rdp2sdd.size;
						rtocbuf_src_1 = &rtocbuf_plus_4680[fssift];
					}
					cdvdfsv_memcpy(rtocbuf_dest_1, (_DWORD *)rtocbuf_src_1, size_1);
					cdvdfsv_rdp2sdd.src = rtocbuf_plus_2340;
				}
				else
				{
					cdvdfsv_rdp2sdd.src = rtocbuf_plus_4680;
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
				goto LABEL_81;
			}
			if ( !fssift )
			{
				i3 = 0;
				if ( csec > 0 )
				{
					ee_addr_offs = &ee_addr[csec_comm * secsize];
					do
					{
						bytes_size = i3 * *p_sector_size;
						i3_1 = i3;
						cdvdfsv_multi_dmat[i3_1].dest = ee_addr_offs;
						++i3;
						cdvdfsv_multi_dmat[i3_1].src = &rtocbuf_plus_4680[bytes_size + 12];
						ee_addr_offs += secsize;
					}
					while ( i3 < csec );
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
				goto LABEL_81;
			}
			size_2 = secsize;
			if ( !condtmp1 )
				size_2 = fssift;
			if ( i2 )
			{
				cdvdfsv_memcpy(rtocbuf_plus_2340, (_DWORD *)((char *)rtocbuf_tmp + fssift + 12), secsize - fssift);
				rtocbuf_src_2 = (_DWORD *)(rtocbuf_plus_4680 + 12);
				rtocbuf_src_tmp_2 = (_DWORD *)((char *)rtocbuf_plus_2340 + secsize - fssift);
				i4 = 0;
				cdvdfsv_memcpy(rtocbuf_tmp, (_DWORD *)&rtocbuf_plus_4680[(csec - 1) * *p_sector_size], *p_sector_size);
				rtocbuf_dest_2 = rtocbuf_src_tmp_2;
				if ( csec - 1 > 0 )
				{
					do
					{
						cdvdfsv_memcpy(rtocbuf_src_tmp_2, rtocbuf_src_2, secsize);
						++i4;
						rtocbuf_src_2 = (_DWORD *)((char *)rtocbuf_src_2 + *p_sector_size);
						rtocbuf_src_tmp_2 = (_DWORD *)((char *)rtocbuf_src_tmp_2 + secsize);
					}
					while ( i4 < csec - 1 );
					rtocbuf_dest_2 = rtocbuf_src_tmp_2;
				}
				cdvdfsv_memcpy(rtocbuf_dest_2, rtocbuf_src_2, size_2);
				if ( !condtmp1 )
				{
					csec_bytes = secsize * csec;
					goto LABEL_76;
				}
			}
			else
			{
				cdvdfsv_memcpy(rtocbuf_tmp, (_DWORD *)&rtocbuf_plus_4680[(csec - 1) * *p_sector_size], *p_sector_size);
				cdvdfsv_memcpy(rtocbuf_plus_2340, (_DWORD *)&rtocbuf_plus_4680[fssift + 12], secsize - fssift);
				rtocbuf_dest_3 = (_DWORD *)((char *)rtocbuf_plus_2340 + secsize - fssift);
				rtocbuf_src_3 = &rtocbuf_plus_4680[*p_sector_size + 12];
				for ( i5 = 0; i5 < csec - 2; rtocbuf_dest_3 = (_DWORD *)((char *)rtocbuf_dest_3 + secsize) )
				{
					cdvdfsv_memcpy(rtocbuf_dest_3, (_DWORD *)rtocbuf_src_3, secsize);
					++i5;
					rtocbuf_src_3 += *p_sector_size;
				}
				cdvdfsv_memcpy(rtocbuf_dest_3, (_DWORD *)rtocbuf_src_3, size_2);
				if ( !condtmp1 )
				{
					csec_bytes = secsize * (csec - 1);
LABEL_76:
					cdvdfsv_rdp2sdd.size = csec_bytes;
					goto LABEL_78;
				}
			}
			cdvdfsv_rdp2sdd.size = dmasize_tmp;
LABEL_78:
			cdvdfsv_rdp2sdd.src = rtocbuf_plus_2340;
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
LABEL_81:
			while ( cdvdfsv_checkdmastat(trid) >= 0 )
				;
			goto LABEL_82;
		}
LABEL_89:
		sceCdSync(5);
		CancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &cdvdfsv_read_to);
		si3 = cdvdfsv_cdvdman_internal_struct_ptr;
		cdvdfsv_cdvdman_internal_struct_ptr->dec_mode_set = 0;
		si3->dec_state = 0;
		Error = sceCdGetError();
		dec_mode_last_set = (unsigned __int16)cdvdfsv_cdvdman_internal_struct_ptr->dec_mode_last_set;
		sc_fffffff1_res = Error;
		if ( dec_mode_last_set )
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
			result = 0;
			if ( cdvdfsv_verbose > 0 )
			{
				Kprintf("secid_chk_ee_trns lsn %d nsec %d IPI Err\n", lsn, nsec);
				return 0;
			}
			return result;
		}
		if ( !cdvdfsv_r2retry )
		{
			++cdvdfsv_r2count;
			if ( cdvdfsv_verbose > 0 )
				printf("Read_CD/DVD-ROM Error Recover Start\n");
			cdvdfsv_r2retry = 3;
		}
	}
	result = 0;
	if ( cdvdfsv_r2count >= 5 && !sc_fffffff1_res )
		goto LABEL_105;
	return result;
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
	cdvdman_internal_struct_t *s; // $v1
	u32 lsnmul; // $a0
	int read_res; // $v0
	int cmd_error; // $s0
	int result; // $v0
	int sid_err_recover_cnt_tmp; // $v0
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
		CpuSuspendIntr(&state);
		if ( dec_shift_enable )
		{
			s = cdvdfsv_cdvdman_internal_struct_ptr;
			cdvdfsv_cdvdman_internal_struct_ptr->dec_shift = dec_shift_value;
			s->dec_state = 2;
		}
		if ( lsn >= 0x30 )
			lsnmul = lsn - 16 * cdvdfsv_sid_err_recover_cnt;
		else
			lsnmul = lsn + 16 * cdvdfsv_sid_err_recover_cnt;
		if ( ps2dvd )
			read_res = sceCdRV(lsnmul, nsec, retptr, rmode, 0, 0);
		else
			read_res = sceCdRead0(lsnmul, nsec, retptr, rmode, 0, 0);
		cmd_error = read_res;
		CpuResumeIntr(state);
		if ( cmd_error )
			SetAlarm(&cdvdfsv_read_to, (unsigned int (__cdecl *)(void *))alarm_cb, &cdvdfsv_read_to);
		sceCdSync(5);
		CancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &cdvdfsv_read_to);
		cdvdfsv_cdvdman_internal_struct_ptr->dec_state = 0;
		Error = sceCdGetError();
		if ( Error || !cmd_error || cdvdfsv_err_count >= 5 )
		{
			if ( cdvdfsv_verbose > 0 )
				Kprintf("Read error error code %x cmd error %d\n", Error, cmd_error);
			if ( !cmd_error || (result = 0, cdvdfsv_err_count >= 5) )
			{
				result = 0;
				if ( !Error )
				{
					sceCdSC(0xFFFFFFFE, &cdvdfsv_rderror);
					return 0;
				}
			}
			return result;
		}
		if ( cdvdfsv_checksid(lsn, nsec, ps2dvd, retptr, dec_shift_enable, dec_shift_value, &syncdec_mask) )
			break;
		if ( !enable_retries )
			goto LABEL_32;
		sid_err_recover_cnt_tmp = cdvdfsv_sid_err_recover_cnt - 1;
		if ( !cdvdfsv_sid_err_recover_cnt )
		{
			++cdvdfsv_err_count;
			if ( cdvdfsv_verbose > 0 )
				printf("Read_CD/DVD-ROM Sector_ID Error Recover Start\n");
			cdvdfsv_sid_err_recover_cnt = 3;
			sid_err_recover_cnt_tmp = cdvdfsv_sid_err_recover_cnt - 1;
			if ( !cdvdfsv_sid_err_recover_cnt )
				continue;
		}
		cdvdfsv_sid_err_recover_cnt = sid_err_recover_cnt_tmp;
	}
	if ( enable_retries && syncdec_mask )
		sc_fffffffe_tmp = 32;
LABEL_32:
	if ( !sc_fffffffe_tmp )
		return 1;
	sceCdSC(0xFFFFFFFE, &sc_fffffffe_tmp);
	if ( cdvdfsv_verbose > 0 )
		Kprintf("secid_chk lsn %d nsec %d IPI Err\n", lsn, nsec);
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
	unsigned int flag; // $s0
	int all_sec; // $s3
	int lsn; // $v0
	void *sec; // $a0
	unsigned int secsize; // $s1
	unsigned int bsize; // $s5
	unsigned int psize; // $s7
	unsigned int ssize; // $s6
	int sc_ffffffe9_res; // $v0
	int all_sec_bytes; // $lo
	int len2; // $v1
	int sec2; // $v0
	char *flag_offs; // $fp
	u32 sectors; // $s0
	int rtoc_ind; // $a1
	unsigned int j; // $a0
	unsigned int i; // $a0
	unsigned int offs_in_sector; // $s3
	u32 offs_sector_only; // $a0
	int offs_sector_mask; // $a1
	int sizestuff; // $s2
	u32 needed_offset; // $s0
	int dmasize; // $s4
	int bsize_in_sectors; // $a1
	u32 sectors_1; // $s0
	unsigned int buf_offs_sum_bytes_in_sector; // $s3
	unsigned int k; // $a0
	unsigned int i2; // $a0
	int i2_offs; // $a1
	unsigned __int8 *pbuf2; // $a2
	u8 *rtocbuf_after_logo; // $a1
	unsigned __int8 val_tmp1; // $v0
	void *lsn2; // $a1
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

	trid = 0;
	decval = 0;
	buf_offs_sum = 0;
	sector_sizes[0] = 2340;
	sector_sizes[1] = 2064;
	pkt_tmp = inbuf;
	flag = inbuf->flag;
	all_sec = inbuf->sec;
	lsn = inbuf->lsn;
	cdvdfsv_rmodeee = inbuf->rmodeee;
	sc_ffffffe9_tmp = lsn;
	if ( decflag )
		decval = pkt_tmp[1].flag;
	cdvdfsv_eerpsdd.src = &cdvdfsv_readpos;
	sec = (void *)pkt_tmp[1].sec;
	cdvdfsv_eerpsdd.size = 4;
	cdvdfsv_eerpsdd.attr = 0;
	cdvdfsv_eerpsdd.dest = sec;
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
			goto LABEL_83;
		}
		sc_ffffffe9_res = sceCdSC(0xFFFFFFE9, &sc_ffffffe9_tmp);
		secsize = 2048;
		datapattern = 0;
		pkt_tmp->lsn = sc_ffffffe9_res;
		sc_ffffffe9_tmp = sc_ffffffe9_res;
		cdvdfsv_rmodeee.datapattern = 0;
	}
	else
	{
		datapattern = cdvdfsv_rmodeee.datapattern;
		if ( cdvdfsv_rmodeee.datapattern == 1 )
		{
			secsize = 2328;
		}
		else
		{
			secsize = 2048;
			if ( cdvdfsv_rmodeee.datapattern >= 2u && datapattern == 2 )
				secsize = 2340;
		}
		cdvdfsv_rmodeee.datapattern = 2;
	}
	all_sec_bytes = secsize * all_sec;
	if ( cdvdfsv_spinctl != -1 )
		cdvdfsv_rmodeee.spindlctrl = cdvdfsv_spinctl;
	len2 = pkt_tmp->lsn;
	sec2 = pkt_tmp->sec;
	len2_plus_sec2 = len2 + sec2;
	if ( (flag & 0x3F) != 0 )
		psize = (flag & 0xFFFFFFC0) - (flag - 64);
	else
		psize = 0;
	paddr = flag;
	flag_offs = (char *)(flag + psize);
	bsize = ((flag + all_sec_bytes) & 0xFFFFFFC0) - (flag + psize);
	ssize = flag + all_sec_bytes - ((flag + all_sec_bytes) & 0xFFFFFFC0);
	saddr = (flag + all_sec_bytes) & 0xFFFFFFC0;
	if ( cdvdfsv_verbose > 0 )
	{
		Kprintf("CD/DVD-ROM lsn= %d sec= %d\n", sc_ffffffe9_tmp, all_sec);
		if ( cdvdfsv_verbose > 0 )
			Kprintf("f psize= %d bsize= %d ssize= %d\n", psize, bsize, ssize);
	}
	sectors = 2;
	if ( psize )
	{
		if ( len2_plus_sec2 < sc_ffffffe9_tmp + buf_offs_sum / secsize + 2 )
			sectors = 1;
		if ( cdvdfsv_verbose > 0 )
			printf("0 CD_READ LBN= %d sectors= %d all= %d\n", sc_ffffffe9_tmp + buf_offs_sum / secsize, sectors, all_sec);
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
LABEL_29:
			bsize = 0;
			goto LABEL_83;
		}
		rtoc_ind = 12;
		if ( datapattern != 2 || ps2dvd )
		{
			for ( i = 0; i < psize; ++i )
			{
				if ( i && !(i % secsize) )
					rtoc_ind += sector_sizes[ps2dvd] - secsize;
				cdvdfsv_eereadx.pbuf1[i] = cdvdfsv_rtocbuf[rtoc_ind++];
			}
		}
		else
		{
			for ( j = 0; j < psize; ++j )
				cdvdfsv_eereadx.pbuf1[j] = cdvdfsv_rtocbuf[j];
		}
		buf_offs_sum += psize;
	}
	while ( bsize )
	{
		if ( cdvdfsv_spinctl != -1 )
			cdvdfsv_rmodeee.spindlctrl = cdvdfsv_spinctl;
		offs_in_sector = buf_offs_sum % secsize;
		offs_sector_only = sc_ffffffe9_tmp + buf_offs_sum / secsize;
		offs_sector_mask = offs_sector_only & 0xF;
		if ( secsize << 6 >= bsize )
		{
			bsize_in_sectors = bsize / secsize;
			sizestuff = bsize;
			dmasize = bsize;
			if ( bsize % secsize )
				bsize_in_sectors = bsize / secsize + 1;
			needed_offset = bsize_in_sectors + (offs_in_sector != 0);
		}
		else
		{
			if ( (offs_sector_only & 0xF) != 0 )
			{
				sizestuff = secsize << 6;
				if ( (secsize & 0xF) == 0 )
				{
					needed_offset = 16 - offs_sector_mask;
					sizestuff = secsize * (16 - offs_sector_mask);
					dmasize = sizestuff;
					if ( offs_in_sector )
						++needed_offset;
					goto LABEL_55;
				}
			}
			else
			{
				sizestuff = secsize << 6;
			}
			dmasize = sizestuff;
			needed_offset = 64;
			if ( buf_offs_sum % secsize )
				needed_offset = 65;
		}
LABEL_55:
		if ( len2_plus_sec2 < offs_sector_only + needed_offset )
			needed_offset = len2_plus_sec2 - (sc_ffffffe9_tmp + buf_offs_sum / secsize);
		cdvdfsv_readpos = buf_offs_sum;
		if ( !readproc2(
						offs_sector_only,
						needed_offset,
						&cdvdfsv_rmodeee,
						ps2dvd,
						sync,
						decflag,
						decval,
						flag_offs,
						buf_offs_sum % secsize,
						secsize,
						dmasize,
						&cdvdfsv_eerpsdd) )
			goto LABEL_29;
		while ( cdvdfsv_checkdmastat(trid) >= 0 )
			;
		CpuSuspendIntr(&state);
		flag_offs += dmasize;
		trid = sceSifSetDma(&cdvdfsv_eerpsdd, 1);
		CpuResumeIntr(state);
		bsize -= sizestuff;
		buf_offs_sum += sizestuff;
	}
	sectors_1 = 2;
	if ( ssize )
	{
		buf_offs_sum_bytes_in_sector = buf_offs_sum % secsize;
		if ( len2_plus_sec2 < sc_ffffffe9_tmp + buf_offs_sum / secsize + 2 )
			sectors_1 = 1;
		if ( cdvdfsv_verbose > 0 )
			printf("2 CD_READ LBN= %d sectors= %d\n", sc_ffffffe9_tmp + buf_offs_sum / secsize, sectors_1);
		if ( !readproc1(
						sc_ffffffe9_tmp + buf_offs_sum / secsize,
						sectors_1,
						cdvdfsv_rtocbuf,
						&cdvdfsv_rmodeee,
						ps2dvd,
						sync,
						decflag,
						decval) )
			goto LABEL_29;
		if ( datapattern != 2 || ps2dvd )
		{
			i2 = 0;
			if ( buf_offs_sum_bytes_in_sector )
			{
				pbuf2 = cdvdfsv_eereadx.pbuf2;
				rtocbuf_after_logo = &cdvdfsv_rtocbuf[buf_offs_sum_bytes_in_sector + 12];
				do
				{
					if ( i2 % secsize == secsize - buf_offs_sum_bytes_in_sector )
						rtocbuf_after_logo += sector_sizes[ps2dvd] - secsize;
					++i2;
					val_tmp1 = *rtocbuf_after_logo++;
					*pbuf2++ = val_tmp1;
				}
				while ( i2 < ssize );
			}
			else
			{
				i2_offs = 12;
				do
				{
					if ( i2 && !(i2 % secsize) )
						i2_offs += sector_sizes[ps2dvd] - secsize;
					cdvdfsv_eereadx.pbuf2[i2++] = cdvdfsv_rtocbuf[i2_offs++];
				}
				while ( i2 < ssize );
			}
		}
		else
		{
			for ( k = 0; k < ssize; ++k )
				cdvdfsv_eereadx.pbuf2[k] = cdvdfsv_rtocbuf[buf_offs_sum_bytes_in_sector + k];
		}
		buf_offs_sum += ssize;
	}
LABEL_83:
	cdvdfsv_eereadx.b1len = psize;
	cdvdfsv_eereadx.b2len = ssize;
	cdvdfsv_eereadx.b1dst = paddr;
	cdvdfsv_eereadx.b2dst = saddr;
	if ( cdvdfsv_verbose > 0 )
		printf("b psize= %d paddr= %08x bsize= %d ssize= %d saddr %08x\n", psize, paddr, bsize, ssize, saddr);
	while ( cdvdfsv_checkdmastat(trid) >= 0 )
		;
	cdvdfsv_datasdd.src = &cdvdfsv_eereadx;
	lsn2 = (void *)pkt_tmp[1].lsn;
	cdvdfsv_datasdd.size = 144;
	cdvdfsv_datasdd.attr = 0;
	cdvdfsv_readpos = buf_offs_sum;
	cdvdfsv_datasdd.dest = lsn2;
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
	if ( cdvdfsv_verbose > 0 )
		printf("read end\n");
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
				sceCdRMode *in_rmode,
				u32 disktype_14,
				int sync)
{
	u32 disktype_14_tmp; // $fp
	unsigned int secsize; // $s1
	unsigned int bytescount; // $s0
	unsigned int offs; // $s4
	int sectors_partial; // $a1
	int readsize_bytes; // $s2
	int dmasize; // $s3
	int bytescount_in_sectors; // $a1
	int readproc2_res; // $v0
	sceCdRMode rmode; // [sp+30h] [-10h] BYREF
	int scres1; // [sp+38h] [-8h] BYREF
	int sc_ffffffe9_res; // [sp+68h] [+28h] BYREF

	sc_ffffffe9_res = secoffs;
	rmode = *in_rmode;
	disktype_14_tmp = disktype_14;
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
		if ( rmode.datapattern == 1 )
		{
			secsize = 2328;
		}
		else
		{
			secsize = 2048;
			if ( rmode.datapattern >= 2u && rmode.datapattern == 2 )
				secsize = 2340;
		}
		rmode.datapattern = 2;
	}
	bytescount = secsize * seccount;
	offs = 0;
	if ( bytescount )
	{
		while ( 1 )
		{
			sectors_partial = (sc_ffffffe9_res + offs / secsize) & 0xF;
			if ( 16 * secsize >= bytescount )
			{
				bytescount_in_sectors = bytescount / secsize;
				readsize_bytes = bytescount;
				dmasize = bytescount;
				if ( bytescount % secsize )
					bytescount_in_sectors = bytescount / secsize + 1;
				goto LABEL_21;
			}
			readsize_bytes = 16 * secsize;
			if ( sectors_partial )
			{
				dmasize = 16 * secsize;
				if ( (secsize & 0xF) == 0 )
				{
					bytescount_in_sectors = 16 - sectors_partial;
					readsize_bytes = secsize * bytescount_in_sectors;
					dmasize = secsize * bytescount_in_sectors;
					goto LABEL_21;
				}
			}
			else
			{
				dmasize = 16 * secsize;
			}
			bytescount_in_sectors = 16;
LABEL_21:
			readproc2_res = readproc2(
												sc_ffffffe9_res + offs / secsize,
												bytescount_in_sectors,
												&rmode,
												disktype_14_tmp,
												sync,
												0,
												0,
												ee_addr,
												0,
												secsize,
												dmasize,
												0);
			ee_addr += dmasize;
			if ( readproc2_res )
			{
				bytescount -= readsize_bytes;
				offs += readsize_bytes;
				if ( bytescount )
					continue;
			}
			return 1;
		}
	}
	return 1;
}
// 402844: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 4028A0: conditional instruction was optimized away because $s1.4 is in (==800|==918|==924)
// 402744: using guessed type sceCdRMode rmode;

//----- (0040293C) --------------------------------------------------------
int __fastcall cdvdfsv_rpc5h_0F_readchain(cdvdfsv_rpc5h_0F_packet *inbuf, int buflen, void *outbuf)
{
	sceCdRMode *p_scecdrmode30C; // $s6
	void *readPos; // $a0
	int datapattern; // $v1
	int sector_size; // $s7
	unsigned int cnt; // $s5
	sceCdRChain *i; // $s4
	int result; // $v0
	u32 buf_tmp; // $s1
	u32 lbn; // $s2
	u32 sectors; // $s3
	void *buf; // $s1
	int re_result; // $s0
	int sc_fffffffc_res; // $v0
	BOOL disktype_14; // $s0
	int error_code; // $v0
	int trid; // $s0
	int sc_fffffffc_tmp; // [sp+18h] [-8h] BYREF
	int state; // [sp+1Ch] [-4h] BYREF

	cdvdfsv_rderror = 254;
	p_scecdrmode30C = &inbuf->scecdrmode30C;
	cdvdfsv_readpos = 0;
	cdvdfsv_cdvdman_internal_struct_ptr->m_break_cdvdfsv_readchain = 0;
	cdvdfsv_chrdsdd.src = &cdvdfsv_readpos;
	readPos = (void *)inbuf->readPos;
	cdvdfsv_chrdsdd.size = 4;
	cdvdfsv_chrdsdd.attr = 0;
	cdvdfsv_chrdsdd.dest = readPos;
	datapattern = p_scecdrmode30C->datapattern;
	if ( datapattern == 1 )
	{
		sector_size = 2328;
	}
	else
	{
		sector_size = 2048;
		if ( p_scecdrmode30C->datapattern >= 2u )
		{
			cnt = 0;
			if ( datapattern != 2 )
				goto LABEL_8;
			sector_size = 2340;
		}
	}
	cnt = 0;
LABEL_8:
	for ( i = (sceCdRChain *)inbuf; ; ++i )
	{
		result = cdvdfsv_cdvdman_internal_struct_ptr->m_break_cdvdfsv_readchain;
		if ( result )
		{
			result = cdvdfsv_verbose;
			if ( cdvdfsv_verbose > 0 )
				return printf("ReadChain cnt %d on sceCdBreak()\n", cnt);
			return result;
		}
		buf_tmp = i->buffer;
		lbn = i->lbn;
		sectors = i->sectors;
		if ( i->lbn == 0xFFFFFFFF )
			return result;
		if ( sectors == 0xFFFFFFFF )
			return result;
		result = i->buffer & 1;
		if ( buf_tmp == 0xFFFFFFFF )
			return result;
		if ( (buf_tmp & 1) != 0 )
		{
			buf = (void *)(buf_tmp & 0xFFFFFFFE);
			if ( cdvdfsv_verbose > 0 )
				printf(
					"ReadChain lsn= %d nsec= %d buf= %08x secsize= %d\n",
					i->lbn,
					i->sectors,
					buf,
					p_scecdrmode30C->datapattern);
			re_result = sceCdRE(lbn, sectors, buf, p_scecdrmode30C);
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
			if ( cdvdfsv_verbose > 0 )
				printf("ReadChain EE  Memory addr= 0x%08x sector= %d\n", i->lbn, i->sectors);
			disktype_14 = MEMORY[0xBF40200F] == 0x14;
			sc_fffffffc_res = sceCdSC(0xFFFFFFFC, &sc_fffffffc_tmp);
			re_result = cdvdfsv_chreadee(lbn, sectors, (char *)buf_tmp, p_scecdrmode30C, disktype_14, sc_fffffffc_res == 0);
		}
		if ( !re_result )
			break;
		cdvdfsv_readpos += sectors * sector_size;
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
		result = ++cnt < 0x40;
		if ( cnt >= 0x40 )
			return result;
	}
	result = cdvdfsv_verbose;
	if ( cdvdfsv_verbose > 0 )
	{
		error_code = sceCdGetError();
		return printf("ReadChain error code= 0x%02x\n", error_code);
	}
	return result;
}

//----- (00402C40) --------------------------------------------------------
int __fastcall cdvdfsv_rpc5h_02_readcdda(cdvdfsv_rpc5h_02_packet *inbuf, int buflen, void *outbuf)
{
	int trid1; // $s7
	unsigned int buf; // $a2
	void *eedest; // $a0
	u8 *rtocbuf_tmp; // $fp
	unsigned int sector_size; // $s3
	int all_sec_bytes; // $t5
	unsigned int buf_1_toalign; // $v0
	unsigned int buf_align_remain; // $s2
	unsigned int buf_offs_sectors; // $lo
	u32 sectors_1; // $s0
	int cmd_error; // $s1
	int error_code; // $s0
	unsigned int i1; // $v1
	unsigned __int8 *rtocbuf_tmp_offs; // $v0
	unsigned int buf_toalign_tmp; // $t3
	unsigned int buf_offs_mod_sector_size; // $s4
	u32 lsn_2; // $s1
	unsigned int sector_size_in_bytes; // $s6
	int sector_count_in_bytes; // $s5
	u32 sector_count; // $s0
	int sector_count_tmp; // $a1
	int cmd_error_1; // $s1
	int error_code_1; // $s0
	u32 sectors_3; // $s0
	u32 lsn_3; // $s1
	unsigned int buf_offs_mod_sector_size_3; // $hi
	int cmd_error_3; // $s1
	int error_code_3; // $s0
	unsigned int i3; // $v1
	unsigned int buf_offs_ex; // $v0
	unsigned int buf_sec_tmp_tmp; // $t1
	void *eeremaindest; // $a1
	int trid2; // $s7
	int result; // $v0
	int state; // [sp+10h] [-40h] BYREF
	int error_code_tmp; // [sp+14h] [-3Ch] BYREF
	unsigned int buf_offs; // [sp+18h] [-38h]
	unsigned int buf_toalign; // [sp+1Ch] [-34h]
	unsigned int buf_sec_tmp; // [sp+20h] [-30h]
	unsigned int buf_1; // [sp+24h] [-2Ch]
	char *buf_aligned; // [sp+28h] [-28h]
	unsigned int buf_1_toalign_tmp; // [sp+2Ch] [-24h]
	int all_sec; // [sp+30h] [-20h]
	unsigned int lbn_1_end; // [sp+34h] [-1Ch]
	int lbn_1; // [sp+38h] [-18h]
	BOOL cnodtmp1; // [sp+3Ch] [-14h]
	cdvdfsv_rpc5h_02_packet *pkt_tmp; // [sp+40h] [-10h]
	sceCdRMode *mode; // [sp+44h] [-Ch]
	unsigned int sector_size_in_bytes_tmp; // [sp+48h] [-8h]

	trid1 = 0;
	cdvdfsv_rderror = 254;
	error_code_tmp = 0;
	pkt_tmp = inbuf;
	buf = inbuf->buf;
	all_sec = inbuf->nsectors;
	lbn_1 = inbuf->lbn;
	cdvdfsv_eereadfull_dma2.src = &cdvdfsv_readpos;
	eedest = (void *)inbuf->eedest;
	cdvdfsv_eereadfull_dma2.size = 4;
	cdvdfsv_eereadfull_dma2.attr = 0;
	cdvdfsv_eereadfull_dma2.dest = eedest;
	cnodtmp1 = (unsigned int)buflen >= 0x19;
	mode = &inbuf->scecdrmodeC;
	rtocbuf_tmp = cdvdfsv_rtocbuf;
	sector_size = 2352;
	if ( inbuf->scecdrmodeC.datapattern && inbuf->scecdrmodeC.datapattern == 1 )
		sector_size = 2368;
	buf_offs = 0;
	all_sec_bytes = sector_size * all_sec;
	lbn_1_end = lbn_1 + all_sec;
	if ( (buf & 0x3F) != 0 )
		buf_toalign = (buf & 0xFFFFFFC0) - (buf - 64);
	else
		buf_toalign = 0;
	buf_1 = buf;
	buf_1_toalign = (buf + all_sec_bytes) & 0xFFFFFFC0;
	buf_align_remain = buf_1_toalign - (buf + buf_toalign);
	buf_aligned = (char *)(buf + buf_toalign);
	buf_1_toalign_tmp = buf_1_toalign;
	buf_sec_tmp = all_sec_bytes - (buf_1_toalign - buf);
	if ( buf_toalign )
	{
		buf_offs_sectors = buf_offs / sector_size;
		sectors_1 = 2;
		if ( lbn_1_end < lbn_1 + buf_offs / sector_size + 2 )
			sectors_1 = 1;
		if ( cdvdfsv_verbose > 0 )
			printf("0 CD_READ LBN= %d sectors= %d all= %d\n", lbn_1 + buf_offs_sectors, sectors_1, all_sec);
		cmd_error = sceCdReadCDDA(lbn_1 + buf_offs_sectors, sectors_1, rtocbuf_tmp, mode);
		sceCdSync(3);
		error_code = sceCdGetError();
		if ( error_code || !cmd_error )
		{
			if ( !cmd_error )
				sceCdSC(0xFFFFFFFE, &cdvdfsv_rderror);
			if ( cdvdfsv_verbose > 0 )
				printf("Read error code %x cmd error %d\n", error_code, cmd_error);
			if ( error_code != 50 && error_code != 56 )
			{
				buf_toalign = 0;
				goto LABEL_74;
			}
			error_code_tmp = error_code;
		}
		i1 = 0;
		rtocbuf_tmp_offs = rtocbuf_tmp;
		do
		{
			buf_toalign_tmp = buf_toalign;
			cdvdfsv_eereadx.pbuf1[i1++] = *rtocbuf_tmp_offs;
			rtocbuf_tmp_offs = &rtocbuf_tmp[i1];
		}
		while ( i1 < buf_toalign_tmp );
		buf_offs += buf_toalign;
	}
	if ( buf_align_remain )
	{
		sector_size_in_bytes_tmp = 8 * sector_size;
		do
		{
			buf_offs_mod_sector_size = buf_offs % sector_size;
			lsn_2 = lbn_1 + buf_offs / sector_size;
			sector_size_in_bytes = sector_size_in_bytes_tmp;
			if ( sector_size_in_bytes_tmp >= buf_align_remain )
			{
				sector_count_tmp = buf_align_remain / sector_size;
				sector_size_in_bytes = buf_align_remain;
				sector_count_in_bytes = buf_align_remain;
				if ( buf_align_remain % sector_size )
					sector_count_tmp = buf_align_remain / sector_size + 1;
				sector_count = sector_count_tmp + (buf_offs_mod_sector_size != 0);
			}
			else
			{
				sector_count_in_bytes = sector_size_in_bytes_tmp;
				sector_count = 8;
				if ( buf_offs % sector_size )
					sector_count = 9;
			}
			if ( lbn_1_end < lsn_2 + sector_count )
				sector_count = lbn_1_end - lsn_2;
			while ( cdvdfsv_checkdmastat(trid1) >= 0 )
				;
			cmd_error_1 = sceCdReadCDDA(lsn_2, sector_count, rtocbuf_tmp, mode);
			sceCdSync(3);
			error_code_1 = sceCdGetError();
			if ( error_code_1 || !cmd_error_1 )
			{
				if ( !cmd_error_1 )
					sceCdSC(0xFFFFFFFE, &cdvdfsv_rderror);
				if ( cdvdfsv_verbose > 0 )
					printf("Read error code %x cmd error %d\n", error_code_1, cmd_error_1);
				if ( error_code_1 != 50 && error_code_1 != 56 )
					goto LABEL_74;
				error_code_tmp = error_code_1;
			}
			if ( buf_offs_mod_sector_size )
				cdvdfsv_memcpy((_DWORD *)rtocbuf_tmp, (_DWORD *)&rtocbuf_tmp[buf_offs_mod_sector_size], sector_count_in_bytes);
			cdvdfsv_eereadfull_dma1.src = rtocbuf_tmp;
			cdvdfsv_eereadfull_dma1.size = sector_count_in_bytes;
			cdvdfsv_eereadfull_dma1.attr = 0;
			cdvdfsv_eereadfull_dma1.dest = buf_aligned;
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
			if ( cnodtmp1 )
			{
				CpuSuspendIntr(&state);
				sceSifSetDma(&cdvdfsv_eereadfull_dma2, 1);
				CpuResumeIntr(state);
			}
			buf_align_remain -= sector_size_in_bytes;
			buf_aligned += sector_count_in_bytes;
			buf_offs += sector_size_in_bytes;
		}
		while ( buf_align_remain );
	}
	sectors_3 = 2;
	if ( buf_sec_tmp )
	{
		lsn_3 = lbn_1 + buf_offs / sector_size;
		if ( lbn_1_end < lsn_3 + 2 )
			sectors_3 = 1;
		if ( cdvdfsv_verbose > 0 )
			printf("0 CD_READ LBN= %d sectors= %d all= %d\n", lbn_1 + buf_offs / sector_size, sectors_3, all_sec);
		buf_offs_mod_sector_size_3 = buf_offs % sector_size;
		if ( cdvdfsv_verbose > 0 )
			printf("2 CD_READ LBN= %d sectors= %d\n", lsn_3, sectors_3);
		cmd_error_3 = sceCdReadCDDA(lsn_3, sectors_3, rtocbuf_tmp, mode);
		sceCdSync(3);
		error_code_3 = sceCdGetError();
		if ( error_code_3 || !cmd_error_3 )
		{
			if ( !cmd_error_3 )
				sceCdSC(0xFFFFFFFE, &cdvdfsv_rderror);
			if ( cdvdfsv_verbose > 0 )
				printf("Read error code %x cmd error %d\n", error_code_3, cmd_error_3);
			if ( error_code_3 == 50 || error_code_3 == 56 )
				error_code_tmp = error_code_3;
			else
				buf_sec_tmp = 0;
		}
		i3 = 0;
		if ( buf_sec_tmp )
		{
			buf_offs_ex = buf_offs_mod_sector_size_3;
			do
			{
				buf_sec_tmp_tmp = buf_sec_tmp;
				cdvdfsv_eereadx.pbuf2[i3++] = rtocbuf_tmp[buf_offs_ex];
				buf_offs_ex = buf_offs_mod_sector_size_3 + i3;
			}
			while ( i3 < buf_sec_tmp_tmp );
		}
		buf_offs += buf_sec_tmp;
	}
LABEL_74:
	cdvdfsv_eereadx.b1len = buf_toalign;
	cdvdfsv_eereadx.b2len = buf_sec_tmp;
	cdvdfsv_eereadx.b1dst = buf_1;
	cdvdfsv_eereadx.b2dst = buf_1_toalign_tmp;
	while ( cdvdfsv_checkdmastat(trid1) >= 0 )
		;
	cdvdfsv_eereadfull_dma1.src = &cdvdfsv_eereadx;
	eeremaindest = (void *)pkt_tmp->eeremaindest;
	cdvdfsv_eereadfull_dma1.size = 144;
	cdvdfsv_eereadfull_dma1.attr = 0;
	cdvdfsv_readpos = buf_offs;
	cdvdfsv_eereadfull_dma1.dest = eeremaindest;
	while ( 1 )
	{
		CpuSuspendIntr(&state);
		trid2 = sceSifSetDma(&cdvdfsv_eereadfull_dma1, 1);
		if ( cnodtmp1 )
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
	result = cdvdfsv_verbose;
	if ( cdvdfsv_verbose > 0 )
		result = printf("read end\n");
	*(_DWORD *)outbuf = buf_offs;
	return result;
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
	int inbuf_arg_tmp; // $s0
	int i; // $s0
	int diskready_res_tmp; // $v1
	int sc_fffffffd_res; // $v0
	int *result; // $v0
	int scres; // [sp+10h] [-8h] BYREF
	u32 efres; // [sp+14h] [-4h] BYREF

	inbuf_arg_tmp = *(_DWORD *)buffer;
	if ( cdvdfsv_verbose > 0 )
		Kprintf("DISK READY call 0x%02x\n", MEMORY[0xBF40200A]);
	if ( inbuf_arg_tmp )
	{
		if ( inbuf_arg_tmp == 8 )
		{
			diskready_res_tmp = MEMORY[0xBF402005];
		}
		else if ( (MEMORY[0xBF402005] & 0xC0) != 64
					 || (sc_fffffffd_res = sceCdSC(0xFFFFFFFD, &scres), diskready_res_tmp = 2, sc_fffffffd_res) )
		{
			diskready_res_tmp = 6;
			if ( cdvdfsv_verbose > 0 )
			{
				Kprintf("Drive Not Ready\n");
				diskready_res_tmp = 6;
			}
		}
	}
	else
	{
		if ( cdvdfsv_verbose > 0 )
			Kprintf("Wait Drive Ready %x\n", MEMORY[0xBF402005]);
		cdvdfsv_ef = sceCdSC(0xFFFFFFF5, &scres);
		for ( i = MEMORY[0xBF40200F]; ; i = MEMORY[0xBF40200F] )
		{
			if ( (MEMORY[0xBF402005] & 0xC0) == 64 && !sceCdSC(0xFFFFFFFD, &scres) )
			{
				diskready_res_tmp = 2;
				if ( (unsigned int)(i - 1) >= 4 )
					break;
			}
			if ( cdvdfsv_verbose >= 2 )
				Kprintf("Wait Drive Ready %x\n", MEMORY[0xBF402005]);
			DelayThread(2000);
			WaitEventFlag(cdvdfsv_ef, 1u, 0, &efres);
		}
	}
	result = &diskready_res;
	diskready_res = diskready_res_tmp;
	return result;
}
// 405BF0: using guessed type int diskready_res;

//----- (0040358C) --------------------------------------------------------
int __fastcall cdvdfsv_rpc5h_04_gettoc(void *inbuf, int buflen, cdvdfsv_rpc5h_04_outpacket *outbuf)
{
	int Toc; // $s1
	void *inbuf_ptr; // $a0
	int trid; // $s0
	int result; // $v0
	int state; // [sp+10h] [-8h] BYREF

	if ( cdvdfsv_verbose > 0 )
		printf("GET TOC call 0x%08x\n", inbuf);
	Toc = sceCdGetToc(cdvdfsv_rtocbuf);
	if ( cdvdfsv_verbose > 0 )
		printf("GET TOC called\n");
	cdvdfsv_rtocsdd.src = cdvdfsv_rtocbuf;
	inbuf_ptr = *(void **)inbuf;
	cdvdfsv_rtocsdd.size = 2064;
	cdvdfsv_rtocsdd.attr = 0;
	cdvdfsv_rtocsdd.dest = inbuf_ptr;
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
	if ( MEMORY[0xBF40200F] == 20 )
		goto LABEL_16;
	result = 0;
	if ( MEMORY[0xBF40200F] < 0x15u )
		goto LABEL_18;
	if ( MEMORY[0xBF40200F] == 253 )
	{
		result = 0;
		goto LABEL_18;
	}
	if ( MEMORY[0xBF40200F] >= 0xFEu )
	{
		result = 0;
		if ( MEMORY[0xBF40200F] == 254 )
			goto LABEL_16;
LABEL_18:
		outbuf->dword0 = Toc;
		goto LABEL_19;
	}
	result = 0;
	if ( MEMORY[0xBF40200F] == 252 )
	{
LABEL_16:
		result = 1;
		goto LABEL_18;
	}
	outbuf->dword0 = Toc;
LABEL_19:
	outbuf->dword4 = result;
	return result;
}

//----- (004036EC) --------------------------------------------------------
int __fastcall cdvdfsv_rpc3h_03_disktype(void *inbuf, int buflen, void *outbuf)
{
	int result; // $v0

	result = sceCdGetDiskType();
	*(_DWORD *)outbuf = result;
	return result;
}

//----- (00403714) --------------------------------------------------------
int __fastcall cdvdfsv_rpc3h_0C_cdstatus(void *inbuf, int buflen, void *outbuf)
{
	int result; // $v0

	result = sceCdStatus();
	*(_DWORD *)outbuf = result;
	return result;
}

//----- (0040373C) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_06_ri(void *inbuf, int buflen, cdvdfsv_rpc3h_06_outpacket *outbuf)
{
	int retry_cnt; // $s1
	int retval; // $v0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	retry_cnt = 0;
	do
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		retval = sceCdRI(&outbuf->buffer, &outbuf->result);
		outbuf->dword0 = retval;
		if ( retval )
			break;
	}
	while ( retry_cnt++ < 3 );
}

//----- (004037A4) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_1A_rm(void *inbuf, int buflen, cdvdfsv_rpc3h_1A_outpacket *outbuf)
{
	int retry_cnt; // $s1
	int retval; // $v0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	retry_cnt = 0;
	do
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		retval = sceCdRM(&outbuf->buffer, &outbuf->status);
		outbuf->dword0 = retval;
		if ( retval )
			break;
	}
	while ( retry_cnt++ < 3 );
}

//----- (0040380C) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_24_readguid(void *inbuf, int buflen, cdvdfsv_rpc3h_24_outpacket *outbuf)
{
	int retry_cnt; // $s0
	int retval; // $v0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	retry_cnt = 0;
	do
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		retval = sceCdReadGUID(&outbuf->guid);
		outbuf->dword0 = retval;
		if ( retval )
			break;
	}
	while ( retry_cnt++ < 3 );
}

//----- (00403870) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_26_readmodelid(void *inbuf, int buflen, cdvdfsv_rpc3h_26_outpacket *outbuf)
{
	int retry_cnt; // $s0
	int retval; // $v0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	retry_cnt = 0;
	do
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		retval = sceCdReadModelID(&outbuf->id);
		outbuf->dword0 = retval;
		if ( retval )
			break;
	}
	while ( retry_cnt++ < 3 );
}

//----- (004038D4) --------------------------------------------------------
int __fastcall cdvdfsv_rpc3h_22_mmode(cdvdfsv_rpc3h_22_packet *inbuf, int buflen, void *outbuf)
{
	int result; // $v0

	if ( buflen == 4 || (result = inbuf->char4) == 0 )
	{
		result = sceCdMmode(inbuf->media);
		*(_DWORD *)outbuf = result;
	}
	return result;
}

//----- (0040391C) --------------------------------------------------------
int __fastcall cdvdfsv_rpc3h_23_changethreadpriority(void *inbuf, int buflen, void *outbuf)
{
	int result; // $v0

	result = sceCdChangeThreadPriority(*(_DWORD *)inbuf);
	*(_DWORD *)outbuf = result;
	return result;
}

//----- (00403948) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_21_poweroff(void *inbuf, int buflen, cdvdfsv_rpc3h_21_outpacket *outbuf)
{
	int retry_cnt; // $s0
	int retval; // $v0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	retry_cnt = 0;
	do
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		retval = sceCdPowerOff(&outbuf->result);
		outbuf->dword0 = retval;
		if ( retval )
			break;
	}
	while ( retry_cnt++ < 3 );
}

//----- (004039AC) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_15_ctrladout(void *inbuf, int buflen, cdvdfsv_rpc3h_15_outpacket *outbuf)
{
	int retry_cnt; // $s0
	int retval; // $v0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	retry_cnt = 0;
	do
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		retval = sceCdCtrlADout(*(_DWORD *)inbuf, &outbuf->status);
		outbuf->dword0 = retval;
		if ( retval )
			break;
	}
	while ( retry_cnt++ < 3 );
}

//----- (00403A20) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_01_readclock(void *inbuf, int buflen, cdvdfsv_rpc3h_01_outpacke *outbuf)
{
	int retry_cnt; // $s0
	int retval; // $v0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	retry_cnt = 0;
	do
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		retval = sceCdReadClock(&outbuf->clock);
		outbuf->dword0 = retval;
		if ( retval )
			break;
	}
	while ( retry_cnt++ < 3 );
}

//----- (00403A84) --------------------------------------------------------
int __fastcall cdvdfsv_rpc5h_11_readdiskid(void *inbuf, int buflen, cdvdfsv_rpc5h_11_outpacket *outbuf)
{
	int result; // $v0
	__int16 diskid_tmp2; // $a1
	u8 diskid_tmp[6]; // [sp+10h] [-10h] BYREF

	result = sceCdReadDiskID((unsigned int *)diskid_tmp);
	outbuf->dword0 = result;
	diskid_tmp2 = *(_WORD *)&diskid_tmp[4];
	outbuf->dword4 = *(_DWORD *)diskid_tmp;
	outbuf->word8 = diskid_tmp2;
	return result;
}

//----- (00403AC0) --------------------------------------------------------
int __fastcall cdvdfsv_rpc5h_17_doesuniquekeyexist(void *inbuf, int buflen, cdvdfsv_rpc5h_17_outpacket *outbuf)
{
	int result; // $v0

	result = sceCdDoesUniqueKeyExist(&outbuf->arg1);
	outbuf->dword0 = result;
	return result;
}

//----- (00403AEC) --------------------------------------------------------
int __fastcall cdvdfsv_rpc3h_0B_applyscmd(
				cdvdfsv_rpc3h_0B_packet *inbuf,
				int buflen,
				cdvdfsv_rpc3h_0B_outpacket *outbuf)
{
	int result; // $v0
	int res1_tmp; // $t0
	int res2_tmp; // $t1
	int res3_tmp; // $t2
	int buf_tmp[4]; // [sp+10h] [-10h] BYREF

	result = sceCdApplySCmd(inbuf->cmdNum, &inbuf->inBuff, inbuf->inBuffSize, buf_tmp);
	res1_tmp = buf_tmp[1];
	res2_tmp = buf_tmp[2];
	res3_tmp = buf_tmp[3];
	outbuf->dword0 = buf_tmp[0];
	outbuf->dword4 = res1_tmp;
	outbuf->dword8 = res2_tmp;
	outbuf->dwordC = res3_tmp;
	return result;
}

//----- (00403B64) --------------------------------------------------------
int __fastcall cdvdfsv_rpc5h_0C_applyncmd(cdvdfsv_rpc5h_0C_packet *inbuf, int buflen, void *outbuf)
{
	*(_DWORD *)outbuf = sceCdApplyNCmd(inbuf->cmdNum, &inbuf->inBuff, inbuf->inBuffSize);
	return sceCdSync(2);
}

//----- (00403BA4) --------------------------------------------------------
int __fastcall cdvdfsv_rpc3h_04_geterror(void *inbuf, int buflen, void *outbuf)
{
	int result; // $v0

	result = sceCdGetError();
	*(_DWORD *)outbuf = result;
	return result;
}

//----- (00403BCC) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3h_05_trayreq(void *inbuf, int buflen, cdvdfsv_rpc3h_05_outpacket *outbuf)
{
	int retry_cnt; // $s0
	int retval; // $v0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	retry_cnt = 0;
	do
	{
		WaitEventFlag(cdvdman_scmd_ef, 1u, 0, efres);
		retval = sceCdTrayReq(*(_DWORD *)inbuf, &outbuf->traychk);
		outbuf->dword0 = retval;
		if ( retval )
			break;
	}
	while ( retry_cnt++ < 3 );
}

//----- (00403C40) --------------------------------------------------------
int __fastcall cdvdfsv_rpc3h_25_settimeout(cdvdfsv_rpc3h_25_packet *inbuf, int buflen, void *outbuf)
{
	int result; // $v0

	result = sceCdSetTimeout(inbuf->param, inbuf->timeout);
	*(_DWORD *)outbuf = result;
	return result;
}

//----- (00403C74) --------------------------------------------------------
int __fastcall cdvdfsv_rpc3h_27_readdvddualinfo(void *inbuf, int buflen, cdvdfsv_rpc3h_27_outpacket *outbuf)
{
	int result; // $v0

	result = sceCdReadDvdDualInfo(&outbuf->on_dual, &outbuf->layer1_start);
	outbuf->dword0 = result;
	return result;
}

//----- (00403CA4) --------------------------------------------------------
int __cdecl cdvdfsv_rpc5h_0E_diskready()
{
	int sc_ffffffda_res; // $s1
	int result; // $v0
	int scval_tmp[2]; // [sp+10h] [-8h] BYREF

	sc_ffffffda_res = MEMORY[0xBF40200F];
	if ( (MEMORY[0xBF402005] & 0xC0) != 64
		|| sceCdSC(0xFFFFFFFD, scval_tmp)
		|| !sceCdSC(0xFFFFFFF4, scval_tmp)
		|| (result = 2, (unsigned int)(sc_ffffffda_res - 1) < 4) )
	{
		result = 6;
		if ( cdvdfsv_verbose > 0 )
		{
			printf("Drive Not Ready\n");
			return 6;
		}
	}
	return result;
}

//----- (00403D4C) --------------------------------------------------------
CDVDReadResult *__fastcall cbrpc_rpc5_cdvdncmds(int fno, void *buffer, int length)
{
	int disktype_xor; // $v0
	BOOL disktype_cond; // $s2
	int sc_fffffffc_val; // $v0
	int stm_devctl_val; // $a1
	int sc_fffffff6_in[2]; // [sp+18h] [-8h] BYREF
	int fno_1; // [sp+30h] [+10h] BYREF

	fno_1 = fno;
	if ( cdvdfsv_verbose > 0 )
		printf("sce_cdvd N cmd start %d\n", fno);
	cdvdfsv_rpc5flg = 1;
	sceCdSC(-10, &fno_1);
	disktype_xor = MEMORY[0xBF40200F] ^ 0x14;
	disktype_cond = disktype_xor == 0;
	switch ( fno_1 )
	{
		case 1:
			sc_fffffffc_val = sceCdSC(-4, sc_fffffff6_in);
			cdvdfsv_rpc5h_01_readee((cdvdfsv_rpc5h_01_packet *)buffer, length, crr, disktype_cond, sc_fffffffc_val == 0, 0);
			break;
		case 2:
			cdvdfsv_rpc5h_02_readcdda((cdvdfsv_rpc5h_02_packet *)buffer, length, crr);
			break;
		case 4:
			cdvdfsv_rpc5h_04_gettoc(buffer, length, (cdvdfsv_rpc5h_04_outpacket *)crr);
			break;
		case 5:
			if ( cdvdfsv_verbose > 0 )
				printf("Call Seek lsn= %d\n", *(_DWORD *)buffer);
			crr[0] = sceCdSeek(*(_DWORD *)buffer);
			if ( cdvdfsv_verbose > 0 )
				printf("Call Seek end\n");
			goto LABEL_24;
		case 6:
			if ( cdvdfsv_verbose > 0 )
				printf("Call Standby\n");
			crr[0] = sceCdStandby();
			sceCdSync(4);
			if ( cdvdfsv_verbose > 0 )
				printf("Call Standby called\n");
			break;
		case 7:
			if ( cdvdfsv_verbose > 0 )
				printf("Call Stop\n");
			crr[0] = sceCdStop();
			sceCdSync(4);
			break;
		case 8:
			if ( cdvdfsv_verbose > 0 )
				printf("Call Pause\n");
			crr[0] = sceCdPause();
LABEL_24:
			sceCdSync(6);
			break;
		case 9:
			stm_devctl_val = 17302;
			goto LABEL_28;
		case 10:
			stm_devctl_val = 17304;
LABEL_28:
			if ( devctl("cdrom_stm0:", stm_devctl_val, buffer, length, crr, 4u) < 0 )
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
			cdvdfsv_rpc5h_01_readee(
				(cdvdfsv_rpc5h_01_packet *)buffer,
				length,
				crr,
				disktype_xor == 0,
				1,
				cdvdfsv_cdvdman_internal_struct_ptr->no_dec_flag == 0);
			break;
		case 23:
			cdvdfsv_rpc5h_17_doesuniquekeyexist(buffer, length, (cdvdfsv_rpc5h_17_outpacket *)crr);
			break;
		default:
			if ( cdvdfsv_verbose > 0 )
				printf("sce_cdvd no block IO :unrecognized code %x\n", fno_1);
			crr[0] = 0;
			break;
	}
	sc_fffffff6_in[0] = 0;
	sceCdSC(-10, sc_fffffff6_in);
	cdvdfsv_rpc5flg = 0;
	if ( cdvdfsv_verbose > 0 )
		printf("sce_cdvd N cmd end\n");
	return (CDVDReadResult *)crr;
}

//----- (00404160) --------------------------------------------------------
CDVDCmdResult *__fastcall cbrpc_rpc3_cdvdscmds(int fno, void *buffer, int length)
{
	CDVDCmdResult *result; // $v0

	if ( cdvdfsv_verbose > 0 )
		printf("sce_cdvd S cmd start %d\n", fno);
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
			if ( cdvdfsv_verbose > 0 )
				printf("sce_cdvd block IO :unrecognized code 0x%02x\n", fno);
			outbuf.dword0 = 0;
			break;
	}
	if ( cdvdfsv_verbose > 0 )
		printf("sce_cdvd S cmd end\n");
	result = (CDVDCmdResult *)&outbuf;
	cdvdfsv_rpc3flg = 0;
	return result;
}
// 405720: using guessed type int cdvdfsv_rpc3flg;

//----- (00404424) --------------------------------------------------------
int __cdecl cdvdfsv_poffloop()
{
	int result; // $v0
	int trid; // $s0
	char cmdpkt[16]; // [sp+18h] [-18h] BYREF
	int scres; // [sp+28h] [-8h] BYREF
	u32 efres; // [sp+2Ch] [-4h] BYREF

	cdvdfsv_ef = sceCdSC(0xFFFFFFF5, &scres);
	while ( 1 )
	{
		ClearEventFlag(cdvdfsv_ef, 0xFFFFFFFB);
		WaitEventFlag(cdvdfsv_ef, 4u, 0, &efres);
		result = cdvdfsv_nopocm;
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
	return result;
}
// 404424: using guessed type char cmdpkt[16];

//----- (004044F4) --------------------------------------------------------
void __cdecl cdvdfsv_rpc1_th(void *arg)
{
	int ThreadId; // $v0

	ThreadId = GetThreadId();
	sceSifSetRpcQueue(&rpc_qdata1, ThreadId);
	sceSifRegisterRpc(&rpc_sdata1, 0x80000592, (SifRpcFunc_t)cbrpc_rpc1_cdinit, rpc_buffer1, 0, 0, &rpc_qdata1);
	sceSifRegisterRpc(&rpc_sdata2, 0x8000059A, (SifRpcFunc_t)cbrpc_rpc2_diskready, rpc_buffer2, 0, 0, &rpc_qdata1);
	sceSifRegisterRpc(&rpc_sdata3, 0x80000593, (SifRpcFunc_t)cbrpc_rpc3_cdvdscmds, rpc_buffer3, 0, 0, &rpc_qdata1);
	sceSifRpcLoop(&rpc_qdata1);
	ExitDeleteThread();
}

//----- (004045CC) --------------------------------------------------------
void __cdecl cdvdfsv_rpc3_th(void *arg)
{
	int ThreadId; // $v0

	ThreadId = GetThreadId();
	sceSifSetRpcQueue(&rpc_qdata3, ThreadId);
	sceSifRegisterRpc(&rpc_sdata6, 0x8000059C, (SifRpcFunc_t)cbrpc_rpc2_diskready, rpc_buffer2, 0, 0, &rpc_qdata3);
	sceSifRpcLoop(&rpc_qdata3);
	ExitDeleteThread();
}

//----- (00404644) --------------------------------------------------------
void __cdecl cdvdfsv_rpc2_th(void *arg)
{
	int ThreadId; // $v0

	ThreadId = GetThreadId();
	sceSifSetRpcQueue(&rpc_qdata2, ThreadId);
	sceSifRegisterRpc(&rpc_sdata4, 0x80000597, (SifRpcFunc_t)cbrpc_rpc4_fscall, rpc_buffer4, 0, 0, &rpc_qdata2);
	sceSifRegisterRpc(&rpc_sdata5, 0x80000595, (SifRpcFunc_t)cbrpc_rpc5_cdvdncmds, rpc_buffer5, 0, 0, &rpc_qdata2);
	sceSifRpcLoop(&rpc_qdata2);
	ExitDeleteThread();
}

//----- (004046F0) --------------------------------------------------------
int __fastcall cdvdfsv_unused_xorfun(unsigned int *a1, int a2)
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
					result ^= 0x80000011;
				v7 = (v6 & 0x80) == 0;
				v6 *= 2;
				if ( !v7 )
					result ^= 1u;
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
