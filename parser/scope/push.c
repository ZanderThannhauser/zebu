
#include <stdio.h>

#include <debug.h>

#include <avl/alloc_tree.h>

#include <arena/malloc.h>

#include <named/charset/compare.h>

#include <named/token/compare.h>

#include <named/gbundle/compare.h>

#include <arena/child/new.h>

#include "private/append_prefix.h"

#include "struct.h"
#include "push.h"

void scope_push(struct scope* this)
{
	ENTER;
	
	struct scope_layer* new = arena_malloc(this->arena, sizeof(*new));
	
	struct memory_arena* arena = new_child_arena(this->arena);
	
	new->charsets       = avl_alloc_tree(arena, compare_named_charsets, NULL);
	new->fragments      = avl_alloc_tree(arena, compare_named_tokens,   NULL);
	new->inline_grammar = avl_alloc_tree(arena, compare_named_gbundles, NULL);
	
	new->arena = arena;
	
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










