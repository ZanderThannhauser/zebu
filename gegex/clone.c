
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/search.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <gegex/struct.h>
#include <gegex/new.h>

#ifdef VERBOSE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <misc/default_sighandler.h>
#include <quack/len.h>
#endif

#include "transition/struct.h"
#include "grammar/struct.h"
#include "add_transition.h"
#include "add_lambda_transition.h"
#include "add_grammar_transition.h"

#include "dotout.h"
#include "clone.h"

struct mapping
{
	struct gegex* old; // must be the first
	struct gegex* new;
};

static struct mapping* new_mapping(struct gegex* old, struct gegex* new)
{
	struct mapping* this = smalloc(sizeof(*this));
	this->old = old, this->new = new;
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

struct gbundle gegex_clone2(struct gbundle original)
{
	ENTER;
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free);
	
	struct quack* todo = new_quack();
	
	struct gegex* new_start = new_gegex();
	
	{
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
			"\e[K" "zebu: grammar clone: %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler);
	#endif
	
	while (quack_is_nonempty(todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct mapping* mapping = quack_pop(todo);
		
		struct gegex* const old = mapping->old;
		struct gegex* const new = mapping->new;
		
		new->accepts = old->accepts;
		
		// for each transition:
		for (unsigned i = 0, n = old->transitions.n; i < n; i++)
		{
			struct gegex_transition* const ele = old->transitions.data[i];
			
			struct avl_node_t* node = avl_search(mappings, &ele->to);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				gegex_add_transition(new, ele->token, ele->whitespace, ele->structinfo, submapping->new);
			}
			else
			{
				struct gegex* subnew = new_gegex();
				
				struct mapping* submapping = new_mapping(ele->to, subnew);
				
				gegex_add_transition(new, ele->token, ele->whitespace, ele->structinfo, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
		
		for (unsigned i = 0, n = old->grammars.n; i < n; i++)
		{
			struct gegex_grammar_transition* const ele = old->grammars.data[i];
			
			struct avl_node_t* node = avl_search(mappings, &ele->to);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				gegex_add_grammar_transition(new, ele->grammar, ele->structinfo, submapping->new);
			}
			else
			{
				struct gegex* subnew = new_gegex();
				
				struct mapping* submapping = new_mapping(ele->to, subnew);
				
				gegex_add_grammar_transition(new, ele->grammar, ele->structinfo, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
		
		// for each lambda transition:
		for (unsigned i = 0, n = old->lambdas.n; i < n; i++)
		{
			struct gegex* const subold = old->lambdas.data[i];
			
			struct avl_node_t* node = avl_search(mappings, &subold);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				gegex_add_lambda_transition(new, submapping->new);
			}
			else
			{
				struct gegex* subnew = new_gegex();
				
				struct mapping* submapping = new_mapping(subold, subnew);
				
				gegex_add_lambda_transition(new, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	struct gegex* new_end = NULL;
	
	if (original.accepts)
	{
		struct avl_node_t* node = avl_search(mappings, &original.accepts);
		assert(node);
		struct mapping* submapping = node->item;
		new_end = submapping->new;
	}
	
	free_quack(todo);
	
	avl_free_tree(mappings);
	
	EXIT;
	return (struct gbundle) {new_start, new_end};
}

