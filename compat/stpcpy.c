
#ifdef WINDOWS_PLATFORM

#include <string.h>

#include "stpcpy.h"

char *stpcpy(char *dest, const char *src)
{
	size_t len = strlen(src);
	
	memcpy(dest, src, len);
	
	dest[len] = 0;
	
	return dest + len;
}

#endif

