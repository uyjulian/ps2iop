
#include "irx_imports.h"
#include "thbase.h"
#include "thevent.h"
#include "thmsgbx.h"
#include "thpool.h"
#include "thsemap.h"

int CreateThread(iop_thread_t *thread) {
	// FIXME: stub
	return 0;
}

int DeleteThread(int thid) {
	// FIXME: stub
	return 0;
}

int StartThread(int thid, void *arg) {
	// FIXME: stub
	return 0;
}

int StartThreadArgs(int thid, int args, void *argp) {
	// FIXME: stub
	return 0;
}

int ExitThread() {
	// FIXME: stub
	return 0;
}

int ExitDeleteThread() {
	// FIXME: stub
	return 0;
}

int TerminateThread(int thid) {
	// FIXME: stub
	return 0;
}

int iTerminateThread(int thid) {
	// FIXME: stub
	return 0;
}

int ChangeThreadPriority(int thid, int priority) {
	// FIXME: stub
	return 0;
}

int iChangeThreadPriority(int thid, int priority) {
	// FIXME: stub
	return 0;
}

int RotateThreadReadyQueue(int priority) {
	// FIXME: stub
	return 0;
}

int iRotateThreadReadyQueue(int priority) {
	// FIXME: stub
	return 0;
}

int ReleaseWaitThread(int thid) {
	// FIXME: stub
	return 0;
}

int iReleaseWaitThread(int thid) {
	// FIXME: stub
	return 0;
}

int GetThreadId(void) {
	// FIXME: stub
	return 0;
}

int CheckThreadStack(void) {
	// FIXME: stub
	return 0;
}

int ReferThreadStatus(int thid, iop_thread_info_t *info) {
	// FIXME: stub
	return 0;
}

int iReferThreadStatus(int thid, iop_thread_info_t *info) {
	// FIXME: stub
	return 0;
}

int SleepThread(void) {
	// FIXME: stub
	return 0;
}

int WakeupThread(int thid) {
	// FIXME: stub
	return 0;
}

int iWakeupThread(int thid) {
	// FIXME: stub
	return 0;
}

int CancelWakeupThread(int thid) {
	// FIXME: stub
	return 0;
}

int iCancelWakeupThread(int thid) {
	// FIXME: stub
	return 0;
}

int DelayThread(int usec) {
	// FIXME: stub
	return 0;
}

int GetSystemTime(iop_sys_clock_t *sys_clock) {
	// FIXME: stub
	return 0;
}

int SetAlarm(iop_sys_clock_t *sys_clock, unsigned int (*alarm_cb)(void *), void *arg) {
	// FIXME: stub
	return 0;
}

int iSetAlarm(iop_sys_clock_t *sys_clock, unsigned int (*alarm_cb)(void *), void *arg) {
	// FIXME: stub
	return 0;
}

int CancelAlarm(unsigned int (*alarm_cb)(void *), void *arg) {
	// FIXME: stub
	return 0;
}

int iCancelAlarm(unsigned int (*alarm_cb)(void *), void *arg) {
	// FIXME: stub
	return 0;
}

void USec2SysClock(u32 usec, iop_sys_clock_t *sys_clock) {
	// FIXME: stub
}

void SysClock2USec(iop_sys_clock_t *sys_clock, u32 *sec, u32 *usec) {
	// FIXME: stub
}

int GetSystemStatusFlag() {
	// FIXME: stub
	return 0;
}

int CreateEventFlag(iop_event_t *event) {
	// FIXME: stub
	return 0;
}

int DeleteEventFlag(int ef) {
	// FIXME: stub
	return 0;
}

int SetEventFlag(int ef, u32 bits) {
	// FIXME: stub
	return 0;
}

int iSetEventFlag(int ef, u32 bits) {
	// FIXME: stub
	return 0;
}

int ClearEventFlag(int ef, u32 bits) {
	// FIXME: stub
	return 0;
}

int iClearEventFlag(int ef, u32 bits) {
	// FIXME: stub
	return 0;
}

int WaitEventFlag(int ef, u32 bits, int mode, u32 *resbits) {
	// FIXME: stub
	return 0;
}

int PollEventFlag(int ef, u32 bits, int mode, u32 *resbits) {
	// FIXME: stub
	return 0;
}

int ReferEventFlagStatus(int ef, iop_event_info_t* info) {
	// FIXME: stub
	return 0;
}

int iReferEventFlagStatus(int ef, iop_event_info_t* info) {
	// FIXME: stub
	return 0;
}

int CreateSema(iop_sema_t *sema) {
	// FIXME: stub
	return 0;
}

int DeleteSema(int semid) {
	// FIXME: stub
	return 0;
}

int SignalSema(int semid) {
	// FIXME: stub
	return 0;
}

int iSignalSema(int semid) {
	// FIXME: stub
	return 0;
}

int WaitSema(int semid) {
	// FIXME: stub
	return 0;
}

int PollSema(int semid) {
	// FIXME: stub
	return 0;
}

int ReferSemaStatus(int semid, iop_sema_info_t *info) {
	// FIXME: stub
	return 0;
}

int iReferSemaStatus(int semid, iop_sema_info_t *info) {
	// FIXME: stub
	return 0;
}

int CreateMbx(iop_mbx_t *mbx) {
	// FIXME: stub
	return 0;
}

int DeleteMbx(int mbxid) {
	// FIXME: stub
	return 0;
}

int SendMbx(int mbxid, void *msg) {
	// FIXME: stub
	return 0;
}

int iSendMbx(int mbxid, void *msg) {
	// FIXME: stub
	return 0;
}

int ReceiveMbx(void **msgvar, int mbxid) {
	// FIXME: stub
	return 0;
}

int PollMbx(void **msgvar, int mbxid) {
	// FIXME: stub
	return 0;
}

int ReferMbxStatus(int mbxid, iop_mbx_status_t *info) {
	// FIXME: stub
	return 0;
}

int iReferMbxStatus(int mbxid, iop_mbx_status_t *info) {
	// FIXME: stub
	return 0;
}

int CreateFpl(iop_fpl_param *param) {
	// FIXME: stub
	return 0;
}

int DeleteFpl(int fplId) {
	// FIXME: stub
	return 0;
}

void *AllocateFpl(int fplId) {
	// FIXME: stub
	return NULL;
}

void *pAllocateFpl(int fplId) {
	// FIXME: stub
	return NULL;
}

void *ipAllocateFpl(int fplId) {
	// FIXME: stub
	return NULL;
}

int FreeFpl(int fplId, void *memory) {
	// FIXME: stub
	return 0;
}

int ReferFplStatus(int fplId, iop_fpl_info_t *info) {
	// FIXME: stub
	return 0;
}

int iReferFplStatus(int fplId, iop_fpl_info_t *info) {
	// FIXME: stub
	return 0;
}

int CreateVpl(iop_vpl_param *param) {
	// FIXME: stub
	return 0;
}

int DeleteVpl(int vplId) {
	// FIXME: stub
	return 0;
}

void *AllocateVpl(int vplId, int size) {
	// FIXME: stub
	return NULL;
}

void *pAllocateVpl(int vplId, int size) {
	// FIXME: stub
	return NULL;
}

void *ipAllocateVpl(int vplId, int size) {
	// FIXME: stub
	return NULL;
}

int FreeVpl(int vplId, void *memory) {
	// FIXME: stub
	return 0;
}

int ReferVplStatus(int vplId, iop_vpl_info_t *info) {
	// FIXME: stub
	return 0;
}

int iReferVplStatus(int vplId, iop_vpl_info_t *info) {
	// FIXME: stub
	return 0;
}
