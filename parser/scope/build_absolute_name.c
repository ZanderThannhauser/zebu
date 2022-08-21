
#include <debug.h>

/*#include <memory/arena/malloc.h>*/

#include "struct.h"
#include "build_absolute_name.h"

char* scope_build_absolute_name(
	struct scope* this,
	struct memory_arena* arena,
	const char* suffix,
	size_t suffix_strlen)
{
	ENTER;
	
	TODO;
	#if 0
	dpvs(suffix);
	
	char* full = arena_malloc(
		arena,
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
	#endif
}

