
#include <debug.h>

#include "struct.h"
#include "new.h"

static int compare_nodes(const void* a, const void* b)
{
	const struct structinfo_node *A = a, *B = b;
	return compare_strings(A->name, B->name);
}

static void free_node(void* ptr)
{
	struct structinfo_node* node = ptr;
	
	if (node && !--node->refcount)
	{
		free_string(node->name);
		
		switch (node->kind)
		{
			case sin_token_scalar:
			case sin_token_array:
				break;
			
			case sin_grammar_scalar:
			case sin_grammar_array:
				free_string(node->grammar);
				break;
			
			default:
				TODO;
				break;
		}
		
		free(node);
	}
}

struct structinfo* new_structinfo(struct string* name)
{
	ENTER;
	
	struct structinfo* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->tree = avl_alloc_tree(compare_nodes, free_node);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}













