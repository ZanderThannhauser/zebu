
#include <string.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/safe_insert.h>

#include "cache/struct.h"
#include "cache/new.h"

#include "../state/struct.h"

#include "are_equal.h"

bool gegex_are_equal(
	struct avl_tree_t* cache,
	const struct gegex* a,
	const struct gegex* b)
{
	bool are_equal = true;
	ENTER;
	
	dpv(a);
	dpv(b);
	
	if (a > b)
	{
		typeof(a) t = a;
		a = b, b = t;
	}
	
	dpv(a);
	dpv(b);
	
	struct avl_node_t* node = avl_search(cache, &(struct gegex_cache){a, b});
	
	struct gegex_cache* ele;
	
	if (node)
	{
		ele = node->item;
		
		are_equal = ele->are_equal;
	}
	else
	{
		safe_avl_insert(cache, ele = new_gegex_cache(a, b));
		
		if (a == b)
			are_equal = true;
		else if (a->is_reduction_point != b->is_reduction_point)
			are_equal = false;
		else
		{
			size_t a_i = 0, a_n = a->transitions.n;
			size_t b_i = 0, b_n = b->transitions.n;
			
			while (are_equal && a_i < a_n && b_i < b_n)
			{
				dpv(a_i);
				dpv(b_i);
				
				const struct transition* ele_a = a->transitions.data[a_i];
				const struct transition* ele_b = b->transitions.data[b_i];
				
				dpv(ele_a->token);
				dpv(ele_b->token);
				
				if (ele_a->token != ele_b->token)
					are_equal = false;
				else
				{
					are_equal = gegex_are_equal(cache, ele_a->to, ele_b->to);
					a_i++, b_i++;
				}
			}
			
			if (are_equal && (a_i < a_n || b_i < b_n))
				are_equal = false;
			
			a_i = 0, a_n = a->grammar_transitions.n;
			b_i = 0, b_n = b->grammar_transitions.n;
			
			while (are_equal && a_i < a_n && b_i < b_n)
			{
				dpv(a_i);
				dpv(b_i);
				
				const struct gtransition* ele_a = a->grammar_transitions.data[a_i];
				const struct gtransition* ele_b = b->grammar_transitions.data[b_i];
				
				dpvs(ele_a->grammar);
				dpvs(ele_b->grammar);
				
				if (strcmp(ele_a->grammar, ele_b->grammar))
					are_equal = false;
				else
				{
					are_equal = gegex_are_equal(cache, ele_a->to, ele_b->to);
					a_i++, b_i++;
				}
			}
			
			if (are_equal && (a_i < a_n || b_i < b_n))
				are_equal = false;
		}
		
		ele->are_equal = are_equal;
	}
	
	dpvb(ele->are_equal);
	
	EXIT;
	return are_equal;
}



