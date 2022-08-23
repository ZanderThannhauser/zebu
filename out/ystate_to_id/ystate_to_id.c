
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include <avl/insert.h>
#include <avl/search.h>

#include "struct.h"
#include "ystate_to_id.h"

unsigned ystate_to_id(
	struct ystate_to_id* this,
	struct yacc_state* state)
{
	unsigned retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &state);
	
	if (node)
	{
		struct ystate_to_id_node* old = node->item;
		
		retval = old->id;
	}
	else
	{
		#ifdef WITH_ARENAS
		struct ystate_to_id_node* new = arena_malloc(this->arena, sizeof(*new));
		#else
		struct ystate_to_id_node* new = malloc(sizeof(*new));
		#endif
		
		new->ystate = state;
		new->id = retval = this->next++;
		
		avl_insert(this->tree, new);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}

