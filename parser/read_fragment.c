
#include <debug.h>

#include <memory/sstrdup.h>

#include <regex/nfa_to_dfa/nfa_to_dfa.h>

#include <regex/simplify_dfa/simplify_dfa.h>

#include <regex/state/free.h>

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/colon.h"
#include "tokenizer/machines/root.h"
#include "tokenizer/machines/expression_root.h"

#include "expression/root.h"

#include "read_fragment.h"

void read_fragment(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_fragment);
	
	char* name = ({
		char* original = tokenizer->tokenchars.chars + 1;
		original[tokenizer->tokenchars.n - 2] = 0;
		sstrdup(original);
	});
	
	dpvs(name);
	
	read_token(tokenizer, colon_machine);
	
	read_token(tokenizer, expression_root_machine);
	
	struct bundle bun = read_root_token_expression(scratchpad, tokenizer);
	
	if (tokenizer->token != t_semicolon)
	{
		TODO;
		exit(e_syntax_error);
	}
	
	read_token(tokenizer, root_machine);
	
	struct regex* simp;
	
	if (bun.is_nfa)
	{
		struct regex* nfa = bun.regex;
		
		struct regex* dfa = regex_nfa_to_dfa(nfa, scratchpad);
		
		free_regex(nfa, scratchpad);
		
		simp = regex_simplify_dfa(dfa, scratchpad);
	}
	else
	{
		simp = bun.regex;
	}
	
	dpvs(name);
	dpv(simp);
	
	TODO;
	#if 0
	// add fragment to fragment lookup
	TODO;
	
	// format scratchpad:
	TODO;
	#endif
	
	free(name);
	
	EXIT;
}














