
#ifdef DEBUGGING

#include <debug.h>

#include <yacc/phase_counter.h>

#include <misc/frame_counter.h>

#include "state/struct.h"
#include "dotout.h"

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
				"\t" "label = \"\";" "\n"
			"]" "\n"
		"", state, state->is_reduction_point ? "doublecircle" : "circle");
		
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
		
		// lambda transitions:
		for (i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			dpv(i);
			
			struct gegex* to = state->lambda_transitions.data[i];
			
			helper(
				/* out: */ out,
				/* state:  */ to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"λ\"" "\n"
				"]" "\n"
			"", state, to);
		}
	}
	
	EXIT;
}

void gegex_dotout(struct gegex* start, struct gegex* optional_end, const char* name)
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
	
	fprintf(out, "\t" "label = \"%s\";" "\n", name);
	
	fprintf(out, "\"%p\" [ style = bold; ];" "\n", start);
	
	yacc_phase_counter++;
	
	helper(out, start);
	
	if (optional_end)
	{
		fprintf(out, ""
			"\"%p\" [" "\n"
				"\t" "shape = doublecircle;" "\n"
			"]" "\n"
		"", optional_end);
	}
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}

#endif
















