
#include <stdlib.h>
#include <assert.h>
#include <strings.h>
#include <string.h>

#include <avl/search.h>

#include <debug.h>

/*#include <memory/smalloc.h>*/

#include "../struct.h"

#include "grammar.h"

struct string* scope_resolve_grammar(
	struct scope* this,
	struct string* original)
{
	bool initially_found = true;
	char *dot, *dot2;
	struct avl_node_t* node;
	ENTER;
	
	char* copy = strdup(original->chars);
	
	dpvs(copy);
	
	while (!(node = avl_search(this->grammar, &(char**[]){&copy})) && (dot = rindex(copy, '.')))
	{
		*dot++ = 0, dot2 = rindex(copy, '.');
		
		if (dot2)
		{
			TODO;
		}
		else
		{
			memmove(copy, dot, strlen(dot) + 1);
			dpvs(copy);
		}
		
		initially_found = false;
	}
	
	if (!node)
	{
		TODO;
		exit(1);
	}
	
	EXIT;
	return initially_found ? inc_string(original) : new_string_without_copy(copy);
}











