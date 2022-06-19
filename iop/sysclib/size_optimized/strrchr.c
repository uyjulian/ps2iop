#define SYSCLIB_DISABLE_BUILTINS
#include <sysclib.h>

char *strrchr(const char *s, int c)
{
	const char *v2;
	const char *i;
	char *result;

	v2 = s;
	if (!s)
	{
		return 0;
	}
	while (*s++) {}
	for (i = s - 1; ; i -= 1)
	{
		result = (char *)i;
		if (*i == (char)c)
		{
			break;
		}
		if (v2 >= i)
		{
			return 0;
		}
	}
	return result;
}
