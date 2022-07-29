
#include <debug.h>

#include <lex/phase_counter.h>

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
			
			char value[10];
			
			if (isalnum(transition->value) || index(":_-[]{},", transition->value))
				sprintf(value, "'%c'", transition->value);
			else switch (transition->value) {
				case '\\': sprintf(value, "'\\\\\\\\'"); break;
				case '\n': sprintf(value, "'\\\\n'"); break;
				case '\"': sprintf(value, "'\\\\\\\"'"); break;
				default: sprintf(value, "\\\\x%02hhX", transition->value); break;
			}
			
			dpvs(value);
			
			fprintf(out, ""
				"\"%p-%p\" -> \"%p-%p\" [" "\n"
					"\t" "label = \"%s\"" "\n"
				"]" "\n"
			"", prefix, state, prefix, transition->to, value);
		}
		
		// default transition?:
		if (state->default_transition_to)
		{
			TODO;
			#if 0
			struct lex_state* to = state->default_transition_to;
			
			helper(
				/* out: */ out,
				/* state:  */ to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"\"" "\n"
				"]" "\n"
			"", state, to);
			#endif
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

















