

#include <assert.h>

#include <debug.h>

#include <set/regex/contains.h>
#include <set/regex/add.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/pop.h>
#include <quack/free.h>

#ifdef VERBOSE
#include <quack/struct.h>
#include <misc/default_sighandler.h>
#endif

#include "../state/struct.h"

#include "build_universe.h"

void regex_simplify_dfa_build_universe(
	struct regexset* universe,
	struct regex* start)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	quack_append(todo, start);
	
	regexset_add(universe, start);
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + todo->n;
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[k" "%s: regex simplify (build universe): %u of %u (%.2f%%)\r", argv0,
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
		
		struct regex* node = quack_pop(todo);
		
		for (unsigned i = 0, n = node->transitions.n; i < n; i++)
		{
			struct regex* to = node->transitions.data[i]->to;
			
			if (regexset_add(universe, to))
			{
				quack_append(todo, to);
			}
		}
		
		if (node->default_transition_to)
		{
			struct regex* to = node->default_transition_to;
			
			if (regexset_add(universe, to))
			{
				quack_append(todo, to);
			}
		}
		
		if (node->EOF_transition_to)
		{
			struct regex* to = node->EOF_transition_to;
			
			if (regexset_add(universe, to))
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








