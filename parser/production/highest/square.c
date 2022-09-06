
#include <debug.h>

#include <parser/charset/root.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/charset/root.h>
#include <parser/tokenizer/machines/production/after_highest.h>

#include <parser/options/struct.h>

#include <set/string/new.h>
#include <set/string/add.h>
#include <set/string/free.h>

#include <regex/from_charset.h>
#include <regex/dfa_to_nfa.h>
#include <regex/nfa_to_dfa.h>
#include <regex/simplify_dfa/simplify_dfa.h>
#include <regex/clone.h>
#include <regex/dotout.h>
#include <regex/state/struct.h>
#include <regex/state/add_lambda_transition.h>
#include <regex/state/free.h>

#include <lex/lookup/add_token.h>

#include <gegex/state/new.h>
#include <gegex/state/add_transition.h>
#include <gegex/dotout.h>

#include "square.h"

struct gbundle read_square_production(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	ENTER;
	
	read_token(tokenizer, charset_root_machine);
	
	charset_t charset = read_root_charset(tokenizer, scope);
	
	if (tokenizer->token != t_csquare)
	{
		TODO;
		exit(1);
	}
	
	struct regex* regex_start = regex_from_charset(charset);
	
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
	
	unsigned token_id = lex_add_token(lex, regex_start, false);
	
	dpv(token_id);
	
	TODO;
	#if 0
	struct stringset* tags = new_stringset();
	
	read_token(tokenizer, production_after_highest_machine);
	
	while (tokenizer->token == t_hashtag)
	{
		struct string* tag = new_string_from_tokenchars(tokenizer);
		
		stringset_add(tags, tag);
		
		read_token(tokenizer, production_after_highest_machine);
		
		free_string(tag);
	}
	
	struct gegex* start = new_gegex();
	struct gegex* end = new_gegex();
	
	gegex_add_transition(start, token_id, tags, end);
	
	free_stringset(tags);
	
	#ifdef DOTOUT
	gegex_dotout(start, end, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return (struct gbundle) {start, end};
	#endif
}








