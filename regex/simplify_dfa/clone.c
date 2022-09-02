
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

/*#include <memory/smalloc.h>*/

#include <set/regex/struct.h>

#include <avl/alloc_tree.h>
#include <avl/search.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#ifdef VERBOSE
#include <quack/struct.h>
#include <misc/default_sighandler.h>
#endif

#include "../state/struct.h"
#include "../state/new.h"
#include "../state/add_transition.h"
#include "../state/set_default_transition.h"
#include "../state/set_EOF_transition.h"

#include "../dotout.h"

#include "same_as_node/struct.h"

#include "clone.h"

struct mapping
{
	struct regex* old; // must be the first
	struct regex* new;
};

static struct mapping* new_mapping(struct regex* old, struct regex* new)
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

static struct regex* find(struct avl_tree_t* connections, struct regex* a)
{
	struct avl_node_t* node = avl_search(connections, &a);
	
	assert(node);
	
	struct regex_same_as_node* sa = node->item;
	
	assert(sa->set->n);
	
	return sa->set->tree->head->item;
}

struct regex* regex_simplify_dfa_clone(
	struct avl_tree_t* connections,
	struct regex* original_start)
{
	ENTER;
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free);
	
	struct quack* todo = new_quack();
	
	struct regex* new_start = new_regex();
	
	{
		struct regex* cloneme = find(connections, original_start);
		
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
			"\e[k" "%s: regex-clone: %u of %u (%.2f%%)\r", argv0,
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
		
		struct regex* const old = mapping->old;
		struct regex* const new = mapping->new;
		
		new->is_accepting = old->is_accepting;
		
		// for each transition:
		for (unsigned i = 0, n = old->transitions.n; i < n; i++)
		{
			struct regex_transition* const ele = old->transitions.data[i];
			
			struct regex* cloneme = find(connections, ele->to);
			
			struct avl_node_t* node = avl_search(mappings, &cloneme);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				regex_add_transition(new, ele->value, submapping->new);
			}
			else
			{
				struct regex* subnew = new_regex();
				
				struct mapping* submapping = new_mapping(cloneme, subnew);
				
				regex_add_transition(new, ele->value, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
		
		// for default transition:
		if (old->default_transition.to)
		{
			struct regex* cloneme = find(connections, old->default_transition.to);
			
			struct avl_node_t* node = avl_search(mappings, &cloneme);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				regex_set_default_transition(new, old->default_transition.exceptions, submapping->new);
			}
			else
			{
				struct regex* subnew = new_regex();
				
				struct mapping* submapping = new_mapping(cloneme, subnew);
				
				regex_set_default_transition(new, old->default_transition.exceptions, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
		
		#ifdef DOTOUT
		regex_dotout(new_start, __PRETTY_FUNCTION__);
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


























