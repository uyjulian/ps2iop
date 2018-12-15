
#include "irx_imports.h"
#include "timrman.h"

int AllocHardTimer(int source, int size, int prescale) {
	// FIXME: stub
	return 0;
}

int ReferHardTimer(int source, int size, int mode, int modemask) {
	// FIXME: stub
	return 0;
}

int FreeHardTimer(int timid) {
	// FIXME: stub
	return 0;
}

void SetTimerMode(int timid, int mode) {
	// FIXME: stub
}

u32 GetTimerStatus(int timid) {
	// FIXME: stub
	return 0;
}

void SetTimerCounter(int timid, u32 count) {
	// FIXME: stub
}

u32 GetTimerCounter(int timid) {
	// FIXME: stub
	return 0;
}

void SetTimerCompare(int timid, u32 compare) {
	// FIXME: stub
}

u32 GetTimerCompare(int timid) {
	// FIXME: stub
	return 0;
}

void SetHoldMode(int holdnum, int mode) {
	// FIXME: stub
}

u32 GetHoldMode(int holdnum) {
	// FIXME: stub
	return 0;
}

u32 GetHoldReg(int holdnum) {
	// FIXME: stub
	return 0;
}

int GetHardTimerIntrCode(int timid) {
	// FIXME: stub
	return 0;
}
