
#ifdef WINDOWS_PLATFORM

#include <string.h>

#include "rindex.h"

char *rindex(const char *s, int c)
{
	const char *e = s + strlen(s);
	
	while (s < e)
	{
		if (*e == c)
			return (char*) e;
		e--;
	}
	
	return NULL;
}

#endif

