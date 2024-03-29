
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <strings.h>
#include <string.h>

#include <debug.h>

#include <enums/error.h>

#include <string/struct.h>
#include <string/inc.h>
#include <string/new.h>

#include <avl/search.h>
/*#include <memory/smalloc.h>*/

#ifdef WINDOWS_PLATFORM
#include <compat/rindex.h>
#endif

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
	
	dpvs(original);
	
	char* copy = strdup(original->chars);
	
	dpvs(copy);
	
	while (!(node = avl_search(this->grammar, &(char**[]){&copy})) && (dot = rindex(copy, '$')))
	{
		*dot++ = 0, dot2 = rindex(copy, '$');
		
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
		fprintf(stderr, "zebu: cannot find grammar-rule '%s'!\n", original->chars);
		exit(e_bad_input_file);
	}
	
	EXIT;
	return initially_found ? (free(copy), inc_string(original)) : new_string_without_copy(copy);
}











