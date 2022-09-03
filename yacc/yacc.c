
#include <debug.h>

#include <avl/foreach.h>

#include <cmdln/minimize_lexer.h>

#include <named/gegex/struct.h>

#include <lex/struct.h>
#include <lex/build_tokenizer/build_tokenizer.h>
#include <lex/minimize_lexer/minimize_lexer.h>

#include <set/unsigned/head.h>
#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/clone.h>
#include <set/unsigned/foreach.h>
#include <set/unsigned/free.h>

#include <set/unsignedset/foreach.h>
#include <set/unsignedset/free.h>

#include "named/trie/struct.h"
#include "named/trie/compare.h"
#include "named/trie/free.h"

#include "structinfo/compare.h"
#include "structinfo/free.h"

#include "build_structinfo.h"
#include "build_tries.h"
#include "calc_firsts.h"

#include "trie/struct.h"

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"
#include "state/add_grammar_transition.h"
#include "state/add_reduce_transition.h"
#include "state/dotout.h"

#include "stateinfo/new.h"
#include "stateinfo/add.h"
#include "stateinfo/inc.h"
#include "stateinfo/compare.h"
#include "stateinfo/foreach.h"
#include "stateinfo/free.h"

#include "expand_stateinfo.h"

#include "yacc.h"

struct mapping
{
	struct stateinfo* stateinfo;
	struct yacc_state* state;
	
	// unsigned hopcount;
	// struct mapping* prev;
};

static struct mapping* new_mapping(
	struct stateinfo* stateinfo,
	struct yacc_state* state)
{
	ENTER;
	
	struct mapping* this = smalloc(sizeof(*this));
	
	this->stateinfo = inc_stateinfo(stateinfo);
	this->state = state;
	
	EXIT;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping *A = a, *B = b;
	return compare_stateinfo(A->stateinfo, B->stateinfo);
}

static void free_mapping(void* ptr)
{
	struct mapping* this = ptr;
	
	free_stateinfo(this->stateinfo);
	
	free(this);
}

struct shift_node
{
	unsigned token; // must be the first
	
	struct stateinfo* stateinfo; // "owned" by struct
};

struct reduce_node
{
	unsigned token; // must be the first
	
	struct string* reduce_as;
	
	unsigned popcount;
	
	struct reductioninfo* reductioninfo;
	
	struct structinfo* structinfo;
};

struct subgrammar_node
{
	struct string* grammar; // must be the first
	
	struct stateinfo* stateinfo; // "owned" by struct
};

static struct shift_node* new_shift_node(
	unsigned token)
{
	ENTER;
	
	struct shift_node* this = smalloc(sizeof(*this));
	
	this->token = token;
	
	this->stateinfo = new_stateinfo();
	
	EXIT;
	return this;
}

static int compare_shift_nodes(const void* a, const void* b)
{
	const struct shift_node* A = a, *B = b;
	
	if (A->token > B->token)
		return +1;
	else if (A->token < B->token)
		return -1;
	else
		return 0;
}

static void free_shift_node(void* ptr)
{
	struct shift_node* const this = ptr;
	ENTER;
	
	free_stateinfo(this->stateinfo);
	
	free(this);
	
	EXIT;
}

static struct reduce_node* new_reduce_node(
	unsigned token,
	struct string* reduce_as,
	unsigned popcount,
	struct reductioninfo* reductioninfo,
	struct structinfo* structinfo)
{
	ENTER;
	
	struct reduce_node* this = smalloc(sizeof(*this));
	
	this->token = token;
	
	this->reduce_as = inc_string(reduce_as);
	
	this->popcount = popcount;
	
	this->reductioninfo = reductioninfo;
	
	this->structinfo = structinfo;
	
	EXIT;
	return this;
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

static struct subgrammar_node* new_subgrammar_node(struct string* grammar)
{
	ENTER;
	
	struct subgrammar_node* this = smalloc(sizeof(*this));
	
	this->grammar = inc_string(grammar);
	
	this->stateinfo = new_stateinfo();
	
	EXIT;
	return this;
}

static int compare_subgrammar_nodes(const void* a, const void* b)
{
	const struct subgrammar_node* A = a, *B = b;
	
	return compare_strings(A->grammar, B->grammar);
}

static void free_subgrammar_node(void* ptr)
{
	struct subgrammar_node* const this = ptr;
	ENTER;
	
	free_string(this->grammar);
	
	free_stateinfo(this->stateinfo);
	
	free(this);
	
	EXIT;
}

static void add_shift(
	struct avl_tree_t* shift_tokens,
	unsigned token,
	struct trie* to,
	struct unsignedset* lookaheads)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(shift_tokens, &token);
	
	if (node)
	{
		struct shift_node* old = node->item;
		
		stateinfo_add(old->stateinfo, to, unsignedset_clone(lookaheads));
	}
	else
	{
		struct shift_node* new = new_shift_node(token);
		
		stateinfo_add(new->stateinfo, to, unsignedset_clone(lookaheads));
		
		avl_insert(shift_tokens, new);
	}
	
	EXIT;
}

static void add_reduce(
	struct avl_tree_t* reduce_tokens,
	unsigned token,
	struct string* reduce_as,
	unsigned popcount,
	struct reductioninfo* reductioninfo,
	struct structinfo* structinfo)
{
	ENTER;
	
	dpv(token);
	
	struct avl_node_t* node = avl_search(reduce_tokens, &token);
	
	if (node)
	{
		dpvs(reduce_as);
		
		TODO;
		#if 0
		struct reduce_node* old = node->item;
		
		if (strcmp(old->reduce_as, reduce_as))
		{
			dpvs(old->reduce_as);
			dpv(reduce_as);
			
			TODO;
		}
		#endif
	}
	else
	{
		struct reduce_node* new = new_reduce_node(token, reduce_as, popcount, reductioninfo, structinfo);
		
		avl_insert(reduce_tokens, new);
	}
	
	EXIT;
}


static void add_subgrammar(
	struct avl_tree_t* subgrammars,
	struct string* grammar,
	struct trie* to,
	struct unsignedset* lookaheads)
{
	ENTER;
	
	dpvs(grammar);
	
	struct avl_node_t* node = avl_search(subgrammars, &grammar);
	
	if (node)
	{
		TODO;
		#if 0
		struct subgrammar_node* old = node->item;
		
		struct unsignedset* duped = unsignedset_clone(lookaheads);
		
		stateinfo_add(old->stateinfo, to, reduce_as, duped);
		#endif
	}
	else
	{
		struct subgrammar_node* new = new_subgrammar_node(grammar);
		
		stateinfo_add(new->stateinfo, to, unsignedset_clone(lookaheads));
		
		avl_insert(subgrammars, new);
	}
	
	EXIT;
}

struct yacc_state* yacc(
	struct lex* lex,
	struct avl_tree_t* named_gegexes)
{
	ENTER;
	
	struct avl_tree_t* structinfos = avl_alloc_tree(compare_structinfos, free_structinfo);
	
	struct avl_tree_t* named_tries = avl_alloc_tree(compare_named_tries, free_named_trie);
	
	avl_tree_foreach(named_gegexes, ({
		void runme(void* ptr)
		{
			struct named_gegex* named_gegex = ptr;
			
			struct structinfo* structinfo = build_structinfo(named_gegex->name, named_gegex->gegex);
			
			build_tries(named_tries, named_gegex->name, named_gegex->gegex, structinfo);
		}
		runme;
	}));
	
	// node->item are of `struct named_unsignedset*` type.
	struct avl_tree_t* named_firsts = calc_firsts(named_tries);
	
	struct quack* todo = new_quack();
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	
	struct yacc_state* start = new_yacc_state();
	
	// setup:
	{
		struct stateinfo* stateinfo = new_stateinfo();
		
		struct unsignedset* lookahead = new_unsignedset();
		
		struct named_trie* start_trie = avl_search(named_tries, &(const char**){(const char*[]) {"(start)"}})->item;
		
		unsignedset_add(lookahead, lex->EOF_token_id);
		
		stateinfo_add(stateinfo, start_trie->trie, lookahead);
		
		expand_stateinfo(stateinfo, named_tries, named_firsts);
		
		quack_append(todo, new_mapping(stateinfo, start));
		
		avl_insert(mappings, stateinfo);
		
		free_stateinfo(stateinfo);
	}
	
	while (quack_len(todo))
	{
		struct mapping* const mapping = quack_pop(todo);
		
		struct stateinfo* const stateinfo = mapping->stateinfo;
		
		struct yacc_state* const state = mapping->state;
		
		struct unsignedset* all_tokens = new_unsignedset();
		
		struct avl_tree_t* shift_tokens = avl_alloc_tree(compare_shift_nodes, free_shift_node);
		
		struct avl_tree_t* reduce_tokens = avl_alloc_tree(compare_reduce_nodes, free);
		
		struct avl_tree_t* subgrammars = avl_alloc_tree(compare_subgrammar_nodes, free_subgrammar_node);
		
		stateinfo_foreach(stateinfo, ({
			void runme(struct trie* trie, struct unsignedset* lookaheads)
			{
				ENTER;
				
				if (trie->reduce_as)
				{
					unsignedset_foreach(lookaheads, ({
						void runme(unsigned token)
						{
							add_reduce(reduce_tokens, token, trie->reduce_as, trie->popcount, trie->reductioninfo, trie->structinfo);
							
							unsignedset_add(all_tokens, token);
						}
						runme;
					}));
				}
				
				for (unsigned i = 0, n = trie->transitions.n; i < n; i++)
				{
					const struct trie_transition* const ele = trie->transitions.data[i];
					
					add_shift(shift_tokens, ele->token, ele->to, lookaheads);
					
					unsignedset_add(all_tokens, ele->token);
				}
				
				for (unsigned i = 0, n = trie->grammar_transitions.n; i < n; i++)
				{
					const struct trie_grammar_transition* ele = trie->grammar_transitions.data[i];
					
					dpvs(ele->grammar);
					
					add_subgrammar(subgrammars, ele->grammar, ele->to, lookaheads);
				}
				
				EXIT;
			}
			runme;
		}));
		
		struct lex_state* tokenizer_start;
		
		// don't free 'tokens', lex will do that
		struct unsignedsetset* tokens = lex_build_tokenzer(
			/* (in/out) struct lex* lex:            */ lex,
			/* (   out) struct lex_state* start:    */ &tokenizer_start,
			/* (in)     struct unsignedset* tokens:    */ all_tokens);
		
		state->tokenizer_start = tokenizer_start;
		
		unsignedsetset_foreach(tokens, ({
			void runme(struct unsignedset* ele)
			{
				ENTER;
				
				unsigned first = unsignedset_head(ele);
				
				dpv(first);
				
				// is this a shift or a reduce transition?
				if (avl_search(shift_tokens, &first))
				{
					struct stateinfo* subinfo = new_stateinfo();
					
					unsignedset_foreach(ele, ({
						void runme(unsigned token)
						{
							dpv(token);
							
							if (avl_search(reduce_tokens, &token))
							{
								// struct reduce_node* rn = rnode->item;
								TODO;
								exit(1);
							}
							
							struct shift_node* shift;
							{
								struct avl_node_t* snode = avl_search(shift_tokens, &token);
								
								assert(snode);
								
								shift = snode->item;
							}
							
							stateinfo_foreach(shift->stateinfo, ({
								void runme(struct trie* subtrie, struct unsignedset* sublookaheads) {
									stateinfo_add(subinfo, subtrie, unsignedset_clone(sublookaheads));
								}
								runme;
							}));
						}
						runme;
					}));
					
					expand_stateinfo(subinfo, named_tries, named_firsts);
					
					struct avl_node_t* node = avl_search(mappings, &subinfo);
					
					if (node)
					{
						struct mapping* submapping = node->item;
						
						yacc_state_add_transition(state, ele, submapping->state);
					}
					else
					{
						struct yacc_state* substate = new_yacc_state();
						
						struct mapping* submapping = new_mapping(subinfo, substate);
						
						yacc_state_add_transition(state, ele, substate);
						
						avl_insert(mappings, submapping);
						
						quack_append(todo, submapping);
					}
					
					free_stateinfo(subinfo);
				}
				else if (avl_search(reduce_tokens, &first))
				{
					struct string* reduce_as = NULL;
					unsigned popcount;
					struct reductioninfo* reductioninfo;
					struct structinfo* structinfo;
					
					unsignedset_foreach(ele, ({
						void runme(unsigned token) {
							dpv(token);
							
							if (avl_search(shift_tokens, &token))
							{
								TODO;
								// shift_reduce_error();
								exit(1);
							}
							
							struct avl_node_t* node = avl_search(reduce_tokens, &first);
							
							assert(node);
							
							struct reduce_node* reduce = node->item;
							
							dpvs(reduce->reduce_as);
							
							if (!reduce_as)
							{
								reduce_as = reduce->reduce_as;
								popcount = reduce->popcount;
								reductioninfo = reduce->reductioninfo;
								structinfo = reduce->structinfo;
							}
							else if (!strings_are_equal(reduce_as, reduce->reduce_as) || (popcount != reduce->popcount))
							{
								TODO;
							}
						}
						runme;
					}));
					
					yacc_state_add_reduce_transition(state, ele, reduce_as, popcount, reductioninfo, structinfo);
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
		
		avl_tree_foreach(subgrammars, ({
			void runme(void* ptr)
			{
				struct subgrammar_node* const ele = ptr;
				
				dpvs(ele->grammar);
				
				struct stateinfo* subinfo = new_stateinfo();
				
				stateinfo_foreach(ele->stateinfo, ({
					void runme(struct trie* subtrie, struct unsignedset* sublookaheads)
					{
						stateinfo_add(subinfo, subtrie, unsignedset_clone(sublookaheads));
					}
					runme;
				}));
				
				expand_stateinfo(subinfo, named_tries, named_firsts);
				
				struct avl_node_t* node = avl_search(mappings, &subinfo);
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					yacc_state_add_grammar_transition(state, ele->grammar, submapping->state);
				}
				else
				{
					struct yacc_state* substate = new_yacc_state();
					
					struct mapping* submapping = new_mapping(subinfo, substate);
					
					yacc_state_add_grammar_transition(state, ele->grammar, substate);
					
					avl_insert(mappings, submapping);
					
					quack_append(todo, submapping);
				}
				
				free_stateinfo(subinfo);
			}
			runme;
		}));
			
		#ifdef DOTOUT
		yacc_state_dotout(start);
		#endif
		
		free_unsignedset(all_tokens);
		
		free_unsignedsetset(tokens);
		
		avl_free_tree(shift_tokens);
		
		avl_free_tree(reduce_tokens);
		
		avl_free_tree(subgrammars);
	}
	
	if (minimize_lexer)
	{
		lex_minimize_lexer(lex, start);
	}
	
	free_quack(todo);
	
	avl_free_tree(mappings);
	
	avl_free_tree(named_firsts);
	
	avl_free_tree(structinfos);
	
	avl_free_tree(named_tries);
	
	EXIT;
	return start;
}

#if 0
#include <assert.h>

#include <debug.h>

#include <avl/foreach.h>

#include <heap/push.h>

#include <lex/struct.h>

/*#include <yacc/state/dotout.h>*/

#include <named/grammar/struct.h>

/*#include <set/of_tokens/new.h>*/
/*#include <set/of_tokens/add.h>*/

#include <heap/len.h>
#include <heap/pop.h>

#include <macros/len.h>

#include <arena/mmap/new.h>
#include <arena/free.h>

#include <lex/simplify_tokenizer/simplify_tokenizer.h>

#include "task/refcount/new.h"
#include "task/setup_trie/new.h"
#include "task/setup_start/new.h"
/*#include "task/expand_tree/new.h"*/
#include "task/process.h"
#include "task/dotout.h"
#include "task/free.h"

#include "state/dotout.h"

/*#include "lookahead_deps/new.h"*/

/*#include "tree/new.h"*/

#include "shared/struct.h"
#include "shared/new.h"
#include "shared/free.h"

/*#include "run_tasks.h"*/
/*#include "nfa_to_dfa.h"*/
#include "yacc.h"

#ifdef VERBOSE
#include <stddef.h>
#include <stdio.h>
#include <defines/argv0.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <cmdln/verbose.h>
#include <misc/default_sighandler.h>
#include <heap/struct.h>
#include "task/kind.h"
#include "task/struct.h"
#endif

#ifdef VERBOSE
static const char* colors[number_of_task_kinds] = {
	[tk_refcount]             = "\e[48;2;200;000;000m",
	[tk_setup_trie]           = "\e[48;2;150;050;000m",
	[tk_build_trie]           = "\e[48;2;100;100;000m",
	
	[tk_explore_firsts]       = "\e[48;2;050;150;000m",
	[tk_percolate_firsts]     = "\e[48;2;000;200;000m",
	
	[tk_setup_start]          = "\e[48;2;000;150;050m",
	[tk_expand_tree]          = "\e[48;2;000;100;100m",
	[tk_percolate_lookaheads] = "\e[48;2;000;050;150m",
	[tk_free_lookahead_deps]  = "\e[48;2;000;000;200m",
	[tk_add_transition]       = "\e[48;2;050;000;150m",
	[tk_build_ystate]         = "\e[48;2;100;000;100m",
};
#endif

struct yacc_state* yacc(
	#ifdef WITH_ARENAS
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	struct memory_arena* tokenizer_arena,
	struct memory_arena* parser_arena,
	#endif
	struct lex* lex,
	struct avl_tree_t* grammar,
	bool simplify_tokenizer)
{
	ENTER;
	
	// declare set of trie starts
	
	// for each named_grammar:
		// iterate through, doing refcounts, adding to trie starts
	
	// declare firsts, firsts-dependencies
	
	// for each trie-start:
		// iterate through, building trie
	
	// for each trie-start:
		// look at first transitions
	
	// percolate first-dependencies
	
	// call generator
	
	
	
	
	TODO;
	#if 0
	#ifdef WITH_ARENAS
	struct memory_arena* yacc_arena = new_mmap_arena();
	#endif
	
	struct yacc_shared* shared = new_yacc_shared(
		#ifdef WITH_ARENAS
		yacc_arena, tokenizer_arena, parser_arena,
		#endif
		lex, grammar, lex->EOF_token_id);
	
	struct heap* const todo = shared->todo;
	
	#ifdef VERBOSE
	void handler1(int _)
	{
		char ptr[1000] = {};
		
		unsigned counts[number_of_task_kinds] = {};
		
		for (unsigned i = 0, n = todo->n; i < n; i++)
			counts[((struct task*) todo->data[i])->kind]++;
		
		size_t len = snprintf(ptr, sizeof(ptr), "\e[K" "%s: %s:", argv0, "yacc");
		
		for (unsigned i = 0, n = number_of_task_kinds; i < n; i++)
			if (counts[i])
				len += sprintf(ptr + len, " %s%u%s", colors[i], counts[i], "\e[0m");
		
		ptr[len++] = '\r';
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	if (verbose)
		signal(SIGALRM, handler1);
	#endif
	
	avl_tree_foreach(shared->grammar, ({
		void runme(const void* item) {
			const struct named_grammar* ng = item;
			
			dpvs(ng->name);
			
			#ifdef WITH_ARENAS
			heap_push(todo, new_refcount_task(yacc_arena, ng->grammar, ng->grammar));
			#else
			heap_push(todo, new_refcount_task(ng->grammar, ng->grammar));
			#endif
			
			#ifdef WITH_ARENAS
			heap_push(todo, new_setup_trie_task(yacc_arena, ng->grammar, ng->name));
			#else
			heap_push(todo, new_setup_trie_task(ng->grammar, ng->name));
			#endif
			
			// build_trie_task()
			
			// new_explore_firsts_task()
			
			// new_percolate_firsts_task()
		}
		runme;
	}));
	
	#ifdef WITH_ARENAS
	heap_push(todo, new_setup_start_task(yacc_arena));
	#else
	heap_push(todo, new_setup_start_task());
	#endif
	
	while (len(todo))
	{
		struct task* task = heap_pop(todo);
		
		task_process(task, shared);
		
		#ifdef DOTOUT
		task_dotout(task, shared);
		#endif
		
		#ifdef WITH_ARENAS
		free_task(yacc_arena, task);
		#else
		free_task(task);
		#endif
	}
	
	#ifdef VERBOSE
	if (verbose)
		signal(SIGALRM, default_sighandler);
	#endif
	
	struct yacc_state* start = shared->yacc_start;
	
	assert(start);
	
	#ifdef DOTOUT
	yacc_state_dotout(start);
	#endif
	
	if (simplify_tokenizer)
	{
		#ifdef WITH_ARENAS
		lex_simplify_tokenizer(tokenizer_arena, lex, start);
		#else
		lex_simplify_tokenizer(lex, start);
		#endif
		
		#ifdef DOTOUT
		yacc_state_dotout(start);
		#endif
	}
	
	#ifdef WITH_ARENAS
	
	free_memory_arena(yacc_arena);
	
	#else
	
	free_yacc_shared(shared);
	
	#endif
	
	EXIT;
	return start;
	#endif
}






















#endif
