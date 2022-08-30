
#include <assert.h>

#include <debug.h>

#include <avl/insert.h>

#include <named/gegex/new.h>

#include "../struct.h"

#include "inline_grammar.h"

void scope_declare_inline_grammar(struct scope* this, char* name, struct gegex* start)
{
	ENTER;
	
	dpvs(name);
	
	assert(this->layer);
	
	avl_insert(this->layer->inline_grammar, new_named_gegex(name, start));
	
	EXIT;
}










