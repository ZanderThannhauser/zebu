
#ifdef DOTOUT

#include <stdio.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <set/unsignedchar/to_string.h>

#include <misc/frame_counter.h>

#include <misc/escape.h>

#include <quack/struct.h>

#include <set/regex/new.h>
#include <set/regex/add.h>
#include <set/regex/contains.h>
#include <set/regex/foreach.h>
#include <set/regex/free.h>

#include "same_as_node/struct.h"

#include "../state/struct.h"

#include "dotout.h"

void simplify_dfa_dotout(
	struct regexset* universe,
	struct avl_tree_t* connections,
	unsigned hopcount)
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
	
	fprintf(out, "\t" "label = \"%s: hopcount: %u\";" "\n", __PRETTY_FUNCTION__, hopcount);
	
	struct regexset* drawn = new_regexset();
	struct regexset* queued = new_regexset();
	
	struct quack* todo = new_quack();
	
	regexset_foreach(universe, ({
		void runme(struct regex* state)
		{
			regexset_add(queued, state);
			quack_append(todo, state);
		}
		runme;
	}));
	
	while (todo->n)
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
		"", state, state->is_accepting ? "doublecircle" : "circle",
		           state->is_accepting ? 0 : 2 + state->priority);
		
		regexset_add(drawn, state);
		
		{
			struct avl_node_t* node = avl_search(connections, &state);
			
			assert(node);
			
			struct regex_same_as_node* sa = node->item;
			
			regexset_foreach(sa->set, ({
				void runme(struct regex* dep) {
					if (!regexset_contains(drawn, dep))
					{
						fprintf(out, ""
							"\"%p\" -> \"%p\" [" "\n"
								"\t" "style = dashed" "\n"
								"\t" "constraint = false" "\n"
								"\t" "dir = none" "\n"
							"]" "\n"
						"", state, dep);
					}
				}
				runme;
			}));
		}
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			char str[10];
			
			struct regex_transition* const ele = state->transitions.data[i];
			
			escape(str, ele->value);
			
			fprintf(out, "\"%p\" -> \"%p\" [ label = \"%s\" ]" "\n", state, ele->to, str);
			
			if (regexset_add(queued, ele->to))
				quack_append(todo, ele->to);
		}
		
		if (state->default_transition.to)
		{
			TODO;
			#if 0
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
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"<EOF>\"" "\n"
				"]" "\n"
			"", state, state->EOF_transition_to);
			#endif
		}
	}
	
	free_quack(todo);
	
	free_regexset(drawn);
	
	free_regexset(queued);
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}





















#endif
