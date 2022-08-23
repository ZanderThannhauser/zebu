
#include <assert.h>

#include <debug.h>

/*#include <memory/sstrndup.h>*/

/*#include "../private/append_prefix.h"*/

#include <avl/insert.h>

#include <named/gbundle/new.h>

/*#include <named/name/new.h>*/

#include "../struct.h"

#include "inline_grammar.h"

void scope_declare_inline_grammar(
	struct scope* this,
	char* name,
	struct gegex* start,
	struct gegex* end)
{
	ENTER;
	
	dpvs(name);
	dpv(start);
	dpv(end);
	
	assert(this->layer);
	
	avl_insert(this->layer->inline_grammar, new_named_gbundle(this->layer->arena, name, start, end));
	
	EXIT;
}











