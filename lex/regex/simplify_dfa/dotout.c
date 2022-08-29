
#ifdef DOTOUT

#include <stdio.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <defines/argv0.h>

#include <avl/search.h>

#include <misc/counters.h>
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
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, path);
		abort();
	}
	
	fprintf(out, "digraph {" "\n");
	
	fprintf(out, "\t" "rankdir = LR;" "\n");
	
	fprintf(out, "\t" "label = \"%s: hopcount: %u\";" "\n", __PRETTY_FUNCTION__, hopcount);
	
	struct regexset* done = new_regexset();
	
	regexset_foreach(universe, ({
		void runme(struct regex* state)
		{
			unsigned i, n;
			
			if (state->is_accepting)
			{
				fprintf(out, ""
					"\"%p\" [" "\n"
						"\t" "shape = doublecircle;" "\n"
						"\t" "label = \"%u\";" "\n"
						"\t" "style = filled;" "\n"
						"\t" "fillcolor = white;" "\n"
						"\t" "peripheries = %u;" "\n"
					"]" "\n"
				"", state, 1, 2 + state->priority);
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
			
			for (unsigned i = 0, n = state->transitions.n; i < n; i++)
			{
				struct regex_transition* const ele = state->transitions.data[i];
				
				char str[10];
				
				escape(str, ele->value);
				
				fprintf(out, ""
					"\"%p\" -> \"%p\" [" "\n"
						"\t" "label = \"%s\"" "\n"
					"]" "\n"
				"", state, ele->to, str);
			}
			
			// default transition?:
			if (state->default_transition_to)
			{
				fprintf(out, ""
					"\"%p\" -> \"%p\" [" "\n"
						"\t" "label = \"<default>\"" "\n"
					"]" "\n"
				"", state, state->default_transition_to);
			}
			
			if (state->EOF_transition_to)
			{
				fprintf(out, ""
					"\"%p\" -> \"%p\" [" "\n"
						"\t" "label = \"<EOF>\"" "\n"
					"]" "\n"
				"", state, state->EOF_transition_to);
			}
			
			{
				struct avl_node_t* node = avl_search(connections, &state);
				
				assert(node);
				
				struct regex_same_as_node* sa = node->item;
				
				regexset_foreach(sa->set, ({
					void runme(struct regex* dep) {
						if (state != dep && !regexset_contains(done, dep))
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
				
				regexset_add(done, state);
			}
		}
		runme;
	}));
	
	free_regexset(done);
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}





















#endif
