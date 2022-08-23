
#include <assert.h>

#include <debug.h>

#include <set/of_tokens/new.h>

#include <named/tokenset/struct.h>
#include <named/tokenset/new.h>

#include <avl/search.h>
#include <avl/insert.h>

#include "struct.h"
#include "lookup_firsts.h"

struct tokenset* shared_lookup_firsts(
	struct yacc_shared* this,
	const char* name)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->firsts.sets, &name);
	
	if (node)
	{
		struct named_tokenset* nt = node->item;
		
		EXIT;
		return nt->tokenset;
	}
	else
	{
		#ifdef WITH_ARENAS
		struct tokenset* new = new_tokenset(this->arena);
		#else
		struct tokenset* new = new_tokenset();
		#endif
		
		#ifdef WITH_ARENAS
		struct named_tokenset* nt = new_named_tokenset(this->arena, name, new);
		#else
		struct named_tokenset* nt = new_named_tokenset(name, new);
		#endif
		
		avl_insert(this->firsts.sets, nt);
		
		EXIT;
		return new;
	}
}



