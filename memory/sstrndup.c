
#include <debug.h>

#include "sstrndup.h"

char* sstrndup(const char* src, size_t len)
{
	char* out = strndup(src, len);
	
	if (!out)
	{
		fprintf(stderr, "%s: strndup(): %m\n", argv0),
		exit(e_out_of_memory);
	}
	
	return out;
}

