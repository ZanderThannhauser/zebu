
#include <debug.h>

#include <memory/arena/strdup.h>

#include "scope/declare/grammar.h"

#include "production/gegex/dotout.h"
#include "production/gegex/state/new.h"
#include "production/gegex/state/add_grammar_transition.h"

#include "create_start_rule.h"

void create_start_rule(
	struct scope* scope,
	struct memory_arena* scratchpad,
	const char* users_start_rule)
{
	ENTER;
	
	dpvs(users_start_rule);
	
	struct gegex* start = new_gegex(scratchpad);
	
	struct gegex* end = new_gegex(scratchpad);
	// end state should reduce on EOF
	
	char* dup = arena_strdup(scratchpad, users_start_rule);
	
	dpvs(dup);
	
	gegex_add_grammar_transition(start, scratchpad, dup, end);
	
	#ifdef DEBUGGING
	gegex_dotout(start, end);
	#endif
	
	scope_declare_grammar(scope, "(start)", start, end);
	
	EXIT;
}













