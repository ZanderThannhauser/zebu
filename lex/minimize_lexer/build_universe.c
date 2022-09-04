
#include <assert.h>

#include <debug.h>

#include <lex/state/struct.h>

#include <set/lexstate/new.h>
#include <set/lexstate/add.h>

#include <avl/foreach.h>

#ifdef VERBOSE
#include <quack/len.h>
#include <misc/default_sighandler.h>
#endif

#include "../struct.h"

#include "../build_tokenizer/node/struct.h"

#include "build_universe.h"

struct lexstateset* minimize_lexer_build_universe(struct lex* this)
{
	ENTER;
	
	struct lexstateset* universe = new_lexstateset();
	
	struct quack* todo = new_quack();
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler2(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[k" "zebu: minimize tokenizer (build universe): %u of %u (%.2f%%)\r",
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
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct lex_state* const to = state->transitions.data[i]->to;
			
			if (lexstateset_add(universe, to))
				quack_append(todo, to);
		}
		
		if (state->default_transition.to)
		{
			struct lex_state* const to = state->default_transition.to;
			
			if (lexstateset_add(universe, to))
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
}








