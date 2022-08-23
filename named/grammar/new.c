
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct named_grammar* new_named_grammar(
	struct memory_arena* arena,
	char* name,
	struct gegex* grammar)
{
	ENTER;
	
	struct named_grammar* this = arena_malloc(arena, sizeof(*this));
	
	this->name = name;
	this->grammar = grammar;
	
	dpvs(this->name);
	
	this->arena = arena;
	
	EXIT;
	return this;
}

