
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

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_grammar_scalar_field.h>
#include <yacc/structinfo/add_grammar_array_field.h>
#include <yacc/structinfo/free.h>

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
					structinfo_add_grammar_scalar_field(structinfo, tag, full_name);
					break;
				
				case t_hashtag_array:
					structinfo_add_grammar_array_field(structinfo, tag, full_name);
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
		
		gegex_add_grammar_transition(start, full_name, structinfo, end);
		
		retval = (struct gbundle) {start, end};
		
		free_structinfo(structinfo);
		
		free_string(full_name);
		
		free_string(base_name);
	}
	
	#ifdef DOTOUT
	gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return retval;
}

















