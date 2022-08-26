
#include <assert.h>

#include <debug.h>

#include <avl/foreach.h>

#include <heap/push.h>

#include <cmdln/minimize_lexer.h>

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

#include <lex/minimize_lexer/minimize_lexer.h>

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
	struct avl_tree_t* grammar)
{
	ENTER;
	
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
	
	if (minimize_lexer)
	{
		#ifdef WITH_ARENAS
		lex_minimize_lexer(tokenizer_arena, lex, start);
		#else
		lex_minimize_lexer(lex, start);
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
}






















