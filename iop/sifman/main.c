
#include "irx_imports.h"
#include "sifman.h"

void sceSifDma2Init() {
	// FIXME: stub
}

void sceSifInit() {
	// FIXME: stub
}

void sceSifSetDChain() {
	// FIXME: stub
}

int sceSifSetDma(SifDmaTransfer_t *dmat, int count) {
	// FIXME: stub
	return 0;
}

int sceSifDmaStat(int trid) {
	// FIXME: stub
	return 0;
}

void sceSifSetOneDma(SifDmaTransfer_t dmat) {
	// FIXME: stub
}

void sceSifDma0Transfer(void *addr, int size, int mode) {
	// FIXME: stub
}

void sceSifDma0Sync() {
	// FIXME: stub
}

int sceSifDma0Sending() {
	// FIXME: stub
	return 0;
}

void sceSifDma1Transfer(void *addr, int size, int mode) {
	// FIXME: stub
}

void sceSifDma1Sync() {
	// FIXME: stub
}

int sceSifDma1Sending() {
	// FIXME: stub
	return 0;
}

void sceSifDma2Transfer(void *addr, int size, int mode) {
	// FIXME: stub
}

void sceSifDma2Sync() {
	// FIXME: stub
}

int sceSifDma2Sending() {
	// FIXME: stub
	return 0;
}

u32 sceSifGetMSFlag() {
	// FIXME: stub
	return 0;
}

u32 sceSifSetMSFlag(u32 val) {
	// FIXME: stub
	return 0;
}

u32 sceSifGetSMFlag() {
	// FIXME: stub
	return 0;
}

u32 sceSifSetSMFlag(u32 val) {
	// FIXME: stub
	return 0;
}

u32 sceSifGetMainAddr() {
	// FIXME: stub
	return 0;
}

u32 sceSifGetSubAddr() {
	// FIXME: stub
	return 0;
}

u32 sceSifSetSubAddr(u32 addr) {
	// FIXME: stub
	return 0;
}

void sceSifIntrMain() {
	// FIXME: stub
}

int sceSifCheckInit() {
	// FIXME: stub
	return 0;
}

void sceSifSetDmaIntrHandler(void (*handler)(void *), void *arg) {
	// FIXME: stub
}

void sceSifResetDmaIntrHandler() {
	// FIXME: stub
}

unsigned int sceSifSetDmaIntr(SifDmaTransfer_t *dmat, int count, void (*completioncb)(void *userdata), void *userdata) {
	// FIXME: stub
}


