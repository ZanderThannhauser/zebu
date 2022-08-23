
#include <debug.h>

#include <arena/malloc.h>

#include <set/of_tokens/clone.h>

#include "struct.h"
#include "new.h"

struct build_tokenizer_node* new_build_tokenizer_node(
	struct memory_arena* arena,
	struct tokenset* token_ids,  // needs to be cloned
	struct tokensetset* matches,
	struct lex_state* start)
{
	ENTER;
	
	struct build_tokenizer_node* this = arena_malloc(arena, sizeof(*this));
	
	this->given = tokenset_clone(token_ids, arena);
	
	this->matches = matches;
	
	this->start = start;
	
	EXIT;
	return this;
}

