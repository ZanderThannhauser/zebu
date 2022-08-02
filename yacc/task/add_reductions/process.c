
#include <debug.h>

#include <memory/arena/strdup.h>

#include <yacc/gegex/state/add_reduction_transition.h>

#include <set/of_tokens/foreach.h>

#include "../../shared/struct.h"
#include "../../lookup_tokenset.h"

#include "struct.h"
#include "process.h"

void add_reductions_task_process(struct task* super, struct yacc_shared* shared)
{
	struct add_reductions_task* const this = (void*) super;
	ENTER;
	
	dpvs(this->name);
	
	TODO;
	#if 0
	struct tokenset* lookaheads = lookup_tokenset(shared->lookaheads.sets, this->name);
	
	char* dup = arena_strdup(this->scratchpad, this->name);
	
	tokenset_foreach(lookaheads, ({
		void runme(unsigned token)
		{
			dpv(token);
			
			gegex_add_reduction_transition(this->end, this->scratchpad, token, dup);
		}
		runme;
	}));
	#endif
	
	EXIT;
}
















