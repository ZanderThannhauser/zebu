
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/foreach.h>
#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/len.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <named/unsignedset/struct.h>
#include <named/unsignedset/new.h>
#include <named/unsignedset/compare.h>
#include <named/unsignedset/free.h>

#include <named/stringset/struct.h>
#include <named/stringset/new.h>
#include <named/stringset/compare.h>
#include <named/stringset/free.h>

#include <named/trie/struct.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/update.h>

#ifdef DOTOUT
#include <limits.h>
#include <stdio.h>
#include <misc/frame_counter.h>
#include <set/unsigned/to_string.h>
#include <string/struct.h>
#include <stdlib.h>
#endif

#include <set/string/new.h>
#include <set/string/add.h>
#include <set/string/foreach.h>

#include "trie/struct.h"

#include "calc_firsts.h"

static struct stringset* get(struct avl_tree_t* tree, struct string* name)
{
	struct avl_node_t* node = avl_search(tree, &name);
	
	if (node)
	{
		struct named_stringset* nss = node->item;
		
		return nss->stringset;
	}
	else
	{
		struct stringset* ss = new_stringset();
		
		avl_insert(tree, new_named_stringset(name, ss));
		
		return ss;
	}
}

static void add(struct avl_tree_t* tree, struct string* name, struct string* addme)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(tree, &name);
	
	if (node)
	{
		struct named_stringset* nss = node->item;
		
		stringset_add(nss->stringset, addme);
	}
	else
	{
		struct stringset* ss = new_stringset();
		
		stringset_add(ss, addme);
		
		avl_insert(tree, new_named_stringset(name, ss));
	}
	
	EXIT;
}

struct unsignedset* get_firsts(struct avl_tree_t* named_firsts, struct string* name)
{
	struct avl_node_t* node = avl_search(named_firsts, &name);
	assert(node);
	struct named_unsignedset* named = node->item;
	return named->unsignedset;
}

#ifdef DOTOUT
static void dotout(
	struct avl_tree_t* named_firsts,
	struct avl_tree_t* dependent_of,
	struct string* focus)
{
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	FILE* stream = fopen(path, "w");
	
	fprintf(stream, "digraph {\n");
	
	fprintf(stream, "rankdir = BT\n");
	
	fprintf(stream, "layout = neato\n");
	
	fprintf(stream, "overlap = false\n");
	
	avl_tree_foreach(named_firsts, ({
		void runme(void* ptr)
		{
			struct named_unsignedset* named_first = ptr;
			
			struct string* my_name = named_first->name;
			
			dpvs(my_name);
			
			char* tokens = unsignedset_to_string(named_first->unsignedset);
			
			fprintf(stream, ""
				"\"%s\" [" "\n"
					"label = \"{%s | %s}\"" "\n"
					"shape = record" "\n"
				"]" "\n"
			"", my_name->chars, my_name->chars, tokens ?: "");
			
			free(tokens);
			
			stringset_foreach(get(dependent_of, my_name), ({
				void runme(struct string* their_name)
				{
					dpvs(their_name);
					
					fprintf(stream, ""
						"\"%s\" -> \"%s\" [" "\n"
						"]" "\n"
					"", my_name->chars, their_name->chars);
				}
				runme;
			}));
		}
		runme;
	}));
	
	if (focus)
	{
		fprintf(stream, ""
			"\"%s\" [" "\n"
				"style = bold" "\n"
			"]" "\n"
		"", focus->chars);
	}
	
	fprintf(stream, "}\n");
	
	fclose(stream);
	
	EXIT;
}
#endif

struct avl_tree_t* calc_firsts(struct avl_tree_t* named_tries)
{
	ENTER;
	
	struct avl_tree_t* named_firsts = avl_alloc_tree(compare_named_unsignedsets, free_named_unsignedset);
	
	struct avl_tree_t* dependent_on = avl_alloc_tree(compare_named_stringsets, free_named_stringset);
	
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_named_stringsets, free_named_stringset);
	
	struct quack* todo = new_quack();
	
	avl_tree_foreach(named_tries, ({
		void runme(void* ptr)
		{
			struct named_trie* ntrie = ptr;
			
			struct string* name = ntrie->name;
			
			struct trie* trie = ntrie->trie;
			
			struct unsignedset* firsts = new_unsignedset();
			
			for (unsigned i = 0, n = trie->transitions.n; i < n; i++)
			{
				unsignedset_add(firsts, trie->transitions.data[i]->token);
			}
			
			for (unsigned i = 0, n = trie->grammar_transitions.n; i < n; i++)
			{
				struct string* const grammar = trie->grammar_transitions.data[i]->grammar;
				
				add(dependent_on, name, grammar);
				add(dependent_of, grammar, name);
			}
			
			quack_append(todo, name);
			
			avl_insert(named_firsts, new_named_unsignedset(name, firsts));
		}
		runme;
	}));
	
	#ifdef DOTOUT
	dotout(named_firsts, dependent_of, NULL);
	#endif
	
	// percolate:
	while (quack_len(todo))
	{
		struct string* name = quack_pop(todo);
		
		struct unsignedset* firsts = get_firsts(named_firsts, name);
		
		bool has_changed = false;
		
		stringset_foreach(get(dependent_on, name), ({
			void runme(struct string* dep_name)
			{
				has_changed = unsignedset_update(firsts, get_firsts(named_firsts, dep_name));
			}
			runme;
		}));
		
		if (has_changed)
		{
			stringset_foreach(get(dependent_of, name), ({
				void runme(struct string* dep_name)
				{
					quack_append(todo, dep_name);
				}
				runme;
			}));
		}
		
		#ifdef DOTOUT
		dotout(named_firsts, dependent_of, name);
		#endif
	}
	
	free_quack(todo);
	
	avl_free_tree(dependent_on);
	
	avl_free_tree(dependent_of);
	
	EXIT;
	return named_firsts;
}









