#define SYSCLIB_DISABLE_BUILTINS
#include <sysclib.h>

void *memmove(void *dest, const void *src, size_t size)
{
	u8 *v3;
	void *result;
	s32 v5;

	v3 = dest;
	if (!dest)
	{
		return 0;
	}
	if (dest < src)
	{
		result = dest;
		if (size > 0)
		{
			char v8;

			do
			{
				v8 = *(u8 *)src;
				src = (u8 *)src + 1;
				size -= 1;
				*v3++ = v8;
			}
			while (size > 0);
			return dest;
		}
	}
	else
	{
		v5 = size - 1;
		result = dest;
		if (v5 >= 0)
		{
			u8 *v6;
			char v7;

			do
			{
				v6 = (u8 *)dest + v5;
				v7 = *((u8 *)src + v5--);
				*v6 = v7;
			}
			while (v5 >= 0);
			return dest;
		}
	}
	return result;
}
