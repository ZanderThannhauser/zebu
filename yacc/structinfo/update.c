
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <avl/tree_t.h>
#include <avl/insert.h>

#include <string/compare.h>

#include "node.h"
#include "struct.h"
#include "update.h"

void structinfo_update(
	struct structinfo* this,
	const struct structinfo* other)
{
	ENTER;
	
	struct avl_node_t* an = this->tree->head, *bn = other->tree->head;
	
	while (an && bn)
	{
		struct structinfo_node *ae = an->item, *be = bn->item;
		
		int cmp = compare_strings(ae->name, be->name);
		
		if (cmp < 0)
		{
			an = an->next;
		}
		else if (cmp > 0)
		{
			struct structinfo_node* be = bn->item;
			
			be->refcount++;
			
			avl_insert(this->tree, be);
			
			bn = bn->next;
		}
		else
		{
			if (ae->type != be->type)
			{
				TODO;
				exit(1);
			}
			
			TODO;
			#if 0
			if (false
				|| ae->type == snt_substructinfo_scalar
				|| ae->type == snt_substructinfo_array)
			{
				structinfo_update(
					ae->substructinfo.structinfo,
					be->substructinfo.structinfo);
			}
			#endif
			
			an = an->next, bn = bn->next;
		}
	}
	
	while (bn)
	{
		struct structinfo_node* be = bn->item;
		
		be->refcount++;
		
		avl_insert(this->tree, be);
		
		bn = bn->next;
	}
	
	EXIT;
}







