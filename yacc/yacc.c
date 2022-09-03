
#include <debug.h>

#include <avl/foreach.h>

#include <named/gegex/struct.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>

#include "named/trie/struct.h"
#include "named/trie/compare.h"
#include "named/trie/free.h"

#include "structinfo/compare.h"
#include "structinfo/free.h"

#include "build_structinfo.h"
#include "build_tries.h"
#include "calc_firsts.h"

#include "state/new.h"

#include "stateinfo/new.h"
#include "stateinfo/add.h"

#include "expand_stateinfo.h"

#include "yacc.h"

struct mapping
{
	struct stateinfo* stateinfo;
	struct yacc_state* state;
};

static struct mapping* new_mapping()
{
	TODO;
}

static int compare_mappings(const void* a, const void* b)
{
	TODO;
}

static void free_mapping(void* ptr)
{
	TODO;
}

struct yacc_state* yacc(
	struct avl_tree_t* named_gegexes,
	unsigned EOF_token_id)
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
	
	{
		struct stateinfo* stateinfo = new_stateinfo();
		
		struct named_trie* start_trie = avl_search(named_tries, &(const char**){(const char*[]) {"(start)"}})->item;
		
		struct unsignedset* lookahead = new_unsignedset();
		
		unsignedset_add(lookahead, EOF_token_id);
		
		stateinfo_add(stateinfo, start_trie->trie, lookahead);
		
		expand_stateinfo(stateinfo);
		
		quack_append(todo, new_mapping(stateinfo, start));
		
		avl_insert(mappings, stateinfo);
	}
	
	while (quack_len(todo))
	{
		TODO;
		
		#ifdef DOTOUT
		yacc_state_dotout(start);
		#endif
	}
	
	TODO;
	#if 0
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
	#endif
	
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
