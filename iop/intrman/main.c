//TODO: need 1-3, 10-13, 19-22, 26-31

#include "irx_imports.h"
#include "intrman.h"

int RegisterIntrHandler(int irq, int mode, int (*handler)(void *), void *arg) {
	// FIXME: stub
	return 0;
}

int ReleaseIntrHandler(int irq) {
	// FIXME: stub
	return 0;
}

int EnableIntr(int irq) {
	// FIXME: stub
	return 0;
}

int DisableIntr(int irq, int *res) {
	// FIXME: stub
	return 0;
}

int CpuDisableIntr() {
	// FIXME: stub
	return 0;
}

int CpuEnableIntr() {
	// FIXME: stub
	return 0;
}

int CpuInvokeInKmode(void *function, ...) {
	// FIXME: stub
	return 0;
}

void DisableDispatchIntr(int irq) {
	// FIXME: stub
	return;
}

void EnableDispatchIntr(int irq) {
	// FIXME: stub
	return;
}

int CpuSuspendIntr(int *state) {
	// FIXME: stub
	return 0;
}

int CpuResumeIntr(int state) {
	// FIXME: stub
	return 0;
}

int QueryIntrContext(void) {
	// FIXME: stub
	return 0;
}

int QueryIntrStack(void) {
	// FIXME: stub
	return 0;
}

int iCatchMultiIntr(void) {
	// FIXME: stub
	return 0;
}
