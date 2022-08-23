

#include <stdlib.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include <arena/malloc.h>

#include "struct.h"
#include "new.h"

static int compare_ystate_to_id_nodes(const void* a, const void* b)
{
	int cmp = 0;
	ENTER;
	
	const struct ystate_to_id_node* A = a, *B = b;
	
	if (A->ystate > B->ystate)
		cmp = +1;
	else if (A->ystate < B->ystate)
		cmp = -1;
	
	EXIT;
	return cmp;
}

static void free_ystate_to_id_node(void* ptr)
{
	ENTER;
	
	struct ystate_to_id_node* node = ptr;
	
	free(node);
	
	EXIT;
}

struct ystate_to_id* new_ystate_to_id(
	struct memory_arena* arena)
{
	ENTER;
	
	struct ystate_to_id* this = arena_malloc(arena, sizeof(*this));
	
	this->tree = avl_alloc_tree(arena, compare_ystate_to_id_nodes, free_ystate_to_id_node);
	this->next = 1; // 0 indicates error
	
	this->arena = arena;
	
	dpv(this->next);
	
	EXIT;
	return this;
}

















