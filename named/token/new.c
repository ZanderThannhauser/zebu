
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct named_token* new_named_token(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	char* name,
	struct regex* token)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct named_token* this = arena_malloc(arena, sizeof(*this));
	#else
	struct named_token* this = malloc(sizeof(*this));
	#endif
	
	this->name = name;
	this->token = token;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	dpvs(this->name);
	dpv(this->token);
	
	EXIT;
	return this;
}

