
#include <debug.h>

/*#include <avl/avl.h>*/
/*#include <avl/safe_insert.h>*/

#include <memory/sstrndup.h>

#include <lex/regex/simplify_dfa/simplify_dfa.h>
#include <lex/regex/nfa_to_dfa/nfa_to_dfa.h>
#include <lex/regex/state/struct.h>
#include <lex/regex/state/free.h>

#include "scope/declare/token.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/colon.h"
#include "tokenizer/machines/expression/root.h"

#include "token/root.h"
#include "token/rbundle.h"

#include "read_fragment.h"

void read_fragment(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct scope* scope)
{
	ENTER;
	
	assert(tokenizer->token == t_fragment);
	
	char* name = sstrndup(
		/* src: */ tokenizer->tokenchars.chars + 1,
		/* len: */ tokenizer->tokenchars.n - 2);
	
	dpvs(name);
	
	read_token(tokenizer, colon_machine);
	
	read_token(tokenizer, expression_root_machine);
	
	struct rbundle bun = read_root_token_expression(tokenizer, scratchpad, scope);
	
	if (bun.is_nfa)
	{
		struct regex* nfa = bun.nfa.start;
		
		bun.nfa.end->is_accepting = true;
		
		struct regex* dfa = regex_nfa_to_dfa(nfa, scratchpad);
		
		free_regex(nfa, scratchpad);
		
		struct regex* simp = regex_simplify_dfa(dfa, scratchpad);
		
		free_regex(dfa, scratchpad);
		
		bun.is_nfa = false;
		bun.dfa = simp;
	}
	
	scope_declare_token(scope, name, bun.dfa);
	
	if (true
		&& tokenizer->token != t_semicolon
		&& tokenizer->token != t_colon)
	{
		TODO;
		exit(e_syntax_error);
	}
	
	EXIT;
}


















