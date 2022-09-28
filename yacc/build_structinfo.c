

#include <debug.h>

#include <avl/foreach.h>

#include <gegex/grammar/struct.h>
#include <gegex/transition/struct.h>
#include <gegex/struct.h>

#include <named/gegex/struct.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <set/string/foreach.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>
/*#include <set/gegex/clear.h>*/

#ifdef DOTOUT
#include <stdio.h>
#include <limits.h>
#include <misc/frame_counter.h>
#include <stdlib.h>
#include <set/ptr/contains.h>
#include <string/struct.h>
#include <quack/free.h>
#endif

#include "structinfo/new.h"
#include "structinfo/update.h"
#include "structinfo/to_string.h"
#include "structinfo/to_hashtagstring.h"
/*#include "structinfo/add_token_field.h"*/
/*#include "structinfo/add_grammar_field.h"*/
/*#include "structinfo/compare.h"*/
/*#include "structinfo/free.h"*/

#include "build_structinfo.h"

#ifdef DOTOUT
static void dotout(
	struct structinfo* structinfo,
	struct gegex* start,
	struct ptrset* seen,
	struct gegex* focus)
{
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	FILE* stream = fopen(path, "w");
	
	fprintf(stream, "digraph {" "\n");
	
	fprintf(stream, "rankdir = LR" "\n");
	
	struct ptrset* queued = new_ptrset();
	
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
		
		ptrset_add(queued, start);
		
		quack_append(todo, start);
		
		free(label);
	}
	
	while (quack_is_nonempty(todo))
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
		ptrset_contains(seen, state) ? "grey" : "white",
		state == focus ? "square" : "circle");
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* transition = state->transitions.data[i];
			
			if (ptrset_add(queued, transition->to))
				quack_append(todo, transition->to);
			
			char* label = structinfo_to_hashtagstring(transition->structinfo);
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"#%u token %s\"" "\n"
				"]" "\n"
			"", state, transition->to, transition->token, label);
			
			free(label);
		}
		
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			struct gegex_grammar_transition* gtransition = state->grammars.data[i];
			
			if (ptrset_add(queued, gtransition->to))
				quack_append(todo, gtransition->to);
			
			char* label = structinfo_to_hashtagstring(gtransition->structinfo);
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [ label = \"%s %s\" ]" "\n"
			"", state, gtransition->to, gtransition->grammar->chars, label);
			
			free(label);
		}
	}
	
	fprintf(stream, "}");
	
	free_ptrset(queued);
	
	free_quack(todo);
	
	fclose(stream);
	
	EXIT;
}

#endif

struct structinfo* build_structinfo(
	struct string* name,
	struct gegex* start,
	struct structinfo* extra)
{
	ENTER;
	
	struct ptrset* queued = new_ptrset();
	
	struct quack* todo = new_quack();
	
	struct structinfo* info = new_structinfo();
	
	ptrset_add(queued, start);
	
	quack_append(todo, start);
	
	if (extra)
	{
		structinfo_update(info, extra);
	}
	
	while (quack_is_nonempty(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* const transition = state->transitions.data[i];
			
			structinfo_update(info, transition->structinfo);
			
			if (ptrset_add(queued, transition->to))
				quack_append(todo, transition->to);
		}
		
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			struct gegex_grammar_transition* const transition = state->grammars.data[i];
			
			structinfo_update(info, transition->structinfo);
			
			if (ptrset_add(queued, transition->to))
				quack_append(todo, transition->to);
		}
		
		#ifdef DOTOUT
		dotout(info, start, queued, state);
		#endif
	}
	
	free_ptrset(queued);
	
	free_quack(todo);
	
	EXIT;
	return info;
}




























