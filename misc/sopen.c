
#if 0
#include <debug.h>

#include "sopen.h"

int sopen(const char *pathname, int flags)
{
	int fd = open(pathname, flags);
	
	if (fd < 0)
	{
		TODO;
	}
	
	return fd;
}

#endif
