
#include <debug.h>

#include <misc/phase_counters.h>

#include <misc/escape.h>

#include <set/of_tokens/to_string.h>

#include "struct.h"

#ifdef DEBUGGING

static void helper(FILE* out, void* prefix, struct lex_state* state)
{
	ENTER;
	
	if (state->phase != lex_phase_counter)
	{
		size_t i, n;
		
		state->phase = lex_phase_counter;
		
		fprintf(out, ""
			"\"%p-%p\" [" "\n"
				"\t" "shape = %s;" "\n"
				"\t" "label = \"\";" "\n"
			"]" "\n"
		"", prefix, state, state->accepting ? "doublecircle" : "circle");
		
		// normal transitions:
		for (i = 0, n = state->transitions.n; i < n; i++)
		{
			struct ltransition* transition = state->transitions.data[i];
			
			helper(out, prefix, transition->to);
			
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
					"\"%p-%p\" -> \"%p-%p\" [" "\n"
						"\t" "label = \"%s - %s\"" "\n"
					"]" "\n"
				"", prefix, state, prefix, transition->to, low, high);
			}
			else
			{
				char str[10];
				escape(str, value);
				dpvs(str);
				
				fprintf(out, ""
					"\"%p-%p\" -> \"%p-%p\" [" "\n"
						"\t" "label = \"%s\"" "\n"
					"]" "\n"
				"", prefix, state, prefix, transition->to, str);
			}
			
		}
		
		// default transition?:
		if (state->default_transition_to)
		{
			struct lex_state* to = state->default_transition_to;
			
			helper(out, prefix, to);
			
			fprintf(out, ""
				"\"%p-%p\" -> \"%p-%p\" [" "\n"
					"\t" "label = \"<default>\"" "\n"
				"]" "\n"
			"", prefix, state, prefix, to);
		}
		
		// EOF transition?
		if (state->EOF_transition_to)
		{
			struct lex_state* to = state->EOF_transition_to;
			
			helper(out, prefix, to);
			
			fprintf(out, ""
				"\"%p-%p\" -> \"%p-%p\" [" "\n"
					"\t" "label = \"<EOF>\"" "\n"
				"]" "\n"
			"", prefix, state, prefix, to);
		}
	}
	
	EXIT;
}

void lex_state_subdotout(
	FILE* out,
	void* prefix,
	struct lex_state* start)
{
	ENTER;
	
	lex_phase_counter++;
	
	helper(out, prefix, start);
	
	EXIT;
}

#endif

















