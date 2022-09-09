
#include <assert.h>
#include <errno.h>

#include <debug.h>

#include <avl/insert.h>

#include "struct.h"
#include "add.h"

bool regexset_add(
	struct regexset* this,
	struct regex* addme)
{
	bool is_new;
	ENTER;
	
	errno = 0;
	
	struct avl_node_t* node = avl_insert(this->tree, addme);
	
	if (node)
	{
		this->n++, is_new = true;
	}
	else if (errno == EEXIST)
	{
		is_new = false;
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return is_new;
}

