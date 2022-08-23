
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct named_charset* new_named_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	char* name,
	struct charset* charset)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct named_charset* this = arena_malloc(arena, sizeof(*this));
	#else
	struct named_charset* this = malloc(sizeof(*this));
	#endif
	
	this->name = name;
	this->charset = charset;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	dpvs(this->name);
	dpv(this->charset);
	
	EXIT;
	return this;
}

