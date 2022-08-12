
#include <assert.h>

#include <debug.h>

#include <avl/safe_insert.h>

#include <set/of_tokens/new.h>

#include <named/tokenset/struct.h>
#include <named/tokenset/new.h>

#include <avl/search.h>

#include "struct.h"
#include "lookup_firsts.h"

struct tokenset* shared_lookup_firsts(
	struct yacc_shared* this,
	const char* name)
{
	struct avl_node_t* node = avl_search(this->firsts.sets, &name);
	
	if (node)
	{
		struct named_tokenset* nt = node->item;
		return nt->tokenset;
	}
	else
	{
		struct tokenset* new = new_tokenset();
		
		struct named_tokenset* nt = new_named_tokenset(name, new);
		
		safe_avl_insert(this->firsts.sets, nt);
		
		return new;
	}
}

