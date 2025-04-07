
#include <irx_imports.h>

IRX_ID("sdr_driver", 4, 1);

#define __cdecl
#define __noreturn
#define __fastcall
#define _WORD u16
#define _DWORD u32

typedef struct SdrEECBData_
{
	int mode;
	int voice_bit;
	int status;
	int opt;
	int pad[12];
} SdrEECBData;

typedef int (__cdecl *sceSdrUserCommandFunction)(unsigned int command, void *data, int size);



//-------------------------------------------------------------------------
// Function declarations

int __cdecl module_start(int ac, char **av);
int __cdecl module_stop(int ac, char **av);
int __cdecl sdrdrv_0(int ac, char **av);
int __cdecl sceSdrChangeThreadPriority(int priority_main, int priority_cb);
int sce_sdr_loop(void);
void *__cdecl sdrFunc(int fno, void *buffer, int length);
sceSdrUserCommandFunction __cdecl sceSdrSetUserCommandFunction(int, sceSdrUserCommandFunction);
void __noreturn sceSifCmdLoop2(void);
int __cdecl sce_sdrDMA0IntrHandler(int core, void *common);
int __cdecl sce_sdrDMA1IntrHandler(int core, void *common);
int __cdecl sce_sdrSpu2IntrHandler(int core_bit, void *common);
void __noreturn sce_sdrcb_loop(void);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_sdrdrv;
int thid_main = 0; // idb
int thid_cb = 0; // idb
int ret = 0; // weak
sceSdrUserCommandFunction sceSdr_vUserCommandFunction[16];
SdrEECBData eeCBData; // weak
SdrEECBData eeCBDataSend; // weak
int initial_priority_main; // weak
SifRpcDataQueue_t rpc_qd; // idb
SifRpcServerData_t rpc_sd; // idb
int initial_priority_cb; // weak
int procbat_returns[384]; // weak
int gRpcArg[16]; // weak
sceSdEffectAttr e_attr; // idb
SifRpcClientData_t cd; // idb


//----- (00400000) --------------------------------------------------------
int __cdecl module_start(int ac, char **av)
{
	int code; // $s0
	int result; // $v0
	int ac_tmp; // $s2
	const char **av_tmp; // $s1
	const char *p; // $s0
	int pval1; // $a1
	int pval2; // $a1
	iop_thread_t thprarm; // [sp+10h] [-20h] BYREF
	int state; // [sp+28h] [-8h] BYREF

	CpuSuspendIntr(&state);
	code = RegisterLibraryEntries(&_exp_sdrdrv);
	CpuResumeIntr(state);
	result = 1;
	if ( !code )
	{
		ac_tmp = 1;
		Kprintf("SDR driver version 4.0.1 (C) SCEI\n");
		initial_priority_main = 24;
		initial_priority_cb = 24;
		thid_main = 0;
		thid_cb = 0;
		av_tmp = (const char **)(av + 1);
		if ( ac > 1 )
		{
			do
			{
				if ( !strncmp("thpri=", *av_tmp, 6) )
				{
					p = *av_tmp + 6;
					if ( (look_ctype_table(*p) & 4) != 0 )
					{
						pval1 = strtol(p, 0, 10);
						if ( (unsigned int)(pval1 - 9) >= 0x73 )
						{
							Kprintf(" SDR driver error: invalid priority %d\n", pval1);
							pval1 = 24;
						}
						initial_priority_main = pval1;
					}
					while ( (look_ctype_table(*p) & 4) != 0 )
						++p;
					if ( *p == 44 && (look_ctype_table(p[1]) & 4) != 0 )
					{
						pval2 = strtol(p + 1, 0, 10);
						if ( (unsigned int)(pval2 - 9) >= 0x73 )
						{
							Kprintf(" SDR driver error: invalid priority %d\n", pval2);
							pval2 = 24;
						}
						initial_priority_cb = pval2;
					}
					if ( initial_priority_cb < initial_priority_main )
					{
						Kprintf(" SDR driver ERROR:\n");
						Kprintf("   callback th. priority is higher than main th. priority.\n");
						initial_priority_cb = initial_priority_main;
					}
					Kprintf(" SDR driver: thread priority: main=%d, callback=%d\n", initial_priority_main, initial_priority_cb);
				}
				++ac_tmp;
				++av_tmp;
			}
			while ( ac_tmp < ac );
		}
		thprarm.attr = 0x2000000;
		thprarm.thread = (void (__cdecl *)(void *))sce_sdr_loop;
		thprarm.stacksize = 2048;
		thprarm.option = 0;
		thprarm.priority = initial_priority_main;
		thid_main = CreateThread(&thprarm);
		result = 1;
		if ( thid_main > 0 )
		{
			StartThread(thid_main, 0);
			Kprintf(" Exit rsd_main \n");
			return 2;
		}
	}
	return result;
}
// 4015B0: using guessed type int initial_priority_main;
// 401624: using guessed type int initial_priority_cb;

//----- (00400284) --------------------------------------------------------
int __cdecl module_stop(int ac, char **av)
{
	int code; // $s0
	int result; // $v0
	int state; // [sp+10h] [-8h] BYREF

	CpuSuspendIntr(&state);
	code = ReleaseLibraryEntries(&_exp_sdrdrv);
	CpuResumeIntr(state);
	result = 2;
	if ( !code )
	{
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
	return result;
}

//----- (004003A0) --------------------------------------------------------
int __cdecl _start(int ac, char **av)
{
	if ( ac >= 0 )
		return module_start(ac, av);
	else
		return module_stop(-ac, av);
}

//----- (004003D4) --------------------------------------------------------
int __cdecl sceSdrChangeThreadPriority(int priority_main, int priority_cb)
{
	int cur_priority; // $s0
	int result; // $v0
	iop_thread_info_t thstatus; // [sp+10h] [-48h] BYREF

	cur_priority = priority_cb;
	if ( (unsigned int)(priority_main - 9) >= 0x73 || (unsigned int)(priority_cb - 9) >= 0x73 )
		return -403;
	if ( priority_cb < priority_main )
	{
		cur_priority = priority_main;
		Kprintf(" SDR driver ERROR:\n");
		Kprintf("   callback th. priority is higher than main th. priority.\n");
	}
	ReferThreadStatus(0, &thstatus);
	ChangeThreadPriority(0, 8);
	if ( thid_main <= 0 || (result = ChangeThreadPriority(thid_main, priority_main), result >= 0) )
	{
		if ( thid_cb <= 0 )
		{
			initial_priority_cb = cur_priority;
		}
		else
		{
			result = ChangeThreadPriority(thid_cb, cur_priority);
			if ( result < 0 )
				return result;
		}
		ChangeThreadPriority(0, thstatus.currentPriority);
		return 0;
	}
	return result;
}
// 401624: using guessed type int initial_priority_cb;

//----- (004004E0) --------------------------------------------------------
int sce_sdr_loop(void)
{
	int thid; // $v0
	int tmpi1; // $v1
	int tmpi2; // $v0

	sceSifInitRpc(0);
	thid = GetThreadId();
	sceSifSetRpcQueue(&rpc_qd, thid);
	sceSifRegisterRpc(&rpc_sd, 0x80000701, sdrFunc, gRpcArg, 0, 0, &rpc_qd);
	tmpi1 = 0;
	tmpi2 = 0;
	do
	{
		sceSdr_vUserCommandFunction[tmpi2] = 0;
		tmpi2 = ++tmpi1;
	}
	while ( tmpi1 < 16 );
	sceSifRpcLoop(&rpc_qd);
	return 0;
}
// 401C30: using guessed type int gRpcArg[16];

//----- (00400588) --------------------------------------------------------
void *__cdecl sdrFunc(int fno, void *buffer, int length)
{
	u16 fno_tmp; // $s1
	unsigned int fno_mask_tmp_1; // $v1
	int fno_eff_param; // $a0
	unsigned int fid; // $v0
	unsigned int fno_mask_tmp_2; // $a0
	int ret_tmp_2; // $v0
	int ret_tmp_1; // $v0
	int xfer_handler_arg0; // $a0
	int (__cdecl *xfer_handler_arg1)(int, void *); // $a1
	int (__cdecl *intr_handler_arg0)(int, void *); // $a0
	iop_thread_t thparam; // [sp+18h] [-18h] BYREF

	fno_tmp = fno;
	fno_mask_tmp_1 = fno & 0xFFF0;
	ret = 0;
	if ( fno_mask_tmp_1 == 0x8190 )
	{
		ret = sceSdCleanEffectWorkArea(*((_DWORD *)buffer + 1), *((_DWORD *)buffer + 2), *((_DWORD *)buffer + 3));
		fno_mask_tmp_2 = fno_tmp & 0xFFF0;
		goto LABEL_127;
	}
	if ( fno_mask_tmp_1 > 0x8190 )
	{
		if ( fno_mask_tmp_1 != 0x9060 )
		{
			if ( fno_mask_tmp_1 > 0x9060 )
			{
				if ( fno_mask_tmp_1 != 0x90C0 )
				{
					if ( fno_mask_tmp_1 > 0x90C0 )
					{
						if ( fno_mask_tmp_1 != 0x90F0 )
						{
							if ( fno_mask_tmp_1 > 0x90F0 )
							{
								if ( fno_mask_tmp_1 != 0xE620 )
								{
									if ( fno_mask_tmp_1 == 0xE630 )
									{
										fno_mask_tmp_2 = fno & 0xFFF0;
										if ( thid_cb > 0 )
										{
											TerminateThread(thid_cb);
											DeleteThread(thid_cb);
											thid_cb = 0;
											Kprintf("SDR callback thread deleted\n");
											fno_mask_tmp_2 = fno_tmp & 0xFFF0;
										}
										goto LABEL_127;
									}
									goto LABEL_125;
								}
								thparam.attr = 0x2000000;
								thparam.thread = (void (__cdecl *)(void *))sce_sdrcb_loop;
								thparam.stacksize = 2048;
								thparam.option = 0;
								thparam.priority = initial_priority_cb;
								thid_cb = CreateThread(&thparam);
								StartThread(thid_cb, 0);
								Kprintf("SDR callback thread created\n");
								fno_mask_tmp_2 = fno_tmp & 0xFFF0;
								goto LABEL_127;
							}
							if ( fno_mask_tmp_1 != 0x90D0 )
							{
								fid = fno & 0xF0;
								if ( fno_mask_tmp_1 != 0x90E0 )
									goto LABEL_125;
								goto LABEL_120;
							}
						}
					}
					else if ( fno_mask_tmp_1 != 0x9090 )
					{
						if ( fno_mask_tmp_1 > 0x9090 )
						{
							if ( fno_mask_tmp_1 != 0x90A0 )
							{
								fid = fno & 0xF0;
								if ( fno_mask_tmp_1 != 0x90B0 )
									goto LABEL_125;
								goto LABEL_120;
							}
						}
						else if ( fno_mask_tmp_1 != 0x9070 )
						{
							fid = fno & 0xF0;
							if ( fno_mask_tmp_1 != 0x9080 )
								goto LABEL_125;
							goto LABEL_120;
						}
					}
				}
			}
			else if ( fno_mask_tmp_1 != 0x9000 )
			{
				if ( fno_mask_tmp_1 <= 0x9000 )
				{
					if ( fno_mask_tmp_1 == 0x81C0 )
					{
						ret_tmp_1 = sceSdProcBatch(
													(sceSdBatch *)buffer + 1,
													(u32 *)&procbat_returns[1],
													*((u16 *)buffer + 1));
					}
					else
					{
						if ( fno_mask_tmp_1 <= 0x81C0 )
						{
							if ( fno_mask_tmp_1 == 0x81A0 )
							{
								ret = sceSdSetEffectMode(fno & 0xF, (sceSdEffectAttr *)buffer);
								fno_mask_tmp_2 = fno_tmp & 0xFFF0;
							}
							else
							{
								fno_eff_param = fno & 0xF;
								if ( fno_mask_tmp_1 != 0x81B0 )
									goto LABEL_125;
								ret = sceSdSetEffectModeParams(fno_eff_param, (sceSdEffectAttr *)buffer);
								fno_mask_tmp_2 = fno_tmp & 0xFFF0;
							}
							goto LABEL_127;
						}
						if ( fno_mask_tmp_1 != 0x81D0 )
						{
							if ( fno_mask_tmp_1 != 0x8F10 )
								goto LABEL_125;
							ret = sceSdrChangeThreadPriority(*((_DWORD *)buffer + 1), *((_DWORD *)buffer + 2));
							fno_mask_tmp_2 = fno_tmp & 0xFFF0;
							goto LABEL_127;
						}
						ret_tmp_1 = sceSdProcBatchEx(
													(sceSdBatch *)buffer + 1,
													(u32 *)&procbat_returns[1],
													*((u16 *)buffer + 1),
													*((_DWORD *)buffer + 1));
					}
					ret = ret_tmp_1;
					procbat_returns[0] = ret_tmp_1;
LABEL_126:
					fno_mask_tmp_2 = fno_tmp & 0xFFF0;
					goto LABEL_127;
				}
				if ( fno_mask_tmp_1 != 0x9030 )
				{
					if ( fno_mask_tmp_1 > 0x9030 )
					{
						if ( fno_mask_tmp_1 != 0x9040 )
						{
							fid = fno & 0xF0;
							if ( fno_mask_tmp_1 != 0x9050 )
								goto LABEL_125;
							goto LABEL_120;
						}
					}
					else if ( fno_mask_tmp_1 != 0x9010 )
					{
						fid = fno & 0xF0;
						if ( fno_mask_tmp_1 != 0x9020 )
							goto LABEL_125;
LABEL_120:
						if ( *(sceSdrUserCommandFunction *)((char *)sceSdr_vUserCommandFunction + (fid >> 2)) )
						{
							ret = (*(int (__fastcall **)(_WORD, void *, int))((char *)sceSdr_vUserCommandFunction + (fid >> 2)))(
											fno,
											buffer,
											length);
							fno_mask_tmp_2 = fno_tmp & 0xFFF0;
							goto LABEL_127;
						}
						goto LABEL_126;
					}
				}
			}
		}
		fid = fno & 0xF0;
		goto LABEL_120;
	}
	if ( fno_mask_tmp_1 == 0x80B0 )
	{
		ret = sceSdProcBatch(*((sceSdBatch **)buffer + 1), *((u32 **)buffer + 2), *((_DWORD *)buffer + 3));
		fno_mask_tmp_2 = fno_tmp & 0xFFF0;
		goto LABEL_127;
	}
	if ( fno_mask_tmp_1 > 0x80B0 )
	{
		if ( fno_mask_tmp_1 == 0x8130 )
		{
			ret = sceSdSetEffectAttr(fno & 0xF, (sceSdEffectAttr *)buffer);
			fno_mask_tmp_2 = fno_tmp & 0xFFF0;
		}
		else if ( fno_mask_tmp_1 > 0x8130 )
		{
			if ( fno_mask_tmp_1 == 0x8160 )
			{
				if ( *((_DWORD *)buffer + 1) )
				{
					xfer_handler_arg0 = 1;
					if ( *((_DWORD *)buffer + 2) )
						xfer_handler_arg1 = sce_sdrDMA1IntrHandler;
					else
						xfer_handler_arg1 = 0;
				}
				else
				{
					xfer_handler_arg0 = 0;
					if ( *((_DWORD *)buffer + 2) )
						xfer_handler_arg1 = sce_sdrDMA0IntrHandler;
					else
						xfer_handler_arg1 = 0;
				}
				ret = (int)sceSdSetTransIntrHandler(xfer_handler_arg0, xfer_handler_arg1, 0);
				fno_mask_tmp_2 = fno_tmp & 0xFFF0;
				goto LABEL_127;
			}
			if ( fno_mask_tmp_1 > 0x8160 )
			{
				if ( fno_mask_tmp_1 == 0x8170 )
				{
					intr_handler_arg0 = sce_sdrSpu2IntrHandler;
					if ( !*((_DWORD *)buffer + 1) )
						intr_handler_arg0 = 0;
					ret = (int)sceSdSetSpu2IntrHandler(intr_handler_arg0, 0);
					fno_mask_tmp_2 = fno_tmp & 0xFFF0;
					goto LABEL_127;
				}
				if ( fno_mask_tmp_1 != 0x8180 )
					goto LABEL_125;
				ret = sceSdStopTrans(*((_DWORD *)buffer + 1));
				fno_mask_tmp_2 = fno_tmp & 0xFFF0;
			}
			else if ( fno_mask_tmp_1 == 0x8140 )
			{
				sceSdGetEffectAttr(fno & 0xF, &e_attr);
				fno_mask_tmp_2 = fno_tmp & 0xFFF0;
			}
			else
			{
				if ( fno_mask_tmp_1 != 0x8150 )
					goto LABEL_125;
				ret = sceSdClearEffectWorkArea(*((_DWORD *)buffer + 1), *((_DWORD *)buffer + 2), *((_DWORD *)buffer + 3));
				fno_mask_tmp_2 = fno_tmp & 0xFFF0;
			}
		}
		else if ( fno_mask_tmp_1 == 0x80E0 )
		{
			ret = sceSdBlockTrans(
							*((_WORD *)buffer + 2),
							*((_WORD *)buffer + 4),
							*((u8 **)buffer + 3),
							*((_DWORD *)buffer + 4),
							*((_DWORD *)buffer + 5));
			fno_mask_tmp_2 = fno_tmp & 0xFFF0;
		}
		else if ( fno_mask_tmp_1 > 0x80E0 )
		{
			if ( fno_mask_tmp_1 == 0x80F0 )
			{
				ret = sceSdVoiceTransStatus(*((_WORD *)buffer + 2), *((_WORD *)buffer + 4));
				fno_mask_tmp_2 = fno_tmp & 0xFFF0;
			}
			else
			{
				if ( fno_mask_tmp_1 != 0x8100 )
					goto LABEL_125;
				ret = sceSdBlockTransStatus(*((_WORD *)buffer + 2), *((_WORD *)buffer + 4));
				fno_mask_tmp_2 = fno_tmp & 0xFFF0;
			}
		}
		else if ( fno_mask_tmp_1 == 0x80C0 )
		{
			ret = sceSdProcBatchEx(
							*((sceSdBatch **)buffer + 1),
							*((u32 **)buffer + 2),
							*((_DWORD *)buffer + 3),
							*((_DWORD *)buffer + 4));
			fno_mask_tmp_2 = fno_tmp & 0xFFF0;
		}
		else
		{
			if ( fno_mask_tmp_1 != 0x80D0 )
				goto LABEL_125;
			ret = sceSdVoiceTrans(
							*((_WORD *)buffer + 2),
							*((_WORD *)buffer + 4),
							*((u8 **)buffer + 3),
							*((u32 **)buffer + 4),
							*((_DWORD *)buffer + 5));
			fno_mask_tmp_2 = fno_tmp & 0xFFF0;
		}
		goto LABEL_127;
	}
	if ( fno_mask_tmp_1 == 0x8050 )
	{
		sceSdSetAddr(*((_WORD *)buffer + 2), *((_DWORD *)buffer + 2));
		fno_mask_tmp_2 = fno_tmp & 0xFFF0;
		goto LABEL_127;
	}
	if ( fno_mask_tmp_1 > 0x8050 )
	{
		if ( fno_mask_tmp_1 == 0x8080 )
		{
			ret_tmp_2 = sceSdGetCoreAttr(*((_WORD *)buffer + 2));
		}
		else
		{
			if ( fno_mask_tmp_1 <= 0x8080 )
			{
				if ( fno_mask_tmp_1 == 0x8060 )
				{
					ret = sceSdGetAddr(*((_WORD *)buffer + 2));
					fno_mask_tmp_2 = fno_tmp & 0xFFF0;
				}
				else
				{
					if ( fno_mask_tmp_1 != 0x8070 )
						goto LABEL_125;
					sceSdSetCoreAttr(*((_WORD *)buffer + 2), *((_WORD *)buffer + 4));
					fno_mask_tmp_2 = fno_tmp & 0xFFF0;
				}
				goto LABEL_127;
			}
			if ( fno_mask_tmp_1 == 0x8090 )
			{
				ret_tmp_2 = sceSdNote2Pitch(
											*((_WORD *)buffer + 2),
											*((_WORD *)buffer + 4),
											*((_WORD *)buffer + 6),
											*((_WORD *)buffer + 8));
			}
			else
			{
				if ( fno_mask_tmp_1 != 0x80A0 )
					goto LABEL_125;
				ret_tmp_2 = sceSdPitch2Note(*((_WORD *)buffer + 2), *((_WORD *)buffer + 4), *((_WORD *)buffer + 6));
			}
		}
LABEL_90:
		ret = ret_tmp_2;
		fno_mask_tmp_2 = fno_tmp & 0xFFF0;
		goto LABEL_127;
	}
	if ( fno_mask_tmp_1 == 0x8020 )
	{
		ret_tmp_2 = sceSdGetParam(*((_WORD *)buffer + 2));
		goto LABEL_90;
	}
	if ( fno_mask_tmp_1 > 0x8020 )
	{
		if ( fno_mask_tmp_1 == 0x8030 )
		{
			sceSdSetSwitch(*((_WORD *)buffer + 2), *((_DWORD *)buffer + 2));
			fno_mask_tmp_2 = fno_tmp & 0xFFF0;
		}
		else
		{
			if ( fno_mask_tmp_1 != 0x8040 )
				goto LABEL_125;
			ret = sceSdGetSwitch(*((_WORD *)buffer + 2));
			fno_mask_tmp_2 = fno_tmp & 0xFFF0;
		}
	}
	else if ( fno_mask_tmp_1 == 0x8000 )
	{
		ret = sceSdInit(*((_DWORD *)buffer + 1));
		fno_mask_tmp_2 = fno_tmp & 0xFFF0;
	}
	else
	{
		if ( fno_mask_tmp_1 != 0x8010 )
		{
LABEL_125:
			Kprintf("SDR driver ERROR: unknown command %x \n", fno_tmp & 0xFFF0);
			goto LABEL_126;
		}
		sceSdSetParam(*((_WORD *)buffer + 2), *((_WORD *)buffer + 4));
		fno_mask_tmp_2 = fno_tmp & 0xFFF0;
	}
LABEL_127:
	if ( fno_mask_tmp_2 == 0x81C0 )
		return procbat_returns;
	if ( fno_mask_tmp_2 <= 0x81C0 )
	{
		if ( fno_mask_tmp_2 == 0x8140 )
			return &e_attr;
		return &ret;
	}
	if ( fno_mask_tmp_2 == 0x81D0 )
		return procbat_returns;
	return &ret;
}
// 4014E0: using guessed type int ret;
// 401624: using guessed type int initial_priority_cb;
// 401630: using guessed type int procbat_returns[384];

//----- (00400DC8) --------------------------------------------------------
sceSdrUserCommandFunction __cdecl sceSdrSetUserCommandFunction(int a1, sceSdrUserCommandFunction a2)
{
	int fid; // $v1
	sceSdrUserCommandFunction oldf; // $v0

	if ( (unsigned int)(a1 - 0x9000) >= 0xF1 )
		return (sceSdrUserCommandFunction)-1;
	fid = (u8)(a1 & 0xF0) >> 2;
	oldf = *(sceSdrUserCommandFunction *)((char *)sceSdr_vUserCommandFunction + fid);
	*(sceSdrUserCommandFunction *)((char *)sceSdr_vUserCommandFunction + fid) = a2;
	return oldf;
}

//----- (00400E10) --------------------------------------------------------
void __noreturn sceSifCmdLoop2(void)
{
	SdrEECBData *send_data; // $v1
	SdrEECBData *cur_data; // $v0
	int voice_bit; // $t1
	int status; // $t2
	int opt; // $t3
	int state[2]; // [sp+28h] [-8h] BYREF

	while ( 1 )
	{
		if ( eeCBData.mode )
		{
			while ( 1 )
			{
				CpuSuspendIntr(state);
				send_data = &eeCBDataSend;
				cur_data = &eeCBData;
				do
				{
					voice_bit = cur_data->voice_bit;
					status = cur_data->status;
					opt = cur_data->opt;
					send_data->mode = cur_data->mode;
					send_data->voice_bit = voice_bit;
					send_data->status = status;
					send_data->opt = opt;
					cur_data = (SdrEECBData *)((char *)cur_data + 16);
					send_data = (SdrEECBData *)((char *)send_data + 16);
				}
				while ( cur_data != &eeCBDataSend );
				CpuResumeIntr(state[0]);
				sceSifCallRpc(&cd, 0, 0, &eeCBDataSend, 64, 0, 0, 0, 0);
				CpuSuspendIntr(state);
				if ( eeCBData.mode == eeCBDataSend.mode )
					break;
				eeCBData.mode &= ~eeCBDataSend.mode;
				CpuResumeIntr(state[0]);
			}
			eeCBData.mode = 0;
			iCancelWakeupThread(0);
			CpuResumeIntr(state[0]);
		}
		SleepThread();
	}
}
// 401530: using guessed type SdrEECBData eeCBData;
// 401570: using guessed type SdrEECBData eeCBDataSend;

//----- (00400F2C) --------------------------------------------------------
int __cdecl sce_sdrDMA0IntrHandler(int core, void *common)
{
	eeCBData.mode |= 0x100u;
	iWakeupThread(thid_cb);
	return 0;
}
// 401530: using guessed type SdrEECBData eeCBData;

//----- (00400F6C) --------------------------------------------------------
int __cdecl sce_sdrDMA1IntrHandler(int core, void *common)
{
	eeCBData.mode |= 0x200u;
	iWakeupThread(thid_cb);
	return 0;
}
// 401530: using guessed type SdrEECBData eeCBData;

//----- (00400FAC) --------------------------------------------------------
int __cdecl sce_sdrSpu2IntrHandler(int core_bit, void *common)
{
	eeCBData.mode |= 0x400u;
	eeCBData.voice_bit = core_bit;
	iWakeupThread(thid_cb);
	return 0;
}
// 401530: using guessed type SdrEECBData eeCBData;

//----- (00400FF0) --------------------------------------------------------
void __noreturn sce_sdrcb_loop(void)
{
	int i; // $v0

	eeCBData.mode = 0;
	while ( sceSifBindRpc(&cd, 0x80000704, 0) >= 0 )
	{
		i = 9998;
		while ( i-- != -1 )
			;
		if ( cd.server )
			sceSifCmdLoop2();
	}
	Kprintf("error \n");
	while ( 1 )
		;
}
// 401530: using guessed type SdrEECBData eeCBData;
