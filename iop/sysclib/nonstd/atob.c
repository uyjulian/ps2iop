#define SYSCLIB_DISABLE_BUILTINS
#include <sysclib.h>

// non-standard function
char *atob(char *s, int *i) {
	char *result;

	*i = strtol(s, &result, 10);
	return result;
}
