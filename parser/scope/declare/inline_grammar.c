
#include <debug.h>

/*#include <memory/sstrndup.h>*/

#include "../struct.h"

/*#include "../private/append_prefix.h"*/

#include <named/gbundle/new.h>

/*#include <named/name/new.h>*/

#include "inline_grammar.h"

void scope_declare_inline_grammar(
	struct scope* this,
	char* name,
	struct gegex* start,
	struct gegex* end)
{
	ENTER;
	
	TODO;
	#if 0
	dpvs(name);
	dpv(start);
	dpv(end);
	
	assert(this->layer);
	
	safe_avl_insert(this->layer->inline_grammar, new_named_gbundle(name, start, end));
	#endif
	
	EXIT;
}











