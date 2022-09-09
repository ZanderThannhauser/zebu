
#ifdef DOTOUT

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include <debug.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/len.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/gegex/new.h>
#include <set/gegex/add.h>
#include <set/gegex/free.h>

#include <misc/frame_counter.h>

#include <string/struct.h>

#include <yacc/structinfo/to_hashtagstring.h>

#include "state/struct.h"

#include "dotout.h"

void gegex_dotout(struct gegex* start, struct gegex* optional_end, const char* name)
{
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	dpvs(path);
	
	FILE* out = fopen(path, "w");
	
	if (!out)
	{
		fprintf(stderr, "zebu: fopen(\"%s\"): %m\n", path);
		abort();
	}
	
	fprintf(out, "digraph {" "\n");
	
	fprintf(out, "\t" "rankdir = LR;" "\n");
	
	fprintf(out, "\t" "label = \"%s\";" "\n", name);
	
	fprintf(out, "\"%p\" [ style = bold; ];" "\n", start);
	
	struct gegexset* queued = new_gegexset();
	
	struct quack* todo = new_quack();
	
	gegexset_add(queued, start);
	
	quack_append(todo, start);
	
	while (quack_len(todo))
	{
		struct gegex* state = quack_pop(todo);
		
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
			
			char* label = structinfo_to_hashtagstring(transition->structinfo);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"#%u token %s\"" "\n"
				"]" "\n"
			"", state, transition->to, transition->token, label);
			
			free(label);
			
			if (gegexset_add(queued, transition->to))
				quack_append(todo, transition->to);
			
		}
		
		// grammar transitions:
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gegex_grammar_transition* gtransition = state->grammar_transitions.data[i];
			
			if (gegexset_add(queued, gtransition->to))
				quack_append(todo, gtransition->to);
			
			char* label = structinfo_to_hashtagstring(gtransition->structinfo);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [ label = \"%s %s\" ]" "\n"
			"", state, gtransition->to, gtransition->grammar->chars, label);
			
			free(label);
		}
		
		// lambda transitions:
		for (unsigned i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			struct gegex* const to = state->lambda_transitions.data[i];
			
			if (gegexset_add(queued, to))
				quack_append(todo, to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"λ\"" "\n"
				"]" "\n"
			"", state, to);
		}
	}
	
	free_quack(todo);
	
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















