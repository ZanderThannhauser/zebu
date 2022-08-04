
#include <assert.h>

#include <debug.h>

#include <memory/arena/strdup.h>

#include <avl/search.h>
/*#include <avl/safe_insert.h>*/

#include <yacc/gegex/state/struct.h>
#include <yacc/gegex/state/new.h>
#include <yacc/gegex/state/add_transition.h>
#include <yacc/gegex/state/add_grammar_transition.h>

/*#include <set/of_tokens/add.h>*/
/*#include <set/of_tokens/print.h>*/

#include <heap/push.h>

#include "../../gegex_to_trie/struct.h"
#include "../../shared/struct.h"

#include "../add_reductions/new.h"

/*#include "../../add_dep.h"*/
/*#include "../../lookup_tokenset.h"*/

/*#include "../setup_trie/new.h"*/

#include "struct.h"
#include "new.h"
#include "process.h"

static struct gegex* process_to(
	struct build_trie_task* this,
	struct yacc_shared* shared,
	struct memory_arena* scratchpad,
	struct gegex* mirrorme_to)
{
	ENTER;
	
	struct gegex* building_to = new_gegex(scratchpad);
		
	assert(mirrorme_to->refcount);
	
	if (mirrorme_to->is_reduction_point)
	{
		building_to->is_reduction_point = true;
		building_to->popcount = this->popcount + 1;
		
		heap_push(shared->todo, new_add_reductions_task(this->name, building_to, this->scratchpad));
	}
	
	if (mirrorme_to->refcount == 1)
	{
		heap_push(shared->todo, new_build_trie_task(
			scratchpad,
			this->name,
			this->start,
			mirrorme_to,
			building_to,
			this->popcount + 1));
	}
	else if (mirrorme_to->transitions.n || mirrorme_to->grammar_transitions.n)
	{
		struct avl_node_t* node = avl_search(shared->gegex_to_trie, &mirrorme_to);
		assert(node);
		
		const struct gegex_to_trie* gtot = node->item;
		
		dpvs(gtot->trie);
		
		struct gegex* reduction = new_gegex(scratchpad);
		
		{
			reduction->is_reduction_point = true;
			reduction->popcount = this->popcount + 2;
			
			heap_push(shared->todo, new_add_reductions_task(this->name, reduction, this->scratchpad));
		}
		
		char* dup = arena_strdup(scratchpad, gtot->trie);
		
		gegex_add_grammar_transition(building_to, scratchpad, dup, reduction);
		
	}
	
	EXIT;
	return building_to;
}

void build_trie_task_process(struct task* super, struct yacc_shared* shared)
{
	struct build_trie_task* const this = (void*) super;
	ENTER;
	
	dpvs(this->name);
	
	struct memory_arena* const scratchpad = this->scratchpad;
	struct gegex* const mirrorme = this->mirrorme;
	struct gegex* const building = this->building;
	
	for (unsigned i = 0, n = mirrorme->transitions.n; i < n; i++)
	{
		unsigned token = mirrorme->transitions.data[i]->token;
		
		struct gegex* mirrorme_to = mirrorme->transitions.data[i]->to;
		struct gegex* building_to = process_to(this, shared, scratchpad, mirrorme_to);
		
		gegex_add_transition(building, scratchpad, token, building_to);
	}
	
	for (unsigned i = 0, n = mirrorme->grammar_transitions.n; i < n; i++)
	{
		char* grammar = mirrorme->grammar_transitions.data[i]->grammar;
		
		struct gegex* mirrorme_to = mirrorme->grammar_transitions.data[i]->to;
		struct gegex* building_to = process_to(this, shared, scratchpad, mirrorme_to);
		
		gegex_add_grammar_transition(building, scratchpad, grammar, building_to);
	}
	
	EXIT;
}

















