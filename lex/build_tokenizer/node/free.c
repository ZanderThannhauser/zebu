
#include <stdlib.h>

#include <assert.h>

#include <debug.h>


#include "struct.h"
#include "free.h"

void free_build_tokenizer_node(void *ptr)
{
	ENTER;
	
	struct build_tokenizer_node* node = ptr;
	
	TODO;
	#if 0
	free_tokenset(node->given);
	
	free_tokensetset(node->matches);
	
	free(node);
	#endif
	EXIT;
}

