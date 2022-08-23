
#include <stdlib.h>

#include <arena/malloc.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct named_tokenset* new_named_tokenset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* name, struct tokenset* tokenset)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct named_tokenset* this = arena_malloc(arena, sizeof(*this));
	#else
	struct named_tokenset* this = malloc(sizeof(*this));
	#endif
	
	this->name = name;
	this->tokenset = tokenset;
	
	EXIT;
	return this;
}

