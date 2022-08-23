
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct named_gbundle* new_named_gbundle(
	struct memory_arena* arena,
	char* name,
	struct gegex* start,
	struct gegex* end)
{
	ENTER;
	
	struct named_gbundle* this = arena_malloc(arena, sizeof(*this));
	
	this->name = name;
	this->start = start;
	this->end = end;
	
	dpvs(this->name);
	
	EXIT;
	return this;
}

