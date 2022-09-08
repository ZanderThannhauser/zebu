
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <set/unsigned/free.h>

#include <set/unsignedset/free.h>

#include "struct.h"
#include "free.h"

void free_build_tokenizer_node(void *ptr)
{
	ENTER;
	
	struct build_tokenizer_node* node = ptr;
	
	free_unsignedset(node->given);
	
	free_unsignedsetset(node->matches);
	
	free(node);
	
	EXIT;
}

