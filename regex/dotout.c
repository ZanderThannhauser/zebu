
#ifdef DEBUGGING

#include <debug.h>

#include "state/struct.h"

#include "dotout.h"

static void helper(
	FILE* out,
	unsigned new_phase,
	struct regex_state* state)
{
	ENTER;
	
	if (state->phase != new_phase)
	{
		size_t i, n;
		
		state->phase = new_phase;
		
		fprintf(out, ""
			"\"%p\" [" "\n"
				"\t" "shape = %s;" "\n"
				"\t" "label = \"\";" "\n"
			"]" "\n"
		"", state, state->is_accepting ? "doublecircle" : "circle");
		
		// normal transitions:
		for (i = 0, n = state->transitions.n; i < n; i++)
		{
			struct transition* transition = state->transitions.data[i];
			
			helper(
				/* out: */ out,
				/* new_phase: */ new_phase,
				/* state:  */ transition->to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"%c\"" "\n"
				"]" "\n"
			"", state, transition->to, transition->value);
		}
		
		// lambda transitions:
		for (i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			dpv(i);
			
			struct regex_state* to = state->lambda_transitions.data[i];
			
			helper(
				/* out: */ out,
				/* new_phase: */ new_phase,
				/* state:  */ to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"λ\"" "\n"
				"]" "\n"
			"", state, to);
		}
		
		// default transition?:
		if (state->default_transition_to)
		{
			TODO;
		}
	}
	
	EXIT;
}

void regex_dotout(struct regex_state* state)
{
	ENTER;
	
	FILE* out = fopen("dot/regex.dot", "w");
	
	fprintf(out, "digraph {" "\n");
	
	fprintf(out, "\t" "layout = neato;" "\n");
	
	fprintf(out, "\"%p\" [ style = bold; ];" "\n", state);
	
	unsigned new_phase = state->phase + 1;
	
	helper(out, new_phase, state);
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}

#endif

