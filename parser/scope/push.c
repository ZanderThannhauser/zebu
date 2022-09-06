
#include <stdlib.h>
#include <stdio.h>

#include <debug.h>

#include <avl/alloc_tree.h>

/*#include <arena/malloc.h>*/

#include <named/charset/compare.h>
#include <named/charset/free.h>

#include <named/regex/compare.h>
#include <named/regex/free.h>

#include <named/gegex/compare.h>
#include <named/gegex/free.h>

/*#include <arena/child/new.h>*/

#include "private/append_prefix.h"

#include "struct.h"
#include "push.h"

void scope_push(struct scope* this)
{
	ENTER;
	
	struct scope_layer* new = smalloc(sizeof(*new));
	
	new->charsets       = avl_alloc_tree(compare_named_charsets, free_named_charset);
	new->fragments      = avl_alloc_tree(compare_named_regexes,  free_named_regex);
	new->inline_grammar = avl_alloc_tree(compare_named_gegexes,  free_named_gegex);
	
	new->sublayer_counter = 0;
	
	new->prefix_len = this->prefix.n;
	
	new->prev = this->layer;
	
	if (this->layer)
	{
		char number[30];
		
		sprintf(number, "__%u", this->layer->sublayer_counter++);
		
		private_scope_append_prefix(this, number);
	}
	
	this->layer = new;
	
	dpv(this->layer);
	
	EXIT;
}











