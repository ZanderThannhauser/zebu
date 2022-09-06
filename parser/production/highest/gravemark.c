
#include <debug.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/regex/root.h>
#include <parser/tokenizer/machines/production/after_highest.h>

#include <parser/token/root.h>

#include <parser/options/struct.h>

#include <gegex/state/new.h>
#include <gegex/state/add_transition.h>
#include <gegex/dotout.h>

#include <lex/lookup/add_token.h>

#include <regex/dfa_to_nfa.h>
#include <regex/clone.h>
#include <regex/dotout.h>
#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa/simplify_dfa.h>
#include <regex/state/struct.h>
#include <regex/state/free.h>
#include <regex/state/add_lambda_transition.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_token_scalar_field.h>
#include <yacc/structinfo/add_token_array_field.h>
#include <yacc/structinfo/free.h>

#include "gravemark.h"

struct gbundle read_gravemark_production(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	read_token(tokenizer, regex_root_machine);
	
	struct rbundle regex = read_root_token_expression(tokenizer, scope);
	
	if (tokenizer->token != t_gravemark)
	{
		TODO;
		exit(1);
	}
	
	struct regex* regex_start;
	
	if (options->skip)
	{
		if (!regex.is_nfa)
		{
			regex = regex_dfa_to_nfa(regex.dfa);
		}
		
		struct regex* clone = regex_clone(options->skip);
		
		regex_add_lambda_transition(clone, regex.nfa.start);
		
		regex.nfa.start = clone;
		
		#ifdef DOTOUT
		regex_dotout(regex.nfa.start, __PRETTY_FUNCTION__);
		#endif
	}
	
	if (regex.is_nfa)
	{
		regex.nfa.end->is_accepting = true;
		
		struct regex* nfa = regex.nfa.start;
		
		struct regex* dfa = regex_nfa_to_dfa(nfa);
		
		regex_start = regex_simplify_dfa(dfa);
		
		free_regex(nfa), free_regex(dfa);
	}
	else
	{
		regex_start = regex.dfa;
	}
	
	unsigned token_id = lex_add_token(lex, regex_start, regex.is_literal);
	
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
	
	struct gegex* start = new_gegex();
	struct gegex* end = new_gegex();
	
	gegex_add_transition(start, token_id, structinfo, end);
	
	free_structinfo(structinfo);
	
	#ifdef DOTOUT
	gegex_dotout(start, end, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct gbundle) {start, end};
}











