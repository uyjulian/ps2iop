
#include "irx_imports.h"
#include "../00common/defs.h"

#include <kerr.h>

IRX_ID("cdvd_ee_driver", 2, 38);

extern struct irx_export_table _exp_cdvdfsv;

int __fastcall cdvdfsv_checkdmastat(int trid);
int __cdecl cdvdfsv_cleanuprpc();
int __fastcall _start(int ac, char **av);
int __cdecl cdvdfsv_init();
void __cdecl cdvdfsv_main_th(void *arg);
int *__fastcall cdvdfsv_4(int arg1);
void __cdecl cdvdfsv_parseargs(int ac, char **av);
int __cdecl sceCdChangeThreadPriority(int priority);
void *__fastcall cbrpc_rpc1_cdinit(int fno, void *buffer, int length);
void __fastcall cdvdfsv_rpc3h_16_break(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void *__fastcall cbrpc_rpc4_fscall(int fno, void *buffer, int length);
int __fastcall alarm_cb(void *a1);
void __cdecl cdvdfsv_rpc5h_0D_iopmread(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf);
u8 __cdecl cdvdfsv_syncdec(int flag, int xorkey, int arg2, u8 data);
int __cdecl cdvdfsv_cb_read();
int __cdecl cdvdfsv_checksid(u32 lsn, u32 sectors, u32 ps2dvd, void *buf, int decflag, int decshift, u32 *syncdec_mask);
int __fastcall readproc2(u32 lsn, u32 nsec, sceCdRMode *mode, u32 sector_size_selection, int do_multi_retries, int enable_dec_shift, int dec_shift, char *ee_addr, int fssift, int secsize, int dmasize, SifDmaTransfer_t *post_dmat);
int __fastcall readproc1(unsigned int lsn, u32 nsec, void *retptr, sceCdRMode *rmode, int ps2dvd, int enable_retries, int dec_shift_enable, int dec_shift_value);
void __cdecl cdvdfsv_rpc5h_01_readee(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf, u32 ps2dvd, int sync, int decflag);
int __fastcall cdvdfsv_chreadee(int secoffs, int seccount, char *ee_addr, const sceCdRMode *in_rmode, u32 disktype_14, int sync);
void __fastcall cdvdfsv_rpc5h_0F_readchain(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf);
void __fastcall cdvdfsv_rpc5h_02_readcdda(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf);
void *__fastcall cbrpc_rpc2_diskready(int fno, void *buffer, int length);
void __fastcall cdvdfsv_rpc5h_04_gettoc(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf);
void __fastcall cdvdfsv_rpc3h_03_disktype(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __fastcall cdvdfsv_rpc3h_0C_cdstatus(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_06_ri(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_1A_rm(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_24_readguid(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_26_readmodelid(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __fastcall cdvdfsv_rpc3h_22_mmode(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __fastcall cdvdfsv_rpc3h_23_changethreadpriority(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_21_poweroff(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_15_ctrladout(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_01_readclock(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __fastcall cdvdfsv_rpc5h_11_readdiskid(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf);
void __fastcall cdvdfsv_rpc5h_17_doesuniquekeyexist(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf);
void __fastcall cdvdfsv_rpc3h_0B_applyscmd(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __fastcall cdvdfsv_rpc5h_0C_applyncmd(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf);
void __fastcall cdvdfsv_rpc3h_04_geterror(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __cdecl cdvdfsv_rpc3h_05_trayreq(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __fastcall cdvdfsv_rpc3h_25_settimeout(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
void __fastcall cdvdfsv_rpc3h_27_readdvddualinfo(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf);
int __cdecl cdvdfsv_rpc5h_0E_diskready();
void *__fastcall cbrpc_rpc5_cdvdncmds(int fno, void *buffer, int length);
void *__fastcall cbrpc_rpc3_cdvdscmds(int fno, void *buffer, int length);
void __cdecl cdvdfsv_poffloop();
void __cdecl cdvdfsv_rpc1_th(void *arg);
void __cdecl cdvdfsv_rpc3_th(void *arg);
void __cdecl cdvdfsv_rpc2_th(void *arg);
void __fastcall cdvdfsv_unused_xorfun(unsigned int *, int);
unsigned int __fastcall optimized_memcpy(char *dst, const char *src, unsigned int n);
void cdvdfsv_1();

int g_cdvdfsv_def_pri = 81;
int g_verbose_level = 0;
int g_cdvdfsv_spinctl = -1;
int g_cdvdfsv_plbreak = 0;
int g_cdvdfsv_nopocm = 0;
int g_cdvdfsv_rpc5flg = 0;
int g_cdvdfsv_rpc3flg = 0;
iop_library_t g_modload_libinfo = { NULL, NULL, 256, 0, "modload", { NULL } };
int g_cdvdfsv_r2retry = 0;
int g_cdvdfsv_r2count = 0;
int g_cdvdfsv_sid_err_recover_cnt = 0;
int g_cdvdfsv_err_count = 0;
int g_dword_405750[2];
void *cdvdfsv_fsvrbuf;
int g_dword_40575C;
char *g_cdvdfsv_rtocbuf;
SifDmaTransfer_t g_cdvdfsv_fssdd;
SifDmaTransfer_t g_cdvdfsv_iomrsdd;
SifDmaTransfer_t g_cdvdfsv_rdp2sdd;
SifDmaTransfer_t g_cdvdfsv_multi_dmat[16];
sceCdRMode g_cdvdfsv_rmodeee;
SifDmaTransfer_t g_cdvdfsv_datasdd;
SifDmaTransfer_t g_cdvdfsv_eerpsdd;
SifDmaTransfer_t g_cdvdfsv_chrdsdd;
SifDmaTransfer_t g_cdvdfsv_eereadfull_dma1;
SifDmaTransfer_t g_cdvdfsv_eereadfull_dma2;
SifDmaTransfer_t g_cdvdfsv_rtocsdd;
iop_sys_clock_t g_cdvdfsv_read_to;
int g_cdvdman_intr_efid;
int g_scmd_evid;
int g_cdvdfsv_thids[4];
cdvdman_internal_struct_t *g_cdvdman_istruct_ptr;
cdvdfsv_rpc1h_outpacket g_cdvdfsv_initres;
cdvdfsv_unaligned_data_outpacket g_cdvdfsv_eereadx;
SifRpcDataQueue_t g_rpc_qdata2;
SifRpcDataQueue_t g_rpc_qdata1;
SifRpcDataQueue_t g_rpc_qdata3;
SifRpcServerData_t g_rpc_sdata1;
SifRpcServerData_t g_rpc_sdata4;
SifRpcServerData_t g_rpc_sdata5;
SifRpcServerData_t g_rpc_sdata2;
SifRpcServerData_t g_rpc_sdata6;
SifRpcServerData_t g_rpc_sdata3;
cdvdfsv_rpc4h_outpacket g_cdvdfsv_srchres;
int g_cdvdfsv_readpos;
int g_cdvdfsv_rderror;
cdvdfsv_rpc2h_outpacket g_diskready_res;
cdvdfsv_rpc5h_outpacket g_crr;
cdvdfsv_rpc3h_outpacket g_outbuf;
int g_rpc_buffer3[260];
int g_rpc_buffer5[256];
int g_rpc_buffer1[4];
int g_rpc_buffer4[76];
int g_rpc_buffer2[4];

int __fastcall cdvdfsv_checkdmastat(int trid)
{
	int retval;
	int state;

	if ( QueryIntrContext() )
		return sceSifDmaStat(trid);
	CpuSuspendIntr(&state);
	retval = sceSifDmaStat(trid);
	CpuResumeIntr(state);
	return retval;
}

int __cdecl cdvdfsv_cleanuprpc()
{
	unsigned int i;

	sceSifRemoveRpc(&g_rpc_sdata1, &g_rpc_qdata1);
	sceSifRemoveRpc(&g_rpc_sdata2, &g_rpc_qdata1);
	sceSifRemoveRpc(&g_rpc_sdata3, &g_rpc_qdata1);
	sceSifRemoveRpc(&g_rpc_sdata6, &g_rpc_qdata3);
	sceSifRemoveRpc(&g_rpc_sdata4, &g_rpc_qdata2);
	sceSifRemoveRpc(&g_rpc_sdata5, &g_rpc_qdata2);
	sceSifRemoveRpcQueue(&g_rpc_qdata1);
	sceSifRemoveRpcQueue(&g_rpc_qdata2);
	sceSifRemoveRpcQueue(&g_rpc_qdata3);
	g_cdvdfsv_nopocm = 1;
	g_cdvdfsv_plbreak = 1;
	for ( i = 0; i < (sizeof(g_cdvdfsv_thids)/sizeof(g_cdvdfsv_thids[0])); i += 1 )
	{
		TerminateThread(g_cdvdfsv_thids[i]);
		DeleteThread(g_cdvdfsv_thids[i]);
	}
	return 1;
}

int __fastcall _start(int ac, char **av)
{
	const unsigned __int16 *LibraryEntryTable;
	int state;

	if ( ac < 0 )
	{
		int error_code;

		// cppcheck-suppress knownConditionTrueFalse
		if ( g_cdvdfsv_rpc5flg || g_cdvdfsv_rpc3flg || cdvdfsv_cleanuprpc() == 0 )
		{
			return 2;
		}
		CpuSuspendIntr(&state);
		error_code = ReleaseLibraryEntries(&_exp_cdvdfsv);
		CpuResumeIntr(state);
		if ( error_code && error_code != KE_LIBRARY_NOTFOUND )
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
	g_dword_40575C = (int)g_dword_405750;
	g_cdvdfsv_rtocbuf = (char *)cdvdfsv_fsvrbuf;
	cdvdfsv_parseargs(ac, av);
	cdvdfsv_init();
	CpuSuspendIntr(&state);
	LibraryEntryTable = (unsigned __int16 *)QueryLibraryEntryTable(&g_modload_libinfo);
	CpuResumeIntr(state);
	if ( !LibraryEntryTable || (*(LibraryEntryTable - 6) < 0x104) )
	{
		KPRINTF("Warning cdvdfsv.irx: Unload function can't be used.\n");
		return 0;
	}
	return 2;
}

int __cdecl cdvdfsv_init()
{
	const int *BootMode;
	iop_thread_t thparam;
	int scres;

	BootMode = QueryBootMode(3);
	if ( BootMode && (BootMode[1] & 2) != 0 )
	{
		PRINTF(" No cdvd driver \n");
		return 1;
	}
	sceCdSC(0xFFFFFFF2, (int *)&g_cdvdman_istruct_ptr);
	g_scmd_evid = sceCdSC(0xFFFFFFE7, &scres);
	thparam.attr = 0x2000000;
	thparam.thread = cdvdfsv_main_th;
	thparam.stacksize = 0x800;
	thparam.option = 0;
	thparam.priority = g_cdvdfsv_def_pri - 1;
	g_cdvdfsv_thids[0] = CreateThread(&thparam);
	if ( g_cdvdfsv_thids[0] <= 0 )
	{
		return 1;
	}
	StartThread(g_cdvdfsv_thids[0], 0);
	return 0;
}

void __cdecl cdvdfsv_main_th(void *arg)
{
	iop_thread_t thparam1;
	iop_thread_t thparam2;

	(void)arg;

	if ( !sceSifCheckInit() )
		sceSifInit();
	sceSifInitRpc(0);
	PRINTF("cdvd driver module version 0.1.1 (C)SCEI\n");
	thparam2.thread = cdvdfsv_rpc1_th;
	thparam2.attr = 0x2000000;
	thparam2.stacksize = 0x1900;
	thparam2.option = 0;
	thparam2.priority = g_cdvdfsv_def_pri;
	g_cdvdfsv_thids[1] = CreateThread(&thparam2);
	StartThread(g_cdvdfsv_thids[1], 0);
	thparam1.attr = 0x2000000;
	thparam1.thread = cdvdfsv_rpc2_th;
	thparam1.stacksize = 0x1900;
	thparam1.option = 0;
	thparam1.priority = g_cdvdfsv_def_pri;
	g_cdvdfsv_thids[2] = CreateThread(&thparam1);
	StartThread(g_cdvdfsv_thids[2], 0);
	thparam1.thread = cdvdfsv_rpc3_th;
	thparam1.attr = 0x2000000;
	thparam1.stacksize = 0x800;
	thparam1.option = 0;
	thparam1.priority = g_cdvdfsv_def_pri;
	g_cdvdfsv_thids[3] = CreateThread(&thparam1);
	StartThread(g_cdvdfsv_thids[3], 0);
	cdvdfsv_poffloop();
	ExitDeleteThread();
}

int *__fastcall cdvdfsv_4(int arg1)
{
	VERBOSE_PRINTF(1, "Dummy Entry Called\n");
	if ( arg1 != 128 )
		return 0;
	return &g_verbose_level;
}

void __cdecl cdvdfsv_parseargs(int ac, char **av)
{
	int i;

	g_cdvdfsv_def_pri = 81;
	for ( i = 1; i < ac; i += 1 )
	{
		if ( !strncmp(av[i], "thpri=", 6) )
		{
			g_cdvdfsv_def_pri = strtol(av[i] + 6, 0, 10);
			if ( (unsigned int)(g_cdvdfsv_def_pri - 9) >= 0x73 )
			{
				PRINTF("Cdvdfsv:thpri=%d Illegal priority\n", g_cdvdfsv_def_pri);
				g_cdvdfsv_def_pri = 81;
			}
			if ( g_cdvdfsv_def_pri == 9 )
				g_cdvdfsv_def_pri = 10;
		}
	}
}

int __cdecl sceCdChangeThreadPriority(int priority)
{
	iop_thread_info_t thinfo;

	if ( (unsigned int)(priority - 9) >= 0x73 )
		return -403;
	if ( priority == 9 )
		priority = 10;
	ReferThreadStatus(0, &thinfo);
	ChangeThreadPriority(0, 8);
	ChangeThreadPriority(g_cdvdfsv_thids[0], priority - 1);
	ChangeThreadPriority(g_cdvdfsv_thids[2], priority);
	ChangeThreadPriority(g_cdvdfsv_thids[1], priority);
	ChangeThreadPriority(g_cdvdfsv_thids[3], priority);
	return 0;
}

void *__fastcall cbrpc_rpc1_cdinit(int fno, void *buffer, int length)
{
	int scres_unused;

	(void)fno;
	(void)length;

	VERBOSE_PRINTF(1, "sceCdInit call\n");
	sceCdInit(((const cdvdfsv_rpc1h_packet *)buffer)->m_mode);
	g_cdvdfsv_spinctl = -1;
	g_cdvdfsv_initres.m_debug_mode = g_verbose_level ? 254 : 0;
	g_cdvdfsv_initres.m_cdvdfsv_ver = (unsigned __int16)_irx_id.v;
	g_cdvdfsv_initres.m_cdvdman_ver = sceCdSC(0xFFFFFFF7, &scres_unused);
	VERBOSE_PRINTF(1, "sceCdInit end\n");
	g_cdvdfsv_initres.m_retres = 1;
	return (void *)&g_cdvdfsv_initres;
}

void __fastcall cdvdfsv_rpc3h_16_break(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	(void)inbuf;
	(void)buflen;

	VERBOSE_PRINTF(1, "sceCdAbort call\n");
	sceCdBreak();
	outbuf->m_retres = 1;
}

void *__fastcall cbrpc_rpc4_fscall(int fno, void *buffer, int length)
{
	int scres;
	int state;
	cdvdfsv_rpc4h_packet *inbuf;

	(void)fno;

	inbuf = buffer;
	scres = 255;
	sceCdSC(0xFFFFFFF6, &scres);
	VERBOSE_PRINTF(1, "search file name %s call struct_siz %d\n", inbuf->m_pkt_sz12c.m_path, length);
	switch ( length )
	{
		case sizeof(inbuf->m_pkt_sz12c):
			g_cdvdfsv_srchres.m_retres = sceCdLayerSearchFile(&(inbuf->m_pkt_sz12c.m_fp), inbuf->m_pkt_sz12c.m_path, inbuf->m_pkt_sz12c.m_layer);
			g_cdvdfsv_fssdd.src = buffer;
			g_cdvdfsv_fssdd.dest = (void *)inbuf->m_pkt_sz12c.m_eedest;
			g_cdvdfsv_fssdd.size = sizeof(sceCdlFILE) + 4;
			break;
		case sizeof(inbuf->m_pkt_sz128):
			PRINTF("sceCdSearchFile: Called from Not_Dual_layer Version.\n");
			g_cdvdfsv_srchres.m_retres = sceCdSearchFile(&(inbuf->m_pkt_sz128.m_fp), inbuf->m_pkt_sz128.m_path);
			g_cdvdfsv_fssdd.src = buffer;
			g_cdvdfsv_fssdd.dest = (void *)inbuf->m_pkt_sz128.m_eedest;
			g_cdvdfsv_fssdd.size = sizeof(sceCdlFILE) + 4;
			break;
		default:
			PRINTF("Warning sceCdSearchFile: Called from Old liblary.\n");
			g_cdvdfsv_srchres.m_retres = sceCdSearchFile(&(inbuf->m_pkt_sz124.m_fp), inbuf->m_pkt_sz124.m_path);
			g_cdvdfsv_fssdd.src = buffer;
			g_cdvdfsv_fssdd.dest = (void *)inbuf->m_pkt_sz124.m_eedest;
			g_cdvdfsv_fssdd.size = sizeof(sceCdlFILE);
			break;
	}
	g_cdvdfsv_fssdd.attr = 0;
	while ( 1 )
	{
		int trid;

		CpuSuspendIntr(&state);
		trid = sceSifSetDma(&g_cdvdfsv_fssdd, 1);
		CpuResumeIntr(state);
		if ( trid )
			break;
		DelayThread(500);
	}
	scres = 0;
	sceCdSC(0xFFFFFFF6, &scres);
	return (void *)&g_cdvdfsv_srchres;
}

int __fastcall alarm_cb(void *a1)
{
	unsigned int read_to;

	read_to = *(_DWORD *)a1 / 0x9000;
	KPRINTF("Read Time Out %d(msec)\n", read_to);
	sceCdSC(0xFFFFFFEE, (int *)&read_to);
	return sceCdBreak() == 0;
}

void __cdecl cdvdfsv_rpc5h_0D_iopmread(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf)
{
	int cmd_error;
	int trid;
	int scres_unused;
	int error_code;
	int state;

	(void)buflen;
	(void)outbuf;

	g_cdvdfsv_rderror = SCECdErREADCFR;
	g_cdvdfsv_read_to.hi = 0;
	g_cdvdfsv_read_to.lo = 0x9000 * sceCdSC(0xFFFFFFF1, &scres_unused);
	g_cdvdfsv_iomrsdd.src = &g_cdvdfsv_readpos;
	g_cdvdfsv_iomrsdd.size = sizeof(g_cdvdfsv_readpos);
	g_cdvdfsv_iomrsdd.attr = 0;
	g_cdvdfsv_iomrsdd.dest = (void *)inbuf->m_pkt_0D.m_eedest;
	VERBOSE_PRINTF(1, "sceCdReadIOPm addr= 0x%08x sector= %d\n", (unsigned int)(uiptr)(inbuf->m_pkt_0D.m_buf), (int)(inbuf->m_pkt_0D.m_sectors));
	cmd_error = sceCdRE(inbuf->m_pkt_0D.m_lbn, inbuf->m_pkt_0D.m_sectors, inbuf->m_pkt_0D.m_buf, (sceCdRMode *)&inbuf->m_pkt_0D.m_mode);
	while ( sceCdSync(1) )
	{
		g_cdvdfsv_readpos = sceCdGetReadPos();
		while ( 1 )
		{
			CpuSuspendIntr(&state);
			trid = sceSifSetDma(&g_cdvdfsv_iomrsdd, 1);
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
			sceCdSC(0xFFFFFFFE, &g_cdvdfsv_rderror);
		VERBOSE_PRINTF(1, "Read error code %x cmd error %d\n", error_code, cmd_error);
	}
}

u8 __cdecl cdvdfsv_syncdec(int flag, int xorkey, int arg2, u8 data)
{
	return flag ? (((data << (arg2 % 8)) | (data >> (8 - arg2 % 8))) ^ xorkey) : data;
}

int __cdecl cdvdfsv_cb_read()
{
	iSetEventFlag(g_cdvdman_intr_efid, 0x20);
	return 0;
}

int __cdecl cdvdfsv_checksid(u32 lsn, u32 sectors, u32 ps2dvd, void *buf, int decflag, int decshift, u32 *syncdec_mask)
{
	int scret;
	u32 i;
	u32 readlsn;
	int syncdec;
	u8 syncdec_4;
	sceCdlLOCCD rpos;
	int scres;
	int ipi_emu;

	ipi_emu = 0;
	*syncdec_mask = 0;
	scret = decflag ? sceCdSC(0xFFFFFFE8, &scres) : 0;
	syncdec_4 = 0;
	for ( i = 0; i < sectors; i += 1 )
	{
		if ( ps2dvd )
		{
			syncdec = cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 0x810))[3]);
			syncdec += cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 0x810))[2]) << 8;
			syncdec += cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 0x810))[1]) << 16;
			syncdec_4 = cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 0x810))[0]);
			if ( i && !*syncdec_mask )
			{
				ipi_emu = syncdec_4 & 0xC;
			}
			else if ( !i )
			{
				*syncdec_mask = syncdec_4 & 0xC;
			}
			readlsn = syncdec - 0x30000;
			if ( g_cdvdman_istruct_ptr->m_opo_or_para
				&& (lsn + i) >= g_cdvdman_istruct_ptr->m_layer_1_lsn
				&& g_cdvdman_istruct_ptr->m_opo_or_para == 1 )
			{
				readlsn += g_cdvdman_istruct_ptr->m_layer_1_lsn;
			}
		}
		else
		{
			rpos.minute = cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 0x924))[0]);
			rpos.second = cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 0x924))[1]);
			rpos.sector = cdvdfsv_syncdec(decflag, scret, decshift, ((u8 *)buf + (i * 0x924))[2]);
			readlsn = sceCdPosToInt(&rpos);
		}
		if ( readlsn != (lsn + i) || ipi_emu )
		{
			VERBOSE_PRINTF(1, "Read_EE Sector_ID error lsn= %d readlsn= %d layer= %d layer1_start %d\n", (int)(lsn + i), (int)readlsn, (syncdec_4 & 1), (int)(g_cdvdman_istruct_ptr->m_layer_1_lsn));
			return 0;
		}
	}
	if ( *syncdec_mask )
	{
		VERBOSE_PRINTF(1, "Read_EE NO_Data_zone error lsn= %d layer= %d SecID %02x\n", (int)lsn, (syncdec_4 & 1), (int)(*syncdec_mask));
	}
	return 1;
}

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
	unsigned int i;
	int csec;
	int read_res_tmp;
	int trid;
	int j;
	int size_2;
	int sector_sizes[2];
	int error_code;
	int scres_unused;
	int state;
	u32 syncdec_mask;
	u32 chcr;
	int error_code_tmp;
	char *ee_addr_tmp;
	int dmasize_tmp;
	int csec_comm;
	int nsec_div_cdvdfsv_sectors;
	int retry_flag1;
	int retry_flag2;
	int sector_size;

	error_code_tmp = 0;
	sector_sizes[0] = 0x924;
	sector_sizes[1] = 0x810;
	g_cdvdfsv_read_to.hi = 0;
	g_cdvdfsv_read_to.lo = 0x9000 * sceCdSC(0xFFFFFFF1, &scres_unused);
	g_cdvdfsv_rderror = SCECdErREADCF;
	g_cdvdfsv_r2retry = 0;
	g_cdvdfsv_r2count = 0;
	if ( secsize != 0x924 && !fssift )
	{
		for ( i = 0; i < (sizeof(g_cdvdfsv_multi_dmat)/sizeof(g_cdvdfsv_multi_dmat[0])); i += 1 )
		{
			g_cdvdfsv_multi_dmat[i].attr = 0;
			g_cdvdfsv_multi_dmat[i].size = secsize;
		}
	}
	sector_size = sector_sizes[sector_size_selection];
	while ( 1 )
	{
		while ( 1 )
		{
			csec = ( nsec <= (sizeof(g_cdvdfsv_multi_dmat)/sizeof(g_cdvdfsv_multi_dmat[0])) ) ? nsec : (sizeof(g_cdvdfsv_multi_dmat)/sizeof(g_cdvdfsv_multi_dmat[0]));
			nsec_div_cdvdfsv_sectors = (nsec >> 4) + (( (nsec & 0xF) != 0 ) ? 1 : 0);
			retry_flag2 = 0;
			ee_addr_tmp = ee_addr;
			dmasize_tmp = dmasize;
			g_cdvdman_istruct_ptr->m_dec_mode_set = 1;
			g_cdvdman_istruct_ptr->m_dec_mode_last_set = 0;
			CpuSuspendIntr(&state);
			if ( enable_dec_shift )
			{
				g_cdvdman_istruct_ptr->m_dec_shift = dec_shift;
				g_cdvdman_istruct_ptr->m_dec_state = 2;
			}
			if ( g_cdvdfsv_r2retry )
			{
				VERBOSE_KPRINTF(1, "Rty_Read\n");
				read_res_tmp = (sector_size_selection ? sceCdRV : sceCdRead0)(( lsn >= 0x60 ) ? (lsn - 0x10 * g_cdvdfsv_r2retry) : (lsn + 0x10 * g_cdvdfsv_r2retry + 0x60), 0x10, &g_cdvdfsv_rtocbuf[0x1248], mode, 0, 0);
				CpuResumeIntr(state);
			}
			else
			{
				read_res_tmp = (sector_size_selection ? sceCdRV : sceCdRead0)(lsn, nsec, &g_cdvdfsv_rtocbuf[0x1248], mode, csec, cdvdfsv_cb_read);
				CpuResumeIntr(state);
				if ( read_res_tmp )
				{
					SetAlarm(&g_cdvdfsv_read_to, (unsigned int (__cdecl *)(void *))alarm_cb, &g_cdvdfsv_read_to);
					csec_comm = 0;
					retry_flag1 = 0;
					break;
				}
			}
			if ( !read_res_tmp )
			{
				g_cdvdman_istruct_ptr->m_dec_state = 0;
				g_cdvdman_istruct_ptr->m_dec_mode_set = 0;
				sceCdSC(0xFFFFFFFE, &g_cdvdfsv_rderror);
				return 0;
			}
			sceCdSync(3);
			g_cdvdfsv_r2retry -= 1;
		}
		for ( i = 0; (int)i < nsec_div_cdvdfsv_sectors; i += 1 )
		{
			sceCdSync(32);
			if ( g_cdvdman_istruct_ptr->m_dec_mode_last_set )
				break;
			if ( !sceCdGetError() )
			{
				if ( cdvdfsv_checksid(
							 lsn + csec_comm,
							 csec,
							 sector_size_selection,
							 &g_cdvdfsv_rtocbuf[0x1248],
							 enable_dec_shift,
							 dec_shift,
							 &syncdec_mask) )
				{
					if ( do_multi_retries && syncdec_mask && !i )
					{
						retry_flag1 = 1;
						error_code_tmp = SCECdErIPI;
					}
				}
				else if ( do_multi_retries )
				{
					retry_flag2 = 1;
					retry_flag1 = 1;
				}
				if ( retry_flag1 || g_cdvdfsv_r2retry )
				{
				}
				else if ( secsize == 0x924 && !sector_size_selection )
				{
					if ( fssift )
					{
						if ( i )
						{
							optimized_memcpy(&g_cdvdfsv_rtocbuf[secsize], &g_cdvdfsv_rtocbuf[fssift], secsize - fssift);
							optimized_memcpy(g_cdvdfsv_rtocbuf, &g_cdvdfsv_rtocbuf[secsize + secsize * csec], secsize);
							g_cdvdfsv_rdp2sdd.size = ((int)i == nsec_div_cdvdfsv_sectors - 1) ? dmasize_tmp : (secsize * (csec - 1) + fssift);
							optimized_memcpy(&g_cdvdfsv_rtocbuf[secsize + secsize - fssift], &g_cdvdfsv_rtocbuf[secsize * 2], g_cdvdfsv_rdp2sdd.size);
						}
						else
						{
							optimized_memcpy(g_cdvdfsv_rtocbuf, &g_cdvdfsv_rtocbuf[secsize * 2 + secsize * (csec - 1)], secsize);
							g_cdvdfsv_rdp2sdd.size = ((int)i == nsec_div_cdvdfsv_sectors - 1) ? dmasize_tmp : (secsize * (csec - 1));
							optimized_memcpy(&g_cdvdfsv_rtocbuf[secsize], &g_cdvdfsv_rtocbuf[secsize * 2 + fssift], g_cdvdfsv_rdp2sdd.size);
						}
						g_cdvdfsv_rdp2sdd.src = &g_cdvdfsv_rtocbuf[secsize];
					}
					else
					{
						g_cdvdfsv_rdp2sdd.src = &g_cdvdfsv_rtocbuf[secsize * 2];
						g_cdvdfsv_rdp2sdd.size = secsize * csec;
					}
					g_cdvdfsv_rdp2sdd.attr = 0;
					g_cdvdfsv_rdp2sdd.dest = ee_addr_tmp;
					ee_addr_tmp += g_cdvdfsv_rdp2sdd.size;
					dmasize_tmp -= g_cdvdfsv_rdp2sdd.size;
					while ( 1 )
					{
						CpuSuspendIntr(&state);
						trid = sceSifSetDma(&g_cdvdfsv_rdp2sdd, 1);
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
						g_cdvdfsv_multi_dmat[j].dest = &ee_addr[(csec_comm + j) * secsize];
						g_cdvdfsv_multi_dmat[j].src = &g_cdvdfsv_rtocbuf[0x1248 + (j * sector_size) + 12];
					}
					while ( 1 )
					{
						CpuSuspendIntr(&state);
						trid = sceSifSetDma(g_cdvdfsv_multi_dmat, csec);
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
					g_cdvdfsv_rdp2sdd.size = dmasize_tmp;
					if ( i )
					{
						optimized_memcpy(&g_cdvdfsv_rtocbuf[0x924], &g_cdvdfsv_rtocbuf[fssift + 12], secsize - fssift);
						optimized_memcpy(g_cdvdfsv_rtocbuf, &g_cdvdfsv_rtocbuf[0x1248 + (csec - 1) * sector_size], sector_size);
						for ( j = 0; j < csec - 1; j += 1 )
						{
							optimized_memcpy(&g_cdvdfsv_rtocbuf[0x924 + secsize - fssift + (j * secsize)], &g_cdvdfsv_rtocbuf[0x1248 + 12 + (j * sector_size)], secsize);
						}
						optimized_memcpy(&g_cdvdfsv_rtocbuf[0x924 + secsize - fssift + ((csec - 1) * secsize)], &g_cdvdfsv_rtocbuf[0x1248 + 12 + ((csec - 1) * sector_size)], size_2);
						if ( (int)i != nsec_div_cdvdfsv_sectors - 1 )
						{
							g_cdvdfsv_rdp2sdd.size = secsize * csec;
						}
					}
					else
					{
						optimized_memcpy(g_cdvdfsv_rtocbuf, &g_cdvdfsv_rtocbuf[0x1248 + (csec - 1) * sector_size], sector_size);
						optimized_memcpy(&g_cdvdfsv_rtocbuf[0x924], &g_cdvdfsv_rtocbuf[0x1248 + fssift + 12], secsize - fssift);
						for ( j = 0; j < csec - 2; j += 1 )
						{
							optimized_memcpy(&g_cdvdfsv_rtocbuf[0x924 + secsize - fssift + (j * secsize)], &g_cdvdfsv_rtocbuf[0x1248 + sector_size + 12 + (j * sector_size)], secsize);
						}
						optimized_memcpy(&g_cdvdfsv_rtocbuf[0x924 + secsize - fssift + ((csec - 2) * secsize)], &g_cdvdfsv_rtocbuf[0x1248 + sector_size + 12 + ((csec - 2) * sector_size)], size_2);
						if ( (int)i != nsec_div_cdvdfsv_sectors - 1 )
						{
							g_cdvdfsv_rdp2sdd.size = secsize * (csec - 1);
						}
					}
					g_cdvdfsv_rdp2sdd.src = &g_cdvdfsv_rtocbuf[0x924];
					g_cdvdfsv_rdp2sdd.attr = 0;
					g_cdvdfsv_rdp2sdd.dest = ee_addr_tmp;
					ee_addr_tmp += g_cdvdfsv_rdp2sdd.size;
					dmasize_tmp -= g_cdvdfsv_rdp2sdd.size;
					while ( 1 )
					{
						CpuSuspendIntr(&state);
						trid = sceSifSetDma(&g_cdvdfsv_rdp2sdd, 1);
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
				DisableIntr(IOP_IRQ_DMA_CDVD, (int *)&chcr);
			}
			else
			{
				csec_comm = csec_comm + csec;
				csec = ( (unsigned int)csec > nsec - (unsigned int)csec_comm ) ? (nsec - (unsigned int)csec_comm) : (sizeof(g_cdvdfsv_multi_dmat)/sizeof(g_cdvdfsv_multi_dmat[0]));
				ClearEventFlag(g_cdvdman_intr_efid, ~0x20);
				dmac_ch_set_chcr(3, 0);
				dmac_ch_get_chcr(3);
				g_cdvdman_istruct_ptr->m_dma3prm.m_dma3_maddress = &g_cdvdfsv_rtocbuf[0x1248];
				dmac_ch_set_madr(3, (uiptr)(&g_cdvdfsv_rtocbuf[0x1248]));
				dmac_ch_set_bcr(
					3,
					g_cdvdman_istruct_ptr->m_dma3prm.m_dma3_blkwords | ((g_cdvdman_istruct_ptr->m_dma3prm.m_dma3_blkcount
																																			 * csec) << 16));
				dmac_ch_set_chcr(3, 0x41000200);
				chcr = dmac_ch_get_chcr(3);
				if ( post_dmat )
				{
					g_cdvdfsv_readpos += secsize * csec;
					sceSifSetDma(post_dmat, 1);
				}
			}
			CpuResumeIntr(state);
		}
		sceCdSync(5);
		CancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &g_cdvdfsv_read_to);
		g_cdvdman_istruct_ptr->m_dec_mode_set = 0;
		g_cdvdman_istruct_ptr->m_dec_state = 0;
		error_code = sceCdGetError();
		if ( (unsigned __int16)g_cdvdman_istruct_ptr->m_dec_mode_last_set )
		{
			retry_flag2 = 1;
			error_code = 0;
			mode->spindlctrl = 16;
		}
		if ( error_code || g_cdvdfsv_r2count >= 5 )
			break;
		if ( !retry_flag2 )
		{
			if ( !error_code_tmp )
				return 1;
			sceCdSC(0xFFFFFFFE, &error_code_tmp);
			VERBOSE_KPRINTF(1, "secid_chk_ee_trns lsn %d nsec %d IPI Err\n", lsn, nsec);
			return 0;
		}
		if ( !g_cdvdfsv_r2retry )
		{
			g_cdvdfsv_r2count += 1;
			VERBOSE_PRINTF(1, "Read_CD/DVD-ROM Error Recover Start\n");
			g_cdvdfsv_r2retry = 3;
		}
	}
	if ( g_cdvdfsv_r2count >= 5 && !error_code )
	{
		sceCdSC(0xFFFFFFFE, &g_cdvdfsv_rderror);
	}
	return 0;
}

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
	int error_code;
	int scres_unused;
	int state;
	u32 syncdec_mask;
	int error_code_tmp;

	error_code_tmp = 0;
	g_cdvdfsv_read_to.hi = 0;
	g_cdvdfsv_read_to.lo = 0x9000 * sceCdSC(0xFFFFFFF1, &scres_unused);
	g_cdvdfsv_rderror = SCECdErREADCF;
	g_cdvdfsv_sid_err_recover_cnt = 0;
	g_cdvdfsv_err_count = 0;
	while ( 1 )
	{
		int cmd_error;

		CpuSuspendIntr(&state);
		if ( dec_shift_enable )
		{
			g_cdvdman_istruct_ptr->m_dec_shift = dec_shift_value;
			g_cdvdman_istruct_ptr->m_dec_state = 2;
		}
		cmd_error = (ps2dvd ? sceCdRV : sceCdRead0)(( lsn >= 0x30 ) ? (lsn - 0x10 * g_cdvdfsv_sid_err_recover_cnt) : (lsn + 0x10 * g_cdvdfsv_sid_err_recover_cnt), nsec, retptr, rmode, 0, 0);
		CpuResumeIntr(state);
		if ( cmd_error )
			SetAlarm(&g_cdvdfsv_read_to, (unsigned int (__cdecl *)(void *))alarm_cb, &g_cdvdfsv_read_to);
		sceCdSync(5);
		CancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &g_cdvdfsv_read_to);
		g_cdvdman_istruct_ptr->m_dec_state = 0;
		error_code = sceCdGetError();
		if ( error_code || !cmd_error || g_cdvdfsv_err_count >= 5 )
		{
			VERBOSE_KPRINTF(1, "Read error error code %x cmd error %d\n", error_code, cmd_error);
			if ( (!cmd_error || g_cdvdfsv_err_count >= 5) && (!error_code) )
			{
				sceCdSC(0xFFFFFFFE, &g_cdvdfsv_rderror);
			}
			return 0;
		}
		if ( cdvdfsv_checksid(lsn, nsec, ps2dvd, retptr, dec_shift_enable, dec_shift_value, &syncdec_mask) )
		{
			if ( enable_retries && syncdec_mask )
				error_code_tmp = SCECdErIPI;
			break;
		}
		if ( !enable_retries )
			break;
		if ( !g_cdvdfsv_sid_err_recover_cnt )
		{
			g_cdvdfsv_err_count += 1;
			VERBOSE_PRINTF(1, "Read_CD/DVD-ROM Sector_ID Error Recover Start\n");
			g_cdvdfsv_sid_err_recover_cnt = 3;
		}
		g_cdvdfsv_sid_err_recover_cnt -= 1;
	}
	if ( !error_code_tmp )
		return 1;
	sceCdSC(0xFFFFFFFE, &error_code_tmp);
	VERBOSE_KPRINTF(1, "secid_chk lsn %d nsec %d IPI Err\n", lsn, nsec);
	return 0;
}

void __cdecl cdvdfsv_rpc5h_01_readee(
				const cdvdfsv_rpc5h_packet *inbuf,
				int buflen,
				cdvdfsv_rpc5h_outpacket *outbuf,
				u32 ps2dvd,
				int sync,
				int decflag)
{
	unsigned int secsize;
	unsigned int bsize;
	unsigned int bsize_tmp;
	unsigned int psize;
	unsigned int ssize;
	unsigned int i;
	int sizestuff;
	u32 needed_offset;
	int sector_sizes[2];
	int scres_unused;
	int lsndualchg_res;
	int state;
	unsigned int buf_offs_sum;
	unsigned int paddr;
	int saddr;
	int datapattern;
	unsigned int len2_plus_sec2;
	int trid;
	int decval;
	int early_break;

	(void)buflen;

	early_break = 0;
	trid = 0;
	buf_offs_sum = 0;
	sector_sizes[0] = 0x924;
	sector_sizes[1] = 0x810;
	g_cdvdfsv_rmodeee = inbuf->m_pkt_01.m_rmodeee;
	lsndualchg_res = inbuf->m_pkt_01.m_lbn;
	decval = decflag ? inbuf->m_pkt_01.m_decval : 0;
	g_cdvdfsv_eerpsdd.src = &g_cdvdfsv_readpos;
	g_cdvdfsv_eerpsdd.size = sizeof(g_cdvdfsv_readpos);
	g_cdvdfsv_eerpsdd.attr = 0;
	g_cdvdfsv_eerpsdd.dest = (void *)inbuf->m_pkt_01.m_eedest;
	if ( ps2dvd )
	{
		if ( !sceCdSC(0xFFFFFFEA, &scres_unused) )
		{
			g_cdvdfsv_rderror = SCECdErREADCFR;
			sceCdSC(0xFFFFFFFE, &g_cdvdfsv_rderror);
			bsize = 0;
			psize = 0;
			ssize = 0;
			saddr = 0;
			paddr = 0;
			early_break = 1;
		}
		else
		{
			lsndualchg_res = sceCdSC(0xFFFFFFE9, &lsndualchg_res);
			secsize = 0x800;
			datapattern = SCECdSecS2048;
			g_cdvdfsv_rmodeee.datapattern = SCECdSecS2048;
		}
	}
	else
	{
		datapattern = g_cdvdfsv_rmodeee.datapattern;
		switch ( datapattern )
		{
			case SCECdSecS2328:
				secsize = 0x918;
				break;
			case SCECdSecS2340:
				secsize = 0x924;
				break;
			case SCECdSecS2048:
			default:
				secsize = 0x800;
				break;
		}
		g_cdvdfsv_rmodeee.datapattern = SCECdSecS2340;
	}
	len2_plus_sec2 = lsndualchg_res + inbuf->m_pkt_01.m_sectors;
	if ( !early_break )
	{
		int all_sec_bytes;

		all_sec_bytes = secsize * inbuf->m_pkt_01.m_sectors;
		if ( g_cdvdfsv_spinctl != -1 )
			g_cdvdfsv_rmodeee.spindlctrl = g_cdvdfsv_spinctl;
		paddr = inbuf->m_pkt_01.m_paddr;
		saddr = (paddr + all_sec_bytes) & ~0x3F;
		psize = ( (paddr & 0x3F) != 0 ) ? ((paddr & ~0x3F) - (paddr - 0x40)) : 0;
		bsize = saddr - (paddr + psize);
		ssize = paddr + all_sec_bytes - saddr;
		VERBOSE_KPRINTF(1, "CD/DVD-ROM lsn= %d sec= %d\n", lsndualchg_res, inbuf->m_pkt_01.m_sectors);
		VERBOSE_KPRINTF(1, "f psize= %d bsize= %d ssize= %d\n", psize, bsize, ssize);
	}
	if ( psize )
	{
		u32 sectors;

		sectors = ( len2_plus_sec2 < lsndualchg_res + buf_offs_sum / secsize + 2 ) ? 1 : 2;
		VERBOSE_PRINTF(1, "0 CD_READ LBN= %d sectors= %d all= %d\n", (int)(lsndualchg_res + buf_offs_sum / secsize), (int)sectors, (int)inbuf->m_pkt_01.m_sectors);
		if ( !readproc1(
						lsndualchg_res + buf_offs_sum / secsize,
						sectors,
						g_cdvdfsv_rtocbuf,
						&g_cdvdfsv_rmodeee,
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
			if ( datapattern != SCECdSecS2340 || ps2dvd )
			{
				int rtoc_ind;

				rtoc_ind = 12;
				for ( i = 0; i < psize; i += 1 )
				{
					rtoc_ind += ( i && !(i % secsize) ) ? (sector_sizes[ps2dvd] - secsize) : 0;
					g_cdvdfsv_eereadx.m_pbuf1[i] = g_cdvdfsv_rtocbuf[rtoc_ind + i];
				}
			}
			else
			{
				for ( i = 0; i < psize; i += 1 )
					g_cdvdfsv_eereadx.m_pbuf1[i] = g_cdvdfsv_rtocbuf[i];
			}
			buf_offs_sum += psize;
		}
	}
	bsize_tmp = bsize;
	for ( i = 0; i < bsize; i += sizestuff )
	{
		u32 offs_sector_only;

		bsize_tmp = bsize - i;
		if ( g_cdvdfsv_spinctl != -1 )
			g_cdvdfsv_rmodeee.spindlctrl = g_cdvdfsv_spinctl;
		offs_sector_only = lsndualchg_res + buf_offs_sum / secsize;
		if ( (unsigned int)(secsize << 6) >= bsize_tmp )
		{
			needed_offset = (bsize_tmp / secsize) + (( bsize_tmp % secsize ) ? 1 : 0);
			sizestuff = bsize_tmp;
		}
		else
		{
			needed_offset = ( ((offs_sector_only & 0xF) != 0) && ((secsize & 0xF) == 0) ) ? (0x10 - (offs_sector_only & 0xF)) : 0x40;
			sizestuff = secsize * needed_offset;
		}
		needed_offset += ( (buf_offs_sum + i) % secsize ) ? 1 : 0;
		if ( len2_plus_sec2 < offs_sector_only + needed_offset )
			needed_offset = len2_plus_sec2 - (lsndualchg_res + (buf_offs_sum + i) / secsize);
		g_cdvdfsv_readpos = buf_offs_sum + i;
		if ( !readproc2(
						offs_sector_only,
						needed_offset,
						&g_cdvdfsv_rmodeee,
						ps2dvd,
						sync,
						decflag,
						decval,
						(char *)(inbuf->m_pkt_01.m_paddr + psize) + i,
						(buf_offs_sum + i) % secsize,
						secsize,
						sizestuff,
						&g_cdvdfsv_eerpsdd) )
		{
			bsize_tmp = 0;
			early_break = 1;
			break;
		}
		while ( cdvdfsv_checkdmastat(trid) >= 0 )
			;
		CpuSuspendIntr(&state);
		trid = sceSifSetDma(&g_cdvdfsv_eerpsdd, 1);
		CpuResumeIntr(state);
	}
	buf_offs_sum += i;
	bsize = bsize_tmp;
	if ( !early_break && ssize )
	{
		u32 sectors_1;
		unsigned int buf_offs_sum_bytes_in_sector;

		buf_offs_sum_bytes_in_sector = buf_offs_sum % secsize;
		sectors_1 = ( len2_plus_sec2 < lsndualchg_res + buf_offs_sum / secsize + 2 ) ? 1 : 2;
		VERBOSE_PRINTF(1, "2 CD_READ LBN= %d sectors= %d\n", (int)(lsndualchg_res + buf_offs_sum / secsize), (int)sectors_1);
		if ( !readproc1(
						lsndualchg_res + buf_offs_sum / secsize,
						sectors_1,
						g_cdvdfsv_rtocbuf,
						&g_cdvdfsv_rmodeee,
						ps2dvd,
						sync,
						decflag,
						decval) )
		{
			bsize = 0;
		}
		else
		{
			if ( datapattern != SCECdSecS2340 || ps2dvd )
			{
				int i2_offs;

				i2_offs = 12;
				for ( i = 0; i < ssize; i += 1 )
				{
					i2_offs += ( (i + buf_offs_sum_bytes_in_sector) && (i % secsize) == (secsize - (buf_offs_sum_bytes_in_sector ? buf_offs_sum_bytes_in_sector : secsize)) ) ? (sector_sizes[ps2dvd] - secsize) : 0;
					g_cdvdfsv_eereadx.m_pbuf2[i] = g_cdvdfsv_rtocbuf[buf_offs_sum_bytes_in_sector + i2_offs + i];
				}
			}
			else
			{
				for ( i = 0; i < ssize; i += 1 )
					g_cdvdfsv_eereadx.m_pbuf2[i] = g_cdvdfsv_rtocbuf[buf_offs_sum_bytes_in_sector + i];
			}
			buf_offs_sum += ssize;
		}
	}
	g_cdvdfsv_eereadx.m_b1len = psize;
	g_cdvdfsv_eereadx.m_b2len = ssize;
	g_cdvdfsv_eereadx.m_b1dst = paddr;
	g_cdvdfsv_eereadx.m_b2dst = saddr;
	VERBOSE_PRINTF(1, "b psize= %d paddr= %08x bsize= %d ssize= %d saddr %08x\n", (int)psize, paddr, (int)bsize, (int)ssize, saddr);
	while ( cdvdfsv_checkdmastat(trid) >= 0 )
		;
	g_cdvdfsv_datasdd.src = &g_cdvdfsv_eereadx;
	g_cdvdfsv_datasdd.size = sizeof(g_cdvdfsv_eereadx);
	g_cdvdfsv_datasdd.attr = 0;
	g_cdvdfsv_readpos = buf_offs_sum;
	g_cdvdfsv_datasdd.dest = (void *)inbuf->m_pkt_01.m_eeremaindest;
	while ( 1 )
	{
		CpuSuspendIntr(&state);
		trid = sceSifSetDma(&g_cdvdfsv_datasdd, 1);
		sceSifSetDma(&g_cdvdfsv_eerpsdd, 1);
		CpuResumeIntr(state);
		if ( trid )
			break;
		DelayThread(500);
	}
	while ( cdvdfsv_checkdmastat(trid) >= 0 )
		;
	g_cdvdfsv_spinctl = -1;
	VERBOSE_PRINTF(1, "read end\n");
	outbuf->m_retres = buf_offs_sum;
}

int __fastcall cdvdfsv_chreadee(
				int secoffs,
				int seccount,
				char *ee_addr,
				const sceCdRMode *in_rmode,
				u32 disktype_14,
				int sync)
{
	unsigned int secsize;
	unsigned int i;
	int readsize_bytes;
	sceCdRMode rmode;
	int scres_unused;
	int lsndualchg_res;

	lsndualchg_res = secoffs;
	rmode = *in_rmode;
	if ( disktype_14 )
	{
		if ( !sceCdSC(0xFFFFFFEA, &scres_unused) )
		{
			g_cdvdfsv_rderror = SCECdErREADCFR;
			sceCdSC(0xFFFFFFFE, &g_cdvdfsv_rderror);
			return 1;
		}
		secsize = 0x800;
		lsndualchg_res = sceCdSC(0xFFFFFFE9, &lsndualchg_res);
		rmode.datapattern = SCECdSecS2048;
	}
	else
	{
		switch ( rmode.datapattern )
		{
			case SCECdSecS2328:
				secsize = 0x918;
				break;
			case SCECdSecS2340:
				secsize = 0x924;
				break;
			case SCECdSecS2048:
			default:
				secsize = 0x800;
				break;
		}
		rmode.datapattern = SCECdSecS2340;
	}
	for ( i = 0; i < (unsigned int)(secsize * seccount); i += readsize_bytes )
	{
		unsigned int bytescount;
		int sectors_partial;
		int bytescount_in_sectors;

		bytescount = (unsigned int)(secsize * seccount) - i;
		sectors_partial = (lsndualchg_res + i / secsize) & 0xF;
		bytescount_in_sectors = 0x10;
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
											lsndualchg_res + i / secsize,
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

void __fastcall cdvdfsv_rpc5h_0F_readchain(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf)
{
	int sector_size;
	unsigned int i;
	const sceCdRChain *chain;
	void *buf;
	int re_result;
	int trid;
	int scres_unused;
	int state;

	(void)buflen;
	(void)outbuf;

	g_cdvdfsv_rderror = SCECdErREADCFR;
	g_cdvdfsv_readpos = 0;
	g_cdvdman_istruct_ptr->m_break_cdvdfsv_readchain = 0;
	g_cdvdfsv_chrdsdd.src = &g_cdvdfsv_readpos;
	g_cdvdfsv_chrdsdd.size = sizeof(g_cdvdfsv_readpos);
	g_cdvdfsv_chrdsdd.attr = 0;
	g_cdvdfsv_chrdsdd.dest = (void *)inbuf->m_pkt_0F.m_eedest;
	switch ( inbuf->m_pkt_0F.m_mode.datapattern )
	{
		case SCECdSecS2328:
			sector_size = 0x918;
			break;
		case SCECdSecS2340:
			sector_size = 0x924;
			break;
		case SCECdSecS2048:
		default:
			sector_size = 0x800;
			break;
	}
	chain = inbuf->m_pkt_0F.m_readChain;
	for ( i = 0; i < 0x40; i += 1 )
	{
		if ( g_cdvdman_istruct_ptr->m_break_cdvdfsv_readchain )
		{
			VERBOSE_PRINTF(1, "ReadChain cnt %d on sceCdBreak()\n", (int)i);
			return;
		}
		if ( chain[i].lbn == 0xFFFFFFFF || chain[i].sectors == 0xFFFFFFFF || chain[i].buffer == 0xFFFFFFFF )
			return;
		if ( (chain[i].buffer & 1) != 0 )
		{
			buf = (void *)(chain[i].buffer & ~1);
			VERBOSE_PRINTF(1, "ReadChain lsn= %d nsec= %d buf= %08x secsize= %d\n", (int)(chain[i].lbn), (int)(chain[i].sectors), (unsigned int)(uiptr)buf, inbuf->m_pkt_0F.m_mode.datapattern);
			re_result = sceCdRE(chain[i].lbn, chain[i].sectors, buf, (sceCdRMode *)&(inbuf->m_pkt_0F.m_mode));
			if ( re_result == 1 )
			{
				sceCdSync(0);
				re_result = sceCdGetError() == 0;
			}
			else
			{
				sceCdSC(0xFFFFFFFE, &g_cdvdfsv_rderror);
			}
		}
		else
		{
			VERBOSE_PRINTF(1, "ReadChain EE  Memory addr= 0x%08x sector= %d\n", (unsigned int)(chain[i].lbn), (int)(chain[i].sectors));
			// The following call to sceCdGetDiskType was inlined
			re_result = cdvdfsv_chreadee(chain[i].lbn, chain[i].sectors, (char *)chain[i].buffer, &(inbuf->m_pkt_0F.m_mode), sceCdGetDiskType() == SCECdPS2DVD, sceCdSC(0xFFFFFFFC, &scres_unused) == 0);
		}
		if ( !re_result )
		{
			VERBOSE_PRINTF(1, "ReadChain error code= 0x%02x\n", sceCdGetError());
			break;
		}
		g_cdvdfsv_readpos += chain[i].sectors * sector_size;
		while ( 1 )
		{
			CpuSuspendIntr(&state);
			trid = sceSifSetDma(&g_cdvdfsv_chrdsdd, 1);
			CpuResumeIntr(state);
			if ( trid )
				break;
			DelayThread(500);
		}
		while ( cdvdfsv_checkdmastat(trid) >= 0 )
			;
	}
}

void __fastcall cdvdfsv_rpc5h_02_readcdda(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf)
{
	int trid1;
	unsigned int sector_size;
	int all_sec_bytes;
	unsigned int buf_1_toalign;
	int cmd_error;
	int error_code;
	unsigned int i;
	int trid2;
	int state;
	int error_code_tmp;
	unsigned int buf_offs;
	unsigned int buf_toalign;
	unsigned int buf_sec_tmp;
	unsigned int lbn_1_end;

	trid1 = 0;
	g_cdvdfsv_rderror = SCECdErREADCFR;
	error_code_tmp = 0;
	g_cdvdfsv_eereadfull_dma2.src = &g_cdvdfsv_readpos;
	g_cdvdfsv_eereadfull_dma2.size = sizeof(g_cdvdfsv_readpos);
	g_cdvdfsv_eereadfull_dma2.attr = 0;
	g_cdvdfsv_eereadfull_dma2.dest = (void *)inbuf->m_pkt_02.m_eedest;
	switch ( inbuf->m_pkt_02.m_mode.datapattern )
	{
		case SCECdSecS2368:
			sector_size = 0x940;
			break;
		case SCECdSecS2352:
		case SCECdSecS2448:
		default:
			sector_size = 0x930;
			break;
	}
	buf_offs = 0;
	all_sec_bytes = sector_size * inbuf->m_pkt_02.m_sectors;
	lbn_1_end = inbuf->m_pkt_02.m_lbn + inbuf->m_pkt_02.m_sectors;
	buf_toalign = ( (inbuf->m_pkt_02.m_buf & 0x3F) != 0 ) ? ((inbuf->m_pkt_02.m_buf & ~0x3F) - (inbuf->m_pkt_02.m_buf - 0x40)) : 0;
	buf_1_toalign = (inbuf->m_pkt_02.m_buf + all_sec_bytes) & ~0x3F;
	buf_sec_tmp = all_sec_bytes - (buf_1_toalign - inbuf->m_pkt_02.m_buf);
	if ( buf_toalign )
	{
		unsigned int buf_offs_sectors;
		u32 sectors_1;

		buf_offs_sectors = buf_offs / sector_size;
		sectors_1 = ( lbn_1_end < inbuf->m_pkt_02.m_lbn + buf_offs / sector_size + 2 ) ? 1 : 2;
		VERBOSE_PRINTF(1, "0 CD_READ LBN= %d sectors= %d all= %d\n", (int)(inbuf->m_pkt_02.m_lbn + buf_offs_sectors), (int)sectors_1, (int)inbuf->m_pkt_02.m_sectors);
		cmd_error = sceCdReadCDDA(inbuf->m_pkt_02.m_lbn + buf_offs_sectors, sectors_1, g_cdvdfsv_rtocbuf, (sceCdRMode *)&inbuf->m_pkt_02.m_mode);
		sceCdSync(3);
		error_code = sceCdGetError();
		if ( error_code || !cmd_error )
		{
			if ( !cmd_error )
				sceCdSC(0xFFFFFFFE, &g_cdvdfsv_rderror);
			VERBOSE_PRINTF(1, "Read error code %x cmd error %d\n", error_code, cmd_error);
			if ( error_code == SCECdErEOM || error_code == SCECdErSFRMTNG )
				error_code_tmp = error_code;
			else
			{
				buf_toalign = 0;
			}
		}
		if ( error_code_tmp != 0 && error_code_tmp != SCECdErEOM && error_code_tmp != SCECdErSFRMTNG )
		{
			for ( i = 0; i < buf_toalign; i += 1 )
			{
				g_cdvdfsv_eereadx.m_pbuf1[i] = g_cdvdfsv_rtocbuf[i];
			}
			buf_offs += buf_toalign;
		}
	}
	if ( error_code_tmp != 0 && error_code_tmp != SCECdErEOM && error_code_tmp != SCECdErSFRMTNG )
	{
		unsigned int sector_count_in_bytes;
		unsigned int buf_aligned;

		for ( buf_aligned = inbuf->m_pkt_02.m_buf + buf_toalign; buf_aligned < buf_1_toalign; buf_aligned += sector_count_in_bytes )
		{
			unsigned int buf_align_remain;
			unsigned int buf_offs_mod_sector_size;
			u32 lsn_2;
			u32 sector_count;

			buf_align_remain = buf_1_toalign - buf_aligned;
			buf_offs_mod_sector_size = buf_offs % sector_size;
			lsn_2 = inbuf->m_pkt_02.m_lbn + buf_offs / sector_size;
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
			cmd_error = sceCdReadCDDA(lsn_2, sector_count, g_cdvdfsv_rtocbuf, (sceCdRMode *)&inbuf->m_pkt_02.m_mode);
			sceCdSync(3);
			error_code = sceCdGetError();
			if ( error_code || !cmd_error )
			{
				if ( !cmd_error )
					sceCdSC(0xFFFFFFFE, &g_cdvdfsv_rderror);
				VERBOSE_PRINTF(1, "Read error code %x cmd error %d\n", error_code, cmd_error);
				if ( error_code == SCECdErEOM || error_code == SCECdErSFRMTNG )
				{
					error_code_tmp = error_code;
					break;
				}
			}
			if ( buf_offs_mod_sector_size )
				optimized_memcpy(g_cdvdfsv_rtocbuf, &g_cdvdfsv_rtocbuf[buf_offs_mod_sector_size], sector_count_in_bytes);
			g_cdvdfsv_eereadfull_dma1.src = g_cdvdfsv_rtocbuf;
			g_cdvdfsv_eereadfull_dma1.size = sector_count_in_bytes;
			g_cdvdfsv_eereadfull_dma1.attr = 0;
			g_cdvdfsv_eereadfull_dma1.dest = (char *)buf_aligned;
			g_cdvdfsv_readpos = buf_offs;
			while ( 1 )
			{
				CpuSuspendIntr(&state);
				trid1 = sceSifSetDma(&g_cdvdfsv_eereadfull_dma1, 1);
				CpuResumeIntr(state);
				if ( trid1 )
					break;
				DelayThread(500);
			}
			if ( (unsigned int)buflen >= 0x19 )
			{
				CpuSuspendIntr(&state);
				sceSifSetDma(&g_cdvdfsv_eereadfull_dma2, 1);
				CpuResumeIntr(state);
			}
			buf_offs += sector_count_in_bytes;
		}
	}
	if ( (error_code_tmp != 0 && error_code_tmp != SCECdErEOM && error_code_tmp != SCECdErSFRMTNG) && buf_sec_tmp )
	{
		u32 sectors_3;
		u32 lsn_3;

		lsn_3 = inbuf->m_pkt_02.m_lbn + buf_offs / sector_size;
		sectors_3 = ( lbn_1_end < lsn_3 + 2 ) ? 1 : 2;
		VERBOSE_PRINTF(1, "0 CD_READ LBN= %d sectors= %d all= %d\n", (int)(inbuf->m_pkt_02.m_lbn + buf_offs / sector_size), (int)sectors_3, (int)inbuf->m_pkt_02.m_sectors);
		VERBOSE_PRINTF(1, "2 CD_READ LBN= %d sectors= %d\n", (int)lsn_3, (int)sectors_3);
		cmd_error = sceCdReadCDDA(lsn_3, sectors_3, g_cdvdfsv_rtocbuf, (sceCdRMode *)&inbuf->m_pkt_02.m_mode);
		sceCdSync(3);
		error_code = sceCdGetError();
		if ( error_code || !cmd_error )
		{
			if ( !cmd_error )
				sceCdSC(0xFFFFFFFE, &g_cdvdfsv_rderror);
			VERBOSE_PRINTF(1, "Read error code %x cmd error %d\n", error_code, cmd_error);
			if ( error_code == SCECdErEOM || error_code == SCECdErSFRMTNG )
				error_code_tmp = error_code;
			else
				buf_sec_tmp = 0;
		}
		for ( i = 0; i < buf_sec_tmp; i += 1 )
		{
			g_cdvdfsv_eereadx.m_pbuf2[i] = g_cdvdfsv_rtocbuf[(buf_offs % sector_size) + i];
		}
		buf_offs += buf_sec_tmp;
	}
	g_cdvdfsv_eereadx.m_b1len = buf_toalign;
	g_cdvdfsv_eereadx.m_b2len = buf_sec_tmp;
	g_cdvdfsv_eereadx.m_b1dst = inbuf->m_pkt_02.m_buf;
	g_cdvdfsv_eereadx.m_b2dst = buf_1_toalign;
	while ( cdvdfsv_checkdmastat(trid1) >= 0 )
		;
	g_cdvdfsv_eereadfull_dma1.src = &g_cdvdfsv_eereadx;
	g_cdvdfsv_eereadfull_dma1.size = sizeof(g_cdvdfsv_eereadx);
	g_cdvdfsv_eereadfull_dma1.attr = 0;
	g_cdvdfsv_readpos = buf_offs;
	g_cdvdfsv_eereadfull_dma1.dest = (void *)inbuf->m_pkt_02.m_eeremaindest;
	while ( 1 )
	{
		CpuSuspendIntr(&state);
		trid2 = sceSifSetDma(&g_cdvdfsv_eereadfull_dma1, 1);
		if ( (unsigned int)buflen >= 0x19 )
			sceSifSetDma(&g_cdvdfsv_eereadfull_dma2, 1);
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
	outbuf->m_retres = buf_offs;
}

void *__fastcall cbrpc_rpc2_diskready(int fno, void *buffer, int length)
{
	(void)fno;
	(void)length;

	// The following call to sceCdStatus was inlined
	VERBOSE_KPRINTF(1, "DISK READY call 0x%02x\n", sceCdStatus());
	// The following call to sceCdDiskReady was inlined
	g_diskready_res.m_retres = sceCdDiskReady(((const cdvdfsv_rpc2h_packet *)buffer)->m_mode);
	return (void *)&g_diskready_res;
}

void __fastcall cdvdfsv_rpc5h_04_gettoc(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf)
{
	int trid;
	int state;

	(void)buflen;

	VERBOSE_PRINTF(1, "GET TOC call 0x%08x\n", (int)inbuf);
	outbuf->m_retres = sceCdGetToc((u8 *)g_cdvdfsv_rtocbuf);
	VERBOSE_PRINTF(1, "GET TOC called\n");
	g_cdvdfsv_rtocsdd.src = g_cdvdfsv_rtocbuf;
	g_cdvdfsv_rtocsdd.size = 0x810;
	g_cdvdfsv_rtocsdd.attr = 0;
	g_cdvdfsv_rtocsdd.dest = (void *)inbuf->m_pkt_04.m_eedest;
	while ( 1 )
	{
		CpuSuspendIntr(&state);
		trid = sceSifSetDma(&g_cdvdfsv_rtocsdd, 1);
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
		case SCECdPS2DVD:
		case SCECdDVDVR:
		case SCECdDVDV:
			outbuf->m_pkt_04.m_isdvd = 1;
			break;
		default:
			outbuf->m_pkt_04.m_isdvd = 0;
			break;
	}
}

void __fastcall cdvdfsv_rpc3h_03_disktype(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	(void)inbuf;
	(void)buflen;

	outbuf->m_retres = sceCdGetDiskType();
}

void __fastcall cdvdfsv_rpc3h_0C_cdstatus(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	(void)inbuf;
	(void)buflen;

	outbuf->m_retres = sceCdStatus();
}

void __cdecl cdvdfsv_rpc3h_06_ri(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	int i;
	u32 efbits;

	(void)inbuf;
	(void)buflen;

	outbuf->m_retres = 0;
	for ( i = 0; i < 3 && !outbuf->m_retres; i += 1 )
	{
		WaitEventFlag(g_scmd_evid, 1, 0, &efbits);
		outbuf->m_retres = sceCdRI(outbuf->m_pkt_06.m_buffer, &outbuf->m_pkt_06.m_result);
	}
}

void __cdecl cdvdfsv_rpc3h_1A_rm(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	int i;
	u32 efbits;

	(void)inbuf;
	(void)buflen;

	outbuf->m_retres = 0;
	for ( i = 0; i < 3 && !outbuf->m_retres; i += 1 )
	{
		WaitEventFlag(g_scmd_evid, 1, 0, &efbits);
		outbuf->m_retres = sceCdRM(outbuf->m_pkt_1A.m_buffer, &outbuf->m_pkt_1A.m_status);
	}
}

void __cdecl cdvdfsv_rpc3h_24_readguid(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	int i;
	u32 efbits;

	(void)inbuf;
	(void)buflen;

	outbuf->m_retres = 0;
	for ( i = 0; i < 3 && !outbuf->m_retres; i += 1 )
	{
		WaitEventFlag(g_scmd_evid, 1, 0, &efbits);
		outbuf->m_retres = sceCdReadGUID(&outbuf->m_pkt_24.m_guid);
	}
}

void __cdecl cdvdfsv_rpc3h_26_readmodelid(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	int i;
	u32 efbits;

	(void)inbuf;
	(void)buflen;

	outbuf->m_retres = 0;
	for ( i = 0; i < 3 && !outbuf->m_retres; i += 1 )
	{
		WaitEventFlag(g_scmd_evid, 1, 0, &efbits);
		outbuf->m_retres = sceCdReadModelID(&outbuf->m_pkt_26.m_id);
	}
}

void __fastcall cdvdfsv_rpc3h_22_mmode(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	if ( buflen == 4 || inbuf->m_pkt_22.m_char4 == 0 )
	{
		outbuf->m_retres = sceCdMmode(inbuf->m_pkt_22.m_media);
	}
}

void __fastcall cdvdfsv_rpc3h_23_changethreadpriority(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	(void)buflen;

	outbuf->m_retres = sceCdChangeThreadPriority(inbuf->m_pkt_23.m_priority);
}

void __cdecl cdvdfsv_rpc3h_21_poweroff(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	int i;
	u32 efbits;

	(void)inbuf;
	(void)buflen;

	outbuf->m_retres = 0;
	for ( i = 0; i < 3 && !outbuf->m_retres; i += 1 )
	{
		WaitEventFlag(g_scmd_evid, 1, 0, &efbits);
		outbuf->m_retres = sceCdPowerOff(&outbuf->m_pkt_21.m_result);
	}
}

void __cdecl cdvdfsv_rpc3h_15_ctrladout(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	int i;
	u32 efbits;

	(void)buflen;

	for ( i = 0; i < 3 && !outbuf->m_retres; i += 1 )
	{
		WaitEventFlag(g_scmd_evid, 1, 0, &efbits);
		outbuf->m_retres = sceCdCtrlADout(inbuf->m_pkt_15.m_mode, &outbuf->m_pkt_15.m_status);
	}
}

void __cdecl cdvdfsv_rpc3h_01_readclock(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	int i;
	u32 efbits;

	(void)inbuf;
	(void)buflen;

	for ( i = 0; i < 3 && !outbuf->m_retres; i += 1 )
	{
		WaitEventFlag(g_scmd_evid, 1, 0, &efbits);
		outbuf->m_retres = sceCdReadClock(&outbuf->m_pkt_01.m_clock);
	}
}

void __fastcall cdvdfsv_rpc5h_11_readdiskid(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf)
{
	u8 diskid_tmp[5];

	(void)inbuf;
	(void)buflen;

	outbuf->m_retres = sceCdReadDiskID((unsigned int *)diskid_tmp);
	memcpy(&(outbuf->m_pkt_11.m_diskid), &diskid_tmp, sizeof(diskid_tmp));
}

void __fastcall cdvdfsv_rpc5h_17_doesuniquekeyexist(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf)
{
	(void)inbuf;
	(void)buflen;

	outbuf->m_retres = sceCdDoesUniqueKeyExist(&outbuf->m_pkt_17.m_status);
}

void __fastcall cdvdfsv_rpc3h_0B_applyscmd(
				const cdvdfsv_rpc3h_packet *inbuf,
				int buflen,
				cdvdfsv_rpc3h_outpacket *outbuf)
{
	u8 resbuf[16];

	(void)buflen;

	sceCdApplySCmd(inbuf->m_pkt_0B.m_cmdNum, &inbuf->m_pkt_0B.m_inBuff, inbuf->m_pkt_0B.m_inBuffSize, &resbuf);
	memcpy(&(outbuf->m_pkt_0B.m_outbuf), &resbuf, sizeof(resbuf));
}

void __fastcall cdvdfsv_rpc5h_0C_applyncmd(const cdvdfsv_rpc5h_packet *inbuf, int buflen, cdvdfsv_rpc5h_outpacket *outbuf)
{
	(void)buflen;

	outbuf->m_retres = sceCdApplyNCmd(inbuf->m_pkt_0C.m_cmdNum, &inbuf->m_pkt_0C.m_inBuff, inbuf->m_pkt_0C.m_inBuffSize);
	sceCdSync(2);
}

void __fastcall cdvdfsv_rpc3h_04_geterror(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	(void)inbuf;
	(void)buflen;

	outbuf->m_retres = sceCdGetError();
}

void __cdecl cdvdfsv_rpc3h_05_trayreq(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	int i;
	u32 efbits;

	(void)buflen;

	for ( i = 0; i < 3 && !outbuf->m_retres; i += 1 )
	{
		WaitEventFlag(g_scmd_evid, 1, 0, &efbits);
		outbuf->m_retres = sceCdTrayReq(inbuf->m_pkt_05.m_param, &outbuf->m_pkt_05.m_traychk);
	}
}

void __fastcall cdvdfsv_rpc3h_25_settimeout(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	(void)buflen;

	outbuf->m_retres = sceCdSetTimeout(inbuf->m_pkt_25.m_param, inbuf->m_pkt_25.m_timeout);
}

void __fastcall cdvdfsv_rpc3h_27_readdvddualinfo(const cdvdfsv_rpc3h_packet *inbuf, int buflen, cdvdfsv_rpc3h_outpacket *outbuf)
{
	(void)inbuf;
	(void)buflen;

	outbuf->m_retres = sceCdReadDvdDualInfo(&outbuf->m_pkt_27.m_on_dual, &outbuf->m_pkt_27.m_layer1_start);
}

int __cdecl cdvdfsv_rpc5h_0E_diskready()
{
	int is_detecting;
	int scres_unused;

	is_detecting = 0;
	// The following call to sceCdGetDiskType was inlined
	switch ( sceCdGetDiskType() )
	{
		case SCECdDETCT:
		case SCECdDETCTCD:
		case SCECdDETCTDVDS:
		case SCECdDETCTDVDD:
			is_detecting = 1;
			break;
		default:
			break;
	}
	// The following call to sceCdDiskReady was inlined
	if ( (sceCdDiskReady(8) & 0xC0) != 0x40
		|| sceCdSC(0xFFFFFFFD, &scres_unused)
		|| !sceCdSC(0xFFFFFFF4, &scres_unused)
		|| is_detecting)
	{
		VERBOSE_PRINTF(1, "Drive Not Ready\n");
		return 6;
	}
	return 2;
}

void *__fastcall cbrpc_rpc5_cdvdncmds(int fno, void *buffer, int length)
{
	int scres_unused;
	int fno_1;

	fno_1 = fno;
	VERBOSE_PRINTF(1, "sce_cdvd N cmd start %d\n", fno);
	g_cdvdfsv_rpc5flg = 1;
	sceCdSC(0xFFFFFFF6, &fno_1);
	switch ( fno )
	{
		case 1:
			// The following call to sceCdGetDiskType was inlined
			cdvdfsv_rpc5h_01_readee(buffer, length, &g_crr, (sceCdGetDiskType() ^ SCECdPS2DVD) == 0, sceCdSC(0xFFFFFFFC, &scres_unused) == 0, 0);
			break;
		case 2:
			cdvdfsv_rpc5h_02_readcdda(buffer, length, &g_crr);
			break;
		case 4:
			cdvdfsv_rpc5h_04_gettoc(buffer, length, &g_crr);
			break;
		case 5:
			VERBOSE_PRINTF(1, "Call Seek lsn= %d\n", (int)(((const cdvdfsv_rpc5h_packet *)buffer)->m_pkt_05.m_lbn));
			g_crr.m_retres = sceCdSeek(((const cdvdfsv_rpc5h_packet *)buffer)->m_pkt_05.m_lbn);
			VERBOSE_PRINTF(1, "Call Seek end\n");
			sceCdSync(6);
			break;
		case 6:
			VERBOSE_PRINTF(1, "Call Standby\n");
			g_crr.m_retres = sceCdStandby();
			sceCdSync(4);
			VERBOSE_PRINTF(1, "Call Standby called\n");
			break;
		case 7:
			VERBOSE_PRINTF(1, "Call Stop\n");
			g_crr.m_retres = sceCdStop();
			sceCdSync(4);
			break;
		case 8:
			VERBOSE_PRINTF(1, "Call Pause\n");
			g_crr.m_retres = sceCdPause();
			sceCdSync(6);
			break;
		case 9:
			if ( devctl("cdrom_stm0:", 0x4396, buffer, length, &g_crr.m_retres, 4) < 0 )
				g_crr.m_retres = 0;
			break;
		case 10:
			if ( devctl("cdrom_stm0:", 0x4398, buffer, length, &g_crr.m_retres, 4) < 0 )
				g_crr.m_retres = 0;
			break;
		case 12:
			cdvdfsv_rpc5h_0C_applyncmd(buffer, length, &g_crr);
			break;
		case 13:
			cdvdfsv_rpc5h_0D_iopmread(buffer, length, &g_crr);
			break;
		case 14:
			g_crr.m_retres = cdvdfsv_rpc5h_0E_diskready();
			break;
		case 15:
			cdvdfsv_rpc5h_0F_readchain(buffer, length, &g_crr);
			break;
		case 17:
			cdvdfsv_rpc5h_11_readdiskid(buffer, length, &g_crr);
			break;
		case 19:
			// The following call to sceCdGetDiskType was inlined
			cdvdfsv_rpc5h_01_readee(
				buffer,
				length,
				&g_crr,
				(sceCdGetDiskType() ^ SCECdPS2DVD) == 0,
				1,
				g_cdvdman_istruct_ptr->m_no_dec_flag == 0);
			break;
		case 23:
			cdvdfsv_rpc5h_17_doesuniquekeyexist(buffer, length, &g_crr);
			break;
		default:
			VERBOSE_PRINTF(1, "sce_cdvd no block IO :unrecognized code %x\n", fno);
			g_crr.m_retres = 0;
			break;
	}
	fno_1 = 0;
	sceCdSC(0xFFFFFFF6, &fno_1);
	g_cdvdfsv_rpc5flg = 0;
	VERBOSE_PRINTF(1, "sce_cdvd N cmd end\n");
	return (void *)&g_crr;
}

// cppcheck-suppress constParameterCallback
void *__fastcall cbrpc_rpc3_cdvdscmds(int fno, void *buffer, int length)
{
	VERBOSE_PRINTF(1, "sce_cdvd S cmd start %d\n", fno);
	g_cdvdfsv_rpc3flg = 1;
	switch ( fno )
	{
		case 1:
			cdvdfsv_rpc3h_01_readclock(buffer, length, &g_outbuf);
			break;
		case 3:
			cdvdfsv_rpc3h_03_disktype(buffer, length, &g_outbuf);
			break;
		case 4:
			cdvdfsv_rpc3h_04_geterror(buffer, length, &g_outbuf);
			break;
		case 5:
			cdvdfsv_rpc3h_05_trayreq(buffer, length, &g_outbuf);
			break;
		case 6:
			cdvdfsv_rpc3h_06_ri(buffer, length, &g_outbuf);
			break;
		case 11:
			cdvdfsv_rpc3h_0B_applyscmd(buffer, length, &g_outbuf);
			break;
		case 12:
			cdvdfsv_rpc3h_0C_cdstatus(buffer, length, &g_outbuf);
			break;
		case 21:
			cdvdfsv_rpc3h_15_ctrladout(buffer, length, &g_outbuf);
			break;
		case 22:
			cdvdfsv_rpc3h_16_break(buffer, length, &g_outbuf);
			break;
		case 26:
			cdvdfsv_rpc3h_1A_rm(buffer, length, &g_outbuf);
			break;
		case 33:
			cdvdfsv_rpc3h_21_poweroff(buffer, length, &g_outbuf);
			break;
		case 34:
			cdvdfsv_rpc3h_22_mmode(buffer, length, &g_outbuf);
			break;
		case 35:
			cdvdfsv_rpc3h_23_changethreadpriority(buffer, length, &g_outbuf);
			break;
		case 36:
			cdvdfsv_rpc3h_24_readguid(buffer, length, &g_outbuf);
			break;
		case 37:
			cdvdfsv_rpc3h_25_settimeout(buffer, length, &g_outbuf);
			break;
		case 38:
			cdvdfsv_rpc3h_26_readmodelid(buffer, length, &g_outbuf);
			break;
		case 39:
			cdvdfsv_rpc3h_27_readdvddualinfo(buffer, length, &g_outbuf);
			break;
		default:
			VERBOSE_PRINTF(1, "sce_cdvd block IO :unrecognized code 0x%02x\n", fno);
			g_outbuf.m_retres = 0;
			break;
	}
	VERBOSE_PRINTF(1, "sce_cdvd S cmd end\n");
	g_cdvdfsv_rpc3flg = 0;
	return (void *)&g_outbuf;
}

void __cdecl cdvdfsv_poffloop()
{
	int trid;
	char cmdpkt[16];
	int scres;
	u32 efbits;

	g_cdvdman_intr_efid = sceCdSC(0xFFFFFFF5, &scres);
	while ( 1 )
	{
		ClearEventFlag(g_cdvdman_intr_efid, ~4);
		WaitEventFlag(g_cdvdman_intr_efid, 4, 0, &efbits);
		if ( g_cdvdfsv_nopocm )
			break;
		if ( !g_cdvdfsv_plbreak )
		{
			while ( 1 )
			{
				trid = sceSifSendCmd(0x80000012, cmdpkt, sizeof(cmdpkt), 0, 0, 0);
				if ( trid )
					break;
				DelayThread(500);
			}
			while ( cdvdfsv_checkdmastat(trid) >= 0 )
				;
		}
	}
}

void __cdecl cdvdfsv_rpc1_th(void *arg)
{
	(void)arg;

	sceSifSetRpcQueue(&g_rpc_qdata1, GetThreadId());
	sceSifRegisterRpc(&g_rpc_sdata1, 0x80000592, cbrpc_rpc1_cdinit, g_rpc_buffer1, 0, 0, &g_rpc_qdata1);
	sceSifRegisterRpc(&g_rpc_sdata2, 0x8000059A, cbrpc_rpc2_diskready, g_rpc_buffer2, 0, 0, &g_rpc_qdata1);
	sceSifRegisterRpc(&g_rpc_sdata3, 0x80000593, cbrpc_rpc3_cdvdscmds, g_rpc_buffer3, 0, 0, &g_rpc_qdata1);
	sceSifRpcLoop(&g_rpc_qdata1);
	ExitDeleteThread();
}

void __cdecl cdvdfsv_rpc3_th(void *arg)
{
	(void)arg;

	sceSifSetRpcQueue(&g_rpc_qdata3, GetThreadId());
	sceSifRegisterRpc(&g_rpc_sdata6, 0x8000059C, cbrpc_rpc2_diskready, g_rpc_buffer2, 0, 0, &g_rpc_qdata3);
	sceSifRpcLoop(&g_rpc_qdata3);
	ExitDeleteThread();
}

void __cdecl cdvdfsv_rpc2_th(void *arg)
{
	(void)arg;

	sceSifSetRpcQueue(&g_rpc_qdata2, GetThreadId());
	sceSifRegisterRpc(&g_rpc_sdata4, 0x80000597, cbrpc_rpc4_fscall, g_rpc_buffer4, 0, 0, &g_rpc_qdata2);
	sceSifRegisterRpc(&g_rpc_sdata5, 0x80000595, cbrpc_rpc5_cdvdncmds, g_rpc_buffer5, 0, 0, &g_rpc_qdata2);
	sceSifRpcLoop(&g_rpc_qdata2);
	ExitDeleteThread();
}

void __fastcall cdvdfsv_unused_xorfun(unsigned int *a1, int a2)
{
	int v2;
	int v4;
	int v5;
	int v6;
	bool v7;

	v2 = 0;
	for ( ; a2; a2 -= 4 )
	{
		unsigned int v3;

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
					v2 ^= 1;
			}
			v3 >>= 8;
		}
		a1 += 1;
	}
}

unsigned int __fastcall optimized_memcpy(char *dst, const char *src, unsigned int n)
{
	int v3;
	int v4;
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	int v10;
	int v11;
	int v12;
	int v13;
	int v14;
	int v15;
	int v16;
	int v17;
	int v18;
	int v19;
	int v20;
	int v21;
	int v22;
	int v23;
	int v24;
	int v25;
	int v26;
	int v27;
	int v28;
	int v29;
	int v30;
	int v31;
	int v32;
	int v33;
	int v34;
	int v35;
	int v36;
	int v37;
	int v38;
	int v39;
	int v40;
	int v41;
	int v42;
	int v43;
	int v44;
	int v45;
	int v46;
	int v47;
	int v48;
	int v49;
	int v50;
	int v51;
	int v52;
	int v53;
	int v54;
	unsigned int v55;

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

void cdvdfsv_1()
{
	;
}
