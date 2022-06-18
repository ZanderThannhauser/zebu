
#include <avl/avl.h>
#include <avl/new.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <regex/state/struct.h>

#include "../phase_counter.h"
#include "../dotout.h"

#include "helper.h"
#include "clone.h"
#include "simplify_dfa.h"

struct regex* regex_simplify_dfa(
	struct regex* original_start,
	struct memory_arena* arena)
{
	ENTER;
	
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
	
	int compare_nodes(const void* a, const void* b)
	{
		ENTER;
		
		dpv(a);
		dpv(b);
		
		struct avl_node_t* node = avl_search(cache, &(struct cache){a, b});
		
		struct cache* ele;
		
		if (node)
		{
			ele = node->item;
		}
		else
		{
			node = avl_insert(cache, ele = new_cache(a, b));
			
			const struct regex* A = a, *B = b;
			
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
	
	struct avl_tree_t* unique_nodes = new_avl_tree(compare_nodes, NULL);
	
	// invoke helper to traverse through the nodes
	// querying for uniqueness
	phase_counter++;
	simplify_dfa_helper(unique_nodes, original_start);
	
	struct regex* new_start = simplify_dfa_clone(
		unique_nodes, original_start, arena);
	
	avl_free_tree(unique_nodes);
	avl_free_tree(cache);
	
	#ifdef DEBUGGING
	regex_dotout(new_start);
	#endif
	
	EXIT;
	return new_start;
}
























