
#include <assert.h>
#include <errno.h>

#include <debug.h>

#include <avl/insert.h>

#include <set/unsigned/inc.h>

#include "struct.h"
#include "add.h"

void unsignedsetset_add(
	struct unsignedsetset* this,
	struct unsignedset* element)
{
	ENTER;
	
	errno = 0;
	
	struct avl_node_t* node = avl_insert(this->tree, element);
	
	if (node)
	{
		inc_unsignedset(element);
	}
	else if (errno == EEXIST)
	{
		
	}
	else
	{
		TODO;
	}
	
	EXIT;
}


