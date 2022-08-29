
#include <debug.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/production/after_highest.h>

#include <parser/options/struct.h>

#include <yacc/gegex/from_token.h>
#include <yacc/gegex/dotout.h>
#include <yacc/gegex/state/new.h>
#include <yacc/gegex/state/add_transition.h>

#include <set/string/new.h>
#include <set/string/add.h>

#include <lex/regex/clone.h>
#include <lex/regex/dotout.h>
#include <lex/regex/dfa_to_nfa.h>
#include <lex/regex/from_literal.h>
#include <lex/regex/state/free.h>
#include <lex/regex/state/struct.h>
#include <lex/regex/state/add_lambda_transition.h>
#include <lex/regex/nfa_to_dfa.h>
#include <lex/regex/simplify_dfa/simplify_dfa.h>

#include <lex/lookup/add_token.h>

#include "string_literal.h"

struct gbundle read_string_literal_production(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
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
	
	struct stringset* tags = new_stringset();
	
	read_token(tokenizer, production_after_highest_machine);
	
	while (tokenizer->token == t_hashtag)
	{
		dpvs(tokenizer->tokenchars.chars);
		
		char* tag = strdup((void*) tokenizer->tokenchars.chars);
		
		stringset_add(tags, tag);
		
		read_token(tokenizer, production_after_highest_machine);
	}
	
	struct gegex* gegex_start = new_gegex();
	
	struct gegex* gegex_end = new_gegex();
	
	gegex_add_transition(gegex_start, token_id, tags, gegex_end);
	
	#ifdef DOTOUT
	gegex_dotout(gegex_start, gegex_end, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct gbundle) {gegex_start, gegex_end};
}


















