
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

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
	
	struct memory_arena* const arena = scope_get_arena(scope);
	
	char* name = arena_memdup(arena, tokenizer->tokenchars.chars, tokenizer->tokenchars.n + 1);
	
	dpvs(name);
	
	read_token(tokenizer, colon_machine);
	
	read_token(tokenizer, regex_root_machine);
	
	struct rbundle bun = read_root_token_expression(tokenizer, arena, scope, token_skip);
	
	if (bun.is_nfa)
	{
		struct regex* nfa = bun.nfa.start;
		
		bun.nfa.end->is_accepting = true;
		
		struct regex* dfa = regex_nfa_to_dfa(nfa, arena);
		
		free_regex(nfa, arena);
		
		struct regex* simp = regex_simplify_dfa(dfa, arena);
		
		free_regex(dfa, arena);
		
		scope_declare_fragment(scope, name, simp);
	}
	else
	{
		scope_declare_fragment(scope, name, bun.dfa);
	}
	
	TODO;
	#if 0
	if (true
		&& tokenizer->token != t_semicolon
		&& tokenizer->token != t_colon)
	{
		TODO;
		exit(e_syntax_error);
	}
	#endif
	
	EXIT;
}


















