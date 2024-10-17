
#include "irx_imports.h"
#include "../00common/defs.h"

IRX_ID("cdvd_st_driver", 2, 2);

extern struct irx_export_table _exp_cdvdstm;

//-------------------------------------------------------------------------
// Function declarations

int __fastcall vCancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg);
int vSetEventFlag();
int vClearEventFlag();
int cdvdstm_4();
int cdvdstm_2();
BOOL __fastcall alarm_cb(void *);
int __fastcall sceCdStream0_inner(unsigned int rdsize, char *addrarg, int modearg, int *error_ptr);
int __fastcall sceCdStream0(int rdsize_sectors, char *addrarg, int modearg, int *error_ptr);
unsigned int __fastcall iop_stream_handler(unsigned int posszarg1, unsigned int posszarg2, void *buffer, int cmdid, const sceCdRMode *rmode, int *error_ptr);
unsigned int __cdecl iop_stream_intr_cb(void *userdata);
int cdrom_stm_init();
int cdrom_stm_deinit();
int __fastcall cdrom_stm_devctl(iop_file_t *f, const char *a2, int a3, void *inbuf, unsigned int inbuf_len, void *outbuf, unsigned int outbuf_len);
int __cdecl cdrom_stm_nulldev();
__int64 __cdecl cdrom_stm_nulldev64();
int __fastcall _start(int);
BOOL __fastcall stm_alarm_timeout_cb(void *a1);
void __fastcall ee_stream_handler_normal(cdrom_stm_devctl_t *instruct, int inbuf_len, int *outres_ptr);
unsigned int __fastcall ee_stream_intr_cb_normal(void *userdata);
void __fastcall ee_stream_handler_cdda(cdrom_stm_devctl_t *instruct, int inbuf_len, int *outres_ptr);
unsigned int __fastcall ee_stream_intr_cb_cdda(void *userdata);
unsigned int __fastcall cdvdstm_memcpy(_DWORD *a1, _DWORD *a2, unsigned int a3);
void cdvdstm_1();
int Kprintf(const char *format, ...);
int __cdecl RegisterLibraryEntries(struct irx_export_table *exports);
int __cdecl ReleaseLibraryEntries(struct irx_export_table *exports);
int __cdecl CpuSuspendIntr(int *state);
int __cdecl CpuResumeIntr(int state);
int QueryIntrContext(void);
int printf(const char *format, ...);
int __cdecl DelayThread(int usec);
int __cdecl iSetAlarm(iop_sys_clock_t *sys_clock, unsigned int (__cdecl *alarm_cb)(void *), void *arg);
int __cdecl CancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg);
int __cdecl iCancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg);
int __cdecl SetEventFlag(int ef, u32 bits);
int __cdecl iSetEventFlag(int ef, u32 bits);
int __cdecl ClearEventFlag(int ef, u32 bits);
int __cdecl iClearEventFlag(int ef, u32 bits);
int __cdecl WaitEventFlag(int ef, u32 bits, int mode, u32 *resbits);
int __cdecl CreateSema(iop_sema_t *sema);
int __cdecl DeleteSema(int semid);
int __cdecl SignalSema(int semid);
int __cdecl WaitSema(int semid);
int __cdecl sceSifSetDma(SifDmaTransfer_t *dmat, int count);
int __cdecl sceSifDmaStat(int trid);
int __cdecl AddDrv(iop_device_t *device);
int __cdecl DelDrv(const char *name);
int __cdecl sceCdSync(int mode);
int sceCdGetDiskType(void);
int sceCdBreak(void);
int __cdecl sceCdReadCDDA(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode);
int sceCdNop(void);
int __cdecl sceCdstm0Cb(void (__cdecl *p)(int));
int __cdecl sceCdstm1Cb(void (__cdecl *p)(int));
int __cdecl sceCdSC(int code, int *param);
int sceCdStStop(void);
int __cdecl sceCdRE(unsigned int lsn, unsigned int sectors, void *buf, sceCdRMode *mode);

static void iop_stream_intr_cb_thunk(int userdata)
{
	iop_stream_intr_cb((void *)userdata);
}

static void ee_stream_intr_cb_normal_thunk(int userdata)
{
	ee_stream_intr_cb_normal((void *)userdata);
}

static void ee_stream_intr_cb_cdda_thunk(int userdata)
{
	ee_stream_intr_cb_cdda((void *)userdata);
}

//-------------------------------------------------------------------------
// Data declarations

int cdvdstm_verbose = 0; // weak
int cdvdstm_in_deldrv = 0; // weak
int cdvdstm_bufmax = 0; // weak
int cdvdstm_numbytes = 0; // weak
int cdvdstm_bankmax = 0; // weak
void *cdvdstm_buffer = NULL;
unsigned int cdvdstm_sectorcount = 0u; // idb
int cdvdstm_last_error_for_iop = 0; // idb
int cdvdstm_retryerr_iop = 0; // weak
int cdvdstm_retrycnt_iop = 0; // weak
static iop_device_ops_t cdrom_stm_dev_ops =
    {
        &cdrom_stm_init,
        &cdrom_stm_deinit,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        &cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev64,
        &cdrom_stm_devctl,
        (void *)&cdrom_stm_nulldev,
        (void *)&cdrom_stm_nulldev,
        &cdrom_stm_nulldev,
    };
iop_device_t cdrom_stm_dev = { "cdrom_stm", 268435472u, 1u, "CD-ROM_STM ", &cdrom_stm_dev_ops }; // idb
int cdvdstm_last_error_for_ee = 0;
int cdvdstm_bufsz2 = 0; // weak
int cdvdstm_chunksz2 = 0; // weak
int cdvdstm_bankcnt2 = 0; // weak
void *cdvdstm_buffer2 = NULL;
u32 cdvdstm_sectorcount2 = 0u; // idb
int cdvdstm_retryerr_ee = 0; // weak
int cdvdstm_retrycnt_ee_normal = 0; // weak
int cdvdstm_usedchunksize2 = 2352; // weak
u32 cdvdstm_retrycnt_ee_cdda = 0u;
sceCdRMode rmode_for_stream0; // weak
int cdvdstm_tgt; // weak
int cdvdstm_semid; // idb
int cdvdstm_ef; // idb
char cdvdstm_usedmap_iop[512]; // weak
unsigned int cdvdstm_lsn_iop; // idb
int cdvdstm_bankgp_iop; // weak
int cdvdstm_bankcur_iop; // weak
int cdvdstm_bankoffs_iop; // weak
sceCdRMode cdvdstm_mode_iop; // idb
int cdvdstm_stmstart_iop; // weak
iop_sys_clock_t cdvdstm_curclk_iop; // idb
SifDmaTransfer_t cdvdstm_dmat; // idb
int cdvdstm_readlbn_ee_normal; // weak
SifDmaTransfer_t cdvdstm_dmat2; // idb
u32 cdvdstm_readlbn_ee_cdda; // idb
char cdvdstm_usedmap_ee[512];
u32 cdvdstm_lsn_ee; // idb
int cdvdstm_bankgp_ee; // weak
int cdvdstm_bankcur_ee; // weak
int cdvdstm_bankoffs_ee; // weak
sceCdRMode cdvdstm_mode_ee;
int cdvdstm_stmstart_ee; // weak
iop_sys_clock_t cdvdstm_curclk_ee; // idb


//----- (00400000) --------------------------------------------------------
int __fastcall vCancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	return (QueryIntrContext() ? iCancelAlarm : CancelAlarm)(alarm_cb, arg);
}

//----- (00400050) --------------------------------------------------------
int vSetEventFlag()
{
	return (QueryIntrContext() ? iSetEventFlag : SetEventFlag)(cdvdstm_ef, 8u);
}

//----- (004000A0) --------------------------------------------------------
int vClearEventFlag()
{
	return (QueryIntrContext() ? iClearEventFlag : ClearEventFlag)(cdvdstm_ef, 0xFFFFFFF7);
}

//----- (004000F0) --------------------------------------------------------
int cdvdstm_4()
{
	if ( cdvdstm_verbose > 0 )
		printf("Dummy Entry Called\n");
	return 0;
}
// 404688: using guessed type int cdvdstm_verbose;

//----- (00400124) --------------------------------------------------------
int cdvdstm_2()
{
	cdrom_stm_devctl_t instruct; // [sp+10h] [-38h] BYREF
	int outres[8]; // [sp+28h] [-20h] BYREF

	memset(&instruct, 0, 12);
	instruct.cmdid = 3;
	instruct.rmode.datapattern = 0;
	instruct.rmode.spindlctrl = 0;
	instruct.rmode.trycount = 0;
	ee_stream_handler_normal(&instruct, 20, outres);
	sceCdStStop();
	return 0;
}

//----- (00400174) --------------------------------------------------------
BOOL __fastcall alarm_cb(void *a1)
{
	Kprintf("Stm Iop Read Time Out %d(msec)\n", *(_DWORD *)a1 / 0x9000u);
	return sceCdBreak() == 0;
}

//----- (004001B8) --------------------------------------------------------
int __fastcall sceCdStream0_inner(unsigned int rdsize, char *addrarg, int modearg, int *error_ptr)
{
	int cur_size; // $s2
	unsigned int streamres; // $s1
	int scres; // [sp+18h] [-10h] BYREF
	u32 efbits; // [sp+1Ch] [-Ch] BYREF
	int err; // [sp+20h] [-8h] BYREF

	if ( cdvdstm_verbose > 0 )
		Kprintf("sceCdStream0 call read size= %d mode= %d addr= %08x\n", rdsize, modearg, addrarg);
	cur_size = 0;
	if ( !sceCdSC(0xFFFFFFFF, &scres) )
		return 0;
	*error_ptr = 0;
	if ( !modearg )
		return iop_stream_handler(0, rdsize, addrarg, 2, &rmode_for_stream0, error_ptr);
	vSetEventFlag();
	err = 0;
	streamres = 0;
	while ( (!err || streamres) )
	{
		WaitEventFlag(cdvdstm_ef, 8u, 0, &efbits);
		streamres = iop_stream_handler(0, rdsize - cur_size, &addrarg[cur_size], 2, &rmode_for_stream0, &err);
		if ( rdsize - cur_size != streamres )
			vClearEventFlag();
		cur_size += streamres;
		if ( err )
			*error_ptr = err;
		if ( cdvdstm_verbose > 0 )
			Kprintf("sceCdStream0 BLK cur_size= %d req_size= %d err 0x%x\n", cur_size, rdsize, err);
		if ( (unsigned int)cur_size == rdsize )
			break;
	}
	return cur_size;
}
// 404688: using guessed type int cdvdstm_verbose;
// 404770: using guessed type sceCdRMode rmode_for_stream0;

//----- (00400358) --------------------------------------------------------
int __fastcall sceCdStream0(int rdsize_sectors, char *addrarg, int modearg, int *error_ptr)
{
	return sceCdStream0_inner(rdsize_sectors << 11, addrarg, modearg, error_ptr) / 2048;
}

//----- (00400384) --------------------------------------------------------
unsigned int __fastcall iop_stream_handler(
				unsigned int posszarg1,
				unsigned int posszarg2,
				void *buffer,
				int cmdid,
				const sceCdRMode *rmode,
				int *error_ptr)
{
	int retryflag; // $s7
	int bankcur_tmp; // $v1
	unsigned int i; // $s1
	unsigned int written_chunk_size_tmp; // $s4
	int bankcur_next_tmp1; // $a0
	int chunk_size; // $s0
	int bankcur_next_tmp2; // $a0
	int state[2]; // [sp+20h] [-8h] BYREF
	unsigned int posszarg1_stk; // [sp+50h] [+28h] BYREF

	retryflag = 0;
	posszarg1_stk = posszarg1;
	if ( cdvdstm_verbose > 0 )
		Kprintf("CD Stream Call mode= %d\n", cmdid);
	*error_ptr = 0;
	if ( cdvdstm_stmstart_iop == 2 && cmdid != 9 && cmdid != 3 )
	{
		return 0;
	}
	switch ( cmdid )
	{
		case 8:
			sceCdSC(1, &cdvdstm_last_error_for_iop);
			if ( sceCdNop() != 0 )
				return 1;
			sceCdSC(0, &cdvdstm_last_error_for_iop);
			return 0;
		case 7:
			CpuSuspendIntr(state);
			vCancelAlarm((unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &cdvdstm_curclk_iop);
			sceCdSC(0, &cdvdstm_last_error_for_iop);
			CpuResumeIntr(state[0]);
			sceCdSync(0);
			vCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &cdvdstm_curclk_iop);
			return 1;
		case 6:
			bankcur_tmp = cdvdstm_bankcur_iop;
			if ( !cdvdstm_usedmap_iop[bankcur_tmp] )
			{
				bankcur_tmp += 1;
				if ( (unsigned int)bankcur_tmp >= (unsigned int)cdvdstm_bankmax )
					bankcur_tmp = 0;
				if ( !cdvdstm_usedmap_iop[bankcur_tmp] )
					bankcur_tmp = cdvdstm_bankcur_iop;
			}
			for ( i = 0; (i < (unsigned int)cdvdstm_bankmax) && cdvdstm_usedmap_iop[bankcur_tmp] && (cdvdstm_bankgp_iop != bankcur_tmp); i += 1 )
			{
				bankcur_tmp += 1;
				if ( (unsigned int)bankcur_tmp >= (unsigned int)cdvdstm_bankmax )
					bankcur_tmp = 0;
			}
			return i * ((unsigned int)cdvdstm_numbytes >> 11);
		case 5:
			sceCdstm0Cb((void (__cdecl *)(int))iop_stream_intr_cb_thunk);
			cdvdstm_bufmax = posszarg1;
			cdvdstm_sectorcount = posszarg1 / posszarg2;
			cdvdstm_numbytes = cdvdstm_sectorcount << 11;
			cdvdstm_buffer = buffer;
			cdvdstm_bankmax = posszarg2;
			Kprintf(
				"Stream Buffer 1Bank %dbyte %dbanks addr:%08x %dbyte used.\n",
				cdvdstm_numbytes,
				posszarg2,
				buffer,
				cdvdstm_numbytes * posszarg2);
			return 1;
		case 3:
			CpuSuspendIntr(state);
			cdvdstm_stmstart_iop = 0;
			vCancelAlarm((unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &cdvdstm_curclk_iop);
			sceCdSC(0, &cdvdstm_last_error_for_iop);
			CpuResumeIntr(state[0]);
			sceCdBreak();
			for ( i = 0; i < (unsigned int)cdvdstm_bankmax; i += 1 )
				cdvdstm_usedmap_iop[i] = 0;
			cdvdstm_bankoffs_iop = 0;
			cdvdstm_bankcur_iop = 0;
			cdvdstm_bankgp_iop = 0;
			sceCdSync(0);
			cdvdstm_last_error_for_iop = 0;
			sceCdSC(0xFFFFFFFE, &cdvdstm_last_error_for_iop);
			vCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &cdvdstm_curclk_iop);
			return 1;
		case 9:
			if ( sceCdSC(0xFFFFFFFF, &cdvdstm_last_error_for_iop) != 0 )
			{
				CpuSuspendIntr(state);
				cdvdstm_lsn_iop = posszarg1;
				for ( i = 0; i < (unsigned int)cdvdstm_bankmax; i += 1 )
					cdvdstm_usedmap_iop[i] = 0;
				cdvdstm_stmstart_iop = 2;
				CpuResumeIntr(state[0]);
				return 1;
			}
			return 0;
		case 1:
			cdvdstm_mode_iop.datapattern = rmode->datapattern;
			cdvdstm_mode_iop.trycount = rmode->trycount;
			cdvdstm_mode_iop.spindlctrl = rmode->spindlctrl;
			cdvdstm_retryerr_iop = 0;
			break;
		case 4:
			CpuSuspendIntr(state);
			vCancelAlarm((unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &cdvdstm_curclk_iop);
			sceCdSC(0, &cdvdstm_last_error_for_iop);
			retryflag = 1;
			CpuResumeIntr(state[0]);
			posszarg2 = 0;
			cmdid = 1;
			cdvdstm_lsn_iop = posszarg1;
			cdvdstm_bankoffs_iop = 0;
			cdvdstm_bankcur_iop = 0;
			cdvdstm_bankgp_iop = 0;
			sceCdSync(0);
			vCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &cdvdstm_curclk_iop);
			break;
	}
	if ( cmdid == 1 )
	{
		CpuSuspendIntr(state);
		retryflag = 1;
		vCancelAlarm((unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &cdvdstm_curclk_iop);
		sceCdSC(0, &cdvdstm_last_error_for_iop);
		CpuResumeIntr(state[0]);
		for ( i = 0; i < (unsigned int)cdvdstm_bankmax; i += 1 )
			cdvdstm_usedmap_iop[i] = 0;
		cdvdstm_lsn_iop = posszarg1;
		sceCdSC(0xFFFFFFE9, (int *)&posszarg1_stk);
		cdvdstm_bankoffs_iop = 0;
		cdvdstm_bankcur_iop = 0;
		cdvdstm_bankgp_iop = 0;
		sceCdSync(0);
		vCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &cdvdstm_curclk_iop);
		cdvdstm_stmstart_iop = 1;
		sceCdSC(1, &cdvdstm_last_error_for_iop);
		if ( !sceCdNop() )
		{
			sceCdSC(0, &cdvdstm_last_error_for_iop);
			return 0;
		}
	}
	CpuSuspendIntr(state);
	written_chunk_size_tmp = -1;
	for ( i = 0; i < posszarg2; i += chunk_size )
	{
		if ( !cdvdstm_usedmap_iop[cdvdstm_bankcur_iop] )
		{
			if ( cdvdstm_verbose > 0 )
				Kprintf(
					"CD read buffer over run %d %d %d %d %d gp %d pp %d\n",
					(unsigned __int8)cdvdstm_usedmap_iop[0],
					(unsigned __int8)cdvdstm_usedmap_iop[1],
					(unsigned __int8)cdvdstm_usedmap_iop[2],
					(unsigned __int8)cdvdstm_usedmap_iop[3],
					(unsigned __int8)cdvdstm_usedmap_iop[4],
					cdvdstm_bankgp_iop,
					cdvdstm_bankcur_iop);
			bankcur_next_tmp1 = cdvdstm_bankcur_iop;
			cdvdstm_bankcur_iop += 1;
			if ( (unsigned int)cdvdstm_bankcur_iop >= (unsigned int)cdvdstm_bankmax )
				cdvdstm_bankcur_iop = 0;
			written_chunk_size_tmp = i;
			if ( !cdvdstm_usedmap_iop[cdvdstm_bankcur_iop] )
			{
				cdvdstm_bankcur_iop = bankcur_next_tmp1;
			}
			break;
		}
		if ( (unsigned int)cdvdstm_bankoffs_iop >= (unsigned int)cdvdstm_numbytes )
		{
			cdvdstm_bankoffs_iop = 0;
			cdvdstm_usedmap_iop[cdvdstm_bankcur_iop] = 0;
			bankcur_next_tmp2 = cdvdstm_bankcur_iop;
			cdvdstm_bankcur_iop += 1;
			if ( (unsigned int)cdvdstm_bankcur_iop >= (unsigned int)cdvdstm_bankmax )
				cdvdstm_bankcur_iop = 0;
			if ( !cdvdstm_usedmap_iop[cdvdstm_bankcur_iop] || cdvdstm_bankgp_iop == cdvdstm_bankcur_iop )
			{
				cdvdstm_bankcur_iop = bankcur_next_tmp2;
				written_chunk_size_tmp = i;
				if ( cdvdstm_verbose > 0 )
				{
					Kprintf(
						"CD read buffer over run %d %d %d %d %d gp %d pp %d\n",
						(unsigned __int8)cdvdstm_usedmap_iop[0],
						(unsigned __int8)cdvdstm_usedmap_iop[1],
						(unsigned __int8)cdvdstm_usedmap_iop[2],
						(unsigned __int8)cdvdstm_usedmap_iop[3],
						(unsigned __int8)cdvdstm_usedmap_iop[4],
						cdvdstm_bankgp_iop,
						cdvdstm_bankcur_iop);
				}
				break;
			}
		}
		cdvdstm_memcpy(
			(_DWORD *)((char *)buffer + i),
			(_DWORD *)((char *)cdvdstm_buffer + cdvdstm_bankcur_iop * cdvdstm_numbytes + cdvdstm_bankoffs_iop),
			0x800u);
		chunk_size = ( (unsigned int)0x800 > posszarg2 - i ) ? (posszarg2 - i) : 0x800;
		cdvdstm_bankoffs_iop += chunk_size;
	}
	if ( written_chunk_size_tmp == 0xFFFFFFFF )
		written_chunk_size_tmp = posszarg2;
	CpuResumeIntr(state[0]);
	if ( !retryflag )
	{
		if ( sceCdSC(0xFFFFFFFF, &cdvdstm_last_error_for_iop) != 1
			&& !written_chunk_size_tmp
			&& !cdvdstm_retryerr_iop )
		{
			cdvdstm_retryerr_iop = 273;
		}
		*error_ptr = cdvdstm_retryerr_iop;
		cdvdstm_retryerr_iop = 0;
		return written_chunk_size_tmp;
	}
	return 1;
}
// 4005AC: conditional instruction was optimized away because $s6.4!=0
// 404688: using guessed type int cdvdstm_verbose;
// 404694: using guessed type int cdvdstm_bufmax;
// 404698: using guessed type int cdvdstm_numbytes;
// 40469C: using guessed type int cdvdstm_bankmax;
// 4046AC: using guessed type int cdvdstm_retryerr_iop;
// 404994: using guessed type int cdvdstm_bankgp_iop;
// 404998: using guessed type int cdvdstm_bankcur_iop;
// 40499C: using guessed type int cdvdstm_bankoffs_iop;
// 4049A4: using guessed type int cdvdstm_stmstart_iop;

//----- (00400D30) --------------------------------------------------------
unsigned int __cdecl iop_stream_intr_cb(void *userdata)
{
	int gptmp; // $a0
	int scres1; // [sp+28h] [-8h] BYREF

	(void)userdata;

	if ( cdvdstm_verbose > 0 )
		Kprintf("Intr Read call\n");
	iCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &cdvdstm_curclk_iop);
	iCancelAlarm((unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &cdvdstm_curclk_iop);
	sceCdSC(0xFFFFFFFF, &scres1);
	if ( !scres1 )
	{
		switch ( sceCdGetDiskType() )
		{
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
				break;
			default:
				scres1 = 253;
				break;
		}
	}
	cdvdstm_curclk_iop.hi = 0;
	if ( cdvdstm_stmstart_iop )
		cdvdstm_retrycnt_iop = 0;
	if ( cdvdstm_stmstart_iop || scres1 || cdvdstm_retrycnt_iop )
	{
		if ( cdvdstm_verbose > 0 )
			Kprintf("Stm Rtry stmstart:%d err:%02x retry:%d\n", cdvdstm_stmstart_iop, scres1, cdvdstm_retrycnt_iop);
	}
	cdvdstm_curclk_iop.lo = ( cdvdstm_stmstart_iop || scres1 || cdvdstm_retrycnt_iop ) ? 552960000 : (36864 * sceCdSC(0xFFFFFFEF, &scres1));
	if ( scres1 )
	{
		if ( cdvdstm_verbose > 0 )
		{
			Kprintf("IOP Stream read Error code= 0x%02x retry= %d\n", scres1, cdvdstm_retrycnt_iop);
		}
		cdvdstm_retrycnt_iop = 1;
		if ( scres1 == 48 || scres1 == 1 )
		{
			if ( cdvdstm_verbose > 0 )
				Kprintf("On err %08x\n", scres1);
			if ( cdvdstm_retrycnt_iop )
				cdvdstm_retryerr_iop = scres1;
			cdvdstm_retrycnt_iop = 3;
		}
		else
		{
			cdvdstm_retryerr_iop = scres1;
		}
	}
	if ( cdvdstm_retrycnt_iop )
	{
		unsigned int tgttmp; // $s0

		cdvdstm_retrycnt_iop -= 1;
		tgttmp = ( (unsigned int)cdvdstm_tgt >= (unsigned int)(16 * cdvdstm_retrycnt_iop) ) ? (cdvdstm_tgt - 16 * cdvdstm_retrycnt_iop) : (cdvdstm_tgt + 16 * cdvdstm_retrycnt_iop);
		if ( cdvdstm_verbose > 0 )
			Kprintf("Stm Rtry Start Tgt=%d Cur= %d\n", cdvdstm_tgt, tgttmp);
		if ( sceCdRE(
					 tgttmp,
					 cdvdstm_sectorcount,
					 (char *)cdvdstm_buffer + cdvdstm_bankgp_iop * cdvdstm_numbytes,
					 &cdvdstm_mode_iop) )
		{
			iSetAlarm(&cdvdstm_curclk_iop, (unsigned int (__cdecl *)(void *))alarm_cb, &cdvdstm_curclk_iop);
		}
		else
		{
			cdvdstm_curclk_iop.lo = 7372800;
			if ( iSetAlarm(&cdvdstm_curclk_iop, (unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &cdvdstm_curclk_iop) && !sceCdNop() )
			{
				sceCdSC(0, &scres1);
			}
			cdvdstm_retrycnt_iop += 1;
		}
		return 0;
	}
	else
	{
		if ( !cdvdstm_stmstart_iop )
		{
			cdvdstm_usedmap_iop[cdvdstm_bankgp_iop] = 1;
			gptmp = cdvdstm_bankgp_iop;
			cdvdstm_bankgp_iop += 1;
			if ( (unsigned int)cdvdstm_bankgp_iop >= (unsigned int)cdvdstm_bankmax )
				cdvdstm_bankgp_iop = 0;
		}
		if ( !cdvdstm_stmstart_iop && (cdvdstm_usedmap_iop[cdvdstm_bankgp_iop] || cdvdstm_bankcur_iop == cdvdstm_bankgp_iop) )
		{
			cdvdstm_bankgp_iop = gptmp;
			cdvdstm_usedmap_iop[gptmp] = 0;
			if ( cdvdstm_verbose > 0 )
				Kprintf(
					"read Full %d %d %d %d %d gp %d pp %d spn %d\n",
					(unsigned __int8)cdvdstm_usedmap_iop[0],
					(unsigned __int8)cdvdstm_usedmap_iop[1],
					(unsigned __int8)cdvdstm_usedmap_iop[2],
					(unsigned __int8)cdvdstm_usedmap_iop[3],
					(unsigned __int8)cdvdstm_usedmap_iop[4],
					cdvdstm_bankgp_iop,
					cdvdstm_bankcur_iop,
					cdvdstm_mode_iop.spindlctrl);
			cdvdstm_curclk_iop.lo = 294912;
			if ( iSetAlarm(&cdvdstm_curclk_iop, (unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &cdvdstm_curclk_iop) != 0 && sceCdNop() == 0 )
			{
				sceCdSC(0, &scres1);
			}
		}
		else
		{
			if ( cdvdstm_stmstart_iop == 2 )
			{
				unsigned int i; // $v1

				cdvdstm_bankoffs_iop = 0;
				cdvdstm_bankcur_iop = 0;
				cdvdstm_bankgp_iop = 0;
				for ( i = 0; i < (unsigned int)cdvdstm_bankmax; i += 1 )
					cdvdstm_usedmap_iop[i] = 0;
			}
			cdvdstm_stmstart_iop = 0;
			cdvdstm_tgt = cdvdstm_lsn_iop;
			if ( sceCdRE(
						 cdvdstm_lsn_iop,
						 cdvdstm_sectorcount,
						 (char *)cdvdstm_buffer + cdvdstm_bankgp_iop * cdvdstm_numbytes,
						 &cdvdstm_mode_iop) )
			{
				iSetAlarm(&cdvdstm_curclk_iop, (unsigned int (__cdecl *)(void *))alarm_cb, &cdvdstm_curclk_iop);
			}
			else
			{
				cdvdstm_curclk_iop.lo = 7372800;
				if ( iSetAlarm(&cdvdstm_curclk_iop, (unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &cdvdstm_curclk_iop)
					&& !sceCdNop() )
				{
					sceCdSC(0, &scres1);
				}
				cdvdstm_retrycnt_iop = 1;
			}
			cdvdstm_lsn_iop += cdvdstm_sectorcount;
		}
	}
	return 0;
}
// 404688: using guessed type int cdvdstm_verbose;
// 404698: using guessed type int cdvdstm_numbytes;
// 40469C: using guessed type int cdvdstm_bankmax;
// 4046AC: using guessed type int cdvdstm_retryerr_iop;
// 4046B0: using guessed type int cdvdstm_retrycnt_iop;
// 404780: using guessed type int cdvdstm_tgt;
// 404994: using guessed type int cdvdstm_bankgp_iop;
// 404998: using guessed type int cdvdstm_bankcur_iop;
// 40499C: using guessed type int cdvdstm_bankoffs_iop;
// 4049A4: using guessed type int cdvdstm_stmstart_iop;

//----- (00401374) --------------------------------------------------------
int cdrom_stm_init()
{
	iop_sema_t semaparam; // [sp+10h] [-10h] BYREF

	semaparam.attr = 1;
	semaparam.initial = 1;
	semaparam.max = 1;
	semaparam.option = 0;
	cdvdstm_semid = CreateSema(&semaparam);
	return 0;
}

//----- (004013B0) --------------------------------------------------------
int cdrom_stm_deinit()
{
	SignalSema(cdvdstm_semid);
	DeleteSema(cdvdstm_semid);
	return 0;
}

//----- (004013E8) --------------------------------------------------------
int __fastcall cdrom_stm_devctl(iop_file_t *f, const char *a2, int a3, void *inbuf, unsigned int inbuf_len, void *outbuf, unsigned int outbuf_len)
{
	int retres; // $s5
	cdrom_stm_devctl_t *instruct;
	int *outres_ptr;

	(void)f;
	(void)a2;
	(void)outbuf_len;

	instruct = inbuf;
	outres_ptr = outbuf;
	WaitSema(cdvdstm_semid);
	retres = 0;
	if ( cdvdstm_in_deldrv )
	{
		SignalSema(cdvdstm_semid);
		return -5;
	}
	switch ( a3 )
	{
		case 0x4393:
			if ( instruct->cmdid == 5 || instruct->cmdid == 3 || instruct->cmdid - 7 < 2 )
			{
				vSetEventFlag();
			}
			*outres_ptr = iop_stream_handler(
											instruct->posszarg1,
											instruct->posszarg2,
											instruct->buffer,
											instruct->cmdid,
											&instruct->rmode,
											(int *)&instruct->error);
			break;
		case 0x4394:
			*outres_ptr = sceCdStream0(instruct->posszarg2, (char *)instruct->buffer, instruct->cmdid, (int *)&instruct->error);
			break;
		case 0x4396:
			ee_stream_handler_normal(instruct, inbuf_len, outres_ptr);
			break;
		case 0x4398:
			ee_stream_handler_cdda(instruct, inbuf_len, outres_ptr);
			break;
		default:
			printf("Un-support devctl %08x\n", a3);
			retres = -5;
			break;
	}
	SignalSema(cdvdstm_semid);
	return retres;
}
// 404690: using guessed type int cdvdstm_in_deldrv;

//----- (00401588) --------------------------------------------------------
int __cdecl cdrom_stm_nulldev()
{
	printf("nulldev0 call\n");
	return -5;
}

//----- (004015B0) --------------------------------------------------------
__int64 __cdecl cdrom_stm_nulldev64()
{
	printf("nulldev0 call\n");
	return -5LL;
}

//----- (004015DC) --------------------------------------------------------
int __fastcall _start(int a1)
{
	int scres; // [sp+10h] [-8h] BYREF
	int state; // [sp+14h] [-4h] BYREF

	if ( a1 < 0 )
	{
		int relres; // $s0

		if ( sceCdSC(0xFFFFFFFF, &scres) == 0 )
		{
			return 2;
		}
		cdvdstm_in_deldrv = 1;
		DelDrv("cdrom_stm");
		CpuSuspendIntr(&state);
		relres = ReleaseLibraryEntries(&_exp_cdvdstm);
		CpuResumeIntr(state);
		cdvdstm_in_deldrv = 0;
		if ( relres && relres != -213 )
		{
			cdvdstm_in_deldrv = 0;
			return 2;
		}
		return 1;
	}
	if ( RegisterLibraryEntries(&_exp_cdvdstm) != 0 )
		return 1;
	DelDrv("cdrom_stm");
	if ( AddDrv(&cdrom_stm_dev) )
	{
		cdrom_stm_deinit();
		return 1;
	}
	cdvdstm_ef = sceCdSC(0xFFFFFFF5, &scres);
	return 2;
}
// 404690: using guessed type int cdvdstm_in_deldrv;

//----- (004016D0) --------------------------------------------------------
BOOL __fastcall stm_alarm_timeout_cb(void *a1)
{
	unsigned int scres; // [sp+10h] [-8h] BYREF

	scres = *(_DWORD *)a1 / 0x9000u;
	Kprintf("Stm EE Read Time Out %d(msec)\n", scres);
	sceCdSC(0xFFFFFFEE, (int *)&scres);
	return sceCdBreak() == 0;
}

//----- (00401724) --------------------------------------------------------
void __fastcall ee_stream_handler_normal(cdrom_stm_devctl_t *instruct, int inbuf_len, int *outres_ptr)
{
	int retryflag; // $fp
	u32 cmdid; // $s1
	u32 posszarg2_bytes; // $s5
	int bankcur_tmp; // $a0
	unsigned int chunks_sectors; // $lo
	int bankcur_next_tmp1; // $a1
	int posszarg2_bytes_clamped; // $s1
	int dmat1; // $s0
	int bankcur_next_tmp2; // $a1
	int posszarg2_bytes_overrun; // [sp+20h] [-10h]
	int outres_tmp2; // [sp+20h] [-10h]
	int state; // [sp+24h] [-Ch] BYREF
	unsigned int i; // [sp+28h] [-8h]
	u32 posszarg1_stk; // [sp+2Ch] [-4h] BYREF

	(void)inbuf_len;

	retryflag = 0;
	cmdid = instruct->cmdid;
	posszarg1_stk = instruct->posszarg1;
	if ( cdvdstm_stmstart_ee == 2 && (cmdid != 9 && cmdid != 3) )
	{
		*outres_ptr = 0;
		return;
	}
	switch ( cmdid )
	{
		case 8u:
			sceCdSC(2, &cdvdstm_last_error_for_ee);
			if ( sceCdNop() == 0 )
			{
				sceCdSC(0, &cdvdstm_last_error_for_ee);
				*outres_ptr = 0;
				return;
			}
			*outres_ptr = 1;
			return;
		case 7u:
			CpuSuspendIntr(&state);
			CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal, &cdvdstm_curclk_ee);
			sceCdSC(0, &cdvdstm_last_error_for_ee);
			CpuResumeIntr(state);
			sceCdSync(0);
			*outres_ptr = 1;
			CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
			return;
		case 6u:
			bankcur_tmp = cdvdstm_bankcur_ee;
			if ( !cdvdstm_usedmap_ee[bankcur_tmp] )
			{
				bankcur_tmp += 1;
				if ( (unsigned int)bankcur_tmp >= (unsigned int)cdvdstm_bankcnt2 )
					bankcur_tmp = 0;
				if ( !cdvdstm_usedmap_ee[bankcur_tmp] )
					bankcur_tmp = cdvdstm_bankcur_ee;
			}
			for ( i = 0; (i < (unsigned int)cdvdstm_bankcnt2) && cdvdstm_usedmap_ee[bankcur_tmp] && (cdvdstm_bankgp_ee != bankcur_tmp); i += 1 )
			{
				bankcur_tmp += 1;
				if ( (unsigned int)bankcur_tmp >= (unsigned int)cdvdstm_bankcnt2 )
					bankcur_tmp = 0;
			}
			*outres_ptr = i * ((unsigned int)cdvdstm_chunksz2 >> 11);
			return;
		case 5u:
			sceCdstm1Cb((void (__cdecl *)(int))ee_stream_intr_cb_normal_thunk);
			if ( !instruct->posszarg2 )
				_break(7u, 0);
			chunks_sectors = instruct->posszarg1 / instruct->posszarg2;
			cdvdstm_bufsz2 = instruct->posszarg1;
			cdvdstm_sectorcount2 = chunks_sectors;
			cdvdstm_chunksz2 = chunks_sectors << 11;
			cdvdstm_buffer2 = (char *)instruct->buffer;
			cdvdstm_bankcnt2 = instruct->posszarg2;
			printf(
				"Stream Buffer 1Bank %dbyte %dbanks %dbyte used\n",
				(int)(chunks_sectors << 11),
				(int)(instruct->posszarg2),
				(int)((chunks_sectors << 11) * (instruct->posszarg2)));
			*outres_ptr = 1;
			return;
		case 3u:
			CpuSuspendIntr(&state);
			cdvdstm_stmstart_ee = 0;
			CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal, &cdvdstm_curclk_ee);
			sceCdSC(0, &cdvdstm_last_error_for_ee);
			CpuResumeIntr(state);
			sceCdBreak();
			for ( i = 0; i < (unsigned int)cdvdstm_bankcnt2; i += 1 )
			{
				cdvdstm_usedmap_ee[i] = 0;
			}
			cdvdstm_bankoffs_ee = 0;
			cdvdstm_bankcur_ee = 0;
			cdvdstm_bankgp_ee = 0;
			*outres_ptr = 1;
			sceCdSync(0);
			cdvdstm_last_error_for_ee = 0;
			sceCdSC(0xFFFFFFFE, &cdvdstm_last_error_for_ee);
			CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
			return;
		case 1u:
			cdvdstm_mode_ee.datapattern = instruct->rmode.datapattern;
			cdvdstm_mode_ee.trycount = instruct->rmode.trycount;
			cdvdstm_mode_ee.spindlctrl = instruct->rmode.spindlctrl;
			cdvdstm_retryerr_ee = 0;
			break;
	}
	posszarg2_bytes = instruct->posszarg2 << 11;
	if ( cmdid == 9 )
	{
		if ( sceCdSC(0xFFFFFFFF, &cdvdstm_last_error_for_ee) )
		{
			CpuSuspendIntr(&state);
			cdvdstm_lsn_ee = instruct->posszarg1;
			for ( i = 0; i < (unsigned int)cdvdstm_bankcnt2; i += 1 )
			{
				cdvdstm_usedmap_ee[i] = 0;
			}
			cdvdstm_stmstart_ee = 2;
			CpuResumeIntr(state);
			*outres_ptr = 1;
			return;
		}
		*outres_ptr = 0;
		return;
	}
	if ( cmdid == 4 )
	{
		retryflag = 1;
		CpuSuspendIntr(&state);
		CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal, &cdvdstm_curclk_ee);
		sceCdSC(0, &cdvdstm_last_error_for_ee);
		posszarg2_bytes = 0;
		cmdid = 1;
		CpuResumeIntr(state);
		cdvdstm_lsn_ee = instruct->posszarg1;
		cdvdstm_bankoffs_ee = 0;
		cdvdstm_bankcur_ee = 0;
		cdvdstm_bankgp_ee = 0;
		sceCdSync(0);
		CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
	}
	if ( cmdid == 1 )
	{
		CpuSuspendIntr(&state);
		CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal, &cdvdstm_curclk_ee);
		sceCdSC(0, &cdvdstm_last_error_for_ee);
		CpuResumeIntr(state);
		retryflag = 1;
		for ( i = 0; i < (unsigned int)cdvdstm_bankcnt2; i += 1 )
		{
			cdvdstm_usedmap_ee[i] = 0;
		}
		cdvdstm_lsn_ee = instruct->posszarg1;
		sceCdSC(0xFFFFFFE9, (int *)&posszarg1_stk);
		cdvdstm_bankoffs_ee = 0;
		cdvdstm_bankcur_ee = 0;
		sceCdSync(0);
		CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
		cdvdstm_stmstart_ee = 1;
		sceCdSC(2, &cdvdstm_last_error_for_ee);
		if ( !sceCdNop() )
		{
			sceCdSC(0, &cdvdstm_last_error_for_ee);
			*outres_ptr = 0;
			return;
		}
	}
	posszarg2_bytes_overrun = -1;
	for ( i = 0; i < posszarg2_bytes; i += posszarg2_bytes_clamped )
	{
		unsigned int posszarg2_bytes_remain; // $s2

		posszarg2_bytes_remain = posszarg2_bytes - i;
		if ( !cdvdstm_usedmap_ee[cdvdstm_bankcur_ee] )
		{
			if ( cdvdstm_verbose > 0 )
				Kprintf(
					"CD read buffer over run %d %d %d %d %d gp %d pp %d\n",
					(unsigned __int8)cdvdstm_usedmap_ee[0],
					(unsigned __int8)cdvdstm_usedmap_ee[1],
					(unsigned __int8)cdvdstm_usedmap_ee[2],
					(unsigned __int8)cdvdstm_usedmap_ee[3],
					(unsigned __int8)cdvdstm_usedmap_ee[4],
					cdvdstm_bankgp_ee,
					cdvdstm_bankcur_ee);
			CpuSuspendIntr(&state);
			bankcur_next_tmp1 = cdvdstm_bankcur_ee;
			cdvdstm_bankcur_ee += 1;
			if ( (unsigned int)cdvdstm_bankcur_ee >= (unsigned int)cdvdstm_bankcnt2 )
				cdvdstm_bankcur_ee = 0;
			if ( !cdvdstm_usedmap_ee[cdvdstm_bankcur_ee] )
				cdvdstm_bankcur_ee = bankcur_next_tmp1;
			posszarg2_bytes_overrun = posszarg2_bytes - posszarg2_bytes_remain;
			CpuResumeIntr(state);
			break;
		}
		posszarg2_bytes_clamped = ( (unsigned int)(cdvdstm_chunksz2 - cdvdstm_bankoffs_ee) < posszarg2_bytes_remain ) ? (unsigned int)(cdvdstm_chunksz2 - cdvdstm_bankoffs_ee) : posszarg2_bytes_remain;
		cdvdstm_dmat.dest = ((char *)instruct->buffer) + i;
		cdvdstm_dmat.size = posszarg2_bytes_clamped;
		cdvdstm_dmat.attr = 0;
		cdvdstm_dmat.src = (char *)cdvdstm_buffer2 + cdvdstm_bankcur_ee * cdvdstm_chunksz2 + cdvdstm_bankoffs_ee;
		if ( posszarg2_bytes_clamped )
		{
			while ( 1 )
			{
				CpuSuspendIntr(&state);
				dmat1 = sceSifSetDma(&cdvdstm_dmat, 1);
				CpuResumeIntr(state);
				if ( dmat1 )
					break;
				DelayThread(500);
			}
			cdvdstm_bankoffs_ee += posszarg2_bytes_clamped;
			while ( sceSifDmaStat(dmat1) >= 0 )
				;
		}
		if ( (unsigned int)cdvdstm_bankoffs_ee >= (unsigned int)cdvdstm_chunksz2 )
		{
			CpuSuspendIntr(&state);
			cdvdstm_bankoffs_ee = 0;
			cdvdstm_usedmap_ee[cdvdstm_bankcur_ee] = 0;
			bankcur_next_tmp2 = cdvdstm_bankcur_ee;
			cdvdstm_bankcur_ee += 1;
			if ( (unsigned int)cdvdstm_bankcur_ee >= (unsigned int)cdvdstm_bankcnt2 )
				cdvdstm_bankcur_ee = 0;
			if ( cdvdstm_usedmap_ee[cdvdstm_bankcur_ee] && cdvdstm_bankgp_ee != cdvdstm_bankcur_ee )
			{
				CpuResumeIntr(state);
			}
			else
			{
				cdvdstm_bankcur_ee = bankcur_next_tmp2;
				CpuResumeIntr(state);
				if ( cdvdstm_verbose > 0 )
					Kprintf(
						"CD read buffer over run %d %d %d %d %d gp %d pp %d\n",
						(unsigned __int8)cdvdstm_usedmap_ee[0],
						(unsigned __int8)cdvdstm_usedmap_ee[1],
						(unsigned __int8)cdvdstm_usedmap_ee[2],
						(unsigned __int8)cdvdstm_usedmap_ee[3],
						(unsigned __int8)cdvdstm_usedmap_ee[4],
						cdvdstm_bankgp_ee,
						cdvdstm_bankcur_ee);
				posszarg2_bytes_overrun = posszarg2_bytes - (posszarg2_bytes_remain - posszarg2_bytes_clamped);
				break;
			}
		}
	}
	if ( posszarg2_bytes_overrun == -1 )
		posszarg2_bytes_overrun = posszarg2_bytes;
	outres_tmp2 = ( retryflag ) ? 1 : (posszarg2_bytes_overrun / 2048);
	if ( !retryflag )
	{
		if ( sceCdSC(0xFFFFFFFF, &cdvdstm_last_error_for_ee) != 2 && !outres_tmp2 && !cdvdstm_retryerr_ee )
			cdvdstm_retryerr_ee = 273;
		if ( cdvdstm_retryerr_ee )
		{
			outres_tmp2 = (unsigned __int16)outres_tmp2 | (cdvdstm_retryerr_ee << 16);
			cdvdstm_retryerr_ee = 0;
		}
	}
	*outres_ptr = outres_tmp2;
	return;
}
// 404688: using guessed type int cdvdstm_verbose;
// 404744: using guessed type int cdvdstm_bufsz2;
// 404748: using guessed type int cdvdstm_chunksz2;
// 40474C: using guessed type int cdvdstm_bankcnt2;
// 404758: using guessed type int cdvdstm_retryerr_ee;
// 404BE4: using guessed type int cdvdstm_bankgp_ee;
// 404BE8: using guessed type int cdvdstm_bankcur_ee;
// 404BEC: using guessed type int cdvdstm_bankoffs_ee;
// 404BF4: using guessed type int cdvdstm_stmstart_ee;

//----- (00402230) --------------------------------------------------------
unsigned int __fastcall ee_stream_intr_cb_normal(void *userdata)
{
	int gptmp; // $a0

	(void)userdata;

	if ( cdvdstm_verbose > 0 )
		Kprintf("Intr EE Stm Read call\n");
	iCancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
	iCancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal, &cdvdstm_curclk_ee);
	sceCdSC(0xFFFFFFFF, &cdvdstm_last_error_for_ee);
	if ( !cdvdstm_last_error_for_ee )
	{
		switch ( sceCdGetDiskType() )
		{
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
				break;
			default:
				cdvdstm_last_error_for_ee = 253;
				break;
		}
	}
	cdvdstm_curclk_ee.hi = 0;
	if ( cdvdstm_stmstart_ee )
		cdvdstm_retrycnt_ee_normal = 0;
	cdvdstm_curclk_ee.lo = ( cdvdstm_stmstart_ee || cdvdstm_last_error_for_ee || cdvdstm_retrycnt_ee_normal ) ? 552960000 : (36864 * sceCdSC(0xFFFFFFEF, &cdvdstm_last_error_for_ee));
	if ( cdvdstm_last_error_for_ee )
	{
		if ( cdvdstm_verbose > 0 )
		{
			Kprintf(
				"EE Stream read LBN= %d Error code= 0x%02x retry= %d\n",
				cdvdstm_readlbn_ee_normal,
				cdvdstm_last_error_for_ee,
				cdvdstm_retrycnt_ee_normal);
		}
		if ( cdvdstm_last_error_for_ee == 48 || cdvdstm_last_error_for_ee == 1 )
		{
			if ( cdvdstm_retrycnt_ee_normal )
			{
				if ( cdvdstm_verbose > 0 )
					Kprintf("On Retry retry %d err %08x\n", cdvdstm_retrycnt_ee_normal, cdvdstm_last_error_for_ee);
			}
			cdvdstm_retrycnt_ee_normal = 3;
		}
		else
		{
			cdvdstm_retrycnt_ee_normal = 1;
		}
		cdvdstm_retryerr_ee = cdvdstm_last_error_for_ee;
	}
	if ( cdvdstm_retrycnt_ee_normal )
	{
		cdvdstm_retrycnt_ee_normal -= 1;
		if ( sceCdRE(
					 ( (unsigned int)cdvdstm_readlbn_ee_normal >= (unsigned int)(16 * cdvdstm_retrycnt_ee_normal) ) ? (cdvdstm_readlbn_ee_normal - 16 * cdvdstm_retrycnt_ee_normal) : (cdvdstm_readlbn_ee_normal + 16 * cdvdstm_retrycnt_ee_normal),
					 cdvdstm_sectorcount2,
					 (char *)cdvdstm_buffer2 + cdvdstm_bankgp_ee * cdvdstm_chunksz2,
					 &cdvdstm_mode_ee) )
		{
			iSetAlarm(&cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
		}
		else
		{
			if ( cdvdstm_verbose > 0 )
				Kprintf("Stm Read Call fail\n");
			cdvdstm_curclk_ee.lo = 7372800;
			if ( iSetAlarm(&cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal, &cdvdstm_curclk_ee) && !sceCdNop() )
			{
				sceCdSC(0, &cdvdstm_last_error_for_ee);
			}
			cdvdstm_retrycnt_ee_normal += 1;
		}
	}
	else
	{
		if ( !cdvdstm_stmstart_ee )
		{
			cdvdstm_usedmap_ee[cdvdstm_bankgp_ee] = 1;
			gptmp = cdvdstm_bankgp_ee;
			cdvdstm_bankgp_ee += 1;
			if ( (unsigned int)cdvdstm_bankgp_ee >= (unsigned int)cdvdstm_bankcnt2 )
				cdvdstm_bankgp_ee = 0;
		}
		if ( !cdvdstm_stmstart_ee && (cdvdstm_usedmap_ee[cdvdstm_bankgp_ee] || cdvdstm_bankcur_ee == cdvdstm_bankgp_ee) )
		{
			cdvdstm_bankgp_ee = gptmp;
			cdvdstm_usedmap_ee[gptmp] = 0;
			if ( cdvdstm_verbose > 0 )
				Kprintf(
					"read Full %d %d %d %d %d gp %d pp %d spn %d\n",
					(unsigned __int8)cdvdstm_usedmap_ee[0],
					(unsigned __int8)cdvdstm_usedmap_ee[1],
					(unsigned __int8)cdvdstm_usedmap_ee[2],
					(unsigned __int8)cdvdstm_usedmap_ee[3],
					(unsigned __int8)cdvdstm_usedmap_ee[4],
					cdvdstm_bankgp_ee,
					cdvdstm_bankcur_ee,
					cdvdstm_mode_ee.spindlctrl);
			cdvdstm_curclk_ee.lo = 294912;
			if ( iSetAlarm(
									&cdvdstm_curclk_ee,
									(unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal,
									&cdvdstm_curclk_ee) != 0 && sceCdNop() == 0 )
			{
				sceCdSC(0, &cdvdstm_last_error_for_ee);
			}
		}
		else
		{
			if ( cdvdstm_stmstart_ee == 2 )
			{
				unsigned int i; // $v1

				cdvdstm_bankoffs_ee = 0;
				cdvdstm_bankcur_ee = 0;
				cdvdstm_bankgp_ee = 0;
				for ( i = 0; i < (unsigned int)cdvdstm_bankcnt2; i += 1 )
					cdvdstm_usedmap_ee[i] = 0;
			}
			cdvdstm_stmstart_ee = 0;
			cdvdstm_readlbn_ee_normal = cdvdstm_lsn_ee;
			if ( sceCdRE(
						 cdvdstm_lsn_ee,
						 cdvdstm_sectorcount2,
						 (char *)cdvdstm_buffer2 + cdvdstm_bankgp_ee * cdvdstm_chunksz2,
						 &cdvdstm_mode_ee) )
			{
				iSetAlarm(&cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
			}
			else
			{
				if ( cdvdstm_verbose > 0 )
					Kprintf("Stm Read Call1 fail\n");
				cdvdstm_curclk_ee.lo = 7372800;
				if ( iSetAlarm(
							 &cdvdstm_curclk_ee,
							 (unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal,
							 &cdvdstm_curclk_ee)
					&& !sceCdNop() )
				{
					sceCdSC(0, &cdvdstm_last_error_for_ee);
				}
				cdvdstm_retrycnt_ee_normal = 1;
			}
			cdvdstm_lsn_ee += cdvdstm_sectorcount2;
		}
	}
	return 0;
}
// 404688: using guessed type int cdvdstm_verbose;
// 404748: using guessed type int cdvdstm_chunksz2;
// 40474C: using guessed type int cdvdstm_bankcnt2;
// 404758: using guessed type int cdvdstm_retryerr_ee;
// 40475C: using guessed type int cdvdstm_retrycnt_ee_normal;
// 4049C0: using guessed type int cdvdstm_readlbn_ee_normal;
// 404BE4: using guessed type int cdvdstm_bankgp_ee;
// 404BE8: using guessed type int cdvdstm_bankcur_ee;
// 404BEC: using guessed type int cdvdstm_bankoffs_ee;
// 404BF4: using guessed type int cdvdstm_stmstart_ee;

//----- (0040289C) --------------------------------------------------------
void __fastcall ee_stream_handler_cdda(cdrom_stm_devctl_t *instruct, int inbuf_len, int *outres_ptr)
{
	u32 cmdid; // $s1
	u32 posszarg2_bytes; // $s5
	int retryflag; // $fp
	int bankcur_tmp; // $a0
	u32 chunks_sectors; // $lo
	int bankcur_next_tmp1; // $a1
	int posszarg2_bytes_clamped; // $s1
	int dmat2; // $s0
	int bankcur_next_tmp2; // $a1
	int posszarg2_overrun_chunks2; // [sp+20h] [-10h]
	unsigned int posszarg2_bytes_overrun; // [sp+20h] [-10h]
	int state; // [sp+24h] [-Ch] BYREF
	unsigned int i; // [sp+28h] [-8h]

	(void)inbuf_len;

	cmdid = instruct->cmdid;
	posszarg2_bytes = instruct->posszarg2 * cdvdstm_usedchunksize2;
	retryflag = 0;
	if ( cdvdstm_stmstart_ee == 2 && (cmdid != 9 && cmdid != 3) )
	{
		*outres_ptr = 0;
		return;
	}
	switch ( cmdid )
	{
		case 8u:
			sceCdSC(2, &cdvdstm_last_error_for_ee);
			if ( sceCdNop() )
			{
				*outres_ptr = 1;
				return;
			}
			sceCdSC(0, &cdvdstm_last_error_for_ee);
			*outres_ptr = 0;
			return;
		case 7u:
			CpuSuspendIntr(&state);
			CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &cdvdstm_curclk_ee);
			sceCdSC(0, &cdvdstm_last_error_for_ee);
			CpuResumeIntr(state);
			sceCdSync(0);
			*outres_ptr = 1;
			CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
			return;
		case 6u:
			bankcur_tmp = cdvdstm_bankcur_ee;
			if ( !cdvdstm_usedmap_ee[bankcur_tmp] )
			{
				bankcur_tmp += 1;
				if ( (unsigned int)bankcur_tmp >= (unsigned int)cdvdstm_bankcnt2 )
					bankcur_tmp = 0;
				if ( !cdvdstm_usedmap_ee[bankcur_tmp] )
					bankcur_tmp = cdvdstm_bankcur_ee;
			}
			for ( i = 0; (i < (unsigned int)cdvdstm_bankcnt2) && cdvdstm_usedmap_ee[bankcur_tmp] && (cdvdstm_bankgp_ee != bankcur_tmp); i += 1 )
			{
				bankcur_tmp += 1;
				if ( (unsigned int)(bankcur_tmp) >= (unsigned int)cdvdstm_bankcnt2 )
					bankcur_tmp = 0;
			}
			if ( !cdvdstm_usedchunksize2 )
				_break(7u, 0);
			*outres_ptr = i * (cdvdstm_chunksz2 / (unsigned int)cdvdstm_usedchunksize2);
			return;
		case 5u:
			sceCdstm1Cb((void (__cdecl *)(int))ee_stream_intr_cb_cdda_thunk);
			switch ( instruct->rmode.datapattern )
			{
				case 1:
					cdvdstm_usedchunksize2 = 2368;
					break;
				case 2:
					cdvdstm_usedchunksize2 = 2448;
					break;
				case 0:
				default:
					cdvdstm_usedchunksize2 = 2352;
					break;
			}
			if ( !instruct->posszarg2 )
				_break(7u, 0);
			chunks_sectors = instruct->posszarg1 / instruct->posszarg2;
			cdvdstm_bufsz2 = instruct->posszarg1;
			cdvdstm_sectorcount2 = chunks_sectors;
			cdvdstm_chunksz2 = chunks_sectors * cdvdstm_usedchunksize2;
			cdvdstm_buffer2 = (char *)instruct->buffer;
			cdvdstm_bankcnt2 = instruct->posszarg2;
			printf(
				"DA Stream Buffer 1Bank %dbyte %dbanks %dbyte used\n",
				(int)(chunks_sectors * cdvdstm_usedchunksize2),
				(int)instruct->posszarg2,
				(int)(chunks_sectors * cdvdstm_usedchunksize2 * instruct->posszarg2));
			*outres_ptr = 1;
			return;
		case 3u:
			CpuSuspendIntr(&state);
			cdvdstm_stmstart_ee = 0;
			CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &cdvdstm_curclk_ee);
			sceCdSC(0, &cdvdstm_last_error_for_ee);
			CpuResumeIntr(state);
			sceCdBreak();
			for ( i = 0; i < (unsigned int)cdvdstm_bankcnt2; i += 1 )
			{
				cdvdstm_usedmap_ee[i] = 0;
			}
			cdvdstm_bankoffs_ee = 0;
			cdvdstm_bankcur_ee = 0;
			cdvdstm_bankgp_ee = 0;
			*outres_ptr = 1;
			sceCdSync(0);
			cdvdstm_last_error_for_ee = 0;
			sceCdSC(0xFFFFFFFE, &cdvdstm_last_error_for_ee);
			CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
			return;
		case 1u:
			cdvdstm_mode_ee.datapattern = instruct->rmode.datapattern;
			cdvdstm_mode_ee.trycount = instruct->rmode.trycount;
			cdvdstm_mode_ee.spindlctrl = instruct->rmode.spindlctrl;
			cdvdstm_retryerr_ee = 0;
			break;
	}
	if ( cmdid == 9 )
	{
		if ( sceCdSC(0xFFFFFFFF, &cdvdstm_last_error_for_ee) )
		{
			CpuSuspendIntr(&state);
			cdvdstm_lsn_ee = instruct->posszarg1;
			for ( i = 0; i < (unsigned int)cdvdstm_bankcnt2; i += 1 )
			{
				cdvdstm_usedmap_ee[i] = 0;
			}
			cdvdstm_stmstart_ee = 2;
			CpuResumeIntr(state);
			*outres_ptr = 1;
			return;
		}
		*outres_ptr = 0;
		return;
	}
	if ( cmdid == 4 )
	{
		retryflag = 1;
		CpuSuspendIntr(&state);
		CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &cdvdstm_curclk_ee);
		sceCdSC(0, &cdvdstm_last_error_for_ee);
		posszarg2_bytes = 0;
		cmdid = 1;
		CpuResumeIntr(state);
		cdvdstm_lsn_ee = instruct->posszarg1;
		cdvdstm_bankoffs_ee = 0;
		cdvdstm_bankcur_ee = 0;
		cdvdstm_bankgp_ee = 0;
		sceCdSync(0);
		CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
	}
	if ( cmdid == 1 )
	{
		signed int posszarg2_chunks; // $s0

		CpuSuspendIntr(&state);
		CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &cdvdstm_curclk_ee);
		sceCdSC(0, &cdvdstm_last_error_for_ee);
		CpuResumeIntr(state);
		retryflag = 1;
		for ( i = 0; i < (unsigned int)cdvdstm_bankcnt2; i += 1 )
		{
			cdvdstm_usedmap_ee[i] = 0;
		}
		cdvdstm_lsn_ee = instruct->posszarg1;
		cdvdstm_bankoffs_ee = 0;
		cdvdstm_bankcur_ee = 0;
		sceCdSync(0);
		CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
		if ( !cdvdstm_chunksz2 )
			_break(7u, 0);
		posszarg2_chunks = (posszarg2_bytes / cdvdstm_chunksz2) + (( posszarg2_bytes % cdvdstm_chunksz2 ) ? 1 : 0);
		for ( cdvdstm_bankgp_ee = 0; cdvdstm_bankgp_ee < posszarg2_chunks; cdvdstm_bankgp_ee += 1 )
		{
			int outres_tmp2; // [sp+20h] [-10h]

			outres_tmp2 = sceCdReadCDDA(cdvdstm_lsn_ee, cdvdstm_sectorcount2, cdvdstm_buffer2, &cdvdstm_mode_ee);
			sceCdSync(3);
			sceCdSC(0xFFFFFFFF, &cdvdstm_last_error_for_ee);
			if ( cdvdstm_last_error_for_ee || !outres_tmp2 )
			{
				sceCdSC(0, &cdvdstm_last_error_for_ee);
				*outres_ptr = 0;
				return;
			}
			cdvdstm_lsn_ee += cdvdstm_sectorcount2;
			cdvdstm_usedmap_ee[cdvdstm_bankgp_ee] = 1;
		}
		cdvdstm_stmstart_ee = 1;
		sceCdSC(2, &cdvdstm_last_error_for_ee);
		if ( !sceCdNop() )
		{
			sceCdSC(0, &cdvdstm_last_error_for_ee);
			*outres_ptr = 0;
			return;
		}
	}
	posszarg2_bytes_overrun = -1;
	for ( i = 0; i < posszarg2_bytes; i += posszarg2_bytes_clamped )
	{
		unsigned int posszarg2_bytes_remain; // $s2

		posszarg2_bytes_remain = posszarg2_bytes - i;
		if ( !cdvdstm_usedmap_ee[cdvdstm_bankcur_ee] )
		{
			if ( cdvdstm_verbose > 0 )
				Kprintf(
					"CD read buffer over run %d %d %d %d %d gp %d pp %d\n",
					(unsigned __int8)cdvdstm_usedmap_ee[0],
					(unsigned __int8)cdvdstm_usedmap_ee[1],
					(unsigned __int8)cdvdstm_usedmap_ee[2],
					(unsigned __int8)cdvdstm_usedmap_ee[3],
					(unsigned __int8)cdvdstm_usedmap_ee[4],
					cdvdstm_bankgp_ee,
					cdvdstm_bankcur_ee);
			CpuSuspendIntr(&state);
			bankcur_next_tmp1 = cdvdstm_bankcur_ee;
			cdvdstm_bankcur_ee += 1;
			if ( (unsigned int)cdvdstm_bankcur_ee >= (unsigned int)cdvdstm_bankcnt2 )
				cdvdstm_bankcur_ee = 0;
			if ( !cdvdstm_usedmap_ee[cdvdstm_bankcur_ee] )
				cdvdstm_bankcur_ee = bankcur_next_tmp1;
			posszarg2_bytes_overrun = posszarg2_bytes - posszarg2_bytes_remain;
			CpuResumeIntr(state);
			break;
		}
		posszarg2_bytes_clamped = ( (unsigned int)(cdvdstm_chunksz2 - cdvdstm_bankoffs_ee) < posszarg2_bytes_remain ) ? (unsigned int)(cdvdstm_chunksz2 - cdvdstm_bankoffs_ee) : posszarg2_bytes_remain;
		cdvdstm_dmat2.dest = ((char *)instruct->buffer) + i;
		cdvdstm_dmat2.size = posszarg2_bytes_clamped;
		cdvdstm_dmat2.attr = 0;
		cdvdstm_dmat2.src = (char *)cdvdstm_buffer2 + cdvdstm_bankcur_ee * cdvdstm_chunksz2 + cdvdstm_bankoffs_ee;
		if ( posszarg2_bytes_clamped )
		{
			while ( 1 )
			{
				CpuSuspendIntr(&state);
				dmat2 = sceSifSetDma(&cdvdstm_dmat2, 1);
				CpuResumeIntr(state);
				if ( dmat2 )
					break;
				DelayThread(500);
			}
			cdvdstm_bankoffs_ee += posszarg2_bytes_clamped;
			while ( sceSifDmaStat(dmat2) >= 0 )
				;
		}
		if ( (unsigned int)cdvdstm_bankoffs_ee >= (unsigned int)cdvdstm_chunksz2 )
		{
			CpuSuspendIntr(&state);
			cdvdstm_bankoffs_ee = 0;
			cdvdstm_usedmap_ee[cdvdstm_bankcur_ee] = 0;
			bankcur_next_tmp2 = cdvdstm_bankcur_ee;
			cdvdstm_bankcur_ee += 1;
			if ( (unsigned int)cdvdstm_bankcur_ee >= (unsigned int)cdvdstm_bankcnt2 )
				cdvdstm_bankcur_ee = 0;
			if ( cdvdstm_usedmap_ee[cdvdstm_bankcur_ee] && cdvdstm_bankgp_ee != cdvdstm_bankcur_ee )
			{
				CpuResumeIntr(state);
			}
			else
			{
				cdvdstm_bankcur_ee = bankcur_next_tmp2;
				CpuResumeIntr(state);
				if ( cdvdstm_verbose > 0 )
					Kprintf(
						"CD read buffer over run %d %d %d %d %d gp %d pp %d\n",
						(unsigned __int8)cdvdstm_usedmap_ee[0],
						(unsigned __int8)cdvdstm_usedmap_ee[1],
						(unsigned __int8)cdvdstm_usedmap_ee[2],
						(unsigned __int8)cdvdstm_usedmap_ee[3],
						(unsigned __int8)cdvdstm_usedmap_ee[4],
						cdvdstm_bankgp_ee,
						cdvdstm_bankcur_ee);
				posszarg2_bytes_overrun = posszarg2_bytes - (posszarg2_bytes_remain - posszarg2_bytes_clamped);
				break;
			}
		}
	}
	if ( posszarg2_bytes_overrun == 0xFFFFFFFF )
		posszarg2_bytes_overrun = posszarg2_bytes;
	if ( !cdvdstm_usedchunksize2 )
		_break(7u, 0);
	posszarg2_overrun_chunks2 = posszarg2_bytes_overrun / cdvdstm_usedchunksize2;
	if ( retryflag )
	{
		*outres_ptr = 1;
		return;
	}
	if ( sceCdSC(0xFFFFFFFF, &cdvdstm_last_error_for_ee) != 2 && !posszarg2_overrun_chunks2 && !cdvdstm_retryerr_ee )
		cdvdstm_retryerr_ee = 273;
	if ( cdvdstm_retryerr_ee )
	{
		posszarg2_overrun_chunks2 = (unsigned __int16)posszarg2_overrun_chunks2 | (cdvdstm_retryerr_ee << 16);
		cdvdstm_retryerr_ee = 0;
	}
	*outres_ptr = posszarg2_overrun_chunks2;
}
// 402B7C: conditional instruction was optimized away because $v0.4!=0
// 404688: using guessed type int cdvdstm_verbose;
// 404744: using guessed type int cdvdstm_bufsz2;
// 404748: using guessed type int cdvdstm_chunksz2;
// 40474C: using guessed type int cdvdstm_bankcnt2;
// 404758: using guessed type int cdvdstm_retryerr_ee;
// 404760: using guessed type int cdvdstm_usedchunksize2;
// 404BE4: using guessed type int cdvdstm_bankgp_ee;
// 404BE8: using guessed type int cdvdstm_bankcur_ee;
// 404BEC: using guessed type int cdvdstm_bankoffs_ee;
// 404BF4: using guessed type int cdvdstm_stmstart_ee;

//----- (00403530) --------------------------------------------------------
unsigned int __fastcall ee_stream_intr_cb_cdda(void *userdata)
{
	int gptmp; // $a0

	(void)userdata;

	if ( cdvdstm_verbose > 0 )
		Kprintf("Intr EE DA Stm Read call\n");
	iCancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
	iCancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &cdvdstm_curclk_ee);
	sceCdSC(0xFFFFFFFF, &cdvdstm_last_error_for_ee);
	if ( !cdvdstm_last_error_for_ee )
	{
		switch ( sceCdGetDiskType() )
		{
			case 17:
			case 19:
			case 33:
			case 253:
				break;
			default:
				cdvdstm_last_error_for_ee = 253;
				break;
		}
	}
	cdvdstm_curclk_ee.hi = 0;
	if ( cdvdstm_stmstart_ee )
		cdvdstm_retrycnt_ee_cdda = 0;
	cdvdstm_curclk_ee.lo = ( cdvdstm_stmstart_ee || cdvdstm_last_error_for_ee || cdvdstm_retrycnt_ee_cdda ) ? 552960000 : (36864 * sceCdSC(0xFFFFFFEF, &cdvdstm_last_error_for_ee));
	if ( cdvdstm_last_error_for_ee )
	{
		if ( cdvdstm_verbose > 0 )
		{
			Kprintf(
				"EE Stream read LBN= %d Error code= 0x%02x retry= %d\n",
				cdvdstm_readlbn_ee_cdda,
				cdvdstm_last_error_for_ee,
				cdvdstm_retrycnt_ee_cdda);
		}
		if ( cdvdstm_last_error_for_ee == 48 || cdvdstm_last_error_for_ee == 1 )
		{
			if ( cdvdstm_retrycnt_ee_cdda )
			{
				if ( cdvdstm_verbose > 0 )
					Kprintf("On Retry retry %d err %08x\n", cdvdstm_retrycnt_ee_cdda, cdvdstm_last_error_for_ee);
			}
			cdvdstm_retrycnt_ee_cdda = 4;
		}
		else
		{
			cdvdstm_retrycnt_ee_cdda = 1;
		}
		cdvdstm_retryerr_ee = cdvdstm_last_error_for_ee;
	}
	else
	{
		cdvdstm_retrycnt_ee_cdda = 0;
	}
	if ( cdvdstm_retrycnt_ee_cdda )
	{
		cdvdstm_retrycnt_ee_cdda -= 1;
		if ( !cdvdstm_retrycnt_ee_cdda && (cdvdstm_last_error_for_ee == 48 || cdvdstm_last_error_for_ee == 1) )
		{
			cdvdstm_readlbn_ee_cdda = cdvdstm_lsn_ee + (( cdvdstm_sectorcount2 < 0x1D ) ? (29 - cdvdstm_sectorcount2) : 0);
			cdvdstm_lsn_ee = cdvdstm_readlbn_ee_cdda + cdvdstm_sectorcount2;
		}
		if ( sceCdReadCDDA(
					 cdvdstm_readlbn_ee_cdda,
					 cdvdstm_sectorcount2,
					 (char *)cdvdstm_buffer2 + cdvdstm_bankgp_ee * cdvdstm_chunksz2,
					 &cdvdstm_mode_ee) )
		{
			iSetAlarm(&cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
		}
		else
		{
			if ( cdvdstm_verbose > 0 )
				Kprintf("Stm Read Call fail\n");
			cdvdstm_curclk_ee.lo = 7372800;
			if ( iSetAlarm(&cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &cdvdstm_curclk_ee) && !sceCdNop() )
			{
				sceCdSC(0, &cdvdstm_last_error_for_ee);
			}
			++cdvdstm_retrycnt_ee_cdda;
		}
	}
	else
	{
		if ( !cdvdstm_stmstart_ee )
		{
			cdvdstm_usedmap_ee[cdvdstm_bankgp_ee] = 1;
			gptmp = cdvdstm_bankgp_ee;
			cdvdstm_bankgp_ee += 1;
			if ( (unsigned int)cdvdstm_bankgp_ee >= (unsigned int)cdvdstm_bankcnt2 )
				cdvdstm_bankgp_ee = 0;
		}
		if ( !cdvdstm_stmstart_ee && (cdvdstm_usedmap_ee[cdvdstm_bankgp_ee] || cdvdstm_bankcur_ee == cdvdstm_bankgp_ee) )
		{
			cdvdstm_bankgp_ee = gptmp;
			cdvdstm_usedmap_ee[gptmp] = 0;
			if ( cdvdstm_verbose > 0 )
				Kprintf(
					"read Full %d %d %d %d %d gp %d pp %d spn %d\n",
					(unsigned __int8)cdvdstm_usedmap_ee[0],
					(unsigned __int8)cdvdstm_usedmap_ee[1],
					(unsigned __int8)cdvdstm_usedmap_ee[2],
					(unsigned __int8)cdvdstm_usedmap_ee[3],
					(unsigned __int8)cdvdstm_usedmap_ee[4],
					cdvdstm_bankgp_ee,
					cdvdstm_bankcur_ee,
					cdvdstm_mode_ee.spindlctrl);
			cdvdstm_curclk_ee.lo = 294912;
			if ( iSetAlarm(
									&cdvdstm_curclk_ee,
									(unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda,
									&cdvdstm_curclk_ee) != 0 && sceCdNop() == 0 )
			{
				sceCdSC(0, &cdvdstm_last_error_for_ee);
			}
		}
		else
		{
			if ( cdvdstm_stmstart_ee == 2 )
			{
				unsigned int i; // $v1

				cdvdstm_bankoffs_ee = 0;
				cdvdstm_bankcur_ee = 0;
				cdvdstm_bankgp_ee = 0;
				for ( i = 0; i < (unsigned int)cdvdstm_bankcnt2; i += 1 )
					cdvdstm_usedmap_ee[i] = 0;
			}
			cdvdstm_stmstart_ee = 0;
			cdvdstm_readlbn_ee_cdda = cdvdstm_lsn_ee;
			if ( sceCdReadCDDA(
						 cdvdstm_lsn_ee,
						 cdvdstm_sectorcount2,
						 (char *)cdvdstm_buffer2 + cdvdstm_bankgp_ee * cdvdstm_chunksz2,
						 &cdvdstm_mode_ee) )
			{
				iSetAlarm(&cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &cdvdstm_curclk_ee);
			}
			else
			{
				if ( cdvdstm_verbose > 0 )
					Kprintf("Stm Read Call1 fail\n");
				cdvdstm_curclk_ee.lo = 7372800;
				if ( iSetAlarm(&cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &cdvdstm_curclk_ee)
					&& !sceCdNop() )
				{
					sceCdSC(0, &cdvdstm_last_error_for_ee);
				}
				cdvdstm_retrycnt_ee_cdda = 1;
			}
			cdvdstm_lsn_ee += cdvdstm_sectorcount2;
		}
	}
	return 0;
}
// 404688: using guessed type int cdvdstm_verbose;
// 404748: using guessed type int cdvdstm_chunksz2;
// 40474C: using guessed type int cdvdstm_bankcnt2;
// 404758: using guessed type int cdvdstm_retryerr_ee;
// 404BE4: using guessed type int cdvdstm_bankgp_ee;
// 404BE8: using guessed type int cdvdstm_bankcur_ee;
// 404BEC: using guessed type int cdvdstm_bankoffs_ee;
// 404BF4: using guessed type int cdvdstm_stmstart_ee;

//----- (00403C10) --------------------------------------------------------
unsigned int __fastcall cdvdstm_memcpy(_DWORD *a1, _DWORD *a2, unsigned int a3)
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

//----- (0040403C) --------------------------------------------------------
void cdvdstm_1()
{
	;
}

#if 0
//----- (00404064) --------------------------------------------------------
int Kprintf(const char *format, ...)
{
	int result; // $v0

	return result;
}
// 404064: variable 'result' is possibly undefined

//----- (00404088) --------------------------------------------------------
int __cdecl RegisterLibraryEntries(struct irx_export_table *exports)
{
	int result; // $v0

	return result;
}
// 404088: variable 'result' is possibly undefined

//----- (00404090) --------------------------------------------------------
int __cdecl ReleaseLibraryEntries(struct irx_export_table *exports)
{
	int result; // $v0

	return result;
}
// 404090: variable 'result' is possibly undefined

//----- (004040B4) --------------------------------------------------------
int __cdecl CpuSuspendIntr(int *state)
{
	int result; // $v0

	return result;
}
// 4040B4: variable 'result' is possibly undefined

//----- (004040BC) --------------------------------------------------------
int __cdecl CpuResumeIntr(int state)
{
	int result; // $v0

	return result;
}
// 4040BC: variable 'result' is possibly undefined

//----- (004040C4) --------------------------------------------------------
int QueryIntrContext(void)
{
	int result; // $v0

	return result;
}
// 4040C4: variable 'result' is possibly undefined

//----- (004040E8) --------------------------------------------------------
int printf(const char *format, ...)
{
	int result; // $v0

	return result;
}
// 4040E8: variable 'result' is possibly undefined

//----- (0040410C) --------------------------------------------------------
int __cdecl DelayThread(int usec)
{
	int result; // $v0

	return result;
}
// 40410C: variable 'result' is possibly undefined

//----- (00404114) --------------------------------------------------------
int __cdecl iSetAlarm(iop_sys_clock_t *sys_clock, unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	int result; // $v0

	return result;
}
// 404114: variable 'result' is possibly undefined

//----- (0040411C) --------------------------------------------------------
int __cdecl CancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	int result; // $v0

	return result;
}
// 40411C: variable 'result' is possibly undefined

//----- (00404124) --------------------------------------------------------
int __cdecl iCancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	int result; // $v0

	return result;
}
// 404124: variable 'result' is possibly undefined

//----- (00404148) --------------------------------------------------------
int __cdecl SetEventFlag(int ef, u32 bits)
{
	int result; // $v0

	return result;
}
// 404148: variable 'result' is possibly undefined

//----- (00404150) --------------------------------------------------------
int __cdecl iSetEventFlag(int ef, u32 bits)
{
	int result; // $v0

	return result;
}
// 404150: variable 'result' is possibly undefined

//----- (00404158) --------------------------------------------------------
int __cdecl ClearEventFlag(int ef, u32 bits)
{
	int result; // $v0

	return result;
}
// 404158: variable 'result' is possibly undefined

//----- (00404160) --------------------------------------------------------
int __cdecl iClearEventFlag(int ef, u32 bits)
{
	int result; // $v0

	return result;
}
// 404160: variable 'result' is possibly undefined

//----- (00404168) --------------------------------------------------------
int __cdecl WaitEventFlag(int ef, u32 bits, int mode, u32 *resbits)
{
	int result; // $v0

	return result;
}
// 404168: variable 'result' is possibly undefined

//----- (0040418C) --------------------------------------------------------
int __cdecl CreateSema(iop_sema_t *sema)
{
	int result; // $v0

	return result;
}
// 40418C: variable 'result' is possibly undefined

//----- (00404194) --------------------------------------------------------
int __cdecl DeleteSema(int semid)
{
	int result; // $v0

	return result;
}
// 404194: variable 'result' is possibly undefined

//----- (0040419C) --------------------------------------------------------
int __cdecl SignalSema(int semid)
{
	int result; // $v0

	return result;
}
// 40419C: variable 'result' is possibly undefined

//----- (004041A4) --------------------------------------------------------
int __cdecl WaitSema(int semid)
{
	int result; // $v0

	return result;
}
// 4041A4: variable 'result' is possibly undefined

//----- (004041C8) --------------------------------------------------------
int __cdecl sceSifSetDma(SifDmaTransfer_t *dmat, int count)
{
	int result; // $v0

	return result;
}
// 4041C8: variable 'result' is possibly undefined

//----- (004041D0) --------------------------------------------------------
int __cdecl sceSifDmaStat(int trid)
{
	int result; // $v0

	return result;
}
// 4041D0: variable 'result' is possibly undefined

//----- (004041F4) --------------------------------------------------------
int __cdecl AddDrv(iop_device_t *device)
{
	int result; // $v0

	return result;
}
// 4041F4: variable 'result' is possibly undefined

//----- (004041FC) --------------------------------------------------------
int __cdecl DelDrv(const char *name)
{
	int result; // $v0

	return result;
}
// 4041FC: variable 'result' is possibly undefined

//----- (00404220) --------------------------------------------------------
int __cdecl sceCdSync(int mode)
{
	int result; // $v0

	return result;
}
// 404220: variable 'result' is possibly undefined

//----- (00404228) --------------------------------------------------------
int sceCdGetDiskType(void)
{
	int result; // $v0

	return result;
}
// 404228: variable 'result' is possibly undefined

//----- (00404230) --------------------------------------------------------
int sceCdBreak(void)
{
	int result; // $v0

	return result;
}
// 404230: variable 'result' is possibly undefined

//----- (00404238) --------------------------------------------------------
int __cdecl sceCdReadCDDA(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode)
{
	int result; // $v0

	return result;
}
// 404238: variable 'result' is possibly undefined

//----- (00404240) --------------------------------------------------------
int sceCdNop(void)
{
	int result; // $v0

	return result;
}
// 404240: variable 'result' is possibly undefined

//----- (00404248) --------------------------------------------------------
int __cdecl sceCdstm0Cb(void (__cdecl *p)(int))
{
	int result; // $v0

	return result;
}
// 404248: variable 'result' is possibly undefined

//----- (00404250) --------------------------------------------------------
int __cdecl sceCdstm1Cb(void (__cdecl *p)(int))
{
	int result; // $v0

	return result;
}
// 404250: variable 'result' is possibly undefined

//----- (00404258) --------------------------------------------------------
int __cdecl sceCdSC(int code, int *param)
{
	int result; // $v0

	return result;
}
// 404258: variable 'result' is possibly undefined

//----- (00404260) --------------------------------------------------------
int sceCdStStop(void)
{
	int result; // $v0

	return result;
}
// 404260: variable 'result' is possibly undefined

//----- (00404268) --------------------------------------------------------
int __cdecl sceCdRE(unsigned int lsn, unsigned int sectors, void *buf, sceCdRMode *mode)
{
	int result; // $v0

	return result;
}
// 404268: variable 'result' is possibly undefined
#endif

// nfuncs=57 queued=57 decompiled=57 lumina nreq=0 worse=0 better=0
// ALL OK, 57 function(s) have been successfully decompiled
