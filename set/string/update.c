
#include <debug.h>

#include "struct.h"
#include "update.h"

void stringset_update(
	struct stringset* this,
	const struct stringset* other)
{
	ENTER;
	
	struct avl_node_t* a = this->tree->head;
	struct avl_node_t* b = other->tree->head;
	
	while (a && b)
	{
		struct string* ae = a->item, *be = b->item;
		
		dpvs(ae->chars);
		dpvs(be->chars);
		
		int cmp = compare_strings(ae, be);
		
		if (cmp > 0)
		{
			TODO;
		}
		else if (cmp < 0)
		{
			TODO;
		}
		else
		{
			a = a->next, b = b->next;
		}
	}
	
	while (b)
	{
		this->n++;
		avl_insert(this->tree, inc_string(b->item));
		b = b->next;
	}
	
	EXIT;
}














