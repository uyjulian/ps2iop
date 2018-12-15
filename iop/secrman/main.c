
#include "irx_imports.h"
#include "secrman.h"

void SecrSetMcCommandHandler(McCommandHandler_t handler) {
	// FIXME: stub
}

void SecrSetMcDevIDHandler(McDevIDHandler_t handler) {
	// FIXME: stub

}

int SecrAuthCard(int port, int slot, int cnum) {
	// FIXME: stub
	return 0;
}

void SecrResetAuthCard(int port, int slot, int cnum) {
	// FIXME: stub
}

int SecrCardBootHeader(int port, int slot, void *buffer, SecrBitTable_t *BitTable, s32 *pSize) {
	// FIXME: stub
	return 0;
}

int SecrCardBootBlock(void *src, void *dst, unsigned int size) {
	// FIXME: stub
	return 0;
}

void *SecrCardBootFile(int port, int slot, void *buffer) {
	// FIXME: stub
	return NULL;
}

int SecrDiskBootHeader(void *buffer, SecrBitTable_t *BitTable, s32 *pSize) {
	// FIXME: stub
	return 0;
}

int SecrDiskBootBlock(void *src, void *dst, unsigned int size) {
	// FIXME: stub
	return 0;
}

void *SecrDiskBootFile(void *buffer) {
	// FIXME: stub
}
