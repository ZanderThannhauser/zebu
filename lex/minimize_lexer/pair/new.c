
#if 0
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct lex_pair* new_lex_pair(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct lex_state* a, struct lex_state* b)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct lex_pair* this = arena_malloc(arena, sizeof(*this));
	#else
	struct lex_pair* this = malloc(sizeof(*this));
	#endif
	
	assert(a < b);
	
	this->a = a;
	this->b = b;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}
#endif
