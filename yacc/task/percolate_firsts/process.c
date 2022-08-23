
#include <debug.h>

/*#include <parser/production/gegex/state/struct.h>*/

/*#include <tokenset/add.h>*/

#include <set/of_strs/foreach.h>

#include <set/of_tokens/update.h>

#include <heap/push.h>

#include "../../shared/struct.h"
/*#include "../../shared/add_firsts_dep.h"*/
#include "../../shared/get_firsts_deps.h"
#include "../../shared/lookup_firsts.h"

#include "struct.h"
#include "new.h"
#include "process.h"

void percolate_firsts_task_process(struct task* super, struct yacc_shared* shared)
{
	struct percolate_firsts_task* const this = (void*) super;
	ENTER;
	
	dpvs(this->name);
	
	struct tokenset* firsts = shared_lookup_firsts(shared, this->name);
	
	bool changed = false;
	
	struct strset* deps = get_firsts_deps(shared, shared->firsts.dependant_on, this->name);
	
	strset_foreach(deps, ({
		void runme(const char* dep) {
			struct tokenset* dep_firsts = shared_lookup_firsts(shared, dep);
			
			if (tokenset_update(firsts, dep_firsts))
			{
				changed = true;
			}
		}
		runme;
	}));
	
	if (changed)
	{
		struct strset* of = get_firsts_deps(shared, shared->firsts.dependant_of, this->name);
		
		strset_foreach(of, ({
			void runme(const char* dep) {
				#ifdef WITH_ARENAS
				heap_push(shared->todo, new_percolate_firsts_task(shared->arena, dep));
				#else
				heap_push(shared->todo, new_percolate_firsts_task(dep));
				#endif
			}
			runme;
		}));
	}
	
	EXIT;
}
















