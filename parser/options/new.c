
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct options* new_options(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct options* this = arena_malloc(arena, sizeof(*this));
	#else
	struct options* this = malloc(sizeof(*this));
	#endif
	
	this->skip = NULL;
	this->token_skip = NULL;
	
	this->disambiguatations.head = NULL;
	this->disambiguatations.tail = NULL;
	
	EXIT;
	return this;
}

