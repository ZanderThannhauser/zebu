
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct named_grammar* new_named_grammar(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	char* name,
	struct gegex* grammar)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct named_grammar* this = arena_malloc(arena, sizeof(*this));
	#else
	struct named_grammar* this = malloc(sizeof(*this));
	#endif
	
	this->name = name;
	this->grammar = grammar;
	
	dpvs(this->name);
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

