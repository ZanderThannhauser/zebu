
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
#include <quack/len.h>
#ifdef WINDOWS_PLATFORM
#include <compat/timer_thread.h>
#endif
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

struct rbundle regex_clone2(struct rbundle original)
{
	ENTER;
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free);
	
	struct quack* todo = new_quack();
	
	struct regex* new_start = new_regex();
	
	{
		assert(original.start);
		struct mapping* mapping = new_mapping(original.start, new_start);
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
	
	#ifdef LINUX_PLATFORM
	signal(SIGALRM, handler);
	#else
	#ifdef WINDOWS_PLATFORM
	timer_handler = handler;
	#else
	#error bad platform
	#endif
	#endif
	#endif
	
	while (quack_is_nonempty(todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct mapping* mapping = quack_pop(todo);
		
		struct regex* const old = mapping->old;
		struct regex* const new = mapping->new;
		
		new->accepts = old->accepts;
		
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
		for (unsigned i = 0, n = old->lambdas.n; i < n; i++)
		{
			struct regex* const subold = old->lambdas.data[i];
			
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
	
	struct regex* new_accepts = NULL;
	
	if (original.accepts)
	{
		struct avl_node_t* node = avl_search(mappings, &original.accepts);
		assert(node);
		struct mapping* mapping = node->item;
		new_accepts = mapping->new;
	}
	
	free_quack(todo);
	
	avl_free_tree(mappings);
	
	EXIT;
	return (struct rbundle) {new_start, new_accepts};
}


























