
#include <irx_imports.h>

IRX_ID("mcxserv", 2, 2);

#define __fastcall
#define __cdecl
#define __noreturn

#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long

struct sceMcxTblInfo_
{
	s16 AppliNo;
	u16 Reserve1;
	s32 AplArg;
	u8 Speaker;
	u8 Infrared;
	u8 Flash;
	u8 Led;
	struct McxRtc_stru
	{
		u8 Week;
		u8 Sec;
		u8 Min;
		u8 Hour;
		u8 Day;
		u8 Month;
		u16 Year;
	} _Rtc;
	u32 Serial;
};

typedef struct sceMcxTblInfo_ sceMcxTblInfo;

//-------------------------------------------------------------------------
// Function declarations

void mcxserv_0();
int __fastcall start(int ac, const char **av);
int module_unload();
int __fastcall mcxserv_5(int thpri);
void rpc_thread();
int *__fastcall rpc_handler(int fno, void *buffer, int length);
int rpc_handler_FE_retzero();
int __fastcall rpc_handler_0C(u32 *rpcbuf);
int __fastcall rpc_handler_01_sceMcxGetInfo(u32 *rpcbuf);
int __fastcall rpc_handler_02_sceMcxSetInfo(u32 *rpcbuf);
int __fastcall rpc_handler_05_sceMcxDispTrans(u32 *rpcbuf);
int __fastcall rpc_handler_07_sceMcxReadDev(u32 *rpcbuf);
int __fastcall rpc_handler_08_sceMcxWriteDev(u32 *rpcbuf);

// temp
char **mcxman_5_GetMcxModVerStruct();
int __fastcall mcxman_6_McxGetInfo(char port, int slot, sceMcxTblInfo *mcx_info);
int __fastcall mcxman_7_McxSetInfoSpeakerInfraredLed(char port, int slot, char speakerval, char infraredval, char ledval);
int __fastcall mcxman_8_McxSetInfoFlash(char port, int slot, char flashval);
int __fastcall mcxman_10_McxWriteDev(int port, int slot, int dev_nr, const void *param_buf, size_t param_buf_sz, void *sect_buf, size_t sect_buf_sz);
int __fastcall mcxman_9_McxReadDev(char port, int slot, char dev_nr, const void *param_buf, size_t param_buf_sz, void *sect_buf, size_t sect_buf_sz);
int __fastcall mcxman_11_McxSetInfoAppli(char port, int slot, __int16 applinoval, int aplargval);
int __fastcall mcxman_12_McxDispTrans(char port, int slot, char dirval, char hideshowval, char timeval);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_mcxserv;
__int16 g_modver_mcxserv = 514; // weak
char g_month_table[] =
{
	'\0',
	'\0',
	'\x03',
	'\x02',
	'\x05',
	'\0',
	'\x03',
	'\x05',
	'\x01',
	'\x04',
	'\x06',
	'\x02',
	'\x04',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0'
}; // weak
int g_rpc_retbuf[4]; // weak
int g_param_buf[32]; // weak
int g_sect_buf[2016]; // weak
int g_rpc_buf[12]; // weak
int g_thid; // idb
SifRpcDataQueue_t g_rpc_qd; // weak
SifRpcServerData_t g_rpc_sd; // idb
int g_in_rpc_handler; // weak


//----- (00400038) --------------------------------------------------------
void mcxserv_0()
{
	;
}

//----- (00400040) --------------------------------------------------------
int __fastcall start(int ac, const char **av)
{
	int thpri_tmp; // $s1
	int i; // $s2
	iop_thread_t thparam; // [sp+10h] [-18h] BYREF

	if ( ac < 0 )
		return module_unload();
	if ( RegisterLibraryEntries((struct irx_export_table *)&_exp_mcxserv) != 0 )
		return 1;
	thpri_tmp = 104;
	CpuEnableIntr();
	for ( i = 0; i < ac; i += 1 )
	{
		if ( !strncmp("thpri=", av[i], 6) )
		{
			thpri_tmp = strtol(av[i] + 6, NULL, 10);
			if ( (unsigned int)(thpri_tmp - 9) >= 0x73 )
			{
				thpri_tmp = 104;
				printf("mcxserv.irx: thread prority definition ignored.\n");
			}
		}
	}
	thparam.attr = 0x2000000;
	thparam.stacksize = 4096;
	thparam.priority = thpri_tmp;
	thparam.option = 0;
	thparam.thread = (void (__cdecl *)(void *))rpc_thread;
	g_thid = CreateThread(&thparam);
	StartThread(g_thid, NULL);
	return 2;
}

//----- (0040015C) --------------------------------------------------------
int module_unload()
{
	int unregres; // $s0
	int state; // [sp+10h] [-8h] BYREF

	if ( g_in_rpc_handler )
		return 2;
	CpuSuspendIntr(&state);
	unregres = ReleaseLibraryEntries((struct irx_export_table *)&_exp_mcxserv);
	CpuResumeIntr(state);
	if ( unregres && unregres != -213 )
		return 2;
	TerminateThread(g_thid);
	DeleteThread(g_thid);
	sceSifRemoveRpc(&g_rpc_sd, &g_rpc_qd);
	sceSifRemoveRpcQueue(&g_rpc_qd);
	return 1;
}
// 402E58: using guessed type SifRpcDataQueue_t g_rpc_qd;
// 402EB4: using guessed type int g_in_rpc_handler;

//----- (00400204) --------------------------------------------------------
int __fastcall mcxserv_5(int thpri)
{
	int retres; // $v0
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	if ( (unsigned int)(thpri - 9) >= 0x73 )
		return -403;
	ReferThreadStatus(0, &thinfo);
	ChangeThreadPriority(0, 8);
	retres = ( g_thid > 0 ) ? ChangeThreadPriority(g_thid, thpri) : 0;
	if ( retres < 0 )
		return retres;
	ChangeThreadPriority(0, thinfo.currentPriority);
	return 0;
}

//----- (00400284) --------------------------------------------------------
void rpc_thread()
{
	int ThreadId; // $v0

	if ( !sceSifCheckInit() )
		sceSifInit();
	sceSifInitRpc(0);
	ThreadId = GetThreadId();
	sceSifSetRpcQueue(&g_rpc_qd, ThreadId);
	sceSifRegisterRpc(&g_rpc_sd, 0x80000420, (SifRpcFunc_t)rpc_handler, g_rpc_buf, NULL, NULL, &g_rpc_qd);
	sceSifRpcLoop(&g_rpc_qd);
}
// 402E20: using guessed type int g_rpc_buf[12];
// 402E58: using guessed type SifRpcDataQueue_t g_rpc_qd;

//----- (00400310) --------------------------------------------------------
int *__fastcall rpc_handler(int fno, void *buffer, int length)
{
	(void)buffer;
	(void)length;
	g_in_rpc_handler = 1;
	switch ( fno )
	{
	case 1:
		{
			g_rpc_retbuf[0] = rpc_handler_01_sceMcxGetInfo((u32 *)g_rpc_buf);
			break;
		}
	case 2:
		{
			g_rpc_retbuf[0] = rpc_handler_02_sceMcxSetInfo((u32 *)g_rpc_buf);
			break;
		}
	case 5:
		{
			g_rpc_retbuf[0] = rpc_handler_05_sceMcxDispTrans((u32 *)g_rpc_buf);
			break;
		}
	case 7:
		{
			g_rpc_retbuf[0] = rpc_handler_07_sceMcxReadDev((u32 *)g_rpc_buf);
			break;
		}
	case 8:
		{
			g_rpc_retbuf[0] = rpc_handler_08_sceMcxWriteDev((u32 *)g_rpc_buf);
			break;
		}
	case 12:
		{
			g_rpc_retbuf[0] = rpc_handler_0C((u32 *)g_rpc_buf);
			break;
		}
	case 254:
		{
			g_rpc_retbuf[0] = rpc_handler_FE_retzero();
			g_rpc_retbuf[1] = (unsigned __int16)g_modver_mcxserv;
			g_rpc_retbuf[2] = *((unsigned __int16 *)mcxman_5_GetMcxModVerStruct() + 2);
			break;
		}
	default:
		break;
	}
	g_in_rpc_handler = 0;
	return g_rpc_retbuf;
}
// 400DF4: using guessed type __int16 g_modver_mcxserv;
// 400E10: using guessed type int g_rpc_retbuf[4];
// 402E20: using guessed type int g_rpc_buf[12];
// 402EB4: using guessed type int g_in_rpc_handler;

//----- (00400484) --------------------------------------------------------
int rpc_handler_FE_retzero()
{
	return 0;
}

//----- (0040048C) --------------------------------------------------------
int __fastcall rpc_handler_0C(u32 *rpcbuf)
{
	int thpri; // $a1

	thpri = rpcbuf[3];
	if ( (unsigned int)(thpri - 9) >= 0x73 )
		return -403;
	ChangeThreadPriority(0, thpri);
	return 0;
}

//----- (004004C8) --------------------------------------------------------
int __fastcall rpc_handler_01_sceMcxGetInfo(u32 *rpcbuf)
{
	int Info; // $v0
	void *dstbuf; // $a1
	int info_tmp; // $s1
	int trid; // $s0
	sceMcxTblInfo mcx_info; // [sp+10h] [-30h] BYREF
	SifDmaTransfer_t dmat; // [sp+28h] [-18h] BYREF
	int state; // [sp+38h] [-8h] BYREF

	Info = mcxman_6_McxGetInfo(*rpcbuf, rpcbuf[1], &mcx_info);
	dmat.src = &mcx_info;
	dstbuf = (void *)rpcbuf[5];
	info_tmp = Info;
	dmat.size = 24;
	dmat.attr = 0;
	dmat.dest = dstbuf;
	CpuSuspendIntr(&state);
	trid = sceSifSetDma(&dmat, 1);
	CpuResumeIntr(state);
	while ( sceSifDmaStat(trid) >= 0 )
		DelayThread(100);
	return info_tmp;
}

//----- (00400560) --------------------------------------------------------
int __fastcall rpc_handler_02_sceMcxSetInfo(u32 *rpcbuf)
{
	u32 port; // $s4
	int slot; // $s5
	int xferres; // $v1
	char Year; // $a2
	__int16 yeardiv1; // $a1
	unsigned __int16 yeardiv2; // kr00_2
	__int16 yeardiv3; // $t3
	unsigned __int16 yeardiv4; // kr02_2
	__int16 yeardiv5; // $v1
	SifRpcReceiveData_t rdata; // [sp+20h] [-58h] BYREF
	sceMcxTblInfo mcx_info; // [sp+40h] [-38h] BYREF
	char sect_buf[12]; // [sp+64h] [-14h] BYREF

	sceSifGetOtherData(&rdata, (void *)rpcbuf[5], &mcx_info, 24, 0);
	port = *rpcbuf;
	slot = rpcbuf[1];
	if ( (rpcbuf[4] & 0x16) )
	{
		if ( (rpcbuf[4] & 2) == 0 )
			mcx_info.Speaker = -1;
		if ( (rpcbuf[4] & 4) == 0 )
			mcx_info.Infrared = -1;
		if ( (rpcbuf[4] & 0x10) == 0 )
			mcx_info.Led = -1;
		xferres = mcxman_7_McxSetInfoSpeakerInfraredLed(port, slot, mcx_info.Speaker, mcx_info.Infrared, mcx_info.Led);
		if ( xferres )
			return xferres;
	}
	if ( (rpcbuf[4] & 8) )
	{
		xferres = mcxman_8_McxSetInfoFlash(port, slot, mcx_info.Flash);
		if ( xferres )
			return xferres;
	}
	if ( (rpcbuf[4] & 0x20) )
	{
		Year = mcx_info._Rtc.Year;
		yeardiv1 = mcx_info._Rtc.Year / 0x64u;
		yeardiv2 = mcx_info._Rtc.Year / 0x3E8u;
		yeardiv3 = mcx_info._Rtc.Year / 0xAu;
		yeardiv4 = mcx_info._Rtc.Year / 0xAu;
		yeardiv5 = mcx_info._Rtc.Year / 0x64u / 0xA;
		mcx_info._Rtc.Year -= mcx_info._Rtc.Month < 3u;
		sect_buf[3] = yeardiv1 - 10 * yeardiv5 + 16 * (yeardiv2 % 0xAu);
		sect_buf[2] = Year - 10 * yeardiv3 + 16 * (yeardiv4 % 0xAu);
		sect_buf[1] = mcx_info._Rtc.Month % 0xAu + 16 * (mcx_info._Rtc.Month / 0xAu % 0xA);
		sect_buf[0] = mcx_info._Rtc.Day % 0xAu + 16 * (mcx_info._Rtc.Day / 0xAu % 0xA);
		sect_buf[6] = mcx_info._Rtc.Hour % 0xAu + 16 * (mcx_info._Rtc.Hour / 0xAu % 0xA);
		sect_buf[5] = mcx_info._Rtc.Min % 0xAu + 16 * (mcx_info._Rtc.Min / 0xAu % 0xA);
		sect_buf[4] = mcx_info._Rtc.Sec % 0xAu + 16 * (mcx_info._Rtc.Sec / 0xAu % 0xA);
		sect_buf[7] = (int)(mcx_info._Rtc.Year
											+ (mcx_info._Rtc.Year >> 2)
											- mcx_info._Rtc.Year / 0x64u
											+ mcx_info._Rtc.Year / 0x190u
											+ (unsigned __int8)g_month_table[mcx_info._Rtc.Month]
											+ mcx_info._Rtc.Day)
								% 7
								+ 1;
		xferres = mcxman_10_McxWriteDev(port, slot, 0, NULL, 0, sect_buf, 8);
		if ( xferres )
			return xferres;
	}
	if ( (rpcbuf[4] & 1) )
	{
		xferres = mcxman_11_McxSetInfoAppli(port, slot, mcx_info.AppliNo, mcx_info.AplArg);
		if ( xferres )
			return xferres;
	}
	return 0;
}
// 400560: using guessed type SifRpcReceiveData_t rdata;

//----- (004009D0) --------------------------------------------------------
int __fastcall rpc_handler_05_sceMcxDispTrans(u32 *rpcbuf)
{
	return mcxman_12_McxDispTrans(*rpcbuf, rpcbuf[1], rpcbuf[3], rpcbuf[4], rpcbuf[2]);
}

//----- (00400A1C) --------------------------------------------------------
int __fastcall rpc_handler_07_sceMcxReadDev(u32 *rpcbuf)
{
	int Dev; // $v0
	int sz_tmp; // $v1
	int dev_tmp; // $s1
	int trid; // $s0
	SifRpcReceiveData_t rdata; // [sp+20h] [-38h] BYREF
	SifDmaTransfer_t dmat; // [sp+40h] [-18h] BYREF
	int state; // [sp+50h] [-8h] BYREF

	sceSifGetOtherData(&rdata, (void *)rpcbuf[5], g_param_buf, rpcbuf[3], 0);
	Dev = mcxman_9_McxReadDev(*rpcbuf, rpcbuf[1], rpcbuf[2], g_param_buf, rpcbuf[3], g_sect_buf, rpcbuf[4]);
	dmat.src = g_sect_buf;
	dmat.dest = (void *)rpcbuf[6];
	sz_tmp = rpcbuf[4];
	dev_tmp = Dev;
	dmat.attr = 0;
	dmat.size = sz_tmp;
	CpuSuspendIntr(&state);
	trid = sceSifSetDma(&dmat, 1);
	CpuResumeIntr(state);
	while ( sceSifDmaStat(trid) >= 0 )
		DelayThread(100);
	return dev_tmp;
}
// 400E20: using guessed type int g_param_buf[32];
// 400EA0: using guessed type int g_sect_buf[2016];
// 400A1C: using guessed type SifRpcReceiveData_t rdata;

//----- (00400AF4) --------------------------------------------------------
int __fastcall rpc_handler_08_sceMcxWriteDev(u32 *rpcbuf)
{
	SifRpcReceiveData_t rdata; // [sp+20h] [-20h] BYREF

	sceSifGetOtherData(&rdata, (void *)rpcbuf[5], g_param_buf, rpcbuf[3], 0);
	sceSifGetOtherData(&rdata, (void *)rpcbuf[6], g_sect_buf, rpcbuf[4], 0);
	return mcxman_10_McxWriteDev(*rpcbuf, rpcbuf[1], rpcbuf[2], g_param_buf, rpcbuf[3], g_sect_buf, rpcbuf[4]);
}
// 400E20: using guessed type int g_param_buf[32];
// 400EA0: using guessed type int g_sect_buf[2016];
// 400AF4: using guessed type SifRpcReceiveData_t rdata;
