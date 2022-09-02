
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

/*#include <memory/smalloc.h>*/

#include <set/gegex/struct.h>

/*#include <avl/alloc_tree.h>*/
/*#include <avl/search.h>*/
/*#include <avl/insert.h>*/
/*#include <avl/free_tree.h>*/

#ifdef VERBOSE
#include <quack/struct.h>
#include <misc/default_sighandler.h>
#endif

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"
#include "../state/add_grammar_transition.h"
#include "../dotout.h"

#include "same_as_node/struct.h"

#include "clone.h"

struct mapping
{
	struct gegex* old; // must be the first
	struct gegex* new;
};

static struct mapping* new_mapping(struct gegex* old, struct gegex* new)
{
	struct mapping* this = smalloc(sizeof(*this));
	this->old = old;
	this->new = new;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping* A = a, *B = b;
	
	if (A->old > B->old)
		return +1;
	else if (A->old < B->old)
		return -1;
	else
		return  0;
}

static struct gegex* find(struct avl_tree_t* connections, struct gegex* a)
{
	struct avl_node_t* node = avl_search(connections, &a);
	
	assert(node);
	
	struct gegex_same_as_node* sa = node->item;
	
	assert(sa->set->n);
	
	return sa->set->tree->head->item;
}

struct gegex* gegex_simplify_dfa_clone(
	struct avl_tree_t* connections,
	struct gegex* original_start)
{
	ENTER;
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free);
	
	struct quack* todo = new_quack();
	
	struct gegex* new_start = new_gegex();
	
	{
		struct gegex* cloneme = find(connections, original_start);
		
		struct mapping* mapping = new_mapping(cloneme, new_start);
		
		avl_insert(mappings, mapping);
		
		quack_append(todo, mapping);
	}
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + todo->n;
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[k" "%s: gegex clone: %u of %u (%.2f%%)\r", argv0,
				completed, total,
				(double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler);
	#endif
	
	while (quack_len(todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct mapping* mapping = quack_pop(todo);
		
		struct gegex* const old = mapping->old;
		struct gegex* const new = mapping->new;
		
		new->is_reduction_point = old->is_reduction_point;
		
		for (unsigned i = 0, n = old->transitions.n; i < n; i++)
		{
			struct gegex_transition* const ele = old->transitions.data[i];
			
			struct gegex* cloneme = find(connections, ele->to);
			
			struct avl_node_t* node = avl_search(mappings, &cloneme);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				gegex_add_transition(new, ele->token, ele->tags, submapping->new);
			}
			else
			{
				struct gegex* subnew = new_gegex();
				
				struct mapping* submapping = new_mapping(cloneme, subnew);
				
				gegex_add_transition(new, ele->token, ele->tags, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
		
		for (unsigned i = 0, n = old->grammar_transitions.n; i < n; i++)
		{
			struct gegex_grammar_transition* const ele = old->grammar_transitions.data[i];
			
			struct gegex* cloneme = find(connections, ele->to);
			
			struct avl_node_t* node = avl_search(mappings, &cloneme);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				gegex_add_grammar_transition(new, ele->grammar, ele->tags, submapping->new);
			}
			else
			{
				struct gegex* subnew = new_gegex();
				
				struct mapping* submapping = new_mapping(cloneme, subnew);
				
				gegex_add_grammar_transition(new, ele->grammar, ele->tags, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
		
		#ifdef DOTOUT
		gegex_dotout(new_start, NULL, __PRETTY_FUNCTION__);
		#endif
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	free_quack(todo);
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
}


















