
#include "irx_imports.h"
#include "xpadman.h"

s32 padInit(void * ee_addr) {
	// FIXME: stub
	return 0;
}

s32 padEnd() {
	// FIXME: stub
	return 0;
}

s32 padPortOpen(s32 port, s32 slot, s32 pad_area_ee_addr, u32 *buf) {
	// FIXME: stub
	return 0;
}

s32 padPortClose(s32 port, s32 slot, s32 wait) {
	// FIXME: stub
	return 0;
}

u32 padGetInBuffer(u32 port, u32 slot, u8 *buf) {
	// FIXME: stub
	return 0;
}

u32 padSetupEEButtonData(u32 port, u32 slot, void *pstate) {
	// FIXME: stub
	return 0;
}

u32 padGetModeConfig(u32 port, u32 slot) {
	// FIXME: stub
	return 0;
}

s32 padInfoAct(u32 port, u32 slot, s32 act, u32 val) {
	// FIXME: stub
	return 0;
}

s32 padInfoComb(u32 port, u32 slot, s32 val1, u32 val2) {
	// FIXME: stub
	return 0;
}

s32 padInfoMode(u32 port, u32 slot, s32 val1, u32 val2) {
	// FIXME: stub
	return 0;
}

u32 padSetMainMode(u32 port, u32 slot, u32 mode, u32 lock) {
	// FIXME: stub
	return 0;
}

u32 padSetActDirect(u32 port, u32 slot, u8 *actData) {
	// FIXME: stub
	return 0;
}
