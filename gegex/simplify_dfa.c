
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <string/struct.h>
#include <string/are_equal.h>

#include <avl/foreach.h>
#include <avl/alloc_tree.h>
#include <avl/search.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/pop.h>
#include <quack/is_nonempty.h>
#include <quack/free.h>

#include <heap/new.h>
#include <heap/is_nonempty.h>
#include <heap/pop.h>
#include <heap/push.h>
#include <heap/free.h>

#include <set/ptr/new.h>
#include <set/ptr/foreach.h>
#include <set/ptr/add.h>
#include <set/ptr/contains.h>
#include <set/ptr/discard.h>
#include <set/ptr/clone.h>
#include <set/ptr/get_head.h>
#include <set/ptr/free.h>

#include <set/unsigned/compare.h>

#include <yacc/structinfo/compare.h>

#include "transition/struct.h"
#include "grammar/struct.h"
#include "struct.h"
#include "new.h"
#include "add_transition.h"
#include "add_grammar_transition.h"
#include "simplify_dfa.h"
#include "dotout.h"


#ifdef VERBOSE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <set/ptr/len.h>
#include <heap/len.h>
#include <misc/default_sighandler.h>
#endif

struct pair
{
	struct gegex *a, *b;
};

static struct pair* new_pair(struct gegex* a, struct gegex* b)
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
	struct gegex* a, struct gegex* b)
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

static struct ptrset* build_universe(struct gegex* start)
{
	ENTER;
	
	struct ptrset* universe = new_ptrset();
	
	struct quack* todo = new_quack();
	
	quack_append(todo, start);
	
	ptrset_add(universe, start);
	
	while (quack_is_nonempty(todo))
	{
		struct gegex* node = quack_pop(todo);
		
		for (unsigned i = 0, n = node->transitions.n; i < n; i++)
		{
			struct gegex* to = node->transitions.data[i]->to;
			
			if (ptrset_add(universe, to))
			{
				quack_append(todo, to);
			}
		}
		
		for (unsigned i = 0, n = node->grammars.n; i < n; i++)
		{
			struct gegex* to = node->grammars.data[i]->to;
			
			if (ptrset_add(universe, to))
			{
				quack_append(todo, to);
			}
		}
	}
	
	free_quack(todo);
	
	EXIT;
	return universe;
}

struct task
{
	struct pair pair;
	
	unsigned hopcount;
};

static struct task* new_task(
	struct gegex* a, struct gegex* b,
	unsigned hopcount)
{
	ENTER;
	
	struct task* this = smalloc(sizeof(*this));
	
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
	
	dpv(A->hopcount);
	dpv(B->hopcount);
	
	if (A->hopcount > B->hopcount)
		cmp = +1;
	else if (A->hopcount < B->hopcount)
		cmp = -1;
	else
		cmp = +0;
	
	EXIT;
	return cmp;
}

struct same_as_node
{
	struct gegex* state;
	
	struct ptrset* set;
};


static struct same_as_node* new_same_as_node(
	struct gegex* state, struct ptrset* set) {
	ENTER;
	
	struct same_as_node* this = malloc(sizeof(*this));
	
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

static void add_dep(
	struct avl_tree_t* dependent_of,
	struct gegex* a_on, struct gegex* b_on,
	struct gegex* a_of, struct gegex* b_of)
{
	ENTER;
	
	if (a_of > b_of)
	{
		struct gegex* swap = b_of;
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

#ifdef DOTOUT

#include <misc/frame_counter.h>

#include <yacc/structinfo/to_hashtagstring.h>

static void dotout(
	struct ptrset* universe,
	struct avl_tree_t* connections)
{
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	dpvs(path);
	
	FILE* out = fopen(path, "w");
	
	if (!out)
	{
		fprintf(stderr, "zebu: fopen(\"%s\"): %m\n", path);
		abort();
	}
	
	fprintf(out, "digraph {" "\n");
	
	fprintf(out, "\t" "rankdir = LR;" "\n");
	
	struct ptrset* drawn = new_ptrset();
	
	struct ptrset* queued = new_ptrset();
	
	struct quack* todo = new_quack();
	
	ptrset_foreach(universe, ({
		void runme(void* ptr)
		{
			struct gegex* state = ptr;
			
			ptrset_add(queued, state);
			quack_append(todo, state);
		}
		runme;
	}));
	
	while (quack_is_nonempty(todo))
	{
		struct gegex* state = quack_pop(todo);
		
		fprintf(out, ""
			"\"%p\" [" "\n"
				"\t" "shape = %s;" "\n"
				"\t" "label = \"\";" "\n"
				"\t" "style = filled;" "\n"
				"\t" "fillcolor = white;" "\n"
			"]" "\n"
		"", state, state->accepts ? "doublecircle" : "circle");
		
		{
			ptrset_add(drawn, state);
			
			struct avl_node_t* node = avl_search(connections, &state);
			
			assert(node);
			
			struct same_as_node* sa = node->item;
			
			ptrset_foreach(sa->set, ({
				void runme(void* ptr) {
					struct gegex* dep = ptr;
					if (!ptrset_contains(drawn, dep))
					{
						fprintf(out, ""
							"\"%p\" -> \"%p\" [" "\n"
								"\t" "style = dashed" "\n"
								"\t" "constraint = false" "\n"
								"\t" "dir = none" "\n"
							"]" "\n"
						"", state, dep);
					}
				}
				runme;
			}));
		}
		
		// normal transitions:
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct gegex_transition* transition = state->transitions.data[i];
			
			if (ptrset_add(queued, transition->to))
				quack_append(todo, transition->to);
			
			char* label = structinfo_to_hashtagstring(transition->structinfo);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"#%u token%s\"" "\n"
				"]" "\n"
			"", state, transition->to, transition->token, label);
			
			free(label);
		}
		
		// grammar_transitions:
		for (unsigned i = 0, n = state->grammars.n; i < n; i++)
		{
			struct gegex_grammar_transition* transition = state->grammars.data[i];
			
			if (ptrset_add(queued, transition->to))
				quack_append(todo, transition->to);
			
			char* label = structinfo_to_hashtagstring(transition->structinfo);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"%s%s\"" "\n"
				"]" "\n"
			"", state, transition->to, transition->grammar->chars, label);
			
			free(label);
		}
	}
	
	free_ptrset(drawn);
	free_ptrset(queued);
	
	free_quack(todo);
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}
#endif


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
	
	struct same_as_node* sa = node->item;
	
	return ptrset_get_head(sa->set);
}

static struct gegex* clone(
	struct avl_tree_t* connections,
	struct gegex* original)
{
	ENTER;
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free);
	
	struct quack* todo = new_quack();
	
	struct gegex* new_start = new_gegex();
	
	{
		struct gegex* cloneme = find(connections, original);
		
		struct mapping* mapping = new_mapping(cloneme, new_start);
		
		avl_insert(mappings, mapping);
		
		quack_append(todo, mapping);
	}
	
	while (quack_is_nonempty(todo))
	{
		struct mapping* mapping = quack_pop(todo);
		
		struct gegex* const old = mapping->old;
		struct gegex* const new = mapping->new;
		
		new->accepts = old->accepts;
		
		for (unsigned i = 0, n = old->transitions.n; i < n; i++)
		{
			struct gegex_transition* const ele = old->transitions.data[i];
			
			struct gegex* cloneme = find(connections, ele->to);
			
			struct avl_node_t* node = avl_search(mappings, &cloneme);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				gegex_add_transition(new, ele->token, ele->whitespace, ele->structinfo, submapping->new);
			}
			else
			{
				struct gegex* subnew = new_gegex();
				
				struct mapping* submapping = new_mapping(cloneme, subnew);
				
				gegex_add_transition(new, ele->token, ele->whitespace, ele->structinfo, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
		
		for (unsigned i = 0, n = old->grammars.n; i < n; i++)
		{
			struct gegex_grammar_transition* const ele = old->grammars.data[i];
			
			struct gegex* cloneme = find(connections, ele->to);
			
			struct avl_node_t* node = avl_search(mappings, &cloneme);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				gegex_add_grammar_transition(new, ele->grammar, ele->structinfo, submapping->new);
			}
			else
			{
				struct gegex* subnew = new_gegex();
				
				struct mapping* submapping = new_mapping(cloneme, subnew);
				
				gegex_add_grammar_transition(new, ele->grammar, ele->structinfo, subnew);
				
				avl_insert(mappings, submapping);
				
				quack_append(todo, submapping);
			}
		}
	}
	
	free_quack(todo);
	
	avl_free_tree(mappings);
	
	EXIT;
	return new_start;
}

struct gegex* gegex_simplify_dfa(struct gegex* original)
{
	ENTER;
	
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_dependent_of_nodes, free_dependent_of_node);
	
	struct ptrset* universe = build_universe(original);
	
	struct heap* todo = new_heap(compare_tasks);
	
	#ifdef VERBOSE
	unsigned count = 0, n = ptrset_len(universe) * ptrset_len(universe) / 2;
	
	void handler1(int _)
	{
		char ptr[1000] = {};
		
		size_t len = snprintf(ptr, sizeof(ptr),
			"\e[K" "zebu: grammar simplify (build dependencies) %u of %u (%.2f%%)\r",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler1);
	#endif
	
	ptrset_foreach(universe, ({
		void runme(void* a_ptr) {
			ptrset_foreach(universe, ({
				void runme(void* b_ptr) {
					if (a_ptr < b_ptr)
					{
						bool unequal = false;
						
						struct gegex* const a = a_ptr;
						struct gegex* const b = b_ptr;
						
						if (a->accepts != b->accepts)
						{
							unequal = true;
						}
						
						if (!unequal)
						{
							unsigned i = 0, a_n = a->transitions.n, b_n = b->transitions.n;
							
							if (a_n != b_n)
							{
								unequal = true;
							}
							
							while (!unequal && i < a_n && i < b_n)
							{
								const struct gegex_transition* const at = a->transitions.data[i];
								const struct gegex_transition* const bt = b->transitions.data[i];
								
								if (false
									|| at->token != bt->token
									|| compare_unsignedsets(at->whitespace, bt->whitespace)
									|| compare_structinfos(at->structinfo, bt->structinfo))
								{
									unequal = true;
								}
								else
								{
									add_dep(dependent_of, a, b, at->to, bt->to);
									i++;
								}
							}
							
						}
						
						if (!unequal)
						{
							unsigned i = 0, a_n = a->grammars.n, b_n = b->grammars.n;
							
							if (a_n != b_n)
							{
								unequal = true;
							}
							
							while (!unequal && i < a_n && i < b_n)
							{
								const struct gegex_grammar_transition* const at = a->grammars.data[i];
								const struct gegex_grammar_transition* const bt = b->grammars.data[i];
								
								if (false
									|| !strings_are_equal(at->grammar, bt->grammar)
									|| compare_structinfos(at->structinfo, bt->structinfo))
								{
									unequal = true;
								}
								else
								{
									add_dep(dependent_of, a, b, at->to, bt->to);
									i++;
								}
							}
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
		char ptr[1000] = {};
		
		size_t len = snprintf(ptr, sizeof(ptr),
			"\e[K" "zebu: grammar simplify (allocating sets): %u of %u (%.2f%%)\r",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	count = 0, n = ptrset_len(universe);
	
	signal(SIGALRM, handler12);
	#endif
	
	struct avl_tree_t* connections = avl_alloc_tree(compare_same_as_nodes, free_same_as_node);
	
	ptrset_foreach(universe, ({
		void runme(void* ptr) {
			ENTER;
			
			struct gegex* a = ptr;
			
			struct ptrset* uni = ptrset_clone(universe);
			
			struct same_as_node* sa = new_same_as_node(a, uni);
			
			avl_insert(connections, sa);
			
			#ifdef VERBOSE
			count++;
			#endif
			
			EXIT;
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
			"\e[K" "zebu: grammar simplify (percolate): %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler2);
	#endif
	
	#ifdef DOTOUT
	dotout(universe, connections);
	#endif
	
	while (heap_is_nonempty(todo))
	{
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
		
		#ifdef VERBOSE
		completed++;
		#endif
		
		free(task);
	}
	
	#ifdef DOTOUT
	dotout(universe, connections);
	#endif
	
	struct gegex* new_start = clone(connections, original);
	
	#ifdef DOTOUT
	gegex_dotout(new_start, NULL, __PRETTY_FUNCTION__);
	#endif
	
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











