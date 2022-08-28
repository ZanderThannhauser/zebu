
#include <stdlib.h>

#include <string.h>

#include <debug.h>

#include "../struct.h"

#include "append_prefix.h"

static void append_prefix(struct scope* this, const char* appendme)
{
	ENTER;
	
	TODO;
	#if 0
	dpvs(appendme);
	
	size_t len = strlen(appendme);
	
	while (this->prefix.n + len > this->prefix.cap)
	{
		this->prefix.cap = this->prefix.cap << 1 ?: 1;
		
		dpv(this->prefix.cap);
		
		#ifdef WITH_ARENAS
		this->prefix.chars = arena_realloc(this->arena, this->prefix.chars, this->prefix.cap);
		#else
		this->prefix.chars = realloc(this->prefix.chars, this->prefix.cap);
		#endif
	}
	
	memcpy(this->prefix.chars + this->prefix.n, appendme, len);
	
	this->prefix.n += len;
	#endif
	
	EXIT;
}

void private_scope_append_prefix(struct scope* this, const char* appendme)
{
	ENTER;
	
	TODO;
	#if 0
	if (this->prefix.n)
	{
		append_prefix(this, ".");
	}
	
	append_prefix(this, appendme);
	#endif
	
	EXIT;
}
