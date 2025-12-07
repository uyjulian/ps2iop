
#include "irx_imports.h"
#include "modload.h"

void GetModloadInternalData(void **pInternalData) {
	// FIXME: stub
}

int ReBootStart(const char *command, unsigned int flags) {
	// FIXME: stub
	return 0;
}

int LoadModuleAddress(const char *name, void *addr, int offset) {
	// FIXME: stub
	return 0;
}

int LoadModule(const char *name) {
	// FIXME: stub
	return 0;
}

int LoadStartModule(const char *name, int arglen, const char *args, int *result) {
	// FIXME: stub
	return 0;
}

int StartModule(int x, const char *name, int arglen, const char *args, int *result) {
	// FIXME: stub
	return 0;
}

int LoadModuleBufferAddress(void *buffer, void *addr, int offset) {
	// FIXME: stub
	return 0;
}

int LoadModuleBuffer(void *buffer) {
	// FIXME: stub
	return 0;
}

void SetSecrmanCallbacks(SecrCardBootFile_callback_t SecrCardBootFile_fnc, SecrDiskBootFile_callback_t SecrDiskBootFile_fnc, SetLoadfileCallbacks_callback_t SetLoadfileCallbacks_fnc) {
	// FIXME: stub
}

void SetCheckKelfPathCallback(CheckKelfPath_callback_t CheckKelfPath_fnc) {
	// FIXME: stub
}

