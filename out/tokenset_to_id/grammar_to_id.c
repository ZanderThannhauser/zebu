
#if 0
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include <avl/insert.h>
#include <avl/search.h>

#include "struct.h"
#include "grammar_to_id.h"

unsigned grammar_to_id(
	struct tokenset_to_id* this,
	const char* grammar)
{
	unsigned retval;
	ENTER;
	
	dpvs(grammar);
	
	struct avl_node_t* node = avl_search(this->tree, &(struct tokenset_to_id_node){
		.is_tokenset = false,
		.grammar = grammar,
	});
	
	if (node)
	{
		struct tokenset_to_id_node* old = node->item;
		
		retval = old->id;
	}
	else
	{
		#ifdef WITH_ARENAS
		struct tokenset_to_id_node* new = arena_malloc(this->arena, sizeof(*new));
		#else
		struct tokenset_to_id_node* new = malloc(sizeof(*new));
		#endif
		
		new->is_tokenset = false;
		new->grammar = grammar;
		new->id = retval = this->next++;
		
		avl_insert(this->tree, new);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}
#endif
