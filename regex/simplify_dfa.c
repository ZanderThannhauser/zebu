
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <avl/foreach.h>
#include <avl/alloc_tree.h>
#include <avl/search.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <memory/smalloc.h>

#include <quack/new.h>
#include <quack/is_nonempty.h>
#include <quack/append.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <heap/new.h>
#include <heap/is_nonempty.h>
#include <heap/pop.h>
#include <heap/push.h>
#include <heap/free.h>

#include <regex/struct.h>
#include <regex/new.h>

#include <set/ptr/new.h>
#include <set/ptr/add.h>
#include <set/ptr/clone.h>
#include <set/ptr/foreach.h>
#include <set/ptr/get_head.h>
#include <set/ptr/contains.h>
#include <set/ptr/discard.h>
#include <set/ptr/free.h>

#ifdef VERBOSE
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <set/ptr/len.h>
#include <heap/len.h>
#include <misc/default_sighandler.h>
#endif

#include "simplify_dfa.h"

struct pair
{
	struct regex *a, *b;
};

static struct pair* new_pair(struct regex* a, struct regex* b)
{
	ENTER;
	
	struct pair* this = smalloc(sizeof(*this));
	
	assert(a < b);
	
	this->a = a;
	this->b = b;
	
	EXIT;
	return this;
}

static int compare_pairs(const void* a, const void* b)
{
	int cmp = 0;
	const struct pair *A = a, *B = b;
	ENTER;
	
	if (A->a > B->a)
		cmp = +1;
	else if (A->a < B->a)
		cmp = -1;
	else if (A->b > B->b)
		cmp = +1;
	else if (A->b < B->b)
		cmp = -1;
	
	EXIT;
	return cmp;
}

struct dependent_of_node
{
	struct pair pair;
	
	struct avl_tree_t* dependent_of;
};

static struct dependent_of_node* new_dependent_of_node(
	struct regex* a, struct regex* b)
{
	ENTER;
	
	struct dependent_of_node* this = smalloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->dependent_of = avl_alloc_tree(compare_pairs, free);
	
	EXIT;
	return this;
}

static int compare_dependent_of_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct dependent_of_node *A = a, *B = b;
	ENTER;
	
	cmp = compare_pairs(&A->pair, &B->pair);
	
	EXIT;
	return cmp;
}

static void free_dependent_of_node(void* ptr)
{
	struct dependent_of_node* this = ptr;
	ENTER;
	
	avl_free_tree(this->dependent_of);
	
	free(this);
	
	EXIT;
}

struct task
{
	struct pair pair;
	
	unsigned hopcount;
};

static struct task* new_task(
	struct regex* a, struct regex* b,
	unsigned hopcount)
{
	ENTER;
	
	struct task* this = malloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->hopcount = hopcount;
	
	EXIT;
	return this;
}

static int compare_tasks(const void* a, const void* b)
{
	const struct task* A = a, *B = b;
	int cmp;
	ENTER;
	
	if (A->hopcount > B->hopcount)
		cmp = +1;
	else if (A->hopcount < B->hopcount)
		cmp = -1;
	else
		cmp = +0;
	
	EXIT;
	return cmp;
}

static void add_dep(
	struct avl_tree_t* dependent_of,
	struct regex* a_on, struct regex* b_on,
	struct regex* a_of, struct regex* b_of)
{
	ENTER;
	
	if (a_of > b_of)
	{
		struct regex* swap = b_of;
		b_of = a_of, a_of = swap;
	}
	
	struct avl_node_t* node = avl_search(dependent_of, &(struct pair){a_of, b_of});
	
	if (node)
	{
		struct dependent_of_node* old = node->item;
		
		if (!avl_search(old->dependent_of, &(struct pair){a_on, b_on}))
		{
			struct pair* dep = new_pair(a_on, b_on);
			
			avl_insert(old->dependent_of, dep);
		}
	}
	else
	{
		struct dependent_of_node* new = new_dependent_of_node(a_of, b_of);
		
		struct pair* dep = new_pair(a_on, b_on);
		
		avl_insert(new->dependent_of, dep);
		
		avl_insert(dependent_of, new);
	}
	
	EXIT;
}

static struct ptrset* build_universe(struct regex* start)
{
	ENTER;
	
	struct ptrset* universe = new_ptrset();
	
	struct quack* todo = new_quack();
	
	quack_append(todo, start);
	
	ptrset_add(universe, start);
	
	while (quack_is_nonempty(todo))
	{
		struct regex* node = quack_pop(todo);
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct regex* const to = node->transitions[i];
			
			if (to && ptrset_add(universe, to))
				quack_append(todo, to);
		}
		
		if (node->EOF_transition_to)
		{
			struct regex* const to = node->EOF_transition_to;
			
			if (ptrset_add(universe, to))
				quack_append(todo, to);
		}
	}
	
	free_quack(todo);
	
	EXIT;
	return universe;
}

struct same_as_node
{
	struct regex* state;
	
	struct ptrset* set;
};

static struct same_as_node* new_same_as_node(
	struct regex* state, struct ptrset* set)
{
	ENTER;
	
	struct same_as_node* this = smalloc(sizeof(*this));
	
	this->state = state;
	
	this->set = set;
	
	EXIT;
	return this;
}

static int compare_same_as_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct same_as_node* A = a, *B = b;
	ENTER;
	
	if (A->state > B->state)
		cmp = +1;
	else if (A->state < B->state)
		cmp = -1;
	else
		cmp = +0;
	
	EXIT;
	return cmp;
}

static void free_same_as_node(void* ptr)
{
	struct same_as_node* this = ptr;
	ENTER;
	
	free_ptrset(this->set);
	
	free(this);
	
	EXIT;
}

static bool mark_as_unequal(
	struct avl_tree_t* connections,
	struct pair* pair)
{
	ENTER;
	
	struct avl_node_t* a_node = avl_search(connections, &pair->a);
	struct avl_node_t* b_node = avl_search(connections, &pair->b);
	
	assert(a_node && b_node);
	
	struct same_as_node* a_sa = a_node->item, *b_sa = b_node->item;
	
	bool removed = false;
	
	if (ptrset_contains(a_sa->set, pair->b))
	{
		assert(ptrset_contains(b_sa->set, pair->a));
		
		ptrset_discard(a_sa->set, pair->b);
		ptrset_discard(b_sa->set, pair->a);
		
		removed = true;
	}
	
	dpvb(removed);
	
	EXIT;
	return removed;
}

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
	
	struct same_as_node* sa = node->item;
	
	return ptrset_get_head(sa->set);
}

static struct regex* clone(
	struct avl_tree_t* connections,
	struct regex* original)
{
	ENTER;
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free);
	
	struct quack* todo = new_quack();
	
	struct regex* new_start = new_regex();
	
	{
		struct regex* cloneme = find(connections, original);
		
		struct mapping* mapping = new_mapping(cloneme, new_start);
		
		avl_insert(mappings, mapping);
		
		quack_append(todo, mapping);
	}
	
	while (quack_is_nonempty(todo))
	{
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
				struct regex* cloneme = find(connections, to);
				
				struct avl_node_t* node = avl_search(mappings, &cloneme);
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					new->transitions[i] = submapping->new;
				}
				else
				{
					struct regex* subnew = new_regex();
					
					struct mapping* submapping = new_mapping(cloneme, subnew);
					
					new->transitions[i] = subnew;
					
					avl_insert(mappings, submapping);
					
					quack_append(todo, submapping);
				}
			}
		}
		
		if (old->EOF_transition_to)
		{
			TODO;
			#if 0
			struct regex* cloneme = find(connections, old->EOF_transition_to);
			
			struct avl_node_t* node = avl_search(mappings, &cloneme);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				new->EOF_transition_to = submapping->new;
			}
			else
			{
				struct regex* subnew = new_regex();
				
				struct mapping* submapping = new_mapping(cloneme, subnew);
				
				new->EOF_transition_to = subnew;
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
			#endif
		}
	}
	
	free_quack(todo);
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
}

struct regex* regex_simplify_dfa(struct regex* original)
{
	ENTER;
	
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_dependent_of_nodes, free_dependent_of_node);
	
	struct ptrset* universe = build_universe(original);
	
	struct heap* todo = new_heap(compare_tasks);
	
	#ifdef VERBOSE
	uintmax_t count = 0, n;
	
	void handler1(int _)
	{
		char buffer[1000] = {};
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: regex simplify (building dependencies): %lu of %lu (%.2f%%)\r",
			count, n, (((double) count * 100) / n));
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	{
		n = (ptrset_len(universe) * (ptrset_len(universe) - 1)) / 2;
		
		signal(SIGALRM, handler1);
	}
	#endif
	
	ptrset_foreach(universe, ({
		void runme(void* a_ptr) {
			ptrset_foreach(universe, ({
				void runme(void* b_ptr) {
					if (a_ptr < b_ptr)
					{
						struct regex* const a = a_ptr;
						struct regex* const b = b_ptr;
						
						bool unequal = false;
						
						if (a->accepts != b->accepts)
							unequal = true;
						else if (!a->EOF_transition_to != !b->EOF_transition_to)
							unequal = true;
						else if (a->EOF_transition_to && b->EOF_transition_to)
							add_dep(dependent_of, a, b, a->EOF_transition_to, b->EOF_transition_to);
						
						for (unsigned i = 0, n = 256; !unequal && i < n; i++)
						{
							struct regex* a_to = a->transitions[i];
							struct regex* b_to = b->transitions[i];
							
							if (!a_to != !b_to)
								unequal = true;
							else if (a_to && b_to)
								add_dep(dependent_of, a, b, a_to, b_to);
						}
						
						if (unequal)
						{
							heap_push(todo, new_task(a, b, 0));
						}
						
						#ifdef VERBOSE
						count++;
						#endif
					}
				}
				runme;
			}));
		}
		runme;
	}));
	
	#ifdef VERBOSE
	void handler12(int _)
	{
		char ptr[200] = {};
		
		size_t len = snprintf(ptr, 200,
			"\e[K" "zebu: regex simplify (allocating sets): %lu of %lu (%.2f%%)\r",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	{
		count = 0, n = ptrset_len(universe);
		signal(SIGALRM, handler12);
	}
	#endif
	
	struct avl_tree_t* connections = avl_alloc_tree(compare_same_as_nodes, free_same_as_node);
	
	ptrset_foreach(universe, ({
		void runme(void* ptr) {
			struct regex* a = ptr;
			
			struct ptrset* uni = ptrset_clone(universe);
			
			struct same_as_node* sa = new_same_as_node(a, uni);
			
			avl_insert(connections, sa);
			
			#ifdef VERBOSE
			count++;
			#endif
		}
		runme;
	}));
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler2(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + heap_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: regex simplify (percolate): %u of %u (%.2f%%)\r",
				completed, total,
				(double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler2);
	#endif
	
	while (heap_is_nonempty(todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct task* task = heap_pop(todo);
		
		if (mark_as_unequal(connections, &task->pair))
		{
			struct avl_node_t* node = avl_search(dependent_of, &task->pair);
			
			if (node)
			{
				struct dependent_of_node* dep = node->item;
				
				unsigned hopcount = task->hopcount + 1;
				
				avl_tree_foreach(dep->dependent_of, ({
					void runme(void* ptr) {
						const struct pair* pair = ptr;
						heap_push(todo, new_task(pair->a, pair->b, hopcount));
					}
					runme;
				}));
			}
		}
		
		free(task);
	}
	
	struct regex* new_start = clone(connections, original);
	
	avl_free_tree(dependent_of);
	
	free_ptrset(universe);
	
	avl_free_tree(connections);
	
	free_heap(todo);
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	EXIT;
	return new_start;
}

