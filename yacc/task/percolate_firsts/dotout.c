
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <linux/limits.h>

#include <debug.h>

#include <avl/foreach.h>

#include <named/grammar/struct.h>

#include <misc/frame_counter.h>

#include <set/of_strs/foreach.h>

#include <set/of_tokens/to_string.h>

#include "../../shared/struct.h"
#include "../../shared/get_firsts_deps.h"
#include "../../shared/lookup_firsts.h"

#include "struct.h"
#include "dotout.h"

#ifdef DOTOUT

void percolate_firsts_task_dotout(struct task* super, struct yacc_shared* shared)
{
	struct percolate_firsts_task* const this = (void*) super;
	ENTER;
	
	char path[PATH_MAX];
	
	dpv(frame_counter);
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	dpvs(path);
	
	FILE* out = fopen(path, "w");
	
	assert(out);
	
	fprintf(out, ""
		"digraph {" "\n"
		// "\t" "rankdir = BT" "\n"
	"");
	
	avl_tree_foreach(shared->new_grammar, ({
		void runme(const void* ptr)
		{
			const struct named_grammar* ng = ptr;
			
			dpvs(ng->name);
			
			struct tokenset* firsts = shared_lookup_firsts(shared, ng->name);
			
			char* str = tokenset_to_string(firsts);
			
			fprintf(out, ""
				"\"%s\" [ " "\n"
					"shape = record" "\n"
					"style = filled" "\n"
					"color = black" "\n"
					"fillcolor = white" "\n"
					"label = \"{%s | %s}\"" "\n"
				"];" "\n"
			"", ng->name, ng->name, str);
			
			strset_foreach(get_firsts_deps(shared, shared->firsts.dependant_on, ng->name), ({
				void runme(const char* dep) {
					fprintf(out, ""
						"\"%s\" -> \"%s\"" "\n"
					"", dep, ng->name);
				}
				runme;
			}));
			
			free(str);
		}
		runme;
	}));
	
	fprintf(out, ""
		"\"%s\" [" "\n"
			"fillcolor = grey;" "\n"
		"]" "\n"
	"", this->name);
	
	fprintf(out, ""
		"}" "\n"
	"");
	
	fclose(out);
	
	EXIT;
}

















#endif
