
#ifdef DOTOUT

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

#include <misc/escape.h>

#include <lex/state/struct.h>

#include <set/unsigned/to_string.h>

#include <misc/frame_counter.h>

void lex_state_dotout(
	struct lex_state* start)
{
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	dpvs(path);
	
	FILE* stream = fopen(path, "w");
	
	if (!stream)
	{
		fprintf(stderr, "zebu: fopen(\"%s\"): %m\n", path);
		abort();
	}
	
	fprintf(stream, "digraph {" "\n");
	
	fprintf(stream, "\t" "rankdir = LR;" "\n");
	
	fprintf(stream, "\"%p\" [ style = bold; ];" "\n", start);
	
	struct ptrset* queued = new_ptrset();
	
	struct quack* todo = new_quack();
	
	ptrset_add(queued, start);
	
	quack_append(todo, start);
	
	while (quack_is_nonempty(todo))
	{
		struct lex_state* state = quack_pop(todo);
		
		if (state->accepts)
		{
			char* label = unsignedset_to_string(state->accepts);
			
			fprintf(stream, ""
				"\"%p\" [" "\n"
					"label = \"%s\"" "\n"
					"shape = doublecircle" "\n"
				"]" "\n"
			"", state, label ?: "");
			
			free(label);
		}
		else
		{
			fprintf(stream, ""
				"\"%p\" [" "\n"
					"label = \"\"" "\n"
					"shape = circle" "\n"
				"]" "\n"
			"", state);
		}
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct lex_state* const to = state->transitions[i];
			
			if (to)
			{
				char str[10];
				
				escape(str, i);
				
				fprintf(stream, ""
					"\"%p\" -> \"%p\" [" "\n"
						"label = \"%s\"" "\n"
					"]" "\n"
				"", state, to, str);
				
				if (ptrset_add(queued, to))
					quack_append(todo, to);
			}
		}
		
		if (state->EOF_transition_to)
		{
			struct lex_state* const to = state->EOF_transition_to;
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [" "\n"
					"label = \"<EOF>\"" "\n"
				"]" "\n"
			"", state, to);
			
			if (ptrset_add(queued, to))
				quack_append(todo, to);
		}
	}
	
	free_ptrset(queued);
	
	fprintf(stream, "}" "\n");
	
	fclose(stream);
	
	EXIT;
}


#endif









