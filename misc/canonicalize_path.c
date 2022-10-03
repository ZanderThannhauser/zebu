
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include <string.h>

#include <debug.h>

#include <macros/strequals.h>

#include <memory/srealloc.h>

#ifdef WINDOWS_PLATFORM
#include <compat/rindex.h>
#endif

#include "canonicalize_path.h"

char* canonicalize_path(const char* ro_in)
{
	ENTER;
	
	struct {
		char* data;
		unsigned n, cap;
	} out = {};
	
	void append(const char* str)
	{
		ENTER;
		
		unsigned len = strlen(str);
		
		while (out.n + len >= out.cap)
		{
			out.cap = out.cap << 1 ?: 1;
			out.data = srealloc(out.data, out.cap);
		}
		
		strcpy(out.data + out.n, str);
		out.n += len;
		
		EXIT;
	}
	
	append("");
	
	dpvs(ro_in);
	
	bool absolute_path = (ro_in[0] == '/');
	unsigned negative = 0;
	
	char* in = strdup(ro_in);
	char *arg, *moving = in;
	while ((arg = strtok_r(NULL, "/", &moving)))
	{
		dpvs(out.data);
		dpvs(arg);
		
		if (strequals(arg, "."))
		{
			;
		}
		else if (strequals(arg, ".."))
		{
			if (out.n)
			{
				char* slash = rindex(out.data, '/') ?: out.data;
				out.n = slash - out.data;
				out.data[out.n] = '\0';
			}
			else
			{
				TODO;
			}
		}
		else
		{
			if (out.n)
				append("/");
			append(arg);
		}
	}

	dpvs(out.data);
	
	if (absolute_path)
	{
		append(" ");
		memmove(out.data + 1, out.data, out.n - 1);
		out.data[0] = '/';
	}
	else if (negative)
	{
		TODO;
	}
	
	dpvs(out.data);
	
	free(in);
	
	EXIT;
	return out.data;
}










