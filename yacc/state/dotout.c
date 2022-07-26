
#include <debug.h>

#include <misc/frame_counter.h>
#include <misc/phase_counter.h>

#include <set/of_tokens/to_string.h>

#include "struct.h"
#include "dotout.h"

#ifdef DEBUGGING

static void helper(FILE* out, struct yacc_state* state)
{
	ENTER;
	
	if (state->phase != phase_counter)
	{
		size_t i, n;
		
		state->phase = phase_counter;
		
		fprintf(out, ""
			"\"%p\" [" "\n"
				"\t" "shape = circle;" "\n"
				"\t" "label = \"\";" "\n"
			"]" "\n"
		"", state);
			
		// normal transitions:
		for (i = 0, n = state->transitions.n; i < n; i++)
		{
			struct ytransition* t = state->transitions.data[i];
			
			helper(out, t->to);
			
			char* label = tokenset_to_string(t->value);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"%s\"" "\n"
				"]" "\n"
			"", state, t->to, label);
			
			free(label);
		}
		
		// reduction transitions:
		for (i = 0, n = state->reduction_transitions.n; i < n; i++)
		{
			struct rytransition* t = state->reduction_transitions.data[i];
			
			char* label = tokenset_to_string(t->value);
			
			fprintf(out, ""
				"\"%p\" [" "\n"
					"\t" "shape = box;" "\n"
					"\t" "label = \"%s\";" "\n"
				"]" "\n"
			"", t->reduce_as, t->reduce_as);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "style = dashed" "\n"
					"\t" "label = \"%s\"" "\n"
				"]" "\n"
			"", state, t->reduce_as, label);
			
			free(label);
		}
		
		// grammar transitions:
		for (i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gytransition* t = state->grammar_transitions.data[i];
			
			helper(out, t->to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"%s\"" "\n"
				"]" "\n"
			"", state, t->to, t->grammar);
			
		}
		
	}
	
	EXIT;
}

void yacc_state_dotout(struct yacc_state* state)
{
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	dpvs(path);
	
	FILE* out = fopen(path, "w");
	
	if (!out)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, path);
		abort();
	}
	
	fprintf(out, "digraph {" "\n");
	
	fprintf(out, "\t" "rankdir = LR;" "\n");
	
	fprintf(out, "\"%p\" [ style = bold; ];" "\n", state);
	
	phase_counter++;
	
	helper(out, state);
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}

#endif
