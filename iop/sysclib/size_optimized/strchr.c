#define SYSCLIB_DISABLE_BUILTINS
#include <sysclib.h>

char *strchr(const char *s, int c)
{

	if (!s)
	{
		return 0;
	}
	while (1)
	{
		int v2;

		v2 = *s;
		if (v2 == (char)c)
		{
			break;
		}
		s += 1;
		if (!v2)
		{
			return 0;
		}
	}
	return (char *)s;
}
