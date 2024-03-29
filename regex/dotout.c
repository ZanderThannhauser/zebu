
#ifdef DOTOUT

#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include <debug.h>

#include <misc/frame_counter.h>

#include <misc/escape.h>

#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/append.h>
#include <quack/new.h>
#include <quack/free.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/foreach.h>
#include <set/ptr/free.h>

#include "struct.h"
#include "dotout.h"

static void helper(const char* name, struct ptrset* queued, struct quack* todo)
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
	
	if (name)
	{
		fprintf(out, "\t" "label = \"%s\";" "\n", name);
	}
	
	while (quack_is_nonempty(todo))
	{
		struct regex* state = quack_pop(todo);
		
		fprintf(out, ""
			"\"%p\" [" "\n"
				"\t" "shape = %s;" "\n"
				"\t" "label = \"\";" "\n"
				"\t" "style = filled;" "\n"
				"\t" "fillcolor = white;" "\n"
				"\t" "peripheries = %u;" "\n"
			"]" "\n"
		"", state, state->accepts ? "doublecircle" : "circle",
		           state->accepts ? 2 + state->kind : 1);
		
		// normal transitions:
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* const to = state->transitions[i];
			
			if (to)
			{
				char str[10];
				
				escape(str, i);
				
				fprintf(out, "\"%p\" -> \"%p\" [ label = \"%s\" ]" "\n", state, to, str);
				
				if (ptrset_add(queued, to))
					quack_append(todo, to);
			}
		}
		
		for (unsigned i = 0, n = state->lambdas.n; i < n; i++)
		{
			struct regex* const to = state->lambdas.data[i];
			
			fprintf(out, "\"%p\" -> \"%p\" [ label = \"λ\" ]" "\n", state, to);
		
			if (ptrset_add(queued, to))
				quack_append(todo, to);
		}
		
		if (state->EOF_transition_to)
		{
			struct regex* const to = state->EOF_transition_to;
			
			if (ptrset_add(queued, to))
				quack_append(todo, to);
			
			fprintf(out, "\"%p\" -> \"%p\" [ label = \"<EOF>\" ]" "\n", state, to);
		}
	}
	
	fprintf(out, "}" "\n");
	
	fclose(out);
	
	EXIT;
}

void regex_dotout(struct regex* state, const char* name)
{
	ENTER;
	
	struct ptrset* queued = new_ptrset();
	
	struct quack* todo = new_quack();
	
	ptrset_add(queued, state);
	
	quack_append(todo, state);
	
	helper(name, queued, todo);
	
	free_ptrset(queued);
	
	free_quack(todo);
	
	EXIT;
}

void regex_dotout_set(struct ptrset* set, const char* name)
{
	ENTER;
	
	struct ptrset* queued = new_ptrset();
	
	struct quack* todo = new_quack();
	
	ptrset_foreach(set, ({
		void runme(void* ptr)
		{
			struct regex* state = ptr;
			
			ptrset_add(queued, state);
			
			quack_append(todo, state);
		}
		runme;
	}));
	
	helper(name, queued, todo);
	
	free_ptrset(queued);
	
	free_quack(todo);
	
	EXIT;
}

void regex_dotout_two_nodes(struct regex* a, struct regex* b, const char* name)
{
	ENTER;
	
	TODO;
	#if 0
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
	
	fprintf(out, "\t" "label = \"%s\";" "\n", name);
	
	dotout_phase_counter++;
	
	helper(out, a);
	
	helper(out, b);
	
	fprintf(out, "\"%p\" [ fillcolor = grey; ];" "\n", a);
	fprintf(out, "\"%p\" [ fillcolor = grey; ];" "\n", b);
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	#endif
	
	EXIT;
}

#endif















