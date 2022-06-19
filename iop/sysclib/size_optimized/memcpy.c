#define SYSCLIB_DISABLE_BUILTINS
#include <sysclib.h>

void *memcpy(void *dest, const void *src, size_t size)
{
	void *result;

	result = 0;
	if (dest)
	{
		if ((((u8)((((u32)dest) & 0xff) | (((u32)src) & 0xff)) | (u8)size) & 3) != 0)
		{
			u8 *i;

			for (i = dest; size > 0; i += 1)
			{
				char v5;

				v5 = *(u8 *)src;
				src = (char *)src + 1;
				size -= 1;
				*i = v5;
			}
			return dest;
		}
		else
		{
			return _wmemcopy((u32 *)dest, (const u32 *)src, size);
		}
	}
	return result;
}
