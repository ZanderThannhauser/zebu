
#include <debug.h>

#include <string/inc.h>

#include <memory/smalloc.h>

#include <avl/insert.h>
#include <avl/search.h>

#include <yacc/reductioninfo/inc.h>

#include <yacc/structinfo/inc.h>

#include "struct.h"
#include "reducerule_to_id.h"

unsigned reducerule_to_id(
	struct reducerule_to_id* this,
	struct string* reduce_as,
	struct string* grammar,
	struct reductioninfo* reductioninfo,
	struct structinfo* structinfo)
{
	struct avl_node_t* node = avl_search(this->tree, &(struct reducerule_to_id_node) {
		.reduce_as = reduce_as,
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
		new->grammar = inc_string(grammar);
		new->reductioninfo = inc_reductioninfo(reductioninfo);
		new->structinfo = inc_structinfo(structinfo);
		
		new->id = this->next++;
		
		avl_insert(this->tree, new);
		
		return new->id;
	}
}

