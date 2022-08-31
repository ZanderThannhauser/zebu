
#ifdef DOTOUT

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include <debug.h>

#include <misc/frame_counter.h>

#include <misc/escape.h>

#include <quack/struct.h>

#include <set/regex/new.h>
#include <set/regex/add.h>
#include <set/regex/free.h>

#include <set/unsignedchar/to_string.h>

#include "state/struct.h"

#include "dotout.h"

static void helper(FILE* out, struct regex* start)
{
	ENTER;
	
	struct regexset* done = new_regexset();
	
	struct quack* todo = new_quack();
	
	quack_append(todo, start);
	
	while (todo->n)
	{
		struct regex* state = quack_pop(todo);
		
		if (state->is_accepting)
		{
			fprintf(out, ""
				"\"%p\" [" "\n"
					"\t" "shape = doublecircle;" "\n"
					"\t" "label = \"\";" "\n"
					"\t" "style = filled;" "\n"
					"\t" "fillcolor = white;" "\n"
					"\t" "peripheries = %u;" "\n"
				"]" "\n"
			"", state, 2 + state->priority);
		}
		else
		{
			fprintf(out, ""
				"\"%p\" [" "\n"
					"\t" "shape = circle;" "\n"
					"\t" "style = filled;" "\n"
					"\t" "fillcolor = white;" "\n"
					"\t" "label = \"\";" "\n"
				"]" "\n"
			"", state);
		}
		
		// normal transitions:
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			char str[10];
			
			struct regex_transition* ele = state->transitions.data[i];
			
			escape(str, ele->value);
			
			fprintf(out, "\"%p\" -> \"%p\" [ label = \"%s\" ]" "\n", state, ele->to, str);
			
			if (regexset_add(done, ele->to))
				quack_append(todo, ele->to);
		}
		
		for (unsigned i = 0, n = state->lambda_transitions.n; i < n; i++)
		{
			struct regex* const to = state->lambda_transitions.data[i];
			
			fprintf(out, "\"%p\" -> \"%p\" [ label = \"λ\" ]" "\n", state, to);
		
			if (regexset_add(done, to))
				quack_append(todo, to);
		}
		
		if (state->default_transition.to)
		{
			TODO;
			#if 0
			helper(out, state->default_transition.to);
			
			char* label = unsignedcharset_to_string(state->default_transition.exceptions, true);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [ label = \"%s\" ]; \n"
			"", state, state->default_transition.to, label ?: "<default>");
			
			free(label);
			#endif
		}
		
		if (state->EOF_transition_to)
		{
			TODO;
			#if 0
			helper(out, to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"<EOF>\"" "\n"
				"]" "\n"
			"", state, to);
			#endif
		}
	}
	
	free_regexset(done);
	
	free_quack(todo);
	
	EXIT;
}

#if 0
void regex_dotout_set(struct regexset* set)
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
	
	dotout_phase_counter++;
	
	regexset_foreach(set, ({
		void runme(struct regex* state) {
			
			helper(out, state);
			
			fprintf(out, "\"%p\" [ fillcolor = grey; ];" "\n", state);
			
		}
		runme;
	}));
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}
#endif

void regex_dotout(struct regex* state, const char* name)
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
	
	fprintf(out, "\t" "label = \"%s\";" "\n", name);
	
	helper(out, state);
	
	fprintf(out, "\"%p\" [ fillcolor = grey; ];" "\n", state);
	
	fprintf(out, "}" "\n");
	
	fclose(out);
	
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















