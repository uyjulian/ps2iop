
#include "cdvdman-internal.h"

/* callback used by sceCdSync (internal) */
unsigned int alarm_cb_cdsync(void *param)
{
    DPRINTF(0, "Cdvd Time Out %d(msec)\n", (iop_sys_clock_t *)(param)->low / 0x9000);

    return sceCdBreak() < 1;
}

/* Exported entry #11 */
int sceCdSync(int mode)
{
    u32 resultp;
    iop_sys_clock_t sys_clock;
    iop_event_info_t evfi;

    DPRINTF(1, "sceCdSync: Call mode %d Com %x\n", mode, cdvdman_command);

    switch (mode) {
        case 0:
            for (;;) {
                if (sceCdCheckCmd())
                    if (!cdvdman_read2_flg)
                        break;
                WaitEventFlag(cdvdman_intr_ef, 1, EF_WAIT_AND, &resultp);
            }
            break;
        case 1:
            if (!sceCdCheckCmd())
                return 1;
            if (!cdvdman_read2_flg)
                return 0;
            return 1;
        case 3:
            sys_clock.hi = 0;
            sys_clock.lo = cdvdman_sync_to * 0x9000;
            set_alarm(&sys_clock, alarm_cb_cdsync, &sys_clock);
            for (;;) {
                if (sceCdCheckCmd())
                    if (!cdvdman_read2_flg)
                        break;
                WaitEventFlag(cdvdman_intr_ef, 1, EF_WAIT_AND, &resultp);
            }
            cancel_alarm(alarm_cb_cdsync, &sys_clock);
            break;
        case 4:
            sys_clock.hi = 0;
            sys_clock.lo = 0x41EB0000;
            set_alarm(&sys_clock, alarm_cb_cdsync, &sys_clock);
            for (;;) {
                if (sceCdCheckCmd())
                    if (!cdvdman_read2_flg)
                        break;
                WaitEventFlag(cdvdman_intr_ef, 1, EF_WAIT_AND, &resultp);
            }
            cancel_alarm(alarm_cb_cdsync, &sys_clock);
            break;
        case 5:
            while (!sceCdCheckCmd())
                WaitEventFlag(cdvdman_intr_ef, 1, EF_WAIT_AND, &resultp);
            break;
        case 6: /* Looks very same as case #3 */
            sys_clock.hi = 0;
            sys_clock.lo = cdvdman_sync_to * 0x9000;
            set_alarm(&sys_clock, alarm_cb_cdsync, &sys_clock);
            for (;;) {
                if (sceCdCheckCmd())
                    if (!cdvdman_read2_flg)
                        break;
                WaitEventFlag(cdvdman_intr_ef, 1, EF_WAIT_AND, &resultp);
            }
            cancel_alarm(alarm_cb_cdsync, &sys_clock);
            break;
        case 16:
            for (;;) {
                if (sceCdCheckCmd())
                    if (!cdvdman_read2_flg)
                        if (!cdvdman_ee_ncmd)
                            if (!cdvdman_strm_id)
                                break;
                WaitEventFlag(cdvdman_intr_ef, 1, EF_WAIT_AND, &resultp);
            }
            break;
        case 17:
            if (sceCdCheckCmd())
                if (!cdvdman_read2_flg)
                    if (!cdvdman_ee_ncmd)
                        if (!cdvdman_strm_id)
                            return 0;
            return 1;
        case 32:
            WaitEventFlag(cdvdman_intr_ef, 0x21, EF_WAIT_OR, &resultp);
            ReferEventFlagStatus(cdvdman_intr_ef, &evfi);
            if (evfi.currBits & 0x20)
                break;
            if (cdvdman_cderror)
                SetEventFlag(cdvdman_intr_ef, 0x20);
            else
                WaitEventFlag(cdvdman_intr_ef, 0x20, EF_WAIT_AND, &resultp);
            break;
        default:
            for (;;) {
                if (sceCdCheckCmd())
                    if (!cdvdman_read2_flg)
                        break;
                WaitEventFlag(cdvdman_intr_ef, 1, EF_WAIT_AND, &resultp);
            }
            break;
    }

    DPRINTF(1, "sceCdSync: Command= %d Error= %d\n", cdvdman_command, cdvdman_cderror);

    return 0;
}

/* Exported entry #6 */
int sceCdRead(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode)
{
    int oldstate, rc;
    iop_event_info_t evf_info;

    CpuSuspendIntr(&oldstate);

    refer_ef_status(cdvdman_read_ef, &evf_info);
    if (!(evf_info.currBits & 1)) {
        CpuResumeIntr(oldstate);
        return 0;
    }
    clear_ev_flag(cdvdman_read_ef, 0xFFFFFFFE);

    CpuResumeIntr(oldstate);

    rc = cdvdman_read(lsn, sectors, buf, mode, 0, 0);

    set_ev_flag(cdvdman_read_ef, 0x1);

    return rc;
}

/* Exported entry #40 */
int sceCdReadCDDA(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode)
{
    return cdvdman_readfull(lsn, sectors, buf, mode, 0);
}

/* Exported entry #9 */
int sceCdGetToc(u8 *toc)
{
    return cdvdman_gettoc(toc);
}

/* Exported entry #7 */
int sceCdSeek(u32 lsn)
{
    if (cdvdman_isdvd()) {
        if (!DvdDual_infochk())
            return 0;
        lsn = sceCdLsnDualChg(lsn);
    }

    return cdvdman_send_ncmd(CDVD_NCMD_SEEK, &lsn, 4, SCECdFuncSeek, 0, 1) >= 0;
}

/* Exported entry #5 */
int sceCdStandby()
{
    int type;
    DMA3PARAM b18;
    char ndata[0xB];

    type = CDVDreg_TYPE;

    if ((type < 0x10) || (type >= 0x14))
        return cdvdman_send_ncmd(CDVD_NCMD_STANDBY, 0, 0, SCECdFuncStandby, 0, 1) >= 0;

    ndata[0] = 0x10;
    ndata[4] = 1;
    ndata[9] = 1;
    b18.cdvdreg_howto = 0x80;
    b18.dma3_blkwords = 0x20;
    b18.dma3_blkcount = 0x10;
    ndata[3] = 0;
    ndata[2] = 0;
    ndata[1] = 0;
    ndata[7] = 0;
    ndata[6] = 0;
    ndata[5] = 0;
    ndata[8] = 9;
    ndata[10] = 0;
    b18.dma3_csectors = 0;
    b18.dma3_msectors = 0;
    b18.dma3_callback = 0;
    b18.dma3_maddress = 0;

    return cdvdman_send_ncmd(CDVD_NCMD_READ, &ndata, 0xB, SCECdFuncStandby, &b18, 1) >= 0;
}

/* Exported entry #15 */
int sceCdStop()
{
    return cdvdman_send_ncmd(CDVD_NCMD_STOP, 0, 0, SCECdFuncStop, 0, 1) >= 0;
}

/* Exported entry #38 */
int sceCdPause()
{
    return cdvdman_send_ncmd(CDVD_NCMD_PAUSE, 0, 0, SCECdFuncPause, 0, 1) >= 0;
}

/* Exported entry #13 */
int sceCdDiskReady(int mode)
{
    u32 resultp;
    u32 type;

    DPRINTF(1, "DISK READY call from iop\n");
    if (!mode) {
        DPRINTF(1, "Wait Drive Ready %x\n", CDVDreg_READY);
        type = CDVDreg_TYPE;
        if ((CDVDreg_READY & 0xC0) == 0x40)
            if (!cdvdman_read2_flg)
                if ((type - 1) >= 4)
                    return 2;

        do {
            delay_thread(2000);
            WaitEventFlag(cdvdman_intr_ef, 1, EF_WAIT_AND, &resultp);
            type = CDVDreg_TYPE;
            if ((CDVDreg_READY & 0xC0) != 0x40)
                continue;
            if (cdvdman_read2_flg)
                continue;
        } while ((type - 1) < 4);

        return CdlCdComplete;
    } else if (mode == 8)
        return CDVDreg_READY; /* This mode is not available in modules from BIOS */

    if ((CDVDreg_READY & 0xC0) == 0x40)
        if (!cdvdman_read2_flg)
            return CdlCdComplete;
    DPRINTF(1, "Drive Not Ready\n");
    return SCECdNotReady;
}

/* Exported entry #46 */
int sceCdNop()
{
    return cdvdman_send_ncmd(CDVD_NCMD_NOP, 0, 0, 0, 0, 1) >= 0;
}

/* internal routine */
int cdvdman_readtoc(u8 *toc, int param, int func)
{
    register int v;
    char ndata;
    DMA3PARAM b18;

    v = CDVDreg_TYPE;
    if (v < 0x10)
        return 0;
    if ((v == 0x14) || (v == 0xFE) || (v == 0xFC)) {
        b18.cdvdreg_howto = 0x84;
        b18.dma3_blkwords = 0x04;
        b18.dma3_blkcount = 0x81;
        b18.dma3_maddress = toc;
        b18.dma3_msectors = 0;
        b18.dma3_csectors = 0;
        b18.dma3_callback = 0;
        ndata = param;
    } else {
        if ((v < 0x14) || (v == 0xFD)) {
            b18.cdvdreg_howto = 0x80;
            b18.dma3_blkwords = 0x20;
            b18.dma3_blkcount = 0x08;
            b18.dma3_maddress = toc;
            b18.dma3_msectors = 0;
            b18.dma3_csectors = 0;
            b18.dma3_callback = 0;
            ndata = 0;
        } else
            return 0;
    }

    v = cdvdman_send_ncmd(CDVD_NCMD_GETTOC, &ndata, 1, func, &b18, 1);
    if (v < 0)
        return 0;

    sceCdSync(0);
    if (cdvdman_minver10700)
        if (!sceCdPause())
            return 0; /* sets drive in PAUSE state for new consoles ? */
    sceCdSync(0);

    return 1;
}

/* internal routine */
int cdvdman_gettoc(u8 *toc)
{
    return cdvdman_readtoc(toc, 0, SCECdFuncGetToc);
}

/* Exported entry #19 (avilable in bios and bbnav) */
/* Looks like alternate TOC reading */
#ifdef __CDVDMAN_SW_E19__
int sceCdGetToc2(char *toc, int param)
{
    DMA3PARAM b18;
    char ndata;

    b18.cdvdreg_howto = 0x8C;
    b18.dma3_blkcount = 0x2B;
    b18.dma3_maddress = toc;
    b18.dma3_msectors = 0;
    b18.dma3_csectors = 0;
    b18.dma3_callback = 0;

    ndata = param;

    return cdvdman_send_ncmd(CDVD_NCMD_GETTOC, &ndata, 1, 0, &b18, 1) >= 0;
}
#endif

/* Exported entry #63 */
int sceCdRV(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int arg5, void *cb)
{
#ifndef __CDVDMAN_BIOS__
    DMA3PARAM b18;
    char ndata[0xB];
    u32 resultp;
#endif

    if (CDVDreg_TYPE != 0x14)
        return 0;

#ifndef __CDVDMAN_BIOS__
    if ((cdvdman_mmode != 2) && (cdvdman_mmode != 0))
        return 0;

    if (PollEventFlag(cdvdman_ncmd_ef, 1, EF_WAIT_CLEAR, &resultp) == 0xFFFFFE5B)
        return 0;

    DPRINTF(1, "RV read: sec %d num %d spin %d trycnt %d  addr %08x\n", lsn, sectors, mode->spindlctrl, mode->trycount, buf);

    cdvdman_readbuf = buf;
    cdvdman_dvdflag = cdvdman_isdvd();
    cdvdman_rdmode = *mode;
    cdvdman_rd_lsn = lsn;
    cdvdman_rd_sec = sectors;
    *(u32 *)&ndata[0] = cdvdman_rd_lsn;
    *(u32 *)&ndata[4] = cdvdman_rd_sec;
    ndata[8] = mode->trycount;
    ndata[9] = cdvdman_speedctl(mode->spindlctrl, 1, lsn + sectors);
    ndata[10] = 0;

    if (!arg5)
        b18.dma3_csectors = 0;
    else
        b18.dma3_csectors = (sectors < arg5) ? sectors : arg5;

    cdvdman_rdchunk = b18.dma3_csectors & 0xFFFF;
    b18.cdvdreg_howto = 0x8C; /* reading mode */
    b18.dma3_blkwords = 0xC;
    b18.dma3_msectors = sectors;
    b18.dma3_blkcount = 43 * ((arg5) ? 1 : sectors);
    cdvdman_rd_buf = buf;
    b18.dma3_callback = cb;
    cdvdman_read_cb = cb;
    b18.dma3_maddress = cdvdman_rd_buf;

    if (cdvdman_send_ncmd(CDVD_NCMD_DVDREAD, ndata, 0xB, 0xE, &b18, 0) < 0) {
        set_ev_flag(cdvdman_ncmd_ef, 1);
        return 0;
    } else {
        set_ev_flag(cdvdman_ncmd_ef, 1);
        return 1;
    }
#else
    return sceCdReadDVDV(lsn, sectors, buf, mode);
#endif
}

/* Exported entry #20 (bios & BBNav) */
#ifdef __CDVDMAN_SW_E20__
int sceCdReadDVDV(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode)
{
    DMA3PARAM b18;
    char ndata[0xB];
    register int s;

#ifdef __CDVDMAN_BIOS__
    DPRINTF(1, "DVD read pram set\n");
#endif

    switch (CDVDreg_TYPE) {
        case 0x14: /* SCECdPS2DVD */
        case 0xFC: /* unknown media type */
        case 0xFE: /* SCECdDVDV */
            break;
        default:
            return 0;
    }

    switch (mode->spindlctrl) {
        case 0:
            s = 3;
            break;
        case 2:
            s = 1;
            break;
        case 3:
        case 12:
            s = 4;
            break;
        case 4:
            s = 3;
            break;
        case 10:
            s = 0x40;
            break;
        case 11:
            s = 2;
            break;
        default:
            s = 0x83;
            break;
    }

    *(u32 *)&ndata[0] = lsn;
    *(u32 *)&ndata[4] = sectors;
    ndata[9] = s;
    b18.cdvdreg_howto = 0x8C;
    b18.dma3_blkwords = 0xC;
    b18.dma3_blkcount = 43 * sectors;
    b18.dma3_maddress = buf;
    ndata[10] = 0;
    b18.dma3_msectors = 0;
    b18.dma3_csectors = 0;
    b18.dma3_callback = 0;
    ndata[8] = mode->trycount;

#ifdef __CDVDMAN_BIOS__
    DPRINTF(1, "DVD read command call\n");
#endif

    return cdvdman_send_ncmd(CDVD_NCMD_DVDREAD, &ndata, 0xB, 0x9, &b18, 1) >= 0;
}
#endif

/* internal routine */
int cdvdman_ncmd0Ch(int arg1, u32 arg2, u32 arg3)
{
    char ndata[7];
    register u8 *p;

    if (arg1)
        arg3 = 0;

    ndata[1] = 0 < arg2;
    ndata[0] = arg1;
    ndata[2] = 0 < (arg2 >> 8);
    p = (u8 *)&arg3;
    ndata[3] = p[0];
    ndata[4] = p[1];
    ndata[5] = p[2];
    ndata[6] = p[3];

    return cdvdman_send_ncmd(0xC, ndata, 7, 0, 0, 1) >= 0;
}

/* Exported entry #35 (available in bios & bbnav) */
int sceCdReadKey(unsigned char arg1, unsigned char arg2, unsigned int lsn, unsigned char *key)
{
    register int r38;
#ifndef __CDVDMAN_SW_E35__
    register u32 index;
    sceCdRMode rmode;
    char buffer[2048];
    u32 resultp;

    if (cdvdman_isdvd()) {
        if (!arg1) {
            if (!DvdDual_infochk())
                return 0;
            lsn = sceCdLsnDualChg(lsn);
        }
    }

    rmode.spindlctrl = 0x10;
    rmode.datapattern = 0;
    rmode.trycount = 0;

    sceCdRead0(lsn, 1, buffer, &rmode, 0, 0);
    sceCdSync(3);

    index = 0;

    do {
        register int t;

        if (!cdvdman_ncmd0Ch(arg1, arg2, lsn + index))
            return 0;
        sceCdSync(3);
        t = cdvdman_cderror & 0xFF;
        if (!t)
            break;
        cdvdman_cderror = t;
    } while (++index < 300);

    WaitEventFlag(cdvdman_scmd_ef, 1, EF_WAIT_AND, &resultp);
#else
    if (!cdvdman_ncmd0Ch(arg1, arg2, lsn))
        return 0;

    while (!sceCdCheckCmd()) {
        ;
    }

    DelayThread(2000);
#endif

    r38 = CDVDreg_KEYSTATE;

    if (r38 & 0x1) {
        key[0] = *(volatile u8 *)0xBF402020;
        key[0] ^= CDVDreg_KEYXOR;
        key[1] = *(volatile u8 *)0xBF402021;
        key[1] ^= CDVDreg_KEYXOR;
        key[2] = *(volatile u8 *)0xBF402022;
        key[2] ^= CDVDreg_KEYXOR;
        key[3] = *(volatile u8 *)0xBF402023;
        key[3] ^= CDVDreg_KEYXOR;
        key[4] = *(volatile u8 *)0xBF402024;
        key[4] ^= CDVDreg_KEYXOR;
    } else {
        key[0] = 0;
        key[1] = 0;
        key[2] = 0;
        key[3] = 0;
        key[4] = 0;
    }

    if (r38 & 0x2) {
        key[5] = *(volatile u8 *)0xBF402028;
        key[5] ^= CDVDreg_KEYXOR;
        key[6] = *(volatile u8 *)0xBF402029;
        key[6] ^= CDVDreg_KEYXOR;
        key[7] = *(volatile u8 *)0xBF40202A;
        key[7] ^= CDVDreg_KEYXOR;
        key[8] = *(volatile u8 *)0xBF40202B;
        key[8] ^= CDVDreg_KEYXOR;
        key[9] = *(volatile u8 *)0xBF40202C;
        key[9] ^= CDVDreg_KEYXOR;
    } else {
        key[5] = 0;
        key[6] = 0;
        key[7] = 0;
        key[8] = 0;
        key[9] = 0;
    }

    if (r38 & 0x4) {
        key[10] = *(volatile u8 *)0xBF402030;
        key[10] ^= CDVDreg_KEYXOR;
        key[11] = *(volatile u8 *)0xBF402031;
        key[11] ^= CDVDreg_KEYXOR;
        key[12] = *(volatile u8 *)0xBF402032;
        key[12] ^= CDVDreg_KEYXOR;
        key[13] = *(volatile u8 *)0xBF402033;
        key[13] ^= CDVDreg_KEYXOR;
        key[14] = *(volatile u8 *)0xBF402034;
        key[14] ^= CDVDreg_KEYXOR;
    } else {
        key[10] = 0;
        key[11] = 0;
        key[12] = 0;
        key[13] = 0;
        key[14] = 0;
    }

    key[15] = r38 & 0x7;

#ifndef __CDVDMAN_SW_E35__
    set_ev_flag(cdvdman_scmd_ef, 1);
#endif

    return 1;
}

