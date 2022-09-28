
#include <stdlib.h>

#include <assert.h>
#include <debug.h>

#include <regex/free.h>

#include "struct.h"
#include "free.h"

void free_dfa_from_id_node(void* this)
{
	ENTER;
	
	struct dfa_from_id_node* node = this;
	
	free_regex(node->token);
	
	free(this);
	
	EXIT;
}

