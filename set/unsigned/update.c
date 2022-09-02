
#include <debug.h>

#include "struct.h"
#include "update.h"

bool unsignedset_update(
	struct unsignedset* this,
	const struct unsignedset* other)
{
	bool has_changed = false;
	ENTER;
	
	struct avl_node_t *an = this->tree->head;
	struct avl_node_t *bn = other->tree->head;
	
	while (an && bn)
	{
		dpv(an->item);
		dpv(bn->item);
		
		unsigned ae = *(unsigned*) an->item;
		unsigned be = *(unsigned*) bn->item;
		
		if (ae > be)
		{
			TODO;
		}
		else if (ae < be)
		{
			dpv(ae);
			an = an->next;
		}
		else
		{
			TODO;
		}
	}
	
	while (bn)
	{
		unsigned be = *(unsigned*) bn->item;
		
		dpv(be);
		
		unsigned *copy = smalloc(sizeof(*copy));
		
		*copy = be;
		
		avl_insert(this->tree, copy);
		
		has_changed = true;
		
		bn = bn->next;
	}
	
	EXIT;
	return has_changed;
}














