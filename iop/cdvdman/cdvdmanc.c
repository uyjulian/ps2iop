/* cdvdman CODE */

#include "cdvdman-internal.h"

IRX_ID("cdvd_driver", 1, 0);

// Missing entries: 23, 25, 31-34, 42, 55, 65, 79-80, 82

/* Entry point */
int _start(int argc, char **argv)
{
    if (RegisterLibraryEntries(&_exp_cdvdman))
        return 1;

    DelDrv(cdvdman_cdrom);
    if (AddDrv(&cdvdman_cddev)) {
        cdrom_deinit(&cdvdman_cddev);
        return 1;
    }

    cdvdman_ptoc = toc_buffer;
    cdvdman_pb_fsvr = cdvdman_fsvrbuf;

    cdvdman_init();

#if 0
    SetRebootTimeLibraryHandlingMode(&_exp_cdvdman, 2);
#endif

    return 0;
}

/* Exported entry #47 (used by cdvdfsv module) */
void *sceGetFsvRbuf()
{
    return cdvdman_fsvrbuf;
}

/* Exported entry #3 */
void cdvdman_termcall(int arg)
{
    int i = 0, dummy;

    DPRINTF(1, "CDVD:library Terminate Call %d\n", arg);
    if (!arg) {
        if (CDVDreg_SDATAIN & 0x80) {
            while (i < 50000) {
                DelayThread(100);
                if (!(CDVDreg_SDATAIN & 0x80))
                    break;
                i++;
            }
        }

        sceCdBreak();
        sceCdSync(0);
        sceCdDecSet(0, 0, 0);

        if (dmac_ch_get_chcr(3) & DMAf_TR)
            CDVDreg_ABORT = 1;
        dmac_ch_set_chcr(3, 0);

        DisableIntr(INUM_DMA_3, &dummy);
        ReleaseIntrHandler(INUM_DMA_3);
        DisableIntr(INUM_CDROM, &dummy);
        ReleaseIntrHandler(INUM_CDROM);
    }
}

/* internal routine */
int cdvdman_initcfg()
{
    u32 eflag = 0;
    u8 mv[4];
    register int count = 0;
    register int rcode;

    for (;; count++) {
        rcode = sceCdMV(mv, &eflag);
        if ((!rcode) && (eflag & 0x80)) {
            if (count <= 100) {
                delay_thread(2000);
                DPRINTF(1, "sceCdMV error\n");
                continue;
            } else
                return 0;
        }

        break;
    }

    count = mv[3] | ((u32)mv[2] << 8) | ((u32)mv[1] << 16);

    /* when CDVDMAN runs on special console the dual-layer dvd emulation will be enabled */
    cdvdman_emudvd9 = mv[2] & 1;

    DPRINTF(1, "MV %02x %02x %02x %02x\n", mv[0], mv[1], mv[2], mv[3]);

    cdvdman_newmeca = (0x106FF < (u32)count) ? 1 : 0;
    cdvdman_nomode0 = (0x201FF < (u32)count) ? 1 : 0;
    cdvdman_scmd1Bh = (0x203FF < (u32)count) ? 1 : 0;
    cdvdman_ncmd0Eh = (0x207FF < (u32)count) ? 1 : 0;
    cdvdman_scmd21h = (0x30600 < (u32)count) ? 1 : 0; /* BBNAV */
    cdvdman_scmd24h = (0x4FFFF < (u32)count) ? 1 : 0; /* BBNAV */
#ifdef __CDVDMAN_NEWBIOS__
    cdvdman_scmd27h = (0x501FF < (u32)count) ? 1 : 0; /* slim PS2 BIOS */
    if (0x501FF < (u32)count) {
        u32 t;

        /* ??? = 0; */
        t = (u32)count & 0xF;
        t ^= 1;
        cdvdman_nontray = (t < 1) ? 1 : 0;
    }
    /* else ??? = 0; */
    cdvdman_scmd28h = (0x503FF < (u32)count) ? 1 : 0; /* slim PS2 BIOS */
#endif

#if 0
    // guards cdvdman_189
    cdvdman_scmd36h = (0x5FFFF < (u32)count) ? 1 : 0; /* slim PS2 BIOS */
#endif

    return 1;
}

/* internal callback routine */
unsigned int alarm_cb_read(void *param)
{
    int rdto;

    rdto = ((iop_sys_clock_t *)(param))->lo / 0x9000;
    DPRINTF(0, "Read Time Out %d(msec)\n", rdto);
    sceCdSC(0xFFFFFFEE, &rdto);

    return (sceCdBreak() == 0);
}

void break_read_timeout_callback(void)
{
    if (QueryIntrContext()) {
        iSetEventFlag(cdvdman_intr_ef, 0x29);
        iCancelAlarm(alarm_cb_read, &cdvdman_racb_to);
    } else {
        SetEventFlag(cdvdman_intr_ef, 0x29);
        CancelAlarm(alarm_cb_read, &cdvdman_racb_to);
    }
}

/* Exported entry #37 */
sceCdCBFunc sceCdCallback(sceCdCBFunc func)
{
    u32 resultp;
    sceCdCBFunc rc;

    if (sceCdSync(1))
        return 0;

    if (PollEventFlag(cdvdman_ncmd_ef, 1, EF_WAIT_CLEAR, &resultp) == 0xFFFFFE5B)
        return 0;
    rc = cdvdman_user_cb;
    cdvdman_user_cb = func;
    set_ev_flag(cdvdman_ncmd_ef, 1);

    return rc;
}

/* Exported entry #78 */
void *sceCdPOffCallback(void (*func)(void *), void *addr)
{
    int oldstate;
    void *old_cb;

    CpuSuspendIntr(&oldstate);

    old_cb = cdvdman_poff_cb;
    cdvdman_poff_cb = func;
    cdvdman_poffarg = addr;

    CpuResumeIntr(oldstate);

    return old_cb;
}

/* Exported entry #48 */
int sceCdstm0Cb(void (*p)(int))
{
    cdvdman_cdstm0cb = p;
    return 0;
}

/* Exported entry #49 */
int sceCdstm1Cb(void (*p)(int))
{
    cdvdman_cdstm1cb = p;
    return 0;
}

/* internal routine */
int cdvdman_intr_cb(void *common)
{
    sceCdRMode cdrmode;
    int oldstate;
    register int s1;
    register int err, rs;

    iSetEventFlag(cdvdman_intr_ef, 0x29);
    DisableIntr(INUM_DMA_3, &oldstate);

    if (cdvdman_cderror == SCECdErEOM)
        cdvdman_cderror = 0;

    DPRINTF(1, "Intr call func_num: %d Err= %02x OnTout= %d\n", cdvdman_cmdfunc, cdvdman_cderror, cdvdman_read_to);

    if (!cdvdman_scmd_flg)
        cdvdman_write_scmd(common);

    err = cdvdman_cderror;

    if (
        (
        ((err == SCECdErREAD) && (cdvdman_cmdfunc == SCECdFuncRead)) ||
        (
            (err == SCECdErABRT) &&
            (cdvdman_read_to) &&
            (cdvdman_brkfunc == err)
        )) &&
        (
            (!cdvdman_nomode0) &&
            (!cdvdman_strm_id) &&
            (!cdvdman_dvdflag) &&
            (!cdvdman_recstat) &&
            ((cdvdman_rdmode.trycount) != 1)
        )
        ) {
        cdvdman_syncerr = 0;

        if (!cdvdman_unk2) {
            register u32 rty_sec, t;

            DPRINTF(1, "dec mode 0x00\n");

            t = cdvdman_rdchunk ? cdvdman_rdchunk : cdvdman_rd_sec;
            t = 0x20 / t;
            cdvdman_unk1 = t;
            if (t)
                t += 1;
            else
                t = 1;
            cdvdman_unk1 = t;

            t = cdvdman_rd_lsn;
            if (t < 0x61) {
                t += cdvdman_rd_sec;
                t += 0x30;
            } else
                t += 0xFFFFFFB0;

            cdvdman_dintrlsn = t;
            rty_sec = cdvdman_rdchunk ? cdvdman_rdchunk : cdvdman_rd_sec;
            ((sceCdRMode *)&cdvdman_rdmode)->spindlctrl = 0x10;
            if (sceCdRead0_Rty(cdvdman_dintrlsn, rty_sec,
                               cdvdman_rd_buf,
                               (sceCdRMode *)&cdvdman_rdmode,
                               cdvdman_command, 0, 0)) {
            lab3:

                t = cdvdman_unk1;
                cdvdman_cderror = 0;
                cdvdman_dintrlsn += cdvdman_rd_sec;
                cdvdman_unk1 = --t;

                cdvdman_recstat = (!t) ? 2 : 1;
                return 1;
            }

            cdvdman_cderror = SCECdErREAD;
            cdvdman_recstat = 0;
        } else
            cdvdman_unk3 = 1;
    }

    DPRINTF(1, "Recover_Stat:%d\n", cdvdman_recstat);

    s1 = CDVDreg_13 & 0xF;

    if (!s1)
        goto lab2;
    err = cdvdman_cderror;
    if ((err != SCECdErREAD) && ((err == SCECdErABRT) || (!cdvdman_read_to))) goto lab2;
    if ((cdvdman_recstat) || (cdvdman_strm_id) || (cdvdman_cmdfunc == 9) || (cdvdman_cmdfunc == SCECdFuncReadCDDA))
        goto lab2;

    /* && ((err == SCECdErREAD) || ((err == SCECdErABRT) && (cdvdman_read_to))) && */
    /* (!cdvdman_recstat) && (!cdvdman_strm_id) && (cdvdman_cmdfunc == 9) && (cdvdman_cmdfunc != SCECdFuncReadCDDA) && */
    if (((u32)((sceCdRMode *)&cdvdman_rdmode)->trycount - 1) >= 4) {
        cdvdman_syncerr = 0;

        if (!cdvdman_unk2) {
            DPRINTF(1, "dec mode 0x01\n");

            cdrmode.trycount = ((sceCdRMode *)&cdvdman_rdmode)->trycount;
            cdrmode.spindlctrl = s1 + 0xD;
            cdrmode.datapattern = ((sceCdRMode *)&cdvdman_rdmode)->datapattern;

            if (sceCdRead0_Rty(cdvdman_rd_lsn, cdvdman_rd_sec, cdvdman_rd_buf, &cdrmode, cdvdman_command, cdvdman_rdchunk, cdvdman_read_cb)) {
                cdvdman_cderror = 0;
                return 1;
            }

            cdvdman_cderror = SCECdErREAD;
        } else
            cdvdman_unk3 = 2;
    }

lab2:

    rs = cdvdman_recstat;
    cdvdman_read_to = 0;

    if (rs == 2) {
        cdvdman_syncerr = 0;

        if (sceCdRead0(cdvdman_rd_lsn, cdvdman_rd_sec, cdvdman_rd_buf, (sceCdRMode *)&cdvdman_rdmode, cdvdman_rdchunk, cdvdman_read_cb)) {
            cdvdman_cderror = 0;
            cdvdman_recstat = 3;
            return 1;
        }
        cdvdman_cderror = SCECdErREAD;
        cdvdman_recstat = 0;
    } else if (rs == 1) {
        register u32 rty_sec;

        cdvdman_syncerr = 0;

        rty_sec = (cdvdman_rdchunk != 0) ? cdvdman_rdchunk : cdvdman_rd_sec;

        if (!cdvdman_cderror) {
            if (sceCdRead0_Rty(cdvdman_dintrlsn, rty_sec, cdvdman_rd_buf, (sceCdRMode *)&cdvdman_rdmode, cdvdman_command, 0, 0))
                goto lab3;
        }

        cdvdman_cderror = SCECdErREAD;
        cdvdman_recstat = 0;
    } else if (rs == 3)
        cdvdman_recstat = 0;

    if (cdvdman_decstate)
        sceCdDecSet(0, 0, 0);

    rs = cdvdman_read2_flg;
    if (((rs == 1) || (rs == 3)) && (!cdvdman_usetoc)) {
        DPRINTF(1, "call Read2intrCDVD()\n");
        Read2intrCDVD(cdvdman_read2_flg);
    }

    cdvdman_syncerr = 0;
    if (cdvdman_decstate != 2)
        cdvdman_decstate = 0;

    if ((cdvdman_strm_id == 1) && (!cdvdman_usetoc) && (!cdvdman_read2_flg)) {
        if (cdvdman_cdstm0cb == 0) {
            DPRINTF(1, "Intr func0 no seting");
        } else
            cdvdman_cdstm0cb(1);
    }

    if ((cdvdman_strm_id == 2) && (!cdvdman_usetoc) && (!cdvdman_read2_flg)) {
        if (cdvdman_cdstm1cb == 0) {
            DPRINTF(1, "Intr func1 no seting");
        } else
            cdvdman_cdstm1cb(1);
    }

    if (cdvdman_read2_flg)
        cdvdman_readptr = 0;

    DPRINTF(1, "Intr call user callback func_addr %08x num %d flg %d\n", cdvdman_user_cb, cdvdman_cmdfunc, cdvdman_read2_flg);

    if (cdvdman_user_cb) {
        if ((cdvdman_cmdfunc) && (!cdvdman_read2_flg) && (!cdvdman_usetoc)) {
            register int func;

            func = cdvdman_cmdfunc;
            cdvdman_cmdfunc = 0;
            if ((func == 0xE) || (func == 0x9))
                func = SCECdFuncRead;
            cdvdman_user_cb(func);
        }

        if (cdvdman_user_cb)
            return 1;
    }

    cdvdman_cmdfunc = 0;

    return 1;
}

/* CDROM IRQ handler (internal) */
/* pretty messy code */
int intrh_cdrom(void *common)
{
    int cdvd_error, ready = 0;
    iop_event_info_t efi;

    cdvdman_cderror = cdvd_error = CDVDreg_ERROR;
    cdvdman_waf2 = cdvdman_waf;
    cdvdman_cderror = cdvd_error;

    if (CDVDreg_PWOFF & CdlDataReady) {
        cdvdman_waf2 = (CDVDreg_READY & CdlDataReady) ? -1 : 1;
        CDVDreg_PWOFF = CdlDataReady;
        ready = 1;
    }

    if (CDVDreg_PWOFF & CdlDataEnd) {
        CDVDreg_PWOFF = CdlDataEnd;
        iSetEventFlag(cdvdman_intr_ef, 0x4);
        iSetEventFlag(cdvdman_intr_ef, 0x10);
        if (cdvdman_poff_cb)
            cdvdman_poff_cb(cdvdman_poffarg);
        if (!ready)
            return 1;
    } else {
        cdvdman_waf2 = 1;
        cdvdman_unused2++; /* common + 0x3 */
        cdvdman_unused2++; /* common + 0x3 */
        CDVDreg_PWOFF = CdlCdComplete;
    }

    iReferEventFlagStatus(cdvdman_intr_ef, &efi);
    if ((efi.currBits & 0x20) || (cdvdman_cderror))
        return cdvdman_intr_cb(common);
    else
        cdvdman_dr_flg = 1;

    return 1;
}

u32 cdvdman_l1start(u8 *toc)
{
    return toc[0x17] + (toc[0x16] << 8) + (toc[0x15] << 16) - 0x30000 + 1;
}

/* internal routine */
int DvdDual_infochk()
{
    if (QueryIntrContext())
        return 1;

    if (!cdvdman_mediactl(4)) {
        if (cdvdman_dldvd != 0xFF)
            return 1;
    }

    cdvdman_usetoc = 1;
    if (!cdvdman_gettoc(cdvdman_ptoc)) {
        cdvdman_usetoc = 0;
        cdvdman_dldvd = 0xFF;
        return 0;
    }

    cdvdman_usetoc = 0;
    cdvdman_layer1 = cdvdman_l1start(cdvdman_ptoc);

    /* Dual Layer & PTP/OTP detection */
    if (((u8 *)cdvdman_ptoc)[0xE] & 0x60) {
        cdvdman_dldvd = (cdvdman_ptoc[0xE] & 0x10) ? 2 : 1;
    } else
        cdvdman_dldvd = 0;

    if (cdvdman_dlemu) {
        DPRINTF(1, "CDVD:DualEmuON\n");
        cdvdman_layer1 = cdvdman_elayer;
        cdvdman_dldvd = 0;
    }

    DPRINTF(1, "DvdDual_info: %02x  Layer1_LSN:%d opo_or_para %d\n", cdvdman_ptoc[0xE], cdvdman_layer1, cdvdman_dldvd);

    return 1;
}

/* Translates "lsn" for DVD9 emulation (internal) */
u32 sceCdLsnDualChg(u32 lsn)
{
    register u32 newlsn;

    newlsn = lsn;

    if (!cdvdman_isdvd())
        return newlsn;
    if (!DvdDual_infochk())
        return newlsn;

    if (cdvdman_dlemu) {
        // TODO: implement dual layer emulation by using two physical discs
    } else {
        if ((cdvdman_dldvd) && (lsn >= cdvdman_layer1))
            newlsn -= 0x10;
    }

    DPRINTF(1, "CDVD: sceCdLsnDualChg lsn %d: change lsn %d\n", lsn, newlsn);

    return newlsn;
}

/* Exported entry #50 */
/* Used by cdvdfsv & cdvdstm */
int sceCdSC(int code, int *param)
{
    switch (code) {
        case 0xFFFFFFE6:
            *param = (int)cdvdman_poff_cb;
            return (int)cdvdman_poffarg;
        case 0xFFFFFFE7:
            return cdvdman_scmd_ef; /* Used by cdvdfsv */
        /* case 0xFFFFFFE8 should return cdvdman_xorvalue (apparently) but hadn't been found */
        case 0xFFFFFFE9:
            return sceCdLsnDualChg(*param); /* Used by cdvdfsv */
        case 0xFFFFFFEA:
            return DvdDual_infochk(); /* Used by cdvdfsv */
        case 0xFFFFFFEE:
            cdvdman_read_to = *param; /* Used by cdvdfsv */
            return 0;
        case 0xFFFFFFEF:
            return TimeOut2;
        case 0xFFFFFFF0:
            *param = (int)&cdvdman_verbose;
            return 0xFF;
        case 0xFFFFFFF1:
            return cdvdman_sync_to;
        case 0xFFFFFFF2:
            *param = (int)&cdvdman_command; /* Returns address of internal data structure (for CDVDFSV) */
            return 0xFF;
        case 0xFFFFFFF3: {
            char *bm;
            bm = (char *)QueryBootMode(4);
            if (!bm)
                return 1;
            if (*bm < 0)
                return 1;
            if (*bm < 3)
                cdvdman_mmode = 0xFF;
            else if (*bm == 3)
                cdvdman_mmode = 0;
            return 1;
        }
        case 0xFFFFFFF4: {
            int type;

            type = CDVDreg_TYPE;
            if ((type < 0x10) || (type > 0x14))
                return 0;

            if ((cdvdman_mmode != ((type == 0x14) ? 2 : 1)) && (cdvdman_mmode != 0xFF))
                return 0;

            return 1;
        }
        case 0xFFFFFFF5:
            return cdvdman_intr_ef; /* used by cdvdfsv&cdvdstm */
        case 0xFFFFFFF6: {
            register int ee_ncmd;

            if (*param) /* Used by cdvdfsv */
            {
                u32 resultp;
                WaitEventFlag(cdvdman_read_ef, 1, EF_WAIT_CLEAR, &resultp);
            } else
                SetEventFlag(cdvdman_read_ef, 1);

            ee_ncmd = *param;
            cdvdman_ee_ncmd = ee_ncmd;

            DPRINTF(2, "EE_ncmd_working code= %d\n", ee_ncmd);

            return cdvdman_ee_ncmd;
        }
        case 0xFFFFFFF7:
            return _irx_id.v; /* Used by cdvdfsv */
        case 0xFFFFFFF8:
            cdvdman_spinctl = *param;
            return 1;
        case 0xFFFFFFFC:
            return cdvdman_cd36key; /* used by cdvdfsv */
        case 0xFFFFFFFD:
            return cdvdman_read2_flg; /* Used by cdvdfsv */
        case 0xFFFFFFFE:
            return cdvdman_cderror = *param;
        default:
            *param = cdvdman_cderror;
            if (code != 0xFFFFFFFF) /* cdvdman_strm_id is used by cdvdstm modules as strean ID. It's an active stream flag also. */
            {
                cdvdman_strm_id = code;
            }

            return cdvdman_strm_id;
    }
}

/* internal routine */
void cdvdman_init()
{
    int dummy;
    u32 stat;
    register int r, t;
    register u16 *p;

    cdvdman_user_cb = 0;
    cdvdman_poff_cb = 0;
    cdvdman_cmdfunc = 0;
    cdvdman_dr_flg = 0;

    RegisterIntrHandler(INUM_CDROM, HTYPE_C, intrh_cdrom, &cdvdman_command);
    RegisterIntrHandler(INUM_DMA_3, HTYPE_C, intrh_dma_3, &cdvdman_command);

    EnableIntr(INUM_CDROM);

    sceCdSC(0xFFFFFFF3, &dummy);

    t = dmac_get_dpcr() | 0x8000;
    dmac_set_dpcr(t);
    dmac_ch_set_chcr(3, 0);

    if (CDVDreg_PWOFF & CdlDataEnd)
        CDVDreg_PWOFF = CdlDataEnd;
    if (CDVDreg_PWOFF & CdlDataReady)
        CDVDreg_PWOFF = CdlDataReady;

    r = 0;
    if (sceCdReadClock(&cdvdman_clock))
        r = (cdvdman_clock.stat < 1) ? 1 : 0;
    cdvdman_clk_flg = r;

    cdvdman_initcfg();

    p = (u16 *)QueryBootMode(6);
    cdvdman_nodecflg = (p != 0) ? (((*p & 0xFFFC) ^ 0x60) < 1) : 0;

    /* 
   Is it a bug in the SCE's code ? It seems the variable "t" (register "$s1") 
   had not been initialized before the begining of the following cycle.
  */

    do {
        r = sceCdCancelPOffRdy(&stat);
        if ((!r) || (stat))
            DelayThread(16000);
    } while ((++t < 0x3D) && ((!r) || (stat)));
}

/* Exported entry #4 */
int sceCdInit(int init_mode)
{
    int dummy, ready, state;

    DPRINTF(1, "sceCdInit called mode= %d\n", init_mode);

    if ((init_mode < 0) || (init_mode < 2) || (init_mode != SCECdEXIT)) {
        DPRINTF(1, "Cdvdman Init\n");
        cdvdman_read2_flg = 0;
        cdvdman_decstate = cdvdman_xorvalue = cdvdman_decshift = 0;
        sceCdDecSet(0, 0, 0);
        cdvdman_init();
    } else {
        sceCdSync(0);
        DPRINTF(1, "Cdvdman Exit\n");
        DisableIntr(INUM_CDROM, &dummy);
        ReleaseIntrHandler(INUM_CDROM);
        DisableIntr(INUM_DMA_3, &dummy);
        ReleaseIntrHandler(INUM_DMA_3);
    }

    if (init_mode == SCECdINIT) {
        DPRINTF(1, "sceCdInit Ready check start.\n");
        state = 0;

        do {
            ready = CDVDreg_READY;
            delay_thread(10000);
            if (state != ready) {
                state = ready;
                DPRINTF(1, "sceCdInit Dev5 Status %x\n", ready);
            }
        } while ((ready & 0xC0) != 0x40);

        DPRINTF(1, "sceCdInit Ready check end.\n");
    }

    cdvdman_waf = 1;
    cdvdman_scmd_flg = 1;
    cdvdman_cderror = SCECdErNO;
    cdvdman_read_to = 0;
    cdvdman_spinctl = -1;
    SetEventFlag(cdvdman_intr_ef, 0x29);
    SetEventFlag(cdvdman_ncmd_ef, 1);
    SetEventFlag(cdvdman_scmd_ef, 1);
    SetEventFlag(cdvdman_srch_ef, 1);

    return 1;
}

/* internal routine */
int cdvdman_send_scmd(int cmd, const void *sdata, int sdlen, void *rdata, int rdlen, int check_sef)
{
    u32 resultp;
    int i, j;

    if (check_sef == 1)
        if (PollEventFlag(cdvdman_scmd_ef, 1, EF_WAIT_CLEAR, &resultp) == 0xFFFFFE5B)
            return 0;

    i = 0;
    cdvdman_scmd = cmd;
    cdvdman_sdlen = sdlen;
    cdvdman_rdlen = rdlen;

    for (; i < sdlen; i++)
        cdvdman_scmd_sd[i] = ((char *)sdata)[i];

    if (!cdvdman_waf) {
        if (QueryIntrContext()) {
            for (;;) {
                if (!(dmac_ch_get_chcr(3) & DMAf_TR))
                    break;
                if (cdvdman_waf)
                    break;
                DPRINTF(1, "set_prev_command: DMA Wait\n");
            }
        } else {
            cdvdman_scmd_flg = 0;
            goto cdvdscmd_l1;
        }
    }

    cdvdman_scmd_flg = 1;

    cdvdman_write_scmd(&cdvdman_command);

cdvdscmd_l1:

    i = 0;

    if (!cdvdman_scmd_flg) {
        j = 1;
        do {
            delay_thread(j * 1000);
            if ((i & 1) && (j < 0x10))
                j <<= 1;
            i += j;
        } while ((i < 500) && (!cdvdman_scmd_flg));
    }

    if (i >= 500) {
        cdvdman_scmd_flg = 1;
        if (check_sef == 1)
            set_ev_flag(cdvdman_scmd_ef, 1);
        return 0;
    }

    if (rdlen) {
        for (i = 0; i < rdlen; i++)
            ((char *)rdata)[i] = cdvdman_scmd_rd[i];
    }

    if (check_sef == 1)
        set_ev_flag(cdvdman_scmd_ef, 1);

    return cdvdman_scmd;
}

/* internal routine */
void cdvdman_write_scmd(void *common)
{
    char rdbuffer[0x40];
    int i, j, t;

    t = 0;

    do {
        register int f;

        if (CDVDreg_SDATAIN & 0x80) {
            cdvdman_scmd_flg = 1;
            cdvdman_scmd = 0;
            return;
        }

        do {
            (void)CDVDreg_SDATAOUT;
        } while (!(CDVDreg_SDATAIN & 0x40));

        if (cdvdman_sdlen) {
            for (i = 0; i < cdvdman_sdlen; i++)
                CDVDreg_SDATAIN = cdvdman_scmd_sd[i];
        }

        CDVDreg_SCOMMAND = cdvdman_scmd;
        (void)CDVDreg_SCOMMAND;

        i = 0;

        if (!QueryIntrContext()) {
            if (CDVDreg_SDATAIN & 0x80) {
                do {
                    DelayThread(100);

                    if (50000 < i) {
                        cdvdman_scmd_flg = 1;
                        cdvdman_scmd = 0;
                        return;
                    }

                    i++;
                } while (CDVDreg_SDATAIN & 0x80);
            }
        } else {
            if (CDVDreg_SDATAIN & 0x80) {
                do {
                    if (0xBEBC20 < i) {
                        cdvdman_scmd_flg = 1;
                        cdvdman_scmd = 0;
                        return;
                    }
                    i++;
                } while (CDVDreg_SDATAIN & 0x80);
            }
        }

        f = i = 0;

        if (!(CDVDreg_SDATAIN & 0x40)) {
            do {
                if (i < cdvdman_rdlen) {
                    rdbuffer[i] = CDVDreg_SDATAOUT;
                    i++;
                } else {
                    f = 1;
                    DPRINTF(1, "Prev Cmd Result Over Flow\n");
                    break;
                }
            } while (!(CDVDreg_SDATAIN & 0x40));
        }

        if (((f) || (cdvdman_rdlen)) && (cdvdman_rdlen != 0x10)) {
            DPRINTF(1, "Prev Cmd Result Illegal Size Try count:%d\n", t);
            t++; /* rewrite this branch ? */
        } else
            break;

    } while (t <= 0);

    if (t == 1) {
        cdvdman_scmd_flg = 1;
        cdvdman_scmd = 0;
        return;
    }

    j = 0xF;

    while (j >= 0)
        cdvdman_scmd_rd[j--] = 0;

    if (cdvdman_rdlen == 0x10) {
        if (i > 0) {
            j = 0;
            do {
                cdvdman_scmd_rd[j] = rdbuffer[j];
            } while (++j < i);
        }
    } else {
        if (cdvdman_rdlen) {
            j = 0;
            do {
                cdvdman_scmd_rd[j] = rdbuffer[j];
            } while (++j < cdvdman_rdlen);
        }
    }

    cdvdman_scmd_flg = 1;
    cdvdman_scmd = 1;
}

/* internal */
int cdvdman_send_scmd2(int cmd, const void *sdata, int sdlen, void *rdata, int rdlen, int check_sef)
{
    char rbuffer[0x40];
    u32 resultp;
    int adlen;
    register int i, t;

    if (check_sef == 1)
        if (PollEventFlag(cdvdman_scmd_ef, 1, EF_WAIT_CLEAR, &resultp) == 0xFFFFFE5B)
            return 0;

    t = 0;
    adlen = (u32)10 - rdlen;

    do {
        register int f;

        if (CDVDreg_SDATAIN & 0x80) {
            if (check_sef == 1)
                set_ev_flag(cdvdman_scmd_ef, 1);
            return 0;
        }

        do {
            (void)CDVDreg_SDATAOUT;
        } while (!(CDVDreg_SDATAIN & 0x40));

        if (sdlen) {
            i = 0;

            do {
                CDVDreg_SDATAIN = ((u8 *)sdata)[i];
            } while (++i < sdlen);
        }

        CDVDreg_SCOMMAND = cmd;
        (void)CDVDreg_SCOMMAND;

        if (CDVDreg_SDATAIN & 0x80) {
            do {
                DelayThread(100);
            } while (CDVDreg_SDATAIN & 0x80);
        }

        f = i = 0;

        if (!(CDVDreg_SDATAIN & 0x40)) {
            do {
                if (i >= rdlen) {
                    f = 1;
                    DPRINTF(1, "Prev Cmd Result Over Flow\n");
                    break;
                }

                rbuffer[i] = CDVDreg_SDATAOUT;

                i++;
            } while (!(CDVDreg_SDATAIN & 0x40));
        }

        if (((f) || (i < rdlen)) && (rdlen != 0x10)) {
            DPRINTF(1, "Prev Cmd Result Illegal Size Try count:%d\n", t);
            if (!(CDVDreg_SDATAIN & 0x20)) {
                do {
                    (void)CDVDreg_SDATAOUT;
                } while (!(CDVDreg_SDATAIN & 0x20));
            }
        } else
            break;

        if (adlen > 0) {
            register int a, b;

            a = 0;
            b = (u32)10 - rdlen;

            do {
                (void)CDVDreg_SDATAOUT;
            } while (++a < b);
        }

    } while (++t <= 0);

    if (t == 1) {
        if (check_sef == 1)
            set_ev_flag(cdvdman_scmd_ef, 1);
        return 0;
    }

    if (rdlen) {
        register int a;

        a = 0;

        do {
            ((u8 *)rdata)[a] = ((u8 *)rbuffer)[a];
        } while (++a < rdlen);
    }

    if (check_sef == 1)
        set_ev_flag(cdvdman_scmd_ef, 1);

    return 1;
}

/* callback used by cdvdman_send_ncmd (internal) */
unsigned int alarm_cb_ncmd(void *param)
{
    DPRINTF(0, "Cmd Time Out %d(msec)\n", (iop_sys_clock_t *)(param)->low / 0x9000);
    ((iop_sys_clock_t *)(param))->lo = 0;
    return 0;
}

int intrh_dma_3(void *common)
{
    int dummy;
    register int dmaflag;

    cdvdman_dma3prm.dma3_msectors -= cdvdman_dma3prm.dma3_csectors;
    if (cdvdman_dma3prm.dma3_callback)
        dmaflag = cdvdman_dma3prm.dma3_callback(common);
    else
        dmaflag = 1;

    cdvdman_dma3sec += cdvdman_dma3prm.dma3_csectors;
    cdvdman_dma3prm.dma3_csectors = (cdvdman_rdchunk < cdvdman_dma3prm.dma3_msectors) ? cdvdman_rdchunk : cdvdman_dma3prm.dma3_msectors;

    if (dmaflag) {
        if (cdvdman_dma3prm.dma3_msectors) {
            dmac_ch_set_chcr(3, 0);
            dmac_ch_get_chcr(3);
            dmac_ch_set_madr(3, (u32)cdvdman_dma3prm.dma3_maddress);
            dmac_ch_set_bcr(3, cdvdman_dma3prm.dma3_blkwords | (cdvdman_dma3prm.dma3_blkcount * cdvdman_dma3prm.dma3_csectors << 16));
            dmac_ch_set_chcr(3, 0x40000000 | DMAf_TR | DMAf_CO);
            dmac_ch_get_chcr(3);

            iClearEventFlag(cdvdman_intr_ef, 0xFFFFFFDF);
        } else {
            DisableIntr(INUM_DMA_3, &dummy);
            iSetEventFlag(cdvdman_intr_ef, 0x20);
        }
    }

    if ((!cdvdman_dma3prm.dma3_msectors) && (cdvdman_dr_flg)) {
        cdvdman_intr_cb(common);
        cdvdman_dr_flg = 0;
    }
    return 0;
}

int cdvdman_setdma3(DMA3PARAM *b18)
{
    int result = 0, val;

    if (dmac_ch_get_chcr(3) & DMAf_TR)
        CDVDreg_ABORT = 1;

    cdvdman_dma3prm = *b18;
    cdvdman_dma3sec = 0;

    dmac_ch_set_chcr(3, 0);
    result = dmac_ch_get_chcr(3);
    if (b18->dma3_csectors) {
        clear_ev_flag(cdvdman_intr_ef, 0xFFFFFFDF);
        EnableIntr(INUM_DMA_3);
    }

    CDVDreg_HOWTO = b18->cdvdreg_howto;
    dmac_ch_set_madr(3, (u32)b18->dma3_maddress);

    if (!b18->dma3_csectors)
        val = b18->dma3_blkcount;
    else
        val = b18->dma3_csectors * b18->dma3_blkcount;
    val <<= 16;

    dmac_ch_set_bcr(3, val | b18->dma3_blkwords);
    dmac_ch_set_chcr(3, 0x40000000 | DMAf_TR | DMAf_CO);
    dmac_ch_get_chcr(3);

    return result;
}

/* internal routine */
/* b18 - is a structure used to initialize dma (ch. 3) transfer */
int cdvdman_send_ncmd(int ncmd, const void *ndata, int ndlen, int func, DMA3PARAM *b18, int check_cb)
{
    u8 media_type;
    int i;
    u32 resultp;

    if (check_cb == 1)
        if (PollEventFlag(cdvdman_ncmd_ef, 1, EF_WAIT_CLEAR, &resultp) == 0xFFFFFE5B)
            return -1;

    if (((CDVDreg_READY & 0xC0) != 0x40) || ((!cdvdman_waf) && ((cdvdman_read2_flg == 1) || ((cdvdman_read2_flg == 1) && ((ncmd & 0xFF) != CDVD_NCMD_DVDREAD)) || ((cdvdman_read2_flg == 2) && ((ncmd & 0xFF) != CDVD_NCMD_READ))))) {
        if (check_cb)
            set_ev_flag(cdvdman_ncmd_ef, 1);
        DPRINTF(1, "set_cd_commnad Error  stat %02x\n", CDVDreg_READY);
        return -1;
    }

    cdvdman_iocache = 0;
    if (b18)
        cdvdman_setdma3(b18);
    cdvdman_cmdfunc = func;
    media_type = CDVDreg_TYPE;

    if ((!cdvdman_newmeca) && (cdvdman_ncmd == CDVD_NCMD_READ)) {
        ncmd &= 0xFF;
        if ((ncmd) && (ncmd != cdvdman_ncmd) && (ncmd != CDVD_NCMD_READFULL) &&
            (ncmd != 0xE) && (ncmd != CDVD_NCMD_DVDREAD) && ((media_type != 0xFD) || (ncmd == CDVD_NCMD_STOP))) {
            cdvdman_ncmd_to.hi = 0;
            cdvdman_ncmd_to.lo = 0x6978000;
            set_alarm(&cdvdman_ncmd_to, alarm_cb_ncmd, &cdvdman_ncmd_to);
            if (CDVDreg_STATUS != 0xA) {
                do {
                    DPRINTF(1, "Read Pause 1 chk status 0x%02x\n", CDVDreg_STATUS);
                    if (!cdvdman_ncmd_to.lo) {
                        cdvdman_ncmd = ncmd;
                        if (check_cb == 1)
                            set_ev_flag(cdvdman_ncmd_ef, 1);
                        DPRINTF(0, "Time Out Pause WAIT set_cd_command\n");
                        return -1;
                    }
                    delay_thread(1000);
                } while (CDVDreg_STATUS != 0xA);
            }
            cancel_alarm(alarm_cb_ncmd, &cdvdman_ncmd_to);
        }
    }

    cdvdman_ncmd = ncmd;
    if (cdvdman_decstate)
        sceCdDecSet(cdvdman_decshift > 0, 1, cdvdman_decshift);

    cdvdman_read_to = 0;
    cdvdman_command = ncmd;
    cdvdman_cderror = 0;
    cdvdman_waf = 0;
    cdvdman_thrd_id = GetThreadId();
    if (QueryIntrContext())
        iClearEventFlag(cdvdman_intr_ef, 0xFFFFFFFE);
    else
        ClearEventFlag(cdvdman_intr_ef, 0xFFFFFFFE);

    i = 0;
    if (ndlen) {
        do {
            CDVDreg_NDATAIN = ((u8 *)ndata)[i];
            i++;
        } while (i < ndlen);
    }
    CDVDreg_NCOMMAND = ncmd;
    (void)CDVDreg_NCOMMAND;

    if (check_cb == 1)
        set_ev_flag(cdvdman_ncmd_ef, 1);

    return 0;
}

/* Exported entry #54 */
int sceCdApplyNCmd(u8 ncmd, const void *ndata, u16 ndlen, void* outBuff)
{
    DPRINTF(0, "Apply NCmd call cmd= 0x%02x\n", ncmd & 0xFF);

    while (cdvdman_send_ncmd(ncmd & 0xFF, ndata, ndlen, 0, 0, 1) < 0)
        delay_thread(2000);
    sceCdSync(4);

    return 1;
}

/* Exported entry #21 */
int sceCdCheckCmd()
{
    return cdvdman_waf;
}

/* internal routine */
int cdvdman_mediactl(int code)
{
    u32 resultp;
    char rdata;
    register int r, b;

    if (PollEventFlag(cdvdman_scmd_ef, 1, EF_WAIT_CLEAR, &resultp) == 0xFFFFFE5B)
        return 0;

    b = CDVDreg_B & 1;
    if (b == cdvdman_chmedia)
    {
        if (cdvdman_chflags[code]) {
            r = 1;
            cdvdman_chflags[code] = 0;
        } else
            r = 0;
    }
    else
    {
        register int i = 0;

        do {
            cdvdman_chflags[i] = (u32)(i ^ code) > 0;
        } while (++i < 4);
        r = 1;
    }

    if ((CDVDreg_STATUS & 1) != b) {
        for (;;) {
            if (cdvdman_send_scmd(5, 0, 0, &rdata, 1, 0))
                if (!rdata)
                    break;
            delay_thread(4000);
        }
    }

    cdvdman_chmedia = CDVDreg_B & 1;
    set_ev_flag(cdvdman_scmd_ef, 1);

    return r;
}

/* Exported entry #44 */
u32 sceCdGetReadPos()
{
    int sector_sizes[3];

    sector_sizes[0] = cdvdman_sect_p0;
    sector_sizes[1] = cdvdman_sect_p1;
    sector_sizes[2] = cdvdman_sect_p2;

    if ((!cdvdman_recstat) || (cdvdman_recstat == 3))
    {
        if (!cdvdman_read2_flg) {
            if (cdvdman_cmdfunc != SCECdFuncRead)
                return 0;
            return dmac_ch_get_madr(3) - (u32)cdvdman_readbuf;
        } else {
            return cdvdman_readptr * sector_sizes[cdvdman_pattern];
        }
    }
    return 0;
}

/* internal routine */
int cdvdman_speedctl(u32 spindlctrl, int dvdflag, u32 maxlsn)
{
    switch (spindlctrl) {
        case 0:
            return (dvdflag) ? 2 : 4;
        case 1:
            if (!dvdflag)
                return 0x85;
            if (cdvdman_newmeca)
                return 0x83;
            if (cdvdman_dldvd) {
                if (maxlsn >= cdvdman_layer1)
                    maxlsn -= cdvdman_layer1;
                if (maxlsn < 0x197000)
                    return 0x83;
            } else if (maxlsn < 0x1C9000)
                return 0x83;

            DPRINTF(1, "Kprob Spd D lsn= %d\n", maxlsn);
            return 0x82;
        case 2:
            return 1;
        case 3:
            return 2;
        case 4:
            return (dvdflag) ? 2 : 3;
        case 5:
            return (dvdflag) ? 3 : 4;
        case 6:
        case 7:
        case 8:
        case 9:
        case 11:
        case 13:
        case 18:
        case 19:
        default:
            return (dvdflag) ? 0x83 : 0x85;
        case 10:
            return 0x40;
        case 12:
            return (dvdflag) ? 4 : 2;
        case 14:
            return 1;
        case 15:
            return 0x82;
        case 16:
            return (dvdflag) ? 0x82 : 0x83;
        case 17:
            return (dvdflag) ? 0x82 : 0x84;
        case 20:
            return (dvdflag) ? 3 : 5;
    }
}

/* internal routine */
int cdvdman_isdvd()
{
    u32 type;

    type = CDVDreg_TYPE & 0xFF;
    if (type == 0x14)
        return 1; /* SCECdPS2DVD */
    if (type < 0x15) {
        if (type < 0x10)
            return 0;
    } else {
        if (type == 0xFD)
            return 0; /* SCECdCDDA */
        if (type < 0xFE) {
            if (type == 0xFC)
                return 1; /* unknown, but should be a DVD anyway, it's probably DVDRW */
        } else if (type == 0xFE)
            return 1; /* SCECdDVDV */
    }

    return 0;
}

/* internal */
int sceCdRead0_Rty(u32 lsn, u32 nsec, void *buf, sceCdRMode *mode, int ncmd, int dintrsec, void *func)
{
    DMA3PARAM b18;
    char ndata[0xB];
    register int fn, sc;

    DPRINTF(1, "sceCdRead0_Rty Lsn:%d nsec:%d dintrsec %d func: %08x\n", lsn, nsec, dintrsec, func);

    *(u32 *)&ndata[0] = lsn;
    *(u32 *)&ndata[4] = nsec;
    ndata[8] = mode->trycount;
    ndata[9] = cdvdman_speedctl(mode->spindlctrl, cdvdman_isdvd(), lsn + nsec);

    b18.dma3_csectors = dintrsec;
    b18.dma3_callback = func;
    b18.dma3_csectors = nsec;
    b18.dma3_maddress = buf;

    sc = (dintrsec & 0xFFFF) ? dintrsec : nsec;


    if (ncmd == CDVD_NCMD_READ) {
        ndata[0xA] = mode->datapattern;
        switch (mode->datapattern) {
            case SCECdSecS2328:
                b18.dma3_blkcount = 97 * sc;
                b18.dma3_blkwords = 0x6;
                b18.cdvdreg_howto = 0x86;
                break;
            case SCECdSecS2340:
                b18.dma3_blkwords = 0xF;
                b18.dma3_blkcount = 39 * sc;
                b18.cdvdreg_howto = 0x8F;
                break;
            default:
                b18.dma3_blkwords = 0x20;
                b18.dma3_blkcount = 16 * sc;
                b18.cdvdreg_howto = 0x80;
                break;
        }
        fn = SCECdFuncRead;
    } else if (ncmd == CDVD_NCMD_DVDREAD) {
        fn = 0xE;
        b18.cdvdreg_howto = 0x8C;
        b18.dma3_blkwords = 0xC;
        b18.dma3_blkcount = 43 * sc;
        ndata[0xA] = 0;
    } else
        return 0;

    return (cdvdman_send_ncmd(ncmd, ndata, 0xB, fn, &b18, 0) >= 0) ? 1 : 0;
}

/* Exported entry #62 */
int sceCdRead0(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int csec, void *cb)
{
    DMA3PARAM b18;
    char ndata[0xB];
    u32 resultp;
    int type;

    if (PollEventFlag(cdvdman_ncmd_ef, 1, EF_WAIT_CLEAR, &resultp) == 0xFFFFFE5B)
        return 0;

    DPRINTF(1, "DVD/CD sceCdRead0 sec %d num %d spin %d trycnt %d dptn %d adr %08x\n", lsn, sectors, mode->spindlctrl, mode->trycount, mode->datapattern, buf);

    cdvdman_readbuf = buf;
    if (!csec)
        b18.dma3_csectors = 0;
    else
        b18.dma3_csectors = (sectors < csec) ? sectors : csec;

    b18.dma3_callback = cb;
    b18.dma3_msectors = sectors;

    switch (mode->datapattern) {
        case SCECdSecS2328:
            b18.dma3_blkwords = 0x6;
            b18.dma3_blkcount = 97 * ((csec) ? 1 : sectors);
            b18.cdvdreg_howto = 0x86;
            break;
        case SCECdSecS2340:
            b18.dma3_blkwords = 0xF;
            b18.dma3_blkcount = 39 * ((csec) ? 1 : sectors);
            b18.cdvdreg_howto = 0x8F;
            break;
        default:
            b18.dma3_blkwords = 0x20;
            b18.dma3_blkcount = 16 * ((csec) ? 1 : sectors);
            b18.cdvdreg_howto = 0x80;
    }

    type = CDVDreg_TYPE;

    /* for revision */
    if ((type >= 0x10) && (type <= 0x14) && ((cdvdman_mmode == ((type == 0x14) ? 2 : 1)) || (cdvdman_mmode == 0xFF))) {
        cdvdman_dvdflag = (type == 0x14) ? 1 : 0;
        cdvdman_rdmode = *mode;
        cdvdman_read_cb = cb;
        cdvdman_rdchunk = b18.dma3_csectors;
        cdvdman_rd_lsn = lsn;
        cdvdman_rd_sec = sectors;

        *(u32 *)&ndata[0] = cdvdman_rd_lsn;
        *(u32 *)&ndata[4] = cdvdman_rd_sec;
        ndata[8] = mode->trycount;
        ndata[9] = cdvdman_speedctl(mode->spindlctrl, cdvdman_dvdflag, lsn + sectors);
        cdvdman_rd_buf = buf;
        ndata[10] = mode->datapattern;
        b18.dma3_maddress = cdvdman_rd_buf;
        DPRINTF(1, "Read Command call\n");

        if (cdvdman_send_ncmd(CDVD_NCMD_READ, ndata, 0xB, SCECdFuncRead, &b18, 0) >= 0) {
            set_ev_flag(cdvdman_ncmd_ef, 1);
            return 1;
        }
    }

    set_ev_flag(cdvdman_ncmd_ef, 1);

    return 0;
}

int read_cdvd_cb(void *common)
{
    sceCdlLOCCD cd_loc;
    register u32 readlsn;
    register int index, dvoff, cdoff, layer = 0, sblock;

    index = layer;
    if (VAR_ushort(cdvdman_dma3prm.dma3_csectors)) {
        dvoff = layer;
        cdoff = layer;

        do {
            register u32 lsn, dlt;

            if ((cdvdman_read2_flg & 0xFFFF) != 3) {
                sblock = 2064;

                readlsn = cdvdman_syncdec(cdvdman_decstate, cdvdman_xorvalue, cdvdman_decshift, ((u8 *)cdvdman_ptoc)[3 + dvoff]) & 0xFF;
                readlsn += (cdvdman_syncdec(cdvdman_decstate, cdvdman_xorvalue, cdvdman_decshift, ((u8 *)cdvdman_ptoc)[2 + dvoff]) & 0xFF) << 8;
                readlsn += (cdvdman_syncdec(cdvdman_decstate, cdvdman_xorvalue, cdvdman_decshift, ((u8 *)cdvdman_ptoc)[1 + dvoff]) & 0xFF) << 16;
                layer = cdvdman_syncdec(cdvdman_decstate, cdvdman_xorvalue, cdvdman_decshift, ((u8 *)cdvdman_ptoc)[1 + dvoff]) & 0x1;

                    readlsn += 0xFFFD0000;

                dlt = cdvdman_dldvd;
                if (dlt) {
                    u32 t, l;

                    t = cdvdman_readlsn;
                    t += cdvdman_csec;
                    t += index;
                    l = cdvdman_layer1;

                    if (!(t < l))
                        if (dlt == 1)
                            readlsn += l;
                }
            } else {
                sblock = 2340;

                cd_loc.minute = cdvdman_syncdec(cdvdman_decstate, cdvdman_xorvalue, cdvdman_decshift, ((u8 *)cdvdman_ptoc)[0 + cdoff]);
                cd_loc.second = cdvdman_syncdec(cdvdman_decstate, cdvdman_xorvalue, cdvdman_decshift, ((u8 *)cdvdman_ptoc)[1 + cdoff]);
                cd_loc.sector = cdvdman_syncdec(cdvdman_decstate, cdvdman_xorvalue, cdvdman_decshift, ((u8 *)cdvdman_ptoc)[2 + cdoff]);

                readlsn = sceCdPosToInt(&cd_loc);
            }

            lsn = cdvdman_readlsn + cdvdman_csec + cdvdman_dma3sec + index;
            if (readlsn != lsn) {
                DPRINTF(1, "Read_IOP Sector_ID error lsn= %d readlsn= %d layer= %d\n", lsn, readlsn, layer);
                break;
            }

            dvoff += 2064;
            cdoff += 2340;

        } while (++index < VAR_ushort(cdvdman_dma3prm.dma3_csectors));
    }

    if (VAR_ushort(cdvdman_dma3prm.dma3_csectors) == index) {
        if (cdvdman_pattern == 2) {
            memcpy((void *)((u32)cdvdman_rbuffer + cdvdman_dma3sec * 2340), cdvdman_ptoc, index * 2340);
        } else {
            register u32 size;

            size = cdvdman_pattern ? 2328 : 2048;

            if (VAR_ushort(cdvdman_dma3prm.dma3_csectors)) {
                register u32 offset;

                index = 0;
                offset = 0xC;

                do {
                    memcpy(((void *)(u32)cdvdman_rbuffer + (cdvdman_dma3sec + index) * size), (void *)((u32)cdvdman_ptoc + offset), size);
                    offset += sblock;
                } while (++index < VAR_ushort(cdvdman_dma3prm.dma3_csectors));
            }
        }

        cdvdman_readptr = cdvdman_csec + cdvdman_dma3sec;
    } else {
        cdvdman_syncerr += 1;
    }

    return 1;
}

/* internal routine */
int cdvdman_read(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int decflag, int shift)
{
    int dvd, rsect;

    dvd = cdvdman_isdvd();
    if (dvd) {
        if (!DvdDual_infochk())
            return 0;
        lsn = sceCdLsnDualChg(lsn);
    } else if (mode->datapattern == 1)
        return sceCdRead0(lsn, sectors, buf, mode, 0, 0);

    if ((!cdvdman_cd36key) || (cdvdman_decstate)) {
        int oldstate, dummy, rc;

        CpuSuspendIntr(&oldstate);

        if (((CDVDreg_READY & 0xC0) == 0x40) && (!cdvdman_read2_flg)) {
            if (decflag) {
                cdvdman_decshift = shift;
                cdvdman_decstate = 1;
            }
            cdvdman_readbuf = buf;
            cdvdman_readptr = 0;
            cdvdman_readlsn = lsn;
            cdvdman_csec = 0;
            cdvdman_nsec = sectors;
            cdvdman_rbuffer = buf;
            cdvdman_pattern = 0;
            cdvdman_cdrmode.trycount = mode->trycount;
            cdvdman_cdrmode.spindlctrl = mode->spindlctrl;
            cdvdman_syncerr = 0;
            if (sectors >= 0x41) {
                if (lsn & 0xF)
                    rsect = 0x10 - (lsn & 0xF);
                else
                    rsect = 0x40;
            } else
                rsect = sectors;

            cdvdman_rdsectc = rsect;
            cdvdman_racb_to.hi = 0;
            cdvdman_racb_to.lo = sceCdSC(0xFFFFFFF1, &dummy) * 0x9000;
            set_alarm(&cdvdman_racb_to, alarm_cb_read, &cdvdman_racb_to);
            if (dvd) {
                cdvdman_read2_flg = 1;
                rc = sceCdRV(lsn, rsect, cdvdman_ptoc, mode, 8, read_cdvd_cb);
            } else {
                cdvdman_cdrmode.datapattern = 2;
                cdvdman_pattern = mode->datapattern;
                cdvdman_read2_flg = 3;
                rc = sceCdRead0(lsn, rsect, cdvdman_ptoc, &cdvdman_cdrmode, 8, read_cdvd_cb);
            }

            if (rc) {
                CpuResumeIntr(oldstate);
                return 1;
            }

            cdvdman_cderror = SCECdErREADCFR;
            cdvdman_rdsectc = 0;
            cdvdman_read2_flg = 0;

            if (cdvdman_decstate) {
                cdvdman_decstate = cdvdman_xorvalue = cdvdman_decshift = 0;
                sceCdDecSet(0, 0, 0);
            }

            cancel_alarm(alarm_cb_read, &cdvdman_racb_to);
        }
        else
        {
            DPRINTF(1, "sceCdRead: Double Booking error r2f= %d waf= %d\n", cdvdman_read2_flg, cdvdman_waf);
        }

        CpuResumeIntr(oldstate);
        return 0;
    } else if (mode->spindlctrl == 1)
        mode->spindlctrl = 0;

    return sceCdRead0(lsn, sectors, buf, mode, 0, 0);
}

/* Exported entry #114 */
/* Used by CDVDSTM.IRX */
/* int sceCdReadIOPmu_int lsn, u32 sectors, void *buf, sceCdRMode *mode) */
int sceCdRE(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode)
{
    return cdvdman_read(lsn, sectors, buf, mode, 0, 0);
}

/* #define ROL8(v, b)  (((v) << (b)) | ((v) >> (8 - (b)))) */

/* internal */
int cdvdman_syncdec(int decflag, int decxor, int shift, u32 data)
{
    register u32 s, t;

    if (decflag) {
        if (shift < 0)
            shift += 7;
        t = shift >> 3;
        t <<= 3;
        s = shift - t;
        data &= 0xFF;
        t = data << s;
        s = 8 - s;
        data >>= s;
        t |= data;

        return t ^ decxor; /* return decxor ^ ROL8(data & 0xFF, shift - ((u32)(shift >> 3) << 3)); */
    } else
        return data & 0xFF;
}

/* internal routine */
void Read2intrCDVD(int read2_flag)
{
    int dummy;
    register int r, t;

    iCancelAlarm(alarm_cb_read, (void *)&cdvdman_racb_to);

    t = cdvdman_retries;

    if ((!cdvdman_cderror) && (t < 5)) {
        register sceCdRMode *rmode;

        rmode = &cdvdman_cdrmode;

        if (!cdvdman_syncerr) {
            register int secsize;

            cdvdman_retries = 0;

            if (cdvdman_pattern == 2)
                secsize = 2340;
            else
                secsize = (cdvdman_pattern) ? 2328 : 2048;

            cdvdman_rbuffer = (void *)((u32)cdvdman_rbuffer + cdvdman_rdsectc * secsize);
            cdvdman_csec += cdvdman_rdsectc;

            if (cdvdman_csec < cdvdman_nsec) {
                cdvdman_rdsectc = ((cdvdman_csec + 0x40) < cdvdman_nsec) ? 0x40 : (cdvdman_nsec - cdvdman_csec);

                if (read2_flag != 3)
                    r = sceCdRV(cdvdman_readlsn + cdvdman_csec, cdvdman_rdsectc, cdvdman_ptoc, rmode, 8, read_cdvd_cb);
                else
                    r = sceCdRead0(cdvdman_readlsn + cdvdman_csec, cdvdman_rdsectc, cdvdman_ptoc, rmode, 8, read_cdvd_cb);
                if (r) {
                    cdvdman_racb_to.hi = 0;
                    cdvdman_racb_to.lo = sceCdSC(0xFFFFFFF1, &dummy) * 0x9000;
                    iSetAlarm(&cdvdman_racb_to, alarm_cb_read, &cdvdman_racb_to);
                } else {
                    cdvdman_cderror = SCECdErNORDY;
                    cdvdman_read2_flg = 0;
                    cdvdman_readptr = 0;
                    if (cdvdman_decstate)
                        cdvdman_decstate = cdvdman_xorvalue = cdvdman_decshift = 0;
                }
            } else {
                cdvdman_read2_flg = 0;
                cdvdman_readptr = 0;
                if (cdvdman_decstate)
                    cdvdman_decstate = cdvdman_xorvalue = cdvdman_decshift = 0;
            }
        } else {
            register u32 lsn;

            if (!cdvdman_rtindex) {
                cdvdman_retries = t + 1;
                cdvdman_rtindex = 3;
            }

            cdvdman_syncerr = 0;

            lsn = cdvdman_readlsn + cdvdman_csec;
            if (lsn >= 0x30)
                lsn -= (cdvdman_rtindex - 1) * 16;
            else
                lsn += (cdvdman_rtindex - 1) * 16;

            if (read2_flag != 3)
                r = sceCdRV(lsn, cdvdman_rdsectc, cdvdman_ptoc, rmode, 8, read_cdvd_cb);
            else
                r = sceCdRead0(lsn, cdvdman_rdsectc, cdvdman_ptoc, rmode, 8, read_cdvd_cb);

            if (r) {
                cdvdman_racb_to.hi = 0;
                cdvdman_racb_to.lo = sceCdSC(0xFFFFFFF1, &dummy) * 0x9000;
                iSetAlarm(&cdvdman_racb_to, alarm_cb_read, &cdvdman_racb_to);
            } else {
                DPRINTF(1, "Retry Read Fatal Error\n");
                cdvdman_cderror = SCECdErNORDY;
                cdvdman_read2_flg = 0;
                cdvdman_retries = 0;
                cdvdman_rtindex = 0;
                cdvdman_readptr = 0;
                if (cdvdman_decstate)
                    cdvdman_decstate = cdvdman_xorvalue = cdvdman_decshift = 0;
            }

            r = cdvdman_retries;
            if (r)
                cdvdman_retries = r - 1;
        }
    } else {
        if (!cdvdman_cderror)
            cdvdman_cderror = SCECdErREADCF;
        cdvdman_read2_flg = 0;
        cdvdman_retries = 0;
        cdvdman_rtindex = 0;
        cdvdman_readptr = 0;
        if (cdvdman_decstate)
            cdvdman_decstate = cdvdman_xorvalue = cdvdman_decshift = 0;
    }
}

/* Exported entry #66 */
int sceCdReadChain(sceCdRChain *read_tag, sceCdRMode *mode)
{
    return 0; /* in most IOP images */
}

/* internal routine */
int cdvdman_readfull(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int flag)
{
    DMA3PARAM b18;
    char ndata[0xB];
    register int ncmd, t;

    b18.dma3_csectors = 0;
    b18.dma3_msectors = 0;
    b18.dma3_callback = 0;

    switch (mode->datapattern) {
        case 1:
            b18.dma3_blkwords = 0x8;
            b18.dma3_blkcount = 74 * sectors;
            t = 0x88;
            break;
        case 2:
            b18.dma3_blkwords = 0xC;
            b18.dma3_blkcount = 51 * sectors;
            t = 0x8C;
            break;
        default:
            b18.dma3_blkwords = 0xC;
            b18.dma3_blkcount = 49 * sectors;
            t = 0x8C;
            break;
    }

    b18.cdvdreg_howto = t;

    switch (CDVDreg_TYPE & 0xFF) {
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0xFD:
            break;
        default:
            return 0;
    }

    ncmd = (flag) ? 0xE : CDVD_NCMD_READFULL;

    *(u32 *)&ndata[0] = lsn;
    *(u32 *)&ndata[4] = sectors;
    ndata[8] = mode->trycount;
    ndata[9] = cdvdman_speedctl(mode->spindlctrl, 0, lsn + sectors);
    b18.dma3_maddress = buf;
    ndata[10] = mode->datapattern;

    return cdvdman_send_ncmd(ncmd, ndata, 0xB, (flag) ? 0xC : SCECdFuncReadCDDA, &b18, 1) >= 0;
}

/* Exported entry #76 */
int sceCdReadFull(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode)
{
    return cdvdman_readfull(lsn, sectors, buf, mode, (cdvdman_ncmd0Eh) ? 1 : 0);
}

/* Exported entry #75 */
int sceCdMmode(int media)
{
    cdvdman_mmode = media;
    return 1;
}

/* Exported entry #36 (bios & bbnav) */
int sceCdDecSet(unsigned char arg1, unsigned char arg2, unsigned char shift)
{
/* Just returns 1 in most IOPRP images */
#ifdef __CDVDMAN_SW_E36__
    /* 
  The code below can be found in a BIOS and BB Nav.
  It's absent in most IOPRP images.
 */
    register u32 dec;
    cdvdman_cd36key = arg2 | shift;
    shift &= 7;
    shift <<= 4;

    dec = (arg1) ? (shift | 2) : shift;
    if (arg2)
        dec |= 1;

    CDVDreg_DEC = dec;
#endif
    return 1;
}

/* Exported entry #71 (only BIOS & BB Nav), internal routine in IOP images. */
int sceCdSpinCtrlIOP(u32 speed)
{
    DPRINTF(1, "sceCdSpinCtrlIOP speed= %d\n", speed);
    cdvdman_spinctl = speed;
    return 1;
}

/* Exported entry #17 */
sceCdlLOCCD *sceCdIntToPos(u32 i, sceCdlLOCCD *p)
{
    register int sc, se, mi;

    i += 150;
    se = i / 75;
    sc = i - se * 75;
    mi = se / 60;
    se = se - mi * 60;
    p->sector = (sc - (sc / 10) * 10) + (sc / 10) * 16;
    p->second = (se / 10) * 16 + se - (se / 10) * 10;
    p->minute = (mi / 10) * 16 + mi - (mi / 10) * 10;

    return p;
}

/* Exported entry #16 */
u32 sceCdPosToInt(sceCdlLOCCD *p)
{
    register int result;

    result = ((u32)p->minute >> 16) * 10 + ((u32)p->minute & 0xF);
    result *= 60;
    result += ((u32)p->second >> 16) * 10 + ((u32)p->second & 0xF);
    result *= 75;
    result += ((u32)p->sector >> 16) * 10 + ((u32)p->sector & 0xF);
    result -= 150;

    return result;
}

/* internal routine */
int CD_newmedia(int layer)
{
    int oldstate;
    u32 ptsector;
    register int type, index;
    register void *buf;
    register u8 *p;
    register int number;
    register u8 *end;

    type = sceCdGetDiskType();
    if ((type != 0x14) && (type != 0x12) && (type != 0x13) && (type != 0x10) &&
        (type != 0x11) && (type != 0xFF) && (type != 0xFE) && (type != 0xFC)) {
        DPRINTF(1, "CD_newmedia: Illegal disc media type =%d\n", type);
        return 0;
    }

    cdvdman_fs_base2 = 0;
    if (type == 0x14) {
        if (!DvdDual_infochk()) {
            DPRINTF(1, "CD_newmedia: Get DvdDual_infochk fail\n");
            return 0;
        }
        if (layer) {
            cdvdman_fs_base2 = cdvdman_layer1;
        } else
            cdvdman_fs_base2 = 0;
    }

    if (disc_read(1, cdvdman_fs_base2 + 0x10, cdvdman_fs_rbuf, layer) != 1) {
        DPRINTF(1, "CD_newmedia: Read error in disc_read(PVD)\n");
        return 0;
    }

    CpuSuspendIntr(&oldstate);

    if (cdvdman_ptblsize) {
        register u32 i = 0;
        register int *p = (int *)cdvdman_pathtbl;

        do {
            p[0] = 0;
            p[1] = 0;
            p[2] = 0;
            p[3] = 0;
            p[4] = 0;
            p += 5;
        } while (++i < cdvdman_ptblsize);
    }

    /* ??? = 0; */
    /* ??? = 0; */
    /* ??? = 0; */

    CpuResumeIntr(oldstate);

    if (strncmp(&cdvdman_fs_rbuf[1], "CD001", 5)) {
        DPRINTF(1, "CD_newmedia: Disc format error in cd_read(PVD)\n");
        return 0;
    }

    switch (type) {
        case 0x10: /* SCECdPSCD */
        case 0x11: /* SCECdPSCDDA */
        case 0x12: /* SCECdPS2CD */
        case 0x13: /* SCECdPS2CDDA */
            ptsector = *(u32 *)(&cdvdman_fs_rbuf[0x8C]);
            DPRINTF(0x11, "CD_newmedia: CD Read mode\n");
            break;
        case 0x14: /* SCECdPS2DVD */
        case 0xFC: /* ? */
        case 0xFE: /* SCECdDVDV */
            ptsector = 0x101;
            DPRINTF(0x11, "CD_newmedia: DVD Read mode\n");
            break;
        default:
            ptsector = 0x101;
            break;
    }

    buf = cdvdman_fs_rbuf;
    if (disc_read(1, cdvdman_fs_base2 + ptsector, buf, layer) != 1) {
        DPRINTF(1, "CD_newmedia: Read error (PT:%08x)\n", ptsector);
        return 0;
    }

    p = (u8 *)buf;

    DPRINTF(2, "CD_newmedia: sarching dir..\n");

    index = 0;
    if (p < &p[0x800]) {
        end = &p[0x800];

        do {
            register char *name;

            if (!*p)
                break;

            name = &cdvdman_dirtbl[index].name[0];

            cdvdman_dirtbl[index].extent = *(int *)&p[2];
            number = index + 1;
            cdvdman_dirtbl[index].number = number;
            cdvdman_dirtbl[index].parent = p[6];

            memcpy(name, &p[8], *p);
            cdvdman_dirtbl[index].name[*p] = 0;

            p += *p + (*p & 0x1) + 8;

            DPRINTF(2, "\t%08x,%04x,%04x,%s\n", cdvdman_dirtbl[index].extent, cdvdman_dirtbl[index].number, cdvdman_dirtbl[index].parent, name);

            index = number;
        } while ((index < CdlMAXDIR) && (p < end));
    }

    if (index < CdlMAXDIR)
        cdvdman_dirtbl[index].parent = 0;

    cdvdman_fs_cdsec = 0;
    cdvdman_fs_layer = layer;

    DPRINTF(2, "CD_newmedia: %d dir entries found\n", index);

    return 1;
}

/* internal routine */
int CD_cachefile(int dsec, int layer)
{
    u32 fslsn;
    u32 *ptrsz;
    u8 *date2;
    u8 *date1;
    register u8 *p;
    register u32 year;
    register int index;
    register u32 *ptlsn;
    register char *pname;
    register u8 *date5;
    register u8 *date4;
    register u8 *date3;


    if (dsec != cdvdman_fs_cdsec) {
        if (!layer) {
            fslsn = cdvdman_dirtbl[dsec - 1].extent;
        } else {
            fslsn = (u32)cdvdman_fs_base2 + cdvdman_dirtbl[dsec - 1].extent;
        }

        p = (u8 *)cdvdman_fs_rbuf;

        if (disc_read(1, fslsn, p, layer) == 1) {
            DPRINTF(2, "CD_cachefile: searching...\n");

            index = 0;
            date1 = &cdvdman_filetbl[0].date[1];
            date2 = &cdvdman_filetbl[0].date[2];
            date3 = &cdvdman_filetbl[0].date[3];
            date4 = &cdvdman_filetbl[0].date[4];
            date5 = &cdvdman_filetbl[0].date[5];
            ptlsn = &cdvdman_filetbl[0].lsn;
            ptrsz = &cdvdman_filetbl[0].size;
            pname = &cdvdman_filetbl[0].name[0];

            if (p < &p[0x800]) {
                do {
                    if (!*p)
                        break;

                    *ptlsn = *(u32 *)&p[0x2];
                    *ptrsz = *(u32 *)&p[0xA];

                    year = p[0x12] + 1900;
                    cdvdman_filetbl[index].date[7] = year >> 8;
                    cdvdman_filetbl[index].date[6] = year;
                    *date5 = p[0x13];
                    *date4 = p[0x14];
                    *date3 = p[0x15];
                    *date2 = p[0x16];
                    *date1 = p[0x17];

                    // TODO: set this correctly after structure entry is added
#if 0
                    cdvdman_filetbl[index].flag = p[0x19];
#endif

                    if (!index) {
                        pname[0] = '.';
                        pname[1] = 0;
                    } else {
                        if (index == 1) {
                            pname[0] = '.';
                            pname[1] = '.';
                            pname[2] = 0;
                        } else {
                            memcpy(pname, &p[0x21], p[0x20]);
                            cdvdman_filetbl[index].name[p[0x20]] = 0;
                        }
                    }

                    DPRINTF(2, "\t lsn %d size %d name:%d:%s %d/%d/%d %d:%d:%d\n", *ptlsn, cdvdman_filetbl[index].size, p[0x20], pname, year, *date5, *date4, *date3, *date2, *date1);

                    date1 += 0x24;
                    date2 += 0x24;
                    date3 += 0x24;
                    date4 += 0x24;
                    date5 += 0x24;
                    pname += 0x24;
                    ptlsn = (u32 *)((u32)ptlsn + 0x24);
                    ptrsz = (u32 *)((u32)ptrsz + 0x24);

                    p += *p;
                    index++;
                } while ((index < CdlMAXFILE) && ((char *)p < &cdvdman_fs_rbuf[0x800]));
            }

            cdvdman_fs_cdsec = dsec;

            if (index < CdlMAXFILE)
                cdvdman_filetbl[index].name[0] = 0;

            DPRINTF(2, "CD_cachefile: %d files found\n", index);
        } else {
            DPRINTF(1, "CD_cachefile: dir not found\n");
            cdvdman_fs_cdsec = 0;

            return 0;
        }
    }

    return 1;
}

int disc_read(int size, int loc, void *buffer, int layer)
{
    sceCdRMode rmode;
    register int f;

    f = 0;
    rmode.trycount = 0x10;

    if (cdvdman_l0check(layer))
        cdvdman_srchspd = 0;

    switch (cdvdman_srchspd) {
        case 2:
            rmode.spindlctrl = 2;
            break;
        case 1:
            rmode.spindlctrl = 1;
            break;
        case 0:
            rmode.spindlctrl = 0;
            break;
        case 3:
            rmode.spindlctrl = 3;
            break;
        case 4:
            rmode.spindlctrl = 4;
            break;
        default:
            rmode.spindlctrl = 1;
            break;
    }

    rmode.datapattern = 0;

    DPRINTF(1, "loc= %d size= %d\n", loc, size);

    if (cdvdman_ptblflag) {
        // TODO: handle cache function
    }

    if (f)
        return size;

    if (!sceCdRE(loc, size, buffer, &rmode))
        return 0;
    sceCdSync(3);
    if (!sceCdGetError())
        return size;

    DPRINTF(1, "cd_read: error code %x\n", sceCdGetError());

    return 0;
}

int cdvdman_cacheinit(u32 blocks, char *fname, int action)
{
    char cachedir[512];
    int oldstate;
    int ioctlarg;
    register int i, v, fd, num;

    v = num = 0;

    if (!action) {
    cacheinit_l1:

        if (cdvdman_cache_fd != -1) {
            v = close(cdvdman_cache_fd);
            if (!(num < 0)) {
                if (!strncmp(cachedir, "pfs", 3)) {
                    num = remove(cachedir);
                } else {
                    if (strncmp(cachedir, "host", 4)) {
                        num = 0;
                        remove(cachedir);
                    }
                }
            }
        }

        CpuSuspendIntr(&oldstate);
        cdvdman_cache_fd = -1;
        /* ??? = 0; ??? = 0; ??? = 0; */
        cdvdman_ptblflag = 0;
        FreeSysMemory(cdvdman_pathtbl);
        cdvdman_pathtbl = 0;
        CpuResumeIntr(oldstate);

        DPRINTF(1, "path_tbl_init Error %d\n", v);

        return (action) ? v : num;
    } else {
        CpuSuspendIntr(&oldstate);
        if ((cdvdman_pathtbl = AllocSysMemory(SMEM_High, blocks * 20, 0))) {
            CpuResumeIntr(oldstate);

            sprintf(cachedir, "%sCache_Path", fname);

            fd = open(cachedir, O_RDWR | O_CREAT | O_TRUNC, 0x1FF);
            if (fd < 0)
                goto cacheinit_l1;

            cdvdman_cache_fd = fd;

            if (!strncmp(cachedir, "pfs", 3)) {
                ioctlarg = blocks << 11;
                ioctl2(cdvdman_cache_fd, PIOCALLOC, &ioctlarg, 4, 0, 0);
            }

            if (num < blocks) {
                i = 0;
                do {
                    v = write(cdvdman_cache_fd, cdvdman_fs_rbuf, 0x800);
                    if (v < 0)
                        goto cacheinit_l1;
                } while (++i < blocks);
            }

            CpuSuspendIntr(&oldstate);
            cdvdman_ptblsize = blocks;
            if (blocks) {
                register int *p;

                i = 0;
                p = (int *)cdvdman_pathtbl;

                do {
                    p[4] = 0;
                    p[3] = 0;
                    p[2] = 0;
                    p[1] = 0;
                    p[0] = 0;

                    p += 5;
                } while (++i < blocks);
            }
            /* ??? = 0; ??? = 0; ??? = 0; */
            cdvdman_ptblflag = 1;
            CpuResumeIntr(oldstate);

            return 0;
        } else {
            CpuResumeIntr(oldstate);
            cdvdman_ptblflag = 0;

            return -12;
        }
    }
    return 0;
}
