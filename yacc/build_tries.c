
#include <debug.h>

#include <avl/foreach.h>

#include <named/gegex/struct.h>

#include <named/trie/new.h>
#include <named/trie/compare.h>
#include <named/trie/free.h>

#include <set/gegex/new.h>
#include <set/gegex/add.h>
#include <set/gegex/free.h>

#include <set/string/new.h>
#include <set/string/foreach.h>

#include <gegex/state/struct.h>

#ifdef DOTOUT
#include <misc/frame_counter.h>
#include <set/gegex/contains.h>
#endif

#include "reductioninfo/new.h"
#include "reductioninfo/inc.h"
#include "reductioninfo/to_string.h"
#include "reductioninfo/free.h"

#include "structinfo/inc.h"
#include "structinfo/to_hashtagstring.h"

#include "trie/struct.h"
#include "trie/add_transition.h"
#include "trie/add_grammar_transition.h"
#include "trie/new.h"

#include "build_tries.h"

#ifdef DOTOUT
#include "structinfo/struct.h"
#endif

struct expand_bundle
{
	struct string* trie_name;
	struct trie* trie;
	struct gegex* gegex;
};

static struct expand_bundle* new_explore_bundle(
	struct string* trie_name, struct trie* trie, struct gegex* gegex)
{
	struct expand_bundle* bundle = smalloc(sizeof(*bundle));
	bundle->trie_name = trie_name;
	bundle->trie = trie;
	bundle->gegex = gegex;
	return bundle;
}

struct gegex_to_trie_name_node
{
	struct gegex* gegex;
	struct string* trie_name;
};

static struct gegex_to_trie_name_node* new_gegex_to_trie_name(
	struct gegex* gegex, struct string* trie_name)
{
	struct gegex_to_trie_name_node* this = smalloc(sizeof(*this));
	this->gegex = gegex;
	this->trie_name = inc_string(trie_name);
	return this;
}

#ifdef DOTOUT
static void explore_dotout(
	struct gegex* start,
	struct gegexset* seen,
	struct avl_tree_t* gegex_to_trie,
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
	
	gegexset_add(queued, start);
	
	quack_append(todo, start);
	
	while (quack_len(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		char* label = "";
		
		{
			struct avl_node_t* node = avl_search(gegex_to_trie, &state);
			if (node)
			{
				struct gegex_to_trie_name_node* gtotn = node->item;
				label = gtotn->trie_name->chars;
			}
		}
		
		fprintf(stream, ""
			"\"%p\" [" "\n"
				"label = \"%s\"" "\n"
				"style = filled" "\n"
				"color = black" "\n"
				"fillcolor = %s" "\n"
				"shape = %s" "\n"
				"peripheries = %u" "\n"
			"];" "\n"
		"", state, label,
		gegexset_contains(seen, state) ? "grey" : "white",
		state == focus ? "square" : "circle",
		state->is_reduction_point ? 2 : 1);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* transition = state->transitions.data[i];
			
			if (gegexset_add(queued, transition->to))
				quack_append(todo, transition->to);
			
			char* label = structinfo_to_hashtagstring(transition->structinfo);
			
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
			
			char* label = structinfo_to_hashtagstring(gtransition->structinfo);
			
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

static void expand_dotout(struct trie* start)
{
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	FILE* stream = fopen(path, "w");
	
	fprintf(stream, "digraph {" "\n");
	
	fprintf(stream, "rankdir = LR" "\n");
	
	void helper(struct trie* trie)
	{
		ENTER;
		
		if (trie->reduce_as)
		{
			char* reductioninfo_string = reductioninfo_to_string(trie->reductioninfo);
			
			#ifdef DEBUGGING
			assert(trie->structinfo->name);
			#endif
			
			fprintf(stream, ""
				"\"%p\" [" "\n"
					"label = \"{ reduce_as = %s } | {structinfo = %s} %s \"" "\n"
					"shape = record" "\n"
					"style = filled" "\n"
					"color = black" "\n"
					"fillcolor = white" "\n"
				"];" "\n"
			"", trie, trie->reduce_as->chars, trie->structinfo->name->chars, reductioninfo_string ?: "");
			
			free(reductioninfo_string);
		}
		else
		{
			fprintf(stream, ""
				"\"%p\" [" "\n"
					"label = \"\"" "\n"
					"shape = box" "\n"
					"style = filled" "\n"
					"color = black" "\n"
					"fillcolor = white" "\n"
				"];" "\n"
			"", trie);
		}
		
		for (unsigned i = 0, n = trie->transitions.n; i < n; i++)
		{
			struct trie_transition* trans = trie->transitions.data[i];
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [ label = \"#%u token\" ];" "\n"
			"", trie, trans->to, trans->token);
			
			helper(trans->to);
		}
		
		for (unsigned i = 0, n = trie->grammar_transitions.n; i < n; i++)
		{
			struct trie_grammar_transition* trans = trie->grammar_transitions.data[i];
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [ label = \"%s\" ];" "\n"
			"", trie, trans->to, trans->grammar->chars);
			
			helper(trans->to);
		}
		
		EXIT;
	}
	
	helper(start);
	
	fprintf(stream, "}");
	
	fclose(stream);
	
}

#endif

static unsigned trie_id = 0;

void build_tries(
	struct avl_tree_t* named_tries,
	struct string* name,
	struct gegex* start,
	struct structinfo* structinfo)
{
	ENTER;
	
	#ifdef DEBUGGING
	assert(structinfo->name);
	#endif
	
	struct quack* explore = new_quack();
	
	struct quack* expand = new_quack();
	
	struct gegexset* seen = new_gegexset();
	
	int compare_gegex_to_trie(const void* a, const void* b)
	{
		const struct gegex_to_trie_name_node *A = a, *B = b;
		if (A->gegex > B->gegex)
			return +1;
		if (A->gegex < B->gegex)
			return -1;
		return +0;
	}
	
	void free_gegex_to_trie(void* a)
	{
		struct gegex_to_trie_name_node* this = a;
		free_string(this->trie_name);
		free(this);
	}
	
	struct avl_tree_t* gegex_to_trie = avl_alloc_tree(compare_gegex_to_trie, free_gegex_to_trie);
	
	// setup:
	{
		gegexset_add(seen, start);
		
		quack_append(explore, start);
		
		avl_insert(gegex_to_trie, new_gegex_to_trie_name(start, name));
		
		struct trie* trie = new_trie();
		
		struct named_trie* new = new_named_trie(name, trie);
		
		quack_append(expand, new_explore_bundle(name, trie, start));
		
		avl_insert(named_tries, new);
	}
	
	// explore:
	while (quack_len(explore))
	{
		struct gegex* state = quack_pop(explore);
		
		void process_to(struct gegex* to)
		{
			if (gegexset_add(seen, to))
			{
				quack_append(explore, to);
			}
			else if ((to->transitions.n || to->grammar_transitions.n) && !avl_search(gegex_to_trie, &to))
			{
				struct string* name = new_string_from_format("(trie #%u)", trie_id++);
				
				struct trie* trie = new_trie();
				
				struct named_trie* new = new_named_trie(name, trie);
				
				quack_append(expand, new_explore_bundle(name, trie, to));
				
				avl_insert(gegex_to_trie, new_gegex_to_trie_name(to, name));
				
				avl_insert(named_tries, new);
			}
		}
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			process_to(state->transitions.data[i]->to);
		}
		
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			process_to(state->grammar_transitions.data[i]->to);
		}
		
		#ifdef DOTOUT
		explore_dotout(start, seen, gegex_to_trie, state);
		#endif
	}
	
	// we have one pass that fills-out all the tries:
	while (quack_len(expand))
	{
		struct expand_bundle* bundle = quack_pop(expand);
		
		void expand_helper(
			struct trie* const trie,
			struct gegex* const gegex,
			struct reductioninfo* reductioninfo)
		{
			ENTER;
			
			if (reductioninfo && gegex->is_reduction_point)
			{
				trie->reductioninfo = inc_reductioninfo(reductioninfo);
				trie->structinfo = inc_structinfo(structinfo);
				trie->reduce_as = inc_string(bundle->trie_name);
			}
			
			struct trie* process_transition(
				struct structinfo* tags, // might be empty
				struct string* grammar, // might be NULL
				struct gegex* to)
			{
				ENTER;
				
				#ifdef DEBUGGING
				assert(structinfo->name);
				#endif
				
				struct reductioninfo* subreductioninfo = new_reductioninfo(grammar ? rik_grammar : rik_token, tags, grammar, reductioninfo);
				
				struct trie* retval = new_trie();
				
				struct avl_node_t* node = avl_search(gegex_to_trie, &to);
				
				if (node)
				{
					if (to->is_reduction_point)
					{
						retval->reductioninfo = inc_reductioninfo(subreductioninfo);
						retval->structinfo = inc_structinfo(structinfo);
						retval->reduce_as = inc_string(bundle->trie_name);
					}
					
					struct trie* reduce = new_trie();
					
					struct gegex_to_trie_name_node* gtotn = node->item;
					
					trie_add_grammar_transition(retval, gtotn->trie_name, reduce);
					
					reduce->reductioninfo = new_reductioninfo(rik_trie, NULL, gtotn->trie_name, subreductioninfo);
					reduce->structinfo = inc_structinfo(structinfo);
					reduce->reduce_as = inc_string(bundle->trie_name);
				}
				else
				{
					expand_helper(retval, to, subreductioninfo);
				}
				
				free_reductioninfo(subreductioninfo);
				
				EXIT;
				return retval;
			}
			
			for (unsigned i = 0, n = gegex->transitions.n; i < n; i++)
			{
				struct gegex_transition* transition = gegex->transitions.data[i];
				
				struct trie* to = process_transition(transition->structinfo, NULL, transition->to);
				
				trie_add_transition(trie, transition->token, to);
			}
			
			for (unsigned i = 0, n = gegex->grammar_transitions.n; i < n; i++)
			{
				struct gegex_grammar_transition* transition = gegex->grammar_transitions.data[i];
				
				struct trie* to = process_transition(transition->structinfo, transition->grammar, transition->to);
				
				trie_add_grammar_transition(trie, transition->grammar, to);
			}
			
			EXIT;
		}
		
		expand_helper(bundle->trie, bundle->gegex, NULL);
		
		#ifdef DOTOUT
		expand_dotout(bundle->trie);
		#endif
		
		free(bundle);
	}
	
	avl_free_tree(gegex_to_trie);
	
	free_gegexset(seen);
	
	free_quack(explore);
	
	free_quack(expand);
	
	EXIT;
}






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











