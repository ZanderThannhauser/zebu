

#include <debug.h>

#include <avl/foreach.h>

#include <named/grammar/struct.h>

#include <misc/frame_counter.h>

#include <strset/foreach.h>

#include <tokenset/to_string.h>

#include "../../shared.h"
#include "../../get_deps.h"
#include "../../lookup_tokenset.h"

#include "struct.h"
#include "dotout.h"

void percolate_firsts_task_dotout(struct task* super, struct shared* shared)
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
		"digraph {"
			"rankdir = LR" "\n"
	"\n");
	
	avl_tree_foreach(shared->grammars, ({
		void runme(const void* ptr)
		{
			const struct named_grammar* ng = ptr;
			
			dpvs(ng->name);
			
			struct tokenset* firsts = lookup_tokenset(shared->firsts.sets, ng->name);
			
			char* str = tokenset_to_string(firsts);
			
			fprintf(out, ""
				"\"%s\" [ "
					"shape = record" "\n"
					"style = filled" "\n"
					"color = black" "\n"
					"fillcolor = white" "\n"
					"label = \"{%s | %s}\"" "\n"
				"];" "\n",
			ng->name, ng->name, str);
			
			strset_foreach(get_deps(shared->firsts.dependant_on, ng->name), ({
				void runme(const char* dep) {
					fprintf(out, ""
						"\"%s\" -> \"%s\"\n"
					"\n", ng->name, dep);
				}
				runme;
			}));
			
			free(str);
		}
		runme;
	}));
	
	fprintf(out, ""
		"\"%s\" ["
			"fillcolor = grey;"
		"]"
	"\n", this->name);
	
	fprintf(out, ""
		"}"
	"\n");
	
	fclose(out);
	
	EXIT;
}


















