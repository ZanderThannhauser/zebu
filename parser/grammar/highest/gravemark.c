
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <enums/error.h>

#include <string/new.h>
#include <string/free.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/free.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/token_names.h>

#include <parser/regex/root.h>

#include <gegex/new.h>
#include <gegex/add_transition.h>
#include <gegex/dotout.h>

#include <lex/struct.h>
#include <lex/add_token.h>

#include <regex/dfa_to_nfa.h>
#include <regex/clone.h>
#include <regex/dotout.h>
#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa.h>
#include <regex/struct.h>
#include <regex/free.h>
#include <regex/add_lambda_transition.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_token_scalar_field.h>
#include <yacc/structinfo/add_token_array_field.h>
#include <yacc/structinfo/free.h>

#include "gravemark.h"

struct gbundle read_gravemark_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	assert(tokenizer->token == t_gravemark);
	
	read_token(tokenizer);
	
	struct rbundle regex = read_root_token_expression(tokenizer, scope);
	
	struct regex* simp;
	
	if (regex.is_nfa)
	{
		struct regex* dfa = regex_nfa_to_dfa(regex);
		
		simp = regex_simplify_dfa(dfa);
		
		free_regex(regex.nfa.start), free_regex(dfa);
	}
	else
	{
		simp = regex.dfa;
	}
	
	unsigned token_id = lex_add_token(lex, simp, tk_regex);
	
	dpv(token_id);
	
	if (tokenizer->token != t_gravemark)
	{
		dpv(tokenizer->token);
		
		assert(token_names[tokenizer->token]);
		assert(token_names[t_gravemark]);
		
		fprintf(stderr, "zebu: error while reading end of regular expression: "
			"unexpected '%s' token on line %u, expecting '%s'!\n",
			token_names[tokenizer->token],
			tokenizer->line,
			token_names[t_gravemark]);
		
		exit(e_syntax_error);
	}
	
	read_token(tokenizer);
	
	struct structinfo* structinfo = new_structinfo(/* name: */ NULL);
	
	while (false
		|| tokenizer->token == t_scalar_hashtag
		|| tokenizer->token == t_array_hashtag)
	{
		struct string* tag = new_string_from_tokenchars(tokenizer);
		
		switch (tokenizer->token)
		{
			case t_scalar_hashtag:
				structinfo_add_token_scalar_field(structinfo, tag);
				break;
			
			case t_array_hashtag:
				structinfo_add_token_array_field(structinfo, tag);
				break;
			
			default:
				TODO;
				break;
		}
		
		read_token(tokenizer);
		
		free_string(tag);
	}
	
	struct gegex* start = new_gegex();
	struct gegex* end = new_gegex();
	
	struct unsignedset* whitespace = new_unsignedset();
	
	if (lex->whitespace_token_id)
	{
		unsignedset_add(whitespace, lex->whitespace_token_id);
	}
	
	gegex_add_transition(start, token_id, whitespace, structinfo, end);
	
	#ifdef DOTOUT
	gegex_dotout(start, end, __PRETTY_FUNCTION__);
	#endif
	
	free_structinfo(structinfo), free_unsignedset(whitespace);
	
	EXIT;
	return (struct gbundle) {start, end};
}










