
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

#include <regex/simplify_dfa.h>
#include <regex/nfa_to_dfa.h>
#include <regex/struct.h>
#include <regex/free.h>

/*#include "scope/get_arena.h"*/

#include "scope/declare/fragment.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"

#include "regex/root.h"
/*#include "token/rbundle.h"*/

#include "read_fragment.h"

void read_fragment(struct tokenizer* tokenizer, struct scope* scope)
{
	ENTER;
	
	assert(tokenizer->token == t_gravemark);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_identifier)
	{
		TODO;
		exit(1);
	}
	
	dpvs(tokenizer->tokenchars.chars);
	
	struct string* name = new_string_from_tokenchars(tokenizer);
	
	read_token(tokenizer);
	
	if (tokenizer->token != t_gravemark)
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
	
	struct rbundle regex = read_root_token_expression(tokenizer, scope);
	
	if (regex.accepts)
	{
		struct regex* dfa = regex_nfa_to_dfa(regex);
		
		struct regex* simp = regex_simplify_dfa(dfa);
		
		scope_declare_fragment(scope, name, simp);
		
		free_regex(regex.start), free_regex(dfa);
	}
	else
	{
		scope_declare_fragment(scope, name, regex.start);
	}
	
	free_string(name);
	
	EXIT;
}

















