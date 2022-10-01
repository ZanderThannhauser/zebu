
#ifdef WINDOWS_PLATFORM

#include <stdlib.h>
#include <string.h>

#include "strndup.h"

char* strndup(const char * a, size_t b)
{
	size_t len = strnlen(a, b);
	char* copy = malloc(len + 1);
	memcpy(copy, a, len);
	copy[len] = 0;
	return copy;
}

#endif

