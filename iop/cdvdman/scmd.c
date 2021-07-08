
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

/* Exported entry #12 */
int sceCdGetDiskType()
{
    return CDVDreg_TYPE;
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
    return (cdvdman_scmd1Bh) ? cdvdman_send_scmd(0x1B, &dummy, 0, stat, 1, 1) : 1;
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

    if (!cdvdman_scmd24h) {
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
