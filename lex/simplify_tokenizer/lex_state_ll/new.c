
#if 0
#include <debug.h>

#include <avl/new.h>

#include "../cache/compare.h"
#include "../cache/free.h"

#include "struct.h"
#include "new.h"

struct lex_state_ll* new_lex_state_ll()
{
	ENTER;
	
	struct lex_state_ll* this = smalloc(sizeof(*this));
	
	this->cache = new_avl_tree(
		compare_lex_state_caches,
		free_lex_state_cache);
	
	this->head = NULL;
	
	EXIT;
	return this;
}

#endif
