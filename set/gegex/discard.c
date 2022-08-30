
#include <debug.h>

#include "struct.h"
#include "discard.h"

void gegexset_discard(
	struct gegexset* this,
	struct gegex* element)
{
	avl_delete(this->tree, element);
}

