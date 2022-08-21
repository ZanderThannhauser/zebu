
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct options* new_options(
	struct memory_arena* arena)
{
	ENTER;
	
	struct options* this = arena_malloc(arena, sizeof(*this));
	
	this->skip = NULL;
	this->token_skip = NULL;
	
	this->disambiguatations.head = NULL;
	this->disambiguatations.tail = NULL;
	
	EXIT;
	return this;
}

