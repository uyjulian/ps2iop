
#include "cdvdman-internal.h"

/* Exported entry #56 */
int sceCdStInit(u32 bufmax, u32 bankmax, void *iop_bufaddr)
{
    int result;
    char devctl_req[0x18];

    memset(&devctl_req, 0, 0x18);

    ((int *)devctl_req)[0x3] = STM0_MODE_INIT;
    ((int *)devctl_req)[0x0] = bufmax;
    ((int *)devctl_req)[0x1] = bankmax;
    ((int *)devctl_req)[0x2] = (u32)iop_bufaddr;

    if (devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &result, 4) < 0)
        result = 0;

    return result;
}

/* Exported entry #59 */
int sceCdStStart(u32 lsn, sceCdRMode *mode)
{
    int result;
    char devctl_req[0x18];

    memset(&devctl_req, 0, 0x18);

    ((u8 *)devctl_req)[0x12] = mode->datapattern;
    ((u8 *)devctl_req)[0x11] = mode->spindlctrl;
    ((int *)devctl_req)[0x03] = STM0_MODE_START;
    ((int *)devctl_req)[0x00] = lsn;
    ((u8 *)devctl_req)[0x10] = mode->trycount;

    if (devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &result, 4) < 0)
        result = 0;

    return result;
}

/* Exported entry #60 */
int sceCdStStat()
{
    int result;
    char devctl_req[0x18];

    memset(&devctl_req, 0, 0x18);

    ((int *)devctl_req)[0x03] = STM0_MODE_STAT;

    if (devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &result, 4) < 0)
        result = 0;

    return result;
}

/* Exported entry #61 */
int sceCdStStop()
{
    int result;
    char devctl_req[0x18];

    memset(&devctl_req, 0, 0x18);

    ((int *)devctl_req)[0x3] = STM0_MODE_STOP;

    if (devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &result, 4) < 0)
        result = 0;

    return result;
}

/* Exported entry #67 */
int sceCdStPause()
{
    int result;
    char devctl_req[0x18];

    memset(&devctl_req, 0, 0x18);

    ((int *)devctl_req)[0x03] = STM0_MODE_PAUSE;

    if (devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &result, 4) < 0)
        result = 0;

    return result;
}

/* Exported entry #68 */
int sceCdStResume()
{
    int result;
    char devctl_req[0x18];

    memset(&devctl_req, 0, 0x18);

    ((int *)devctl_req)[0x03] = STM0_MODE_RESUME;

    if (devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &result, 4) < 0)
        result = 0;

    return result;
}

/* Exported entry #58 */
int sceCdStSeek(u32 lsn)
{
    int result;
    char devctl_req[0x18];

    memset(&devctl_req, 0, 0x18);

    ((int *)devctl_req)[0x03] = STM0_MODE_SEEK;
    ((int *)devctl_req)[0x00] = lsn;

    if (devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &result, 4) < 0)
        result = 0;

    return result;
}

/* Exported entry #57 */
int sceCdStRead(u32 size, u32 *buf, u32 mode, u32 *err)
{
    int result;
    char devctl_req[0x18];

    memset(&devctl_req, 0, 0x18);

    ((int *)devctl_req)[0x03] = 1;
    ((int *)devctl_req)[0x01] = size;
    ((int *)devctl_req)[0x02] = (int)buf;

    if (devctl(cdvdman_stmdev, CDIOC_CDSTREAD0, &devctl_req, 0x18, &result, 4) < 0) {
        *err = ((u32 *)devctl_req)[0x5];
        result = 0;
    }

    return result;
}

/* Exported entry #77 */
int sceCdStSeekF(u32 lsn)
{
    int result;
    char devctl_req[0x18];

    memset(&devctl_req, 0, 0x18);

    ((int *)devctl_req)[0x3] = STM0_MODE_SEEKF;
    ((int *)devctl_req)[0x0] = lsn;

    if (devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &result, 4) < 0)
        result = 0;

    return result;
}
