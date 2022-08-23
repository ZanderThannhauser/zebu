
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/free_tree.h>
#include <avl/insert.h>
#include <avl/alloc_tree.h>

#include <arena/strdup.h>
#include <arena/malloc.h>
#include <arena/dealloc.h>

#include <yacc/gegex/state/struct.h>

/*#include <named/grammar/struct.h>*/

/*#include <set/of_tokens/free.h>*/

#include <lex/build_tokenizer/build_tokenizer.h>

#include <set/of_gegexes/struct.h>
#include <set/of_gegexes/clear.h>
#include <set/of_gegexes/new.h>
#include <set/of_gegexes/add.h>
#include <set/of_gegexes/update.h>
#include <set/of_gegexes/free.h>

#include <set/of_tokens/struct.h>
#include <set/of_tokens/new.h>
#include <set/of_tokens/add.h>
#include <set/of_tokens/foreach.h>
#include <set/of_tokensets/foreach.h>
#include <set/of_tokensets/prettyprint.h>
/*#include <set/of_tokens/update.h>*/
#include <set/of_tokens/clone.h>
#include <set/of_tokens/free.h>

#ifdef DEBUGGING
#include <set/of_tokens/print.h>
#endif

#include <heap/push.h>

#include <yacc/state/struct.h>
#include <yacc/state/add_reduce_transition.h>
#include <yacc/state/add_grammar_transition.h>
#include <yacc/state/add_transition.h>

#include "../../stateinfo/new.h"
#include "../../stateinfo/free.h"
#include "../../stateinfo/add.h"
/*#include "../../tree/contains.h"*/
/*#include "../../tree/add.h"*/

#include "../expand_tree/new.h"
#include "../add_transition/new.h"
#include "../../lookahead_deps/new.h"
#include "../free_lookahead_deps/new.h"
/*#include "../add_transition/new.h"*/

/*#include "../../lookahead_deps/new.h"*/
/*#include "../../lookahead_deps/add.h"*/

#include "../../shared/struct.h"
/*#include "../../add_dep.h"*/
/*#include "../../lookup_tokenset.h"*/

#include <yacc/stateinfo/foreach.h>

#include "struct.h"
/*#include "new.h"*/
#include "process.h"

struct shift_node
{
	unsigned token; // must be the first
	
	struct yacc_stateinfo* stateinfo; // "owned" by struct
	
	struct memory_arena* arena;
};

static struct shift_node* new_shift_node(
	struct memory_arena* arena,
	unsigned token)
{
	ENTER;
	
	struct shift_node* this = arena_malloc(arena, sizeof(*this));
	
	this->token = token;
	this->stateinfo = new_yacc_stateinfo(arena);
	
	this->arena = arena;
	
	EXIT;
	return this;
}

static void add_shift(
	struct memory_arena* arena,
	struct avl_tree_t* tree,
	unsigned token,
	struct gegex* to,
	const char* reduce_as,
	struct tokenset* lookaheads)
{
	ENTER;
	
	dpv(token);
	dpvs(reduce_as);
	
	struct avl_node_t* node = avl_search(tree, &token);
	
	if (node)
	{
		struct shift_node* old = node->item;
		
		struct tokenset* duped = tokenset_clone(lookaheads, arena);
		
		yacc_stateinfo_add(old->stateinfo, to, reduce_as, duped);
	}
	else
	{
		struct shift_node* new = new_shift_node(arena, token);
		
		struct tokenset* duped = tokenset_clone(lookaheads, arena);
		
		yacc_stateinfo_add(new->stateinfo, to, reduce_as, duped);
		
		avl_insert(tree, new);
	}
	
	EXIT;
}

static int compare_shift_nodes(const void* a, const void* b)
{
	int cmp = 0;
	
	const struct shift_node* A = a, *B = b;
	
	if (A->token > B->token)
		cmp = +1;
	else if (A->token < B->token)
		cmp = -1;
	
	return cmp;
}

static void free_shift_node(void* ptr)
{
	struct shift_node* const this = ptr;
	ENTER;
	
	free_yacc_stateinfo(this->stateinfo);
	
	arena_dealloc(this->arena, this);
	
	EXIT;
}

struct reduce_node
{
	unsigned token; // must be the first
	const char* reduce_as;
	unsigned popcount;
	
	struct memory_arena* arena;
};

static struct reduce_node* new_reduce_node(
	struct memory_arena* arena,
	unsigned token,
	const char* reduce_as,
	unsigned popcount)
{
	ENTER;
	
	struct reduce_node* this = arena_malloc(arena, sizeof(*this));
	
	this->token = token;
	this->reduce_as = reduce_as;
	this->popcount = popcount;
	
	this->arena = arena;
	
	dpv(this->token);
	dpvs(this->reduce_as);
	dpv(this->popcount);
	
	EXIT;
	return this;
}

static void add_reduce(
	struct memory_arena* arena,
	struct avl_tree_t* tree,
	unsigned token,
	const char* reduce_as,
	unsigned popcount)
{
	ENTER;
	
	dpv(token);
	
	struct avl_node_t* node = avl_search(tree, &token);
	
	if (node)
	{
		dpvs(reduce_as);
		
		struct reduce_node* old = node->item;
		
		if (strcmp(old->reduce_as, reduce_as))
		{
			dpvs(old->reduce_as);
			dpv(reduce_as);
			
			TODO;
		}
	}
	else
	{
		struct reduce_node* new = new_reduce_node(arena, token, reduce_as, popcount);
		
		avl_insert(tree, new);
	}
	
	EXIT;
}

static int compare_reduce_nodes(const void* a, const void* b)
{
	const struct reduce_node* A = a, *B = b;
	
	if (A->token > B->token)
		return +1;
	else if (A->token < B->token)
		return -1;
	else
		return +0;
}

static void free_reduce_node(void* ptr)
{
	struct reduce_node* this = ptr;
	ENTER;
	
	arena_dealloc(this->arena, this);
	
	EXIT;
}

struct subgrammar_node
{
	const char* grammar;
	
	struct yacc_stateinfo* stateinfo; // free me
	
	struct memory_arena* arena;
};

static struct subgrammar_node* new_subgrammar_node(
	struct memory_arena* arena,
	const char* grammar)
{
	ENTER;
	
	struct subgrammar_node* this = arena_malloc(arena, sizeof(*this));
	
	this->grammar = grammar;
	this->stateinfo = new_yacc_stateinfo(arena);
	
	this->arena = arena;
	
	dpvs(this->grammar);
	
	EXIT;
	return this;
}

static void add_subgrammar(
	struct memory_arena* arena,
	struct avl_tree_t* tree,
	const char* grammar,
	struct gegex* to,
	const char* reduce_as,
	struct tokenset* lookaheads)
{
	ENTER;
	
	dpvs(grammar);
	dpvs(reduce_as);
	
	struct avl_node_t* node = avl_search(tree, &grammar);
	
	if (node)
	{
		struct subgrammar_node* old = node->item;
		
		struct tokenset* duped = tokenset_clone(lookaheads, arena);
		
		yacc_stateinfo_add(old->stateinfo, to, reduce_as, duped);
	}
	else
	{
		struct subgrammar_node* new = new_subgrammar_node(arena, grammar);
		
		struct tokenset* duped = tokenset_clone(lookaheads, arena);
		
		yacc_stateinfo_add(new->stateinfo, to, reduce_as, duped);
		
		avl_insert(tree, new);
	}
	
	EXIT;
}

static int compare_subgrammar_nodes(const void* a, const void* b)
{
	const struct subgrammar_node* A = a, *B = b;
	
	return strcmp(A->grammar, B->grammar);
}

static void free_subgrammar_node(void* ptr)
{
	struct subgrammar_node* const this = ptr;
	ENTER;
	
	free_yacc_stateinfo(this->stateinfo);
	
	arena_dealloc(this->arena, this);
	
	EXIT;
}

void build_ystate_task_process(struct task* super, struct yacc_shared* shared)
{
	struct build_ystate_task* const this = (void*) super;
	ENTER;
	
	struct memory_arena* const arena = shared->arena;
	
	struct yacc_state* const state = this->state;
	
	// create set for all tokens accepted by all gegex states:
	struct tokenset* all_tokens = new_tokenset(arena);

	// map from token to set of gegex states:
	struct avl_tree_t* shift_tokens = avl_alloc_tree(arena, compare_shift_nodes, free_shift_node);

	// map from token to name to reduce by:
	struct avl_tree_t* reduce_tokens = avl_alloc_tree(arena, compare_reduce_nodes, free_reduce_node);

	// map from subgrammar name to set of gegex states:
	struct avl_tree_t* subgrammars = avl_alloc_tree(arena, compare_subgrammar_nodes, free_subgrammar_node);
	
	yacc_stateinfo_foreach(this->stateinfo, ({
		void runme(struct gegex* state, const char* reduce_as, struct tokenset* lookaheads)
		{
			ENTER;
			
			unsigned i, n;
			
			if (state->is_reduction_point)
			{
				tokenset_foreach(lookaheads, ({
					void runme(unsigned token) {
						
						add_reduce(arena, reduce_tokens, token, reduce_as, state->popcount);
						
						tokenset_add(all_tokens, token);
					}
					runme;
				}));
			}
			
			for (i = 0, n = state->transitions.n; i < n; i++)
			{
				const struct transition* const ele = state->transitions.data[i];
				
				unsigned token = ele->token;
				
				struct tokenset* duped = tokenset_clone(lookaheads, arena);
				
				add_shift(arena, shift_tokens, token, ele->to, reduce_as, duped);
				
				tokenset_add(all_tokens, token);
			}
			
			for (i = 0, n = state->grammar_transitions.n; i < n; i++)
			{
				const struct gtransition* t = state->grammar_transitions.data[i];
				
				dpvs(t->grammar);
				
				struct tokenset* duped = tokenset_clone(lookaheads, arena);
				
				add_subgrammar(arena, subgrammars, t->grammar, t->to, reduce_as, duped);
			}
			
			EXIT;
		}
		runme;
	}));
	
	struct lex_state* tokenizer_start;
	
	// don't free 'tokens', lex will do that
	struct tokensetset* tokens = lex_build_tokenzer(
		/* (in/out) struct memory_arena* arena: */ shared->tokenizer_arena,
		/* (   out) struct lex_state* start:    */ &tokenizer_start,
		/* (in/out) struct lex* lex:            */ shared->lex,
		/* (in)     struct tokenset* tokens:    */ all_tokens);
	
	state->tokenizer_start = tokenizer_start;
	
	tokensetset_foreach(tokens, ({
		void runme(struct tokenset* ele)
		{
			ENTER;
			
			unsigned first = ele->data[0];
			
			dpv(first);
			
			// is this a shift or a reduce transition?
			if (avl_search(shift_tokens, &first))
			{
				struct yacc_stateinfo* subinfo = new_yacc_stateinfo(arena);
				
				struct lookahead_deps* subldeps = new_lookahead_deps(arena);
				
				tokenset_foreach(ele, ({
					void runme(unsigned token) {
						dpv(token);
						
						struct avl_node_t* rnode;
						
						if ((rnode = avl_search(reduce_tokens, &token)))
						{
							// struct reduce_node* rn = rnode->item;
							TODO;
							exit(1);
						}
						
						struct avl_node_t* snode = avl_search(shift_tokens, &token);
						assert(snode);
						
						struct shift_node* shift = snode->item;
						
						yacc_stateinfo_foreach(shift->stateinfo, ({
							void runme(struct gegex* substate, const char* subreduce_as, struct tokenset* sublookaheads) {
								
								dpv(token);
								
								struct tokenset* duped = tokenset_clone(sublookaheads, arena);
								
								heap_push(shared->todo, new_expand_tree_task(arena,
									subinfo, subldeps, substate, subreduce_as, duped));
							}
							runme;
						}));
					}
					runme;
				}));
				
				heap_push(shared->todo, new_free_lookahead_deps_task(arena, subldeps));
				
				struct ytransition* yt = yacc_state_add_transition(state, ele, NULL);
				
				heap_push(shared->todo, new_add_transition_task(arena, &yt->to, subinfo));
			}
			else if (avl_search(reduce_tokens, &first))
			{
				const char* reduce_as = NULL;
				unsigned popcount;
				
				tokenset_foreach(ele, ({
					void runme(unsigned token) {
						dpv(token);
						
						if (avl_search(shift_tokens, &token))
						{
							TODO;
							// shift_reduce_error();
						}
						
						struct avl_node_t* node = avl_search(reduce_tokens, &first);
						assert(node);
						
						struct reduce_node* reduce = node->item;
						
						dpvs(reduce->reduce_as);
						
						if (!reduce_as)
						{
							reduce_as = reduce->reduce_as;
							popcount = reduce->popcount;
						}
						else if (strcmp(reduce_as, reduce->reduce_as) || popcount != reduce->popcount)
						{
							TODO;
						}
					}
					runme;
				}));
				
				dpvs(reduce_as);
				assert(reduce_as);
				
				char* dup = arena_strdup(shared->parser_arena, reduce_as);
				
				dpvs(dup);
				dpv(popcount);
				
				yacc_state_add_reduce_transition(state, ele, dup, popcount);
			}
			else
			{
				// huh?
				TODO;
			}
			
			EXIT;
		}
		runme;
	}));
	
	// grammar transitions
	for (struct avl_node_t* node = subgrammars->head; node; node = node->next)
	{
		struct subgrammar_node* ele = node->item;
		
		dpvs(ele->grammar);
		
		struct yacc_stateinfo* subinfo = new_yacc_stateinfo(arena);
		
		struct lookahead_deps* subldeps = new_lookahead_deps(arena);
		
		yacc_stateinfo_foreach(ele->stateinfo, ({
			void runme(struct gegex* substate, const char* reduce_as, struct tokenset* sublookaheads) {
				
				struct tokenset* duped = tokenset_clone(sublookaheads, arena);
				
				heap_push(shared->todo, new_expand_tree_task(arena,
					subinfo, subldeps, substate, reduce_as, duped));
			}
			runme;
		}));
		
		heap_push(shared->todo, new_free_lookahead_deps_task(arena, subldeps));
		
		char* grammar = arena_strdup(shared->parser_arena, ele->grammar);
		
		dpvs(grammar);
		
		struct gytransition* yt = yacc_state_add_grammar_transition(state, grammar, NULL);
		
		heap_push(shared->todo, new_add_transition_task(arena, &yt->to, subinfo));
	}
	
	free_tokenset(all_tokens);
	
	avl_free_tree(shift_tokens);
	
	avl_free_tree(reduce_tokens);
	
	avl_free_tree(subgrammars);
	
	EXIT;
}
















