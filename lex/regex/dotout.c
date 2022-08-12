
#ifdef DEBUGGING

#include <debug.h>

#include <misc/phase_counters.h>

#include <misc/frame_counter.h>
#include <misc/escape.h>

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
					"\t" "peripheries = %u;" "\n"
				"]" "\n"
			"", state, state->is_accepting, 2 + state->priority);
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
			
			helper(out, transition->to);
			
			unsigned value = transition->value;
			
			dpvc(value);
			
			if (true
				&& i + 1 < n
				&& value + 1 == state->transitions.data[i + 1]->value
				&& transition->to == state->transitions.data[i + 1]->to)
			{
				do i++; while (true
					&& i + 1 < n
					&& state->transitions.data[i]->value + 1 == state->transitions.data[i + 1]->value
					&& transition->to == state->transitions.data[i + 1]->to);
				
				unsigned value2 = state->transitions.data[i]->value;
				
				dpvc(value2);
				
				char low[10], high[10];
				escape(low, value);
				escape(high, value2);
				
				fprintf(out, ""
					"\"%p\" -> \"%p\" [" "\n"
						"\t" "label = \"%s - %s\"" "\n"
					"]" "\n"
				"", state, transition->to, low, high);
			}
			else
			{
				char str[10];
				escape(str, value);
				dpvs(str);
				
				fprintf(out, ""
					"\"%p\" -> \"%p\" [" "\n"
						"\t" "label = \"%s\"" "\n"
					"]" "\n"
				"", state, transition->to, str);
			}
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
					"\t" "label = \"<default>\"" "\n"
				"]" "\n"
			"", state, to);
		}
		
		// EOF transition?
		if (state->EOF_transition_to)
		{
			struct regex* to = state->EOF_transition_to;
			
			helper(out, to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"<EOF>\"" "\n"
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

void regex_dotout(struct regex* state, const char* name)
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
	
	fprintf(out, "\"%p\" [ style = bold; ];" "\n", state);
	
	lex_phase_counter++;
	
	helper(out, state);
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}

#endif
















