
#include <debug.h>

#include <memory/sstrdup.h>

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/colon.h"
#include "tokenizer/machines/root.h"
#include "tokenizer/machines/expression_root.h"

#include "expression/root.h"

#include "read_fragment.h"

int read_fragment(
	struct tokenizer* tokenizer,
	struct memory_arena* token_scratchpad,
	struct lex* lex)
{
	int error = 0;
	ENTER;
	
	assert(tokenizer->token == t_fragment);
	
	char* name = NULL;
	
	bool is_nfa;
	struct regex_state* regex = NULL;
	
	tokenizer->tokenchars.chars[tokenizer->tokenchars.n - 1] = 0;
	
	error = 0
		?: sstrdup(&name, tokenizer->tokenchars.chars + 1)
		?: read_token(tokenizer, colon_machine)
		?: read_token(tokenizer, expression_root_machine)
		?: read_root_token_expression(&is_nfa, &regex, token_scratchpad, tokenizer);
	
	TODO;
	#if 0
	if (!error && tokenizer->token != t_semicolon)
	{
		TODO;
		error = e_syntax_error;
	}
	
	if (!error)
		error = read_token(tokenizer, root_machine);
	
	dpvs(name);
	dpv(regex);
	
	// add fragment to fragment lookup
	TODO;
	
	// format scratchpad:
	TODO;
	
	free(name);
	#endif
	
	EXIT;
	return error;
}














