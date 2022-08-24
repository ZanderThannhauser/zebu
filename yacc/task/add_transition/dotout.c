
#include <stdio.h>
#include <debug.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>

#include <avl/tree_t.h>

/*#include <avl/search.h>*/

/*#include <named/grammar/struct.h>*/

#include <set/of_tokens/to_string.h>

#include <yacc/state/struct.h>

/*#include <misc/phase_counters.h>*/

#include <misc/frame_counter.h>

#include "../../shared/struct.h"
#include "../../stateinfo_to_state/struct.h"

#include "struct.h"
#include "dotout.h"

#ifdef DOTOUT

void add_transition_task_dotout(struct task* super, struct yacc_shared* shared)
{
	struct add_transition_task* const this = (void*) super;
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	dpvs(path);
	
	FILE* out = fopen(path, "w");
	assert(out);
	
	fprintf(out, "digraph {" "\n");
	
	fprintf(out, "\t" "rankdir = LR;" "\n");
	
	assert(shared->yacc_start);
	
	fprintf(out, ""
		"\"<start>\" [" "\n"
			"\t" "shape = point" "\n"
			"\t" "color = white" "\n"
			"\t" "label = \"\"" "\n"
		"];" "\n"
		"\"<start>\" -> \"%p\";" "\n"
	"", shared->yacc_start);
	
	unsigned counter = 0;
	
	for (struct avl_node_t* node = shared->stateinfo_to_state->head; node; node = node->next)
	{
		struct stateinfo_to_state* ele = node->item;
		
		fprintf(out, ""
			"\"%p\" [ " "\n"
				"\t" "shape = square" "\n"
				"\t" "label = \"\"" "\n"
				"\t" "style = \"%s\"" "\n"
			"];" "\n"
		"", ele->state, ele->stateinfo == this->stateinfo ? "bold" : "");
		
		for (unsigned i = 0, n = ele->state->transitions.n; i < n; i++)
		{
			struct ytransition* const yt = ele->state->transitions.data[i];
			
			char* token_value = tokenset_to_string(yt->value);
			
			if (yt->to)
			{
				fprintf(out, ""
					"\"%p\" -> \"%p\" [" "\n"
						"\t" "label = \"%s\"" "\n"
					"];" "\n"
				"", ele->state, yt->to, token_value);
			}
			else
			{
				
				fprintf(out, ""
					"\"%p\" -> \"_%u\" [" "\n"
						"\t" "label = \"%s\"" "\n"
					"];" "\n"
					"\"_%u\" [" "\n"
						"\t" "shape = box" "\n"
						"\t" "label = NULL" "\n"
					"];" "\n"
				"", ele->state, counter, token_value, counter);
				
				counter++;
			}
			
			free(token_value);
		}
		
		for (unsigned i = 0, n = ele->state->grammar_transitions.n; i < n; i++)
		{
			struct gytransition* const yt = ele->state->grammar_transitions.data[i];
			
			if (yt->to)
			{
				fprintf(out, ""
					"\"%p\" -> \"%p\" [" "\n"
						"\t" "label = \"%s\"" "\n"
					"];" "\n"
				"", ele->state, yt->to, yt->grammar);
			}
			else
			{
				fprintf(out, ""
					"\"%p\" -> \"_%u\" [" "\n"
						"\t" "label = \"%s\"" "\n"
					"];" "\n"
					"\"_%u\" [" "\n"
						"\t" "shape = box" "\n"
						"\t" "label = NULL" "\n"
					"];" "\n"
				"", ele->state, counter, yt->grammar, counter);
				
				counter++;
			}
		}
		
		for (unsigned i = 0, n = ele->state->reduction_transitions.n; i < n; i++)
		{
			struct rytransition* const rt = ele->state->reduction_transitions.data[i];
			
			char* token_value = tokenset_to_string(rt->value);
			
			fprintf(out, ""
				"\"%p\" -> \"_%u\" [" "\n"
					"\t" "style = dashed" "\n"
					"\t" "label = \"%s\"" "\n"
				"];" "\n"
				
				"\"_%u\" [" "\n"
					"\t" "shape = box" "\n"
					"\t" "label = \"%s (%u)\"" "\n"
				"];" "\n"
			"", ele->state, counter, token_value, counter, rt->reduce_as, rt->popcount);
			
			counter++;
			
			free(token_value);
		}
	}
	
	fprintf(out, "}" "\n");
	
	fclose(out);
	
	EXIT;
}

#endif


















