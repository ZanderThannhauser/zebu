
#include <stdio.h>

#include <debug.h>

#include <avl/new.h>

#include <memory/smalloc.h>

#include <named/charset/compare.h>
#include <named/charset/free.h>

#include <named/token/compare.h>
#include <named/token/free.h>

#include <named/gbundle/compare.h>
#include <named/gbundle/free.h>

#include <memory/arena/new.h>

#include "private/append_prefix.h"

#include "struct.h"
#include "push.h"

void scope_push(struct scope* this)
{
	ENTER;
	
	struct scope_layer* new = smalloc(sizeof(*new));
	
	new->charsets       = new_avl_tree(compare_named_charsets, free_named_charset);
	new->fragments      = new_avl_tree(compare_named_tokens,   free_named_token);
	new->inline_grammar = new_avl_tree(compare_named_gbundles, free_named_gbundle);
	
	new->arena = new_memory_arena();
	
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










