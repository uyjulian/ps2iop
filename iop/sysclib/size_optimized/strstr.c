#define SYSCLIB_DISABLE_BUILTINS
#include <sysclib.h>

char *strstr(const char *haystack, const char *needle)
{
	const char *i;
	int v4;
	const char *v5;

	if (!*needle)
	{
		return (char *)haystack;
	}
LABEL_10:
	v5 = haystack;
	if (*haystack)
	{
		for (i = needle; *i; i += 1)
		{
			v4 = *v5;
			if (!*v5)
			{
				return 0;
			}
			v5 += 1;
			if (v4 != *i)
			{
				haystack += 1;
				goto LABEL_10;
			}
		}
		return (char *)haystack;
	}
	return 0;
}
