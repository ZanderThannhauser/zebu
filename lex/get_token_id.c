
#include <debug.h>

#include <avl/new.h>
#include <avl/safe_insert.h>

#include <parser/token/regex/state/are_equal/are_equal.h>
#include <parser/token/regex/state/are_equal/cache/compare.h>
#include <parser/token/regex/state/are_equal/cache/free.h>

#include "node/struct.h"
#include "node/new.h"
#include "struct.h"
#include "get_token_id.h"

unsigned lex_get_token_id(
	struct lex* this,
	struct regex* token)
{
	unsigned retval;
	ENTER;
	
	dpv(token);
	
	struct avl_node_t* node;
	
	struct avl_tree_t* cache = new_avl_tree(compare_caches, free_cache);
	
	for (node = this->nodes.head; node; node = node->next)
	{
		const struct node* const ele = node->item;
		
		dpv(ele);
		
		if (regex_are_equal(cache, ele->token, token))
		{
			retval = ele->id;
			break;
		}
	}
	
	if (!node)
	{
		retval = this->next_id++;
		safe_avl_insert(&this->nodes, new_node(retval, token));
	}
	
	avl_free_tree(cache);
	
	EXIT;
	return retval;
}












