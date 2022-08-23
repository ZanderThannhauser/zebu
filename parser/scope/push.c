
#include <stdlib.h>
#include <stdio.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include <arena/malloc.h>

#include <named/charset/compare.h>
#include <named/charset/free.h>

#include <named/token/compare.h>
#include <named/token/free.h>

#include <named/gbundle/compare.h>
#include <named/gbundle/free.h>

#include <arena/child/new.h>

#include "private/append_prefix.h"

#include "struct.h"
#include "push.h"

void scope_push(struct scope* this)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct scope_layer* new = arena_malloc(this->arena, sizeof(*new));
	#else
	struct scope_layer* new = malloc(sizeof(*new));
	#endif
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena = new_child_arena(this->arena);
	#endif
	
	#ifdef WITH_ARENAS
	new->arena = arena;
	
	new->charsets       = avl_alloc_tree(arena, compare_named_charsets, free_named_charset);
	new->fragments      = avl_alloc_tree(arena, compare_named_tokens,   free_named_token);
	new->inline_grammar = avl_alloc_tree(arena, compare_named_gbundles, free_named_gbundle);
	
	#else
	
	new->charsets       = avl_alloc_tree(compare_named_charsets, free_named_charset);
	new->fragments      = avl_alloc_tree(compare_named_tokens,   free_named_token);
	new->inline_grammar = avl_alloc_tree(compare_named_gbundles, free_named_gbundle);
	
	#endif
	
	new->sublayer_counter = 0;
	
	new->prefix_len = this->prefix.n;
	
	new->prev = this->layer;
	
	if (this->layer)
	{
		char number[30];
		
		sprintf(number, "%u", this->layer->sublayer_counter++);
		
		private_scope_append_prefix(this, number);
	}
	
	this->layer = new;
	
	dpv(this->layer);
	
	EXIT;
}










