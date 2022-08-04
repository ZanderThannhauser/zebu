
#include <memory/smalloc.h>

#include <debug.h>

#include <heap/new.h>

#include <avl/new.h>

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

#include "struct.h"
#include "new.h"

struct yacc_shared* new_yacc_shared(
	struct avl_tree_t* grammar,
	unsigned EOF_token_id)
{
	ENTER;
	struct yacc_shared* this = smalloc(sizeof(*this));
	
	this->grammar = grammar;
	this->EOF_token_id = EOF_token_id;
	
	this->todo = new_heap(compare_tasks);
	
	this->new_grammar = new_avl_tree(compare_named_grammar, free_named_grammar);
	
	this->gegex_to_trie = new_avl_tree(compare_gegex_to_tries, free_gegex_to_trie);
	
	this->next_trie_id = 0;
	
	this->firsts.sets = new_avl_tree(compare_named_tokensets, free_named_tokenset);
	this->firsts.dependant_of = new_avl_tree(compare_named_strsets, free_named_strset);
	this->firsts.dependant_on = new_avl_tree(compare_named_strsets, free_named_strset);
	
	this->lookaheads.sets = new_avl_tree(compare_named_tokensets, free_named_tokenset);
	this->lookaheads.dependant_of = new_avl_tree(compare_named_strsets, free_named_strset);
	this->lookaheads.dependant_on = new_avl_tree(compare_named_strsets, free_named_strset);
	
	EXIT;
	return this;
}















