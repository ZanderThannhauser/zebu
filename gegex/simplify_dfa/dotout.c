
#ifdef DOTOUT

#include <stdio.h>
#include <linux/limits.h>

#include <debug.h>

#include <misc/frame_counter.h>

/*#include <avl/search.h>*/

#include <set/gegex/new.h>
#include <set/gegex/add.h>
#include <set/gegex/contains.h>
#include <set/gegex/foreach.h>
#include <set/gegex/free.h>

#include <set/string/to_hashtagstring.h>

#include "same_as_node/struct.h"

#include "../state/struct.h"

#include "dotout.h"

void gegex_simplify_dfa_dotout(
	struct gegexset* universe,
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
	
	struct gegexset* drawn = new_gegexset();
	
	struct gegexset* queued = new_gegexset();
	
	struct quack* todo = new_quack();
	
	gegexset_foreach(universe, ({
		void runme(struct gegex* state)
		{
			gegexset_add(queued, state);
			quack_append(todo, state);
		}
		runme;
	}));
	
	while (quack_len(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		fprintf(out, ""
			"\"%p\" [" "\n"
				"\t" "shape = %s;" "\n"
				"\t" "label = \"\";" "\n"
				"\t" "style = filled;" "\n"
				"\t" "fillcolor = white;" "\n"
			"]" "\n"
		"", state, state->is_reduction_point ? "doublecircle" : "circle");
		
		{
			gegexset_add(drawn, state);
			
			struct avl_node_t* node = avl_search(connections, &state);
			
			assert(node);
			
			struct gegex_same_as_node* sa = node->item;
			
			gegexset_foreach(sa->set, ({
				void runme(struct gegex* dep) {
					if (!gegexset_contains(drawn, dep))
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
		
		// normal transitions:
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* transition = state->transitions.data[i];
			
			if (gegexset_add(queued, transition->to))
				quack_append(todo, transition->to);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"token #%u\"" "\n"
				"]" "\n"
			"", state, transition->to, transition->token);
		}
		
		// grammar_transitions:
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gegex_grammar_transition* transition = state->grammar_transitions.data[i];
			
			if (gegexset_add(queued, transition->to))
				quack_append(todo, transition->to);
			
			char* label = stringset_to_hashtagstring(transition->tags);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"%s%s\"" "\n"
				"]" "\n"
			"", state, transition->to, transition->grammar->chars, label);
			
			free(label);
		}
	}
	
	free_gegexset(drawn);
	free_gegexset(queued);
	
	free_quack(todo);
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}





















#endif
