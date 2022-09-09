
#include <assert.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/production/after_highest.h>

#include <parser/options/struct.h>

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

#include <lex/lookup/add_token.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_token_array_field.h>
#include <yacc/structinfo/add_token_scalar_field.h>
#include <yacc/structinfo/free.h>

#include "string_literal.h"

struct gbundle read_string_literal_production(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
	
	struct regex* regex_start = regex_from_literal(
		/* chars:  */ tokenizer->tokenchars.chars,
		/* strlen: */ tokenizer->tokenchars.n);
	
	if (options->skip)
	{
		struct rbundle nfa = regex_dfa_to_nfa(regex_start);
		
		struct regex* clone = regex_clone(options->skip);
		
		regex_add_lambda_transition(clone, regex_start);
		
		#ifdef DOTOUT
		regex_dotout(clone, __PRETTY_FUNCTION__);
		#endif
		
		nfa.nfa.end->is_accepting = true;
		
		struct regex* dfa = regex_nfa_to_dfa(clone);
		
		regex_start = regex_simplify_dfa(dfa);
		
		#ifdef DOTOUT
		regex_dotout(regex_start, __PRETTY_FUNCTION__);
		#endif
		
		free_regex(clone), free_regex(dfa);
	}
	
	unsigned token_id = lex_add_token(lex, regex_start, /* is_literal: */ true);
	
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
	
	gegex_add_transition(gegex_start, token_id, structinfo, gegex_end);
	
	free_structinfo(structinfo);
	
	#ifdef DOTOUT
	gegex_dotout(gegex_start, gegex_end, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct gbundle) {gegex_start, gegex_end};
}

























