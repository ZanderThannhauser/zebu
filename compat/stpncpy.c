
#ifdef WINDOWS_PLATFORM

#include <string.h>

#include "stpncpy.h"

char *stpncpy(char *dest, const char *src, size_t n)
{
	size_t len = strnlen(src, n);
	
	memcpy(dest, src, len);
	
	dest[len] = 0;
	
	return dest + len;
}

#endif

