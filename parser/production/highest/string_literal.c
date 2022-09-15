
#include <assert.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/production/after_highest.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/free.h>

#include <gegex/from_token.h>
#include <gegex/dotout.h>
#include <gegex/state/new.h>
#include <gegex/state/add_transition.h>

#include <regex/clone.h>
#include <regex/dotout.h>
#include <regex/dfa_to_nfa.h>
#include <regex/from_literal.h>
#include <regex/state/free.h>
#include <regex/state/struct.h>
#include <regex/state/add_lambda_transition.h>
#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa/simplify_dfa.h>

#include <lex/struct.h>
#include <lex/lookup/add_token.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_token_array_field.h>
#include <yacc/structinfo/add_token_scalar_field.h>
#include <yacc/structinfo/free.h>

#include "string_literal.h"

struct gbundle read_string_literal_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
	
	struct regex* regex_start = regex_from_literal(
		/* chars:  */ tokenizer->tokenchars.chars,
		/* strlen: */ tokenizer->tokenchars.n);
	
	unsigned token_id = lex_add_token2(lex, regex_start, tk_literal);
	
	dpv(token_id);
	
	struct structinfo* structinfo = new_structinfo(/* name: */ NULL);
	
	read_token(tokenizer, production_after_highest_machine);
	
	while (false
		|| tokenizer->token == t_hashtag_scalar
		|| tokenizer->token == t_hashtag_array)
	{
		struct string* tag = new_string_from_tokenchars(tokenizer);
		
		switch (tokenizer->token)
		{
			case t_hashtag_scalar:
				structinfo_add_token_scalar_field(structinfo, tag);
				break;
			
			case t_hashtag_array:
				structinfo_add_token_array_field(structinfo, tag);
				break;
			
			default:
				TODO;
				break;
		}
		
		read_token(tokenizer, production_after_highest_machine);
		
		free_string(tag);
	}
	
	struct gegex* gegex_start = new_gegex();
	
	struct gegex* gegex_end = new_gegex();
	
	struct unsignedset* whitespace = new_unsignedset();
	
	if (lex->whitespace_token_id)
	{
		unsignedset_add(whitespace, lex->whitespace_token_id);
	}
	
	gegex_add_transition(gegex_start, token_id, whitespace, structinfo, gegex_end);
	
	#ifdef DOTOUT
	gegex_dotout(gegex_start, gegex_end, __PRETTY_FUNCTION__);
	#endif
	
	free_unsignedset(whitespace);
	
	free_structinfo(structinfo);
	
	EXIT;
	return (struct gbundle) {gegex_start, gegex_end};
}

























