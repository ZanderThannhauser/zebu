
#include <debug.h>

/*#include <parser/production/gegex/state/struct.h>*/

/*#include <tokenset/add.h>*/
#include <tokenset/update.h>

#include <strset/foreach.h>

#include <heap/push.h>

#include "../../shared.h"
/*#include "../../add_dep.h"*/
#include "../../get_deps.h"
#include "../../lookup_tokenset.h"

#include "struct.h"
#include "new.h"
#include "process.h"

void percolate_lookaheads_task_process(struct task* super, struct shared* shared)
{
	struct percolate_lookaheads_task* const this = (void*) super;
	ENTER;
	
	dpvs(this->name);
	
	// percolate_lookaheads_task(grammar):
		// tuple = ("percolate-lookahead", node);
		// if tuple in done: return set();
		// before = lookaheads[grammar];
		// after = before.copy();
		// for dep in lookaheads.dependant_on[grammar]:
			// after.update(lookaheads[dep]);
		// todo = set();
		// if before != after:
			// for dep in lookaheads.dependant_of[grammar]:
				// todo.add(percolate_lookahead_task(dep));
		// return todo;
	
	struct tokenset* lookaheads = lookup_tokenset(shared->lookaheads.sets, this->name);
	
	bool changed = false;
	
	struct strset* deps = get_deps(shared->lookaheads.dependant_on, this->name);
	
	strset_foreach(deps, ({
		void runme(const char* dep) {
			struct tokenset* dep_lookaheads = lookup_tokenset(shared->lookaheads.sets, dep);
			
			if (tokenset_update(lookaheads, dep_lookaheads))
				changed = true;
		}
		runme;
	}));
	
	if (changed)
	{
		struct strset* of = get_deps(shared->lookaheads.dependant_of, this->name);
		
		strset_foreach(of, ({
			void runme(const char* dep) {
				heap_push(shared->todo, new_percolate_lookaheads_task(dep));
			}
			runme;
		}));
	}
	
	EXIT;
}
















