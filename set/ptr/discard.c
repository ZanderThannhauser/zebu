
#include <debug.h>

#include <avl/delete.h>

#include "struct.h"
#include "discard.h"

void ptrset_discard(
	struct ptrset* this,
	void* element)
{
	ENTER;
	
	
	#ifdef VERBOSE
	if (avl_delete(this->tree, element))
	{
		this->n--;
	}
	#else
	avl_delete(this->tree, element);
	#endif
	
	EXIT;
}
