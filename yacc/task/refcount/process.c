
#include <debug.h>

/*#include <avl/search.h>*/
/*#include <avl/safe_insert.h>*/

#include <yacc/gegex/state/struct.h>

/*#include <set/of_tokens/add.h>*/
/*#include <set/of_tokens/print.h>*/

#include <heap/push.h>

#include "../../shared/struct.h"
/*#include "../../add_dep.h"*/
/*#include "../../lookup_tokenset.h"*/

#include "../setup_trie/new.h"

#include "struct.h"
#include "new.h"
#include "process.h"

void refcount_task_process(struct task* super, struct yacc_shared* shared)
{
	struct refcount_task* const this = (void*) super;
	ENTER;
	
	dpv(this->node);
	
	switch (this->node->refcount)
	{
		case 0:
		{
			for (unsigned i = 0, n = this->node->transitions.n; i < n; i++)
			{
				struct gegex* to = this->node->transitions.data[i]->to;
				
				#ifdef WITH_ARENAS
				heap_push(shared->todo, new_refcount_task(shared->arena, this->start, to));
				#else
				heap_push(shared->todo, new_refcount_task(this->start, to));
				#endif
			}
			
			for (unsigned i = 0, n = this->node->grammar_transitions.n; i < n; i++)
			{
				struct gegex* to = this->node->grammar_transitions.data[i]->to;
				
				#ifdef WITH_ARENAS
				heap_push(shared->todo, new_refcount_task(shared->arena, this->start, to));
				#else
				heap_push(shared->todo, new_refcount_task(this->start, to));
				#endif
			}
			
			break;
		}
		
		case 1: if (this->start != this->node)
		{
			#ifdef WITH_ARENAS
			heap_push(shared->todo, new_setup_trie_task(shared->arena, this->node, false));
			#else
			heap_push(shared->todo, new_setup_trie_task(this->node, false));
			#endif
			break;
		}
		
		default:
		{
			break;
		}
	}
	
	this->node->refcount++;
	
	EXIT;
}
















