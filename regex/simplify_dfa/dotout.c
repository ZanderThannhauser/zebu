
#ifdef DOTOUT

#include <stdio.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <misc/frame_counter.h>

#include <misc/escape.h>

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
		fprintf(stderr, "zebu: fopen(\"%s\"): %m\n", path);
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
	
	while (quack_len(todo))
	{
		struct regex* state = quack_pop(todo);
		
		fprintf(out, ""
			"\"%p\" [" "\n"
				"\t" "shape = %s;" "\n"
				"\t" "label = \"\";" "\n"
				"\t" "style = filled;" "\n"
				"\t" "color = black;" "\n"
				"\t" "fillcolor = white;" "\n"
				"\t" "peripheries = %u;" "\n"
			"]" "\n"
		"", state, state->is_accepting ? "doublecircle" : "circle",
		           state->is_accepting ? 2 + state->is_literal : 1);
		
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
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* const to = state->transitions[i];
			
			if (to)
			{
				char str[10];
				
				escape(str, i);
				
				fprintf(out, "\"%p\" -> \"%p\" [ label = \"%s\" ]" "\n", state, to, str);
				
				if (regexset_add(queued, to))
					quack_append(todo, to);
			}
		}
		
		if (state->EOF_transition_to)
		{
			struct regex* const to = state->EOF_transition_to;
			
			if (regexset_add(queued, to))
				quack_append(todo, to);
			
			fprintf(out, "\"%p\" -> \"%p\" [ label = \"<EOF>\" ]" "\n", state, to);
		}
	}
	
	free_quack(todo);
	
	free_regexset(drawn);
	
	free_regexset(queued);
	
	fprintf(out, "}" "\n");
	
	fclose(out);
	
	EXIT;
}





















#endif
