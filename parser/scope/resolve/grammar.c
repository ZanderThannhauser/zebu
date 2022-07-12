
#include <avl/search.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "../struct.h"

#include <named/grammar/struct.h>

#include "grammar.h"

struct gegex* scope_resolve_grammar(
	struct scope* this,
	char** full_name_in_out)
{
	ENTER;
	
	char* full_name = *full_name_in_out;
	
	char* dot;
	
	dpvs(full_name);
	
	struct avl_node_t* node = avl_search(this->grammar, &full_name);
	
	while (!node && (dot = rindex(full_name, '.')))
	{
		TODO;
		node = avl_search(this->grammar, &full_name);
	}
	
	*full_name_in_out = full_name;
	
	if (!node)
	{
		TODO;
		exit(1);
	}
	
	struct named_grammar* ngrammar = node->item;
	struct gegex* start = ngrammar->start;
	
	EXIT;
	return start;
}












