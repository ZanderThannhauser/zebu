
#include <debug.h>

#include <misc/phase_counter.h>
#include <misc/frame_counter.h>

#include <set/of_tokens/to_string.h>

#include "struct.h"

#ifdef DEBUGGING

static void helper(FILE* out, struct lex_state* state)
{
	ENTER;
	
	if (state->phase != phase_counter)
	{
		size_t i, n;
		
		state->phase = phase_counter;
		
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
			
			helper(
				/* out: */ out,
				/* state:  */ transition->to);
			
			char value[10];
			
			if (isalnum(transition->value) || index(":_-", transition->value))
				sprintf(value, "'%c'", transition->value);
			else switch (transition->value) {
				case '\\': sprintf(value, "'\\\\\\\\'"); break;
				case '\n': sprintf(value, "'\\\\n'"); break;
				default: sprintf(value, "\\\\x%02hhX", transition->value); break;
			}
			
			dpvs(value);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"%s\"" "\n"
				"]" "\n"
			"", state, transition->to, value);
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
					"\t" "label = \"\"" "\n"
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
	
	phase_counter++;
	
	helper(out, state);
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}

#endif

















