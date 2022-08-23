
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct named_token* new_named_token(
	struct memory_arena* arena,
	char* name,
	struct regex* token)
{
	ENTER;
	
	struct named_token* this = arena_malloc(arena, sizeof(*this));
	
	this->name = name;
	this->token = token;
	
	this->arena = arena;
	
	dpvs(this->name);
	dpv(this->token);
	
	EXIT;
	return this;
}

