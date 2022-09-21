
#include <debug.h>

#if 0

struct lex_pair
{
	struct lex_state *a, *b;
};


struct lex_pair* new_lex_pair(
	struct lex_state* a, struct lex_state* b)
{
	ENTER;
	
	struct lex_pair* this = smalloc(sizeof(*this));
	
	assert(a < b);
	
	this->a = a;
	this->b = b;
	
	EXIT;
	return this;
}

int compare_lex_pairs(const void* a, const void* b)
{
	int cmp = 0;
	const struct lex_pair *A = a, *B = b;
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


struct lex_dependent_of_node
{
	struct lex_pair pair;
	
	struct avl_tree_t* dependent_of;
};


struct lex_dependent_of_node* new_lex_dependent_of_node(
	struct lex_state* a, struct lex_state* b)
{
	ENTER;
	
	struct lex_dependent_of_node* this = smalloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->dependent_of = avl_alloc_tree(compare_lex_pairs, free_lex_pair);
	
	EXIT;
	return this;
}

int compare_lex_dependent_of_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct lex_dependent_of_node *A = a, *B = b;
	ENTER;
	
	cmp = compare_lex_pairs(&A->pair, &B->pair);
	
	EXIT;
	return cmp;
}


void free_lex_dependent_of_node(void* ptr)
{
	struct lex_dependent_of_node* this = ptr;
	ENTER;
	
	avl_free_tree(this->dependent_of);
	
	free(this);
	
	EXIT;
}

struct lex_same_as_node
{
	struct lex_state* state;
	
	struct lexstateset* set;
};


struct lex_same_as_node* new_lex_same_as_node(
	struct lex_state* state, struct lexstateset* set)
{
	ENTER;
	
	struct lex_same_as_node* this = smalloc(sizeof(*this));
	
	this->state = state;
	
	this->set = set;
	
	EXIT;
	return this;
}

int compare_lex_same_as_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct lex_same_as_node* A = a, *B = b;
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


void free_lex_same_as_node(void* ptr)
{
	struct lex_same_as_node* this = ptr;
	ENTER;
	
	free_lexstateset(this->set);
	
	free(this);
	
	EXIT;
}

struct lex_simplify_task
{
	struct lex_pair pair;
	
	unsigned hopcount;
};


struct lex_simplify_task* new_lex_simplify_task(
	struct lex_state* a, struct lex_state* b,
	unsigned hopcount)
{
	ENTER;
	
	struct lex_simplify_task* this = smalloc(sizeof(*this));
	
	this->pair.a = a;
	this->pair.b = b;
	
	this->hopcount = hopcount;
	
	EXIT;
	return this;
}

int compare_lex_simplify_tasks(const void* a, const void* b)
{
	const struct lex_simplify_task* A = a, *B = b;
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


void lex_simplify_dfa_add_dep(
	struct avl_tree_t* dependent_of,
	struct lex_state* a_on, struct lex_state* b_on,
	struct lex_state* a_of, struct lex_state* b_of)
{
	ENTER;
	
	if (a_of > b_of)
	{
		struct lex_state* swap = b_of;
		b_of = a_of, a_of = swap;
	}
	
	struct avl_node_t* node = avl_search(dependent_of, &(struct lex_pair){a_of, b_of});
	
	if (node)
	{
		struct lex_dependent_of_node* old = node->item;
		
		if (!avl_search(old->dependent_of, &(struct lex_pair){a_on, b_on}))
		{
			struct lex_pair* dep = new_lex_pair(a_on, b_on);
			
			avl_insert(old->dependent_of, dep);
		}
	}
	else
	{
		struct lex_dependent_of_node* new = new_lex_dependent_of_node(a_of, b_of);
		
		struct lex_pair* dep = new_lex_pair(a_on, b_on);
		
		avl_insert(new->dependent_of, dep);
		
		avl_insert(dependent_of, new);
	}
	
	EXIT;
}





struct lexstateset* minimize_lexer_build_universe(struct lex* this)
{
	ENTER;
	
	TODO;
	#if 0
	struct lexstateset* universe = new_lexstateset();
	
	struct quack* todo = new_quack();
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler2(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: minimize tokenizer (build universe): %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler2);
	#endif
	
	avl_tree_foreach(this->tokenizer_cache, ({
		void runme(void* ptr)
		{
			struct build_tokenizer_node* ele = ptr;
			
			lexstateset_add(universe, ele->start);
			
			quack_append(todo, ele->start);
		}
		runme;
	}));
	
	while (quack_len(todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct lex_state* state = quack_pop(todo);
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct lex_state* const to = state->transitions[i];
			
			if (to && lexstateset_add(universe, to))
				quack_append(todo, to);
		}
		
		if (state->EOF_transition_to)
		{
			struct lex_state* const to = state->EOF_transition_to;
			
			if (lexstateset_add(universe, to))
				quack_append(todo, to);
		}
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	free_quack(todo);
	
	EXIT;
	return universe;
	#endif
}



bool lex_simplify_dfa_mark_as_unequal(
	struct avl_tree_t* connections,
	struct lex_pair* pair)
{
	ENTER;
	
	
	struct avl_node_t* a_node = avl_search(connections, &pair->a);
	struct avl_node_t* b_node = avl_search(connections, &pair->b);
	
	assert(a_node && b_node);
	
	struct lex_same_as_node* a_sa = a_node->item, *b_sa = b_node->item;
	
	bool removed = false;
	
	if (lexstateset_contains(a_sa->set, pair->b))
	{
		assert(lexstateset_contains(b_sa->set, pair->a));
		
		lexstateset_discard(a_sa->set, pair->b);
		lexstateset_discard(b_sa->set, pair->a);
		
		removed = true;
	}
	
	dpvb(removed);
	
	EXIT;
	return removed;
}


struct mapping
{
	struct lex_state* old;
	struct lex_state* new;
};

static struct mapping* new_mapping(struct lex_state* old, struct lex_state* new)
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

static struct lex_state* find(struct avl_tree_t* connections, struct lex_state* a)
{
	struct avl_node_t* node = avl_search(connections, &a);
	
	assert(node);
	
	struct lex_same_as_node* sa = node->item;
	
	assert(sa->set->len);
	
	return sa->set->tree->head->item;
}

void lex_minimize_traverse_and_clone(
	struct avl_tree_t* connections,
	struct yacc_state* start)
{
	ENTER;
	
	struct quack* yacc_todo = new_quack();
	
	struct quack* lex_todo = new_quack();
	
	struct yaccstateset* queued = new_yaccstateset();
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free);
	
	yaccstateset_add(queued, start);
	
	quack_append(yacc_todo, start);
	
	while (quack_len(yacc_todo))
	{
		struct yacc_state* state = quack_pop(yacc_todo);
		
		struct lex_state* cloneme = find(connections, state->tokenizer_start);
		
		struct avl_node_t* node = avl_search(mappings, &cloneme);
		
		if (node)
		{
			state->tokenizer_start = ((struct mapping*) node->item)->new;
		}
		else
		{
			struct lex_state* substate = new_lex_state();
			
			struct mapping* submapping = new_mapping(cloneme, substate);
			
			state->tokenizer_start = substate;
			
			avl_insert(mappings, submapping);
			
			quack_append(lex_todo, submapping);
		}
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct yacc_state* const to = state->transitions.data[i]->to;
			
			if (yaccstateset_add(queued, to))
				quack_append(yacc_todo, to);
		}
		
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct yacc_state* const to = state->grammar_transitions.data[i]->to;
			
			if (yaccstateset_add(queued, to))
				quack_append(yacc_todo, to);
		}
	}
	
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(lex_todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: minimize lexer (clone): %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler);
	#endif
	
	while (quack_len(lex_todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct mapping* mapping = quack_pop(lex_todo);
		
		struct lex_state* const old = mapping->old;
		struct lex_state* const new = mapping->new;
		
		new->accepts = inc_unsignedset(old->accepts);
		
		new->kind = old->kind;
		
		// for each transition:
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct lex_state* to = old->transitions[i];
			
			if (to)
			{
				struct lex_state* subold = find(connections, to);
				
				struct avl_node_t* node = avl_search(mappings, &subold);
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					new->transitions[i] = submapping->new;
				}
				else
				{
					struct lex_state* substate = new_lex_state();
					
					struct mapping* submapping = new_mapping(subold, substate);
					
					new->transitions[i] = substate;
					
					avl_insert(mappings, submapping);
					
					quack_append(lex_todo, submapping);
				}
			}
		}
		
		// EOF transitions?
		if (old->EOF_transition_to)
		{
			struct lex_state* subold = find(connections, old->EOF_transition_to);
			
			struct avl_node_t* node = avl_search(mappings, &subold);
			
			if (node)
			{
				struct mapping* submapping = node->item;
				
				new->EOF_transition_to = submapping->new;
			}
			else
			{
				struct lex_state* substate = new_lex_state();
				
				struct mapping* submapping = new_mapping(subold, substate);
				
				new->EOF_transition_to = substate;
				
				avl_insert(mappings, submapping);
				
				quack_append(lex_todo, submapping);
			}
		}
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	free_yaccstateset(queued);
	
	avl_free_tree(mappings);
	
	free_quack(yacc_todo);
	
	free_quack(lex_todo);
	
	EXIT;
}


#endif

void lex_minimize_lexer(
	struct lex* this,
	struct yacc_state* ystart)
{
	ENTER;
	
	TODO;
	#if 0
	struct lexstateset* universe = minimize_lexer_build_universe(this);
	
	struct avl_tree_t* dependent_of = avl_alloc_tree(compare_lex_dependent_of_nodes, free_lex_dependent_of_node);
	
	struct heap* todo = new_heap(compare_lex_simplify_tasks);
	
	#ifdef VERBOSE
	uintmax_t count = 0, n = lexstateset_len(universe);
	
	dpv(n);
	
	n = (n * (n - 1)) / 2;
	
	dpv(n);
	
	void handler1(int _)
	{
		char ptr[1000] = {};
		
		size_t len = snprintf(ptr, 1000,
			"\e[K" "zebu: minimize lexer (build dependencies): %lu of %lu (%.2f%%)\r",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler1);
	#endif
	
	lexstateset_foreach(universe, ({
		void runme(struct lex_state* a) {
			lexstateset_foreach(universe, ({
				void runme(struct lex_state* b) {
					if (a < b)
					{
						ENTER;
						
						bool unequal = false;
						
						if (!a->accepts != !b->accepts)
							unequal = true;
						else if (a->accepts && b->accepts && (a->kind != b->kind || compare_unsignedsets(a->accepts, b->accepts)))
							unequal = true;
						else if (!a->EOF_transition_to != !b->EOF_transition_to)
							unequal = true;
						else if (a->EOF_transition_to && b->EOF_transition_to)
							lex_simplify_dfa_add_dep(dependent_of, a, b, a->EOF_transition_to, b->EOF_transition_to);
							
						for (unsigned i = 0, n = 256; !unequal && i < n; i++)
						{
							struct lex_state* at = a->transitions[i];
							struct lex_state* bt = b->transitions[i];
							
							if (!at != !bt)
								unequal = true;
							else if (at && bt)
								lex_simplify_dfa_add_dep(dependent_of, a, b, at, bt);
						}
						
						if (unequal)
							heap_push(todo, new_lex_simplify_task(a, b, 0));
						
						#ifdef VERBOSE
						count++;
						#endif
						
						EXIT;
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
		
		size_t len = snprintf(ptr, 1000,
			"\e[K" "zebu: minimize tokenizer (allocating dependency-trees): %lu of %lu (%.2f%%)\r",
			count, n, (((double) count * 100) / n));
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	count = 0, n = lexstateset_len(universe);
	
	signal(SIGALRM, handler12);
	#endif
	
	struct avl_tree_t* connections = avl_alloc_tree(compare_lex_same_as_nodes, free_lex_same_as_node);
	
	lexstateset_foreach(universe, ({
		void runme(struct lex_state* a) {
			ENTER;
			
			struct lexstateset* uni = lexstateset_clone(universe);
			
			struct lex_same_as_node* sa = new_lex_same_as_node(a, uni);
			
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
			"\e[K" "zebu: minimize tokenizer (percolate): %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler2);
	#endif
	
	while (heap_len(todo))
	{
		struct lex_simplify_task* task = heap_pop(todo);
		
		if (lex_simplify_dfa_mark_as_unequal(connections, &task->pair))
		{
			struct avl_node_t* node = avl_search(dependent_of, &task->pair);
			
			if (node)
			{
				struct lex_dependent_of_node* dep = node->item;
				
				unsigned hopcount = task->hopcount + 1;
				
				avl_tree_foreach(dep->dependent_of, ({
					void runme(void* ptr) {
						const struct lex_pair* pair = ptr;
						
						heap_push(todo, new_lex_simplify_task(pair->a, pair->b, hopcount));
					}
					runme;
				}));
			}
		}
		
		#ifdef VERBOSE
		completed++;
		#endif
		
		free_lex_simplify_task(task);
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	lex_minimize_traverse_and_clone(connections, ystart);
	
	struct lexstateset* freed = new_lexstateset();
	
	lexstateset_foreach(universe, ({
		void runme(struct lex_state* state) {
			free_lex_state(freed, state);
		}
		runme;
	}));
	
	free_lexstateset(freed);
	
	avl_free_tree(dependent_of);
	
	free_lexstateset(universe);
	
	avl_free_tree(connections);
	
	free_heap(todo);
	#endif
	
	EXIT;
}


