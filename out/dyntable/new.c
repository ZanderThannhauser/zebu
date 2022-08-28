
#if 0
#include <assert.h>
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
	
	
	#ifdef WITH_ARENAS
	TODO;
	#else
	
	struct dyntable_node* node = ptr;
	
	free(node);
	#endif
	
	EXIT;
}

struct dyntable* new_dyntable(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const char* name)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct dyntable* this = arena_malloc(arena, sizeof(*this));
	#else
	struct dyntable* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->tree = avl_alloc_tree(arena, compare_dyntable_nodes, free_dyntable_node);
	#else
	this->tree = avl_alloc_tree(compare_dyntable_nodes, free_dyntable_node);
	#endif
	
	this->name = name;
	this->width = 0;
	this->height = 0;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}
















#endif
