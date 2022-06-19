#define SYSCLIB_DISABLE_BUILTINS
#include <sysclib.h>

size_t strspn(const char *s, const char *accept)
{
	const char *v2;
	const char *v3;
	int v4;

	v2 = s;
	if (*s)
	{
		v3 = accept;
		do
		{
			v4 = *(u8 *)v3 << 24;
			if (!*v3)
			{
				break;
			}
			do
			{
				if (v4 >> 24 == *s)
				{
					break;
				}
				v4 = *(u8 *)++v3 << 24;
			}
			while (*v3);
			if (!*v3)
			{
				break;
			}
			s += 1;
			v3 = accept;
		}
		while (*s);
	}
	return s - v2;
}
