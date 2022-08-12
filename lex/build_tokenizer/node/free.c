
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <set/of_tokens/free.h>
#include <set/of_tokensets/free.h>

#include "struct.h"
#include "free.h"

void free_build_tokenizer_node(void *ptr)
{
	struct build_tokenizer_node* node = ptr;
	
	free_tokenset(node->given);
	
	free_tokensetset(node->matches);
	
	free(node);
}

