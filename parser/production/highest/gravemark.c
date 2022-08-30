
#include <debug.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/regex/root.h>
#include <parser/tokenizer/machines/production/after_highest.h>

#include <parser/token/root.h>

#include <parser/options/struct.h>

#include <yacc/gegex/state/new.h>
#include <yacc/gegex/state/add_transition.h>
#include <yacc/gegex/dotout.h>

#include <set/string/new.h>
#include <set/string/add.h>
#include <set/string/free.h>

#include <lex/lookup/add_token.h>

#include <lex/regex/dfa_to_nfa.h>
#include <lex/regex/clone.h>
#include <lex/regex/dotout.h>
#include <lex/regex/nfa_to_dfa.h>
#include <lex/regex/simplify_dfa/simplify_dfa.h>
#include <lex/regex/state/struct.h>
#include <lex/regex/state/free.h>
#include <lex/regex/state/add_lambda_transition.h>

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
	
	struct rbundle regex = read_root_token_expression(tokenizer, scope, options->token_skip);
	
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
	
	struct stringset* tags = new_stringset();
	
	read_token(tokenizer, production_after_highest_machine);
	
	while (tokenizer->token == t_hashtag)
	{
		char* dup = strdup((void*) tokenizer->tokenchars.chars);
		
		stringset_add(tags, dup);
		
		read_token(tokenizer, production_after_highest_machine);
	}
	
	struct gegex* start = new_gegex();
	struct gegex* end = new_gegex();
	
	dpv(start);
	dpv(end);
	
	gegex_add_transition(start, token_id, tags, end);
	
	#ifdef DOTOUT
	gegex_dotout(start, end, __PRETTY_FUNCTION__);
	#endif
	
	free_stringset(tags);
	
	EXIT;
	return (struct gbundle) {start, end};
}











