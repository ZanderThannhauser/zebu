
#include <debug.h>

#include <avl/foreach.h>

#include <gegex/state/struct.h>

#include <named/gegex/struct.h>

#include <set/string/foreach.h>

#include <set/gegex/new.h>
#include <set/gegex/add.h>
#include <set/gegex/free.h>
#include <set/gegex/clear.h>

#ifdef DOTOUT
#include <set/string/to_hashtagstring.h>
#include <set/gegex/contains.h>
#include <misc/frame_counter.h>
#endif

#include "structinfo/new.h"
#include "structinfo/to_string.h"
#include "structinfo/add_token_field.h"
#include "structinfo/add_grammar_field.h"
/*#include "structinfo/compare.h"*/
/*#include "structinfo/free.h"*/

#include "build_structinfo.h"

#ifdef DOTOUT
static void dotout(
	struct structinfo* structinfo,
	struct gegex* start,
	struct gegexset* seen,
	struct gegex* focus)
{
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	FILE* stream = fopen(path, "w");
	
	fprintf(stream, "digraph {" "\n");
	
	fprintf(stream, "rankdir = LR" "\n");
	
	struct gegexset* queued = new_gegexset();
	
	struct quack* todo = new_quack();
	
	{
		char* label = structinfo_to_string(structinfo);
		
		fprintf(stream, ""
			"\"label\" [" "\n"
				"label = \"%s\"" "\n"
				"shape = box" "\n"
			"];" "\n"
			"\"label\" -> \"%p\";" "\n"
		"", label, start);
		
		gegexset_add(queued, start);
		
		quack_append(todo, start);
		
		free(label);
	}
	
	while (quack_len(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		fprintf(stream, ""
			"\"%p\" [" "\n"
				"label = \"\"" "\n"
				"style = filled" "\n"
				"color = black" "\n"
				"fillcolor = %s" "\n"
				"shape = %s" "\n"
			"];" "\n"
		"", state,
		gegexset_contains(seen, state) ? "grey" : "white",
		state == focus ? "square" : "circle");
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* transition = state->transitions.data[i];
			
			if (gegexset_add(queued, transition->to))
				quack_append(todo, transition->to);
			
			char* label = stringset_to_hashtagstring(transition->tags);
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"#%u token %s\"" "\n"
				"]" "\n"
			"", state, transition->to, transition->token, label);
			
			free(label);
		}
		
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gegex_grammar_transition* gtransition = state->grammar_transitions.data[i];
			
			if (gegexset_add(queued, gtransition->to))
				quack_append(todo, gtransition->to);
			
			char* label = stringset_to_hashtagstring(gtransition->tags);
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [ label = \"%s %s\" ]" "\n"
			"", state, gtransition->to, gtransition->grammar->chars, label);
			
			free(label);
		}
	}
	
	fprintf(stream, "}");
	
	free_gegexset(queued);
	
	free_quack(todo);
	
	fclose(stream);
	
	EXIT;
}

#endif

struct structinfo* build_structinfo(struct string* name, struct gegex* start)
{
	ENTER;
	
	struct gegexset* queued = new_gegexset();
	
	struct quack* todo = new_quack();
	
	struct structinfo* info = new_structinfo(name);
	
	gegexset_add(queued,  start);
	
	quack_append(todo,  start);
	
	while (quack_len(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* const transition = state->transitions.data[i];
			
			stringset_foreach(transition->tags, ({
				void runme(struct string* tag) {
					structinfo_add_token_field(info, tag);
				}
				runme;
			}));
			
			if (gegexset_add(queued, transition->to))
				quack_append(todo, transition->to);
		}
		
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gegex_grammar_transition* const transition = state->grammar_transitions.data[i];
			
			stringset_foreach(transition->tags, ({
				void runme(struct string* tag) {
					structinfo_add_grammar_field(info, tag, transition->grammar);
				}
				runme;
			}));
			
			if (gegexset_add(queued, transition->to))
				quack_append(todo, transition->to);
		}
		
		
		#ifdef DOTOUT
		dotout(info, start, queued, state);
		#endif
	}
	
	free_gegexset(queued);
	
	EXIT;
	return info;
}




























