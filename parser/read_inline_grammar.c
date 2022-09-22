
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <enums/error.h>

/*#include <arena/memdup.h>*/

#include <gegex/struct.h>
/*#include <gegex/state/new.h>*/
#include <gegex/nfa_to_dfa.h>
#include <gegex/simplify_dfa.h>
#include <gegex/free.h>

#include "grammar/root.h"
/*#include "grammar/gbundle.h"*/

#include "scope/declare/inline_grammar.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"

/*#include "scope/get_arena.h"*/

#include "read_inline_grammar.h"

void read_inline_grammar(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_oparen);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_identifier)
	{
		TODO;
		exit(1);
	}
	
	struct string* name = new_string_from_tokenchars(tokenizer);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_cparen)
	{
		TODO;
		exit(1);
	}
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_colon)
	{
		TODO;
		exit(1);
	}
	
	read_token(tokenizer);
	
	struct gbundle nfa = read_root_production(tokenizer, scope, lex);
	
	struct gegex* dfa = gegex_nfa_to_dfa(nfa);
	
	struct gegex* simp = gegex_simplify_dfa(dfa);
	
	scope_declare_inline_grammar(scope, name, simp);
	
	if (true
		&& tokenizer->token != t_semicolon
		&& tokenizer->token != t_colon)
	{
		TODO;
		exit(e_syntax_error);
	}
	
	free_gegex(nfa.start);
	
	free_gegex(dfa);
	
	free_string(name);
	
	EXIT;
}











