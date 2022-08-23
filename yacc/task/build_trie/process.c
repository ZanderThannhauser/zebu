
#include <string.h>

#include <assert.h>

#include <debug.h>

#include <arena/strdup.h>

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

/*#include "../../add_dep.h"*/
/*#include "../../lookup_tokenset.h"*/

/*#include "../setup_trie/new.h"*/

#include "struct.h"
#include "new.h"
#include "process.h"

static struct gegex* process_to(
	struct build_trie_task* this,
	struct yacc_shared* shared,
	struct gegex* mirrorme_to)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct memory_arena* const arena = shared->arena;
	#endif
	
	#ifdef WITH_ARENAS
	struct gegex* building_to = new_gegex(arena);
	#else
	struct gegex* building_to = new_gegex();
	#endif
	
	assert(mirrorme_to->refcount);
	
	if (mirrorme_to->is_reduction_point)
	{
		building_to->is_reduction_point = true;
		building_to->popcount = this->popcount + 1;
	}
	
	if (mirrorme_to->refcount == 1)
	{
		heap_push(shared->todo, new_build_trie_task(
			#ifdef WTIH_ARENAS
			arena,
			#endif
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
		
		#ifdef WTIH_ARENAS
		struct gegex* reduction = new_gegex(arena);
		#else
		struct gegex* reduction = new_gegex();
		#endif
		
		reduction->is_reduction_point = true;
		reduction->popcount = this->popcount + 2;
		
		#ifdef WTIH_ARENAS
		char* dup = arena_strdup(arena, gtot->trie);
		#else
		char* dup = strdup(gtot->trie);
		#endif
		
		gegex_add_grammar_transition(building_to, dup, reduction);
	}
	
	EXIT;
	return building_to;
}

void build_trie_task_process(struct task* super, struct yacc_shared* shared)
{
	struct build_trie_task* const this = (void*) super;
	ENTER;
	
	dpvs(this->name);
	
	struct gegex* const mirrorme = this->mirrorme;
	struct gegex* const building = this->building;
	
	for (unsigned i = 0, n = mirrorme->transitions.n; i < n; i++)
	{
		unsigned token = mirrorme->transitions.data[i]->token;
		
		struct gegex* mirrorme_to = mirrorme->transitions.data[i]->to;
		struct gegex* building_to = process_to(this, shared, mirrorme_to);
		
		gegex_add_transition(building, token, building_to);
	}
	
	for (unsigned i = 0, n = mirrorme->grammar_transitions.n; i < n; i++)
	{
		char* grammar = mirrorme->grammar_transitions.data[i]->grammar;
		
		struct gegex* mirrorme_to = mirrorme->grammar_transitions.data[i]->to;
		struct gegex* building_to = process_to(this, shared, mirrorme_to);
		
		gegex_add_grammar_transition(building, grammar, building_to);
	}
	
	EXIT;
}

















