
#ifdef DEBUGGING

#include <debug.h>

#include <misc/phase_counter.h>
#include <misc/frame_counter.h>

#include <set/of_regexes/foreach.h>

#include <set/of_tokens/to_string.h>

#include "state/struct.h"
#include "dotout.h"

static void helper(FILE* out, struct regex* state)
{
	ENTER;
	
	if (state->phase != phase_counter)
	{
		size_t i, n;
		
		state->phase = phase_counter;
		
		if (state->is_accepting)
		{
			fprintf(out, ""
				"\"%p\" [" "\n"
					"\t" "shape = doublecircle;" "\n"
					"\t" "label = \"%u\";" "\n"
				"]" "\n"
			"", state, state->is_accepting);
		}
		else
		{
			fprintf(out, ""
				"\"%p\" [" "\n"
					"\t" "shape = circle;" "\n"
					"\t" "label = \"\";" "\n"
				"]" "\n"
			"", state);
		}
		
		// normal transitions:
		for (i = 0, n = state->transitions.n; i < n; i++)
		{
			struct transition* transition = state->transitions.data[i];
			
			helper(
				/* out: */ out,
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
			
			struct regex* to = state->lambda_transitions.data[i];
			
			helper(
				/* out: */ out,
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
			struct regex* to = state->default_transition_to;
			
			helper(
				/* out: */ out,
				/* state:  */ to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"\"" "\n"
				"]" "\n"
			"", state, to);
		}
	}
	
	EXIT;
}

void regex_dotout_set(struct regexset* set)
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
	
	phase_counter++;
	
	regexset_foreach(set, ({
		void runme(struct regex* state) {
			fprintf(out, "\"%p\" [ style = bold; ];" "\n", state);
			
			helper(out, state);
		}
		runme;
	}));
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}

void regex_dotout(struct regex* state)
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
















