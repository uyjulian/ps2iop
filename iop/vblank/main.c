
#include "irx_imports.h"
#include "vblank.h"

void WaitVblankStart() {
	// FIXME: stub
}

void WaitVblankEnd() {
	// FIXME: stub
}

void WaitVblank() {
	// FIXME: stub
}

void WaitNonVblank() {
	// FIXME: stub
}

int RegisterVblankHandler(int startend, int priority, int (*handler)(void *), void *arg) {
	// FIXME: stub
	return 0;
}

int ReleaseVblankHandler(int startend, int (*handler)(void *)) {
	// FIXME: stub
	return 0;
}
