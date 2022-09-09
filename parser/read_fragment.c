
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <enums/error.h>

/*#include <avl/avl.h>*/
/*#include <avl/safe_insert.h>*/

/*#include <arena/memdup.h>*/

#include <regex/simplify_dfa/simplify_dfa.h>
#include <regex/nfa_to_dfa.h>
#include <regex/state/struct.h>
#include <regex/state/free.h>

/*#include "scope/get_arena.h"*/

#include "scope/declare/fragment.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/misc/colon.h"
#include "tokenizer/machines/regex/root.h"

#include "token/root.h"
/*#include "token/rbundle.h"*/

#include "read_fragment.h"

void read_fragment(struct tokenizer* tokenizer, struct scope* scope)
{
	ENTER;
	
	assert(tokenizer->token == t_gravemarked_identifier);
	
	dpvs(tokenizer->tokenchars.chars);
	
	struct string* name = new_string_from_tokenchars(tokenizer);
	
	read_token(tokenizer, colon_machine);
	
	read_token(tokenizer, regex_root_machine);
	
	struct rbundle bun = read_root_token_expression(tokenizer, scope);
	
	if (bun.is_nfa)
	{
		struct regex* nfa = bun.nfa.start;
		
		bun.nfa.end->is_accepting = true;
		
		struct regex* dfa = regex_nfa_to_dfa(nfa);
		
		struct regex* simp = regex_simplify_dfa(dfa);
		
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
	
	free_string(name);
	
	EXIT;
}

















