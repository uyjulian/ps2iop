
#include "irx_imports.h"
#include "cdvdman.h"

int sceCdInit(int mode) {
	//FIXME: stub
	return 0;
}

int sceCdStandby(void) {
	//FIXME: stub
	return 0;
}

int sceCdRead(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode) {
	//FIXME: stub
	return 0;
}

int sceCdSeek(u32 lbn) {
	//FIXME: stub
	return 0;
}

int sceCdGetError(void) {
	//FIXME: stub
	return 0;
}

int sceCdGetToc(u8 *toc) {
	//FIXME: stub
	return 0;
}

int sceCdSearchFile(sceCdlFILE *file, const char *name) {
	//FIXME: stub
	return 0;
}

int sceCdSync(int mode) {
	//FIXME: stub
	return 0;
}

int sceCdGetDiskType(void) {
	//FIXME: stub
	return 0;
}

int sceCdDiskReady(int mode) {
	//FIXME: stub
	return 0;
}

int sceCdTrayReq(int param, u32 *traychk) {
	//FIXME: stub
	return 0;
}

int sceCdStop(void) {
	//FIXME: stub
	return 0;
}

u32 sceCdPosToInt(sceCdlLOCCD *p) {
	//FIXME: stub
	return 0;
}

sceCdlLOCCD *sceCdIntToPos(u32 i, sceCdlLOCCD *p) {
	//FIXME: stub
	return NULL;
}

//18

//sceCdGetToc2

int sceCdReadDVDV(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode) {
	//FIXME: stub
	return 0;
}

int sceCdCheckCmd(void) {
	//FIXME: stub
	return 0;
}

int sceCdRI(u8 *buffer, u32 *result) {
	//FIXME: stub
	return 0;
}

int sceCdWI(const u8 *buffer, u32 *result) {
	//FIXME: stub
	return 0;
}

int sceCdReadClock(sceCdCLOCK *clock) {
	//FIXME: stub
	return 0;
}

int sceCdWriteClock(sceCdCLOCK *clock) {
	//FIXME: stub
	return 0;
}

//26, 27

int sceCdStatus(void) {
	//FIXME: stub
	return 0;
}

int sceCdApplySCmd(u8 cmdNum, const void* inBuff, u16 inBuffSize, void *outBuff) {
	//FIXME: stub
	return 0;
}

int sceCdSetHDMode(u32 mode) {
	//FIXME: stub
	return 0;
}

int sceCdOpenConfig(int block, int mode, int NumBlocks, u32 *status) {
	//FIXME: stub
	return 0;
}

int sceCdCloseConfig(u32 *result) {
	//FIXME: stub
	return 0;
}

int sceCdReadConfig(void *buffer, u32 *result) {
	//FIXME: stub
	return 0;
}

int sceCdWriteConfig(const void *buffer, u32 *result) {
	//FIXME: stub
	return 0;
}

int sceCdReadKey(unsigned char arg1, unsigned char arg2, unsigned int command, unsigned char *key) {
	//FIXME: stub
	return 0;
}

int sceCdDecSet(unsigned char arg1, unsigned char arg2, unsigned char shift) {
	//FIXME: stub
	return 0;
}

sceCdCBFunc sceCdCallback(sceCdCBFunc function) {
	//FIXME: stub
	return NULL;
}

int sceCdPause(void) {
	//FIXME: stub
	return 0;
}

int sceCdBreak(void) {
	//FIXME: stub
	return 0;
}

int sceCdReadCDDA(u32 lbn, u32 sectors, void *buffer, sceCdRMode *mode) {
	//FIXME: stub
	return 0;
}

int sceCdReadConsoleID(u8 *buffer, u32 *result) {
	//FIXME: stub
	return 0;
}

int sceCdWriteConsoleID(const u8 *buffer, u32 *status) {
	//FIXME: stub
	return 0;
}

int sceCdMV(u8 *buffer, u32 *status) {
	//FIXME: stub
	return 0;
}

u32 sceCdGetReadPos(void) {
	//FIXME: stub
	return 0;
}

int sceCdCtrlADout(int arg1, u32 *status) {
	//FIXME: stub
	return 0;
}

int sceCdNop(void) {
	//FIXME: stub
	return 0;
}

void *sceGetFsvRbuf(void) {
	//FIXME: stub
	return NULL;
}

int sceCdstm0Cb(void (*p)(int)) {
	//FIXME: stub
	return 0;
}

int sceCdstm1Cb(void (*p)(int)) {
	//FIXME: stub
	return 0;
}

int sceCdSC(int code, int *param) {
	//FIXME: stub
	return 0;
}

int sceCdRC(sceCdCLOCK *clock) {
	//FIXME: stub
	return 0;
}

int sceCdForbidDVDP(u32 *result) {
	//FIXME: stub
	return 0;
}

int sceCdReadSUBQ(void *buffer, u32 *status) {
	//FIXME: stub
	return 0;
}

int sceCdApplyNCmd(u8 cmdNum, const void* inBuff, u16 inBuffSize) {
	//FIXME: stub
	return 0;
}

int sceCdAutoAdjustCtrl(int mode, u32 *result) {
	//FIXME: stub
	return 0;
}

int sceCdStInit(u32 bufmax, u32 bankmax, void *buffer) {
	//FIXME: stub
	return 0;
}

int sceCdStRead(u32 sectors, u32 *buffer, u32 mode, u32 *error) {
	//FIXME: stub
	return 0;
}

int sceCdStSeek(u32 lbn) {
	//FIXME: stub
	return 0;
}

int sceCdStStart(u32 lbn, sceCdRMode *mode) {
	//FIXME: stub
	return 0;
}

int sceCdStStat(void) {
	//FIXME: stub
	return 0;
}

int sceCdStStop(void) {
	//FIXME: stub
	return 0;
}
