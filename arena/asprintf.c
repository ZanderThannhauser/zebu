
#ifdef WITH_ARENAS

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>

#include <debug.h>

#include "realloc.h"
#include "asprintf.h"

char* arena_asprintf(
	struct memory_arena* this,
	const char* fmt, ...)
{
	ENTER;
	
	dpvs(fmt);
	
	char* buffer = NULL;
	size_t n = 0, cap = 0;
	
	ssize_t write(void *_, const char *buf, size_t size)
	{
		ENTER;
		
		dpvsn(buf, size);
		
		while (n + size > cap)
		{
			cap = cap << 1 ?: 1;
			
			buffer = arena_realloc(this, buffer, cap);
		}
		
		memcpy(buffer + n, buf, size);
		
		n += size;
		
		EXIT;
		return size;
	}
	
	FILE *stream = fopencookie(NULL, "w", (cookie_io_functions_t) {.write = write});
	
	va_list ap;
	
	va_start(ap, fmt);
	
	vfprintf(stream, fmt, ap);
	
	fclose(stream);
	
	write(NULL, "", 1);
	
	dpvs(buffer);
	
	va_end(ap);
	
	EXIT;
	return buffer;
}









#endif
