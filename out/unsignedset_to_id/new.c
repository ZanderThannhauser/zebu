
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>

#include <set/unsigned/compare.h>
#include <set/unsigned/free.h>

#include "struct.h"
#include "new.h"

static int compare_nodes(const void* a, const void* b)
{
	const struct unsignedset_to_id_node* A = a, *B = b;
	
	return compare_unsignedsets(A->unsignedset, B->unsignedset);
}

static void free_node(void* ptr)
{
	struct unsignedset_to_id_node* node = ptr;
	free_unsignedset(node->unsignedset);
	free(node);
}

struct unsignedset_to_id* new_unsignedset_to_id()
{
	ENTER;
	
	struct unsignedset_to_id* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_nodes, free_node);
	
	this->next = 2; // 0 indicates error, 1 indicates whitespace
	
	dpv(this->next);

	EXIT;
	return this;
}

















