
#include <debug.h>

#include <avl/avl.h>
#include <avl/new.h>

#include <memory/smalloc.h>

#include <parser/token/regex/state/struct.h>

#include "struct.h"
#include "compare.h"

static int helper(
	struct regex* a,
	struct regex* b)
{
	int cmp = 0;
	ENTER;
	
	TODO;
	
	EXIT;
	return cmp;
}

int compare_nodes(const void* a, const void* b)
{
	int cmp;
	ENTER;
	
	const struct node* A = a, *B = b;
	
	struct cache {
		const struct regex *a, *b; // must be the firsts
		
		signed result; // -1, 0, +1
		
	}* new_cache(const struct regex* a, const struct regex* b) {
		
		struct cache* this = smalloc(sizeof(*this));
		
		this->a = a;
		this->b = b;
		this->result = 0;
		
		return this;
	}
	
	int compare_caches(const void* a, const void* b)
	{
		const struct cache *A = a, *B = b;
		
		if (A->a > B->a)
			return +1;
		else if (A->a < B->a)
			return -1;
		else if (A->b > B->b)
			return +1;
		else if (A->b < B->b)
			return -1;
		
		return 0;
	}
	
	void free_cache(void* a)
	{
		struct cache *A = a;
		free(A);
	}
	
	struct avl_tree_t* cache = new_avl_tree(compare_caches, free_cache);
	
	int compare_nodes(struct regex* A, struct regex* B)
	{
		ENTER;
		
		dpv(A);
		dpv(B);
		
		struct avl_node_t* node = avl_search(cache, &(struct cache){A, B});
		
		struct cache* ele;
		
		if (node)
		{
			ele = node->item;
		}
		else
		{
			node = avl_insert(cache, ele = new_cache(A, B));
			
			if (A == B)
				ele->result = 0;
			else if (A->is_accepting > B->is_accepting)
				ele->result = +1;
			else if (A->is_accepting < B->is_accepting)
				ele->result = -1;
			else
			{
				size_t a_i = 0, a_n = A->transitions.n;
				size_t b_i = 0, b_n = B->transitions.n;
				
				while (!ele->result && a_i < a_n && b_i < b_n)
				{
					const struct transition* ele_a = A->transitions.data[a_i++];
					const struct transition* ele_b = B->transitions.data[b_i++];
					
					if (A->default_transition_to)
					{
						TODO;
					}
					
					if (B->default_transition_to)
					{
						TODO;
					}
					
					if (ele_a->value > ele_b->value)
						ele->result = +1;
					else if (ele_a->value < ele_b->value)
						ele->result = -1;
					else
						ele->result = compare_nodes(ele_a->to, ele_b->to);
				}
				
				if (ele->result)
					;
				else if (a_i < a_n)
					ele->result = +1;
				else if (b_i < b_n)
					ele->result = -1;
				else if (!!A->default_transition_to > !!B->default_transition_to)
					ele->result = +1;
				else if (!!B->default_transition_to < !!A->default_transition_to)
					ele->result = -1;
			}
		}
		
		dpv(ele->result);
		
		EXIT;
		return ele->result;
	}
	
	cmp = compare_nodes(A->token, B->token);
	
	avl_free_tree(cache);
	
	EXIT;
	return cmp;
}


