
#include "irx_imports.h"
#include "../00common/defs.h"

#include <errno.h>
#include <kerr.h>

IRX_ID("cdvd_st_driver", 2, 2);

extern struct irx_export_table _exp_cdvdstm;

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
unsigned int __fastcall optimized_memcpy(char *dst, const char *src, unsigned int n);
void cdvdstm_1();

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

int g_verbose_level = 0;
int g_cdvdstm_in_deldrv = 0;
int g_cdvdstm_bufmax = 0;
int g_cdvdstm_numbytes = 0;
int g_cdvdstm_bankmax = 0;
void *g_cdvdstm_buffer = NULL;
unsigned int g_cdvdstm_sectorcount = 0;
int g_cdvdstm_last_error_for_iop = 0;
int g_cdvdstm_retryerr_iop = 0;
int g_cdvdstm_retrycnt_iop = 0;
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
iop_device_t g_cdrom_stm_dev = { "cdrom_stm", 0x10000010, 1, "CD-ROM_STM ", &g_cdrom_stm_dev_ops };
int g_cdvdstm_last_error_for_ee = 0;
int g_cdvdstm_bufsz2 = 0;
int g_cdvdstm_chunksz2 = 0;
int g_cdvdstm_bankcnt2 = 0;
void *g_cdvdstm_buffer2 = NULL;
u32 g_cdvdstm_sectorcount2 = 0;
int g_cdvdstm_retryerr_ee = 0;
int g_cdvdstm_retrycnt_ee_normal = 0;
int g_cdvdstm_usedchunksize2 = 0x930;
u32 g_cdvdstm_retrycnt_ee_cdda = 0;
sceCdRMode g_rmode_for_stream0;
int g_cdvdstm_tgt;
int g_cdvdstm_semid;
int g_cdvdman_intr_efid;
char g_cdvdstm_usedmap_iop[512];
unsigned int g_cdvdstm_lsn_iop;
int g_cdvdstm_bankgp_iop;
int g_cdvdstm_bankcur_iop;
int g_cdvdstm_bankoffs_iop;
sceCdRMode g_cdvdstm_mode_iop;
int g_cdvdstm_stmstart_iop;
iop_sys_clock_t g_cdvdstm_curclk_iop;
SifDmaTransfer_t g_cdvdstm_dmat;
int g_cdvdstm_readlbn_ee_normal;
SifDmaTransfer_t g_cdvdstm_dmat2;
u32 g_cdvdstm_readlbn_ee_cdda;
char g_cdvdstm_usedmap_ee[512];
u32 g_cdvdstm_lsn_ee;
int g_cdvdstm_bankgp_ee;
int g_cdvdstm_bankcur_ee;
int g_cdvdstm_bankoffs_ee;
sceCdRMode g_cdvdstm_mode_ee;
int g_cdvdstm_stmstart_ee;
iop_sys_clock_t g_cdvdstm_curclk_ee;

int __fastcall vCancelAlarm(unsigned int (__cdecl *alarm_cb)(void *), void *arg)
{
	return (QueryIntrContext() ? iCancelAlarm : CancelAlarm)(alarm_cb, arg);
}

int vSetEventFlag()
{
	return (QueryIntrContext() ? iSetEventFlag : SetEventFlag)(g_cdvdman_intr_efid, 8);
}

int vClearEventFlag()
{
	return (QueryIntrContext() ? iClearEventFlag : ClearEventFlag)(g_cdvdman_intr_efid, ~8);
}

int cdvdstm_4()
{
	VERBOSE_PRINTF(1, "Dummy Entry Called\n");
	return 0;
}

int cdvdstm_2()
{
	cdrom_stm_devctl_t instruct;
	int outres;

	memset(&instruct, 0, sizeof(instruct));
	instruct.m_cmdid = 3;
	instruct.m_rmode.datapattern = SCECdSecS2048;
	instruct.m_rmode.spindlctrl = SCECdSpinMax;
	instruct.m_rmode.trycount = 0;
	ee_stream_handler_normal(&instruct, 0x14, &outres);
	sceCdStStop();
	return 0;
}

BOOL __fastcall alarm_cb(void *a1)
{
	KPRINTF("Stm Iop Read Time Out %d(msec)\n", *(_DWORD *)a1 / 0x9000);
	return sceCdBreak() == 0;
}

int __fastcall sceCdStream0_inner(unsigned int rdsize, char *addrarg, int modearg, int *error_ptr)
{
	int cur_size;
	unsigned int streamres;
	int last_error;
	u32 efbits;
	int err;

	VERBOSE_KPRINTF(1, "sceCdStream0 call read size= %d mode= %d addr= %08x\n", rdsize, modearg, addrarg);
	cur_size = 0;
	if ( !sceCdSC(0xFFFFFFFF, &last_error) )
		return 0;
	*error_ptr = 0;
	if ( !modearg )
		return iop_stream_handler(0, rdsize, addrarg, 2, &g_rmode_for_stream0, error_ptr);
	vSetEventFlag();
	err = 0;
	streamres = 0;
	while ( (!err || streamres) )
	{
		WaitEventFlag(g_cdvdman_intr_efid, 8, 0, &efbits);
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

int __fastcall sceCdStream0(int rdsize_sectors, char *addrarg, int modearg, int *error_ptr)
{
	return sceCdStream0_inner(rdsize_sectors << 11, addrarg, modearg, error_ptr) / 0x800;
}

unsigned int __fastcall iop_stream_handler(
				unsigned int posszarg1,
				unsigned int posszarg2,
				void *buffer,
				int cmdid,
				const sceCdRMode *rmode,
				int *error_ptr)
{
	int retryflag;
	int bankcur_tmp;
	unsigned int i;
	unsigned int written_chunk_size_tmp;
	int bankcur_next_tmp1;
	int chunk_size;
	int bankcur_next_tmp2;
	int state;

	retryflag = 0;
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
		sceCdSC(0xFFFFFFE9, (int *)&g_cdvdstm_lsn_iop);
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
		optimized_memcpy(
			&((char *)buffer)[i],
			&((char *)g_cdvdstm_buffer)[g_cdvdstm_bankcur_iop * g_cdvdstm_numbytes + g_cdvdstm_bankoffs_iop],
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

unsigned int __cdecl iop_stream_intr_cb(void *userdata)
{
	int gptmp;
	int last_error;
	int scres_unused;

	(void)userdata;

	VERBOSE_KPRINTF(1, "Intr Read call\n");
	iCancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, &g_cdvdstm_curclk_iop);
	iCancelAlarm((unsigned int (__cdecl *)(void *))iop_stream_intr_cb, &g_cdvdstm_curclk_iop);
	sceCdSC(0xFFFFFFFF, &last_error);
	if ( !last_error )
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
				last_error = SCECdErREADCF;
				break;
		}
	}
	g_cdvdstm_curclk_iop.hi = 0;
	if ( g_cdvdstm_stmstart_iop )
		g_cdvdstm_retrycnt_iop = 0;
	if ( g_cdvdstm_stmstart_iop || last_error || g_cdvdstm_retrycnt_iop )
	{
		VERBOSE_KPRINTF(1, "Stm Rtry stmstart:%d err:%02x retry:%d\n", g_cdvdstm_stmstart_iop, last_error, g_cdvdstm_retrycnt_iop);
	}
	g_cdvdstm_curclk_iop.lo = ( g_cdvdstm_stmstart_iop || last_error || g_cdvdstm_retrycnt_iop ) ? 0x20f58000 : (0x9000 * sceCdSC(0xFFFFFFEF, &scres_unused));
	if ( last_error )
	{
		VERBOSE_KPRINTF(1, "IOP Stream read Error code= 0x%02x retry= %d\n", last_error, g_cdvdstm_retrycnt_iop);
		g_cdvdstm_retrycnt_iop = 1;
		if ( last_error == SCECdErREAD || last_error == SCECdErABRT )
		{
			VERBOSE_KPRINTF(1, "On err %08x\n", last_error);
			if ( g_cdvdstm_retrycnt_iop )
				g_cdvdstm_retryerr_iop = last_error;
			g_cdvdstm_retrycnt_iop = 3;
		}
		else
		{
			g_cdvdstm_retryerr_iop = last_error;
		}
	}
	if ( g_cdvdstm_retrycnt_iop )
	{
		unsigned int tgttmp;

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
				sceCdSC(0, &last_error);
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
				sceCdSC(0, &last_error);
			}
		}
		else
		{
			if ( g_cdvdstm_stmstart_iop == 2 )
			{
				unsigned int i;

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
					sceCdSC(0, &last_error);
				}
				g_cdvdstm_retrycnt_iop = 1;
			}
			g_cdvdstm_lsn_iop += g_cdvdstm_sectorcount;
		}
	}
	return 0;
}

int cdrom_stm_init()
{
	iop_sema_t semaparam;

	semaparam.attr = 1;
	semaparam.initial = 1;
	semaparam.max = 1;
	semaparam.option = 0;
	g_cdvdstm_semid = CreateSema(&semaparam);
	return 0;
}

int cdrom_stm_deinit()
{
	SignalSema(g_cdvdstm_semid);
	DeleteSema(g_cdvdstm_semid);
	return 0;
}

int __fastcall cdrom_stm_devctl(iop_file_t *f, const char *a2, int a3, void *inbuf, unsigned int inbuf_len, void *outbuf, unsigned int outbuf_len)
{
	int retres;
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

int __cdecl cdrom_stm_nulldev()
{
	PRINTF("nulldev0 call\n");
	return -EIO;
}

__int64 __cdecl cdrom_stm_nulldev64()
{
	PRINTF("nulldev0 call\n");
	return -EIO;
}

int __fastcall _start(int a1)
{
	int last_error;
	int scres_unused;
	int state;

	if ( a1 < 0 )
	{
		int relres;

		if ( sceCdSC(0xFFFFFFFF, &last_error) == 0 )
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
	g_cdvdman_intr_efid = sceCdSC(0xFFFFFFF5, &scres_unused);
	return 2;
}

BOOL __fastcall stm_alarm_timeout_cb(void *a1)
{
	unsigned int read_to;

	read_to = *(_DWORD *)a1 / 0x9000;
	KPRINTF("Stm EE Read Time Out %d(msec)\n", read_to);
	sceCdSC(0xFFFFFFEE, (int *)&read_to);
	return sceCdBreak() == 0;
}

void __fastcall ee_stream_handler_normal(cdrom_stm_devctl_t *instruct, int inbuf_len, int *outres_ptr)
{
	int retryflag;
	u32 cmdid;
	u32 posszarg2_bytes;
	int bankcur_tmp;
	unsigned int chunks_sectors;
	int bankcur_next_tmp1;
	int posszarg2_bytes_clamped;
	int dmat1;
	int bankcur_next_tmp2;
	int posszarg2_bytes_overrun;
	int outres_tmp2;
	int state;
	unsigned int i;

	(void)inbuf_len;

	retryflag = 0;
	cmdid = instruct->m_cmdid;
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
		sceCdSC(0xFFFFFFE9, (int *)&g_cdvdstm_lsn_ee);
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
		unsigned int posszarg2_bytes_remain;

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

unsigned int __fastcall ee_stream_intr_cb_normal(void *userdata)
{
	int gptmp;
	int scres_unused;

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
	g_cdvdstm_curclk_ee.lo = ( g_cdvdstm_stmstart_ee || g_cdvdstm_last_error_for_ee || g_cdvdstm_retrycnt_ee_normal ) ? 0x20f58000 : (0x9000 * sceCdSC(0xFFFFFFEF, &scres_unused));
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
				unsigned int i;

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

void __fastcall ee_stream_handler_cdda(cdrom_stm_devctl_t *instruct, int inbuf_len, int *outres_ptr)
{
	u32 cmdid;
	u32 posszarg2_bytes;
	int retryflag;
	int bankcur_tmp;
	u32 chunks_sectors;
	int bankcur_next_tmp1;
	int posszarg2_bytes_clamped;
	int dmat2;
	int bankcur_next_tmp2;
	int posszarg2_overrun_chunks2;
	unsigned int posszarg2_bytes_overrun;
	int state;
	unsigned int i;

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
		signed int posszarg2_chunks;

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
			int outres_tmp2;

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
		unsigned int posszarg2_bytes_remain;

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

unsigned int __fastcall ee_stream_intr_cb_cdda(void *userdata)
{
	int gptmp;
	int scres_unused;

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
	g_cdvdstm_curclk_ee.lo = ( g_cdvdstm_stmstart_ee || g_cdvdstm_last_error_for_ee || g_cdvdstm_retrycnt_ee_cdda ) ? 0x20f58000 : (0x9000 * sceCdSC(0xFFFFFFEF, &scres_unused));
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
				unsigned int i;

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

void cdvdstm_1()
{
	;
}
