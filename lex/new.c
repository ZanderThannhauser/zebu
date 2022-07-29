
#include <debug.h>

#include <avl/new.h>

#include <memory/smalloc.h>

#include "lookup/to_node/compare.h"
#include "lookup/to_node/free.h"
#include "lookup/from_node/compare.h"
#include "lookup/from_node/free.h"

#include "build_tokenizer/node/compare.h"
#include "build_tokenizer/node/free.h"

#include "struct.h"
#include "new.h"

struct lex* new_lex()
{
	ENTER;
	
	struct lex* this = smalloc(sizeof(*this));
	
	this->dfa_to_id =
		new_avl_tree(compare_dfa_to_id_nodes, free_dfa_to_id_node);
		
	this->dfa_from_id =
		new_avl_tree(compare_dfa_from_id_nodes, free_dfa_from_id_node);
	
	this->tokenizer.cache =
		new_avl_tree(compare_build_tokenizer_nodes, free_build_tokenizer_node);
	
	this->next_id = 1; // because token 0 is for error
	
	this->EOF_token_id = 0;
	
	EXIT;
	return this;
}

