
#include "irx_imports.h"
#include "excepman.h"

int RegisterExceptionHandler(int exception, exception_handler_t handlr) {
	// FIXME: stub
	return 0;
}

int RegisterPriorityExceptionHandler(int exception, int priority, exception_handler_t handlr) {
	// FIXME: stub
	return 0;
}

int RegisterDefaultExceptionHandler(exception_handler_t handlr) {
	// FIXME: stub
	return 0;
}

int ReleaseExceptionHandler(int exception, exception_handler_t handlr) {
	// FIXME: stub
	return 0;
}

int ReleaseDefaultExceptionHandler(exception_handler_t handlr) {
	// FIXME: stub
	return 0;
}
