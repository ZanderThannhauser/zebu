
#include <stdio.h>
#include <debug.h>

#include <avl/search.h>

#include <named/grammar/struct.h>

#include <yacc/gegex/state/struct.h>

#include <misc/phase_counters.h>

#include <misc/frame_counter.h>

#include "../../shared/struct.h"

#include "../../stateinfo/dotout.h"

#include "struct.h"
#include "dotout.h"

#ifdef DEBUGGING

void expand_tree_task_dotout(struct task* super, struct yacc_shared* shared)
{
	struct expand_tree_task* const this = (void*) super;
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
