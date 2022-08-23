
#include <debug.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

struct dfa_to_id_node* new_dfa_to_id_node(
	struct memory_arena* arena,
	unsigned id, struct regex* token)
{
	ENTER;
	
	struct dfa_to_id_node* this = arena_malloc(arena, sizeof(*this));
	
	this->id = id;
	this->token = token;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

