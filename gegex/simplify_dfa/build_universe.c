
#include <assert.h>

#include <debug.h>

#include <set/gegex/add.h>

#ifdef VERBOSE
#include <misc/default_sighandler.h>
#endif

#include "../state/struct.h"

#include "build_universe.h"

void gegex_simplify_dfa_build_universe(
	struct gegexset* universe,
	struct gegex* start)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	quack_append(todo, start);
	
	gegexset_add(universe, start);
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: grammar simplify (build universe): %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler);
	#endif
	
	while (quack_len(todo))
	{
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct gegex* node = quack_pop(todo);
		
		for (unsigned i = 0, n = node->transitions.n; i < n; i++)
		{
			struct gegex* to = node->transitions.data[i]->to;
			
			if (gegexset_add(universe, to))
			{
				quack_append(todo, to);
			}
		}
		
		for (unsigned i = 0, n = node->grammar_transitions.n; i < n; i++)
		{
			struct gegex* to = node->grammar_transitions.data[i]->to;
			
			if (gegexset_add(universe, to))
			{
				quack_append(todo, to);
			}
		}
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	free_quack(todo);
	
	EXIT;
}








