
#include <debug.h>

#include <yacc/reductioninfo/inc.h>

#include "struct.h"
#include "reducerule_to_id.h"

unsigned reducerule_to_id(
	struct reducerule_to_id* this,
	struct string* reduce_as,
	unsigned popcount,
	struct reductioninfo* reductioninfo)
{
	struct avl_node_t* node = avl_search(this->tree, &(struct reducerule_to_id_node) {
		.popcount = popcount,
		.reductioninfo = reductioninfo,
	});
	
	if (node)
	{
		struct reducerule_to_id_node* old = node->item;
		return old->id;
	}
	else
	{
		struct reducerule_to_id_node* new = smalloc(sizeof(*new));
		
		new->reduce_as = inc_string(reduce_as);
		new->popcount = popcount;
		new->reductioninfo = inc_reductioninfo(reductioninfo);
		new->id = this->next++;
		
		avl_insert(this->tree, new);
		
		return new->id;
	}
}

