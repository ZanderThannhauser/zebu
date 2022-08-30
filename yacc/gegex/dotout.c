
#ifdef DOTOUT

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include <debug.h>

#include <misc/counters.h>

#include <set/string/to_hashtagstring.h>

#include "state/struct.h"

#include "dotout.h"

static void helper(FILE* out, struct gegex* state)
{
	ENTER;
	
	if (state->phase != phase_counter)
	{
		state->phase = phase_counter;
		
		fprintf(out, ""
			"\"%p\" [" "\n"
				"\t" "shape = %s;" "\n"
				"\t" "label = \"\";" "\n"
			"]" "\n"
		"", state, state->is_reduction_point ? "doublecircle" : "circle");
		
		// normal transitions:
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* transition = state->transitions.data[i];
			
			helper(out, transition->to);
			
			char* label = stringset_to_hashtagstring(transition->tags);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"#%u token %s\"" "\n"
				"]" "\n"
			"", state, transition->to, transition->token, label);
			
			free(label);
		}
		
		// grammar transitions:
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gegex_grammar_transition* gtransition = state->grammar_transitions.data[i];
			
			helper(out, gtransition->to);
			
			char* label = stringset_to_hashtagstring(gtransition->tags);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [ label = \"%s %s\" ]" "\n"
			"", state, gtransition->to, gtransition->grammar, label);
			
			free(label);
		}
		
		// lambda transitions:
		for (unsigned i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			dpv(i);
			
			struct gegex* const to = state->lambda_transitions.data[i];
			
			helper(out, to);
			
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
	
	phase_counter++;
	
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
	
	fclose(out);
	
	EXIT;
}

#endif















