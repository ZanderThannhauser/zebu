
#include <debug.h>

#include <avl/tree_t.h>
#include <avl/insert.h>

#include <string/compare.h>
#include <string/inc.h>

#include "struct.h"
#include "update.h"

bool stringset_update(
	struct stringset* this,
	const struct stringset* other)
{
	bool has_changed = false;
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
			a = a->next;
		}
		else if (cmp < 0)
		{
			avl_insert(this->tree, inc_string(b->item));
			this->n++, b = b->next, has_changed = true;
		}
		else
		{
			a = a->next, b = b->next;
		}
	}
	
	while (b)
	{
		avl_insert(this->tree, inc_string(b->item));
		this->n++, b = b->next, has_changed = true;
	}
	
	EXIT;
	return has_changed;
}














