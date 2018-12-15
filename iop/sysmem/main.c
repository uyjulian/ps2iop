
#include "irx_imports.h"
#include "sysmem.h"

void * AllocSysMemory(int mode, int size, void *ptr) {
	// FIXME: stub
	return NULL;
}

int FreeSysMemory(void *ptr) {
	// FIXME: stub
	return 0;
}

u32 QueryMemSize() {
	// FIXME: stub
}

u32 QueryMaxFreeMemSize() {
	// FIXME: stub
}

u32 QueryTotalFreeMemSize() {
	// FIXME: stub
}

void * QueryBlockTopAddress(void *address) {
	// FIXME: stub
	return NULL;
}

int QueryBlockSize(void *address) {
	// FIXME: stub
	return 0;
}

int Kprintf(const char *format,...) {
	// FIXME: stub
	return 0;
}

void KprintfSet(KprintfHandler_t * x, void *context) {
	// FIXME: stub
}
