
/*#include <avl/avl.h>*/
/*#include <avl/new.h>*/
/*#include <avl/free_tree.h>*/

#include <debug.h>

#include <memory/smalloc.h>

#include <misc/phase_counters.h>

#include "../dotout.h"

#include "../state/struct.h"

#include "regex_ll/new.h"
#include "regex_ll/free.h"

#include "survey.h"
#include "clone.h"
#include "simplify_dfa.h"

struct regex* regex_simplify_dfa(
	struct regex* original_start,
	struct memory_arena* arena)
{
	ENTER;
	
	struct regex_ll* unique_nodes = new_regex_ll();
	
	lex_phase_counter++;
	
	simplify_dfa_survey(unique_nodes, original_start);
	
	struct regex* new_start = regex_simplify_dfa_clone(
		unique_nodes, original_start, arena);
	
	free_regex_ll(unique_nodes);
	
	#ifdef DEBUGGING
	regex_dotout(new_start, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return new_start;
}
























