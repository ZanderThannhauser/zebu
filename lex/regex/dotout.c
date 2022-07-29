
#ifdef DEBUGGING

#include <debug.h>

#include <lex/phase_counter.h>

#include <misc/frame_counter.h>

#include <set/of_regexes/foreach.h>

#include <set/of_tokens/to_string.h>

#include "state/struct.h"
#include "dotout.h"

static void helper(FILE* out, struct regex* state)
{
	if (state->phase != lex_phase_counter)
	{
		size_t i, n;
		
		state->phase = lex_phase_counter;
		
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
			
			char value[10];
			
			if (isalnum(transition->value) || index(":-_", transition->value))
				sprintf(value, "'%c'", transition->value);
			else switch (transition->value) {
				case '\\': sprintf(value, "'\\\\\\\\'"); break;
				case '\n': sprintf(value, "'\\\\n'"); break;
				default: sprintf(value, "'\\\\x%02hhX'", transition->value); break;
			}
			
			dpvs(value);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"%s\"" "\n"
				"]" "\n"
			"", state, transition->to, value);
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
	
	lex_phase_counter++;
	
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
	
	lex_phase_counter++;
	
	helper(out, state);
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}

#endif
















