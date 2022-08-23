
#include <string.h>
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>
#include <arena/memdup.h>

#include "struct.h"
#include "clone.h"

struct charset* clone_charset(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const struct charset* cloneme)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct charset* this = arena_malloc(arena, sizeof(*this));
	#else
	struct charset* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->chars = arena_memdup(arena, cloneme->chars, cloneme->len);
	#else
	this->chars = memcpy(malloc(cloneme->len), cloneme->chars, cloneme->len);
	#endif
	
	this->len = cloneme->len;
	
	this->is_complement = cloneme->is_complement;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

