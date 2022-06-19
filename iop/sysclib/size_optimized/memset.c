#define SYSCLIB_DISABLE_BUILTINS
#include <sysclib.h>

void *memset(void *ptr, int c, size_t size)
{
	u8 *i;

	if (ptr)
	{
		if (!c && (((((u32)ptr) & 0xff) | (u8)size) & 3) == 0)
		{
			return _wmemset((u32 *)ptr, 0, size);
		}
		for (i = ptr; size > 0; i += 1)
		{
			*i = c;
			size -= 1;
		}
	}
	return ptr;
}
