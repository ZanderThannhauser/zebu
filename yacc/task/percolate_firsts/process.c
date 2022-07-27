
#include <debug.h>

/*#include <parser/production/gegex/state/struct.h>*/

/*#include <tokenset/add.h>*/

#include <set/of_strs/foreach.h>

#include <set/of_tokens/update.h>

#include <heap/push.h>

#include "../../shared/struct.h"
/*#include "../../add_dep.h"*/
#include "../../get_deps.h"
#include "../../lookup_tokenset.h"

#include "struct.h"
#include "new.h"
#include "process.h"

void percolate_firsts_task_process(struct task* super, struct yacc_shared* shared)
{
	struct percolate_firsts_task* const this = (void*) super;
	ENTER;
	
	dpvs(this->name);
	
	struct tokenset* firsts = lookup_tokenset(shared->firsts.sets, this->name);
	
	bool changed = false;
	
	struct strset* deps = get_deps(shared->firsts.dependant_on, this->name);
	
	strset_foreach(deps, ({
		void runme(const char* dep) {
			struct tokenset* dep_firsts = lookup_tokenset(shared->firsts.sets, dep);
			
			if (tokenset_update(firsts, dep_firsts))
				changed = true;
		}
		runme;
	}));
	
	if (changed)
	{
		struct strset* of = get_deps(shared->firsts.dependant_of, this->name);
		
		strset_foreach(of, ({
			void runme(const char* dep) {
				heap_push(shared->todo, new_percolate_firsts_task(dep));
			}
			runme;
		}));
	}
	
	EXIT;
}
















