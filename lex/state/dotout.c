
#include <debug.h>

#include <misc/phase_counters.h>

#include <misc/escape.h>

#include <misc/frame_counter.h>

#include <set/of_tokens/to_string.h>

#include "struct.h"

#ifdef DOTOUT

static void helper(FILE* out, struct lex_state* state)
{
	ENTER;
	
	if (state->phase != lex_phase_counter)
	{
		size_t i, n;
		
		state->phase = lex_phase_counter;
		
		{
			char* label = NULL;
			
			if (state->accepting)
				label = tokenset_to_string(state->accepting);
			
			fprintf(out, ""
				"\"%p\" [" "\n"
					"\t" "shape = %s;" "\n"
					"\t" "label = \"%s\";" "\n"
				"]" "\n"
			"", state, state->accepting ? "doublecircle" : "circle", label ?: "");
			
			free(label);
		}
		
		// normal transitions:
		for (i = 0, n = state->transitions.n; i < n; i++)
		{
			struct ltransition* transition = state->transitions.data[i];
			
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
		
		// default transition?:
		if (state->default_transition_to)
		{
			struct lex_state* to = state->default_transition_to;
			
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
			struct lex_state* to = state->EOF_transition_to;
			
			helper(out, to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"<EOF>\"" "\n"
				"]" "\n"
			"", state, to);
		}
	}
	
	EXIT;
}

void lex_state_dotout(
	struct lex_state* state)
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

















