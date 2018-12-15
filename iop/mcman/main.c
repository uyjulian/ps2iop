
#include "irx_imports.h"
#include "mcman.h"

int McDetectCard(int port, int slot) {
	// FIXME: stub
	return 0;
}

int McOpen(int port, int slot, char *filename, int flags) {
	// FIXME: stub
	return 0;
}

int McClose(int fd) {
	// FIXME: stub
	return 0;
}

int McRead(int fd, void *buf, int length) {
	// FIXME: stub
	return 0;
}

int McWrite(int fd, void *buf, int length) {
	// FIXME: stub
	return 0;
}

int McSeek(int fd, int offset, int origin) {
	// FIXME: stub
	return 0;
}

int McFormat(int port, int slot) {
	// FIXME: stub
	return 0;
}

int McGetDir(int port, int slot, char *dirname, int flags, int maxent, sceMcTblGetDir *info) {
	// FIXME: stub
	return 0;
}

int McDelete(int port, int slot, char *filename, int flags) {
	// FIXME: stub
	return 0;
}

int McFlush(int fd) {
	// FIXME: stub
	return 0;
}

int McChDir(int port, int slot, char *newdir, char *currentdir) {
	// FIXME: stub
	return 0;
}

int McSetFileInfo(int port, int slot, char *filename, sceMcTblGetDir *info, int flags) {
	// FIXME: stub
	return 0;
}

int McEraseBlock(int port, int block, void **pagebuf, void *eccbuf) {
	// FIXME: stub
	return 0;
}

int McReadPage(int port, int slot, int page, void *buf) {
	// FIXME: stub
	return 0;
}

int McWritePage(int port, int slot, int page, void *pagebuf, void *eccbuf) {
	// FIXME: stub
	return 0;
}

void McDataChecksum(void *buf, void *ecc) {
	// FIXME: stub
	return;
}

int McGetFormat(int port, int slot) {
	// FIXME: stub
	return 0;
}

int McGetEntSpace(int port, int slot, char *dirname) {
	// FIXME: stub
	return 0;
}

int McReplaceBadBlock(void) {
	// FIXME: stub
	return 0;
}

int McCloseAll(void) {
	// FIXME: stub
	return 0;
}

int McReadPS1PDACard(int port, int slot, int page, void *buf) {
	// FIXME: stub
	return 0;
}

int McWritePS1PDACard(int port, int slot, int page, void *buf) {
	// FIXME: stub
	return 0;
}

int McUnformat(int port, int slot) {
	// FIXME: stub
	return 0;
}

int McRetOnly(int fd) {
	// FIXME: stub
	return 0;
}

int McGetFreeClusters(int port, int slot) {
	// FIXME: stub
	return 0;
}

int McGetMcType(int port, int slot) {
	// FIXME: stub
	return 0;
}

void McSetPS1CardFlag(int flag) {
	// FIXME: stub
	return;
}

struct irx_id *McGetModuleInfo(void) {
	// FIXME: stub
	return NULL;
}
