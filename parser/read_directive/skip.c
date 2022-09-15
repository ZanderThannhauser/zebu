
#include <stddef.h>

#include <debug.h>

#include <regex/dfa_to_nfa.h>
#include <regex/state/add_lambda_transition.h>
#include <regex/state/struct.h>
#include <regex/state/free.h>
#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa/simplify_dfa.h>

#include <parser/token/root.h>

#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/misc/colon.h>
#include <parser/tokenizer/machines/regex/root.h>

#include <lex/struct.h>
#include <lex/lookup/add_token.h>

#include "skip.h"

void read_skip_directive(
	struct pragma_once* pragma_once,
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex,
	int absolute_dirfd,
	int relative_dirfd)
{
	ENTER;
	
	read_token(tokenizer, colon_machine);
	
	read_token(tokenizer, regex_root_machine);
	
	struct rbundle regex = read_root_token_expression(tokenizer, scope);
	
	if (!regex.is_nfa)
	{
		regex = regex_dfa_to_nfa(regex.dfa);
	}
	
	regex_add_lambda_transition(regex.nfa.end, regex.nfa.start);
	
	regex.nfa.end->is_accepting = true;
	
	struct regex* nfa = regex.nfa.start;
	
	struct regex* dfa = regex_nfa_to_dfa(nfa);
	
	struct regex* regex_start = regex_simplify_dfa(dfa);
	
	unsigned token_id = lex_add_token2(lex, regex_start, tk_whitespace);
	
	dpv(token_id);
	
	lex->whitespace_token_id = token_id;
	
	free_regex(nfa), free_regex(dfa);
	
	EXIT;
}













