
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <string/new.h>
#include <string/inc.h>
#include <string/free.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/search.h>
#include <avl/free_tree.h>

/*#include <named/gegex/struct.h>*/

#include <set/unsigned/to_string.h>

#include <named/trie/new.h>
/*#include <named/trie/compare.h>*/
/*#include <named/trie/free.h>*/

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/free.h>

/*#include <set/string/new.h>*/
/*#include <set/string/foreach.h>*/

#include <gegex/grammar/struct.h>
#include <gegex/transition/struct.h>
#include <gegex/struct.h>

#ifdef VERBOSE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <misc/default_sighandler.h>
#include <quack/len.h>
#ifdef WINDOWS_PLATFORM
#include <compat/timer_thread.h>
#endif
#endif

#ifdef DOTOUT
#include <limits.h>
#include <stdio.h>
#include <misc/frame_counter.h>
#include <string/struct.h>
#include <set/ptr/contains.h>
#endif

#include "reductioninfo/new.h"
#include "reductioninfo/inc.h"
#include "reductioninfo/free.h"

#include "structinfo/inc.h"

#include "trie/struct.h"
#include "trie/new.h"
#include "trie/add_transition.h"
#include "trie/add_grammar_transition.h"

#include "build_tries.h"

#ifdef DOTOUT
#include "structinfo/struct.h"
#include "reductioninfo/to_string.h"
#include "structinfo/to_hashtagstring.h"
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
	struct ptrset* seen,
	struct avl_tree_t* gegex_to_trie,
	struct gegex* focus)
{
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	FILE* stream = fopen(path, "w");
	
	fprintf(stream, "digraph {" "\n");
	
	fprintf(stream, "rankdir = LR" "\n");
	
	struct ptrset* queued = new_ptrset();
	
	struct quack* todo = new_quack();
	
	ptrset_add(queued, start);
	
	quack_append(todo, start);
	
	while (quack_is_nonempty(todo))
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
		ptrset_contains(seen, state) ? "grey" : "white",
		state == focus ? "square" : "circle",
		state->accepts ? 2 : 1);
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* transition = state->transitions.data[i];
			
			if (ptrset_add(queued, transition->to))
				quack_append(todo, transition->to);
			
			char* label = structinfo_to_hashtagstring(transition->structinfo);
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"#%u token %s\"" "\n"
				"]" "\n"
			"", state, transition->to, transition->token, label);
			
			free(label);
		}
		
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			struct gegex_grammar_transition* gtransition = state->grammars.data[i];
			
			if (ptrset_add(queued, gtransition->to))
				quack_append(todo, gtransition->to);
			
			char* label = structinfo_to_hashtagstring(gtransition->structinfo);
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [ label = \"%s %s\" ]" "\n"
			"", state, gtransition->to, gtransition->grammar->chars, label);
			
			free(label);
		}
	}
	
	fprintf(stream, "}");
	
	free_ptrset(queued);
	
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
			assert(trie->grammar);
			
			char* reductioninfo_string = reductioninfo_to_string(trie->reductioninfo);
			
			fprintf(stream, ""
				"\"%p\" [" "\n"
					"label = \"{ reduce_as = %s } | { grammar = %s } %s \"" "\n"
					"shape = record" "\n"
					"style = filled" "\n"
					"color = black" "\n"
					"fillcolor = white" "\n"
				"];" "\n"
			"", trie, trie->reduce_as->chars, trie->grammar->chars, reductioninfo_string ?: "");
			
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
			
			char* whitespace = unsignedset_to_string(trans->whitespace);
			
			fprintf(stream, ""
				"\"%p\" -> \"%p\" [ label = \"%s #%u token\" ];" "\n"
			"", trie, trans->to, whitespace, trans->token);
			
			helper(trans->to);
			
			free(whitespace);
		}
		
		for (unsigned i = 0, n = trie->grammars.n; i < n; i++)
		{
			struct trie_grammar_transition* trans = trie->grammars.data[i];
			
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
	struct string* reduce_as,
	struct gegex* start,
	struct structinfo* structinfo)
{
	ENTER;
	
	assert(reduce_as);
	
	struct quack* explore = new_quack();
	
	struct quack* expand = new_quack();
	
	struct ptrset* seen = new_ptrset();
	
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
		ptrset_add(seen, start);
		
		quack_append(explore, start);
		
		avl_insert(gegex_to_trie, new_gegex_to_trie_name(start, reduce_as));
		
		struct trie* trie = new_trie();
		
		struct named_trie* new = new_named_trie(reduce_as, trie);
		
		quack_append(expand, new_explore_bundle(reduce_as, trie, start));
		
		avl_insert(named_tries, new);
	}
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler1(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(explore);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: building tries (explore): %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	#ifdef LINUX_PLATFORM
	signal(SIGALRM, handler1);
	#else
	#ifdef WINDOWS_PLATFORM
	timer_handler = handler1;
	#else
	#error bad platform
	#endif
	#endif
	#endif
	
	// explore:
	while (quack_is_nonempty(explore))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct gegex* state = quack_pop(explore);
		
		void process_to(struct gegex* to)
		{
			if (ptrset_add(seen, to))
			{
				quack_append(explore, to);
			}
			else if ((to->transitions.n || to->grammars.n) && !avl_search(gegex_to_trie, &to))
			{
				struct string* name = new_string_from_format("(trie #%u)", trie_id++);
				
				struct trie* trie = new_trie();
				
				struct named_trie* new = new_named_trie(name, trie);
				
				quack_append(expand, new_explore_bundle(name, trie, to));
				
				avl_insert(gegex_to_trie, new_gegex_to_trie_name(to, name));
				
				avl_insert(named_tries, new);
				
				free_string(name);
			}
		}
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			process_to(state->transitions.data[i]->to);
		}
		
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			process_to(state->grammars.data[i]->to);
		}
		
		#ifdef DOTOUT
		explore_dotout(start, seen, gegex_to_trie, state);
		#endif
	}
	
	#ifdef VERBOSE
	completed = 0;
	
	void handler2(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(expand);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: building tries (expand): %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	#ifdef LINUX_PLATFORM
	signal(SIGALRM, handler2);
	#else
	#ifdef WINDOWS_PLATFORM
	timer_handler = handler2;
	#else
	#error bad platform
	#endif
	#endif
	#endif
	
	// we have one pass that fills-out all the tries:
	while (quack_is_nonempty(expand))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct expand_bundle* bundle = quack_pop(expand);
		
		void expand_helper(
			struct trie* const trie,
			struct gegex* const gegex,
			struct reductioninfo* reductioninfo)
		{
			ENTER;
			
			if (reductioninfo && gegex->accepts)
			{
				trie->reductioninfo = inc_reductioninfo(reductioninfo);
				trie->structinfo = inc_structinfo(structinfo);
				trie->reduce_as = inc_string(bundle->trie_name);
				trie->grammar = inc_string(reduce_as);
			}
			
			struct trie* process_transition(
				struct structinfo* tags, // might be empty
				struct string* grammar, // might be NULL
				struct gegex* to)
			{
				ENTER;
				
				struct reductioninfo* subreductioninfo = new_reductioninfo(grammar ? rik_grammar : rik_token, tags, grammar, reductioninfo);
				
				struct trie* retval = new_trie();
				
				struct avl_node_t* node = avl_search(gegex_to_trie, &to);
				
				if (node)
				{
					if (to->accepts)
					{
						retval->reductioninfo = inc_reductioninfo(subreductioninfo);
						retval->structinfo = inc_structinfo(structinfo);
						retval->reduce_as = inc_string(bundle->trie_name);
						retval->grammar = inc_string(reduce_as);
					}
					
					struct trie* reduce = new_trie();
					
					struct gegex_to_trie_name_node* gtotn = node->item;
					
					trie_add_grammar_transition(retval, gtotn->trie_name, reduce);
					
					reduce->reductioninfo = new_reductioninfo(rik_trie, NULL, gtotn->trie_name, subreductioninfo);
					reduce->structinfo = inc_structinfo(structinfo);
					reduce->reduce_as = inc_string(bundle->trie_name);
					reduce->grammar = inc_string(reduce_as);
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
				
				trie_add_transition(trie, transition->token, transition->whitespace, to);
			}
			
			for (unsigned i = 0, n = gegex->grammars.n; i < n; i++)
			{
				struct gegex_grammar_transition* transition = gegex->grammars.data[i];
				
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
	
	#ifdef VERBOSE
	#ifdef LINUX_PLATFORM
	signal(SIGALRM, default_sighandler);
	#else
	#ifdef WINDOWS_PLATFORM
	timer_handler = default_sighandler;
	#else
	#error bad platform
	#endif
	#endif
	#endif
	
	avl_free_tree(gegex_to_trie);
	
	free_ptrset(seen);
	
	free_quack(explore);
	
	free_quack(expand);
	
	EXIT;
}




