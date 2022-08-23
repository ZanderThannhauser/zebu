
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

struct lex* new_lex(struct memory_arena* arena)
{
	ENTER;
	
	struct lex* this = arena_malloc(arena, sizeof(*this));
	
	this->dfa_to_id = avl_alloc_tree(arena, compare_dfa_to_id_nodes, NULL);
		
	this->dfa_from_id = avl_alloc_tree(arena, compare_dfa_from_id_nodes, NULL);
	
	this->tokenizer.cache = avl_alloc_tree(arena, compare_build_tokenizer_nodes, NULL);
	
	this->disambiguations.literal_ids = new_tokenset(arena);
	
	this->disambiguations.regex_ids = new_tokenset(arena);
	
	this->next_id = 1; // because token 0 is for error
	
	this->EOF_token_id = 0;
	
	this->arena = arena;
	
	EXIT;
	return this;
}







