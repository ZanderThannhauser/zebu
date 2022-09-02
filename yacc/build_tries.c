
#include <debug.h>

#include <avl/foreach.h>

#include <named/gegex/struct.h>

#include <set/gegex/new.h>
#include <set/gegex/add.h>
#include <set/gegex/free.h>

#include <gegex/state/struct.h>

#ifdef DOTOUT
#include <misc/frame_counter.h>
#include <set/string/to_hashtagstring.h>
#include <set/gegex/contains.h>
#endif

#include "trie/new.h"
#include "trieinfo/new.h"
#include "build_tries.h"

#ifdef DOTOUT
static void explore_dotout(
	struct avl_tree_t* named_gegexes,
	struct gegexset* seen,
	struct gegexset* roots,
	struct gegex* focus)
{
	ENTER;
	
	TODO;
	#if 0
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	FILE* stream = fopen(path, "w");
	
	fprintf(stream, "digraph {" "\n");
	
	fprintf(stream, "rankdir = LR" "\n");
	
	struct gegexset* queued = new_gegexset();
	
	struct quack* todo = new_quack();
	
	avl_tree_foreach(named_gegexes, ({
		void runme(void* ptr)
		{
			struct named_gegex* const ng = ptr;
			
			fprintf(stream, ""
				"\"%p\" [" "\n"
					"label = \"%s\"" "\n"
					"shape = none" "\n"
				"];" "\n"
				"\"%p\" -> \"%p\";" "\n"
			"", ng->name, ng->name, ng->name, ng->gegex);
			
			gegexset_add(queued, ng->gegex);
			
			quack_append(todo, ng->gegex);
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
		"", state, gegexset_contains(seen, state) ? gegexset_contains(roots, state) ? "green" : "blue" : "white",
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
			"", state, gtransition->to, gtransition->grammar, label);
			
			free(label);
		}
	}
	
	fprintf(stream, "}");
	
	free_gegexset(queued);
	
	free_quack(todo);
	
	fclose(stream);
	#endif
	
	EXIT;
}

static void expand_dotout()
{
	TODO;
}
#endif

struct avl_tree_t* build_tries(
	struct avl_tree_t* trieinfos,
	struct avl_tree_t* named_gegexes)
{
	ENTER;
	
/*	struct avl_tree_t* named_trieinfo = avl_alloc_tree(compare_trieinfos, free_trieinfo);*/
	
	// reference counting:
	TODO;
	
	// we have one pass that builds the tries:
	TODO;
	
	// another pass that figures out reductioninfo:
	TODO;
	
	TODO;
	#if 0
	unsigned trie_id = 0;
	
	struct explore_bundle
	{
		struct gegex* gegex;
		struct trie* trie;
		struct trieinfo* trieinfo;
		unsigned popcount;
		struct reductioninfo* reductioninfo;
	};
	
	struct explore_bundle* new_explore_bundle(const char* given_name, struct gegex* gegex)
	{
		char* name;
		ENTER;
		
		if (given_name)
			name = strdup(given_name);
		else if (asprintf(&name, "(trie #%u)", trie_id++) < 0)
			abort();
		
		dpvs(name);
		
		struct explore_bundle* new = smalloc(sizeof(*new));
		
		struct trie* trie = new_trie();
		
		struct trieinfo* trieinfo = new_trieinfo(name, trie);
		
		new->gegex = gegex;
		new->trie = trie;
		new->trieinfo = trieinfo;
		new->popcount = 0;
		new->reductioninfo = NULL;
		
		avl_insert(trieinfos, trieinfo);
		
		EXIT;
		return new;
	}
	
	struct explore_bundle* new_explore_bundle2(
		struct gegex* gegex,
		struct trie* trie,
		struct trieinfo* trieinfo,
		unsigned popcount,
		struct reductioninfo* reductioninfo)
	{
		ENTER;
		
		struct explore_bundle* new = smalloc(sizeof(*new));
		
		new->gegex = gegex;
		new->trie = trie;
		new->trieinfo = trieinfo;
		new->popcount = popcount;
		new->reductioninfo = reductioninfo;
		
		EXIT;
		return new;
	}
	
	struct gegexset* seen = new_gegexset();
	
	struct quack* explore = new_quack();
	
	struct gegexset* roots = new_gegexset();
	
	struct quack* expand = new_quack();
	
	// gegex to trieinfo map?
	
	avl_tree_foreach(named_gegexes, ({
		void runme(void* ptr)
		{
			struct named_gegex* const ng = ptr;
			
			struct gegex* const g = ng->gegex;
			
			gegexset_add(seen, g);
			
			quack_append(explore, g);
			
			gegexset_add(roots, g);
			
			quack_append(expand, new_explore_bundle(ng->name, g));
		}
		runme;
	}));
	
	// explore loop:
	while (quack_len(explore))
	{
		struct gegex* state = quack_pop(explore);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex* const to = state->transitions.data[i]->to;
			
			if (gegexset_add(seen, to))
				quack_append(explore, to);
			else if (gegexset_add(roots, to))
				quack_append(expand, new_explore_bundle(NULL, to));
		}
		
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gegex* const to = state->grammar_transitions.data[i]->to;
			
			if (gegexset_add(seen, to))
				quack_append(explore, to);
			else if (gegexset_add(roots, to))
				quack_append(expand, new_explore_bundle(NULL, to));
		}
		
		#ifdef DOTOUT
		explore_dotout(named_gegexes, seen, roots, state);
		#endif
	}
	
	// expand loop:
	while (quack_len(expand))
	{
		struct explore_bundle* const bundle = quack_pop(expand);
		
		TODO;
		#if 0
		struct trie* const trie = bundle->trie;
		
		struct gegex* const gegex = bundle->gegex;
		
		struct reductioninfo* const reductioninfo = bundle->reductioninfo;
		
		dpv(bundle->popcount);
		
		if (gegex->is_reduction_point)
		{
			trie->reductioninfo = inc_reductioninfo(reductioninfo);
		}
		
		for (unsigned i = 0, n = gegex->transitions.n; i < n; i++)
		{
			struct gegex_transition* const trans = gegex->transitions.data[i];
			
			struct gegex* const to = trans->to;
			
			TODO;
			#if 0
			struct reductioninfo* current_ri = inc_reductioninfo(reductioninfo);
			
			stringset_foreach(trans->tags, ({
				void runme(const char* tag)
				{
					// add tag to trieinfo as a token
					TODO;
					
					// add tag & current popcount to reductioninfo:
					TODO;
				}
				runme;
			}));
			
			if (gegexset_contains(roots, to) && (to->transitions.n || to->grammar_transitions.n))
			{
				// call the other trie
				TODO;
			}
			else
			{
				struct trie* subtrie = new_trie();
				
				trie_add_transition(trie, trans->value, subtrie);
				
				// treat it like it's mine, submit expansion task
				quack_append(expand, new_explore_bundle2(
					/* gegex: */ to,
					/* trie: */ subtrie,
					/* trieinfo: */ trieinfo,
					/* popcount: */ popcount + 1,
					/* reductioninfo: */ current_ri));
			}
			#endif
		}
		
		for (unsigned i = 0, n = gegex->grammar_transitions.n; i < n; i++)
		{
			TODO;
		}
		#endif
		
		#ifdef DOTOUT
		expand_dotout();
		#endif
		
		CHECK;
		
		free(bundle);
	}
	
	TODO;
	
	free_gegexset(seen);
	
	free_quack(explore);
	
	free_gegexset(roots);
	
	free_quack(expand);
	#endif
	
	EXIT;
}

















