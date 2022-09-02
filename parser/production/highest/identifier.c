
#include <debug.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/production/after_highest.h>

#include <parser/scope/lookup/inline_grammar.h>
#include <parser/scope/build_absolute_name.h>

#include <gegex/state/new.h>
#include <gegex/dotout.h>
#include <gegex/clone.h>
#include <gegex/dfa_to_nfa.h>
#include <gegex/state/add_grammar_transition.h>

#include <set/string/new.h>
#include <set/string/add.h>
#include <set/string/free.h>

#include "identifier.h"

struct gbundle read_identifier_production(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	dpvs(tokenizer->tokenchars.chars);
	
	struct gegex* inlined;
	
	if ((inlined = scope_lookup_inline_grammar(scope, (void*) tokenizer->tokenchars.chars)))
	{
		retval = gegex_dfa_to_nfa(gegex_clone(inlined));
		
		read_token(tokenizer, production_after_highest_machine);
	}
	else
	{
		struct string* base_name = new_string_from_tokenchars(tokenizer);
		
		struct string* full_name = scope_build_absolute_name(scope, base_name);
		
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
		
		gegex_add_grammar_transition(start, full_name, tags, end);
		
		retval = (struct gbundle) {start, end};
		
		free_stringset(tags);
		
		free_string(full_name);
		
		free_string(base_name);
	}
	
	#ifdef DOTOUT
	gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return retval;
}

















