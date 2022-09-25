
#include <assert.h>
#include <stdbool.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>

#include <parser/scope/lookup/inline_grammar.h>
#include <parser/scope/build_absolute_name.h>

#include <gegex/new.h>
#include <gegex/dotout.h>
#include <gegex/clone.h>
#include <gegex/dfa_to_nfa.h>
#include <gegex/add_grammar_transition.h>

#include <yacc/structinfo/new.h>
#include <yacc/structinfo/add_grammar_scalar_field.h>
#include <yacc/structinfo/add_grammar_array_field.h>
#include <yacc/structinfo/free.h>

#include "identifier.h"

struct gbundle read_identifier_production(
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	dpvs(tokenizer->tokenchars.chars);
	
	struct gegex* inlined;
	
	if ((inlined = scope_lookup_inline_grammar(scope, (void*) tokenizer->tokenchars.chars)))
	{
		struct gbundle clone = gegex_clone2((struct gbundle) {inlined, NULL});
		
		retval = gegex_dfa_to_nfa(clone.start);
		
		read_token(tokenizer);
	}
	else
	{
		struct string* base_name = new_string_from_tokenchars(tokenizer);
		
		struct string* full_name = scope_build_absolute_name(scope, base_name);
		
		struct structinfo* structinfo = new_structinfo();
		
		read_token(tokenizer);
		
		while (false
			|| tokenizer->token == t_scalar_hashtag
			|| tokenizer->token == t_array_hashtag)
		{
			struct string* tag = new_string_from_tokenchars(tokenizer);
			
			switch (tokenizer->token)
			{
				case t_scalar_hashtag:
					structinfo_add_grammar_scalar_field(structinfo, tag, full_name);
					break;
				
				case t_array_hashtag:
					structinfo_add_grammar_array_field(structinfo, tag, full_name);
					break;
				
				default:
					TODO;
					break;
			}
			
			read_token(tokenizer);
			
			free_string(tag);
		}
		
		struct gegex* start = new_gegex();
		struct gegex* accepts = new_gegex();
		
		gegex_add_grammar_transition(start, full_name, structinfo, accepts);
		
		retval = (struct gbundle) {start, accepts};
		
		free_structinfo(structinfo);
		
		free_string(full_name);
		
		free_string(base_name);
	}
	
	#ifdef DOTOUT
	gegex_dotout(retval.start, retval.accepts, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return retval;
}

















