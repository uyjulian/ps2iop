
#include "cdvdman-internal.h"

/* Exported entry #24 */
int sceCdReadClock(sceCdCLOCK *rtc)
{
    int rc;

    rc = cdvdman_send_scmd(8, 0, 0, rtc, sizeof(sceCdCLOCK), 1);
    rtc->pad = 0;
    rtc->month &= 0x7F;

    if ((rc) && (!rtc->stat)) {
        cdvdman_clock = *rtc;
        cdvdman_clk_flg = 1;
    } else if (!cdvdman_clk_flg) {
        rtc->month = 3;
        rtc->day = 4;
        rtc->hour = 5;
        rtc->minute = 6;
        rtc->year = 0;
        rtc->second = 7;
    } else
        *rtc = cdvdman_clock;

    return rc;
}

/* Exported entry #25 */
int sceCdWriteClock(const sceCdCLOCK *clock)
{
	int dummy;
	return cdvdman_send_scmd(9, &clock->second, 7, &dummy, 1, 1);
}

/* Exported entry #26 */
int sceCdReadNVM(u32 address, u16 *data, u8 *result)
{
	int ret;
	u8 out[3];
	u16 in;

	in = ((address << 8) & 0xFF00) | ((address >> 8) & 0xFF);
	ret = cdvdman_send_scmd(10, &in, 2, out, 3, 1);
	*result = out[0];
	*data = out[2] | (out[1] << 8);
	DPRINTF(0, "ReadNVM call addr= 0x%04x data= 0x%04x stat= 0x%02x\n", address, *data, *result);
	return ret;
}

/* Exported entry #27 */
int sceCdWriteNVM(u32 address, u16 data, u8 *result)
{
	int ret;
	u32 in;

	in = ((address << 8) & 0xFF00) | (address & 0xff) | (data << 24) | ((data << 8) & 0xFF0000);
	ret = cdvdman_send_scmd(11, &in, 4, result, 1, 1);
	DPRINTF(0, "WriteNVM call addr= 0x%04x data= 0x%04x stat= 0x%02x\n", address, data, *result);
	return ret;
}

/* Exported entry #12 */
int sceCdGetDiskType()
{
    return CDVDreg_TYPE;
}

/* Exported entry #183 */
int sceCdGetWakeUpReason(void)
{
    int ret;

    ret = CDVDreg_15;
    if ( ret != -1 )
        ret &= 0xFu;
    return ret;
}

/* Exported entry #8 */
int sceCdGetError()
{
    if (cdvdman_cderror)
        DPRINTF(1, "sceCdGetError: 0x%02x\n", cdvdman_cderror);

    return cdvdman_cderror;
}

/* Exported entry #14 */
int sceCdTrayReq(int param, u32 *traychk)
{
    u8 data[2];

    if (param != SCECdTrayCheck) {
#ifdef __CDVDMAN_NEWBIOS__
        if (cdvdman_nontray)
            if (cdvdman_nontray == 1)
                return 1;
#endif

        data[0] = param;
        cdvdman_iocache = 0;

        if (cdvdman_send_scmd(6, &data[0], 1, &data[1], 1, 1)) {
            if (!data[1]) {
                if ( !param )
                {
                    cdvdman_medium_removal_state = 0;
                }
                delay_thread(11000);
                return 1;
            }
        }

        return 0;
    } else {
        u32 v;

        *traychk = v = cdvdman_mediactl(1);
        DPRINTF(1, "Tray Req test = %d\n", v);
    }

    return 1;
}

/* Exported entry #29 */
int sceCdApplySCmd(u8 cmd, const void *wdata, u16 wdlen, void *rdata)
{
    register int i;

    for (i = 0; i <= 2500; i++) {
        if (cdvdman_send_scmd(cmd & 0xFF, wdata, wdlen, rdata, 0x10, 1)) {
            DelayThread(2000);
            return 1;
        }
        DelayThread(2000);
    }
    DPRINTF(0, "CDVD: set_prev_command TIMEOUT 5(SEC)\n");

    return 0;
}

int cdvdman_traycheck(u8 *p, int *stat)
{
    u8 sdata[4];
    u8 rdata[16];
    register int rcode;

    sdata[0] = 0x30;
    sdata[1] = 0x02;

    rcode = cdvdman_send_scmd(3, sdata, 2, rdata, 2, 1);

    *stat = rdata[0];
    *p = rdata[1];

    return rcode;
}

/* Exported entry #28 */
int sceCdStatus()
{
#ifdef __CDVDMAN_SW_E28__
    return CDVDreg_STATUS; /* bios version */
#else
    u8 trs;
    int result;
    register int stat, type;

    type = CDVDreg_TYPE;
    stat = CDVDreg_STATUS;

    if (type == 0) {
        if (cdvdman_traycheck(&trs, &result) == 1) {
            if (!result) {
                if (trs & 0x08)
                    stat |= 0x01;
                else
                    stat &= 0xFE;
            }
        }
    }

    if (cdvdman_usetoc)
        stat &= 0xFFFFFFFE;

    return (cdvdman_pwr_flg) ? -1 : stat;
#endif
}

/* Exported entry #90 (bbnav only) */
#ifdef __CDVDMAN_SW_E90__
int sceCdStatus2()
{
    return (!cdvdman_pwr_flg) ? (CDVDreg_STATUS & 0xFF) : -1;
}
#endif

/* Exported entry #39 */
int sceCdBreak()
{
    int dummy, oldstate;
    u32 resultp;

    if (PollEventFlag(cdvdman_ncmd_ef, 1, EF_WAIT_CLEAR, &resultp) == 0xFFFFFE5B)
        return 0;

    CpuSuspendIntr(&oldstate);

    DPRINTF(1, "Break call: read2_flag= %d func= %d lsn= %d csec= %d nsec= %d\n", cdvdman_read2_flg, cdvdman_cmdfunc, cdvdman_readlsn, cdvdman_csec, cdvdman_nsec);

    cdvdman_cderror = SCECdErABRT;
    cdvdman_thrd_id = GetThreadId();

    if (cdvdman_decstate) {
        cdvdman_decstate = cdvdman_xorvalue = cdvdman_decshift = 0;
        sceCdDecSet(0, 0, 0);
    }

    cdvdman_recstat = 0;
    break_read_timeout_callback();

    if (!cdvdman_waf) {
        if ((CDVDreg_READY & 0xC0) == 0x40) {
            DPRINTF(1, "cdvd: NonInter END\n");
            cdvdman_waf = 1;
        }
        cdvdman_brkfunc = cdvdman_cmdfunc;
        cdvdman_cmdfunc = SCECdFuncBreak;

        CDVDreg_ABORT = 1;
        DisableIntr(INUM_DMA_3, &dummy);

        DPRINTF(1, "cdvd: Abort command On\n");
    }

    CpuResumeIntr(oldstate);
    set_ev_flag(cdvdman_ncmd_ef, 1);

    return 1;
}

/* internal callback routine */
unsigned int alarm_cb_poff(void *param)
{
#if 0
    ((u32 *)param)[0x84] = 0; /* supposed to be "cdvdman_pwr_flg" variable here */
#endif
	cdvdman_pwr_flg = 0;
    return 0;
}

/* Exported entry #74 */
int sceCdPowerOff(u32 *stat)
{
    u32 dummy;
    int rc;

    *stat = 0;
    DPRINTF(1, "sceCdPowerOff Call\n");

    while (sceCdStatus() & 1) {
        sceCdTrayReq(SCECdTrayClose, &dummy);
        delay_thread(25000);
    }

    rc = cdvdman_send_scmd(0xF, 0, 0, stat, 1, 1);
    if (rc) {
        cdvdman_pwr_flg = 1;
        cdvdman_poff_to.hi = 0;
        cdvdman_poff_to.lo = 0xAFC8000;
        set_alarm(&cdvdman_poff_to, alarm_cb_poff, &cdvdman_command);
    } else
        cdvdman_pwr_flg = 0;

    return rc;
}

/* Exported entry #83 */
int sceCdReadDvdDualInfo(int *on_dual, u32 *layer1_start)
{
    sceCdRMode read_mode;
    *on_dual = 0;
    *layer1_start = 0;
    cdvdman_dlemu = 0;
    if (!cdvdman_emudvd9) {
        if (!DvdDual_infochk())
            return 0;
        *on_dual = cdvdman_dldvd;
        *layer1_start = cdvdman_layer1;
        return 1;
    } else {
        int i;

        if (!cdvdman_isdvd())
            return 1;
        if ((cdvdman_mmode != 2) && (cdvdman_mmode != 0xFF))
            return 0;

        read_mode.trycount = 0;
        read_mode.spindlctrl = 0;
        read_mode.datapattern = 0;

        sceCdRead0(0xE, 1, cdvdman_ptoc, &read_mode, 0, 0);
        if ((!sceCdSync(3)) && (cdvdman_cderror))
        {
            DPRINTF(1, "CDVD: ReadDvdDualInfo Read Error %02x, %d\n", cdvdman_cderror, 0);
            return 0;
        }

        for (i = 0; i < 0x14; i++) {
            if (cdvdman_ptoc[0x68 + i] != cdvdman_masterd[i])
                break;
        }
        if (i != 0x14) {
            if (DvdDual_infochk()) {
                *on_dual = cdvdman_dldvd;
                *layer1_start = cdvdman_layer1;
                return 1;
            } else
                return 0;
        } else {
            if (cdvdman_ptoc[0x83] != 2)
                return 1;
            if (!(cdvdman_ptoc[0x84] & 0x2))
                return 1;
            cdvdman_curdvd = cdvdman_ptoc[0x85];
            cdvdman_elayer = 1 + (cdvdman_ptoc[0x86]) + (cdvdman_ptoc[0x87] << 8) + (cdvdman_ptoc[0x88] << 16) + (cdvdman_ptoc[0x89] << 24);
            cdvdman_dldvd = 0;
            cdvdman_layer1 = cdvdman_elayer;
            cdvdman_dlemu = 1;
            *on_dual = 1;
            *layer1_start = cdvdman_layer1;
            DPRINTF(1, "sceCdReadDvdDualInfo():Cur_Disk %d layer1_start %d\n", cdvdman_elayer, cdvdman_curdvd);
            return 1;
        }
    }
}

/* Exported entry #22 */
int sceCdRI(u8 *buf, u32 *stat)
{
    int r;
    u8 rdata[9];

    r = cdvdman_send_scmd(0x12, 0, 0, rdata, 9, 1);
    *stat = rdata[0];

    /* copy rdata 1-8 to arg1 0-7 */
    *(u32 *)&buf[0] = *(u32 *)&rdata[1];
    *(u32 *)&buf[4] = *(u32 *)&rdata[5];

    return r;
}

/* Exported entry #23 */
int sceCdWI(const u8 *buffer, u32 *result)
{
	int ret; // $s0

	DelayThread(16000);
	*result = 0;
	ret = cdvdman_send_scmd(19, buffer, 8, result, 1, 1);
	DelayThread(16000);
	return ret;
}

/* Exported entry #51 */
int sceCdRC(sceCdCLOCK *rtc)
{
    return cdvdman_send_scmd(8, 0, 0, rtc, sizeof(sceCdCLOCK), 1);
}

/* Exported entry #64 */
int sceCdRM(char *m, u32 *stat)
{
    u8 rdata[9];
    u8 sdata;
    u32 resultp;
    register int rval1, rval2;
    register int rcode;

    *stat = 0;
    rcode = sceCdMV(rdata, stat);
    if ((rcode == 1) && (0x104FF < (rdata[3] | ((u32)rdata[2] << 8) | ((u32)rdata[1] << 16))))
    {
        if (PollEventFlag(cdvdman_scmd_ef, 1, EF_WAIT_CLEAR, &resultp) == 0xFFFFFE5B)
            return 0;
        DelayThread(2000);

        sdata = 0;
        rval1 = cdvdman_send_scmd(0x17, &sdata, 1, rdata, 9, 0);

        *stat = rdata[0];
        *(u32 *)&m[0x0] = *(u32 *)&rdata[0x1];
        *(u32 *)&m[0x4] = *(u32 *)&rdata[0x5];
        DelayThread(2000);

        sdata = 8;
        rval2 = cdvdman_send_scmd(0x17, &sdata, 1, rdata, 9, 0);

        *stat |= rdata[0];
        *(u32 *)&m[0x8] = *(u32 *)&rdata[0x1];
        *(u32 *)&m[0xC] = *(u32 *)&rdata[0x5];

        set_ev_flag(cdvdman_scmd_ef, 1);

        if (!rval1)
            return 0;
        return rval2 > 0;
    }
    else {
        char *unknown = "M_NAME_UNKNOWN\0";

        *(u32 *)&m[0x0] = *(u32 *)&unknown[0x0];
        *(u32 *)&m[0x4] = *(u32 *)&unknown[0x4];
        *(u32 *)&m[0x8] = *(u32 *)&unknown[0x8];
        *(u32 *)&m[0xC] = *(u32 *)&unknown[0xC];
        *stat |= 0x40;

        return 1;
    }
}

/* Exported entry #65 */
int sceCdWM(const char *buffer, u32 *status)
{
	int result;
	int rval1;
	int rval2;
	char wdata[8];
	u8 rdata[9];

	*status = 0;
	if (sceCdMV(rdata, status) == 1 && 0x104FF < (rdata[3] | (rdata[2] << 8) | (rdata[1] << 16)))
	{
		DelayThread(2000);
		rdata[0] = 0;
		memcpy(&rdata[1], buffer, 8);
		rval1 = cdvdman_send_scmd(24, rdata, 9, wdata, 1, 1);
		*status = wdata[0] & 0xff;
		DelayThread(16000);
		rdata[0] = 8;
		memcpy(&rdata[1], &buffer[8], 8);
		rval2 = cdvdman_send_scmd(24, rdata, 9, wdata, 1, 1);
		*status |= wdata[0] & 0xff;
		DelayThread(16000);
		result = 0;
		if ( rval1 )
			result = rval2 != 0;
	}
	else
	{
		result = 1;
		*status |= 0x40u;
	}
	return result;
}

/* Exported entry #43 */
int sceCdMV(u8 *mv, u32 *stat)
{
    u8 sdata[4];
    u8 mvbuf[4];
    register int rcode;

    sdata[0] = 0;
    rcode = cdvdman_send_scmd(3, sdata, 1, mvbuf, 4, 1);
    *stat = mvbuf[0] & 0x80;
    DPRINTF(1, "MV 0x%02x,0x%02x,0x%02x,0x%02x\n", mvbuf[0], mvbuf[1], mvbuf[2], mvbuf[3]);
    mvbuf[0] &= 0x7F;
    *(u32 *)mv = *(u32 *)mvbuf;

    return rcode;
}

/* Exported entry #53 */
int sceCdReadSUBQ(void *buf, u32 *stat)
{
    u8 rdata[16];
    u32 resultp;
    char *bbuf;
    register int rcode;
    register u32 i, c1, d1, e1;

    bbuf = (char *)buf;

    if (PollEventFlag(cdvdman_scmd_ef, 1, EF_WAIT_CLEAR, &resultp) == 0xFFFFFE5B)
        return 0;

    CDVDreg_9 = 0;

    rcode = cdvdman_send_scmd2(2, 0, 0, rdata, 11, 0);

    i = 0;
    *(u32 *)&bbuf[0x0] = *(u32 *)&rdata[0x1];
    *(u32 *)&bbuf[0x4] = *(u32 *)&rdata[0x5];
    bbuf[0x8] = rdata[0x9];
    bbuf[0x9] = rdata[0xA];

    do {
        register int c2, d2, e2;

        e1 = CDVDreg_E;
        d1 = CDVDreg_D;
        c1 = CDVDreg_C;
        e2 = CDVDreg_E;
        d2 = CDVDreg_D;
        c2 = CDVDreg_C;

        if ((c1 == c2) && (d1 == d2) && (e1 == e2))
            break;

        i++;
    } while ((i & 0xFF) < 10);

    if ((i & 0xFF) != 10) {
        bbuf[0x9] = e1;
        bbuf[0x8] = d1;
        bbuf[0x7] = c1;
    }

    *stat = rdata[0];
    set_ev_flag(cdvdman_scmd_ef, 1);

    return rcode;
}

/* Exported entry #55 */
int sceCdAutoAdjustCtrl(int mode, u32 *result)
{
	int in;

	in = mode;
	*result = 0;
	DelayThread(2000);
	DPRINTF(0, "Auto Adjust Ctrl: Set param %d\n", in);
	return cdvdman_send_scmd(22, &in, 1, result, 1, 1);
}

/* Exported entry #52 */
int sceCdForbidDVDP(u32 *stat)
{
    u8 rdata[8];
    u8 sdata[4];
    register int rcode;

    memset(sdata, 0, sizeof(sdata));
    *stat = 0;
    rcode = cdvdman_send_scmd(0x15, sdata, 0, rdata, 1, 1);
    *stat = rdata[0];

    return rcode;
}

/* Exported entry #69 */
int sceCdForbidRead(u32 *stat)
{
    int dummy = 0;

    *stat = 0;
    return cdvdman_send_scmd(0x19, &dummy, 0, stat, 1, 1);
}

/* Exported entry #70 */
int sceCdBootCertify(const u8 *buf)
{
    int dummy;

    DPRINTF(1, "Boot Certify %d %d %d %d\n", buf[0], buf[1], buf[2], buf[3]);

    return cdvdman_send_scmd(0x1A, buf, 4, &dummy, 1, 1);
}

/* Exported entry #73 */
int sceCdCancelPOffRdy(u32 *stat)
{
    int dummy = 0;

    *stat = 0;
    return (cdvdman_minver20400) ? cdvdman_send_scmd(0x1B, &dummy, 0, stat, 1, 1) : 1;
}

/* Exported entry #72 (available in XCDVDMAN & BBNav) */
int sceCdBlueLEDCtl(u8 code, u32 *result)
{
    *result = 0;
    DPRINTF(1, "sceCdBlueLEDCtl\n");

    return cdvdman_send_scmd(0x1B, &code, 1, result, 1, 1);
}

/* Exported entry #45 */
int sceCdCtrlADout(int param, u32 *stat)
{
    *stat = 0;
    DelayThread(2000);

    DPRINTF(1, "Audio Digital Out: Set param %d\n", param);

    return cdvdman_send_scmd(0x14, &param, 1, stat, 1, 1);
}

/* Exported entry #115 (BBNav) */
int sceCdRcBypassCtl(int param, u32 *stat)
{
    *stat = 0;

    if (!cdvdman_minver50000) {
        *stat = 0x100;
        return 1;
    }

    return cdvdman_send_scmd(0x24, &param, 1, stat, 1, 1);
}

/* Exported entry #112 */
int sceCdApplySCmd2(u8 cmd, const void *wdata, unsigned long int wdlen, void *rdata)
{
    register int i;

    for (i = 0; i <= 2500; i++) {
        if (cdvdman_send_scmd2(cmd & 0xFF, wdata, wdlen, rdata, 0x10, 1))
            return 1;
        DelayThread(2000);
    }
    DPRINTF(0, "CDVD: set_prev_command TIMEOUT 5(SEC)\n");

    return 0;
}

/* Exported entry #125 */
int cdvdman_125(int cmd, void *wdata, int wdlen, void *rdata)
{
#ifdef __CDVDMAN_BIOS__
    for (;;) {
        if (cdvdman_send_scmd(cmd & 0xFF, wdata, wdlen, rdata, 0x10, 1))
            break;
        DelayThread(2000);
    }

    DelayThread(2000);

    return 1;
#else
    return 0;
#endif
}

/* Exported entry #41 */
int sceCdReadConsoleID(u8 *id, u32 *stat)
{
    u8 rdata[9];
    u8 sdata[4];
    register int r;

    sdata[0] = 45;

    r = cdvdman_send_scmd(3, sdata, 1, rdata, 9, 0);

    *stat = rdata[0];
    *(u32 *)&id[0x0] = *(u32 *)&rdata[0x1];
    *(u32 *)&id[0x4] = *(u32 *)&rdata[0x5];

    return r;
}

/* Exported entry #42 */
int sceCdWriteConsoleID(const u8 *buffer, u32 *status)
{
	int ret;
	u8 in[9];

	DelayThread(16000);
	*status = 0;
	in[0] = 68;
	memcpy(&in[1], buffer, 8);
	ret = cdvdman_send_scmd(3, &in, 9, status, 1, 1);
	DelayThread(16000);
	return ret;
}

/* Exported entry #30 */
int sceCdSetHDMode(u32 arg)
{
    u8 data[4];

    data[0] = arg;
    if (cdvdman_send_scmd(0xC, &data[0], 1, &data[1], 1, 1))
        return (data[1] == 0);

    return 0;
}

/* Exported entry #81 */
int sceCdSetTimeout(int param, int timeout)
{
    if (!sceCdCheckCmd())
        return 0;
    if (cdvdman_read2_flg)
        return 0;

    switch (param) {
        case 1:
            cdvdman_sync_to = timeout;
            return 1;
        case 2:
            TimeOut2 = timeout;
            return 1;
        default:
            return 0;
    }
}

/* Exported entry #109 */
int sceCdReadWakeUpTime(sceCdCLOCK *clock, u16 *arg2, u32 *arg3, int *arg4)
{
	int res;
	u8 out[10];

	clock->year = 0;
	clock->month = 0;
	clock->day = 0;
	clock->pad = 0;
	clock->hour = 0;
	clock->minute = 0;
	clock->second = 0;
	clock->stat = 0;
	*arg2 = 0;
	*arg3 = 0;
	if ( cdvdman_minver50000 )
	{
		res = cdvdman_send_scmd(34, 0, 0, out, 10, 1);
		if ( res )
		{
			clock->stat = out[0];
			clock->second = out[2] == 255 ? 0xff : out[2] & 0x7F;;
			clock->minute = out[3] & 0x7F;
			clock->pad = 0;
			clock->hour = out[4];
			clock->day = out[5];
			clock->month = out[6];
			clock->year = out[7];
			*arg2 = out[8] | (out[9] << 8);
			*arg3 = out[1] & 0xff;
			*arg4 = 2 * (out[2] >> 7);
			if ( (out[3] & 0x80) != 0 )
				*arg4 |= 1;
		}
	}
	else
	{
		*arg3 = 256;
		res = 1;
	}
	return res;
}

/* Exported entry #110 */
int sceCdWriteWakeUpTime(const sceCdCLOCK *clock, u16 arg2, int arg3)
{
	u32 var5;
	u32 var6;
	u32 dummy;
	u8 in[8];

	if ( !cdvdman_minver50000 )
		return 0;
	var5 = 10 * (clock->month >> 4) + (clock->month & 0xF);
	var6 = 10 * (clock->day >> 4) + (clock->day & 0xF);
	if ( (10 * (clock->second >> 4) + (clock->second & 0xFu) >= 0x3C
			|| 10 * (clock->minute >> 4) + (clock->minute & 0xFu) >= 0x3C
			|| 10 * (clock->hour >> 4) + (clock->hour & 0xFu) >= 0x18
			|| 10 * (clock->year >> 4) + (clock->year & 0xFu) >= 0x64
			|| var5 >= 0xD
			|| !var5
			|| var6 >= 0x20
			|| !var6)
		&& arg3 != 255
		&& (clock->second & 0x80) == 0
		&& (clock->minute & 0x80) == 0 )
	{
		return 0;
	}
	in[0] = clock->second;
	in[1] = clock->minute;
	in[2] = clock->hour;
	in[3] = clock->day;
	in[4] = clock->month;
	in[5] = clock->year;
	memcpy(&in[6], &arg2, 2);
	if (arg3 == 1)
	{
		in[1] |= 0x80;
	}
	else if (arg3 == 255)
	{
		in[0] = -1;
	}
	return cdvdman_send_scmd(33, in, 8, &dummy, 1, 1);
}

/* Exported entry #116 */
int cdvdman_116(u32 *a1, u32 *a2, u32 *a3, u32 *a4)
{
	int result;
	u32 v9;
	u32 v10[5];
	u32 v11 = 0;

	*a4 = 0;
	*a3 = 0;
	*a2 = 0;
	*a1 = 0;
	if ( !cdvdman_minver50000 )
	{
		*a4 = 256;
		return 1;
	}
	result = cdvdman_send_scmd(29, 0, 0, v10, 5, 1);
	if ( result != 1 )
		return result;
	*a4 = v10[0];
	*a1 = v10[1];
	v11 |= v10[2] << 16;
	v11 |= v10[3] << 8;
	v11 |= v10[4] << 0;
	v9 = *a1;
	if ( *a1 == 15 )
	{
		*a2 = (v11 >> 17) & 0x7F;
		*a3 = (u8)(v11 >> 9);
		return 1;
	}
	if ( (u32)*a1 >= 0x10 )
	{
		result = 0;
		if ( v9 != 20 )
			return result;
		*a2 = (v11 >> 17) & 0x7F;
		*a3 = (v11 >> 4) & 0x1FFF;
		return 1;
	}
	result = 0;
	if ( v9 != 12 )
		return result;
	*a2 = (v11 >> 17) & 0x7F;
	*a3 = (v11 >> 12) & 0x1F;
	return 1;
}

/* Exported entry #117 */
int sceRemote2_7(u16 a1, u32 *a2)
{
	int result;
	u16 v3;

	*a2 = 0;
	if ( cdvdman_minver50000 )
	{
		v3 = a1;
		result = cdvdman_send_scmd(31, &v3, 2, a2, 1, 1);
	}
	else
	{
		*a2 = 256;
		result = 1;
	}
	return result;
}

/* Exported entry #120 */
int sceCdSetLEDsMode(u32 arg1, u32 *result)
{
	int ret;
	u8 v3;

	v3 = arg1 & 0xff;
	if ( cdvdman_minver50000 )
	{
		*result = 0;
		ret = cdvdman_send_scmd(37, &v3, 1, result, 1, 1);
	}
	else
	{
		*result = 256;
		ret = 1;
	}
	return ret;
}

/* Exported entry #128 */
int cdvdman_128(u32 *a1, u32 *a2)
{
	int result;
	u8 v5[3];

	*a1 = 0;
	*a2 = 0;
	if ( cdvdman_minver50000 )
	{
		result = cdvdman_send_scmd(38, 0, 0, v5, 3, 1);
		*a1 = ((u8)v5[2] << 8) | (u8)v5[1];
		*a2 = (u8)v5[0];
	}
	else
	{
		*a2 = 256;
		result = 1;
	}
	return result;
}

/* Exported entry #148 */
int sceCdReadPS1BootParam(u8 *out, u32 *result)
{
	int ret;
	u8 outt[13];

	*result = 0;
	memset(out, 0, 11);
	if ( cdvdman_minver50200 )
	{
		ret = cdvdman_send_scmd(39, 0, 0, &outt, 13, 1);
		memcpy(out, &outt[1], 11);
		*result = outt[0];
	}
	else
	{
		*result = 256;
		ret = 1;
	}
	return ret;
}

/* Exported entry #150 */
int sceCdSetFanProfile(u8 arg1, u32 *result)
{
	int ret;
	u8 v4;
	u8 v5;

	*result = 0;
	if ( cdvdman_minver50400 )
	{
		v5 = arg1;
		ret = cdvdman_send_scmd(40, &v5, 1, &v4, 1, 1);
		*result = v4;
	}
	else
	{
		*result = 256;
		ret = 1;
	}
	return ret;
}

/* Exported entry #152 */
int cdvdman_152(u32 *a1, u32 *a2)
{
	int ret;
	u8 v7[3];
	u8 v8;

	*a2 = 0;
	if ( cdvdman_minver50400 )
	{
		v8 = 0xEF;
		ret = cdvdman_send_scmd(3, &v8, 1, v7, 3, 1);
		*a1 = 3125 * (((u8)v7[2] | ((u8)v7[1] << 8)) << 16 >> 18) / 100;
		*a2 = (u8)v7[0];
	}
	else
	{
		ret = 1;
		*a2 = 256;
		*a1 = 0;
	}
	return ret;
}

/* Exported entry #189 */
int sceCdReadRegionParams(u32 *arg1, u32 *result)
{
	int ret;
	u8 out[15];

	*result = 0;
	memset(arg1, 0, 15);
	if ( cdvdman_minver60000 )
	{
		ret = cdvdman_send_scmd(54, 0, 0, &out, 15, 1);
		memcpy(&arg1[0], &out[1], 4);
		memcpy(&arg1[1], &out[5], 4);
		memcpy(&arg1[2], &out[9], 4);
		memcpy(((u8 *)&arg1[3]), &out[13], 1);
		memcpy(((u8 *)&arg1[3]) + 1, &out[14], 1);
		*result = out[0];
	}
	else
	{
		*result = 256;
		ret = 1;
	}
	return ret;
}

/* Exported entry #191 */
int sceCdWriteRegionParams(u8 arg1, u32 *arg2, u8 *arg3, u32 *result)
{
	int ret;
	u32 v9;
	u32 v10;
	u8 v11[16];

	*result = 0;
	memset(v11, 0, sizeof(v11));
	if ( cdvdman_minver60600 )
	{
		v11[0] = arg1;
		v9 = arg2[1];
		v10 = arg2[2];
		*(u32 *)&v11[1] = *arg2;
		*(u32 *)&v11[5] = v9;
		*(u32 *)&v11[9] = v10;
		v9 |= arg3[1] & 0xff;
		v11[13] = *arg3;
		v11[14] = v9;
		ret = cdvdman_send_scmd(62, v11, 15, result, 1, 1);
	}
	else
	{
		*result = 256;
		ret = 1;
	}
	return ret;
}

/* Exported entry #31 */
int sceCdOpenConfig(int block, int mode, int NumBlocks, u32 *status)
{
	int in;

	DelayThread(16000);
	in = (mode & 0xff) | ((block & 0xff) << 8) | ((NumBlocks & 0xff) << 16);
	cdvdman_config_numblocks = NumBlocks;
	*status = 0;
	return cdvdman_send_scmd(64, &in, 3, status, 1, 1);
}

/* Exported entry #32 */
int sceCdCloseConfig(u32 *result)
{
	int ret;

	*result = 0;
	ret = cdvdman_send_scmd(67, 0, 0, result, 1, 1);
	cdvdman_config_numblocks = 0;
	return ret;
}

int read_config_process(void *a1, u32 *a2)
{
	int ret;
	u8 out[16];

	ret = cdvdman_send_scmd(65, 0, 0, out, 16, 1);
	*a2 = (u8)(out[14] + out[13] + out[12] + out[11] + out[10] + out[9] + out[8] + out[7] + out[6] + out[5] + out[4] + out[3] + out[2] + out[0] + out[1]) != out[15];
	memcpy(a1, out, 15);
	return ret;
}

/* Exported entry #33 */
int sceCdReadConfig(void *buffer, u32 *result)
{
	int ret;

	ret = 0;
	if ( cdvdman_config_numblocks <= 0 )
		return ret;
	while ( 1 )
	{
		if ( !read_config_process(buffer, result) )
		{
			DPRINTF(0, "ReadConfig fail Command busy\n");
			return ret;
		}
		if ( *result )
			break;
		++ret;
		buffer = (u8 *)buffer + 15;
		if ( ret >= cdvdman_config_numblocks )
			return ret;
	}
	DPRINTF(0, "ReadConfig fail status: 0x%02x\n", *result);
	return ret;
}

int write_config_process(const u8 *a1, u32 *a2)
{
	char in[16];

	*a2 = 0;
	memcpy(in, a1, 15);
	in[15] = in[14] + in[13] + in[12] + in[11] + in[10] + in[9] + in[8] + in[7] + in[6] + in[5] + in[4] + in[3] + in[2] + in[0] + in[1];
	return cdvdman_send_scmd(66, in, 16, a2, 1, 1);
}

/* Exported entry #34 */
int sceCdWriteConfig(const void *buffer, u32 *result)
{
	int ret;

	ret = 0;
	if ( cdvdman_config_numblocks <= 0 )
		return ret;
	while ( 1 )
	{
		if ( !write_config_process(buffer, result) )
		{
			DPRINTF(0, "WriteConfig fail Command busy\n");
			return ret;
		}
		if ( *result )
			break;
		++ret;
		buffer = (u8 *)buffer + 15;
		if ( ret >= cdvdman_config_numblocks )
			return ret;
	}
	DPRINTF(0, "WriteConfig fail status: 0x%02x\n", *result);
	return ret;
}

int cdvdman_readID(int mode, u8 *buf)
{
    u8 lbuf[16];
    u32 stat;
    int r;

    r = sceCdRI(lbuf, &stat);
    if ((r == 0) || (stat))
        return 0;

    if (mode == 0) { // GUID
        u32 *GUID0 = (u32 *)&buf[0];
        u32 *GUID1 = (u32 *)&buf[4];
        *GUID0 = lbuf[0] | 0x08004600; //Replace the MODEL ID segment with the SCE OUI, to get the console's IEEE1394 EUI-64.
        *GUID1 = *(u32 *)&lbuf[4];
    } else { // ModelID
        u32 *ModelID = (u32 *)&buf[0];
        *ModelID = (*(u32 *)&lbuf[0]) >> 8;
    }

    return 1;
}

/* Exported entry #80 */
int sceCdReadGUID(u64 *GUID)
{
    return cdvdman_readID(0, (u8 *)GUID);
}

/* Exported entry #82 */
int sceCdReadModelID(unsigned long int *ModelID)
{
    return cdvdman_readID(1, (u8 *)ModelID);
}

/* Exported entry #163 */
int sceCdXLEDCtl(u8 arg1, u8 arg2, u32 *result1, u32 *result2)
{
	int ret;
	u8 in[8];
	u8 out[16];

	*result1 = 0;
	ret = 1;
	if ( cdvdman_minver50600 )
	{
		in[0] = arg1;
		in[1] = arg2;
		*result2 = 0;
		ret = cdvdman_send_scmd(0x2Du, in, 2, out, 2, 1);
		if ( ret )
		{
			*result2 = (u8)out[0];
			*result1 = (u8)out[1];
		}
	}
	else
	{
		*result2 = 256;
	}
	return ret;
}

/* Exported entry #165 */
int sceCdBuzzerCtl(u32 *result)
{
	int ret;

	ret = 1;
	if ( cdvdman_minver50600 )
	{
		*result = 0;
		ret = cdvdman_send_scmd(0x2Eu, 0, 0, result, 1, 1);
	}
	else
	{
		*result = 256;
	}
	return ret;
}

/* Exported entry #171 */
int sceCdXBSPowerCtl(u8 arg1, u8 arg2, u32 *result1, u32 *result2)
{
	int v6;
	char in[8];
	char out[16];

	*result1 = 0;
	v6 = 1;
	if ( cdvdman_minver50600 )
	{
		in[0] = arg1;
		in[1] = arg2;
		*result2 = 0;
		v6 = cdvdman_send_scmd(0x2Cu, in, 2, out, 2, 1);
		if ( v6 )
		{
			*result2 = (u8)out[0];
			*result1 = (u8)out[1];
		}
	}
	else
	{
		*result2 = 256;
	}
	return v6;
}

/* Exported entry #181 */
int sceCdXDVRPReset(u8 arg1, u32 *result)
{
	int ret;
	u8 in[8];

	ret = 1;
	if ( cdvdman_minver50600 )
	{
		in[0] = arg1;
		*result = 0;
		ret = cdvdman_send_scmd(0x33u, in, 1, result, 1, 1);
	}
	else
	{
		*result = 256;
	}
	return ret;
}

/* Exported entry #175 */
int sceCdSetMediumRemoval(u8 arg1, u32 *result)
{
    int ret;
    int medium_removal_state_old;
    u8 in[8];
    int state;

    ret = 1;
    if ( cdvdman_minver50600 )
    {
        in[0] = arg1;
        *result = 0;
        CpuSuspendIntr(&state);
        medium_removal_state_old = cdvdman_medium_removal_state;
        cdvdman_medium_removal_state = arg1;
        ret = cdvdman_send_scmd(0x31u, in, 1, result, 1, 1);
        if ( !ret || *result )
            cdvdman_medium_removal_state = medium_removal_state_old;
        CpuResumeIntr(state);
    }
    else
    {
        *result = 256;
    }
    return ret;
}

/* Exported entry #177 */
int sceCdGetMediumRemoval(u32 *result1, u32 *result2)
{
    int ret;
    char out[16];

    *result1 = 0;
    ret = 1;
    if ( cdvdman_minver50600 )
    {
        *result2 = 0;
        ret = cdvdman_send_scmd(0x32u, 0, 0, out, 2, 1);
        if ( !ret )
            return ret;
        *result2 = (u8)out[0];
        *result1 = (u8)out[1];
    }
    else
    {
        *result2 = 256;
    }
    if ( ret && !*result2 )
        cdvdman_medium_removal_state = *result1;
    return ret;
}

/* Exported entry #156 */
int sceCdNoticeGameStart(u8 arg1, u32 *result)
{
    int res;
    char out[8];
    u8 in[8];

    *result = 0;
    if ( cdvdman_minver50400 )
    {
        in[0] = arg1;
        res = cdvdman_send_scmd(0x29u, in, 1, out, 1, 1);
        *result = (u8)out[0];
    }
    else
    {
        *result = 256;
        res = 1;
    }
    if ( res && !*result )
        cdvdman_medium_removal_state = 0;
    return res;
}
