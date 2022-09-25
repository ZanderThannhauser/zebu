
#include <assert.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/free.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>

#include <regex/nfa_to_dfa.h>
#include <regex/dfa_to_nfa.h>
#include <regex/clone.h>
#include <regex/dotout.h>
#include <regex/struct.h>
#include <regex/free.h>
#include <regex/add_lambda_transition.h>
#include <regex/simplify_dfa.h>
#include <regex/from_literal.h>

#include <lex/struct.h>
#include <lex/add_token.h>

#include <gegex/dotout.h>
#include <gegex/new.h>
#include <gegex/add_transition.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_token_array_field.h>
#include <yacc/structinfo/add_token_scalar_field.h>
#include <yacc/structinfo/free.h>

#include "character_literal.h"

struct gbundle read_character_literal_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	unsigned char code = tokenizer->tokenchars.chars[0];
	
	dpvc(code);
	
	struct regex* regex = regex_from_literal(&code, 1);
	
	unsigned token_id = lex_add_token(lex, regex, tk_literal);
	
	dpv(token_id);
	
	struct structinfo* tags = new_structinfo();
	
	read_token(tokenizer);
	
	while (false
		|| tokenizer->token == t_scalar_hashtag
		|| tokenizer->token == t_array_hashtag)
	{
		struct string* tag = new_string_from_tokenchars(tokenizer);
		
		switch (tokenizer->token)
		{
			case t_scalar_hashtag:
				structinfo_add_token_scalar_field(tags, tag);
				break;
			
			case t_array_hashtag:
				structinfo_add_token_array_field(tags, tag);
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
	
	gegex_add_transition(start, token_id, whitespace, tags, end);
	
	#ifdef DOTOUT
	gegex_dotout(start, end, __PRETTY_FUNCTION__);
	#endif
	
	free_structinfo(tags), free_unsignedset(whitespace);
	
	EXIT;
	return (struct gbundle) {start, end};
}

























