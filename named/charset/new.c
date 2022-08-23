
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct named_charset* new_named_charset(
	struct memory_arena* arena,
	char* name,
	struct charset* charset)
{
	ENTER;
	
	struct named_charset* this = arena_malloc(arena, sizeof(*this));
	
	this->name = name;
	this->charset = charset;
	
	this->arena = arena;
	
	dpvs(this->name);
	dpv(this->charset);
	
	EXIT;
	return this;
}

