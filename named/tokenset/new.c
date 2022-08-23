
#include <arena/malloc.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct named_tokenset* new_named_tokenset(
	struct memory_arena* arena,
	const char* name, struct tokenset* tokenset)
{
	ENTER;
	
	struct named_tokenset* this = arena_malloc(arena, sizeof(*this));
	
	this->name = name;
	this->tokenset = tokenset;
	
	EXIT;
	return this;
}

