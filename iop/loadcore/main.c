
#include "irx_imports.h"
#include "loadcore.h"

lc_internals_t *GetLoadcoreInternalData(void) {
	// FIXME: stub
	return NULL;
}

void FlushIcache(void) {
	// FIXME: stub
}

void FlushDcache(void) {
	// FIXME: stub
}

int RegisterLibraryEntries(struct irx_export_table *exports) {
	// FIXME: stub
	return 0;
}

int ReleaseLibraryEntries(struct irx_export_table *exports) {
	// FIXME: stub
	return 0;
}

int RegisterNonAutoLinkEntries(struct irx_export_table *exports) {
	// FIXME: stub
	return 0;
}

void *QueryLibraryEntryTable(iop_library_t *library) {
	// FIXME: stub
	return 0;
}

int *QueryBootMode(int mode) {
	// FIXME: stub
	return NULL;
}

void RegisterBootMode(iop_bootmode_t *b) {
	// FIXME: stub
}
