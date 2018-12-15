
#include "irx_imports.h"
#include "modload.h"

void *GetModloadInternalData(void **pInternalData) {
	// FIXME: stub
	return NULL;
}

int ReBootStart(const char *command, unsigned int flags) {
	// FIXME: stub
	return 0;
}

int LoadModuleAddress(const char *name, int x, int y) {
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

int LoadModuleBufferAddress(void *buffer, int x, int y) {
	// FIXME: stub
	return 0;
}

int LoadModuleBuffer(void *buffer) {
	// FIXME: stub
	return 0;
}

void SetSecrmanCallbacks(void *SecrCardBootFile_fnc, void *SecrDiskBootFile_fnc, void *SetLoadfileCallbacks_fnc) {
	// FIXME: stub
}

void SetCheckKelfPathCallback(void *CheckKelfPath_fnc) {
	// FIXME: stub
}

