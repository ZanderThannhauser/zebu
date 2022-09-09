
#include <stdlib.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include <memory/smalloc.h>

#include <string/compare.h>
#include <string/free.h>

#include "struct.h"
#include "new.h"

static int compare_nodes(const void* a, const void* b)
{
	const struct string_to_id_node *A = a, *B = b;
	
	return compare_strings(A->string, B->string);
}

static void free_node(void* ptr)
{
	struct string_to_id_node* node = ptr;
	free_string(node->string);
	free(node);
}

struct string_to_id* new_string_to_id()
{
	ENTER;
	
	struct string_to_id* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_nodes, free_node);
	
	this->next = 1; // 0 indicates error
	
	EXIT;
	return this;
}

