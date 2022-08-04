
#include <stdlib.h>

#include <assert.h>

#include <strings.h>

#include <avl/search.h>

#include <debug.h>

/*#include <memory/smalloc.h>*/

#include "../struct.h"

/*#include <named/grammar/struct.h>*/

#include "grammar.h"

char* scope_resolve_grammar(
	struct scope* this,
	char* full_name)
{
	ENTER;
	
	char* dot;
	
	dpvs(full_name);
	
	struct avl_node_t* node;
	
	while (!(node = avl_search(this->grammar, &full_name)) && (dot = rindex(full_name, '.')))
	{
		// memmove fullname
		TODO;
		node = avl_search(this->grammar, &full_name);
	}
	
	if (!node)
	{
		TODO;
		exit(1);
	}
	
	EXIT;
	return full_name;
}












