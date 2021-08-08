/* cdvdman's file system support (CODE) */

#include "cdvdman-internal.h"

/* For "cdrom" device OPS */
int cdrom_init(iop_device_t *dev)
{
    iop_event_t evfp;
    int dummy;

    DPRINTF(0, "cdvdman Init\n");

    cdvdman_waf = 1;
    cdvdman_scmd_flg = 1;
    cdvdman_read2_flg = 0;
    cdvdman_strm_id = 0;
    cdvdman_cderror = 0;
    cdvdman_layer1 = 0;
    cdvdman_usetoc = 0;
    cdvdman_read_to = 0;
    cdvdman_pwr_flg = 0;
    cdvdman_curdvd = 0;
    cdvdman_dlemu = 0;
    cdvdman_decstate = 0;
    cdvdman_xorvalue = 0;
    cdvdman_decshift = 0;
    cdvdman_dldvd = 0xFF;
    cdvdman_nodecflg = 0;
    cdvdman_ee_ncmd = 0;

    evfp.attr = EA_MULTI;
    evfp.bits = 0;
    evfp.option = 0;

    cdvdman_intr_ef = CreateEventFlag(&evfp);
    cdvdman_scmd_ef = CreateEventFlag(&evfp);
    cdvdman_ncmd_ef = CreateEventFlag(&evfp);
    cdvdman_read_ef = CreateEventFlag(&evfp);

    ClearEventFlag(cdvdman_intr_ef, 0xFFFFFFFB);
    ClearEventFlag(cdvdman_intr_ef, 0xFFFFFFEF);

    SetEventFlag(cdvdman_intr_ef, 0x29);
    SetEventFlag(cdvdman_ncmd_ef, 0x1);
    SetEventFlag(cdvdman_scmd_ef, 0x1);
    SetEventFlag(cdvdman_read_ef, 0x1);

    sceCdSC(0xFFFFFFF3, &dummy);

    return 0;
}

/* For "cdrom" device OPS */
int cdrom_deinit(iop_device_t *)
{
    DeleteEventFlag(cdvdman_read_ef);
    DeleteEventFlag(cdvdman_intr_ef);
    DeleteEventFlag(cdvdman_ncmd_ef);
    DeleteEventFlag(cdvdman_scmd_ef);

    return 0;
}

/* Dummy IOP device call entry */
int cdrom_nulldev(iop_file_t *nuldev, ...)
{
    DPRINTF(0, "nulldev0 call\n");
    return -5;
}

s64 cdrom_nulldev64(iop_file_t *nuldev, ...)
{
    DPRINTF(0, "nulldev0 call\n");
    return -5;
}
