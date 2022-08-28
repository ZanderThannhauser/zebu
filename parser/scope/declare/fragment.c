
#include <assert.h>

#include <debug.h>

#include <avl/insert.h>

#include <named/regex/new.h>

#include "../struct.h"

#include "fragment.h"

void scope_declare_fragment(struct scope* this, char* name, struct regex* token)
{
	ENTER;
	
	dpvs(name);
	dpv(token);
	
	assert(this->layer);
	
	avl_insert(this->layer->fragments, new_named_regex(name, token));
	
	EXIT;
}










