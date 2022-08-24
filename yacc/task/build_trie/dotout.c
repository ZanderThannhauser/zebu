
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <debug.h>

#include <avl/search.h>

#include <yacc/gegex/state/struct.h>

#include <misc/phase_counters.h>

#include <misc/frame_counter.h>

#include "../../shared/struct.h"

#include "struct.h"
#include "dotout.h"

#ifdef DOTOUT

static void helper(FILE* out, struct gegex* state)
{
	ENTER;
	
	if (state->phase != yacc_phase_counter)
	{
		size_t i, n;
		
		state->phase = yacc_phase_counter;
		
		fprintf(out, ""
			"\"%p\" [" "\n"
				"\t" "shape = %s;" "\n"
				"\t" "style = filled;" "\n"
				"\t" "color = black;" "\n"
				"\t" "fillcolor = white;" "\n"
				"\t" "label = \"%u (%u)\";" "\n"
			"]" "\n"
		"", state, state->is_reduction_point ? "doublecircle" : "circle", state->refcount, state->popcount);
		
		// normal transitions:
		for (i = 0, n = state->transitions.n; i < n; i++)
		{
			struct transition* transition = state->transitions.data[i];
			
			helper(out, transition->to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"#%u token\"" "\n"
				"]" "\n"
			"", state, transition->to, transition->token);
		}
		
		// grammar transitions:
		for (i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gtransition* gtransition = state->grammar_transitions.data[i];
			
			helper(out, gtransition->to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"%s\"" "\n"
				"]" "\n"
			"", state, gtransition->to, gtransition->grammar);
		}
	}
	
	EXIT;
}

void build_trie_task_dotout(struct task* super, struct yacc_shared* shared)
{
	struct build_trie_task* const this = (void*) super;
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	dpvs(path);
	
	FILE* out = fopen(path, "w");
	assert(out);
	
	fprintf(out, "digraph {" "\n");
	
	fprintf(out, "\t" "rankdir = LR;" "\n");
	
	fprintf(out, "\t" "label = \"%s, pop_count: %u\";" "\n", this->name, this->popcount);
	
	yacc_phase_counter++;
	
	helper(out, this->start);
	
	fprintf(out, "\"%p\" [ style = bold ];" "\n", this->start);
	
	fprintf(out, "\"%p\" [ fillcolor = grey ];" "\n", this->building);
	
	fprintf(out, "}" "\n");
	
	fclose(out);
	
	EXIT;
}

















#endif
