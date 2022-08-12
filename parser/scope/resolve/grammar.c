
#include <stdlib.h>
#include <assert.h>
#include <strings.h>
#include <string.h>

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
	
	char *dot, *dot2;
	
	dpvs(full_name);
	
	struct avl_node_t* node;
	
	while (!(node = avl_search(this->grammar, &full_name)) && (dot = rindex(full_name, '.')))
	{
		dpvs(dot);
		
		*dot++ = 0, dot2 = rindex(full_name, '.');
		
		if (dot2)
		{
			TODO;
		}
		else
		{
			memmove(full_name, dot, strlen(dot) + 1);
		}
		
		dpvs(full_name);
		
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












