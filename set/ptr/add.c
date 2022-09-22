
#include <assert.h>
#include <errno.h>

#include <debug.h>

#include <avl/insert.h>

#include "struct.h"
#include "add.h"

bool ptrset_add(
	struct ptrset* set,
	void* element)
{
	ENTER;
	
	bool new;
	struct avl_node_t* node = avl_insert(set->tree, element);
	
	if (node)
	{
		#ifdef VERBOSE
		set->n++;
		#endif
		new = true;
	}
	else if (errno == EEXIST)
	{
		new = false;
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return new;
}

