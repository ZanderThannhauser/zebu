
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <debug.h>

#include "sasprintf.h"

char* sasprintf(const char* fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	
	char* retval;
	
	if (vasprintf(&retval, fmt, ap) < 0)
	{
		TODO;
	}
	
	va_end(ap);
	return retval;
}

