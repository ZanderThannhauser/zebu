
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <enums/error.h>

/*#include <avl/avl.h>*/
/*#include <avl/safe_insert.h>*/

#include <arena/memdup.h>

#include <lex/regex/simplify_dfa/simplify_dfa.h>
#include <lex/regex/nfa_to_dfa/nfa_to_dfa.h>
#include <lex/regex/state/struct.h>
#include <lex/regex/state/free.h>

#include "scope/get_arena.h"

#include "scope/declare/fragment.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/misc/colon.h"
#include "tokenizer/machines/regex/root.h"

#include "token/root.h"
#include "token/rbundle.h"

#include "read_fragment.h"

void read_fragment(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct regex* token_skip)
{
	ENTER;
	
	assert(tokenizer->token == t_gravemarked_identifier);
	
	dpvs(tokenizer->tokenchars.chars);
	
	#ifdef WITH_ARENAS
	struct memory_arena* const arena = scope_get_arena(scope);
	char* name = arena_memdup(arena, tokenizer->tokenchars.chars, tokenizer->tokenchars.n + 1);
	
	#else
	
	char* name = strdup(tokenizer->tokenchars.chars);
	#endif
	
	dpvs(name);
	
	read_token(tokenizer, colon_machine);
	
	read_token(tokenizer, regex_root_machine);
	
	#ifdef WITH_ARENAS
	struct rbundle bun = read_root_token_expression(arena, tokenizer, scope, token_skip);
	#else
	struct rbundle bun = read_root_token_expression(tokenizer, scope, token_skip);
	#endif
	
	if (bun.is_nfa)
	{
		struct regex* nfa = bun.nfa.start;
		
		bun.nfa.end->is_accepting = true;
		
		#ifdef WITH_ARENAS
		struct regex* dfa = regex_nfa_to_dfa(arena, nfa);
		struct regex* simp = regex_simplify_dfa(arena, dfa);
		#else
		struct regex* dfa = regex_nfa_to_dfa(nfa);
		struct regex* simp = regex_simplify_dfa(dfa);
		#endif
		
		scope_declare_fragment(scope, name, simp);
		
		free_regex(nfa), free_regex(dfa);
	}
	else
	{
		scope_declare_fragment(scope, name, bun.dfa);
	}
	
	if (true
		&& tokenizer->token != t_semicolon
		&& tokenizer->token != t_colon)
	{
		TODO;
		exit(e_syntax_error);
	}
	
	EXIT;
}


















