
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include <avl/alloc_tree.h>

#include "struct.h"
#include "new.h"

static int compare_dyntable_nodes(const void* a, const void* b)
{
	int cmp = 0;
	
	const struct dyntable_node* A = a, *B = b;
	
	if (A->x > B->x)
		cmp = +1;
	else if (A->x < B->x)
		cmp = -1;
	else if (A->y > B->y)
		cmp = +1;
	else if (A->y < B->y)
		cmp = -1;
	
	return cmp;
}

static void free_dyntable_node(void* ptr)
{
	ENTER;
	
	struct dyntable_node* node = ptr;
	
	free(node);
	
	EXIT;
}

struct dyntable* new_dyntable(
	struct memory_arena* arena,
	const char* name)
{
	ENTER;
	
	struct dyntable* this = arena_malloc(arena, sizeof(*this));
	
	this->tree = avl_alloc_tree(arena, compare_dyntable_nodes, free_dyntable_node);
	this->name = name;
	this->width = 0;
	this->height = 0;
	
	this->arena = arena;
	
	EXIT;
	return this;
}

















