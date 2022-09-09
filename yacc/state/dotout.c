
#ifdef DOTOUT

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <debug.h>

#include <string/struct.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/len.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/unsigned/to_string.h>

#include <set/yaccstate/new.h>
#include <set/yaccstate/add.h>
#include <set/yaccstate/free.h>

#include <misc/frame_counter.h>

#include <yacc/reductioninfo/to_string.h>

#include "struct.h"
#include "dotout.h"

void yacc_state_dotout(
	struct yacc_state* start)
{
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	FILE* stream = fopen(path, "w");
	
	fprintf(stream, "digraph {\n");
	
	fprintf(stream, "rankdir = LR\n");
	
	struct yaccstateset* queued = new_yaccstateset();
	
	struct quack* todo = new_quack();
	
	quack_append(todo, start);
	
	unsigned reduce_counter = 0;
	
	while (quack_len(todo))
	{
		struct yacc_state* const state = quack_pop(todo);
		
		fprintf(stream, ""
			"\"%p\" [" "\n"
				"label = \"\"" "\n"
				"shape = circle" "\n"
			"]" "\n"
		"", state);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct yacc_state_transition* const ele = state->transitions.data[i];
			
			char* label = unsignedset_to_string(ele->on);
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [" "\n"
					"label = \"%s\"" "\n"
					"color = \"black:black\"" "\n"
				"]" "\n"
			"", state, ele->to, label);
			
			free(label);
			
			if (yaccstateset_add(queued, ele->to))
				quack_append(todo, ele->to);
		}
		
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct yacc_state_grammar_transition* const ele = state->grammar_transitions.data[i];
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [" "\n"
					"label = \"%s\"" "\n"
					"color = \"black:black\"" "\n"
				"]" "\n"
			"", state, ele->to, ele->grammar->chars);
			
			if (yaccstateset_add(queued, ele->to))
				quack_append(todo, ele->to);
		}
		
		for (unsigned i = 0, n = state->reduce_transitions.n; i < n; i++)
		{
			struct yacc_state_reduce_transition* const ele = state->reduce_transitions.data[i];
			
			char* label = unsignedset_to_string(ele->on);
			
			char* rinfo = reductioninfo_to_string(ele->reductioninfo);
			
			fprintf(stream, ""
				"\"%p\" -> \"reduce_%u\" [" "\n"
					"label = \"%s\"" "\n"
					"style = dashed" "\n"
				"]" "\n"
			"", state, reduce_counter, label);
			
			fprintf(stream, ""
				"\"reduce_%u\" [" "\n"
					"label = \"{reduce_as = %s} | %s\"" "\n"
					"shape = record" "\n"
				"]" "\n"
			"", reduce_counter, ele->reduce_as->chars, rinfo ?: "");
			
			reduce_counter++;
			
			free(label);
			free(rinfo);
		}
	}
	
	free_quack(todo);
	
	free_yaccstateset(queued);
	
	fprintf(stream, "}\n");
	
	fclose(stream);
	
	EXIT;
}
























#endif
