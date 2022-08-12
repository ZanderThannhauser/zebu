
#include <linux/limits.h>

#include <debug.h>

/*#include <avl/foreach.h>*/

/*#include <named/grammar/struct.h>*/

#include <misc/frame_counter.h>

/*#include <set/of_strs/foreach.h>*/

/*#include <set/of_tokens/to_string.h>*/

#include "../../stateinfo/dotout.h"

#include "../../shared/struct.h"
/*#include "../../get_deps.h"*/
/*#include "../../lookup_tokenset.h"*/

#include "struct.h"
#include "dotout.h"

#ifdef DEBUGGING

void percolate_lookaheads_task_dotout(struct task* super, struct yacc_shared* shared)
{
	struct percolate_lookaheads_task* const this = (void*) super;
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	dpvs(path);
	
	FILE* stream = fopen(path, "w");
	
	assert(stream);
	
	fprintf(stream, "digraph {" "\n");
	
	fprintf(stream, "\t" "rankdir = LR;" "\n");
	
	yacc_stateinfo_dotout(this->stateinfo, shared->new_grammar, stream);
	
	fprintf(stream, "}" "\n");
	
	fclose(stream);
	
	EXIT;
}

















#endif
