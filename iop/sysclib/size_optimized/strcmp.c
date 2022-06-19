#define SYSCLIB_DISABLE_BUILTINS
#include <sysclib.h>

int strcmp(const char *p, const char *q)
{
	int result;

	if (p && q)
	{
		while (1)
		{
			int v3;
			int v4;

			v3 = *q;
			v4 = *(u8 *)p;
			q += 1;
			if (*p != v3)
			{
				break;
			}
			p += 1;
			if (!v4)
			{
				return 0;
			}
		}
		return *p - *(q - 1);
	}
	else
	{
		result = 0;
		if (p != q)
		{
			result = -1;
			if (p)
			{
				return 1;
			}
		}
	}
	return result;
}
