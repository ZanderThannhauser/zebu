
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <debug.h>

/*#include <defines/argv0.h>*/

#include <enums/error.h>

#include <avl/search.h>
#include <avl/insert.h>

#include "struct.h"
#include "lookup.h"

bool pragma_once_lookup(
	struct pragma_once* this,
	const char* path)
{
	ENTER;
	
	dpvs(path);
	
	bool first_time = !avl_search(this->tree, path);
	
	dpvb(first_time);
	
	if (first_time)
	{
		avl_insert(this->tree, strdup(path));
	}
	
	EXIT;
	return first_time;
}


























