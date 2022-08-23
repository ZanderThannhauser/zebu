
#include <debug.h>

#include <heap/new.h>

#include <avl/alloc_tree.h>

#include <arena/malloc.h>

#include <named/tokenset/compare.h>
#include <named/tokenset/free.h>

#include <named/grammar/compare.h>
#include <named/grammar/free.h>

#include <named/strset/compare.h>
#include <named/strset/free.h>

#include "../task/compare.h"
#include "../task/free.h"

#include "../gegex_to_trie/compare.h"
#include "../gegex_to_trie/free.h"

#include "../stateinfo_to_state/compare.h"
#include "../stateinfo_to_state/free.h"

#include "struct.h"
#include "new.h"

struct yacc_shared* new_yacc_shared(
	struct memory_arena* arena,
	struct memory_arena* tokenizer_arena,
	struct memory_arena* parser_arena,
	struct lex* lex,
	struct avl_tree_t* grammar,
	unsigned EOF_token_id)
{
	ENTER;
	
	struct yacc_shared* this = arena_malloc(arena, sizeof(*this));
	
	this->arena = arena;
	
	this->tokenizer_arena = tokenizer_arena;
	
	this->parser_arena = parser_arena;
	
	this->grammar = grammar;
	
	this->lex = lex;
	
	this->EOF_token_id = EOF_token_id;
	
	this->todo = new_heap(arena, compare_tasks);
	
	this->new_grammar = avl_alloc_tree(arena, compare_named_grammars, NULL);
	
	this->gegex_to_trie = avl_alloc_tree(arena, compare_gegex_to_tries, NULL);
	
	this->next_trie_id = 0;
	
	this->firsts.sets = avl_alloc_tree(arena, compare_named_tokensets, NULL);
	
	this->firsts.dependant_of = avl_alloc_tree(arena, compare_named_strsets, NULL);
	
	this->firsts.dependant_on = avl_alloc_tree(arena, compare_named_strsets, NULL);
	
	this->stateinfo_to_state = avl_alloc_tree(arena, compare_stateinfo_to_states, NULL);
	
	this->yacc_start = NULL;
	
	EXIT;
	return this;
}















