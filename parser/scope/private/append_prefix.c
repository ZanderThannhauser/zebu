
#include <stdlib.h>

#include <string.h>

#include <debug.h>

#include "../struct.h"

#include "append_prefix.h"

static void append_prefix(struct scope* this, const char* appendme)
{
	ENTER;
	
	dpvs(appendme);
	
	size_t len = strlen(appendme);
	
	while (this->prefix.n + len > this->prefix.cap)
	{
		this->prefix.cap = this->prefix.cap << 1 ?: 1;
		
		dpv(this->prefix.cap);
		
		this->prefix.chars = srealloc(this->prefix.chars, this->prefix.cap);
	}
	
	memcpy(this->prefix.chars + this->prefix.n, appendme, len);
	
	this->prefix.n += len;
	
	EXIT;
}

void private_scope_append_prefix(struct scope* this, const char* appendme)
{
	ENTER;
	
	if (this->prefix.n)
	{
		append_prefix(this, "$");
	}
	
	append_prefix(this, appendme);
	
	EXIT;
}










