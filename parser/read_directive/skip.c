
#include <stddef.h>

#include <debug.h>

#include <regex/dfa_to_nfa.h>
#include <regex/state/add_lambda_transition.h>
#include <regex/state/free.h>

#include <parser/options/struct.h>

#include <parser/token/root.h>

#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/misc/colon.h>
#include <parser/tokenizer/machines/regex/root.h>

#include "skip.h"

void read_skip_directive(
	struct pragma_once* pragma_once,
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex,
	int absolute_dirfd,
	int relative_dirfd)
{
	ENTER;
	
	free_regex(options->skip), options->skip = NULL;
	
	read_token(tokenizer, colon_machine);
	
	read_token(tokenizer, regex_root_machine);
	
	struct rbundle bun = read_root_token_expression(tokenizer, scope);
	
	if (!bun.is_nfa)
	{
		bun = regex_dfa_to_nfa(bun.dfa);
	}
	
	regex_add_lambda_transition(bun.nfa.end, bun.nfa.start);
	
	options->skip = bun.nfa.start;
	
	EXIT;
}

