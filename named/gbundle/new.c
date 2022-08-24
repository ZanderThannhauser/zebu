
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct named_gbundle* new_named_gbundle(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	char* name,
	struct gegex* start,
	struct gegex* end)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct named_gbundle* this = arena_malloc(arena, sizeof(*this));
	#else
	struct named_gbundle* this = malloc(sizeof(*this));
	#endif
	
	this->name = name;
	
	this->start = start;
	
	this->end = end;
	
	dpvs(this->name);
	
	EXIT;
	return this;
}

