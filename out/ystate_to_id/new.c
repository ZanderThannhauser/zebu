
#include <assert.h>
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
	
	
	#ifdef WITH_ARENAS
	TODO;
	#else
	struct ystate_to_id_node* node = ptr;
	free(node);
	#endif
	
	EXIT;
}

struct ystate_to_id* new_ystate_to_id(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct ystate_to_id* this = arena_malloc(arena, sizeof(*this));
	#else
	struct ystate_to_id* this = malloc(sizeof(*this));
	#endif
	
	#ifdef WITH_ARENAS
	this->tree = avl_alloc_tree(arena, compare_ystate_to_id_nodes, free_ystate_to_id_node);
	#else
	this->tree = avl_alloc_tree(compare_ystate_to_id_nodes, free_ystate_to_id_node);
	#endif
	
	this->next = 1; // 0 indicates error
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	dpv(this->next);
	
	EXIT;
	return this;
}

















