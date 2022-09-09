
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/search.h>
#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/len.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <named/trie/struct.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/update.h>

#ifdef DOTOUT
#include <limits.h>
#include <stdio.h>
#include <misc/frame_counter.h>
#include <string/struct.h>
#include <set/unsigned/to_string.h>
#endif

#include "trie/struct.h"

#include "stateinfo/node/struct.h"
#include "stateinfo/get_lookaheads.h"
#include "stateinfo/foreach.h"
#include "stateinfo/add.h"

#include "calc_firsts.h"
#include "expand_stateinfo.h"

struct trieset
{
	struct avl_tree_t* tree;
};

static int trieset_node_compare(const void* a, const void* b)
{
	if (a > b)
		return +1;
	else if (a < b)
		return -1;
	else
		return +0;
}

static struct trieset* new_trieset()
{
	ENTER;
	
	struct trieset* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(trieset_node_compare, NULL);
	
	EXIT;
	return this;
}

static void trieset_add(struct trieset* this, struct trie* trie)
{
	ENTER;
	
	avl_insert(this->tree, trie);
	
	EXIT;
}

static void trieset_foreach(
	const struct trieset* this,
	void (*runme)(struct trie* subtrie))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
		runme(node->item);
	
	EXIT;
}

static void free_trieset(struct trieset* this)
{
	avl_free_tree(this->tree);
	free(this);
}

struct trie_to_trieset
{
	struct trie* trie;
	struct trieset* trieset;
};

static struct trie_to_trieset* new_trie_to_trieset(struct trie* trie, struct trieset* trieset)
{
	ENTER;
	
	struct trie_to_trieset* this = smalloc(sizeof(*this));
	
	this->trie = trie;
	this->trieset = trieset;
	
	EXIT;
	return this;
}

static int compare_trie_to_triesets(const void* a, const void* b)
{
	const struct trie_to_trieset *A = a, *B = b;
	if (A->trie > B->trie)
		return +1;
	if (A->trie < B->trie)
		return -1;
	return 0;
}

static void free_trie_to_trieset(void* ptr)
{
	struct trie_to_trieset* this = ptr;
	free_trieset(this->trieset);
	free(this);
}

static void add_dep(struct avl_tree_t* tree, struct trie* trie1, struct trie* trie2)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(tree, &trie1);
	
	if (node)
	{
		struct trie_to_trieset* old = node->item;
		
		trieset_add(old->trieset, trie2);
	}
	else
	{
		struct trieset* trieset = new_trieset();
		
		trieset_add(trieset, trie2);
		
		struct trie_to_trieset* new = new_trie_to_trieset(trie1, trieset);
		
		avl_insert(tree, new);
	}
	
	EXIT;
}

static struct trieset* get_deps(struct avl_tree_t* tree, struct trie* trie)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(tree, &trie);
	
	if (node)
	{
		struct trie_to_trieset* old = node->item;
		EXIT;
		return old->trieset;
	}
	else
	{
		struct trieset* empty = new_trieset();
		
		avl_insert(tree, new_trie_to_trieset(trie, empty));
		
		EXIT;
		return empty;
	}
}

#ifdef DOTOUT
static void dotout(
	struct stateinfo* stateinfo,
	struct avl_tree_t* dependent_on,
	struct trie* focus)
{
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	FILE* stream = fopen(path, "w");
	
	void trie_dotout(struct trie* prefix, struct trie* trie, char* lookaheads)
	{
		ENTER;
		
		fprintf(stream, ""
			"\"%p_%p\" [" "\n"
				"shape = box" "\n"
				"style = \"%s\"" "\n"
				"label = \"%s\"" "\n"
				"peripheries = %u" "\n"
			"]" "\n"
		"", prefix, trie,
			trie == focus ? "bold" : "",
			trie->reduce_as ? lookaheads : "", trie->reduce_as ? 2 : 1);
		
		for (unsigned i = 0, n = trie->transitions.n; i < n; i++)
		{
			const struct trie_transition* const trans = trie->transitions.data[i];
			
			fprintf(stream, ""
				"\"%p_%p\" -> \"%p_%p\" [" "\n"
					"label = \"#%u token\"" "\n"
				"]" "\n"
			"", prefix, trie, prefix, trans->to, trans->token);
			
			trie_dotout(prefix, trans->to, lookaheads);
		}
		
		for (unsigned i = 0, n = trie->grammar_transitions.n; i < n; i++)
		{
			const struct trie_grammar_transition* const trans = trie->grammar_transitions.data[i];
			
			fprintf(stream, ""
				"\"%p_%p\" -> \"%p_%p\" [" "\n"
					"label = \"%s\"" "\n"
				"]" "\n"
			"", prefix, trie, prefix, trans->to, trans->grammar->chars);
			
			trie_dotout(prefix, trans->to, lookaheads);
		}
		
		EXIT;
	}
	
	fprintf(stream, "digraph {");
	
	fprintf(stream, "rankdir = LR;");
	
	stateinfo_foreach(stateinfo, ({
		void runme(struct trie* trie, struct unsignedset* lookaheads)
		{
			char* label = unsignedset_to_string(lookaheads);
			
			trie_dotout(trie, trie, label ?: "");
			
			trieset_foreach(get_deps(dependent_on, trie), ({
				void runme(struct trie* subtrie)
				{
					fprintf(stream, ""
						"\"%p_%p\" -> \"%p_%p\" [" "\n"
							"color = black" "\n"
							"style = dashed" "\n"
							"constraint = false" "\n"
						"]" "\n"
					"", subtrie, subtrie, trie, trie);
				}
				runme;
			}));
			
			free(label);
		}
		runme;
	}));
	
	fprintf(stream, "}");
	
	fclose(stream);
}
#endif

void expand_stateinfo(
	struct stateinfo* stateinfo,
	struct avl_tree_t* named_tries,
	struct avl_tree_t* named_firsts)
{
	ENTER;
	
	struct quack* explore = new_quack();
	
	struct quack* percolate = new_quack();
	
	stateinfo_foreach2(stateinfo, ({
		void runme(struct stateinfo_node* ele) {
		
			quack_append(explore, ele);
			
			quack_append(percolate, ele->trie);
		}
		runme;
	}));
	
	struct avl_tree_t* dependent_on = avl_alloc_tree(compare_trie_to_triesets, free_trie_to_trieset);
	
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_trie_to_triesets, free_trie_to_trieset);
	
	#ifdef DOTOUT
	dotout(stateinfo, dependent_on, NULL);
	#endif
	
	// expand stateinfo, setting up lookahead dependencies:
	while (quack_len(explore))
	{
		struct stateinfo_node* node = quack_pop(explore);
		
		struct trie* const trie = node->trie;
		
		for (unsigned i = 0, n = trie->grammar_transitions.n; i < n; i++)
		{
			struct trie_grammar_transition *const ele = trie->grammar_transitions.data[i];
			
			struct trie* subgrammar_start;
			
			{
				struct avl_node_t* node = avl_search(named_tries, &ele->grammar);
				
				assert(node);
				
				struct named_trie* ntrie = node->item;
				
				subgrammar_start = ntrie->trie;
			}
			
			struct trie* const to = ele->to;
			
			struct unsignedset* lookaheads = new_unsignedset();
			
			for (unsigned i = 0, n = to->transitions.n; i < n; i++)
			{
				unsignedset_add(lookaheads, to->transitions.data[i]->token);
			}
			
			for (unsigned i = 0, n = to->grammar_transitions.n; i < n; i++)
			{
				unsignedset_update(lookaheads, get_firsts(named_firsts, to->grammar_transitions.data[i]->grammar));
			}
			
			if (to->reduce_as)
			{
				add_dep(dependent_on, subgrammar_start, trie);
				add_dep(dependent_of, trie, subgrammar_start);
			}
			
			struct stateinfo_node* node = stateinfo_add(stateinfo, subgrammar_start, lookaheads);
			
			if (node)
			{
				quack_append(explore, node);
				
				quack_append(percolate, subgrammar_start);
			}
			
			#ifdef DOTOUT
			dotout(stateinfo, dependent_on, trie);
			#endif
		}
	}
	
	// percolate lookaheads:
	while (quack_len(percolate))
	{
		struct trie* const trie = quack_pop(percolate);
		
		struct unsignedset* lookaheads = stateinfo_get_lookaheads(stateinfo, trie);
		
		bool has_changed = false;
		
		trieset_foreach(get_deps(dependent_on, trie), ({
			void runme(struct trie* dep)
			{
				has_changed = unsignedset_update(lookaheads, stateinfo_get_lookaheads(stateinfo, dep));
			}
			runme;
		}));
		
		if (has_changed)
		{
			trieset_foreach(get_deps(dependent_of, trie), ({
				void runme(struct trie* dep)
				{
					quack_append(percolate, dep);
				}
				runme;
			}));
		}
		
		#ifdef DOTOUT
		dotout(stateinfo, dependent_on, trie);
		#endif
	}
	
	avl_free_tree(dependent_of);
	avl_free_tree(dependent_on);
	
	free_quack(percolate);
	free_quack(explore);
	
	EXIT;
}










