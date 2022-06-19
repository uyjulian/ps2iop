#define SYSCLIB_DISABLE_BUILTINS
#include <sysclib.h>

void *memchr(const void *s, int c, size_t n)
{
	if (!s || n <= 0)
	{
		return 0;
	}
	while (1)
	{
		n -= 1;
		if (*(u8 *)s == (u8)c)
		{
			break;
		}
		s = (char *)s + 1;
		if (n <= 0)
		{
			return 0;
		}
	}
	return (void *)s;
}
