
#include <debug.h>

#include "struct.h"
#include "discard.h"

void ptrset_discard(
	struct ptrset* this,
	void* element)
{
	ENTER;
	
	avl_delete(this->tree, element);
	
	EXIT;
}
