
#include <debug.h>

#include <arena/malloc.h>
#include <arena/memdup.h>

#include "struct.h"
#include "clone.h"

struct charset* clone_charset(
	struct memory_arena* arena,
	const struct charset* cloneme)
{
	ENTER;
	
	struct charset* this = arena_malloc(arena, sizeof(*this));
	
	this->chars = arena_memdup(arena, cloneme->chars, cloneme->len);
	this->len = cloneme->len;
	
	this->is_complement = cloneme->is_complement;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

