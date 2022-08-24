
#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

#include <debug.h>

#include <macros/strequals.h>

/*#include <avl/search.h>*/
#include <avl/insert.h>

#include <yacc/gegex/state/struct.h>
#include <yacc/gegex/state/new.h>

#include <arena/strdup.h>
#include <arena/asprintf.h>

/*#include <set/of_tokens/new.h>*/
/*#include <set/of_tokens/add.h>*/
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

#include "struct.h"
#include "process.h"

void setup_trie_task_process(struct task* super, struct yacc_shared* shared)
{
	struct setup_trie_task* const this = (void*) super;
	ENTER;
	
	dpv(this->node);
	
	dpvs(this->name);
	
	char* name;
	
	#ifdef WITH_ARENAS
	struct memory_arena* const arena = shared->arena;
	
	if (this->name)
		name = arena_strdup(arena, this->name);
	else
		name = arena_asprintf(arena, "(trie #%u)", shared->next_trie_id++);
	#else
	
	if (this->name)
		name = strdup(this->name);
	else
	{
		int val = asprintf(&name, "(trie #%u)", shared->next_trie_id++);
		
		if (val < 0)
			abort();
	}
	
	#endif
	
	dpvs(name);
	
	#ifdef WITH_ARENAS
	struct gegex* trie = new_gegex(arena);
	#else
	struct gegex* trie = new_gegex();
	#endif
	
	#ifdef WITH_ARENAS
	avl_insert(shared->gegex_to_trie, new_gegex_to_trie(arena, this->node, name));
	#else
	avl_insert(shared->gegex_to_trie, new_gegex_to_trie(this->node, name));
	#endif
	
	#ifdef WITH_ARENAS
	avl_insert(shared->new_grammar, new_named_grammar(arena, name, trie));
	#else
	avl_insert(shared->new_grammar, new_named_grammar(name, trie));
	#endif
	
	#ifdef WITH_ARENAS
	heap_push(shared->todo, new_build_trie_task(arena, name, trie, this->node, trie, 0));
	#else
	heap_push(shared->todo, new_build_trie_task(name, trie, this->node, trie, 0));
	#endif
	
	#ifdef WITH_ARENAS
	heap_push(shared->todo, new_explore_firsts_task(arena, trie, name, trie));
	#else
	heap_push(shared->todo, new_explore_firsts_task(trie, name, trie));
	#endif
	
	#ifdef WITH_ARENAS
	heap_push(shared->todo, new_percolate_firsts_task(arena, name));
	#else
	heap_push(shared->todo, new_percolate_firsts_task(name));
	#endif
	
	this->built_name = name;
	
	EXIT;
}
















