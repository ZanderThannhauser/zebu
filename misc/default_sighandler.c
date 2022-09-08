
#ifdef VERBOSE

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "default_sighandler.h"

void default_sighandler(int _)
{
	char ptr[100] = {};
	
	size_t len = snprintf(ptr, 100, "\e[K" "zebu: \r");
	
	if (write(1, ptr, len) != len)
	{
		abort();
	}
}

#endif
