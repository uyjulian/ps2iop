/* cdvdman's additional internal functions (CODE) */

#include "cdvdman-internal.h"

int set_alarm(iop_sys_clock_t *clock, unsigned int (*handler)(void *), void *common)
{
    if (QueryIntrContext())
        return iSetAlarm(clock, handler, common);
    else
        return SetAlarm(clock, handler, common);
}

int cancel_alarm(unsigned int (*handler)(void *), void *common)
{
    if (QueryIntrContext())
        return iCancelAlarm(handler, common);
    else
        return CancelAlarm(handler, common);
}

int clear_ev_flag(int evfid, u32 bitpattern)
{
    if (!QueryIntrContext())
        return ClearEventFlag(evfid, bitpattern);
    else
        return iClearEventFlag(evfid, bitpattern);
}

int set_ev_flag(int evfid, u32 bitpattern)
{
    if (!QueryIntrContext())
        return SetEventFlag(evfid, bitpattern);
    else
        return iSetEventFlag(evfid, bitpattern);
}

int refer_ef_status(int evfid, iop_event_info_t *info)
{
    if (!QueryIntrContext())
        return ReferEventFlagStatus(evfid, info);
    else
        return iReferEventFlagStatus(evfid, info);
}

int delay_thread(u32 usec)
{
    if (QueryIntrContext())
        return 0;
    return DelayThread(usec);
}
