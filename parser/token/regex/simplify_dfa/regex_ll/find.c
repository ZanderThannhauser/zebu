
#include <debug.h>

#include "../../state/are_equal/are_equal.h"

#include "struct.h"
#include "find.h"

struct regex* regex_ll_find(
	struct regex_ll* this,
	struct regex* element)
{
	ENTER;
	
	struct regex_link* i;
	
	struct regex* retval = NULL;
	
	for (i = this->head; !retval && i; i = i->next)
		if (regex_are_equal(this->cache, element, i->element))
			retval = i->element;
	
	if (!retval)
	{
		TODO;
	}
	
	EXIT;
	return retval;
}










