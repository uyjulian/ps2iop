
#include <irx_imports.h>

#ifndef SDRDRV_OBSOLETE_FUNCS
#define SDRDRV_OBSOLETE_FUNCS 1
#endif

IRX_ID("sdr_driver", 4, 1);

typedef struct SdrEECBData_
{
	int mode;
	int voice_bit;
	int status;
	int opt;
	int pad[12];
} SdrEECBData;

typedef int (*sceSdrUserCommandFunction)(unsigned int command, void *data, int size);

//-------------------------------------------------------------------------
// Function declarations

int module_start(int ac, char **av);
int module_stop(int ac, char **av);
int sceSdrChangeThreadPriority(int priority_main, int priority_cb);
void sce_sdr_loop(void* arg);
void *sdrFunc(int fno, void *buffer, int length);
sceSdrUserCommandFunction sceSdrSetUserCommandFunction(int command, sceSdrUserCommandFunction func);
void sceSifCmdLoop2(void);
#if SDRDRV_OBSOLETE_FUNCS
int _sce_sdrDMA0CallBackProc(void *data);
int _sce_sdrDMA1CallBackProc(void *data);
int _sce_sdrIRQCallBackProc(void *data);
#endif
int _sce_sdrDMA0IntrHandler(int core, void *common);
int _sce_sdrDMA1IntrHandler(int core, void *common);
int _sce_sdrSpu2IntrHandler(int core_bit, void *common);
void sce_sdrcb_loop(void* arg);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_sdrdrv;
// Unofficial: move to bss
int thid_main;
// Unofficial: move to bss
int thid_cb;
sceSdrUserCommandFunction sceSdr_vUserCommandFunction[16];
SdrEECBData eeCBData;
int initial_priority_main;
SifRpcDataQueue_t rpc_qd;
SifRpcServerData_t rpc_sd;
int initial_priority_cb;
int procbat_returns[384];
sceSdEffectAttr e_attr;
SifRpcClientData_t cd;

//----- (00400000) --------------------------------------------------------
int module_start(int ac, char **av)
{
	int code; // $s0
	int i; // $s2
	const char *p; // $s0
	iop_thread_t thprarm; // [sp+10h] [-20h] BYREF
	int state; // [sp+28h] [-8h] BYREF

	CpuSuspendIntr(&state);
	code = RegisterLibraryEntries(&_exp_sdrdrv);
	CpuResumeIntr(state);
	if ( code )
		return 1;
	Kprintf("SDR driver version 4.0.1 (C) SCEI\n");
	initial_priority_main = 24;
	initial_priority_cb = 24;
	thid_main = 0;
	thid_cb = 0;
	for ( i = 1; i < ac; i += 1 )
	{
		if ( !strncmp("thpri=", av[i], 6) )
		{
			p = av[i] + 6;
			if ( isdigit(*p) )
			{
				initial_priority_main = strtol(p, 0, 10);
				if ( (unsigned int)(initial_priority_main - 9) >= 0x73 )
				{
					Kprintf(" SDR driver error: invalid priority %d\n", initial_priority_main);
					initial_priority_main = 24;
				}
			}
			while ( isdigit(*p) )
				++p;
			if ( *p == ',' && isdigit(p[1]) )
			{
				initial_priority_cb = strtol(&p[1], 0, 10);
				if ( (unsigned int)(initial_priority_cb - 9) >= 0x73 )
				{
					Kprintf(" SDR driver error: invalid priority %d\n", initial_priority_cb);
					initial_priority_cb = 24;
				}
			}
			if ( initial_priority_cb < initial_priority_main )
			{
				Kprintf(" SDR driver ERROR:\n");
				Kprintf("   callback th. priority is higher than main th. priority.\n");
				initial_priority_cb = initial_priority_main;
			}
			Kprintf(" SDR driver: thread priority: main=%d, callback=%d\n", initial_priority_main, initial_priority_cb);
		}
	}
	thprarm.attr = 0x2000000;
	thprarm.thread = sce_sdr_loop;
	thprarm.stacksize = 2048;
	thprarm.option = 0;
	thprarm.priority = initial_priority_main;
	thid_main = CreateThread(&thprarm);
	if ( thid_main <= 0 )
		return 1;
	StartThread(thid_main, 0);
	Kprintf(" Exit rsd_main \n");
	return 2;
}
// 4015B0: using guessed type int initial_priority_main;
// 401624: using guessed type int initial_priority_cb;

//----- (00400284) --------------------------------------------------------
int module_stop(int ac, char **av)
{
	int code; // $s0
	int state; // [sp+10h] [-8h] BYREF

	(void)ac;
	(void)av;

	CpuSuspendIntr(&state);
	code = ReleaseLibraryEntries(&_exp_sdrdrv);
	CpuResumeIntr(state);
	if ( code )
		return 2;
	sceSdSetTransIntrHandler(0, 0, 0);
	sceSdSetTransIntrHandler(1, 0, 0);
	sceSdSetSpu2IntrHandler(0, 0);
	if ( thid_cb > 0 )
	{
		TerminateThread(thid_cb);
		DeleteThread(thid_cb);
		thid_cb = 0;
	}
	if ( thid_main > 0 )
	{
		sceSifRemoveRpc(&rpc_sd, &rpc_qd);
		sceSifRemoveRpcQueue(&rpc_qd);
		TerminateThread(thid_main);
		DeleteThread(thid_main);
		thid_main = 0;
	}
	Kprintf(" sdrdrv: unloaded! \n");
	return 1;
}

//----- (004003A0) --------------------------------------------------------
int _start(int ac, char **av)
{
	return ( ac >= 0 ) ? module_start(ac, av) : module_stop(-ac, av);
}

//----- (004003D4) --------------------------------------------------------
int sceSdrChangeThreadPriority(int priority_main, int priority_cb)
{
	int cur_priority; // $s0
	int ret; // $v0
	iop_thread_info_t thstatus; // [sp+10h] [-48h] BYREF

	if ( (unsigned int)(priority_main - 9) >= 0x73 || (unsigned int)(priority_cb - 9) >= 0x73 )
		return -403;
	if ( priority_cb < priority_main )
	{
		Kprintf(" SDR driver ERROR:\n");
		Kprintf("   callback th. priority is higher than main th. priority.\n");
	}
	cur_priority = ( priority_cb < priority_main ) ? priority_main : priority_cb;
	ReferThreadStatus(0, &thstatus);
	ChangeThreadPriority(0, 8);
	ret = 0;
	if ( thid_main > 0 )
		ret = ChangeThreadPriority(thid_main, priority_main);
	if ( ret < 0 )
		return ret;
	if ( thid_cb > 0 )
		ret = ChangeThreadPriority(thid_cb, cur_priority);
	if ( ret < 0 )
		return ret;
	initial_priority_cb = cur_priority;
	ChangeThreadPriority(0, thstatus.currentPriority);
	return 0;
}
// 401624: using guessed type int initial_priority_cb;

//----- (004004E0) --------------------------------------------------------
void sce_sdr_loop(void *arg)
{
	// Unofficial: make local variable
	int gRpcArg[16];

	(void)arg;

	sceSifInitRpc(0);
	sceSifSetRpcQueue(&rpc_qd, GetThreadId());
	sceSifRegisterRpc(&rpc_sd, 0x80000701, sdrFunc, gRpcArg, 0, 0, &rpc_qd);
	// Unofficial: was inlined
	memset(sceSdr_vUserCommandFunction, 0, sizeof(sceSdr_vUserCommandFunction));
	sceSifRpcLoop(&rpc_qd);
}

//----- (00400588) --------------------------------------------------------
void *sdrFunc(int fno, void *buffer, int length)
{
	int ret; // $v0
	iop_thread_t thparam; // [sp+18h] [-18h] BYREF

	ret = 0;
	switch (fno & 0xFFF0)
	{
		case 0x8000:
			ret = sceSdInit(*((u32 *)buffer + 1));
			break;
		case 0x8010:
			sceSdSetParam(*((u16 *)buffer + 2), *((u16 *)buffer + 4));
			break;
		case 0x8020:
			ret = sceSdGetParam(*((u16 *)buffer + 2));
			break;
		case 0x8030:
			sceSdSetSwitch(*((u16 *)buffer + 2), *((u32 *)buffer + 2));
			break;
		case 0x8040:
			ret = sceSdGetSwitch(*((u16 *)buffer + 2));
			break;
		case 0x8050:
			sceSdSetAddr(*((u16 *)buffer + 2), *((u32 *)buffer + 2));
			break;
		case 0x8060:
			ret = sceSdGetAddr(*((u16 *)buffer + 2));
			break;
		case 0x8070:
			sceSdSetCoreAttr(*((u16 *)buffer + 2), *((u16 *)buffer + 4));
			break;
		case 0x8080:
			ret = sceSdGetCoreAttr(*((u16 *)buffer + 2));
			break;
		case 0x8090:
			ret = sceSdNote2Pitch(*((u16 *)buffer + 2), *((u16 *)buffer + 4), *((u16 *)buffer + 6), *((u16 *)buffer + 8));
			break;
		case 0x80A0:
			ret = sceSdPitch2Note(*((u16 *)buffer + 2), *((u16 *)buffer + 4), *((u16 *)buffer + 6));
			break;
		case 0x80B0:
			ret = sceSdProcBatch(*((sceSdBatch **)buffer + 1), *((u32 **)buffer + 2), *((u32 *)buffer + 3));
			break;
		case 0x80C0:
			ret = sceSdProcBatchEx(*((sceSdBatch **)buffer + 1), *((u32 **)buffer + 2), *((u32 *)buffer + 3), *((u32 *)buffer + 4));
			break;
		case 0x80D0:
			ret = sceSdVoiceTrans(*((u16 *)buffer + 2), *((u16 *)buffer + 4), *((u8 **)buffer + 3), *((u32 **)buffer + 4), *((u32 *)buffer + 5));
			break;
		case 0x80E0:
			ret = sceSdBlockTrans(*((u16 *)buffer + 2), *((u16 *)buffer + 4), *((u8 **)buffer + 3), *((u32 *)buffer + 4), *((u32 *)buffer + 5));
			break;
		case 0x80F0:
			ret = sceSdVoiceTransStatus(*((u16 *)buffer + 2), *((u16 *)buffer + 4));
			break;
		case 0x8100:
			ret = sceSdBlockTransStatus(*((u16 *)buffer + 2), *((u16 *)buffer + 4));
			break;
#if SDRDRV_OBSOLETE_FUNCS
		case 0x8110:
			ret = (int)sceSdSetTransCallback(*((u32 *)buffer + 1) ? 1 : 0, *((u32 *)buffer + 2) ? (*((u32 *)buffer + 1) ? _sce_sdrDMA1CallBackProc : _sce_sdrDMA0CallBackProc) : 0);
			break;
    case 0x8120:
    	ret = (int)sceSdSetIRQCallback(*((u32 *)buffer + 1) ? _sce_sdrIRQCallBackProc : 0);
    	break;
#endif
		case 0x8130:
			ret = sceSdSetEffectAttr(fno & 0xF, (sceSdEffectAttr *)buffer);
			break;
		case 0x8140:
			sceSdGetEffectAttr(fno & 0xF, &e_attr);
			return &e_attr;
		case 0x8150:
			ret = sceSdClearEffectWorkArea(*((u32 *)buffer + 1), *((u32 *)buffer + 2), *((u32 *)buffer + 3));
			break;
		case 0x8160:
			ret = (int)sceSdSetTransIntrHandler(*((u32 *)buffer + 1) ? 1 : 0, *((u32 *)buffer + 2) ? (*((u32 *)buffer + 1) ? _sce_sdrDMA1IntrHandler : 0) : _sce_sdrDMA0IntrHandler, 0);
			break;
		case 0x8170:
			ret = (int)sceSdSetSpu2IntrHandler(*((u32 *)buffer + 1) ? _sce_sdrSpu2IntrHandler : 0, 0);
			break;
		case 0x8180:
			ret = sceSdStopTrans(*((u32 *)buffer + 1));
			break;
		case 0x8190:
			ret = sceSdCleanEffectWorkArea(*((u32 *)buffer + 1), *((u32 *)buffer + 2), *((u32 *)buffer + 3));
			break;
		case 0x81A0:
			ret = sceSdSetEffectMode(fno & 0xF, (sceSdEffectAttr *)buffer);
			break;
		case 0x81C0:
			ret = sceSdProcBatch((sceSdBatch *)buffer + 1, (u32 *)&procbat_returns[1], *((u16 *)buffer + 1));
			break;
		case 0x81D0:
			ret = sceSdProcBatchEx((sceSdBatch *)buffer + 1, (u32 *)&procbat_returns[1], *((u16 *)buffer + 1), *((u32 *)buffer + 1));
			break;
		case 0x8F10:
			ret = sceSdrChangeThreadPriority(*((u32 *)buffer + 1), *((u32 *)buffer + 2));
			break;
		case 0x9000:
		case 0x9010:
		case 0x9020:
		case 0x9030:
		case 0x9040:
		case 0x9050:
		case 0x9060:
		case 0x9070:
		case 0x9080:
		case 0x9090:
		case 0x90A0:
		case 0x90B0:
		case 0x90C0:
		case 0x90D0:
		case 0x90E0:
		case 0x90F0:
		{
			ret = sceSdr_vUserCommandFunction[(fno & 0xF0) >> 4] ? sceSdr_vUserCommandFunction[(fno & 0xF0) >> 4](fno, buffer, length) : 0;
			break;
		}
		case 0xE620:
		{
			thparam.attr = 0x2000000;
			thparam.thread = sce_sdrcb_loop;
			thparam.stacksize = 2048;
			thparam.option = 0;
			thparam.priority = initial_priority_cb;
			thid_cb = CreateThread(&thparam);
			StartThread(thid_cb, 0);
			Kprintf("SDR callback thread created\n");
			break;
		}
		case 0xE630:
		{
			if ( thid_cb > 0 )
			{
				TerminateThread(thid_cb);
				DeleteThread(thid_cb);
				thid_cb = 0;
				Kprintf("SDR callback thread deleted\n");
			}
			break;
		}
		default:
			Kprintf("SDR driver ERROR: unknown command %x \n", fno & 0xFFF0);
			break;
	}
	// Unofficial: always return pointer to procbat_returns
	procbat_returns[0] = ret;
	return procbat_returns;
}
// 401624: using guessed type int initial_priority_cb;
// 401630: using guessed type int procbat_returns[384];

//----- (00400DC8) --------------------------------------------------------
sceSdrUserCommandFunction sceSdrSetUserCommandFunction(int command, sceSdrUserCommandFunction func)
{
	sceSdrUserCommandFunction oldf; // $v0

	if ( (command < 0x9000) || (command > 0xF0) )
		return (sceSdrUserCommandFunction)-1;
	oldf = sceSdr_vUserCommandFunction[(command & 0xF0) >> 4];
	sceSdr_vUserCommandFunction[(command & 0xF0) >> 4] = func;
	return oldf;
}

//----- (00400E10) --------------------------------------------------------
void sceSifCmdLoop2(void)
{
	int state;
	// Unofficial: make local variable
	SdrEECBData eeCBDataSend;

	while ( 1 )
	{
		if ( eeCBData.mode )
		{
			while ( 1 )
			{
				CpuSuspendIntr(&state);
				// Unofficial: was inlined
				memcpy(&eeCBDataSend, &eeCBData, sizeof(eeCBDataSend));
				CpuResumeIntr(state);
				sceSifCallRpc(&cd, 0, 0, &eeCBDataSend, sizeof(eeCBDataSend), 0, 0, 0, 0);
				CpuSuspendIntr(&state);
				if ( eeCBData.mode == eeCBDataSend.mode )
				{
					eeCBData.mode = 0;
					iCancelWakeupThread(0);
					CpuResumeIntr(state);
					break;
				}
				eeCBData.mode &= ~eeCBDataSend.mode;
				CpuResumeIntr(state);
			}
		}
		SleepThread();
	}
}
// 401530: using guessed type SdrEECBData eeCBData;

#if SDRDRV_OBSOLETE_FUNCS
int _sce_sdrDMA0CallBackProc(void *data)
{
	(void)data;

	eeCBData.mode |= (1 << 0);
	iWakeupThread(thid_cb);
	return 1;
}

int _sce_sdrDMA1CallBackProc(void *data)
{
	(void)data;

	eeCBData.mode |= (1 << 1);
	iWakeupThread(thid_cb);
	return 1;
}

int _sce_sdrIRQCallBackProc(void *data)
{
	(void)data;

	eeCBData.mode |= (1 << 2);
	iWakeupThread(thid_cb);
	return 1;
}
#endif

//----- (00400F2C) --------------------------------------------------------
int _sce_sdrDMA0IntrHandler(int core, void *common)
{
	(void)core;
	(void)common;

	eeCBData.mode |= (1 << 8);
	iWakeupThread(thid_cb);
	return 0;
}
// 401530: using guessed type SdrEECBData eeCBData;

//----- (00400F6C) --------------------------------------------------------
int _sce_sdrDMA1IntrHandler(int core, void *common)
{
	(void)core;
	(void)common;

	eeCBData.mode |= (1 << 9);
	iWakeupThread(thid_cb);
	return 0;
}
// 401530: using guessed type SdrEECBData eeCBData;

//----- (00400FAC) --------------------------------------------------------
int _sce_sdrSpu2IntrHandler(int core_bit, void *common)
{
	(void)core_bit;
	(void)common;

	eeCBData.mode |= (1 << 10);
	eeCBData.voice_bit = core_bit;
	iWakeupThread(thid_cb);
	return 0;
}
// 401530: using guessed type SdrEECBData eeCBData;

//----- (00400FF0) --------------------------------------------------------
void sce_sdrcb_loop(void *arg)
{
	int i; // $v0

	(void)arg;

	eeCBData.mode = 0;
	while ( sceSifBindRpc(&cd, 0x80000704, 0) >= 0 )
	{
		for ( i = 0; i < 10000; i += 1 );
		if ( cd.server )
			sceSifCmdLoop2();
	}
	Kprintf("error \n");
	while ( 1 )
		;
}
// 401530: using guessed type SdrEECBData eeCBData;
