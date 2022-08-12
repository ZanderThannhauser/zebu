
#if 0
#include <stdio.h>

#include <linux/limits.h>

#include <debug.h>

#include <avl/search.h>

#include <named/grammar/struct.h>

#include <yacc/gegex/state/struct.h>

#include <misc/frame_counter.h>

#include <yacc/phase_counter.h>

/*#include <strset/foreach.h>*/

/*#include <tokenset/to_string.h>*/

#include "../../shared/struct.h"
/*#include "../../get_deps.h"*/
/*#include "../../lookup_tokenset.h"*/

#include "struct.h"
#include "dotout.h"

#ifdef DEBUGGING

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
				"\t" "label = \"(%u)\";" "\n"
			"]" "\n"
		"", state, state->is_reduction_point ? "doublecircle" : "circle", state->popcount);
		
		
		// normal transitions:
		for (i = 0, n = state->transitions.n; i < n; i++)
		{
			struct transition* transition = state->transitions.data[i];
			
			helper(
				/* out: */ out,
				/* state:  */ transition->to);
			
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
			
			helper(
				/* out: */ out,
				/* state:  */ gtransition->to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"%s\"" "\n"
				"]" "\n"
			"", state, gtransition->to, gtransition->grammar);
		}
		
		// reduction transitions:
		for (i = 0, n = state->reduction_transitions.n; i < n; i++)
		{
			struct rtransition* rtransition = state->reduction_transitions.data[i];
			
			fprintf(out, ""
				"\"%p\" [" "\n"
					"\t" "shape = box;" "\n"
					"\t" "label = \"%s\";" "\n"
				"]" "\n"
			"", rtransition->reduce_as, rtransition->reduce_as);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "style = dashed" "\n"
					"\t" "label = \"#%u token (%u)\"" "\n"
				"]" "\n"
			"", state, rtransition->reduce_as, rtransition->token, rtransition->popcount);
		}
	}
	
	EXIT;
}

void add_reductions_task_dotout(struct task* super, struct yacc_shared* shared)
{
	struct add_reductions_task* const this = (void*) super;
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	dpvs(path);
	
	FILE* out = fopen(path, "w");
	
	assert(out);
	
	fprintf(out, "digraph {" "\n");
	
	fprintf(out, "\t" "rankdir = LR;" "\n");
	
	yacc_phase_counter++;
	
	struct avl_node_t* node = avl_search(shared->new_grammar, &this->name);
	
	struct named_grammar* ng = node->item;
	
	helper(out, ng->grammar);
	
	fprintf(out, "\"%p\" [ shape = square ];" "\n", ng->grammar);
	
	fprintf(out, "}" "\n");
	
	fclose(out);
	
	EXIT;
}


















#endif
#endif
