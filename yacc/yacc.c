
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

struct yacc_state* yacc(
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	struct memory_arena* tokenizer_arena,
	struct memory_arena* parser_arena,
	struct lex* lex,
	struct avl_tree_t* grammar,
	bool simplify_tokenizer)
{
	ENTER;
	
	struct memory_arena* yacc_arena = new_mmap_arena();
	
	struct yacc_shared* shared = new_yacc_shared(
		yacc_arena,
		tokenizer_arena, parser_arena,
		lex, grammar, lex->EOF_token_id);
	
	struct heap* const todo = shared->todo;
	
	avl_tree_foreach(shared->grammar, ({
		void runme(const void* item) {
			const struct named_grammar* ng = item;
			
			dpvs(ng->name);
			
			heap_push(todo, new_refcount_task(yacc_arena, ng->grammar, ng->grammar));
			
			heap_push(todo, new_setup_trie_task(yacc_arena, ng->grammar, ng->name));
			
			// build_trie_task()
			
			// new_explore_firsts_task()
			
			// new_percolate_firsts_task()
		}
		runme;
	}));
	
	heap_push(todo, new_setup_start_task(yacc_arena));
	
	while (len(todo))
	{
		struct task* task = heap_pop(todo);
		
		task_process(task, shared);
		
		#ifdef DEBUGGING
		task_dotout(task, shared);
		#endif
		
		free_task(task, yacc_arena);
	}
	
	struct yacc_state* start = shared->yacc_start;
	
	assert(start);
	
	#ifdef DEBUGGING
	yacc_state_dotout(start);
	#endif
	
	if (simplify_tokenizer)
	{
		lex_simplify_tokenizer(tokenizer_arena, lex, start);
		
		#ifdef DEBUGGING
		yacc_state_dotout(start);
		#endif
	}
	
	free_memory_arena(yacc_arena);
	
	EXIT;
	return start;
}






















