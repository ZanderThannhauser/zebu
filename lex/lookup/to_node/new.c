
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct dfa_to_id_node* new_dfa_to_id_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	unsigned id, struct regex* token)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct dfa_to_id_node* this = arena_malloc(arena, sizeof(*this));
	#else
	struct dfa_to_id_node* this = malloc(sizeof(*this));
	#endif
	
	this->id = id;
	this->token = token;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

