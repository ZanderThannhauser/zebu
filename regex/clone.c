
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/search.h>
#include <avl/insert.h>
#include <avl/free_tree.h>
#include <avl/alloc_tree.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#ifdef VERBOSE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <misc/default_sighandler.h>
#endif

#include "struct.h"
#include "new.h"
#include "add_lambda_transition.h"
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

struct regex* regex_clone(struct regex* original_start)
{
	ENTER;
	
	TODO;
	#if 0
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free);
	
	struct quack* todo = new_quack();
	
	struct regex* new_start = new_regex();
	
	{
		struct mapping* mapping = new_mapping(original_start, new_start);
		avl_insert(mappings, mapping);
		quack_append(todo, mapping);
	}
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: regex clone: %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
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
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* const to = old->transitions[i];
			
			if (to)
			{
				struct avl_node_t* node = avl_search(mappings, &to);
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					new->transitions[i] = submapping->new;
				}
				else
				{
					struct regex* subnew = new_regex();
					
					struct mapping* submapping = new_mapping(to, subnew);
					
					new->transitions[i] = subnew;
					
					avl_insert(mappings, submapping);
					
					quack_append(todo, submapping);
				}
			}
		}
		
		// for each lambda transition:
		for (unsigned i = 0, n = old->lambda_transitions.n; i < n; i++)
		{
			struct regex* const subold = old->lambda_transitions.data[i];
			
			struct avl_node_t* node = avl_search(mappings, &subold);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				regex_add_lambda_transition(new, submapping->new);
			}
			else
			{
				struct regex* subnew = new_regex();
				
				struct mapping* submapping = new_mapping(subold, subnew);
				
				regex_add_lambda_transition(new, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
		
		if (old->EOF_transition_to)
		{
			TODO;
		}
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	free_quack(todo);
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
	#endif
}

struct rbundle regex_clone_nfa(
	struct regex* start, struct regex* end)
{
	ENTER;
	
	TODO;
	#if 0
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free);
	
	struct quack* todo = new_quack();
	
	struct regex* new_start = new_regex();
	
	{
		struct mapping* mapping = new_mapping(start, new_start);
		avl_insert(mappings, mapping);
		quack_append(todo, mapping);
	}
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: regex clone: %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
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
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* const to = old->transitions[i];
			
			if (to)
			{
				struct avl_node_t* node = avl_search(mappings, &to);
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					new->transitions[i] = submapping->new;
				}
				else
				{
					struct regex* subnew = new_regex();
					
					struct mapping* submapping = new_mapping(to, subnew);
					
					new->transitions[i] = subnew;
					
					avl_insert(mappings, submapping);
					
					quack_append(todo, submapping);
				}
			}
		}
		
		// for each lambda transition:
		for (unsigned i = 0, n = old->lambda_transitions.n; i < n; i++)
		{
			struct regex* const subold = old->lambda_transitions.data[i];
			
			struct avl_node_t* node = avl_search(mappings, &subold);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				regex_add_lambda_transition(new, submapping->new);
			}
			else
			{
				struct regex* subnew = new_regex();
				
				struct mapping* submapping = new_mapping(subold, subnew);
				
				regex_add_lambda_transition(new, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
		
		if (old->EOF_transition_to)
		{
			TODO;
		}
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	struct regex* new_end;
	
	{
		struct avl_node_t* node = avl_search(mappings, &end);
		assert(node);
		struct mapping* mapping = node->item;
		new_end = mapping->new;
	}
	
	free_quack(todo);
	
	avl_free_tree(mappings);
	
	EXIT;
	return (struct clone_nfa_bundle) {new_start, new_end};
	#endif
}


























