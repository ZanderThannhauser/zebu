
#if 0
#include <stdlib.h>

#include <debug.h>

#include <set/of_tokens/free.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_tokenset_to_id(struct tokenset_to_id* this)
{
	ENTER;
	
	avl_free_tree(this->tree);
	
	free_tokenset(this->eof);
	
	free(this);
	
	EXIT;
}

#endif
