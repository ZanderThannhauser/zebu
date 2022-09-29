
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include <memory/smalloc.h>

#include <string/inc.h>
#include <string/compare.h>
#include <string/free.h>

#include <misc/format_flags/free.h>

#include "node.h"
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
		
		switch (node->type)
		{
			case snt_token_scalar:
			case snt_token_array:
				break;
			
			case snt_grammar_scalar:
			case snt_grammar_array:
				free_string(node->grammar.name);
				break;
			
			case snt_scanf_scalar:
				free_format_flags(node->scanf.fflags);
				break;
			
			case snt_scanf_array:
				TODO;
				break;
			
			case snt_user_defined:
				free_string(node->user_defined.type);
				free_string(node->user_defined.destructor);
				break;
			
			default:
				TODO;
				break;
		}
		
		free(node);
	}
}

struct structinfo* new_structinfo(void)
{
	ENTER;
	
	struct structinfo* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_nodes, free_node);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}













