
#include "irx_imports.h"
#include "../00common/defs.h"

#include <errno.h>
#include <kerr.h>

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
#if 0
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
#endif

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

int g_verbose_level = 0; // weak
int g_cdvdstm_in_deldrv = 0; // weak
int g_cdvdstm_bufmax = 0; // weak
int g_cdvdstm_numbytes = 0; // weak
int g_cdvdstm_bankmax = 0; // weak
void *g_cdvdstm_buffer = NULL;
unsigned int g_cdvdstm_sectorcount = 0; // idb
int g_cdvdstm_last_error_for_iop = 0; // idb
int g_cdvdstm_retryerr_iop = 0; // weak
int g_cdvdstm_retrycnt_iop = 0; // weak
static iop_device_ops_t g_cdrom_stm_dev_ops =
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
iop_device_t g_cdrom_stm_dev = { "cdrom_stm", 0x10000010, 1, "CD-ROM_STM ", &g_cdrom_stm_dev_ops }; // idb
int g_cdvdstm_last_error_for_ee = 0;
int g_cdvdstm_bufsz2 = 0; // weak
int g_cdvdstm_chunksz2 = 0; // weak
int g_cdvdstm_bankcnt2 = 0; // weak
void *g_cdvdstm_buffer2 = NULL;
u32 g_cdvdstm_sectorcount2 = 0; // idb
int g_cdvdstm_retryerr_ee = 0; // weak
int g_cdvdstm_retrycnt_ee_normal = 0; // weak
int g_cdvdstm_usedchunksize2 = 0x930; // weak
u32 g_cdvdstm_retrycnt_ee_cdda = 0;
sceCdRMode g_rmode_for_stream0; // weak
int g_cdvdstm_tgt; // weak
int g_cdvdstm_semid; // idb
int g_cdvdstm_ef; // idb
char g_cdvdstm_usedmap_iop[512]; // weak
unsigned int g_cdvdstm_lsn_iop; // idb
int g_cdvdstm_bankgp_iop; // weak
int g_cdvdstm_bankcur_iop; // weak
int g_cdvdstm_bankoffs_iop; // weak
sceCdRMode g_cdvdstm_mode_iop; // idb
int g_cdvdstm_stmstart_iop; // weak
iop_sys_clock_t g_cdvdstm_curclk_iop; // idb
SifDmaTransfer_t g_cdvdstm_dmat; // idb
int g_cdvdstm_readlbn_ee_normal; // weak
SifDmaTransfer_t g_cdvdstm_dmat2; // idb
u32 g_cdvdstm_readlbn_ee_cdda; // idb
char g_cdvdstm_usedmap_ee[512];
u32 g_cdvdstm_lsn_ee; // idb
int g_cdvdstm_bankgp_ee; // weak
int g_cdvdstm_bankcur_ee; // weak
int g_cdvdstm_bankoffs_ee; // weak
sceCdRMode g_cdvdstm_mode_ee;
int g_cdvdstm_stmstart_ee; // weak
iop_sys_clock_t g_cdvdstm_curclk_ee; // idb


//----- (00400000) --------------------------------------------------------
int __fastcall vCancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	return (QueryIntrContext() ? iCancelAlarm : CancelAlarm)(alarm_cb, arg);
}

//----- (00400050) --------------------------------------------------------
int vSetEventFlag()
{
	return (QueryIntrContext() ? iSetEventFlag : SetEventFlag)(g_cdvdstm_ef, 8);
}

//----- (004000A0) --------------------------------------------------------
int vClearEventFlag()
{
	return (QueryIntrContext() ? iClearEventFlag : ClearEventFlag)(g_cdvdstm_ef, ~8);
}

//----- (004000F0) --------------------------------------------------------
int cdvdstm_4()
{
	VERBOSE_PRINTF(1, "Dummy Entry Called\n");
	return 0;
}

//----- (00400124) --------------------------------------------------------
int cdvdstm_2()
{
	cdrom_stm_devctl_t instruct; // [sp+10h] [-38h] BYREF
	int outres; // [sp+28h] [-20h] BYREF

	memset(&instruct, 0, sizeof(instruct));
	instruct.m_cmdid = 3;
	instruct.m_rmode.datapattern = SCECdSecS2048;
	instruct.m_rmode.spindlctrl = SCECdSpinMax;
	instruct.m_rmode.trycount = 0;
	ee_stream_handler_normal(&instruct, 0x14, &outres);
	sceCdStStop();
	return 0;
}

//----- (00400174) --------------------------------------------------------
BOOL __fastcall alarm_cb(void *a1)
{
	KPRINTF("Stm Iop Read Time Out %d(msec)\n", *(_DWORD *)a1 / 0x9000);
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

	VERBOSE_KPRINTF(1, "sceCdStream0 call read size= %d mode= %d addr= %08x\n", rdsize, modearg, addrarg);
	cur_size = 0;
	if ( !sceCdSC(0xFFFFFFFF, &scres) )
		return 0;
	*error_ptr = 0;
	if ( !modearg )
		return iop_stream_handler(0, rdsize, addrarg, 2, &g_rmode_for_stream0, error_ptr);
	vSetEventFlag();
	err = 0;
	streamres = 0;
	while ( (!err || streamres) )
	{
		WaitEventFlag(g_cdvdstm_ef, 8, 0, &efbits);
		streamres = iop_stream_handler(0, rdsize - cur_size, &addrarg[cur_size], 2, &g_rmode_for_stream0, &err);
		if ( rdsize - cur_size != streamres )
			vClearEventFlag();
		cur_size += streamres;
		if ( err )
			*error_ptr = err;
		VERBOSE_KPRINTF(1, "sceCdStream0 BLK cur_size= %d req_size= %d err 0x%x\n", cur_size, rdsize, err);
		if ( (unsigned int)cur_size == rdsize )
			break;
	}
	return cur_size;
}
// 404770: using guessed type sceCdRMode g_rmode_for_stream0;

//----- (00400358) --------------------------------------------------------
int __fastcall sceCdStream0(int rdsize_sectors, char *addrarg, int modearg, int *error_ptr)
{
	return sceCdStream0_inner(rdsize_sectors << 11, addrarg, modearg, error_ptr) / 0x800;
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
	int state; // [sp+20h] [-8h] BYREF
	unsigned int posszarg1_stk; // [sp+50h] [+28h] BYREF

	retryflag = 0;
	posszarg1_stk = posszarg1;
	VERBOSE_KPRINTF(1, "CD Stream Call mode= %d\n", cmdid);
	*error_ptr = 0;
	if ( g_cdvdstm_stmstart_iop == 2 && cmdid != 9 && cmdid != 3 )
	{
		return 0;
	}
	switch ( cmdid )
	{
		case 8:
			sceCdSC(1, &g_cdvdstm_last_error_for_iop);
			if ( sceCdNop() != 0 )
				return 1;
			sceCdSC(0, &g_cdvdstm_last_error_for_iop);
			return 0;
		case 7:
			CpuSuspendIntr(&state);
			vCancelAlarm((unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &g_cdvdstm_curclk_iop);
			sceCdSC(0, &g_cdvdstm_last_error_for_iop);
			CpuResumeIntr(state);
			sceCdSync(0);
			vCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &g_cdvdstm_curclk_iop);
			return 1;
		case 6:
			bankcur_tmp = g_cdvdstm_bankcur_iop;
			if ( !g_cdvdstm_usedmap_iop[bankcur_tmp] )
			{
				bankcur_tmp += 1;
				if ( (unsigned int)bankcur_tmp >= (unsigned int)g_cdvdstm_bankmax )
					bankcur_tmp = 0;
				if ( !g_cdvdstm_usedmap_iop[bankcur_tmp] )
					bankcur_tmp = g_cdvdstm_bankcur_iop;
			}
			for ( i = 0; (i < (unsigned int)g_cdvdstm_bankmax) && g_cdvdstm_usedmap_iop[bankcur_tmp] && (g_cdvdstm_bankgp_iop != bankcur_tmp); i += 1 )
			{
				bankcur_tmp += 1;
				if ( (unsigned int)bankcur_tmp >= (unsigned int)g_cdvdstm_bankmax )
					bankcur_tmp = 0;
			}
			return i * ((unsigned int)g_cdvdstm_numbytes >> 11);
		case 5:
			sceCdstm0Cb((void (__cdecl *)(int))iop_stream_intr_cb_thunk);
			g_cdvdstm_bufmax = posszarg1;
			g_cdvdstm_sectorcount = posszarg1 / posszarg2;
			g_cdvdstm_numbytes = g_cdvdstm_sectorcount << 11;
			g_cdvdstm_buffer = buffer;
			g_cdvdstm_bankmax = posszarg2;
			KPRINTF(
				"Stream Buffer 1Bank %dbyte %dbanks addr:%08x %dbyte used.\n",
				g_cdvdstm_numbytes,
				posszarg2,
				buffer,
				g_cdvdstm_numbytes * posszarg2);
			return 1;
		case 3:
			CpuSuspendIntr(&state);
			g_cdvdstm_stmstart_iop = 0;
			vCancelAlarm((unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &g_cdvdstm_curclk_iop);
			sceCdSC(0, &g_cdvdstm_last_error_for_iop);
			CpuResumeIntr(state);
			sceCdBreak();
			for ( i = 0; i < (unsigned int)g_cdvdstm_bankmax; i += 1 )
				g_cdvdstm_usedmap_iop[i] = 0;
			g_cdvdstm_bankoffs_iop = 0;
			g_cdvdstm_bankcur_iop = 0;
			g_cdvdstm_bankgp_iop = 0;
			sceCdSync(0);
			g_cdvdstm_last_error_for_iop = 0;
			sceCdSC(0xFFFFFFFE, &g_cdvdstm_last_error_for_iop);
			vCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &g_cdvdstm_curclk_iop);
			return 1;
		case 9:
			if ( sceCdSC(0xFFFFFFFF, &g_cdvdstm_last_error_for_iop) != 0 )
			{
				CpuSuspendIntr(&state);
				g_cdvdstm_lsn_iop = posszarg1;
				for ( i = 0; i < (unsigned int)g_cdvdstm_bankmax; i += 1 )
					g_cdvdstm_usedmap_iop[i] = 0;
				g_cdvdstm_stmstart_iop = 2;
				CpuResumeIntr(state);
				return 1;
			}
			return 0;
		case 1:
			g_cdvdstm_mode_iop.datapattern = rmode->datapattern;
			g_cdvdstm_mode_iop.trycount = rmode->trycount;
			g_cdvdstm_mode_iop.spindlctrl = rmode->spindlctrl;
			g_cdvdstm_retryerr_iop = 0;
			break;
		case 4:
			CpuSuspendIntr(&state);
			vCancelAlarm((unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &g_cdvdstm_curclk_iop);
			sceCdSC(0, &g_cdvdstm_last_error_for_iop);
			retryflag = 1;
			CpuResumeIntr(state);
			posszarg2 = 0;
			cmdid = 1;
			g_cdvdstm_lsn_iop = posszarg1;
			g_cdvdstm_bankoffs_iop = 0;
			g_cdvdstm_bankcur_iop = 0;
			g_cdvdstm_bankgp_iop = 0;
			sceCdSync(0);
			vCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &g_cdvdstm_curclk_iop);
			break;
	}
	if ( cmdid == 1 )
	{
		CpuSuspendIntr(&state);
		retryflag = 1;
		vCancelAlarm((unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &g_cdvdstm_curclk_iop);
		sceCdSC(0, &g_cdvdstm_last_error_for_iop);
		CpuResumeIntr(state);
		for ( i = 0; i < (unsigned int)g_cdvdstm_bankmax; i += 1 )
			g_cdvdstm_usedmap_iop[i] = 0;
		g_cdvdstm_lsn_iop = posszarg1;
		sceCdSC(0xFFFFFFE9, (int *)&posszarg1_stk);
		g_cdvdstm_bankoffs_iop = 0;
		g_cdvdstm_bankcur_iop = 0;
		g_cdvdstm_bankgp_iop = 0;
		sceCdSync(0);
		vCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &g_cdvdstm_curclk_iop);
		g_cdvdstm_stmstart_iop = 1;
		sceCdSC(1, &g_cdvdstm_last_error_for_iop);
		if ( !sceCdNop() )
		{
			sceCdSC(0, &g_cdvdstm_last_error_for_iop);
			return 0;
		}
	}
	CpuSuspendIntr(&state);
	written_chunk_size_tmp = -1;
	for ( i = 0; i < posszarg2; i += chunk_size )
	{
		if ( !g_cdvdstm_usedmap_iop[g_cdvdstm_bankcur_iop] )
		{
			VERBOSE_KPRINTF(1, "CD read buffer over run %d %d %d %d %d gp %d pp %d\n", (unsigned __int8)g_cdvdstm_usedmap_iop[0], (unsigned __int8)g_cdvdstm_usedmap_iop[1], (unsigned __int8)g_cdvdstm_usedmap_iop[2], (unsigned __int8)g_cdvdstm_usedmap_iop[3], (unsigned __int8)g_cdvdstm_usedmap_iop[4], g_cdvdstm_bankgp_iop, g_cdvdstm_bankcur_iop);
			bankcur_next_tmp1 = g_cdvdstm_bankcur_iop;
			g_cdvdstm_bankcur_iop += 1;
			if ( (unsigned int)g_cdvdstm_bankcur_iop >= (unsigned int)g_cdvdstm_bankmax )
				g_cdvdstm_bankcur_iop = 0;
			written_chunk_size_tmp = i;
			if ( !g_cdvdstm_usedmap_iop[g_cdvdstm_bankcur_iop] )
			{
				g_cdvdstm_bankcur_iop = bankcur_next_tmp1;
			}
			break;
		}
		if ( (unsigned int)g_cdvdstm_bankoffs_iop >= (unsigned int)g_cdvdstm_numbytes )
		{
			g_cdvdstm_bankoffs_iop = 0;
			g_cdvdstm_usedmap_iop[g_cdvdstm_bankcur_iop] = 0;
			bankcur_next_tmp2 = g_cdvdstm_bankcur_iop;
			g_cdvdstm_bankcur_iop += 1;
			if ( (unsigned int)g_cdvdstm_bankcur_iop >= (unsigned int)g_cdvdstm_bankmax )
				g_cdvdstm_bankcur_iop = 0;
			if ( !g_cdvdstm_usedmap_iop[g_cdvdstm_bankcur_iop] || g_cdvdstm_bankgp_iop == g_cdvdstm_bankcur_iop )
			{
				g_cdvdstm_bankcur_iop = bankcur_next_tmp2;
				written_chunk_size_tmp = i;
				VERBOSE_KPRINTF(1, "CD read buffer over run %d %d %d %d %d gp %d pp %d\n", (unsigned __int8)g_cdvdstm_usedmap_iop[0], (unsigned __int8)g_cdvdstm_usedmap_iop[1], (unsigned __int8)g_cdvdstm_usedmap_iop[2], (unsigned __int8)g_cdvdstm_usedmap_iop[3], (unsigned __int8)g_cdvdstm_usedmap_iop[4], g_cdvdstm_bankgp_iop, g_cdvdstm_bankcur_iop);
				break;
			}
		}
		cdvdstm_memcpy(
			(_DWORD *)((char *)buffer + i),
			(_DWORD *)((char *)g_cdvdstm_buffer + g_cdvdstm_bankcur_iop * g_cdvdstm_numbytes + g_cdvdstm_bankoffs_iop),
			0x800);
		chunk_size = ( (unsigned int)0x800 > posszarg2 - i ) ? (posszarg2 - i) : 0x800;
		g_cdvdstm_bankoffs_iop += chunk_size;
	}
	if ( written_chunk_size_tmp == 0xFFFFFFFF )
		written_chunk_size_tmp = posszarg2;
	CpuResumeIntr(state);
	if ( !retryflag )
	{
		if ( sceCdSC(0xFFFFFFFF, &g_cdvdstm_last_error_for_iop) != 1
			&& !written_chunk_size_tmp
			&& !g_cdvdstm_retryerr_iop )
		{
			g_cdvdstm_retryerr_iop = 273;
		}
		*error_ptr = g_cdvdstm_retryerr_iop;
		g_cdvdstm_retryerr_iop = 0;
		return written_chunk_size_tmp;
	}
	return 1;
}
// 4005AC: conditional instruction was optimized away because $s6.4!=0
// 404694: using guessed type int g_cdvdstm_bufmax;
// 404698: using guessed type int g_cdvdstm_numbytes;
// 40469C: using guessed type int g_cdvdstm_bankmax;
// 4046AC: using guessed type int g_cdvdstm_retryerr_iop;
// 404994: using guessed type int g_cdvdstm_bankgp_iop;
// 404998: using guessed type int g_cdvdstm_bankcur_iop;
// 40499C: using guessed type int g_cdvdstm_bankoffs_iop;
// 4049A4: using guessed type int g_cdvdstm_stmstart_iop;

//----- (00400D30) --------------------------------------------------------
unsigned int __cdecl iop_stream_intr_cb(void *userdata)
{
	int gptmp; // $a0
	int scres1; // [sp+28h] [-8h] BYREF

	(void)userdata;

	VERBOSE_KPRINTF(1, "Intr Read call\n");
	iCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &g_cdvdstm_curclk_iop);
	iCancelAlarm((unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &g_cdvdstm_curclk_iop);
	sceCdSC(0xFFFFFFFF, &scres1);
	if ( !scres1 )
	{
		switch ( sceCdGetDiskType() )
		{
			case SCECdPSCD:
			case SCECdPSCDDA:
			case SCECdPS2CD:
			case SCECdPS2CDDA:
			case SCECdPS2DVD:
				break;
			default:
				scres1 = SCECdErREADCF;
				break;
		}
	}
	g_cdvdstm_curclk_iop.hi = 0;
	if ( g_cdvdstm_stmstart_iop )
		g_cdvdstm_retrycnt_iop = 0;
	if ( g_cdvdstm_stmstart_iop || scres1 || g_cdvdstm_retrycnt_iop )
	{
		VERBOSE_KPRINTF(1, "Stm Rtry stmstart:%d err:%02x retry:%d\n", g_cdvdstm_stmstart_iop, scres1, g_cdvdstm_retrycnt_iop);
	}
	g_cdvdstm_curclk_iop.lo = ( g_cdvdstm_stmstart_iop || scres1 || g_cdvdstm_retrycnt_iop ) ? 0x20f58000 : (0x9000 * sceCdSC(0xFFFFFFEF, &scres1));
	if ( scres1 )
	{
		VERBOSE_KPRINTF(1, "IOP Stream read Error code= 0x%02x retry= %d\n", scres1, g_cdvdstm_retrycnt_iop);
		g_cdvdstm_retrycnt_iop = 1;
		if ( scres1 == SCECdErREAD || scres1 == SCECdErABRT )
		{
			VERBOSE_KPRINTF(1, "On err %08x\n", scres1);
			if ( g_cdvdstm_retrycnt_iop )
				g_cdvdstm_retryerr_iop = scres1;
			g_cdvdstm_retrycnt_iop = 3;
		}
		else
		{
			g_cdvdstm_retryerr_iop = scres1;
		}
	}
	if ( g_cdvdstm_retrycnt_iop )
	{
		unsigned int tgttmp; // $s0

		g_cdvdstm_retrycnt_iop -= 1;
		tgttmp = ( (unsigned int)g_cdvdstm_tgt >= (unsigned int)(0x10 * g_cdvdstm_retrycnt_iop) ) ? (g_cdvdstm_tgt - 0x10 * g_cdvdstm_retrycnt_iop) : (g_cdvdstm_tgt + 0x10 * g_cdvdstm_retrycnt_iop);
		VERBOSE_KPRINTF(1, "Stm Rtry Start Tgt=%d Cur= %d\n", g_cdvdstm_tgt, tgttmp);
		if ( sceCdRE(
					 tgttmp,
					 g_cdvdstm_sectorcount,
					 (char *)g_cdvdstm_buffer + g_cdvdstm_bankgp_iop * g_cdvdstm_numbytes,
					 &g_cdvdstm_mode_iop) )
		{
			iSetAlarm(&g_cdvdstm_curclk_iop, (unsigned int (__cdecl *)(void *))alarm_cb, &g_cdvdstm_curclk_iop);
		}
		else
		{
			g_cdvdstm_curclk_iop.lo = 0x708000;
			if ( iSetAlarm(&g_cdvdstm_curclk_iop, (unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &g_cdvdstm_curclk_iop) && !sceCdNop() )
			{
				sceCdSC(0, &scres1);
			}
			g_cdvdstm_retrycnt_iop += 1;
		}
		return 0;
	}
	else
	{
		if ( !g_cdvdstm_stmstart_iop )
		{
			g_cdvdstm_usedmap_iop[g_cdvdstm_bankgp_iop] = 1;
			gptmp = g_cdvdstm_bankgp_iop;
			g_cdvdstm_bankgp_iop += 1;
			if ( (unsigned int)g_cdvdstm_bankgp_iop >= (unsigned int)g_cdvdstm_bankmax )
				g_cdvdstm_bankgp_iop = 0;
		}
		if ( !g_cdvdstm_stmstart_iop && (g_cdvdstm_usedmap_iop[g_cdvdstm_bankgp_iop] || g_cdvdstm_bankcur_iop == g_cdvdstm_bankgp_iop) )
		{
			g_cdvdstm_bankgp_iop = gptmp;
			g_cdvdstm_usedmap_iop[gptmp] = 0;
			VERBOSE_KPRINTF(1, "read Full %d %d %d %d %d gp %d pp %d spn %d\n", (unsigned __int8)g_cdvdstm_usedmap_iop[0], (unsigned __int8)g_cdvdstm_usedmap_iop[1], (unsigned __int8)g_cdvdstm_usedmap_iop[2], (unsigned __int8)g_cdvdstm_usedmap_iop[3], (unsigned __int8)g_cdvdstm_usedmap_iop[4], g_cdvdstm_bankgp_iop, g_cdvdstm_bankcur_iop, g_cdvdstm_mode_iop.spindlctrl);
			g_cdvdstm_curclk_iop.lo = 0x48000;
			if ( iSetAlarm(&g_cdvdstm_curclk_iop, (unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &g_cdvdstm_curclk_iop) != 0 && sceCdNop() == 0 )
			{
				sceCdSC(0, &scres1);
			}
		}
		else
		{
			if ( g_cdvdstm_stmstart_iop == 2 )
			{
				unsigned int i; // $v1

				g_cdvdstm_bankoffs_iop = 0;
				g_cdvdstm_bankcur_iop = 0;
				g_cdvdstm_bankgp_iop = 0;
				for ( i = 0; i < (unsigned int)g_cdvdstm_bankmax; i += 1 )
					g_cdvdstm_usedmap_iop[i] = 0;
			}
			g_cdvdstm_stmstart_iop = 0;
			g_cdvdstm_tgt = g_cdvdstm_lsn_iop;
			if ( sceCdRE(
						 g_cdvdstm_lsn_iop,
						 g_cdvdstm_sectorcount,
						 (char *)g_cdvdstm_buffer + g_cdvdstm_bankgp_iop * g_cdvdstm_numbytes,
						 &g_cdvdstm_mode_iop) )
			{
				iSetAlarm(&g_cdvdstm_curclk_iop, (unsigned int (__cdecl *)(void *))alarm_cb, &g_cdvdstm_curclk_iop);
			}
			else
			{
				g_cdvdstm_curclk_iop.lo = 0x708000;
				if ( iSetAlarm(&g_cdvdstm_curclk_iop, (unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &g_cdvdstm_curclk_iop)
					&& !sceCdNop() )
				{
					sceCdSC(0, &scres1);
				}
				g_cdvdstm_retrycnt_iop = 1;
			}
			g_cdvdstm_lsn_iop += g_cdvdstm_sectorcount;
		}
	}
	return 0;
}
// 404698: using guessed type int g_cdvdstm_numbytes;
// 40469C: using guessed type int g_cdvdstm_bankmax;
// 4046AC: using guessed type int g_cdvdstm_retryerr_iop;
// 4046B0: using guessed type int g_cdvdstm_retrycnt_iop;
// 404780: using guessed type int g_cdvdstm_tgt;
// 404994: using guessed type int g_cdvdstm_bankgp_iop;
// 404998: using guessed type int g_cdvdstm_bankcur_iop;
// 40499C: using guessed type int g_cdvdstm_bankoffs_iop;
// 4049A4: using guessed type int g_cdvdstm_stmstart_iop;

//----- (00401374) --------------------------------------------------------
int cdrom_stm_init()
{
	iop_sema_t semaparam; // [sp+10h] [-10h] BYREF

	semaparam.attr = 1;
	semaparam.initial = 1;
	semaparam.max = 1;
	semaparam.option = 0;
	g_cdvdstm_semid = CreateSema(&semaparam);
	return 0;
}

//----- (004013B0) --------------------------------------------------------
int cdrom_stm_deinit()
{
	SignalSema(g_cdvdstm_semid);
	DeleteSema(g_cdvdstm_semid);
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
	WaitSema(g_cdvdstm_semid);
	retres = 0;
	if ( g_cdvdstm_in_deldrv )
	{
		SignalSema(g_cdvdstm_semid);
		return -EIO;
	}
	switch ( a3 )
	{
		case 0x4393:
			if ( instruct->m_cmdid == 5 || instruct->m_cmdid == 3 || instruct->m_cmdid - 7 < 2 )
			{
				vSetEventFlag();
			}
			*outres_ptr = iop_stream_handler(
											instruct->m_posszarg1,
											instruct->m_posszarg2,
											instruct->m_buffer,
											instruct->m_cmdid,
											&instruct->m_rmode,
											(int *)&instruct->m_error);
			break;
		case 0x4394:
			*outres_ptr = sceCdStream0(instruct->m_posszarg2, (char *)instruct->m_buffer, instruct->m_cmdid, (int *)&instruct->m_error);
			break;
		case 0x4396:
			ee_stream_handler_normal(instruct, inbuf_len, outres_ptr);
			break;
		case 0x4398:
			ee_stream_handler_cdda(instruct, inbuf_len, outres_ptr);
			break;
		default:
			PRINTF("Un-support devctl %08x\n", a3);
			retres = -EIO;
			break;
	}
	SignalSema(g_cdvdstm_semid);
	return retres;
}
// 404690: using guessed type int g_cdvdstm_in_deldrv;

//----- (00401588) --------------------------------------------------------
int __cdecl cdrom_stm_nulldev()
{
	PRINTF("nulldev0 call\n");
	return -EIO;
}

//----- (004015B0) --------------------------------------------------------
__int64 __cdecl cdrom_stm_nulldev64()
{
	PRINTF("nulldev0 call\n");
	return -EIO;
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
		g_cdvdstm_in_deldrv = 1;
		DelDrv("cdrom_stm");
		CpuSuspendIntr(&state);
		relres = ReleaseLibraryEntries(&_exp_cdvdstm);
		CpuResumeIntr(state);
		g_cdvdstm_in_deldrv = 0;
		if ( relres && relres != KE_LIBRARY_NOTFOUND )
		{
			g_cdvdstm_in_deldrv = 0;
			return 2;
		}
		return 1;
	}
	if ( RegisterLibraryEntries(&_exp_cdvdstm) != 0 )
		return 1;
	DelDrv("cdrom_stm");
	if ( AddDrv(&g_cdrom_stm_dev) )
	{
		cdrom_stm_deinit();
		return 1;
	}
	g_cdvdstm_ef = sceCdSC(0xFFFFFFF5, &scres);
	return 2;
}
// 404690: using guessed type int g_cdvdstm_in_deldrv;

//----- (004016D0) --------------------------------------------------------
BOOL __fastcall stm_alarm_timeout_cb(void *a1)
{
	unsigned int scres; // [sp+10h] [-8h] BYREF

	scres = *(_DWORD *)a1 / 0x9000;
	KPRINTF("Stm EE Read Time Out %d(msec)\n", scres);
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
	cmdid = instruct->m_cmdid;
	posszarg1_stk = instruct->m_posszarg1;
	if ( g_cdvdstm_stmstart_ee == 2 && (cmdid != 9 && cmdid != 3) )
	{
		*outres_ptr = 0;
		return;
	}
	switch ( cmdid )
	{
		case 8:
			sceCdSC(2, &g_cdvdstm_last_error_for_ee);
			if ( sceCdNop() == 0 )
			{
				sceCdSC(0, &g_cdvdstm_last_error_for_ee);
				*outres_ptr = 0;
				return;
			}
			*outres_ptr = 1;
			return;
		case 7:
			CpuSuspendIntr(&state);
			CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal, &g_cdvdstm_curclk_ee);
			sceCdSC(0, &g_cdvdstm_last_error_for_ee);
			CpuResumeIntr(state);
			sceCdSync(0);
			*outres_ptr = 1;
			CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
			return;
		case 6:
			bankcur_tmp = g_cdvdstm_bankcur_ee;
			if ( !g_cdvdstm_usedmap_ee[bankcur_tmp] )
			{
				bankcur_tmp += 1;
				if ( (unsigned int)bankcur_tmp >= (unsigned int)g_cdvdstm_bankcnt2 )
					bankcur_tmp = 0;
				if ( !g_cdvdstm_usedmap_ee[bankcur_tmp] )
					bankcur_tmp = g_cdvdstm_bankcur_ee;
			}
			for ( i = 0; (i < (unsigned int)g_cdvdstm_bankcnt2) && g_cdvdstm_usedmap_ee[bankcur_tmp] && (g_cdvdstm_bankgp_ee != bankcur_tmp); i += 1 )
			{
				bankcur_tmp += 1;
				if ( (unsigned int)bankcur_tmp >= (unsigned int)g_cdvdstm_bankcnt2 )
					bankcur_tmp = 0;
			}
			*outres_ptr = i * ((unsigned int)g_cdvdstm_chunksz2 >> 11);
			return;
		case 5:
			sceCdstm1Cb((void (__cdecl *)(int))ee_stream_intr_cb_normal_thunk);
			if ( !instruct->m_posszarg2 )
				_break(7, 0);
			chunks_sectors = instruct->m_posszarg1 / instruct->m_posszarg2;
			g_cdvdstm_bufsz2 = instruct->m_posszarg1;
			g_cdvdstm_sectorcount2 = chunks_sectors;
			g_cdvdstm_chunksz2 = chunks_sectors << 11;
			g_cdvdstm_buffer2 = (char *)instruct->m_buffer;
			g_cdvdstm_bankcnt2 = instruct->m_posszarg2;
			PRINTF(
				"Stream Buffer 1Bank %dbyte %dbanks %dbyte used\n",
				(int)(chunks_sectors << 11),
				(int)(instruct->m_posszarg2),
				(int)((chunks_sectors << 11) * (instruct->m_posszarg2)));
			*outres_ptr = 1;
			return;
		case 3:
			CpuSuspendIntr(&state);
			g_cdvdstm_stmstart_ee = 0;
			CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal, &g_cdvdstm_curclk_ee);
			sceCdSC(0, &g_cdvdstm_last_error_for_ee);
			CpuResumeIntr(state);
			sceCdBreak();
			for ( i = 0; i < (unsigned int)g_cdvdstm_bankcnt2; i += 1 )
			{
				g_cdvdstm_usedmap_ee[i] = 0;
			}
			g_cdvdstm_bankoffs_ee = 0;
			g_cdvdstm_bankcur_ee = 0;
			g_cdvdstm_bankgp_ee = 0;
			*outres_ptr = 1;
			sceCdSync(0);
			g_cdvdstm_last_error_for_ee = 0;
			sceCdSC(0xFFFFFFFE, &g_cdvdstm_last_error_for_ee);
			CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
			return;
		case 1:
			g_cdvdstm_mode_ee.datapattern = instruct->m_rmode.datapattern;
			g_cdvdstm_mode_ee.trycount = instruct->m_rmode.trycount;
			g_cdvdstm_mode_ee.spindlctrl = instruct->m_rmode.spindlctrl;
			g_cdvdstm_retryerr_ee = 0;
			break;
	}
	posszarg2_bytes = instruct->m_posszarg2 << 11;
	if ( cmdid == 9 )
	{
		if ( sceCdSC(0xFFFFFFFF, &g_cdvdstm_last_error_for_ee) )
		{
			CpuSuspendIntr(&state);
			g_cdvdstm_lsn_ee = instruct->m_posszarg1;
			for ( i = 0; i < (unsigned int)g_cdvdstm_bankcnt2; i += 1 )
			{
				g_cdvdstm_usedmap_ee[i] = 0;
			}
			g_cdvdstm_stmstart_ee = 2;
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
		CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal, &g_cdvdstm_curclk_ee);
		sceCdSC(0, &g_cdvdstm_last_error_for_ee);
		posszarg2_bytes = 0;
		cmdid = 1;
		CpuResumeIntr(state);
		g_cdvdstm_lsn_ee = instruct->m_posszarg1;
		g_cdvdstm_bankoffs_ee = 0;
		g_cdvdstm_bankcur_ee = 0;
		g_cdvdstm_bankgp_ee = 0;
		sceCdSync(0);
		CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
	}
	if ( cmdid == 1 )
	{
		CpuSuspendIntr(&state);
		CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal, &g_cdvdstm_curclk_ee);
		sceCdSC(0, &g_cdvdstm_last_error_for_ee);
		CpuResumeIntr(state);
		retryflag = 1;
		for ( i = 0; i < (unsigned int)g_cdvdstm_bankcnt2; i += 1 )
		{
			g_cdvdstm_usedmap_ee[i] = 0;
		}
		g_cdvdstm_lsn_ee = instruct->m_posszarg1;
		sceCdSC(0xFFFFFFE9, (int *)&posszarg1_stk);
		g_cdvdstm_bankoffs_ee = 0;
		g_cdvdstm_bankcur_ee = 0;
		sceCdSync(0);
		CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
		g_cdvdstm_stmstart_ee = 1;
		sceCdSC(2, &g_cdvdstm_last_error_for_ee);
		if ( !sceCdNop() )
		{
			sceCdSC(0, &g_cdvdstm_last_error_for_ee);
			*outres_ptr = 0;
			return;
		}
	}
	posszarg2_bytes_overrun = -1;
	for ( i = 0; i < posszarg2_bytes; i += posszarg2_bytes_clamped )
	{
		unsigned int posszarg2_bytes_remain; // $s2

		posszarg2_bytes_remain = posszarg2_bytes - i;
		if ( !g_cdvdstm_usedmap_ee[g_cdvdstm_bankcur_ee] )
		{
			VERBOSE_KPRINTF(1, "CD read buffer over run %d %d %d %d %d gp %d pp %d\n", (unsigned __int8)g_cdvdstm_usedmap_ee[0], (unsigned __int8)g_cdvdstm_usedmap_ee[1], (unsigned __int8)g_cdvdstm_usedmap_ee[2], (unsigned __int8)g_cdvdstm_usedmap_ee[3], (unsigned __int8)g_cdvdstm_usedmap_ee[4], g_cdvdstm_bankgp_ee, g_cdvdstm_bankcur_ee);
			CpuSuspendIntr(&state);
			bankcur_next_tmp1 = g_cdvdstm_bankcur_ee;
			g_cdvdstm_bankcur_ee += 1;
			if ( (unsigned int)g_cdvdstm_bankcur_ee >= (unsigned int)g_cdvdstm_bankcnt2 )
				g_cdvdstm_bankcur_ee = 0;
			if ( !g_cdvdstm_usedmap_ee[g_cdvdstm_bankcur_ee] )
				g_cdvdstm_bankcur_ee = bankcur_next_tmp1;
			posszarg2_bytes_overrun = posszarg2_bytes - posszarg2_bytes_remain;
			CpuResumeIntr(state);
			break;
		}
		posszarg2_bytes_clamped = ( (unsigned int)(g_cdvdstm_chunksz2 - g_cdvdstm_bankoffs_ee) < posszarg2_bytes_remain ) ? (unsigned int)(g_cdvdstm_chunksz2 - g_cdvdstm_bankoffs_ee) : posszarg2_bytes_remain;
		g_cdvdstm_dmat.dest = ((char *)instruct->m_buffer) + i;
		g_cdvdstm_dmat.size = posszarg2_bytes_clamped;
		g_cdvdstm_dmat.attr = 0;
		g_cdvdstm_dmat.src = (char *)g_cdvdstm_buffer2 + g_cdvdstm_bankcur_ee * g_cdvdstm_chunksz2 + g_cdvdstm_bankoffs_ee;
		if ( posszarg2_bytes_clamped )
		{
			while ( 1 )
			{
				CpuSuspendIntr(&state);
				dmat1 = sceSifSetDma(&g_cdvdstm_dmat, 1);
				CpuResumeIntr(state);
				if ( dmat1 )
					break;
				DelayThread(500);
			}
			g_cdvdstm_bankoffs_ee += posszarg2_bytes_clamped;
			while ( sceSifDmaStat(dmat1) >= 0 )
				;
		}
		if ( (unsigned int)g_cdvdstm_bankoffs_ee >= (unsigned int)g_cdvdstm_chunksz2 )
		{
			CpuSuspendIntr(&state);
			g_cdvdstm_bankoffs_ee = 0;
			g_cdvdstm_usedmap_ee[g_cdvdstm_bankcur_ee] = 0;
			bankcur_next_tmp2 = g_cdvdstm_bankcur_ee;
			g_cdvdstm_bankcur_ee += 1;
			if ( (unsigned int)g_cdvdstm_bankcur_ee >= (unsigned int)g_cdvdstm_bankcnt2 )
				g_cdvdstm_bankcur_ee = 0;
			if ( g_cdvdstm_usedmap_ee[g_cdvdstm_bankcur_ee] && g_cdvdstm_bankgp_ee != g_cdvdstm_bankcur_ee )
			{
				CpuResumeIntr(state);
			}
			else
			{
				g_cdvdstm_bankcur_ee = bankcur_next_tmp2;
				CpuResumeIntr(state);
				VERBOSE_KPRINTF(1, "CD read buffer over run %d %d %d %d %d gp %d pp %d\n", (unsigned __int8)g_cdvdstm_usedmap_ee[0], (unsigned __int8)g_cdvdstm_usedmap_ee[1], (unsigned __int8)g_cdvdstm_usedmap_ee[2], (unsigned __int8)g_cdvdstm_usedmap_ee[3], (unsigned __int8)g_cdvdstm_usedmap_ee[4], g_cdvdstm_bankgp_ee, g_cdvdstm_bankcur_ee);
				posszarg2_bytes_overrun = posszarg2_bytes - (posszarg2_bytes_remain - posszarg2_bytes_clamped);
				break;
			}
		}
	}
	if ( posszarg2_bytes_overrun == -1 )
		posszarg2_bytes_overrun = posszarg2_bytes;
	outres_tmp2 = ( retryflag ) ? 1 : (posszarg2_bytes_overrun / 0x800);
	if ( !retryflag )
	{
		if ( sceCdSC(0xFFFFFFFF, &g_cdvdstm_last_error_for_ee) != 2 && !outres_tmp2 && !g_cdvdstm_retryerr_ee )
			g_cdvdstm_retryerr_ee = 273;
		if ( g_cdvdstm_retryerr_ee )
		{
			outres_tmp2 = (unsigned __int16)outres_tmp2 | (g_cdvdstm_retryerr_ee << 16);
			g_cdvdstm_retryerr_ee = 0;
		}
	}
	*outres_ptr = outres_tmp2;
	return;
}
// 404744: using guessed type int g_cdvdstm_bufsz2;
// 404748: using guessed type int g_cdvdstm_chunksz2;
// 40474C: using guessed type int g_cdvdstm_bankcnt2;
// 404758: using guessed type int g_cdvdstm_retryerr_ee;
// 404BE4: using guessed type int g_cdvdstm_bankgp_ee;
// 404BE8: using guessed type int g_cdvdstm_bankcur_ee;
// 404BEC: using guessed type int g_cdvdstm_bankoffs_ee;
// 404BF4: using guessed type int g_cdvdstm_stmstart_ee;

//----- (00402230) --------------------------------------------------------
unsigned int __fastcall ee_stream_intr_cb_normal(void *userdata)
{
	int gptmp; // $a0

	(void)userdata;

	VERBOSE_KPRINTF(1, "Intr EE Stm Read call\n");
	iCancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
	iCancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal, &g_cdvdstm_curclk_ee);
	sceCdSC(0xFFFFFFFF, &g_cdvdstm_last_error_for_ee);
	if ( !g_cdvdstm_last_error_for_ee )
	{
		switch ( sceCdGetDiskType() )
		{
			case SCECdPSCD:
			case SCECdPSCDDA:
			case SCECdPS2CD:
			case SCECdPS2CDDA:
			case SCECdPS2DVD:
				break;
			default:
				g_cdvdstm_last_error_for_ee = SCECdErREADCF;
				break;
		}
	}
	g_cdvdstm_curclk_ee.hi = 0;
	if ( g_cdvdstm_stmstart_ee )
		g_cdvdstm_retrycnt_ee_normal = 0;
	g_cdvdstm_curclk_ee.lo = ( g_cdvdstm_stmstart_ee || g_cdvdstm_last_error_for_ee || g_cdvdstm_retrycnt_ee_normal ) ? 0x20f58000 : (0x9000 * sceCdSC(0xFFFFFFEF, &g_cdvdstm_last_error_for_ee));
	if ( g_cdvdstm_last_error_for_ee )
	{
		VERBOSE_KPRINTF(1, "EE Stream read LBN= %d Error code= 0x%02x retry= %d\n", g_cdvdstm_readlbn_ee_normal, g_cdvdstm_last_error_for_ee, g_cdvdstm_retrycnt_ee_normal);
		if ( g_cdvdstm_last_error_for_ee == SCECdErREAD || g_cdvdstm_last_error_for_ee == SCECdErABRT )
		{
			if ( g_cdvdstm_retrycnt_ee_normal )
			{
				VERBOSE_KPRINTF(1, "On Retry retry %d err %08x\n", g_cdvdstm_retrycnt_ee_normal, g_cdvdstm_last_error_for_ee);
			}
			g_cdvdstm_retrycnt_ee_normal = 3;
		}
		else
		{
			g_cdvdstm_retrycnt_ee_normal = 1;
		}
		g_cdvdstm_retryerr_ee = g_cdvdstm_last_error_for_ee;
	}
	if ( g_cdvdstm_retrycnt_ee_normal )
	{
		g_cdvdstm_retrycnt_ee_normal -= 1;
		if ( sceCdRE(
					 ( (unsigned int)g_cdvdstm_readlbn_ee_normal >= (unsigned int)(0x10 * g_cdvdstm_retrycnt_ee_normal) ) ? (g_cdvdstm_readlbn_ee_normal - 0x10 * g_cdvdstm_retrycnt_ee_normal) : (g_cdvdstm_readlbn_ee_normal + 0x10 * g_cdvdstm_retrycnt_ee_normal),
					 g_cdvdstm_sectorcount2,
					 (char *)g_cdvdstm_buffer2 + g_cdvdstm_bankgp_ee * g_cdvdstm_chunksz2,
					 &g_cdvdstm_mode_ee) )
		{
			iSetAlarm(&g_cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
		}
		else
		{
			VERBOSE_KPRINTF(1, "Stm Read Call fail\n");
			g_cdvdstm_curclk_ee.lo = 0x708000;
			if ( iSetAlarm(&g_cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal, &g_cdvdstm_curclk_ee) && !sceCdNop() )
			{
				sceCdSC(0, &g_cdvdstm_last_error_for_ee);
			}
			g_cdvdstm_retrycnt_ee_normal += 1;
		}
	}
	else
	{
		if ( !g_cdvdstm_stmstart_ee )
		{
			g_cdvdstm_usedmap_ee[g_cdvdstm_bankgp_ee] = 1;
			gptmp = g_cdvdstm_bankgp_ee;
			g_cdvdstm_bankgp_ee += 1;
			if ( (unsigned int)g_cdvdstm_bankgp_ee >= (unsigned int)g_cdvdstm_bankcnt2 )
				g_cdvdstm_bankgp_ee = 0;
		}
		if ( !g_cdvdstm_stmstart_ee && (g_cdvdstm_usedmap_ee[g_cdvdstm_bankgp_ee] || g_cdvdstm_bankcur_ee == g_cdvdstm_bankgp_ee) )
		{
			g_cdvdstm_bankgp_ee = gptmp;
			g_cdvdstm_usedmap_ee[gptmp] = 0;
			VERBOSE_KPRINTF(1, "read Full %d %d %d %d %d gp %d pp %d spn %d\n", (unsigned __int8)g_cdvdstm_usedmap_ee[0], (unsigned __int8)g_cdvdstm_usedmap_ee[1], (unsigned __int8)g_cdvdstm_usedmap_ee[2], (unsigned __int8)g_cdvdstm_usedmap_ee[3], (unsigned __int8)g_cdvdstm_usedmap_ee[4], g_cdvdstm_bankgp_ee, g_cdvdstm_bankcur_ee, g_cdvdstm_mode_ee.spindlctrl);
			g_cdvdstm_curclk_ee.lo = 0x48000;
			if ( iSetAlarm(
									&g_cdvdstm_curclk_ee,
									(unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal,
									&g_cdvdstm_curclk_ee) != 0 && sceCdNop() == 0 )
			{
				sceCdSC(0, &g_cdvdstm_last_error_for_ee);
			}
		}
		else
		{
			if ( g_cdvdstm_stmstart_ee == 2 )
			{
				unsigned int i; // $v1

				g_cdvdstm_bankoffs_ee = 0;
				g_cdvdstm_bankcur_ee = 0;
				g_cdvdstm_bankgp_ee = 0;
				for ( i = 0; i < (unsigned int)g_cdvdstm_bankcnt2; i += 1 )
					g_cdvdstm_usedmap_ee[i] = 0;
			}
			g_cdvdstm_stmstart_ee = 0;
			g_cdvdstm_readlbn_ee_normal = g_cdvdstm_lsn_ee;
			if ( sceCdRE(
						 g_cdvdstm_lsn_ee,
						 g_cdvdstm_sectorcount2,
						 (char *)g_cdvdstm_buffer2 + g_cdvdstm_bankgp_ee * g_cdvdstm_chunksz2,
						 &g_cdvdstm_mode_ee) )
			{
				iSetAlarm(&g_cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
			}
			else
			{
				VERBOSE_KPRINTF(1, "Stm Read Call1 fail\n");
				g_cdvdstm_curclk_ee.lo = 0x708000;
				if ( iSetAlarm(
							 &g_cdvdstm_curclk_ee,
							 (unsigned int (__cdecl *)(void *))ee_stream_intr_cb_normal,
							 &g_cdvdstm_curclk_ee)
					&& !sceCdNop() )
				{
					sceCdSC(0, &g_cdvdstm_last_error_for_ee);
				}
				g_cdvdstm_retrycnt_ee_normal = 1;
			}
			g_cdvdstm_lsn_ee += g_cdvdstm_sectorcount2;
		}
	}
	return 0;
}
// 404748: using guessed type int g_cdvdstm_chunksz2;
// 40474C: using guessed type int g_cdvdstm_bankcnt2;
// 404758: using guessed type int g_cdvdstm_retryerr_ee;
// 40475C: using guessed type int g_cdvdstm_retrycnt_ee_normal;
// 4049C0: using guessed type int g_cdvdstm_readlbn_ee_normal;
// 404BE4: using guessed type int g_cdvdstm_bankgp_ee;
// 404BE8: using guessed type int g_cdvdstm_bankcur_ee;
// 404BEC: using guessed type int g_cdvdstm_bankoffs_ee;
// 404BF4: using guessed type int g_cdvdstm_stmstart_ee;

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

	cmdid = instruct->m_cmdid;
	posszarg2_bytes = instruct->m_posszarg2 * g_cdvdstm_usedchunksize2;
	retryflag = 0;
	if ( g_cdvdstm_stmstart_ee == 2 && (cmdid != 9 && cmdid != 3) )
	{
		*outres_ptr = 0;
		return;
	}
	switch ( cmdid )
	{
		case 8:
			sceCdSC(2, &g_cdvdstm_last_error_for_ee);
			if ( sceCdNop() )
			{
				*outres_ptr = 1;
				return;
			}
			sceCdSC(0, &g_cdvdstm_last_error_for_ee);
			*outres_ptr = 0;
			return;
		case 7:
			CpuSuspendIntr(&state);
			CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &g_cdvdstm_curclk_ee);
			sceCdSC(0, &g_cdvdstm_last_error_for_ee);
			CpuResumeIntr(state);
			sceCdSync(0);
			*outres_ptr = 1;
			CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
			return;
		case 6:
			bankcur_tmp = g_cdvdstm_bankcur_ee;
			if ( !g_cdvdstm_usedmap_ee[bankcur_tmp] )
			{
				bankcur_tmp += 1;
				if ( (unsigned int)bankcur_tmp >= (unsigned int)g_cdvdstm_bankcnt2 )
					bankcur_tmp = 0;
				if ( !g_cdvdstm_usedmap_ee[bankcur_tmp] )
					bankcur_tmp = g_cdvdstm_bankcur_ee;
			}
			for ( i = 0; (i < (unsigned int)g_cdvdstm_bankcnt2) && g_cdvdstm_usedmap_ee[bankcur_tmp] && (g_cdvdstm_bankgp_ee != bankcur_tmp); i += 1 )
			{
				bankcur_tmp += 1;
				if ( (unsigned int)(bankcur_tmp) >= (unsigned int)g_cdvdstm_bankcnt2 )
					bankcur_tmp = 0;
			}
			if ( !g_cdvdstm_usedchunksize2 )
				_break(7, 0);
			*outres_ptr = i * (g_cdvdstm_chunksz2 / (unsigned int)g_cdvdstm_usedchunksize2);
			return;
		case 5:
			sceCdstm1Cb((void (__cdecl *)(int))ee_stream_intr_cb_cdda_thunk);
			switch ( instruct->m_rmode.datapattern )
			{
				case SCECdSecS2368:
					g_cdvdstm_usedchunksize2 = 2368;
					break;
				case SCECdSecS2448:
					g_cdvdstm_usedchunksize2 = 2448;
					break;
				case SCECdSecS2352:
				default:
					g_cdvdstm_usedchunksize2 = 0x930;
					break;
			}
			if ( !instruct->m_posszarg2 )
				_break(7, 0);
			chunks_sectors = instruct->m_posszarg1 / instruct->m_posszarg2;
			g_cdvdstm_bufsz2 = instruct->m_posszarg1;
			g_cdvdstm_sectorcount2 = chunks_sectors;
			g_cdvdstm_chunksz2 = chunks_sectors * g_cdvdstm_usedchunksize2;
			g_cdvdstm_buffer2 = (char *)instruct->m_buffer;
			g_cdvdstm_bankcnt2 = instruct->m_posszarg2;
			PRINTF(
				"DA Stream Buffer 1Bank %dbyte %dbanks %dbyte used\n",
				(int)(chunks_sectors * g_cdvdstm_usedchunksize2),
				(int)instruct->m_posszarg2,
				(int)(chunks_sectors * g_cdvdstm_usedchunksize2 * instruct->m_posszarg2));
			*outres_ptr = 1;
			return;
		case 3:
			CpuSuspendIntr(&state);
			g_cdvdstm_stmstart_ee = 0;
			CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &g_cdvdstm_curclk_ee);
			sceCdSC(0, &g_cdvdstm_last_error_for_ee);
			CpuResumeIntr(state);
			sceCdBreak();
			for ( i = 0; i < (unsigned int)g_cdvdstm_bankcnt2; i += 1 )
			{
				g_cdvdstm_usedmap_ee[i] = 0;
			}
			g_cdvdstm_bankoffs_ee = 0;
			g_cdvdstm_bankcur_ee = 0;
			g_cdvdstm_bankgp_ee = 0;
			*outres_ptr = 1;
			sceCdSync(0);
			g_cdvdstm_last_error_for_ee = 0;
			sceCdSC(0xFFFFFFFE, &g_cdvdstm_last_error_for_ee);
			CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
			return;
		case 1:
			g_cdvdstm_mode_ee.datapattern = instruct->m_rmode.datapattern;
			g_cdvdstm_mode_ee.trycount = instruct->m_rmode.trycount;
			g_cdvdstm_mode_ee.spindlctrl = instruct->m_rmode.spindlctrl;
			g_cdvdstm_retryerr_ee = 0;
			break;
	}
	if ( cmdid == 9 )
	{
		if ( sceCdSC(0xFFFFFFFF, &g_cdvdstm_last_error_for_ee) )
		{
			CpuSuspendIntr(&state);
			g_cdvdstm_lsn_ee = instruct->m_posszarg1;
			for ( i = 0; i < (unsigned int)g_cdvdstm_bankcnt2; i += 1 )
			{
				g_cdvdstm_usedmap_ee[i] = 0;
			}
			g_cdvdstm_stmstart_ee = 2;
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
		CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &g_cdvdstm_curclk_ee);
		sceCdSC(0, &g_cdvdstm_last_error_for_ee);
		posszarg2_bytes = 0;
		cmdid = 1;
		CpuResumeIntr(state);
		g_cdvdstm_lsn_ee = instruct->m_posszarg1;
		g_cdvdstm_bankoffs_ee = 0;
		g_cdvdstm_bankcur_ee = 0;
		g_cdvdstm_bankgp_ee = 0;
		sceCdSync(0);
		CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
	}
	if ( cmdid == 1 )
	{
		signed int posszarg2_chunks; // $s0

		CpuSuspendIntr(&state);
		CancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &g_cdvdstm_curclk_ee);
		sceCdSC(0, &g_cdvdstm_last_error_for_ee);
		CpuResumeIntr(state);
		retryflag = 1;
		for ( i = 0; i < (unsigned int)g_cdvdstm_bankcnt2; i += 1 )
		{
			g_cdvdstm_usedmap_ee[i] = 0;
		}
		g_cdvdstm_lsn_ee = instruct->m_posszarg1;
		g_cdvdstm_bankoffs_ee = 0;
		g_cdvdstm_bankcur_ee = 0;
		sceCdSync(0);
		CancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
		if ( !g_cdvdstm_chunksz2 )
			_break(7, 0);
		posszarg2_chunks = (posszarg2_bytes / g_cdvdstm_chunksz2) + (( posszarg2_bytes % g_cdvdstm_chunksz2 ) ? 1 : 0);
		for ( g_cdvdstm_bankgp_ee = 0; g_cdvdstm_bankgp_ee < posszarg2_chunks; g_cdvdstm_bankgp_ee += 1 )
		{
			int outres_tmp2; // [sp+20h] [-10h]

			outres_tmp2 = sceCdReadCDDA(g_cdvdstm_lsn_ee, g_cdvdstm_sectorcount2, g_cdvdstm_buffer2, &g_cdvdstm_mode_ee);
			sceCdSync(3);
			sceCdSC(0xFFFFFFFF, &g_cdvdstm_last_error_for_ee);
			if ( g_cdvdstm_last_error_for_ee || !outres_tmp2 )
			{
				sceCdSC(0, &g_cdvdstm_last_error_for_ee);
				*outres_ptr = 0;
				return;
			}
			g_cdvdstm_lsn_ee += g_cdvdstm_sectorcount2;
			g_cdvdstm_usedmap_ee[g_cdvdstm_bankgp_ee] = 1;
		}
		g_cdvdstm_stmstart_ee = 1;
		sceCdSC(2, &g_cdvdstm_last_error_for_ee);
		if ( !sceCdNop() )
		{
			sceCdSC(0, &g_cdvdstm_last_error_for_ee);
			*outres_ptr = 0;
			return;
		}
	}
	posszarg2_bytes_overrun = -1;
	for ( i = 0; i < posszarg2_bytes; i += posszarg2_bytes_clamped )
	{
		unsigned int posszarg2_bytes_remain; // $s2

		posszarg2_bytes_remain = posszarg2_bytes - i;
		if ( !g_cdvdstm_usedmap_ee[g_cdvdstm_bankcur_ee] )
		{
			VERBOSE_KPRINTF(1, "CD read buffer over run %d %d %d %d %d gp %d pp %d\n", (unsigned __int8)g_cdvdstm_usedmap_ee[0], (unsigned __int8)g_cdvdstm_usedmap_ee[1], (unsigned __int8)g_cdvdstm_usedmap_ee[2], (unsigned __int8)g_cdvdstm_usedmap_ee[3], (unsigned __int8)g_cdvdstm_usedmap_ee[4], g_cdvdstm_bankgp_ee, g_cdvdstm_bankcur_ee);
			CpuSuspendIntr(&state);
			bankcur_next_tmp1 = g_cdvdstm_bankcur_ee;
			g_cdvdstm_bankcur_ee += 1;
			if ( (unsigned int)g_cdvdstm_bankcur_ee >= (unsigned int)g_cdvdstm_bankcnt2 )
				g_cdvdstm_bankcur_ee = 0;
			if ( !g_cdvdstm_usedmap_ee[g_cdvdstm_bankcur_ee] )
				g_cdvdstm_bankcur_ee = bankcur_next_tmp1;
			posszarg2_bytes_overrun = posszarg2_bytes - posszarg2_bytes_remain;
			CpuResumeIntr(state);
			break;
		}
		posszarg2_bytes_clamped = ( (unsigned int)(g_cdvdstm_chunksz2 - g_cdvdstm_bankoffs_ee) < posszarg2_bytes_remain ) ? (unsigned int)(g_cdvdstm_chunksz2 - g_cdvdstm_bankoffs_ee) : posszarg2_bytes_remain;
		g_cdvdstm_dmat2.dest = ((char *)instruct->m_buffer) + i;
		g_cdvdstm_dmat2.size = posszarg2_bytes_clamped;
		g_cdvdstm_dmat2.attr = 0;
		g_cdvdstm_dmat2.src = (char *)g_cdvdstm_buffer2 + g_cdvdstm_bankcur_ee * g_cdvdstm_chunksz2 + g_cdvdstm_bankoffs_ee;
		if ( posszarg2_bytes_clamped )
		{
			while ( 1 )
			{
				CpuSuspendIntr(&state);
				dmat2 = sceSifSetDma(&g_cdvdstm_dmat2, 1);
				CpuResumeIntr(state);
				if ( dmat2 )
					break;
				DelayThread(500);
			}
			g_cdvdstm_bankoffs_ee += posszarg2_bytes_clamped;
			while ( sceSifDmaStat(dmat2) >= 0 )
				;
		}
		if ( (unsigned int)g_cdvdstm_bankoffs_ee >= (unsigned int)g_cdvdstm_chunksz2 )
		{
			CpuSuspendIntr(&state);
			g_cdvdstm_bankoffs_ee = 0;
			g_cdvdstm_usedmap_ee[g_cdvdstm_bankcur_ee] = 0;
			bankcur_next_tmp2 = g_cdvdstm_bankcur_ee;
			g_cdvdstm_bankcur_ee += 1;
			if ( (unsigned int)g_cdvdstm_bankcur_ee >= (unsigned int)g_cdvdstm_bankcnt2 )
				g_cdvdstm_bankcur_ee = 0;
			if ( g_cdvdstm_usedmap_ee[g_cdvdstm_bankcur_ee] && g_cdvdstm_bankgp_ee != g_cdvdstm_bankcur_ee )
			{
				CpuResumeIntr(state);
			}
			else
			{
				g_cdvdstm_bankcur_ee = bankcur_next_tmp2;
				CpuResumeIntr(state);
				VERBOSE_KPRINTF(1, "CD read buffer over run %d %d %d %d %d gp %d pp %d\n", (unsigned __int8)g_cdvdstm_usedmap_ee[0], (unsigned __int8)g_cdvdstm_usedmap_ee[1], (unsigned __int8)g_cdvdstm_usedmap_ee[2], (unsigned __int8)g_cdvdstm_usedmap_ee[3], (unsigned __int8)g_cdvdstm_usedmap_ee[4], g_cdvdstm_bankgp_ee, g_cdvdstm_bankcur_ee);
				posszarg2_bytes_overrun = posszarg2_bytes - (posszarg2_bytes_remain - posszarg2_bytes_clamped);
				break;
			}
		}
	}
	if ( posszarg2_bytes_overrun == 0xFFFFFFFF )
		posszarg2_bytes_overrun = posszarg2_bytes;
	if ( !g_cdvdstm_usedchunksize2 )
		_break(7, 0);
	posszarg2_overrun_chunks2 = posszarg2_bytes_overrun / g_cdvdstm_usedchunksize2;
	if ( retryflag )
	{
		*outres_ptr = 1;
		return;
	}
	if ( sceCdSC(0xFFFFFFFF, &g_cdvdstm_last_error_for_ee) != 2 && !posszarg2_overrun_chunks2 && !g_cdvdstm_retryerr_ee )
		g_cdvdstm_retryerr_ee = 273;
	if ( g_cdvdstm_retryerr_ee )
	{
		posszarg2_overrun_chunks2 = (unsigned __int16)posszarg2_overrun_chunks2 | (g_cdvdstm_retryerr_ee << 16);
		g_cdvdstm_retryerr_ee = 0;
	}
	*outres_ptr = posszarg2_overrun_chunks2;
}
// 402B7C: conditional instruction was optimized away because $v0.4!=0
// 404744: using guessed type int g_cdvdstm_bufsz2;
// 404748: using guessed type int g_cdvdstm_chunksz2;
// 40474C: using guessed type int g_cdvdstm_bankcnt2;
// 404758: using guessed type int g_cdvdstm_retryerr_ee;
// 404760: using guessed type int g_cdvdstm_usedchunksize2;
// 404BE4: using guessed type int g_cdvdstm_bankgp_ee;
// 404BE8: using guessed type int g_cdvdstm_bankcur_ee;
// 404BEC: using guessed type int g_cdvdstm_bankoffs_ee;
// 404BF4: using guessed type int g_cdvdstm_stmstart_ee;

//----- (00403530) --------------------------------------------------------
unsigned int __fastcall ee_stream_intr_cb_cdda(void *userdata)
{
	int gptmp; // $a0

	(void)userdata;

	VERBOSE_KPRINTF(1, "Intr EE DA Stm Read call\n");
	iCancelAlarm((unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
	iCancelAlarm((unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &g_cdvdstm_curclk_ee);
	sceCdSC(0xFFFFFFFF, &g_cdvdstm_last_error_for_ee);
	if ( !g_cdvdstm_last_error_for_ee )
	{
		switch ( sceCdGetDiskType() )
		{
			case SCECdPSCDDA:
			case SCECdPS2CDDA:
			case 0x21:
			case SCECdCDDA:
				break;
			default:
				g_cdvdstm_last_error_for_ee = SCECdErREADCF;
				break;
		}
	}
	g_cdvdstm_curclk_ee.hi = 0;
	if ( g_cdvdstm_stmstart_ee )
		g_cdvdstm_retrycnt_ee_cdda = 0;
	g_cdvdstm_curclk_ee.lo = ( g_cdvdstm_stmstart_ee || g_cdvdstm_last_error_for_ee || g_cdvdstm_retrycnt_ee_cdda ) ? 0x20f58000 : (0x9000 * sceCdSC(0xFFFFFFEF, &g_cdvdstm_last_error_for_ee));
	if ( g_cdvdstm_last_error_for_ee )
	{
		VERBOSE_KPRINTF(1, "EE Stream read LBN= %d Error code= 0x%02x retry= %d\n", g_cdvdstm_readlbn_ee_cdda, g_cdvdstm_last_error_for_ee, g_cdvdstm_retrycnt_ee_cdda);
		if ( g_cdvdstm_last_error_for_ee == SCECdErREAD || g_cdvdstm_last_error_for_ee == SCECdErABRT )
		{
			if ( g_cdvdstm_retrycnt_ee_cdda )
			{
				VERBOSE_KPRINTF(1, "On Retry retry %d err %08x\n", g_cdvdstm_retrycnt_ee_cdda, g_cdvdstm_last_error_for_ee);
			}
			g_cdvdstm_retrycnt_ee_cdda = 4;
		}
		else
		{
			g_cdvdstm_retrycnt_ee_cdda = 1;
		}
		g_cdvdstm_retryerr_ee = g_cdvdstm_last_error_for_ee;
	}
	else
	{
		g_cdvdstm_retrycnt_ee_cdda = 0;
	}
	if ( g_cdvdstm_retrycnt_ee_cdda )
	{
		g_cdvdstm_retrycnt_ee_cdda -= 1;
		if ( !g_cdvdstm_retrycnt_ee_cdda && (g_cdvdstm_last_error_for_ee == SCECdErREAD || g_cdvdstm_last_error_for_ee == SCECdErABRT) )
		{
			g_cdvdstm_readlbn_ee_cdda = g_cdvdstm_lsn_ee + (( g_cdvdstm_sectorcount2 < 0x1D ) ? (0x1D - g_cdvdstm_sectorcount2) : 0);
			g_cdvdstm_lsn_ee = g_cdvdstm_readlbn_ee_cdda + g_cdvdstm_sectorcount2;
		}
		if ( sceCdReadCDDA(
					 g_cdvdstm_readlbn_ee_cdda,
					 g_cdvdstm_sectorcount2,
					 (char *)g_cdvdstm_buffer2 + g_cdvdstm_bankgp_ee * g_cdvdstm_chunksz2,
					 &g_cdvdstm_mode_ee) )
		{
			iSetAlarm(&g_cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
		}
		else
		{
			VERBOSE_KPRINTF(1, "Stm Read Call fail\n");
			g_cdvdstm_curclk_ee.lo = 0x708000;
			if ( iSetAlarm(&g_cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &g_cdvdstm_curclk_ee) && !sceCdNop() )
			{
				sceCdSC(0, &g_cdvdstm_last_error_for_ee);
			}
			g_cdvdstm_retrycnt_ee_cdda += 1;
		}
	}
	else
	{
		if ( !g_cdvdstm_stmstart_ee )
		{
			g_cdvdstm_usedmap_ee[g_cdvdstm_bankgp_ee] = 1;
			gptmp = g_cdvdstm_bankgp_ee;
			g_cdvdstm_bankgp_ee += 1;
			if ( (unsigned int)g_cdvdstm_bankgp_ee >= (unsigned int)g_cdvdstm_bankcnt2 )
				g_cdvdstm_bankgp_ee = 0;
		}
		if ( !g_cdvdstm_stmstart_ee && (g_cdvdstm_usedmap_ee[g_cdvdstm_bankgp_ee] || g_cdvdstm_bankcur_ee == g_cdvdstm_bankgp_ee) )
		{
			g_cdvdstm_bankgp_ee = gptmp;
			g_cdvdstm_usedmap_ee[gptmp] = 0;
			VERBOSE_KPRINTF(1, "read Full %d %d %d %d %d gp %d pp %d spn %d\n", (unsigned __int8)g_cdvdstm_usedmap_ee[0], (unsigned __int8)g_cdvdstm_usedmap_ee[1], (unsigned __int8)g_cdvdstm_usedmap_ee[2], (unsigned __int8)g_cdvdstm_usedmap_ee[3], (unsigned __int8)g_cdvdstm_usedmap_ee[4], g_cdvdstm_bankgp_ee, g_cdvdstm_bankcur_ee, g_cdvdstm_mode_ee.spindlctrl);
			g_cdvdstm_curclk_ee.lo = 0x48000;
			if ( iSetAlarm(
									&g_cdvdstm_curclk_ee,
									(unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda,
									&g_cdvdstm_curclk_ee) != 0 && sceCdNop() == 0 )
			{
				sceCdSC(0, &g_cdvdstm_last_error_for_ee);
			}
		}
		else
		{
			if ( g_cdvdstm_stmstart_ee == 2 )
			{
				unsigned int i; // $v1

				g_cdvdstm_bankoffs_ee = 0;
				g_cdvdstm_bankcur_ee = 0;
				g_cdvdstm_bankgp_ee = 0;
				for ( i = 0; i < (unsigned int)g_cdvdstm_bankcnt2; i += 1 )
					g_cdvdstm_usedmap_ee[i] = 0;
			}
			g_cdvdstm_stmstart_ee = 0;
			g_cdvdstm_readlbn_ee_cdda = g_cdvdstm_lsn_ee;
			if ( sceCdReadCDDA(
						 g_cdvdstm_lsn_ee,
						 g_cdvdstm_sectorcount2,
						 (char *)g_cdvdstm_buffer2 + g_cdvdstm_bankgp_ee * g_cdvdstm_chunksz2,
						 &g_cdvdstm_mode_ee) )
			{
				iSetAlarm(&g_cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))stm_alarm_timeout_cb, &g_cdvdstm_curclk_ee);
			}
			else
			{
				VERBOSE_KPRINTF(1, "Stm Read Call1 fail\n");
				g_cdvdstm_curclk_ee.lo = 0x708000;
				if ( iSetAlarm(&g_cdvdstm_curclk_ee, (unsigned int (__cdecl *)(void *))ee_stream_intr_cb_cdda, &g_cdvdstm_curclk_ee)
					&& !sceCdNop() )
				{
					sceCdSC(0, &g_cdvdstm_last_error_for_ee);
				}
				g_cdvdstm_retrycnt_ee_cdda = 1;
			}
			g_cdvdstm_lsn_ee += g_cdvdstm_sectorcount2;
		}
	}
	return 0;
}
// 404748: using guessed type int g_cdvdstm_chunksz2;
// 40474C: using guessed type int g_cdvdstm_bankcnt2;
// 404758: using guessed type int g_cdvdstm_retryerr_ee;
// 404BE4: using guessed type int g_cdvdstm_bankgp_ee;
// 404BE8: using guessed type int g_cdvdstm_bankcur_ee;
// 404BEC: using guessed type int g_cdvdstm_bankoffs_ee;
// 404BF4: using guessed type int g_cdvdstm_stmstart_ee;

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
