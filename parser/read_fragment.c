
#include <debug.h>

#include <avl/avl.h>
#include <avl/safe_insert.h>

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

#include "fragment/new.h"

#include "read_fragment.h"

void read_fragment(
	struct tokenizer* tokenizer,
	struct memory_arena* scratchpad,
	struct avl_tree_t* fragments)
{
	ENTER;
	
	assert(tokenizer->token == t_fragment);
	
	char* name;
	{
		char* original = tokenizer->tokenchars.chars + 1;
		
		original[tokenizer->tokenchars.n - 2] = 0;
		
		name = sstrdup(original);
	}
	
	dpvs(name);
	
	if (avl_search(fragments, &name))
	{
		TODO;
		exit(e_bad_input_file);
	}
	
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
		
		free_regex(dfa, scratchpad);
	}
	else
	{
		simp = bun.regex;
	}
	
	dpvs(name);
	dpv(simp);
	
	safe_avl_insert(fragments, new_fragment(name, simp));
	
	EXIT;
}


















