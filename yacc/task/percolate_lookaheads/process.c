
#include <debug.h>

/*#include <parser/production/gegex/state/struct.h>*/

/*#include <tokenset/add.h>*/
#include <set/of_tokens/update.h>

#include <set/of_gegexes/foreach.h>

#include <heap/push.h>

#include "../../shared/struct.h"
/*#include "../../add_dep.h"*/
/*#include "../../get_deps.h"*/
/*#include "../../lookup_tokenset.h"*/

#include "../../stateinfo/get.h"

#include "../../lookahead_deps/get_deps_on.h"
#include "../../lookahead_deps/get_deps_of.h"

#include "struct.h"
#include "new.h"
#include "process.h"

void percolate_lookaheads_task_process(struct task* super, struct yacc_shared* shared)
{
	struct percolate_lookaheads_task* const this = (void*) super;
	ENTER;
	
	struct tokenset* lookaheads = yacc_stateinfo_get(this->stateinfo, this->state);
	
	bool changed = false;
	
	struct gegexset* deps = lookahead_get_deps_on(this->ldeps, this->state);
	
	if (deps)
	{
		gegexset_foreach(deps, ({
			void runme(struct gegex* substate) {
				struct tokenset* dep_lookaheads = yacc_stateinfo_get(this->stateinfo, substate);
				
				if (tokenset_update(lookaheads, dep_lookaheads)) {
					changed = true;
				}
			}
			runme;
		}));
	}
	
	dpvb(changed);
	
	if (changed)
	{
		struct gegexset* of = lookahead_get_deps_of(this->ldeps, this->state);
		
		if (of)
		{
			gegexset_foreach(of, ({
				void runme(struct gegex* substate) {
					#ifdef WITH_ARENAS
					heap_push(shared->todo, new_percolate_lookaheads_task(shared->arena, this->stateinfo, substate, this->ldeps));
					#else
					heap_push(shared->todo, new_percolate_lookaheads_task(this->stateinfo, substate, this->ldeps));
					#endif
				}
				runme;
			}));
		}
	}
	
	EXIT;
}
















