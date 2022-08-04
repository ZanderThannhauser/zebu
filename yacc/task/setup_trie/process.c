
#include <assert.h>

#include <debug.h>

#include <memory/sstrdup.h>
#include <memory/sasprintf.h>

#include <macros/strequals.h>

/*#include <avl/search.h>*/
#include <avl/safe_insert.h>

#include <yacc/gegex/state/struct.h>
#include <yacc/gegex/state/new.h>

#include <set/of_tokens/new.h>
#include <set/of_tokens/add.h>
/*#include <set/of_tokens/print.h>*/

#include <named/grammar/new.h>
#include <named/tokenset/new.h>

#include <heap/push.h>

#include "../../shared/struct.h"
/*#include "../../add_dep.h"*/
/*#include "../../lookup_tokenset.h"*/

#include "../../gegex_to_trie/new.h"

#include "../build_trie/new.h"

#include "../explore_firsts/new.h"
#include "../percolate_firsts/new.h"
#include "../explore_lookaheads/new.h"
#include "../percolate_lookaheads/new.h"
#include "../add_reductions/new.h"

#include "struct.h"
#include "process.h"

void setup_trie_task_process(struct task* super, struct yacc_shared* shared)
{
	struct setup_trie_task* const this = (void*) super;
	ENTER;
	
	dpv(this->node);
	
	dpvs(this->name);
	
	char* name;
	
	if (this->name)
		name = sstrdup(this->name);
	else
		name = sasprintf("(trie #%u)", shared->next_trie_id++);
	
	dpvs(name);
	
	struct gegex* trie = new_gegex(this->scratchpad);
	
	safe_avl_insert(shared->gegex_to_trie, new_gegex_to_trie(this->node, name));
	
	safe_avl_insert(shared->new_grammar, new_named_grammar(name, trie));
	
	heap_push(shared->todo, new_build_trie_task(this->scratchpad, name, trie, this->node, trie, 0));
	
	{
		struct tokenset* firsts = new_tokenset();
		struct tokenset* lookaheads = new_tokenset();
		
		if (strequals(name, "(start)"))
		{
			assert(shared->EOF_token_id);
			tokenset_add(lookaheads, shared->EOF_token_id);
		}
		
		safe_avl_insert(shared->firsts.sets, new_named_tokenset(name, firsts));
		safe_avl_insert(shared->lookaheads.sets, new_named_tokenset(name, lookaheads));
		
		heap_push(shared->todo, new_explore_firsts_task(trie, name, trie));
		heap_push(shared->todo, new_percolate_firsts_task(name));
		
		heap_push(shared->todo, new_explore_lookaheads_task(trie, name, trie, NULL, this->scratchpad));
		
		heap_push(shared->todo, new_percolate_lookaheads_task(name));
		
		// heap_push(todo, new_add_reductions_task(ng->name, scratchpad)); //
		
		// heap.push(new lambda_subgrammars()) //
	}
	
	this->built_name = name;
	
	EXIT;
}
















