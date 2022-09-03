
#ifdef DOTOUT

#include <debug.h>

#include <set/lexstate/new.h>
#include <set/lexstate/add.h>
#include <set/lexstate/free.h>

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
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, path);
		abort();
	}
	
	fprintf(stream, "digraph {" "\n");
	
	fprintf(stream, "\t" "rankdir = LR;" "\n");
	
	fprintf(stream, "\"%p\" [ style = bold; ];" "\n", start);
	
	struct lexstateset* queued = new_lexstateset();
	
	struct quack* todo = new_quack();
	
	lexstateset_add(queued, start);
	
	quack_append(todo, start);
	
	while (quack_len(todo))
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
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct lex_transition* const ele = state->transitions.data[i];
			
			char str[10];
			
			escape(str, ele->value);
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [" "\n"
					"label = \"%s\"" "\n"
				"]" "\n"
			"", state, ele->to, str);
			
			if (lexstateset_add(queued, ele->to))
				quack_append(todo, ele->to);
		}
		
		if (state->default_transition_to)
		{
			TODO;
		}
		
		if (state->EOF_transition_to)
		{
			struct lex_state* const to = state->EOF_transition_to;
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [" "\n"
					"label = \"<EOF>\"" "\n"
				"]" "\n"
			"", state, to);
			
			if (lexstateset_add(queued, to))
				quack_append(todo, to);
		}
	}
	
	free_lexstateset(queued);
	
	fprintf(stream, "}" "\n");
	
	fclose(stream);
	
	EXIT;
}


#endif









