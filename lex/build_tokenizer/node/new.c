
#if 0
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include <set/of_tokens/clone.h>

#include "struct.h"
#include "new.h"

struct build_tokenizer_node* new_build_tokenizer_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenset* token_ids,  // needs to be cloned
	struct tokensetset* matches,
	struct lex_state* start)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct build_tokenizer_node* this = arena_malloc(arena, sizeof(*this));
	#else
	struct build_tokenizer_node* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->given = tokenset_clone(arena, token_ids);
	#else
	this->given = tokenset_clone(token_ids);
	#endif
	
	this->matches = matches;
	
	this->start = start;
	
	EXIT;
	return this;
}

#endif
