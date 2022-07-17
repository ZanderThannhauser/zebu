
#include <debug.h>

#include <memory/smalloc.h>

#include "../are_equal.h"

#include "struct.h"
#include "add.h"

void regex_ll_add(struct regex_ll* this, struct regex* element)
{
	ENTER;
	
	struct regex_link* i;
	
	for (i = this->head; i; i = i->next)
	{
		if (regex_are_equal(this->cache, element, i->element))
		{
			break;
		}
	}
	
	if (!i)
	{
		ddprintf("looks new, adding...\n");
		
		struct regex_link* new = smalloc(sizeof(*new));
		
		new->element = element;
		new->next = this->head;
		
		this->head = new;
	}
	
	EXIT;
}
