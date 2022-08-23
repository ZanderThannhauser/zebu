
#include <stdlib.h>
#include <string.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "build_absolute_name.h"

char* scope_build_absolute_name(
	struct scope* this,
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* suffix,
	size_t suffix_strlen)
{
	ENTER;
	
	dpvs(suffix);
	
	#ifdef WITH_ARENAS
	char* full = arena_malloc(arena,
	#else
	char* full = malloc(
	#endif
		this->prefix.n + 1 + 
		suffix_strlen + 1), *m = full;
	
	if (this->prefix.n)
	{
		memcpy(m, this->prefix.chars, this->prefix.n);
		m += this->prefix.n;
		*m++ = '.';
	}
	
	memcpy(m, suffix, suffix_strlen);
	m += suffix_strlen;
	*m++ = '\0';
	
	dpvs(full);
	
	EXIT;
	return full;
}

