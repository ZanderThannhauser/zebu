
#include <debug.h>

#include <avl/foreach.h>

#include <gegex/state/struct.h>

#include <named/gegex/struct.h>

#include <set/string/foreach.h>

#include <set/gegex/new.h>
#include <set/gegex/add.h>
#include <set/gegex/free.h>

#include "structinfo/new.h"
#include "structinfo/to_string.h"
#include "structinfo/add_token_field.h"
#include "structinfo/add_grammar_field.h"
#include "structinfo/compare.h"
#include "structinfo/free.h"

#include "build_structs.h"

#ifdef DOTOUT

#include <set/string/to_hashtagstring.h>

#include <set/gegex/contains.h>

#include <misc/frame_counter.h>

static void dotout(
	struct avl_tree_t* structinfos,
	struct avl_tree_t* named_gegexes,
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
	
	unsigned label_counter = 0;
	
	avl_tree_foreach(named_gegexes, ({
		void runme(void* ptr)
		{
			struct named_gegex* const ng = ptr;
			
			dpvs(ng->name->chars);
			
			struct structinfo* si = avl_search(structinfos, &ng->name)->item;
			
			char* label = structinfo_to_string(si);
			
			fprintf(stream, ""
				"\"label_%u\" [" "\n"
					"label = \"%s\"" "\n"
					"shape = box" "\n"
				"];" "\n"
				"\"label_%u\" -> \"%p\";" "\n"
			"", label_counter, label, label_counter, ng->gegex);
			
			gegexset_add(queued, ng->gegex);
			
			quack_append(todo, ng->gegex);
			
			free(label);
			
			label_counter++;
		}
		runme;
	}));
	
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

struct bundle
{
	struct structinfo* structinfo;
	struct gegex* gegex;
};

static struct bundle* new_bundle(
	struct structinfo* structinfo,
	struct gegex* gegex)
{
	ENTER;
	struct bundle* this = smalloc(sizeof(*this));
	this->structinfo = structinfo;
	this->gegex = gegex;
	EXIT;
	return this;
}

struct avl_tree_t* build_structs(struct avl_tree_t* named_gegexes)
{
	ENTER;
	
	struct avl_tree_t* structinfos = avl_alloc_tree(compare_structinfos, free_structinfo);
	
	struct gegexset* queued = new_gegexset();
	
	struct quack* todo = new_quack();
	
	avl_tree_foreach(named_gegexes, ({
		void runme(void* ptr)
		{
			struct named_gegex* ngegex = ptr;
			
			struct structinfo* info = new_structinfo(ngegex->name);
			
			gegexset_add(queued, ngegex->gegex);
			
			avl_insert(structinfos, info);
			
			quack_append(todo, new_bundle(info, ngegex->gegex));
		}
		runme;
	}));
	
	while (quack_len(todo))
	{
		struct bundle* const bundle = quack_pop(todo);
		
		struct structinfo* const structinfo = bundle->structinfo;
		
		struct gegex* const gegex = bundle->gegex;
		
		for (unsigned i = 0, n = gegex->transitions.n; i < n; i++)
		{
			struct gegex_transition* const transition = gegex->transitions.data[i];
			
			stringset_foreach(transition->tags, ({
				void runme(struct string* tag) {
					structinfo_add_token_field(structinfo, tag);
				}
				runme;
			}));
			
			if (gegexset_add(queued, transition->to))
				quack_append(todo, new_bundle(structinfo, transition->to));
		}
		
		for (unsigned i = 0, n = gegex->grammar_transitions.n; i < n; i++)
		{
			struct gegex_grammar_transition* const transition = gegex->grammar_transitions.data[i];
			
			stringset_foreach(transition->tags, ({
				void runme(struct string* tag) {
					structinfo_add_grammar_field(structinfo, tag, transition->grammar);
				}
				runme;
			}));
			
			if (gegexset_add(queued, transition->to))
				quack_append(todo, new_bundle(structinfo, transition->to));
		}
		
		#ifdef DOTOUT
		dotout(structinfos, named_gegexes, queued, gegex);
		#endif
		
		free(bundle);
	}
	
	free_quack(todo);
	
	free_gegexset(queued);
	
	EXIT;
	return structinfos;
}
































