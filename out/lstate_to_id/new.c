

#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include <avl/alloc_tree.h>

#include "struct.h"
#include "new.h"

static int compare_lstate_to_id_nodes(const void* a, const void* b)
{
	int cmp = 0;
	ENTER;
	
	const struct lstate_to_id_node* A = a, *B = b;
	
	if (A->lstate > B->lstate)
		cmp = +1;
	else if (A->lstate < B->lstate)
		cmp = -1;
	
	EXIT;
	return cmp;
}

static void free_lstate_to_id_node(void* ptr)
{
	ENTER;
	
	struct lstate_to_id_node* node = ptr;
	
	free(node);
	
	EXIT;
}

struct lstate_to_id* new_lstate_to_id(
	struct memory_arena* arena)
{
	ENTER;
	
	struct lstate_to_id* this = arena_malloc(arena, sizeof(*this));
	
	this->tree = avl_alloc_tree(arena, compare_lstate_to_id_nodes, free_lstate_to_id_node);
	this->next = 1; // 0 indicates error
	
	dpv(this->next);
	
	this->arena = arena;
	
	EXIT;
	return this;
}












