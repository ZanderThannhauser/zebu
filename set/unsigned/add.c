
#include <debug.h>

#include <memory/smalloc.h>

#include <avl/search.h>
#include <avl/insert.h>

#include "struct.h"
#include "add.h"

void unsignedset_add(
	struct unsignedset* this,
	unsigned token)
{
	ENTER;
	
	if (!avl_search(this->tree, &token))
	{
		unsigned* new = smalloc(sizeof(token));
		
		*new = token;
		
		avl_insert(this->tree, new);
		
		this->len++;
	}
	
	EXIT;
}

