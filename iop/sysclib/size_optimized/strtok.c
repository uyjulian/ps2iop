#define SYSCLIB_DISABLE_BUILTINS
#include <sysclib.h>

char *strtok(char *s, const char *delim)
{
	static char *strtok_lasts_unused;
	return strtok_r(s, delim, &strtok_lasts_unused);
}
