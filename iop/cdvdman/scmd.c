
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

/* Exported entry #39 */
int sceCdBreak()
{
    int dummy, oldstate;
    u32 resultp;

    if (PollEventFlag(cdvdman_ncmd_ef, 1, WEF_CLEAR, &resultp) == 0xFFFFFE5B)
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
        DisableIntr(IOP_IRQ_DMA_CDVD, &dummy);

        DPRINTF(1, "cdvd: Abort command On\n");
    }

    CpuResumeIntr(oldstate);
    set_ev_flag(cdvdman_ncmd_ef, 1);

    return 1;
}

/* internal callback routine */
unsigned int alarm_cb_poff(void *param)
{
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

    if (PollEventFlag(cdvdman_scmd_ef, 1, WEF_CLEAR, &resultp) == 0xFFFFFE5B)
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

/* Exported entry #73 */
int sceCdCancelPOffRdy(u32 *stat)
{
    int dummy = 0;

    *stat = 0;
    return (cdvdman_minver20400) ? cdvdman_send_scmd(0x1B, &dummy, 0, stat, 1, 1) : 1;
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
