
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/search.h>
#include <avl/free_tree.h>

#include <memory/smalloc.h>

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

#ifdef DOTOUT
#include <regex/dotout.h>
#endif

#include "struct.h"
#include "new.h"
#include "intersect_dfas.h"

struct mapping
{
	struct regex* a, *b;
	struct regex* new;
};

static struct mapping* new_mapping(
	struct regex* a, struct regex* b,
	struct regex* new)
{
	ENTER;
	
	struct mapping* this = smalloc(sizeof(*this));
	
	this->a = a;
	this->b = b;
	this->new = new;
	
	EXIT;
	return this;
}

static int compare(const void* a, const void* b)
{
	const struct mapping *A = a, *B = b;
	
	if (A->a > B->a)
		return +1;
	else if (A->a < B->a)
		return -1;
	else if (A->b > B->b)
		return +1;
	else if (A->b < B->b)
		return -1;
	else
		return 0;
}

struct regex* regex_intersect_dfas(struct regex* A_start, struct regex* B_start)
{
	ENTER;
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare, free);
	
	struct quack* todo = new_quack();
	
	struct regex* new_start = new_regex();
	
	{
		struct mapping* mapping = new_mapping(A_start, B_start, new_start);
		
		quack_append(todo, mapping);
		
		avl_insert(mappings, mapping);
	}
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: regex intersect: %u of %u (%.2f%%)\r",
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
		
		struct regex* const A = mapping->a;
		struct regex* const B = mapping->b;
		struct regex* const state = mapping->new;
		
		state->accepts = A->accepts && B->accepts;
		
		dpvb(state->accepts);
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* at = A->transitions[i], *bt = B->transitions[i];
			
			if (at && bt)
			{
				struct avl_node_t* node = avl_search(mappings, &(struct mapping) {at, bt});
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					state->transitions[i] = submapping->new;
				}
				else
				{
					struct regex* substate = new_regex();
					
					struct mapping* submapping = new_mapping(at, bt, substate);
					
					state->transitions[i] = substate;
					
					avl_insert(mappings, submapping);
					
					quack_append(todo, submapping);
				}
			}
		}
		
		#ifdef DOTOUT
		regex_dotout(new_start, __PRETTY_FUNCTION__);
		#endif
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
	
	avl_free_tree(mappings);
	
	free_quack(todo);
	
	EXIT;
	return new_start;
}












