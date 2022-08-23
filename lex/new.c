
#include <stdlib.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include <arena/malloc.h>

#include <set/of_tokens/new.h>

#include "lookup/to_node/compare.h"
#include "lookup/to_node/free.h"

#include "lookup/from_node/compare.h"
#include "lookup/from_node/free.h"

#include "build_tokenizer/node/compare.h"
#include "build_tokenizer/node/free.h"

#include "struct.h"
#include "new.h"

struct lex* new_lex(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct lex* this = arena_malloc(arena, sizeof(*this));
	#else
	struct lex* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->dfa_to_id = avl_alloc_tree(arena, compare_dfa_to_id_nodes, NULL);
	#else
	this->dfa_to_id = avl_alloc_tree(compare_dfa_to_id_nodes, free_dfa_to_id_node);
	#endif
		
	#ifdef WITH_ARENAS
	this->dfa_from_id = avl_alloc_tree(arena, compare_dfa_from_id_nodes, NULL);
	#else
	this->dfa_from_id = avl_alloc_tree(compare_dfa_from_id_nodes, free_dfa_from_id_node);
	#endif
	
	#ifdef WITH_ARENAS
	this->tokenizer.cache = avl_alloc_tree(arena, compare_build_tokenizer_nodes, NULL);
	#else
	this->tokenizer.cache = avl_alloc_tree(compare_build_tokenizer_nodes, free_build_tokenizer_node);
	#endif
	
	#ifdef WITH_ARENAS
	this->disambiguations.literal_ids = new_tokenset(arena);
	#else
	this->disambiguations.literal_ids = new_tokenset();
	#endif
	
	#ifdef WITH_ARENAS
	this->disambiguations.regex_ids = new_tokenset(arena);
	#else
	this->disambiguations.regex_ids = new_tokenset();
	#endif
	
	this->next_id = 1; // because token 0 is for error
	
	this->EOF_token_id = 0;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}







